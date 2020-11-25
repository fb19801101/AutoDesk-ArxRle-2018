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

#include "ArxRleUiPage.h"


// ArxRleUiPage 对话框

IMPLEMENT_DYNAMIC(ArxRleUiPage, CDialogEx)

ArxRleUiPage::ArxRleUiPage()
	: CDialogEx()
{

}

ArxRleUiPage::ArxRleUiPage(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialogEx(nIDTemplate, pParent)
{

}

ArxRleUiPage::ArxRleUiPage(LPCTSTR lpszTemplateName, CWnd *pParent /*= NULL*/)
	: CDialogEx(lpszTemplateName, pParent)
{
}

ArxRleUiPage::~ArxRleUiPage()
{
}

void ArxRleUiPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ArxRleUiPage, CDialogEx)
END_MESSAGE_MAP()


// ArxRleUiPage 消息处理程序


void ArxRleUiPage::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	CWnd* pParent = GetParent();
	while(pParent != NULL && !pParent->IsKindOf(RUNTIME_CLASS(CDialogEx)) && !pParent->IsKindOf(RUNTIME_CLASS(CDialog)))
		pParent = pParent->GetParent();
	if(pParent != NULL)
		pParent->PostMessage(WM_COMMAND, MAKEWPARAM(IDCANCEL, BN_CLICKED), 0);
}
