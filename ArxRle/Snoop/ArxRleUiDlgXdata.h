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

#ifndef ARXRLEUIDLGXDATA_H
#define ARXRLEUIDLGXDATA_H

#include "ArxRleUiDlgDxf.h"
#include "AcadUtils/ArxRleXdata.h"

/****************************************************************************
**
**	CLASS ArxRleUiDlgXdata:
**
**	**jma
**
*************************************/

class ArxRleUiDlgXdata : public ArxRleUiDlgDxf {

public:
				ArxRleUiDlgXdata(CWnd* parent, AcDbObject* obj);
    virtual		~ArxRleUiDlgXdata()    {}

    //{{AFX_DATA(ArxRleUiDlgXdata)
    enum { IDD = ARXRLE_DLG_XDATA };
    CComboBox    m_appPopUp;
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgXdata)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgXdata)
    virtual BOOL OnInitDialog();
    afx_msg void OnAppNameSelected();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ArxRleAppXdataList    m_xdata;
};


#endif  // ARXRLEUIDLGXDATA_H
