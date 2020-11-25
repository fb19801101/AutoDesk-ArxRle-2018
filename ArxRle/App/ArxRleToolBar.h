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

#ifndef ARXRLETOOLBAR_H
#define ARXRLETOOLBAR_H

/****************************************************************************
**
**  CLASS ArxRleToolBar:
**
**  **jma
**
*************************************/

class ArxRleToolBar : public CToolBar {
	DECLARE_DYNAMIC (ArxRleToolBar)

	CWnd *m_pOwner;

public:
	ArxRleToolBar();

public:
	//{{AFX_VIRTUAL(ArxRleToolBar)
	//}}AFX_VIRTUAL
	static ArxRleToolBar* CreateToolBar(UINT nID, CWnd *pOwner, LPCTSTR lpszTitle = NULL);

public:
	virtual ~ArxRleToolBar();
	BOOL Create(CWnd *pParent, CWnd *pOwner = NULL,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_SIZE_DYNAMIC | CBRS_FLYBY | CBRS_TOP | CBRS_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_TRANSPARENT,
		UINT nID = AFX_IDW_TOOLBAR);

protected:
	//{{AFX_MSG(ArxRleToolBar)
	//}}AFX_MSG
	afx_msg void OnUpdateToolBar(CCmdUI *pCmdUI); //----- See TN031

	DECLARE_MESSAGE_MAP ()
};

#endif //ARXRLETOOLBAR_H
 