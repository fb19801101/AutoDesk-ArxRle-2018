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

#include "ArxRleUiPrKeyWordDef.h"



/****************************************************************************
**
**  ArxRleUiPrKeyWordDef::ArxRleUiPrKeyWordDef
**
**  **jma
**
*************************************/

ArxRleUiPrKeyWordDef::ArxRleUiPrKeyWordDef(LPCTSTR msg, LPCTSTR keyWordList, LPCTSTR def)
:   ArxRleUiPrKeyWord(msg, keyWordList),
    m_default(def)
{
    ASSERT(def != NULL);
}

/****************************************************************************
**
**  ArxRleUiPrKeyWordDef::~ArxRleUiPrKeyWordDef
**
**  **jma
**
*************************************/

ArxRleUiPrKeyWordDef::~ArxRleUiPrKeyWordDef()
{
}

/****************************************************************************
**
**  ArxRleUiPrKeyWordDef::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrKeyWordDef::go()
{
    CString prompt;

    prompt.Format(_T("\n%s<%s>: "), message(), m_default);

    acedInitGet(0, keyWords());
    const size_t kBufSize = 512;
    int result = acedGetKword(prompt, m_keyWordPicked.GetBuffer(kBufSize), kBufSize);
    m_keyWordPicked.ReleaseBuffer();

    if (result == RTNORM) {
        return ArxRleUiPrBase::kOk;
    }
    else if (result == RTNONE) {
        if (keyWordMatch() == Adesk::kTrue)
            return ArxRleUiPrBase::kOk;
        else
            return ArxRleUiPrBase::kCancel;
    }
    else
        return ArxRleUiPrBase::kCancel;
}

/****************************************************************************
**
**  ArxRleUiPrKeyWordDef::keyWordMatch
**      Find the full keyword for this default, in case the default
**  was an abbreviation (like "Y" for "Yes").
**
**  **jma
**
*************************************/

bool
ArxRleUiPrKeyWordDef::keyWordMatch()
{
    CString kword;
    CString keyWordList = keyWords();
    int defLen = m_default.GetLength();
    int kwordLen = keyWordList.GetLength();
    int i = 0;
    while (1) {
            // parse out an individual keyword
        kword.Empty();
        while ((i < kwordLen) && (keyWordList[i] != _T(' ')))
            kword += keyWordList[i++];

            // see if it matches the default
        if (!_tcsncmp(kword, m_default, defLen)) {
            m_keyWordPicked = kword;
            return true;
        }
        if (i >= kwordLen) {
            ASSERT(0);    // should never happen
            return false;
        }
        else {
            while (keyWordList[i] == _T(' ')) // chew any whitespace between words
                i++;
        }
    }
}

