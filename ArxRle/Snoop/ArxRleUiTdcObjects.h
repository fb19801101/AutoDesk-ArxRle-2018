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

#ifndef ARXRLEUITDCOBJECTS_H
#define ARXRLEUITDCOBJECTS_H

#include "ArxRleUiTdcDbObjectBase.h"

/****************************************************************************
**
**	CLASS ArxRleUiTdcObjects:
**
**	**jma
**
*************************************/

class ArxRleUiTdcObjects : public ArxRleUiTdcDbObjectBase {

public:
				ArxRleUiTdcObjects(const AcDbObjectIdArray& objList);
    virtual		~ArxRleUiTdcObjects()    {}

    //{{AFX_DATA(ArxRleUiTdcObjects)
    enum { IDD = ARXRLE_TDC_OBJS };
    CStatic		m_txtErased;
    CListCtrl	m_dataList;
    CListBox   	m_lbObjList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcObjects)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcObjects)
    virtual BOOL OnInitDialog();
	virtual void OnSelchangedObjs();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    const AcDbObjectIdArray&	m_objList;

		// helper functions
    void        displayCurrent(int index);

};

#endif    // ARXRLEUITDCOBJECTS_H
