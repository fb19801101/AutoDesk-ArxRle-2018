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

#include "App\ArxRleDataManager.h"         // Utility class for document data
#include "App\ArxRleDocData.h"          // Your document specific data
#include "ArxRleCmdEnt.h"
#include "Reactor\ArxRleDbDoubleClickEdit.h"
#include "Reactor\ArxRleInputPointMonitor.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleSelSet.h"
#include "AcadUtils\ArxRleApply.h"
#include "Prompt\ArxRleKeywordArray.h"
#include "DbEntity\ArxRleEntityClass.h"

extern ArxRleDataManager<ArxRleDocData> DocVars;

/****************************************************************************
**
**  ArxRleCmdEnt::registerCommandLineFunctions
**
**  **000
**
*************************************/

void ArxRleCmdEnt::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
	cmdStack->addCommand(appname, _T("ArxRleEntDelAll"),             _T("EntDelAll"),             ACRX_CMD_MODAL, &entDelAll);
	cmdStack->addCommand(appname, _T("ArxRleEntDelByLayer"),         _T("EntDelByLayer"),         ACRX_CMD_MODAL, &entDelByLayer);
	cmdStack->addCommand(appname, _T("ArxRleEntDelByColor"),         _T("EntDelByColor"),         ACRX_CMD_MODAL, &entDelByColor);
	cmdStack->addCommand(appname, _T("ArxRleEntCpyByDist"),          _T("EntCpyByDist"),          ACRX_CMD_MODAL, &entCpyByDist);
	cmdStack->addCommand(appname, _T("ArxRleEntCpyByAngle"),         _T("EntCpyByAngle"),         ACRX_CMD_MODAL, &entCpyByAngle);
	cmdStack->addCommand(appname, _T("ArxRleEntCpyByIf"),            _T("EntCpyByIf"),            ACRX_CMD_MODAL, &entCpyByIf);
	cmdStack->addCommand(appname, _T("ArxRleEntClrSetByLayer"),      _T("EntClrSetByLayer"),      ACRX_CMD_MODAL, &entClrSetByLayer);
	cmdStack->addCommand(appname, _T("ArxRleEntClrSetByColor"),      _T("EntClrSetByColor"),      ACRX_CMD_MODAL, &entClrSetByColor);
	cmdStack->addCommand(appname, _T("ArxRleEntClrSetByEntity"),     _T("EntClrSetByEntity"),     ACRX_CMD_MODAL, &entClrSetByEntity);
	cmdStack->addCommand(appname, _T("ArxRleEntLtSetByLayer"),       _T("EntLtSetByLayer"),       ACRX_CMD_MODAL, &entLtSetByLayer);
	cmdStack->addCommand(appname, _T("ArxRleEntLtSetByColor"),       _T("EntLtSetByColor"),       ACRX_CMD_MODAL, &entLtSetByColor);
	cmdStack->addCommand(appname, _T("ArxRleEntLtSetByEntity"),      _T("EntLtSetByEntity"),      ACRX_CMD_MODAL, &entLtSetByEntity);
	cmdStack->addCommand(appname, _T("ArxRleEntInfoTipShow"),        _T("EntInfoTipShow"),        ACRX_CMD_MODAL, &entInfoTipShow);
	cmdStack->addCommand(appname, _T("ArxRleEntInfoTipHide"),        _T("EntInfoTipHide"),        ACRX_CMD_MODAL, &entInfoTipHide);
	cmdStack->addCommand(appname, _T("ArxRleEntConvertTo2d"),        _T("EntConvertTo2d"),        ACRX_CMD_MODAL, &entConvertTo2d);
}

