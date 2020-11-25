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

#include "ArxRleUiTdmReferences.h"
#include "ArxRleUiTdcReferences.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxRleUiTdmReferences::ArxRleUiTdmReferences
**
**	**jma
**
*************************************/

ArxRleUiTdmReferences::ArxRleUiTdmReferences(const AcDbObjectIdArray& hardPointerIds,
											 const AcDbObjectIdArray& softPointerIds,
											 const AcDbObjectIdArray& hardOwnershipIds,
											 const AcDbObjectIdArray& softOwnershipIds,
											 CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxRleUiTdmReferences::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxRle-References"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcRefs = new ArxRleUiTdcReferences(hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds);

    //{{AFX_DATA_INIT(ArxRleUiTdmReferences)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxRleUiTdmReferences::~ArxRleUiTdmReferences
**
**	**jma
**
*************************************/

ArxRleUiTdmReferences::~ArxRleUiTdmReferences()
{
	delete m_tdcRefs;
}

/****************************************************************************
**
**  ArxRleUiTdmReferences::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdmReferences::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdmReferences)
    DDX_Control(pDX, ARXRLE_ENTS_TAB, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmReferences message map

BEGIN_MESSAGE_MAP(ArxRleUiTdmReferences, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdmReferences)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmReferences message handlers

/****************************************************************************
**
**  ArxRleUiTdmReferences::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdmReferences::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("References"),  ArxRleUiTdcReferences::IDD,   m_tdcRefs);

    return TRUE;
}

