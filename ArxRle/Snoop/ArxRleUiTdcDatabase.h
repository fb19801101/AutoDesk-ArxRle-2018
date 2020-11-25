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

#ifndef ARXRLEUITDCDATABASE_H
#define ARXRLEUITDCDATABASE_H

#include "ArxRleUiTdcDbObjectBase.h"


/****************************************************************************
**
**	CLASS ArxRleUiTdcDatabase:
**
**	**jma
**
*************************************/

class ArxRleUiTdcDatabase : public ArxRleUiTdcRxObjectBase {

public:
				ArxRleUiTdcDatabase(AcDbDatabase* db);
    virtual		~ArxRleUiTdcDatabase() {}

    //{{AFX_DATA(ArxRleUiTdcDatabase)
    enum { IDD = ARXRLE_TDC_DBMISC };
    CStatic     m_frPreview;
    CListCtrl	m_dataList;
    //}}AFX_DATA


    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcDatabase)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcDatabase)
    afx_msg void OnPaint();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members
    AcDbDatabase*	m_db;

		// helper functions
	void		display();

};

#endif    // ARXRLEUITDCDATABASE_H
