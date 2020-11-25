// ArxRleUiDlgDimLand.h: interface for the ArxRleUiDlgDimLand class.
//

#ifndef ARXRLE_UIDLG_DIMLAND_H
#define ARXRLE_UIDLG_DIMLAND_H

#include "Resource.h"
#include "App/ArxRleButton.h"
#include "App/ArxRleListCtrl.h" 
#include "afxwin.h"

// ArxRleUiDlgDimLand 对话框
class ArxRleUiDlgDimLand : public CAcUiDialog 
{
	DECLARE_DYNAMIC(ArxRleUiDlgDimLand)

public:
	ArxRleUiDlgDimLand(CWnd* pParent = NULL, HINSTANCE hInstance =NULL);   // 标准构造函数
	virtual ~ArxRleUiDlgDimLand();

// 对话框数据
	enum { IDD = ARXRLE_DLG_DIMLAND };

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnAcadKeepFocus(WPARAM, LPARAM);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg LRESULT OnItemSorted(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

public:
	CAcUiComboBox     m_cbType;
	CButton           m_ckDrawText;
	CAcUiPickButton   m_bnPt1;
	CAcUiPickButton   m_bnPt2;
	ArxRleButton      m_bnEnt;
	ArxRleButton      m_bnDimLand;
	ArxRleButton      m_bnImport;
	ArxRleButton      m_bnExport;
	ArxRleButton      m_bnClear;
	CAcUiEdit         m_etX1;
	CAcUiEdit         m_etY1;
	CAcUiEdit         m_etZ1;
	CAcUiEdit         m_etX2;
	CAcUiEdit         m_etY2;
	CAcUiEdit         m_etZ2;
	CAcUiEdit         m_etPrix;
	CAcUiEdit         m_etGap;
	CAcUiEdit         m_etFont;
	CAcUiEdit         m_etSize;

	BOOL              m_bFileSel;
	BOOL              m_bFlag;

	CString m_strDataFilePathName;
	CString m_strDataFileName;

	CToolTipCtrl   *m_pToolTip;
	ArxRleListCtrl m_wndList;

	afx_msg void OnBnClickedBtnPt1();
	afx_msg void OnBnClickedBtnPt2();
	afx_msg void OnBnClickedBtnEnt();
	afx_msg void OnBnClickedBtnDimLand();
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnBnClickedBtnExport();
	afx_msg void OnBnClickedBtnClear();
};

#endif //ARXRLE_UIDLG_DIMLAND_H