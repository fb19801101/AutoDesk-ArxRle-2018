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

#include "ArxRleUiTdcNetPlanWorkInput.h"
#include "ArxRleUiTdmNetPlan.h"
#include "ArxRleReportRecord.h"

enum
{
	COLUMN_IMPORTANCE,
	COLUMN_ICON,
	COLUMN_ATTACHMENT,
	COLUMN_FROM,
	COLUMN_SUBJECT,
	COLUMN_SENT,
	COLUMN_SIZE,
	COLUMN_CHECK,
	COLUMN_PRICE,
	COLUMN_CREATED,
	COLUMN_RECEIVED,
	COLUMN_CONVERSATION,
	COLUMN_CONTACTS,
	COLUMN_MESSAGE,
	COLUMN_CC,
	COLUMN_CATEGORIES,
	COLUMN_AUTOFORWARD,
	COLUMN_DO_NOT_AUTOARCH,
	COLUMN_DUE_BY,
};
const int COLUMN_MAIL_ICON   =  0;
const int COLUMN_CHECK_ICON  =  2;

// ArxRleUiTdcNetPlanWorkInput 对话框
IMPLEMENT_DYNAMIC(ArxRleUiTdcNetPlanWorkInput, CAcUiTabChildDialog)

ArxRleUiTdcNetPlanWorkInput::ArxRleUiTdcNetPlanWorkInput()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
{
}

ArxRleUiTdcNetPlanWorkInput::~ArxRleUiTdcNetPlanWorkInput()
{
	if(m_xtpReport != NULL) delete m_xtpReport;
}

void ArxRleUiTdcNetPlanWorkInput::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, ARXRLE_NETPLAN_WORKINPUT_REPORT, m_xtpReport);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcNetPlanWorkInput, CAcUiTabChildDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// ArxRleUiTdcNetPlanWorkInput 消息处理程序

BOOL ArxRleUiTdcNetPlanWorkInput::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作

	// TODO: 在此添加额外的初始化代码
	m_xtpReport->AllowEdit(TRUE);
	m_xtpReport->EditOnClick(FALSE);

	//
	//  Add sample columns
	//
	m_xtpReport->AddColumn(new CXTPReportColumn(COLUMN_ICON, _T(""), 18, FALSE, COLUMN_MAIL_ICON));
	m_xtpReport->AddColumn(new CXTPReportColumn(COLUMN_CHECK, _T(""), 18, FALSE, COLUMN_CHECK_ICON));
	CXTPReportColumn* pNewPMCol = m_xtpReport->AddColumn(new CXTPReportColumn(COLUMN_SUBJECT, _T("Subject"), 280));
	pNewPMCol->SetPlusMinus(TRUE);
	pNewPMCol->SetExpanded(TRUE);
	pNewPMCol->SetNextVisualBlock(2);
	m_xtpReport->AddColumn(new CXTPReportColumn(COLUMN_FROM, _T("From"), 180));
	m_xtpReport->AddColumn(new CXTPReportColumn(COLUMN_SENT, _T("Sent"), 150));
	m_xtpReport->AddColumn(new CXTPReportColumn(COLUMN_SIZE, _T("Size"), 50));
	m_xtpReport->AddColumn(new CXTPReportColumn(COLUMN_PRICE, _T("Price"), 80));

	//
	//  Add sample records in tree
	//

	COleDateTime odtSent(COleDateTime::GetCurrentTime());
	COleDateTime odtCreated(COleDateTime::GetCurrentTime());
	COleDateTime odtReceived(COleDateTime::GetCurrentTime());
	CString strMessage(" ");
	CString strEmpty(" ");

	m_xtpReport->AddRecord(new ArxRleReportRecord(ImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_xtpReport->AddRecord(new ArxRleReportRecord(ImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	ArxRleReportRecord *pParentRec1 = new ArxRleReportRecord(ImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_xtpReport->AddRecord(pParentRec1);
	m_xtpReport->AddRecord(new ArxRleReportRecord(ImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;

	m_xtpReport->AddRecord(new ArxRleReportRecord(ImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_xtpReport->AddRecord(new ArxRleReportRecord(ImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1 = new ArxRleReportRecord(ImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_xtpReport->AddRecord(pParentRec1);
	m_xtpReport->AddRecord(new ArxRleReportRecord(ImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;

	m_xtpReport->AddRecord(new ArxRleReportRecord(ImportanceNormal, FALSE, FALSE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 5,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage));   odtSent -= 0.8;
	m_xtpReport->AddRecord(new ArxRleReportRecord(ImportanceLow, FALSE, FALSE, _T("Clark Kent"), _T("RE: Hi Louis"), odtSent, 14, FALSE, 4.3,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 0.8;
	pParentRec1 = new ArxRleReportRecord(ImportanceNormal, TRUE, TRUE, _T("Bruce Wayne"), _T("RE:"), odtSent, 24, FALSE, 56,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage); odtSent -= 0.8;
	m_xtpReport->AddRecord(pParentRec1);
	m_xtpReport->AddRecord(new ArxRleReportRecord(ImportanceNormal, FALSE, TRUE, _T("postmaster@mail.codejock.com"), _T("Undeliverable Mail"), odtSent, 7, TRUE, 10,
		odtCreated, odtReceived, strEmpty, strEmpty, strMessage,
		strEmpty, strEmpty, strEmpty,
		strEmpty, strEmpty,
		strMessage)); odtSent -= 80;

	m_xtpReport->GetColumns()->Find(COLUMN_SUBJECT)->SetTreeColumn(TRUE);
	m_xtpReport->Populate();
	m_xtpReport->EnableDragDrop(_T("ReportGrid"), xtpReportAllowDrag | xtpReportAllowDrop);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

int ArxRleUiTdcNetPlanWorkInput::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAcUiTabChildDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rc;
	GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.bottom -= 5;
	m_xtpReport = new CXTPReportControl;
	m_xtpReport->Create(WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE,rc,this,ARXRLE_NETPLAN_WORKINPUT_REPORT);

	m_imgList.Create(ARXRLE_BMP_POKER, 16, 1, RGB(255,0,255));
	m_xtpReport->SetImageList(&m_imgList);

	return 0;
}