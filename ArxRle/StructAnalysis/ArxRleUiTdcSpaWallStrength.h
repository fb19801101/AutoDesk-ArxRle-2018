// ArxRleUiTdcSpaWallStrength.h: interface for the ArxRleUiTdcSpaWallStrength class.
//

#ifndef ARXRLE_UITDC_SPA_WALL_STRENGTH_H
#define ARXRLE_UITDC_SPA_WALL_STRENGTH_H

#include "Resource.h"


// ArxRleUiTdcSpaWallStrength 对话框

class ArxRleUiTdcSpaWallStrength : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcSpaWallStrength)

public:
	ArxRleUiTdcSpaWallStrength();   // 标准构造函数
	virtual ~ArxRleUiTdcSpaWallStrength();

	// 对话框数据
	enum { IDD = ARXRLE_TDC_STRUCT_SPA_WALLSTRENGTH };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	afx_msg void OnClickBtnCalc();
	DECLARE_MESSAGE_MAP()

public:
	CComboBox	m_ComboKzdj;
	CComboBox	m_ComboFyw;
	CComboBox	m_ComboFyv;
	CComboBox	m_ComboFy;
	CComboBox	m_ComboFcuk;
	float	m_B;
	float	m_Bhcx;
	BOOL	m_bDi;
	BOOL	m_bDiBu;
	BOOL	m_bXjm;
	BOOL	m_bYiTa;
	BOOL	m_bZjm;
	float	m_Elx;
	float	m_Ely;
	float	m_H;
	float	m_Rmd;
	float	m_M;
	float	m_N;
	float	m_Ro;
	float	m_S;
	float	m_V;
	float	m_Zyb;
};

#endif //ARXRLE_UITDC_SPA_WALL_STRENGTH_H