/****************************************************************************
**
**  ArxRleCmdEnt::entDelAll
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entDelAll()
{
	ArxRleApply<BlockTableRecord> apply = ArxRleApply<BlockTableRecord>( ARXRLEDS, AcDb::kForWrite );
	BlockTableRecord::Iterator* iter;
	apply.createIterator( iter );
	if (NULL != iter)
	{
		for ( ; !iter->done(); apply.stepIterator( iter ))
		{
			BlockTableRecord::Element* elem = apply.getElement( iter );
			if (NULL != elem)
			{
				elem->erase();
				elem->close();
			}
		}
	}

	delete iter;
	ARXRLEDS->close();
}

/****************************************************************************
**
**  ArxRleCmdEnt::entDelByLayer
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entDelByLayer()
{
	ArxRleSelSet ss;
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
				es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForRead, true);		// might have passed in erased ones
				if(es == Acad::eOk)
				{
					AcDbLayerTableRecord* pRcd = (AcDbLayerTableRecord*)GetRecordPtr(ent->layerId(),AcDb::kForWrite);;
					AcDbLayerTable *pLt;
					if (Acad::eOk != ARXRLEDB->getLayerTable( pLt, AcDb::kForWrite ))
						return;

					ArxRleApply<LayerTable> apply = ArxRleApply<LayerTable>( pLt, AcDb::kForWrite );
					LayerTable::Iterator* iter;
					apply.createIterator( iter );
					if (NULL == iter)
						return;

					for ( ; !iter->done(); apply.stepIterator( iter ))
					{
						LayerTable::Element* elem = apply.getElement( iter );
						if (NULL != elem)
						{
							if(pRcd == elem) elem->erase();
							elem->close();
						}
					}
					delete iter;

					pLt->close();
					pRcd->close();

					ent->close();
				}
			}
		}
	}
}

/****************************************************************************
**
**  ArxRleCmdEnt::entDelByColor
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entDelByColor()
{
	ArxRleSelSet ss;
	AcCmColor clr;
	COLORREF ref;
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
					clr = ent->color();
					ref = AcCmColorToRefColor(clr, ent->layerId());
					ent->setVisibility(AcDb::kVisible);
					ent->close();
				}
				else if(es == Acad::eOnLockedLayer)
				{
					es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForRead, true);		// might have passed in erased ones
					if(es == Acad::eOk)
					{
						if(UnLockEntity(ent))
						{
							clr = ent->color();
							ref = AcCmColorToRefColor(clr, ent->layerId());
							ent->setVisibility(AcDb::kVisible);
							ent->close();
						}
					}
				}
			}
		}
	}

	ArxRleApply<BlockTableRecord> apply = ArxRleApply<BlockTableRecord>( ARXRLEDS, AcDb::kForWrite );
	BlockTableRecord::Iterator* iter;
	apply.createIterator( iter );
	if (NULL != iter)
	{
		for ( ; !iter->done(); apply.stepIterator( iter ))
		{
			BlockTableRecord::Element* elem = apply.getElement( iter );
			if (NULL != elem)
			{
				AcCmColor clr1 = elem->color();
				COLORREF ref1 = AcCmColorToRefColor(clr1, elem->layerId());
				if(ref == ref1) elem->erase();
				elem->close();
			}
		}
	}

	delete iter;
	ARXRLEDS->close();
}

/****************************************************************************
**
**  ArxRleCmdEnt::entCpyByDist
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entCpyByDist()
{
	acedSendCommand(L"COPY");
}

/****************************************************************************
**
**  ArxRleCmdEnt::entCpyByAngle
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entCpyByAngle()
{
	msgErr(L"CpyByAngle");
}

/****************************************************************************
**
**  ArxRleCmdEnt::entCpyByIf
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entCpyByIf()
{
	msgErr(L"CpyByIf");
}

/****************************************************************************
**
**  ArxRleCmdEnt::entClrSetByLayer
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entClrSetByLayer()
{
	msgErr(L"ClrSetByLayer");
}

/****************************************************************************
**
**  ArxRleCmdEnt::entClrSetByColor
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entClrSetByColor()
{
	ArxRleSelSet ss;
	AcCmColor clr;
	COLORREF ref;
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
					clr = ent->color();
					ref = AcCmColorToRefColor(clr, ent->layerId());
					ent->setVisibility(AcDb::kVisible);
					ent->close();
				}
				else if(es == Acad::eOnLockedLayer)
				{
					es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForRead, true);		// might have passed in erased ones
					if(es == Acad::eOk)
					{
						if(UnLockEntity(ent))
						{
							clr = ent->color();
							ref = AcCmColorToRefColor(clr, ent->layerId());
							ent->setVisibility(AcDb::kVisible);
							ent->close();
						}
					}
				}
			}
		}
	}

	int int_put;
	AcCmColor clr2;
	clr2.setColorMethod(AcCmEntityColor::kByACI);
	clr2.setColorIndex(6);
	if(acedGetInt(_T("\n«Î ‰»Î—’…´À˜“˝... "),&int_put) == RTNORM)
		clr2.setColorIndex(int_put);

	ArxRleApply<BlockTableRecord> apply = ArxRleApply<BlockTableRecord>( ARXRLEDS, AcDb::kForWrite );
	BlockTableRecord::Iterator* iter;
	apply.createIterator( iter );
	if (NULL != iter)
	{
		for ( ; !iter->done(); apply.stepIterator( iter ))
		{
			BlockTableRecord::Element* elem = apply.getElement( iter );
			if (NULL != elem)
			{
				AcCmColor clr1 = elem->color();
				COLORREF ref1 = AcCmColorToRefColor(clr1, elem->layerId());
				if(ref == ref1) elem->setColor(clr2);
				elem->close();
			}
		}
	}

	delete iter;
	ARXRLEDS->close();
}

/****************************************************************************
**
**  ArxRleCmdEnt::entClrSetByEntity
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entClrSetByEntity()
{
	msgErr(L"ClrSetByEntity");
}

/****************************************************************************
**
**  ArxRleCmdEnt::entLtSetByLayer
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entLtSetByLayer()
{
	msgErr(L"LtSetByLayer");
}

/****************************************************************************
**
**  ArxRleCmdEnt::entLtSetByColor
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entLtSetByColor()
{
	msgErr(L"LtSetByColor");
}

/****************************************************************************
**
**  ArxRleCmdEnt::entLtSetByEntity
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entLtSetByEntity()
{
	msgErr(L"entLtSetByEntity");
}

/****************************************************************************
**
**  ArxRleCmdEnt::entInfoTipShow
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entInfoTipShow()
{
	ArxRleInputPointMonitor::getInstance();
}

/****************************************************************************
**
**  ArxRleCmdEnt::entInfoTipHide
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entInfoTipHide()
{
	ArxRleInputPointMonitor::destroyInstance();
}

/****************************************************************************
**
**  ArxRleCmdEnt::entConvertTo2d
**
**  **000
**
*************************************/

