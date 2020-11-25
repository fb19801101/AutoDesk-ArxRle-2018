// ArxRleToolsView.cpp: implementation of the ArxRleToolsView class.
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleToolsView.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArxRleToolsView::ArxRleToolsView()
{
	m_nToolBarID = ARXRLE_BAR_TOOLS;
	m_nCurrentTool = ARXRLE_TOOLS_SELECTION;
}

ArxRleToolsView::~ArxRleToolsView()
{

}


BEGIN_MESSAGE_MAP(ArxRleToolsView, ArxRlePaneView)
	//{{AFX_MSG_MAP(ArxRleToolsView)
	ON_COMMAND_RANGE(ARXRLE_TOOLS_SELECTION, ARXRLE_TOOLS_ELLIPSE2, OnToolsCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ARXRLE_TOOLS_SELECTION, ARXRLE_TOOLS_ELLIPSE2, OnUpdateToolsCommand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void ArxRleToolsView::Refresh()
{
	if (m_wndNavigateWnd.GetSafeHwnd())
		m_wndNavigateWnd.Invalidate(FALSE);
}

CWnd* ArxRleToolsView::OnCreateView()
{
	if (!m_wndNavigateWnd.Create(NULL, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CRect(0,0,0,0), this ))
	{
		TRACE0( "Unable to create tree control.\n" );
		return NULL;
	}

	return &m_wndNavigateWnd;
}

void ArxRleToolsView::OnToolsCommand(UINT nID)
{
	m_nCurrentTool = nID;

}

void ArxRleToolsView::OnUpdateToolsCommand(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_nCurrentTool == pCmdUI->m_nID? TRUE: FALSE);

}


/////////////////////////////////////////////////////////////////////////////
// CToolsNavigateWnd

CToolsNavigateWnd::CToolsNavigateWnd()
{
}

CToolsNavigateWnd::~CToolsNavigateWnd()
{
}


BEGIN_MESSAGE_MAP(CToolsNavigateWnd, CStatic)
	//{{AFX_MSG_MAP(CToolsNavigateWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolsNavigateWnd message handlers

BOOL CToolsNavigateWnd::OnEraseBkgnd(CDC*)
{
	return TRUE;
}

void CToolsNavigateWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CXTPClientRect rc(this);

	dc.FillSolidRect(rc, GetSysColor(COLOR_WINDOW));


	//CDockingContainersView* pView =
	//	((CMDIFrameWnd*)AfxGetMainWnd())->MDIGetActive()?
	//	(CDockingContainersView*)(((CMDIFrameWnd*)AfxGetMainWnd())->MDIGetActive()->GetActiveView())
	//	: NULL;

	//if (pView)
	//{
	//	pView->DrawLines(&dc, rc);
	//}
}

void CToolsNavigateWnd::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

	Invalidate(FALSE);
}
