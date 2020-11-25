//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleUiTdmObjects.h"
#include "ArxRleUiTdcObjects.h"
#include "ArxRle.h"
#include "AcadUtils/ArxRleSelSet.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxRleUiTdmObjects::ArxRleUiTdmObjects
**
**	**jma
**
*************************************/

ArxRleUiTdmObjects::ArxRleUiTdmObjects(const AcDbObjectIdArray& objIds, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxRleUiTdmObjects::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxRle-Objects"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcObjs = new ArxRleUiTdcObjects(objIds);

    //{{AFX_DATA_INIT(ArxRleUiTdmObjects)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxRleUiTdmObjects::~ArxRleUiTdmObjects
**
**	**jma
**
*************************************/

ArxRleUiTdmObjects::~ArxRleUiTdmObjects()
{
	delete m_tdcObjs;
}

/****************************************************************************
**
**  ArxRleUiTdmObjects::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdmObjects::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdmObjects)
    DDX_Control(pDX, ARXRLE_ENTS_TAB, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmObjects message map

BEGIN_MESSAGE_MAP(ArxRleUiTdmObjects, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdmObjects)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmObjects message handlers

/****************************************************************************
**
**  ArxRleUiTdmObjects::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdmObjects::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("Objects"),  ArxRleUiTdcObjects::IDD, m_tdcObjs);

    return TRUE;
}

