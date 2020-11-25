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
#include "stdafx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleUiDlgCrdTrm.h"
#include "ArxRleCoord.h"

// ArxRleUiDlgCrdTrm 对话框

void measureCrdTrm()
{
	ArxRleUiDlgCrdTrm dlg;
	dlg.DoModal();
}

ArxRleUiDlgCrdTrm::ArxRleUiDlgCrdTrm(CWnd* pParent /*=NULL*/)
	: CAcUiDialog(ArxRleUiDlgCrdTrm::IDD, pParent)
{
	m_B = m_L = m_H = m_X = m_Y = m_Z =  "0.0";
	m_L0 = 0;
	m_dx = 0.0;
	m_dy = 0.0;
	m_dz = 0.0;
	m_rx = 0.0;
	m_ry = 0.0;
	m_rz = 0.0;
	m_m = 0.0;

	m_hIcon = AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);
}

void ArxRleUiDlgCrdTrm::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_CRDTRM_BN_APPLY, m_cApply);
	DDX_Text(pDX, ARXRLE_CRDTRM_EB_DX, m_dx);
	DDX_Text(pDX, ARXRLE_CRDTRM_EB_DY, m_dy);
	DDX_Text(pDX, ARXRLE_CRDTRM_EB_DZ, m_dz);
	DDX_Text(pDX, ARXRLE_CRDTRM_EB_RX, m_rx);
	DDX_Text(pDX, ARXRLE_CRDTRM_EB_RY, m_ry);
	DDX_Text(pDX, ARXRLE_CRDTRM_EB_RZ, m_rz);
	DDX_Text(pDX, ARXRLE_CRDTRM_EB_M, m_m);
	DDX_Control(pDX, ARXRLE_CRDTRM_BN_FILE, m_cBtnFile);
	DDX_Control(pDX, ARXRLE_CRDTRM_EB_INPUT_L0, m_cMed);
	DDX_Control(pDX, ARXRLE_CRDTRM_BN_CONVERT, m_cConvert);
	DDX_Control(pDX, ARXRLE_CRDTRM_BN_READ, m_cRead);
	DDX_Control(pDX, ARXRLE_CRDTRM_BN_CLEAR, m_cClear);
	DDX_Control(pDX, ARXRLE_CRDTRM_BN_SET, m_cSet);
	DDX_Text(pDX,ARXRLE_CRDTRM_EB_INPUT_B, m_B);
	DDX_Text(pDX,ARXRLE_CRDTRM_EB_INPUT_L, m_L);
	DDX_Text(pDX,ARXRLE_CRDTRM_EB_INPUT_H, m_H);
	DDX_Text(pDX,ARXRLE_CRDTRM_EB_INPUT_L0, m_L0);
	DDX_Text(pDX,ARXRLE_CRDTRM_EB_OUTPUT_X, m_X);
	DDX_Text(pDX,ARXRLE_CRDTRM_EB_OUTPUT_Y, m_Y);
	DDX_Text(pDX,ARXRLE_CRDTRM_EB_OUTPUT_Z, m_Z);
}

BEGIN_MESSAGE_MAP(ArxRleUiDlgCrdTrm, CAcUiDialog)
	//ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
	//ON_WM_CLOSE()
	ON_BN_CLICKED(ARXRLE_CRDTRM_RO_MODE1, OnMode1)
	ON_BN_CLICKED(ARXRLE_CRDTRM_RO_MODE2, OnMode2)
	ON_BN_CLICKED(ARXRLE_CRDTRM_RO_MODE3, OnMode3)
	ON_BN_CLICKED(ARXRLE_CRDTRM_RO_MODE4, OnMode4)
	ON_BN_CLICKED(ARXRLE_CRDTRM_RO_MODE5, OnMode5)
	ON_BN_CLICKED(ARXRLE_CRDTRM_RO_REF1, OnRef1)
	ON_BN_CLICKED(ARXRLE_CRDTRM_RO_REF2, OnRef2)
	ON_BN_CLICKED(ARXRLE_CRDTRM_RO_REF3, OnRef3)
	ON_BN_CLICKED(ARXRLE_CRDTRM_BN_READ, OnBtnRead)
	ON_BN_CLICKED(ARXRLE_CRDTRM_BN_CLEAR, OnBtnClear)
	ON_BN_CLICKED(ARXRLE_CRDTRM_BN_SET, OnBtnSet)
	ON_BN_CLICKED(ARXRLE_CRDTRM_BN_CONVERT, OnBtnConvert)
	ON_BN_CLICKED(ARXRLE_CRDTRM_BN_FILE, OnBtnFile)
	ON_BN_CLICKED(ARXRLE_CRDTRM_BN_APPLY, OnBtnApply)