void ArxRleCmdEnt::entConvertTo2d()
{
	ArxRleSelSet ss;
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
					if (ent->isKindOf(AcDb3dPolyline::desc()))
					{
						AcDb3dPolyline *p3dPline = AcDb3dPolyline::cast(ent);
						AcDb2dPolyline *p2dPline = new AcDb2dPolyline();
						AcDbObjectIterator *pItr = p3dPline->vertexIterator();

						for (pItr->start(); !pItr->done(); pItr->step())
						{
							AcDb3dPolylineVertex *p3dVertex = NULL;
							AcDbObjectId vId = pItr->objectId();
							acdbOpenObject(p3dVertex, vId, AcDb::kForRead);
							AcDb::Vertex3dType verType = p3dVertex->vertexType();
							if (verType != AcDb::k3dControlVertex)
							{
								AcDb2dVertex *p2dVertex = new AcDb2dVertex(p3dVertex->position());
								p2dVertex->setXData(p3dVertex->xData());
								p2dPline->appendVertex(p2dVertex);
								p2dVertex->close();
							}

							p3dVertex->close();
						}
						delete pItr;
						pItr = 0;

						p2dPline->setElevation(0);
						p2dPline->setPropertiesFrom(p3dPline);
						if (p3dPline->isClosed())
						{
							p2dPline->makeClosed();
						}

						p2dPline->setXData(p3dPline->xData());
						ArxRleUtils::addToCurrentSpaceAndClose(p2dPline);
						p3dPline->erase();
					}
					if (ent->isKindOf(AcDbPolyline::desc()))
					{
						AcDbPolyline *pPline = AcDbPolyline::cast(ent);
						pPline->setElevation(0);
					}
					if (ent->isKindOf(AcDbLine::desc()))
					{
						AcDbLine *pLint = AcDbLine::cast(ent);
						AcGePoint3d pt = pLint->startPoint();
						pt.z = 0;
						pLint->setStartPoint(pt); 
						pt = pLint->endPoint();
						pt.z = 0;
						pLint->setEndPoint(pt);
					}
					if (ent->isKindOf(AcDbArc::desc()))
					{
						AcDbArc *pArc = AcDbArc::cast(ent);
						AcGePoint3d pt = pArc->center();
						AcGeVector3d nor = pArc->normal();
						double a1 = pArc->startAngle();
						double a2 = pArc->endAngle();
						double r = pArc->radius();
						pt.z = 0;
						AcDbArc *pNewArc = new AcDbArc(pt,nor,r,a1,a2);
						pNewArc->setLayer(pArc->layerId());
						pNewArc->setColor(pArc->color());
						pNewArc->setLinetype(pArc->linetypeId());
						pNewArc->setLinetypeScale(pArc->linetypeScale());
						pNewArc->setLineWeight(pArc->lineWeight());
						ArxRleUtils::addToCurrentSpaceAndClose(pNewArc);
						pArc->erase();
					}
					if (ent->isKindOf(AcDbCircle::desc()))
					{
						AcDbCircle *pCircle = AcDbCircle::cast(ent);
						AcGePoint3d pt = pCircle->center();
						double r = pCircle->radius();
						AcGeVector3d nor = pCircle->normal();
						pt.z = 0;
						AcDbCircle *pNewCircle = new AcDbCircle(pt,nor,r);
						pNewCircle->setLayer(pCircle->layerId());
						pNewCircle->setColor(pCircle->color());
						pNewCircle->setLinetype(pCircle->linetypeId());
						pNewCircle->setLinetypeScale(pCircle->linetypeScale());
						pNewCircle->setLineWeight(pCircle->lineWeight());
						ArxRleUtils::addToCurrentSpaceAndClose(pNewCircle);
						pCircle->erase();
					}

					ent->close();
				}
			}
		}
	}
}
