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

#include "ArxRleToolBarGenWnd.h"
#include "UiDlg\ArxRleUiDlgWindoType.h"
#include "UiDlg\ArxRleUiDlgWindoInfo.h"
#include "UiDlg\ArxRleUiDlgAboutBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ArxRleToolBarGenWnd

ArxRleToolBarGenWnd::ArxRleToolBarGenWnd()
{
}

ArxRleToolBarGenWnd::~ArxRleToolBarGenWnd()
{
}


BEGIN_MESSAGE_MAP(ArxRleToolBarGenWnd, CWnd)
	//{{AFX_MSG_MAP(ArxRleToolBarGenWnd)
	ON_COMMAND(ARXRLE_APP_WINDDLG, OnShowWindTypeDlg)
	ON_COMMAND(ARXRLE_APP_DRAW, OnDrawWindo)
	ON_COMMAND(ARXRLE_APP_INFO, OnWindInfoDlg)
	ON_COMMAND(ARXRLE_APP_ABOUT, OnAbout)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ArxRleToolBarGenWnd message handlers

void ArxRleToolBarGenWnd::OnShowWindTypeDlg() 
{
	if(ArxRleUiDlgWindoType::m_pWindoTypeDlg != NULL && !ArxRleUiDlgWindoType::m_pWindoTypeDlg->IsWindowVisible())
	{
		ArxRleUiDlgWindoType::m_pWindoTypeDlg->ShowWindow(SW_SHOW);
	}
	else if(ArxRleUiDlgWindoType::m_pWindoTypeDlg != NULL)
	{
		ArxRleUiDlgWindoType::m_pWindoTypeDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		CAcModuleResourceOverride resOverride;

		ArxRleUiDlgWindoType::m_pWindoTypeDlg = new ArxRleUiDlgWindoType(acedGetAcadFrame());
		ArxRleUiDlgWindoType::m_pWindoTypeDlg->Create(ARXRLE_DLG_WINDOTYPE, acedGetAcadFrame());
		ArxRleUiDlgWindoType::m_pWindoTypeDlg->CenterWindow();
		ArxRleUiDlgWindoType::m_pWindoTypeDlg->ShowWindow(SW_SHOW);

		((CButton*) ArxRleUiDlgWindoType::m_pWindoTypeDlg->GetDlgItem(ARXRLE_WINDOTYPE_CK_VISTB))->SetCheck(1);
		ArxRleUiDlgWindoType::m_pWindoTypeDlg->GetDlgItem(ARXRLE_WINDOTYPE_BN_HIDEDLG)->EnableWindow(TRUE);
	}
}

void ArxRleToolBarGenWnd::OnDrawWindo()
{
	if(ArxRleUiDlgWindoType::m_pWindoTypeDlg != NULL)
	{
		ArxRleUiDlgWindoType::m_pWindoTypeDlg->UpdateData(TRUE);
		
		// Transfer the values in the dialog
		// back to the global variables

		windInfo.m_dWindHt		= ArxRleUiDlgWindoType::m_pWindoTypeDlg->m_dHeight;
		windInfo.m_dWindWt		= ArxRleUiDlgWindoType::m_pWindoTypeDlg->m_dWidth;
		windInfo.m_nCols		= ArxRleUiDlgWindoType::m_pWindoTypeDlg->m_nCols;
		windInfo.m_nRows		= ArxRleUiDlgWindoType::m_pWindoTypeDlg->m_nRows;
		windInfo.m_nWindType	= ArxRleUiDlgWindoType::m_pWindoTypeDlg->m_nWindType;
		windInfo.m_startPt.x	= ArxRleUiDlgWindoType::m_pWindoTypeDlg->m_dXVal;
		windInfo.m_startPt.y	= ArxRleUiDlgWindoType::m_pWindoTypeDlg->m_dYVal;
	}

	ArxRleUiDlgWindoType::drawWindo();	
}

void ArxRleToolBarGenWnd::OnWindInfoDlg() 
{
	CAcModuleResourceOverride resOverride;

	ArxRleUiDlgWindoInfo dlg;
	dlg.DoModal();
}

void ArxRleToolBarGenWnd::OnAbout() 
{
	CAcModuleResourceOverride resOverride;

	ArxRleUiDlgAboutBox dbox(acedGetAcadDwgView());
	dbox.DoModal();
}

void ArxRleToolBarGenWnd::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnClose();
}

void ArxRleToolBarGenWnd::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CWnd::PostNcDestroy();
}
