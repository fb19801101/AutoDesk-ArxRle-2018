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

#include "ArxRleDLinkerReactor.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleDLinkerReactor, AcRxDLinkerReactor);

/****************************************************************************
**
**  ArxRleDLinkerReactor::ArxRleDLinkerReactor
**
**  **jma
**
*************************************/

ArxRleDLinkerReactor::ArxRleDLinkerReactor()
{
    acrxDynamicLinker->addReactor(this);
}

/****************************************************************************
**
**  ArxRleDLinkerReactor::~ArxRleDLinkerReactor
**
**  **jma
**
*************************************/

ArxRleDLinkerReactor::~ArxRleDLinkerReactor()
{
    acrxDynamicLinker->removeReactor(this);
}

/****************************************************************************
**
**  ArxRleDLinkerReactor::rxAppWillBeLoaded
**
**  **jma
**
*************************************/

void
ArxRleDLinkerReactor::rxAppWillBeLoaded(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Will Be Loaded"), moduleName);
}

/****************************************************************************
**
**  ArxRleDLinkerReactor::rxAppLoaded
**
**  **jma
**
*************************************/

void
ArxRleDLinkerReactor::rxAppLoaded(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Loaded"), moduleName);
}

/****************************************************************************
**
**  ArxRleDLinkerReactor::rxAppLoadAborted
**
**  **jma
**
*************************************/

void
ArxRleDLinkerReactor::rxAppLoadAborted(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Load Aborted"), moduleName);
}

/****************************************************************************
**
**  ArxRleDLinkerReactor::rxAppWillBeUnloaded
**
**  **jma
**
*************************************/

void
ArxRleDLinkerReactor::rxAppWillBeUnloaded(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Will Be Unloaded"), moduleName);
}

/****************************************************************************
**
**  ArxRleDLinkerReactor::rxAppUnloaded
**
**  **jma
**
*************************************/

void
ArxRleDLinkerReactor::rxAppUnloaded(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Unloaded"), moduleName);
}

/****************************************************************************
**
**  ArxRleDLinkerReactor::rxAppUnloadAborted
**
**  **jma
**
*************************************/

void
ArxRleDLinkerReactor::rxAppUnloadAborted(const TCHAR* moduleName)
{
    printReactorMessage(_T("ARX App Unload Aborted"), moduleName);
}

/****************************************************************************
**
**  ArxRleDLinkerReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleDLinkerReactor::printReactorMessage(LPCTSTR event, const TCHAR* moduleName) const
{
    acutPrintf(_T("\n%-15s : [%s = %s] "), _T("[DLINKER REACTOR]"), event, moduleName);
}
