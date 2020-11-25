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

#ifndef ARXRLEUIDLGABOUTBOX_H
#define ARXRLEUIDLGABOUTBOX_H

#include "Resource.h"

/****************************************************************************
**
**	CLASS ArxRleUiDlgAboutBox:
**
**	**jma
**
*************************************/

class ArxRleUiDlgAboutBox : public CAcUiDialog {

public:
    ArxRleUiDlgAboutBox(CWnd* pParent);

    //{{AFX_DATA(ArxRleUiDlgAboutBox)
    enum { IDD = ARXRLE_DLG_ABOUT };
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgAboutBox)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgAboutBox)
        // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


#endif // ARXRLEUIDLGABOUTBOX_H
