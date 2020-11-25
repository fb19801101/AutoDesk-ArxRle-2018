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

#include "ArxRleCmdDim.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleSelSet.h"
#include "AcadUtils\ArxRleApply.h"
#include "Prompt\ArxRleKeywordArray.h"
#include "DbEntity\ArxRleEntityClass.h"


/****************************************************************************
**
**  ArxRleCmdDim::registerCommandLineFunctions
**
**  **000
**
*************************************/

void ArxRleCmdDim::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{																			    
	cmdStack->addCommand(appname, _T("ArxRleDimSetCur"),             _T("DimSetCur"),             ACRX_CMD_MODAL, &dimSetCur);
	cmdStack->addCommand(appname, _T("ArxRleDimShowAll"),            _T("DimShowAll"),            ACRX_CMD_MODAL, &dimShowAll);
	cmdStack->addCommand(appname, _T("ArxRleDimHideAll"),            _T("DimHideAll"),            ACRX_CMD_MODAL, &dimHideAll);
	cmdStack->addCommand(appname, _T("ArxRleDimHidePart"),           _T("DimHidePart"),           ACRX_CMD_MODAL, &dimHidePart);
	cmdStack->addCommand(appname, _T("ArxRleDimShowByStyle"),        _T("DimShowByStyle"),        ACRX_CMD_MODAL, &dimShowByStyle);
	cmdStack->addCommand(appname, _T("ArxRleDimHideByStyle"),        _T("DimHideByStyle"),        ACRX_CMD_MODAL, &dimHideByStyle);
	cmdStack->addCommand(appname, _T("ArxRleDimEntity"),             _T("DimEntity"),             ACRX_CMD_MODAL, &dimEntity);
	cmdStack->addCommand(appname, _T("ArxRleDimSection"),            _T("DimSection"),            ACRX_CMD_MODAL, &dimSection);
	cmdStack->addCommand(appname, _T("ArxRleDimSetStr"),             _T("DimSetStr"),             ACRX_CMD_MODAL, &dimSetStr);
}

/****************************************************************************
**
**  ArxRleCmdDim::dimSetCur
**
**  **000
**
*************************************/

void ArxRleCmdDim::dimSetCur()
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
					if(ent->isKindOf(AcDbDimension::desc()))
					{
						AcDbDimension* pDim;
						AcDbObjectId tsId;
						if((pDim = AcDbDimension::cast(ent)) != NULL)
						{
							tsId = pDim->dimensionStyle();
						}

						ARXRLEDB->setDimstyle(tsId);
					}

					ent->close();
				}
			}
		}
	}
}

/****************************************************************************
**
**  ArxRleCmdDim::dimShowAll
**
**  **000
**
*************************************/

Adesk::Boolean ShowAllDim( AcDbEntity* ent )
{

	if(ent->isKindOf(AcDbDimension::desc()))
		ent->setVisibility(AcDb::kVisible);

	return Adesk::kTrue;
}
void ArxRleCmdDim::dimShowAll()
{
	ArxRleApply<BlockTableRecord>(ARXRLEDS, ShowAllDim, AcDb::kForWrite );
	ARXRLEDS->close();
}

/****************************************************************************
**
**  ArxRleCmdDim::dimHideAll
**
**  **000
**
*************************************/

Adesk::Boolean HideAllDim( AcDbEntity* ent )
{
	if(ent->isKindOf(AcDbDimension::desc()))
		ent->setVisibility(AcDb::kInvisible);

	return Adesk::kTrue;
}
void ArxRleCmdDim::dimHideAll()
{
	ArxRleApply<BlockTableRecord>(ARXRLEDS, HideAllDim, AcDb::kForWrite );
	ARXRLEDS->close();
}

/****************************************************************************
**
**  ArxRleCmdDim::dimHidePart
**
**  **000
**
*************************************/

void ArxRleCmdDim::dimHidePart()
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
					if(ent->isKindOf(AcDbDimension::desc()))
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
							if(ent->isKindOf(AcDbDimension::desc()))
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
**  ArxRleCmdDim::dimShowByStyle
**
**  **000
**
*************************************/

void ArxRleCmdDim::dimShowByStyle()
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
					if(ent->isKindOf(AcDbDimension::desc()))
						tsId = ((AcDbDimension*)ent)->dimensionStyle();

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
							if(ent->isKindOf(AcDbDimension::desc()))
								tsId = ((AcDbDimension*)ent)->dimensionStyle();

							ent->setVisibility(AcDb::kVisible);

							ent->close();
						}
					}
				}
			}
		}
	}
	else
	{
		ACHAR* str_put = new ACHAR[MAX_PATH];;
		if(acedGetString(1,L"输入标注样式名称：",str_put,MAX_PATH) == RTNORM)
		{
			if(ArxRleString(str_put).GetLength() > 0)
				tsId = FindDimStyle(str_put);
		}
	}

	if(!tsId.isNull())
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
					AcDbObjectId tsId1;
					if(elem->isKindOf(AcDbDimension::desc()))
						tsId1 = ((AcDbDimension*)elem)->dimensionStyle();

					if(tsId1 != tsId) elem->setVisibility(AcDb::kInvisible);

					elem->close();
				}
			}
		}
		delete iter;
		ARXRLEDS->close();
	}
}

/****************************************************************************
**
**  ArxRleCmdDim::dimHideByStyle
**
**  **000
**
*************************************/

