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

#include "ArxRleSelSet.h"
#include "ArxRleUtils.h"
#include "ArxRleRbList.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleSelSet::ArxRleSelSet
**
**  **jma
**
*************************************/

ArxRleSelSet::ArxRleSelSet()
:   m_allowDuplicates(false),
    m_allAtPickBox(false),
    m_singleOnly(false),
    m_kwordFuncPtr(NULL),
    m_otherFuncPtr(NULL),
    m_allowLast(true),
	m_filterLockedLayers(false),
	m_rejectNonCurrentSpace(false),
	m_rejectPaperSpaceViewport(false)
{
    m_ss[0] = 0L;
    m_ss[1] = 0L;

    m_lastStatus = kCanceled;
}

/****************************************************************************
**
**  ArxRleSelSet::~ArxRleSelSet
**
**  **jma
**
*************************************/

ArxRleSelSet::~ArxRleSelSet()
{
    clear();
}

/****************************************************************************
**
**  ArxRleSelSet::isInitialized
**
**  **jma
**
*************************************/

bool
ArxRleSelSet::isInitialized() const
{
    if ((m_ss[0] == 0L) && (m_ss[1] == 0L))
        return false;
    else
        return true;
}

/****************************************************************************
**
**  ArxRleSelSet::clear
**
**  **jma
**
*************************************/

void
ArxRleSelSet::clear()
{
    if (isInitialized()) {
        acedSSFree(m_ss);
        m_ss[0] = m_ss[1] = 0L;
    }
}

/****************************************************************************
**
**  ArxRleSelSet::createEmptySet
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::createEmptySet()
{
    clear();

    int result = acedSSAdd(NULL, NULL, m_ss);
    ASSERT(result == RTNORM);

    if (result == RTNORM)
        m_lastStatus = ArxRleSelSet::kSelected;
    else
        m_lastStatus = ArxRleSelSet::kCanceled;

    return m_lastStatus;
}

/****************************************************************************
**
**  ArxRleSelSet::handleResult
**       private helper function to process common result code action.
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::handleResult(int result)
{
    if (result == RTNORM)
        m_lastStatus = ArxRleSelSet::kSelected;
    else if (result == RTCAN)
        m_lastStatus = ArxRleSelSet::kCanceled;
	else if (result == RTREJ) {
		ASSERT(0);
		m_lastStatus = ArxRleSelSet::kRejected;
	}
    else {        // doesn't return RTNONE
        createEmptySet();
        m_lastStatus = ArxRleSelSet::kNone;
    }
    return m_lastStatus;
}

/****************************************************************************
**
**  ArxRleSelSet::userSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::userSelect(const resbuf* filter)
{
    clear();

    setFlags(false);

        // if caller wants callback function for keywords
    if (m_kwordFuncPtr)
        acedSSSetKwordCallbackPtr(m_kwordFuncPtr);

        // if caller wants callback function for garbage input
    if (m_otherFuncPtr)
        acedSSSetOtherCallbackPtr(m_otherFuncPtr);

    int result;
    if (m_kwordFuncPtr)
        result = acedSSGet(m_flags, NULL, static_cast<LPCTSTR>(m_extraKwords), filter, m_ss);
    else
        result = acedSSGet(m_flags, NULL, NULL, filter, m_ss);

    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::userSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::userSelect(LPCTSTR selectPrompt, LPCTSTR removePrompt, const resbuf* filter)
{
    ASSERT(selectPrompt || removePrompt);   // if they wanted both to be NULL they should have used other signature!
    TCHAR* promptPtrs[2];

        // allow for one of the prompts to be NULL.  It is usually useful for the
        // Remove prompt.
    if ((selectPrompt == NULL) || (selectPrompt[0] == _T('\0')))
        promptPtrs[0] = _T("\nSelect objects: ");
    else
        promptPtrs[0] = const_cast<LPTSTR>(selectPrompt);

    if ((removePrompt == NULL) || (removePrompt[0] == _T('\0')))
        promptPtrs[1] =  _T("\nRemove objects: ");
    else
        promptPtrs[1] = const_cast<LPTSTR>(removePrompt);

        // if caller wants callback function for keywords
    if (m_kwordFuncPtr)
        acedSSSetKwordCallbackPtr(m_kwordFuncPtr);

        // if caller wants callback function for garbage input
    if (m_otherFuncPtr)
        acedSSSetOtherCallbackPtr(m_otherFuncPtr);

    setFlags(true);                     // set current state of flags

    int result;
    if (m_kwordFuncPtr)
        result = acedSSGet(m_flags, promptPtrs, static_cast<LPCTSTR>(m_extraKwords), filter, m_ss);
    else
        result = acedSSGet(m_flags, promptPtrs, NULL, filter, m_ss);

    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::impliedSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::impliedSelect(const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_I"), NULL, NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::crossingSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::crossingSelect(const AcGePoint3d& pt1, const AcGePoint3d& pt2, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_C"), asDblArray(pt1), asDblArray(pt2), filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::crossingPolygonSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::crossingPolygonSelect(const AcGePoint3dArray& ptArray, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    resbuf* ptList = ptArrayToResbuf(ptArray);
    if (ptList == NULL) {
        m_lastStatus = ArxRleSelSet::kCanceled;
        return m_lastStatus;
    }

    int result = acedSSGet(_T("_CP"), ptList, NULL, filter, m_ss);
    acutRelRb(ptList);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::fenceSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::fenceSelect(const AcGePoint3dArray& ptArray, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    resbuf* ptList = ptArrayToResbuf(ptArray);
    if (ptList == NULL) {
        m_lastStatus = ArxRleSelSet::kCanceled;
        return m_lastStatus;
    }

    int result = acedSSGet(_T("_F"), ptList, NULL, filter, m_ss);
    acutRelRb(ptList);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::lastSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::lastSelect(const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_L"), NULL, NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::pointSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::pointSelect(const AcGePoint3d& pt1, const resbuf* filter)
{
    clear();
	setFlags(false);

    int result = acedSSGet(m_flags, asDblArray(pt1), NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::previousSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::previousSelect(const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_P"), NULL, NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::windowSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::windowSelect(const AcGePoint3d& pt1, const AcGePoint3d& pt2, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_W"), asDblArray(pt1), asDblArray(pt2), filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::windowPolygonSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::windowPolygonSelect(const AcGePoint3dArray& ptArray, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    resbuf* ptList = ptArrayToResbuf(ptArray);
    if (ptList == NULL) {
        m_lastStatus = ArxRleSelSet::kCanceled;
        return m_lastStatus;
    }

    int result = acedSSGet(_T("_WP"), ptList, NULL, filter, m_ss);
    acutRelRb(ptList);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::filterOnlySelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::filterOnlySelect(const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_X"), NULL, NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::allSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::allSelect(const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection
	
    int result = acedSSGet(_T("_A"), NULL, NULL, filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::boxSelect
**
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::boxSelect(const AcGePoint3d& pt1, const AcGePoint3d& pt2, const resbuf* filter)
{
    clear();

	// NOTE: flags not allowed on this type of selection

    int result = acedSSGet(_T("_B"), asDblArray(pt1), asDblArray(pt2), filter, m_ss);
    return handleResult(result);
}

/****************************************************************************
**
**  ArxRleSelSet::length
**
**  **jma
**
*************************************/

