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

#include "ArxRleUiTdmSpa.h"


// ArxRleUiTdmSpa �Ի���

IMPLEMENT_DYNAMIC(ArxRleUiTdmSpa, CAcUiTabMainDialog)

ArxRleUiTdmSpa::ArxRleUiTdmSpa(CWnd* pParent /*=NULL*/)
	:  CAcUiTabMainDialog(ArxRleUiTdmSpa::IDD, pParent, ArxRleApp::m_hInstance)
{
	m_pPageBeamCracks = new ArxRleUiTdcSpaBeamCracks;
	m_pPageBeamSection = new ArxRleUiTdcSpaBeamSection;
	m_pPageCircleStrength = new ArxRleUiTdcSpaCircleStrength;
	m_pPageColumnStrength = new ArxRleUiTdcSpaColumnStrength;
	m_pPageWallStrength = new ArxRleUiTdcSpaWallStrength;
	m_pPageOutResult = new ArxRleUiTdcSpaOutResult;


	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);
}

ArxRleUiTdmSpa::~ArxRleUiTdmSpa()
{
	if(m_pPageBeamCracks != NULL) delete m_pPageBeamCracks;
	if(m_pPageBeamSection != NULL) delete m_pPageBeamSection;
	if(m_pPageCircleStrength != NULL) delete m_pPageCircleStrength;
	if(m_pPageColumnStrength != NULL) delete m_pPageColumnStrength;
	if(m_pPageWallStrength != NULL) delete m_pPageWallStrength;
	if(m_pPageOutResult != NULL) delete m_pPageOutResult;
}

void ArxRleUiTdmSpa::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabMainDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_SPA_TAB, m_tabCtrl);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdmSpa, CAcUiTabMainDialog)
	ON_BN_CLICKED(IDOK, &ArxRleUiTdmSpa::OnBnClickedOk)
END_MESSAGE_MAP()


// ArxRleUiTdmSpa ��Ϣ�������


BOOL ArxRleUiTdmSpa::OnInitDialog()
{
	CAcUiTabMainDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	//SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetAcadTabPointer(&m_tabCtrl);

	AddTab(0, _T("������ʹ�ü���"), ArxRleUiTdcSpaBeamCracks::IDD,     m_pPageBeamCracks);
	AddTab(1, _T("������������"), ArxRleUiTdcSpaBeamSection::IDD, m_pPageBeamSection);
	AddTab(2, _T("Բ������������"), ArxRleUiTdcSpaCircleStrength::IDD,  m_pPageCircleStrength);
	AddTab(3, _T("������������"), ArxRleUiTdcSpaColumnStrength::IDD,  m_pPageColumnStrength);
	AddTab(4, _T("����ǽ����������"), ArxRleUiTdcSpaWallStrength::IDD,  m_pPageWallStrength);
	AddTab(5, _T("������"), ArxRleUiTdcSpaOutResult::IDD,  m_pPageOutResult);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void ArxRleUiTdmSpa::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CAcUiTabMainDialog::OnOK();
}