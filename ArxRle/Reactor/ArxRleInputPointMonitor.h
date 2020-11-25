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

#ifndef ARXRLE_INPUTPOINT_MONITOR_H
#define ARXRLE_INPUTPOINT_MONITOR_H

/****************************************************************************
**
**  CLASS ArxRleInputPointMonitor:
**
**  **000
**
*************************************/

class ArxRleInputPointMonitor : public AcEdInputPointMonitor
{
public:
	ACRX_DECLARE_MEMBERS(ArxRleInputPointMonitor);

	ArxRleInputPointMonitor();
	virtual ~ArxRleInputPointMonitor();

protected:
	// 监控输入点信息
	virtual Acad::ErrorStatus monitorInputPoint(const AcEdInputPoint& input, AcEdInputPointMonitorResult& output);

	// 计算需要从自动捕捉中排除的实体
	virtual bool excludeFromOsnapCalculation(const AcArray<AcDbObjectId>& nestedEntity,
		int gsSelectionMark);

private:
	// outlawed functions
	ArxRleInputPointMonitor(const ArxRleInputPointMonitor &copy);
	ArxRleInputPointMonitor& operator=(const ArxRleInputPointMonitor &copy);


	// static functions for constructing/retrieving/destroying singleton instance
public:
	static ArxRleInputPointMonitor*  getInstance();
	static void                     destroyInstance();

private:
	static ArxRleInputPointMonitor*  m_instance;        // singleton instance
};

#endif // ARXRLE_INPUTPOINT_MONITOR_H
