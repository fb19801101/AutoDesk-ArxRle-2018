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

#include "ArxRleUiTdcRxObjectBase.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiTdcRxObjectBase::ArxRleUiTdcRxObjectBase
**
**  **jma
**
*************************************/

ArxRleUiTdcRxObjectBase::ArxRleUiTdcRxObjectBase()
:	CAcUiTabChildDialog(NULL, ArxRleApp::getApp()->dllInstance()),
	m_dataListCtrl(NULL)
{
}

/****************************************************************************
**
**  ArxRleUiTdcRxObjectBase::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcRxObjectBase::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabChildDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcRxObjectBase)
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcRxObjectBase message map

BEGIN_MESSAGE_MAP(ArxRleUiTdcRxObjectBase, CAcUiTabChildDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdcRxObjectBase)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcRxObjectBase message handlers

/****************************************************************************
**
**  ArxRleUiTdcRxObjectBase::buildColumns
**
**  **jma
**
*************************************/

void
ArxRleUiTdcRxObjectBase::buildColumns(CListCtrl& dataList)
{
        // get the width of the window
    CRect lvRect;
    int col1_width, col2_width;
    dataList.GetClientRect(lvRect);
    col1_width = lvRect.Width() / 2;
    col2_width = lvRect.Width() - col1_width - ::GetSystemMetrics(SM_CXVSCROLL);

        // initialize the columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
    lvc.cx = col1_width;
    lvc.pszText = _T("Field");
    lvc.iSubItem = 0;
    dataList.InsertColumn(0, &lvc);

    lvc.cx = col2_width;
    lvc.iSubItem = 1;
    lvc.pszText = _T("Value");
    dataList.InsertColumn(1, &lvc);
}

/****************************************************************************
**
**  ArxRleUiTdcRxObjectBase::drawPropsList
**
**  **jma
**
*************************************/

void
ArxRleUiTdcRxObjectBase::drawPropsList(CListCtrl& dataList)
{
	this->LockWindowUpdate();		// suppress redraw events

    dataList.DeleteAllItems();		// remove any existing items from the control

        // build up the list view control
    LV_ITEM lvi;
    lvi.mask = 0;
    int row = 0;

    POSITION pos1 = m_fieldStrList.GetHeadPosition();
    POSITION pos2 = m_valueStrList.GetHeadPosition();

    while ((pos1 != NULL) && (pos2 != NULL)) {
        lvi.iItem = row;
        lvi.iSubItem = 0;
        dataList.InsertItem(&lvi);
        dataList.SetItemText(row, 0, m_fieldStrList.GetNext(pos1));
        dataList.SetItemText(row, 1, m_valueStrList.GetNext(pos2));
        row++;
    }

	this->UnlockWindowUpdate();		// flushes redraw events
}

/****************************************************************************
**
**  ArxRleUiTdcRxObjectBase::addToDataList
**
**  **jma
**
*************************************/

void
ArxRleUiTdcRxObjectBase::addToDataList(LPCTSTR field, LPCTSTR value, bool addQuotes)
{
    if (field == NULL)
		m_fieldStrList.AddTail(_T(""));
	else
		m_fieldStrList.AddTail(field);

    if (value == NULL) {
        m_valueStrList.AddTail(_T("(NULL)"));    // some Acad funcs return Null strings!
    }
    else {
        if (addQuotes) {
            CString str;
            str.Format(_T("\"%s\""), value);
            m_valueStrList.AddTail(str);
        }
        else
            m_valueStrList.AddTail(value);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcRxObjectBase::addSeperatorLine
**
**  **jma
**
*************************************/

void
ArxRleUiTdcRxObjectBase::addSeperatorLine(LPCTSTR className)
{
    CString str;

    str.Format(_T("------ %s ------"), className);
    addToDataList(str, _T(""));
}

