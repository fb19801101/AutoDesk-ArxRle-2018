//////////////////////////////////////////////////////////////////////////////
//  class ArxRleNetPlanWork
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//  
//  ArxRleNetPlanWork.h Declaration of ArxRleNetPlanWork
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ARXRLE_NETPLAN_WORK_H
#define ARXRLE_NETPLAN_WORK_H

#include "DbEntity\ArxRleEntityClass.h"
#include "DbEntity\ArxRleDbEntity.h"

/****************************************************************************
**
**  CLASS ArxRleNetPlanWork:
**
**  **000
**
*************************************/

class ArxRleNetPlanWorkStyle;

class ArxRleNetPlanWork : public ArxRleDbEntity
{
public:
	ACRX_DECLARE_MEMBERS(ArxRleNetPlanWork);

public:
	ArxRleNetPlanWork ();
	virtual ~ArxRleNetPlanWork ();

	void          setWorkCode(Adesk::UInt32 workCode);
	void          setPointBegin(CPt3d ptBegin);
	void          setPointLeft(CPt3d ptLeft);
	void          setPointMid(CPt3d ptMid);
	void          setPointRight(CPt3d ptRight);
	void          setPointEnd(CPt3d ptEnd);
	void          setLabelBegin(ArxRleString labelBegin);
	void          setLabelEnd(ArxRleString labelEnd);
	void          setLabelUp(ArxRleString labelUp);
	void          setLabelDown(ArxRleString labelDown);
	void          setWorkStyle(ArxRleString wsName);
	void          setWorkDes(ArxRleString workDes);
	void          setBindWorkRef(ArxRleString wrName);
	void          setResMens(double resMens);
	void          setResTools(double resTools);
	void          setResMoney(double resMoney);
	void          setPoint(CPt3d ptBegin, CPt3d ptEnd);
	void          setLabel(ArxRleString labelBegin, ArxRleString labelEnd, ArxRleString labelUp,ArxRleString labelDown = "");
	void          setNode(ArxRleString labelBegin, ArxRleString labelEnd);

	Adesk::UInt32 getWorkCode() const {return m_workCode;}
	CPt3d         getPointBegin() const {return m_ptBegin;}
	CPt3d         getPointLeft() const {return m_ptLeft;}
	CPt3d         getPointMid() const {return m_ptMid;}
	CPt3d         getPointRight() const {return m_ptRight;}
	CPt3d         getPointEnd() const {return m_ptEnd;}
	ArxRleString  getLabelBegin() const {return m_labelBegin;}
	ArxRleString  getLabelEnd() const {return m_labelEnd;}
	ArxRleString  getLabelUp() const {return m_labelUp;}
	ArxRleString  getLabelDown() const {return m_labelDown;}
	ArxRleString  getWorkStyle() const {return m_workStyleName;}
	ArxRleString  getWorkDes() const {return m_workDes;}
	ArxRleString  getBindWorkRef() const {return m_bindWorkRefName;}
	double        getResMens() const {return m_resMens;}
	double        getResTools() const {return m_resTools;}
	double        getResMoney() const {return m_resMoney;}

	AcDbObjectId        getWorkStyleId() const;
	void                setWorkStyleId(const AcDbObjectId& styleId);

	AcDbObjectId		getBindWorkRefId() const;
	void             	setBindWorkRefId(const AcDbObjectId& refId);

protected:
	// Dwg Filing interface
	virtual Acad::ErrorStatus  dwgOutFields(AcDbDwgFiler *pFiler) const;
	virtual Acad::ErrorStatus  dxfOutFields(AcDbDxfFiler *pFiler) const;
	virtual Acad::ErrorStatus  dwgInFields(AcDbDwgFiler *pFiler);
	virtual Acad::ErrorStatus  dxfInFields(AcDbDxfFiler *pFiler);

	// 保存图形-R12/代理图形
	virtual void               saveAs(AcGiWorldDraw* pWd, AcDb::SaveType st);

	// AcGiDrawable interface
	//sub开头函数用于vc90以及上版本继承函数，对应的不带sub开头的为vc80及以下版本继承函数
	// 模型空间绘制实体
	virtual Adesk::Boolean     subWorldDraw (AcGiWorldDraw *pWd);
	virtual void               subViewportDraw(AcGiViewportDraw* pVd);

	// 设置属性
	virtual Adesk::UInt32      subSetAttributes (AcGiDrawableTraits *pTraits);

	////获得一个实体的范围（一个极大点  一个极小点）
	virtual Acad::ErrorStatus  subGetGeomExtents(AcDbExtents& extents) const;

