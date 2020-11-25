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

#include "ArxRleSmartString.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRleSmartString

ArxRleSmartString::ArxRleSmartString(UINT nIdText)
{
	m_bCString = true;
	m_pStrText = new CString;

	#ifdef _DEBUG
	if(!m_pStrText->LoadString(nIdText))
		TRACE("\nError loading string %d", nIdText);
	#else
	m_pStrText->LoadString(nIdText);
	#endif
}

void ArxRleSmartString::SetCString(const CString& strText)
{
	m_bCString = true;
	m_pStrText = new CString(strText);
}

void ArxRleSmartString::SetLPCTSTR(LPCTSTR pText)
{
	m_bCString = false;
	m_pText = pText;
}

void ArxRleSmartString::Clear()
{
	if(m_bCString)
		delete m_pStrText;
	m_pStrText = NULL;
}

ArxRleSmartString::ArxRleSmartString(const ArxRleSmartString& d)
{
	if(d.m_bCString)
		SetCString(*d.m_pStrText);
	else
		SetLPCTSTR(d.m_pText);
}

ArxRleSmartString::~ArxRleSmartString()
{
	if(m_bCString)
		delete m_pStrText;
}

ArxRleSmartString& ArxRleSmartString::operator=(const ArxRleSmartString& data)
{
	Clear();

	if(data.m_bCString)
		SetCString(*data.m_pStrText);
	else
		SetLPCTSTR(data.m_pText);

	return *this;
}

/*
ArxRleSmartString& ArxRleSmartString::operator=(const CString& strText)
{
	Clear();
	SetCString(strText);

	return *this;
}
*/

ArxRleSmartString& ArxRleSmartString::operator=(LPCTSTR pData)
{
	Clear();
	SetLPCTSTR(pData);

	return *this;
}

ArxRleSmartString::operator LPCTSTR() const
{
	return m_bCString ? m_pStrText->operator LPCTSTR() : m_pText;
}
