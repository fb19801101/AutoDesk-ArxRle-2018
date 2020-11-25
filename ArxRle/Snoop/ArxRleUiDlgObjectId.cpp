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

#include "ArxRleUiDlgObjectId.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiDlgObjectId::ArxRleUiDlgObjectId
**
**  **jma
**
*************************************/

ArxRleUiDlgObjectId::ArxRleUiDlgObjectId(const AcDbObjectId& objId, CWnd* parent)
:	CAcUiDialog(ArxRleUiDlgObjectId::IDD, parent, ArxRleApp::getApp()->dllInstance()),
	m_objId(objId)
{
    //{{AFX_DATA_INIT(ArxRleUiDlgObjectId)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiDlgObjectId::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjectId::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgObjectId)
    DDX_Control(pDX, ARXRLE_OBJECT_ID_INFO_LC_VALUES, m_dataList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgObjectId message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgObjectId, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxRleUiDlgObjectId)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgObjectId message handlers

/****************************************************************************
**
**  ArxRleUiDlgObjectId::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgObjectId::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();
    
    buildColumns();
    display();
    
    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiDlgObjectId::buildColumns
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjectId::buildColumns()
{
        // get the width of the window
    CRect lvRect;
    int col1_width, col2_width;
    m_dataList.GetClientRect(lvRect);
    col1_width = lvRect.Width() / 2;
    col2_width = lvRect.Width() - col1_width - ::GetSystemMetrics(SM_CXVSCROLL);

        // initialize the columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.cx = col1_width;
    lvc.iSubItem = 0;
    lvc.pszText = _T("Field");
    m_dataList.InsertColumn(0, &lvc);

    lvc.cx = col2_width;
    lvc.iSubItem = 1;
    lvc.pszText = _T("Value");
    m_dataList.InsertColumn(1, &lvc);
}

/****************************************************************************
**
**  ArxRleUiDlgObjectId::display
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjectId::display()
{
		// remove any existing items
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

	CString str;
	SetDlgItemText(ARXRLE_OBJECT_ID_INFO_EB_OBJTYPE, ArxRleUtils::objToClassAndHandleStr(m_objId, str));

	addToDataList(_T("Is Null"), ArxRleUtils::booleanToStr(m_objId.isNull(), str));
	addToDataList(_T("Is Valid"), ArxRleUtils::booleanToStr(m_objId.isValid(), str));
	addToDataList(_T("Is Erased"), ArxRleUtils::booleanToStr(m_objId.isErased(), str));
	addToDataList(_T("Is Effectively Erased"), ArxRleUtils::booleanToStr(m_objId.isEffectivelyErased(), str));
	addToDataList(_T("Object Left On Disk"), ArxRleUtils::booleanToStr(m_objId.objectLeftOnDisk(), str));

    TCHAR tmpStr[256];
    m_objId.handle().getIntoAsciiBuffer(tmpStr);
	addToDataList(_T("Handle"), tmpStr);

    m_objId.handle().getIntoAsciiBuffer(tmpStr);
	addToDataList(_T("Non-Forwarded Handle"), tmpStr);

	addToDataList(_T("As Old Id"), ArxRleUtils::intDbIdToStr(m_objId.asOldId(), str));

	addToDataList(_T("Database"), ArxRleUtils::dbToStr(m_objId.database(), str));
	addToDataList(_T("Original Database"), ArxRleUtils::dbToStr(m_objId.originalDatabase(), str));

	drawPropsList();
}

/****************************************************************************
**
**  ArxRleUiDlgObjectId::drawPropsList
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjectId::drawPropsList()
{
	this->LockWindowUpdate();		// suppress redraw events

    m_dataList.DeleteAllItems();	// remove any existing items from the control

        // build up the list view control
    LV_ITEM lvi;
    lvi.mask = 0;
    int row = 0;

    POSITION pos1 = m_fieldStrList.GetHeadPosition();
    POSITION pos2 = m_valueStrList.GetHeadPosition();

    while ((pos1 != NULL) && (pos2 != NULL)) {
        lvi.iItem = row;
        lvi.iSubItem = 0;
        m_dataList.InsertItem(&lvi);
        m_dataList.SetItemText(row, 0, m_fieldStrList.GetNext(pos1));
        m_dataList.SetItemText(row, 1, m_valueStrList.GetNext(pos2));
        row++;
    }

	this->UnlockWindowUpdate();		// flushes redraw events
}

/****************************************************************************
**
**  ArxRleUiDlgObjectId::addToDataList
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjectId::addToDataList(LPCTSTR field, LPCTSTR value, bool addQuotes)
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