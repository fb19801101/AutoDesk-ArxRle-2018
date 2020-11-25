//
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
#include "Resource.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleMsgHandler.h"


IMPLEMENT_DYNAMIC (ArxRleMsgHandler, CWnd)

BEGIN_MESSAGE_MAP(ArxRleMsgHandler, CWnd)
	//{{AFX_MSG_MAP(ArxRleMsgHandler)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(ARXRLE_APP_DRAW, ARXRLE_APP_ABOUT, OnToolBarCommands)
	ON_UPDATE_COMMAND_UI_RANGE(ARXRLE_APP_DRAW, ARXRLE_APP_ABOUT, OnUpdateToolBarCommands)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


ArxRleMsgHandler::ArxRleMsgHandler() {
}

ArxRleMsgHandler::~ArxRleMsgHandler() {
}
 

int ArxRleMsgHandler::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// 创建工具栏
	m_pToolbar = ArxRleToolBar::CreateToolBar(ARXRLE_BAR_APP, this, _T("自定义工具条"));

	return 0;
}

void ArxRleMsgHandler::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// 销毁工具栏
	delete m_pToolbar;
	acedGetAcadFrame()->RecalcLayout();
}

void ArxRleMsgHandler::OnToolBarCommands(UINT nID) 
{
	LPCTSTR cmdStr = NULL;
	CString str;
	switch (nID)
	{
	case ARXRLE_APP_DRAW:
		cmdStr = _T("ArxRle_App_Draw");
		msgInf(_T("ArxRle_App_Draw"));
		break;
	case ARXRLE_APP_INFO:
		cmdStr = _T("ArxRle_App_Info");
		msgInf(_T("ArxRle_App_Info"));
		break;
	case ARXRLE_APP_WINDDLG:
		cmdStr = _T("ArxRle_App_WindDlg");
		msgInf(_T("ArxRle_App_WindDlg"));
		break;
	case ARXRLE_APP_ABOUT:
		cmdStr = _T("ArxRle_App_About");
		msgInf(_T("ArxRle_App_About"));
		break;
	}

	if(cmdStr != NULL)
	{
		str.Format(_T("%s\n"), cmdStr);
		acDocManager->sendStringToExecute(acDocManager->curDocument(), str, false, false);
	}
}

void ArxRleMsgHandler::OnUpdateToolBarCommands(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

ArxRleMsgHandler* ArxRleMsgHandler::m_pMsgHandler = NULL;
BOOL ArxRleMsgHandler::CreateMsgHandler()
{
	if(m_pMsgHandler != NULL)
	{
		if(m_pMsgHandler->GetSafeHwnd() != NULL)
			return TRUE;
	}
	else
	{
		m_pMsgHandler =new ArxRleMsgHandler;
	}

	return m_pMsgHandler->Create(NULL, NULL, WS_CHILD | WS_MINIMIZE , CRect (0, 0, 1, 1), acedGetAcadFrame(), 10);
}

void ArxRleMsgHandler::DestroyMsgHandler() {
	if(m_pMsgHandler == NULL)
		return;

	if(m_pMsgHandler->GetSafeHwnd() != NULL)
		m_pMsgHandler->DestroyWindow();

	delete m_pMsgHandler;
	m_pMsgHandler = NULL;
}

ArxRleMsgHandler* ArxRleMsgHandler::GetMsgHandler() {
	if(m_pMsgHandler != NULL && m_pMsgHandler->GetSafeHwnd() != NULL)
		return (m_pMsgHandler);

	return NULL;
}
