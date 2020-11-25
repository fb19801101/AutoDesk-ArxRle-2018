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

#include "ArxRleDatabaseReactor.h"
#include "AcadUtils/ArxRleUtils.h"
#include "Snoop/ArxRleUiTdmObjects.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleDatabaseReactor, AcDbDatabaseReactor);

/****************************************************************************
**
**  ArxRleDatabaseReactor::ArxRleDatabaseReactor
**
**  **jma
**
*************************************/

ArxRleDatabaseReactor::ArxRleDatabaseReactor()
{
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::~ArxRleDatabaseReactor
**
**  **jma
**
*************************************/

ArxRleDatabaseReactor::~ArxRleDatabaseReactor()
{
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxRleDatabaseReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::objectAppended
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::objectAppended(const AcDbDatabase* db, const AcDbObject* obj)
{
    printReactorMessage(db, _T("Appended"), obj);
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::objectUnAppended
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::objectUnAppended(const AcDbDatabase* db, const AcDbObject* obj)
{
    printReactorMessage(db, _T("Un-Appended"), obj);
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::objectReAppended
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::objectReAppended(const AcDbDatabase* db, const AcDbObject* obj)
{
    printReactorMessage(db, _T("Re-Appended"), obj);
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::objectOpenedForModify
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::objectOpenedForModify(const AcDbDatabase* db, const AcDbObject* obj)
{
    printReactorMessage(db, _T("Opened For Modify"), obj);
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::objectModified
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::objectModified(const AcDbDatabase* db, const AcDbObject* obj)
{
    printReactorMessage(db, _T("Modified"), obj);
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::objectErased
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::objectErased(const AcDbDatabase* db, const AcDbObject* obj,
                            Adesk::Boolean erased)
{
    if (erased)
        printReactorMessage(db, _T("Erased"), obj);
    else
        printReactorMessage(db, _T("Un-erased"), obj);
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::headerSysVarWillChange
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::headerSysVarWillChange(const AcDbDatabase* db, const TCHAR* name)
{
    printReactorMessage(db, _T("SysVar Will Change"), name);
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::headerSysVarChanged
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::headerSysVarChanged(const AcDbDatabase* db, const TCHAR* name,
                                        Adesk::Boolean bSuccess)
{
    printReactorMessage(db, _T("SysVar Changed"), name);
    if (bSuccess != Adesk::kTrue)
        acutPrintf(_T("\n*** SYSVAR NOT CHANGED SUCCESSFULLY!!! ***"));
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::proxyResurrectionCompleted
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::proxyResurrectionCompleted(const AcDbDatabase* db,
										const TCHAR* appname, AcDbObjectIdArray& objects)
{
	printReactorMessage(db, _T("Proxy Resurrection Completed"), appname);

	if (m_showDetails) {
		CString str;
		str.Format(_T("Resurrected Proxies: %s"), appname);
		ArxRleUiTdmObjects dbox(objects, acedGetAcadDwgView(), str);
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::goodbye
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::goodbye(const AcDbDatabase* db)
{
	printReactorMessage(db, _T("Goodbye"));
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::printReactorMessage(const AcDbDatabase* db, LPCTSTR event, const AcDbObject* obj) const
{
    CString str, str2;
    ArxRleUtils::objToHandleStr(obj, str);
    str2.Format(_T("<DB REACTOR: %p>"), db);
    
    acutPrintf(_T("\n%-15s : <%-18s: %s, %s> "), str2, event,
                        ArxRleUtils::objToClassStr(obj), str);
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::printReactorMessage(const AcDbDatabase* db, LPCTSTR event, const LPCTSTR str) const
{
    CString str2;
    str2.Format(_T("<DB REACTOR: %p>"), db);

    acutPrintf(_T("\n%-15s : <%-18s: %s> "), str2, event, str);
}

/****************************************************************************
**
**  ArxRleDatabaseReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleDatabaseReactor::printReactorMessage(const AcDbDatabase* db, LPCTSTR event) const
{
    CString str2;
    str2.Format(_T("<DB REACTOR: %p>"), db);

    acutPrintf(_T("\n%-15s : <%-18s> "), str2, event);
}


