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

#ifndef ARXRLE_CMD_DRAW_H
#define ARXRLE_CMD_DRAW_H

#include "App\ArxRleCmd.h"

/****************************************************************************
**
**  CLASS ArxRleCmdDraw:
**
**  **000
**
*************************************/

class ArxRleCmdDraw : public ArxRleCmd {

public:
					ArxRleCmdDraw()	{}
    virtual			~ArxRleCmdDraw()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

	// static command functions
	static void drawHatch();
	static void drawNumber();
};


#endif  // ARXRLE_CMD_DRAW_H
