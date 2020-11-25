//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef ARXRLE_UIDLG_CRDTRM_H
#define ARXRLE_UIDLG_CRDTRM_H

#include "Resource.h"
#include "App/ArxRleButton.h"

// ArxRleUiDlgCrdTrm 对话框
class ArxRleUiDlgCrdTrm : public CAcUiDialog
{
// 构造
public:
	ArxRleUiDlgCrdTrm(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = ARXRLE_DLG_CRDTRM };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	int m_nSelMode;
	int m_nSelRef;
	ArxRleButtonXP	m_cConvert;
	ArxRleButtonXP	m_cClear;
	ArxRleButtonXP	m_cRead;
	ArxRleButtonXP	m_cSet;
	CEdit m_cMed;
	BOOL  m_bSmall;
	BOOL  m_bFlag;
	int   m_nHeight;
	ArxRleButton m_cApply;
	ArxRleButton m_cBtnFile;


public:
	void SetInterface(int nMode);

/*	double	m_B;
	double	m_L;
	double	m_H;
	double	m_Z;
	double	m_Y;
	double	m_X;*/
	CString m_B;
	CString m_L;
	CString m_H;
	CString m_Y;
	CString m_X;
	CString m_Z;

	double	m_L0;
	double	m_dx;
	double	m_dy;
	double	m_dz;
	double	m_rx;
	double	m_ry;
	double	m_rz;
	double	m_m;

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	afx_msg void OnMode1();
	afx_msg void OnMode2();
	afx_msg void OnMode3();
	afx_msg void OnMode4();
	afx_msg void OnMode5();
	afx_msg void OnRef1();
	afx_msg void OnRef2();
	afx_msg void OnRef3();
	afx_msg void OnBtnRead();
	afx_msg void OnBtnClear();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnConvert();
	afx_msg void OnBtnFile();
	afx_msg void OnBtnApply();
};

#endif //ARXRLE_UIDLG_CRDTRM_H
