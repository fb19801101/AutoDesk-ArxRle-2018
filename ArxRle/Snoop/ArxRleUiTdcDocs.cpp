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

#include "ArxRleUiTdcDocs.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRleUiTdmDatabase.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  ArxRleUiTdcDocs::ArxRleUiTdcDocs
**
**  **jma
**
*************************************/

ArxRleUiTdcDocs::ArxRleUiTdcDocs()
:   m_curIndex(0)
{
		// get all document pointers
    AcApDocumentIterator* iter = acDocManager->newAcApDocumentIterator();
    if (iter) {
        AcApDocument* tmpDoc;
        for (; !iter->done(); iter->step()) {
            tmpDoc = iter->document();
			if (tmpDoc)
				m_docPtrs.append(tmpDoc);
        }
        delete iter;
    }

    //{{AFX_DATA_INIT(ArxRleUiTdcDocs)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcDocs::ArxRleUiTdcDocs
**
**  **jma
**
*************************************/

ArxRleUiTdcDocs::ArxRleUiTdcDocs(AcApDocument* doc)
:   m_curIndex(0)
{
	ASSERT(doc != NULL);

	m_docPtrs.append(doc);

    //{{AFX_DATA_INIT(ArxRleUiTdcDocs)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcDocs::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDocs::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiTdcRxObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcDocs)
	DDX_Control(pDX, ARXRLE_DOCS_LB_DOCS, m_docList);
	DDX_Control(pDX, ARXRLE_DOCS_LC_DATA, m_dataList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcDocs message map

BEGIN_MESSAGE_MAP(ArxRleUiTdcDocs, ArxRleUiTdcRxObjectBase)
    //{{AFX_MSG_MAP(ArxRleUiTdcDocs)
	ON_LBN_SELCHANGE(ARXRLE_DOCS_LB_DOCS, OnSelchangeDocs)
	ON_BN_CLICKED(ARXRLE_DOCS_BN_DATABASE, OnDatabase)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcDocs message handlers

/****************************************************************************
**
**  ArxRleUiTdcDocs::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcDocs::OnInitDialog() 
{
    ArxRleUiTdcRxObjectBase::OnInitDialog();

	fillListBox(m_curIndex);

	buildColumns(m_dataList);
    displayCurrent(m_curIndex);

    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcDocs::fillListBox
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDocs::fillListBox(int defIndex)
{
    m_docList.ResetContent();

	AcApDocument* tmpDoc;
	CString str;

	int len = m_docPtrs.length();
	for (int i=0; i<len; i++) {
		tmpDoc = static_cast<AcApDocument*>(m_docPtrs[i]);
		str = tmpDoc->docTitle();

		if ((acDocManager->curDocument() == tmpDoc) && (acDocManager->mdiActiveDocument() == tmpDoc))
			str += _T("  (Current/MDI Active)");
		else if (acDocManager->curDocument() == tmpDoc)
			str += _T("  (Current)");
		else if (acDocManager->mdiActiveDocument() == tmpDoc)
			str += _T("  (MDI Active)");

		m_docList.AddString(str);
    }

    int retCode = m_docList.SetCurSel(defIndex);
    ASSERT(retCode != LB_ERR);
}

/****************************************************************************
**
**  ArxRleUiTdcDocs::displayCurrent
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDocs::displayCurrent(int index)
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    ASSERT((index >= 0) && (index < m_docPtrs.length()));

	CString str;
	AcApDocument* doc = static_cast<AcApDocument*>(m_docPtrs[index]);

    addToDataList(_T("File Name"), doc->fileName(), true);
    addToDataList(_T("Document Title"), doc->docTitle(), true);
    addToDataList(_T("Database"), ArxRleUtils::dbToStr(doc->database(), str));
    addToDataList(_T("MFC CDocument"), ArxRleUtils::ptrToStr(doc->cDoc(), str));
    addToDataList(_T("Transaction Manager"), ArxRleUtils::ptrToStr(doc->transactionManager(), str));
    addToDataList(_T("Context Pointer"), ArxRleUtils::ptrToStr(doc->contextPtr(), str));
    addToDataList(_T("Format For Save"), ArxRleUtils::saveFormatToStr(doc->formatForSave(), str));
    addToDataList(_T("Lock Mode"), ArxRleUtils::docLockModeToStr(doc->lockMode(), str));
    addToDataList(_T("My Lock Mode"), ArxRleUtils::docLockModeToStr(doc->myLockMode(), str));
    addToDataList(_T("Is Quiescent"), ArxRleUtils::booleanToStr(doc->isQuiescent(), str));
    addToDataList(_T("Is Read Only"), ArxRleUtils::booleanToStr(doc->isReadOnly(), str));

		// print out all the lisp apps that are loaded with this document
	CString unloadStr;
    int lispAppCount = doc->GetCountOfLispList();
	if (lispAppCount > 0) {
		addSeperatorLine(_T("LISP Apps"));

		AcLispAppInfo* appInfo;
		for (int i=0; i<lispAppCount; i++) {
			appInfo = doc->GetItemOfLispList(i);
			if (appInfo) {
				if (appInfo->bUnloadable)
					unloadStr = _T("Unloadable");
				else
					unloadStr = _T("Not Unloadable");

				addToDataList(appInfo->appFileName, unloadStr);
			}
		}
	}

	drawPropsList(m_dataList);
}

/****************************************************************************
**
**  ArxRleUiTdcDocs::OnSelchangeDocs
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDocs::OnSelchangeDocs()
{
    int index = m_docList.GetCurSel();

    if (index != LB_ERR) {
		m_curIndex = index;
		displayCurrent(m_curIndex);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDocs::OnDatabase
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDocs::OnDatabase() 
{
    ASSERT((m_curIndex >= 0) && (m_curIndex < m_docPtrs.length()));

	AcApDocument* doc = static_cast<AcApDocument*>(m_docPtrs[m_curIndex]);

    ArxRleUiTdmDatabase dbox(doc->database(), this, doc->docTitle());
    dbox.DoModal();
}

