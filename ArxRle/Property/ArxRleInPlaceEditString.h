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

#ifndef ARXRLE_INPLACE_EDIT_STRING_H
#define ARXRLE_INPLACE_EDIT_STRING_H


#include "ArxRleInPlaceControl.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceEditString

class ArxRleInPlaceEditString : public ArxRleInPlaceEdit
{
	ArxRleInPlaceEditString(const ArxRleInPlaceEditString& d);
	ArxRleInPlaceEditString& operator=(const ArxRleInPlaceEditString& d);
protected:
	DECLARE_DYNAMIC(ArxRleInPlaceEditString)

public:
	ArxRleInPlaceEditString(const CString& srtInitText);
	~ArxRleInPlaceEditString();

	// Operations
	virtual void ProcessData();
	void MoveControl(CRect& rect);

	static CWnd* CreateInPlaceEditString(const CString& strInitText, CWnd* pWndParent, CRect& rect, DWORD exDwStyle = 0);
};

#endif // ARXRLE_INPLACE_EDIT_STRING_H