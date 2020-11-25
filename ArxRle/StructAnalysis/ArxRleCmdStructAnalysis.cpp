/
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
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "AcadUtils\ArxRleUtils.h"
#include "Prompt\ArxRleKeywordArray.h"
#include "DbEntity\ArxRleEntityClass.h"
#include "AcadUtils/ArxRleSelSet.h"
#include "ArxRleCmdStructAnalysis.h"
#include "ArxRleUiDlgSteelSection.h"
#include "ArxRleUiTdmSpa.h"


/****************************************************************************
**
**  ArxRleCmdStructAnalysis::registerCommandLineFunctions
**
**  **000
**
*************************************/

void ArxRleCmdStructAnalysis::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
	cmdStack->addCommand(appname, _T("ArxRleAnalysisConcrete"),           _T("AnalysisConcrete"),           ACRX_CMD_MODAL, &AnalysisConcrete);
	cmdStack->addCommand(appname, _T("ArxRleAnalysisSteel"),              _T("AnalysisSteel"),              ACRX_CMD_MODAL, &AnalysisSteel);

	cmdStack->addCommand(appname, _T("ArxRleSteelSection"),               _T("SteelSection"),               ACRX_CMD_MODAL, &drawSteelSection);
}

/****************************************************************************
**
**  ArxRleCmdStructAnalysis::setParam
**
**  **000
**
*************************************/

void ArxRleCmdStructAnalysis::AnalysisConcrete() //加载施工网络计划基本设置对话框
{
	ArxRleUiTdmSpa dlg(acedGetAcadDwgView());
	dlg.DoModal();
}

/****************************************************************************
**
**  ArxRleCmdStructAnalysis::importWork
**
**  **000
**
*************************************/

void ArxRleCmdStructAnalysis::AnalysisSteel()
{
	msgInf(L"AnalysisSteel");
}


/****************************************************************************
**
**  ArxRleCmdStructAnalysis::drawSteelSection
**
**  **000
**
*************************************/

void ArxRleCmdStructAnalysis::drawSteelSection()
{
	ArxRleUiDlgSteelSection dlg(acedGetAcadDwgView());
	dlg.DoModal();
}

