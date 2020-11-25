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

#ifndef ARXRLEUIDLGSYSREGISTRY_H
#define ARXRLEUIDLGSYSREGISTRY_H

#include "Resource.h"

/****************************************************************************
**
**  CLASS ArxRleUiDlgSysRegistry:
**
**  **jma
**
*************************************/

class ArxRleUiDlgSysRegistry : public CAcUiDialog {

public:
                ArxRleUiDlgSysRegistry(CWnd* pParent);
    virtual     ~ArxRleUiDlgSysRegistry()    {}

    //{{AFX_DATA(ArxRleUiDlgSysRegistry)
    enum { IDD = ARXRLE_DLG_SYSREGISTRY };
    CTreeCtrl    m_tree;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgSysRegistry)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgSysRegistry)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedSysReg(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    AcDbVoidPtrArray    m_objList;

    HTREEITEM           addTreeItem(LPCTSTR name, AcRxObject* obj, HTREEITEM parent);
    void                displayCurrent(int index);

};

#endif    // ARXRLEUIDLGSYSREGISTRY_H
