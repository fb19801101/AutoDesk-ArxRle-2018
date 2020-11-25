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
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleEdUiContext.h"
#include "ArxRle.h"
#include "AcExtensionModule.h"
#include "Resource.h"



//ACRX_CONS_DEFINE_MEMBERS(ArxRleEdUiContext, AcEdUiContext, 1)

/**************************************************************************
**
**  ArxRleEdUiContext::ArxRleEdUiContext
**
**  **jma
**
*************************************/

ArxRleEdUiContext::ArxRleEdUiContext(int nSub)
{
	CAcModuleResourceOverride(ArxRleApp::getApp()->dllInstance());

	m_nSub = nSub;
    m_cMenu = new CMenu;
    BOOL res = m_cMenu->LoadMenu(ARXRLE_MENU_CONTEXT);
    VERIFY(res);
    if (!res) {
        delete m_cMenu;
        m_cMenu = NULL;
    }
}

/**************************************************************************
**
**  ArxRleEdUiContext::ArxRleEdUiContext
**
**  **jma
**
*************************************/

ArxRleEdUiContext::~ArxRleEdUiContext()
{
    if (m_cMenu) 
        delete m_cMenu;
}

/**************************************************************************
**
**  ArxRleEdUiContext::getMenuContext
**
**  **jma
**
*************************************/

void* 
ArxRleEdUiContext::getMenuContext(const AcRxClass* classtype, const AcDbObjectIdArray& selectedObjs)
{
    m_hMenu = m_cMenu->GetSubMenu(m_nSub)->GetSafeHmenu();
    return &m_hMenu;
}

/**************************************************************************
**
**  ArxRleEdUiContext::onCommand
**
**  **jma
**
*************************************/

void  
ArxRleEdUiContext::onCommand(Adesk::UInt32 cmdId)
{
	LPCTSTR cmdStr = NULL;
	CString str;

	if (cmdId == ARXRLE_CONTEXT_EDITOR_INFO)
		cmdStr = _T("ArxRleSnoopEd");
	else if (cmdId == ARXRLE_CONTEXT_DB_INFO)
		cmdStr = _T("ArxRleSnoopDb");
	else if (cmdId == ARXRLE_CONTEXT_ENT_INFO)
		cmdStr = _T("ArxRleSnoopEnts");
	else if (cmdId == ARXRLE_CONTEXT_NESTEDENT_INFO)
		cmdStr = _T("ArxRleSnoopNents");
	else if (cmdId == ARXRLE_CONTEXT_SERVICES_INFO)
		cmdStr = _T("ArxRleSnoopServices");
	else if (cmdId == ARXRLE_CONTEXT_REGISTRY_INFO)
		cmdStr = _T("ArxRleSnoopSysRegistry");
	else if (cmdId == ARXRLE_CONTEXT_REACTOR_INFO)
		cmdStr = _T("ArxRleReactors");
	else if (cmdId == ARXRLE_CONTEXT_OBJ_STATE)
		cmdStr = _T("ArxRleTestState");
	else if (cmdId == ARXRLE_CONTEXT_DWG_FILER)
		cmdStr = _T("ArxRleTestDwgFiler");
	else if (cmdId == ARXRLE_CONTEXT_TDB_CLONE)
		cmdStr = _T("ArxRleTestTransDbClones");
	else if (cmdId == ARXRLE_CONTEXT_WORLD_DRAW)
		cmdStr = _T("ArxRleTestWorldDraw");
	else if (cmdId == ARXRLE_CONTEXT_CURVES)
		cmdStr = _T("ArxRleTestCurve");
	else if (cmdId == ARXRLE_CONTEXT_SELSET)
		cmdStr = _T("ArxRleTestSelSet");
	else if (cmdId == ARXRLE_CONTEXT_XDATA)
		cmdStr = _T("ArxRleTestXdata");
	else if (cmdId == ARXRLE_CONTEXT_EXTENTS)
		cmdStr = _T("ArxRleTestExtents");
	else if (cmdId == ARXRLE_CONTEXT_INTERSECT)
		cmdStr = _T("ArxRleTestIntersect");
	else if (cmdId == ARXRLE_CONTEXT_GRIPPTS)
		cmdStr = _T("ArxRleTestGetGripPoints");
	else if (cmdId == ARXRLE_CONTEXT_STRETCHPTS)
		cmdStr = _T("ArxRleTestGetStretchPoints");
	else if (cmdId == ARXRLE_CONTEXT_OSNAP)
		cmdStr = _T("ArxRleTestGetOsnapPoints");
	else if (cmdId == ARXRLE_CONTEXT_EXTDICT_ADD)
		cmdStr = _T("ArxRleTestExtDictAdd");
	else if (cmdId == ARXRLE_CONTEXT_EXTDICT_REMOVE)
		cmdStr = _T("ArxRleTestExtDictRemove");
	else if (cmdId == ARXRLE_CONTEXT_COLOR)
		cmdStr = _T("ArxRleTestColor");
	else if (cmdId == ARXRLE_CONTEXT_PURGE)
		cmdStr = _T("ArxRleTestPruge");
	else if (cmdId == ARXRLE_CONTEXT_COUNTREFS)
		cmdStr = _T("ArxRleTestCountHardRefs");
	else if (cmdId == ARXRLE_CONTEXT_ENTMAKE)
		cmdStr = _T("ArxRleTestEntMake");
	else if (cmdId == ARXRLE_CONTEXT_TBLMAKE)
		cmdStr = _T("ArxRleTestTblMake");
	else if (cmdId == ARXRLE_CONTEXT_XFORM)
		cmdStr = _T("ArxRleTestXform");
	else if (cmdId == ARXRLE_CONTEXT_LOGO_ADD)
		cmdStr = _T("ArxRleAdeskLogoAdd");
	else if (cmdId == ARXRLE_CONTEXT_LOGO_MODIFY)
		cmdStr = _T("ArxRleAdeskLogoModify");
	else if (cmdId == ARXRLE_CONTEXT_LOGO_HARDWIRE1)
		cmdStr = _T("ArxRleAdeskLogoHardwire1");
	else if (cmdId == ARXRLE_CONTEXT_LOGO_HARDWIRE2)
		cmdStr = _T("ArxRleAdeskLogoHardwire2");
	else if (cmdId == ARXRLE_CONTEXT_LOGO_ADD_STYLE)
		cmdStr = _T("ArxRleAdeskLogoStyleAdd");
	else if (cmdId == ARXRLE_CONTEXT_LOGO_MOD_STYLE)
		cmdStr = _T("ArxRleAdeskLogoStyleModify");
	else if (cmdId == ARXRLE_CONTEXT_ABOUT)
		cmdStr = _T("ArxRleAbout");

	else if (cmdId == ARXRLE_CONTEXT_ENT_ATTRIBUTE)
		cmdStr = _T("ArxRleEntAttribute");
	else if (cmdId == ARXRLE_CONTEXT_NETPLAN_NODEMODIFY)
		cmdStr = _T("ArxRleNetPlanWorkModifyWorkNodes");

	if (cmdStr != NULL) {
		str.Format(_T("%s\n"), cmdStr);
	    acDocManager->sendStringToExecute(acDocManager->curDocument(), str, false, false);
	}
}

