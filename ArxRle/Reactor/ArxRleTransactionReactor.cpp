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

#include "ArxRleTransactionReactor.h"
#include "AcadUtils/ArxRleUtils.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleTransactionReactor, AcTransactionReactor);

/****************************************************************************
**
**  ArxRleTransactionReactor::ArxRleTransactionReactor
**
**  **jma
**
*************************************/

ArxRleTransactionReactor::ArxRleTransactionReactor()
{
}

/****************************************************************************
**
**  ArxRleTransactionReactor::~ArxRleTransactionReactor
**
**  **jma
**
*************************************/

ArxRleTransactionReactor::~ArxRleTransactionReactor()
{
}

/****************************************************************************
**
**  ArxRleTransactionReactor::transactionAboutToStart
**
**  **jma
**
*************************************/

void
ArxRleTransactionReactor::transactionAboutToStart(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction About To Start"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxRleTransactionReactor::transactionAboutToEnd
**
**  **jma
**
*************************************/

void
ArxRleTransactionReactor::transactionAboutToEnd(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction About To End"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxRleTransactionReactor::transactionAboutToAbort
**
**  **jma
**
*************************************/

void
ArxRleTransactionReactor::transactionAboutToAbort(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction About To Abort"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxRleTransactionReactor::transactionStarted
**
**  **jma
**
*************************************/

void
ArxRleTransactionReactor::transactionStarted(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction Started"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxRleTransactionReactor::transactionEnded
**
**  **jma
**
*************************************/

void
ArxRleTransactionReactor::transactionEnded(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction Ended"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxRleTransactionReactor::transactionAborted
**
**  **jma
**
*************************************/

void
ArxRleTransactionReactor::transactionAborted(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("Transaction Aborted"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxRleTransactionReactor::endCalledOnOutermostTransaction
**
**  **jma
**
*************************************/

void
ArxRleTransactionReactor::endCalledOnOutermostTransaction(int& numTransactions, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("End Called On Outermost Transaction"), numTransactions, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxRleTransactionReactor::objectIdSwapped
**
**  **jma
**
*************************************/

void
ArxRleTransactionReactor::objectIdSwapped(const AcDbObject* pTransResObj, const AcDbObject* pOtherObj, AcDbTransactionManager* transactionManagerPtr)
{
    printReactorMessage(_T("ObjectId Swapped"), pTransResObj, pOtherObj, transactionManagerPtr);
}

/****************************************************************************
**
**  ArxRleTransactionReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleTransactionReactor::printReactorMessage(LPCTSTR event, int numTransactions) const
{
    acutPrintf(_T("\n%-15s : [%d --> %s] "), _T("[TRANSACT REACTOR]"), numTransactions, event);
}

/****************************************************************************
**
**  ArxRleTransactionReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleTransactionReactor::printReactorMessage(LPCTSTR event, int numTransactions,
							AcDbTransactionManager* transactionManagerPtr) const
{
	CString str;

    acutPrintf(_T("\n%-15s : [%d --> %s] (TrMgr = %s)"), _T("[TRANSACT REACTOR]"),
			numTransactions, event, ArxRleUtils::ptrToStr(transactionManagerPtr, str));
}

/****************************************************************************
**
**  ArxRleTransactionReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleTransactionReactor::printReactorMessage(LPCTSTR event, const AcDbObject* obj1,
							const AcDbObject* obj2,
							AcDbTransactionManager* transactionManagerPtr) const
{
	CString str, str2;

    acutPrintf(_T("\n%-15s : [%s] (TrMgr = %s)"), _T("[TRANSACT REACTOR]"),
			event, ArxRleUtils::ptrToStr(transactionManagerPtr, str));
	acutPrintf(_T("\n    SWAPPED: %s --> %s"),
			ArxRleUtils::objToClassAndHandleStr(obj1, str),
			ArxRleUtils::objToClassAndHandleStr(obj2, str2));
					
}


