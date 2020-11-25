//////////////////////////////////////////////////////////////////////////////
//  class ArxRleLeadDimension
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//  
//  ArxRleLeadDimension.h Declaration of ArxRleLeadDimension
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ARXRLE_LEAD_DIMENSION_H
#define ARXRLE_LEAD_DIMENSION_H

#include "DbEntity/ArxRleEntityClass.h"
#include "Filer/ArxRleDwgFiler.h"

class ArxRleLeadDimension : public AcDbEntity
{
public:
	ACRX_DECLARE_MEMBERS(ArxRleLeadDimension);

public:
	ArxRleLeadDimension ();
	virtual ~ArxRleLeadDimension ();

	void setPointBase(CPt3d ptBase);
	void setPointBegin(CPt3d ptBegin);
	void setPointMid(CPt3d ptMid);
	void setPointEnd(CPt3d ptEnd);
	void setLabelUp(ArxRleString labelUp);
	void setLabelDown(ArxRleString labelDown);
	void setTextSize(double fTextSize);
	void setTextStyle(ArxRleString tsName);
	void setTextAngle(double fTextAngle);
	void setPoint(CPt3d ptBase, CPt3d ptBegin, CPt3d ptEnd);
	void setLabel(ArxRleString labelUp, ArxRleString labelDown, double fTextSize);

	CPt3d getPointBase() {return m_ptBase;}
	CPt3d getPointBegin() {return m_ptBegin;}
	CPt3d getPointMid() {return m_ptMid;}
	CPt3d getPointEnd() {return m_ptEnd;}
	ArxRleString getLabelUp() {return m_labelUp;}
	ArxRleString getLabelDown() {return m_labelDown;}
	double getTextSize() {return m_fTextSize;}
	double getTextAngle() {return m_fTextAngle;}
	ArxRleString getTextStyle() {return m_tsName;}

protected:
	// Dwg Filing interface
	// ��������
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const;
	virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const;
	// �������
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler);
	virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler);
	// ����ͼ��-R12/����ͼ��
	virtual void saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);

	// AcGiDrawable interface
	//sub��ͷ��������vc90�Լ��ϰ汾�̳к�������Ӧ�Ĳ���sub��ͷ��Ϊvc80�����°汾�̳к���
	// ģ�Ϳռ����ʵ��
	virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *pWd);
	// ͼֽ�ռ����ʵ��
	virtual void subViewportDraw(AcGiViewportDraw* pVd);
	// ��������
	virtual Adesk::UInt32 subSetAttributes (AcGiDrawableTraits *pTraits);

	// AcDbOsnap Overrule
	// ��ò�׽�� ����2��vc90�Լ��ϰ汾ΪAdesk::GsMarke���ͣ���vc80�����°汾Ϊint���ͣ���д��Ļ��ᵼ�²�׽����Ч
	virtual Acad::ErrorStatus subGetOsnapPoints ( AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark,
		const AcGePoint3d &pickPoint, const AcGePoint3d &lastPoint, const AcGeMatrix3d &viewXform,
		AcGePoint3dArray &snapPoints, AcDbIntArray &geomIds) const;

	// AcDbGrip Overrule
	// ��üе�
	virtual Acad::ErrorStatus subGetGripPoints (AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const;
	// �ƶ��е�
	virtual Acad::ErrorStatus subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset);

	// AcDbTransformOverrule
	// ʵ����ƶ�����ת������
	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d & xform);

private:
	static Adesk::Int16 m_version;

	AcGePoint3d m_ptBase;
	AcGePoint3d m_ptBegin;
	AcGePoint3d m_ptMid;
	AcGePoint3d m_ptEnd;
	AcString m_labelUp;
	AcString m_labelDown;
	double m_fTextSize;
	double m_fTextAngle;
	AcString m_tsName;

	AcDbObjectId m_tsId;

	AcDbText *m_txtUp,*m_txtDown;
	AcDbPolyline *m_pPolyline;

	// Dxf Codes
	enum {
		kDxfPtBase		= 1,
		kDxfPtBegin		= 2,
		kDxfPtMid		= 3,
		kDxfPtEnd		= 4,
		kDxfTxtUp		= 5,
		kDxfTxtDown		= 6,
		kDxfTxtSize		= 7,
		kDxfTxtAngle    = 8,
		kDxfTxtStyle    = 9,
	};
};


class ArxRleJigLeadDimension : public AcEdJig
{
public:
	ArxRleJigLeadDimension();

	void setPoint(CPt3d ptBase, CPt3d ptBegin);
	void setLabel(ArxRleString labelUp, ArxRleString labelDown, double fTextSize);

	void dragIt();
	virtual DragStatus sampler();
	virtual Adesk::Boolean update();
	virtual AcDbEntity* entity() const;

private:
	ArxRleLeadDimension *m_pLeadDimension;

	AcGePoint3d m_ptBase;
	AcGePoint3d m_ptBegin;
	AcGePoint3d m_ptMove;
	AcString m_labelUp;
	AcString m_labelDown;
	double m_fTextSize;
};
#endif  //ARXRLE_TITLELABEL_H
