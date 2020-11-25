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

#ifndef ARXRLE_CMD_STRUCT_ANALYSIS_H
#define ARXRLE_CMD_STRUCT_ANALYSIS_H

#include "App\ArxRleCmd.h"


/****************************************************************************
**
**  CLASS ArxRleCmdStructAnalysis:
**
**  **000
**
*************************************/

class ArxRleCmdStructAnalysis : public ArxRleCmd {

public:
					ArxRleCmdStructAnalysis()	{}
    virtual			~ArxRleCmdStructAnalysis()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

		// static command functions
	static void	AnalysisConcrete();
	static void	AnalysisSteel();
	static void drawSteelSection();
};


#endif  // ARXRLE_CMD_STRUCT_ANALYSIS_H
