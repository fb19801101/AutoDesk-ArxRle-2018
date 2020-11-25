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

#ifndef ARXRLECMD_H
#define ARXRLECMD_H

/****************************************************************************
**
**  CLASS ArxRleCmd:
**
**  **jma
**
*************************************/

class ArxRleCmd {

public:
					ArxRleCmd()	    {}
    virtual			~ArxRleCmd()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)   {}

};


#endif    // ARXRLECMD_H
