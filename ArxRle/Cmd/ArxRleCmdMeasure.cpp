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
#include "stdafx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleCmdMeasure.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleSelSet.h"
#include "AcadUtils\ArxRleApply.h"
#include "Prompt\ArxRleKeywordArray.h"
#include "DbEntity\ArxRleEntityClass.h"

extern void measureCrdTrm();
extern void measureCurve();
extern void measurePtInData();
extern void measurePtOutData();


/****************************************************************************
**
**  ArxRleCmdMeasure::registerCommandLineFunctions
**
**  **000
**
*************************************/

void ArxRleCmdMeasure::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{																			    
	cmdStack->addCommand(appname, _T("ArxRleMeasureCrdTrm"),         _T("MeasureCrdTrm"),         ACRX_CMD_MODAL, &measureCrdTrm);
	cmdStack->addCommand(appname, _T("ArxRleMeasureCurve"),          _T("MeasureCurve"),          ACRX_CMD_MODAL, &measureCurve);
	cmdStack->addCommand(appname, _T("ArxRleMeasurePtInData"),       _T("MeasurePtInData"),       ACRX_CMD_MODAL, &measurePtInData);
	cmdStack->addCommand(appname, _T("ArxRleMeasurePtOutData"),      _T("MeasurePtOutData"),      ACRX_CMD_MODAL, &measurePtOutData);
	cmdStack->addCommand(appname, _T("ArxRleMeasureDimXYZ"),         _T("MeasureDimXYZ"),         ACRX_CMD_MODAL, &measureDimXYZ);
	cmdStack->addCommand(appname, _T("ArxRleMeasureDimH"),           _T("MeasureDimH"),           ACRX_CMD_MODAL, &measureDimH);
	cmdStack->addCommand(appname, _T("ArxRleMeasureArea"),           _T("MeasureArea"),           ACRX_CMD_MODAL, &measureArea);
	cmdStack->addCommand(appname, _T("ArxRleMeasureLength"),         _T("MeasureLenght"),         ACRX_CMD_MODAL, &measureLength);
	cmdStack->addCommand(appname, _T("ArxRleMeasureAllArea"),        _T("MeasureAllArea"),        ACRX_CMD_MODAL, &measureAllArea);
	cmdStack->addCommand(appname, _T("ArxRleMeasureAllLength"),      _T("MeasureAllLenght"),      ACRX_CMD_MODAL, &measureAllLength);
}

/****************************************************************************
**
**  ArxRleCmdMeasure::measureDimXYZ
**
**  **000
**
*************************************/

void ArxRleCmdMeasure::measureDimXYZ()
{
	ArxRleUiPrIntDef prType(_T("请输入坐标类型 1.X,Y,Z  2.E,N,H "), NULL, ArxRleUiPrInt::kAny, 1);
	if (prType.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrDoubleDef prHeight(_T("请输入文字高度 "), NULL, ArxRleUiPrDouble::kAny, 2.5);
	if (prHeight.go() != ArxRleUiPrBase::kOk)
		return;

	AddLayer("arx_xyz", 4);
	SetCurLayer("arx_xyz");
	AddTextStyle("arx_xyz");
	SetCurTextStyle("arx_xyz");

	while (1)
	{
		ArxRleUiPrPoint prPt(_T("Point1"), NULL);
		if (prPt.go() != ArxRleUiPrBase::kOk)
			return;

		CPt3d pt = prPt.value();
		if (isUcs()) pt = U2W(prPt.value());

		double height = prHeight.value();
		CPt3d pt1 = pt.GetLineEnd(height * 2, PI / 3);
		CPt3d pt2 = pt.GetLineEnd(height * 2, 2 * PI / 3);
		CPt3d pt3 = pt1.GetLineEnd(height * 15, pt2.GetAngle(pt1));
		AddLine(pt, pt1);
		AddLine(pt1, pt3);

		ArxRleString xyz = ArxRleString(pt1.sPt());
		AddText(xyz, pt1.GetLineEnd(height/2, PI/2), height, pt2.GetAngle(pt1), ArxLeftBottom);
	}
}

/****************************************************************************
**
**  ArxRleCmdMeasure::measureDimH
**
**  **000
**
*************************************/

void ArxRleCmdMeasure::measureDimH()
{
	ArxRleUiPrDoubleDef prHeight(_T("请输入文字高度 "), NULL, ArxRleUiPrDouble::kAny, 2.5);
	if (prHeight.go() != ArxRleUiPrBase::kOk)
		return;

	AddLayer("arx_xyz", 4);
	SetCurLayer("arx_xyz");
	AddTextStyle("arx_xyz");
	SetCurTextStyle("arx_xyz");

	while (1)
	{
		ArxRleUiPrPoint prPt(_T("Point"), NULL);
		if (prPt.go() != ArxRleUiPrBase::kOk)
			return;

		CPt3d pt = prPt.value();

		if (isUcs()) pt = U2W(prPt.value());

		double height = prHeight.value();
		CPt3d pt1 = pt.GetLineEnd(height, PI / 3);
		CPt3d pt2 = pt.GetLineEnd(height, 2 * PI / 3);
		CPt3d pt3 = pt1.GetLineEnd(height * 3, pt2.GetAngle(pt1));
		AddLine(pt, pt1);
		AddLine(pt2, pt3);
		AddLine(pt2, pt);
		ArxRleString xyz = ArxRleString(pt.sPt(2));
		AddText(xyz, pt1.GetLineEnd(height/2, PI/2), height, pt2.GetAngle(pt1), ArxLeftBottom);
	}
}

/****************************************************************************
**
**  ArxRleCmdMeasure::measureArea
**
**  **000
**
*************************************/

void ArxRleCmdMeasure::measureArea()
{
	ArxRleUiPrEntity prEnt(_T("Select Polyline Ref"), NULL);
	prEnt.addAllowedClass(AcDbPolyline::desc());
	prEnt.setFilterLockedLayers(true);

	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	AcDbPolyline* pline = new AcDbPolyline;
	Acad::ErrorStatus es = acdbOpenObject(pline, prEnt.objectId(), AcDb::kForRead);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete pline;
		return;
	}

	double area = 0;
	pline->getArea(area);
	_printf(_T("\n面积= %.3f 平米  %.3f 亩"),area,area/666.7);
	pline->close();
}

