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

#ifndef ARXRLEUITDCLONGTRANS_H
#define ARXRLEUITDCLONGTRANS_H

#include "ArxRleUiTdcDbObjectBase.h"

/****************************************************************************
**
**	CLASS ArxRleUiTdcLongTrans:
**
**	**jma
**
*************************************/

class ArxRleUiTdcLongTrans : public ArxRleUiTdcDbObjectBase {

public:
                ArxRleUiTdcLongTrans(AcDbLongTransaction* lt);
    virtual		~ArxRleUiTdcLongTrans()    {}

    //{{AFX_DATA(ArxRleUiTdcLongTrans)
    enum { IDD = ARXRLE_TDC_LONG_TRANS };
    CListCtrl	m_dataList;
    CTreeCtrl	m_tblTree;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcLongTrans)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcLongTrans)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedSymtabs(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg virtual void OnDxf();
    afx_msg virtual void OnExtdict();
    afx_msg virtual void OnReactors();
    afx_msg virtual void OnXdata();
    afx_msg virtual void OnDatabase();
    afx_msg virtual void OnDocument();
    afx_msg virtual void OnShowIdMap();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members
	AcDbLongTransaction*	m_longTrans;
	AcDbObjectIdArray		m_objIdList;

		// helper functions
    HTREEITEM		addOneTreeItem(LPCTSTR name, const AcDbObjectId& objId,
								HTREEITEM parent, bool sortAlpha = true);
    void			displayCurrent(int index);

	virtual bool	getReferencedObjects(AcDbObjectIdArray& hardPointerIds,
										 AcDbObjectIdArray& softPointerIds,
										 AcDbObjectIdArray& hardOwnershipIds,
										 AcDbObjectIdArray& softOwnershipIds);
};


#endif    // ARXRLEUITDCLONGTRANS_H
