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

#include "ArxRleUiTdcNetPlanParam.h"
#include "ArxRleUiTdmNetPlan.h"


// ArxRleUiTdcNetPlanParam 对话框

IMPLEMENT_DYNAMIC(ArxRleUiTdcNetPlanParam, CAcUiTabChildDialog)

	ArxRleUiTdcNetPlanParam::ArxRleUiTdcNetPlanParam()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
	, m_strProject(ArxRleUiTdmNetPlan::m_itemNetPlanData.strProject)
	, m_fBeginStat(ArxRleUiTdmNetPlan::m_itemNetPlanData.fBeginStat)
	, m_fEndStat(ArxRleUiTdmNetPlan::m_itemNetPlanData.fEndStat)
	, m_fStatLen(ArxRleUiTdmNetPlan::m_itemNetPlanData.fStatLen)
	, m_strStatGap(ToString(ArxRleUiTdmNetPlan::m_itemNetPlanData.fStatGap,1))
	, m_tBeginDay(ArxRleUiTdmNetPlan::m_itemNetPlanData.tBeginDay)
	, m_tEndDay(ArxRleUiTdmNetPlan::m_itemNetPlanData.tEndDay)
	, m_nPlaneTime(ArxRleUiTdmNetPlan::m_itemNetPlanData.nPlanTime)
	, m_strDayGap(ToString(ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap,0))
	, m_strPaperSize(ArxRleUiTdmNetPlan::m_itemNetPlanData.strPaperSize)
	, m_bDayLine(ArxRleUiTdmNetPlan::m_itemNetPlanData.bDayLine)
	, m_bWeekLine(ArxRleUiTdmNetPlan::m_itemNetPlanData.bWeekLine)
	, m_bMonthLine(ArxRleUiTdmNetPlan::m_itemNetPlanData.bMonthLine)
	, m_bYearLine(ArxRleUiTdmNetPlan::m_itemNetPlanData.bYearLine)
{
	m_nPlaneTime = (m_tEndDay-m_tBeginDay).GetDays();
	ArxRleUiTdmNetPlan::m_itemNetPlanData.nPlanTime = m_nPlaneTime;
}

ArxRleUiTdcNetPlanParam::~ArxRleUiTdcNetPlanParam()
{
}

void ArxRleUiTdcNetPlanParam::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Text(pDX, ARXRLE_NETPLAN_PARAM_EB_PROJECT, m_strProject);
	DDX_Text(pDX, ARXRLE_NETPLAN_PARAM_EB_BEGINSTAT, m_fBeginStat);
	DDX_Text(pDX, ARXRLE_NETPLAN_PARAM_EB_ENDSTAT, m_fEndStat);
	DDX_Text(pDX, ARXRLE_NETPLAN_PARAM_EB_STATLEN, m_fStatLen);
	DDX_CBString(pDX, ARXRLE_NETPLAN_PARAM_CB_STATGAP, m_strStatGap);
	DDX_DateTimeCtrl(pDX, ARXRLE_NETPLAN_PARAM_DT_BGGINDATE, m_tBeginDay);
	DDX_DateTimeCtrl(pDX, ARXRLE_NETPLAN_PARAM_DT_ENDDATE, m_tEndDay);
	DDX_Text(pDX, ARXRLE_NETPLAN_PARAM_EB_PLANETIME, m_nPlaneTime);
	DDX_CBString(pDX, ARXRLE_NETPLAN_PARAM_CB_PAPERSIZE, m_strPaperSize);
	DDX_CBString(pDX, ARXRLE_NETPLAN_PARAM_CB_DAYGAP, m_strDayGap);
	DDX_Check(pDX, ARXRLE_NETPLAN_PARAM_CK_DAYLINE, m_bDayLine);
	DDX_Check(pDX, ARXRLE_NETPLAN_PARAM_CK_WEEKLINE, m_bWeekLine);
	DDX_Check(pDX, ARXRLE_NETPLAN_PARAM_CK_MONTHLINE, m_bMonthLine);
	DDX_Check(pDX, ARXRLE_NETPLAN_PARAM_CK_YEARLINE, m_bYearLine);
	DDX_Control(pDX, ARXRLE_NETPLAN_PARAM_DT_BGGINDATE, m_dtBeginDay);
	DDX_Control(pDX, ARXRLE_NETPLAN_PARAM_DT_ENDDATE, m_dtEndDay);
	DDX_Control(pDX, ARXRLE_NETPLAN_PARAM_CB_PAPERSIZE, m_cbPaperSize);
	DDX_Control(pDX, ARXRLE_NETPLAN_PARAM_CB_DAYGAP, m_cbDayGap);
	DDX_Control(pDX, ARXRLE_NETPLAN_PARAM_CB_STATGAP, m_cbStatGap);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcNetPlanParam, CAcUiTabChildDialog)
	ON_EN_CHANGE(ARXRLE_NETPLAN_PARAM_EB_PLANETIME, &ArxRleUiTdcNetPlanParam::OnEnChangeNetplanParamEbPlanetime)
	ON_NOTIFY(DTN_DATETIMECHANGE, ARXRLE_NETPLAN_PARAM_DT_ENDDATE, &ArxRleUiTdcNetPlanParam::OnDtnDatetimechangeNetplanParamDtEnddate)
	ON_NOTIFY(DTN_DATETIMECHANGE, ARXRLE_NETPLAN_PARAM_DT_BGGINDATE, &ArxRleUiTdcNetPlanParam::OnDtnDatetimechangeNetplanParamDtBggindate)
