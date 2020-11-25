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

#include "ArxRleUiDlgServiceDict.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiDlgServiceDict::ArxRleUiDlgServiceDict
**
**  **jma
**
*************************************/

ArxRleUiDlgServiceDict::ArxRleUiDlgServiceDict(CWnd* parent)
:	CAcUiDialog(ArxRleUiDlgServiceDict::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxRleUiDlgServiceDict)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiDlgServiceDict::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgServiceDict::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgServiceDict)
    DDX_Control(pDX, ARXRLE_SERV_DICT_LC_SERVICES, m_lcServices);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgServiceDict message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgServiceDict, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxRleUiDlgServiceDict)
	ON_BN_CLICKED(ARXRLE_SERV_DICT_BN_ADD, OnAdd)
	ON_BN_CLICKED(ARXRLE_SERV_DICT_BN_REMOVE, OnRemove)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgServiceDict message handlers


/****************************************************************************
**
**  ArxRleUiDlgServiceDict::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgServiceDict::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();
    
    buildColumns();
    buildServiceList();
    display();
    
    return TRUE; 
}

/****************************************************************************
**
**  ArxRleUiDlgServiceDict::buildColumns
**
**  **jma
**
*************************************/

void
ArxRleUiDlgServiceDict::buildColumns()
{
        // get the width of the window
    CRect lvRect;
    int col1_width, col2_width, col3_width, col4_width;
    m_lcServices.GetClientRect(lvRect);
    col1_width = lvRect.Width() / 3;
    col2_width = col1_width;
    col3_width = col2_width / 2;
    col4_width = lvRect.Width() - col1_width - col2_width - col3_width - ::GetSystemMetrics(SM_CXVSCROLL);

        // initialize the columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_WIDTH | LVCF_TEXT;
    lvc.cx = col1_width;
    lvc.pszText = _T("Name");
    m_lcServices.InsertColumn(0, &lvc);

    lvc.cx = col2_width;
    lvc.pszText = _T("Class");
    m_lcServices.InsertColumn(1, &lvc);

    lvc.cx = col3_width;
    lvc.pszText = _T("ID");
    m_lcServices.InsertColumn(2, &lvc);

    lvc.cx = col4_width;
    lvc.pszText = _T("Unloadable");
    m_lcServices.InsertColumn(3, &lvc);
}

/****************************************************************************
**
**  ArxRleUiDlgServiceDict::buildServiceList
**
**  **jma
**
*************************************/

void
ArxRleUiDlgServiceDict::buildServiceList()
{
        // get an interator over the class dictionary
    AcRxDictionary* serviceDict = acrxServiceDictionary;
    AcRxDictionaryIterator* iter;
    if ((serviceDict == NULL) || ((iter = serviceDict->newIterator()) == NULL)) {
        ArxRleUtils::stopAlertBox(_T("ERROR: Couldn't get service dictionary."));
        return;
    }
        // iterate over each item and get its info
    AcRxService* srv;
    CString str;

    for (; !iter->done(); iter->next()) {
        m_keyStrs.Add(iter->key());
        m_idStrs.Add(ArxRleUtils::intToStr(iter->id(), str));

        srv = AcRxService::cast(iter->object());
        m_servicePtrs.append(srv);
        if (srv) {
            m_classStrs.Add(ArxRleUtils::objToClassStr(srv));
            m_depStrs.Add(ArxRleUtils::booleanToStr(srv->unloadable(), str));
        }
        else {
            ASSERT(0);
                // have to add something to keep lists in sync
            m_classStrs.Add(_T(""));
            m_depStrs.Add(_T(""));
        }
    }
    delete iter;
}

/****************************************************************************
**
**  ArxRleUiDlgServiceDict::display
**
**  **jma
**
*************************************/

void
ArxRleUiDlgServiceDict::display()
{
        // build up the list view control
    LV_ITEM lvi;
    lvi.mask = 0;

    for (int row=0; row<m_keyStrs.GetSize(); row++) {
        lvi.iItem = row;
        lvi.iSubItem = 0;
        m_lcServices.InsertItem(&lvi);
        m_lcServices.SetItemText(row, 0, m_keyStrs[row]);
        m_lcServices.SetItemText(row, 1, m_classStrs[row]);
        m_lcServices.SetItemText(row, 2, m_idStrs[row]);
        m_lcServices.SetItemText(row, 3, m_depStrs[row]);
    }
}

/****************************************************************************
**
**  ArxRleUiDlgServiceDict::OnAdd
**
**  **jma
**
*************************************/

void
ArxRleUiDlgServiceDict::OnAdd()
{
    AcRxService* srv = getCurrentService();
    if (srv) {
        srv->addDependency();
        updateDependencyStrings();
    }
}

/****************************************************************************
**
**  ArxRleUiDlgServiceDict::OnRemove
**
**  **jma
**
*************************************/

void
ArxRleUiDlgServiceDict::OnRemove()
{
    AcRxService* srv = getCurrentService();
    if (srv) {
        srv->removeDependency();
        updateDependencyStrings();
    }
}

/****************************************************************************
**
**  ArxRleUiDlgServiceDict::getCurrentService
**
**  **jma
**
*************************************/

AcRxService*
ArxRleUiDlgServiceDict::getCurrentService()
{
    AcRxService* srv = NULL;

    int itemNum = m_lcServices.GetNextItem(-1, LVNI_SELECTED);
	return static_cast<AcRxService*>(itemNum>=0? m_servicePtrs[itemNum] : NULL);
}

/****************************************************************************
**
**  ArxRleUiDlgServiceDict::updateDependencyStrings
**
**  **jma
**
*************************************/

void
ArxRleUiDlgServiceDict::updateDependencyStrings()
{
    CString str;

    m_depStrs.RemoveAll();
    int len = m_servicePtrs.length();
    for (int i=0; i<len; i++) {
        AcRxService* srv = static_cast<AcRxService*>(m_servicePtrs[i]);
        m_depStrs.Add(ArxRleUtils::booleanToStr(srv->unloadable(), str));
        m_lcServices.SetItemText(i, 3, str);
    }
}

