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


#ifndef ARXRLECMDREACTORS_H
#define ARXRLECMDREACTORS_H

#include "App/ArxRleCmd.h"

/****************************************************************************
**
**  CLASS ArxRleCmdReactors:
**
**  **jma
**
*************************************/

class ArxRleCmdReactors : public ArxRleCmd {

public:
					ArxRleCmdReactors()		{}
    virtual			~ArxRleCmdReactors()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

		// static command functions
	static void	reactors();
};


#endif    // ARXRLECMDREACTORS_H
