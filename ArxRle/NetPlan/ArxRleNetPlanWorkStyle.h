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

#ifndef ARXRLE_NETPLAN_WORK_STYLE_H
#define ARXRLE_NETPLAN_WORK_STYLE_H

#include "DbEntity\ArxRleDbDictRecord.h"
#include "DbEntity\ArxRleString.h"

/****************************************************************************
**
**  CLASS ArxRleNetPlanWorkStyle:
**
**  **000
**
*************************************/

class ArxRleNetPlanWorkStyle : public ArxRleDbDictRecord {

public:
                ArxRleNetPlanWorkStyle();
    virtual     ~ArxRleNetPlanWorkStyle();

    ACRX_DECLARE_MEMBERS(ArxRleNetPlanWorkStyle);

	ArxRleString  name() const;
	void          setName(ArxRleString newValue);

	ArxRleString  layer() const;
	void          setLayer(ArxRleString newValue);

	AcDbObjectId  layerId() const;
	void          setLayerId(const AcDbObjectId& id);

	ArxRleString  textStyle() const;
	void          setTextStyle(ArxRleString newValue);

	AcDbObjectId  textStyleId() const;
	void          setTextStyleId(const AcDbObjectId& id);

	ArxRleString  lineType() const;
	void          setLineType(ArxRleString newValue);

	AcDbObjectId  lineTypeId() const;
	void          setLineTypeId(const AcDbObjectId& id);

	Adesk::UInt16 colorIndex() const;
	void          setColorIndex(Adesk::UInt16 newValue);

	double        lineScale() const;
	void          setLineScale(double newValue);

	double        radiusBegin() const;
	void          setRadiusBegin(double newValue);

	double        radiusEnd() const;
	void          setRadiusEnd(double newValue);

	double        lenArrow() const;
	void          setLenArrow(double newValue);

	double        sizeLabel() const;
	void          setSizeLabel(double newValue);

	double        sizeNode() const;
	void          setSizeNode(double newValue);

	double        dayGap() const;
	void          setDayGap(double newValue);

	double        lineGap() const;
	void          setLineGap(double newValue);

	bool          drawLabelBegin() const;
	void          setDrawLabelBegin(bool newValue);

	bool          drawLabelEnd() const;
	void          setDrawLabelEnd(bool newValue);

	bool          drawLabelUp() const;
	void          setDrawLabelUp(bool newValue);

	bool          drawLabelDown() const;
	void          setDrawLabelDown(bool newValue);

protected:
    // overridden from AcDbObject
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* filer) const;

private:
    // data members
	AcString  m_styleName;
    AcString  m_layerName;
	AcString  m_textStyleName;
	AcString  m_lineTypeName;
	Adesk::UInt16 m_colorIndex;
	double    m_lineScale;
	double    m_radiusBegin;
	double    m_radiusEnd;
	double    m_lenArrow;
	double    m_sizeLabel;
	double    m_sizeNode;
	double    m_dayGap;
	double    m_lineGap;
	bool      m_drawLabelBegin;
	bool      m_drawLabelEnd;
	bool      m_drawLabelUp;
	bool      m_drawLabelDown;

	AcDbHardPointerId   m_layerId;
	AcDbHardPointerId   m_textStyleId;
	AcDbHardPointerId   m_lineTypeId;

    static Adesk::Int16  m_version;
	static LPCTSTR		 m_dictName;

    // Dxf Codes
    enum {
		kDxfName            = 1,
		kDxfLayer           = 2,
		kDxfTextStyle       = 3,
		kDxfLineType        = 4,
		kDxfColorIndex      = 5,
		kDxfLineScale       = 6,
		kDxfRadiusBegin     = 7,
		kDxfRadiusEnd       = 8,
		kDxfLenArrow        = 9,
		kDxfSizeLabel       = 10,
		kDxfSizeNode        = 11,
		kDxfDayGap          = 12,
		kDxfLineGap         = 13,
		kDxfDrawLabelBegin  = 14,
		kDxfDrawLabelEnd    = 15,
		kDxfDrawLabelUp     = 16,
		kDxfDrawLabelDown   = 17,
		kDxfLayerId         = 540,
		kDxfTextStyleId     = 541,
		kDxfLineTypeId      = 542
    };

public:
	static LPCTSTR		dictName()	{ return m_dictName; }
	static AcDbObjectId dictObjectId();
	static AcDbObjectId	getStandardStyle(bool makeIfNotThere = true);
	static AcDbObjectId	getGeneralStyle(bool makeIfNotThere = true, bool drawBeginNode = true);
	static AcDbObjectId	getKeyStyle(bool makeIfNotThere = true, bool drawBeginNode = true);
	static AcDbObjectId	getVirtualStyle(bool makeIfNotThere = true);
	static AcDbObjectId	getFreeStyle(bool makeIfNotThere = true);
	static bool         getWorkStyle(AcDbObjectId& wsId);
	static AcDbObjectId getWorkStyle(ArxRleString wsName);
};


#endif  // ARXRLE_NETPLAN_WORK_STYLE_H
