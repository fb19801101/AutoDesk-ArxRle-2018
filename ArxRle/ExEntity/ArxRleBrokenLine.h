//////////////////////////////////////////////////////////////////////////////
//  class ArxRleBrokenLine
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//  
//  ArxRleBrokenLine.h Declaration of ArxRleBrokenLine
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ARXRLE_BROKENLINE_H
#define ARXRLE_BROKENLINE_H

#include "DbEntity/ArxRleEntityClass.h"
#include "DbEntity/ArxRleDbEntity.h"

class ArxRleBrokenLine : public ArxRleDbEntity
{
public:
	ACRX_DECLARE_MEMBERS(ArxRleBrokenLine);

public:
	ArxRleBrokenLine ();
	virtual ~ArxRleBrokenLine ();

	void setPointBegin(AcGePoint3d ptBegin);
	void setPointEnd(AcGePoint3d ptEnd);
	void setPoint(AcGePoint3d ptBegin, AcGePoint3d ptEnd);
	void setBrokenSize(double fBrokenSize);
	void set(AcGePoint3d ptBegin, AcGePoint3d ptEnd, double fBrokenSize);

	CPt3d getPointBegin() {return m_ptBegin;}
	CPt3d getPointEnd() {return m_ptEnd;}
	double getBrokenSize() {return m_fBrokenSize;}

protected:
	// Dwg Filing interface
	// 导出变量
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const;
	// 导入变量
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler);
	// 保存图形-R12/代理图形
	virtual void saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);

	// AcGiDrawable interface
	// 模型空间绘制实体
	virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *pWd);
	// 图纸空间绘制实体
	virtual void subViewportDraw(AcGiViewportDraw* pVd);
	// 设置属性
	virtual Adesk::UInt32 subSetAttributes (AcGiDrawableTraits *pTraits);

	// AcDbOsnap Overrule
	// 获得捕捉点 参数2在vc90以及上版本为Adesk::GsMarke类型；在vc80及以下版本为int类型；填写错的话会导致捕捉点无效
	virtual Acad::ErrorStatus subGetOsnapPoints ( AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark,
		const AcGePoint3d &pickPoint, const AcGePoint3d &lastPoint, const AcGeMatrix3d &viewXform,
		AcGePoint3dArray &snapPoints, AcDbIntArray &geomIds) const;

	// AcDbGrip Overrule
	// 获得夹点
	virtual Acad::ErrorStatus subGetGripPoints (AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const;
	// 移动夹点
	virtual Acad::ErrorStatus subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset);

	// AcDbTransformOverrule
	// 实体的移动、旋转、缩放
	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d & xform);
	virtual Acad::ErrorStatus subGetTransformedCopy(const AcGeMatrix3d &xform, ArxRleDbEntity *&pEnt);
	virtual Acad::ErrorStatus subGetGeomExtents(AcDbExtents &extents);

private:
	static Adesk::Int16 m_version;

	AcGePoint3d m_ptBegin;
	AcGePoint3d m_ptMid;
	AcGePoint3d m_ptEnd;
	AcGePoint3d m_ptUp;
	AcGePoint3d m_ptDown;
	double m_fBrokenSize;

	AcDbPolyline* m_polyline;
};

class ArxRleJigBrokenLine : public AcEdJig
{
public:
	ArxRleJigBrokenLine();

	void set(AcGePoint3d ptBegin, double fBrokenSize);

	void dragIt();
	virtual DragStatus sampler();
	virtual Adesk::Boolean update();
	virtual ArxRleDbEntity* entity() const;

private:
	ArxRleBrokenLine *m_pBrokenLine;

	AcGePoint3d m_ptMove;
	AcGePoint3d m_ptBegin;
	double m_fBrokenSize;
};
#endif  //ARXRLE_BROKENLINE_H
