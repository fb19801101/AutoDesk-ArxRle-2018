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

#include "ArxRleDocumentReactor.h"
#include "AcadUtils/ArxRleUtils.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleDocumentReactor, AcApDocManagerReactor);

/****************************************************************************
**
**  ArxRleDocumentReactor::ArxRleDocumentReactor
**
**  **jma
**
*************************************/

ArxRleDocumentReactor::ArxRleDocumentReactor()
{
    acDocManager->addReactor(this);
}

/****************************************************************************
**
**  ArxRleDocumentReactor::~ArxRleDocumentReactor
**
**  **jma
**
*************************************/

ArxRleDocumentReactor::~ArxRleDocumentReactor()
{
    acDocManager->removeReactor(this);
}

/****************************************************************************
**
**  ArxRleDocumentReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxRleDocumentReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxRleDocumentReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentCreateStarted
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentCreateStarted(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document Create Started"));
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentCreated
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentCreated(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document Created"));
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentToBeDestroyed
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentToBeDestroyed(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document To Be Destroyed"));
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentCreateCanceled
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentCreateCanceled(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document Create Canceled"));
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentLockModeWillChange
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentLockModeWillChange(AcApDocument* doc,
                AcAp::DocLockMode myCurrentMode,
                AcAp::DocLockMode myNewMode,
                AcAp::DocLockMode currentMode,
                const TCHAR* pGlobalCmdName)
{
    printReactorMessage(doc, _T("Document Lock Mode Will Change"));

	if (m_showDetails) {
		CString str1;

		acutPrintf(_T("\n    MyCurMode:  %s"), ArxRleUtils::docLockModeToStr(myCurrentMode, str1));
		acutPrintf(_T("\n    MyNewMode:  %s"), ArxRleUtils::docLockModeToStr(myNewMode, str1));
		acutPrintf(_T("\n    CurMode:    %s"), ArxRleUtils::docLockModeToStr(currentMode, str1));
		acutPrintf(_T("\n    CmdName:    %s"), pGlobalCmdName);
	}
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentLockModeChangeVetoed
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentLockModeChangeVetoed(AcApDocument* doc,
                const TCHAR* pGlobalCmdName)
{
	CString msg;
	msg.Format(_T("Document Lock Mode Change Vetoed, CmdName = %s"), pGlobalCmdName);
    printReactorMessage(doc, msg);
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentLockModeChanged
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentLockModeChanged(AcApDocument* doc,
                AcAp::DocLockMode myPreviousMode,
                AcAp::DocLockMode myCurrentMode,
                AcAp::DocLockMode currentMode,
                const TCHAR* pGlobalCmdName)
{
    printReactorMessage(doc, _T("Document Lock Mode Changed"));

	if (m_showDetails) {
		CString str1;

		acutPrintf(_T("\n    MyPrevMode: %s"), ArxRleUtils::docLockModeToStr(myPreviousMode, str1));
		acutPrintf(_T("\n    MyCurMode:  %s"), ArxRleUtils::docLockModeToStr(myCurrentMode, str1));
		acutPrintf(_T("\n    CurMode:    %s"), ArxRleUtils::docLockModeToStr(currentMode, str1));
		acutPrintf(_T("\n    CmdName:    %s"), pGlobalCmdName);
	}
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentBecameCurrent
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentBecameCurrent(AcApDocument* doc)
{
    if (doc)
        printReactorMessage(doc, _T("Document Became Current"));
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentToBeActivated
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentToBeActivated(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document To Be Activated"));
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentToBeDeactivated
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentToBeDeactivated(AcApDocument* doc)
{
    printReactorMessage(doc, _T("Document To Be De-activated"));
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentActivationModified
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentActivationModified(bool bActivation)
{
	CString msg, str;
	msg.Format(_T("Document Activation Modified (Activation = %s)"),
					ArxRleUtils::booleanToStr(bActivation, str));
    printReactorMessage(msg);
}

/****************************************************************************
**
**  ArxRleDocumentReactor::documentActivated
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::documentActivated(AcApDocument* doc)
{
    if (doc)
        printReactorMessage(doc, _T("Document Activated"));
}

/****************************************************************************
**
**  ArxRleDocumentReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::printReactorMessage(AcApDocument* doc, LPCTSTR event) const
{
    CString str2;
    str2.Format(_T("<DOC REACTOR: %s>"), doc->docTitle());

    acutPrintf(_T("\n%-15s : [%s] "), str2, event);
}

/****************************************************************************
**
**  ArxRleDocumentReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleDocumentReactor::printReactorMessage(LPCTSTR event) const
{
    CString str2 = _T("<DOC REACTOR: >");

    acutPrintf(_T("\n%-15s : [%s] "), str2, event);
}


