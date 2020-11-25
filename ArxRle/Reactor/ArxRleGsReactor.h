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

#ifndef ARXRLEGSREACTOR_H
#define ARXRLEGSREACTOR_H

/****************************************************************************
**
**  CLASS ArxRleGsReactor:
**
**  **jma
**
*************************************/

class ArxRleGsReactor : public AcGsReactor {

public:
    //ACRX_DECLARE_MEMBERS(ArxRleGsReactor); TBD: not derived off of AcRxObject yet!

                 ArxRleGsReactor();
    virtual     ~ArxRleGsReactor();

    virtual void viewWasCreated(AcGsView* pView);
    virtual void viewToBeDestroyed(AcGsView* pView);
    virtual void gsToBeUnloaded(AcGsGraphicsKernel* pGraphicsKernel);

private:
    void printReactorMessage(LPCTSTR event) const;
    class AcGsGraphicsKernel *m_pGraphicsKernel;

    // outlawed functions
    ArxRleGsReactor(const ArxRleGsReactor &copy);
    ArxRleGsReactor& operator=(const ArxRleGsReactor &copy);
};


#endif    // ARXRLEGSREACTOR_H
