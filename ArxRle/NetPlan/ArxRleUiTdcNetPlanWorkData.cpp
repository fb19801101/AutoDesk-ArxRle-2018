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

#include "ArxRleUiTdcNetPlanWorkData.h"
#include "ArxRleUiTdmNetPlan.h"


// ArxRleUiTdcNetPlanWorkData 对话框

IMPLEMENT_DYNAMIC(ArxRleUiTdcNetPlanWorkData, CAcUiTabChildDialog)

	ArxRleUiTdcNetPlanWorkData::ArxRleUiTdcNetPlanWorkData()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
	, m_strXlsFilePath(ArxRleUiTdmNetPlan::m_itemNetPlanData.strXlsFilePath)
	, m_strXlsFileName(ArxRleUiTdmNetPlan::m_itemNetPlanData.strXlsFileName)
	, m_strXlsSheetName(ArxRleUiTdmNetPlan::m_itemNetPlanData.strXlsSheetName)
	, m_nWorkNameCol1(ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkNameCol1)
	, m_nWorkNameCol2(ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkNameCol2)
	, m_nNodeBeginCol(ArxRleUiTdmNetPlan::m_itemNetPlanData.nNodeBeginCol)
	, m_nNodeEndCol(ArxRleUiTdmNetPlan::m_itemNetPlanData.nNodeEndCol)
	, m_nTimeBeginCol(ArxRleUiTdmNetPlan::m_itemNetPlanData.nTimeBeginCol)
	, m_nTimeEndCol(ArxRleUiTdmNetPlan::m_itemNetPlanData.nTimeEndCol)
	, m_nWorkBeginRow(ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkBeginRow)
	, m_nWorkEndRow(ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkEndRow)
{
	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);
}

ArxRleUiTdcNetPlanWorkData::~ArxRleUiTdcNetPlanWorkData()
{
}

void ArxRleUiTdcNetPlanWorkData::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKDATA_EB_FILEPATH, m_strXlsFileName);
	DDX_CBString(pDX, ARXRLE_NETPLAN_WORKDATA_CB_SHEETNAME, m_strXlsSheetName);
	DDX_CBIndex(pDX, ARXRLE_NETPLAN_WORKDATA_CB_WORKNAME1, m_nWorkNameCol1);
	DDX_CBIndex(pDX, ARXRLE_NETPLAN_WORKDATA_CB_WORKNAME2, m_nWorkNameCol2);
	DDX_CBIndex(pDX, ARXRLE_NETPLAN_WORKDATA_CB_NODEBEGIN, m_nNodeBeginCol);
	DDX_CBIndex(pDX, ARXRLE_NETPLAN_WORKDATA_CB_NODEEND, m_nNodeEndCol);
	DDX_CBIndex(pDX, ARXRLE_NETPLAN_WORKDATA_CB_TIMEEND, m_nTimeEndCol);
	DDX_CBIndex(pDX, ARXRLE_NETPLAN_WORKDATA_CB_TIMEBEGIN, m_nTimeBeginCol);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKDATA_EB_WORKBEGIN, m_nWorkBeginRow);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKDATA_EB_WORKEND, m_nWorkEndRow);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKDATA_BN_FILEPATH, m_btnFilePath);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKDATA_CB_SHEETNAME, m_cxSheetName);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKDATA_CB_WORKNAME1, m_cxWorkNameCol1);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKDATA_CB_WORKNAME2, m_cxWorkNameCol2);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKDATA_CB_TIMEBEGIN, m_cxTimeBeginCol);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKDATA_CB_TIMEEND, m_cxTimeEndCol);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKDATA_CB_NODEBEGIN, m_cxNodeBeginCol);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKDATA_CB_NODEEND, m_cxNodeEndCol);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcNetPlanWorkData, CAcUiTabChildDialog)
	ON_BN_CLICKED(ARXRLE_NETPLAN_WORKDATA_BN_FILEPATH, OnBnClickedNetPlanPage2BnFilepath)
	ON_CBN_SELCHANGE(ARXRLE_NETPLAN_WORKDATA_CB_SHEETNAME, OnCbnSelchangeNetPlanPage2CxSheetname)
