// TBGenWnd.h : header file
//

#ifndef ARXRLE_TOOLBARGENWND_H
#define ARXRLE_TOOLBARGENWND_H

/////////////////////////////////////////////////////////////////////////////
// ArxRleToolBarGenWnd window

class ArxRleToolBarGenWnd : public CWnd
{
// Construction
public:
	ArxRleToolBarGenWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRleToolBarGenWnd)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ArxRleToolBarGenWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(ArxRleToolBarGenWnd)
	afx_msg void OnShowWindTypeDlg();
	afx_msg void OnDrawWindo();
	afx_msg void OnWindInfoDlg();
	afx_msg void OnAbout();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif //ARXRLETOOLBARGENWND_H
