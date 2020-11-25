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
#include "StdAfx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleDataManager.h"
#include "ArxRleDocData.h"

// The one and only document manager object
// You can use the DocVars object to retrieve
// document specific data throughout your application
ArxRleDataManager<ArxRleDocData> ArxRleDocData::m_mgrDocVars;


//
// Implementation of the document data class.
//
ArxRleDocData::ArxRleDocData()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_DATA_INIT(ArxRleDocData)
	//}}AFX_ARX_DATA_INIT

	// TODO: add your own initialization.
	m_dWindHt = 20.0;
	m_dWindWt = 20.0;
	m_nCols		= 1;
	m_nRows		= 1;
	m_nWindType	= 0; // Default Rect
	m_startPt.set(0.0, 0.0);
}

ArxRleDocData::~ArxRleDocData()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_DATA_DEL(ArxRleDocData)
	//}}AFX_ARX_DATA_DEL

	// TODO: clean up.
}