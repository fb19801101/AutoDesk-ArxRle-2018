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

#ifndef ARXRLEUITDCDOCS_H
#define ARXRLEUITDCDOCS_H

#include "Resource.h"
#include "ArxRleUiTdcRxObjectBase.h"

/****************************************************************************
**
**	CLASS ArxRleUiTdcDocs:
**
**	**jma
**
*************************************/

class ArxRleUiTdcDocs : public ArxRleUiTdcRxObjectBase {

public:
				ArxRleUiTdcDocs();
				ArxRleUiTdcDocs(AcApDocument* doc);	// just show a specific document
    virtual		~ArxRleUiTdcDocs()    {}

    //{{AFX_DATA(ArxRleUiTdcDocs)
    enum { IDD = ARXRLE_TDC_DOCS };
    CListBox	m_docList;
    CListCtrl	m_dataList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcDocs)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcDocs)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangeDocs();
    afx_msg void OnDatabase();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
		// data members
    AcDbVoidPtrArray	m_docPtrs;
    int                 m_curIndex;

		// helper functions
	void		fillListBox(int defIndex);
    void        displayCurrent(int index);
};

#endif    // ARXRLEUITDCDOCS_H
