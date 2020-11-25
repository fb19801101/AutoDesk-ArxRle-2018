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

#include "ArxRleUiPrCorner.h"



/****************************************************************************
**
**  ArxRleUiPrCorner::ArxRleUiPrCorner
**
**  **jma
**
*************************************/

ArxRleUiPrCorner::ArxRleUiPrCorner(LPCTSTR msg, LPCTSTR keyWordList, const AcGePoint3d& basePt)
:   ArxRleUiPrBase(msg, keyWordList),
    m_basePt(basePt),
    m_value(AcGePoint3d::kOrigin),
	m_useDashedLine(false),
	m_noLimCheck(false)
{
}

/****************************************************************************
**
**  ArxRleUiPrCorner::~ArxRleUiPrCorner
**
**  **jma
**
*************************************/

ArxRleUiPrCorner::~ArxRleUiPrCorner()
{
}

/****************************************************************************
**
**  ArxRleUiPrCorner::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrCorner::go()
{
    CString prompt;
    int result;
    ads_point adsPt;
    int initFlag = RSG_NONULL;

    if (m_noLimCheck == true)
        initFlag += RSG_NOLIM;
    if (m_useDashedLine == true)
        initFlag += RSG_DASH;

    prompt.Format(_T("\n%s: "), message());

    acedInitGet(initFlag, keyWords());
    result = acedGetCorner(asDblArray(m_basePt), prompt, adsPt);

    if (result == RTNORM) {
        m_value = asPnt3d(adsPt);
        return ArxRleUiPrBase::kOk;
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

/****************************************************************************
**
**  ArxRleUiPrCorner::setBasePt
**
**  **jma
**
*************************************/

void
ArxRleUiPrCorner::setBasePt(const AcGePoint3d& basePt)
{
    m_basePt = basePt;
}

/****************************************************************************
**
**  ArxRleUiPrCorner::setUseDashedLine
**
**  **jma
**
*************************************/

void
ArxRleUiPrCorner::setUseDashedLine(bool useIt)
{
    m_useDashedLine = useIt;
}

/****************************************************************************
**
**  ArxRleUiPrCorner::setNoLimitsCheck
**
**  **jma
**
*************************************/

void
ArxRleUiPrCorner::setNoLimitsCheck(bool noCheck)
{
    m_noLimCheck = noCheck;
}

/****************************************************************************
**
**  ArxRleUiPrCorner::value
**
**  **jma
**
*************************************/

const AcGePoint3d&
ArxRleUiPrCorner::value()
{
    return m_value;
}

