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

#ifndef ARXRLEUITDCRXOBJECTBASE_H
#define ARXRLEUITDCRXOBJECTBASE_H

#include "Resource.h"

/****************************************************************************
**
**	CLASS ArxRleUiTdcRxObjectBase:
**
**	**jma
**
*************************************/

class ArxRleUiTdcRxObjectBase : public CAcUiTabChildDialog {

public:
    virtual    ~ArxRleUiTdcRxObjectBase()    {}

    //{{AFX_DATA(ArxRleUiTdcRxObjectBase)
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcRxObjectBase)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
            ArxRleUiTdcRxObjectBase();    // can only be constructed by derived classes

    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcRxObjectBase)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

        // data members
    CStringList		m_fieldStrList;
    CStringList		m_valueStrList;
	CListCtrl*		m_dataListCtrl;	// pointer from derived dialog

        // helper functions
	void		buildColumns(CListCtrl& dataList);
	void		drawPropsList(CListCtrl& dataList);
    void        addToDataList(LPCTSTR field, LPCTSTR value, bool addQuotes = false);
    void        addSeperatorLine(LPCTSTR className);
};

#endif    // ARXRLEUITDCRXOBJECTBASE_H
