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

#include "ArxRleUiTdcNetPlanWorkStyle.h"
#include "ArxRleUiTdmNetPlan.h"
#include "ArxRleNetPlanWorkStyle.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleApply.h"
#include "DbEntity\ArxRleEntityClass.h"
#include "Test\ArxRleUiDlgColor.h"


// ArxRleUiTdcNetPlanWorkStyle 对话框

IMPLEMENT_DYNAMIC(ArxRleUiTdcNetPlanWorkStyle, CAcUiTabChildDialog)

ArxRleUiTdcNetPlanWorkStyle::ArxRleUiTdcNetPlanWorkStyle()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
	,m_styleName(_T("Standard"))
	,m_layerName(_T("NetPlan"))
	,m_textStyleName(_T("NetPlan"))
	,m_lineTypeName(_T("Continuous"))
	,m_colorIndex(4)
	,m_lineScale(1)
	,m_radiusBegin(1.6)
	,m_radiusEnd(1.6)
	,m_lenArrow(1.5)
	,m_sizeLabel(1.8)
	,m_sizeNode(1.8)
	,m_dayGap(1)
	,m_lineGap(4)
	,m_drawLabelBegin(true)
	,m_drawLabelEnd(true)
	,m_drawLabelUp(true)
	,m_drawLabelDown(true)
{
	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);
}

ArxRleUiTdcNetPlanWorkStyle::~ArxRleUiTdcNetPlanWorkStyle()
{
}

void ArxRleUiTdcNetPlanWorkStyle::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, ARXRLE_NETPLAN_WORKSTYLE_CB_STYLENAME, m_styleName);
	DDX_CBString(pDX, ARXRLE_NETPLAN_WORKSTYLE_CB_LAYER, m_layerName);
	DDX_CBString(pDX, ARXRLE_NETPLAN_WORKSTYLE_CB_LINETYPE, m_textStyleName);
	DDX_CBString(pDX, ARXRLE_NETPLAN_WORKSTYLE_CB_TEXTSTYLE, m_lineTypeName);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKSTYLE_EB_COLORINDEX, m_colorIndex);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKSTYLE_EB_LINESCALE, m_lineScale);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKSTYLE_EB_RADIUSBEGIN, m_radiusBegin);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKSTYLE_EB_RADIUSEND, m_radiusEnd);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKSTYLE_EB_LENARROW, m_lenArrow);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKSTYLE_EB_SIZELABEL, m_sizeLabel);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKSTYLE_EB_SIZENODE, m_sizeNode);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKSTYLE_EB_DAYGAP, m_dayGap);
	DDX_Text(pDX, ARXRLE_NETPLAN_WORKSTYLE_EB_LINEGAP, m_lineGap);
	DDX_Check(pDX, ARXRLE_NETPLAN_WORKSTYLE_CK_DRAWLABELBEGIN, m_drawLabelBegin);
	DDX_Check(pDX, ARXRLE_NETPLAN_WORKSTYLE_CK_DRAWLABELEND, m_drawLabelEnd);
	DDX_Check(pDX, ARXRLE_NETPLAN_WORKSTYLE_CK_DRAWLABELUP, m_drawLabelUp);
	DDX_Check(pDX, ARXRLE_NETPLAN_WORKSTYLE_CK_DRAWLABELDOWN, m_drawLabelDown);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKSTYLE_BN_NEW, m_btnStyleNew);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKSTYLE_BN_DELETE, m_btnStyleDel);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKSTYLE_BN_APPLY, m_btnStyleApply);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKSTYLE_BN_COLORINDEX, m_btnStyleClrIdx);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKSTYLE_CB_STYLENAME, m_cxStyleName);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKSTYLE_CB_LAYER, m_cxStyleLayer);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKSTYLE_CB_LINETYPE, m_cxStyleLineType);
	DDX_Control(pDX, ARXRLE_NETPLAN_WORKSTYLE_CB_TEXTSTYLE, m_cxStyleTextStyle);
}

