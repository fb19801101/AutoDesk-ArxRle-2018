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

#ifndef ARXRLE_SMART_STRING_H
#define ARXRLE_SMART_STRING_H

/////////////////////////////////////////////////////////////////////////////
// ArxRleSmartString

class ArxRleSmartString
{
	// Constuctors and d-tor
public:
	ArxRleSmartString(LPCTSTR pText = NULL);
	ArxRleSmartString(UINT nIdText);
	ArxRleSmartString(const ArxRleSmartString& d);

	~ArxRleSmartString();

	// Operators
	ArxRleSmartString& operator=(const ArxRleSmartString& data);
	ArxRleSmartString& operator=(LPCTSTR pData);

	operator LPCTSTR() const;

	// Operations
protected:
	void SetCString(const CString& strText);
	void SetLPCTSTR(LPCTSTR pText);
	void Clear();
	
	// Data
private:
	union 
	{
		CString* m_pStrText;
		LPCTSTR m_pText;
	};
	bool m_bCString;
};

inline ArxRleSmartString::ArxRleSmartString(LPCTSTR pText)
{	
	SetLPCTSTR(pText);
}

#endif // ARXRLE_SMART_STRING_H