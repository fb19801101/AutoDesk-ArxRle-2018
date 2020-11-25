//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//  ArxRleUiTdmReactors.cpp
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleUiTdmReactors.h"
#include "ArxRleUiTdcSysReactors.h"
#include "ArxRleUiTdcTransientReactors.h"
#include "ArxRleUiTdcPersistentReactors.h"
#include "ArxRle.h"
#include "ArxRleTransientEntReactor.h"
#include "ArxRlePersistentEntReactor.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleSelSet.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**	ArxRleUiTdmReactors::ArxRleUiTdmReactors
**
**	**jma
**
*************************************/

ArxRleUiTdmReactors::ArxRleUiTdmReactors(CWnd* parent)
:   CAcUiTabMainDialog(ArxRleUiTdmReactors::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
	SetDialogName(_T("ArxRle-Reactors"));

	m_tdcSysReactors = new ArxRleUiTdcSysReactors;
	m_tdcTransientReactors = new ArxRleUiTdcTransientReactors;
	m_tdcPersistentReactors = new ArxRleUiTdcPersistentReactors;

    //{{AFX_DATA_INIT(ArxRleUiTdmReactors)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**	ArxRleUiTdmReactors::~ArxRleUiTdmReactors
**
**	**jma
**
*************************************/

ArxRleUiTdmReactors::~ArxRleUiTdmReactors()
{
	delete m_tdcSysReactors;
	delete m_tdcTransientReactors;
	delete m_tdcPersistentReactors;
}

/****************************************************************************
**
**  ArxRleUiTdmReactors::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdmReactors::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabMainDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdmReactors)
    DDX_Control(pDX, ARXRLE_REACTORS_TAB, m_tabCtrl);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmReactors message map

BEGIN_MESSAGE_MAP(ArxRleUiTdmReactors, CAcUiTabMainDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdmReactors)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdmReactors message handlers

/****************************************************************************
**
**  ArxRleUiTdmReactors::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdmReactors::OnInitDialog() 
{
    CAcUiTabMainDialog::OnInitDialog();

	SetAcadTabPointer(&m_tabCtrl);

	ASSERT(m_tdcSysReactors != NULL);

	AddTab(0, _T("System"), ArxRleUiTdcSysReactors::IDD, m_tdcSysReactors);
	AddTab(1, _T("Transient Obj/Ent"), ArxRleUiTdcTransientReactors::IDD, m_tdcTransientReactors);
	AddTab(2, _T("Persistent Obj/Ent"), ArxRleUiTdcPersistentReactors::IDD, m_tdcPersistentReactors);
    
    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdmReactors::attachEntTransientReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdmReactors::attachEntTransientReactor(ArxRleTransientEntReactor* entReactor)
{
	BeginEditorCommand();

	ArxRleSelSet ss;
	if (ss.userSelect() != ArxRleSelSet::kSelected) {
		CompleteEditorCommand();
		return;
	}

	Acad::ErrorStatus es;
	AcDbEntity* ent;
	long alreadyAttachedCount = 0;

	AcDbObjectIdArray objIds;
	ss.asArray(objIds);

	int len = objIds.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbEntity(ent, objIds[i], AcDb::kForWrite);
		if (es == Acad::eOk) {
			if (entReactor->addToObject(ent) == FALSE)
				alreadyAttachedCount++;
			else {
				CString str;
				acutPrintf(_T("\nAttached to %s"), ArxRleUtils::objToClassAndHandleStr(ent, str));
			}
			ent->close();
		}
		else
			ArxRleUtils::rxErrorMsg(es);
	}

	if (alreadyAttachedCount > 0)
		acutPrintf(_T("\n%ld entities already had the reactor attached."), alreadyAttachedCount);

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiTdmReactors::detachEntTransientReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdmReactors::detachEntTransientReactor(ArxRleTransientEntReactor* entReactor)
{
	BeginEditorCommand();

	ArxRleSelSet ss;
	if (ss.userSelect() != ArxRleSelSet::kSelected) {
		CompleteEditorCommand();
		return;
	}

	Acad::ErrorStatus es;
	AcDbEntity* ent;
	long notAttachedCount = 0;

	AcDbObjectIdArray objIds;
	ss.asArray(objIds);

	int len = objIds.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbEntity(ent, objIds[i], AcDb::kForWrite);
		if (es == Acad::eOk) {
			if (entReactor->delFromObject(ent) == FALSE)
				notAttachedCount++;
			else {
				CString str;
				acutPrintf(_T("\nDetached from %s"), ArxRleUtils::objToClassAndHandleStr(ent, str));
			}
			ent->close();
		}
		else
			ArxRleUtils::rxErrorMsg(es);
	}

	if (notAttachedCount > 0)
		acutPrintf(_T("\n%ld entities did not have the reactor attached."), notAttachedCount);

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiTdmReactors::attachEntPersistentReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdmReactors::attachEntPersistentReactor()
{
	BeginEditorCommand();

	ArxRleSelSet ss;
	if (ss.userSelect() != ArxRleSelSet::kSelected) {
		CompleteEditorCommand();
		return;
	}

	Acad::ErrorStatus es;
	AcDbEntity* ent;
	ArxRlePersistentEntReactor* peReactor;
	long alreadyAttachedCount = 0;

	AcDbObjectIdArray objIds;
	ss.asArray(objIds);

		// find the persistent reactor that goes with this database
	AcDbObjectId persistentId;
	if (objIds.isEmpty() == false)
		persistentId = ArxRleUiTdcPersistentReactors::getPersistentEntReactor(objIds.first().database(), true);

	int len = objIds.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbEntity(ent, objIds[i], AcDb::kForWrite);
		if (es == Acad::eOk) {
			if (hasPersistentReactor(ent, persistentId))
				alreadyAttachedCount++;
			else {
				ent->addPersistentReactor(persistentId);
				CString str;
				acutPrintf(_T("\nAttached to %s"), ArxRleUtils::objToClassAndHandleStr(ent, str));

				es = acdbOpenObject(peReactor, persistentId, AcDb::kForWrite);
				if (es == Acad::eOk) {
					peReactor->attachTo(ent->objectId());
					peReactor->close();
				}
				else {
					acutPrintf(_T("\nERROR: Could not update backward reference in reactor: (%s)"), ArxRleUtils::rxErrorStr(es));
				}
			}

			ent->close();
        }
		else
			ArxRleUtils::rxErrorMsg(es);
	}

	if (alreadyAttachedCount > 0)
		acutPrintf(_T("\n%ld entities already had the reactor attached."), alreadyAttachedCount);

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiTdmReactors::detachEntPersistentReactor
**
**  **jma
**
*************************************/

void
ArxRleUiTdmReactors::detachEntPersistentReactor()
{
	BeginEditorCommand();

	ArxRleSelSet ss;
	if (ss.userSelect() != ArxRleSelSet::kSelected) {
		CompleteEditorCommand();
		return;
	}

	Acad::ErrorStatus es;
	AcDbEntity* ent;
	ArxRlePersistentEntReactor* peReactor;
	long notAttachedCount = 0;

	AcDbObjectIdArray objIds;
	ss.asArray(objIds);

		// find the persistent reactor that goes with this database
	AcDbObjectId persistentId;
	if (objIds.isEmpty() == false)
		persistentId = ArxRleUiTdcPersistentReactors::getPersistentEntReactor(objIds.first().database(), true);

	int len = objIds.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbEntity(ent, objIds[i], AcDb::kForWrite);
		if (es == Acad::eOk) {
			if (!hasPersistentReactor(ent, persistentId))
				notAttachedCount++;
			else {
				ent->removePersistentReactor(persistentId);
				CString str;
				acutPrintf(_T("\nDetached from %s"), ArxRleUtils::objToClassAndHandleStr(ent, str));

				es = acdbOpenObject(peReactor, persistentId, AcDb::kForWrite);
				if (es == Acad::eOk) {
					peReactor->detachFrom(ent->objectId());
					peReactor->close();
				}
				else {
					acutPrintf(_T("\nERROR: Could not update backward reference in reactor: (%s)"), ArxRleUtils::rxErrorStr(es));
				}
			}

			ent->close();
        }
		else
			ArxRleUtils::rxErrorMsg(es);
	}

	if (notAttachedCount > 0)
		acutPrintf(_T("\n%ld entities did not have the reactor attached."), notAttachedCount);

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiTdmReactors::hasPersistentReactor
**
**  **jma
**
*************************************/

bool
ArxRleUiTdmReactors::hasPersistentReactor(AcDbObject* obj, const AcDbObjectId& reactorId)
{
	void* pSomething;

    const AcDbVoidPtrArray* reactors = obj->reactors();
    if (reactors != nullptr) {
        for (int i=0; i<reactors->length(); i++) {
            pSomething = reactors->at(i);
			if (acdbPersistentReactorObjectId(pSomething) == reactorId)
                return true;
        }
    }
    return false;
}

/****************************************************************************
**
**  ArxRleUiTdmReactors::cleanUpReactors
**		static function to allow app to clean up global pointers to reactors
**
**  **jma
**
*************************************/

void
ArxRleUiTdmReactors::cleanUpReactors() 
{
	ArxRleUiTdcSysReactors::cleanUpReactors();
	ArxRleUiTdcTransientReactors::cleanUpReactors();
}

