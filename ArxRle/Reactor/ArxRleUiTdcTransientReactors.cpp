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

#include "ArxRleUiTdcTransientReactors.h"
#include "Snoop/ArxRleUiDlgObjState.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"
#include "ArxRleUiTdmREactors.h"
#include "AcadUtils/ArxRleDocLockWrite.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

    // static state variables for showing state of notifying object
BOOL    ArxRleUiTdcTransientReactors::m_doStateModified = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateCancelled = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateErased = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateCopied = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateGoodbye = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateOpenMod = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateSubObjMod = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateModUndone = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateModXdata = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateModGraphics = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateUnappended = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateReappended = FALSE;
BOOL    ArxRleUiTdcTransientReactors::m_doStateClosed = FALSE;


// These statics are all MDI aware
ArxRleTransientObjReactor*	ArxRleUiTdcTransientReactors::m_objReactor = NULL;
ArxRleTransientEntReactor*	ArxRleUiTdcTransientReactors::m_entReactor = NULL;


/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::ArxRleUiTdcTransientReactors
**
**  **jma
**
*************************************/

ArxRleUiTdcTransientReactors::ArxRleUiTdcTransientReactors()
:   ArxRleUiTdcObjReactorsBase()
{
    //{{AFX_DATA_INIT(ArxRleUiTdcTransientReactors)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::cleanUpReactors
**      static function to clean up any left over reactors if
**  app exits and they are still turned on.
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::cleanUpReactors()
{
    delete m_objReactor;
    delete m_entReactor;

    m_objReactor = NULL;
    m_entReactor = NULL;
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiTdcObjReactorsBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcTransientReactors)
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_MODIFIED, m_doStateModified);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_CANCELLED, m_doStateCancelled);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_ERASED, m_doStateErased);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_COPIED, m_doStateCopied);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_GOODBYE, m_doStateGoodbye);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_OPENMOD, m_doStateOpenMod);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_SUBOBJMOD, m_doStateSubObjMod);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_MODUNDONE, m_doStateModUndone);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_MODXDATA, m_doStateModXdata);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_MODGRAPHICS, m_doStateModGraphics);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_UNAPPENDED, m_doStateUnappended);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_REAPPENDED, m_doStateReappended);
	DDX_Check(pDX, ARXRLE_REACTORS_CK_STATE_CLOSED, m_doStateClosed);
    //}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcTransientReactors message handlers

BEGIN_MESSAGE_MAP(ArxRleUiTdcTransientReactors, ArxRleUiTdcObjReactorsBase)
    //{{AFX_MSG_MAP(ArxRleUiTdcTransientReactors)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcTransientReactors message handlers


