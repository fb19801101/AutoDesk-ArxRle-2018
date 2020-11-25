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

#include "ArxRleUiTdcEntities.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleUtilsGe.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  ArxRleUiTdcEntities::ArxRleUiTdcEntities
**
**  **jma
**
*************************************/

ArxRleUiTdcEntities::ArxRleUiTdcEntities(const AcDbObjectIdArray& objList, bool isBlkDef)
:   m_origEnts(objList),
    m_isBlkDef(isBlkDef)
{
    //{{AFX_DATA_INIT(ArxRleUiTdcEntities)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcEntities::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcEntities::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiTdcDbObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcEntities)
	DDX_Control(pDX, ARXRLE_ENTS_EB_ERASE_STATUS, m_txtErased);
	DDX_Control(pDX, ARXRLE_ENTS_LC_DATA, m_dataList);
	DDX_Control(pDX, ARXRLE_ENTS_TR_ENTS, m_entTree);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcEntities message map

BEGIN_MESSAGE_MAP(ArxRleUiTdcEntities, ArxRleUiTdcDbObjectBase)
    //{{AFX_MSG_MAP(ArxRleUiTdcEntities)
	ON_NOTIFY(TVN_SELCHANGED, ARXRLE_ENTS_TR_ENTS, OnSelchangedEnts)
	ON_BN_CLICKED(ARXRLE_ENTS_BN_DATABASE, OnDatabase)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcEntities message handlers

/****************************************************************************
**
**  ArxRleUiTdcEntities::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcEntities::OnInitDialog() 
{
    ArxRleUiTdcDbObjectBase::OnInitDialog();

	AcDbEntity* ent;
	Acad::ErrorStatus es;
    HTREEITEM treeItem;
	CString str;

	int len = m_origEnts.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbEntity(ent, m_origEnts[i], AcDb::kForRead, true);		// might have passed in erased ones
		if (es == Acad::eOk) {
			treeItem = addOneTreeItem(ArxRleUtils::objToClassAndHandleStr(ent, str), ent, TVI_ROOT);
			if (treeItem != NULL) {
				addSubentitiesToTree(ent, treeItem);
				if (i == 0)
					m_entTree.SelectItem(treeItem);		// make first one selected
			}
			ent->close();
		}
	}

    buildColumns(m_dataList);
    displayCurrent(0);

    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcEntities::OnSelchangedEnts
**
**  **jma
**
*************************************/

void
ArxRleUiTdcEntities::OnSelchangedEnts(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    displayCurrent(static_cast<int>(pNMTreeView->itemNew.lParam));    
    *pResult = 0;
}

/****************************************************************************
**
**  ArxRleUiTdcEntities::addOneTreeItem
**
**  **jma
**
*************************************/

HTREEITEM
ArxRleUiTdcEntities::addOneTreeItem(LPCTSTR name, const AcDbObject* obj, HTREEITEM parent, bool sort)
{
    m_treeObjIdList.append(obj->objectId());    // keep track of the objectId for each entry
    int index = m_treeObjIdList.length() - 1;
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

    return m_entTree.InsertItem(&tvInsert);            
}

/****************************************************************************
**
**  ArxRleUiTdcEntities::addSubentitiesToTree
**
**  **jma
**
*************************************/

void
ArxRleUiTdcEntities::addSubentitiesToTree(const AcDbEntity* mainEnt, HTREEITEM parent)
{
	AcDbObjectIdArray subEnts;

    AcDbBlockReference* blkRef;
	
	if ((blkRef = AcDbBlockReference::cast(mainEnt)) != NULL) {
		collectAttributes(blkRef, subEnts);
	}
	else if ((mainEnt->isKindOf(AcDbPolyFaceMesh::desc())) ||
			 (mainEnt->isKindOf(AcDbPolygonMesh::desc())) ||
			 (mainEnt->isKindOf(AcDb2dPolyline::desc())) ||
			 (mainEnt->isKindOf(AcDb3dPolyline::desc()))) {
		collectVertices(mainEnt, subEnts);
	}

	AcDbObject* tmpObj;
	HTREEITEM treeItem;
	Acad::ErrorStatus es;
	CString str;

	int len = subEnts.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbObject(tmpObj, subEnts[i], AcDb::kForRead, true);		// might have passed in erased ones
		if (es == Acad::eOk) {
			treeItem = addOneTreeItem(ArxRleUtils::objToClassAndHandleStr(tmpObj, str), tmpObj, parent);
			tmpObj->close();
		}
		else
			ArxRleUtils::rxErrorMsg(es);
	}
}

/****************************************************************************
**
**  ArxRleUiTdcEntities::displayCurrent
**
**  **jma
**
*************************************/

void
ArxRleUiTdcEntities::displayCurrent(int index)
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    ASSERT((index >= 0) && (index < m_treeObjIdList.length()));
    m_currentObjId = m_treeObjIdList[index];

    CString str;

    AcDbObject* obj = NULL;
    Acad::ErrorStatus es = acdbOpenObject(obj, m_currentObjId, AcDb::kForRead, true);	// might want to show erased
    setExtensionButtons(obj);

    if (es == Acad::eOk) {
		display(obj);

		    // hide or show the erased entity message
		if (obj->isErased())
			m_txtErased.ShowWindow(SW_SHOW);
		else
			m_txtErased.ShowWindow(SW_HIDE);

        obj->close();
    }

	drawPropsList(m_dataList);
}

/****************************************************************************
**
**  ArxRleUiTdcEntities::collectAttributes
**
**  **jma
**
*************************************/

void
ArxRleUiTdcEntities::collectAttributes(const AcDbBlockReference* blkRef, AcDbObjectIdArray& subEnts)
{
	ASSERT(blkRef != NULL);

    AcDbObjectIterator* attribIter = blkRef->attributeIterator();
    if (attribIter != NULL) {
        while (attribIter->done() == false) {
            subEnts.append(attribIter->objectId());
            attribIter->step();
        }
        delete attribIter;
    }
}

/****************************************************************************
**
**  ArxRleUiTdcEntities::collectVertices
**
**  **jma
**
*************************************/

void
ArxRleUiTdcEntities::collectVertices(const AcDbEntity* ent, AcDbObjectIdArray& subEnts)
{
    AcDb2dPolyline* pline2d;
    AcDb3dPolyline* pline3d;
    AcDbPolygonMesh* pmesh;
    AcDbPolyFaceMesh* pface;

    AcDbObjectIterator* vertexIter;

    if ((pline2d = AcDb2dPolyline::cast(ent)) != NULL)
        vertexIter = pline2d->vertexIterator();
    else if ((pline3d = AcDb3dPolyline::cast(ent)) != NULL)
        vertexIter = pline3d->vertexIterator();
    else if ((pmesh = AcDbPolygonMesh::cast(ent)) != NULL)
        vertexIter = pmesh->vertexIterator();
    else if ((pface = AcDbPolyFaceMesh::cast(ent)) != NULL)
        vertexIter = pface->vertexIterator();
    else
        vertexIter = NULL;

	if (vertexIter == NULL) {
		ASSERT(0);
		return;
	}

    while (vertexIter->done() == false) {
		subEnts.append(vertexIter->objectId());
        vertexIter->step();
    }

    delete vertexIter;
}

