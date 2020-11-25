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

#include "ArxRleUiTdmCurveElement.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleApply.h"
#include "AcadUtils/ArxRleSmartPtr.h"
#include "AcadUtils/ArxRleSelSet.h"
#include "AcadUtils/ArxRleRbList.h"
#include "DbEntity/ArxRleEntityClass.h"


/**************************************************************************
**
**  measureCurve
**
**  **曲线要素绘制对话框
**
*************************************/
void measureCurve() //曲线要素绘制
{
	ArxRleUiTdmCurveElement dlg(acedGetAcadDwgView());
	dlg.DoModal();
}


// ArxRleUiTdmCurveElement 对话框

IMPLEMENT_DYNAMIC(ArxRleUiTdmCurveElement, CAcUiTabMainDialog)

ArxRleUiTdmCurveElement::ArxRleUiTdmCurveElement(CWnd* pParent /*=NULL*/)
:  CAcUiTabMainDialog(ArxRleUiTdmCurveElement::IDD, pParent, ArxRleApp::m_hInstance)
{
	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);

	m_pTdcCurveElement = new ArxRleUiTdcCurveElement;
	m_pTdcOvalElement = new ArxRleUiTdcOvalElement;
	m_pTdcCurveXY = new ArxRleUiTdcCurveXY;
	m_pTdcSqxElement = new ArxRleUiTdcSqxElement;
}

ArxRleUiTdmCurveElement::~ArxRleUiTdmCurveElement()
{
	if(m_pTdcCurveElement != NULL) delete m_pTdcCurveElement;
	if(m_pTdcOvalElement != NULL) delete m_pTdcOvalElement;
	if(m_pTdcCurveXY != NULL) delete m_pTdcCurveXY;
	if(m_pTdcSqxElement != NULL) delete m_pTdcSqxElement;
}

void ArxRleUiTdmCurveElement::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabMainDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_CURVE_ELEMENT_TAB, m_tabCtrl);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdmCurveElement, CAcUiTabMainDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// ArxRleUiTdmCurveElement 消息处理程序
BOOL ArxRleUiTdmCurveElement::OnInitDialog()
{
	CAcUiTabMainDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//SetIcon(m_hIcon, TRUE);		// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("曲线要素"), ArxRleUiTdcCurveElement::IDD, m_pTdcCurveElement);
	AddTab(1, _T("曲线坐标"), ArxRleUiTdcCurveXY::IDD, m_pTdcCurveXY);
	AddTab(2, _T("缓和曲线"), ArxRleUiTdcOvalElement::IDD, m_pTdcOvalElement);
	AddTab(3, _T("竖曲线"), ArxRleUiTdcSqxElement::IDD, m_pTdcSqxElement);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ArxRleUiTdmCurveElement::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CAcUiTabMainDialog::OnOK();
}