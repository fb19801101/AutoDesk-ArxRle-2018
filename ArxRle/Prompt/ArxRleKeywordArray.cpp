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

#include "ArxRleKeywordArray.h"
#include "AcExtensionModule.h"



/****************************************************************************
**
**  ArxRleKeywordInfo::ArxRleKeywordInfo
**
**  **jma
**
*************************************/

ArxRleKeywordInfo::ArxRleKeywordInfo(const CString& localKword,
                               const CString& globalKword,
                               const CString& optionStr)
:   m_localKword(localKword),
    m_globalKword(globalKword),
    m_optionStr(optionStr),
    m_isVisible(true),
    m_isEnabled(true),
    m_isDefault(false)
{
    ASSERT(localKword.IsEmpty() == FALSE);
    ASSERT(globalKword.IsEmpty() == FALSE);
    ASSERT(optionStr.IsEmpty() == FALSE);
}

/****************************************************************************
**
**  ArxRleKeywordInfo::~ArxRleKeywordInfo
**
**  **jma
**
*************************************/

ArxRleKeywordInfo::~ArxRleKeywordInfo()
{
}

/****************************************************************************
**
**  ArxRleKeywordInfo::localKeyword
**
**  **jma
**
*************************************/

const CString&
ArxRleKeywordInfo::localKeyword() const
{
    return m_localKword;
}

/****************************************************************************
**
**  ArxRleKeywordInfo::setLocalKeyword
**
**  **jma
**
*************************************/

void
ArxRleKeywordInfo::setLocalKeyword(const CString& kword)
{
    m_localKword = kword;
}

/****************************************************************************
**
**  ArxRleKeywordInfo::globalKeyword
**
**  **jma
**
*************************************/

const CString&
ArxRleKeywordInfo::globalKeyword() const
{
    return m_globalKword;
}

/****************************************************************************
**
**  ArxRleKeywordInfo::setGlobalKeyword
**
**  **jma
**
*************************************/

void
ArxRleKeywordInfo::setGlobalKeyword(const CString& kword)
{
    m_globalKword = kword;
}

/****************************************************************************
**
**  ArxRleKeywordInfo::optionStr
**
**  **jma
**
*************************************/

const CString&
ArxRleKeywordInfo::optionStr() const
{
    return m_optionStr;
}

/****************************************************************************
**
**  ArxRleKeywordInfo::setOptionStr
**
**  **jma
**
*************************************/

void
ArxRleKeywordInfo::setOptionStr(const CString& str)
{
    m_optionStr = str;
}

/****************************************************************************
**
**  ArxRleKeywordInfo::isVisible
**
**  **jma
**
*************************************/

bool
ArxRleKeywordInfo::isVisible() const
{
    return m_isVisible;
}

/****************************************************************************
**
**  ArxRleKeywordInfo::setIsVisible
**
**  **jma
**
*************************************/

void
ArxRleKeywordInfo::setIsVisible(bool itIs)
{
    m_isVisible = itIs;
}

/****************************************************************************
**
**  ArxRleKeywordInfo::isEnabled
**
**  **jma
**
*************************************/

bool
ArxRleKeywordInfo::isEnabled() const
{
    return m_isEnabled;
}

/****************************************************************************
**
**  ArxRleKeywordInfo::setIsEnabled
**
**  **jma
**
*************************************/

void
ArxRleKeywordInfo::setIsEnabled(bool itIs)
{
    m_isEnabled = itIs;
}

/****************************************************************************
**
**  ArxRleKeywordInfo::isDefault
**
**  **jma
**
*************************************/

bool
ArxRleKeywordInfo::isDefault() const
{
    return m_isDefault;
}

/****************************************************************************
**
**  ArxRleKeywordInfo::setIsDefault
**
**  **jma
**
*************************************/

void
ArxRleKeywordInfo::setIsDefault(bool itIs)
{
    m_isDefault = itIs;
}



/////////////////////////////////////////////////////////////////////////////
/////////////////////////// ARXRLE KEYWORD ARRAY ////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  ArxRleKeywordArray::ArxRleKeywordArray
**
**  **jma
**
*************************************/

ArxRleKeywordArray::ArxRleKeywordArray(HINSTANCE resDllInstance)
:   m_resDllHandle(resDllInstance)
{
}

/****************************************************************************
**
**  ArxRleKeywordArray::~ArxRleKeywordArray
**
**  **jma
**
*************************************/

ArxRleKeywordArray::~ArxRleKeywordArray()
{
    deleteAll();
}

/****************************************************************************
**
**  ArxRleKeywordArray::count
**
**  **jma
**
*************************************/

int
ArxRleKeywordArray::count() const
{
    return m_keywordArray.length();
}

/****************************************************************************
**
**  ArxRleKeywordArray::append
**
**  **jma
**
*************************************/

