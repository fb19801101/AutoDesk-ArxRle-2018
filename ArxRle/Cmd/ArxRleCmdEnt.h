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

#ifndef ARXRLE_CMD_ENT_H
#define ARXRLE_CMD_ENT_H

#include "App\ArxRleCmd.h"

/****************************************************************************
**
**  CLASS ArxRleCmdEnt:
**
**  **000
**
*************************************/

class ArxRleCmdEnt : public ArxRleCmd {

public:
					ArxRleCmdEnt()	{}
    virtual			~ArxRleCmdEnt()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

	// static command functions
	static void entDelAll();
	static void entDelByLayer();
	static void entDelByColor();
	static void entCpyByDist();
	static void entCpyByAngle();
	static void entCpyByIf();
	static void entClrSetByLayer();
	static void entClrSetByColor();
	static void entClrSetByEntity();
	static void entLtSetByLayer();
	static void entLtSetByColor();
	static void entLtSetByEntity();
	static void entAttribute();
	static void entInfoTipShow();
	static void entInfoTipHide();
	static void entConvertTo2d();
};


#endif  // ARXRLE_CMD_ENT_H
