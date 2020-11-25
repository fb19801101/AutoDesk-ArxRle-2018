//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRlePersistentEntReactor.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRleUiTdcPersistentReactors.h"



Adesk::Int16     ArxRlePersistentEntReactor::m_version = 0;     // MDI safe

ACRX_DXF_DEFINE_MEMBERS(ArxRlePersistentEntReactor, ArxRlePersistentObjReactor,
						AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
						0, ARXRLE_PERSISTENT_ENT_REACTOR, ArxRle);

/****************************************************************************
**
**  ArxRlePersistentEntReactor::dwgInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRlePersistentEntReactor::dwgInFields(AcDbDwgFiler* filer)
{
    Acad::ErrorStatus es;
    if ((es = ArxRlePersistentObjReactor::dwgInFields(filer)) != Acad::eOk)
        return es;

    Adesk::Int16 version;
    filer->readItem(&version);
    //if (version > m_version)
    //    return Acad::eMakeMeProxy;

	// we don't have any data at this level yet, but we still want to file
	// out version in case we do some day.

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRlePersistentEntReactor::dwgOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRlePersistentEntReactor::dwgOutFields(AcDbDwgFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxRlePersistentObjReactor::dwgOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(m_version);

	// we don't have any data at this level yet, but we still want to file
	// out version in case we do some day.

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRlePersistentEntReactor::dxfInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRlePersistentEntReactor::dxfInFields(AcDbDxfFiler* filer)
{
    Acad::ErrorStatus es;
    if (((es = ArxRlePersistentObjReactor::dxfInFields(filer)) != Acad::eOk) ||
        (filer->atSubclassData(this->desc()->name()) != Adesk::kTrue))
        return filer->filerStatus();

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRlePersistentEntReactor::dxfOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRlePersistentEntReactor::dxfOutFields(AcDbDxfFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxRlePersistentObjReactor::dxfOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(AcDb::kDxfSubclass, this->desc()->name());

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRlePersistentEntReactor::modifiedGraphics
**
**  **jma
**
*************************************/

void
ArxRlePersistentEntReactor::modifiedGraphics(const AcDbObject* obj)
{
    printReactorMessage(_T("Modified Graphics"), obj);
    ArxRleUiTdcPersistentReactors::doStateDboxModifiedGraphics(obj);
}

/****************************************************************************
**
**  ArxRlePersistentEntReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRlePersistentEntReactor::printReactorMessage(LPCTSTR event, const AcDbObject* obj) const
{
    CString str;

    if (obj != NULL) {
        acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T("{ENT P-REACTOR}"), event,
                ArxRleUtils::objToClassStr(obj), ArxRleUtils::objToHandleStr(obj, str));
    }
    else {
        acutPrintf(_T("\n%-15s : {%-18s: } "), _T("{ENT P-REACTOR}"), event);
    }
}
