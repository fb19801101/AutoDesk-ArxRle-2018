// ArxRleUiTdcNetPlanWorkData.h: interface for the ArxRleUiTdcNetPlanWorkData class.
//

#ifndef ARXRLE_UITDC_NETPLAN_WORKDATA_H
#define ARXRLE_UITDC_NETPLAN_WORKDATA_H

#include "Resource.h"



// ArxRleUiTdcNetPlanWorkData 对话框

class ArxRleUiTdcNetPlanWorkData : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcNetPlanWorkData)

public:
	ArxRleUiTdcNetPlanWorkData();   // 标准构造函数
	virtual ~ArxRleUiTdcNetPlanWorkData();

	// 对话框数据
	enum { IDD = ARXRLE_TDC_NETPLAN_WORKDATA };

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strXlsFilePath;
	CString m_strXlsFileName;
	CString m_strXlsSheetName;
	int m_nWorkNameCol1;
	int m_nWorkNameCol2;
	int m_nTimeBeginCol;
	int m_nTimeEndCol;
	int m_nNodeBeginCol;
	int m_nNodeEndCol;
	int m_nWorkBeginRow;
	int m_nWorkEndRow;
	CButton m_btnFilePath;
	CComboBox m_cxSheetName;
	CComboBox m_cxWorkNameCol1;
	CComboBox m_cxWorkNameCol2;
	CComboBox m_cxTimeBeginCol;
	CComboBox m_cxTimeEndCol;
	CComboBox m_cxNodeBeginCol;
	CComboBox m_cxNodeEndCol;

	afx_msg void OnBnClickedNetPlanPage2BnFilepath();
	afx_msg void OnCbnSelchangeNetPlanPage2CxSheetname();
};

#endif //ARXRLE_UITDC_NETPLAN_WORKDATA_H