void
ArxRleKeywordArray::append(LPCTSTR localKword, LPCTSTR globalKword,
                                bool isVisible,
                                bool isEnabled)
{
    ArxRleKeywordInfo* tmpInfo = new ArxRleKeywordInfo(localKword, globalKword, localKword);
    tmpInfo->setIsVisible(isVisible);
    tmpInfo->setIsEnabled(isEnabled);

    m_keywordArray.append(tmpInfo);
}

/****************************************************************************
**
**  ArxRleKeywordArray::append
**
**  **jma
**
*************************************/

void
ArxRleKeywordArray::append(UINT localKwordResId, LPCTSTR globalKword,
                                    bool isVisible,
                                    bool isEnabled)
{
	CAcModuleResourceOverride(m_resDllInstance);
    CString str;
	str.LoadString(localKwordResId);

    ArxRleKeywordInfo* tmpInfo = new ArxRleKeywordInfo(str, globalKword, str);
    tmpInfo->setIsVisible(isVisible);
    tmpInfo->setIsEnabled(isEnabled);

    m_keywordArray.append(tmpInfo);
}

/****************************************************************************
**
**  ArxRleKeywordArray::append
**
**  **jma
**
*************************************/

void
ArxRleKeywordArray::append(LPCTSTR localKword, LPCTSTR globalKword,
                                LPCTSTR optionStr,
                                bool isVisible,
                                bool isEnabled)
{
    ArxRleKeywordInfo* tmpInfo = new ArxRleKeywordInfo(localKword, globalKword, optionStr);
    tmpInfo->setIsVisible(isVisible);
    tmpInfo->setIsEnabled(isEnabled);

    m_keywordArray.append(tmpInfo);
}

/****************************************************************************
**
**  ArxRleKeywordArray::append
**
**  **jma
**
*************************************/

void
ArxRleKeywordArray::append(UINT localKwordResId, LPCTSTR globalKword,
                                    UINT optionStrId,
                                    bool isVisible,
                                    bool isEnabled)
{
	CAcModuleResourceOverride(m_resDllInstance);

    CString localKwordStr;
	localKwordStr.LoadString(localKwordResId);

    CString optionStr;
	optionStr.LoadString(optionStrId);

    ArxRleKeywordInfo* tmpInfo = new ArxRleKeywordInfo(localKwordStr, globalKword, optionStr);
    tmpInfo->setIsVisible(isVisible);
    tmpInfo->setIsEnabled(isEnabled);

    m_keywordArray.append(tmpInfo);
}

/****************************************************************************
**
**  ArxRleKeywordArray::deleteAll
**
**  **jma
**
*************************************/

void
ArxRleKeywordArray::deleteAll()
{
    ArxRleKeywordInfo* tmpInfo;

    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxRleKeywordInfo*>(m_keywordArray[i]);
        delete tmpInfo;
    }

    m_keywordArray.setLogicalLength(0);
}

/****************************************************************************
**
**  ArxRleKeywordArray::getAt
**
**  **jma
**
*************************************/

ArxRleKeywordInfo*
ArxRleKeywordArray::getAt(int index)
{
    return static_cast<ArxRleKeywordInfo*>(m_keywordArray[index]);
}

/****************************************************************************
**
**  ArxRleKeywordArray::find
**
**  **jma
**
*************************************/

bool
ArxRleKeywordArray::find(LPCTSTR kwordPicked, int& indexFoundAt)
{
    ArxRleKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxRleKeywordInfo*>(m_keywordArray[i]);

        if (_tcscmp(kwordPicked, tmpInfo->globalKeyword()) == 0) {
            ASSERT(tmpInfo->isEnabled());

            indexFoundAt = i;
            return true;
        }
    }

    return false;
}

/****************************************************************************
**
**  ArxRleKeywordArray::findByJigIndex
**      jig indexes for kwords only account for enabled ones.  So,
**  go through the array and find out the actual index that corresponds
**  to what the jig thinks the kword is.
**
**  **jma
**
*************************************/

bool
ArxRleKeywordArray::findByJigIndex(int jigIndex, int& actualIndex)
{
    int enabledKwordCount = 0;

    ArxRleKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxRleKeywordInfo*>(m_keywordArray[i]);

        if (tmpInfo->isEnabled()) {
                // jig kword indexes start at 1, not 0, so increment first
            enabledKwordCount++;

            if (jigIndex == enabledKwordCount) {
                actualIndex = i;
                return true;
            }
        }
    }

    return false;
}

/****************************************************************************
**
**  ArxRleKeywordArray::getActualIndexRange
**
**  **jma
**
*************************************/

bool
ArxRleKeywordArray::getActualIndexRange(int& startIndex, int& endIndex)
{
    int actualEnd = m_keywordArray.length() - 1;

    if (startIndex == -1)
        startIndex = 0;
    if (endIndex == -1)
        endIndex = actualEnd;

    if (endIndex < startIndex) {    // equal is OK, but not less than
        ASSERT(0);
        return false;
    }
    if ((startIndex > actualEnd) || (endIndex > actualEnd)) {
        ASSERT(0);
        return false;
    }

    return true;
}

