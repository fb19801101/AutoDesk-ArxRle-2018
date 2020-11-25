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

#include "ArxRleCmdLayer.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleSelSet.h"
#include "AcadUtils\ArxRleApply.h"
#include "Prompt\ArxRleKeywordArray.h"
#include "DbEntity\ArxRleEntityClass.h"


/****************************************************************************
**
**  ArxRleCmdLayer::registerCommandLineFunctions
**
**  **000
**
*************************************/

void ArxRleCmdLayer::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
	//Í¼²ã¹ÜÀí
	cmdStack->addCommand(appname, _T("ArxRleLayerSetCur"),           _T("LayerSetCur"),           ACRX_CMD_MODAL, &layerSetCur);
	cmdStack->addCommand(appname, _T("ArxRleLayerShowAll"),          _T("LayerShowAll"),          ACRX_CMD_MODAL, &layerShowAll);
	cmdStack->addCommand(appname, _T("ArxRleLayerHideAll"),          _T("LayerHideAll"),          ACRX_CMD_MODAL, &layerHideAll);
	cmdStack->addCommand(appname, _T("ArxRleLayerHidePart"),         _T("LayerHidePart"),         ACRX_CMD_MODAL, &layerHidePart);
	cmdStack->addCommand(appname, _T("ArxRleLayerShowByLayer"),      _T("LayerShowByLayer"),      ACRX_CMD_MODAL, &layerShowByLayer);
	cmdStack->addCommand(appname, _T("ArxRleLayerHideByLayer"),      _T("LayerHideByLayer"),      ACRX_CMD_MODAL, &layerHideByLayer);
	cmdStack->addCommand(appname, _T("ArxRleLayerShowByColor"),      _T("LayerShowByColor"),      ACRX_CMD_MODAL, &layerShowByColor);
	cmdStack->addCommand(appname, _T("ArxRleLayerHideByColor"),      _T("LayerHideByColor"),      ACRX_CMD_MODAL, &layerHideByColor);
	cmdStack->addCommand(appname, _T("ArxRleLayerLock"),             _T("LayerLock"),             ACRX_CMD_MODAL, &layerLock);
	cmdStack->addCommand(appname, _T("ArxRleLayerUnLock"),           _T("LayerUnLock"),           ACRX_CMD_MODAL, &layerUnLock);
}

/****************************************************************************
**
**  ArxRleCmdLayer::layerSetCur
**
**  **000
**
*************************************/

void ArxRleCmdLayer::layerSetCur()
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
					AcDbObjectId layerId = ent->layerId();

					ARXRLEDB->setClayer(layerId);

					ent->close();
				}
			}
		}
	}
}

/****************************************************************************
**
**  ArxRleCmdLayer::layerShowAll
**
**  **000
**
*************************************/

Adesk::Boolean ShowAllEntity( AcDbEntity* ent )
{
	ent->setVisibility(AcDb::kVisible);

	return Adesk::kTrue;
}
Adesk::Boolean ShowAllLayer( AcDbLayerTableRecord* rcd )
{
	//rcd->setIsLocked(0);
	//rcd->setIsFrozen(0);
	rcd->setIsOff(0);

	return Adesk::kTrue;
}
void ArxRleCmdLayer::layerShowAll()
{
	ArxRleApply<BlockTableRecord>(ARXRLEDS, ShowAllEntity, AcDb::kForWrite );
	ARXRLEDS->close();

	AcDbLayerTable *pLt;
	if (Acad::eOk != ARXRLEDB->getLayerTable( pLt, AcDb::kForWrite ))
		return;
	ArxRleApply<LayerTable>( pLt, ShowAllLayer, AcDb::kForWrite );
	pLt->close();
}

/****************************************************************************
**
**  ArxRleCmdLayer::layerHideAll
**
**  **000
**
*************************************/

Adesk::Boolean HideAllLayer( AcDbLayerTableRecord* rcd )
{
	rcd->setIsOff(1);

	return Adesk::kTrue;
}
Adesk::Boolean HideAllEntity( AcDbEntity* ent )
{
	ent->setVisibility(AcDb::kInvisible);

	return Adesk::kTrue;
}
void ArxRleCmdLayer::layerHideAll()
{
	ArxRleApply<BlockTableRecord>(ARXRLEDS, HideAllEntity, AcDb::kForWrite );
	ARXRLEDS->close();

	AcDbLayerTable *pLt;
	if (Acad::eOk != ARXRLEDB->getLayerTable( pLt, AcDb::kForWrite ))
		return;
	ArxRleApply<LayerTable>( pLt, HideAllLayer, AcDb::kForWrite );
	pLt->close();
}

