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

#include "ArxRleUiTdmNetPlan.h"


// ArxRleUiTdmNetPlan 对话框

ArxRleNetPlanDataItem ArxRleUiTdmNetPlan::m_itemNetPlanData(_T("京沈客专TJ-2标无砟轨道施工计划网络图"),_T("A2_597.00_x_420.00_mm"),
													283900,312400,CTime(2017,2,16,0,0,0),CTime(2017,7,31,0,0,0));
IMPLEMENT_DYNAMIC(ArxRleUiTdmNetPlan, CAcUiTabMainDialog)

ArxRleUiTdmNetPlan::ArxRleUiTdmNetPlan(CWnd* pParent /*=NULL*/)
	:  CAcUiTabMainDialog(ArxRleUiTdmNetPlan::IDD, pParent, ArxRleApp::m_hInstance)
{
	m_pPageParam = new ArxRleUiTdcNetPlanParam;
	m_pPageWorkData = new ArxRleUiTdcNetPlanWorkData;
	m_pPageWorkStyle = new ArxRleUiTdcNetPlanWorkStyle;
	m_pPageWorkInput = new ArxRleUiTdcNetPlanWorkInput;


	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);
}

ArxRleUiTdmNetPlan::~ArxRleUiTdmNetPlan()
{
	if(m_pPageParam != NULL) delete m_pPageParam;
	if(m_pPageWorkData != NULL) delete m_pPageWorkData;
	if(m_pPageWorkStyle != NULL) delete m_pPageWorkStyle;
	if(m_pPageWorkInput != NULL) delete m_pPageWorkInput;
}

void ArxRleUiTdmNetPlan::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabMainDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_NETPLAN_TAB, m_tabCtrl);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdmNetPlan, CAcUiTabMainDialog)
	ON_BN_CLICKED(IDOK, &ArxRleUiTdmNetPlan::OnBnClickedOk)
END_MESSAGE_MAP()


// ArxRleUiTdmNetPlan 消息处理程序


BOOL ArxRleUiTdmNetPlan::OnInitDialog()
{
	CAcUiTabMainDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("基本设置"), ArxRleUiTdcNetPlanParam::IDD,     m_pPageParam);
	AddTab(1, _T("工序样式"), ArxRleUiTdcNetPlanWorkStyle::IDD, m_pPageWorkStyle);
	AddTab(2, _T("工序数据"), ArxRleUiTdcNetPlanWorkData::IDD,  m_pPageWorkData);
	AddTab(3, _T("工序数据"), ArxRleUiTdcNetPlanWorkInput::IDD,  m_pPageWorkInput);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ArxRleUiTdmNetPlan::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pPageParam->UpdateData(TRUE);
	m_pPageWorkData->UpdateData(TRUE);

	m_itemNetPlanData.strProject = m_pPageParam->m_strProject;
	m_itemNetPlanData.fBeginStat = m_pPageParam->m_fBeginStat;
	m_itemNetPlanData.fEndStat = m_pPageParam->m_fEndStat;
	m_itemNetPlanData.fStatLen = m_pPageParam->m_fStatLen;
	m_itemNetPlanData.fStatGap = _tstof(m_pPageParam->m_strStatGap);
	m_itemNetPlanData.tBeginDay = m_pPageParam->m_tBeginDay;
	m_itemNetPlanData.tEndDay = m_pPageParam->m_tEndDay;
	m_itemNetPlanData.nPlanTime = m_pPageParam->m_nPlaneTime;
	m_itemNetPlanData.strPaperSize = m_pPageParam->m_strPaperSize;
	CStringArray strArray;
	ParseSubStrByDelimiter(m_itemNetPlanData.strPaperSize,strArray,'_');
	m_itemNetPlanData.nPaperWidth = _tstoi(strArray[1]);
	m_itemNetPlanData.nPaperHeight = _tstoi(strArray[3]);
	m_itemNetPlanData.nDayGap = _tstoi(m_pPageParam->m_strDayGap);
	m_itemNetPlanData.bDayLine = m_pPageParam->m_bDayLine;
	m_itemNetPlanData.bWeekLine = m_pPageParam->m_bWeekLine;
	m_itemNetPlanData.bMonthLine = m_pPageParam->m_bMonthLine;
	m_itemNetPlanData.bYearLine = m_pPageParam->m_bYearLine;
	m_itemNetPlanData.strXlsFilePath = m_pPageWorkData->m_strXlsFilePath;
	m_itemNetPlanData.strXlsFileName = m_pPageWorkData->m_strXlsFileName;
	m_itemNetPlanData.strXlsSheetName  = m_pPageWorkData->m_strXlsSheetName;
	m_itemNetPlanData.nWorkNameCol1 = m_pPageWorkData->m_nWorkNameCol1+1;
	m_itemNetPlanData.nWorkNameCol2 = m_pPageWorkData->m_nWorkNameCol2+1;
	m_itemNetPlanData.nNodeBeginCol = m_pPageWorkData->m_nNodeBeginCol+1;
	m_itemNetPlanData.nNodeEndCol = m_pPageWorkData->m_nNodeEndCol+1;
	m_itemNetPlanData.nTimeBeginCol = m_pPageWorkData->m_nTimeBeginCol+1;
	m_itemNetPlanData.nTimeEndCol = m_pPageWorkData->m_nTimeEndCol+1;
	m_itemNetPlanData.nWorkBeginRow = m_pPageWorkData->m_nWorkBeginRow;
	m_itemNetPlanData.nWorkEndRow = m_pPageWorkData->m_nWorkEndRow;
	m_itemNetPlanData.objIdList.removeAll();
	m_itemNetPlanData.objIdList = m_pPageWorkStyle->m_objIdList;

	CAcUiTabMainDialog::OnOK();
}