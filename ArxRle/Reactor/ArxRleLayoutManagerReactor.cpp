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

#include "ArxRleLayoutManagerReactor.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleLayoutManagerReactor, AcDbLayoutManagerReactor);

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::ArxRleLayoutManagerReactor
**
**  **jma
**
*************************************/

ArxRleLayoutManagerReactor::ArxRleLayoutManagerReactor()
{
	acdbHostApplicationServices()->layoutManager()->addReactor(this);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::~ArxRleLayoutManagerReactor
**
**  **jma
**
*************************************/

ArxRleLayoutManagerReactor::~ArxRleLayoutManagerReactor()
{
	acdbHostApplicationServices()->layoutManager()->removeReactor(this);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::layoutCreated
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::layoutCreated(const TCHAR* newLayoutName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Layout Created"), newLayoutName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::layoutToBeRemoved
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::layoutToBeRemoved(const TCHAR* layoutName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Layout To Be Removed"), layoutName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::layoutRemoved
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::layoutRemoved(const TCHAR* layoutName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Layout Removed"), layoutName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::abortLayoutRemoved
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::abortLayoutRemoved(const TCHAR* layoutName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Abort Layout Removed"), layoutName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::layoutToBeCopied
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::layoutToBeCopied(const TCHAR* layoutName, const AcDbObjectId& oldLayoutId)
{
	printReactorMessage(_T("Layout To Be Copied"), layoutName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::layoutCopied
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::layoutCopied(const TCHAR* oldLayoutName,
				const AcDbObjectId& oldLayoutId,
				const TCHAR* newLayoutName,
				const AcDbObjectId& newLayoutId)
{
	printReactorMessage(_T("Layout Copied"), oldLayoutName, newLayoutName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::abortLayoutCopied
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::abortLayoutCopied(const TCHAR* layoutName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Abort Layout Copied"), layoutName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::layoutToBeRenamed
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::layoutToBeRenamed(const TCHAR* oldName,
				const TCHAR* newName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Layout To Be Renamed"), oldName, newName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::layoutsReordered
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::layoutsReordered()
{
	printReactorMessage(_T("Layouts Reordered"), _T("All"));
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::layoutRenamed
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::layoutRenamed(const TCHAR* oldName,
				const TCHAR* newName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Layout Renamed"), oldName, newName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::abortLayoutRename
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::abortLayoutRename(const TCHAR* oldName,
				const TCHAR* newName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Abort Layout Rename"), oldName, newName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::layoutSwitched
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::layoutSwitched(const TCHAR* newLayoutname, const AcDbObjectId& newLayoutId)
{
	printReactorMessage(_T("Layout Switched"), newLayoutname);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::plotStyleTableChanged
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::plotStyleTableChanged(const TCHAR* newTableName, const AcDbObjectId& layoutId)
{
	printReactorMessage(_T("Plot Style Table Changed"), newTableName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::printReactorMessage(LPCTSTR event, const TCHAR* layoutName) const
{
    acutPrintf(_T("\n%-15s : [%s, \"%s\"] "), _T("[LAYOUT REACTOR]"), event, layoutName);
}

/****************************************************************************
**
**  ArxRleLayoutManagerReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleLayoutManagerReactor::printReactorMessage(LPCTSTR event, const TCHAR* layoutName1,
												const TCHAR* layoutName2) const
{
    acutPrintf(_T("\n%-15s : [%s, \"%s\" --> \"%s\"] "), _T("[LAYOUT REACTOR]"), event, layoutName1, layoutName2);
}

