//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#pragma message("Building debug version of this module to be used with non-debug/Prod AutoCAD")
//#define DEBUG_THIS_ONLY
#undef _DEBUG
#endif

#pragma warning(disable: 4275)

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxinet.h>
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>            // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#pragma warning(push)
#pragma warning(disable:4265)//disable missing virtual destructor warning
#include <afxdao.h>         // MFC DAO database classes
#pragma warning(pop) // C4265
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>            // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxdtctl.h>          // MFC support for Internet Explorer 4 Common Controls
#include <afxadv.h>			   // recent file list
#include <afxcview.h>		   // MFC support for Windows 95 Common Controls
#include <afxhtml.h>		   // MFC support for Windows 95 Common Controls

#include <math.h>
#include "acadafx.h"
#include "AcExtensionModule.h"

// Turn on the _DEBUG symbol if it was defined, before including
// non-MFC header files.
//
#ifdef DEBUG_THIS_ONLY
#define _DEBUG
#undef DEBUG_THIS_ONLY
#endif

#include "Ac64BitHelpers.h"
#include <afxcontrolbars.h>
#include "easysize.h"
#include "App/ArxRleCommon.h"

#pragma warning( disable : 4278)
#import "acax22ENU.tlb" no_implementation raw_interfaces_only named_guids
#pragma warning( default : 4278)
#include "CAcadApplication.h"
#include "CAcadDocument.h"
#include "CAcadModelSpace.h"
#include "CAcadMenuBar.h"
#include "CAcadMenuGroup.h"
#include "CAcadMenuGroups.h"
#include "CAcadPopupMenu.h"
#include "CAcadPopupMenuItem.h"
#include "CAcadPopupMenus.h"
#include "CAcadToolBars.h"
#include "CAcadToolBar.h"
#include "CAcadToolBarItem.h"

#include <XTToolkitPro.h>   // Codejock Software Components

inline bool intToBool(int intBoolVal)
{
	return (intBoolVal == 0) ? false : true;
}

inline int boolToInt(bool boolVal)
{
	return (boolVal == false) ? 0 : 1;
}

// ·¢ËÍÃüÁî¸øAutoCAD
inline void acedSendCommand(CString cmd)
{
	cmd.Format(L"_%s\n", cmd);
	acDocManagerPtr()->sendStringToExecute(curDoc(),cmd,false,true);
}

inline void acedSendCommand(const char* cmd)
{
	CString str;
	str.Format(L"%s", cmd);
	COPYDATASTRUCT cmdMsg;
	cmdMsg.dwData = (DWORD)1;
	cmdMsg.cbData = (DWORD)_tcslen(str) + 1;
	cmdMsg.lpData = str.GetBuffer(str.GetLength()+1) ;                   
	SendMessage(adsw_acadMainWnd(), WM_COPYDATA, (WPARAM)adsw_acadMainWnd(), (LPARAM)&cmdMsg);
}

extern Adesk::Boolean acedPostCommand(const char*); 
extern Adesk::Boolean acedPostCommand(const ACHAR*);

