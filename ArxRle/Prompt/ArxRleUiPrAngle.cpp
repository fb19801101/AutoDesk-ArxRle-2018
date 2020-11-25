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

#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleUiPrAngle.h"



/****************************************************************************
**
**  ArxRleUiPrAngle::init
**      handle the common work for the constructors
**
**  **jma
**
*************************************/

void
ArxRleUiPrAngle::init()
{
    m_value = 0.0;
    m_minVal = 0.0;
    m_maxVal = 0.0;
    m_useDashedLine = false;
    m_unit = -1;		// use current setting
    m_precision = -1;	// use current setting
    m_allowNone = false;
}

/****************************************************************************
**
**  ArxRleUiPrAngle::ArxRleUiPrAngle
**
**  **jma
**
*************************************/

ArxRleUiPrAngle::ArxRleUiPrAngle(LPCTSTR msg, LPCTSTR keyWordList, AngleType type)
:   ArxRleUiPrBase(msg, keyWordList),
    m_angType(type),
    m_basePt(AcGePoint3d::kOrigin),
    m_useBasePt(false)
{
    init();
}

/****************************************************************************
**
**  ArxRleUiPrAngle::ArxRleUiPrAngle
**
**  **jma
**
*************************************/

ArxRleUiPrAngle::ArxRleUiPrAngle(LPCTSTR msg, LPCTSTR keyWordList, AngleType type, const AcGePoint3d& basePt)
:   ArxRleUiPrBase(msg, keyWordList),
    m_angType(type),
    m_basePt(basePt),
    m_useBasePt(true)
{
    init();
}

/****************************************************************************
**
**  ArxRleUiPrAngle::~ArxRleUiPrAngle
**
**  **jma
**
*************************************/

ArxRleUiPrAngle::~ArxRleUiPrAngle()
{
}

/****************************************************************************
**
**  ArxRleUiPrAngle::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrAngle::go()
{
    CString prompt;
    int initFlag = 0;

        // set up prompt
    prompt.Format(_T("\n%s: "), message());

        // set up init flag
    if (m_allowNone == false)
        initFlag += RSG_NONULL;

    if (m_angType == kNoZero)
        initFlag += RSG_NOZERO;

    int result;
    while (1) {
        acedInitGet(initFlag, keyWords());
        if (m_useBasePt)
            result = acedGetOrient(asDblArray(m_basePt), prompt, &m_value);
        else
            result = acedGetOrient(NULL, prompt, &m_value);

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
**  ArxRleUiPrAngle::setRange
**
**  **jma
**
*************************************/

void
ArxRleUiPrAngle::setRange(double minVal, double maxVal)
{
    ASSERT(maxVal >= minVal);

    m_minVal = minVal;
    m_maxVal = maxVal;
}

/****************************************************************************
**
**  ArxRleUiPrAngle::inRange
**
**  **jma
**
*************************************/

bool
ArxRleUiPrAngle::inRange()
{
    if (m_angType == ArxRleUiPrAngle::kRange) {
        ASSERT(m_minVal != m_maxVal);    // make sure they set ranges!
        if ((m_value >= m_minVal)&&(m_value <= m_maxVal))
            return true;
        else {
            TCHAR str1[512], str2[512];
            acdbAngToS(m_minVal, m_unit, m_precision, str1);
            acdbAngToS(m_maxVal, m_unit, m_precision, str2);
            acutPrintf(_T("\nValue must be in range %s to %s."), str1, str2);
            return false;
        }
    }
    else
        return true;
}

/****************************************************************************
**
**  ArxRleUiPrAngle::value
**
**  **jma
**
*************************************/

double
ArxRleUiPrAngle::value()
{
    return m_value;
}

/****************************************************************************
**
**  ArxRleUiPrAngle::setAngleType
**
**  **jma
**
*************************************/

void
ArxRleUiPrAngle::setAngleType(AngleType newType)
{
    m_angType = newType;
}

/****************************************************************************
**
**  ArxRleUiPrAngle::setBasePt
**
**  **jma
**
*************************************/

void
ArxRleUiPrAngle::setBasePt(const AcGePoint3d& basePt)
{
    m_basePt = basePt;
    m_useBasePt = true;
}

/****************************************************************************
**
**  ArxRleUiPrAngle::setUseBasePt
**
**  **jma
**
*************************************/

void
ArxRleUiPrAngle::setUseBasePt(bool useIt)
{
    m_useBasePt = useIt;
}

/****************************************************************************
**
**  ArxRleUiPrAngle::setUseDashedLine
**
**  **jma
**
*************************************/

void
ArxRleUiPrAngle::setUseDashedLine(bool useIt)
{
    m_useDashedLine = useIt;
}

/****************************************************************************
**
**  ArxRleUiPrAngle::setUnit
**
**  **jma
**
*************************************/

void
ArxRleUiPrAngle::setUnit(int unit)
{
    m_unit = unit;
}

/****************************************************************************
**
**  ArxRleUiPrAngle::setPrecision
**
**  **jma
**
*************************************/

void
ArxRleUiPrAngle::setPrecision(int precision)
{
    m_precision = precision;
}

/****************************************************************************
**
**  ArxRleUiPrAngle::setAllowNone
**
**  **jma
**
*************************************/

void
ArxRleUiPrAngle::setAllowNone(bool allowIt)
{
    m_allowNone = allowIt;
}

