// ArxRleIconsView.cpp : implementation file
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

#include "ArxRleIconsView.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRleIconsView

ArxRleIconsView::ArxRleIconsView()
{
}

ArxRleIconsView::~ArxRleIconsView()
{
}


BEGIN_MESSAGE_MAP(ArxRleIconsView, ArxRlePaneView)
	//{{AFX_MSG_MAP(ArxRleIconsView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ArxRleIconsView message handlers

CWnd* ArxRleIconsView::OnCreateView()
{
	if (!m_wndIcons.Create(WS_CHILD|WS_VISIBLE|LVS_ICON, CXTPEmptyRect(), this, 0))
		return NULL;

	return &m_wndIcons;
}
