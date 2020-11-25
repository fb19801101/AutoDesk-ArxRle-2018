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

#include "ArxRleUiDlgXdata.h"
#include "AcadUtils/ArxRleUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiDlgXdata::ArxRleUiDlgXdata
**
**  **jma
**
*************************************/

ArxRleUiDlgXdata::ArxRleUiDlgXdata(CWnd* parent, AcDbObject* obj)
:   ArxRleUiDlgDxf(parent, obj, ArxRleUiDlgXdata::IDD),
    m_xdata(obj)
{
    //{{AFX_DATA_INIT(ArxRleUiDlgXdata)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


/****************************************************************************
**
**  ArxRleUiDlgXdata::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgXdata::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiDlgDxf::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgXdata)
    DDX_Control(pDX, ARXRLE_XDATA_CB_APPS, m_appPopUp);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgXdata message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgXdata, ArxRleUiDlgDxf)
    //{{AFX_MSG_MAP(ArxRleUiDlgXdata)
    ON_CBN_SELENDOK(ARXRLE_XDATA_CB_APPS, OnAppNameSelected)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgXdata message handlers

/****************************************************************************
**
**  ArxRleUiDlgXdata::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgXdata::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();	// purposely bypass base class

    buildColumns();        // insert list control columns
    
        // build up list of app names for pop up list
    ArxRleAppXdataListIterator iter(m_xdata);
    m_appPopUp.AddString(_T("*  (All Applications)"));
    for (; !iter.done(); iter.next()) {
        m_appPopUp.AddString(iter.item()->getAppName());
    }
    m_appPopUp.SetCurSel(0);
    OnAppNameSelected();    // fake out selection of item 0
    
    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiDlgXdata::OnAppNameSelected
**
**  **jma
**
*************************************/

void
ArxRleUiDlgXdata::OnAppNameSelected() 
{
    resbuf* tmpXdata;
    int index = m_appPopUp.GetCurSel();

    if (index == CB_ERR)
        index = 0;

    if (index == 0) {    // iterate through all apps
        ArxRleRbList allXdata, singleAppXdata;
        ArxRleAppXdataListIterator iter(m_xdata);
        for (; !iter.done(); iter.next()) {
            singleAppXdata.adoptData(iter.item()->allocResbufChain());
            allXdata.append(singleAppXdata);
        }
        displayRbChain(allXdata.data());    // display one big list
    }
    else {
            // look up this specific app
        ArxRleAppXdata* xdPtr = m_xdata.at(index-1);
        tmpXdata = xdPtr->allocResbufChain();
        displayRbChain(tmpXdata);
        acutRelRb(tmpXdata);
    }
}