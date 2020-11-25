//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "stdafx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleCmdBlock.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleSelSet.h"
#include "AcadUtils\ArxRleApply.h"
#include "Prompt\ArxRleKeywordArray.h"
#include "DbEntity\ArxRleEntityClass.h"


/****************************************************************************
**
**  ArxRleCmdBlock::registerCommandLineFunctions
**
**  **000
**
*************************************/

void ArxRleCmdBlock::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{																			    
	cmdStack->addCommand(appname, _T("ArxRleBlockTK"),               _T("BlockTK"),               ACRX_CMD_MODAL, &blockTK);
	cmdStack->addCommand(appname, _T("ArxRleBlockBTL"),              _T("BlockBTL"),              ACRX_CMD_MODAL, &blockBTL);
	cmdStack->addCommand(appname, _T("ArxRleBlockZBZ"),              _T("BlockZBZ"),              ACRX_CMD_MODAL, &blockZBZ);
}

/****************************************************************************
**
**  ArxRleCmdBlock::blockTK
**
**  **000
**
*************************************/

void ArxRleCmdBlock::blockTK()
{
	ArxRleKeywordArray kwords(ArxRleApp::getApp()->dllInstance());
	kwords.append(_T("A2"), _T("A2"));
	kwords.append(_T("A3"), _T("A3"));
	kwords.append(_T("A4"), _T("A4"));

	CString optionsStr, kwordStr;
	kwords.makeOptionsList(optionsStr);
	kwords.makeKeywordList(kwordStr);

	CString promptStr;
	promptStr.Format(_T("TK selection options %s"), optionsStr);

	ArxRleUiPrKeyWord prCmd(promptStr, kwordStr);
	if(prCmd.go() != ArxRleUiPrBase::kOk)
		return;

	int keywordIndex;
	if(kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
		ASSERT(0);
		return;
	}


	ArxRleString blk_path = GetCurPath()+L"\\ArxRle\\blk.dwg";
	if(!FileExist(blk_path.t_str())) return;

	ArxRleUiPrPoint prPt(_T("InsertPt"), NULL);
	if(prPt.go() != ArxRleUiPrBase::kOk)
		return;

	if(keywordIndex == 0)
	{
		AddBlock(blk_path, "A2", CPt3d(prPt.value()));
	}
	else if(keywordIndex == 1)
	{
		AddBlock(blk_path, "A3", CPt3d(prPt.value()));
	}
	else if(keywordIndex == 2)
	{
		AddBlock(blk_path, "A4", CPt3d(prPt.value()));
	}
	else 
	{
		ASSERT(0);
		return;
	}
}

/****************************************************************************
**
**  ArxRleCmdBlock::blockBTL
**
**  **000
**
*************************************/

void ArxRleCmdBlock::blockBTL()
{
	ArxRleString blk_path = GetCurPath()+L"\\ArxRle\\blk.dwg";
	if(!FileExist(blk_path.t_str())) return;

	ArxRleUiPrPoint prPt(_T("InsertPt"), NULL);
	if(prPt.go() != ArxRleUiPrBase::kOk)
		return;

	AddBlock(blk_path, "BTL", CPt3d(prPt.value()));
}

/****************************************************************************
**
**  ArxRleCmdBlock::blockZBZ
**
**  **000
**
*************************************/

void ArxRleCmdBlock::blockZBZ()
{
	ArxRleString blk_path = GetCurPath()+L"\\ArxRle\\blk.dwg";
	if(!FileExist(blk_path.t_str())) return;

	ArxRleUiPrPoint prPt(_T("InsertPt"), NULL);
	if(prPt.go() != ArxRleUiPrBase::kOk)
		return;

	AddBlock(blk_path, "ZBZ", CPt3d(prPt.value()));
}
