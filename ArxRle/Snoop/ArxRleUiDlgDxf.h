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

#ifndef ARXRLEUIDLGDXF_H
#define ARXRLEUIDLGDXF_H

#include "Resource.h"

/****************************************************************************
**
**	CLASS ArxRleUiDlgDxf:
**
**	**jma
**
*************************************/

class ArxRleUiDlgDxf : public CAcUiDialog {

public:
				ArxRleUiDlgDxf(CWnd* parent, AcDbObject* obj);
    virtual		~ArxRleUiDlgDxf()    {}

    //{{AFX_DATA(ArxRleUiDlgDxf)
    enum { IDD = ARXRLE_DLG_DXF };
    CListCtrl    m_dxfList;
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgDxf)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
            ArxRleUiDlgDxf(CWnd* parent, AcDbObject* obj, UINT dlgId);

    void    displayRbChain(resbuf* dxfData);
    void    buildColumns();

    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgDxf)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    AcDbObject*    m_objPtr;
};


#endif
