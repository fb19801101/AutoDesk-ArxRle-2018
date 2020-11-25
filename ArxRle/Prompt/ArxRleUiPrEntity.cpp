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

#include "ArxRleUiPrEntity.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/AcadStr.h"
#include "AcadUtils/ArxRleSdSysVar.h"



/****************************************************************************
**
**  ArxRleUiPrEntity::ArxRleUiPrEntity
**
**  **jma
**
*************************************/

ArxRleUiPrEntity::ArxRleUiPrEntity(LPCTSTR msg, LPCTSTR keyWordList)
:   ArxRleUiPrBase(msg, keyWordList),
    m_allowNone(false),
    m_objId(AcDbObjectId::kNull),
    m_filterLockedLayers(false)
{
}

/****************************************************************************
**
**  ArxRleUiPrEntity::~ArxRleUiPrEntity
**
**  **jma
**
*************************************/

ArxRleUiPrEntity::~ArxRleUiPrEntity()
{
}

/****************************************************************************
**
**  ArxRleUiPrEntity::addAllowedClass
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleUiPrEntity::addAllowedClass(AcRxClass* classType, bool doIsATest)
{
    ASSERT(classType != NULL);

    if (m_allowedClassTypes.contains(classType))
        return Acad::eDuplicateKey;

    m_allowedClassTypes.append(classType);
    m_doIsATest.append(static_cast<int>(doIsATest));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleUiPrEntity::filterLockedLayers
**
**  **jma
**
*************************************/

bool
ArxRleUiPrEntity::filterLockedLayers() const
{
    return m_filterLockedLayers;
}

/****************************************************************************
**
**  ArxRleUiPrEntity::setFilterLockedLayers
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleUiPrEntity::setFilterLockedLayers(bool filterThem)
{
    m_filterLockedLayers = filterThem;

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleUiPrEntity::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrEntity::go()
{
    CString prompt;
    int result;
    int errNum;
    ads_point adsPt;
    ads_name ent;
    AcDbObjectId tmpId;
    AcDbEntity* tmpEnt;
    Acad::ErrorStatus es;

    prompt.Format(_T("\n%s: "), message());

    while (1) {
        acedInitGet(0, keyWords());
        result = acedEntSel(prompt, ent, adsPt);

        if (result == RTNORM) {
            ArxRleUtils::enameToObjId(ent, tmpId);
            es = acdbOpenAcDbEntity(tmpEnt, tmpId, AcDb::kForRead);
            if (es == Acad::eOk) {
                    // if its correct class and we are not filtering locked layers its ok,
                    // or if we are filtering locked layers and this one isn't on a locked layer
                if (correctClass(tmpEnt)) {     // correctClass() will print error msg
                    if ((!m_filterLockedLayers) ||
                        (ArxRleUtils::isOnLockedLayer(tmpEnt, true) == false)) {    // isOnLockedLayer() will print error msg
                        tmpEnt->close();
                        m_pickPt = asPnt3d(adsPt);
                        m_objId = tmpId;
                        return ArxRleUiPrBase::kOk;
                    }
                }
                tmpEnt->close();    // close and loop again until they get it right!
            }
            else {
                ASSERT(0);
                ArxRleUtils::rxErrorMsg(es);
                return ArxRleUiPrBase::kCancel;
            }
        }
        else if (result == RTERROR) {
            getSysVar(AcadVar::adserr, errNum);
            if (errNum == OL_ENTSELPICK)            // picked but didn't get anything
                acutPrintf(_T("\nNothing selected."));
            else if (errNum == OL_ENTSELNULL) {     // hit RETURN or SPACE
                if (m_allowNone)
                    return ArxRleUiPrBase::kNone;      // prompt specifically wants to know about None
                else
                    return ArxRleUiPrBase::kCancel;    // prompt wants to bail on None
            }
            else
                acutPrintf(_T("\nNothing selected."));
        }
        else if (result == RTKWORD) {
            const size_t kBufSize = 512;
            acedGetInput(m_keyWordPicked.GetBuffer(kBufSize), kBufSize);
            m_keyWordPicked.ReleaseBuffer();
            return ArxRleUiPrBase::kKeyWord;
        }
        else
            return ArxRleUiPrBase::kCancel;
    }
}

/****************************************************************************
**
**  ArxRleUiPrEntity::correctClass
**
**  **jma
**
*************************************/

bool
ArxRleUiPrEntity::correctClass(AcDbEntity* ent)
{
    if (m_allowedClassTypes.isEmpty())
        return Adesk::kTrue;

    AcRxClass* rxClass;
    int len = m_allowedClassTypes.length();
    bool isOk = false;
    for (int i=0; i<len; i++) {
        rxClass = static_cast<AcRxClass*>(m_allowedClassTypes[i]);
        if (m_doIsATest[i]) {
            if (ent->isA() == rxClass)
                isOk = true;
        }
        else {
            if (ent->isKindOf(rxClass))
                isOk = true;
        }
    }

    if (isOk)
        return true;

        // print out error message with allowed types
    CString types;
    CString str;
    for (int ii=0; ii<len;ii++) {
        if (ii > 0)
            types += _T(", ");

        rxClass = static_cast<AcRxClass*>(m_allowedClassTypes[ii]);
        types += rxClass->name();
    }

    acutPrintf(_T("\nSelected entity must be of type: %s"), types);

    return false;
}

/****************************************************************************
**
**  ArxRleUiPrEntity::objectId
**
**  **jma
**
*************************************/

AcDbObjectId
ArxRleUiPrEntity::objectId() const
{
    return m_objId;
}

/****************************************************************************
**
**  ArxRleUiPrEntity::pickPoint
**
**  **jma
**
*************************************/

AcGePoint3d
ArxRleUiPrEntity::pickPoint() const
{
    return m_pickPt;
}

/****************************************************************************
**
**  ArxRleUiPrEntity::setAllowNone
**
**  **jma
**
*************************************/

void
ArxRleUiPrEntity::setAllowNone(bool allowIt)
{
    m_allowNone = allowIt;
}


