// ArxRleUiTdcCurveXY.h: interface for the ArxRleUiTdcCurveXY class.
//

#ifndef ARXRLE_UITDC_CURVE_XY_H
#define ARXRLE_UITDC_CURVE_XY_H

#include "Resource.h"
#include "ArxRleCurveElement.h"

// ArxRleUiTdcCurveXY 对话框

class ArxRleUiTdcCurveXY : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcCurveXY)

public:
	ArxRleUiTdcCurveXY();   // 标准构造函数
	virtual ~ArxRleUiTdcCurveXY();

	void InitGridCtrl();

// 对话框数据
	enum { IDD = ARXRLE_TDC_CURVE_XY };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedCurveXyBnData();
	afx_msg void OnBnClickedCurveXyBnImport();
	afx_msg void OnBnClickedCurveXyBnCalc();
	afx_msg void OnGridDblClick(NMHDR *pNMHDR, LRESULT* pResult);
	afx_msg void OnGridRClick(NMHDR *pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

private:
	double m_x1,m_y1,m_x2,m_y2,m_x3,m_y3;
	double m_R,m_ls,m_L,m_A,m_T,m_E,m_W;
	double m_QD,m_ZD,m_ZH,m_HY,m_QZ,m_YH,m_HZ;
	double m_mDist,m_mOffset;
	ArxRleCurveElement m_curveElement;
	CString m_openPathName;
	CString m_jdPathName;
	CString m_savePathName;

	CXTPGridControl* m_pGridCtrl;
	CImageList m_imgList;
	GV_ITEM m_gvItem;
	CStatic m_gpGridCtrl;
};

#endif //ARXRLE_UITDC_CURVE_XY_H
