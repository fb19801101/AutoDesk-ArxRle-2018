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

#ifndef ARXRLE_CMD_BLOCK_H
#define ARXRLE_CMD_BLOCK_H

#include "App\ArxRleCmd.h"

/****************************************************************************
**
**  CLASS ArxRleCmdBlock:
**
**  **000
**
*************************************/

class ArxRleCmdBlock : public ArxRleCmd {

public:
					ArxRleCmdBlock()	{}
    virtual			~ArxRleCmdBlock()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

	// static command functions
	static void blockTK();
	static void blockBTL();
	static void blockZBZ();
};


#endif  // ARXRLE_CMD_BLOCK_H
