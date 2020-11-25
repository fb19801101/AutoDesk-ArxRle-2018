//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleBrokenLine.h"
#include "App/ArxRlePaletteAttribute.h"

Adesk::Int16 ArxRleBrokenLine::m_version = 0;
ACRX_DXF_DEFINE_MEMBERS (
	ArxRleBrokenLine, ArxRleDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, ArxRleBrokenLine/*在CAD中该实体类的名称*/,
	ARXRLE_ADESK_BROKENLINE
	|Product Desc:     间断线
	|Company:          中铁十二局集团一公司
	|WEB Address:      http://www.cr201.com
);

ArxRleBrokenLine::ArxRleBrokenLine () : ArxRleDbEntity ()
{
	m_polyline = NULL;
}

ArxRleBrokenLine::~ArxRleBrokenLine ()
{
	if(m_polyline != NULL) delete m_polyline;
}

// 属性设置
void ArxRleBrokenLine::setPointBegin(AcGePoint3d ptBegin)
{
	assertWriteEnabled ();
	m_ptBegin = ptBegin;
	m_ptEnd = ptBegin;
	m_ptMid = AcGePoint3d((m_ptBegin.x+m_ptEnd.x)/2,(m_ptBegin.y+m_ptEnd.y)/2,(m_ptBegin.z+m_ptEnd.z)/2);
}

void ArxRleBrokenLine::setPointEnd(AcGePoint3d ptEnd)
{
	assertWriteEnabled ();
	m_ptEnd = ptEnd;
	m_ptMid = AcGePoint3d((m_ptBegin.x+m_ptEnd.x)/2,(m_ptBegin.y+m_ptEnd.y)/2,(m_ptBegin.z+m_ptEnd.z)/2);
}

void ArxRleBrokenLine::setPoint(AcGePoint3d ptBegin, AcGePoint3d ptEnd)
{
	assertWriteEnabled ();
	m_ptBegin = ptBegin;
	m_ptEnd = ptEnd;
	m_ptMid = AcGePoint3d((m_ptBegin.x+m_ptEnd.x)/2,(m_ptBegin.y+m_ptEnd.y)/2,(m_ptBegin.z+m_ptEnd.z)/2);
}

void ArxRleBrokenLine::setBrokenSize(double fBrokenSize)
{
	assertWriteEnabled ();
	m_fBrokenSize = fBrokenSize;
	m_ptUp = AcGePoint3d(m_ptMid.x-m_fBrokenSize/4,m_ptMid.y+m_fBrokenSize,m_ptMid.z);
	m_ptDown = AcGePoint3d(m_ptMid.x+m_fBrokenSize/4,m_ptMid.y-m_fBrokenSize,m_ptMid.z);
}

void ArxRleBrokenLine::set(AcGePoint3d ptBegin, AcGePoint3d ptEnd, double fBrokenSize)
{
	assertWriteEnabled ();
	m_ptBegin = ptBegin;
	m_ptEnd = ptEnd;
	m_ptMid = AcGePoint3d((m_ptBegin.x+m_ptEnd.x)/2,(m_ptBegin.y+m_ptEnd.y)/2,(m_ptBegin.z+m_ptEnd.z)/2);
	m_fBrokenSize = fBrokenSize;
	m_ptUp = AcGePoint3d(m_ptMid.x-m_fBrokenSize/4,m_ptMid.y+m_fBrokenSize,m_ptMid.z);
	m_ptDown = AcGePoint3d(m_ptMid.x+m_fBrokenSize/4,m_ptMid.y-m_fBrokenSize,m_ptMid.z);
}

//  Dwg Filing interface
// 导出变量
Acad::ErrorStatus ArxRleBrokenLine::dwgOutFields (AcDbDwgFiler *pFiler) const
{
	assertReadEnabled ();
	//----- Save parent class information first.
	Acad::ErrorStatus es =ArxRleDbEntity::dwgOutFields (pFiler);
	if (es != Acad::eOk)
		return (es);

	//----- Object version number needs to be saved first
	if ((es =pFiler->writeItem (ArxRleBrokenLine::m_version)) != Acad::eOk)
		return (es);

	if (pFiler->filerType()==AcDb::kWblockCloneFiler)
		pFiler->writeHardPointerId((AcDbHardPointerId)ownerId());

	//----- Output params
	pFiler->writeItem(m_ptBegin);
	pFiler->writeItem(m_ptMid);
	pFiler->writeItem(m_ptEnd);
	pFiler->writeItem(m_fBrokenSize);
	pFiler->writeItem(m_ptUp);
	pFiler->writeItem(m_ptDown);

	return pFiler->filerStatus();
}

