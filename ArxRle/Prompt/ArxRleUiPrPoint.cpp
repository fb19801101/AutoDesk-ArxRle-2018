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

#include "ArxRleUiPrPoint.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleSdSysVar.h"



/****************************************************************************
**
**  ArxRleUiPrPoint::init
**      handle the common work for the constructors
**
**  **jma
**
*************************************/

void
ArxRleUiPrPoint::init()
{
    m_value = AcGePoint3d::kOrigin;
    m_useDashedLine = false;
    m_noLimCheck = false;
    m_allowNone = false;
}

/****************************************************************************
**
**  ArxRleUiPrPoint::ArxRleUiPrPoint
**
**  **jma
**
*************************************/

ArxRleUiPrPoint::ArxRleUiPrPoint(LPCTSTR msg, LPCTSTR keyWordList)
:   ArxRleUiPrBase(msg, keyWordList),
    m_basePt(AcGePoint3d::kOrigin),
    m_useBasePt(false)
{
    init();
}

/****************************************************************************
**
**  ArxRleUiPrPoint::ArxRleUiPrPoint
**
**  **jma
**
*************************************/

ArxRleUiPrPoint::ArxRleUiPrPoint(LPCTSTR msg, LPCTSTR keyWordList, const AcGePoint3d& basePt)
:   ArxRleUiPrBase(msg, keyWordList),
    m_basePt(basePt),
    m_useBasePt(true)
{
    init();
}

/****************************************************************************
**
**  ArxRleUiPrPoint::~ArxRleUiPrPoint
**
**  **jma
**
*************************************/

ArxRleUiPrPoint::~ArxRleUiPrPoint()
{
}

/****************************************************************************
**
**  ArxRleUiPrPoint::go
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUiPrPoint::go()
{
    CString prompt;
    int result;
    ads_point adsPt;
    int initFlag = 0;

    if (m_allowNone == Adesk::kFalse)
        initFlag += RSG_NONULL;
    if (m_noLimCheck == Adesk::kTrue)
        initFlag += RSG_NOLIM;
    if (m_useDashedLine == Adesk::kTrue)
        initFlag += RSG_DASH;

    prompt.Format(_T("\n%s: "), message());

    acedInitGet(initFlag, keyWords());
    if (m_useBasePt)
        result = acedGetPoint(asDblArray(m_basePt), prompt, adsPt);
    else
        result = acedGetPoint(NULL, prompt, adsPt);

    if (result == RTNORM){
        m_value = asPnt3d(adsPt);
        setSysVar(_T("LASTPOINT"), m_value);
        return ArxRleUiPrBase::kOk;
    }
    else if (result == RTNONE){
        ASSERT(m_allowNone == Adesk::kTrue);
        return ArxRleUiPrBase::kNone;
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

/****************************************************************************
**
**  ArxRleUiPrPoint::value
**
**  **jma
**
*************************************/

const AcGePoint3d&
ArxRleUiPrPoint::value() const
{
    return m_value;
}

/****************************************************************************
**
**  ArxRleUiPrPoint::basePt
**
**  **jma
**
*************************************/

const AcGePoint3d&
ArxRleUiPrPoint::basePt() const
{
    return m_basePt;
}

/****************************************************************************
**
**  ArxRleUiPrPoint::setBasePt
**
**  **jma
**
*************************************/

void
ArxRleUiPrPoint::setBasePt(const AcGePoint3d& basePt)
{
    m_basePt = basePt;
    m_useBasePt = true;
}

/****************************************************************************
**
**  ArxRleUiPrPoint::setUseBasePt
**
**  **jma
**
*************************************/

void
ArxRleUiPrPoint::setUseBasePt(bool useIt)
{
    m_useBasePt = useIt;
}

/****************************************************************************
**
**  ArxRleUiPrPoint::setUseDashedLine
**
**  **jma
**
*************************************/

void
ArxRleUiPrPoint::setUseDashedLine(bool useIt)
{
    m_useDashedLine = useIt;
}

/****************************************************************************
**
**  ArxRleUiPrPoint::setNoLimitsCheck
**
**  **jma
**
*************************************/

void
ArxRleUiPrPoint::setNoLimitsCheck(bool noCheck)
{
    m_noLimCheck = noCheck;
}

/****************************************************************************
**
**  ArxRleUiPrPoint::setAllowNone
**
**  **jma
**
*************************************/

void
ArxRleUiPrPoint::setAllowNone(bool allowIt)
{
    m_allowNone = allowIt;
}


