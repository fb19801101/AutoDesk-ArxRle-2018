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

#include "ArxRleUiTdcSysReactors.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// These statics are all MDI aware

ArxRleDatabaseReactor*			ArxRleUiTdcSysReactors::m_dbReactor = nullptr;
ArxRleDLinkerReactor*			ArxRleUiTdcSysReactors::m_dLinkerReactor = nullptr;
ArxRleDocumentReactor*			ArxRleUiTdcSysReactors::m_docReactor = nullptr;
ArxRleEditorReactor*			ArxRleUiTdcSysReactors::m_edReactor = nullptr;
ArxRleEventReactor*				ArxRleUiTdcSysReactors::m_eventReactor = nullptr;
ArxRleGsReactor*				ArxRleUiTdcSysReactors::m_gsReactor = nullptr;
ArxRleEdInputContextReactor*	ArxRleUiTdcSysReactors::m_inputReactor = nullptr;
ArxRleLayoutManagerReactor*		ArxRleUiTdcSysReactors::m_layoutReactor = nullptr;
ArxRleLongTransactionReactor*	ArxRleUiTdcSysReactors::m_longTransReactor = nullptr;
ArxRleTransactionReactor*		ArxRleUiTdcSysReactors::m_transReactor = nullptr;


/****************************************************************************
**
**  ArxRleUiTdcSysReactors::ArxRleUiTdcSysReactors
**
**  **jma
**
*************************************/

ArxRleUiTdcSysReactors::ArxRleUiTdcSysReactors()
:   CAcUiTabChildDialog(nullptr, ArxRleApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxRleUiTdcSysReactors)
    m_doDatabase	= (m_dbReactor != nullptr) ? TRUE : FALSE;
    m_doDoc			= (m_docReactor != nullptr) ? TRUE : FALSE;
    m_doLinker		= (m_dLinkerReactor != nullptr) ? TRUE : FALSE;
    m_doEditor		= (m_edReactor != nullptr) ? TRUE : FALSE;
    m_doEvent		= (m_eventReactor != nullptr) ? TRUE : FALSE;
    m_doGs			= (m_gsReactor != nullptr) ? TRUE : FALSE;
    m_doInput		= (m_inputReactor != nullptr) ? TRUE : FALSE;
    m_doLongTrans	= (m_longTransReactor != nullptr) ? TRUE : FALSE;
    m_doLayout		= (m_layoutReactor != nullptr) ? TRUE : FALSE;
    m_doTrans		= (m_transReactor != nullptr) ? TRUE : FALSE;
    //}}AFX_DATA_INIT

	m_showLongTransDetails = FALSE;
	if (m_longTransReactor)
		m_showLongTransDetails = m_longTransReactor->showDetails();

	m_showEventDetails = FALSE;
	if (m_eventReactor)
		m_showEventDetails = m_eventReactor->showDetails();

	m_showDocDetails = FALSE;
	if (m_docReactor)
		m_showDocDetails = m_docReactor->showDetails();

	m_showDbDetails = FALSE;
	if (m_dbReactor)
		m_showDbDetails = m_dbReactor->showDetails();

	m_showInputDetails = FALSE;
	if (m_inputReactor)
		m_showInputDetails = m_inputReactor->showDetails();

	m_suppressInputDetailsDuringDrag = TRUE;
	if (m_inputReactor)
		m_suppressInputDetailsDuringDrag = m_inputReactor->suppressDetailsDuringDrag();
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::cleanUpReactors
**      static function to clean up any left over reactors if
**  app exits and they are still turned on.
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::cleanUpReactors()
{
    removeDbReactorFromAll();
	removeTransactionReactorFromAll();
	removeInputReactorFromAll();

    delete m_dbReactor;
    delete m_docReactor;
    delete m_dLinkerReactor;
    delete m_edReactor;
    delete m_eventReactor;
    delete m_gsReactor;
    delete m_inputReactor;
    delete m_longTransReactor;
    delete m_layoutReactor;
    delete m_transReactor;

    m_dbReactor = nullptr;
    m_docReactor = nullptr;
    m_dLinkerReactor = nullptr;
    m_edReactor = nullptr;
    m_eventReactor = nullptr;
    m_gsReactor = nullptr;
    m_inputReactor = nullptr;
    m_layoutReactor = nullptr;
    m_longTransReactor = nullptr;
    m_transReactor = nullptr;
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabChildDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcSysReactors)
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_DATABASE, m_doDatabase);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_DOCUMENT, m_doDoc);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_DYN_LINKER, m_doLinker);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_EDITOR, m_doEditor);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_EVENT, m_doEvent);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_TRANS, m_doTrans);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_LONG_TRANS, m_doLongTrans);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_LAYOUT, m_doLayout);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_GS, m_doGs);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_INPUT, m_doInput);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_LONG_TRANS_DEBAILS, m_showLongTransDetails);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_EVENT_DETAILS, m_showEventDetails);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_DOC_DETAILS, m_showDocDetails);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_EDITOR_DETAILS, m_showEditorDetails);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_DB_DETAILS, m_showDbDetails);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_INPUT_DETAILS, m_showInputDetails);
	DDX_Check(pDX, ARXRLE_SYS_REACTORS_CK_DRAG_SUPPRESS_INPUT, m_suppressInputDetailsDuringDrag);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcSysReactors message handlers

