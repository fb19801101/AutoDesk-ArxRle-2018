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

#ifndef ARXRLE_CMD_LAYER_H
#define ARXRLE_CMD_LAYER_H

#include "App\ArxRleCmd.h"

/****************************************************************************
**
**  CLASS ArxRleCmdLayer:
**
**  **000
**
*************************************/

class ArxRleCmdLayer : public ArxRleCmd {

public:
					ArxRleCmdLayer()	{}
    virtual			~ArxRleCmdLayer()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

	// static command functions
	static void layerSetCur();
	static void layerShowAll();
	static void layerHideAll();
	static void layerHidePart();
	static void layerShowByLayer();
	static void layerHideByLayer();
	static void layerShowByColor();
	static void layerHideByColor();
	static void layerLock();
	static void layerUnLock();
};

#endif  // ARXRLE_CMD_NETPLAN_WORK_H
