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

#include "ArxRleUiDlgAboutBox.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  cmdAboutBox
**
**  **jma
**
*************************************/

void
cmdAboutBox()
{
    ArxRleUiDlgAboutBox dbox(acedGetAcadDwgView());
    dbox.DoModal();
}


/****************************************************************************
**
**  ArxRleUiDlgAboutBox::ArxRleUiDlgAboutBox
**
**  **jma
**
*************************************/

ArxRleUiDlgAboutBox::ArxRleUiDlgAboutBox(CWnd* parent)
:	CAcUiDialog(ArxRleUiDlgAboutBox::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxRleUiDlgAboutBox)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiDlgAboutBox::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgAboutBox::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgAboutBox)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgAboutBox message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgAboutBox, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxRleUiDlgAboutBox)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgAboutBox message handlers