long
ArxRleSelSet::length()
{
    ASSERT(isInitialized());

    Adesk::Int32 sslen;
    if (acedSSLength(m_ss, &sslen) != RTNORM) {
        acutPrintf(_T("\nInvalid selection set."));
        return 0L;
    }
    else
        return sslen;
}

/****************************************************************************
**
**  ArxRleSelSet::add
**
**  **jma
**
*************************************/

void
ArxRleSelSet::add(ads_name ent)
{
    ASSERT(isInitialized());
    acedSSAdd(ent, m_ss, m_ss);
}

/****************************************************************************
**
**  ArxRleSelSet::add
**
**  **jma
**
*************************************/

void
ArxRleSelSet::add(const AcDbObjectId& objId)
{
    ads_name ent;
    if (ArxRleUtils::objIdToEname(objId, ent) == Acad::eOk)
        add(ent);
}

/****************************************************************************
**
**  ArxRleSelSet::remove
**
**  **jma
**
*************************************/

void
ArxRleSelSet::remove(ads_name ent)
{
    ASSERT(isInitialized());
    acedSSDel(ent, m_ss);
}

/****************************************************************************
**
**  ArxRleSelSet::remove
**
**  **jma
**
*************************************/

void
ArxRleSelSet::remove(const AcDbObjectId& objId)
{
    ads_name ent;
    if (ArxRleUtils::objIdToEname(objId, ent) == Acad::eOk)
        remove(ent);
}

/****************************************************************************
**
**  ArxRleSelSet::member
**
**  **jma
**
*************************************/

bool
ArxRleSelSet::member(ads_name ent)
{
    ASSERT(isInitialized());

    if (acedSSMemb(ent, m_ss) == RTNORM)
        return true;
    else
        return false;
}

/****************************************************************************
**
**  ArxRleSelSet::member
**
**  **jma
**
*************************************/

bool
ArxRleSelSet::member(const AcDbObjectId& objId)
{
    ads_name ent;
    if (ArxRleUtils::objIdToEname(objId, ent) == Acad::eOk)
        return member(ent);
    else
        return false;
}

/****************************************************************************
**
**  ArxRleSelSet::subEntMarkerAt
**
**  **jma
**
*************************************/

