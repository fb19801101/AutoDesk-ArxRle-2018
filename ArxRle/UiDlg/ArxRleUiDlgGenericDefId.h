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

#ifndef ARXRLEUIDLGGENERICDEFID_H
#define ARXRLEUIDLGGENERICDEFID_H

#include "Resource.h"
#include "AcadUtils/ArxRleSdStrObjId.h"

/****************************************************************************
**
**	CLASS ArxRleUiDlgGenericDefId:
**
**	**jma
**
*************************************/

class ArxRleUiDlgGenericDefId : public CAcUiDialog {

public:
				ArxRleUiDlgGenericDefId(CWnd* pParent,
								ArxRleSdStrObjIdList& entries,
                                const AcDbObjectId& currentValue,
                                bool allowNone);

                ArxRleUiDlgGenericDefId(CWnd* pParent,
                                ArxRleSdStrObjIdList& entries,
                                const AcDbObjectIdArray& currentValues,
                                bool allowNone);

    virtual     ~ArxRleUiDlgGenericDefId();

        // must be called before DoModal()
    void            setDboxTitle(const CString& title) { m_title = title; }
    void            setPrompt(const CString& prompt)   { m_prompt = prompt; }

        // use these after DoModal() call to find out what was selected
    LPCTSTR         getSelectedName (CString& name) const;
    AcDbObjectId    getSelectedId() const;

    bool            isVaries() const;
    bool            isNone() const;

    //{{AFX_DATA(ArxRleUiDlgGenericDefId)
    enum { IDD = ARXRLE_DLG_GENERIC_DEF_ID };
    CListCtrl    m_lcDefIds;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgGenericDefId)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:

    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgGenericDefId)
    afx_msg void OnListItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
    virtual BOOL OnInitDialog();
    afx_msg void OnDblclickList(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    ArxRleSdStrObjIdList&	m_entries;
    int             m_curIndex;
    bool            m_hasVaries;
    bool            m_hasNone;
    CString         m_title;
    CString         m_prompt;

        // helper functions
    void            buildColumns();
    void            fillList();

};

#endif    // ARXRLEUIDLGGENERICDEFID_H
