// ArxRleUiDlgReg.h : header file
//

#ifndef ARXRLE_UIDLG_REG_H
#define ARXRLE_UIDLG_REG_H

#include "resource.h"
class ArxRleUiDlgReg : public CDialog
{
public:
	ArxRleUiDlgReg(CWnd* pParent = NULL);

	enum { IDD = ARXRLE_DLG_REG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedRegBnCode();
	afx_msg void OnBnClickedRegBnSerial();
	afx_msg void OnBnClickedRegBnReg();
	afx_msg void OnBnClickedRegBnExit();
};

#endif  // ARXRLE_UIDLG_REG_H