bool
ArxRleSelSet::subEntMarkerAt(long index, AcDbObjectId& objId, int& gsMarker)
{
    resbuf* rb;

    if (acedSSNameX(&rb, m_ss, index) != RTNORM)
        return false;

        // walk to third element to retrieve ename of selected entity
    int i = 1;
    resbuf* tmp = rb;
    while (tmp && (i < 3)) {
        i++;
        tmp = tmp->rbnext;
    }
        // get the objectId of the slected entity
    ASSERT((tmp != NULL) && (i == 3));
    if (tmp == NULL)
        return false;

    if (ArxRleUtils::enameToObjId(tmp->resval.rlname, objId) != Acad::eOk) {
        acutRelRb(rb);
        return false;
    }
        // get the gsMarker, which should be the 4th element
    tmp = tmp->rbnext;
    ASSERT(tmp != NULL);
    if (tmp == NULL) {
        acutRelRb(rb);
        return false;
    }

    gsMarker = tmp->resval.rint;
    acutRelRb(rb);
    return true;
}

/****************************************************************************
**
**  ArxRleSelSet::asArray
**
**  **jma
**
*************************************/

void
ArxRleSelSet::asArray(AcDbObjectIdArray& objIds)
{
    ASSERT(isInitialized());
    long len = length();
    int ret;
    AcDbObjectId objId;
    ads_name ent;

    for (long i=0L; i<len; i++) {
        ret = acedSSName(m_ss, i, ent);
        ASSERT(ret == RTNORM);
        if (ArxRleUtils::enameToObjId(ent, objId) == Acad::eOk)
            objIds.append(objId);
    }
}

/****************************************************************************
**
**  ArxRleSelSet::lastStatus
**    if client wants to delay check for status to subroutine
**  **jma
**
*************************************/

ArxRleSelSet::SelSetStatus
ArxRleSelSet::lastStatus() const
{
    return m_lastStatus;
}

/****************************************************************************
**
**  ArxRleSelSet::asAdsName
**
**  **jma
**
*************************************/

void
ArxRleSelSet::asAdsName(ads_name ss)
{
    ss[0] = m_ss[0];
    ss[1] = m_ss[1];
}

/****************************************************************************
**
**  ArxRleSelSet::setFilterLockedLayers
**
**  **jma
**
*************************************/

void
ArxRleSelSet::setFilterLockedLayers(bool filterThem)
{
    m_filterLockedLayers = filterThem;
}

/****************************************************************************
**
**  ArxRleSelSet::setAllowDuplicates
**
**  **jma
**
*************************************/

void
ArxRleSelSet::setAllowDuplicates(bool dups)
{
    m_allowDuplicates = dups;
}

/****************************************************************************
**
**  ArxRleSelSet::setAllAtPickBox
**
**  **jma
**
*************************************/

void
ArxRleSelSet::setAllAtPickBox(bool pickBox)
{
    m_allAtPickBox = pickBox;
}

/****************************************************************************
**
**  ArxRleSelSet::setAllowSingleOnly
**
**  **jma
**
*************************************/

void
ArxRleSelSet::setAllowSingleOnly(bool single, bool allowLast)
{
    m_singleOnly = single;
    m_allowLast = allowLast;
}

/****************************************************************************
**
**  ArxRleSelSet::setRejectNonCurrentSpace
**
**  **jma
**
*************************************/

void
ArxRleSelSet::setRejectNonCurrentSpace(bool rejectIt)
{
	m_rejectNonCurrentSpace = rejectIt;
}

/****************************************************************************
**
**  ArxRleSelSet::setRejectPaperSpaceViewport
**
**  **jma
**
*************************************/

void
ArxRleSelSet::setRejectPaperSpaceViewport(bool rejectIt)
{
	m_rejectPaperSpaceViewport = rejectIt;
}

/****************************************************************************
**
**  ArxRleSelSet::setKeywordCallback
**
**  **jma
**
*************************************/

void
ArxRleSelSet::setKeywordCallback(LPCTSTR extraKwords, struct resbuf* (*pFunc) (const TCHAR*))
{
    ASSERT(pFunc != NULL);

    m_kwordFuncPtr = pFunc;
    m_extraKwords = extraKwords;
}

/****************************************************************************
**
**  ArxRleSelSet::setOtherCallback
**
**  **jma
**
*************************************/

void
ArxRleSelSet::setOtherCallback(struct resbuf* (*pFunc) (const TCHAR*))
{
    ASSERT(pFunc != NULL);

    m_otherFuncPtr = pFunc;
}

/****************************************************************************
**
**  ArxRleSelSet::setFlags
**
**  **jma
**
*************************************/

void
ArxRleSelSet::setFlags(bool hasPrompt)
{
    m_flags = _T("_");

    if (m_singleOnly) {
        if (m_allowLast)
            m_flags += _T("+L");

        m_flags += _T("+.:S");    // put in single mode, plus allow only pick selection
    }

    if (hasPrompt)
        m_flags += _T(":$");

    if (m_allowDuplicates)
        m_flags += _T(":D");

    if (m_allAtPickBox)
        m_flags += _T(":E");

	if (m_filterLockedLayers)
		m_flags += _T(":L");

	if (m_rejectNonCurrentSpace)
		m_flags += _T(":C");

	if (m_rejectPaperSpaceViewport)
		m_flags += _T(":P");

    if (m_kwordFuncPtr != NULL)
        m_flags += _T(":K");

    if (m_otherFuncPtr != NULL)
        m_flags += _T(":?");
}