END_MESSAGE_MAP()


// ArxRleUiTdcNetPlanWorkData 消息处理程序

BOOL ArxRleUiTdcNetPlanWorkData::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(m_hIcon,TRUE);
	SetIcon(m_hIcon,FALSE);

	HICON hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_SELECT);
	m_btnFilePath.SetIcon(hIcon);

	char ch = 'A';
	CString str;
	for(int i=0; i<26; i++)
	{
		str.Format(_T("%c"),ch);
		m_cxWorkNameCol1.AddString(str);
		m_cxWorkNameCol2.AddString(str);
		m_cxTimeBeginCol.AddString(str);
		m_cxTimeEndCol.AddString(str);
		m_cxNodeBeginCol.AddString(str);
		m_cxNodeEndCol.AddString(str);
		ch++;
	}
	ch = 'A';
	for(int i=0; i<26; i++)
	{
		str.Format(_T("A%c"),ch);
		m_cxWorkNameCol1.AddString(str);
		m_cxWorkNameCol2.AddString(str);
		m_cxNodeBeginCol.AddString(str);
		m_cxNodeEndCol.AddString(str);
		m_cxTimeBeginCol.AddString(str);
		m_cxTimeEndCol.AddString(str);
		ch++;
	}
	ch = 'A';
	for(int i=0; i<26; i++)
	{
		str.Format(_T("B%c"),ch);
		m_cxWorkNameCol1.AddString(str);
		m_cxWorkNameCol2.AddString(str);
		m_cxNodeBeginCol.AddString(str);
		m_cxNodeEndCol.AddString(str);
		m_cxTimeBeginCol.AddString(str);
		m_cxTimeEndCol.AddString(str);
		ch++;
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ArxRleUiTdcNetPlanWorkData::OnBnClickedNetPlanPage2BnFilepath()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置文件过滤器
	TCHAR szFilter[] = _T("EXCEL文件|*.xls|所有文件|*.*||");
	// 构造打开文件对话框
	CFileDialog FileDlg(FALSE, _T("xls"), NULL, 0, szFilter, this);
	CString strFilePath,strFileName;

	// 设置默认路径
	FileDlg.m_ofn.lpstrInitialDir = _T("$(ProjectDir)\\");

	// 显示打开文件对话框
	if(IDOK == FileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里
		m_strXlsFilePath = FileDlg.GetPathName();
		m_strXlsFileName = FileDlg.GetFileName();
	}

	CXTPExcelUtil xls;
	xls.InitExcel();
	if(FileExist(m_strXlsFilePath))
	{
		xls.OpenExcel(m_strXlsFilePath);
		int nSheets = xls.GetSheetCount();
		m_cxSheetName.Clear();
		for(int i=1; i<=nSheets; i++)
		{
			CString str = xls.GetSheetName(i);
			m_cxSheetName.AddString(str);
			m_strXlsSheetName = str;
		}
		xls.Save();
		xls.CloseExcel();
	}
	xls.ReleaseExcel();

	UpdateData(FALSE);
}

void ArxRleUiTdcNetPlanWorkData::OnCbnSelchangeNetPlanPage2CxSheetname()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nWorkNameCol1 = 1;
	m_nWorkNameCol2 = 2;
	m_nNodeBeginCol = 3;
	m_nNodeEndCol = 4;
	m_nTimeBeginCol = 5;
	m_nTimeEndCol = 6;
	m_nWorkBeginRow = 1;
	m_cxSheetName.GetLBText(m_cxSheetName.GetCurSel(), m_strXlsSheetName);
	CXTPExcelUtil xls;
	xls.InitExcel();
	if(FileExist(m_strXlsFilePath))
	{
		xls.OpenExcel(m_strXlsFilePath);

		if(xls.LoadSheet(m_strXlsSheetName));
		{
			int nRows = xls.GetRowCount();
			m_nWorkEndRow = nRows;
		}
		xls.Save();
		xls.CloseExcel();
	}
	xls.ReleaseExcel();

	UpdateData(FALSE);
}