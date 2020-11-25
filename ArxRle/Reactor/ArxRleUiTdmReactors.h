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

#ifndef ARXRLEUITDMREACTORS_H
#define ARXRLEUITDMREACTORS_H

#include "Resource.h"

class ArxRleUiTdcSysReactors;
class ArxRleUiTdcTransientReactors;
class ArxRleUiTdcPersistentReactors;
class ArxRleTransientEntReactor;


/****************************************************************************
**
**	CLASS ArxRleUiTdmReactors:
**
**	**jma
**
*************************************/

class ArxRleUiTdmReactors : public CAcUiTabMainDialog {

public:
            ArxRleUiTdmReactors(CWnd* pParent);
	virtual	~ArxRleUiTdmReactors();

	void	attachEntTransientReactor(ArxRleTransientEntReactor* entReactor);
	void	detachEntTransientReactor(ArxRleTransientEntReactor* entReactor);

	void	attachEntPersistentReactor();
	void	detachEntPersistentReactor();

    //{{AFX_DATA(ArxRleUiTdmReactors)
    enum { IDD = ARXRLE_TDM_REACTORS };
	CAdUiTab	m_tabCtrl;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiTdmReactors)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiTdmReactors)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	ArxRleUiTdcSysReactors*			m_tdcSysReactors;
	ArxRleUiTdcTransientReactors*	m_tdcTransientReactors;
	ArxRleUiTdcPersistentReactors*	m_tdcPersistentReactors;

		// statics
public:
    static void cleanUpReactors();
	static bool	hasPersistentReactor(AcDbObject* obj, const AcDbObjectId& reactorId);

};

#endif // ARXRLEUITDMREACTORS_H

