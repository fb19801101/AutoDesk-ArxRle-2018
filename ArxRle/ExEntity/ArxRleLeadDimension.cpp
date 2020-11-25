//////////////////////////////////////////////////////////////////////////////
//  class ArxRleLeadDimension
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//  
//  ArxRleLeadDimension.cpp  Implementation of ArxRleLeadDimension
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleLeadDimension.h"
#include "DbEntity/ArxRleEntityClass.h"

Adesk::Int16 ArxRleLeadDimension::m_version = 0;
ACRX_DXF_DEFINE_MEMBERS (
	ArxRleLeadDimension, AcDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	0, ArxRleLeadDimension/*在CAD中该实体类的名称*/,
	ARXRLE_ADESK_LEADDIMENSION
	|Product Desc:     引线标注
	|Company:          中铁十二局集团一公司
	|WEB Address:      http://www.cr201.com
);

ArxRleLeadDimension::ArxRleLeadDimension () : AcDbEntity ()
{
	m_tsName = "Arx_Txt";
	m_tsId = AddTextStyle(m_tsName);

	m_txtUp = NULL;
	m_txtDown = NULL;
	m_pPolyline = NULL;
}

ArxRleLeadDimension::~ArxRleLeadDimension ()
{
	if(m_txtUp != NULL) delete m_txtUp;
	if(m_txtDown != NULL) delete m_txtDown;
	if(m_pPolyline != NULL) delete m_pPolyline;

	m_txtUp = NULL;
	m_txtDown = NULL;
	m_pPolyline = NULL;
}

// 属性设置

void ArxRleLeadDimension::setPointBase(CPt3d ptBase)
{
	assertWriteEnabled ();
	m_ptBase = ptBase;
}

void ArxRleLeadDimension::setPointBegin(CPt3d ptBegin)
{
	assertWriteEnabled ();
	m_ptBegin = ptBegin;
	m_ptMid[X] = (m_ptBegin[X]+m_ptEnd[X])/2;
	m_ptMid[Y] = (m_ptBegin[Y]+m_ptEnd[Y])/2;
	m_fTextAngle = CPt3d::GetAngle(m_ptBegin, m_ptEnd);
}

void ArxRleLeadDimension::setPointMid(CPt3d ptMid)
{
	assertWriteEnabled ();
	m_ptMid = ptMid;
}

void ArxRleLeadDimension::setPointEnd(CPt3d ptEnd)
{
	assertWriteEnabled ();
	m_ptEnd = ptEnd;
	m_ptMid[X] = (m_ptBegin[X]+m_ptEnd[X])/2;
	m_ptMid[Y] = (m_ptBegin[Y]+m_ptEnd[Y])/2;
	m_fTextAngle = CPt3d::GetAngle(m_ptBegin, m_ptEnd);
}

void ArxRleLeadDimension::setLabelUp(ArxRleString labelUp)
{
	assertWriteEnabled ();
	m_labelUp = labelUp.a_str();
}

void ArxRleLeadDimension::setLabelDown(ArxRleString labelDown)
{
	assertWriteEnabled ();
	m_labelDown = labelDown.a_str();
}

void ArxRleLeadDimension::setTextSize(double fTextSize)
{
	assertWriteEnabled ();
	m_fTextSize = fTextSize;
}

void ArxRleLeadDimension::setTextAngle(double fTextAngle)
{
	assertWriteEnabled ();
	m_fTextAngle = fTextAngle;
}

void ArxRleLeadDimension::setTextStyle(ArxRleString tsName)
{
	assertWriteEnabled ();
	if(!tsName.IsEmpty() && tsName != ArxRleString(m_tsName))
	{
		m_tsName = tsName.a_str();
		m_tsId = AddTextStyle(tsName);
	}
}

void ArxRleLeadDimension::setPoint(CPt3d ptBase, CPt3d ptBegin, CPt3d ptEnd)
{
	assertWriteEnabled ();
	m_ptBase = ptBase;
	m_ptBegin = ptBegin;
	m_ptEnd = ptEnd;
	m_ptMid[X] = (m_ptBegin[X]+m_ptEnd[X])/2;
	m_ptMid[Y] = (m_ptBegin[Y]+m_ptEnd[Y])/2;
	m_fTextAngle = CPt3d::GetAngle(m_ptBegin, m_ptEnd);
}

