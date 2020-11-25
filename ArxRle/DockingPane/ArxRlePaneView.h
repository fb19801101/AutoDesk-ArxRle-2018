// ArxRlePaneView.h : header file
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

#ifndef ARXRLE_PANEVIEW_H
#define ARXRLE_PANEVIEW_H

#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRlePaneView window


class ArxRlePaneView : public CWnd
{
// Construction
public:
	ArxRlePaneView();

// Attributes
public:
	CWnd* m_pView;

	CListCtrl m_wndView;
	int m_nToolBarID;


	CXTPToolBar m_wndToolBar;

// Operations
public:

	virtual CWnd* ArxRlePaneView::OnCreateView();


	CWnd* CreatePane(CWnd* pParentWnd);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRlePaneView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ArxRlePaneView();

	// Generated message map functions
protected:
	//{{AFX_MSG(ArxRlePaneView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // ARXRLE_PANEVIEW_H
