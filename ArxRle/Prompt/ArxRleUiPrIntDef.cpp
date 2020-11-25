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

#include "ArxRleUiPrIntDef.h"



/****************************************************************************
**
**  ArxRleUiPrIntDef::ArxRleUiPrIntDef
**
**  **jma
**
*************************************/

ArxRleUiPrIntDef::ArxRleUiPrIntDef(LPCTSTR msg, LPCTSTR keyWordList, IntType type, int def)
:   ArxRleUiPrInt(msg, keyWordList, type),
    m_default(def)
{
}

/****************************************************************************
**
**  ArxRleUiPrIntDef::~ArxRleUiPrIntDef
**
**  **jma
**
*************************************/

ArxRleUiPrIntDef::~ArxRleUiPrIntDef()
{
}

/****************************************************************************
**
**  ArxRleUiPrIntDef::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrIntDef::go()
{
    CString prompt;
    int initFlag;

        // set up prompt
    prompt.Format(_T("\n%s<%d>: "), message(), m_default);

        // set up init flag
    if (m_intType == kNoZero)
        initFlag = RSG_NOZERO;
    else if (m_intType == kNoNeg)
        initFlag = RSG_NONEG;
    else if (m_intType == kNoNegNoZero)
        initFlag = RSG_NOZERO+RSG_NONEG;
    else
        initFlag = 0;

    while (1) {
        acedInitGet(initFlag, keyWords());
        int result = acedGetInt(prompt, &m_value);

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
        else if (result == RTNONE) {
            if (m_intType == ArxRleUiPrInt::kRange) {
                ASSERT(m_minVal != m_maxVal);    // make sure they set ranges!
                ASSERT((m_default >= m_minVal) && (m_default <= m_maxVal));
            }
            m_value = m_default;
            return ArxRleUiPrBase::kOk;
        }
        else
            return ArxRleUiPrBase::kCancel;
    }
}

