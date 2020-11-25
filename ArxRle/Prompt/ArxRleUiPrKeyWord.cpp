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

#include "ArxRleUiPrKeyWord.h"



/****************************************************************************
**
**  ArxRleUiPrKeyWord::ArxRleUiPrKeyWord
**
**  **jma
**
*************************************/

ArxRleUiPrKeyWord::ArxRleUiPrKeyWord(LPCTSTR msg, LPCTSTR keyWordList)
:   ArxRleUiPrBase(msg, keyWordList),
    m_allowNone(false)
{
}

/****************************************************************************
**
**  ArxRleUiPrKeyWord::~ArxRleUiPrKeyWord
**
**  **jma
**
*************************************/

ArxRleUiPrKeyWord::~ArxRleUiPrKeyWord()
{
}

/****************************************************************************
**
**  ArxRleUiPrKeyWord::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrKeyWord::go()
{
    CString prompt;

    prompt.Format(_T("\n%s: "), message());

    int initFlag = 0;
    if (m_allowNone == false)
        initFlag += RSG_NONULL;

    acedInitGet(initFlag, keyWords());
    const size_t kBufSize = 512;
    int result = acedGetKword(prompt, m_keyWordPicked.GetBuffer(kBufSize), kBufSize);
    m_keyWordPicked.ReleaseBuffer();

    if (result == RTNORM)
        return ArxRleUiPrBase::kOk;
    else if (result == RTNONE) {
        ASSERT(m_allowNone == Adesk::kTrue);
        return ArxRleUiPrBase::kNone;
    }
    else
        return ArxRleUiPrBase::kCancel;
}

/****************************************************************************
**
**  ArxRleUiPrKeyWord::value
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUiPrKeyWord::value()
{
    return ArxRleUiPrBase::keyWordPicked();
}

/****************************************************************************
**
**  ArxRleUiPrKeyWord::setAllowNone
**
**  **jma
**
*************************************/

void
ArxRleUiPrKeyWord::setAllowNone(bool allowIt)
{
    m_allowNone = allowIt;
}


