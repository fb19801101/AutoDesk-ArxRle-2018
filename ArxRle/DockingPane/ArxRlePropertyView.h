// ArxRleToolsView.h: interface for the ArxRleToolsView class.
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

#ifndef ARXRLE_PROPERTY_VIEW_H
#define ARXRLE_PROPERTY_VIEW_H

#include "ArxRlePaneView.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyView window

class ArxRlePropertyView : public ArxRlePaneView
{
	// Construction
public:
	ArxRlePropertyView();

	// Attributes
public:
	CXTPPropertyGrid m_wndPropertyGrid;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRlePropertyView)
	//}}AFX_VIRTUAL
	CWnd* OnCreateView();
	void UpdateContent(AcDbObjectId& id);
	void UpdateEntity(AcDbObjectId& id);
	BOOL m_bUpdate;

	// Implementation
public:
	virtual ~ArxRlePropertyView();

	// Generated message map functions
protected:
	//{{AFX_MSG(ArxRlePropertyView)
	afx_msg LRESULT OnAcadKeepFocus(WPARAM, LPARAM);
	afx_msg LRESULT OnGridNotify(WPARAM wParam, LPARAM lParam);
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // ARXRLE_PROPERTY_VIEW_H
