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

#ifndef ARXRLEUITDCCLONESET_H
#define ARXRLEUITDCCLONESET_H

#include "Resource.h"
#include "Snoop/ArxRleCloneSet.h"

/****************************************************************************
**
**	CLASS ArxRleUiTdcCloneSet:
**
**	**jma
**
*************************************/

class ArxRleUiTdcCloneSet : public CAcUiTabChildDialog {

public:
				ArxRleUiTdcCloneSet();
    virtual		~ArxRleUiTdcCloneSet()    {}

    //{{AFX_DATA(ArxRleUiTdcCloneSet)
    enum { IDD = ARXRLE_TDC_CLONESET };
	CListBox			m_lbObjList;
	CListBox			m_lbDbList;
    CAcUiSelectButton	m_selectButton;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcCloneSet)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    //}}AFX_VIRTUAL

protected:

    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcCloneSet)
    afx_msg void OnShow();
    afx_msg void OnBrowse();
    afx_msg void OnRemove();
    afx_msg void OnRemoveAll();
    afx_msg void OnSelect();
    afx_msg void OnObjectsChanged();
    afx_msg void OnDatabaseChanged();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	AcDbVoidPtrArray	m_dbPtrs;
	AcDbObjectIdArray	m_objIds;
	ArxRleCloneSet&		m_cloneSet;

        // helper functions
	void	setButtonModes();
	void	displayDbList();
	void	displayObjList();
	int		getIndexFor(AcDbDatabase* db);
};

#endif    // ARXRLEUITDCCLONESET_H
