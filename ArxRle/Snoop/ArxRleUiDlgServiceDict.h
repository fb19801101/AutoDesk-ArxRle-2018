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

#ifndef ARXRLEUIDLGSERVICEDICT_H
#define ARXRLEUIDLGSERVICEDICT_H

#include "Resource.h"

/****************************************************************************
**
**	CLASS ArxRleUiDlgServiceDict:
**
**	**jma
**
*************************************/

class ArxRleUiDlgServiceDict : public CAcUiDialog {

public:
                ArxRleUiDlgServiceDict(CWnd* pParent);

    //{{AFX_DATA(ArxRleUiDlgServiceDict)
    enum { IDD = ARXRLE_DLG_SERV_DICT };
    CListCtrl    m_lcServices;
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgServiceDict)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgServiceDict)
    virtual BOOL OnInitDialog();
    afx_msg void OnAdd();
    afx_msg void OnRemove();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    CStringArray        m_keyStrs;
    CStringArray        m_classStrs;
    CStringArray        m_idStrs;
    CStringArray        m_depStrs;
    AcDbVoidPtrArray    m_servicePtrs;

        // helper functions
    void            buildColumns();
    void            buildServiceList();
    void            display();
    AcRxService*    getCurrentService();
    void            updateDependencyStrings();

};


#endif    // ARXRLEUIDLGSERVICEDICT_H
