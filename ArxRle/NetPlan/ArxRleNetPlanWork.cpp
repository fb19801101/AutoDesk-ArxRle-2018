//////////////////////////////////////////////////////////////////////////////
//  class ArxRleNetPlanWork
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//  
//  ArxRleNetPlanWork.cpp  Implementation of ArxRleNetPlanWork
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArxRleNetPlanWork.h"
#include "ArxRleNetPlanWorkStyle.h"
#include "DbEntity/ArxRleEntityClass.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#define ACDBTEXT_COUNT 5

Adesk::Int16 ArxRleNetPlanWork::m_version = 0;
ACRX_DXF_DEFINE_MEMBERS (
	ArxRleNetPlanWork, ArxRleDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	0, ArxRleNetPlanWork/*在CAD中该实体类的名称*/,
	ARXRLE_ADESK_NETPLAN_WORK
	|Product Desc:     工序标注
	|Company:          中铁十二局集团一公司
	|WEB Address:      http://www.cr201.com
);

ArxRleNetPlanWork::ArxRleNetPlanWork () : ArxRleDbEntity ()
{
	m_workStyleName = acdbGetReservedString(AcDb::kStandard, false);
	m_workStyleId = ArxRleNetPlanWorkStyle::getStandardStyle(True);
	m_autoMove     = false;
	m_moveLeft     = false;
	m_moveMid      = false;
	m_moveRight    = false;
	m_setLabelDown = false;
	m_bindWork     = false;
	m_drawNode     = 2;

	m_txtBegin = NULL;
	m_txtEnd = NULL;
	m_txtDown = NULL;
	m_circleBegin = NULL;
	m_circleEnd = NULL;
	m_polyline = NULL;

	m_bindWorkRefId = AcDbObjectId::kNull;

	for(int i=0; i<ACDBTEXT_COUNT; i++)
		m_vecTxtUp.push_back(new AcDbText);
}

ArxRleNetPlanWork::~ArxRleNetPlanWork ()
{
	if(NULL != m_txtBegin) delete m_txtBegin;
	if(NULL != m_txtEnd) delete m_txtEnd;
	if(NULL != m_txtDown) delete m_txtDown;
	if(NULL != m_circleBegin) delete m_circleBegin;
	if(NULL != m_circleEnd) delete m_circleEnd;
	if(NULL != m_polyline) delete m_polyline;

	m_txtBegin = NULL;
	m_txtEnd = NULL;
	m_txtDown = NULL;
	m_circleBegin = NULL;
	m_circleEnd = NULL;
	m_polyline = NULL;

	for(int i=0; i<ACDBTEXT_COUNT; i++)
		if(m_vecTxtUp[i] != NULL) delete m_vecTxtUp[i];
	m_vecTxtUp.clear();
}

// 属性设置

void ArxRleNetPlanWork::setWorkCode(Adesk::UInt32 workCode)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_workCode = workCode;
}

void ArxRleNetPlanWork::setPointBegin(CPt3d ptBegin)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_ptBegin = ptBegin;
}

void ArxRleNetPlanWork::setPointLeft(CPt3d ptLeft)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_ptLeft = ptLeft;
}

void ArxRleNetPlanWork::setPointMid(CPt3d ptMid)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_ptMid = ptMid;
}

void ArxRleNetPlanWork::setPointRight(CPt3d pRight)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_ptRight = pRight;
}

void ArxRleNetPlanWork::setPointEnd(CPt3d ptEnd)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_ptEnd = ptEnd;
}

void ArxRleNetPlanWork::setLabelBegin(ArxRleString labelBegin)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_labelBegin = labelBegin.a_str();
}

void ArxRleNetPlanWork::setLabelEnd(ArxRleString labelEnd)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_labelEnd = labelEnd.a_str();
}

void ArxRleNetPlanWork::setLabelUp(ArxRleString labelUp)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_labelUp = labelUp.a_str();
}

void ArxRleNetPlanWork::setLabelDown(ArxRleString labelDown)
{
	assertWriteEnabled ();
	m_autoMove = false;

	m_labelDown = labelDown.a_str();
	if(!m_labelDown.isEmpty())
		m_setLabelDown = true;
}

void ArxRleNetPlanWork::setWorkStyle(ArxRleString wsName)
{
	m_workStyleId = ArxRleNetPlanWorkStyle::getWorkStyle(wsName);
	if(m_workStyleId != AcDbObjectId::kNull)
	{
		assertWriteEnabled ();
		m_autoMove = false;
		m_workStyleName = wsName.a_str();

		ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
		Acad::ErrorStatus es = acdbOpenObject(style, m_workStyleId, AcDb::kForRead);
		if(es == Acad::eOk)
		{
			m_workStyleName = style->name().a_str();
			setColorIndex(style->colorIndex());
			setLayer(style->layer());
			setLinetype(style->lineType());
			setLinetypeScale(style->lineScale());
			m_drawNode = style->drawLabelBegin()+style->drawLabelEnd();
			style->close();
		}
		else
			delete style;
	}
}

void ArxRleNetPlanWork::setWorkDes(ArxRleString resDes)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_workDes = resDes.a_str();
}

void ArxRleNetPlanWork::setBindWorkRef(ArxRleString wrName)
{
	if(m_bindWorkRefId != AcDbObjectId::kNull)
	{
		assertWriteEnabled();
		m_bindWorkRefName = wrName.a_str();

		ArxRleNetPlanWork* work = new ArxRleNetPlanWork;
		Acad::ErrorStatus es = acdbOpenObject(work, m_bindWorkRefId, AcDb::kForWrite);
		if(es == Acad::eOk)
		{
			work->setLabelUp(m_bindWorkRefName);
			work->close();
		}
		else
			delete work;
	}
}

void ArxRleNetPlanWork::setResMens(double resMens)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_resMens = resMens;
}

void ArxRleNetPlanWork::setResTools(double resTools)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_resTools = resTools;
}

void ArxRleNetPlanWork::setResMoney(double resMoney)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_resMoney = resMoney;
}

void ArxRleNetPlanWork::setPoint(CPt3d ptBegin, CPt3d ptEnd)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_ptBegin = ptBegin;
	m_ptEnd = ptEnd;
	m_ptMid[X] = (m_ptBegin[X]+m_ptEnd[X])/2;
	m_ptMid[Y] = (m_ptBegin[Y]+m_ptEnd[Y])/2;
	m_ptRight = m_ptLeft = m_ptMid;
}

void ArxRleNetPlanWork::setLabel(ArxRleString labelBegin, ArxRleString labelEnd, ArxRleString labelUp,ArxRleString labelDown)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_labelBegin = labelBegin.a_str();
	m_labelEnd = labelEnd.a_str();
	m_labelUp = labelUp.a_str();
	m_labelDown = labelDown.a_str();
	if(!m_labelDown.isEmpty())
		m_setLabelDown = true;
}