BEGIN_MESSAGE_MAP(ArxRleUiTdcNetPlanWorkStyle, CAcUiTabChildDialog)
	ON_BN_CLICKED(ARXRLE_NETPLAN_WORKSTYLE_BN_NEW, OnBnClickedNetPlanPage2BnStylenew)
	ON_BN_CLICKED(ARXRLE_NETPLAN_WORKSTYLE_BN_DELETE, OnBnClickedNetPlanPage2BnStyledel)
	ON_BN_CLICKED(ARXRLE_NETPLAN_WORKSTYLE_BN_APPLY, OnBnClickedNetPlanPage2BnStyleapply)
	ON_BN_CLICKED(ARXRLE_NETPLAN_WORKSTYLE_BN_COLORINDEX, OnBnClickedNetPlanPage2BnStyleclridx)
	ON_CBN_SELCHANGE(ARXRLE_NETPLAN_WORKSTYLE_CB_STYLENAME, OnCbnSelchangeNetPlanPage2CxStylename)
END_MESSAGE_MAP()


// ArxRleUiTdcNetPlanWorkStyle 消息处理程序

BOOL ArxRleUiTdcNetPlanWorkStyle::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(m_hIcon,TRUE);
	SetIcon(m_hIcon,FALSE);

	HICON hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_SELECT);
	m_btnStyleClrIdx.SetIcon(hIcon);

	m_btnStyleApply.SetIcon(ARXRLE_ICON_CORRECT);
	m_btnStyleApply.SetBtnCursor(ARXRLE_CURSOR_STAR);
	m_btnStyleApply.SetBtnBkColor(RGB(255,255,255));
	m_btnStyleApply.SetColor(ArxRleButton::BTNST_COLOR_FG_IN,RGB(0,0,218));
	m_btnStyleApply.SetShade(ArxRleButtonXP::SHS_HARDBUMP);
	m_btnStyleApply.SetRounded(TRUE);
	m_btnStyleApply.ActivateTooltip();
	m_btnStyleApply.SetTooltipText(L"应用样式数据修改");
	m_btnStyleApply.SetSound(ARXRLE_WAVE_STONE,ArxRleApp::m_hInstance);

	AcDbDictionary *dict;
	dict = ArxRleUtils::openDictionaryForRead(ArxRleNetPlanWorkStyle::dictName(), ARXRLEDB);
	if(dict != NULL)
	{
		ArxRleApply<Dictionary> apply = ArxRleApply<Dictionary>( dict, AcDb::kForRead );
		Dictionary::Iterator* iter;
		apply.createIterator(iter);
		m_cxStyleName.Clear();
		m_objIdList.removeAll();
		if (NULL != iter)
		{
			for ( ; !iter->done(); apply.stepIterator( iter ))
			{
				Dictionary::Element* elem = apply.getElement( iter );
				if (NULL != elem)
				{
					ArxRleString sName = ((ArxRleNetPlanWorkStyle*)elem)->name();
					if(sName.GetLength() > 0)
					{
						m_cxStyleName.AddString(sName.t_str());
						m_objIdList.append(elem->objectId());
					}
					elem->close();
				}
			}
			delete iter;
		}
		dict->close();
	}

	AcDbLayerTable *pLt;
	if (Acad::eOk == ARXRLEDB->getLayerTable( pLt, AcDb::kForRead ))
	{
		ArxRleApply<LayerTable> apply = ArxRleApply<LayerTable>( pLt, AcDb::kForRead );
		LayerTable::Iterator* iter;
		apply.createIterator( iter );
		if (NULL != iter)
		{
			for ( ; !iter->done(); apply.stepIterator( iter ))
			{
				LayerTable::Element* elem = apply.getElement( iter );
				if (NULL != elem)
				{
					ACHAR* sName;
					elem->getName(sName);
					if(ArxRleString(sName).GetLength() > 0)
						m_cxStyleLayer.AddString(sName);
					elem->close();
				}
			}
			delete iter;
		}

		pLt->close();
	}

	AcDbLinetypeTable *pLtt;
	if (Acad::eOk == ARXRLEDB->getLinetypeTable( pLtt, AcDb::kForRead ))
	{
		ArxRleApply<LinetypeTable> apply = ArxRleApply<LinetypeTable>( pLtt, AcDb::kForRead );
		LinetypeTable::Iterator* iter;
		apply.createIterator( iter );
		if (NULL != iter)
		{
			for ( ; !iter->done(); apply.stepIterator( iter ))
			{
				LinetypeTable::Element* elem = apply.getElement( iter );
				if (NULL != elem)
				{
					ACHAR* sName;
					elem->getName(sName);
					if(ArxRleString(sName).GetLength() > 0)
						m_cxStyleLineType.AddString(sName);
					elem->close();
				}
			}
			delete iter;
		}

		pLtt->close();
	}

	AcDbTextStyleTable *pTs;
	if (Acad::eOk == ARXRLEDB->getTextStyleTable( pTs, AcDb::kForRead ))
	{
		ArxRleApply<TextStyleTable> apply = ArxRleApply<TextStyleTable>( pTs, AcDb::kForRead );
		TextStyleTable::Iterator* iter;
		apply.createIterator( iter );
		if (NULL != iter)
		{
			for ( ; !iter->done(); apply.stepIterator( iter ))
			{
				TextStyleTable::Element* elem = apply.getElement( iter );
				if (NULL != elem)
				{
					ACHAR* sName;
					elem->getName(sName);
					if(ArxRleString(sName).GetLength() > 0)
						m_cxStyleTextStyle.AddString(sName);
					elem->close();
				}
			}
			delete iter;
		}

		pTs->close();
	}

	m_cxStyleName.SetCurSel(0);
	ReadStyle(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ArxRleUiTdcNetPlanWorkStyle::OnBnClickedNetPlanPage2BnStylenew()
{
	// TODO: 在此添加控件通知处理程序代码
	m_cxStyleName.GetWindowText(m_styleName);
	if(m_cxStyleName.FindString(0,m_styleName) == -1 || m_cxStyleName.GetCount() == 0)
	{
		AcDbObjectId id = ArxRleNetPlanWorkStyle::getWorkStyle(m_styleName);
		m_objIdList.insertAt(0,id);
		m_cxStyleName.InsertString(0,m_styleName);
		m_cxStyleName.SetCurSel(0);

		WriteStyle(0,true);
	}
}

void ArxRleUiTdcNetPlanWorkStyle::OnBnClickedNetPlanPage2BnStyledel()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx = m_cxStyleName.GetCurSel();
	if(idx >= 0)
	{
		m_cxStyleName.DeleteString(idx);
		DeleteStyle(idx,true);
	}
}

