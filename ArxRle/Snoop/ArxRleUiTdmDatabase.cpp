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

#include "ArxRleUiTdmDatabase.h"
#include "ArxRleUiTdcSymTbl.h"
#include "ArxRleUiTdcDict.h"
#include "ArxRleUiTdcDatabase.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxRleUiTdmDatabase::ArxRleUiTdmDatabase
**
**	**jma
**
*************************************/

ArxRleUiTdmDatabase::ArxRleUiTdmDatabase(AcDbDatabase* db, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxRleUiTdmDatabase::IDD, parent, ArxRleApp::getApp()->dllInstance()),
	m_db(db)
{
	SetDialogName(_T("ArxRle-Database"));

	ASSERT(db != NULL);

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcSymTbl = new ArxRleUiTdcSymTbl(db);
	m_tdcDicts = new ArxRleUiTdcDict(db->namedObjectsDictionaryId(), false);
	m_tdcDb = new ArxRleUiTdcDatabase(db);

    //{{AFX_DATA_INIT(ArxRleUiTdmDatabase)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxRleUiTdmDatabase::ArxRleUiTdmDatabase
**
**	**jma
**
*************************************/

ArxRleUiTdmDatabase::ArxRleUiTdmDatabase(const AcDbObjectId& dictId, CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxRleUiTdmDatabase::IDD, parent, ArxRleApp::getApp()->dllInstance()),
	m_db(dictId.database())
{
	SetDialogName(_T("ArxRle-Database"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcSymTbl = NULL;
	m_tdcDicts = new ArxRleUiTdcDict(dictId, true);
	m_tdcDb = NULL;

    //{{AFX_DATA_INIT(ArxRleUiTdmDatabase)
    //}}AFX_DATA_INIT
}


/****************************************************************************
**
**	ArxRleUiTdmDatabase::~ArxRleUiTdmDatabase
**
**	**jma
**
*************************************/

ArxRleUiTdmDatabase::~ArxRleUiTdmDatabase()
{
	delete m_tdcSymTbl;
	delete m_tdcDicts;
	delete m_tdcDb;
}

/****************************************************************************
**
**  ArxRleUiTdmDatabase::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdmDatabase::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdmDatabase)
    DDX_Control(pDX, ARXRLE_DATABASE_TAB, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmDatabase message map

BEGIN_MESSAGE_MAP(ArxRleUiTdmDatabase, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdmDatabase)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmDatabase message handlers

/****************************************************************************
**
**  ArxRleUiTdmDatabase::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdmDatabase::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	int i = 0;

	if (m_tdcSymTbl)
		AddTab(i++, _T("Symbol Tables"),  ArxRleUiTdcSymTbl::IDD,   m_tdcSymTbl);

	if (m_tdcDicts)
		AddTab(i++, _T("Dictionaries"),   ArxRleUiTdcDict::IDD,     m_tdcDicts);

	if (m_tdcDb)
		AddTab(i++, _T("Database"),       ArxRleUiTdcDatabase::IDD, m_tdcDb);
    
    return TRUE;
}

