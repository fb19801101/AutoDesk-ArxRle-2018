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

#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRlePropertyData.h"
#include "DbEntity\ArxRleEntityClass.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleApply.h"
#include "AcadUtils\ArxRleSmartPtr.h"
#include "AcadUtils\ArxRleSelSet.h"
#include "AcadUtils\ArxRleRbList.h"
#include "NetPlan\ArxRleNetPlanWork.h"
#include "NetPlan\ArxRleNetPlanWorkStyle.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemListYesNo

BEGIN_LIST_ITEM_DATA_TYPE(ArxRlePropertyItemListYesNo)
	LPCTSTR_STRING_ITEM_DATA(_T("No")),
	LPCTSTR_STRING_ITEM_DATA(_T("Yes"))
END_LIST_ITEM_DATA_TYPE(ArxRlePropertyItemListYesNo)

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemListColor

BEGIN_LIST_ITEM_DATA_TYPE(ArxRlePropertyItemListColor)
	LPCTSTR_STRING_ITEM_DATA(_T("Red (255,0,0)")),
	LPCTSTR_STRING_ITEM_DATA(_T("Yewllow (0,255,0)")),
	LPCTSTR_STRING_ITEM_DATA(_T("Green (0,0,255)")),
	LPCTSTR_STRING_ITEM_DATA(_T("Blue (255,255,0)")),
END_LIST_ITEM_DATA_TYPE(ArxRlePropertyItemListColor)

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyData

ArxRlePropertyData::ArxRlePropertyData()
:m_styleName(_T("Standard")),   
m_layerName(_T("NetPlan")),
m_textStyleName(_T("NetPlan")),
m_lineTypeName(_T("Continuous")),
m_colorIndex(4),
m_radiusBegin(2.5),
m_radiusEnd(2.5),
m_lenArrow(1.5),
m_sizeLabel(2),
m_sizeNode(2),
m_dayGap(1),
m_lineGap(4),
m_drawLabelBegin(true),
m_drawLabelEnd(true),
m_drawLabelUp(true),
m_drawLabelDown(true)
{
	m_layer = _T("0");
	m_color = _T("RGB(255,255,255)");
	m_lineType = _T("Continues");
	m_lineSalse = 1;
	m_lineWeight = -1;
	m_wsName = _T("Standard");
}

