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

#ifndef ARXRLE_CMD_EXENTITY_H
#define ARXRLE_CMD_EXENTITY_H

#include "App\ArxRleCmd.h"

/****************************************************************************
**
**  CLASS ArxRleCmdExEntity:
**
**  **000
**
*************************************/

class ArxRleCmdExEntity : public ArxRleCmd {

public:
					ArxRleCmdExEntity()	{}
    virtual			~ArxRleCmdExEntity()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

		// static command functions
	static void	cmdLineTitle();
	static void	cmdLineBroken();
	static void	cmdLineLeadDimension();
	static void addTitle();
	static void modifyTitle();
	static void addBroken();
	static void modifyBroken();
	static void addLeadDimension();
	static void modifyLeadDimension();
	static void changeToPolyline();
};


#endif  // ARXRLE_CMD_EXENTITY_H
