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

#include "ArxRleGsReactor.h"

//ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleGsReactor, AcGsReactor); TBD: not derived off of AcRxObject yet!

/****************************************************************************
**
**  ArxRleGsReactor::ArxRleGsReactor
**
**  **jma
**
*************************************/

ArxRleGsReactor::ArxRleGsReactor()
{
// TBD: this isn't really good enough... it needs to get all CViews, not just
// the one that is current... will finish off later.
    AcGsKernelDescriptor descriptor;
    descriptor.addRequirement(AcGsKernelDescriptor::k3DDrawing);
    m_pGraphicsKernel = AcGsManager::acquireGraphicsKernel(descriptor);
    if (m_pGraphicsKernel)
        m_pGraphicsKernel->addReactor(this);
}

/****************************************************************************
**
**  ArxRleGsReactor::~ArxRleGsReactor
**
**  **jma
**
*************************************/

ArxRleGsReactor::~ArxRleGsReactor()
{
    if (m_pGraphicsKernel) {
        m_pGraphicsKernel->removeReactor(this);
        AcGsManager::releaseGraphicsKernel(m_pGraphicsKernel);
    }
}

/****************************************************************************
**
**  ArxRleGsReactor::viewWasCreated
**
**  **jma
**
*************************************/

void
ArxRleGsReactor::viewWasCreated(AcGsView* pView)
{
    printReactorMessage(_T("View Was Created"));
}

/****************************************************************************
**
**  ArxRleGsReactor::viewToBeDestroyed
**
**  **jma
**
*************************************/

void
ArxRleGsReactor::viewToBeDestroyed(AcGsView* pView)
{
    printReactorMessage(_T("View To Be Destroyed"));
}

/****************************************************************************
**
**  ArxRleGsReactor::gsToBeUnloaded
**
**  **jma
**
*************************************/

void
ArxRleGsReactor::gsToBeUnloaded(AcGsGraphicsKernel* pGraphicsKernel)
{
    printReactorMessage(_T("GS To Be Unloaded"));
}

/****************************************************************************
**
**  ArxRleGsReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleGsReactor::printReactorMessage(LPCTSTR event) const
{
    acutPrintf(_T("\n%-15s : [%s] "), _T("[GS REACTOR]"), event);
}
