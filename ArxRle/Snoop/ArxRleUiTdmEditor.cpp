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

#include "ArxRleUiTdmEditor.h"
#include "ArxRleUiTdcDocs.h"
#include "ArxRleUiTdcClasses.h"
#include "ArxRleUiTdcCmds.h"
#include "ArxRleUiTdcHostAppSrv.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxRleUiTdmEditor::ArxRleUiTdmEditor
**
**	**jma
**
*************************************/

ArxRleUiTdmEditor::ArxRleUiTdmEditor(CWnd* parent)
:   CAcUiTabMainDialog(ArxRleUiTdmEditor::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxRle-Editor"));

	m_tdcDocs = new ArxRleUiTdcDocs;
	m_tdcClasses = new ArxRleUiTdcClasses;
	m_tdcCommands = new ArxRleUiTdcCmds;
	m_tdcHostAppSrv = new ArxRleUiTdcHostAppSrv;

    //{{AFX_DATA_INIT(ArxRleUiTdmEditor)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxRleUiTdmEditor::ArxRleUiTdmEditor
**
**	**jma
**
*************************************/

ArxRleUiTdmEditor::ArxRleUiTdmEditor(CWnd* parent, AcApDocument* doc)
:   CAcUiTabMainDialog(ArxRleUiTdmEditor::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxRle-Editor"));

	ASSERT(doc != NULL);

	m_tdcDocs = new ArxRleUiTdcDocs(doc);
	m_tdcClasses = NULL;
	m_tdcCommands = NULL;
	m_tdcHostAppSrv = NULL;

    //{{AFX_DATA_INIT(ArxRleUiTdmEditor)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxRleUiTdmEditor::~ArxRleUiTdmEditor
**
**	**jma
**
*************************************/

ArxRleUiTdmEditor::~ArxRleUiTdmEditor()
{
	delete m_tdcDocs;
	delete m_tdcClasses;
	delete m_tdcCommands;
	delete m_tdcHostAppSrv;
}

/****************************************************************************
**
**  ArxRleUiTdmEditor::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdmEditor::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdmEditor)
    DDX_Control(pDX, ARXRLE_EDITOR_TAB, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmEditor message map

BEGIN_MESSAGE_MAP(ArxRleUiTdmEditor, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdmEditor)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmEditor message handlers

/****************************************************************************
**
**  ArxRleUiTdmEditor::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdmEditor::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	SetAcadTabPointer(&m_tabCtrl);

	ASSERT(m_tdcDocs != NULL);
	int i = 0;

	AddTab(i++, _T("Documents"), ArxRleUiTdcDocs::IDD,     m_tdcDocs);

		// if constructor with Docs only called, we don't add these two pages
	if (m_tdcClasses)
		AddTab(i++, _T("Classes"),   ArxRleUiTdcClasses::IDD, m_tdcClasses);

	if (m_tdcCommands)
		AddTab(i++, _T("Commands"),  ArxRleUiTdcCmds::IDD, m_tdcCommands);

	if (m_tdcHostAppSrv)
		AddTab(i++, _T("Host App Services"),  ArxRleUiTdcHostAppSrv::IDD, m_tdcHostAppSrv);

    return TRUE;
}

