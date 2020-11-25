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
#include "ArxRleUiTdcSpaBeamSection.h"


extern float GetGjKanglaFy(CString &cs);
extern float GetGjKanglaFyc(CString &cs);
// ArxRleUiTdcSpaBeamSection 对话框

IMPLEMENT_DYNAMIC(ArxRleUiTdcSpaBeamSection, CAcUiTabChildDialog)

ArxRleUiTdcSpaBeamSection::ArxRleUiTdcSpaBeamSection()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
{
	m_Alf = 45.0f;
	m_Asa = 0.0f;
	m_Asb = 0.0f;
	m_B = 250.0f;
	m_Bfd = 250.0f;
	m_Bfu = 250.0f;
	m_H = 600.0f;
	m_Hfd = 0.0f;
	m_Hfu = 0.0f;
	m_Rmd = 1.0f;
	m_Span = 6000.0f;
	m_S = 100.0f;
	m_T = 0.0f;
	m_bLa = FALSE;
	m_bEq = FALSE;
	m_bNiu = FALSE;
	m_bXjm = TRUE;
	m_bWan = TRUE;
	m_M = 300.0f;
	m_N = 100.0f;
	m_asu = 35.0f;
	m_asd = 35.0f;
	m_V = 200.0f;
	m_Pmin = 0.2f;
	m_bJLoad = FALSE;
	m_bDChen = FALSE;
	m_bJYun = FALSE;
	m_E0 = 0.0f;
}

ArxRleUiTdcSpaBeamSection::~ArxRleUiTdcSpaBeamSection()
{
}

void ArxRleUiTdcSpaBeamSection::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_SPA_BEAMSECTION_CB_JMLX, m_ComboJmLx);
	DDX_Control(pDX, ARXRLE_SPA_BEAMSECTION_CB_RO, m_ComboRo);
	DDX_Control(pDX, ARXRLE_SPA_BEAMSECTION_CB_FYC, m_ComboFyc);
	DDX_Control(pDX, ARXRLE_SPA_BEAMSECTION_CB_LLX, m_ComboLLx);
	DDX_Control(pDX, ARXRLE_SPA_BEAMSECTION_CB_KZDJ, m_ComboKzdj);
	DDX_Control(pDX, ARXRLE_SPA_BEAMSECTION_CB_FYV, m_ComboFyv);
	DDX_Control(pDX, ARXRLE_SPA_BEAMSECTION_CB_FY, m_ComboFy);
	DDX_Control(pDX, ARXRLE_SPA_BEAMSECTION_CB_FCUK, m_ComboFcuk);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_ALF, m_Alf);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_ASA, m_Asa);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_ASB, m_Asb);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_B, m_B);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_BFD, m_Bfd);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_BFU, m_Bfu);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_H, m_H);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_HFD, m_Hfd);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_HFU, m_Hfu);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_LEMD, m_Rmd);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_LO, m_Span);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_S, m_S);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_T, m_T);
	DDX_Check(pDX, ARXRLE_SPA_BEAMSECTION_CK_LA, m_bLa);
	DDX_Check(pDX, ARXRLE_SPA_BEAMSECTION_CK_DI, m_bEq);
	DDX_Check(pDX, ARXRLE_SPA_BEAMSECTION_CK_NIU, m_bNiu);
	DDX_Check(pDX, ARXRLE_SPA_BEAMSECTION_CK_XIE, m_bXjm);
	DDX_Check(pDX, ARXRLE_SPA_BEAMSECTION_CK_ZHENG, m_bWan);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_M, m_M);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_N, m_N);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_BHCS, m_asu);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_BHCX, m_asd);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_V, m_V);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_PMIN, m_Pmin);
	DDX_Check(pDX, ARXRLE_SPA_BEAMSECTION_CK_JZHLOAD, m_bJLoad);
	DDX_Check(pDX, ARXRLE_SPA_BEAMSECTION_CK_DUICHEN, m_bDChen);
	DDX_Check(pDX, ARXRLE_SPA_BEAMSECTION_CK_JUNYUN, m_bJYun);
	DDX_Text(pDX, ARXRLE_SPA_BEAMSECTION_ET_E0, m_E0);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcSpaBeamSection, CAcUiTabChildDialog)
	ON_BN_CLICKED(ARXRLE_SPA_BEAMSECTION_BN_CALC, OnClickBtnCalc)
	ON_BN_CLICKED(ARXRLE_SPA_BEAMSECTION_CK_LA, OnCheckLa)
	ON_BN_CLICKED(ARXRLE_SPA_BEAMSECTION_CK_ZHENG, OnCheckZheng)
	ON_BN_CLICKED(ARXRLE_SPA_BEAMSECTION_CK_XIE, OnCheckXie)
	ON_BN_CLICKED(ARXRLE_SPA_BEAMSECTION_CK_NIU, OnCheckNiu)
	ON_BN_CLICKED(ARXRLE_SPA_BEAMSECTION_CK_DI, OnCheckDi)
	ON_CBN_SELCHANGE(ARXRLE_SPA_BEAMSECTION_CB_JMLX, OnSelchangeComboJmlx)
	ON_BN_CLICKED(ARXRLE_SPA_BEAMSECTION_CK_JZHLOAD, OnCheckJzhload)
	ON_BN_CLICKED(ARXRLE_SPA_BEAMSECTION_CK_DUICHEN, OnCheckDuichen)
	ON_BN_CLICKED(ARXRLE_SPA_BEAMSECTION_CK_JUNYUN, OnCheckJunyun)
