/
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

#include "ArxRleNetPlanWorkStyle.h"
#include "AcadUtils\ArxRleUtils.h"
#include "DbEntity\ArxRleEntityClass.h"
#include "UiDlg\ArxRleUiDlgGenericDefId.h"



     // MDI safe statics
Adesk::Int16    ArxRleNetPlanWorkStyle::m_version = 0;
LPCTSTR			ArxRleNetPlanWorkStyle::m_dictName = _T("ARXRLE_NETPLAN_WORK_STYLES");


ACRX_DXF_DEFINE_MEMBERS(ArxRleNetPlanWorkStyle, ArxRleDbDictRecord,
                        AcDb::kDHL_1015, AcDb::kMRelease0,
                        0, ARXRLE_ADSK_NETPLAN_WORK_STYLE, ArxRle)

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::ArxRleNetPlanWorkStyle
**
**  **000
**
*************************************/

ArxRleNetPlanWorkStyle::ArxRleNetPlanWorkStyle()
:   m_styleName(_T("Standard")),   
    m_layerName(_T("NetPlan")),
	m_textStyleName(_T("NetPlan")),
	m_lineTypeName(_T("Continuous")),
	m_colorIndex(4),
	m_lineScale(1),
	m_radiusBegin(1.6),
	m_radiusEnd(1.6),
	m_lenArrow(1.5),
	m_sizeLabel(1.8),
	m_sizeNode(1.8),
	m_dayGap(1),
	m_lineGap(4),
	m_drawLabelBegin(true),
	m_drawLabelEnd(true),
	m_drawLabelUp(true),
	m_drawLabelDown(true)
{
	m_layerId = AddLayer(m_layerName);
	m_textStyleId = AddTextStyle(m_textStyleName);
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::~ArxRleNetPlanWorkStyle
**
**  **000
**
*************************************/

ArxRleNetPlanWorkStyle::~ArxRleNetPlanWorkStyle()
{
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::name
**
**  **000
**
*************************************/

ArxRleString ArxRleNetPlanWorkStyle::name() const
{
	assertReadEnabled();
	return m_styleName;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setName
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setName(ArxRleString newValue)
{
	assertWriteEnabled();
	m_styleName = newValue.a_str();
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::layer
**
**  **000
**
*************************************/

ArxRleString ArxRleNetPlanWorkStyle::layer() const
{
	assertReadEnabled();
	return m_layerName;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setLayer
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setLayer(ArxRleString newValue)
{
	assertWriteEnabled();
	m_layerName = newValue.a_str();
	m_layerId = AddLayer(m_layerName);
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::layerId
**
**  **000
**
*************************************/

AcDbObjectId ArxRleNetPlanWorkStyle::layerId() const
{
	assertReadEnabled();
	return m_layerId;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setLayerId
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setLayerId(const AcDbObjectId& id)
{
	if(id != AcDbObjectId::kNull && id != m_layerId)
	{
		assertWriteEnabled();
		m_layerId = id;
		ACHAR* sName;
		GetRecordPtr(id)->getName(sName);
		m_layerName = sName;
	}
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::textStyle
**
**  **000
**
*************************************/

ArxRleString ArxRleNetPlanWorkStyle::textStyle() const
{
	assertReadEnabled();
	return m_textStyleName;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setTextStyle
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setTextStyle(ArxRleString newValue)
{
	assertWriteEnabled();
	m_textStyleName = newValue.a_str();
	m_textStyleId = AddTextStyle(m_textStyleName);
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::textStyleId
**
**  **000
**
*************************************/

AcDbObjectId ArxRleNetPlanWorkStyle::textStyleId() const
{
	assertReadEnabled();
	return m_textStyleId;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setTextStyleId
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setTextStyleId(const AcDbObjectId& id)
{
	if(id != AcDbObjectId::kNull && id != m_textStyleId)
	{
		assertWriteEnabled();
		m_textStyleId = id;
		ACHAR* sName;
		GetRecordPtr(id)->getName(sName);
		m_textStyleName = sName;
	}
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::lineType
**
**  **000
**
*************************************/

ArxRleString ArxRleNetPlanWorkStyle::lineType() const
{
	assertReadEnabled();
	return m_lineTypeName;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setLineType
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setLineType(ArxRleString newValue)
{
	assertWriteEnabled();
	m_lineTypeName = newValue.a_str();;
	m_lineTypeId = GetLineType(m_lineTypeName);
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::lineTypeId
**
**  **000
**
*************************************/

AcDbObjectId ArxRleNetPlanWorkStyle::lineTypeId() const
{
	assertReadEnabled();
	return m_lineTypeId;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setLineTypeId
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setLineTypeId(const AcDbObjectId& id)
{
	if(id != AcDbObjectId::kNull && id != m_lineTypeId)
	{
		assertWriteEnabled();
		m_lineTypeId = id;
		ACHAR* sName;
		GetRecordPtr(id)->getName(sName);
		m_lineTypeName = sName;
	}
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::aciText
**
**  **000
**
*************************************/

Adesk::UInt16 ArxRleNetPlanWorkStyle::colorIndex() const
{
	assertReadEnabled();
	return m_colorIndex;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setAciText
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setColorIndex(Adesk::UInt16 newValue)
{
	assertWriteEnabled();
	m_colorIndex = newValue;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::lineScale
**
**  **000
**
*************************************/

double ArxRleNetPlanWorkStyle::lineScale() const
{
	assertReadEnabled();
	return m_lineScale;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setLineScale
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setLineScale(double newValue)
{
	assertWriteEnabled();
	m_lineScale = newValue;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::radiusBegin
**
**  **000
**
*************************************/

double ArxRleNetPlanWorkStyle::radiusBegin() const
{
	assertReadEnabled();
	return m_radiusBegin;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setRadiusBegin
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setRadiusBegin(double newValue)
{
	assertWriteEnabled();
	m_radiusBegin = newValue;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::radiusEnd
**
**  **000
**
*************************************/

double ArxRleNetPlanWorkStyle::radiusEnd() const
{
	assertReadEnabled();
	return m_radiusEnd;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setRadiusEnd
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setRadiusEnd(double newValue)
{
	assertWriteEnabled();
	m_radiusEnd = newValue;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::lenArrow
**
**  **000
**
*************************************/

double ArxRleNetPlanWorkStyle::lenArrow() const
{
	assertReadEnabled();
	return m_lenArrow;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setLenArrow
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setLenArrow(double newValue)
{
	assertWriteEnabled();
	m_lenArrow = newValue;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::sizeLabel
**
**  **000
**
*************************************/

double ArxRleNetPlanWorkStyle::sizeLabel() const
{
	assertReadEnabled();
	return m_sizeLabel;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setSizeLabel
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setSizeLabel(double newValue)
{
	assertWriteEnabled();
	m_sizeLabel = newValue;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::sizeNode
**
**  **000
**
*************************************/

double ArxRleNetPlanWorkStyle::sizeNode() const
{
	assertReadEnabled();
	return m_sizeNode;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setSizeNode
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setSizeNode(double newValue)
{
	assertWriteEnabled();
	m_sizeNode = newValue;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::dayGap
**
**  **000
**
*************************************/

double ArxRleNetPlanWorkStyle::dayGap() const
{
	assertReadEnabled();
	return m_dayGap;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setDayGap
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setDayGap(double newValue)
{
	assertWriteEnabled();
	m_dayGap = newValue;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::lineGap
**
**  **000
**
*************************************/

double ArxRleNetPlanWorkStyle::lineGap() const
{
	assertReadEnabled();
	return m_lineGap;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setLineGap
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setLineGap(double newValue)
{
	assertWriteEnabled();
	m_lineGap = newValue;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::drawLabelBegin
**
**  **000
**
*************************************/

bool ArxRleNetPlanWorkStyle::drawLabelBegin() const
{
	assertReadEnabled();
	return m_drawLabelBegin;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setDrawLabelBegin
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setDrawLabelBegin(bool newValue)
{
	assertWriteEnabled();
	m_drawLabelBegin = newValue;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::drawLabelEnd
**
**  **000
**
*************************************/

bool ArxRleNetPlanWorkStyle::drawLabelEnd() const
{
	assertReadEnabled();
	return m_drawLabelEnd;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setDrawLabelEnd
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setDrawLabelEnd(bool newValue)
{
	assertWriteEnabled();
	m_drawLabelEnd = newValue;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::drawLabelUp
**
**  **000
**
*************************************/

bool ArxRleNetPlanWorkStyle::drawLabelUp() const
{
	assertReadEnabled();
	return m_drawLabelUp;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setDrawLabelUp
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setDrawLabelUp(bool newValue)
{
	assertWriteEnabled();
	m_drawLabelUp = newValue;
}


/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::drawLabelDown
**
**  **000
**
*************************************/

bool ArxRleNetPlanWorkStyle::drawLabelDown() const
{
	assertReadEnabled();
	return m_drawLabelDown;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::setDrawLabelDown
**
**  **000
**
*************************************/

void ArxRleNetPlanWorkStyle::setDrawLabelDown(bool newValue)
{
	assertWriteEnabled();
	m_drawLabelDown = newValue;
}


/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::dwgInFields
**
**  **000
**
*************************************/

Acad::ErrorStatus ArxRleNetPlanWorkStyle::dwgInFields(AcDbDwgFiler* filer)
{
	assertWriteEnabled ();
    Acad::ErrorStatus es;
    if((es = ArxRleDbDictRecord::dwgInFields(filer)) != Acad::eOk)
        return es;

    Adesk::Int16 version;
    filer->readInt16(&version);
    if(version > m_version)
        return Acad::eMakeMeProxy;

	if(filer->filerType() == AcDb::kWblockCloneFiler)
	{
		AcDbHardPointerId Id;
		filer->readHardPointerId(&Id);
	}

	filer->readString(m_styleName);
	filer->readString(m_layerName);
	filer->readString(m_textStyleName);
	filer->readString(m_lineTypeName);
	filer->readUInt16(&m_colorIndex);
	filer->readDouble(&m_lineScale);
	filer->readDouble(&m_radiusBegin);
	filer->readDouble(&m_radiusEnd);
	filer->readDouble(&m_lenArrow);
	filer->readDouble(&m_sizeLabel);
	filer->readDouble(&m_sizeNode);
	filer->readDouble(&m_dayGap);
	filer->readDouble(&m_lineGap);
	filer->readBool(&m_drawLabelBegin);
	filer->readBool(&m_drawLabelEnd);
	filer->readBool(&m_drawLabelUp);
	filer->readBool(&m_drawLabelDown);
	filer->readItem(&m_layerId);
	filer->readItem(&m_textStyleId);
	filer->readItem(&m_lineTypeId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::dwgOutFields
**
**  **000
**
*************************************/

Acad::ErrorStatus ArxRleNetPlanWorkStyle::dwgOutFields(AcDbDwgFiler* filer) const
{
	assertReadEnabled ();
    Acad::ErrorStatus es;
    if((es = ArxRleDbDictRecord::dwgOutFields(filer)) != Acad::eOk)
        return es;

	if ((es =filer->writeInt16 (m_version)) != Acad::eOk)
		return (es);

	if (filer->filerType()==AcDb::kWblockCloneFiler)
		filer->writeHardPointerId((AcDbHardPointerId)ownerId());

	filer->writeString(m_styleName);
	filer->writeString(m_layerName);
	filer->writeString(m_textStyleName);
	filer->writeString(m_lineTypeName);
	filer->writeUInt16(m_colorIndex);
	filer->writeDouble(m_lineScale);
	filer->writeDouble(m_radiusBegin);
	filer->writeDouble(m_radiusEnd);
	filer->writeDouble(m_lenArrow);
	filer->writeDouble(m_sizeLabel);
	filer->writeDouble(m_sizeNode);
	filer->writeDouble(m_dayGap);
	filer->writeDouble(m_lineGap);
	filer->writeBool(m_drawLabelBegin);
	filer->writeBool(m_drawLabelEnd);
	filer->writeBool(m_drawLabelUp);
	filer->writeBool(m_drawLabelDown);
	filer->writeItem(m_layerId);
	filer->writeItem(m_textStyleId);
	filer->writeItem(m_lineTypeId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::dxfInFields
**
**  **000
**
*************************************/

Acad::ErrorStatus ArxRleNetPlanWorkStyle::dxfInFields(AcDbDxfFiler* filer)
{
	assertWriteEnabled ();
    Acad::ErrorStatus es;
    if(((es = ArxRleDbDictRecord::dxfInFields(filer)) != Acad::eOk) ||
        (filer->atSubclassData(this->desc()->name()) != Adesk::kTrue))
        return filer->filerStatus();

    resbuf rb;

    while ((es == Acad::eOk) && ((es = filer->readResBuf(&rb)) == Acad::eOk)) {
        if(rb.restype == kDxfName)
            setName(rb.resval.rstring);
		else if(rb.restype == kDxfLayer)
			setLayer(rb.resval.rstring);
		else if(rb.restype == kDxfTextStyle)
			setTextStyle(rb.resval.rstring);
		else if(rb.restype == kDxfLineType)
			setLineType(rb.resval.rstring);
		else if(rb.restype == kDxfColorIndex)
			setColorIndex(rb.resval.rint);
		else if(rb.restype == kDxfLineScale)
			setLineScale(rb.resval.rreal);
		else if(rb.restype == kDxfRadiusBegin)
			setRadiusBegin(rb.resval.rreal);
		else if(rb.restype == kDxfRadiusEnd)
			setRadiusEnd(rb.resval.rreal);
		else if(rb.restype == kDxfLenArrow)
			setLenArrow(rb.resval.rreal);
		else if(rb.restype == kDxfSizeLabel)
			setSizeLabel(rb.resval.rreal);
		else if(rb.restype == kDxfSizeNode)
			setSizeNode(rb.resval.rreal);
		else if(rb.restype == kDxfDayGap)
			setDayGap(rb.resval.rreal);
		else if(rb.restype == kDxfLineGap)
			setLineGap(rb.resval.rreal);
		else if(rb.restype == kDxfDrawLabelBegin)
			setDrawLabelBegin(rb.resval.rint);
		else if(rb.restype == kDxfDrawLabelEnd)
			setDrawLabelEnd(rb.resval.rint);
		else if(rb.restype == kDxfDrawLabelUp)
			setDrawLabelUp(rb.resval.rint);
		else if(rb.restype == kDxfDrawLabelDown)
			setDrawLabelDown(rb.resval.rint);
		else if(rb.restype == kDxfLayerId) {
			AcDbObjectId id;
			id.setFromOldId(rb.resval.mnLongPtr);
			setLayerId(id);
		}
		else if(rb.restype == kDxfTextStyleId) {
			AcDbObjectId id;
			id.setFromOldId(rb.resval.mnLongPtr);
			setTextStyleId(id);
		}
		else if(rb.restype == kDxfLineTypeId) {
			AcDbObjectId id;
			id.setFromOldId(rb.resval.mnLongPtr);
			setLineTypeId(id);
		}
        else {
            filer->pushBackItem();
            es = Acad::eEndOfFile;
        }
    }

    if(es != Acad::eEndOfFile)
        return Acad::eInvalidResBuf;

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::dxfOutFields
**
**  **000
**
*************************************/

Acad::ErrorStatus ArxRleNetPlanWorkStyle::dxfOutFields(AcDbDxfFiler* filer) const
{
	assertReadEnabled ();
    Acad::ErrorStatus es;
    if((es = ArxRleDbDictRecord::dxfOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(AcDb::kDxfSubclass, this->desc()->name());

    filer->writeString(kDxfName, m_styleName);
	filer->writeString(kDxfLayer, m_layerName);
	filer->writeString(kDxfTextStyle, m_textStyleName);
	filer->writeString(kDxfLineType, m_lineTypeName);
	filer->writeUInt16(kDxfColorIndex, m_colorIndex);
	filer->writeDouble(kDxfLineScale, m_lineScale);
	filer->writeDouble(kDxfRadiusBegin, m_radiusBegin);
	filer->writeDouble(kDxfRadiusEnd, m_radiusEnd);
	filer->writeDouble(kDxfLenArrow, m_lenArrow);
	filer->writeDouble(kDxfSizeLabel, m_sizeLabel);
	filer->writeDouble(kDxfSizeNode, m_sizeNode);
	filer->writeDouble(kDxfDayGap, m_dayGap);
	filer->writeDouble(kDxfDayGap, m_lineGap);
	filer->writeBool(kDxfDrawLabelBegin, m_drawLabelBegin);
	filer->writeBool(kDxfDrawLabelEnd, m_drawLabelEnd);
	filer->writeBool(kDxfDrawLabelUp, m_drawLabelUp);
	filer->writeBool(kDxfDrawLabelDown, m_drawLabelDown);
	filer->writeItem(kDxfLayerId, m_layerId);
	filer->writeItem(kDxfTextStyleId, m_textStyleId);
	filer->writeItem(kDxfLineTypeId, m_lineTypeId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::dictObjectId
**		look up the dict AcDbObjectId from dict name
**	workStyle for new objects.
**
**  **000
**
*************************************/

AcDbObjectId ArxRleNetPlanWorkStyle::dictObjectId()
{
	return ArxRleUtils::getRegularDictionaryId(ArxRleNetPlanWorkStyle::dictName(), true, ARXRLEDB);
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::getStandardStyle
**		look up the style "STANDARD" so that we can set it as the default
**	workStyle for new objects.
**
**  **000
**
*************************************/

AcDbObjectId ArxRleNetPlanWorkStyle::getStandardStyle(bool makeIfNotThere)
{
    Acad::ErrorStatus es;
    AcDbObjectId layerTextId, layerEntId, styleId;
    AcDbDictionary* dict;

    const TCHAR* standardStrPtr = acdbGetReservedString(AcDb::kStandard, false);
    ASSERT(standardStrPtr != NULL);
    
    dict = ArxRleUtils::openDictionaryForRead(m_dictName, ARXRLEDB);
    if(dict) {
        es = dict->getAt(standardStrPtr, styleId);

        if(es == Acad::eOk)
		{
			ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
			style->setName(standardStrPtr);
			style->close();
			dict->close();
			return styleId;
		}

		dict->close();
        if(makeIfNotThere == false)
            return AcDbObjectId::kNull;
    }

        // wasn't already there, so we need to make it
    dict = ArxRleUtils::openDictionaryForWrite(m_dictName, true, ARXRLEDB);
    if(dict) {
        ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
        es = dict->setAt(standardStrPtr, style, styleId);
        
        if(es == Acad::eOk) {
			style->setName(standardStrPtr);
            style->close();
			dict->close();
            return styleId;
        }
        else {
            acutPrintf(_T("\nERROR: Could not add new ArxRleNetPlanWorkStyle (%s)"), ArxRleUtils::rxErrorStr(es));
            delete style;
			dict->close();
        }
    }

    return AcDbObjectId::kNull;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::getGeneralStyle
**		look up the style "GENERAL" so that we can set it as the default
**	workStyle for new objects.
**
**  **000
**
*************************************/

AcDbObjectId ArxRleNetPlanWorkStyle::getGeneralStyle(bool makeIfNotThere, bool drawBeginNode)
{
	Acad::ErrorStatus es;
	AcDbObjectId layerTextId, layerEntId, styleId;
	AcDbDictionary* dict;

	dict = ArxRleUtils::openDictionaryForRead(m_dictName, ARXRLEDB);
	if(dict) {
		es = dict->getAt(L"General", styleId);

		if(es == Acad::eOk)
		{
			ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
			style->setName(L"General");
			style->setDrawLabelBegin(drawBeginNode);
			style->close();
			dict->close();
			return styleId;
		}

		dict->close();
		if(makeIfNotThere == false)
			return AcDbObjectId::kNull;
	}

	// wasn't already there, so we need to make it
	dict = ArxRleUtils::openDictionaryForWrite(m_dictName, true, ARXRLEDB);
	if(dict) {
		ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
		es = dict->setAt(L"General", style, styleId);

		if(es == Acad::eOk) {
			style->setName(L"General");
			style->setDrawLabelBegin(drawBeginNode);
			style->close();
			dict->close();
			return styleId;
		}
		else {
			acutPrintf(_T("\nERROR: Could not add new ArxRleNetPlanWorkStyle (%s)"), ArxRleUtils::rxErrorStr(es));
			delete style;
			dict->close();
		}
	}

	return AcDbObjectId::kNull;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::getKeyStyle
**		look up the style "KEY" so that we can set it as the default
**	workStyle for new objects.
**
**  **000
**
*************************************/

AcDbObjectId ArxRleNetPlanWorkStyle::getKeyStyle(bool makeIfNotThere, bool drawBeginNode)
{
	Acad::ErrorStatus es;
	AcDbObjectId layerTextId, layerEntId, styleId;
	AcDbDictionary* dict;

	dict = ArxRleUtils::openDictionaryForRead(m_dictName, ARXRLEDB);
	if(dict) {
		es = dict->getAt(L"Key", styleId);

		if(es == Acad::eOk)
		{
			ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
			style->setName(L"Key");
			style->setDrawLabelBegin(drawBeginNode);
			style->setColorIndex(1);
			style->close();
			dict->close();
			return styleId;
		}

		dict->close();
		if(makeIfNotThere == false)
			return AcDbObjectId::kNull;
	}

	// wasn't already there, so we need to make it
	dict = ArxRleUtils::openDictionaryForWrite(m_dictName, true, ARXRLEDB);
	if(dict) {
		ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
		es = dict->setAt(L"Key", style, styleId);

		if(es == Acad::eOk) {
			style->setName(L"Key");
			style->setDrawLabelBegin(drawBeginNode);
			style->setColorIndex(1);
			style->close();
			dict->close();
			return styleId;
		}
		else {
			acutPrintf(_T("\nERROR: Could not add new ArxRleNetPlanWorkStyle (%s)"), ArxRleUtils::rxErrorStr(es));
			delete style;
			dict->close();
		}
	}

	return AcDbObjectId::kNull;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::getVirtualStyle
**		look up the style "VIRTUAL" so that we can set it as the default
**	workStyle for new objects.
**
**  **000
**
*************************************/

AcDbObjectId ArxRleNetPlanWorkStyle::getVirtualStyle(bool makeIfNotThere)
{
	Acad::ErrorStatus es;
	AcDbObjectId layerTextId, layerEntId, styleId;
	AcDbDictionary* dict;

	dict = ArxRleUtils::openDictionaryForRead(m_dictName, ARXRLEDB);
	if(dict) {
		es = dict->getAt(L"Virtual", styleId);

		if(es == Acad::eOk)
		{
			ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
			style->setName(L"Virtual");
			style->setDrawLabelBegin(false);
			style->setDrawLabelEnd(false);
			style->setDrawLabelUp(false);
			style->setDrawLabelDown(false);
			style->setColorIndex(5);
			style->setLineScale(10);
			style->setLineType("Dashed");
			style->close();
			dict->close();
			return styleId;
		}

		dict->close();
		if(makeIfNotThere == false)
			return AcDbObjectId::kNull;
	}

	// wasn't already there, so we need to make it
	dict = ArxRleUtils::openDictionaryForWrite(m_dictName, true, ARXRLEDB);
	if(dict) {
		ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
		es = dict->setAt(L"Virtual", style, styleId);

		if(es == Acad::eOk) {
			style->setName(L"Virtual");
			style->setDrawLabelBegin(false);
			style->setDrawLabelEnd(false);
			style->setDrawLabelUp(false);
			style->setDrawLabelDown(false);
			style->setColorIndex(5);
			style->setLineScale(10);
			style->setLineType("Dashed");
			style->close();
			dict->close();
			return styleId;
		}
		else {
			acutPrintf(_T("\nERROR: Could not add new ArxRleNetPlanWorkStyle (%s)"), ArxRleUtils::rxErrorStr(es));
			delete style;
			dict->close();
		}
	}

	return AcDbObjectId::kNull;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::getFreeStyle
**		look up the style "FREE" so that we can set it as the default
**	workStyle for new objects.
**
**  **000
**
*************************************/

AcDbObjectId ArxRleNetPlanWorkStyle::getFreeStyle(bool makeIfNotThere)
{
	Acad::ErrorStatus es;
	AcDbObjectId layerTextId, layerEntId, styleId;
	AcDbDictionary* dict;

	dict = ArxRleUtils::openDictionaryForRead(m_dictName, ARXRLEDB);
	if(dict) {
		es = dict->getAt(L"Free", styleId);

		if(es == Acad::eOk)
		{
			ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
			style->setName(L"Free");
			style->setDrawLabelBegin(false);
			style->setColorIndex(3);
			style->setLineType("Zxgzag");
			style->close();
			dict->close();
			return styleId;
		}

		dict->close();
		if(makeIfNotThere == false)
			return AcDbObjectId::kNull;
	}

	// wasn't already there, so we need to make it
	dict = ArxRleUtils::openDictionaryForWrite(m_dictName, true, ARXRLEDB);
	if(dict) {
		ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
		es = dict->setAt(L"Free", style, styleId);

		if(es == Acad::eOk) {
			style->setName(L"Free");
			style->setDrawLabelBegin(false);
			style->setColorIndex(3);
			style->setLineType("Zxgzag");
			style->close();
			dict->close();
			return styleId;
		}
		else {
			acutPrintf(_T("\nERROR: Could not add new ArxRleNetPlanWorkStyle (%s)"), ArxRleUtils::rxErrorStr(es));
			delete style;
			dict->close();
		}
	}

	return AcDbObjectId::kNull;
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::getWorkStyle
**
**  **000
**
*************************************/

bool ArxRleNetPlanWorkStyle::getWorkStyle(AcDbObjectId& wsId)
{
	// try to get the standard style, which will hardwire it if it doesn't
	// yet exist
	ArxRleNetPlanWorkStyle::getStandardStyle();
	ArxRleNetPlanWorkStyle::getGeneralStyle(true,false);
	ArxRleNetPlanWorkStyle::getKeyStyle();
	ArxRleNetPlanWorkStyle::getVirtualStyle();
	ArxRleNetPlanWorkStyle::getFreeStyle();

	ArxRleSdStrObjIdList workStyles;
	AcDbObjectId workStyleDictId = ArxRleUtils::getRegularDictionaryId(ArxRleNetPlanWorkStyle::dictName(), true, ARXRLEDB);

	ArxRleUtils::collectDictionaryEntryNames(workStyleDictId, workStyles, ArxRleNetPlanWorkStyle::desc());

	if(workStyles.Count() == 0) {
		ArxRleUtils::alertBox(_T("There are no NetPlan Work Styles to choose from."));
		return false;
	}

	ArxRleUiDlgGenericDefId dbox(acedGetAcadDwgView(),
		workStyles, wsId, false);
	dbox.setDboxTitle(_T("NetPlan Work Styles"));

	if(dbox.DoModal() == IDOK) {
		wsId = dbox.getSelectedId();
		return true;
	}

	return false;
}

/****************************************************************************
**
**  ArxRleNetPlanWorkStyle::getStandardStyle
**		look up the style AcDbObjectId for style name
**	workStyle for new objects.
**
**  **000
**
*************************************/

AcDbObjectId ArxRleNetPlanWorkStyle::getWorkStyle(ArxRleString wsName)
{
	Acad::ErrorStatus es;
	AcDbObjectId styleId;
	AcDbDictionary* dict = ArxRleUtils::openDictionaryForRead(m_dictName, ARXRLEDB);

	if(dict) {
		es = dict->getAt(wsName, styleId);
		dict->close();

		if(es == Acad::eOk)
			return styleId;
	}

	// wasn't already there, so we need to make it
	dict = ArxRleUtils::openDictionaryForWrite(m_dictName, true, ARXRLEDB);
	if(dict) {
		ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
		es = dict->setAt(wsName, style, styleId);
		if(es == Acad::eOk) {
			style->setName(wsName);
			style->close();
			dict->close();
			return styleId;
		}
		else {
			acutPrintf(_T("\nERROR: Could not add new ArxRleNetPlanWorkStyle (%s)"), ArxRleUtils::rxErrorStr(es));
			delete style;
			dict->close();
		}
	}

	return AcDbObjectId::kNull;
}