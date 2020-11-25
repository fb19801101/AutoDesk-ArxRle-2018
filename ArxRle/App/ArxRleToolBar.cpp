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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleToolBar.h"


IMPLEMENT_DYNAMIC (ArxRleToolBar, CToolBar)

BEGIN_MESSAGE_MAP (ArxRleToolBar, CToolBar)
	//{{AFX_MSG_MAP(ArxRleToolBar)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE (0x0000, 0xffff, OnUpdateToolBar) //----- See TN031
END_MESSAGE_MAP ()

ArxRleToolBar::ArxRleToolBar() {
	m_pOwner = NULL;
}

ArxRleToolBar::~ArxRleToolBar() {
}

BOOL ArxRleToolBar::Create(CWnd *pParent, CWnd *pOwner, DWORD dwStyle, UINT nID) {
	if(CToolBar::Create(pParent, dwStyle, nID)) {
		m_pOwner = (pOwner == NULL ? pParent : pOwner);
		ASSERT(m_pOwner->GetSafeHwnd() != NULL);
		ASSERT_KINDOF(CWnd, m_pOwner);
		GetToolBarCtrl().SetOwner(m_pOwner);

		//----- Unfortunatelly CToolBar::Create() ignores TBSTYLE_FLAT | TBSTYLE_TRANSPARENT
		ModifyStyle(0, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT, 0);
		return TRUE;
	}
	return FALSE;
}

void ArxRleToolBar::OnUpdateToolBar(CCmdUI *pCmdUI) {
	pCmdUI->DoUpdate(m_pOwner, FALSE);
}

ArxRleToolBar* ArxRleToolBar::CreateToolBar(UINT nID, CWnd *pOwner, LPCTSTR lpszTitle) {
	ArxRleToolBar* pToolbar = new ArxRleToolBar;
	pToolbar->Create(acedGetAcadFrame(), pOwner);
	AfxSetResourceHandle(::GetModuleHandle(_T("CArx.arx")));
	pToolbar->LoadToolBar(nID);
	AfxSetResourceHandle(acedGetAcadResourceInstance());
	pToolbar->EnableDocking(CBRS_ALIGN_ANY);
	if ( lpszTitle != NULL )
		pToolbar->SetWindowText(lpszTitle);

	acedGetAcadFrame()->FloatControlBar(pToolbar, CPoint(100, 100), CBRS_ALIGN_TOP);
	acedGetAcadFrame()->ShowControlBar(pToolbar, FALSE, TRUE);

	return pToolbar;
}
 