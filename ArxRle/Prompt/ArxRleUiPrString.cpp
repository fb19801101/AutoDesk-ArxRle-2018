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

#include "ArxRleUiPrString.h"



/****************************************************************************
**
**  ArxRleUiPrString::ArxRleUiPrString
**
**  **jma
**
*************************************/

ArxRleUiPrString::ArxRleUiPrString(LPCTSTR msg, bool allowSpaces)
:   ArxRleUiPrBase(msg, NULL),
	m_allowSpaces(allowSpaces)
{
}

/****************************************************************************
**
**  ArxRleUiPrString::~ArxRleUiPrString
**
**  **jma
**
*************************************/

ArxRleUiPrString::~ArxRleUiPrString()
{
}

/****************************************************************************
**
**  ArxRleUiPrString::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrString::go()
{
    CString prompt;
    TCHAR val[512];
    int result;

    prompt.Format(_T("\n%s: "), message());

    if (m_allowSpaces == true)
        result = acedGetString(1, prompt, val);
    else
        result = acedGetString(0, prompt, val);

    if (result == RTNORM) {
        m_value = val;
        return ArxRleUiPrBase::kOk;
    }
    else
        return ArxRleUiPrBase::kCancel;
}

/****************************************************************************
**
**  ArxRleUiPrString::value
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUiPrString::value()
{
    return m_value;
}

/****************************************************************************
**
**  ArxRleUiPrString::keyWords
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUiPrString::keyWords() const
{
    return _T("");
}

/****************************************************************************
**
**  ArxRleUiPrString::setKeyWords
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleUiPrString::setKeyWords(LPCTSTR keyWordList)
{
    return Acad::eNotApplicable;
}

/****************************************************************************
**
**  ArxRleUiPrString::keyWordPicked
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUiPrString::keyWordPicked()
{
    return NULL;
}

/****************************************************************************
**
**  ArxRleUiPrString::isKeyWordPicked
**
**  **jma
**
*************************************/

bool
ArxRleUiPrString::isKeyWordPicked(LPCTSTR matchKeyWord)
{
    return false;
}