END_MESSAGE_MAP()


// ArxRleUiDlgCrdTrm 消息处理程序

BOOL ArxRleUiDlgCrdTrm::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	// TODO: 在此添加额外的初始化代码
	SetIcon(m_hIcon,TRUE);
	SetIcon(m_hIcon,FALSE);

	((CButton*)GetDlgItem(ARXRLE_CRDTRM_RO_MODE1))->SetCheck(1);
	((CButton*)GetDlgItem(ARXRLE_CRDTRM_RO_REF1))->SetCheck(1);

	m_cMed.EnableWindow(FALSE);
	m_cSet.EnableWindow(FALSE);

	m_cConvert.SetIcon(ARXRLE_ICON_RIGHT);
	m_cConvert.SetShade(ArxRleButtonXP::SHS_HARDBUMP);
	m_cConvert.SetAlign(ArxRleButtonXP::ST_ALIGN_HORIZ_RIGHT);
	m_cConvert.SetBtnCursor(ARXRLE_CURSOR_STAR);

	m_cSet.SetIcon(ARXRLE_ICON_SET);
	m_cSet.SetShade(ArxRleButtonXP::SHS_HARDBUMP);
	m_cSet.SetBtnCursor(ARXRLE_CURSOR_STAR);
	m_cSet.SetSound(MAKEINTRESOURCE(ARXRLE_WAVE_STONE),ArxRleApp::m_hInstance);

	m_cClear.SetIcon(ARXRLE_ICON_CANCLE);
	m_cClear.SetShade(ArxRleButtonXP::SHS_HARDBUMP);
	m_cClear.SetBtnCursor(ARXRLE_CURSOR_STAR);

	m_cRead.SetIcon(ARXRLE_ICON_LEFT);
	m_cRead.SetBtnCursor(ARXRLE_CURSOR_STAR);
	m_cRead.SetShade(ArxRleButtonXP::SHS_HARDBUMP);

	m_cBtnFile.SetIcon(ARXRLE_ICON_FOLDER);
	m_cBtnFile.SetBtnCursor(ARXRLE_CURSOR_STAR);

	m_cApply.SetIcon(ARXRLE_ICON_CORRECT);
	m_cApply.SetBtnCursor(ARXRLE_CURSOR_STAR);

	m_bSmall = TRUE;
	m_bFlag = FALSE;
	m_nSelMode = 1;
	m_nSelRef = 1;
	m_L0 = 0;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ArxRleUiDlgCrdTrm::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if(!m_bFlag)
	{
		m_bFlag = TRUE;
		CRect rcLarge,rcSmall;
		GetWindowRect(&rcLarge);
		GetDlgItem(ARXRLE_CRDTRM_PC_SEPARATOR)->GetWindowRect(&rcSmall);
		m_nHeight = rcLarge.bottom - rcSmall.bottom;
		rcSmall.top = rcLarge.top;
		rcSmall.left = rcLarge.left;
		rcSmall.right = rcLarge.right;
		CRect rc(rcSmall.CenterPoint().x,rcSmall.CenterPoint().y,rcSmall.CenterPoint().x,rcSmall.CenterPoint().y);
		int Width = rcSmall.Width();
		int Height = rcSmall.Height();
		for(int n=20; n>=1; n--)
		{
			rc.InflateRect(Width/40,Height/40);
			MoveWindow(&rc);
			ShowWindow(SW_SHOW);
			Sleep(10);
		}
		MoveWindow(&rcSmall);
		ShowWindow(SW_SHOW);
	}
	CAcUiDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
}

BOOL ArxRleUiDlgCrdTrm::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default

	return CAcUiDialog::OnEraseBkgnd(pDC);
}

void ArxRleUiDlgCrdTrm::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;
	GetWindowRect(&rc);
	int Width = rc.Width();
	int Height = rc.Height();
	for(int n=20; n>=1; n--)
	{
		rc.DeflateRect(Width/40,Height/40);
		MoveWindow(&rc);
		ShowWindow(SW_SHOW);
		Sleep(10);
	}
	CAcUiDialog::OnClose();
}

