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

#ifndef ARXRLEUITDMTRANSDBCLONES_H
#define ARXRLEUITDMTRANSDBCLONES_H

#include "Resource.h"
#include "Snoop/ArxRleCloneSet.h"

class ArxRleUiTdcCloneSet;
class ArxRleUiTdcWblockClone;
class ArxRleUiTdcInsert;


/****************************************************************************
**
**	CLASS ArxRleUiTdmTransDbClones:
**
**	**jma
**
*************************************/

class ArxRleUiTdmTransDbClones : public CAcUiTabMainDialog {

public:
            ArxRleUiTdmTransDbClones(CWnd* parent, const TCHAR* winTitle = NULL);
	virtual	~ArxRleUiTdmTransDbClones();

	void	addToCloneSet(ArxRleCloneSet& cloneSet);	// ugly hacks since child dialogs can't call BeginEditorCommand()
	void	getBasePoint(AcGePoint3d& basePt);

    //{{AFX_DATA(ArxRleUiTdmTransDbClones)
    enum { IDD = ARXRLE_TDM_TRANSDB_CLONES };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdmTransDbClones)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdmTransDbClones)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	CString					m_winTitle;
	ArxRleUiTdcCloneSet*	m_tdcCloneSet;
	ArxRleUiTdcWblockClone*	m_tdcWblockClone;
	ArxRleUiTdcInsert*		m_tdcInsert;
};

#endif // ARXRLEUITDMTRANSDBCLONES_H

