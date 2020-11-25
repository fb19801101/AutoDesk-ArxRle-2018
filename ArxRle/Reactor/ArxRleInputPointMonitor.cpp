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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleInputPointMonitor.h"
#include "AcadUtils\ArxRleUtils.h"
#include "DbEntity\ArxRleEntityClass.h"
#include "ExEntity\ArxRleTitleLabel.h"
#include "ExEntity\ArxRleBrokenLine.h"
#include "NetPlan\ArxRleNetPlanWork.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleInputPointMonitor, AcEdInputPointMonitor);


/////////////////////////////////////////////////////////////////////////////
//////////// STATIC CONSTRUCTOR/DESTRUCTOR FOR THIS SINGLETON CLASS /////////
/////////////////////////////////////////////////////////////////////////////

ArxRleInputPointMonitor* ArxRleInputPointMonitor::m_instance = NULL;

/****************************************************************************
**
**  ArxRleInputPointMonitor::getInstance
**
**  **000
**
*************************************/

ArxRleInputPointMonitor* ArxRleInputPointMonitor::getInstance()
{
	if(m_instance)
		return m_instance;

	m_instance = new ArxRleInputPointMonitor;

	AcApDocument* pDoc = acDocManager->curDocument();
	pDoc->inputPointManager()->addPointMonitor(m_instance);

	return m_instance;
}

/****************************************************************************
**
**  ArxRleInputPointMonitor::destroyInstance
**
**  **000
**
*************************************/

