// ArxRleUiTdmCurveElement.h: interface for the ArxRleUiTdmCurveElement class.
//

#ifndef ARXRLE_UITDM_CURVE_ELEMENT_H
#define ARXRLE_UITDM_CURVE_ELEMENT_H

#include "Resource.h"
#include "ArxRleUiTdcCurveElement.h"
#include "ArxRleUiTdcOvalElement.h"
#include "ArxRleUiTdcCurveXY.h"
#include "ArxRleUiTdcSqxElement.h"

// ArxRleUiTdmCurveElement 对话框
class ArxRleUiTdmCurveElement : public CAcUiTabMainDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdmCurveElement)

public:
	ArxRleUiTdmCurveElement(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ArxRleUiTdmCurveElement();

	// 对话框数据
	enum { IDD = ARXRLE_TDM_CURVE_ELEMENT };

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	CAdUiTab m_tabCtrl;
	ArxRleUiTdcCurveElement* m_pTdcCurveElement;
	ArxRleUiTdcOvalElement* m_pTdcOvalElement;
	ArxRleUiTdcCurveXY* m_pTdcCurveXY;
	ArxRleUiTdcSqxElement* m_pTdcSqxElement;
};

#endif //ARXRLE_UITDM_CURVE_ELEMENT_H