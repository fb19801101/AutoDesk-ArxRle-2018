// ArxRleColorsView.cpp: implementation of the ArxRleColorsView class.
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

#include "ArxRleColorsView.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArxRleColorsView::ArxRleColorsView()
{
	m_nToolBarID = ARXRLE_BAR_COLORS;
}

ArxRleColorsView::~ArxRleColorsView()
{

}

BEGIN_MESSAGE_MAP(ArxRleColorsView, ArxRlePaneView)
	//{{AFX_MSG_MAP(ArxRleExplorerView)
	ON_COMMAND_RANGE(ARXRLE_COLORS_EXPLORE, ARXRLE_COLROS_SWITCH, OnColorsCommand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CWnd* ArxRleColorsView::OnCreateView()
{
	if (!m_wndColors.Create(NULL, WS_VISIBLE | WS_CHILD |SS_NOTIFY,
		CRect(0,0,0,0), this ))
	{
		TRACE0( "Unable to create tree control.\n" );
		return NULL;
	}

	return &m_wndColors;
}

void ArxRleColorsView::OnColorsCommand(UINT)
{
	// TODO: Add your command handler code here

}


/////////////////////////////////////////////////////////////////////////////
// CColorsSwatchWnd

CColorsSwatchWnd::CColorsSwatchWnd()
{
}

CColorsSwatchWnd::~CColorsSwatchWnd()
{
}


BEGIN_MESSAGE_MAP(CColorsSwatchWnd, CStatic)
	//{{AFX_MSG_MAP(CColorsSwatchWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorsSwatchWnd message handlers

BOOL CColorsSwatchWnd::OnEraseBkgnd(CDC*)
{
	return TRUE;
}

void CColorsSwatchWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CXTPClientRect rc(this);

	CBitmap bmp;
	VERIFY(bmp.LoadBitmap(ARXRLE_BMP_SWATCH));
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);

	CXTPCompatibleDC dcMem(&dc, &bmp);

	dc.StretchBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
}

void CColorsSwatchWnd::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

	Invalidate(FALSE);

}
