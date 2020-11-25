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

#ifndef ARXRLEUITDCREFERENCES_H
#define ARXRLEUITDCREFERENCES_H

#include "ArxRleUiTdcDbObjectBase.h"

/****************************************************************************
**
**	CLASS ArxRleUiTdcReferences:
**
**	**jma
**
*************************************/

class ArxRleUiTdcReferences : public ArxRleUiTdcDbObjectBase {

public:
				ArxRleUiTdcReferences(const AcDbObjectIdArray& hardPointerIds,
									  const AcDbObjectIdArray& softPointerIds,
									  const AcDbObjectIdArray& hardOwnershipIds,
									  const AcDbObjectIdArray& softOwnershipIds);
    virtual		~ArxRleUiTdcReferences()    {}

    //{{AFX_DATA(ArxRleUiTdcReferences)
    enum { IDD = ARXRLE_TDC_ENTS };
    CStatic		m_txtErased;
    CListCtrl	m_dataList;
    CTreeCtrl	m_entTree;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcReferences)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcReferences)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedEnts(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    const AcDbObjectIdArray&	m_hardPointerIds;
    const AcDbObjectIdArray&	m_softPointerIds;
    const AcDbObjectIdArray&	m_hardOwnershipIds;
    const AcDbObjectIdArray&	m_softOwnershipIds;
    AcDbObjectIdArray			m_treeObjIdList;		// tblentry Object Ids

		// helper functions
    HTREEITEM	addOneTreeItem(LPCTSTR name, const AcDbObject* obj, HTREEITEM parent, bool sort = false);
    void        addEntriesToTree(const AcDbObjectIdArray& ids, HTREEITEM parent);

    void        displayCurrent(int index);

};


#endif    // ARXRLEUITDCENTITIES_H
