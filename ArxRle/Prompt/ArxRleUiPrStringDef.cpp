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

#include "ArxRleUiPrStringDef.h"



/****************************************************************************
**
**  ArxRleUiPrStringDef::ArxRleUiPrStringDef
**
**  **jma
**
*************************************/

ArxRleUiPrStringDef::ArxRleUiPrStringDef(LPCTSTR msg, LPCTSTR def, bool allowSpaces)
:   ArxRleUiPrString(msg, allowSpaces),
    m_default(def)
{
    ASSERT(def != NULL);
}

/****************************************************************************
**
**  ArxRleUiPrStringDef::~ArxRleUiPrStringDef
**
**  **jma
**
*************************************/

ArxRleUiPrStringDef::~ArxRleUiPrStringDef()
{
}

/****************************************************************************
**
**  ArxRleUiPrStringDef::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrStringDef::go()
{
    CString prompt;
    TCHAR val[512];
    int result;

    prompt.Format(_T("\n%s<%s>: "), message(), m_default);

    if (m_allowSpaces == Adesk::kTrue)
        result = acedGetString(1, prompt, val);
    else
        result = acedGetString(0, prompt, val);

    if (result == RTNORM) {
        if (val[0] == _T('\0'))
            m_value = m_default;
        else
            m_value = val;
        return ArxRleUiPrBase::kOk;
    }
    else
        return ArxRleUiPrBase::kCancel;
}

