// ArxRleUiTdcSqxElement.h: interface for the ArxRleUiTdcSqxElement class.
//

#ifndef ARXRLE_UITDC_SQX_ELEMENT_H
#define ARXRLE_UITDC_SQX_ELEMENT_H

#include "Resource.h"
#include "ArxRleCurveElement.h"
#include "App\ArxRleButton.h"

// ArxRleUiTdcSqxElement 对话框

class ArxRleUiTdcSqxElement : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcSqxElement)

public:
	ArxRleUiTdcSqxElement();   // 标准构造函数
	virtual ~ArxRleUiTdcSqxElement();

	void InitGridCtrl();

// 对话框数据
	enum { IDD = ARXRLE_TDC_SQX_ELEMENT };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedSqxElementBnData();
	afx_msg void OnBnClickedSqxElementBnImport();
	afx_msg void OnBnClickedSqxElementBnCalc();
	afx_msg void OnGridDblClick(NMHDR *pNMHDR, LRESULT* pResult);
	afx_msg void OnGridRClick(NMHDR *pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

private:
	double m_DK,m_H,m_R,m_I1,m_I2,m_L,m_T,m_E;
	double m_mBegin,m_mEnd,m_mDist;
	CString m_openPathName;
	CString m_sqxPathName;
	CString m_savePathName;
	ArxRleCurveElement m_curveElement;
	SQXELEMENT m_sqx;

	ArxRleButtonXP m_bnData;
	ArxRleButtonXP m_bnImport;
	ArxRleButtonXP m_bnCalc;

	CXTPGridControl* m_pGridCtrl;
	CImageList m_imgList;
	GV_ITEM m_gvItem;
	CStatic m_gpGridCtrl;
};

#endif //ARXRLE_UITDC_SQX_ELEMENT_H
