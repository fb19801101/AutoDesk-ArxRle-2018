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

#ifndef ARXRLEUITDCIDMAP_H
#define ARXRLEUITDCIDMAP_H

#include "ArxRleUiTdcRxObjectBase.h"

/****************************************************************************
**
**	CLASS ArxRleUiTdcIdMap:
**
**	**jma
**
*************************************/

class ArxRleUiTdcIdMap : public ArxRleUiTdcRxObjectBase {

public:
				ArxRleUiTdcIdMap(AcDbIdMapping* idMap);
    virtual		~ArxRleUiTdcIdMap()    {}

    //{{AFX_DATA(ArxRleUiTdcIdMap)
    enum { IDD = ARXRLE_TDC_IDMAP };
    CStatic		m_txtErased;
    CListCtrl	m_dataList;
    CListCtrl   m_lcObjList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcIdMap)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcIdMap)
    virtual BOOL OnInitDialog();
    virtual void OnMainDialogOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	AcDbIdMapping*		m_idMap;
    AcDbObjectIdArray	m_objIds;

		// helper functions
    void        displayCurrent();
	void		displayMapItems();
	void		buildMapItemColumns();

};

#endif    // ARXRLEUITDCIDMAP_H