void ArxRleLeadDimension::setLabel(ArxRleString labelUp, ArxRleString labelDown, double fTextSize)
{
	assertWriteEnabled ();
	m_labelUp = labelUp.a_str();
	m_labelDown = labelDown.a_str();
	m_fTextSize = fTextSize;
}

//  Dwg Filing interface
// 导出变量
Acad::ErrorStatus ArxRleLeadDimension::dwgOutFields (AcDbDwgFiler *pFiler) const
{
	assertReadEnabled ();
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgOutFields (pFiler);
	if (es != Acad::eOk)
		return (es);

	//----- Object version number needs to be saved first
	if ((es =pFiler->writeInt16 (ArxRleLeadDimension::m_version)) != Acad::eOk)
		return (es);

	if (pFiler->filerType()==AcDb::kWblockCloneFiler)
		pFiler->writeHardPointerId((AcDbHardPointerId)ownerId());

	//----- Output params
	pFiler->writePoint3d(m_ptBase);
	pFiler->writePoint3d(m_ptBegin);
	pFiler->writePoint3d(m_ptMid);
	pFiler->writePoint3d(m_ptEnd);
	pFiler->writeString(m_labelUp);
	pFiler->writeString(m_labelDown);
	pFiler->writeDouble(m_fTextSize);
	pFiler->writeDouble(m_fTextAngle);
	pFiler->writeString(m_tsName);

	return pFiler->filerStatus();
}

Acad::ErrorStatus ArxRleLeadDimension::dxfOutFields (AcDbDxfFiler *pFiler) const
{
	assertReadEnabled ();
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dxfOutFields (pFiler);
	if (es != Acad::eOk)
		return (es);

	pFiler->writeItem(AcDb::kDxfSubclass, this->desc()->name());

	//----- Output params
	pFiler->writePoint3d(kDxfPtBase, m_ptBase);
	pFiler->writePoint3d(kDxfPtBegin, m_ptBegin);
	pFiler->writePoint3d(kDxfPtMid, m_ptMid);
	pFiler->writePoint3d(kDxfPtEnd, m_ptEnd);
	pFiler->writeString(kDxfTxtUp, m_labelUp);
	pFiler->writeString(kDxfTxtDown, m_labelDown);
	pFiler->writeDouble(kDxfTxtSize, m_fTextSize);
	pFiler->writeDouble(kDxfTxtAngle, m_fTextAngle);
	pFiler->writeString(kDxfTxtStyle, m_tsName);

	return pFiler->filerStatus();
}

// 导入变量
Acad::ErrorStatus ArxRleLeadDimension::dwgInFields (AcDbDwgFiler *pFiler)
{
	assertWriteEnabled ();
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgInFields (pFiler);
	if (es != Acad::eOk)
		return (es);

	//----- Object version number nee;ds to be read first
	Adesk::Int16 version = 0;
	if ((es =pFiler->readInt16 (&version)) != Acad::eOk)
		return (es);

	if (version > ArxRleLeadDimension::m_version)
		return (Acad::eMakeMeProxy);

	if(pFiler->filerType() == AcDb::kWblockCloneFiler)
	{
		AcDbHardPointerId Id;
		pFiler->readHardPointerId(&Id);
	}

	pFiler->readPoint3d(&m_ptBase);
	pFiler->readPoint3d(&m_ptBegin);
	pFiler->readPoint3d(&m_ptMid);
	pFiler->readPoint3d(&m_ptEnd);
	pFiler->readString(m_labelUp);
	pFiler->readString(m_labelDown);
	pFiler->readDouble(&m_fTextSize);
	pFiler->readDouble(&m_fTextAngle);
	pFiler->readString(m_tsName);

	return (pFiler->filerStatus ());
}

