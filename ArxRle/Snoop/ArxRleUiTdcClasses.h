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

#ifndef ARXRLEUITDCCLASSES_H
#define ARXRLEUITDCCLASSES_H

#include "Resource.h"

/****************************************************************************
**
**	CLASS ArxRleUiTdcClasses:
**
**	**jma
**
*************************************/

class ArxRleUiTdcClasses : public CAcUiTabChildDialog {

public:
    ArxRleUiTdcClasses();

    //{{AFX_DATA(ArxRleUiTdcClasses)
    enum { IDD = ARXRLE_TDC_CLASSES };
    CTreeCtrl	m_tblTree;
    CListBox    m_lbProxyFlags;
    CListBox    m_lbProtocolExt;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcClasses)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcClasses)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnCompClasses();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    AcDbVoidPtrArray    m_classArray;
    AcDbVoidPtrArray    m_placedNodes;
    AcDbVoidPtrArray    m_treeItems;

    void        buildClassTree();
    BOOL        regress(int& index, HTREEITEM& parentItem);
    HTREEITEM   addTreeItem(AcRxClass* classObj, HTREEITEM parent);
    void        displayCurrent(AcRxClass* classObj);
};


#endif    // ARXRLEUITDCCLASSES_H
