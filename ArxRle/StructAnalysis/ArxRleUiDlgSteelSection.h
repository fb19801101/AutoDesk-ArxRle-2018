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

#ifndef ARXRLE_UIDLG_STEEL_SECTION_H
#define ARXRLE_UIDLG_STEEL_SECTION_H

#include "Resource.h"
#include "App/ArxRleButton.h"
#include "App/ArxRleListCtrl.h" 
#include "ArxRleSteelSection.h"


/****************************************************************************
**
**	CLASS ArxRleUiDlgSteelSection:
**
**	**000
**
*************************************/

class ArxRleUiDlgSteelSection : public CAcUiDialog
{
	DECLARE_DYNAMIC(ArxRleUiDlgSteelSection)

public:
	ArxRleUiDlgSteelSection(CWnd* pParent = NULL, HINSTANCE hInstance =NULL);   // 标准构造函数
	virtual ~ArxRleUiDlgSteelSection();

	// 对话框数据
	enum { IDD = ARXRLE_DLG_STEEL_SECTION };

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg LRESULT OnAcadKeepFocus(WPARAM, LPARAM);
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnCbnSelchangeCbType();
	afx_msg void OnNMClickSteelSectionLcTypes(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

public:
	int               m_item;
	CAcUiComboBox     m_cbType;
	ArxRleButton      m_bnDraw;

	CToolTipCtrl     *m_pToolTip;
	ArxRleListCtrl   m_lstTypes;
	ArxRleListCtrl   m_lstValues;
	CStatic          m_wndPreview;

	void DrawGongSteelSection(STEELSECTION sec);
	void DrawCaoSteelSection(STEELSECTION sec);
	void DrawJiaoSteelSection(STEELSECTION sec);
	void DrawJiaoSteelSection2(STEELSECTION sec);
	void DrawHSteelSection(STEELSECTION sec);
	void DrawGuanSteelSection(STEELSECTION sec);
};

#endif  // ARXRLE_UIDLG_STEEL_SECTION_H