// 导入变量
Acad::ErrorStatus ArxRleBrokenLine::dwgInFields (AcDbDwgFiler *pFiler)
{
	assertWriteEnabled ();
	//----- Read parent class information first.
	Acad::ErrorStatus es =ArxRleDbEntity::dwgInFields (pFiler);
	if (es != Acad::eOk)
		return (es);

	//----- Object version number nee;ds to be read first
	Adesk::Int16 version = 0;
	if ((es =pFiler->readItem (&version)) != Acad::eOk)
		return (es);

	if (version > ArxRleBrokenLine::m_version)
		return (Acad::eMakeMeProxy);

	if(pFiler->filerType() == AcDb::kWblockCloneFiler)
	{
		AcDbHardPointerId Id;
		pFiler->readItem(&Id);
	}

	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//----- Read params
	pFiler->readItem(&m_ptBegin);
	pFiler->readItem(&m_ptMid);
	pFiler->readItem(&m_ptEnd);
	pFiler->readItem(&m_fBrokenSize);
	pFiler->readItem(&m_ptUp);
	pFiler->readItem(&m_ptDown);

	return (pFiler->filerStatus ());
}

// 保存图形-R12/代理图形
void ArxRleBrokenLine::saveAs(AcGiWorldDraw* mode, AcDb::SaveType st)
{
	assertReadEnabled ();

	ArxRleDbEntity::saveAs (mode, st);
}

// AcGiDrawable interface
// 模型空间绘制实体
Adesk::Boolean ArxRleBrokenLine::subWorldDraw (AcGiWorldDraw *pWd)
{
	//AcGiWorldDraw类提供产生几何体对而不随视口改变的功能。
	assertReadEnabled ();

	// Bounding Polyline
	AcGePoint3d pts[6];
	pts[0] = m_ptBegin;
	pts[1] = AcGePoint3d(m_ptMid.x-m_fBrokenSize/2,m_ptMid.y,m_ptMid.z);
	pts[2] = m_ptUp;
	pts[3] = m_ptDown;
	pts[4] = AcGePoint3d(m_ptMid.x+m_fBrokenSize/2,m_ptMid.y,m_ptMid.z);
	pts[5] = m_ptEnd;

	if(m_polyline == NULL) m_polyline = new AcDbPolyline();
	if(m_polyline->numVerts() == 0)
	{
		
		m_polyline->addVertexAt(0, CPt3d(pts[0]));
		m_polyline->addVertexAt(1, CPt3d(pts[1]));
		m_polyline->addVertexAt(2, CPt3d(pts[2]));
		m_polyline->addVertexAt(3, CPt3d(pts[3]));
		m_polyline->addVertexAt(4, CPt3d(pts[4]));
		m_polyline->addVertexAt(5, CPt3d(pts[5]));
	}
	else
	{
		m_polyline->setPointAt(0, CPt3d(pts[0]));
		m_polyline->setPointAt(1, CPt3d(pts[1]));
		m_polyline->setPointAt(2, CPt3d(pts[2]));
		m_polyline->setPointAt(3, CPt3d(pts[3]));
		m_polyline->setPointAt(4, CPt3d(pts[4]));
		m_polyline->setPointAt(5, CPt3d(pts[5]));
	}

	m_polyline->worldDraw(pWd);

	return Adesk::kTrue;
}

// 图纸空间绘制实体
void ArxRleBrokenLine::subViewportDraw(AcGiViewportDraw* pVd)
{
	assertReadEnabled ();

	// Bounding Polyline
	AcGePoint3d pts[6];
	pts[0] = m_ptBegin;
	pts[1] = AcGePoint3d(m_ptMid.x-m_fBrokenSize/2,m_ptMid.y,m_ptMid.z);
	pts[2] = m_ptUp;
	pts[3] = m_ptDown;
	pts[4] = AcGePoint3d(m_ptMid.x+m_fBrokenSize/2,m_ptMid.y,m_ptMid.z);
	pts[5] = m_ptEnd;

	if(m_polyline == NULL) m_polyline = new AcDbPolyline();
	if(m_polyline->numVerts() == 0)
	{

		m_polyline->addVertexAt(0, CPt3d(pts[0]));
		m_polyline->addVertexAt(1, CPt3d(pts[1]));
		m_polyline->addVertexAt(2, CPt3d(pts[2]));
		m_polyline->addVertexAt(3, CPt3d(pts[3]));
		m_polyline->addVertexAt(4, CPt3d(pts[4]));
		m_polyline->addVertexAt(5, CPt3d(pts[5]));
	}
	else
	{
		m_polyline->setPointAt(0, CPt3d(pts[0]));
		m_polyline->setPointAt(1, CPt3d(pts[1]));
		m_polyline->setPointAt(2, CPt3d(pts[2]));
		m_polyline->setPointAt(3, CPt3d(pts[3]));
		m_polyline->setPointAt(4, CPt3d(pts[4]));
		m_polyline->setPointAt(5, CPt3d(pts[5]));
	}

	m_polyline->viewportDraw(pVd);

	ArxRleDbEntity::subViewportDraw (pVd);
}

