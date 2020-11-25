/
	//////////////////////////////////////////////////////////////////////////////
	//
	//  Copyright 2015 Autodesk, Inc.  All rights reserved.
	//
	//  Use of this software is subject to the terms of the Autodesk license 
	//  agreement provided at the time of installation or download, or which 
	//  otherwise accompanies this software in either electronic or hard copy form.   
	//
	//////////////////////////////////////////////////////////////////////////////
	//
#include "StdAfx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleUiTdmSpa.h"
#include "ArxRleUiTdcSpaWallStrength.h"


// ArxRleUiTdcSpaWallStrength 对话框

IMPLEMENT_DYNAMIC(ArxRleUiTdcSpaWallStrength, CAcUiTabChildDialog)

ArxRleUiTdcSpaWallStrength::ArxRleUiTdcSpaWallStrength()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
{
	m_B = 250.0f;
	m_Bhcx = 35.0f;
	m_bDi = FALSE;
	m_bDiBu = FALSE;
	m_bXjm = TRUE;
	m_bYiTa = TRUE;
	m_bZjm = TRUE;
	m_Elx = 4000.0f;
	m_Ely = 4000.0f;
	m_H = 600.0f;
	m_Rmd = 1.0f;
	m_M = 300.0f;
	m_N = 0.0f;
	m_Ro = 0.2f;
	m_S = 100.0f;
	m_V = 200.0f;
	m_Zyb = 0.0f;
}

ArxRleUiTdcSpaWallStrength::~ArxRleUiTdcSpaWallStrength()
{
}

void ArxRleUiTdcSpaWallStrength::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_SPA_WALLSTRENGTH_CB_KZDJ, m_ComboKzdj);
	DDX_Control(pDX, ARXRLE_SPA_WALLSTRENGTH_CB_FYW, m_ComboFyw);
	DDX_Control(pDX, ARXRLE_SPA_WALLSTRENGTH_CB_FYV, m_ComboFyv);
	DDX_Control(pDX, ARXRLE_SPA_WALLSTRENGTH_CB_FY, m_ComboFy);
	DDX_Control(pDX, ARXRLE_SPA_WALLSTRENGTH_CB_FCUK, m_ComboFcuk);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_B, m_B);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_BHCX, m_Bhcx);
	DDX_Check(pDX, ARXRLE_SPA_WALLSTRENGTH_CK_DI, m_bDi);
	DDX_Check(pDX, ARXRLE_SPA_WALLSTRENGTH_CK_DIBU, m_bDiBu);
	DDX_Check(pDX, ARXRLE_SPA_WALLSTRENGTH_CK_XJM, m_bXjm);
	DDX_Check(pDX, ARXRLE_SPA_WALLSTRENGTH_CK_YITA, m_bYiTa);
	DDX_Check(pDX, ARXRLE_SPA_WALLSTRENGTH_CK_ZJM, m_bZjm);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_ELX, m_Elx);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_ELY, m_Ely);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_H, m_H);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_LEMD, m_Rmd);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_M, m_M);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_N, m_N);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_ROY, m_Ro);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_S, m_S);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_V, m_V);
	DDX_Text(pDX, ARXRLE_SPA_WALLSTRENGTH_ET_ZYB, m_Zyb);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcSpaWallStrength, CAcUiTabChildDialog)
	ON_BN_CLICKED(ARXRLE_SPA_WALLSTRENGTH_BN_CALC, OnClickBtnCalc)
END_MESSAGE_MAP()


// ArxRleUiTdcSpaWallStrength 消息处理程序

BOOL ArxRleUiTdcSpaWallStrength::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作

	// TODO: 在此添加额外的初始化代码
	int nCount = m_ComboFy.GetCount();
	if (nCount > 0)
		m_ComboFy.SetCurSel(1);

	nCount = m_ComboFyv.GetCount();
	if (nCount > 0)
		m_ComboFyv.SetCurSel(1);

	nCount = m_ComboFyw.GetCount();
	if (nCount > 0)
		m_ComboFyw.SetCurSel(0);

	nCount = m_ComboFcuk.GetCount();
	if (nCount > 0)
		m_ComboFcuk.SetCurSel(2);

	nCount = m_ComboKzdj.GetCount();
	if (nCount > 0)
		m_ComboKzdj.SetCurSel(5);

	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

extern float B, H, Bfu, Hfu, Bfd, Hfd, Bhcx, Fcuk, Fy, Fyv, Fyw;
extern int Kzjm, Kxjm, Kzdj, Klxl, Khzz, Kcy;
extern float Dfd, Dfu, Elx, Ely, Dimx, Dimy, Dimc;
extern float Wzyb, Ro, Rmd, Arf, S, N, Vy, Vx, Mx, My;

void ArxRleUiTdcSpaWallStrength::OnClickBtnCalc() 
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString rString;

	int iCurSel=m_ComboFcuk.GetCurSel();
	if(iCurSel > 0)
		m_ComboFcuk.GetLBText( iCurSel, rString );
	rString.Delete(0);
	Fcuk=_tstof(rString);

	iCurSel=m_ComboFy.GetCurSel();
	if(iCurSel > 0)
		m_ComboFy.GetLBText( iCurSel, rString );
	Fy=_tstof(rString);

	iCurSel=m_ComboFyw.GetCurSel();
	if(iCurSel > 0)
		m_ComboFyw.GetLBText( iCurSel, rString );
	Fyv=_tstof(rString);

	iCurSel=m_ComboFyv.GetCurSel();
	if(iCurSel > 0)
		m_ComboFyv.GetLBText( iCurSel, rString );
	Fyw=_tstof(rString);

	iCurSel=m_ComboKzdj.GetCurSel();
	Kzdj=iCurSel;


	Kzjm=m_bZjm;
	Kxjm=m_bXjm;
	Khzz=m_bDi;
	Kcy=m_bYiTa;	
	Klxl=m_bDiBu;

	B=m_B;
	H=m_H;
	Bhcx=m_Bhcx;

	Elx=m_Elx;
	Ely=m_Ely;

	Wzyb=m_Zyb;
	S=m_S;

	Ro=m_Ro;
	N=m_N;
	Vx=m_V;
	Mx=m_M;

	Rmd=m_Rmd;

	((ArxRleUiTdmSpa*)GetParent())->m_pPageOutResult->ShowWallStrengthText();
}