END_MESSAGE_MAP()


// ArxRleUiTdcNetPlanParam 消息处理程序


BOOL ArxRleUiTdcNetPlanParam::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作

	// TODO: 在此添加额外的初始化代码
	m_dtBeginDay.SetMonthCalStyle( MCS_NOTODAY );
	m_dtBeginDay.SetFormat(_T("yyyy-MM-dd"));
	m_dtEndDay.SetMonthCalStyle( MCS_NOTODAY );
	m_dtEndDay.SetFormat(_T("yyyy-MM-dd"));

	m_cbPaperSize.AddString(_T("A0_1188.00_x_840.00_mm"));
	m_cbPaperSize.AddString(_T("A1_840.00_x_594.00_mm"));
	m_cbPaperSize.AddString(_T("A2_594.00_x_420.00_mm"));
	m_cbPaperSize.AddString(_T("A3_420.00_x_297.00_mm"));
	m_cbPaperSize.AddString(_T("A4_297.00_x_210.00_mm"));
	m_cbPaperSize.AddString(_T("自定义..."));

	m_cbDayGap.AddString(_T("1"));
	m_cbDayGap.AddString(_T("2"));
	m_cbDayGap.AddString(_T("5"));
	m_cbDayGap.AddString(_T("7"));
	m_cbDayGap.AddString(_T("10"));
	m_cbDayGap.AddString(_T("自定义..."));

	m_cbStatGap.AddString(_T("20"));
	m_cbStatGap.AddString(_T("50"));
	m_cbStatGap.AddString(_T("100"));
	m_cbStatGap.AddString(_T("200"));
	m_cbStatGap.AddString(_T("500"));
	m_cbStatGap.AddString(_T("1000"));
	m_cbStatGap.AddString(_T("自定义..."));

	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ArxRleUiTdcNetPlanParam::OnEnChangeNetplanParamEbPlanetime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CAcUiTabChildDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CTimeSpan ts(m_nPlaneTime,0,0,0);
	m_tEndDay = m_tBeginDay+ts;
	UpdateData(FALSE);
}

void ArxRleUiTdcNetPlanParam::OnDtnDatetimechangeNetplanParamDtEnddate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nPlaneTime = (m_tEndDay-m_tBeginDay).GetDays();
	UpdateData(FALSE);
	*pResult = 0;
}

void ArxRleUiTdcNetPlanParam::OnDtnDatetimechangeNetplanParamDtBggindate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_nPlaneTime = (m_tEndDay-m_tBeginDay).GetDays();
	UpdateData(FALSE);
	*pResult = 0;
}
