// ArxRleIconsView.h : header file
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

#ifndef ARXRLE_ICONS_VIEW_H
#define ARXRLE_ICONS_VIEW_H

#include "ArxRlePaneView.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRleIconsView window

class ArxRleIconsView : public ArxRlePaneView
{
// Construction
public:
	ArxRleIconsView();

// Attributes
public:
	CListCtrl m_wndIcons;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRleIconsView)
	//}}AFX_VIRTUAL
	CWnd* OnCreateView();

// Implementation
public:
	virtual ~ArxRleIconsView();

	// Generated message map functions
protected:
	//{{AFX_MSG(ArxRleIconsView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // ARXRLE_ICONS_VIEW_H
