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


// ArxRleUiTdmSpa 对话框

IMPLEMENT_DYNAMIC(ArxRleUiTdmSpa, CAcUiTabMainDialog)

ArxRleUiTdmSpa::ArxRleUiTdmSpa(CWnd* pParent /*=NULL*/)
	:  CAcUiTabMainDialog(ArxRleUiTdmSpa::IDD, pParent, ArxRleApp::m_hInstance)
{
	m_pPageBeamCracks = new ArxRleUiTdcSpaBeamCracks;
	m_pPageBeamSection = new ArxRleUiTdcSpaBeamSection;
	m_pPageCircleStrength = new ArxRleUiTdcSpaCircleStrength;
	m_pPageColumnStrength = new ArxRleUiTdcSpaColumnStrength;
	m_pPageWallStrength = new ArxRleUiTdcSpaWallStrength;
	m_pPageOutResult = new ArxRleUiTdcSpaOutResult;


	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);
}

ArxRleUiTdmSpa::~ArxRleUiTdmSpa()
{
	if(m_pPageBeamCracks != NULL) delete m_pPageBeamCracks;
	if(m_pPageBeamSection != NULL) delete m_pPageBeamSection;
	if(m_pPageCircleStrength != NULL) delete m_pPageCircleStrength;
	if(m_pPageColumnStrength != NULL) delete m_pPageColumnStrength;
	if(m_pPageWallStrength != NULL) delete m_pPageWallStrength;
	if(m_pPageOutResult != NULL) delete m_pPageOutResult;
}

void ArxRleUiTdmSpa::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabMainDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_SPA_TAB, m_tabCtrl);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdmSpa, CAcUiTabMainDialog)
	ON_BN_CLICKED(IDOK, &ArxRleUiTdmSpa::OnBnClickedOk)
END_MESSAGE_MAP()


// ArxRleUiTdmSpa 消息处理程序


BOOL ArxRleUiTdmSpa::OnInitDialog()
{
	CAcUiTabMainDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("梁正常使用计算"), ArxRleUiTdcSpaBeamCracks::IDD,     m_pPageBeamCracks);
	AddTab(1, _T("梁承载力计算"), ArxRleUiTdcSpaBeamSection::IDD, m_pPageBeamSection);
	AddTab(2, _T("圆柱承载力计算"), ArxRleUiTdcSpaCircleStrength::IDD,  m_pPageCircleStrength);
	AddTab(3, _T("柱承载力计算"), ArxRleUiTdcSpaColumnStrength::IDD,  m_pPageColumnStrength);
	AddTab(4, _T("剪力墙承载力计算"), ArxRleUiTdcSpaWallStrength::IDD,  m_pPageWallStrength);
	AddTab(5, _T("计算书"), ArxRleUiTdcSpaOutResult::IDD,  m_pPageOutResult);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ArxRleUiTdmSpa::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CAcUiTabMainDialog::OnOK();
}