void ArxRleUiDlgCrdTrm::OnMode1() 
{
	// TODO: Add your control notification handler code here
	if(m_nSelMode==1)
		return;
	m_nSelMode = 1;
	SetInterface(1);
}

void ArxRleUiDlgCrdTrm::OnMode2() 
{
	// TODO: Add your control notification handler code here
	if(m_nSelMode==2)
		return;
	m_nSelMode = 2;
	SetInterface(2);

}

void ArxRleUiDlgCrdTrm::OnMode3() 
{
	// TODO: Add your control notification handler code here
	if(m_nSelMode==3)
		return;
	m_nSelMode = 3;
	SetInterface(3);

}

void ArxRleUiDlgCrdTrm::OnMode4() 
{
	// TODO: Add your control notification handler code here
	if(m_nSelMode==4)
		return;
	m_nSelMode = 4;
	SetInterface(4);

}

void ArxRleUiDlgCrdTrm::OnMode5() 
{
	// TODO: Add your control notification handler code here
	if(m_nSelMode==5)
		return;
	m_nSelMode = 5;
	SetInterface(5);
}

void ArxRleUiDlgCrdTrm::SetInterface(int nMode)
{
    CString str;
	switch(nMode)
	{
	case 1:
		str = "BLHXYZ";
		if(m_cMed.IsWindowEnabled())m_cMed.EnableWindow(FALSE);
		if(m_cSet.IsWindowEnabled())m_cSet.EnableWindow(FALSE);
		break;
	case 2:
		str = "XYZBLH";
		if(m_cMed.IsWindowEnabled())m_cMed.EnableWindow(FALSE);
		if(m_cSet.IsWindowEnabled())m_cSet.EnableWindow(FALSE);
		break;
	case 3:
		str = "BLHxyH";
		if(!m_cMed.IsWindowEnabled())m_cMed.EnableWindow();
		if(!(m_cMed.GetStyle() & ES_READONLY))
			m_cMed.SetReadOnly();
		if(m_cSet.IsWindowEnabled())m_cSet.EnableWindow(FALSE);
		break;
	case 4:
		str = "xyHBLH";
		if(!m_cMed.IsWindowEnabled())m_cMed.EnableWindow();
		if(m_cMed.GetStyle() & ES_READONLY)
			m_cMed.SetReadOnly(FALSE);
		if(m_cSet.IsWindowEnabled())m_cSet.EnableWindow(FALSE);
		break;		
	case 5:
		str = "XYZXYZ";
		if(m_cMed.IsWindowEnabled())m_cMed.EnableWindow(FALSE);
		if(!m_cSet.IsWindowEnabled())m_cSet.EnableWindow();
		break;
	}
	GetDlgItem(ARXRLE_CRDTRM_SC_IN1)->SetWindowText((CString)str.GetAt(0)+":");
	GetDlgItem(ARXRLE_CRDTRM_SC_IN2)->SetWindowText((CString)str.GetAt(1)+":");
	GetDlgItem(ARXRLE_CRDTRM_SC_IN3)->SetWindowText((CString)str.GetAt(2)+":");
	GetDlgItem(ARXRLE_CRDTRM_SC_OUT1)->SetWindowText((CString)str.GetAt(3)+":");
	GetDlgItem(ARXRLE_CRDTRM_SC_OUT2)->SetWindowText((CString)str.GetAt(4)+":");
	GetDlgItem(ARXRLE_CRDTRM_SC_OUT3)->SetWindowText((CString)str.GetAt(5)+":");
}

void ArxRleUiDlgCrdTrm::OnRef1() 
{
	// TODO: Add your control notification handler code here
	m_nSelRef = 1;
}

void ArxRleUiDlgCrdTrm::OnRef2() 
{
	// TODO: Add your control notification handler code here
	m_nSelRef = 2;
}

void ArxRleUiDlgCrdTrm::OnRef3() 
{
	// TODO: Add your control notification handler code here
	m_nSelRef = 3;
}