void ArxRleNetPlanWork::setNode(ArxRleString labelBegin, ArxRleString labelEnd)
{
	assertWriteEnabled ();
	m_autoMove = false;
	m_labelBegin = labelBegin.a_str();
	m_labelEnd = labelEnd.a_str();
}

AcDbObjectId ArxRleNetPlanWork::getWorkStyleId() const
{
	assertReadEnabled();
	return m_workStyleId;
}

void ArxRleNetPlanWork::setWorkStyleId(const AcDbObjectId& styleId)
{
	if(styleId != AcDbObjectId::kNull && styleId != m_workStyleId)
	{
		assertWriteEnabled();
		m_autoMove = false;
		m_workStyleId = styleId;
		ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
		Acad::ErrorStatus es = acdbOpenObject(style, m_workStyleId, AcDb::kForRead);
		if(es == Acad::eOk)
		{
			m_workStyleName = style->name().a_str();
			setColorIndex(style->colorIndex());
			setLayer(style->layer());
			setLinetype(style->lineType());
			setLinetypeScale(style->lineScale());
			m_drawNode = style->drawLabelBegin()+style->drawLabelEnd();
			style->close();
		}
		else
			delete style;

	}
}

AcDbObjectId ArxRleNetPlanWork::getBindWorkRefId() const
{
	assertReadEnabled();
	return m_bindWorkRefId;
}

void ArxRleNetPlanWork::setBindWorkRefId(const AcDbObjectId& refId)
{
	if(refId != AcDbObjectId::kNull && refId != m_bindWorkRefId)
	{
		assertWriteEnabled();
		m_bindWork = true;
		m_bindWorkRefId = refId;

		ArxRleNetPlanWork* work = new ArxRleNetPlanWork;
		Acad::ErrorStatus es = acdbOpenObject(work, m_bindWorkRefId, AcDb::kForRead);
		if(es == Acad::eOk)
		{
			m_bindWorkRefName = work->getLabelUp().a_str();
			work->close();
		}
		else
			delete work;
	}
}

//  Dwg Filing interface
// 导出变量
Acad::ErrorStatus ArxRleNetPlanWork::dwgOutFields (AcDbDwgFiler *pFiler) const
{
	assertReadEnabled ();
	//----- Save parent class information first.
	Acad::ErrorStatus es =ArxRleDbEntity::dwgOutFields (pFiler);
	if (es != Acad::eOk)
		return (es);

	//----- Object version number needs to be saved first
	if ((es =pFiler->writeInt16 (ArxRleNetPlanWork::m_version)) != Acad::eOk)
		return (es);

	if (pFiler->filerType()==AcDb::kWblockCloneFiler)
		pFiler->writeHardPointerId((AcDbHardPointerId)ownerId());

	//----- Output params
	pFiler->writeUInt32(m_workCode);
	pFiler->writePoint3d(m_ptBegin);
	pFiler->writePoint3d(m_ptLeft);
	pFiler->writePoint3d(m_ptMid);
	pFiler->writePoint3d(m_ptRight);
	pFiler->writePoint3d(m_ptEnd);
	pFiler->writeString(m_labelBegin);
	pFiler->writeString(m_labelEnd);
	pFiler->writeString(m_labelUp);
	pFiler->writeString(m_labelDown);
	pFiler->writeString(m_workStyleName);
	pFiler->writeString(m_workDes);
	pFiler->writeString(m_bindWorkRefName);
	pFiler->writeDouble(m_resMens);
	pFiler->writeDouble(m_resTools);
	pFiler->writeDouble(m_resMoney);
	pFiler->writeItem(m_workStyleId);
	pFiler->writeItem(m_bindWorkRefId);

	return pFiler->filerStatus();
}

Acad::ErrorStatus ArxRleNetPlanWork::dxfOutFields (AcDbDxfFiler *pFiler) const
{
	assertReadEnabled ();
	//----- Save parent class information first.
	Acad::ErrorStatus es =ArxRleDbEntity::dxfOutFields (pFiler);
	if (es != Acad::eOk)
		return (es);

	pFiler->writeItem(AcDb::kDxfSubclass, this->desc()->name());

	//----- Output params
	pFiler->writeInt32(kDxfWorkCode, m_workCode);
	pFiler->writePoint3d(kDxfPtBegin, m_ptBegin);
	pFiler->writePoint3d(kDxfPtLeft, m_ptLeft);
	pFiler->writePoint3d(kDxfPtMid, m_ptMid);
	pFiler->writePoint3d(kDxfPtRight, m_ptRight);
	pFiler->writePoint3d(kDxfPtEnd, m_ptEnd);
	pFiler->writeString(kDxfTxtBegin, m_labelBegin);
	pFiler->writeString(kDxfTxtEnd, m_labelEnd);
	pFiler->writeString(kDxfTxtUp, m_labelUp);
	pFiler->writeString(kDxfTxtDown, m_labelDown);
	pFiler->writeString(kDxfWorkStyle, m_workStyleName);
	pFiler->writeString(kDxfWorkDes, m_workDes);
	pFiler->writeString(kDxfBindWorkRef, m_bindWorkRefName);
	pFiler->writeDouble(kDxfResMens, m_resMens);
	pFiler->writeDouble(kDxfResTools, m_resTools);
	pFiler->writeDouble(kDxfResMoney, m_resMoney);
	pFiler->writeItem(kDxfWorkStyleId, m_workStyleId);
	pFiler->writeItem(kDxfBindWorkRefId, m_bindWorkRefId);

	return pFiler->filerStatus();
}

// 导入变量
Acad::ErrorStatus ArxRleNetPlanWork::dwgInFields (AcDbDwgFiler *pFiler)
{
	assertWriteEnabled ();
	//----- Read parent class information first.
	Acad::ErrorStatus es =ArxRleDbEntity::dwgInFields (pFiler);
	if (es != Acad::eOk)
		return (es);

	//----- Object version number nee;ds to be read first
	Adesk::Int16 version = 0;
	if ((es =pFiler->readInt16 (&version)) != Acad::eOk)
		return (es);

	if (version > ArxRleNetPlanWork::m_version)
		return (Acad::eMakeMeProxy);

	if(pFiler->filerType() == AcDb::kWblockCloneFiler)
	{
		AcDbHardPointerId Id;
		pFiler->readHardPointerId(&Id);
	}

	pFiler->readUInt32(&m_workCode);
	pFiler->readPoint3d(&m_ptBegin);
	pFiler->readPoint3d(&m_ptLeft);
	pFiler->readPoint3d(&m_ptMid);
	pFiler->readPoint3d(&m_ptRight);
	pFiler->readPoint3d(&m_ptEnd);
	pFiler->readString(m_labelBegin);
	pFiler->readString(m_labelEnd);
	pFiler->readString(m_labelUp);
	pFiler->readString(m_labelDown);
	pFiler->readString(m_workStyleName);
	pFiler->readString(m_workDes);
	pFiler->readString(m_bindWorkRefName);
	pFiler->readDouble(&m_resMens);
	pFiler->readDouble(&m_resTools);
	pFiler->readDouble(&m_resMoney);
	pFiler->readItem(&m_workStyleId);
	pFiler->readItem(&m_bindWorkRefId);

	return (pFiler->filerStatus ());
}