/****************************************************************************
**
**  ArxRleCmdLayer::layerHidePart
**
**  **000
**
*************************************/

void ArxRleCmdLayer::layerHidePart()
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
					ent->setVisibility(AcDb::kInvisible);
					ent->close();
				}
				else if(es == Acad::eOnLockedLayer)
				{
					es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForRead, true);
					if(es == Acad::eOk)
					{
						if(UnLockEntity(ent))
						{
							ent->setVisibility(AcDb::kInvisible);
							ent->close();
						}
					}
				}
			}
		}
	}
}

/****************************************************************************
**
**  ArxRleCmdLayer::layerShowByLayer
**
**  **000
**
*************************************/

void ArxRleCmdLayer::layerShowByLayer()
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
					AcDbLayerTableRecord* pRcd = (AcDbLayerTableRecord*)GetRecordPtr(ent->layerId(),AcDb::kForWrite);
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
							if(pRcd != elem)
								elem->setIsOff(1);

							elem->close();
						}
					}
					delete iter;

					pRcd->close();
					pLt->close();

					ent->close();
				}
			}
		}
	}
	else
	{
		ACHAR* str_put = new ACHAR[MAX_PATH];;
		acedGetString(1,L"\nÇëÊäÈëÍ¼²ãÃû³Æ£º",str_put,MAX_PATH);

		AcDbLayerTable *pLt;
		if (Acad::eOk != ARXRLEDB->getLayerTable( pLt, AcDb::kForWrite ))
			return;

		AcDbObjectId id;
		if(pLt->has(str_put))
			pLt->getAt(str_put,id);
		AcDbLayerTableRecord* pRcd = (AcDbLayerTableRecord*)GetRecordPtr(id,AcDb::kForWrite);

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
				if(pRcd != elem)
					elem->setIsOff(1);
				else
					elem->setIsOff(0);

				elem->close();
			}
		}
		delete iter;

		pLt->close();
		pRcd->close();
	}
}

/****************************************************************************
**
**  ArxRleCmdLayer::layerHideByLayer
**
**  **000
**
*************************************/

void ArxRleCmdLayer::layerHideByLayer()
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
					pRcd->setIsOff(1);
					pRcd->close();

					ent->close();
				}
			}
		}
	}
	else
	{
		ACHAR* str_put = new ACHAR[MAX_PATH];;
		acedGetString(1,L"\nÇëÊäÈëÍ¼²ãÃû³Æ£º",str_put,MAX_PATH);

		AcDbLayerTable *pLt;
		if (Acad::eOk != ARXRLEDB->getLayerTable( pLt, AcDb::kForWrite ))
			return;

		AcDbObjectId id;
		if(pLt->has(str_put))
			pLt->getAt(str_put,id);
		AcDbLayerTableRecord* pRcd = (AcDbLayerTableRecord*)GetRecordPtr(id,AcDb::kForWrite);
		pRcd->setIsOff(1);

		pRcd->close();
		pLt->close();
	}
}

/****************************************************************************
**
**  ArxRleCmdLayer::layerShowByColor
**
**  **000
**
*************************************/

void ArxRleCmdLayer::layerShowByColor()
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
				if(ref != ref1) elem->setVisibility(AcDb::kInvisible);

				elem->close();
			}
		}
	}

	delete iter;
	ARXRLEDS->close();
}

/****************************************************************************
**
**  ArxRleCmdLayer::layerHideByColor
**
**  **000
**
*************************************/

void ArxRleCmdLayer::layerHideByColor()
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
					ent->setVisibility(AcDb::kInvisible);
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
							ent->setVisibility(AcDb::kInvisible);
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
				if(ref == ref1) elem->setVisibility(AcDb::kInvisible);

				elem->close();
			}
		}
	}

	delete iter;
	ARXRLEDS->close();
}

/****************************************************************************
**
**  ArxRleCmdLayer::layerLock
**
**  **000
**
*************************************/

void ArxRleCmdLayer::layerLock()
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
					if(pRcd != NULL) pRcd->setIsLocked(true);

					ent->close();
					pRcd->close();
				}
			}
		}
	}
}

/****************************************************************************
**
**  ArxRleCmdLayer::layerUnLock
**
**  **000
**
*************************************/

void ArxRleCmdLayer::layerUnLock()
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
					if(pRcd != NULL) pRcd->setIsLocked(false);

					ent->close();
					pRcd->close();
				}
			}
		}
	}
}

