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

#include "ArxRleTransientObjReactor.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRleUiTdcTransientReactors.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleTransientObjReactor, AcDbObjectReactor);

/****************************************************************************
**
**  ArxRleTransientObjReactor::~ArxRleTransientObjReactor
**
**  **jma
**
*************************************/

ArxRleTransientObjReactor::~ArxRleTransientObjReactor()
{
    delFromAll();
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::addToObject
**
**  **jma
**
*************************************/

bool
ArxRleTransientObjReactor::addToObject(AcDbObject* obj)
{
    ASSERT(obj != NULL);
    ASSERT(obj->isWriteEnabled() == Adesk::kTrue);

    if (m_objList.contains(obj->objectId()))
        return false;
    else {
        obj->addReactor(this);
        m_objList.append(obj->objectId());
        return true;
    }
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::delFromObject
**
**  **jma
**
*************************************/

bool
ArxRleTransientObjReactor::delFromObject(AcDbObject* obj)
{
    ASSERT(obj != NULL);
    ASSERT(obj->isWriteEnabled() == Adesk::kTrue);

    int index;
    if (m_objList.find(obj->objectId(), index)) {
        obj->removeReactor(this);
        m_objList.removeAt(index);
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::delFromAll
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::delFromAll()
{
    AcDbObject* obj;
    Acad::ErrorStatus es;

    int length = m_objList.length();
    for (int i=0; i<length; i++) {
            // must open erased entities too!
        es = acdbOpenObject(obj, m_objList[i], AcDb::kForWrite, true);
        if (es == Acad::eOk) {
            obj->removeReactor(this);
            obj->close();
        }
        else
            ArxRleUtils::rxErrorAlert(es);
    }
    m_objList.setLogicalLength(0);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::cancelled
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::cancelled(const AcDbObject* obj)
{
    printReactorMessage(_T("Cancelled"), obj);
    ArxRleUiTdcTransientReactors::doStateDboxCacelled(obj);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::copied
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::copied(const AcDbObject* obj, const AcDbObject* newObj)
{
    CString str;

    printReactorMessage(_T("Copied"), obj);
    acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T(""), _T("New Object"),
            ArxRleUtils::objToClassStr(newObj), ArxRleUtils::objToHandleStr(newObj, str));
    ArxRleUiTdcTransientReactors::doStateDboxCopied(obj, newObj);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::erased
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::erased(const AcDbObject* obj, Adesk::Boolean pErasing)
{
    if (pErasing)
        printReactorMessage(_T("Erase"), obj);
    else
        printReactorMessage(_T("Un-erase"), obj);

    ArxRleUiTdcTransientReactors::doStateDboxErased(obj, pErasing);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::goodbye
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::goodbye(const AcDbObject* obj)
{
    printReactorMessage(_T("Goodbye"), obj);
    ArxRleUiTdcTransientReactors::doStateDboxGoodbye(obj);

	m_objList.remove(obj->objectId());	// remove this from the list of things we are keeping track of
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::openedForModify
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::openedForModify(const AcDbObject* obj)
{
    printReactorMessage(_T("Open For Modify"), obj);
    ArxRleUiTdcTransientReactors::doStateDboxOpenedModify(obj);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::modified
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::modified(const AcDbObject* obj)
{
    printReactorMessage(_T("Modified"), obj);
    ArxRleUiTdcTransientReactors::doStateDboxModified(obj);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::subObjModified
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::subObjModified(const AcDbObject* obj, const AcDbObject* subObj)
{
    CString str;

    printReactorMessage(_T("Sub-Obj Modified"), obj);
    acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T(""), _T("Sub Object"),
            ArxRleUtils::objToClassStr(subObj), ArxRleUtils::objToHandleStr(subObj, str));

    ArxRleUiTdcTransientReactors::doStateDboxSubObjModified(obj, subObj);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::modifyUndone
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::modifyUndone(const AcDbObject* obj)
{
    printReactorMessage(_T("Modify Undone"), obj);
    ArxRleUiTdcTransientReactors::doStateDboxModifyUndone(obj);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::modifiedXData
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::modifiedXData(const AcDbObject* obj)
{
    printReactorMessage(_T("Modified Xdata"), obj);
    ArxRleUiTdcTransientReactors::doStateDboxModifiedXdata(obj);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::unappended
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::unappended(const AcDbObject* obj)
{
    printReactorMessage(_T("Un-appended"), obj);
    ArxRleUiTdcTransientReactors::doStateDboxUnappended(obj);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::reappended
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::reappended(const AcDbObject* obj)
{
    printReactorMessage(_T("Re-appended"), obj);
    ArxRleUiTdcTransientReactors::doStateDboxReappended(obj);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::objectClosed
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::objectClosed(const AcDbObjectId objId)
{
    printReactorMessage(_T("Object Closed"), NULL);
    ArxRleUiTdcTransientReactors::doStateDboxClosed(objId);
}

/****************************************************************************
**
**  ArxRleTransientObjReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleTransientObjReactor::printReactorMessage(LPCTSTR event, const AcDbObject* obj) const
{
    CString str;

    if (obj != NULL) {
        acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T("{OBJ T-REACTOR}"), event,
                ArxRleUtils::objToClassStr(obj), ArxRleUtils::objToHandleStr(obj, str));
    }
    else {
        acutPrintf(_T("\n%-15s : {%-18s: } "), _T("{OBJ T-REACTOR}"), event);
    }
}
