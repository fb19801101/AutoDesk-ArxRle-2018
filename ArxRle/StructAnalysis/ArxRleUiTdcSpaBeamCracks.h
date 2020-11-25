// ArxRleUiTdcSpaBeamCracks.h: interface for the ArxRleUiTdcSpaBeamCracks class.
//

#ifndef ARXRLE_UITDC_SPA_BEAM_CRACKS_H
#define ARXRLE_UITDC_SPA_BEAM_CRACKS_H

#include "Resource.h"


// ArxRleUiTdcSpaBeamCracks 对话框

class ArxRleUiTdcSpaBeamCracks : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcSpaBeamCracks)

public:
	ArxRleUiTdcSpaBeamCracks();   // 标准构造函数
	virtual ~ArxRleUiTdcSpaBeamCracks();

	// 对话框数据
	enum { IDD = ARXRLE_TDC_STRUCT_SAP_BEAMCRACKS };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持OnCmdMsg

protected:
	afx_msg void OnClickBtnCalc();
	DECLARE_MESSAGE_MAP()

public:
	CComboBox	m_ComboGjXz;
	CComboBox	m_ComboFy;
	CComboBox	m_ComboFcuk;
	float	m_Asa;
	float	m_Asb;
	float	m_B;
	float	m_Bfd;
	float	m_Bfu;
	float	m_Bhcs;
	float	m_Bhcx;
	float	m_C;
	BOOL	m_bNaoDu;
	BOOL	m_bWidth;
	float	m_Deq;
	float	m_H;
	float	m_Hfd;
	float	m_Hfu;
	float	m_Lo;
	float	m_Mk;
	float	m_Mq;
	float	m_Nk;
};

#endif //ARXRLE_UITDC_SPA_BEAM_CRACKS_H