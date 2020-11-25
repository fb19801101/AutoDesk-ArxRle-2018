// ArxRleUiDlgDrawCondition.h: interface for the ArxRleUiDlgDrawCondition class.
//

#ifndef ARXRLE_UIDLG_DRAW_CONDITION_H
#define ARXRLE_UIDLG_DRAW_CONDITION_H

#include "Resource.h"
#include "App/ArxRleButton.h"
#include "App/ArxRleListCtrl.h" 

#define PARAMETS_COUNT 8


// ArxRleUiDlgDrawCondition 对话框

struct SQX
{
	double S, H, R, I1, I2, T, E, L;
	SQX()
	{
		S=H=R=I1=I2=T=E=L = 0;
	}
	SQX(const SQX& src)
	{
		S = src.S;
		H = src.H;
		R = src.R;
		I1 = src.I1;
		I2 = src.I2;
		T = src.T;
		E = src.E;
		L = src.L;
	}
};

class ArxRleUiDlgDrawCondition : public CAcUiDialog 
{
	DECLARE_DYNAMIC(ArxRleUiDlgDrawCondition)

public:
	ArxRleUiDlgDrawCondition(CWnd* pParent = NULL, HINSTANCE hInstance =NULL);   // 标准构造函数
	virtual ~ArxRleUiDlgDrawCondition();

// 对话框数据
	enum { IDD = ARXRLE_DLG_DRAW_CONDITION };

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnAcadKeepFocus(WPARAM, LPARAM);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg LRESULT OnCheckBox(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnItemSorted(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

public:
	CAcUiComboBox     m_cbType;
	CButton           m_ckDrawText;
	CAcUiPickButton   m_bnPt1;
	CAcUiPickButton   m_bnPt2;
	ArxRleButton      m_bnCalc;
	ArxRleButton      m_bnSel;
	ArxRleButton      m_bnExec;
	ArxRleButton      m_bnRoll;
	ArxRleButton      m_bnExport;
	ArxRleButton      m_bnClear;
	CAcUiEdit         m_etX1;
	CAcUiEdit         m_etY1;
	CAcUiEdit         m_etZ1;
	CAcUiEdit         m_etX2;
	CAcUiEdit         m_etY2;
	CAcUiEdit         m_etZ2;
	CAcUiEdit         m_etParamets[PARAMETS_COUNT];
	CButton           m_ckParamets[PARAMETS_COUNT];
	CStatic           m_scParamets[PARAMETS_COUNT];

	CString m_strDataFilePathName;
	CString m_strDataFileName;
	BOOL m_bSmall;
	int m_nHeight;
	BOOL m_bFlag;

	CToolTipCtrl   *m_pToolTip;
	ArxRleListCtrl m_wndList;

	void SetParamets(int count, CString* strs);
	int GetParametsUnCheck(int bgegin, int end);
	SQX GetSqx(double stat, vector<SQX> vecSqx);
	vector<SQX> GetSqxs(CString filePath);
	double SqxCalc(double stat, SQX sqx);
	BOOL IsSqx(double stat, SQX sqx);

	afx_msg void OnBnClickedBtnPt1();
	afx_msg void OnBnClickedBtnPt2();
	afx_msg void OnBnClickedBtnSel();
	afx_msg void OnBnClickedBtnCalc();
	afx_msg void OnBnClickedBtnExec();
	afx_msg void OnCbnSelchangeCbType();
	afx_msg void OnBnClickedBtnCheck();
	afx_msg void OnBnClickedBtnRoll();
	afx_msg void OnBnClickedBtnExport();
	afx_msg void OnBnClickedBtnClear();
};

#endif //ARXRLE_UIDLG_DRAW_CONDITION_H