void ArxRleUiTdcNetPlanWorkStyle::OnBnClickedNetPlanPage2BnStyleapply()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx = m_cxStyleName.GetCurSel();
	if(idx >= 0)
		WriteStyle(idx,true);
}

void ArxRleUiTdcNetPlanWorkStyle::OnBnClickedNetPlanPage2BnStyleclridx()
{
	// TODO: 在此添加控件通知处理程序代码
	ArxRleUiDlgColor clrDlg(acedGetAcadFrame());
	if(clrDlg.DoModal() == IDOK)
		m_colorIndex = clrDlg.m_currentIndex;

	UpdateData(FALSE);
}

void ArxRleUiTdcNetPlanWorkStyle::OnCbnSelchangeNetPlanPage2CxStylename()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx = m_cxStyleName.GetCurSel();
	if(idx >= 0)
		ReadStyle(idx);
}

void ArxRleUiTdcNetPlanWorkStyle::WriteStyle(int cur, bool alert)
{
	UpdateData(TRUE);
	AcDbDictionary* dict = ArxRleUtils::openDictionaryForWrite(ArxRleNetPlanWorkStyle::dictName(), true, ARXRLEDB);
	if(dict != NULL)
	{
		if(dict->has(m_objIdList[cur]))
		{
			ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
			Acad::ErrorStatus es = acdbOpenObject(style, m_objIdList[cur], AcDb::kForWrite);
			if(es == Acad::eOk)
			{
				style->setName(m_styleName);
				style->setLayer(m_layerName);
				style->setLineType(m_textStyleName);
				style->setTextStyle(m_lineTypeName);
				style->setColorIndex(m_colorIndex);
				style->setLineScale(m_lineScale);
				style->setRadiusBegin(m_radiusBegin);
				style->setRadiusEnd(m_radiusEnd);
				style->setLenArrow(m_lenArrow);
				style->setSizeLabel(m_sizeLabel);
				style->setSizeNode(m_sizeNode);
				style->setDayGap(m_dayGap);
				style->setLineGap(m_lineGap);
				style->setDrawLabelBegin(m_drawLabelBegin);
				style->setDrawLabelEnd(m_drawLabelEnd);
				style->setDrawLabelUp(m_drawLabelUp);
				style->setDrawLabelDown(m_drawLabelDown);
				style->close();

				if(alert)
				{
					CString msg;
					msg.Format(_T("Write %s NetPlan Work Style successfully!"), m_styleName);
					ArxRleUtils::alertBox(msg);
				}
			}
			else
			{
				ArxRleUtils::rxErrorMsg(es);
				delete style;
			}
		}
		else
		{
			CString msg;
			msg.Format(_T("Dictionary Not Has %s NetPlan Work Style."), m_styleName);
			ArxRleUtils::stopAlertBox(msg);
		}

		dict->close();
	}
}

