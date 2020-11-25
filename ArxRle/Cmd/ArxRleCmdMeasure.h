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

#ifndef ARXRLE_CMD_MEASURE_H
#define ARXRLE_CMD_MEASURE_H

#include "App\ArxRleCmd.h"

/****************************************************************************
**
**  CLASS ArxRleCmdMeasure:
**
**  **000
**
*************************************/

class ArxRleCmdMeasure : public ArxRleCmd {

public:
					ArxRleCmdMeasure()	{}
    virtual			~ArxRleCmdMeasure()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

	// static command functions
	static void measureDimXYZ();
	static void measureDimH();
	static void measureArea();
	static void measureLength();
	static void measureAllArea();
	static void measureAllLength();
};


#endif  // ARXRLE_CMD_MEASURE_H
