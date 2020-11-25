// ArxRleUiTdcSpaCircleStrength.h: interface for the ArxRleUiTdcSpaCircleStrength class.
//

#ifndef ARXRLE_UITDC_SPA_CIRCLE_STRENGTH_H
#define ARXRLE_UITDC_SPA_CIRCLE_STRENGTH_H

#include "Resource.h"


// ArxRleUiTdcSpaCircleStrength 对话框

class ArxRleUiTdcSpaCircleStrength : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcSpaCircleStrength)

public:
	ArxRleUiTdcSpaCircleStrength();   // 标准构造函数
	virtual ~ArxRleUiTdcSpaCircleStrength();

	// 对话框数据
	enum { IDD = ARXRLE_TDC_STRUCT_SAP_CIRCLESTRENGTH };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	afx_msg void OnClickBtnCalc();
	DECLARE_MESSAGE_MAP()

public:
	CComboBox	m_ComboKzdj;
	CComboBox	m_ComboFyv;
	CComboBox	m_ComboFy;
	CComboBox	m_ComboFcuk;
	float	m_Bhcs;
	BOOL	m_bDi;
	BOOL	m_bKjz;
	BOOL	m_bYiTa;
	BOOL	m_bZjm;
	BOOL	m_bXjm;
	float	m_D;
	float	m_Rmd;
	float	m_Span;
	float	m_M;
	float	m_N;
	float	m_S;
	float	m_Vx;
	float	m_Vy;
};

#endif //ARXRLE_UITDC_SPA_CIRCLE_STRENGTH_H