void ArxRleCmdDim::dimHideByStyle()
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
					if(ent->isKindOf(AcDbDimension::desc()))
						tsId = ((AcDbDimension*)ent)->dimensionStyle();

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
							if(ent->isKindOf(AcDbDimension::desc()))
								tsId = ((AcDbDimension*)ent)->dimensionStyle();

							ent->setVisibility(AcDb::kInvisible);

							ent->close();
						}
					}
				}
			}
		}
	}
	else
	{
		ACHAR* str_put = new ACHAR[MAX_PATH];;
		if(acedGetString(1,L"输入标注样式名称：",str_put,MAX_PATH) == RTNORM)
		{
			if(ArxRleString(str_put).GetLength() > 0)
				tsId = FindDimStyle(str_put);
		}
	}

	if(!tsId.isNull())
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
					AcDbObjectId tsId1;
					if(elem->isKindOf(AcDbDimension::desc()))
						tsId1 = ((AcDbDimension*)elem)->dimensionStyle();

					if(tsId1 == tsId) elem->setVisibility(AcDb::kInvisible);

					elem->close();
				}
			}
		}

		delete iter;
		ARXRLEDS->close();
	}
}

/****************************************************************************
**
**  ArxRleCmdDim::dimEntity
**
**  **000
**
*************************************/

void ArxRleCmdDim::dimEntity()
{
	ArxRleUiPrPoint prPt1(_T("BeginPoint"), NULL);
	if(prPt1.go() != ArxRleUiPrBase::kOk)
		return;
	ArxRleUiPrPoint prPt2(_T("EndPoint"), NULL);
	if(prPt2.go() != ArxRleUiPrBase::kOk)
		return;

	CPt3d pt1 = prPt1.value();
	CPt3d pt2 = prPt2.value();
	ArxRleUiPrString prStr(_T("Input Text"), true);
	if((prStr.go() == ArxRleUiPrBase::kOk))
	{
		double fAngle = pt1.GetAngle(pt2);
		pt1 = pt1.GetLineEnd(3,fAngle+PI/2);
		CText oText;
		oText.SetAlignmentMode(ArxLeftMiddle);
		oText.SetTextHeight(2.5);
		oText.SetWidthFactor(0.7);
		oText.SetRotation(fAngle);
		oText.SetText(prStr.value());
		oText.SetPosition(pt1);
		oText.addToSpaceAndClose();
	}
}

/****************************************************************************
**
**  ArxRleCmdDim::dimSection
**
**  **000
**
*************************************/

void ArxRleCmdDim::dimSection()
{
	ArxRleUiPrEntity prEnt(_T("Select Text Ref"), NULL);
	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	AcDbEntity* ent;
	Acad::ErrorStatus es = acdbOpenObject(ent, prEnt.objectId(), AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete ent;
		return;
	}

	if(ent->isKindOf(AcDbText::desc()))
	{
		ArxRleUiPrPoint prPt1(_T("BeginPoint"), NULL);
		if(prPt1.go() != ArxRleUiPrBase::kOk)
			return;
		ArxRleUiPrPoint prPt2(_T("EndPoint"), NULL);
		if(prPt2.go() != ArxRleUiPrBase::kOk)
			return;

		CPt3d pt1 = prPt1.value();
		CPt3d pt2 = prPt2.value();
		double fAngle = pt1.GetAngle(pt2);

		((AcDbText*)ent)->setRotation(fAngle);
	}

	ent->close();
}

/****************************************************************************
**
**  ArxRleCmdDim::dimSetStr
**
**  **000
**
*************************************/

void ArxRleCmdDim::dimSetStr()
{
	ArxRleUiPrEntity prEnt(_T("Select Dimension/Mtext/Text to modify"), NULL);
	prEnt.addAllowedClass(AcDbEntity::desc());
	prEnt.setFilterLockedLayers(true);
	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	AcDbEntity* ent;
	Acad::ErrorStatus es = acdbOpenObject(ent, prEnt.objectId(), AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete ent;
		return;
	}

	if(ent->isKindOf(AcDbDimension::desc()))
	{
		ArxRleUiPrStringDef prDimText(_T("DimText "), ((AcDbDimension*)ent)->dimensionText(), true);
		if(prDimText.go() != ArxRleUiPrBase::kOk) {
			delete ent;
			return;
		}

		if(ArxRleString(prDimText.value()).GetLength() > 0)
			((AcDbDimension*)ent)->setDimensionText(prDimText.value());
	}
	else if(ent->isKindOf(AcDbMText::desc()))
	{
		ArxRleUiPrStringDef prMText(_T("MText "), ((AcDbMText*)ent)->contents(), true);
		if(prMText.go() != ArxRleUiPrBase::kOk) {
			delete ent;
			return;
		}

		if(ArxRleString(prMText.value()).GetLength() > 0)
			((AcDbMText*)ent)->setContents(prMText.value());
	}
	else if(ent->isKindOf(AcDbText::desc()))
	{
		ArxRleUiPrStringDef prText(_T("Text "), ((AcDbText*)ent)->textString(), true);
		if(prText.go() != ArxRleUiPrBase::kOk) {
			delete ent;
			return;
		}

		if(ArxRleString(prText.value()).GetLength() > 0)
			((AcDbText*)ent)->setTextString(prText.value());
	}
	ent->close();
}