/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcTransientReactors::OnInitDialog() 
{
	ArxRleUiTdcObjReactorsBase::OnInitDialog();

	return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::getAttachedObjects
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::getAttachedObjects(AcDbObjectIdArray& objIds)
{
	if (m_objReactor)
		objIds = m_objReactor->m_objList;
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::getAttachedEntities
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::getAttachedEntities(AcDbObjectIdArray& objIds)
{
	if (m_entReactor)
		objIds = m_entReactor->m_objList;
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::detachSelectedEnts
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::detachSelectedEnts(const AcDbObjectIdArray& objIds) 
{
	if (m_entReactor != NULL) {
		Acad::ErrorStatus es;
		AcDbEntity* ent;

		ArxRleDocLockWrite docLock;	// these potentially came from other documents

		int len = objIds.length();
		for (int i=0; i<len; i++) {
			es = docLock.lock(objIds[i].database());	// lock the document associated with this database
			if (es == Acad::eOk) {
				es = acdbOpenAcDbEntity(ent, objIds[i], AcDb::kForWrite, true);
				if (es == Acad::eOk) {
					m_entReactor->delFromObject(ent);
					ent->close();
				}
				else {
					ArxRleUtils::rxErrorAlert(es);
				}
			}
			else {
				ArxRleUtils::rxErrorAlert(es);
			}
		}
	}
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::detachSelectedObjs
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::detachSelectedObjs(const AcDbObjectIdArray& objIds) 
{
	if (m_objReactor != NULL) {
		Acad::ErrorStatus es;
		AcDbObject* obj;

		ArxRleDocLockWrite docLock;	// these potentially came from other documents

		int len = objIds.length();
		for (int i=0; i<len; i++) {
			es = docLock.lock(objIds[i].database());	// lock the document associated with this database
			if (es == Acad::eOk) {
				es = acdbOpenAcDbObject(obj, objIds[i], AcDb::kForWrite, true);
				if (es == Acad::eOk) {
					m_objReactor->delFromObject(obj);
					obj->close();
				}
				else {
					ArxRleUtils::rxErrorAlert(es);
				}
			}
			else {
				ArxRleUtils::rxErrorAlert(es);
			}
		}
	}
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::attachObjReactors
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::attachObjReactors(const AcDbObjectIdArray& objIds)
{
        // re-use same reactor if it is already allocated
    if (m_objReactor == NULL) {
        acutPrintf(_T("\nAllocating new ObjectReactor..."));
        m_objReactor = new ArxRleTransientObjReactor;
    }

	Acad::ErrorStatus es;
	AcDbObject* obj;

	ArxRleDocLockWrite docLock;	// these potentially came from other documents

	int len = objIds.length();
	for (int i=0; i<len; i++) {
		es = docLock.lock(objIds[i].database());	// lock the document associated with this database
		if (es == Acad::eOk) {
			es = acdbOpenAcDbObject(obj, objIds[i], AcDb::kForWrite, true);
			if (es == Acad::eOk) {
				m_objReactor->addToObject(obj);
				obj->close();
			}
			else {
				ArxRleUtils::rxErrorAlert(es);
			}
		}
		else {
			ArxRleUtils::rxErrorAlert(es);
		}
	}
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::attachEntReactors
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::attachEntReactors()
{
        // re-use same reactor if it is already allocated
    if (m_entReactor == NULL) {
        acutPrintf(_T("\nAllocating new EntityReactor..."));
        m_entReactor = new ArxRleTransientEntReactor;
    }

		// unfortunately, this structure for making this page know about the main
		// dialog means that we could never use this page within another main dialog
		// container.  So, cast to our known type of owning Main Dialog
	ArxRleUiTdmReactors* tdmReactors = static_cast<ArxRleUiTdmReactors*>(GetMainDialog());
	tdmReactors->attachEntTransientReactor(m_entReactor);
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::detachEntReactors
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::detachEntReactors()
{
		// unfortunately, this structure for making this page know about the main
		// dialog means that we could never use this page within another main dialog
		// container.  So, cast to our known type of owning Main Dialog
	ArxRleUiTdmReactors* tdmReactors = static_cast<ArxRleUiTdmReactors*>(GetMainDialog());
	tdmReactors->detachEntTransientReactor(m_entReactor);
}


/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxCacelled
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxCacelled(const AcDbObject* obj)
{
    if (ArxRleUiTdcTransientReactors::m_doStateCancelled)
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Cancelled"));
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxCopied
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxCopied(const AcDbObject* obj, const AcDbObject* newObject)
{
    if (ArxRleUiTdcTransientReactors::m_doStateCopied) {
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Copied (source object)"));
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Copied (new object)"));
    }
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxErased
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxErased(const AcDbObject* obj, Adesk::Boolean isErasing)
{
    if (ArxRleUiTdcTransientReactors::m_doStateErased) {
        if (isErasing)
            ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Erase"));
        else
            ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Un-erase"));
    }
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxGoodbye
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxGoodbye(const AcDbObject* obj)
{
    if (ArxRleUiTdcTransientReactors::m_doStateGoodbye)
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Goodbye"));
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxOpenedModify
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxOpenedModify(const AcDbObject* obj)
{
    if (ArxRleUiTdcTransientReactors::m_doStateOpenMod)
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Open For Modify"));
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxModified
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxModified(const AcDbObject* obj)
{
    if (ArxRleUiTdcTransientReactors::m_doStateModified)
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Modified"));
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxSubObjModified
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxSubObjModified(const AcDbObject* obj, const AcDbObject* subObj)
{
    if (ArxRleUiTdcTransientReactors::m_doStateSubObjMod) {
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("SubObject Modified (main object)"));
        ArxRleUiTdcTransientReactors::doStateDbox(subObj, _T("SubObject Modified (sub-object)"));
    }
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxModifyUndone
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxModifyUndone(const AcDbObject* obj)
{
    if (ArxRleUiTdcTransientReactors::m_doStateModUndone)
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Modify Undone"));
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxModifiedXdata
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxModifiedXdata(const AcDbObject* obj)
{
    if (ArxRleUiTdcTransientReactors::m_doStateModXdata)
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Modified Xdata"));
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxModifiedGraphics
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxModifiedGraphics(const AcDbObject* obj)
{
    if (ArxRleUiTdcTransientReactors::m_doStateModGraphics)
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Modified Graphics"));
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxUnappended
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxUnappended(const AcDbObject* obj)
{
    if (ArxRleUiTdcTransientReactors::m_doStateUnappended)
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Un-appended"));
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxReappended
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxReappended(const AcDbObject* obj)
{
    if (ArxRleUiTdcTransientReactors::m_doStateReappended)
        ArxRleUiTdcTransientReactors::doStateDbox(obj, _T("Re-appended"));
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::doStateDboxClosed
**
**  **jma
**
*************************************/

void
ArxRleUiTdcTransientReactors::doStateDboxClosed(const AcDbObjectId& objId)
{
    if (ArxRleUiTdcTransientReactors::m_doStateClosed)
        ArxRleUiTdcTransientReactors::doStateDbox(objId, _T("Object Closed"));
}




