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

#include "ArxRleCmdText.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleSelSet.h"
#include "AcadUtils\ArxRleApply.h"
#include "Prompt\ArxRleKeywordArray.h"
#include "DbEntity\ArxRleEntityClass.h"

/****************************************************************************
**
**  ArxRleCmdText::registerCommandLineFunctions
**
**  **000
**
*************************************/

void ArxRleCmdText::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
	cmdStack->addCommand(appname, _T("ArxRleTextSetCur"),            _T("TextSetCur"),            ACRX_CMD_MODAL, &textSetCur);
	cmdStack->addCommand(appname, _T("ArxRleTextStyles"),            _T("TextStyles"),            ACRX_CMD_MODAL, &textStyles);
	cmdStack->addCommand(appname, _T("ArxRleTextShowAll"),           _T("TextShowAll"),           ACRX_CMD_MODAL, &textShowAll);
	cmdStack->addCommand(appname, _T("ArxRleTextHideAll"),           _T("TextHideAll"),           ACRX_CMD_MODAL, &textHideAll);
	cmdStack->addCommand(appname, _T("ArxRleTextHidePart"),          _T("TextHidePart"),          ACRX_CMD_MODAL, &textHidePart);
	cmdStack->addCommand(appname, _T("ArxRleTextShowByStyle"),       _T("TextShowByStyle"),       ACRX_CMD_MODAL, &textShowByStyle);
	cmdStack->addCommand(appname, _T("ArxRleTextHideByStyle"),       _T("TextHideByStyle"),       ACRX_CMD_MODAL, &textHideByStyle);
	cmdStack->addCommand(appname, _T("ArxRleTextShowByHeight"),      _T("TextShowByHeight"),      ACRX_CMD_MODAL, &textShowByHeight);
	cmdStack->addCommand(appname, _T("ArxRleTextHideByHeight"),      _T("TextHideByHeight"),      ACRX_CMD_MODAL, &textHideByHeight);
	cmdStack->addCommand(appname, _T("ArxRleTextShowByAngle"),       _T("TextShowByAngle"),       ACRX_CMD_MODAL, &textShowByAngle);
	cmdStack->addCommand(appname, _T("ArxRleTextHideByAngle"),       _T("TextHideByAngle"),       ACRX_CMD_MODAL, &textHideByAngle);
	cmdStack->addCommand(appname, _T("ArxRleTextShowByStr"),         _T("TextShowByStr"),         ACRX_CMD_MODAL, &textShowByStr);
	cmdStack->addCommand(appname, _T("ArxRleTextHideByStr"),         _T("TextHideByStr"),         ACRX_CMD_MODAL, &textHideByStr);
	cmdStack->addCommand(appname, _T("ArxRleTextFlush"),             _T("TextFlush"),             ACRX_CMD_MODAL, &textFlush);
	cmdStack->addCommand(appname, _T("ArxRleTextCalc"),              _T("TextCalc"),              ACRX_CMD_MODAL, &textCalc);
	cmdStack->addCommand(appname, _T("ArxRleTextImport"),            _T("TextImport"),            ACRX_CMD_MODAL, &textImport);
	cmdStack->addCommand(appname, _T("ArxRleTextExport"),            _T("TextExport"),            ACRX_CMD_MODAL, &textExport);
}

/****************************************************************************
**
**  ArxRleCmdText::textSetCur
**
**  **000
**
*************************************/

void ArxRleCmdText::textSetCur()
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
					if(ent->isKindOf(AcDbMText::desc()) || ent->isKindOf(AcDbText::desc()))
					{
						AcDbMText* pMText;
						AcDbText* pText;

						AcDbObjectId tsId;
						if((pMText = AcDbMText::cast(ent)) != NULL)
						{
							tsId = pMText->textStyle();
						}
						else if((pText = AcDbText::cast(ent)) != NULL)
						{
							tsId = pText->textStyle();
						}

						ARXRLEDB->setTextstyle(tsId);
					}

					ent->close();
				}
			}
		}
	}
}

/****************************************************************************
**
**  ArxRleCmdText::textStyles
**
**  **000
**
*************************************/

