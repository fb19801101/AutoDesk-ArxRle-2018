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

#ifndef ARXRLEUITDCWBLOCKCLONE_H
#define ARXRLEUITDCWBLOCKCLONE_H

#include "Resource.h"
#include "Snoop/ArxRleCloneSet.h"
#include "AcadUtils/ArxRleSdStrObjId.h"

/****************************************************************************
**
**	CLASS ArxRleUiTdcWblockClone:
**
**	**jma
**
*************************************/

class ArxRleUiTdcWblockClone : public CAcUiTabChildDialog {

public:
				ArxRleUiTdcWblockClone();
    virtual		~ArxRleUiTdcWblockClone()    {}

    //{{AFX_DATA(ArxRleUiTdcWblockClone)
    enum { IDD = ARXRLE_TDC_WBLOCK };
	CListBox			m_lbSourceDb;
	CListBox			m_lbDestDb;
    CAcUiPickButton		m_pickPtButton;
	BOOL				m_doForceCopy;
	BOOL				m_saveAsDwg;
	int					m_puBlockDefIndex;
	CComboBox			m_puBlockDef;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdcWblockClone)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    //}}AFX_VIRTUAL

protected:

    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdcWblockClone)
    afx_msg void OnWblockObjects();
    afx_msg void OnWblockBlkDef();
    afx_msg void OnWblockAll();
    afx_msg void OnPickBasePt();
	afx_msg void OnSourceDatabaseChanged();
	afx_msg void OnDestDatabaseChanged();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	AcDbVoidPtrArray	m_dbPtrs;
	ArxRleCloneSet&		m_cloneSet;
	AcGePoint3d			m_basePt;
	ArxRleSdStrObjIdList		m_blockList;

        // helper functions
	void			setButtonModes();
	void			displayDbLists();
	void			fillBlockList();
	AcDbDatabase*	getSourceDb();
	AcDbDatabase*	getDestDb();
	void			doSaveOption(AcDbDatabase* tmpDb);
	void			doInsertOption(AcDbDatabase* tmpDb);
	void			divideCloneSet(const AcDbObjectIdArray& cloneSet,
                            AcDbObjectIdArray& nonEntSet,
                            AcDbObjectIdArray& okToCloneSet);
};

#endif    // ARXRLEUITDCWBLOCKCLONE_H
