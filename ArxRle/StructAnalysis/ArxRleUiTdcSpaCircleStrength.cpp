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
#include "ArxRleUiTdcSpaCircleStrength.h"


// ArxRleUiTdcSpaCircleStrength 对话框

IMPLEMENT_DYNAMIC(ArxRleUiTdcSpaCircleStrength, CAcUiTabChildDialog)

ArxRleUiTdcSpaCircleStrength::ArxRleUiTdcSpaCircleStrength()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
{
	m_Bhcs = 35.0f;
	m_bDi = FALSE;
	m_bKjz = FALSE;
	m_bYiTa = TRUE;
	m_bZjm = TRUE;
	m_bXjm = TRUE;
	m_D = 600.0f;
	m_Rmd = 1.0f;
	m_Span = 4000.0f;
	m_M = 300.0f;
	m_N = 500.0f;
	m_S = 100.0f;
	m_Vx = 0.0f;
	m_Vy = 200.0f;
}

ArxRleUiTdcSpaCircleStrength::~ArxRleUiTdcSpaCircleStrength()
{
}

void ArxRleUiTdcSpaCircleStrength::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_SAP_CIRCLESTRENGTH_CB_KZDJ, m_ComboKzdj);
	DDX_Control(pDX, ARXRLE_SAP_CIRCLESTRENGTH_CB_FYV, m_ComboFyv);
	DDX_Control(pDX, ARXRLE_SAP_CIRCLESTRENGTH_CB_FY, m_ComboFy);
	DDX_Control(pDX, ARXRLE_SAP_CIRCLESTRENGTH_CB_FCUK, m_ComboFcuk);
	DDX_Text(pDX, ARXRLE_SAP_CIRCLESTRENGTH_ET_BHCS, m_Bhcs);
	DDX_Check(pDX, ARXRLE_SAP_CIRCLESTRENGTH_CK_DI, m_bDi);
	DDX_Check(pDX, ARXRLE_SAP_CIRCLESTRENGTH_CK_KJZ, m_bKjz);
	DDX_Check(pDX, ARXRLE_SAP_CIRCLESTRENGTH_CK_YITA, m_bYiTa);
	DDX_Check(pDX, ARXRLE_SAP_CIRCLESTRENGTH_CK_ZHENG, m_bZjm);
	DDX_Check(pDX, ARXRLE_SAP_CIRCLESTRENGTH_CK_XIE, m_bXjm);
	DDX_Text(pDX, ARXRLE_SAP_CIRCLESTRENGTH_ET_D, m_D);
	DDX_Text(pDX, ARXRLE_SAP_CIRCLESTRENGTH_ET_LEMD, m_Rmd);
	DDX_Text(pDX, ARXRLE_SAP_CIRCLESTRENGTH_ET_LO, m_Span);
	DDX_Text(pDX, ARXRLE_SAP_CIRCLESTRENGTH_ET_M, m_M);
	DDX_Text(pDX, ARXRLE_SAP_CIRCLESTRENGTH_ET_N, m_N);
	DDX_Text(pDX, ARXRLE_SAP_CIRCLESTRENGTH_ET_S, m_S);
	DDX_Text(pDX, ARXRLE_SAP_CIRCLESTRENGTH_ET_VX, m_Vx);
	DDX_Text(pDX, ARXRLE_SAP_CIRCLESTRENGTH_ET_VY, m_Vy);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcSpaCircleStrength, CAcUiTabChildDialog)
	ON_BN_CLICKED(ARXRLE_SAP_CIRCLESTRENGTH_BN_CALC, OnClickBtnCalc)
END_MESSAGE_MAP()


// ArxRleUiTdcSpaCircleStrength 消息处理程序

BOOL ArxRleUiTdcSpaCircleStrength::OnInitDialog()
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

	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

extern float B, Bhcs, Fcuk, Fy, Fyv;
extern int Kzjm, Kxjm, Kzdj, Klxl, Kzzh, Kcy;
extern float  Span;
extern float Rmd, S, N, Vy, Vx, Mx;

void ArxRleUiTdcSpaCircleStrength::OnClickBtnCalc() 
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString rString;
	int iCurSel=m_ComboFy.GetCurSel();
	if(iCurSel > 0)
		m_ComboFy.GetLBText( iCurSel, rString );
	Fy=_tstof(rString);

	iCurSel=m_ComboFyv.GetCurSel();
	if(iCurSel > 0)
		m_ComboFyv.GetLBText( iCurSel, rString );
	Fyv=_tstof(rString);

	iCurSel=m_ComboFcuk.GetCurSel();
	if(iCurSel > 0)
		m_ComboFcuk.GetLBText( iCurSel, rString );
	rString.Delete(0);
	Fcuk=_tstof(rString);

	iCurSel=m_ComboKzdj.GetCurSel();
	Kzdj=iCurSel;

	B=m_D;
	Bhcs=m_Bhcs;
	Span=m_Span;

	Kzjm=m_bZjm;
	Kxjm=m_bXjm;
	Kzzh=m_bDi;
	Klxl=m_bKjz;
	Kcy=m_bYiTa;

	Mx=m_M;
	N=m_N;

	Rmd=m_Rmd;
	S=m_S;
	Vy=m_Vy;
	Vx=m_Vx;

	((ArxRleUiTdmSpa*)GetParent())->m_pPageOutResult->ShowCircleStrengthText();
}