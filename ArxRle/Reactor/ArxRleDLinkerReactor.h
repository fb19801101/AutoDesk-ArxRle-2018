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

#ifndef ARXRLEDLINKERREACTOR_H
#define ARXRLEDLINKERREACTOR_H

/****************************************************************************
**
**  CLASS ArxRleDLinkerReactor:
**
**  **jma
**
*************************************/

class ArxRleDLinkerReactor : public AcRxDLinkerReactor {

public:
	ACRX_DECLARE_MEMBERS(ArxRleDLinkerReactor);

        // constructors/destructor
					ArxRleDLinkerReactor();
    virtual			~ArxRleDLinkerReactor();

    virtual void	rxAppWillBeLoaded(const TCHAR* moduleName);
    virtual void	rxAppLoaded(const TCHAR* moduleName);
    virtual void	rxAppLoadAborted(const TCHAR* moduleName);

    virtual void	rxAppWillBeUnloaded(const TCHAR* moduleName);
    virtual void	rxAppUnloaded(const TCHAR* moduleName);
    virtual void	rxAppUnloadAborted(const TCHAR* moduleName);

private:
    void    printReactorMessage(LPCTSTR event, const TCHAR* moduleName) const;

        // outlawed functions
    ArxRleDLinkerReactor(const ArxRleDLinkerReactor &copy);
    ArxRleDLinkerReactor&	operator=(const ArxRleDLinkerReactor &copy);        
};


#endif    // ARXRLEDLINKERREACTOR_H