BEGIN_MESSAGE_MAP(ArxRleUiTdcSysReactors, CAcUiTabChildDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdcSysReactors)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcSysReactors message handlers


/****************************************************************************
**
**  ArxRleUiTdcSysReactors::OnMainDialogOK
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::OnMainDialogOK()
{
	doEditorReactor();
	doEventReactor();
	doDbReactor();
	doDocReactor();
	doDLinkerReactor();
	doGsReactor();
	doInputReactor();
	doLongTransReactor();
	doLayoutReactor();
	doTransReactor();

	CAcUiTabChildDialog::OnMainDialogOK();
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::doDbReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::doDbReactor()
{
    if (m_doDatabase) {
        if (m_dbReactor == NULL) {
            m_dbReactor = new ArxRleDatabaseReactor;
            acutPrintf(_T("\nDatabase Reactor Spy Turned On ..."));
            ArxRleUiTdcSysReactors::attachDbReactorToAll();
        }
		m_dbReactor->setShowDetails(intToBool(m_showDbDetails));
    }
    else {
        if (m_dbReactor != NULL) {
            ArxRleUiTdcSysReactors::removeDbReactorFromAll();
            delete m_dbReactor;
            m_dbReactor = NULL;
            acutPrintf(_T("\nDatabase Reactor Spy Turned Off ..."));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::doDocReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::doDocReactor()
{
    if (m_doDoc) {
        if (m_docReactor == NULL) {
            m_docReactor = new ArxRleDocumentReactor;
            acutPrintf(_T("\nDocument Reactor Spy Turned On ..."));
        }
		m_docReactor->setShowDetails(intToBool(m_showDocDetails));
    }
    else {
        if (m_docReactor != NULL) {
            delete m_docReactor;
            m_docReactor = NULL;
            acutPrintf(_T("\nDocument Reactor Spy Turned Off ..."));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::doEditorReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::doEditorReactor()
{
    if (m_doEditor) {
        if (m_edReactor == NULL) {
            m_edReactor = new ArxRleEditorReactor;
            acutPrintf(_T("\nEditor Reactor Spy Turned On ..."));
        }
		m_edReactor->setShowDetails(intToBool(m_showEditorDetails));
    }
    else {
        if (m_edReactor != NULL) {
            delete m_edReactor;
            m_edReactor = NULL;
            acutPrintf(_T("\nEditor Reactor Spy Turned Off ..."));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::doEventReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::doEventReactor()
{
    if (m_doEvent) {
        if (m_eventReactor == NULL) {
            m_eventReactor = new ArxRleEventReactor;
            acutPrintf(_T("\nEvent Reactor Spy Turned On ..."));
        }
		m_eventReactor->setShowDetails(intToBool(m_showEventDetails));
    }
    else {
        if (m_eventReactor != NULL) {
            delete m_eventReactor;
            m_eventReactor = NULL;
            acutPrintf(_T("\nEvent Reactor Spy Turned Off ..."));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::doDLinkerReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::doDLinkerReactor()
{
    if (m_doLinker) {
        if (m_dLinkerReactor == NULL) {
            m_dLinkerReactor = new ArxRleDLinkerReactor;
            acutPrintf(_T("\nDynamic Linker Reactor Spy Turned On ..."));
        }
    }
    else {
        if (m_dLinkerReactor != NULL) {
            delete m_dLinkerReactor;
            m_dLinkerReactor = NULL;
            acutPrintf(_T("\nDynamic Linker Reactor Spy Turned Off ..."));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::doInputReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::doInputReactor()
{
    if (m_doInput) {
        if (m_inputReactor == NULL) {
            m_inputReactor = new ArxRleEdInputContextReactor;
            acutPrintf(_T("\nEditor Input Reactor Spy Turned On ..."));
			ArxRleUiTdcSysReactors::attachInputReactorToAll();
        }
		m_inputReactor->setShowDetails(intToBool(m_showInputDetails));
		m_inputReactor->setSuppressDetailsDuringDrag(intToBool(m_suppressInputDetailsDuringDrag));
    }
    else {
        if (m_inputReactor != NULL) {
			ArxRleUiTdcSysReactors::removeInputReactorFromAll();
            delete m_inputReactor;
            m_inputReactor = NULL;
            acutPrintf(_T("\nEditor Input Reactor Spy Turned Off ..."));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::doLayoutReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::doLayoutReactor()
{
    if (m_doLayout) {
        if (m_layoutReactor == NULL) {
            m_layoutReactor = new ArxRleLayoutManagerReactor;
            acutPrintf(_T("\nLayout Manager Reactor Spy Turned On ..."));
        }
    }
    else {
        if (m_layoutReactor != NULL) {
            delete m_layoutReactor;
            m_layoutReactor = NULL;
            acutPrintf(_T("\nLayout Manager Reactor Spy Turned Off ..."));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::doGsReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::doGsReactor()
{
    if (m_doGs) {
        if (m_gsReactor == NULL) {
            m_gsReactor = new ArxRleGsReactor;
            acutPrintf(_T("\nGraphics System Reactor Spy Turned On ..."));
        }
    }
    else {
        if (m_gsReactor != NULL) {
            delete m_gsReactor;
            m_gsReactor = NULL;
            acutPrintf(_T("\nGraphics System Reactor Spy Turned Off ..."));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::doTransReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::doTransReactor()
{
    if (m_doTrans) {
        if (m_transReactor == NULL) {
            m_transReactor = new ArxRleTransactionReactor;
            acutPrintf(_T("\nTransaction Reactor Spy Turned On ..."));
            ArxRleUiTdcSysReactors::attachTransactionReactorToAll();
        }
    }
    else {
        if (m_transReactor != NULL) {
            ArxRleUiTdcSysReactors::removeTransactionReactorFromAll();
            delete m_transReactor;
            m_transReactor = NULL;
            acutPrintf(_T("\nTransaction Reactor Spy Turned Off ..."));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::doLongTransReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::doLongTransReactor()
{
    if (m_doLongTrans) {
        if (m_longTransReactor == NULL) {
            m_longTransReactor = new ArxRleLongTransactionReactor;
            acutPrintf(_T("\nLong Transaction Reactor Spy Turned On ..."));
        }
		m_longTransReactor->setShowDetails(intToBool(m_showLongTransDetails));
    }
    else {
        if (m_longTransReactor != NULL) {
            delete m_longTransReactor;
            m_longTransReactor = NULL;
            acutPrintf(_T("\nLong Transaction Reactor Spy Turned Off ..."));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::attachDbReactorToAll
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::attachDbReactorToAll()
{
    if (m_dbReactor) {
        auto dbPtrs = acdbActiveDatabaseArray();

        acutPrintf(_T("\nAttaching Database Reactor to all active databases..."));

        for (auto&& pDb: dbPtrs) {
            pDb->addReactor(m_dbReactor);
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::removeDbReactorFromAll
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::removeDbReactorFromAll()
{
    if (m_dbReactor) {
        auto dbPtrs = acdbActiveDatabaseArray();

        acutPrintf(_T("\nRemoving Database Reactor from all active databases..."));

        for (auto&& pDb : dbPtrs) {
            pDb->removeReactor(m_dbReactor);
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::attachTransactionReactorToAll
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::attachTransactionReactorToAll()
{
    if (m_transReactor) {
        auto dbPtrs = acdbActiveDatabaseArray();

		AcDbVoidPtrArray trMgrs;	// keep track of ones we've attached to since some db's share transMgr

        acutPrintf(_T("\nAttaching Transaction Reactor to all active databases..."));

        for (auto&& pDb: dbPtrs) {
            AcDbTransactionManager* tmpTrMgr = pDb->transactionManager();
			if (tmpTrMgr && (trMgrs.contains(tmpTrMgr) == false)) {
				tmpTrMgr->addReactor(m_transReactor);
				trMgrs.append(tmpTrMgr);
			}
			else {
				CString str;
                acutPrintf(_T("\nSkipping duplicate transaction manager for: (%s)"), ArxRleUtils::dbToStr(pDb, str));
			}
		}
	}
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::removeTransactionReactorFromAll
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::removeTransactionReactorFromAll()
{
    if (m_transReactor) {
        auto dbPtrs = acdbActiveDatabaseArray();

        acutPrintf(_T("\nRemoving Transaction Reactor from all active databases..."));

        for (auto&& pDb : dbPtrs) {
            AcDbTransactionManager* tmpTrMgr = pDb->transactionManager();
            if (tmpTrMgr)
                tmpTrMgr->removeReactor(m_transReactor);
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::attachInputReactorToAll
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::attachInputReactorToAll()
{
    if (m_inputReactor) {
		AcDbVoidPtrArray docPtrs;
		ArxRleUtils::getAllDocuments(docPtrs);

        acutPrintf(_T("\nAttaching Editor Input Reactor to all documents..."));

        for (void *pVoid : docPtrs) {
            AcApDocument* tmpDoc = static_cast<AcApDocument*>(pVoid);
		    tmpDoc->inputPointManager()->addInputContextReactor(m_inputReactor);
		}
	}
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::removeInputReactorFromAll
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::removeInputReactorFromAll()
{
    if (m_inputReactor) {
		AcDbVoidPtrArray docPtrs;
		ArxRleUtils::getAllDocuments(docPtrs);

        acutPrintf(_T("\nRemoving Editor Input Reactor from all documents..."));

        for (void *pVoid : docPtrs) {
            AcApDocument* tmpDoc = static_cast<AcApDocument*>(pVoid);
		    tmpDoc->inputPointManager()->removeInputContextReactor(m_inputReactor);
		}
	}
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::databaseConstructed
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::databaseConstructed(AcDbDatabase* db)
{
	if (m_dbReactor)
		db->addReactor(m_dbReactor);

	if (m_transReactor) {
		AcDbTransactionManager* trMgr = db->transactionManager();
		if (trMgr)
			trMgr->addReactor(m_transReactor);
	}
}

/****************************************************************************
**
**  ArxRleUiTdcSysReactors::databaseDestroyed
**
**  **jma
**
*************************************/

void
ArxRleUiTdcSysReactors::databaseDestroyed(AcDbDatabase* db)
{
	if (m_dbReactor)
		db->removeReactor(m_dbReactor);

	if (m_transReactor) {
		AcDbTransactionManager* trMgr = db->transactionManager();
		if (trMgr)
			trMgr->removeReactor(m_transReactor);
	}
}




