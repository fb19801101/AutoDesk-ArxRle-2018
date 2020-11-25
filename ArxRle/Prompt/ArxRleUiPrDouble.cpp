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

#include "ArxRleUiPrDouble.h"



/****************************************************************************
**
**  ArxRleUiPrDouble::ArxRleUiPrDouble
**
**  **jma
**
*************************************/

ArxRleUiPrDouble::ArxRleUiPrDouble(LPCTSTR msg, LPCTSTR keyWordList, DoubleType type)
:   ArxRleUiPrBase(msg, keyWordList),
    m_doubleType(type),
    m_value(0.0),
    m_minVal(0.0),
    m_maxVal(0.0),
    m_unit(-1),
    m_precision(-1)
{
}

/****************************************************************************
**
**  ArxRleUiPrDouble::~ArxRleUiPrDouble
**
**  **jma
**
*************************************/

ArxRleUiPrDouble::~ArxRleUiPrDouble()
{
}

/****************************************************************************
**
**  ArxRleUiPrDouble::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrDouble::go()
{
    CString prompt;
    int initFlag;

        // set up prompt
    prompt.Format(_T("\n%s: "), message());

        // set up init flag
    if (m_doubleType == kNoZero)
        initFlag = RSG_NONULL+RSG_NOZERO;
    else if (m_doubleType == kNoNeg)
        initFlag = RSG_NONULL+RSG_NONEG;
    else if (m_doubleType == kNoNegNoZero)
        initFlag = RSG_NONULL+RSG_NOZERO+RSG_NONEG;
    else
        initFlag = RSG_NONULL;

    int result;
    while (1) {
        acedInitGet(initFlag, keyWords());
        result = acedGetReal(prompt, &m_value);

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
**  ArxRleUiPrDouble::setRange
**
**  **jma
**
*************************************/

void
ArxRleUiPrDouble::setRange(double minVal, double maxVal)
{
    ASSERT(maxVal >= minVal);

    m_minVal = minVal;
    m_maxVal = maxVal;
}

/****************************************************************************
**
**  ArxRleUiPrDouble::inRange
**
**  **jma
**
*************************************/

bool
ArxRleUiPrDouble::inRange()
{
    if (m_doubleType == ArxRleUiPrDouble::kRange) {
        ASSERT(m_minVal != m_maxVal);    // make sure they set ranges!
        if ((m_value >= m_minVal)&&(m_value <= m_maxVal))
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
**  ArxRleUiPrDouble::value
**
**  **jma
**
*************************************/

double
ArxRleUiPrDouble::value()
{
    return m_value;
}

/****************************************************************************
**
**  ArxRleUiPrDouble::setDoubleType
**
**  **jma
**
*************************************/

void
ArxRleUiPrDouble::setDoubleType(DoubleType newType)
{
    m_doubleType = newType;
}

/****************************************************************************
**
**  ArxRleUiPrDouble::setUnit
**
**  **jma
**
*************************************/

void
ArxRleUiPrDouble::setUnit(int unit)
{
    m_unit = unit;
}

/****************************************************************************
**
**  ArxRleUiPrDouble::setPrecision
**
**  **jma
**
*************************************/

void
ArxRleUiPrDouble::setPrecision(int precision)
{
    m_precision = precision;
}
