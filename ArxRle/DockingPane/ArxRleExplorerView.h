// ArxRleExplorerView.h : header file
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

#ifndef ARXRLE_EXPLORERVIEW_H
#define ARXRLE_EXPLORERVIEW_H

#include "ArxRlePaneView.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRleExplorerView window

class ArxRleExplorerView : public ArxRlePaneView
{
// Construction
public:
	ArxRleExplorerView();

// Attributes
public:
	CTreeCtrl   m_wndExplorer;

// Operations
public:
	CWnd* OnCreateView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRleExplorerView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ArxRleExplorerView();

	// Generated message map functions
protected:
	//{{AFX_MSG(ArxRleExplorerView)
	afx_msg void OnExplorerCommand(UINT);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // ARXRLE_EXPLORERVIEW_H