/****************************************************************************
**
**  ArxRleCmdMeasure::measureLength
**
**  **000
**
*************************************/

void ArxRleCmdMeasure::measureLength()
{
	ArxRleUiPrEntity prEnt(_T("Select Polyline Ref"), NULL);
	prEnt.addAllowedClass(AcDbPolyline::desc());
	prEnt.setFilterLockedLayers(true);

	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrPoint prPt1(_T("BeginPt"), NULL);
	if(prPt1.go() != ArxRleUiPrBase::kOk)
		return;
	ArxRleUiPrPoint prPt2(_T("EndPt"), NULL);
	if(prPt2.go() != ArxRleUiPrBase::kOk)
		return;

	AcDbPolyline* pline = new AcDbPolyline;
	Acad::ErrorStatus es = acdbOpenObject(pline, prEnt.objectId(), AcDb::kForRead);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete pline;
		return;
	}

	AcGePoint3d pt1 = prPt1.value(), pt2 = prPt2.value();
	double length1 = 0,length2 = 0;
	if(isUcs())
	{
		pt1 = U2W(prPt1.value());
		pt2 = U2W(prPt2.value());
	}

	pline->getDistAtPoint(pt1,length1);
	pline->getDistAtPoint(pt2,length2);
	_printf(_T("\n距离= %.3f 单位"),fabs(length2-length1));
	pline->close();
}

/****************************************************************************
**
**  ArxRleCmdMeasure::measureAllArea
**
**  **000
**
*************************************/

void ArxRleCmdMeasure::measureAllArea()
{
	ArxRleSelSet ss;
	if(ss.userSelect() == ArxRleSelSet::kSelected)
	{    // have user select entities from DWG
		AcDbObjectIdArray objList;
		ss.asArray(objList);
		if(!objList.isEmpty())
		{
			int len = objList.length();
			double areas = 0.0;
			int num = 0;
			for(int i=0; i<len; i++)
			{
				AcDbPolyline* ent = new AcDbPolyline;
				Acad::ErrorStatus es = acdbOpenObject(ent, objList[i], AcDb::kForRead);
				if(es == Acad::eOk)
				{
					double area = 0.0;
					ent->getArea(area);
					areas += area;
					num++;
					ent->close();
				}
			}
			_printf(_T("\n个数= %d  面积= %.3f 平米  %.3f 亩"),num,areas,areas/666.7);
		}
	}
}

/****************************************************************************
**
**  ArxRleCmdMeasure::measureAllLength
**
**  **000
**
*************************************/

void ArxRleCmdMeasure::measureAllLength()
{
	ArxRleSelSet ss;
	if(ss.userSelect() == ArxRleSelSet::kSelected)
	{    // have user select entities from DWG
		AcDbObjectIdArray objList;
		ss.asArray(objList);
		if(!objList.isEmpty())
		{
			int len = objList.length();
			double lengths = 0.0;
			int num = 0;
			for(int i=0; i<len; i++)
			{
				AcDbPolyline* ent = new AcDbPolyline;
				Acad::ErrorStatus es = acdbOpenObject(ent, objList[i], AcDb::kForRead);
				if(es == Acad::eOk)
				{
					AcGePoint3d pt;
					double length = 0.0;
					ent->getEndPoint(pt);
					ent->getDistAtPoint(pt,length);
					lengths += length;
					num++;
					ent->close();
				}
			}
			_printf(_T("\n个数= %d  距离= %.3f 单位"),num, lengths);
		}
	}
}