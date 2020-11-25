// ArxRleUiDlgMeasure.h: interface for the ArxRleUiDlgMeasure class.
//

#ifndef ARXRLE_UIDLG_MEASURE_H
#define ARXRLE_UIDLG_MEASURE_H

#include "Resource.h"
#include "DbEntity\ArxRleEntityClass.h"
#include "afxwin.h"


// ArxRleUiDlgMeasure 对话框

class ArxRleUiDlgMeasure : public CDialogEx
{
	DECLARE_DYNAMIC(ArxRleUiDlgMeasure)

public:
	ArxRleUiDlgMeasure(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ArxRleUiDlgMeasure();
	void GetPolylineVertexs();
	void SetInData(BOOL bInData = TRUE) {m_bInData = bInData;}
	void SetDataType(int nDataType = 1) {m_nDataType = nDataType;}
	BOOL IsInData() {return m_bInData;}


// 对话框数据
	enum { IDD = ARXRLE_DLG_MEASURE };

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

private:
	CString m_strDataFilePathName;
	CString m_strDataFileName;

	CComboBox m_cbDataType;
	CComboBox m_cbResultType;
	CButton m_bnDataFileSel;
	CButton m_ckXY;
	CButton m_ckZ;
	CButton m_ckHDM;
	CButton m_ckZDM;

	BOOL m_bInData;
	int m_nDataType;
	CPt3dArray m_vecPt3D;

	afx_msg void OnBnClickedMeasureButtonDatafile();
	afx_msg void OnBnClickedOk();
};

#endif //ARXRLEUIDLGMEASURE_H