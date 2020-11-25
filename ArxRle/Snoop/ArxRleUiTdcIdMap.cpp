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

#include "ArxRleUiTdcIdMap.h"
#include "AcadUtils/ArxRleUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiTdcIdMap::ArxRleUiTdcIdMap
**
**  **jma
**
*************************************/

ArxRleUiTdcIdMap::ArxRleUiTdcIdMap(AcDbIdMapping* idMap)
:   m_idMap(idMap)
{
    //{{AFX_DATA_INIT(ArxRleUiTdcIdMap)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcIdMap::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcIdMap::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiTdcRxObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcIdMap)
	DDX_Control(pDX, ARXRLE_IDMAP_LC_VALUES, m_dataList);
	DDX_Control(pDX, ARXRLE_IDMAP_LC_MAPVALUES, m_lcObjList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcIdMap message map

BEGIN_MESSAGE_MAP(ArxRleUiTdcIdMap, ArxRleUiTdcRxObjectBase)
    //{{AFX_MSG_MAP(ArxRleUiTdcIdMap)
    //ON_LBN_SELCHANGE(ARXRLE_LC_MAPVALUES, OnSelchangedObjs)
    //ON_BN_CLICKED(ARXRLE_BN_DATABASE, OnDatabase)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcIdMap message handlers

/****************************************************************************
**
**  ArxRleUiTdcIdMap::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcIdMap::OnInitDialog() 
{
    ArxRleUiTdcRxObjectBase::OnInitDialog();

    buildColumns(m_dataList);
    displayCurrent();

	buildMapItemColumns();
	displayMapItems();

    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcIdMap::OnMainDialogOK
**
**  **jma
**
*************************************/

void
ArxRleUiTdcIdMap::OnMainDialogOK()
{
	GetMainDialog()->SaveColumnSizes(&m_lcObjList);

    ArxRleUiTdcRxObjectBase::OnMainDialogOK();
}

/****************************************************************************
**
**  ArxRleUiTdcIdMap::displayCurrent
**
**  **jma
**
*************************************/

void
ArxRleUiTdcIdMap::displayCurrent()
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

	CString str;
	Acad::ErrorStatus es;
	AcDbDatabase* destDb = NULL;
	AcDbDatabase* origDb = NULL;
	
	es = m_idMap->destDb(destDb);
	if (es == Acad::eOk)
		ArxRleUtils::dbToStr(destDb, str);
	else
		str = ArxRleUtils::rxErrorStr(es);

	addToDataList(_T("Destination Database"), str);

	es = m_idMap->origDb(origDb);
	if (es == Acad::eOk)
		ArxRleUtils::dbToStr(origDb, str);
	else
		str = ArxRleUtils::rxErrorStr(es);

	addToDataList(_T("Original Database"), str);

	addToDataList(_T("Deep Clone Context"), ArxRleUtils::deepCloneContextToStr(m_idMap->deepCloneContext(), str));
	addToDataList(_T("Duplicate Record Cloning"), ArxRleUtils::mergeStyleToStr(m_idMap->duplicateRecordCloning(), str));

	drawPropsList(m_dataList);
}

/****************************************************************************
**
**  ArxRleUiTdcIdMap::displayMapItems
**
**  **jma
**
*************************************/

void
ArxRleUiTdcIdMap::displayMapItems()
{
	this->LockWindowUpdate();		// suppress redraw events

    m_lcObjList.DeleteAllItems();		// remove any existing items from the control
	m_objIds.setLogicalLength(0);

        // build up the list view control
    LV_ITEM lvi;
    lvi.mask = 0;
    int row = 0;

    AcDbObject* obj;
    Acad::ErrorStatus es;

	CString str;

    AcDbIdPair idPair;
    AcDbIdMappingIter mapIter(*m_idMap);
    for (mapIter.start(); !mapIter.done(); mapIter.next()) {
        if (mapIter.getMap(idPair)) {
			m_objIds.append(idPair.key());	// record this in case we later add ability to open and inspect

			lvi.iItem = row;
			lvi.iSubItem = 0;
			m_lcObjList.InsertItem(&lvi);

            es = acdbOpenObject(obj, idPair.value(), AcDb::kForRead);
            if (es == Acad::eOk) {
				m_lcObjList.SetItemText(row, 0, ArxRleUtils::objToClassStr(obj));
				m_lcObjList.SetItemText(row, 1, ArxRleUtils::objToHandleStr(obj, str));

				obj->close();
            }
			else {
				m_lcObjList.SetItemText(row, 0, _T("** Failed Open **"));
				m_lcObjList.SetItemText(row, 1, ArxRleUtils::rxErrorStr(es));
			}

			m_lcObjList.SetItemText(row, 2, ArxRleUtils::intDbIdToStr(idPair.key().asOldId(), str));
			m_lcObjList.SetItemText(row, 3, ArxRleUtils::intDbIdToStr(idPair.value().asOldId(), str));
			m_lcObjList.SetItemText(row, 4, ArxRleUtils::booleanToStr(idPair.isCloned(), str));
			m_lcObjList.SetItemText(row, 5, ArxRleUtils::booleanToStr(idPair.isPrimary(), str));
			m_lcObjList.SetItemText(row, 6, ArxRleUtils::booleanToStr(idPair.isOwnerXlated(), str));

			row++;
        }
    }

	this->UnlockWindowUpdate();		// flushes redraw events
}

/****************************************************************************
**
**  ArxRleUiTdcIdMap::buildMapItemColumns
**
**  **jma
**
*************************************/

void
ArxRleUiTdcIdMap::buildMapItemColumns()
{
        // get the width of the window
    CRect lvRect;
    int col1_width, col2_width, col3_width, col4_width, col5_width, col6_width, col7_width;
    m_lcObjList.GetClientRect(lvRect);
    int controlWidth = lvRect.Width() - ::GetSystemMetrics(SM_CXVSCROLL);

    col1_width = static_cast<int>(controlWidth * 0.30);
    col2_width = static_cast<int>(controlWidth * 0.10);
    col2_width = static_cast<int>(controlWidth * 0.10);
    col3_width = static_cast<int>(controlWidth * 0.10);
    col4_width = static_cast<int>(controlWidth * 0.10);
    col5_width = static_cast<int>(controlWidth * 0.10);
    col6_width = static_cast<int>(controlWidth * 0.10);
    col7_width = static_cast<int>(controlWidth * 0.10);

        // initialize the columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
    lvc.cx = col1_width;
    lvc.pszText = _T("Object");
    lvc.iSubItem = 0;
    m_lcObjList.InsertColumn(0, &lvc);

    lvc.cx = col2_width;
    lvc.iSubItem = 1;
    lvc.pszText = _T("Handle");
    m_lcObjList.InsertColumn(1, &lvc);

    lvc.cx = col3_width;
    lvc.iSubItem = 2;
    lvc.pszText = _T("Key");
    m_lcObjList.InsertColumn(2, &lvc);

    lvc.cx = col4_width;
    lvc.iSubItem = 3;
    lvc.pszText = _T("Value");
    m_lcObjList.InsertColumn(3, &lvc);

	lvc.cx = col5_width;
    lvc.iSubItem = 4;
    lvc.pszText = _T("Cloned");
    m_lcObjList.InsertColumn(4, &lvc);

	lvc.cx = col6_width;
    lvc.iSubItem = 5;
    lvc.pszText = _T("Primary");
    m_lcObjList.InsertColumn(5, &lvc);

	lvc.cx = col7_width;
    lvc.iSubItem = 6;
    lvc.pszText = _T("Owner Xlated");
    m_lcObjList.InsertColumn(6, &lvc);

	GetMainDialog()->GetColumnSizes(&m_lcObjList);
}

