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

#include "ArxRleUiDlgFilerTest.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRleDwgFiler.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiDlgFilerTest::ArxRleUiDlgFilerTest
**
**  **jma
**
*************************************/

ArxRleUiDlgFilerTest::ArxRleUiDlgFilerTest(CWnd* parent)
:	CAcUiDialog(ArxRleUiDlgFilerTest::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxRleUiDlgFilerTest)
    m_puFilerTypeIndex = 1;		// default to CopyFiler
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiDlgFilerTest::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgFilerTest::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgFilerTest)
    DDX_CBIndex(pDX, ARXRLE_FILER_TEST_CB_FILER_TYPE, m_puFilerTypeIndex);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgFilerTest message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgFilerTest, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxRleUiDlgFilerTest)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgFilerTest message handlers

/****************************************************************************
**
**  ArxRleUiDlgFilerTest::indexToFilerType
**
**  **jma
**
*************************************/

AcDb::FilerType
ArxRleUiDlgFilerTest::indexToFilerType(int index)
{
    if (index == 0)
        return AcDb::kFileFiler;
    else if (index == 1)
        return AcDb::kCopyFiler;
    else if (index == 2)
        return AcDb::kUndoFiler;
    else if (index == 3)
        return AcDb::kIdFiler;
    else if (index == 4)
        return AcDb::kIdXlateFiler;
    else if (index == 5)
        return AcDb::kPageFiler;
    else if (index == 6)
        return AcDb::kDeepCloneFiler;
    else if (index == 7)
        return AcDb::kWblockCloneFiler;
    else if (index == 8)
        return AcDb::kPurgeFiler;
    else {
        ASSERT(0);
        return AcDb::kFileFiler;
    }
}
