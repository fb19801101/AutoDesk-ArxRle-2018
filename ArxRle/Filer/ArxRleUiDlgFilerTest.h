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

#ifndef ARXRLEUIDLGFILERTEST_H
#define ARXRLEUIDLGFILERTEST_H

#include "Resource.h"

/****************************************************************************
**
**	CLASS ArxRleUiDlgFilerTest:
**
**	**jma
**
*************************************/

class ArxRleUiDlgFilerTest : public CAcUiDialog {

public:
                ArxRleUiDlgFilerTest(CWnd* pParent);

    AcDb::FilerType        indexToFilerType(int index);

    //{{AFX_DATA(ArxRleUiDlgFilerTest)
    enum { IDD = ARXRLE_DLG_FILER_TEST };
    int        m_puFilerTypeIndex;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgFilerTest)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgFilerTest)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // ARXRLEUIDLGFILERTEST_H
