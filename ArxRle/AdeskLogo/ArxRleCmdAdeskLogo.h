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

#ifndef ARXRLECMDADESKLOGO_H
#define ARXRLECMDADESKLOGO_H

#include "App/ArxRleCmd.h"

/****************************************************************************
**
**  CLASS ArxRleCmdAdeskLogo:
**
**  **jma
**
*************************************/

class ArxRleCmdAdeskLogo : public ArxRleCmd {

public:
					ArxRleCmdAdeskLogo()	{}
    virtual			~ArxRleCmdAdeskLogo()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

		// static command functions
	static void	cmdLineMain();
	static void	add();
	static void modify();
	static void	styles();
	static void hardwire();
	static void hardwire2();
	static void	styleAdd();
	static void	styleModify();

	static bool	getLogoStyle(AcDbObjectId& styleId);
};


#endif    // ARXRLECMDADESKLOGO_H
