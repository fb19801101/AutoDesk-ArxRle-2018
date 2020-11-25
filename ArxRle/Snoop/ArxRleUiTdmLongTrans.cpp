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

#include "ArxRleUiTdmLongTrans.h"
#include "ArxRleUiTdcLongTrans.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxRleUiTdmLongTrans::ArxRleUiTdmLongTrans
**
**	**jma
**
*************************************/

ArxRleUiTdmLongTrans::ArxRleUiTdmLongTrans(AcDbLongTransaction* lt, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxRleUiTdmLongTrans::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxRle-LongTrans"));

	ASSERT(lt != NULL);

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcLongTrans = new ArxRleUiTdcLongTrans(lt);

    //{{AFX_DATA_INIT(ArxRleUiTdmLongTrans)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxRleUiTdmLongTrans::~ArxRleUiTdmLongTrans
**
**	**jma
**
*************************************/

ArxRleUiTdmLongTrans::~ArxRleUiTdmLongTrans()
{
	delete m_tdcLongTrans;
}

/****************************************************************************
**
**  ArxRleUiTdmLongTrans::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdmLongTrans::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdmLongTrans)
    DDX_Control(pDX, ARXRLE_DATABASE_TAB, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmLongTrans message map

BEGIN_MESSAGE_MAP(ArxRleUiTdmLongTrans, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdmLongTrans)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmLongTrans message handlers

/****************************************************************************
**
**  ArxRleUiTdmLongTrans::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdmLongTrans::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("Long Transaction"),  ArxRleUiTdcLongTrans::IDD,   m_tdcLongTrans);
    
    return TRUE;
}