void ArxRleUiDlgCrdTrm::OnBtnRead() 
{
	// TODO: Add your control notification handler code here
	CString  temp;
	temp = m_B;
	m_B = m_X;
	m_X = temp;

	temp = m_L;
	m_L = m_Y;
	m_Y = temp;

	temp = m_H;
	m_H = m_Z;
	m_Z = temp;
	UpdateData(FALSE);
}

void ArxRleUiDlgCrdTrm::OnBtnClear() 
{
	// TODO: Add your control notification handler code here
	m_X = m_Y = m_Z = m_B = m_L = m_H = L"";
	m_L0 = 0.0;
	UpdateData(FALSE);
}

void ArxRleUiDlgCrdTrm::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	if(!m_bSmall)
		return;
	CRect rc;
	GetWindowRect(&rc);
	rc.bottom += m_nHeight;
	MoveWindow(rc);
	ShowWindow(SW_SHOW);
	m_bSmall = FALSE;
}

void ArxRleUiDlgCrdTrm::OnBtnConvert() 
{
	// TODO: Add your control notification handler code here
	if(!UpdateData())return;
	double e2, a;
	switch (m_nSelRef )
	{
	case 1:
		e2 = WGS84_E2;
		a = WGS84_A;
		break;
	case 2:
		e2 = BJ54_E2;
		a = BJ54_A;
		break;
	case 3:
		e2 = C80_E2;
		a = C80_A;
		break;
	}
    ArxRleCoord blh;
	double L0;
	switch(m_nSelMode)
	{
	case 1:
		blh.Input(m_B, m_L, m_H, DT_DMS);
		blh.EarthToSpace(e2, a);//BLH->XYZ
		blh.Output(m_X, m_Y, m_Z,DT_LENGTH);
		break;
	case 2:
		blh.Input(m_B, m_L, m_H, DT_LENGTH);
		blh.SpaceToEarth(e2, a);//XYZ->BLH
		blh.Output(m_X, m_Y, m_Z,DT_DMS);
		break;
	case 3:	
		blh.Input(m_B, m_L, m_H, DT_DMS);
		m_L0 = blh.GetMeridian();
		if(m_L0<0)return;
		L0 = blh.DMSToRadian(m_L0);
		blh.EarthToGauss(e2, a, L0);//BLH->xyH
		blh.Output(m_X, m_Y, m_Z,DT_LENGTH);
		break;
	case 4:
		blh.Input(m_B, m_L, m_H, DT_LENGTH);
		L0 = blh.DMSToRadian(m_L0);
		blh.GaussToEarth(L0);//xyH->BLH
		blh.Output(m_X, m_Y, m_Z,DT_DMS);
		break;
	case 5:
		blh.Input(m_B, m_L, m_H, DT_LENGTH);
		Rot r;
		r.dx = m_dx;
		r.dy = m_dy;
		r.dz = m_dz;
		r.rx = m_rx;
		r.ry = m_ry;
		r.rz = m_rz;
		r.m  = m_m;
		blh.SpaceToSpace(r);
		blh.Output(m_X, m_Y, m_Z, DT_LENGTH);
		break;
	default:
		return;
	}
	
	UpdateData(FALSE);
}

void ArxRleUiDlgCrdTrm::OnBtnFile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,NULL,NULL,OFN_READONLY,
		_T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"));
	CString strPath;
	if(dlg.DoModal()==IDOK)
	{
		strPath = dlg.GetPathName();
	/*	CStdioFile file;
		if(!file.Open(strPath,CFile::modeRead))
		{
			AfxMessageBox("打开文件失败");
		};
		CString strData;
		file.ReadString(strData);*/
		ArxRleMatrix Points;
		Points.LoadFromDatFile(strPath);
		if(Points.GetNumRows()<3)
		{
			AfxMessageBox(L"公共点数不足，至少有三个");
			return;
		}
		ArxRleCoord crd;
		Rot r;
		crd.CmpRot(Points, r);
		m_dx = r.dx;
		m_dy = r.dy;
		m_dz = r.dz;
		m_rx = r.rx;
		m_ry = r.ry;
		m_rz = r.rz;
		m_m = r.m;
		UpdateData(FALSE);
	}
}

void ArxRleUiDlgCrdTrm::OnBtnApply() 
{
	// TODO: Add your control notification handler code here
    CRect rc;
	GetWindowRect(&rc);
	rc.bottom-=m_nHeight;
	MoveWindow(&rc);
	m_bSmall = TRUE;
}