Acad::ErrorStatus ArxRleLeadDimension::dxfInFields (AcDbDxfFiler *pFiler)
{
	assertWriteEnabled ();
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dxfInFields (pFiler);
	if ((es != Acad::eOk) || 
		(pFiler->atSubclassData(this->desc()->name()) != Adesk::kTrue))
		return (pFiler->filerStatus ());

	resbuf rb;

	while ((es == Acad::eOk) && ((es = pFiler->readResBuf(&rb)) == Acad::eOk)) {
		if(rb.restype == kDxfPtBase) {
			CPt3d tmpPt(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
			setPointBase(tmpPt);
		}
		else if(rb.restype == kDxfPtBegin) {
			CPt3d tmpPt(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
			setPointBegin(tmpPt);
		}
		else if(rb.restype == kDxfPtMid) {
			CPt3d tmpPt(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
			setPointMid(tmpPt);
		}
		else if(rb.restype == kDxfPtEnd) {
			CPt3d tmpPt(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
			setPointEnd(tmpPt);
		}
		else if(rb.restype == kDxfTxtUp)
			setLabelUp(rb.resval.rstring); 
		else if(rb.restype == kDxfTxtDown)
			setLabelDown(rb.resval.rstring); 
		else if(rb.restype == kDxfTxtSize)
			setTextSize(rb.resval.rreal); 
		else if(rb.restype == kDxfTxtAngle)
			setTextAngle(rb.resval.rreal); 
		else if(rb.restype == kDxfTxtStyle)
			setTextStyle(rb.resval.rstring); 
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
void ArxRleLeadDimension::saveAs(AcGiWorldDraw* mode, AcDb::SaveType st)
{
	assertReadEnabled ();
	if(m_txtUp != NULL)
		m_txtUp->saveAs (mode, st);
	if(m_txtDown != NULL)
		m_txtDown->saveAs (mode, st);
	if(m_pPolyline != NULL)
		m_pPolyline->saveAs (mode, st);

	AcDbEntity::saveAs (mode, st);
}

// AcGiDrawable interface
// 模型空间绘制实体
Adesk::Boolean ArxRleLeadDimension::subWorldDraw (AcGiWorldDraw *pWd)
{
	//AcGiWorldDraw类提供产生几何体对而不随视口改变的功能。
	assertReadEnabled ();

	AcDbObjectId tsId = FindTextStyle(m_tsName);
	AcDbTextStyleTableRecord* ts = (AcDbTextStyleTableRecord*)GetRecordPtr(tsId);
	if(ts == NULL) return Adesk::kFalse;

	double offset = 0.15*m_fTextSize;

	if(m_txtUp == NULL) m_txtUp = new AcDbText;
	m_txtUp->setTextStyle(tsId);
	m_txtUp->setWidthFactor(ts->xScale());
	m_txtUp->setTextString(m_labelUp);
	m_txtUp->setHeight(m_fTextSize);
	m_txtUp->setRotation(m_fTextAngle);
	m_txtUp->setHorizontalMode(AcDb::kTextCenter);
	m_txtUp->setVerticalMode(AcDb::kTextBottom);
	m_txtUp->setPosition(CPt3d(m_ptMid[X],m_ptMid[Y]+offset));
	m_txtUp->setAlignmentPoint(CPt3d(m_ptMid[X],m_ptMid[Y]+offset));
	m_txtUp->adjustAlignment(ARXRLEDB);

    if(m_txtDown == NULL) m_txtDown = new AcDbText;
	m_txtDown->setTextStyle(tsId);
	m_txtDown->setWidthFactor(ts->xScale());
	m_txtDown->setTextString(m_labelDown);
	m_txtDown->setHeight(m_fTextSize/2);
	m_txtDown->setRotation(m_fTextAngle);
	m_txtDown->setHorizontalMode(AcDb::kTextCenter);
	m_txtDown->setVerticalMode(AcDb::kTextTop);
	m_txtDown->setPosition(CPt3d(m_ptMid[X],m_ptMid[Y]-offset));
	m_txtDown->setAlignmentPoint(CPt3d(m_ptMid[X],m_ptMid[Y]-offset));
	m_txtDown->adjustAlignment(ARXRLEDB);
	ts->close();

	double ang = CPt3d::GetAngle(m_ptBase, m_ptBegin);
	if(m_pPolyline == NULL) m_pPolyline = new AcDbPolyline();
	if(m_pPolyline->numVerts() == 0)
	{
		CPt3d pt = CPt3d(m_ptBase).GetLineEnd(m_fTextSize/2,ang);
		m_pPolyline->addVertexAt(0, pt);
		pt = pt.GetLineEnd(m_fTextSize/10,ang+PI/2);
		m_pPolyline->addVertexAt(1, pt);
		m_pPolyline->addVertexAt(2, CPt3d(m_ptBase));
		m_pPolyline->addVertexAt(3, CPt3d(m_ptBegin));
		m_pPolyline->addVertexAt(4, CPt3d(m_ptEnd));
	}
	else
	{
		CPt3d pt = CPt3d(m_ptBase).GetLineEnd(m_fTextSize/2,ang);
		m_pPolyline->setPointAt(0, pt);
		pt = pt.GetLineEnd(m_fTextSize/10,ang+PI/2);
		m_pPolyline->setPointAt(1, pt);
		m_pPolyline->setPointAt(2, CPt3d(m_ptBase));
		m_pPolyline->setPointAt(3, CPt3d(m_ptBegin));
		m_pPolyline->setPointAt(4, CPt3d(m_ptEnd));
	}

	m_pPolyline->worldDraw(pWd);
	m_txtUp->worldDraw(pWd);
	m_txtDown->worldDraw(pWd);

	return Adesk::kTrue;
}

// 图纸空间绘制实体
void ArxRleLeadDimension::subViewportDraw(AcGiViewportDraw* pVd)
{
	assertReadEnabled ();

	AcDbObjectId tsId = FindTextStyle(m_tsName);
	AcDbTextStyleTableRecord* ts = (AcDbTextStyleTableRecord*)GetRecordPtr(tsId);
	if(ts == NULL) return;

	double offset = 0.15*m_fTextSize;

	if(m_txtUp == NULL) m_txtUp = new AcDbText;
	m_txtUp->setTextStyle(tsId);
	m_txtUp->setWidthFactor(ts->xScale());
	m_txtUp->setTextString(m_labelUp);
	m_txtUp->setHeight(m_fTextSize);
	m_txtUp->setRotation(m_fTextAngle);
	m_txtUp->setHorizontalMode(AcDb::kTextCenter);
	m_txtUp->setVerticalMode(AcDb::kTextBottom);
	m_txtUp->setPosition(CPt3d(m_ptMid[X],m_ptMid[Y]+offset));
	m_txtUp->setAlignmentPoint(CPt3d(m_ptMid[X],m_ptMid[Y]+offset));
	m_txtUp->adjustAlignment(ARXRLEDB);

	if(m_txtDown == NULL) m_txtDown = new AcDbText;
	m_txtDown->setTextStyle(tsId);
	m_txtDown->setWidthFactor(ts->xScale());
	m_txtDown->setTextString(m_labelDown);
	m_txtDown->setHeight(m_fTextSize/2);
	m_txtDown->setRotation(m_fTextAngle);
	m_txtDown->setHorizontalMode(AcDb::kTextCenter);
	m_txtDown->setVerticalMode(AcDb::kTextTop);
	m_txtDown->setPosition(CPt3d(m_ptMid[X],m_ptMid[Y]-offset));
	m_txtDown->setAlignmentPoint(CPt3d(m_ptMid[X],m_ptMid[Y]-offset));
	m_txtDown->adjustAlignment(ARXRLEDB);
	ts->close();

	double ang = CPt3d::GetAngle(m_ptBase, m_ptBegin);
	if(m_pPolyline == NULL) m_pPolyline = new AcDbPolyline();
	if(m_pPolyline->numVerts() == 0)
	{
		CPt3d pt = CPt3d(m_ptBase).GetLineEnd(m_fTextSize/2,ang);
		m_pPolyline->addVertexAt(0, pt);
		pt = pt.GetLineEnd(m_fTextSize/10,ang+PI/2);
		m_pPolyline->addVertexAt(1, pt);
		m_pPolyline->addVertexAt(2, CPt3d(m_ptBase));
		m_pPolyline->addVertexAt(3, CPt3d(m_ptBegin));
		m_pPolyline->addVertexAt(4, CPt3d(m_ptEnd));
	}
	else
	{
		CPt3d pt = CPt3d(m_ptBase).GetLineEnd(m_fTextSize/2,ang);
		m_pPolyline->setPointAt(0, pt);
		pt = pt.GetLineEnd(m_fTextSize/10,ang+PI/2);
		m_pPolyline->setPointAt(1, pt);
		m_pPolyline->setPointAt(2, CPt3d(m_ptBase));
		m_pPolyline->setPointAt(3, CPt3d(m_ptBegin));
		m_pPolyline->setPointAt(4, CPt3d(m_ptEnd));
	}

	m_pPolyline->viewportDraw(pVd);
	m_txtUp->viewportDraw(pVd);
	m_txtDown->viewportDraw(pVd);

	AcDbEntity::subViewportDraw (pVd);
}

// 设置属性
Adesk::UInt32 ArxRleLeadDimension::subSetAttributes (AcGiDrawableTraits *pTraits)
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

	return (AcDbEntity::subSetAttributes (pTraits));
}

// 获得捕捉点，这里添加一个中心点         
// 这里仅用第一个变量,虽捕捉到，但是有点问题，鼠标移开后就没有了
// This OSNAP solution handles only simple OSNAP types like CENTER, MIDPOINT and
// ENDPOINT. Complex OSNAP modes like INTERSECTION require other methods implementations and
// 参数2在vc90以及上版本为Adesk::GsMarke类型；在vc80及以下版本为int类型；填写错的话会导致捕捉点无效
Acad::ErrorStatus ArxRleLeadDimension::subGetOsnapPoints (AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark,
	const AcGePoint3d &pickPoint, const AcGePoint3d &lastPoint, const AcGeMatrix3d &viewXform,
	AcGePoint3dArray &snapPoints, AcDbIntArray &geomIds) const
{
	assertReadEnabled ();

	switch (osnapMode)
	{
	case AcDb::kOsModeEnd:
		snapPoints.append(m_ptBase);
		snapPoints.append(m_ptBegin);
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
Acad::ErrorStatus ArxRleLeadDimension::subGetGripPoints (AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const
{
	assertReadEnabled ();
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new getGripPoints() method below (which is the default implementation)
	gripPoints.append(m_ptBase);
	gripPoints.append(m_ptBegin);
	gripPoints.append(m_ptMid);
	gripPoints.append(m_ptEnd);

	return Acad::eOk;
}

// 移动夹点
Acad::ErrorStatus ArxRleLeadDimension::subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset)
{
	assertWriteEnabled ();
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new moveGripPointsAt() method below (which is the default implementation)
	if (indices.length() == 0 || offset.isZeroLength())
		return Acad::eOk;

	int i = indices[0];
	//for(int i=0; i<indices.length(); i++) 
	{
		switch (i/*indices.at(i)*/)
		{
		case 0://左侧端点
			m_ptBase += offset;
			m_ptBegin += offset;
			m_ptEnd += offset;
			break;
		case 1://左侧端点
			m_ptBegin += offset;
			break;
		case 2://中间端点
			m_ptBegin += offset;
			m_ptEnd += offset;
			break;
		case 3://右侧端点
			m_ptEnd += offset;
			break;
		}

		m_ptMid[X] = (m_ptBegin[X]+m_ptEnd[X])/2;
		m_ptMid[Y] = (m_ptBegin[Y]+m_ptEnd[Y])/2;
		m_fTextAngle = CPt3d::GetAngle(m_ptBegin, m_ptEnd);
	}

	return Acad::eOk;
}

// 实体的移动、旋转、缩放
Acad::ErrorStatus ArxRleLeadDimension::subTransformBy(const AcGeMatrix3d & xform)
{
	assertWriteEnabled ();

	m_ptBase.transformBy(xform);
 	m_ptBegin.transformBy(xform);
 	m_ptMid.transformBy(xform);
 	m_ptEnd.transformBy(xform);
	return Acad::eOk;
}


////////////////////////////AcEdJig 拖动////////////////////////////////////////////////////////
ArxRleJigLeadDimension::ArxRleJigLeadDimension()
{
}

void ArxRleJigLeadDimension::setPoint(CPt3d ptBase, CPt3d ptBegin)
{
	m_ptBase = ptBase;
	m_ptBegin = ptBegin;
}

void ArxRleJigLeadDimension::setLabel(ArxRleString labelUp, ArxRleString labelDown, double fTextSize)
{
	m_labelUp = labelUp.a_str();
	m_labelDown = labelDown.a_str();
	m_fTextSize = fTextSize;
}

void ArxRleJigLeadDimension::dragIt()
{
	m_pLeadDimension = new ArxRleLeadDimension;
	if(m_pLeadDimension)
	{ 
		setDispPrompt(L"\nEndPt: ");
		AcEdJig::DragStatus ds = drag();
		append();
	}
}

// 捕获定点设备并作出分析
AcEdJig::DragStatus ArxRleJigLeadDimension::sampler()
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
Adesk::Boolean ArxRleJigLeadDimension::update()
{
	m_pLeadDimension->setPoint(m_ptBase, m_ptBegin, m_ptMove);
	m_pLeadDimension->setLabel(m_labelUp, m_labelDown, m_fTextSize);
	m_pLeadDimension->setColorIndex(3);

	return Adesk::kTrue;
}

//更新实体
AcDbEntity* ArxRleJigLeadDimension::entity() const
{
	return m_pLeadDimension;
}