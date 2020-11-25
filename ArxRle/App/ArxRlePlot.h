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

#ifndef ARXRLE_PLOT_H
#define ARXRLE_PLOT_H

#include "dbplotsetval.h"

class ArxRlePlot
{
public:
	ArxRlePlot(CString strPath);
	virtual ~ArxRlePlot();

	void StartPlot();
	void BatPlot();

public:
	CString m_strDevice;
	CString m_strPath;
	AcDbPlotSettingsValidator* m_pPSV;
	AcDbPlotSettings* m_pPlotSettings;
	AcDbObjectId m_layoutId;
};

#endif // ARXRLE_PLOT_H
