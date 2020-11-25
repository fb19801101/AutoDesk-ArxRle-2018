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

#include "ArxRlePersistentObjReactor.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRleUiTdcPersistentReactors.h"



Adesk::Int16     ArxRlePersistentObjReactor::m_version = 0;     // MDI safe

ACRX_DXF_DEFINE_MEMBERS(ArxRlePersistentObjReactor, AcDbObject,
                        AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
                        0, ARXRLE_PERSISTENT_OBJ_REACTOR, ArxRle);

/****************************************************************************
**
**  ArxRlePersistentObjReactor::getAttachedToObjs
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::getAttachedToObjs(AcDbObjectIdArray& objIds) const
{
    assertReadEnabled();

    objIds = m_attachedToObjs;
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::attachTo
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRlePersistentObjReactor::attachTo(const AcDbObjectId& objId)
{
    if (m_attachedToObjs.contains(objId) == false) {
        assertWriteEnabled();
        m_attachedToObjs.append(objId);
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::detachFrom
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRlePersistentObjReactor::detachFrom(const AcDbObjectId& objId)
{
    if (m_attachedToObjs.contains(objId) == false)
        return Acad::eKeyNotFound;

    assertWriteEnabled();
    m_attachedToObjs.remove(objId);

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::dwgInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRlePersistentObjReactor::dwgInFields(AcDbDwgFiler* filer)
{
    Acad::ErrorStatus es;
    if ((es = AcDbObject::dwgInFields(filer)) != Acad::eOk)
        return es;

    Adesk::Int16 version;
    filer->readItem(&version);
    if (version > m_version)
        return Acad::eMakeMeProxy;

    AcDbSoftPointerId tmpId;
    Adesk::Int32 count;
    filer->readItem(&count);
    
    m_attachedToObjs.setLogicalLength(0);
    for (int i=0; i<count; i++) {
        filer->readItem(&tmpId);
        if (tmpId.isNull() == false)
            m_attachedToObjs.append(tmpId);
    }

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::dwgOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRlePersistentObjReactor::dwgOutFields(AcDbDwgFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = AcDbObject::dwgOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(m_version);

    int len = m_attachedToObjs.length();
    filer->writeInt32(len);	// count of ids

    for (int i=0; i<len; i++)
        filer->writeSoftPointerId(m_attachedToObjs[i]);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::dxfInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRlePersistentObjReactor::dxfInFields(AcDbDxfFiler* filer)
{
    Acad::ErrorStatus es;
    if (((es = AcDbObject::dxfInFields(filer)) != Acad::eOk) ||
        (filer->atSubclassData(this->desc()->name()) != Adesk::kTrue))
        return filer->filerStatus();

    resbuf rb;
    m_attachedToObjs.setLogicalLength(0);

    while ((es == Acad::eOk) && ((es = filer->readResBuf(&rb)) == Acad::eOk)) {
        if (rb.restype == AcDb::kDxfSoftPointerId) {
            AcDbObjectId tmpId;
            tmpId.setFromOldId(rb.resval.mnLongPtr);
            if (tmpId.isNull() == false)
                m_attachedToObjs.append(tmpId);
        }
        else {
            filer->pushBackItem();
            es = Acad::eEndOfFile;
        }
    }

    if (es != Acad::eEndOfFile)
        return Acad::eInvalidResBuf;

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::dxfOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRlePersistentObjReactor::dxfOutFields(AcDbDxfFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = AcDbObject::dxfOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(AcDb::kDxfSubclass, this->desc()->name());

        // write out all the Ids
    int len = m_attachedToObjs.length();
    for (int i=0; i<len; i++) {
        if (m_attachedToObjs[i].isNull() == false)
            filer->writeItem(AcDb::kDxfSoftPointerId, m_attachedToObjs[i]);
    }

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::cancelled
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::cancelled(const AcDbObject* obj)
{
    printReactorMessage(_T("Cancelled"), obj);
    ArxRleUiTdcPersistentReactors::doStateDboxCacelled(obj);
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::copied
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::copied(const AcDbObject* obj, const AcDbObject* newObj)
{
    CString str;

    printReactorMessage(_T("Copied"), obj);
    acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T(""), _T("New Object"),
            ArxRleUtils::objToClassStr(newObj), ArxRleUtils::objToHandleStr(newObj, str));

    ArxRleUiTdcPersistentReactors::doStateDboxCopied(obj, newObj);

    if (newObj->database() != NULL) {
        Adesk::Boolean wasWritable;
        Acad::ErrorStatus es = upgradeFromNotify(wasWritable);
        if (es == Acad::eOk) {
            attachTo(newObj->objectId());
            downgradeToNotify(wasWritable);
        }
    }
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::erased
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::erased(const AcDbObject* obj, Adesk::Boolean pErasing)
{
    if (pErasing)
        printReactorMessage(_T("Erase"), obj);
    else
        printReactorMessage(_T("Un-erase"), obj);

    ArxRleUiTdcPersistentReactors::doStateDboxErased(obj, pErasing);
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::goodbye
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::goodbye(const AcDbObject* obj)
{
    printReactorMessage(_T("Goodbye"), obj);
    ArxRleUiTdcPersistentReactors::doStateDboxGoodbye(obj);
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::openedForModify
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::openedForModify(const AcDbObject* obj)
{
    printReactorMessage(_T("Open For Modify"), obj);
    ArxRleUiTdcPersistentReactors::doStateDboxOpenedModify(obj);
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::modified
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::modified(const AcDbObject* obj)
{
    printReactorMessage(_T("Modified"), obj);
    ArxRleUiTdcPersistentReactors::doStateDboxModified(obj);
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::subObjModified
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::subObjModified(const AcDbObject* obj, const AcDbObject* subObj)
{
    CString str;

    printReactorMessage(_T("Sub-Obj Modified"), obj);
    acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T(""), _T("Sub Object"),
            ArxRleUtils::objToClassStr(subObj), ArxRleUtils::objToHandleStr(subObj, str));

    ArxRleUiTdcPersistentReactors::doStateDboxSubObjModified(obj, subObj);
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::modifyUndone
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::modifyUndone(const AcDbObject* obj)
{
    printReactorMessage(_T("Modify Undone"), obj);
    ArxRleUiTdcPersistentReactors::doStateDboxModifyUndone(obj);
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::modifiedXData
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::modifiedXData(const AcDbObject* obj)
{
    printReactorMessage(_T("Modified Xdata"), obj);
    ArxRleUiTdcPersistentReactors::doStateDboxModifiedXdata(obj);
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::unappended
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::unappended(const AcDbObject* obj)
{
    printReactorMessage(_T("Un-appended"), obj);
    ArxRleUiTdcPersistentReactors::doStateDboxUnappended(obj);
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::reappended
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::reappended(const AcDbObject* obj)
{
    printReactorMessage(_T("Re-appended"), obj);
    ArxRleUiTdcPersistentReactors::doStateDboxReappended(obj);
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::objectClosed
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::objectClosed(const AcDbObjectId objId)
{
    printReactorMessage(_T("Object Closed"), NULL);
    ArxRleUiTdcPersistentReactors::doStateDboxClosed(objId);
}

/****************************************************************************
**
**  ArxRlePersistentObjReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRlePersistentObjReactor::printReactorMessage(LPCTSTR event, const AcDbObject* obj) const
{
    CString str;

    if (obj != NULL) {
        acutPrintf(_T("\n%-15s : {%-18s: %s, %s} "), _T("{OBJ P-REACTOR}"), event,
                ArxRleUtils::objToClassStr(obj), ArxRleUtils::objToHandleStr(obj, str));
    }
    else {
        acutPrintf(_T("\n%-15s : {%-18s: } "), _T("{OBJ P-REACTOR}"), event);
    }
}

