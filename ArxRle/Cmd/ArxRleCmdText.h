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

#ifndef ARXRLE_CMD_TEXT_H
#define ARXRLE_CMD_TEXT_H

#include "App\ArxRleCmd.h"

/****************************************************************************
**
**  CLASS ArxRleCmdText:
**
**  **000
**
*************************************/

class ArxRleCmdText : public ArxRleCmd {

public:
					ArxRleCmdText()	{}
    virtual			~ArxRleCmdText() {}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

	// static command functions
	static void textSetCur();
	static void textStyles();
	static void textShowAll();
	static void textHideAll();
	static void textHidePart();
	static void textShowByStyle();
	static void textHideByStyle();
	static void textShowByHeight();
	static void textHideByHeight();
	static void textShowByAngle();
	static void textHideByAngle();
	static void textShowByStr();
	static void textHideByStr();
	static void textFlush();
	static void textCalc();
	static void textImport();
	static void textExport();
};


#endif  // ARXRLE_CMD_TEXT_H
