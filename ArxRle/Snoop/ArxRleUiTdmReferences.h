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

#ifndef ARXRLEUITDMREFERENCES_H
#define ARXRLEUITDMREFERENCES_H

#include "Resource.h"

class ArxRleUiTdcReferences;


/****************************************************************************
**
**	CLASS ArxRleUiTdmReferences:
**
**	**jma
**
*************************************/

class ArxRleUiTdmReferences : public CAcUiTabMainDialog {

public:
            ArxRleUiTdmReferences(const AcDbObjectIdArray& hardPointerIds,
								  const AcDbObjectIdArray& softPointerIds,
								  const AcDbObjectIdArray& hardOwnershipIds,
								  const AcDbObjectIdArray& softOwnershipIds,
								  CWnd* parent, const TCHAR* winTitle = NULL);
	virtual	~ArxRleUiTdmReferences();

    //{{AFX_DATA(ArxRleUiTdmReferences)
    enum { IDD = ARXRLE_TDM_ENTS };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdmReferences)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdmReferences)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	CString					m_winTitle;
	ArxRleUiTdcReferences*	m_tdcRefs;
};

#endif // ARXRLEUITDMREFERENCES_H