	// AcDbOsnap Overrule
	// 获得捕捉点 参数2在vc90以及上版本为Adesk::GsMarke类型；在vc80及以下版本为int类型；填写错的话会导致捕捉点无效
	virtual Acad::ErrorStatus  subGetOsnapPoints ( AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark,
		const AcGePoint3d &pickPoint, const AcGePoint3d &lastPoint, const AcGeMatrix3d &viewXform,
		AcGePoint3dArray &snapPoints, AcDbIntArray &geomIds) const;

	// AcDbGrip Overrule
	virtual Acad::ErrorStatus  subGetGripPoints (AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const;
	virtual Acad::ErrorStatus  subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset);

	// AcDbTransformOverrule
	virtual Acad::ErrorStatus  subTransformBy(const AcGeMatrix3d & xform);
	virtual Acad::ErrorStatus  subGetTransformedCopy(const AcGeMatrix3d& xform,AcDbEntity*& ent) const;

	// handle all deepClone
	virtual void		       getCloneReferences(AcDb::DeepCloneType type, AcDbObjectIdArray& objIds, AcDbIntArray& refTypes) const;

	virtual Acad::ErrorStatus  subExplode(AcDbVoidPtrArray& entitySet) const;

	void                       drawLabel(AcGiWorldDraw *pWd, ArxRleNetPlanWorkStyle* style);
	void                       drawLabel(AcGiViewportDraw *pVd, ArxRleNetPlanWorkStyle* style);

	void                       drawCircle(AcGiWorldDraw *pWd, ArxRleNetPlanWorkStyle* style);
	void                       drawCircle(AcGiViewportDraw *pVd, ArxRleNetPlanWorkStyle* style);

	void                       drawPolyline(AcGiWorldDraw *pWd, ArxRleNetPlanWorkStyle* style);
	void                       drawPolyline(AcGiViewportDraw *pVd, ArxRleNetPlanWorkStyle* style);

private:
	static Adesk::Int16 m_version;

	Adesk::UInt32 m_workCode;
	AcGePoint3d m_ptBegin;
	AcGePoint3d m_ptLeft;
	AcGePoint3d m_ptMid;
	AcGePoint3d m_ptRight;
	AcGePoint3d m_ptEnd;
	AcString    m_labelBegin;
	AcString    m_labelEnd;
	AcString    m_labelUp;
	AcString    m_labelDown;
	AcString    m_workStyleName;
	AcString    m_workDes;
	AcString    m_bindWorkRefName;
	double      m_resMens;
	double      m_resTools;
	double      m_resMoney;

	AcDbHardPointerId   m_workStyleId;
	AcDbHardPointerId	m_bindWorkRefId;

	double       m_length;
	bool         m_autoMove;   
	bool         m_moveLeft;
	bool         m_moveMid;
	bool         m_moveRight;
	bool         m_setLabelDown;
	int          m_drawNode;
	bool         m_bindWork;

	vector<AcDbText*> m_vecTxtUp;
	AcDbText     *m_txtBegin,*m_txtEnd,*m_txtDown;
	AcDbCircle   *m_circleBegin,*m_circleEnd;
	AcDbPolyline *m_polyline;

	// Dxf Codes
	enum {
		kDxfWorkCode      = 1,
		kDxfPtBegin		  = 2,
		kDxfPtLeft		  = 3,
		kDxfPtMid		  = 4,
		kDxfPtRight		  = 5,
		kDxfPtEnd		  = 6,
		kDxfTxtBegin	  = 7,
		kDxfTxtEnd		  = 8,
		kDxfTxtUp		  = 9,
		kDxfTxtDown		  = 10,
		kDxfWorkStyle     = 11,
		kDxfWorkDes       = 12,
		kDxfBindWorkRef   = 13,
		kDxfResMens       = 14,
		kDxfResTools      = 15,
		kDxfResMoney      = 16,
		kDxfWorkStyleId   = 340,
		kDxfBindWorkRefId = 341,
	};
};

/****************************************************************************
**
**  CLASS ArxRleJigNetPlanWork:
**
**  **000
**
*************************************/

class ArxRleJigNetPlanWork : public AcEdJig
{
public:
	ArxRleJigNetPlanWork();

	void                    setPoint(CPt3d ptBegin, ArxRleString wsName);
	void                    setLabel(ArxRleString labelBegin, ArxRleString labelEnd, ArxRleString labelUp,ArxRleString labelDown);

	void                    dragIt();
	virtual DragStatus      sampler();
	virtual Adesk::Boolean  update();
	virtual AcDbEntity*     entity() const;

private:
	ArxRleNetPlanWork* m_pNetPlanWork;

	AcGePoint3d m_ptBegin;
	AcGePoint3d m_ptMove;

	ArxRleString m_workStyleName;
	ArxRleString m_labelBegin;
	ArxRleString m_labelEnd;
	ArxRleString m_labelUp;
	ArxRleString m_labelDown;
};

#endif  //ARXRLE_NETPLAN_WORK_H
