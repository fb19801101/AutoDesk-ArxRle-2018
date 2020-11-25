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

#include "ArxRleUiPrDist.h"



/****************************************************************************
**
**  ArxRleUiPrDist::init
**      handle the common work for the constructors
**
**  **jma
**
*************************************/

void
ArxRleUiPrDist::init()
{
    m_value = 0.0;
    m_minVal = 0.0;
    m_maxVal = 0.0;
    m_useDashedLine = false;
    m_2dOnly = false;
    m_unit = -1;
    m_precision = -1;
    m_allowNone = false;
}

/****************************************************************************
**
**  ArxRleUiPrDist::ArxRleUiPrDist
**
**  **jma
**
*************************************/

ArxRleUiPrDist::ArxRleUiPrDist(LPCTSTR msg, LPCTSTR keyWordList, DistType type)
:   ArxRleUiPrBase(msg, keyWordList),
    m_distType(type),
    m_basePt(AcGePoint3d::kOrigin),
    m_useBasePt(false)
{
    init();
}

/****************************************************************************
**
**  ArxRleUiPrDist::ArxRleUiPrDist
**
**  **jma
**
*************************************/

ArxRleUiPrDist::ArxRleUiPrDist(LPCTSTR msg, LPCTSTR keyWordList, DistType type, const AcGePoint3d& basePt)
:   ArxRleUiPrBase(msg, keyWordList),
    m_distType(type),
    m_basePt(basePt),
    m_useBasePt(true)
{
    init();
}

/****************************************************************************
**
**  ArxRleUiPrDist::~ArxRleUiPrDist
**
**  **jma
**
*************************************/

ArxRleUiPrDist::~ArxRleUiPrDist()
{
}

/****************************************************************************
**
**  ArxRleUiPrDist::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrDist::go()
{
    CString prompt;
    int initFlag = 0;

        // set up prompt
    prompt.Format(_T("\n%s: "), message());

        // set up init flag
    if (m_allowNone == false)
        initFlag += RSG_NONULL;

    if (m_distType == kNoZero)
        initFlag += RSG_NOZERO;
    else if (m_distType == kNoNeg)
        initFlag += RSG_NONEG;
    else if (m_distType == kNoNegNoZero)
        initFlag += (RSG_NOZERO+RSG_NONEG);

    int result;
    while (1) {
        acedInitGet(initFlag, keyWords());
        if (m_useBasePt)
            result = acedGetDist(asDblArray(m_basePt), prompt, &m_value);
        else
            result = acedGetDist(NULL, prompt, &m_value);

        if (result == RTNORM) {
            if (inRange())
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
}

/****************************************************************************
**
**  ArxRleUiPrDist::setRange
**
**  **jma
**
*************************************/

void
ArxRleUiPrDist::setRange(double minVal, double maxVal)
{
    ASSERT(maxVal >= minVal);

    m_minVal = minVal;
    m_maxVal = maxVal;
}

/****************************************************************************
**
**  ArxRleUiPrDist::inRange
**
**  **jma
**
*************************************/

bool
ArxRleUiPrDist::inRange()
{
    if (m_distType == ArxRleUiPrDist::kRange) {
        ASSERT(m_minVal != m_maxVal);    // make sure they set ranges!
        if ((m_value >= m_minVal) && (m_value <= m_maxVal))
            return true;
        else {
            TCHAR str1[512], str2[512];
            acdbRToS(m_minVal, m_unit, m_precision, str1);
            acdbRToS(m_maxVal, m_unit, m_precision, str2);
            acutPrintf(_T("\nValue must be in range %s to %s."), str1, str2);
            return false;
        }
    }
    else
        return true;
}

/****************************************************************************
**
**  ArxRleUiPrDist::value
**
**  **jma
**
*************************************/

double
ArxRleUiPrDist::value()
{
    return m_value;
}

/****************************************************************************
**
**  ArxRleUiPrDist::setDistType
**
**  **jma
**
*************************************/

void
ArxRleUiPrDist::setDistType(DistType newType)
{
    m_distType = newType;
}

/****************************************************************************
**
**  ArxRleUiPrDist::setBasePt
**
**  **jma
**
*************************************/

void
ArxRleUiPrDist::setBasePt(const AcGePoint3d& basePt)
{
    m_basePt = basePt;
    m_useBasePt = Adesk::kTrue;
}

/****************************************************************************
**
**  ArxRleUiPrDist::setUseBasePt
**
**  **jma
**
*************************************/

void
ArxRleUiPrDist::setUseBasePt(bool useIt)
{
    m_useBasePt = useIt;
}

/****************************************************************************
**
**  ArxRleUiPrDist::setUseDashedLine
**
**  **jma
**
*************************************/

void
ArxRleUiPrDist::setUseDashedLine(bool useIt)
{
    m_useDashedLine = useIt;
}

/****************************************************************************
**
**  ArxRleUiPrDist::set2dOnly
**
**  **jma
**
*************************************/

void
ArxRleUiPrDist::set2dOnly(bool only2d)
{
    m_2dOnly = only2d;
}

/****************************************************************************
**
**  ArxRleUiPrDist::setUnit
**
**  **jma
**
*************************************/

void
ArxRleUiPrDist::setUnit(int unit)
{
    m_unit = unit;
}

/****************************************************************************
**
**  ArxRleUiPrDist::setPrecision
**
**  **jma
**
*************************************/

void
ArxRleUiPrDist::setPrecision(int precision)
{
    m_precision = precision;
}

/****************************************************************************
**
**  ArxRleUiPrDist::setAllowNone
**
**  **jma
**
*************************************/

void
ArxRleUiPrDist::setAllowNone(bool allowIt)
{
    m_allowNone = allowIt;
}


