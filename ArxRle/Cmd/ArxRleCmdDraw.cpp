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

#include "ArxRleCmdDraw.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleSelSet.h"
#include "AcadUtils\ArxRleApply.h"
#include "Prompt\ArxRleKeywordArray.h"
#include "DbEntity\ArxRleEntityClass.h"


void drawCondition();
void drawDimLand();


/****************************************************************************
**
**  ArxRleCmdDraw::registerCommandLineFunctions
**
**  **000
**
*************************************/

void ArxRleCmdDraw::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{																			    
	cmdStack->addCommand(appname, _T("ArxRleDrawHatch"),            _T("DrawHatch"),              ACRX_CMD_MODAL, &drawHatch);
	cmdStack->addCommand(appname, _T("ArxRleDrawNumber"),           _T("DrawNumber"),             ACRX_CMD_MODAL, &drawNumber);
	cmdStack->addCommand(appname, _T("ArxRleDrawCondition"),        _T("DrawCondition"),          ACRX_CMD_MODAL, &drawCondition);
	cmdStack->addCommand(appname, _T("ArxRleDrawDimLand"),          _T("DrawDimLand"),            ACRX_CMD_MODAL, &drawDimLand);
}

/****************************************************************************
**
**  ArxRleCmdDraw::drawHatch
**
**  **000
**
*************************************/

void ArxRleCmdDraw::drawHatch()
{
	ArxRleUiPrIntDef prEdge(_T("请输入边界方式(0-多段线，1-坐标点) "), NULL,ArxRleUiPrInt::kAny, 0);
	if(prEdge.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrStringDef prStyle(_T("请输入填充样式名称 "), _T("SOLID"), true);
	if(prStyle.go() != ArxRleUiPrBase::kOk)
		return;

	if(prEdge.value() == 0)
	{
		ArxRleSelSet ss;
		AcDbObjectId tsId;
		if(ss.userSelect() == ArxRleSelSet::kSelected)
		{    // have user select entities from DWG
			AcDbObjectIdArray objList;
			ss.asArray(objList);
			if(!objList.isEmpty())
			{
				AcDbEntity* ent;
				Acad::ErrorStatus es;

				int len = objList.length();
				for(int i=0; i<len; i++)
				{
					es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForWrite, true);		// might have passed in erased ones
					if(es == Acad::eOk)
					{
						if(ent->isKindOf(AcDbPolyline::desc()) || ent->isKindOf(AcDb3dPolyline::desc()))
						{
							AcDbHatch* pHatch = new AcDbHatch;
							pHatch->setNormal(AcGeVector3d(0.0,0.0,1.0));
							pHatch->setElevation(0.0);//设置填充平面
							pHatch->setAssociative(Adesk::kTrue);//设置关联性
							pHatch->setPatternScale(1);
							pHatch->setPattern(AcDbHatch::kPreDefined,prStyle.value());
							pHatch->setHatchStyle(AcDbHatch::kNormal);

							AcGeDoubleArray vertexBulges;
							AcGePoint2dArray vtxs;
							if(ent->isKindOf(AcDbPolyline::desc()))
							{
								int nums = ((AcDbPolyline*)ent)->numVerts();
								AcGePoint2d pt;
								if(isUcs())
								{
									CPt3d pt1;
									for(int i=0; i<nums; i++)
									{
										((AcDbPolyline*)ent)->getPointAt(i,pt);
										pt1 = W2U(CPt3d(pt));
										vtxs.append(pt1);
									}
									((AcDbPolyline*)ent)->getPointAt(0,pt);
									pt1 = W2U(CPt3d(pt));
									vtxs.append(pt1);
								}
								else
								{
									for(int i=0; i<nums; i++)
									{
										((AcDbPolyline*)ent)->getPointAt(i,pt);
										vtxs.append(pt);
									}
									((AcDbPolyline*)ent)->getPointAt(0,pt);
									vtxs.append(pt);
								}
							}
							else
							{
								AcDbObjectIterator* pVerIetor = ((AcDb3dPolyline*)ent)->vertexIterator();

								AcGePoint2d ptBegin;
								for(int i = 0; !pVerIetor->done(); i++, pVerIetor->step())
								{
									AcDb3dPolylineVertex *pVertex;
									AcDbObjectId id = pVerIetor->objectId();
									acdbOpenObject(pVertex, id, AcDb::kForRead);
									AcGePoint3d pt = pVertex->position();
									if(i == 0) ptBegin = AcGePoint2d(pt.x, pt.y);
									vtxs.append(AcGePoint2d(pt.x, pt.y));
								}
								vtxs.append(ptBegin);

								delete pVerIetor;
							}
							pHatch->appendLoop(AcDbHatch::kExternal | AcDbHatch::kPolyline, vtxs, vertexBulges);
							pHatch->evaluateHatch();//设置填充对象

							AddEntity(pHatch);
							pHatch->close();
						}
						ent->close();
					}
				}
			}
		}
	}
	else
	{
		AcDbHatch* pHatch = new AcDbHatch;
		pHatch->setNormal(AcGeVector3d(0.0,0.0,1.0));
		pHatch->setElevation(0.0);//设置填充平面
		pHatch->setAssociative(Adesk::kTrue);//设置关联性
		pHatch->setPatternScale(1);
		pHatch->setPattern(AcDbHatch::kPreDefined,prStyle.value());
		pHatch->setHatchStyle(AcDbHatch::kNormal);

		AcGeDoubleArray vertexBulges;
		AcGePoint2dArray vtxs;
		ads_point pt;
		while(acedGetPoint(NULL,L"\n选择坐标点:",pt) == RTNORM)
			vtxs.append(AcGePoint2d(pt[0],pt[1]));
		pHatch->appendLoop(AcDbHatch::kExternal | AcDbHatch::kPolyline, vtxs, vertexBulges);
		pHatch->evaluateHatch();//设置填充对象

		AddEntity(pHatch);
		pHatch->close();
	}
}

/****************************************************************************
**
**  ArxRleCmdDraw::drawNumber
**
**  **000
**
*************************************/

void ArxRleCmdDraw::drawNumber()
{
	ArxRleUiPrStringDef prPrix(_T("请输入编号前缀 "), _T(""), true);
	if(prPrix.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrIntDef prNum(_T("请输入起始编号 "), NULL,ArxRleUiPrInt::kAny, 1);
	if(prNum.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrIntDef prGap(_T("请输入编号间隔 "), NULL,ArxRleUiPrInt::kAny, 1);
	if(prGap.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrDoubleDef prHeight(_T("请输入文字高度 "), NULL,ArxRleUiPrDouble::kAny, 2.5);
	if(prHeight.go() != ArxRleUiPrBase::kOk)
		return;

	AddLayer("arx_nr",4);
	SetCurLayer("arx_nr");
	AddTextStyle("arx_nr");
	SetCurTextStyle("arx_nr");

	int num = prNum.value();

	while(1)
	{
		ArxRleUiPrPoint prPt(_T("InsertPt"), NULL);
		if(prPt.go() != ArxRleUiPrBase::kOk)
			return;

		AddCircle(CPt3d(prPt.value()),3*prHeight.value()/4);
		ArxRleString strNr;
		strNr = _variant_t(prNum.value());
		num += prGap.value();
		strNr = ArxRleString(prPrix.value())+strNr;
		AddText(strNr, CPt3d(prPt.value()),prHeight.value());
	}
}