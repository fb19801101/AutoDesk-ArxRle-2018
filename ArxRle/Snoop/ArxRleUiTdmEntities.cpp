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

#include "ArxRleUiTdmEntities.h"
#include "ArxRleUiTdcEntities.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxRleUiTdmEntities::ArxRleUiTdmEntities
**
**	**jma
**
*************************************/

ArxRleUiTdmEntities::ArxRleUiTdmEntities(const AcDbObjectIdArray& ents, bool isBlkDef, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxRleUiTdmEntities::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxRle-Entities"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcEnts = new ArxRleUiTdcEntities(ents, isBlkDef);

    //{{AFX_DATA_INIT(ArxRleUiTdmEntities)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxRleUiTdmEntities::~ArxRleUiTdmEntities
**
**	**jma
**
*************************************/

ArxRleUiTdmEntities::~ArxRleUiTdmEntities()
{
	delete m_tdcEnts;
}

/****************************************************************************
**
**  ArxRleUiTdmEntities::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdmEntities::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdmEntities)
    DDX_Control(pDX, ARXRLE_ENTS_TAB, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmEntities message map

BEGIN_MESSAGE_MAP(ArxRleUiTdmEntities, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdmEntities)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmEntities message handlers

/****************************************************************************
**
**  ArxRleUiTdmEntities::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdmEntities::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("Entities"),  ArxRleUiTdcEntities::IDD,   m_tdcEnts);

    return TRUE;
}

