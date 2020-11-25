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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleReferenceFiler.h"



ACRX_CONS_DEFINE_MEMBERS(ArxRleReferenceFiler, AcDbDwgFiler, 0);

/****************************************************************************
**
**  ArxRleReferenceFiler::writeHardOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleReferenceFiler::writeHardOwnershipId(const AcDbHardOwnershipId& id)
{
	if (id.isNull() == false)
		m_hardOwnershipIds.append(id);
	return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleReferenceFiler::writeSoftOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleReferenceFiler::writeSoftOwnershipId(const AcDbSoftOwnershipId& id)
{
	if (id.isNull() == false)
		m_softOwnershipIds.append(id);
	return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleReferenceFiler::writeHardPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleReferenceFiler::writeHardPointerId(const AcDbHardPointerId& id)
{
	if (id.isNull() == false)
		m_hardPointerIds.append(id);
	return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleReferenceFiler::writeSoftPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleReferenceFiler::writeSoftPointerId(const AcDbSoftPointerId& id)
{
	if (id.isNull() == false)
		m_softPointerIds.append(id);
	return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleReferenceFiler::reset
**
**  **jma
**
*************************************/

void
ArxRleReferenceFiler::reset()
{
    m_hardPointerIds.setLogicalLength(0);
    m_softPointerIds.setLogicalLength(0);
    m_hardOwnershipIds.setLogicalLength(0);
    m_softOwnershipIds.setLogicalLength(0);
}