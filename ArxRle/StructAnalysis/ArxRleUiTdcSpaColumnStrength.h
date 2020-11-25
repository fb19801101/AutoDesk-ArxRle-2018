// ArxRleUiTdcSpaColumnStrength.h: interface for the ArxRleUiTdcSpaColumnStrength class.
//

#ifndef ARXRLE_UITDC_SPA_COLUMN_STRENGTH_H
#define ARXRLE_UITDC_SPA_COLUMN_STRENGTH_H

#include "Resource.h"


// ArxRleUiTdcSpaColumnStrength 对话框

class ArxRleUiTdcSpaColumnStrength : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcSpaColumnStrength)

public:
	ArxRleUiTdcSpaColumnStrength();   // 标准构造函数
	virtual ~ArxRleUiTdcSpaColumnStrength();

	// 对话框数据
	enum { IDD = ARXRLE_TDC_STRUCT_SAP_COLUMNSTRENGTH };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	afx_msg void OnClickBtnCalc();
	DECLARE_MESSAGE_MAP()

public:
	CComboBox	m_ComboKzdj;
	CComboBox	m_ComboKlxl;
	CComboBox	m_ComboFyv;
	CComboBox	m_ComboFy;
	CComboBox	m_ComboFcuk;
	float	m_Alf;
	float	m_B;
	float	m_Bfd;
	float	m_Bfu;
	float	m_Bhcx;
	BOOL	m_bDi;
	BOOL	m_bXie;
	BOOL	m_bYiTa;
	float	m_Dfd;
	float	m_Dfu;
	float	m_Dimc;
	float	m_Dimx;
	float	m_Dimy;
	float	m_Elx;
	float	m_Ely;
	float	m_H;
	float	m_Hfd;
	float	m_Hfu;
	float	m_Lmd;
	float	m_Mx;
	float	m_My;
	float	m_N;
	int		m_bSigleOrDouble;
	float	m_S;
	float	m_T;
	float	m_Vx;
	float	m_Vy;
};

#endif //ARXRLE_UITDC_SPA_COLUMN_STRENGTH_H