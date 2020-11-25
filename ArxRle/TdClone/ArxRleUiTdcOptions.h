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


#ifndef ARXRLEUITDCOPTIONS_H
#define ARXRLEUITDCOPTIONS_H

#include "Resource.h"

/****************************************************************************
**
**  CLASS ArxRleUiTdcOptions:
**
**  **jma
**
*************************************/

class ArxRleUiTdcOptions : public CAcUiTabChildDialog {

public:
		ArxRleUiTdcOptions(CWnd* pParent = NULL);

	//{{AFX_DATA(ArxRleUiTdcOptions)
	enum { IDD = ARXRLE_TDC_OPTIONS };
	BOOL	m_showDwgFilerMsgs;
	BOOL	m_showWblockCloneDetails;
	BOOL	m_showDeepCloneDetails;
	BOOL	m_doDictInsertByHand;
	//}}AFX_DATA

public:
    virtual void OnMainDialogOK();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRleUiTdcOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(ArxRleUiTdcOptions)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // ARXRLEUITDCOPTIONS_H
