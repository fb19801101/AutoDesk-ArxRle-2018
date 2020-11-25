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
#ifndef ARXRLEUIDLGCLASSDICT_H
#define ARXRLEUIDLGCLASSDICT_H

#include "Resource.h"


/****************************************************************************
**
**	CLASS ArxRleUiDlgClassDict:
**
**	**jma
**
*************************************/


class ArxRleUiDlgClassDict : public CAcUiDialog {

public:
            ArxRleUiDlgClassDict(CWnd* pParent);

    //{{AFX_DATA(ArxRleUiDlgClassDict)
    enum { IDD = ARXRLE_DLG_CLASS_DICT };
    CListCtrl    m_classList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgClassDict)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgClassDict)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    CStringList    m_classNameStrList;
    CStringList    m_dxfNameStrList;
    CStringList    m_appNameStrList;
    CStringList    m_proxyStrList;
	CStringList	   m_birthDwgVerList;
	CStringList    m_birthMntVerList;

        // helper functions
    void        buildColumns();
    void        buildClassList();
    void        display();
};

#endif // ARXRLEUIDLGCLASSDICT_H

