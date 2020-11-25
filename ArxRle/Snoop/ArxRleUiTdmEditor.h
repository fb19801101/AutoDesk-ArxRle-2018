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

#ifndef ARXRLEUITDMEDITOR_H
#define ARXRLEUITDMEDITOR_H

#include "Resource.h"

class ArxRleUiTdcDocs;
class ArxRleUiTdcClasses;
class ArxRleUiTdcCmds;
class ArxRleUiTdcHostAppSrv;

/****************************************************************************
**
**	CLASS ArxRleUiTdmEditor:
**
**	**jma
**
*************************************/

class ArxRleUiTdmEditor : public CAcUiTabMainDialog {

public:
            ArxRleUiTdmEditor(CWnd* pParent);
            ArxRleUiTdmEditor(CWnd* pParent, AcApDocument* doc); // when only want to see the Doc's page
	virtual	~ArxRleUiTdmEditor();

    //{{AFX_DATA(ArxRleUiTdmEditor)
    enum { IDD = ARXRLE_TDM_EDITOR };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdmEditor)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdmEditor)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	ArxRleUiTdcDocs*		m_tdcDocs;
	ArxRleUiTdcClasses*		m_tdcClasses;
	ArxRleUiTdcCmds*		m_tdcCommands;
	ArxRleUiTdcHostAppSrv*	m_tdcHostAppSrv;
};

#endif // ARXRLEUITDMEDITOR_H