END_MESSAGE_MAP()


// ArxRleUiTdcSpaBeamSection 消息处理程序

BOOL ArxRleUiTdcSpaBeamSection::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作

	// TODO: 在此添加额外的初始化代码
	int nCount = m_ComboLLx.GetCount();
	if (nCount > 0)
		m_ComboLLx.SetCurSel(0);

	nCount = m_ComboRo.GetCount();
	if (nCount > 0)
		m_ComboRo.SetCurSel(1);


	nCount = m_ComboFy.GetCount();
	if (nCount > 0)
		m_ComboFy.SetCurSel(1);

	nCount = m_ComboFyv.GetCount();
	if (nCount > 0)
		m_ComboFyv.SetCurSel(0);

	nCount = m_ComboFyc.GetCount();
	if (nCount > 0)
		m_ComboFyc.SetCurSel(1);

	nCount = m_ComboFcuk.GetCount();
	if (nCount > 0)
		m_ComboFcuk.SetCurSel(2);

	nCount = m_ComboKzdj.GetCount();
	if (nCount > 0)
		m_ComboKzdj.SetCurSel(0);

	nCount = m_ComboJmLx.GetCount();
	if (nCount > 0)
		m_ComboJmLx.SetCurSel(0);

	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

extern float B, H, Bfu, Hfu, Bfd, Hfd, Asu, Asd, Span, Fy, Fyc, Fyv, M, N, V, Tt, e0;
extern BOOL bWan, bXjm, bEq, bNiu, bLa, bJLoad, bDuiCh, bJunY;
extern int kFcuk,Klxl, Kzdj,KJmLx;
extern float Rmd, Arf, S, Asa, Asb ,Ro, pmin;
extern CString csTringFy,csTringFyc,csTringFyv;

void ArxRleUiTdcSpaBeamSection::OnClickBtnCalc() 
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString rString;
	int iCurSel=m_ComboFy.GetCurSel();
	if(iCurSel > 0)
		m_ComboFy.GetLBText( iCurSel, rString );
	csTringFy=rString;

	iCurSel=m_ComboFyc.GetCurSel();
	if(iCurSel > 0)
		m_ComboFyc.GetLBText( iCurSel, rString );
	csTringFyc=rString;

	iCurSel=m_ComboFyv.GetCurSel();
	if(iCurSel > 0)
		m_ComboFyv.GetLBText( iCurSel, rString );
	csTringFyv=rString;

	iCurSel=m_ComboFcuk.GetCurSel();
	if(iCurSel > 0)
		m_ComboFcuk.GetLBText( iCurSel, rString );
	rString.Delete(0);
	kFcuk=_tstol(rString);

	iCurSel=m_ComboLLx.GetCurSel();
	Klxl=iCurSel;

	iCurSel=m_ComboKzdj.GetCurSel();
	Kzdj=iCurSel;

	iCurSel=m_ComboRo.GetCurSel();
	if(iCurSel==0) Ro=0.1;
	else if(iCurSel==1) Ro=1;
	else if(iCurSel==2) Ro=1.1;
	
	KJmLx=m_ComboJmLx.GetCurSel();

	B=m_B;
	H=m_H;
	Bfu=m_Bfu;
	Hfu=m_Hfu;
	Bfd=m_Bfd;
	Hfd=m_Hfd;
	Asu=m_asu;
	Asd=m_asd;
	Span=m_Span;

	e0=m_E0;

	Asa=m_Asa;
	Asb=m_Asb;

	pmin=m_Pmin;
	bWan=m_bWan;
	bXjm=m_bXjm;
	bEq=m_bEq;
	bNiu=m_bNiu;
	bLa=m_bLa;
	bJLoad=m_bJLoad;
	
	bDuiCh=m_bDChen;
	bJunY=m_bJYun;

	M=m_M;
	N=m_N;

	Rmd=m_Rmd;
	Arf=m_Alf;
	S=m_S;
	V=m_V;
	Tt=m_T;

