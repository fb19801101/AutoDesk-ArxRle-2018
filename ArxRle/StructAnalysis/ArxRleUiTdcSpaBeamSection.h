// ArxRleUiTdcSpaBeamSection.h: interface for the ArxRleUiTdcSpaBeamSection class.
//

#ifndef ARXRLE_UITDC_SPA_BEAM_SECTION_H
#define ARXRLE_UITDC_SPA_BEAM_SECTION_H

#include "Resource.h"


// ArxRleUiTdcSpaBeamSection 对话框

class ArxRleUiTdcSpaBeamSection : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcSpaBeamSection)

public:
	ArxRleUiTdcSpaBeamSection();   // 标准构造函数
	virtual ~ArxRleUiTdcSpaBeamSection();

	// 对话框数据
	enum { IDD = ARXRLE_TDC_STRUCT_SPA_BEAMSECTION };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	afx_msg void OnClickBtnCalc();
	afx_msg void OnCheckLa();
	afx_msg void OnCheckZheng();
	afx_msg void OnCheckXie();
	afx_msg void OnCheckNiu();
	afx_msg void OnCheckDi();
	afx_msg void OnSelchangeComboJmlx();
	afx_msg void OnCheckJzhload();
	afx_msg void OnCheckDuichen();
	afx_msg void OnCheckJunyun();
	DECLARE_MESSAGE_MAP()

public:
	CComboBox	m_ComboJmLx;
	CComboBox	m_ComboRo;
	CComboBox	m_ComboFyc;
	CComboBox	m_ComboLLx;
	CComboBox	m_ComboKzdj;
	CComboBox	m_ComboFyv;
	CComboBox	m_ComboFy;
	CComboBox	m_ComboFcuk;
	float	m_Alf;
	float	m_Asa;
	float	m_Asb;
	float	m_B;
	float	m_Bfd;
	float	m_Bfu;
	float	m_H;
	float	m_Hfd;
	float	m_Hfu;
	float	m_Rmd;
	float	m_Span;
	float	m_S;
	float	m_T;
	BOOL	m_bLa;
	BOOL	m_bEq;
	BOOL	m_bNiu;
	BOOL	m_bXjm;
	BOOL	m_bWan;
	float	m_M;
	float	m_N;
	float	m_asu;
	float	m_asd;
	float	m_V;
	float	m_Pmin;
	BOOL	m_bJLoad;
	BOOL	m_bDChen;
	BOOL	m_bJYun;
	float	m_E0;
};

#endif //ARXRLE_UITDC_SPA_BEAM_SECTION_H