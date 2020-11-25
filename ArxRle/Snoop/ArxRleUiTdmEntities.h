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

#ifndef ARXRLEUITDMENTITIES_H
#define ARXRLEUITDMENTITIES_H

#include "Resource.h"

class ArxRleUiTdcEntities;


/****************************************************************************
**
**	CLASS ArxRleUiTdmEntities:
**
**	**jma
**
*************************************/

class ArxRleUiTdmEntities : public CAcUiTabMainDialog {

public:
            ArxRleUiTdmEntities(const AcDbObjectIdArray& ents, bool isBlkDef, CWnd* parent, const TCHAR* winTitle = NULL);
	virtual	~ArxRleUiTdmEntities();

    //{{AFX_DATA(ArxRleUiTdmEntities)
    enum { IDD = ARXRLE_TDM_ENTS };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdmEntities)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdmEntities)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	CString					m_winTitle;
	ArxRleUiTdcEntities*	m_tdcEnts;
};

#endif // ARXRLEUITDMENTITIES_H

