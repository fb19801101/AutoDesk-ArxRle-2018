//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleUiDlgWindoType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ArxRleUiDlgWindoType* ArxRleUiDlgWindoType::m_pWindoTypeDlg = NULL;
ArxRleToolBar* ArxRleUiDlgWindoType::m_pToolBar	= NULL;
ArxRleToolBarGenWnd* ArxRleUiDlgWindoType::m_pToolBarGenWnd = NULL;

void ArxRleUiDlgWindoType::showWindoDlg()
{
	// TODO: Implement the command
	CAcModuleResourceOverride resOverride;

	m_pWindoTypeDlg = new ArxRleUiDlgWindoType(acedGetAcadFrame());
	m_pWindoTypeDlg->Create(ARXRLE_DLG_WINDOTYPE, acedGetAcadFrame());
	m_pWindoTypeDlg->CenterWindow();
	m_pWindoTypeDlg->ShowWindow(SW_SHOW);

	if(m_pToolBar != NULL && m_pToolBar->IsWindowVisible())
	{
		((CButton*)m_pWindoTypeDlg->GetDlgItem(ARXRLE_WINDOTYPE_CK_VISTB))->SetCheck(TRUE);
	}
}

void ArxRleUiDlgWindoType::drawWindo()
{
	switch(windInfo.m_nWindType)
	{
	case 0 :
		AfxMessageBox(L"Here 1 would have drawn a Rect window.");
		break;

	case 1 :
		AfxMessageBox(L"Here 2 would have drawn a Arch window.");
		break;

	case 2 :
		AfxMessageBox(L"Here 3 would have drawn a Apex window.");
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgWindoType dialog


ArxRleUiDlgWindoType::ArxRleUiDlgWindoType(CWnd* pParent /*=NULL*/)
	: CDialog(ArxRleUiDlgWindoType::IDD, pParent)
{
	//{{AFX_DATA_INIT(ArxRleUiDlgWindoType)
	m_nWindType = windInfo.m_nWindType;
	m_nCols = windInfo.m_nCols;
	m_nRows = windInfo.m_nRows;
	m_dHeight = windInfo.m_dWindHt;
	m_dWidth = windInfo.m_dWindWt;
	m_dXVal = windInfo.m_startPt.x;
	m_dYVal = windInfo.m_startPt.y;
	//}}AFX_DATA_INIT
}


void ArxRleUiDlgWindoType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ArxRleUiDlgWindoType)
	DDX_Radio(pDX, ARXRLE_WINDOTYPE_RB_TYPERECT, m_nWindType);
	DDX_Text(pDX, ARXRLE_WINDOTYPE_EB_COLS, m_nCols);
	DDV_MinMaxInt(pDX, m_nCols, 1, 10);
	DDX_Text(pDX, ARXRLE_WINDOTYPE_EB_ROWS, m_nRows);
	DDV_MinMaxInt(pDX, m_nRows, 1, 10);
	DDX_Text(pDX, ARXRLE_WINDOTYPE_EB_HEIGHT, m_dHeight);
	DDV_MinMaxDouble(pDX, m_dHeight, 20., 300.);
	DDX_Text(pDX, ARXRLE_WINDOTYPE_EB_WIDTH, m_dWidth);
	DDV_MinMaxDouble(pDX, m_dWidth, 20., 300.);
	DDX_Text(pDX, ARXRLE_WINDOTYPE_EB_XVAL, m_dXVal);
	DDX_Text(pDX, ARXRLE_WINDOTYPE_EB_YVAL, m_dYVal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ArxRleUiDlgWindoType, CDialog)
	//{{AFX_MSG_MAP(ArxRleUiDlgWindoType)
	ON_BN_CLICKED(ARXRLE_WINDOTYPE_BN_PICKPT, OnBtnPickPt)
	ON_BN_CLICKED(ARXRLE_WINDOTYPE_CK_VISTB, OnChkViewToolBar)
	ON_BN_CLICKED(ARXRLE_WINDOTYPE_BN_HIDEDLG, OnBtnHideDlg)
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_ACAD_KEEPFOCUS, onAcadKeepFocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgWindoType message handlers

LRESULT ArxRleUiDlgWindoType::onAcadKeepFocus(WPARAM,LPARAM) 
{
	return (TRUE) ;
}


BOOL ArxRleUiDlgWindoType::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CSpinButtonCtrl* pSpin;
    pSpin = (CSpinButtonCtrl*) GetDlgItem(ARXRLE_WINDOTYPE_SN_COLS);
	pSpin->SetRange(1, 10);

    pSpin = (CSpinButtonCtrl*) GetDlgItem(ARXRLE_WINDOTYPE_SN_ROWS);
	pSpin->SetRange(1, 10);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ArxRleUiDlgWindoType::PostNcDestroy() 
{
	delete this;
	m_pWindoTypeDlg = NULL;
	CDialog::PostNcDestroy();
}

void ArxRleUiDlgWindoType::OnCancel() 
{
	// Do NOT call CDialog::OnCancel(); 
	// Remember we're modeless,
	// Call DestroyWindow() instead!
	
	DestroyWindow();
}

void ArxRleUiDlgWindoType::OnOK() 
{
	if (!UpdateData(TRUE))
	{
		return;
	}

	// Transfer the values in the dialog
	// back to the global variables

	windInfo.m_dWindHt = m_dHeight;
	windInfo.m_dWindWt = m_dWidth;
	windInfo.m_nCols = m_nCols;
	windInfo.m_nRows = m_nRows;
	windInfo.m_nWindType = m_nWindType;
	windInfo.m_startPt.x = m_dXVal;
	windInfo.m_startPt.y = m_dYVal;

	drawWindo();
}

void ArxRleUiDlgWindoType::OnBtnPickPt() 
{
	// Here we hide our modal dialog
	// to allow the user to pick a point
	AcGePoint3d pkPt;
	int retCode;

	ShowWindow(SW_HIDE);		// Hide our dialog

	acedInitGet(NULL, NULL);

	retCode = acedGetPoint(NULL, L"\nPick lower left corner of window: ",
							asDblArray(pkPt));

	switch(retCode)
	{
		case RTCAN  :
		case RTNONE :

			pkPt.set(0.0, 0.0, 0.0);

		break;

		case RTNORM :



		break;
	}

	m_dXVal = pkPt.x;
	m_dYVal = pkPt.y;

	ShowWindow(SW_SHOW); // Display our dialog again

	// Transfer the data values from the member variables
	// to the dialog.
	UpdateData(FALSE);
}

void ArxRleUiDlgWindoType::OnBtnHideDlg() 
{
	ShowWindow(SW_HIDE);	
}

void ArxRleUiDlgWindoType::OnChkViewToolBar() 
{
	if(m_pToolBar != NULL && m_pToolBar->IsWindowVisible())
	{
		((CButton*) GetDlgItem(ARXRLE_WINDOTYPE_CK_VISTB))->SetCheck(FALSE);
		acedGetAcadFrame()->ShowControlBar(m_pToolBar, FALSE, FALSE);
		GetDlgItem(ARXRLE_WINDOTYPE_BN_HIDEDLG)->EnableWindow(FALSE);
	}
	else if(m_pToolBar != NULL)
	{
		((CButton*) GetDlgItem(ARXRLE_WINDOTYPE_CK_VISTB))->SetCheck(TRUE);
		acedGetAcadFrame()->ShowControlBar(m_pToolBar, TRUE, FALSE);
		GetDlgItem(ARXRLE_WINDOTYPE_BN_HIDEDLG)->EnableWindow(TRUE);
	}
	else
	{
		acedGetAcadFrame()->EnableDocking(CBRS_ALIGN_ANY);
		acedGetAcadFrame()->RecalcLayout();

		CAcModuleResourceOverride resOverride;

		// Does the ArxRleToolBarGenWnd already exist?
		if(m_pToolBarGenWnd == NULL)
		{
			m_pToolBarGenWnd = new ArxRleToolBarGenWnd;
			m_pToolBarGenWnd->Create (NULL,
							     NULL,
							     WS_CHILD | WS_MINIMIZE,
							     CRect (0,0,1,1),
							     acedGetAcadFrame(),
							     10);
		}

		m_pToolBar = new ArxRleToolBar;

		m_pToolBar->Create(acedGetAcadFrame(), m_pToolBarGenWnd);
		m_pToolBar->LoadToolBar(ARXRLE_BAR_APP);
		m_pToolBar->EnableDocking(CBRS_ALIGN_ANY);
		m_pToolBar->SetWindowText(_T("ARX Window"));

		acedGetAcadFrame()->FloatControlBar(m_pToolBar, CPoint (100, 200), CBRS_ALIGN_TOP) ;
		acedGetAcadFrame()->ShowControlBar(m_pToolBar, TRUE, FALSE) ;

		((CButton*) GetDlgItem(ARXRLE_WINDOTYPE_CK_VISTB))->SetCheck(TRUE);
		GetDlgItem(ARXRLE_WINDOTYPE_BN_HIDEDLG)->EnableWindow(TRUE);
	}

}
