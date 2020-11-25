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

#ifndef ARXRLE_CMD_NETPLAN_WORK_H
#define ARXRLE_CMD_NETPLAN_WORK_H

#include "App\ArxRleCmd.h"

/****************************************************************************
**
**  CLASS ArxRleCmdNetPlanWork:
**
**  **000
**
*************************************/

class ArxRleNetPlanDataItem;
class ArxRleNetPlanWorkItem;
class ArxRleCmdNetPlanWork : public ArxRleCmd {

public:
					ArxRleCmdNetPlanWork()	{}
    virtual			~ArxRleCmdNetPlanWork()	{}

    virtual void	registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname);    // no op

		// static command functions
	static void	initParam();
	static void	importWork();
	static void	exportWork();
	static void	importStyle();
	static void	exportStyle();
	static void	insertGrid();
	static void	insertTable();
	static void	batchWork();
	static void	batchProc();
	static void	reSetProc();
	static void	reNumber();
	static void	bindWork();
	static void	flushStyle();
	static void	cmdLineWork();
	static void	workAdd();
	static void cmdLineModify();
	static void modifyWorkInfo();
	static void modifyWorkNodes();
	static void modifyWorkDays();
	static void modifyWorkName();
	static void modifyWorkStyle();
	static void	cmdLineStyle();
	static void	styleAdd();
	static void	styleModify();
	static void	styleCopy();
	static void	styleDelete();
	static void styleCommon();

	static vector<ArxRleNetPlanWorkItem> m_itemNetPlanWorkList;
};


#endif  // ARXRLE_CMD_NETPLAN_WORK_H