//	typedef void (WINAPI * TESTDLL)(float &b,float &h,float &Bfu,float &Hfu,float &Bfd,float &Hfd,
//			float &asu,float &asd,float &Span,int &Fcuk,CString &csTringFy,CString &csTringFyc,
//			float &Asc,float &pmin0,BOOL &bWan,BOOL &bLa,BOOL &bNiu,BOOL &bXjm,BOOL &bEq,int &Kzdj,
//			int &Klxl,float &Ro,float &M,float &N,float &V,float &T);
//	HINSTANCE hmod;
//	hmod = ::LoadLibrary ("SpaBeamDesign.dll");
//	if(hmod==NULL)
//	{
//		AfxMessageBox("Load dll Fail");
//	}
//	TESTDLL lpproc;
//	lpproc = (TESTDLL)GetProcAddress (hmod,"Beam_Moment_WanJu");
//	if(lpproc!=(TESTDLL)NULL)
//		(*lpproc)(B,H,Bfu,Hfu,Bfd,Hfd,Asu,Asd,Span,kFcuk
//			  ,csTringFy,csTringFyc,Asa,pmin,bWan,bLa,bNiu,bXjm,bEq,Kzdj,Klxl,
//			  Ro,M,N,V,T);
//	
//	FreeLibrary(hmod);

	((ArxRleUiTdmSpa*)GetParent())->m_pPageOutResult->ShowBeamSectionText();
	((ArxRleUiTdmSpa*)GetParent())->m_tabCtrl.SetActiveTab(5);
}

void ArxRleUiTdcSpaBeamSection::OnCheckZheng() 
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pWnd0=(CButton*)GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_ZHENG);
	int iCheck=pWnd0->GetCheck();

	CWnd* pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_M);
	pWnd->EnableWindow(iCheck);
}

void ArxRleUiTdcSpaBeamSection::OnCheckXie() 
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pWnd0=(CButton*)GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_XIE);
	int iCheck=pWnd0->GetCheck();
	
	CWnd* pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_S);
	pWnd->EnableWindow(iCheck);

	pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_ALF);
	pWnd->EnableWindow(iCheck);

	pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_ASB);
	pWnd->EnableWindow(iCheck);

	pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_V);
	pWnd->EnableWindow(iCheck);
}

void ArxRleUiTdcSpaBeamSection::OnCheckLa() 
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(L"对不起，待做...");
	CButton* pWnd0=(CButton*)GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_LA);
	pWnd0->SetCheck(0);

/*	CButton* pWnd0=(CButton*)GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_LA);
	int iCheck=pWnd0->GetCheck();
	
	CWnd* pWnd=GetDlgItem(IDC_N);
	pWnd->EnableWindow(iCheck);

	pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_DUICHEN);
	pWnd->EnableWindow(iCheck);
	pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_JUNYUN);
	pWnd->EnableWindow(iCheck);
	pWnd=GetDlgItem(IDC_E0);
	pWnd->EnableWindow(iCheck);
*/
}

void ArxRleUiTdcSpaBeamSection::OnCheckNiu() 
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(L"对不起，待做...");
	CButton* pWnd0=(CButton*)GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_NIU);
	pWnd0->SetCheck(0);

/*
	CButton* pWnd0=(CButton*)GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_NIU);
	int iCheck=pWnd0->GetCheck();
	
	CWnd* pWnd=GetDlgItem(IDC_T);
	pWnd->EnableWindow(iCheck);	
*/
}

void ArxRleUiTdcSpaBeamSection::OnCheckDi() 
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pWnd0=(CButton*)GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_DI);
	int iCheck=pWnd0->GetCheck();
	
	CWnd* pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_CB_KZDJ);
	pWnd->EnableWindow(iCheck);	
}

void ArxRleUiTdcSpaBeamSection::OnSelchangeComboJmlx() 
{
	// TODO: 在此添加控件通知处理程序代码
	CComboBox* pWnd0=(CComboBox*)GetDlgItem(ARXRLE_SPA_BEAMSECTION_CB_JMLX);
	int iCheck=pWnd0->GetCurSel();
	CWnd* pWnd;
	if(iCheck==0)//矩形
	{
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_BFU);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_BFD);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_HFU);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_HFD);
		pWnd->EnableWindow(FALSE);
	}
	else if(iCheck==1)//倒T形
	{
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_BFU);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_BFD);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_HFU);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_HFD);
		pWnd->EnableWindow(TRUE);
	}
	else if(iCheck==2|| iCheck==3)//T形，倒L形
	{
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_BFU);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_BFD);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_HFU);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_HFD);
		pWnd->EnableWindow(FALSE);
	}
	else if(iCheck==4)//倒T形
	{
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_BFU);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_BFD);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_HFU);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_HFD);
		pWnd->EnableWindow(TRUE);
	}
}

void ArxRleUiTdcSpaBeamSection::OnCheckJzhload() 
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pWnd0=(CButton*)GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_JZHLOAD);
	int iCheck=pWnd0->GetCheck();
	
	CWnd* pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_ET_LEMD);
	pWnd->EnableWindow(iCheck);		
}

void ArxRleUiTdcSpaBeamSection::OnCheckDuichen() 
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pWnd0=(CButton*)GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_DUICHEN);
	int iCheck=pWnd0->GetCheck();
	
	CWnd* pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_JUNYUN);
	pWnd->EnableWindow(!iCheck);	
}

void ArxRleUiTdcSpaBeamSection::OnCheckJunyun() 
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pWnd0=(CButton*)GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_JUNYUN);
	int iCheck=pWnd0->GetCheck();
	
	CWnd* pWnd=GetDlgItem(ARXRLE_SPA_BEAMSECTION_CK_DUICHEN);
	pWnd->EnableWindow(!iCheck);	
}