//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef ARXRLEMSGHANDLER_H
#define ARXRLEMSGHANDLER_H

/****************************************************************************
**
**  CLASS ArxRleMsgHandler:
**
**  **jma
**
*************************************/

#include "ArxRleToolBar.h"

class ArxRleMsgHandler : public CWnd {
	DECLARE_DYNAMIC (ArxRleMsgHandler)

public:
	ArxRleMsgHandler();

public:
	//{{AFX_VIRTUAL(ArxRleMsgHandler)
	//}}AFX_VIRTUAL
	static BOOL CreateMsgHandler();
	static void DestroyMsgHandler();
	static ArxRleMsgHandler* GetMsgHandler();
	static ArxRleMsgHandler *m_pMsgHandler;

public:
	virtual ~ArxRleMsgHandler();

protected:
	//{{AFX_MSG(ArxRleMsgHandler)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnToolBarCommands(UINT nID);
	afx_msg void OnUpdateToolBarCommands(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	ArxRleToolBar* m_pToolbar;
};

#endif //ARXRLEMSGHANDLER_H
