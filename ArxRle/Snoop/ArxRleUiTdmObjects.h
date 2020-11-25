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

#ifndef ARXRLEUITDMOBJECTS_H
#define ARXRLEUITDMOBJECTS_H

#include "Resource.h"

class ArxRleUiTdcObjects;


/****************************************************************************
**
**	CLASS ArxRleUiTdmObjects:
**
**	**jma
**
*************************************/

class ArxRleUiTdmObjects : public CAcUiTabMainDialog {

public:
            ArxRleUiTdmObjects(const AcDbObjectIdArray& objIds, CWnd* parent, const TCHAR* winTitle = NULL);
	virtual	~ArxRleUiTdmObjects();

    //{{AFX_DATA(ArxRleUiTdmObjects)
    enum { IDD = ARXRLE_TDM_ENTS };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdmObjects)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdmObjects)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	CString				m_winTitle;
	ArxRleUiTdcObjects*	m_tdcObjs;
};

#endif // ARXRLEUITDMOBJECTS_H

