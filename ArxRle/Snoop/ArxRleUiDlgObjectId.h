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

#ifndef ARXRLEUIDLGOBJECTID_H
#define ARXRLEUIDLGOBJECTID_H

#include "Resource.h"

/****************************************************************************
**
**	CLASS ArxRleUiDlgObjectId:
**
**	**jma
**
*************************************/

class ArxRleUiDlgObjectId : public CAcUiDialog {

public:
				ArxRleUiDlgObjectId(const AcDbObjectId& objId, CWnd* parent);
    virtual		~ArxRleUiDlgObjectId()    {}

    //{{AFX_DATA(ArxRleUiDlgObjectId)
    enum { IDD = ARXRLE_DLG_OBJECT_ID_INFO };
    CListCtrl    m_dataList;
    //}}AFX_DATA


    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgObjectId)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    void    display();
    void    buildColumns();

    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgObjectId)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members
    AcDbObjectId    m_objId;
    CStringList		m_fieldStrList;
    CStringList		m_valueStrList;

		// helper functions
	void		drawPropsList();
    void        addToDataList(LPCTSTR field, LPCTSTR value, bool addQuotes = false);
};


#endif	//ARXRLEUIDLGOBJECTID_H
