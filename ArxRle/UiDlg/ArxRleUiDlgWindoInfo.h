// ArxRleUiDlgWindoInfo.h: interface for the ArxRleUiDlgWindoInfo class.
//

#ifndef ARXRLE_UIDLGWINDOINFO_H
#define ARXRLE_UIDLGWINDOINFO_H

#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgWindoInfo dialog

class ArxRleUiDlgWindoInfo : public CDialog
{
// Construction
public:
	CImageList m_imgList;
	CTreeCtrl* m_pTreeCtrl;
	ArxRleUiDlgWindoInfo(CWnd* pParent = NULL);   // standard constructor

	int m_nIdxWindow;
	int m_nIdxRect;
	int m_nIdxArch;
	int m_nIdxApex;
	int m_nIdxHeight;
	int m_nIdxWidth;
	int m_nIdxRows;
	int m_nIdxCols;
	int m_nIdxStartPt;

	void AddTreeViewItems();
	HTREEITEM AddOneItem(HTREEITEM, CString, HTREEITEM, int, BOOL);

// Dialog Data
	//{{AFX_DATA(ArxRleUiDlgWindoInfo)
	enum { IDD = ARXRLE_DLG_TREEDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRleUiDlgWindoInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ArxRleUiDlgWindoInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //ARXRLEUIDLGWINDOINFO_H
