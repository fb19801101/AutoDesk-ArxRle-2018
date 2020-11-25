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

#include "ArxRleUiTdcLongTrans.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRleUiDlgDxf.h"
#include "ArxRleUiTdmDatabase.h"
#include "ArxRleUiDlgReactors.h"
#include "ArxRleUiDlgXdata.h"
#include "ArxRleUiTdmEditor.h"
#include "ArxRleUiTdmIdMap.h"
#include "Filer/ArxRleReferenceFiler.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  ArxRleUiTdcLongTrans::ArxRleUiTdcLongTrans
**
**  **jma
**
*************************************/

ArxRleUiTdcLongTrans::ArxRleUiTdcLongTrans(AcDbLongTransaction* lt)
:	m_longTrans(lt)
{
    //{{AFX_DATA_INIT(ArxRleUiTdcLongTrans)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcLongTrans::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiTdcDbObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcLongTrans)
	DDX_Control(pDX, ARXRLE_LONG_TRANS_LC_VALUES, m_dataList);
	DDX_Control(pDX, ARXRLE_LONG_TRANS_TR_OBJS, m_tblTree);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcLongTrans message map

BEGIN_MESSAGE_MAP(ArxRleUiTdcLongTrans, ArxRleUiTdcDbObjectBase)
    //{{AFX_MSG_MAP(ArxRleUiTdcLongTrans)
	ON_NOTIFY(TVN_SELCHANGED, ARXRLE_LONG_TRANS_TR_OBJS, OnSelchangedSymtabs)
	ON_BN_CLICKED(ARXRLE_LONG_TRANS_BN_DATABASE, OnDatabase)
	ON_BN_CLICKED(ARXRLE_LONG_TRANS_BN_IDMAP, OnShowIdMap)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcLongTrans message handlers

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcLongTrans::OnInitDialog() 
{
    ArxRleUiTdcDbObjectBase::OnInitDialog();

    HTREEITEM treeItem;

    treeItem = addOneTreeItem(_T("Long Transaction"), m_longTrans->objectId(), TVI_ROOT);
    m_tblTree.SelectItem(treeItem);        // make this one the currently selected one

	buildColumns(m_dataList);
    displayCurrent(0);

		// disable IdMap button if there isn't one.
	AcDbIdMapping* idMap = m_longTrans->activeIdMap();
	if (idMap == NULL)
		ArxRleUtils::enableDlgItem(this, ARXRLE_LONG_TRANS_BN_IDMAP, FALSE);
    
    return TRUE; 
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::displayCurrent
**
**  **jma
**
*************************************/

void
ArxRleUiTdcLongTrans::displayCurrent(int index)
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    ASSERT((index >= 0) && (index < m_objIdList.length()));
    m_currentObjId = m_objIdList[index];

	// TBD: index is ignored right now because we only have one item

    CString str;

    setExtensionButtons(m_longTrans);

	display(m_longTrans);

	drawPropsList(m_dataList);
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::OnSelchangedSymtabs
**
**  **jma
**
*************************************/

void
ArxRleUiTdcLongTrans::OnSelchangedSymtabs(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    displayCurrent(static_cast<int>(pNMTreeView->itemNew.lParam));    
    *pResult = 0;
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::addOneTreeItem
**
**  **jma
**
*************************************/

HTREEITEM
ArxRleUiTdcLongTrans::addOneTreeItem(LPCTSTR name, const AcDbObjectId& objId, HTREEITEM parent, bool sort)
{
    m_objIdList.append(objId);    // keep track of the objectId for each entry
    int index = m_objIdList.length() - 1;
    ASSERT(index >= 0);

    TV_ITEM    tvItem;
    TV_INSERTSTRUCT tvInsert;

    tvItem.mask = TVIF_TEXT | TVIF_PARAM;
    tvItem.pszText = const_cast<TCHAR*>(name);
    tvItem.cchTextMax = lstrlen(name);
    tvItem.lParam = (LPARAM)index;        //index of AcDbObjectId
    
    tvInsert.item = tvItem;
    if (sort)
        tvInsert.hInsertAfter = TVI_SORT;
    else
        tvInsert.hInsertAfter = TVI_LAST;
    tvInsert.hParent = parent;

    return m_tblTree.InsertItem(&tvInsert);            
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::OnDxf
**
**  **jma
**
*************************************/

void
ArxRleUiTdcLongTrans::OnDxf() 
{
	Acad::ErrorStatus es = m_longTrans->downgradeOpen();
	if (es == Acad::eOk) {
		ArxRleUiDlgDxf dbox(this, m_longTrans);
		dbox.DoModal();

		es = m_longTrans->upgradeOpen();
		if (es != Acad::eOk)
			ArxRleUtils::rxErrorAlert(es);
	}
	else
		ArxRleUtils::rxErrorAlert(es);
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::OnExtdict
**
**  **jma
**
*************************************/

void
ArxRleUiTdcLongTrans::OnExtdict() 
{
    AcDbObjectId extDictId = m_longTrans->extensionDictionary();

    ArxRleUiTdmDatabase dbox(extDictId, this, _T("Extension Dictionary"));
	dbox.DoModal();
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::OnReactors
**
**  **jma
**
*************************************/

void
ArxRleUiTdcLongTrans::OnReactors() 
{
    ArxRleUiDlgReactors dbox(this, m_longTrans);
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::OnXdata
**
**  **jma
**
*************************************/

void
ArxRleUiTdcLongTrans::OnXdata() 
{
    ArxRleUiDlgXdata dbox(this, m_longTrans);
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::OnDatabase
**
**  **jma
**
*************************************/

void
ArxRleUiTdcLongTrans::OnDatabase() 
{
	AcDbDatabase* db = m_longTrans->database();

	if (db != NULL) {
		ArxRleUiTdmDatabase dbox(db, this, _T("Database For Object"));
		dbox.DoModal();
	}
	else {
		ASSERT(0);	// button should have been disabled!
	}
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::OnDocument
**
**  **jma
**
*************************************/

void
ArxRleUiTdcLongTrans::OnDocument() 
{
	AcDbDatabase* db = m_longTrans->database();

	AcApDocument* doc = acDocManager->document(db);
	if (doc) {
		ArxRleUiTdmEditor dbox(this, doc);
		dbox.DoModal();
	}
	else {
		ASSERT(0);	// this button should have been disabled!
	}
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::getReferencedObjects
**
**  **jma
**
*************************************/

bool
ArxRleUiTdcLongTrans::getReferencedObjects(AcDbObjectIdArray& hardPointerIds,
										   AcDbObjectIdArray& softPointerIds,
										   AcDbObjectIdArray& hardOwnershipIds,
										   AcDbObjectIdArray& softOwnershipIds) 
{
	ArxRleReferenceFiler filer;
	m_longTrans->dwgOut(&filer);

	hardPointerIds = filer.m_hardPointerIds;
	softPointerIds = filer.m_softPointerIds;
	hardOwnershipIds = filer.m_hardOwnershipIds;
	softOwnershipIds = filer.m_softOwnershipIds;

	return true;
}

/****************************************************************************
**
**  ArxRleUiTdcLongTrans::OnShowIdMap
**
**  **jma
**
*************************************/

void
ArxRleUiTdcLongTrans::OnShowIdMap() 
{
	AcDbIdMapping* idMap = m_longTrans->activeIdMap();

	if (idMap) {
		ArxRleUiTdmIdMap dbox(idMap, this);
		dbox.DoModal();
	}
	else {
		ASSERT(0);	// this button should have been disabled!
	}
}