/****************************************************************************
**
**  ArxRleKeywordArray::setEnabled
**
**  **jma
**
*************************************/

void
ArxRleKeywordArray::setEnabled(bool isEnabled, int startIndex, int endIndex)
{
    if (getActualIndexRange(startIndex, endIndex) == false)
        return;

    ArxRleKeywordInfo* tmpInfo;
    for (int i=startIndex; i<=endIndex; i++) {
        tmpInfo = static_cast<ArxRleKeywordInfo*>(m_keywordArray[i]);
        tmpInfo->setIsEnabled(isEnabled);

            // setEnable will control visibility as well...
			// if you want the keyword enabled but invisible, you need to call
			// setIsVisible after setEnabled.
        tmpInfo->setIsVisible(isEnabled);
    }
}

/****************************************************************************
**
**  ArxRleKeywordArray::setVisible
**
**  **jma
**
*************************************/

void
ArxRleKeywordArray::setVisible(bool isVisible, int startIndex, int endIndex)
{
    if (getActualIndexRange(startIndex, endIndex) == false)
        return;

    ArxRleKeywordInfo* tmpInfo;
    for (int i=startIndex; i<=endIndex; i++) {
        tmpInfo = static_cast<ArxRleKeywordInfo*>(m_keywordArray[i]);
        tmpInfo->setIsVisible(isVisible);
    }
}

/****************************************************************************
**
**  ArxRleKeywordArray::setAsDefault
**      set this item as the lone default
**
**  **jma
**
*************************************/

void
ArxRleKeywordArray::setAsDefault(int index)
{
    ArxRleKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxRleKeywordInfo*>(m_keywordArray[i]);
        if (i == index)
            tmpInfo->setIsDefault(true);
        else
            tmpInfo->setIsDefault(false);
    }
}

/****************************************************************************
**
**  ArxRleKeywordArray::makeKeywordList
**
**  **jma
**
*************************************/

void
ArxRleKeywordArray::makeKeywordList(CString& str)
{
    str.Empty();

    CString localKwords, globalKwords;

    bool isFirst = true;

    ArxRleKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxRleKeywordInfo*>(m_keywordArray[i]);
        if (tmpInfo->isEnabled()) {
            if (isFirst == Adesk::kFalse) {
                localKwords += _T(" ");   // add seperator space
                globalKwords += _T(" ");  // add seperator space
            }
            else
                isFirst = false;

            localKwords += tmpInfo->localKeyword();
            globalKwords += tmpInfo->globalKeyword();
        }
    }

		// see documentation for acedGetKeyword() for an explanation of how to do
		// local and global keywords
    str.Format(_T("%s _ %s"), static_cast<LPCTSTR>(localKwords), static_cast<LPCTSTR>(globalKwords));
}

/****************************************************************************
**
**  ArxRleKeywordArray::makeOptionsList
**
**  **jma
**
*************************************/

void
ArxRleKeywordArray::makeOptionsList(CString& str)
{
    str.Empty();

    CString opsStr;

    bool isFirst = true;

    ArxRleKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxRleKeywordInfo*>(m_keywordArray[i]);

        if (tmpInfo->isDefault()) {
            ASSERT(0);  // shouldn't have called this function!
            continue;
        }

        if (tmpInfo->isEnabled() && tmpInfo->isVisible()) {
            if (isFirst == false)
                opsStr += _T("/");   // add seperator
            else
                isFirst = false;

            opsStr += tmpInfo->optionStr();
        }
    }
        // Wrap options within square brackets "[op1/op2]" for rt-click menu support
    if (!opsStr.IsEmpty()) {
        str.Format(_T("[%s]"), static_cast<LPCTSTR>(opsStr));
    }
}

/****************************************************************************
**
**  ArxRleKeywordArray::makeOptionsList
**
**  **jma
**
*************************************/

void
ArxRleKeywordArray::makeOptionsList(CString& optionsStr, CString& defaultStr, bool includeDefInOptions)
{
    optionsStr.Empty();
    defaultStr.Empty();

    CString opsStr;

    bool isFirst = true;

    ArxRleKeywordInfo* tmpInfo;
    int len = m_keywordArray.length();
    for (int i=0; i<len; i++) {
        tmpInfo = static_cast<ArxRleKeywordInfo*>(m_keywordArray[i]);

        if (tmpInfo->isDefault()) {
            defaultStr = tmpInfo->localKeyword();

            if (includeDefInOptions == false) {
                continue;
            }
            else {
                ASSERT(tmpInfo->isEnabled());
            }
        }

        if (tmpInfo->isEnabled() && tmpInfo->isVisible()) {
            if (isFirst == false)
                opsStr += _T("/");   // add seperator
            else
                isFirst = false;

            opsStr += tmpInfo->optionStr();
        }
    }
        // Wrap options within square brackets "[op1/op2]" for rt-click menu support
    if (!opsStr.IsEmpty()) {
        optionsStr.Format(_T("[%s]"), static_cast<LPCTSTR>(opsStr));
    }
}
