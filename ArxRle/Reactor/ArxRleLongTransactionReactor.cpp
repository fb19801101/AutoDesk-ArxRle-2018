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

#include "ArxRleLongTransactionReactor.h"
#include "AcadUtils/ArxRleUtils.h"
#include "Snoop/ArxRleUiTdmLongTrans.h"
#include "Snoop/ArxRleUiTdmObjects.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleLongTransactionReactor, AcApLongTransactionReactor);

/****************************************************************************
**
**  ArxRleLongTransactionReactor::ArxRleLongTransactionReactor
**
**  **jma
**
*************************************/

ArxRleLongTransactionReactor::ArxRleLongTransactionReactor()
:	m_showDetails(false)
{
    acapLongTransactionManager->addReactor(this);
}

/****************************************************************************
**
**  ArxRleLongTransactionReactor::~ArxRleLongTransactionReactor
**
**  **jma
**
*************************************/

ArxRleLongTransactionReactor::~ArxRleLongTransactionReactor()
{
    acapLongTransactionManager->removeReactor(this);
}

/****************************************************************************
**
**  ArxRleLongTransactionReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxRleLongTransactionReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxRleLongTransactionReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxRleLongTransactionReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxRleLongTransactionReactor::beginCheckOut
**
**  **jma
**
*************************************/

void
ArxRleLongTransactionReactor::beginCheckOut(AcDbLongTransaction& lt, AcDbObjectIdArray& originList)
{
	printReactorMessage(lt, _T("Begin Check Out"));

	if (m_showDetails) {
		ArxRleUiTdmObjects dbox(originList, acedGetAcadDwgView(), _T("Original Check-Out Set"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleLongTransactionReactor::endCheckOut
**
**  **jma
**
*************************************/

void
ArxRleLongTransactionReactor::endCheckOut(AcDbLongTransaction& lt)
{
	printReactorMessage(lt, _T("End Check Out"));
}

/****************************************************************************
**
**  ArxRleLongTransactionReactor::beginCheckIn
**
**  **jma
**
*************************************/

void
ArxRleLongTransactionReactor::beginCheckIn(AcDbLongTransaction& lt)
{
	printReactorMessage(lt, _T("Begin Check In"));
}

/****************************************************************************
**
**  ArxRleLongTransactionReactor::endCheckIn
**
**  **jma
**
*************************************/

void
ArxRleLongTransactionReactor::endCheckIn(AcDbLongTransaction& lt)
{
	printReactorMessage(lt, _T("End Check In"));
}

/****************************************************************************
**
**  ArxRleLongTransactionReactor::abortLongTransaction
**
**  **jma
**
*************************************/

void
ArxRleLongTransactionReactor::abortLongTransaction(AcDbLongTransaction& lt)
{
	printReactorMessage(lt, _T("Abort Long Transaction"));
}

/****************************************************************************
**
**  ArxRleLongTransactionReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleLongTransactionReactor::printReactorMessage(AcDbLongTransaction& lt, LPCTSTR event) const
{
    CString str;

	TCHAR* transName = NULL;
    Acad::ErrorStatus es = lt.getLongTransactionName(transName);
	if (es == Acad::eOk) {
		str = transName;
		acutDelString(transName);
	}
	else {
		str = ArxRleUtils::rxErrorStr(es);
	}

    acutPrintf(_T("\n%-15s : <%-18s: %s> "), _T("<LONG TRANS REACTOR>"), event, str);

	if (m_showDetails) {
		ArxRleUiTdmLongTrans dbox(&lt, acedGetAcadDwgView(), event);
		dbox.DoModal();
	}
}

