// ArxRleUiDlgWindoType.h: interface for the ArxRleUiDlgWindoType class.
//

#ifndef ARXRLE_UIDLGWINDOTYPE_H
#define ARXRLE_UIDLGWINDOTYPE_H

#include "Resource.h"
#include "App/ArxRleToolBar.h"
#include "App/ArxRleToolBarGenWnd.h"
#include "App/ArxRleDocData.h"

#define windInfo ArxRleDocData::m_mgrDocVars.docData()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgWindoType dialog

class ArxRleUiDlgWindoType : public CDialog
{
// Construction
public:
	ArxRleUiDlgWindoType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ArxRleUiDlgWindoType)
	enum { IDD = ARXRLE_DLG_WINDOTYPE };
	int		m_nWindType;
	int		m_nCols;
	int		m_nRows;
	double	m_dHeight;
	double	m_dWidth;
	double	m_dXVal;
	double	m_dYVal;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	static ArxRleUiDlgWindoType* m_pWindoTypeDlg;
	static ArxRleToolBar* m_pToolBar;
	static ArxRleToolBarGenWnd* m_pToolBarGenWnd;
	static void showWindoDlg();
	static void drawWindo();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRleUiDlgWindoType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ArxRleUiDlgWindoType)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnBtnPickPt();
	afx_msg void OnChkViewToolBar();
	afx_msg void OnBtnHideDlg();
	//}}AFX_MSG
	afx_msg LRESULT onAcadKeepFocus(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //ARXRLEUIDLGWINDOTYPE_H
