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

#include "ArxRleUiTdcOptions.h"
#include "App/ArxRleOptions.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiTdcOptions::ArxRleUiTdcOptions
**
**  **jma
**
*************************************/

ArxRleUiTdcOptions::ArxRleUiTdcOptions(CWnd* pParent)
:	CAcUiTabChildDialog(pParent)
{
	//{{AFX_DATA_INIT(ArxRleUiTdcOptions)
	//}}AFX_DATA_INIT

		// get the initial values from our global object
	m_showDwgFilerMsgs =       ArxRleOptions::m_instance.m_showDwgFilerMessages;
	m_showWblockCloneDetails = ArxRleOptions::m_instance.m_showWblockCloneDetails;
	m_showDeepCloneDetails =   ArxRleOptions::m_instance.m_showDeepCloneDetails;
	m_doDictInsertByHand =     ArxRleOptions::m_instance.m_doDictRecordInsertByHand;
}

/****************************************************************************
**
**  ArxRleUiTdcOptions::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcOptions::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ArxRleUiTdcOptions)
	DDX_Check(pDX, ARXRLE_OPTIONS_CK_DWG_FILER_MESSAGES, m_showDwgFilerMsgs);
	DDX_Check(pDX, ARXRLE_OPTIONS_CK_DEEP_CLONE_DETAILS, m_showDeepCloneDetails);
	DDX_Check(pDX, ARXRLE_OPTIONS_CK_WBLOCK_CLONE_DETAILS, m_showWblockCloneDetails);
	DDX_Check(pDX, ARXRLE_OPTIONS_CK_USE_DICT_MERGESTYLE, m_doDictInsertByHand);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcOptions message map

BEGIN_MESSAGE_MAP(ArxRleUiTdcOptions, CAcUiTabChildDialog)
	//{{AFX_MSG_MAP(ArxRleUiTdcOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcOptions message handlers

/****************************************************************************
**
**  ArxRleUiTdcOptions::OnMainDialogOK
**
**  **jma
**
*************************************/

void
ArxRleUiTdcOptions::OnMainDialogOK()
{
    CAcUiTabChildDialog::OnMainDialogOK();

		// set the final values on our global object. NOTE: can't just
		// put these directly in the DDX map since MFC doesn't map anything
		// to type "bool", only to type "BOOL"
	ArxRleOptions::m_instance.m_showDwgFilerMessages     = intToBool(m_showDwgFilerMsgs);
	ArxRleOptions::m_instance.m_showWblockCloneDetails   = intToBool(m_showWblockCloneDetails);
	ArxRleOptions::m_instance.m_showDeepCloneDetails     = intToBool(m_showDeepCloneDetails);
	ArxRleOptions::m_instance.m_doDictRecordInsertByHand = intToBool(m_doDictInsertByHand);
}