void ArxRleCmdText::textStyles()
{
	AcDbTextStyleTable* pTextStyleTable;
	ARXRLEDB->getTextStyleTable(pTextStyleTable, AcDb::kForWrite);

	AcDbTextStyleTableIterator *pIt = NULL;
	pTextStyleTable->newIterator(pIt);
	for (;!pIt->done();pIt->step())
	{
		AcDbTextStyleTableRecord *pRcd = NULL;
		if (pIt->getRecord(pRcd, AcDb::kForWrite) == Acad::eOk)
		{
			pRcd->setFileName(L"txt");
			pRcd->setBigFontFileName(L"tjhzf");
			pRcd->setXScale(0.7);
			pRcd->close();
		}
	}
	delete pIt;
	pTextStyleTable->close();

	msgInf(L"文字样式统一格式为 txt.shx+tjhzf.shx!");
}

/****************************************************************************
**
**  ArxRleCmdText::textShowAll
**
**  **000
**
*************************************/

Adesk::Boolean ShowAllText( AcDbEntity* ent )
{

	if(ent->isKindOf(AcDbMText::desc()) || ent->isKindOf(AcDbText::desc()))
		ent->setVisibility(AcDb::kVisible);

	return Adesk::kTrue;
}
void ArxRleCmdText::textShowAll()
{
	ArxRleApply<BlockTableRecord>(ARXRLEDS, ShowAllText, AcDb::kForWrite );
	ARXRLEDS->close();
}

/****************************************************************************
**
**  ArxRleCmdText::textHideAll
**
**  **000
**
*************************************/

Adesk::Boolean HideAllText( AcDbEntity* ent )
{
	if(ent->isKindOf(AcDbMText::desc()) || ent->isKindOf(AcDbText::desc()))
		ent->setVisibility(AcDb::kInvisible);

	return Adesk::kTrue;
}
void ArxRleCmdText::textHideAll()
{
	ArxRleApply<BlockTableRecord>(ARXRLEDS, HideAllText, AcDb::kForWrite );
	ARXRLEDS->close();
}

/****************************************************************************
**
**  ArxRleCmdText::textHidePart
**
**  **000
**
*************************************/

void ArxRleCmdText::textHidePart()
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
					if(ent->isKindOf(AcDbMText::desc()) || ent->isKindOf(AcDbText::desc()))
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
							if(ent->isKindOf(AcDbMText::desc()) || ent->isKindOf(AcDbText::desc()))
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
**  ArxRleCmdText::textShowByStyle
**
**  **000
**
*************************************/

