// ArxRleColorsView.h: interface for the ArxRleColorsView class.
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

#ifndef ARXRLE_COLORS_VIEW_H
#define ARXRLE_COLORS_VIEW_H

#include "ArxRlePaneView.h"

/////////////////////////////////////////////////////////////////////////////
// CColorsSwatchWnd window

class CColorsSwatchWnd : public CStatic
{
// Construction
public:
	CColorsSwatchWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorsSwatchWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorsSwatchWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorsSwatchWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


class ArxRleColorsView : public ArxRlePaneView
{
public:
	ArxRleColorsView();
	virtual ~ArxRleColorsView();

	CWnd* OnCreateView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRleColorsView)
	//}}AFX_VIRTUAL

	CColorsSwatchWnd m_wndColors;

	//{{AFX_MSG(ArxRleColorsView)
	afx_msg void OnColorsCommand(UINT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // ARXRLE_COLORS_VIEW_H
