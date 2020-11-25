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

#ifndef ARXRLE_PROPERTY_DATA_NETPLAN_H
#define ARXRLE_PROPERTY_DATA_NETPLAN_H


#include "ArxRlePropertyListBox.h"
#include "DbEntity/ArxRleString.h"
#include "DbEntity/ArxRleEntityClass.h"

#define ID_PD_GENERAL_LAYER		1
#define ID_PD_GENERAL_COLOR		2
#define ID_PD_GENERAL_LTYPE		3
#define ID_PD_GENERAL_LSCALE	4
#define ID_PD_GENERAL_LWEIGHT   5

#define ID_PD_POINT_X1		    6
#define ID_PD_POINT_Y1		    7
#define ID_PD_POINT_Z1		    8
#define ID_PD_POINT_X2		    9
#define ID_PD_POINT_Y2		    10
#define ID_PD_POINT_Z2          11

#define ID_PD_BIND_WORK         12

#define ID_PD_WORK_BEGIN		13
#define ID_PD_WORK_END		    14
#define ID_PD_WORK_UP		    15
#define ID_PD_WORK_DOWN		    16
#define ID_PD_WORK_STYLE		17
#define ID_PD_WORK_DES		    18

#define ID_PD_BIND_STYLE	    19

#define ID_PD_STYLE_NAME		20
#define ID_PD_STYLE_LAYER		21
#define ID_PD_STYLE_FONT	    22
#define ID_PD_STYLE_LTYPE		23
#define ID_PD_STYLE_COLOR		24
#define ID_PD_STYLE_RBEGIN      25
#define ID_PD_STYLE_REND        26
#define ID_PD_STYLE_ARROW       27
#define ID_PD_STYLE_SWORK       28
#define ID_PD_STYLE_SNODE       29
#define ID_PD_STYLE_DGAP        30
#define ID_PD_STYLE_LGAP        31
#define ID_PD_STYLE_BLBEGIN     32
#define ID_PD_STYLE_BLEND       33
#define ID_PD_STYLE_BLUP        34
#define ID_PD_STYLE_BLDOWN      35

class ArxRleWorkPropertyItemManager;

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyData

class ArxRlePropertyData : public CObject
{
	ArxRlePropertyData(const ArxRlePropertyData& d);
	ArxRlePropertyData& operator=(const ArxRlePropertyData& d);

public:
	ArxRlePropertyData();
	~ArxRlePropertyData();

	// Data
private:
	ArxRleString m_layer;
	ArxRleString m_color;
	ArxRleString m_lineType;
	int m_lineSalse;
	int m_lineWeight; 

	CPt3d m_ptBegin, m_ptEnd;

	ArxRleString    m_labelBegin;
	ArxRleString    m_labelEnd;
	ArxRleString    m_labelUp;
	ArxRleString    m_labelDown;
	ArxRleString    m_wsName;
	ArxRleString    m_resDes;

	bool m_isBindWork;
	bool m_isBindStyle;

	ArxRleString  m_styleName;
	ArxRleString  m_layerName;
	ArxRleString  m_textStyleName;
	ArxRleString  m_lineTypeName;
	int           m_colorIndex;
	double        m_radiusBegin;
	double        m_radiusEnd;
	double        m_lenArrow;
	double        m_sizeLabel;
	double        m_sizeNode;
	double        m_dayGap;
	double        m_lineGap;
	bool          m_drawLabelBegin;
	bool          m_drawLabelEnd;
	bool          m_drawLabelUp;
	bool          m_drawLabelDown;

	friend ArxRleWorkPropertyItemManager;
};

/////////////////////////////////////////////////////////////////////////////
// ArxRleWorkPropertyItemManager

class ArxRleWorkPropertyItemManager : public ArxRlePropertyItemManagerAdaptable
{
	ArxRleWorkPropertyItemManager(const ArxRleWorkPropertyItemManager& d);
	ArxRleWorkPropertyItemManager& operator=(const ArxRleWorkPropertyItemManager& d);

public:
	ArxRleWorkPropertyItemManager();
	~ArxRleWorkPropertyItemManager();

	bool SetData(const CObject* pData);
	bool GetData(CObject* pData) const;

	void OnDataChanged(ArxRlePropertyItem* pPropertyItem, ArxRlePropertyListBox* pWndPropertyListCtrl, int nIndex);

	void SetObjId(AcDbObjectId& objId);
	AcDbObjectId GetObjId() const;

	void UpdateEntity();
	void UpdateList();

	AcDbObjectId m_objId;
};

#endif // ARXRLE_PROPERTY_DATA_NETPLAN_H