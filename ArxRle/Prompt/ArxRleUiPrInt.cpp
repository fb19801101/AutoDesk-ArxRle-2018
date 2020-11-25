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

#include "ArxRleUiPrInt.h"



/****************************************************************************
**
**  ArxRleUiPrInt::ArxRleUiPrInt
**
**  **jma
**
*************************************/

ArxRleUiPrInt::ArxRleUiPrInt(LPCTSTR msg, LPCTSTR keyWordList, IntType type)
:   ArxRleUiPrBase(msg, keyWordList),
    m_intType(type),
    m_value(0),
    m_minVal(0),
    m_maxVal(0)
{
}

/****************************************************************************
**
**  ArxRleUiPrInt::~ArxRleUiPrInt
**
**  **jma
**
*************************************/

ArxRleUiPrInt::~ArxRleUiPrInt()
{
}

/****************************************************************************
**
**  ArxRleUiPrInt::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrInt::go()
{
    CString prompt;
    int initFlag;

        // set up prompt
    prompt.Format(_T("\n%s: "), message());

        // set up init flag
    if (m_intType == kNoZero)
        initFlag = RSG_NONULL+RSG_NOZERO;
    else if (m_intType == kNoNeg)
        initFlag = RSG_NONULL+RSG_NONEG;
    else if (m_intType == kNoNegNoZero)
        initFlag = RSG_NONULL+RSG_NOZERO+RSG_NONEG;
    else
        initFlag = RSG_NONULL;

    while (1) {
        acedInitGet(initFlag, keyWords());
        int result = acedGetInt(prompt, &m_value);

        if (result == RTNORM) {
            if (inRange())
                return ArxRleUiPrBase::kOk;
        }
        else if (result == RTKWORD){
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
**  ArxRleUiPrInt::setRange
**
**  **jma
**
*************************************/

void
ArxRleUiPrInt::setRange(int minVal, int maxVal)
{
    ASSERT(maxVal >= minVal);

    m_minVal = minVal;
    m_maxVal = maxVal;
}

/****************************************************************************
**
**  ArxRleUiPrInt::inRange
**
**  **jma
**
*************************************/

bool
ArxRleUiPrInt::inRange()
{
    if (m_intType == ArxRleUiPrInt::kRange) {
        if ((m_value >= m_minVal) && (m_value <= m_maxVal))
            return true;
        else {
		    acutPrintf(_T("\nValue must be in range %d to %d."), m_minVal, m_maxVal);
            return false;
        }
    }
    else
        return true;
}

/****************************************************************************
**
**  ArxRleUiPrInt::value
**
**  **jma
**
*************************************/

int
ArxRleUiPrInt::value()
{
    return m_value;
}

/****************************************************************************
**
**  ArxRleUiPrInt::setType
**
**  **jma
**
*************************************/

void
ArxRleUiPrInt::setType(IntType type)
{
    m_intType = type;
}