Acad::ErrorStatus ArxRleNetPlanWork::dxfInFields (AcDbDxfFiler *pFiler)
{
	assertWriteEnabled ();
	//----- Read parent class information first.
	Acad::ErrorStatus es =ArxRleDbEntity::dxfInFields (pFiler);
	if ((es != Acad::eOk) || 
		(pFiler->atSubclassData(this->desc()->name()) != Adesk::kTrue))
		return (pFiler->filerStatus ());

	resbuf rb;

	while ((es == Acad::eOk) && ((es = pFiler->readResBuf(&rb)) == Acad::eOk)) {
		if(rb.restype == kDxfWorkCode)
			setWorkCode(rb.resval.rlong);
		else if(rb.restype == kDxfPtBegin) {
			CPt3d tmpPt(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
			setPointBegin(tmpPt);
		}
		else if(rb.restype == kDxfPtLeft) {
			CPt3d tmpPt(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
			setPointLeft(tmpPt);
		}
		else if(rb.restype == kDxfPtMid) {
			CPt3d tmpPt(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
			setPointMid(tmpPt);
		}
		else if(rb.restype == kDxfPtRight) {
			CPt3d tmpPt(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
			setPointRight(tmpPt);
		}
		else if(rb.restype == kDxfPtEnd) {
			CPt3d tmpPt(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
			setPointEnd(tmpPt);
		}
		else if(rb.restype == kDxfTxtBegin)
			setLabelUp(rb.resval.rstring); 
		else if(rb.restype == kDxfTxtEnd)
			setLabelDown(rb.resval.rstring); 
		else if(rb.restype == kDxfTxtUp)
			setLabelUp(rb.resval.rstring); 
		else if(rb.restype == kDxfTxtDown)
			setLabelDown(rb.resval.rstring); 
		else if(rb.restype == kDxfWorkStyle)
			setWorkStyle(rb.resval.rstring); 
		else if(rb.restype == kDxfWorkDes)
			setWorkDes(rb.resval.rstring); 
		else if(rb.restype == kDxfBindWorkRef)
			setBindWorkRef(rb.resval.rstring); 
		else if(rb.restype == kDxfResMens)
			setResMens(rb.resval.rreal);
		else if(rb.restype == kDxfResTools)
			setResTools(rb.resval.rreal);
		else if(rb.restype == kDxfResMoney)
			setResMoney(rb.resval.rreal);
		else if(rb.restype == kDxfWorkStyleId) {
			AcDbObjectId id;
			id.setFromOldId(rb.resval.mnLongPtr);
			setWorkStyleId(id);
		}
		else if(rb.restype == kDxfBindWorkRefId) {
			AcDbObjectId id;
			id.setFromOldId(rb.resval.mnLongPtr);
			setBindWorkRefId(id);
		}
		else {
			pFiler->pushBackItem();
			es = Acad::eEndOfFile;
		}
	}

	if(es != Acad::eEndOfFile)
		return Acad::eInvalidResBuf;

	return (pFiler->filerStatus ());
}

// 保存图形-R12/代理图形
void ArxRleNetPlanWork::saveAs(AcGiWorldDraw* pWd, AcDb::SaveType st)
{
	assertReadEnabled ();

	if(m_txtBegin != NULL) 
		m_txtBegin->saveAs (pWd, st);
	if(m_txtEnd != NULL) 
		m_txtEnd->saveAs (pWd, st);
	for(int i=0; i<ACDBTEXT_COUNT; i++)
	{
		if(m_vecTxtUp[i] != NULL) 
			m_vecTxtUp[i]->saveAs (pWd, st);
	}
	if(m_txtDown != NULL) 
		m_txtDown->saveAs (pWd, st);
	if(m_circleBegin != NULL) 
		m_circleBegin->saveAs (pWd, st);
	if(m_circleEnd != NULL) 
		m_circleEnd->saveAs (pWd, st);
	if(m_polyline != NULL) 
		m_polyline->saveAs (pWd, st);

	ArxRleDbEntity::saveAs (pWd, st);
}

// AcGiDrawable interface
// 模型空间绘制实体
Adesk::Boolean ArxRleNetPlanWork::subWorldDraw (AcGiWorldDraw *pWd)
{
	//AcGiWorldDraw类提供产生几何体对而不随视口改变的功能。
	assertReadEnabled ();

	double dx = m_ptEnd[X]-m_ptBegin[X];
	double dy = m_ptEnd[Y]-m_ptBegin[Y];

	m_workStyleId = ArxRleNetPlanWorkStyle::getWorkStyle(m_workStyleName);
	ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
	Acad::ErrorStatus es = acdbOpenObject(style, m_workStyleId, AcDb::kForRead);
	if(es != Acad::eOk) {
		delete style;
		return Adesk::kFalse;
	}

	m_drawNode = style->drawLabelBegin()+style->drawLabelEnd();

	if(m_setLabelDown)
	{
		dx = _tstof(m_labelDown)*style->lineGap();
		m_ptEnd[X] = m_ptBegin[X] + dx;
		m_setLabelDown = false;
	}

	if(m_autoMove)
	{
		m_moveLeft   =  true;
		m_moveMid    =  true;
		m_moveRight  =  true;
	}

	double zw = CPt3d::GetAngle(CPt3d(m_ptBegin[X],0,0),CPt3d(m_ptEnd[X],0,0));
	if(dx > 0.001 && dy > 0.001)
	{
		if(m_moveLeft) m_ptLeft = CPt3d(m_ptBegin).GetLineEnd(dy/2,zw+PI/2);
		if(m_moveRight) m_ptRight = CPt3d(m_ptEnd).GetLineEnd(dy/2,zw-PI/2);
	}
	else if(dx > 0.001 && dy < -0.001)
	{
		if(m_moveLeft) m_ptLeft = CPt3d(m_ptBegin).GetLineEnd(dy/2,zw+PI/2);
		if(m_moveRight) m_ptRight = CPt3d(m_ptEnd).GetLineEnd(dy/2,zw-PI/2);
	}
	else if(dx < -0.001 && dy > 0.001)
	{
		if(m_moveLeft) m_ptLeft = CPt3d(m_ptBegin).GetLineEnd(dy/2,zw-PI/2);
		if(m_moveRight) m_ptRight = CPt3d(m_ptEnd).GetLineEnd(dy/2,zw+PI/2);
	}
	else if(dx < -0.001 && dy < -0.001)
	{
		if(m_moveLeft) m_ptLeft = CPt3d(m_ptBegin).GetLineEnd(dy/2,zw-PI/2);
		if(m_moveRight) m_ptRight = CPt3d(m_ptEnd).GetLineEnd(dy/2,zw+PI/2);
	}
	else
	{
		if(m_moveLeft)
		{
			m_ptLeft[X] = (m_ptBegin[X]+m_ptEnd[X])/2;
			m_ptLeft[Y] = (m_ptBegin[Y]+m_ptEnd[Y])/2;
		}

		if(m_moveRight) 
		{
			m_ptRight[X] = (m_ptBegin[X]+m_ptEnd[X])/2;
			m_ptRight[Y] = (m_ptBegin[Y]+m_ptEnd[Y])/2;
		}
	}

	if(m_moveMid)
	{
		m_ptMid[X] = (m_ptLeft[X]+m_ptRight[X])/2;
		m_ptMid[Y] = (m_ptLeft[Y]+m_ptRight[Y])/2;
	}

	m_length = abs(dx);

	drawLabel(pWd, style);
	drawCircle(pWd, style);
	drawPolyline(pWd, style);
	style->close();

	return Adesk::kTrue;
	/*worldDraw()函数用于绘制实体图形中表示那些与任何特定模型空间视图或图纸空间视口内容独立无关的部分。
	viewportDraw()函数则用来绘制依赖视图的实体图形。
	如果实体的图形中存在着依赖视图的部分，
	则worldDraw()函数必须返回kFalse且开发者必须执行viewportDraw()函数。
	然后用viewportDraw()函数绘制实体图形中哪些依赖于视图的部分。
	如果实体中不存在依赖于视图的图形，则worldDraw()函数必须返回kTrue，
	开发者也不必自定义实体中执行viewportDraw()函数*/
}

// 图纸空间绘制实体
void ArxRleNetPlanWork::subViewportDraw(AcGiViewportDraw* pVd)
{
	assertReadEnabled ();

	double dx = m_ptEnd[X]-m_ptBegin[X];
	double dy = m_ptEnd[Y]-m_ptBegin[Y];

	m_workStyleId = ArxRleNetPlanWorkStyle::getWorkStyle(m_workStyleName);
	ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
	Acad::ErrorStatus es = acdbOpenObject(style, m_workStyleId, AcDb::kForRead);
	if(es != Acad::eOk) {
		delete style;
		return;
	}

	m_drawNode = style->drawLabelBegin()+style->drawLabelEnd();

	if(m_setLabelDown)
	{
		dx = _tstof(m_labelDown)*style->lineGap();
		m_ptEnd[X] = m_ptBegin[X] + dx;
		m_setLabelDown = false;
	}

	if(m_autoMove)
	{
		m_moveLeft   =  true;
		m_moveMid    =  true;
		m_moveRight  =  true;
	}

	double zw = CPt3d::GetAngle(CPt3d(m_ptBegin[X],0,0),CPt3d(m_ptEnd[X],0,0));
	if(dx > 0.001 && dy > 0.001)
	{
		if(m_moveLeft) m_ptLeft = CPt3d(m_ptBegin).GetLineEnd(dy/2,zw+PI/2);
		if(m_moveRight) m_ptRight = CPt3d(m_ptEnd).GetLineEnd(dy/2,zw-PI/2);
	}
	else if(dx > 0.001 && dy < -0.001)
	{
		if(m_moveLeft) m_ptLeft = CPt3d(m_ptBegin).GetLineEnd(dy/2,zw+PI/2);
		if(m_moveRight) m_ptRight = CPt3d(m_ptEnd).GetLineEnd(dy/2,zw-PI/2);
	}
	else if(dx < -0.001 && dy > 0.001)
	{
		if(m_moveLeft) m_ptLeft = CPt3d(m_ptBegin).GetLineEnd(dy/2,zw-PI/2);
		if(m_moveRight) m_ptRight = CPt3d(m_ptEnd).GetLineEnd(dy/2,zw+PI/2);
	}
	else if(dx < -0.001 && dy < -0.001)
	{
		if(m_moveLeft) m_ptLeft = CPt3d(m_ptBegin).GetLineEnd(dy/2,zw-PI/2);
		if(m_moveRight) m_ptRight = CPt3d(m_ptEnd).GetLineEnd(dy/2,zw+PI/2);
	}
	else
	{
		if(m_moveLeft)
		{
			m_ptLeft[X] = (m_ptBegin[X]+m_ptEnd[X])/2;
			m_ptLeft[Y] = (m_ptBegin[Y]+m_ptEnd[Y])/2;
		}

		if(m_moveRight) 
		{
			m_ptRight[X] = (m_ptBegin[X]+m_ptEnd[X])/2;
			m_ptRight[Y] = (m_ptBegin[Y]+m_ptEnd[Y])/2;
		}
	}

	if(m_moveMid)
	{
		m_ptMid[X] = (m_ptLeft[X]+m_ptRight[X])/2;
		m_ptMid[Y] = (m_ptLeft[Y]+m_ptRight[Y])/2;
	}

	m_length = abs(dx);

	drawLabel(pVd, style);
	drawCircle(pVd, style);
	drawPolyline(pVd, style);
	style->close();

	ArxRleDbEntity::subViewportDraw (pVd);
}

// 设置属性
Adesk::UInt32 ArxRleNetPlanWork::subSetAttributes (AcGiDrawableTraits *pTraits)
{
	assertReadEnabled ();

	int aci = this->colorIndex();
	pTraits->setColor(aci);
	AcDbObjectId id = this->layerId();
	pTraits->setLayer(id);
	id = this->linetypeId();
	pTraits->setLineType(id);
	double lts = this->linetypeScale();
	pTraits->setLineTypeScale(lts);
	AcDb::LineWeight lw = this->lineWeight();
	pTraits->setLineWeight(lw);

	return (ArxRleDbEntity::subSetAttributes (pTraits));
}

//获得一个实体的范围（一个极大点  一个极小点）
Acad::ErrorStatus ArxRleNetPlanWork::subGetGeomExtents(AcDbExtents& extents) const
{
	assertReadEnabled ();
	//extents.addPoint( m_ptBegin + sqrt(2)*200.0*AcGeVector3d(1,1,0)) ;
	//extents.addPoint( m_ptEnd - sqrt(2)*200.0*AcGeVector3d(1,1,0)) ;
	return (ArxRleDbEntity::subGetGeomExtents (extents));
}

// 获得捕捉点，这里添加一个中心点         
// 这里仅用第一个变量,虽捕捉到，但是有点问题，鼠标移开后就没有了
// This OSNAP solution handles only simple OSNAP types like CENTER, MIDPOINT and
// ENDPOINT. Complex OSNAP modes like INTERSECTION require other methods implementations and
// 参数2在vc90以及上版本为Adesk::GsMarke类型；在vc80及以下版本为int类型；填写错的话会导致捕捉点无效
Acad::ErrorStatus ArxRleNetPlanWork::subGetOsnapPoints (AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark,
	const AcGePoint3d &pickPoint, const AcGePoint3d &lastPoint, const AcGeMatrix3d &viewXform,
	AcGePoint3dArray &snapPoints, AcDbIntArray &geomIds) const
{
	assertReadEnabled ();

	switch (osnapMode)
	{
	case AcDb::kOsModeEnd:
		snapPoints.append(m_ptBegin);
		snapPoints.append(m_ptLeft);
		snapPoints.append(m_ptRight);
		snapPoints.append(m_ptEnd);
		break;
	case AcDb::kOsModeMid:
		snapPoints.append(m_ptMid);
		break;
	case AcDb::kOsModeCen:
		snapPoints.append(m_ptMid);
		break;
	}

	return Acad::eOk;
}

// 获得夹点
Acad::ErrorStatus ArxRleNetPlanWork::subGetGripPoints (AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const
{
	assertReadEnabled ();
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new getGripPoints() method below (which is the default implementation)
	gripPoints.append(m_ptBegin);
	gripPoints.append(m_ptLeft);
	gripPoints.append(m_ptMid);
	gripPoints.append(m_ptRight);
	gripPoints.append(m_ptEnd);

	return Acad::eOk;
}

// 移动夹点
Acad::ErrorStatus ArxRleNetPlanWork::subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset)
{
	assertWriteEnabled ();
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new moveGripPointsAt() method below (which is the default implementation)
	if (indices.length() == 0 || offset.isZeroLength())
		return Acad::eOk;

	int i = indices[0];
	m_autoMove = false;

	switch (i)
	{
	case 0://左侧端点
		m_ptBegin += offset;
		m_ptEnd += offset;
		m_moveLeft = true;
		m_moveMid = true;
		m_moveRight = true;
		if(m_drawNode == 0) m_moveLeft = m_moveMid = m_moveRight = false;
		break;
	case 1://左侧边点
		m_ptLeft += offset;
		m_moveLeft = false;
		m_moveMid = true;
		m_moveRight = false;
		if(m_drawNode == 0) m_moveMid = false;
		if(m_drawNode > 0) m_ptRight[Y] = m_ptLeft[Y];
		break;
	case 2://中心点
		m_ptMid += offset;
		m_moveLeft = false;
		m_moveMid = false;
		m_moveRight = false;
		break;
	case 3://右侧边点
		m_ptRight += offset;
		m_moveLeft = false;
		m_moveMid = true;
		m_moveRight = false;
		if(m_drawNode == 0) m_moveMid = false;
		if(m_drawNode > 0) m_ptLeft[Y] = m_ptRight[Y];
		break;
	case 4://右侧端点
		m_ptEnd += offset;
		m_moveLeft = true;
		m_moveMid = true;
		m_moveRight = true;
		break;
	}

	return Acad::eOk;
}

// 实体的移动、旋转、缩放
Acad::ErrorStatus ArxRleNetPlanWork::subTransformBy(const AcGeMatrix3d & xform)
{
	assertWriteEnabled ();

 	m_ptBegin.transformBy(xform);
	m_ptLeft.transformBy(xform);
 	m_ptMid.transformBy(xform);
	m_ptRight.transformBy(xform);
 	m_ptEnd.transformBy(xform);
	return ArxRleDbEntity::subTransformBy (xform);
}

Acad::ErrorStatus ArxRleNetPlanWork::subGetTransformedCopy(const AcGeMatrix3d& xform, AcDbEntity*& ent) const
{
	assertReadEnabled ();

	return ArxRleDbEntity::subGetTransformedCopy (xform, ent);
}

void ArxRleNetPlanWork::getCloneReferences(AcDb::DeepCloneType type, AcDbObjectIdArray& refIds, AcDbIntArray& refTypes) const
{
	// these types should have been filtered out.  NOTE that kDcObjects
	// is usually ambiguous and has been mapped to kDcBlock or kDcCopy.
	ASSERT((type != AcDb::kDcExplode) &&
		(type != AcDb::kDcInsert) &&
		(type != AcDb::kDcInsertCopy) &&
		(type != AcDb::kDcSymTableMerge) &&
		(type != AcDb::kDcXrefBind) &&
		(type != AcDb::kDcXrefInsert) &&
		(type != AcDb::kDcObjects));

	if(type == AcDb::kDcCopy) {
		refIds.append(m_bindWorkRefId);
		refTypes.append(kClone);	// you could set this to kNoClone and both would point to the same one.
	}
	else if(type == AcDb::kDcBlock) {
		refIds.append(m_bindWorkRefId);
		refTypes.append(kClone);

		// LongTransactions (RefEdit) will not allow our object to be checked
		// out from a block definition unless its accompanying style def is
		// also in the check out set (which it won't be by default).  So, we
		// have to tell ::deepClone() to fake like it cloned the style definition
		// so it will pass LongTransaction's checkOut validation.
		refIds.append(m_workStyleId);
		refTypes.append(kFakeClone);
	}
	else if(type == AcDb::kDcWblock) {
		refIds.append(m_bindWorkRefId);
		refTypes.append(kClone);
	}
	else if(type == AcDb::kDcWblkObjects) {
		refIds.append(m_bindWorkRefId);
		refTypes.append(kClone);
	}
	else {
		ASSERT(0);	// which context did we not account for?
	}
}

Acad::ErrorStatus ArxRleNetPlanWork::subExplode(AcDbVoidPtrArray& entitySet) const
{
	assertReadEnabled ();

	if(m_txtBegin != NULL) entitySet.append (m_txtBegin);
	if(m_txtEnd != NULL) entitySet.append (m_txtEnd);
	if(m_txtDown != NULL) entitySet.append (m_txtDown);
	if(m_circleBegin != NULL) entitySet.append (m_circleBegin);
	if(m_circleEnd != NULL) entitySet.append (m_circleEnd);
	if(m_polyline != NULL) entitySet.append (m_polyline);
	for(int i=0; i<m_vecTxtUp.size();i++)
		if(m_vecTxtUp[i] != NULL) entitySet.append (m_vecTxtUp[i]);

	return Acad::eOk /*ArxRleDbEntity::subExplode (entitySet)*/;
}

void ArxRleNetPlanWork::drawLabel(AcGiWorldDraw *pWd, ArxRleNetPlanWorkStyle* style)
{
	double       sl,sn,lg;
	AcDbObjectId tsId;
	bool         dlb,dle,dlu,dld;

	if(style)
	{
		sl = style->sizeLabel();
		sn = style->sizeNode();
		lg = style->lineGap();
		dlb = style->drawLabelBegin();
		dle = style->drawLabelEnd();
		dlu = style->drawLabelUp();
		dld = style->drawLabelDown();
		tsId = AddTextStyle(style->textStyle());
	}

	if(m_txtBegin == NULL) m_txtBegin = new AcDbText;
	AcDbTextStyleTableRecord* ts = (AcDbTextStyleTableRecord*)GetRecordPtr(tsId);
	m_txtBegin->setTextStyle(tsId);
	if(ts != NULL) m_txtBegin->setWidthFactor(ts->xScale());
	m_txtBegin->setTextString(m_labelBegin);
	m_txtBegin->setHeight(sn);
	m_txtBegin->setRotation(0);
	m_txtBegin->setHorizontalMode(AcDb::kTextCenter);
	m_txtBegin->setVerticalMode(AcDb::kTextVertMid);
	m_txtBegin->setPosition(m_ptBegin);
	m_txtBegin->setAlignmentPoint(m_ptBegin);
	m_txtBegin->adjustAlignment(ARXRLEDB);
	
	if(m_txtEnd == NULL) m_txtEnd = new AcDbText;
	m_txtEnd->setTextStyle(tsId);
	if(ts != NULL) m_txtEnd->setWidthFactor(ts->xScale());
	m_txtEnd->setTextString(m_labelEnd);
	m_txtEnd->setHeight(sn);
	m_txtEnd->setRotation(0);
	m_txtEnd->setHorizontalMode(AcDb::kTextCenter);
	m_txtEnd->setVerticalMode(AcDb::kTextVertMid);
	m_txtEnd->setPosition(m_ptEnd);
	m_txtEnd->setAlignmentPoint(m_ptEnd);
	m_txtEnd->adjustAlignment(ARXRLEDB);

	ArxRleString label(m_labelUp);
	vector<ArxRleString> vecLabelUp;
	AcString labelUp = m_labelUp;
	int cnt = label.ParseSubStrByDelimiter(vecLabelUp);
	for(int i=0; i<ACDBTEXT_COUNT; i++)
	{
		if(i > cnt-1)
			labelUp = "";
		else
			labelUp = vecLabelUp[cnt-i-1].a_str();
		if(m_vecTxtUp[i] == NULL) m_vecTxtUp[i] = new AcDbText;
		m_vecTxtUp[i]->setTextStyle(tsId);
		if(ts != NULL) m_vecTxtUp[i]->setWidthFactor(ts->xScale());
		m_vecTxtUp[i]->setTextString(labelUp);
		m_vecTxtUp[i]->setHeight(sl);
		m_vecTxtUp[i]->setRotation(0);
		m_vecTxtUp[i]->setHorizontalMode(AcDb::kTextCenter);
		m_vecTxtUp[i]->setVerticalMode(AcDb::kTextBase);
		m_vecTxtUp[i]->setPosition(CPt3d(m_ptMid[X],m_ptMid[Y]+(sl+0.1)*i*+0.5));
		m_vecTxtUp[i]->setAlignmentPoint(CPt3d(m_ptMid[X],m_ptMid[Y]+(sl+0.1)*i+0.5));
		m_vecTxtUp[i]->adjustAlignment(ARXRLEDB);
	}

	if(lg > 0)
		m_labelDown.format(L"%.0f天",m_length/lg);
	if(m_labelUp.isEmpty()) m_labelDown.setEmpty();
	if(m_txtDown == NULL) m_txtDown = new AcDbText;
	m_txtDown->setTextStyle(tsId);
	if(ts != NULL) m_txtDown->setWidthFactor(ts->xScale());
	m_txtDown->setTextString(m_labelDown);
	m_txtDown->setHeight(sl);
	m_txtDown->setRotation(0);
	m_txtDown->setHorizontalMode(AcDb::kTextCenter);
	m_txtDown->setVerticalMode(AcDb::kTextTop);
	m_txtDown->setPosition(CPt3d(m_ptMid[X],m_ptMid[Y]-0.5));
	m_txtDown->setAlignmentPoint(CPt3d(m_ptMid[X],m_ptMid[Y]-0.5));
	m_txtDown->adjustAlignment(ARXRLEDB);
	if(ts != NULL) ts->close();

	if(dlb)
		m_txtBegin->worldDraw(pWd);
	if(dle)
		m_txtEnd->worldDraw(pWd);

	for(int i=0; i<ACDBTEXT_COUNT; i++)
	{
		if(dlu)
			m_vecTxtUp[i]->worldDraw(pWd);
	}

	if(dld)
		m_txtDown->worldDraw(pWd);
}

void ArxRleNetPlanWork::drawLabel(AcGiViewportDraw *pVd, ArxRleNetPlanWorkStyle* style)
{
	double       sl,sn,lg;
	AcDbObjectId tsId;
	bool         dlb,dle,dlu,dld;

	if(style)
	{
		sl = style->sizeLabel();
		sn = style->sizeNode();
		lg = style->lineGap();
		dlb = style->drawLabelBegin();
		dle = style->drawLabelEnd();
		dlu = style->drawLabelUp();
		dld = style->drawLabelDown();
		tsId = AddTextStyle(style->textStyle());
	}

	if(m_txtBegin == NULL) m_txtBegin = new AcDbText;
	AcDbTextStyleTableRecord* ts = (AcDbTextStyleTableRecord*)GetRecordPtr(tsId);
	m_txtBegin->setTextStyle(tsId);
	if(ts != NULL) m_txtBegin->setWidthFactor(ts->xScale());
	m_txtBegin->setTextString(m_labelBegin);
	m_txtBegin->setHeight(sn);
	m_txtBegin->setRotation(0);
	m_txtBegin->setHorizontalMode(AcDb::kTextCenter);
	m_txtBegin->setVerticalMode(AcDb::kTextVertMid);
	m_txtBegin->setPosition(m_ptBegin);
	m_txtBegin->setAlignmentPoint(m_ptBegin);
	m_txtBegin->adjustAlignment(ARXRLEDB);

	if(m_txtEnd == NULL) m_txtEnd = new AcDbText;
	m_txtEnd->setTextStyle(tsId);
	if(ts != NULL) m_txtEnd->setWidthFactor(ts->xScale());
	m_txtEnd->setTextString(m_labelEnd);
	m_txtEnd->setHeight(sn);
	m_txtEnd->setRotation(0);
	m_txtEnd->setHorizontalMode(AcDb::kTextCenter);
	m_txtEnd->setVerticalMode(AcDb::kTextVertMid);
	m_txtEnd->setPosition(m_ptEnd);
	m_txtEnd->setAlignmentPoint(m_ptEnd);
	m_txtEnd->adjustAlignment(ARXRLEDB);

	ArxRleString label(m_labelUp);
	vector<ArxRleString> vecLabelUp;
	AcString labelUp = m_labelUp;
	int cnt = label.ParseSubStrByDelimiter(vecLabelUp);
	for(int i=0; i<ACDBTEXT_COUNT; i++)
	{
		if(i > cnt-1)
			labelUp = "";
		else
			labelUp = vecLabelUp[cnt-i-1].a_str();
		if(m_vecTxtUp[i] == NULL) m_vecTxtUp[i] = new AcDbText;
		m_vecTxtUp[i]->setTextStyle(tsId);
		if(ts != NULL) m_vecTxtUp[i]->setWidthFactor(ts->xScale());
		m_vecTxtUp[i]->setTextString(labelUp);
		m_vecTxtUp[i]->setHeight(sl);
		m_vecTxtUp[i]->setRotation(0);
		m_vecTxtUp[i]->setHorizontalMode(AcDb::kTextCenter);
		m_vecTxtUp[i]->setVerticalMode(AcDb::kTextBase);
		m_vecTxtUp[i]->setPosition(CPt3d(m_ptMid[X],m_ptMid[Y]+(sl+0.1)*i*+0.5));
		m_vecTxtUp[i]->setAlignmentPoint(CPt3d(m_ptMid[X],m_ptMid[Y]+(sl+0.1)*i+0.5));
		m_vecTxtUp[i]->adjustAlignment(ARXRLEDB);
	}

	if(lg > 0)
		m_labelDown.format(L"%.0f天",m_length/lg);
	if(m_labelUp.isEmpty()) m_labelDown.setEmpty();
	if(m_txtDown == NULL) m_txtDown = new AcDbText;
	m_txtDown->setTextStyle(tsId);
	if(ts != NULL) m_txtDown->setWidthFactor(ts->xScale());
	m_txtDown->setTextString(m_labelDown);
	m_txtDown->setHeight(sl);
	m_txtDown->setRotation(0);
	m_txtDown->setHorizontalMode(AcDb::kTextCenter);
	m_txtDown->setVerticalMode(AcDb::kTextTop);
	m_txtDown->setPosition(CPt3d(m_ptMid[X],m_ptMid[Y]-0.5));
	m_txtDown->setAlignmentPoint(CPt3d(m_ptMid[X],m_ptMid[Y]-0.5));
	m_txtDown->adjustAlignment(ARXRLEDB);
	if(ts != NULL) ts->close();

	if(dlb)
		m_txtBegin->viewportDraw(pVd);
	if(dle)
		m_txtEnd->viewportDraw(pVd);

	for(int i=0; i<ACDBTEXT_COUNT; i++)
	{
		if(dlu)
			m_vecTxtUp[i]->viewportDraw(pVd);
	}

	if(dld)
		m_txtDown->viewportDraw(pVd);
}

void ArxRleNetPlanWork::drawCircle(AcGiWorldDraw *pWd, ArxRleNetPlanWorkStyle* style)
{
	double   r1,r2;
	bool     dlb,dle;

	if(style)
	{
		r1 = style->radiusBegin();
		r2 = style->radiusEnd();
		dlb = style->drawLabelBegin();
		dle = style->drawLabelEnd();
	}

	if(m_circleBegin == NULL) m_circleBegin = new AcDbCircle;
	m_circleBegin->setCenter(m_ptBegin);
	m_circleBegin->setRadius(r1);
	
	if(m_circleEnd == NULL) m_circleEnd = new AcDbCircle;
	m_circleEnd->setCenter(m_ptEnd);
	m_circleEnd->setRadius(r2);



	if(dlb)
		m_circleBegin->worldDraw(pWd);
	if(dle)
		m_circleEnd->worldDraw(pWd);
}

void ArxRleNetPlanWork::drawCircle(AcGiViewportDraw *pVd, ArxRleNetPlanWorkStyle* style)
{
	double   r1,r2;
	bool     dlb,dle;

	if(style)
	{
		r1 = style->radiusBegin();
		r2 = style->radiusEnd();
		dlb = style->drawLabelBegin();
		dle = style->drawLabelEnd();
	}

	if(m_circleBegin == NULL) m_circleBegin = new AcDbCircle;
	m_circleBegin->setCenter(m_ptBegin);
	m_circleBegin->setRadius(r1);

	if(m_circleEnd == NULL) m_circleEnd = new AcDbCircle;
	m_circleEnd->setCenter(m_ptEnd);
	m_circleEnd->setRadius(r2);

	if(dlb)
		m_circleBegin->viewportDraw(pVd);
	if(dle)
		m_circleEnd->viewportDraw(pVd);
}

void ArxRleNetPlanWork::drawPolyline(AcGiWorldDraw *pWd, ArxRleNetPlanWorkStyle* style)
{
	double r1,r2,la,sl,sn;

	if(style)
	{
		r1= style->radiusBegin();
		r2= style->radiusEnd();
		la= style->lenArrow();
		sl= style->sizeLabel();
		sn= style->sizeNode();
	}

	if(m_polyline == NULL) m_polyline = new AcDbPolyline();
	if(m_polyline->numVerts() == 0)
	{
		if(m_ptLeft == m_ptRight)
		{
			double zw = CPt3d::GetAngle(m_ptBegin,m_ptEnd);
			m_polyline->addVertexAt(0, CPt3d(m_ptBegin).GetLineEnd(r1,zw));
			m_polyline->addVertexAt(1, CPt3d(m_ptLeft));
			m_polyline->addVertexAt(2, CPt3d(m_ptMid));
			m_polyline->addVertexAt(3, CPt3d(m_ptRight));
			m_polyline->addVertexAt(4, CPt3d(m_ptEnd).GetLineEnd(r2+la,zw+PI));
			m_polyline->addVertexAt(5, CPt3d(m_ptEnd).GetLineEnd(r2,zw+PI));
		}
		else
		{
			double zw = CPt3d::GetAngle(m_ptBegin,m_ptLeft);
			m_polyline->addVertexAt(0, CPt3d(m_ptBegin).GetLineEnd(r1,zw));
			m_polyline->addVertexAt(1, CPt3d(m_ptLeft));
			m_polyline->addVertexAt(2, CPt3d(m_ptMid));
			m_polyline->addVertexAt(3, CPt3d(m_ptRight));
			zw = CPt3d::GetAngle(m_ptEnd,m_ptRight);
			m_polyline->addVertexAt(4, CPt3d(m_ptEnd).GetLineEnd(r2+la,zw));
			m_polyline->addVertexAt(5, CPt3d(m_ptEnd).GetLineEnd(r2,zw));
		}
	}
	else
	{
		if(m_ptLeft == m_ptRight)
		{
			double zw = CPt3d::GetAngle(m_ptBegin,m_ptEnd);
			m_polyline->setPointAt(0, CPt3d(m_ptBegin).GetLineEnd(r1,zw));
			m_polyline->setPointAt(1, CPt3d(m_ptLeft));
			m_polyline->setPointAt(2, CPt3d(m_ptMid));
			m_polyline->setPointAt(3, CPt3d(m_ptRight));
			m_polyline->setPointAt(4, CPt3d(m_ptEnd).GetLineEnd(r2+la,zw+PI));
			m_polyline->setPointAt(5, CPt3d(m_ptEnd).GetLineEnd(r2,zw+PI));
		}
		else
		{
			double zw = CPt3d::GetAngle(m_ptBegin,m_ptLeft);
			m_polyline->setPointAt(0, CPt3d(m_ptBegin).GetLineEnd(r1,zw));
			m_polyline->setPointAt(1, CPt3d(m_ptLeft));
			m_polyline->setPointAt(2, CPt3d(m_ptMid));
			m_polyline->setPointAt(3, CPt3d(m_ptRight));
			zw = CPt3d::GetAngle(m_ptEnd,m_ptRight);
			m_polyline->setPointAt(4, CPt3d(m_ptEnd).GetLineEnd(r2+la,zw));
			m_polyline->setPointAt(5, CPt3d(m_ptEnd).GetLineEnd(r2,zw));
		}
	}
	m_polyline->setWidthsAt(0,la/10,la/10);
	m_polyline->setWidthsAt(1,la/10,la/10);
	m_polyline->setWidthsAt(2,la/10,la/10);
	m_polyline->setWidthsAt(3,la/10,la/10);
	m_polyline->setWidthsAt(4,la/5,0);

	m_polyline->worldDraw(pWd);
}

void ArxRleNetPlanWork::drawPolyline(AcGiViewportDraw *pVd, ArxRleNetPlanWorkStyle* style)
{
	double r1,r2,la,sl,sn;

	if(style)
	{
		r1= style->radiusBegin();
		r2= style->radiusEnd();
		la= style->lenArrow();
		sl= style->sizeLabel();
		sn= style->sizeNode();
	}

	if(m_polyline == NULL) m_polyline = new AcDbPolyline();
	if(m_polyline->numVerts() == 0)
	{
		if(m_ptLeft == m_ptRight)
		{
			double zw = CPt3d::GetAngle(m_ptBegin,m_ptEnd);
			m_polyline->addVertexAt(0, CPt3d(m_ptBegin).GetLineEnd(r1,zw));
			m_polyline->addVertexAt(1, CPt3d(m_ptLeft));
			m_polyline->addVertexAt(2, CPt3d(m_ptMid));
			m_polyline->addVertexAt(3, CPt3d(m_ptRight));
			m_polyline->addVertexAt(4, CPt3d(m_ptEnd).GetLineEnd(r2+la,zw+PI));
			m_polyline->addVertexAt(5, CPt3d(m_ptEnd).GetLineEnd(r2,zw+PI));
		}
		else
		{
			double zw = CPt3d::GetAngle(m_ptBegin,m_ptLeft);
			m_polyline->addVertexAt(0, CPt3d(m_ptBegin).GetLineEnd(r1,zw));
			m_polyline->addVertexAt(1, CPt3d(m_ptLeft));
			m_polyline->addVertexAt(2, CPt3d(m_ptMid));
			m_polyline->addVertexAt(3, CPt3d(m_ptRight));
			zw = CPt3d::GetAngle(m_ptEnd,m_ptRight);
			m_polyline->addVertexAt(4, CPt3d(m_ptEnd).GetLineEnd(r2+la,zw));
			m_polyline->addVertexAt(5, CPt3d(m_ptEnd).GetLineEnd(r2,zw));
		}
	}
	else
	{
		if(m_ptLeft == m_ptRight)
		{
			double zw = CPt3d::GetAngle(m_ptBegin,m_ptEnd);
			m_polyline->setPointAt(0, CPt3d(m_ptBegin).GetLineEnd(r1,zw));
			m_polyline->setPointAt(1, CPt3d(m_ptLeft));
			m_polyline->setPointAt(2, CPt3d(m_ptMid));
			m_polyline->setPointAt(3, CPt3d(m_ptRight));
			m_polyline->setPointAt(4, CPt3d(m_ptEnd).GetLineEnd(r2+la,zw+PI));
			m_polyline->setPointAt(5, CPt3d(m_ptEnd).GetLineEnd(r2,zw+PI));
		}
		else
		{
			double zw = CPt3d::GetAngle(m_ptBegin,m_ptLeft);
			m_polyline->setPointAt(0, CPt3d(m_ptBegin).GetLineEnd(r1,zw));
			m_polyline->setPointAt(1, CPt3d(m_ptLeft));
			m_polyline->setPointAt(2, CPt3d(m_ptMid));
			m_polyline->setPointAt(3, CPt3d(m_ptRight));
			zw = CPt3d::GetAngle(m_ptEnd,m_ptRight);
			m_polyline->setPointAt(4, CPt3d(m_ptEnd).GetLineEnd(r2+la,zw));
			m_polyline->setPointAt(5, CPt3d(m_ptEnd).GetLineEnd(r2,zw));
		}
	}
	m_polyline->setWidthsAt(0,la/10,la/10);
	m_polyline->setWidthsAt(1,la/10,la/10);
	m_polyline->setWidthsAt(2,la/10,la/10);
	m_polyline->setWidthsAt(3,la/10,la/10);
	m_polyline->setWidthsAt(4,la/5,0);

	m_polyline->viewportDraw(pVd);
}

////////////////////////////AcEdJig 拖动////////////////////////////////////////////////////////
ArxRleJigNetPlanWork::ArxRleJigNetPlanWork()
{
}

void ArxRleJigNetPlanWork::setPoint(CPt3d ptBegin, ArxRleString wsName)
{
	m_ptBegin = ptBegin;
	m_workStyleName = wsName;
}

void ArxRleJigNetPlanWork::setLabel(ArxRleString labelBegin, ArxRleString labelEnd, ArxRleString labelUp,ArxRleString labelDown)
{
	m_labelBegin = labelBegin;
	m_labelEnd = labelEnd;
	m_labelUp = labelUp;
	m_labelDown = labelDown;
}

void ArxRleJigNetPlanWork::dragIt()
{
	m_pNetPlanWork = new ArxRleNetPlanWork;
	if(m_pNetPlanWork)
	{
		m_pNetPlanWork->setLabel(m_labelBegin, m_labelEnd, m_labelUp, m_labelDown);
		m_pNetPlanWork->setWorkStyle(m_workStyleName);

		setDispPrompt(L"\nEndPoint: ");
		AcEdJig::DragStatus ds = drag();
		append();
	}
}

// 捕获定点设备并作出分析
AcEdJig::DragStatus ArxRleJigNetPlanWork::sampler()
{
	static AcGePoint3d ptTmp;
	DragStatus ds = acquirePoint(m_ptMove, m_ptBegin);

	if (ptTmp != m_ptMove)
		ptTmp = m_ptMove;
	else if (ds == AcEdJig::kNormal)
		return AcEdJig::kNoChange;

	return ds;
}

//更新数据,并更新类成员变量的值
Adesk::Boolean ArxRleJigNetPlanWork::update()
{
	m_pNetPlanWork->setPoint(m_ptBegin, m_ptMove);
	m_pNetPlanWork->setLabel(m_labelBegin, m_labelEnd, m_labelUp, m_labelDown);

	AcDbObjectId styleId = ArxRleNetPlanWorkStyle::getWorkStyle(m_workStyleName);
	ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
	Acad::ErrorStatus es = acdbOpenObject(style, styleId, AcDb::kForRead);
	if(es != Acad::eOk) {
		delete style;
		return Adesk::kFalse;
	}
	m_pNetPlanWork->setLayer(style->layer());
	m_pNetPlanWork->setColorIndex(style->colorIndex());
	m_pNetPlanWork->setLinetype(style->lineType());
	style->close();

	return Adesk::kTrue;
}

//更新实体
AcDbEntity* ArxRleJigNetPlanWork::entity() const
{
	return m_pNetPlanWork;
}