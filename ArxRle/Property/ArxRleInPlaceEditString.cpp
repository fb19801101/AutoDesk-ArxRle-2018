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

#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleInPlaceEditString.h"
#include "ArxRleUserMessage.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceEditString

IMPLEMENT_DYNAMIC(ArxRleInPlaceEditString, CAdUiEdit)


ArxRleInPlaceEditString::ArxRleInPlaceEditString(const CString& srtInitText) 
: ArxRleInPlaceEdit(srtInitText)
{
}

ArxRleInPlaceEditString::~ArxRleInPlaceEditString() 
{
}


void ArxRleInPlaceEditString::MoveControl(CRect& rect)
{
	rect.DeflateRect(0, 1);
	MoveWindow(rect, FALSE);
}

void ArxRleInPlaceEditString::ProcessData()
{
	GetOwner()->SendMessage(WM_USER_SET_DATA);
}

CWnd* ArxRleInPlaceEditString::CreateInPlaceEditString(const CString& strInitText, CWnd* pWndParent, CRect& rect, DWORD exDwStyle)
{
	ArxRleInPlaceEditString* pEdit = new ArxRleInPlaceEditString(strInitText);
	rect.DeflateRect(0, 1);
	pEdit->Create(WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_LEFT|exDwStyle, rect, pWndParent, 1);
	//pEdit->CreateEx(WS_EX_TRANSPARENT, _T("EDIT"), NULL, WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_LEFT|exDwStyle, rect, pWndParent, 1);

	return pEdit;
}