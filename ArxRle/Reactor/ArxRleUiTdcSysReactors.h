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

#ifndef ARXRLEUITDCSYSREACTORS_H
#define ARXRLEUITDCSYSREACTORS_H

#include "Resource.h"

#include "ArxRleDatabaseReactor.h"
#include "ArxRleDocumentReactor.h"
#include "ArxRleDLinkerReactor.h"
#include "ArxRleEditorReactor.h"
#include "ArxRleEventReactor.h"
#include "ArxRleGsReactor.h"
#include "ArxRleEdInputContextReactor.h"
#include "ArxRleLayoutManagerReactor.h"
#include "ArxRleLongTransactionReactor.h"
#include "ArxRleTransactionReactor.h"

/****************************************************************************
**
**  CLASS ArxRleUiTdcSysReactors:
**
**  **jma
**
*************************************/

class ArxRleUiTdcSysReactors : public CAcUiTabChildDialog {

friend class ArxRleUiTdmReactors;
friend class ArxRleAppEditorReactor;	// has to be able to attach to newly constructed databases

public:
                    ArxRleUiTdcSysReactors();
    virtual         ~ArxRleUiTdcSysReactors()    {}

    //{{AFX_DATA(ArxRleUiTdcSysReactors)
    enum { IDD = ARXRLE_TDC_SYS_REACTORS };
    BOOL    m_doDatabase;
    BOOL    m_doDoc;
    BOOL    m_doLinker;
    BOOL    m_doEditor;
    BOOL    m_doEvent;
    BOOL    m_doTrans;
    BOOL    m_doLongTrans;
    BOOL    m_doGs;
    BOOL    m_doInput;
    BOOL    m_doLayout;
    BOOL    m_showLongTransDetails;
    BOOL    m_showEventDetails;
    BOOL    m_showEditorDetails;
    BOOL    m_showDocDetails;
    BOOL    m_showDbDetails;
    BOOL    m_showInputDetails;
	BOOL	m_suppressInputDetailsDuringDrag;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcSysReactors)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnMainDialogOK();
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcSysReactors)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members

        // helper functions
    void        doDbReactor();
    void        doDLinkerReactor();
    void        doDocReactor();
    void        doEditorReactor();
    void        doEventReactor();
    void        doGsReactor();
    void        doInputReactor();
    void        doLayoutReactor();
    void        doLongTransReactor();
    void        doTransReactor();

        // static global reactor pointers
	static ArxRleDatabaseReactor*			m_dbReactor;
	static ArxRleDLinkerReactor*			m_dLinkerReactor;
	static ArxRleDocumentReactor*			m_docReactor;
	static ArxRleEditorReactor*				m_edReactor;
	static ArxRleEventReactor*				m_eventReactor;
	static ArxRleGsReactor*					m_gsReactor;
	static ArxRleEdInputContextReactor*		m_inputReactor;
	static ArxRleLayoutManagerReactor*		m_layoutReactor;
	static ArxRleLongTransactionReactor*	m_longTransReactor;
	static ArxRleTransactionReactor*		m_transReactor;

        // attach/detach/cleanup functions
    static void attachDbReactorToAll();
    static void removeDbReactorFromAll();

    static void attachTransactionReactorToAll();
    static void removeTransactionReactorFromAll();

    static void attachInputReactorToAll();
    static void removeInputReactorFromAll();

    static void databaseConstructed(AcDbDatabase* db);
    static void databaseDestroyed(AcDbDatabase* db);

    static void cleanUpReactors();
};


#endif // ARXRLEUITDCSYSREACTORS_H

