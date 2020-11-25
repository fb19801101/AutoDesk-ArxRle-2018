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

#include "ArxRleUiDlgReg.h"
#include "DbEntity/ArxRleString.h"

void ArxReg()
{
	ArxRleUiDlgReg dlg;
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgReg �Ի���

ArxRleUiDlgReg::ArxRleUiDlgReg(CWnd* pParent /*=NULL*/)
	: CDialog(ArxRleUiDlgReg::IDD, pParent)
{
	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);
}

void ArxRleUiDlgReg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ArxRleUiDlgReg, CDialog)
	ON_BN_CLICKED(ARXRLE_REG_BN_CODE, &ArxRleUiDlgReg::OnBnClickedRegBnCode)
	ON_BN_CLICKED(IDOK, &ArxRleUiDlgReg::OnBnClickedRegBnReg)
	ON_BN_CLICKED(IDCANCEL, &ArxRleUiDlgReg::OnBnClickedRegBnExit)
	ON_BN_CLICKED(ARXRLE_REG_BN_SERIAL, &ArxRleUiDlgReg::OnBnClickedRegBnSerial)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgReg ��Ϣ�������
BOOL ArxRleUiDlgReg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CEdit*)GetDlgItem(ARXRLE_REG_EB_CODE))->SetReadOnly(!ArxRleApp::m_bIsAdmin);
	GetDlgItem(ARXRLE_REG_BN_SERIAL)->ShowWindow(ArxRleApp::m_bIsAdmin);

	return TRUE;
	// �쳣: OCX ����ҳӦ���� FALSE
}

void ArxRleUiDlgReg::OnBnClickedRegBnCode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString reg_user;
	GetDlgItem(ARXRLE_REG_EB_USER)->GetWindowText(reg_user);
	if(reg_user.IsEmpty())
	{
		msgErr(L"�û�������Ϊ�գ�");
		return;
	}

	CString reg_code = DiskSerial()+MacAddress();

	GetDlgItem(ARXRLE_REG_EB_CODE)->SetWindowText(reg_code);
}

void ArxRleUiDlgReg::OnBnClickedRegBnSerial()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString reg_user;
	GetDlgItem(ARXRLE_REG_EB_USER)->GetWindowText(reg_user);
	if(reg_user.IsEmpty())
	{
		msgErr(L"�û�������Ϊ�գ�");
		return;
	}

	CString reg_code;
	CString reg_serial;
	
	GetDlgItem(ARXRLE_REG_EB_CODE)->GetWindowText(reg_code);
	if(reg_code.IsEmpty())
	{
		msgErr(L"�����벻��Ϊ�գ�");
		reg_code = DiskSerial()+MacAddress();
		GetDlgItem(ARXRLE_REG_EB_CODE)->SetWindowText(reg_code);
	}

	CString disk = reg_code.Mid(0,8);
	CString mac = reg_code.Mid(8,19);
	reg_code = disk.Mid(3,4)+mac.Mid(4,6);
	reg_serial = SnKey(reg_code);

	GetDlgItem(ARXRLE_REG_EB_SN1)->SetWindowText(reg_serial.Mid(0,5));
	GetDlgItem(ARXRLE_REG_EB_SN2)->SetWindowText(reg_serial.Mid(5,5));
	GetDlgItem(ARXRLE_REG_EB_SN3)->SetWindowText(reg_serial.Mid(10,5));
	GetDlgItem(ARXRLE_REG_EB_SN4)->SetWindowText(reg_serial.Mid(15,5));
}

void ArxRleUiDlgReg::OnBnClickedRegBnReg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString reg_user;
	GetDlgItem(ARXRLE_REG_EB_USER)->GetWindowText(reg_user);
	if(reg_user.IsEmpty())
	{
		msgErr(L"�û�������Ϊ�գ�");
		return;
	}

	CString reg_code;
	GetDlgItem(ARXRLE_REG_EB_CODE)->GetWindowText(reg_code);
	if(reg_code.IsEmpty())
	{
		msgErr(L"�����벻��Ϊ�գ�");
		return;
	}

	HKEY key;
	CString skey=L"Software\\Autodesk\\ArxRleSoft";
	if(RegCreateKey(HKEY_CURRENT_USER,skey,&key) == ERROR_SUCCESS)//���û��������½�����ֱ�ӷ���
	{
		CTime tm = CTime::GetCurrentTime();
		CString reg_date = tm.Format(L"%Y-%m-%d");
		RegSetValueEx(key,L"RegDate",0,REG_SZ,(BYTE*)reg_date.GetBuffer(),2*reg_date.GetLength());
		RegSetValueEx(key,L"RegUser",0,REG_SZ,(BYTE*)reg_user.GetBuffer(),2*reg_user.GetLength());
		RegSetValueEx(key,L"RegCode",0,REG_SZ,(BYTE*)reg_code.GetBuffer(),2*reg_code.GetLength());

		CString sn1,sn2,sn3,sn4,reg_serial;
		GetDlgItem(ARXRLE_REG_EB_SN1)->GetWindowText(sn1);
		GetDlgItem(ARXRLE_REG_EB_SN2)->GetWindowText(sn2);
		GetDlgItem(ARXRLE_REG_EB_SN3)->GetWindowText(sn3);
		GetDlgItem(ARXRLE_REG_EB_SN4)->GetWindowText(sn4);
		reg_serial = sn1+sn2+sn3+sn4;

		CString serial = SnKey(DiskSerial().Mid(3,4)+MacAddress().Mid(4,6));
		if(!reg_serial.IsEmpty())
		{
			if(reg_serial == serial)
			{
				reg_serial = reg_user+"_"+reg_serial;
				RegSetValueEx(key,L"RegSerial",0,REG_SZ,(BYTE*)reg_serial.GetBuffer(),2*reg_serial.GetLength());
				RegSetValueEx(key,L"IsReged",0,REG_SZ,(BYTE*)"1",1);
				msgInf(L"ע��ɹ�!");
			}
			else
			{
				reg_serial = reg_user+"_"+reg_serial;
				RegSetValueEx(key,L"RegSerial",0,REG_SZ,(BYTE*)serial.GetBuffer(),2*serial.GetLength());
				RegSetValueEx(key,L"IsReged",0,REG_SZ,(BYTE*)"0",1);
				msgErr(L"ע��ʧ��!");
			}
		}
		else
		{
			msgErr(L"ע���벻��Ϊ�գ�");
		}
	}

	RegCloseKey(key);
}

void ArxRleUiDlgReg::OnBnClickedRegBnExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}