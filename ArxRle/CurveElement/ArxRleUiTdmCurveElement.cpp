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
**  **����Ҫ�ػ��ƶԻ���
**
*************************************/
void measureCurve() //����Ҫ�ػ���
{
	ArxRleUiTdmCurveElement dlg(acedGetAcadDwgView());
	dlg.DoModal();
}


// ArxRleUiTdmCurveElement �Ի���

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


// ArxRleUiTdmCurveElement ��Ϣ�������
BOOL ArxRleUiTdmCurveElement::OnInitDialog()
{
	CAcUiTabMainDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	//SetIcon(m_hIcon, TRUE);		// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("����Ҫ��"), ArxRleUiTdcCurveElement::IDD, m_pTdcCurveElement);
	AddTab(1, _T("��������"), ArxRleUiTdcCurveXY::IDD, m_pTdcCurveXY);
	AddTab(2, _T("��������"), ArxRleUiTdcOvalElement::IDD, m_pTdcOvalElement);
	AddTab(3, _T("������"), ArxRleUiTdcSqxElement::IDD, m_pTdcSqxElement);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void ArxRleUiTdmCurveElement::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CAcUiTabMainDialog::OnOK();
}