ArxRlePropertyData::~ArxRlePropertyData()
{
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleWorkPropertyItemManager

ArxRleWorkPropertyItemManager::ArxRleWorkPropertyItemManager()
{	
	BEGIN_PROPERTY_TAB(_T("常规属性"), true)
		PROPERTY_ITEM(ID_PD_GENERAL_LAYER, ArxRlePropertyItemString, _T("图层"), true)
		PROPERTY_ITEM(ID_PD_GENERAL_COLOR, ArxRlePropertyItemString, _T("颜色"), true)
		PROPERTY_ITEM(ID_PD_GENERAL_LTYPE, ArxRlePropertyItemString, _T("线型"), true)
		PROPERTY_ITEM(ID_PD_GENERAL_LSCALE, ArxRlePropertyItemString, _T("比例"), true)
		PROPERTY_ITEM(ID_PD_GENERAL_LWEIGHT, ArxRlePropertyItemString, _T("线宽"), true)
	END_PROPERTY_TAB()

	BEGIN_PROPERTY_TAB(_T("基点坐标"), true)
		PROPERTY_ITEM(ID_PD_POINT_X1, ArxRlePropertyItemString, _T("起点 X:"), true)
		PROPERTY_ITEM(ID_PD_POINT_Y1, ArxRlePropertyItemString, _T("起点 Y:"), true)
		PROPERTY_ITEM(ID_PD_POINT_Z1, ArxRlePropertyItemString, _T("起点 Z:"), true)
		PROPERTY_ITEM(ID_PD_POINT_X2, ArxRlePropertyItemString, _T("终点 X:"), true)
		PROPERTY_ITEM(ID_PD_POINT_Y2, ArxRlePropertyItemString, _T("终点 Y:"), true)
		PROPERTY_ITEM(ID_PD_POINT_Z2, ArxRlePropertyItemString, _T("终点 Z:"), true)
		PROPERTY_ITEM(ID_PD_BIND_WORK, ArxRlePropertyItemListYesNo, _T("工序参数"), true)
	END_PROPERTY_TAB()

	BEGIN_PROPERTY_TAB(_T("工序参数"), false)
		PROPERTY_ITEM(ID_PD_WORK_BEGIN, ArxRlePropertyItemString, _T("起点编号"), true)
		PROPERTY_ITEM(ID_PD_WORK_END, ArxRlePropertyItemString, _T("终点标号"), true)
		PROPERTY_ITEM(ID_PD_WORK_UP, ArxRlePropertyItemString, _T("工序名称"), true)
		PROPERTY_ITEM(ID_PD_WORK_DOWN, ArxRlePropertyItemString, _T("工序历时"), true)
		PROPERTY_ITEM(ID_PD_WORK_STYLE, ArxRlePropertyItemString, _T("工序样式"), true)
		PROPERTY_ITEM(ID_PD_WORK_DES, ArxRlePropertyItemString, _T("资源备注"), true)
		PROPERTY_ITEM(ID_PD_BIND_STYLE, ArxRlePropertyItemListYesNo, _T("样式参数"), true)
	END_PROPERTY_TAB()

	BEGIN_PROPERTY_TAB(_T("工序样式"), false)
		PROPERTY_ITEM(ID_PD_STYLE_NAME, ArxRlePropertyItemString, _T("样式名称"), true)
		PROPERTY_ITEM(ID_PD_STYLE_LAYER, ArxRlePropertyItemString, _T("图层名称"), true)
		PROPERTY_ITEM(ID_PD_STYLE_FONT, ArxRlePropertyItemString, _T("字体样式"), true)
		PROPERTY_ITEM(ID_PD_STYLE_LTYPE, ArxRlePropertyItemString, _T("线型样式"), true)
		PROPERTY_ITEM(ID_PD_STYLE_COLOR, ArxRlePropertyItemListColor, _T("颜色索引"), true)
		PROPERTY_ITEM(ID_PD_STYLE_RBEGIN, ArxRlePropertyItemString, _T("起点半径"), true)
		PROPERTY_ITEM(ID_PD_STYLE_REND, ArxRlePropertyItemString, _T("终点半径"), true)
		PROPERTY_ITEM(ID_PD_STYLE_ARROW, ArxRlePropertyItemString, _T("箭头大小"), true)
		PROPERTY_ITEM(ID_PD_STYLE_SWORK, ArxRlePropertyItemString, _T("工序字高"), true)
		PROPERTY_ITEM(ID_PD_STYLE_SNODE, ArxRlePropertyItemString, _T("节点字高"), true)
		PROPERTY_ITEM(ID_PD_STYLE_DGAP, ArxRlePropertyItemString, _T("日历间隔"), true)
		PROPERTY_ITEM(ID_PD_STYLE_LGAP, ArxRlePropertyItemString, _T("日线间隔"), true)
		PROPERTY_ITEM(ID_PD_STYLE_BLBEGIN, ArxRlePropertyItemListYesNo, _T("绘制开始节点"), true)
		PROPERTY_ITEM(ID_PD_STYLE_BLEND, ArxRlePropertyItemListYesNo, _T("绘制终止节点"), true)
		PROPERTY_ITEM(ID_PD_STYLE_BLUP, ArxRlePropertyItemListYesNo, _T("绘制工序名称"), true)
		PROPERTY_ITEM(ID_PD_STYLE_BLDOWN, ArxRlePropertyItemListYesNo, _T("绘制工序时间"), true)
	END_PROPERTY_TAB()
}

ArxRleWorkPropertyItemManager::~ArxRleWorkPropertyItemManager()
{
}

bool ArxRleWorkPropertyItemManager::SetData(const CObject* pData)
{
	const ArxRlePropertyData* data = static_cast<const ArxRlePropertyData*>(pData);

	BEGIN_ITERATE_PROPERTY_ITEMS()
		SET_ITEM_STRING(ID_PD_GENERAL_LAYER, data->m_layer.t_str())
		SET_ITEM_STRING(ID_PD_GENERAL_COLOR, data->m_color.t_str())
		SET_ITEM_STRING(ID_PD_GENERAL_LTYPE, data->m_lineType.t_str())
		SET_ITEM_INT(ID_PD_GENERAL_LSCALE, data->m_lineSalse)
		SET_ITEM_INT(ID_PD_GENERAL_LWEIGHT, data->m_lineWeight)

		SET_ITEM_DOUBLE(ID_PD_POINT_X1, data->m_ptBegin.x)
		SET_ITEM_DOUBLE(ID_PD_POINT_Y1, data->m_ptBegin.y)
		SET_ITEM_DOUBLE(ID_PD_POINT_Z1, data->m_ptBegin.z)
		SET_ITEM_DOUBLE(ID_PD_POINT_X2, data->m_ptEnd.x)
		SET_ITEM_DOUBLE(ID_PD_POINT_Y2, data->m_ptEnd.y)
		SET_ITEM_DOUBLE(ID_PD_POINT_Z2, data->m_ptEnd.z)

		SET_ITEM_LIST(ID_PD_BIND_WORK, data->m_isBindWork)

		SET_ITEM_STRING(ID_PD_WORK_BEGIN, data->m_labelBegin.t_str())
		SET_ITEM_STRING(ID_PD_WORK_END, data->m_labelEnd.t_str())
		SET_ITEM_STRING(ID_PD_WORK_UP, data->m_labelUp.t_str())
		SET_ITEM_STRING(ID_PD_WORK_DOWN, data->m_labelDown.t_str())
		SET_ITEM_STRING(ID_PD_WORK_STYLE, data->m_wsName.t_str())
		SET_ITEM_STRING(ID_PD_WORK_DES, data->m_resDes.t_str())

		SET_ITEM_LIST(ID_PD_BIND_STYLE, data->m_isBindStyle)

		SET_ITEM_STRING(ID_PD_STYLE_NAME, data->m_styleName.t_str())
		SET_ITEM_STRING(ID_PD_STYLE_LAYER, data->m_layerName.t_str())
		SET_ITEM_STRING(ID_PD_STYLE_FONT, data->m_textStyleName.t_str())
		SET_ITEM_STRING(ID_PD_STYLE_LTYPE, data->m_lineTypeName.t_str())
		SET_ITEM_LIST(ID_PD_STYLE_COLOR, data->m_colorIndex)
		SET_ITEM_DOUBLE(ID_PD_STYLE_RBEGIN, data->m_radiusBegin)
		SET_ITEM_DOUBLE(ID_PD_STYLE_REND, data->m_radiusEnd)
		SET_ITEM_DOUBLE(ID_PD_STYLE_ARROW, data->m_lenArrow)
		SET_ITEM_DOUBLE(ID_PD_STYLE_SWORK, data->m_sizeLabel)
		SET_ITEM_DOUBLE(ID_PD_STYLE_SNODE, data->m_sizeNode)
		SET_ITEM_DOUBLE(ID_PD_STYLE_DGAP, data->m_dayGap)
		SET_ITEM_DOUBLE(ID_PD_STYLE_LGAP, data->m_lineGap)
		SET_ITEM_LIST(ID_PD_STYLE_BLBEGIN, data->m_drawLabelBegin)
		SET_ITEM_LIST(ID_PD_STYLE_BLEND, data->m_drawLabelEnd)
		SET_ITEM_LIST(ID_PD_STYLE_BLUP, data->m_drawLabelUp)
		SET_ITEM_LIST(ID_PD_STYLE_BLDOWN, data->m_drawLabelDown)
	END_ITERATE_PROPERTY_ITEMS()

	return true;
}

bool ArxRleWorkPropertyItemManager::GetData(CObject* pData) const
{
	ArxRlePropertyData* data = static_cast<ArxRlePropertyData*>(pData);

	BEGIN_ITERATE_PROPERTY_ITEMS()
		GET_ITEM_STRING(ID_PD_GENERAL_LAYER, data->m_layer.t_str())
		GET_ITEM_STRING(ID_PD_GENERAL_COLOR, data->m_color.t_str())
		GET_ITEM_STRING(ID_PD_GENERAL_LTYPE, data->m_lineType.t_str())
		GET_ITEM_INT(ID_PD_GENERAL_LSCALE, data->m_lineSalse)
		GET_ITEM_INT(ID_PD_GENERAL_LWEIGHT, data->m_lineWeight)

		GET_ITEM_DOUBLE(ID_PD_POINT_X1, data->m_ptBegin.x)
		GET_ITEM_DOUBLE(ID_PD_POINT_Y1, data->m_ptBegin.y)
		GET_ITEM_DOUBLE(ID_PD_POINT_Z1, data->m_ptBegin.z)
		GET_ITEM_DOUBLE(ID_PD_POINT_X2, data->m_ptEnd.x)
		GET_ITEM_DOUBLE(ID_PD_POINT_Y2, data->m_ptEnd.y)
		GET_ITEM_DOUBLE(ID_PD_POINT_Z2, data->m_ptEnd.z)

		GET_ITEM_LIST(ID_PD_BIND_WORK, data->m_isBindWork)

		GET_ITEM_STRING(ID_PD_WORK_BEGIN, data->m_labelBegin.t_str())
		GET_ITEM_STRING(ID_PD_WORK_END, data->m_labelEnd.t_str())
		GET_ITEM_STRING(ID_PD_WORK_UP, data->m_labelUp.t_str())
		GET_ITEM_STRING(ID_PD_WORK_DOWN, data->m_labelDown.t_str())
		GET_ITEM_STRING(ID_PD_WORK_STYLE, data->m_wsName.t_str())
		GET_ITEM_STRING(ID_PD_WORK_DES, data->m_resDes.t_str())

		GET_ITEM_LIST(ID_PD_BIND_STYLE, data->m_isBindStyle)

		GET_ITEM_STRING(ID_PD_STYLE_NAME, data->m_styleName.t_str())
		GET_ITEM_STRING(ID_PD_STYLE_LAYER, data->m_layerName.t_str())
		GET_ITEM_STRING(ID_PD_STYLE_FONT, data->m_textStyleName.t_str())
		GET_ITEM_STRING(ID_PD_STYLE_LTYPE, data->m_lineTypeName.t_str())
		GET_ITEM_LIST(ID_PD_STYLE_COLOR, data->m_colorIndex)
		GET_ITEM_DOUBLE(ID_PD_STYLE_RBEGIN, data->m_radiusBegin)
		GET_ITEM_DOUBLE(ID_PD_STYLE_REND, data->m_radiusEnd)
		GET_ITEM_DOUBLE(ID_PD_STYLE_ARROW, data->m_lenArrow)
		GET_ITEM_DOUBLE(ID_PD_STYLE_SWORK, data->m_sizeLabel)
		GET_ITEM_DOUBLE(ID_PD_STYLE_SNODE, data->m_sizeNode)
		GET_ITEM_DOUBLE(ID_PD_STYLE_DGAP, data->m_dayGap)
		GET_ITEM_DOUBLE(ID_PD_STYLE_LGAP, data->m_lineGap)
		GET_ITEM_LIST(ID_PD_STYLE_BLBEGIN, data->m_drawLabelBegin)
		GET_ITEM_LIST(ID_PD_STYLE_BLEND, data->m_drawLabelEnd)
		GET_ITEM_LIST(ID_PD_STYLE_BLUP, data->m_drawLabelUp)
		GET_ITEM_LIST(ID_PD_STYLE_BLDOWN, data->m_drawLabelDown)
	END_ITERATE_PROPERTY_ITEMS()

	return true;
}

void ArxRleWorkPropertyItemManager::OnDataChanged(ArxRlePropertyItem* pPropertyItem, ArxRlePropertyListBox* pWndPropertyListCtrl, int nIndex)
{
	bool bDoChecking = false;

	switch(pPropertyItem->GetPropertyID())
	{
	case ID_PD_BIND_WORK:
		{
			// Yes/No item
			bool bEnableTabs;
			static_cast<ArxRlePropertyItemList*>(pPropertyItem)->GetData(bEnableTabs);

			// Enable/Disable tabs 1
			ArxRlePropertyItemCategory* pPropertyItemTab = GetCategoryTab(1);

			if(pPropertyItemTab->SetEnabled(bEnableTabs))
				bDoChecking = true;

			// Enable/Disable tabs 2
			int bBindWork;
			static_cast<ArxRlePropertyItemList*>(pPropertyItemTab->GetPropertyItem(ID_PD_BIND_WORK))->GetData(bBindWork);

			pPropertyItemTab = GetCategoryTab(2);

			if(pPropertyItemTab->SetEnabled(bEnableTabs && bBindWork))
				bDoChecking = true;
		}
		break;
	case ID_PD_BIND_STYLE:
		{
			// Enumerate item
			int nItemType;
			static_cast<ArxRlePropertyItemList*>(pPropertyItem)->GetData(nItemType);

			// For items 4 (Form) and 5 (Macro) disable tab #2, for others enable			
			ArxRlePropertyItemCategory* pPropertyItemTab = GetCategoryTab(3);
			bDoChecking = pPropertyItemTab->SetEnabled(nItemType < 4);
		}
		break;
	default:
		return;
	}

	if(bDoChecking) CheckState(pWndPropertyListCtrl, nIndex, pPropertyItem->GetPropertyID());
}

void ArxRleWorkPropertyItemManager::SetObjId(AcDbObjectId& objId)
{
	m_objId = objId;
}

AcDbObjectId ArxRleWorkPropertyItemManager::GetObjId() const
{
	return m_objId;
}

void ArxRleWorkPropertyItemManager::UpdateEntity()
{
	ArxRlePropertyData* data = new ArxRlePropertyData;
	GetData(data);

	AcDbEntity* ent;
	Acad::ErrorStatus es = OpenEntity(ent, m_objId, AcDb::kForWrite);		// might have passed in erased ones
	if(es == Acad::eOk) {
		ArxRleString layer(data->m_layer);
		ent->setLayer(layer.w_ptr());
		CStringArray strArray;
		CString str = data->m_color;
		str = str.Mid(4,str.GetLength()-5);
		ParseSubStrByDelimiter(str,strArray,',');
		int r = _tstoi(strArray[0]);
		int g = _tstoi(strArray[1]);
		int b = _tstoi(strArray[2]);
		COLORREF clr = RGB(r,g,b);
		ent->setColor(RefColorToAcCmColor(clr));
		ArxRleString lt(data->m_lineType);
		ent->setLinetype(lt);
		ent->setLinetypeScale(data->m_lineSalse);
		ent->setLineWeight((AcDb::LineWeight)data->m_lineWeight);

		if(ent->isKindOf(ArxRleNetPlanWork::desc())) {
			ArxRleNetPlanWork* pNetPlanWork = ArxRleNetPlanWork::cast(ent);

			pNetPlanWork->setPointBegin(data->m_ptBegin);
			pNetPlanWork->setPointEnd(data->m_ptEnd);

			pNetPlanWork->setLabelBegin(data->m_labelBegin);
			pNetPlanWork->setLabelEnd(data->m_labelEnd);
			pNetPlanWork->setLabelUp(data->m_labelUp);
			pNetPlanWork->setLabelDown(data->m_labelDown);
			pNetPlanWork->setWorkDes(data->m_resDes);

			ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
			Acad::ErrorStatus es = acdbOpenObject(style, pNetPlanWork->getWorkStyleId(), AcDb::kForWrite);
			if(es != Acad::eOk) {
				ArxRleUtils::rxErrorMsg(es);
				delete style;
				return;
			}
			style->setName(data->m_styleName);
			style->setLayer(data->m_layerName);
			style->setTextStyle(data->m_textStyleName);
			style->setLineType(data->m_lineTypeName);
			style->setColorIndex(data->m_colorIndex);
			style->setRadiusBegin(data->m_radiusBegin);
			style->setRadiusEnd(data->m_radiusEnd);
			style->setLenArrow(data->m_lenArrow);
			style->setSizeLabel(data->m_sizeLabel);
			style->setSizeNode(data->m_sizeNode);
			style->setDayGap(data->m_dayGap);
			style->setLineGap(data->m_lineGap);
			style->setDrawLabelBegin(data->m_drawLabelBegin);
			style->setDrawLabelEnd(data->m_drawLabelEnd);
			style->setDrawLabelUp(data->m_drawLabelUp);
			style->setDrawLabelDown(data->m_drawLabelDown);
			style->close();
		}

		CloseEntity(ent);
	}
}

void ArxRleWorkPropertyItemManager::UpdateList()
{
	ArxRlePropertyData* data = new ArxRlePropertyData;

	AcDbEntity* ent;
	Acad::ErrorStatus es = OpenEntity(ent, m_objId, AcDb::kForWrite);		// might have passed in erased ones
	if(es == Acad::eOk) {
		data->m_layer = ent->layer();
		CString str;
		COLORREF ref = AcCmColorToRefColor(ent->color(), ent->layerId());
		str.Format(L"RGB(%d,%d,%d)",GetRValue(ref),GetGValue(ref),GetBValue(ref));
		data->m_color = str;
		data->m_lineType = ent->linetype();
		data->m_lineSalse = ent->linetypeScale();
		data->m_lineWeight = ent->lineWeight();
		if(ent->isKindOf(ArxRleNetPlanWork::desc())) {
			ArxRleNetPlanWork* pNetPlanWork = ArxRleNetPlanWork::cast(ent);
			data->m_ptBegin = pNetPlanWork->getPointBegin();
			data->m_ptEnd = pNetPlanWork->getPointEnd();
			data->m_labelBegin = pNetPlanWork->getLabelBegin();
			data->m_labelEnd = pNetPlanWork->getLabelEnd();
			data->m_labelUp = pNetPlanWork->getLabelUp();
			data->m_labelDown = pNetPlanWork->getLabelDown();
			data->m_resDes = pNetPlanWork->getWorkDes();
			ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
			Acad::ErrorStatus es = acdbOpenObject(style, pNetPlanWork->getWorkStyleId(), AcDb::kForWrite);
			if(es != Acad::eOk) {
				ArxRleUtils::rxErrorMsg(es);
				delete style;
				return;
			}
			data->m_styleName = style->name();
			data->m_layerName = style->layer();
			data->m_textStyleName = style->textStyle();
			data->m_lineTypeName = style->lineType();
			data->m_colorIndex = style->colorIndex();
			data->m_radiusBegin = style->radiusBegin();
			data->m_radiusEnd = style->radiusEnd();
			data->m_lenArrow = style->lenArrow();
			data->m_sizeLabel = style->sizeLabel();
			data->m_sizeNode = style->sizeNode();
			data->m_dayGap = style->dayGap();
			data->m_lineGap = style->lineGap();
			data->m_drawLabelBegin = style->drawLabelBegin();
			data->m_drawLabelEnd = style->drawLabelEnd();
			data->m_drawLabelUp = style->drawLabelUp();
			data->m_drawLabelDown = style->drawLabelDown();
			style->close();
		}
	}

	SetData(data);
}