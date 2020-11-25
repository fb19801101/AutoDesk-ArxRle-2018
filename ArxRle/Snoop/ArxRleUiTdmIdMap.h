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

#ifndef ARXRLEUITDMIDMAP_H
#define ARXRLEUITDMIDMAP_H

#include "Resource.h"

class ArxRleUiTdcIdMap;


/****************************************************************************
**
**	CLASS ArxRleUiTdmIdMap:
**
**	**jma
**
*************************************/

class ArxRleUiTdmIdMap : public CAcUiTabMainDialog {

public:
            ArxRleUiTdmIdMap(AcDbIdMapping* idMap, CWnd* parent, const TCHAR* winTitle = NULL);
	virtual	~ArxRleUiTdmIdMap();

    //{{AFX_DATA(ArxRleUiTdmIdMap)
    enum { IDD = ARXRLE_TDM_IDMAP };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdmIdMap)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdmIdMap)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	CString				m_winTitle;
	ArxRleUiTdcIdMap*	m_tdcIdMap;
};

#endif // ARXRLEUITDMIDMAP_H

