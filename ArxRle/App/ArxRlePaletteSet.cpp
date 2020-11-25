//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//----- ArxRlePaletteSet.cpp : Implementation of ArxRlePaletteSet
//
//////////////////////////////////////////////////////////////////////////////
//

#include "StdAfx.h"
#include "resource.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRlePaletteSet.h"

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (ArxRlePaletteSet, CAdUiPaletteSet)

BEGIN_MESSAGE_MAP(ArxRlePaletteSet, CAdUiPaletteSet)
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
ArxRlePaletteSet::ArxRlePaletteSet () {
}

//-----------------------------------------------------------------------------
ArxRlePaletteSet::~ArxRlePaletteSet () {
}

BOOL ArxRlePaletteSet::Create(CWnd *pwndParent, CRect rect, LPCTSTR strTitle)
{
	if(!CAdUiPaletteSet::Create(strTitle, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN, rect,
		pwndParent, PSS_PROPERTIES_MENU | PSS_AUTO_ROLLUP | PSS_CLOSE_BUTTON | PSS_SNAP))
		return FALSE;
	return TRUE;
}

void ArxRlePaletteSet::ClearPalettes()
{
	int count = GetPaletteCount();
	for(int i=0; i<count; i++)
		RemovePalette(i);
}

//-----------------------------------------------------------------------------
//- Called by the palette set framework to determine size constraints.
//- Override these methods to provide minimum and maximum palette set sizes.
void ArxRlePaletteSet::GetMinimumSize (CSize &size) {
	//- Call the default implementation by default
	CAdUiPaletteSet::GetMinimumSize (size) ;
	size.cx = 100;
	size.cy = 100;
}

//-----------------------------------------------------------------------------
void ArxRlePaletteSet::GetMaximumSize (CSize &size) {
	//- Call the default implementation by default
	CAdUiPaletteSet::GetMaximumSize (size) ;
	size.cx = 400;
	size.cy = 400;
}

//-----------------------------------------------------------------------------
BOOL ArxRlePaletteSet::PreTranslateMessage (MSG *pMsg)
{
	if (pMsg->message == WM_CHAR || pMsg->message == WM_SYSCHAR )
		return CWnd::PreTranslateMessage(pMsg);
	else
		return CAdUiPaletteSet::PreTranslateMessage(pMsg);
}