void ArxRleCmdText::textShowByStyle()
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
					if(ent->isKindOf(AcDbMText::desc()))
						tsId = ((AcDbMText*)ent)->textStyle();
					if(ent->isKindOf(AcDbText::desc()))
						tsId = ((AcDbText*)ent)->textStyle();

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
							if(ent->isKindOf(AcDbMText::desc()))
								tsId = ((AcDbMText*)ent)->textStyle();
							if(ent->isKindOf(AcDbText::desc()))
								tsId = ((AcDbText*)ent)->textStyle();

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
		if(acedGetString(1,L"输入文字样式名称：",str_put,MAX_PATH) == RTNORM)
		{
			if(ArxRleString(str_put).GetLength() > 0)
				tsId = FindTextStyle(str_put);
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
					if(elem->isKindOf(AcDbMText::desc()))
						tsId1 = ((AcDbMText*)elem)->textStyle();
					if(elem->isKindOf(AcDbText::desc()))
						tsId1 = ((AcDbText*)elem)->textStyle();
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
**  ArxRleCmdText::textHideByStyle
**
**  **000
**
*************************************/

void ArxRleCmdText::textHideByStyle()
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
					if(ent->isKindOf(AcDbMText::desc()))
						tsId = ((AcDbMText*)ent)->textStyle();
					if(ent->isKindOf(AcDbText::desc()))
						tsId = ((AcDbText*)ent)->textStyle();

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
							if(ent->isKindOf(AcDbMText::desc()))
								tsId = ((AcDbMText*)ent)->textStyle();
							if(ent->isKindOf(AcDbText::desc()))
								tsId = ((AcDbText*)ent)->textStyle();

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
		if(acedGetString(1,L"输入文字样式名称：",str_put,MAX_PATH) == RTNORM)
		{
			if(ArxRleString(str_put).GetLength() > 0)
				tsId = FindTextStyle(str_put);
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
					if(elem->isKindOf(AcDbMText::desc()))
						tsId1 = ((AcDbMText*)elem)->textStyle();
					if(elem->isKindOf(AcDbText::desc()))
						tsId1 = ((AcDbText*)elem)->textStyle();
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
**  ArxRleCmdText::textShowByHeight
**
**  **000
**
*************************************/

void ArxRleCmdText::textShowByHeight()
{
	ArxRleSelSet ss;
	double height = 0;
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
					if(ent->isKindOf(AcDbMText::desc()))
						height = ((AcDbMText*)ent)->textHeight();
					if(ent->isKindOf(AcDbText::desc()))
						height = ((AcDbText*)ent)->height();

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
							if(ent->isKindOf(AcDbMText::desc()))
								height = ((AcDbMText*)ent)->textHeight();
							if(ent->isKindOf(AcDbText::desc()))
								height = ((AcDbText*)ent)->height();

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
		ads_real real_put;
		if(acedGetReal(_T("\n请输入文字高度... "),&real_put) == RTNORM)
			height = real_put;
	}

	if(height > 0)
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
					double height1 = 0;
					if(elem->isKindOf(AcDbMText::desc()))
						height1 = ((AcDbMText*)elem)->textHeight();
					if(elem->isKindOf(AcDbText::desc()))
						height1 = ((AcDbText*)elem)->height();
					if(height != height1) elem->setVisibility(AcDb::kInvisible);

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
**  ArxRleCmdText::textHideByHeight
**
**  **000
**
*************************************/

void ArxRleCmdText::textHideByHeight()
{
	ArxRleSelSet ss;
	double height = 0;
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
					if(ent->isKindOf(AcDbMText::desc()))
						height = ((AcDbMText*)ent)->textHeight();
					if(ent->isKindOf(AcDbText::desc()))
						height = ((AcDbText*)ent)->height();

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
							if(ent->isKindOf(AcDbMText::desc()))
								height = ((AcDbMText*)ent)->textHeight();
							if(ent->isKindOf(AcDbText::desc()))
								height = ((AcDbText*)ent)->height();

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
		ads_real real_put;
		if(acedGetReal(_T("\n请输入文字高度... "),&real_put) == RTNORM)
			height = real_put;
	}

	if(height > 0)
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
					double height1 = 0;
					if(elem->isKindOf(AcDbMText::desc()))
						height1 = ((AcDbMText*)elem)->textHeight();
					if(elem->isKindOf(AcDbText::desc()))
						height1 = ((AcDbText*)elem)->height();
					if(height == height1) elem->setVisibility(AcDb::kInvisible);

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
**  ArxRleCmdText::textShowByAngle
**
**  **000
**
*************************************/

void ArxRleCmdText::textShowByAngle()
{
	ArxRleSelSet ss;
	double angle = 0;
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
					if(ent->isKindOf(AcDbMText::desc()))
						angle = ((AcDbMText*)ent)->rotation();
					if(ent->isKindOf(AcDbText::desc()))
						angle = ((AcDbText*)ent)->rotation();

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
							if(ent->isKindOf(AcDbMText::desc()))
								angle = ((AcDbMText*)ent)->rotation();
							if(ent->isKindOf(AcDbText::desc()))
								angle = ((AcDbText*)ent)->rotation();

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
		ads_real real_put;
		if(acedGetReal(_T("\n请输入文字角度... "),&real_put) == RTNORM)
			angle = real_put;
	}

	if(angle != 0)
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
					double angle1 = 0;
					if(elem->isKindOf(AcDbMText::desc()))
						angle1 = ((AcDbMText*)elem)->rotation();
					if(elem->isKindOf(AcDbText::desc()))
						angle1 = ((AcDbText*)elem)->rotation();
					if(angle != angle1) elem->setVisibility(AcDb::kInvisible);

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
**  ArxRleCmdText::textHideByAngle
**
**  **000
**
*************************************/

void ArxRleCmdText::textHideByAngle()
{
	ArxRleSelSet ss;
	double angle = 0;
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
					if(ent->isKindOf(AcDbMText::desc()))
						angle = ((AcDbMText*)ent)->rotation();
					if(ent->isKindOf(AcDbText::desc()))
						angle = ((AcDbText*)ent)->rotation();

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
							if(ent->isKindOf(AcDbMText::desc()))
								angle = ((AcDbMText*)ent)->rotation();
							if(ent->isKindOf(AcDbText::desc()))
								angle = ((AcDbText*)ent)->rotation();

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
		ads_real real_put;
		if(acedGetReal(_T("\n请输入文字角度... "),&real_put) == RTNORM)
			angle = real_put;
	}

	if(angle > 0)
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
					double angle1 = 0;
					if(elem->isKindOf(AcDbMText::desc()))
						angle1 = ((AcDbMText*)elem)->rotation();
					if(elem->isKindOf(AcDbText::desc()))
						angle1 = ((AcDbText*)elem)->rotation();
					if(angle == angle1) elem->setVisibility(AcDb::kInvisible);

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
**  ArxRleCmdText::textShowByStr
**
**  **000
**
*************************************/

void ArxRleCmdText::textShowByStr()
{
	ArxRleSelSet ss;
	ArxRleString str;
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
					if(ent->isKindOf(AcDbMText::desc()))
						str = ((AcDbMText*)ent)->contents();
					if(ent->isKindOf(AcDbText::desc()))
						str = ((AcDbText*)ent)->textString();

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
							if(ent->isKindOf(AcDbMText::desc()))
								str = ((AcDbMText*)ent)->contents();
							if(ent->isKindOf(AcDbText::desc()))
								str = ((AcDbText*)ent)->textString();

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
		if(acedGetString(1,_T("\n请输入文字内容... "),str_put,MAX_PATH) == RTNORM)
			str = str_put;
	}

	if(str.GetLength() > 0)
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
					ArxRleString str1;
					if(elem->isKindOf(AcDbMText::desc()))
						str1 = ((AcDbMText*)elem)->contents();
					if(elem->isKindOf(AcDbText::desc()))
						str1 = ((AcDbText*)elem)->textString();
					if(str != str1) elem->setVisibility(AcDb::kInvisible);

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
**  ArxRleCmdText::textHideByStr
**
**  **000
**
*************************************/

void ArxRleCmdText::textHideByStr()
{
	ArxRleSelSet ss;
	ArxRleString str;
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
					if(ent->isKindOf(AcDbMText::desc()))
						str = ((AcDbMText*)ent)->contents();
					if(ent->isKindOf(AcDbText::desc()))
						str = ((AcDbText*)ent)->textString();

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
							if(ent->isKindOf(AcDbMText::desc()))
								str = ((AcDbMText*)ent)->contents();
							if(ent->isKindOf(AcDbText::desc()))
								str = ((AcDbText*)ent)->textString();

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
		if(acedGetString(1,_T("\n请输入文字内容... "),str_put,MAX_PATH) == RTNORM)
			str = str_put;
	}

	if(str.GetLength() > 0)
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
					ArxRleString str1;
					if(elem->isKindOf(AcDbMText::desc()))
						str1 = ((AcDbMText*)elem)->contents();
					if(elem->isKindOf(AcDbText::desc()))
						str1 = ((AcDbText*)elem)->textString();
					if(str == str1) elem->setVisibility(AcDb::kInvisible);

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
**  ArxRleCmdText::textFlush
**
**  **000
**
*************************************/

void ArxRleCmdText::textFlush()
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
					if(ent->isKindOf(AcDbMText::desc()) || ent->isKindOf(AcDbText::desc()))
					{
						AcDbMText* pMText;
						AcDbText* pText;

						AcDbObjectId tsId  = GetCurTextStyle();
						if((pMText = AcDbMText::cast(ent)) != NULL)
						{
							pMText->setTextStyle(tsId);
						}
						else if((pText = AcDbText::cast(ent)) != NULL)
						{
							AcDbTextStyleTableRecord* ts = (AcDbTextStyleTableRecord*)GetRecordPtr(tsId);
							pText->setTextStyle(tsId);
							double wf = ts->xScale();
							pText->setWidthFactor(wf);
							ts->close();
						}
					}

					ent->close();
				}
				else if(es == Acad::eOnLockedLayer)
				{
					es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForRead, true);		// might have passed in erased ones
					if(es == Acad::eOk)
					{
						if(UnLockEntity(ent))
						{
							if(ent->isKindOf(AcDbMText::desc()) || ent->isKindOf(AcDbText::desc()))
							{
								AcDbMText* pMText;
								AcDbText* pText;

								AcDbObjectId tsId  = GetCurTextStyle();
								if((pMText = AcDbMText::cast(ent)) != NULL)
								{
									pMText->setTextStyle(tsId);
								}
								else if((pText = AcDbText::cast(ent)) != NULL)
								{
									AcDbTextStyleTableRecord* ts = (AcDbTextStyleTableRecord*)GetRecordPtr(tsId);
									pText->setTextStyle(tsId);
									double wf = ts->xScale();
									pText->setWidthFactor(wf);
									ts->close();
								}
							}

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
**  ArxRleCmdText::textCalc
**
**  **000
**
*************************************/

void ArxRleCmdText::textCalc()
{
	ArxRleString str;
	ArxRleSelSet ss;
	AcDbEntity* entOrg = NULL;
	bool bOrg = true;
	while(1)
	{
		if(ss.userSelect(L"选择数字：",NULL) == ArxRleSelSet::kSelected)
		{    // have user select entities from DWG
			AcDbObjectIdArray objIds;
			Acad::ErrorStatus es;
			ss.asArray(objIds);
			if(bOrg)
			{
				es = acdbOpenAcDbEntity(entOrg, objIds[0], AcDb::kForRead, true);		// might have passed in erased ones
				if(es == Acad::eOk)
				{
					if(entOrg->isKindOf(AcDbMText::desc()) || entOrg->isKindOf(AcDbText::desc()))
						bOrg = !bOrg;
				}
			}
			else
			{
				AcDbEntity* ent;
				es = acdbOpenAcDbEntity(ent, objIds[0], AcDb::kForRead, true);		// might have passed in erased ones
				if(es == Acad::eOk)
				{
					if(ent->isKindOf(AcDbMText::desc()))
						str += ((AcDbMText*)ent)->contents();

					if(ent->isKindOf(AcDbText::desc()))
						str += ((AcDbText*)ent)->textString();

					ent->close();
				}
			}
		}
		else
		{
			ACHAR* str_put = new ACHAR[MAX_PATH];;
			if(acedGetString(1,L"输入公式：",str_put,MAX_PATH) == RTNORM)
			{
				if(ArxRleString(str_put).GetLength() > 0)
					str += str_put;
				else break;
			}
			else
			{
				str = L"";
				break;
			}
		}
	}

	CMapVariable vars;
	CXTPExpression expr;
	vars.InitHashTable(100);
	expr.AtachVariables(&vars);
	expr.ChangeExpression(str.t_str());
	double fvalue = 0;
	long result = expr.GetValue(fvalue);
	if(result == 0 && entOrg != NULL)
	{
		if(UnLockEntity(entOrg))
		{
			str = _variant_t(fvalue);
			if(entOrg->isKindOf(AcDbMText::desc()))
				((AcDbMText*)entOrg)->setContents(str.w_ptr());
			if(entOrg->isKindOf(AcDbText::desc()))
				((AcDbText*)entOrg)->setTextString(str.w_ptr());

			entOrg->close();
		}
	}
	else acutPrintf(L"Invalid Expression !");
}

/****************************************************************************
**
**  ArxRleCmdText::textImport
**
**  **000
**
*************************************/

void ArxRleCmdText::textImport()
{
	TCHAR szFilter[] = _T("文本文件|*.txt|所有文件|*.*||");
	CFileDialog FileDlg(TRUE, _T("txt"), NULL, 0, szFilter, NULL);
	if (IDOK == FileDlg.DoModal())
	{
		CString strFilePath = FileDlg.GetPathName();
		CString strPath = strFilePath.Mid(0, strFilePath.ReverseFind('\\')) + _T("\\");

		CStdioFile file;
		CStringArray strArray;
		if (file.Open(strPath + _T("dwg_txt.txt"), CFile::modeRead))
		{
			int nPos = 0;
			CString strLine;

			while (file.ReadString(strLine))
			{
				strLine.Trim();
				strArray.Add(strLine);
			}

			file.Close();
		}

		CPt3d pt(0, 0, 0);
		for (int i = 0; i < strArray.GetCount(); i++)
		{
			pt.y += i * 5;
			CText text;
			ArxRleString str;
			text.SetText(strArray[i]);
			text.SetTextHeight(2);
			text.SetPosition(pt);
			text.SetAlignmentMode(ArxLeftBottom);
			AddEntity(&text);
		}

		msgInf(_T("DWG TXT文件导入成功!"));
	}
}

/****************************************************************************
**
**  ArxRleCmdText::textExport
**
**  **000
**
*************************************/

void ArxRleCmdText::textExport()
{
	ArxRleSelSet ss;
	if (ss.userSelect() == ArxRleSelSet::kSelected)
	{    // have user select entities from DWG
		AcDbObjectIdArray objList;
		ss.asArray(objList);
		if (!objList.isEmpty())
		{
			AcDbEntity* ent;
			Acad::ErrorStatus es;
			CStringArray strArray;

			int len = objList.length();
			for (int i = 0; i < len; i++)
			{
				es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForWrite, true);		// might have passed in erased ones
				if (es == Acad::eOk)
				{
					if (ent->isKindOf(AcDbMText::desc()) || ent->isKindOf(AcDbText::desc()))
					{
						AcDbMText* pMText;
						AcDbText* pText;

						AcDbObjectId tsId = GetCurTextStyle();
						if ((pMText = AcDbMText::cast(ent)) != NULL)
						{
							strArray.Add(pMText->text());
						}
						else if ((pText = AcDbText::cast(ent)) != NULL)
						{
							strArray.Add(pText->textString());
						}
					}

					ent->close();
				}
				else if (es == Acad::eOnLockedLayer)
				{
					es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForRead, true);		// might have passed in erased ones
					if (es == Acad::eOk)
					{
						if (UnLockEntity(ent))
						{
							if (ent->isKindOf(AcDbMText::desc()) || ent->isKindOf(AcDbText::desc()))
							{
								AcDbMText* pMText;
								AcDbText* pText;

								AcDbObjectId tsId = GetCurTextStyle();
								if ((pMText = AcDbMText::cast(ent)) != NULL)
								{
									strArray.Add(pMText->text());
								}
								else if ((pText = AcDbText::cast(ent)) != NULL)
								{
									strArray.Add(pText->textString());
								}
							}

							ent->close();
						}
					}
				}
			}

			TCHAR szFilter[] = _T("文本文件|*.txt|所有文件|*.*||");
			CFileDialog FileDlg(TRUE, _T("txt"), NULL, 0, szFilter, NULL);
			if (IDOK == FileDlg.DoModal())
			{
				CString strFilePath = FileDlg.GetPathName();
				CString strPath = strFilePath.Mid(0, strFilePath.ReverseFind('\\')) + _T("\\");

				CStdioFile file;
				if (file.Open(strPath + _T("dwg_txt.txt"), CFile::modeCreate | CFile::modeReadWrite))
				{
					file.Seek(CFile::begin, 0);

					for (int i = 0; i < strArray.GetCount(); i++)
					{
						CString str;
						str.Format(_T("%s\n"), strArray[i]);
						file.WriteString(str);
					}

					file.Close();
					msgInf(_T("DWG TXT文件生成成功!"));
				}
			}
		}
	}
}