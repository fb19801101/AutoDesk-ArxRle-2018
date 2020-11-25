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

#ifndef ARXRLEUITDCHOSTAPPSRV_H
#define ARXRLEUITDCHOSTAPPSRV_H

#include "Resource.h"
#include "ArxRleUiTdcRxObjectBase.h"

/****************************************************************************
**
**	CLASS ArxRleUiTdcHostAppSrv:
**
**	**jma
**
*************************************/

class ArxRleUiTdcHostAppSrv : public ArxRleUiTdcRxObjectBase {

public:
				ArxRleUiTdcHostAppSrv();
    virtual		~ArxRleUiTdcHostAppSrv();

    //{{AFX_DATA(ArxRleUiTdcHostAppSrv)
    enum { IDD = ARXRLE_TDC_HOSTAPPSERV };
    CListCtrl	m_dataList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcHostAppSrv)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcHostAppSrv)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members

		// helper functions
    void        displayCurrent();

};


#endif    // ARXRLEUITDCHOSTAPPSRV_H
