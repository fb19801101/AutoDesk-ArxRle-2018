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
#include "ArxRleUiTdcSpaBeamCracks.h"

;
// ArxRleUiTdcSpaBeamCracks 对话框

IMPLEMENT_DYNAMIC(ArxRleUiTdcSpaBeamCracks, CAcUiTabChildDialog)

ArxRleUiTdcSpaBeamCracks::ArxRleUiTdcSpaBeamCracks()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
{
	m_Asa = 1200.0f;
	m_Asb = 0.0f;
	m_B = 250.0f;
	m_Bfd = 250.0f;
	m_Bfu = 250.0f;
	m_Bhcs = 35.0f;
	m_Bhcx = 35.0f;
	m_C = 0.0f;
	m_bNaoDu = TRUE;
	m_bWidth = TRUE;
	m_Deq = 20.0f;
	m_H = 600.0f;
	m_Hfd = 0.0f;
	m_Hfu = 0.0f;
	m_Lo = 6000.0f;
	m_Mk = 300.0f;
	m_Mq = 0.0f;
	m_Nk = 0.0f;
}

ArxRleUiTdcSpaBeamCracks::~ArxRleUiTdcSpaBeamCracks()
{
}

void ArxRleUiTdcSpaBeamCracks::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_SAP_BEAMCRACKS_CB_GJXZ, m_ComboGjXz);
	DDX_Control(pDX, ARXRLE_SAP_BEAMCRACKS_CB_FY, m_ComboFy);
	DDX_Control(pDX, ARXRLE_SAP_BEAMCRACKS_CB_FCUK, m_ComboFcuk);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_ASA, m_Asa);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_ASB, m_Asb);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_B, m_B);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_BFD, m_Bfd);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_BFU, m_Bfu);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_BHCS, m_Bhcs);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_BHCX, m_Bhcx);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_C, m_C);
	DDX_Check(pDX, ARXRLE_SAP_BEAMCRACKS_CK_NAODU, m_bNaoDu);
	DDX_Check(pDX, ARXRLE_SAP_BEAMCRACKS_CK_WIDTH, m_bWidth);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_DEQ, m_Deq);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_H, m_H);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_HFD, m_Hfd);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_HFU, m_Hfu);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_LO, m_Lo);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_MK, m_Mk);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_MQ, m_Mq);
	DDX_Text(pDX, ARXRLE_SAP_BEAMCRACKS_ET_NK, m_Nk);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcSpaBeamCracks, CAcUiTabChildDialog)
	ON_BN_CLICKED(ARXRLE_SAP_BEAMCRACKS_BN_CALC, OnClickBtnCalc)
END_MESSAGE_MAP()


// ArxRleUiTdcSpaBeamCracks 消息处理程序

BOOL ArxRleUiTdcSpaBeamCracks::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作

	// TODO: 在此添加额外的初始化代码
	int nCount = m_ComboFcuk.GetCount();
	if (nCount > 0)
		m_ComboFcuk.SetCurSel(2);

	nCount = m_ComboFy.GetCount();
	if (nCount > 0)
		m_ComboFy.SetCurSel(1);

	nCount = m_ComboGjXz.GetCount();
	if (nCount > 0)
		m_ComboGjXz.SetCurSel(0);

	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

extern float B, H, Bfu, Hfu, Bfd, Hfd, Bhcs, Bhcx, Span, Fcuk, Fy, Asa, Asb;
extern float GjXz,Cover,Deq,Nk,Mk,Mq;
extern BOOL bNaoDu,bWidth;

void ArxRleUiTdcSpaBeamCracks::OnClickBtnCalc() 
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString rString;
	int iCurSel=m_ComboFy.GetCurSel();
	if(iCurSel > 0)
		m_ComboFy.GetLBText( iCurSel, rString );
	Fy=_tstof(rString);

	iCurSel=m_ComboFcuk.GetCurSel();
	if(iCurSel > 0)
		m_ComboFcuk.GetLBText( iCurSel, rString );
	rString.Delete(0);
	Fcuk=_tstof(rString);

	iCurSel=m_ComboGjXz.GetCurSel();
	if(iCurSel > 0)
		m_ComboGjXz.GetLBText( iCurSel, rString );
	GjXz=_tstof(rString);
	
	B=m_B;
	H=m_H;
	Bfu=m_Bfu;
	Hfu=m_Hfu;
	Bfd=m_Bfd;
	Hfd=m_Hfd;
	Bhcs=m_Bhcs;
	Bhcx=m_Bhcx;
	Span=m_Lo;
	Asa=m_Asa;
	Asb=m_Asb;
	Cover=m_C;
	Deq=m_Deq;

	Mk=m_Mk;
	Nk=m_Nk;
	Mq=m_Mq;
	
	bNaoDu=m_bNaoDu;
	bWidth=m_bWidth;

	((ArxRleUiTdmSpa*)GetParent())->m_pPageOutResult->ShowBeamCracksText();
}
