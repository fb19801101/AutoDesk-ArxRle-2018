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

#ifndef ARXRLE_CMD_DIM_H
#define ARXRLE_CMD_DIM_H

#include "App\ArxRleCmd.h"

/****************************************************************************
**
**  CLASS ArxRleCmdDim:
**
**  **000
**
*************************************/

class ArxRleCmdDim : public ArxRleCmd {

public:
					ArxRleCmdDim()	{}
    virtual			~ArxRleCmdDim()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

	// static command functions
	static void dimSetCur();
	static void dimShowAll();
	static void dimHideAll();
	static void dimHidePart();
	static void dimShowByStyle();
	static void dimHideByStyle();
	static void dimEntity();
	static void dimSection();
	static void dimSetStr();
};


#endif  // ARXRLE_CMD_DIM_H
