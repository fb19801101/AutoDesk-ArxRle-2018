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
#include "ArxRleUiTdcSpaColumnStrength.h"


// ArxRleUiTdcSpaColumnStrength 对话框

IMPLEMENT_DYNAMIC(ArxRleUiTdcSpaColumnStrength, CAcUiTabChildDialog)

ArxRleUiTdcSpaColumnStrength::ArxRleUiTdcSpaColumnStrength()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
{
	m_Alf = 0.0f;
	m_B = 250.0f;
	m_Bfd = 250.0f;
	m_Bfu = 250.0f;
	m_Bhcx = 35.0f;
	m_bDi = FALSE;
	m_bXie = TRUE;
	m_bYiTa = TRUE;
	m_Dfd = 0.0f;
	m_Dfu = 0.0f;
	m_Dimc = 0.0f;
	m_Dimx = 0.0f;
	m_Dimy = 0.0f;
	m_Elx = 4000.0f;
	m_Ely = 4000.0f;
	m_H = 600.0f;
	m_Hfd = 0.0f;
	m_Hfu = 0.0f;
	m_Lmd = 1.0f;
	m_Mx = 300.0f;
	m_My = 0.0f;
	m_N = 500.0f;
	m_bSigleOrDouble = 1;
	m_S = 100.0f;
	m_T = 0.0f;
	m_Vx = 0.0f;
	m_Vy = 200.0f;
}

ArxRleUiTdcSpaColumnStrength::~ArxRleUiTdcSpaColumnStrength()
{
}

void ArxRleUiTdcSpaColumnStrength::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_SAP_COLUMNSTRENGTH_CB_KZDJ, m_ComboKzdj);
	DDX_Control(pDX, ARXRLE_SAP_COLUMNSTRENGTH_CB_KLXL, m_ComboKlxl);
	DDX_Control(pDX, ARXRLE_SAP_COLUMNSTRENGTH_CB_FYV, m_ComboFyv);
	DDX_Control(pDX, ARXRLE_SAP_COLUMNSTRENGTH_CB_FY, m_ComboFy);
	DDX_Control(pDX, ARXRLE_SAP_COLUMNSTRENGTH_CB_FCUK, m_ComboFcuk);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_ALF, m_Alf);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_B, m_B);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_BFD, m_Bfd);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_BFU, m_Bfu);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_BHCX, m_Bhcx);
	DDX_Check(pDX, ARXRLE_SAP_COLUMNSTRENGTH_CK_DI, m_bDi);
	DDX_Check(pDX, ARXRLE_SAP_COLUMNSTRENGTH_CK_XIE, m_bXie);
	DDX_Check(pDX, ARXRLE_SAP_COLUMNSTRENGTH_CK_YITA, m_bYiTa);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_DFD, m_Dfd);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_DFU, m_Dfu);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_DIMC, m_Dimc);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_DIMX, m_Dimx);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_DIMY, m_Dimy);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_ELX, m_Elx);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_ELY, m_Ely);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_H, m_H);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_HFD, m_Hfd);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_HFU, m_Hfu);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_LEMD, m_Lmd);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_MX, m_Mx);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_MY, m_My);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_N, m_N);
	DDX_Radio(pDX, ARXRLE_SAP_COLUMNSTRENGTH_RO_SIGLE, m_bSigleOrDouble);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_S, m_S);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_T, m_T);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_VX, m_Vx);
	DDX_Text(pDX, ARXRLE_SAP_COLUMNSTRENGTH_ET_VY, m_Vy);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcSpaColumnStrength, CAcUiTabChildDialog)
	ON_BN_CLICKED(ARXRLE_SAP_COLUMNSTRENGTH_BN_CALC, OnClickBtnCalc)
END_MESSAGE_MAP()


// ArxRleUiTdcSpaColumnStrength 消息处理程序

BOOL ArxRleUiTdcSpaColumnStrength::OnInitDialog()
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
		m_ComboFyv.SetCurSel(0);

	nCount = m_ComboFcuk.GetCount();
	if (nCount > 0)
		m_ComboFcuk.SetCurSel(2);

	nCount = m_ComboKzdj.GetCount();
	if (nCount > 0)
		m_ComboKzdj.SetCurSel(5);

	nCount = m_ComboKlxl.GetCount();
	if (nCount > 0)
		m_ComboKlxl.SetCurSel(0);

	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

extern float B, H, Bfu, Hfu, Bfd, Hfd, Bhcx, Fcuk, Fy, Fyv;
extern int Kxjm, Kzdj, Klxl, Khzz, Kcy;
extern BOOL bSigleOrDouble, bXie;
extern float Dfd, Dfu, Elx, Ely, Dimx, Dimy, Dimc;
extern float Rmd, Arf, S, N, Vy, Vx, Tt, Mx, My;

void ArxRleUiTdcSpaColumnStrength::OnClickBtnCalc() 
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

	iCurSel=m_ComboFyv.GetCurSel();
	if(iCurSel > 0)
		m_ComboFyv.GetLBText( iCurSel, rString );
	Fyv=_tstof(rString);

	iCurSel=m_ComboKzdj.GetCurSel();
	Kzdj=iCurSel;

	iCurSel=m_ComboKlxl.GetCurSel();
	Klxl=iCurSel;

	bSigleOrDouble=m_bSigleOrDouble;
	Khzz=m_bDi;
	Kxjm=m_bXie;
	Kcy=m_bYiTa;

	B=m_B;
	H=m_H;
	Bfu=m_Bfu;
	Hfu=m_Hfu;
	Bfd=m_Bfd;
	Hfd=m_Hfd;
	Dfd=m_Dfd;
	Dfd=m_Dfd;
	Bhcx=m_Bhcx;

	Elx=m_Elx;
	Ely=m_Ely;

	Dimx=m_Dimx;
	Dimy=m_Dimy;
	Dimc=m_Dimc;
	S=m_S;

	N=m_N;
	Mx=m_Mx;
	My=m_My;
	Vy=m_Vy;
	Vx=m_Vx;
	Tt=m_T;

	Rmd=m_Lmd;
	Arf=m_Alf;

	((ArxRleUiTdmSpa*)GetParent())->m_pPageOutResult->ShowColumnStrengthText();
}