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

#include "ArxRleUiPrBase.h"



/****************************************************************************
**
**  ArxRleUiPrBase::ArxRleUiPrBase
**
**  **jma
**
*************************************/

ArxRleUiPrBase::ArxRleUiPrBase(LPCTSTR msg, LPCTSTR keyWordList)
:	m_keyWords(keyWordList),
	m_message(msg)
{
    ASSERT(msg != NULL);
}

/****************************************************************************
**
**  ArxRleUiPrBase::~ArxRleUiPrBase
**
**  **jma
**
*************************************/

ArxRleUiPrBase::~ArxRleUiPrBase()
{
}

/****************************************************************************
**
**  ArxRleUiPrBase::keyWords
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUiPrBase::keyWords() const
{
   return m_keyWords;
}

/****************************************************************************
**
**  ArxRleUiPrBase::setKeyWords
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleUiPrBase::setKeyWords(LPCTSTR keyWordList)
{
    ASSERT(keyWordList != NULL);

	m_keyWords = keyWordList;

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleUiPrBase::message
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUiPrBase::message() const
{
   return m_message;
}

/****************************************************************************
**
**  ArxRleUiPrBase::setMessage
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleUiPrBase::setMessage(LPCTSTR msg)
{
    m_message = msg;
    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleUiPrBase::keyWordPicked
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUiPrBase::keyWordPicked() const
{
    ASSERT(m_keyWordPicked.IsEmpty() == false);
    return m_keyWordPicked;
}

/****************************************************************************
**
**  ArxRleUiPrBase::isKeyWordPicked
**
**  **jma
**
*************************************/

bool
ArxRleUiPrBase::isKeyWordPicked(LPCTSTR keyWordMatch)
{
    ASSERT(m_keyWordPicked.IsEmpty() == false);
    ASSERT(keyWordMatch != NULL);

    if (m_keyWordPicked == keyWordMatch)
        return true;
    else
        return false;
}
