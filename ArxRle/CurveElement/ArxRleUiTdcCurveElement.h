// ArxRleUiTdcCurveElement.h: interface for the ArxRleUiTdcCurveElement class.
//

#ifndef ARXRLE_UITDC_CURVE_ELEMENT_H
#define ARXRLE_UITDC_CURVE_ELEMENT_H

#include "Resource.h"
#include "ArxRleCurveElement.h"


// ArxRleUiTdcCurveElement 对话框

class ArxRleUiTdcCurveElement : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcCurveElement)

public:
	ArxRleUiTdcCurveElement();   // 标准构造函数
	virtual ~ArxRleUiTdcCurveElement();

// 对话框数据
	enum { IDD = ARXRLE_TDC_CURVE_ELEMENT };

public:
	void InitGridCtrl();

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnAcadKeepFocus(WPARAM, LPARAM);
	afx_msg void OnBnClickedOpenfile();
	afx_msg void OnBnClickedCalcelement();
	afx_msg void OnBnClickedSavefile();
	afx_msg void OnBnClickedDrawcurve();
	afx_msg void OnBnClickedShowdata();
	afx_msg void OnBnClickedAddrow();
	afx_msg void OnBnClickedDelrow();
	afx_msg void OnBnClickedSavechange();
	DECLARE_MESSAGE_MAP()

private:
	ArxRleCurveElement m_curveElement;
	CString m_openPathName;
	CString m_savePathName;
	double m_breakBegin;
	double m_breakEnd;
	double m_distEases;

	CButton m_bnOpenFile;
	CButton m_bnSaveFile;
	CXTPGridControl* m_pGridCtrl;
	CImageList m_imgList;
	GV_ITEM m_gvItem;
	CStatic m_gpGridCtrl;
};

#endif //ARXRLE_UITDC_CURVE_ELEMENT_H
