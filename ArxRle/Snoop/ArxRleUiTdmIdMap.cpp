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

#include "ArxRleUiTdmIdMap.h"
#include "ArxRleUiTdcIdMap.h"
#include "ArxRle.h"
#include "AcadUtils/ArxRleSelSet.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxRleUiTdmIdMap::ArxRleUiTdmIdMap
**
**	**jma
**
*************************************/

ArxRleUiTdmIdMap::ArxRleUiTdmIdMap(AcDbIdMapping* idMap, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxRleUiTdmIdMap::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxRle-IdMap"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcIdMap = new ArxRleUiTdcIdMap(idMap);

    //{{AFX_DATA_INIT(ArxRleUiTdmIdMap)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxRleUiTdmIdMap::~ArxRleUiTdmIdMap
**
**	**jma
**
*************************************/

ArxRleUiTdmIdMap::~ArxRleUiTdmIdMap()
{
	delete m_tdcIdMap;
}

/****************************************************************************
**
**  ArxRleUiTdmIdMap::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdmIdMap::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdmIdMap)
    DDX_Control(pDX, ARXRLE_IDMAP_TAB, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmIdMap message map

BEGIN_MESSAGE_MAP(ArxRleUiTdmIdMap, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdmIdMap)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmIdMap message handlers

/****************************************************************************
**
**  ArxRleUiTdmIdMap::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdmIdMap::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("Id Mapping"), ArxRleUiTdcIdMap::IDD, m_tdcIdMap);

    return TRUE;
}