// 设置属性
Adesk::UInt32 ArxRleBrokenLine::subSetAttributes (AcGiDrawableTraits *pTraits)
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

// 获得捕捉点，这里添加一个中心点         
// 这里仅用第一个变量,虽捕捉到，但是有点问题，鼠标移开后就没有了
// This OSNAP solution handles only simple OSNAP types like CENTER, MIDPOINT and
// ENDPOINT. Complex OSNAP modes like INTERSECTION require other methods implementations and
// 参数2在vc90以及上版本为Adesk::GsMarke类型；在vc80及以下版本为int类型；填写错的话会导致捕捉点无效
Acad::ErrorStatus ArxRleBrokenLine::subGetOsnapPoints (AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark,
const AcGePoint3d &pickPoint, const AcGePoint3d &lastPoint, const AcGeMatrix3d &viewXform,
AcGePoint3dArray &snapPoints, AcDbIntArray &geomIds) const
{
	assertReadEnabled ();

	switch (osnapMode)
	{
	case AcDb::kOsModeEnd:
		snapPoints.append(m_ptBegin);
		snapPoints.append(AcGePoint3d(m_ptMid.x-m_fBrokenSize/2,m_ptMid.y,m_ptMid.z));
		snapPoints.append(m_ptUp);
		snapPoints.append(m_ptDown);
		snapPoints.append(AcGePoint3d(m_ptMid.x+m_fBrokenSize/2,m_ptMid.y,m_ptMid.z));
		snapPoints.append(m_ptEnd);
		break;
	case AcDb::kOsModeMid:
		snapPoints.append(m_ptMid);
		break;
	}

	return Acad::eOk;
}

// 获得夹点
Acad::ErrorStatus ArxRleBrokenLine::subGetGripPoints (AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const
{
	assertReadEnabled ();
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new getGripPoints() method below (which is the default implementation)
	gripPoints.append(m_ptBegin);
	gripPoints.append(m_ptUp);
	gripPoints.append(m_ptMid);
	gripPoints.append(m_ptDown);
	gripPoints.append(m_ptEnd);

	return Acad::eOk;
}

// 移动夹点
Acad::ErrorStatus ArxRleBrokenLine::subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset)
{
	assertWriteEnabled ();

	for(int i=0; i<indices.length(); i++)
	{
		switch (indices.at(i))
		{
		case 0:
			m_ptBegin += offset;
			break;
		case 1:
			m_ptUp += offset;
			m_ptDown -= offset;
			break;
		case 2:
			m_ptBegin += offset;
			m_ptUp += offset;
			m_ptMid += offset;
			m_ptDown += offset;
			m_ptEnd += offset;
			break;
		case 3:
			m_ptUp -= offset;
			m_ptDown += offset;
			break;
		case 4:
			m_ptEnd += offset;
			break;
		}
	}

	return Acad::eOk;
}

// 实体的移动、旋转、缩放
Acad::ErrorStatus ArxRleBrokenLine::subTransformBy(const AcGeMatrix3d & xform)
{
	assertReadEnabled ();

	m_ptBegin.transformBy(xform);
	m_ptUp.transformBy(xform);
	m_ptMid.transformBy(xform);
	m_ptDown.transformBy(xform);
	m_ptEnd.transformBy(xform);

	return Acad::eOk;
}

// 这个函数实现几何转换后新产生一个实体，我没有实现它
Acad::ErrorStatus ArxRleBrokenLine::subGetTransformedCopy(const AcGeMatrix3d &xform, ArxRleDbEntity *&pEnt)
{
	assertReadEnabled();

	return Acad::eOk;
}

Acad::ErrorStatus ArxRleBrokenLine::subGetGeomExtents(AcDbExtents &extents)
{
	assertReadEnabled ();

	return Acad::eOk;
}


////////////////////////////AcEdJig 拖动////////////////////////////////////////////////////////
ArxRleJigBrokenLine::ArxRleJigBrokenLine()
{
}

void ArxRleJigBrokenLine::set(AcGePoint3d ptBegin, double fBrokenSize)
{
	m_ptBegin = ptBegin;
	m_fBrokenSize = fBrokenSize;
}

void ArxRleJigBrokenLine::dragIt()
{
	m_pBrokenLine = new ArxRleBrokenLine;
	if(m_pBrokenLine)
	{ 
		setDispPrompt(L"\nEndPt: ");
		AcEdJig::DragStatus ds = drag();
		append();
	}
}

// 捕获定点设备并作出分析
AcEdJig::DragStatus ArxRleJigBrokenLine::sampler()
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
Adesk::Boolean ArxRleJigBrokenLine::update()
{
	m_pBrokenLine->set(m_ptBegin, m_ptMove, m_fBrokenSize);

	return Adesk::kTrue;
}

//更新实体
ArxRleDbEntity* ArxRleJigBrokenLine::entity() const
{
	return m_pBrokenLine;
}