void ArxRleInputPointMonitor::destroyInstance()
{
	if(m_instance) {
		AcApDocument* pDoc = acDocManager->curDocument();
		pDoc->inputPointManager()->removePointMonitor(m_instance);
		delete m_instance;
		m_instance = NULL;
	}
	else {
		ASSERT(0);
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**	ArxRleInputPointMonitor::ArxRleInputPointMonitor
**
**  **000
**
*************************************/

ArxRleInputPointMonitor::ArxRleInputPointMonitor()
{
	AcApDocument* pDoc = acDocManager->curDocument();
	pDoc->inputPointManager()->addPointMonitor(this);
}

/****************************************************************************
**
**	ArxRleAppEditorReactor::~ArxRleInputPointMonitor
**
**  **000
**
*************************************/

ArxRleInputPointMonitor::~ArxRleInputPointMonitor()
{
	AcApDocument* pDoc = acDocManager->curDocument();
	pDoc->inputPointManager()->removePointMonitor(this);
}

/****************************************************************************
**
**	ArxRleAppEditorReactor::monitorInputPoint
**
**  **000
**
*************************************/

Acad::ErrorStatus ArxRleInputPointMonitor::monitorInputPoint(const AcEdInputPoint& input, AcEdInputPointMonitorResult& output)
{
	if ( !input.pointComputed() )  
	{  
		// Points cannot be computed in the Monitor  
		// Forced picking may be enabled  

		if ( input.history() & Acad::eCyclingPt)  
			acutPrintf( _T("\nNo point computed, but new cycling osnap: %.2f, %.2f, %.2f\n"),  
			input.osnappedPoint()[X], input.osnappedPoint()[Y], input.osnappedPoint()[Z] );  

		return Acad::eOk;  
	}

	// 一定要注意检查缓冲区的大小，避免越界导致的Acad直接跳出
	TCHAR mtooltipStr[1024], tempStr[1024];			
	mtooltipStr[0] = '\0';

	Acad::ErrorStatus es;
	AcDbEntity* pEnt;
	AcDbObjectId highlightId = AcDbObjectId::kNull;

	// 分析光标所覆盖的实体
	if (input.pickedEntities().length() > 0)
	{
		for (int i = 0; i < input.pickedEntities().length(); ++i)
		{
			// 避免显示更多的实体（根据需要确定是否需要）
			if (i > 0)
			{
				break;
			}

			if (Acad::eOk != (acdbOpenAcDbEntity(pEnt, input.pickedEntities()[i], AcDb::kForRead)))
			{
				continue;
			}

			if (pEnt->isKindOf(ArxRleBrokenLine::desc()))
			{					
				_tcscpy(mtooltipStr, TEXT("折断线 (ArxRleBrokenLine):"));
				ArxRleBrokenLine* broken = ArxRleBrokenLine::cast(pEnt);
				double size = broken->getBrokenSize();
				CPt3d pt1 = broken->getPointBegin();
				CPt3d pt2 = broken->getPointEnd();
				_stprintf(tempStr, TEXT("\n 起点坐标: %s\n 终点坐标: %s\n 大小: %.3f\n"), pt1.sPt(), pt2.sPt(),size);
				_tcscat(mtooltipStr, tempStr);
			}
			else if (pEnt->isKindOf(ArxRleTitleLabel::desc()))
			{
				_tcscpy(mtooltipStr, TEXT("标题 (ArxRleTitleLabel):"));
				ArxRleTitleLabel* title = ArxRleTitleLabel::cast(pEnt);
				double size = title->getTextSize();
				CPt3d pt = title->getPointMid();
				_stprintf(tempStr, TEXT("\n 插入点坐标: %s\n 文字样式: %s\n 文字大小: %.3f\n 标题内容: %s\n"), pt.sPt(), title->getTextStyle().t_str(), size, title->getLabelUp().t_str());
				_tcscat(mtooltipStr, tempStr);
			}
			else if (pEnt->isKindOf(ArxRleNetPlanWork::desc()))
			{
				_tcscpy(mtooltipStr, TEXT("工序 (ArxRleNetPlanWork):"));
				ArxRleNetPlanWork* work = ArxRleNetPlanWork::cast(pEnt);
				CString begin = work->getLabelBegin().t_str();
				CString end = work->getLabelEnd().t_str();
				CString up = work->getLabelUp().t_str();
				CString down = work->getLabelDown().t_str();
				CString style = work->getWorkStyle().t_str();
				CString res = work->getWorkDes().t_str();
				CString ref = work->getBindWorkRef().t_str();

				_stprintf(tempStr, TEXT("\n 开始节点: %s\n 结束节点: %s\n 工序样式: %s\n 工序名称: %s\n 工序时长: %s\n 紧后工序: %s\n"), begin,end,style,up,down,ref);
				_tcscat(mtooltipStr, tempStr);
			}

			pEnt->close();				
		}
		highlightId = input.pickedEntities()[0];
	}

	// 执行高亮显示，只有在显示最顶层的实体会被高亮显示
	static AcDbObjectId oldHighlightId = AcDbObjectId::kNull;
	if(highlightId != oldHighlightId)
	{
		if (AcDbObjectId::kNull != oldHighlightId)
		{
			es = acdbOpenAcDbEntity(pEnt, oldHighlightId, AcDb::kForRead);
			if (es == Acad::eOk)
			{
				es = pEnt->unhighlight();
				pEnt->close();
				oldHighlightId = AcDbObjectId::kNull;
			}
		}
		es = acdbOpenAcDbEntity(pEnt, highlightId, AcDb::kForRead);
		if (es == Acad::eOk)
		{
			es = pEnt->highlight();
			pEnt->close();
			oldHighlightId = highlightId;
		}
	}

	output.setAdditionalTooltipString(mtooltipStr);

	return Acad::eOk;

	// Show historical point selection information  
	//  
#define HISTORY_CHECK(x)  if (input.history() & Acad:: ## x) acutPrintf(_T("%s "), _T(#x))  

	acutPrintf( _T("\nHistory: %d, "), input.history() );  

	HISTORY_CHECK(eTablet);  
	HISTORY_CHECK(eNotDigitizer);  
	HISTORY_CHECK(eLastPt);  
	HISTORY_CHECK(eGripped);  
	HISTORY_CHECK(eCartSnapped);  
	HISTORY_CHECK(eOrtho);  
	HISTORY_CHECK(eCyclingPt);  
	HISTORY_CHECK(eOsnapped);  
	HISTORY_CHECK(ePolarAngle);  
	HISTORY_CHECK(eAligned);  
	HISTORY_CHECK(eAppFiltered);  
	HISTORY_CHECK(eForcedPick);  
	HISTORY_CHECK(ePickMask);  
	HISTORY_CHECK(eDidNotPick);  
	HISTORY_CHECK(eUsedPickBox);  
	HISTORY_CHECK(eUsedOsnapBox);  
	HISTORY_CHECK(ePickAborted);  
	HISTORY_CHECK(eXPending);  
	HISTORY_CHECK(eYPending);  
	HISTORY_CHECK(eZPending);  
	HISTORY_CHECK(eCoordPending);  

#undef HISTORY_CHECK  

	acutPrintf( _T("\n") );  

	// Show more point input information  
	//  
	if ( input.history() & Acad::eLastPt )  
		acutPrintf( _T("Last point:              %.2f, %.2f, %.2f\n"), input.lastPoint()[X], input.lastPoint()[Y], input.lastPoint()[Z] );  

	acutPrintf( _T("Raw point:               %.2f, %.2f, %.2f\n"), input.rawPoint()[X], input.rawPoint()[Y], input.rawPoint()[Z] );  
	acutPrintf( _T("Computed point:          %.2f, %.2f, %.2f\n"), input.computedPoint()[X], input.computedPoint()[Y], input.computedPoint()[Z] );  

	if ( input.history() & Acad::eGripped )  
		acutPrintf( _T("Gripped point:           %.2f, %.2f, %.2f\n"), input.grippedPoint()[X], input.grippedPoint()[Y], input.grippedPoint()[Z] );  

	if ( input.history() & Acad::eCartSnapped )  
		acutPrintf( _T("Cartesian snapped point: %.2f, %.2f, %.2f\n"), input.cartesianSnappedPoint()[X], input.cartesianSnappedPoint()[Y], input.cartesianSnappedPoint()[Z] );  

	if ( input.history() & Acad::eOsnapped )  
	{  
		acutPrintf( _T("Osnapped point:          %.2f, %.2f, %.2f\n"), input.osnappedPoint()[X], input.osnappedPoint()[Y], input.osnappedPoint()[Z] );  

		acutPrintf( _T("Object snap masks: ") );  

#define OSMASK_CHECK(x)  if (input.osnapMask() & AcDb:: ## x) acutPrintf(_T("%s "), _T(#x))  

		OSMASK_CHECK(kOsMaskEnd);  
		OSMASK_CHECK(kOsMaskMid);  
		OSMASK_CHECK(kOsMaskCen);  
		OSMASK_CHECK(kOsMaskNode);  
		OSMASK_CHECK(kOsMaskQuad);  
		OSMASK_CHECK(kOsMaskInt);  
		OSMASK_CHECK(kOsMaskIns);  
		OSMASK_CHECK(kOsMaskPerp);  
		OSMASK_CHECK(kOsMaskTan);  
		OSMASK_CHECK(kOsMaskNear);  
		OSMASK_CHECK(kOsMaskQuick);  
		OSMASK_CHECK(kOsMaskApint);  
		OSMASK_CHECK(kOsMaskImmediate);  
		OSMASK_CHECK(kOsMaskAllowTan);  
		OSMASK_CHECK(kOsMaskDisablePerp);  
		OSMASK_CHECK(kOsMaskRelCartesian);  
		OSMASK_CHECK(kOsMaskRelPolar);  

#undef OSMASK_CHECK  

		if ( 0 == input.osnapMask() )  
		{  
			for ( int i = 0; i < input.customOsnapModes().length(); i++ )  
				acutPrintf( _T("%s\n"), input.customOsnapModes()[i] );  
		}  
		acutPrintf( _T("\n") );  
	}  

	// Show the object snap overrides  
	//  
	if ( 0 != input.osnapOverrides() )  
	{  

		acutPrintf( _T("Object snap overrides: ") );  

#define OSMASK_CHECK(x)  if (input.osnapOverrides() & AcDb:: ## x) acutPrintf(_T("%s "), _T(#x))  

		OSMASK_CHECK(kOsMaskEnd);  
		OSMASK_CHECK(kOsMaskMid);  
		OSMASK_CHECK(kOsMaskCen);  
		OSMASK_CHECK(kOsMaskNode);  
		OSMASK_CHECK(kOsMaskQuad);  
		OSMASK_CHECK(kOsMaskInt);  
		OSMASK_CHECK(kOsMaskIns);  
		OSMASK_CHECK(kOsMaskPerp);  
		OSMASK_CHECK(kOsMaskTan);  
		OSMASK_CHECK(kOsMaskNear);  
		OSMASK_CHECK(kOsMaskQuick);  
		OSMASK_CHECK(kOsMaskApint);  
		OSMASK_CHECK(kOsMaskImmediate);  
		OSMASK_CHECK(kOsMaskAllowTan);  
		OSMASK_CHECK(kOsMaskDisablePerp);  
		OSMASK_CHECK(kOsMaskRelCartesian);  
		OSMASK_CHECK(kOsMaskRelPolar);  

#undef OSMASK_CHECK  

		acutPrintf(_T("\n"));  
	}  

	// Show custom object snap overrides  
	//  
	if ( 0 != input.customOsnapOverrides().length() )  
	{  
		acutPrintf( _T("Custom object snap overrides: ") );  
		for ( int x = 0; x < input.customOsnapOverrides().length(); x++)  
			acutPrintf( _T("%s "), input.customOsnapOverrides()[x] );  
		acutPrintf( _T("\n") );  
	}  

	// Show object snap or forced pick information: the entities in the aperture  
	acutPrintf( _T("%d apertured entities, "), input.pickedEntities().length() );  
	acutPrintf( _T("%d nested apertured entities\n"), input.nestedPickedEntities().length() );  

	// Show AutoSnap information  
	// Note: nestedKeyPointEntities.length() == keyPointGsSelectionMark.length()  
	//  
	acutPrintf( _T("%d key point entities, "), input.keyPointEntities().length() );  
	acutPrintf( _T("%d nested key point entities\n"), input.nestedKeyPointEntities().length() );  
	acutPrintf( _T("%d alignment paths\n"), input.alignmentPaths().length() );  

	// Add an additional comment to the tootip string  
	//  
	if ( NULL != input.tooltipString() )  
	{  
		output.setAdditionalTooltipString(_T(", Additional comment!"));  
		acutPrintf( _T("Appending \"%s\" to \"%s\"\n"), _T(", Additional comment!"), input.tooltipString() );  
	}  
	else  
		acutPrintf( _T("Tooltip is NULL\n") );  

	acedPostCommandPrompt();  
	return Acad::eOk; 
}

/****************************************************************************
**
**	ArxRleAppEditorReactor::excludeFromOsnapCalculation
**
**  **000
**
*************************************/

bool ArxRleInputPointMonitor::excludeFromOsnapCalculation( const AcArray<AcDbObjectId>& nestedEntity, int gsSelectionMark )
{
	return false;
}
