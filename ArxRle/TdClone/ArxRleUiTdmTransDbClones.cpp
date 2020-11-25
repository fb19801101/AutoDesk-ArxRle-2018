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

#include "ArxRleUiTdmTransDbClones.h"
#include "ArxRleUiTdcCloneSet.h"
#include "ArxRleUiTdcWblockClone.h"
#include "ArxRleUiTdcInsert.h"
#include "ArxRle.h"
#include "AcadUtils/ArxRleSelSet.h"
#include "Prompt/ArxRleUiPrompts.h"
#include "AcadUtils/ArxRleUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxRleUiTdmTransDbClones::ArxRleUiTdmTransDbClones
**
**	**jma
**
*************************************/

ArxRleUiTdmTransDbClones::ArxRleUiTdmTransDbClones(CWnd* parent, const TCHAR* winTitle)
:   CAcUiTabMainDialog(ArxRleUiTdmTransDbClones::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxRle-TransDbClones"));

	if (winTitle != NULL)
		m_winTitle = winTitle;

	m_tdcCloneSet = new ArxRleUiTdcCloneSet;
	m_tdcWblockClone = new ArxRleUiTdcWblockClone;
	m_tdcInsert = new ArxRleUiTdcInsert;

    //{{AFX_DATA_INIT(ArxRleUiTdmTransDbClones)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxRleUiTdmTransDbClones::~ArxRleUiTdmTransDbClones
**
**	**jma
**
*************************************/

ArxRleUiTdmTransDbClones::~ArxRleUiTdmTransDbClones()
{
	delete m_tdcCloneSet;
	delete m_tdcWblockClone;
	delete m_tdcInsert;
}

/****************************************************************************
**
**  ArxRleUiTdmTransDbClones::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdmTransDbClones::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdmTransDbClones)
    DDX_Control(pDX, ARXRLE_TRANSDB_CLONES_TAB, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmTransDbClones message map

BEGIN_MESSAGE_MAP(ArxRleUiTdmTransDbClones, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdmTransDbClones)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmTransDbClones message handlers

/****************************************************************************
**
**  ArxRleUiTdmTransDbClones::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdmTransDbClones::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	if (m_winTitle.IsEmpty() == FALSE)
		SetWindowText(m_winTitle);

	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("Clone Set"),     ArxRleUiTdcCloneSet::IDD,    m_tdcCloneSet);
	AddTab(1, _T("Wblock Clone"),  ArxRleUiTdcWblockClone::IDD, m_tdcWblockClone);
	AddTab(2, _T("Insert"),        ArxRleUiTdcInsert::IDD,      m_tdcInsert);
    
    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdmTransDbClones::addToCloneSet
**
**  **jma
**
*************************************/

void
ArxRleUiTdmTransDbClones::addToCloneSet(ArxRleCloneSet& cloneSet)
{
	BeginEditorCommand();

	ArxRleSelSet ss;
	if (ss.userSelect() != ArxRleSelSet::kSelected) {
		CompleteEditorCommand();
		return;
	}

	AcDbObjectIdArray objIds;
	ss.asArray(objIds);

	cloneSet.addObjects(objIds);

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiTdmTransDbClones::getBasePoint
**
**  **jma
**
*************************************/

void
ArxRleUiTdmTransDbClones::getBasePoint(AcGePoint3d& basePt)
{
	BeginEditorCommand();

	ArxRleUiPrPoint prPt(_T("Base point"), NULL);
	if (prPt.go() == ArxRleUiPrPoint::kOk)
		basePt = ArxRleUtils::ucsToWcs(prPt.value());

	CompleteEditorCommand();
}

