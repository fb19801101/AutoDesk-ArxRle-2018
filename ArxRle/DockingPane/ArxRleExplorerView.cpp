// ArxRleExplorerView.cpp : implementation file
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

#include "ArxRleExplorerView.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRleExplorerView

ArxRleExplorerView::ArxRleExplorerView()
{
	m_nToolBarID = ARXRLE_BAR_EXPLORER;
}

ArxRleExplorerView::~ArxRleExplorerView()
{
}


BEGIN_MESSAGE_MAP(ArxRleExplorerView, ArxRlePaneView)
	//{{AFX_MSG_MAP(ArxRleExplorerView)
	ON_COMMAND_RANGE(ARXRLE_EXPLORER_PARENT, ARXRLE_EXPLORER_SEARCH, OnExplorerCommand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ArxRleExplorerView message handlers

CWnd* ArxRleExplorerView::OnCreateView()
{
	if (!m_wndExplorer.Create( WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
		CRect(0,0,0,0), this, 0xFF ))
	{
		TRACE0( "Unable to create tree control.\n" );
		return NULL;
	}
	//m_wndExplorer.ModifyStyleEx(0, WS_EX_STATICEDGE);


	// add the parent item, make it bold
	HTREEITEM htiParent = m_wndExplorer.InsertItem(_T("Codejock Software"));
	m_wndExplorer.SetItemState (htiParent, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM htiChild; // child item

	htiChild = m_wndExplorer.InsertItem (_T("Library"), 1, 1, htiParent);

	// add the children of the parent item
	HTREEITEM hti = m_wndExplorer.InsertItem(_T("Icons"), 2, 3, htiChild);
	m_wndExplorer.InsertItem(_T("Temporary Files"), 4, 4, htiChild);
	m_wndExplorer.InsertItem(_T("New Files"), 4, 4, htiChild);
	m_wndExplorer.Expand(hti, TVE_EXPAND);

	hti = m_wndExplorer.InsertItem(_T("Deleted Items"), 2, 3, htiParent);

	m_wndExplorer.Expand(htiParent, TVE_EXPAND);
	m_wndExplorer.Expand(htiChild, TVE_EXPAND);


	return &m_wndExplorer;
}

void ArxRleExplorerView::OnExplorerCommand(UINT)
{
	// TODO: Add your command handler code here
}
