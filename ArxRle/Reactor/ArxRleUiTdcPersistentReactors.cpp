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

#include "ArxRleUiTdcPersistentReactors.h"
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
BOOL    ArxRleUiTdcPersistentReactors::m_doStateModified = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateCancelled = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateErased = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateCopied = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateGoodbye = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateOpenMod = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateSubObjMod = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateModUndone = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateModXdata = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateModGraphics = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateUnappended = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateReappended = FALSE;
BOOL    ArxRleUiTdcPersistentReactors::m_doStateClosed = FALSE;


// These statics are all MDI aware
ArxRlePersistentObjReactor*	ArxRleUiTdcPersistentReactors::m_objReactor = nullptr;
ArxRlePersistentEntReactor*	ArxRleUiTdcPersistentReactors::m_entReactor = nullptr;

    // names of our dictionaries for reactor storage
LPCTSTR ArxRleUiTdcPersistentReactors::m_dictName = _T("ARXRLE_PERSISTENT_REACTORS");


/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::ArxRleUiTdcPersistentReactors
**
**  **jma
**
*************************************/

ArxRleUiTdcPersistentReactors::ArxRleUiTdcPersistentReactors()
:   ArxRleUiTdcObjReactorsBase()
{
    //{{AFX_DATA_INIT(ArxRleUiTdcPersistentReactors)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiTdcObjReactorsBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcPersistentReactors)
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
// ArxRleUiTdcPersistentReactors message handlers

BEGIN_MESSAGE_MAP(ArxRleUiTdcPersistentReactors, ArxRleUiTdcObjReactorsBase)
    //{{AFX_MSG_MAP(ArxRleUiTdcPersistentReactors)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcPersistentReactors message handlers


/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcPersistentReactors::OnInitDialog() 
{
	ArxRleUiTdcObjReactorsBase::OnInitDialog();

	return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::getPersistentObjReactor
**
**  **jma
**
*************************************/

AcDbObjectId
ArxRleUiTdcPersistentReactors::getPersistentObjReactor(AcDbDatabase* db, bool createIfNotFound)
{
	static LPCTSTR dictEntryName = _T("ARXRLE_PERSISTENT_OBJ_REACTOR");

	AcDbObjectId prId;
    AcDbDictionary* prDict;

		// first see if its already there without "disturbing" anyone by opening them
		// for write.
    prDict = ArxRleUtils::openDictionaryForRead(m_dictName, db);
    if (prDict != nullptr) {
		if (prDict->getAt(dictEntryName, prId) == Acad::eOk) {
			prDict->close();
			return prId;
		}
		prDict->close();
	}

		// couldn't find it, bail if we aren't supposed to create it.
	if (createIfNotFound == false)
		return AcDbObjectId::kNull;

		// not here yet, so make an entry
    prDict = ArxRleUtils::openDictionaryForWrite(m_dictName, true, db);
    if (prDict == nullptr)
        return AcDbObjectId::kNull;

    Acad::ErrorStatus es;
    ArxRlePersistentObjReactor* pr = new ArxRlePersistentObjReactor;

    es = prDict->setAt(dictEntryName, pr, prId);
    if (es != Acad::eOk) {
        ArxRleUtils::rxErrorMsg(es);
        ArxRleUtils::alertBox(_T("ERROR: Could not add entry to dictionary."));
        delete pr;

		prDict->close();
		return AcDbObjectId::kNull;
    }
    else {
		pr->close();
		prDict->close();
		return prId;
    }
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::getPersistentEntReactor
**
**  **jma
**
*************************************/

AcDbObjectId
ArxRleUiTdcPersistentReactors::getPersistentEntReactor(AcDbDatabase* db, bool createIfNotFound)
{
	static LPCTSTR dictEntryName = _T("ARXRLE_PERSISTENT_ENT_REACTOR");

	AcDbObjectId prId;
    AcDbDictionary* prDict;

		// first see if its already there without "disturbing" anyone by opening them
		// for write.
    prDict = ArxRleUtils::openDictionaryForRead(m_dictName, db);
    if (prDict != nullptr) {
		if (prDict->getAt(dictEntryName, prId) == Acad::eOk) {
			prDict->close();
			return prId;
		}
		prDict->close();
	}

		// couldn't find it, bail if we aren't supposed to create it.
	if (createIfNotFound == false)
		return AcDbObjectId::kNull;

		// not here yet, so make an entry
    prDict = ArxRleUtils::openDictionaryForWrite(m_dictName, true, db);
    if (prDict == nullptr)
        return AcDbObjectId::kNull;

    Acad::ErrorStatus es;
    ArxRlePersistentEntReactor* pr = new ArxRlePersistentEntReactor;

    es = prDict->setAt(dictEntryName, pr, prId);
    if (es != Acad::eOk) {
        ArxRleUtils::rxErrorMsg(es);
        ArxRleUtils::alertBox(_T("ERROR: Could not add entry to dictionary."));
        delete pr;

		prDict->close();
		return AcDbObjectId::kNull;
    }
    else {
		pr->close();
		prDict->close();
		return prId;
    }
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::getAttachedObjects
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::getAttachedObjects(AcDbObjectIdArray& objIds)
{
    auto dbPtrs = acdbActiveDatabaseArray();

    ArxRlePersistentObjReactor* peReactor;
    Acad::ErrorStatus es;
    AcDbObjectIdArray tmpIds;

    for (auto&& pDb : dbPtrs) {
        const AcDbObjectId prId = getPersistentObjReactor(pDb, false);

		es = acdbOpenObject(peReactor, prId, AcDb::kForRead);
		if (es == Acad::eOk) {
			tmpIds.setLogicalLength(0);	// reusing array for each database

			peReactor->getAttachedToObjs(tmpIds);
			peReactor->close();

			objIds.append(tmpIds);
		}
	}
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::getAttachedEntities
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::getAttachedEntities(AcDbObjectIdArray& objIds)
{
    auto dbPtrs = acdbActiveDatabaseArray();

    ArxRlePersistentEntReactor* peReactor;
    Acad::ErrorStatus es;
    AcDbObjectIdArray tmpIds;

    for (auto&& pDb : dbPtrs) {
        const AcDbObjectId prId = getPersistentEntReactor(pDb, false);

        es = acdbOpenObject(peReactor, prId, AcDb::kForRead);
        if (es == Acad::eOk) {
            tmpIds.setLogicalLength(0);	// reusing array for each database

            peReactor->getAttachedToObjs(tmpIds);
            peReactor->close();

            objIds.append(tmpIds);
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::detachSelectedEnts
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::detachSelectedEnts(const AcDbObjectIdArray& objIds) 
{
	Acad::ErrorStatus es;
	ArxRlePersistentEntReactor* peReactor;

	ArxRleDocLockWrite docLock;	// these potentially came from other documents

    for (AcDbObjectId id : objIds) {
        es = docLock.lock(id.database());   // lock the document associated with this database
        if (es == Acad::eOk) {
            AcDbEntity* ent;
            es = acdbOpenAcDbEntity(ent, id, AcDb::kForWrite, true);
            if (es == Acad::eOk) {
                const AcDbObjectId prId = getPersistentEntReactor(id.database(), true);

				ent->removePersistentReactor(prId);

				es = acdbOpenObject(peReactor, prId, AcDb::kForWrite);
				if (es == Acad::eOk) {
					peReactor->detachFrom(ent->objectId());
					peReactor->close();
				}
				else {
					CString str;
					str.Format(_T("ERROR: Could not update backward reference in reactor: (%s)"), ArxRleUtils::rxErrorStr(es));
					ArxRleUtils::stopAlertBox(str);
				}

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

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::detachSelectedObjs
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::detachSelectedObjs(const AcDbObjectIdArray& objIds) 
{
	Acad::ErrorStatus es;
	AcDbEntity* ent;
	ArxRlePersistentObjReactor* peReactor;

	ArxRleDocLockWrite docLock;	// these potentially came from other documents

    for (AcDbObjectId id : objIds) {
        es = docLock.lock(id.database());   // lock the document associated with this database
        if (es == Acad::eOk) {
            es = acdbOpenAcDbEntity(ent, id, AcDb::kForWrite, true);
            if (es == Acad::eOk) {
                const AcDbObjectId prId = getPersistentObjReactor(id.database(), true);

				ent->removePersistentReactor(prId);

				es = acdbOpenObject(peReactor, prId, AcDb::kForWrite);
				if (es == Acad::eOk) {
					peReactor->detachFrom(ent->objectId());
					peReactor->close();
				}
				else {
					CString str;
					str.Format(_T("ERROR: Could not update backward reference in reactor: (%s)"), ArxRleUtils::rxErrorStr(es));
					ArxRleUtils::stopAlertBox(str);
				}

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

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::attachObjReactors
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::attachObjReactors(const AcDbObjectIdArray& objIds)
{
	Acad::ErrorStatus es;
	AcDbObject* obj;
	ArxRlePersistentObjReactor* peReactor;

	ArxRleDocLockWrite docLock;	// these potentially came from other documents

    for (AcDbObjectId id : objIds) {
        es = docLock.lock(id.database());   // lock the document associated with this database
        if (es == Acad::eOk) {
            es = acdbOpenAcDbObject(obj, id, AcDb::kForWrite, true);
            if (es == Acad::eOk) {
                const AcDbObjectId prId = getPersistentObjReactor(id.database(), true);

				if (ArxRleUiTdmReactors::hasPersistentReactor(obj, prId)) {
					ArxRleUtils::alertBox(_T("That object already has the reactor attached."));
				}
				else {
					obj->addPersistentReactor(prId);

					es = acdbOpenObject(peReactor, prId, AcDb::kForWrite);
					if (es == Acad::eOk) {
						peReactor->attachTo(obj->objectId());
						peReactor->close();
					}
					else {
						CString str;
						str.Format(_T("ERROR: Could not update backward reference in reactor: (%s)"), ArxRleUtils::rxErrorStr(es));
						ArxRleUtils::stopAlertBox(str);
					}
				}

				obj->close();
			}
			else {
				ArxRleUtils::rxErrorMsg(es);
			}
		}
		else {
			ArxRleUtils::rxErrorAlert(es);
		}
	}
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::attachEntReactors
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::attachEntReactors()
{
		// unfortunately, this structure for making this page know about the main
		// dialog means that we could never use this page within another main dialog
		// container.  Oh well...
	ArxRleUiTdmReactors* tdmReactors = static_cast<ArxRleUiTdmReactors*>(GetMainDialog());
	tdmReactors->attachEntPersistentReactor();
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::detachEntReactors
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::detachEntReactors()
{
		// unfortunately, this structure for making this page know about the main
		// dialog means that we could never use this page within another main dialog
		// container.  Oh well...
	ArxRleUiTdmReactors* tdmReactors = static_cast<ArxRleUiTdmReactors*>(GetMainDialog());
	tdmReactors->detachEntPersistentReactor();
}


/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxCacelled
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxCacelled(const AcDbObject* obj)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateCancelled)
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Cancelled"));
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxCopied
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxCopied(const AcDbObject* obj, const AcDbObject* newObject)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateCopied) {
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Copied (source object)"));
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Copied (new object)"));
    }
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxErased
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxErased(const AcDbObject* obj, Adesk::Boolean isErasing)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateErased) {
        if (isErasing)
            ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Erase"));
        else
            ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Un-erase"));
    }
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxGoodbye
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxGoodbye(const AcDbObject* obj)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateGoodbye)
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Goodbye"));
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxOpenedModify
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxOpenedModify(const AcDbObject* obj)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateOpenMod)
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Open For Modify"));
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxModified
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxModified(const AcDbObject* obj)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateModified)
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Modified"));
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxSubObjModified
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxSubObjModified(const AcDbObject* obj, const AcDbObject* subObj)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateSubObjMod) {
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("SubObject Modified (main object)"));
        ArxRleUiTdcPersistentReactors::doStateDbox(subObj, _T("SubObject Modified (sub-object)"));
    }
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxModifyUndone
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxModifyUndone(const AcDbObject* obj)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateModUndone)
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Modify Undone"));
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxModifiedXdata
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxModifiedXdata(const AcDbObject* obj)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateModXdata)
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Modified Xdata"));
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxModifiedGraphics
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxModifiedGraphics(const AcDbObject* obj)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateModGraphics)
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Modified Graphics"));
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxUnappended
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxUnappended(const AcDbObject* obj)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateUnappended)
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Un-appended"));
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxReappended
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxReappended(const AcDbObject* obj)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateReappended)
        ArxRleUiTdcPersistentReactors::doStateDbox(obj, _T("Re-appended"));
}

/****************************************************************************
**
**  ArxRleUiTdcPersistentReactors::doStateDboxClosed
**
**  **jma
**
*************************************/

void
ArxRleUiTdcPersistentReactors::doStateDboxClosed(const AcDbObjectId& objId)
{
    if (ArxRleUiTdcPersistentReactors::m_doStateClosed)
        ArxRleUiTdcPersistentReactors::doStateDbox(objId, _T("Object Closed"));
}