void ArxRleUiTdcNetPlanWorkStyle::ReadStyle(int cur, bool alert)
{
	AcDbDictionary* dict = ArxRleUtils::openDictionaryForRead(ArxRleNetPlanWorkStyle::dictName(), ARXRLEDB);
	if(dict != NULL)
	{
		if(dict->has(m_objIdList[cur]))
		{
			ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
			Acad::ErrorStatus es = acdbOpenObject(style, m_objIdList[cur], AcDb::kForRead);

			if(es == Acad::eOk)
			{
				m_styleName = style->name().t_str();
				m_layerName = style->layer().t_str();
				m_textStyleName = style->lineType().t_str();
				m_lineTypeName = style->textStyle().t_str();
				m_colorIndex = style->colorIndex();
				m_lineScale = style->lineScale();
				m_radiusBegin = style->radiusBegin();
				m_radiusEnd = style->radiusEnd();
				m_lenArrow = style->lenArrow();
				m_sizeLabel = style->sizeLabel();
				m_sizeNode = style->sizeNode();
				m_dayGap = style->dayGap();
				m_lineGap = style->lineGap();
				m_drawLabelBegin = style->drawLabelBegin();
				m_drawLabelEnd = style->drawLabelEnd();
				m_drawLabelUp = style->drawLabelUp();
				m_drawLabelDown = style->drawLabelDown();
				style->close();

				if(alert)
				{
					CString msg;
					msg.Format(_T("Read %s NetPlan Work Style successfully!"), m_styleName);
					ArxRleUtils::alertBox(msg);
				}
			}
			else
			{
				ArxRleUtils::rxErrorMsg(es);
				delete style;
			}
		}
		else
		{
			CString msg;
			msg.Format(_T("Dictionary Not Has %s NetPlan Work Style."), m_styleName);
			ArxRleUtils::stopAlertBox(msg);
		}

		dict->close();
	}

	UpdateData(FALSE);
}

void ArxRleUiTdcNetPlanWorkStyle::DeleteStyle(int cur, bool alert)
{
	AcDbDictionary* dict = ArxRleUtils::openDictionaryForWrite(ArxRleNetPlanWorkStyle::dictName(), true, ARXRLEDB);
	if(dict != NULL)
	{
		if(dict->has(m_objIdList[cur]))
		{
			dict->remove(m_objIdList[cur]);
			m_objIdList.removeAt(cur);
			m_cxStyleName.DeleteString(cur);

			if(alert)
			{
				CString msg;
				msg.Format(_T("Delete %s NetPlan Work Style successfully!"), m_styleName);
				ArxRleUtils::alertBox(msg);
			}
		}
		else
		{
			CString msg;
			msg.Format(_T("Dictionary Not Has %s NetPlan Work Style."), m_styleName);
			ArxRleUtils::stopAlertBox(msg);
		}

		dict->close();
	}
}