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

#ifndef ARXRLEUITDMDATABASE_H
#define ARXRLEUITDMDATABASE_H

#include "Resource.h"

class ArxRleUiTdcSymTbl;
class ArxRleUiTdcDict;
class ArxRleUiTdcDatabase;


/****************************************************************************
**
**	CLASS ArxRleUiTdmDatabase:
**
**	**jma
**
*************************************/

class ArxRleUiTdmDatabase : public CAcUiTabMainDialog {

public:
            ArxRleUiTdmDatabase(AcDbDatabase* db, CWnd* parent, const TCHAR* winTitle = NULL);
			ArxRleUiTdmDatabase(const AcDbObjectId& dictId, CWnd* parent, const TCHAR* winTitle = NULL);	// when you just want page for extension dict
	virtual	~ArxRleUiTdmDatabase();

    //{{AFX_DATA(ArxRleUiTdmDatabase)
    enum { IDD = ARXRLE_TDM_DATABASE };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdmDatabase)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdmDatabase)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	AcDbDatabase*			m_db;
	CString					m_winTitle;
	ArxRleUiTdcSymTbl*		m_tdcSymTbl;
	ArxRleUiTdcDict*		m_tdcDicts;
	ArxRleUiTdcDatabase*	m_tdcDb;
};

#endif // ARXRLEUITDMDATABASE_H

