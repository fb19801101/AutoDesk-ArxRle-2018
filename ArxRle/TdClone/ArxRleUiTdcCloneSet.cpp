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

#include "ArxRleUiTdcCloneSet.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"
#include "Reactor/ArxRleAppEditorReactor.h"
#include "Snoop/ArxRleUiTdmObjects.h"
#include "Snoop/ArxRleUiTdmDatabase.h"
#include "ArxRleUiTdmTransDbClones.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  ArxRleUiTdcCloneSet::ArxRleUiTdcCloneSet
**
**  **jma
**
*************************************/

ArxRleUiTdcCloneSet::ArxRleUiTdcCloneSet()
:   CAcUiTabChildDialog(NULL, ArxRleApp::getApp()->dllInstance()),
	m_cloneSet(ArxRleAppEditorReactor::getInstance()->cloneSet())
{
    //{{AFX_DATA_INIT(ArxRleUiTdcCloneSet)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcCloneSet::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCloneSet::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabChildDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcCloneSet)
	DDX_Control(pDX, ARXRLE_CLONESET_BN_SELECT, m_selectButton);
	DDX_Control(pDX, ARXRLE_CLONESET_LB_OBJECTS, m_lbObjList);
	DDX_Control(pDX, ARXRLE_CLONESET_LB_DATABASES, m_lbDbList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcCloneSet message handlers

BEGIN_MESSAGE_MAP(ArxRleUiTdcCloneSet, CAcUiTabChildDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdcCloneSet)
	ON_BN_CLICKED(ARXRLE_CLONESET_BN_OBJ_SHOW, OnShow)
	ON_BN_CLICKED(ARXRLE_CLONESET_BN_OBJ_BROWSE, OnBrowse)
	ON_BN_CLICKED(ARXRLE_CLONESET_BN_OBJ_REMOVE, OnRemove)
	ON_BN_CLICKED(ARXRLE_CLONESET_BN_OBJ_REMOVEALL, OnRemoveAll)
	ON_BN_CLICKED(ARXRLE_CLONESET_BN_SELECT, OnSelect)
	ON_LBN_SELCHANGE(ARXRLE_CLONESET_LB_OBJECTS, OnObjectsChanged)
	ON_LBN_SELCHANGE(ARXRLE_CLONESET_LB_DATABASES, OnDatabaseChanged)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcCloneSet message handlers


/****************************************************************************
**
**  ArxRleUiTdcCloneSet::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcCloneSet::OnInitDialog() 
{
	CAcUiTabChildDialog::OnInitDialog();

    m_selectButton.AutoLoad();

	displayDbList();

	m_lbDbList.SetCurSel(getIndexFor(acdbHostApplicationServices()->workingDatabase()));

	displayObjList();

	return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcCloneSet::displayObjList
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCloneSet::displayObjList() 
{
	m_objIds.setLogicalLength(0);
	m_lbObjList.ResetContent();

	int index = m_lbDbList.GetCurSel();
	if (index == LB_ERR) {
		ASSERT(0);
		return;
	}

	AcDbDatabase* curDb = static_cast<AcDbDatabase*>(m_dbPtrs[index]);
	m_cloneSet.getObjectsForDatabase(curDb, m_objIds);

	CString str;
	Acad::ErrorStatus es;
	AcDbObject* obj;

    int len = m_objIds.length();
    for (int i=0; i<len; i++) {
		es = acdbOpenAcDbObject(obj, m_objIds[i], AcDb::kForRead, true);
		if (es == Acad::eOk) {
			ArxRleUtils::objToClassAndHandleStr(obj, str);
			if (obj->isErased())
				str += _T("  (erased)");

			m_lbObjList.AddString(str);

			obj->close();
		}
    }

	m_lbObjList.SetCurSel(-1);

	setButtonModes();
}

/****************************************************************************
**
**  ArxRleUiTdcCloneSet::displayDbList
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCloneSet::displayDbList() 
{
	m_dbPtrs.setLogicalLength(0);
	m_lbDbList.ResetContent();

	m_cloneSet.getAllDatabases(m_dbPtrs);

	CString str;
	AcDbDatabase* tmpDb;

    int len = m_dbPtrs.length();
    for (int i=0; i<len; i++) {
		tmpDb = static_cast<AcDbDatabase*>(m_dbPtrs[i]);
		m_lbDbList.AddString(ArxRleUtils::dbToStr(tmpDb, str));
    }
}

/****************************************************************************
**
**  ArxRleUiTdcCloneSet::OnObjectsChanged
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCloneSet::OnObjectsChanged() 
{
	setButtonModes();
}

/****************************************************************************
**
**  ArxRleUiTdcCloneSet::OnDatabaseChanged
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCloneSet::OnDatabaseChanged() 
{
	displayObjList();
}

/****************************************************************************
**
**  ArxRleUiTdcCloneSet::setButtonModes
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCloneSet::setButtonModes()
{
    int count = m_lbObjList.GetSelCount();

	ArxRleUtils::enableDlgItem(this, ARXRLE_CLONESET_BN_OBJ_SHOW, (m_objIds.isEmpty() == false));
	ArxRleUtils::enableDlgItem(this, ARXRLE_CLONESET_BN_OBJ_REMOVE, (count > 0));
	ArxRleUtils::enableDlgItem(this, ARXRLE_CLONESET_BN_OBJ_REMOVEALL, (m_objIds.isEmpty() == false));
}

/****************************************************************************
**
**  ArxRleUiTdcCloneSet::OnShow
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCloneSet::OnShow() 
{
	ArxRleUiTdmObjects dbox(m_objIds, this, _T("Objects in Clone Set"));
	dbox.DoModal();

	displayObjList();
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::OnBrowse
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCloneSet::OnBrowse()
{
	int index = m_lbDbList.GetCurSel();
	if (index == LB_ERR) {
		ASSERT(0);
		return;
	}

	AcDbDatabase* curDb = static_cast<AcDbDatabase*>(m_dbPtrs[index]);

	ArxRleUiTdmDatabase dbox(curDb, this);
	dbox.DoModal();

	displayObjList();
}

/****************************************************************************
**
**  ArxRleUiTdcCloneSet::OnRemove
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCloneSet::OnRemove()
{
	AcDbObjectIdArray selObjIds;

    int count = m_lbObjList.GetSelCount();
    if (count > 0) {
        int* intArray = new int[count];
        if (m_lbObjList.GetSelItems(count, intArray) != LB_ERR) {
            for (int i=0; i<count; i++) {
                selObjIds.append(m_objIds[intArray[i]]);
            }
        }
        delete [] intArray;
	}

	m_cloneSet.removeObjects(selObjIds);
	displayObjList();
}

/****************************************************************************
**
**  ArxRleUiTdcCloneSet::OnRemoveAll
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCloneSet::OnRemoveAll() 
{
	int index = m_lbDbList.GetCurSel();
	if (index == LB_ERR) {
		ASSERT(0);
		return;
	}

	AcDbDatabase* curDb = static_cast<AcDbDatabase*>(m_dbPtrs[index]);
	m_cloneSet.removeAll(curDb);

	displayObjList();
}

/****************************************************************************
**
**  ArxRleUiTdcCloneSet::OnSelect
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCloneSet::OnSelect() 
{
		// unfortunately, this structure for making this page know about the main
		// dialog means that we could never use this page within another main dialog
		// container.  So, we have to cast to the known type of our owning main dialog
	ArxRleUiTdmTransDbClones* tdmClones = static_cast<ArxRleUiTdmTransDbClones*>(GetMainDialog());
	tdmClones->addToCloneSet(m_cloneSet);

		// we want them to see the changes they just made, but the list that was current
		// might not have been from the database they just deal with, so find the current
		// database and make it show up as current in the list.
	m_lbDbList.SetCurSel(getIndexFor(acdbHostApplicationServices()->workingDatabase()));

	OnDatabaseChanged();
}

/****************************************************************************
**
**  ArxRleUiTdcCloneSet::getIndexFor
**
**  **jma
**
*************************************/

int
ArxRleUiTdcCloneSet::getIndexFor(AcDbDatabase* db) 
{
	AcDbDatabase* tmpDb = NULL;
	int len = m_dbPtrs.length();
	for (int i=0; i<len; i++) {
		tmpDb = static_cast<AcDbDatabase*>(m_dbPtrs[i]);
		if (tmpDb == db)
			return i;
	}

	ASSERT(0);
	return 0;
}
