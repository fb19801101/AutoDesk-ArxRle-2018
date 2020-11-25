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

#include "ArxRleUiTdcCurveElement.h"
#include "ArxRleUiTdmCurveElement.h"
#include "DbEntity\ArxRleEntityClass.h"



// ArxRleUiTdcCurveElement �Ի���

IMPLEMENT_DYNAMIC(ArxRleUiTdcCurveElement, CAcUiTabChildDialog)

ArxRleUiTdcCurveElement::ArxRleUiTdcCurveElement()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
	, m_openPathName(_T(""))
	, m_savePathName(_T(""))
	, m_breakBegin(178065.000)
	, m_breakEnd(178221.702)
	, m_distEases(1.0)
{
}

ArxRleUiTdcCurveElement::~ArxRleUiTdcCurveElement()
{
	if(m_pGridCtrl != NULL) delete m_pGridCtrl;
}

void ArxRleUiTdcCurveElement::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_CURVE_ELEMENT_BN_OPENFILE, m_bnOpenFile);
	DDX_Control(pDX, ARXRLE_CURVE_ELEMENT_BN_SAVEFILE, m_bnSaveFile);
	DDX_Control(pDX, ARXRLE_CURVE_ELEMENT_SC_GRIDCTRL, m_gpGridCtrl);
	DDX_Text(pDX, ARXRLE_CURVE_ELEMENT_EB_OPENFILE, m_openPathName);
	DDX_Text(pDX, ARXRLE_CURVE_ELEMENT_EB_SAVEFILE, m_savePathName);
	DDX_Text(pDX, ARXRLE_CURVE_ELEMENT_EB_BREAK_BEGIN, m_breakBegin);
	DDX_Text(pDX, ARXRLE_CURVE_ELEMENT_EB_BREAK_END, m_breakEnd);
	DDX_Text(pDX, ARXRLE_CURVE_ELEMENT_EB_EASES_DIST, m_distEases);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcCurveElement, CAcUiTabChildDialog)
	ON_WM_CREATE()
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(ARXRLE_CURVE_ELEMENT_BN_OPENFILE, OnBnClickedOpenfile)
	ON_BN_CLICKED(ARXRLE_CURVE_ELEMENT_BN_CALCELEMENT, OnBnClickedCalcelement)
	ON_BN_CLICKED(ARXRLE_CURVE_ELEMENT_BN_SAVEFILE, OnBnClickedSavefile)
	ON_BN_CLICKED(ARXRLE_CURVE_ELEMENT_BN_DRAWCURVE, OnBnClickedDrawcurve)
	ON_BN_CLICKED(ARXRLE_CURVE_ELEMENT_BN_SHOWDATA, OnBnClickedShowdata)
	ON_BN_CLICKED(ARXRLE_CURVE_ELEMENT_BN_ADDROW, OnBnClickedAddrow)
	ON_BN_CLICKED(ARXRLE_CURVE_ELEMENT_BN_DELROW, OnBnClickedDelrow)
	ON_BN_CLICKED(ARXRLE_CURVE_ELEMENT_BN_SAVECHANGE, OnBnClickedSavechange)
END_MESSAGE_MAP()


// ArxRleUiTdcCurveElement ��Ϣ�������

BOOL ArxRleUiTdcCurveElement::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	HICON hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_SELECT);
	m_bnOpenFile.SetIcon(hIcon);
	m_bnSaveFile.SetIcon(hIcon);

	CRect rc;
	m_gpGridCtrl.GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.DeflateRect(8,15,8,8);
	m_pGridCtrl->MoveWindow(rc);

	InitGridCtrl();

	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

int ArxRleUiTdcCurveElement::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAcUiTabChildDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_pGridCtrl = new CXTPGridControl;
	m_pGridCtrl->Create(CRect(),this,ARXRLE_CURVE_ELEMENT_GRIDCTRL);

	m_imgList.Create(ARXRLE_BMP_POKER, 16, 1, ILC_COLOR8 | ILC_MASK);
	m_pGridCtrl->SetImageList(&m_imgList);

	return 0;
}

LRESULT ArxRleUiTdcCurveElement::OnAcadKeepFocus(WPARAM, LPARAM)
{
	return TRUE;
}

void ArxRleUiTdcCurveElement::InitGridCtrl()
{
	m_pGridCtrl->SetEditable(TRUE);
	m_pGridCtrl->SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));
	m_pGridCtrl->SetRowCount(1); //��ʼΪ1��
	m_pGridCtrl->SetColumnCount(23); //��ʼ��Ϊ5��
	m_pGridCtrl->SetFixedRowCount(1); //��ͷΪһ��
	m_pGridCtrl->SetFixedColumnCount(1); //��ͷΪһ�� 

	for (int row = 0; row < m_pGridCtrl->GetRowCount(); row++)
	{
		for (int col = 0; col < m_pGridCtrl->GetColumnCount(); col++)
		{ 
			//���ñ����ʾ����
			m_gvItem.mask = GVIF_TEXT|GVIF_FORMAT;
			m_gvItem.row = row;
			m_gvItem.col = col;
			if ( row == 0)//��(0��0)��
			{
				m_pGridCtrl->SetColumnWidth(col,60);//�п�
				if(col == 0)
				{
					m_gvItem.nFormat = DT_CENTER|DT_WORDBREAK;
					m_gvItem.strText.Format(_T("���JD"),col);
					m_pGridCtrl->SetColumnWidth(col,40);//�п�
				}
				else if(col == 1)
					m_gvItem.strText.Format(_T("���DK"),col);
				else if(col == 2)
					m_gvItem.strText.Format(_T("����E/X"),col);
				else if(col == 3)
					m_gvItem.strText.Format(_T("����N/Y"),col);
				else if (col == 4)
					m_gvItem.strText.Format(_T("ǰ���߳�T1"), col);
				else if (col == 5)
					m_gvItem.strText.Format(_T("�����߳�T2"), col);
				else if(col == 6)
					m_gvItem.strText.Format(_T("ǰ�������߰뾶R1"),col);
				else if (col == 7)
					m_gvItem.strText.Format(_T("�󻺺����߰뾶R2"), col);
				else if (col == 8)
					m_gvItem.strText.Format(_T("Բ���߰뾶Rc"), col);
				else if(col == 9)
					m_gvItem.strText.Format(_T("ǰ�������߳�Ls1"),col);
				else if (col == 10)
					m_gvItem.strText.Format(_T("�󻺺����߳�Ls2"), col);
				else if(col == 11)
					m_gvItem.strText.Format(_T("Բ���߳�Lc"),col);
				else if (col == 12)
					m_gvItem.strText.Format(_T("��ֱ�߳�Lz"), col);
				else if(col == 13)
					m_gvItem.strText.Format(_T("��ʧ��E"),col);
				else if (col == 14)
					m_gvItem.strText.Format(_T("ƫ��PJ"), col);
				else if (col == 15)
					m_gvItem.strText.Format(_T("��λ��W"), col);
				else if(col == 16)
					m_gvItem.strText.Format(_T("���QD"),col);
				else if (col == 17)
					m_gvItem.strText.Format(_T("ֱ��ZH"), col);
				else if(col == 18)
					m_gvItem.strText.Format(_T("��ԲHY"),col);
				else if(col == 19)
					m_gvItem.strText.Format(_T("����QZ"),col);
				else if(col == 20)
					m_gvItem.strText.Format(_T("Բ��YH"),col);
				else if(col == 21)
					m_gvItem.strText.Format(_T("��ֱHZ"),col);
				else if (col == 22)
					m_gvItem.strText.Format(_T("�յ�ZD"), col);
			}
			else
			{
				m_gvItem.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

				if(col == 0)
					m_gvItem.strText.Format(_T("JD%d"),row);
				else
					m_gvItem.strText.Format(_T(""),2);
			}

			m_pGridCtrl->SetItem(&m_gvItem); 
			m_pGridCtrl->SetRowHeight(row, 25);//�и�
		}
	}
}

void ArxRleUiTdcCurveElement::OnBnClickedOpenfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("�����ļ�|*.jd|�ı��ļ�|*.txt|�����ļ�|*.*||");
	CFileDialog dlg(TRUE,_T("jd"), NULL, 0, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString pathName = dlg.GetPathName();
		POSITION po;
		po=dlg.GetStartPosition();//��ȡ��һ���ļ�λ��
		while(po)
		{
			pathName=dlg.GetNextPathName(po);//��ȡѡ���ļ��б��е���һ���ļ���
			m_openPathName=pathName;
			UpdateData(FALSE);
		}
		m_curveElement.InputJDData(m_openPathName);

		msgInf(L"�ļ��򿪳ɹ���");
	}
}

void ArxRleUiTdcCurveElement::OnBnClickedCalcelement()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_curveElement.m_vecJDElement.size() > 0)
	{
		m_curveElement.Calc_Point_dk(m_breakBegin,m_breakEnd);
		m_curveElement.Calc_Point_xy(m_breakBegin,m_breakEnd);
		m_curveElement.Calc_fwj_pj();
		m_curveElement.Calc_A_E_L();
		msgInf(L"������ϣ�");
	}
}

void ArxRleUiTdcCurveElement::OnBnClickedSavefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("�����ļ�|*.jd|�ı��ļ�|*.txt|�����ļ�|*.*||");
	CFileDialog dlg(FALSE,_T("jd"), NULL, 0, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString pathName = dlg.GetPathName();
		POSITION po;
		po=dlg.GetStartPosition();//��ȡ��һ���ļ�λ��
		while(po)
		{
			pathName=dlg.GetNextPathName(po);//��ȡѡ���ļ��б��е���һ���ļ���
			m_savePathName=pathName;
			UpdateData(FALSE);
		}
		m_curveElement.OutputJDResult(m_savePathName);

		msgInf(L"�ļ�����ɹ���");
	}
}

void ArxRleUiTdcCurveElement::OnBnClickedDrawcurve()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CompleteEditorCommand();

	int nJDNum = m_curveElement.m_vecJDElement.size();

	//������
	AddLayer("����",3);
	SetCurLayer("����");

	CPt3dArray oPointArray;
	for (int i= 0; i < nJDNum; i++)
	{
		JDELEMENT jd = m_curveElement.m_vecJDElement[i];
		oPointArray.push_back(CPt3d(jd.x, jd.y));
	}
	AddPolyline(oPointArray);

	//��Բ����
	AddLayer("������",1);
	SetCurLayer("������");
	for (int i= 1;i < nJDNum-1; i++)
	{
		JDELEMENT jd = m_curveElement.m_vecJDElement[i];
		// ���㷨����Բ��(��Բ����)
		CPt3d ptHY(jd.HY_x,jd.HY_y);
		CPt3d ptQZ(jd.QZ_x,jd.QZ_y);
		CPt3d ptYH(jd.YH_x,jd.YH_y);

		if (jd.pj>0.0)
			AddArc(ptYH, ptQZ, ptHY);
		else
			AddArc(ptHY, ptQZ, ptYH);
	}

	//����������
	AddLayer("��������",4);
	SetCurLayer("��������");
	for (int i= 1;i < nJDNum-1; i++)
	{
		JDELEMENT jd = m_curveElement.m_vecJDElement[i];
		oPointArray.clear();
		oPointArray.push_back(CPt3d(jd.ZH_x, jd.ZH_y));
		//ǰ��
		double dk = jd.ZH + m_distEases;
		while (dk<jd.HY)
		{
			double* xys = m_curveElement.Calc_Curve_xy(dk, 0, m_breakBegin, m_breakEnd);
			oPointArray.push_back(CPt3d(xys[0], xys[1]));

			dk += m_distEases;
		};
		oPointArray.push_back(CPt3d(jd.HY_x, jd.HY_y));
		AddPolyline(oPointArray);

		//��
		oPointArray.clear();
		oPointArray.push_back(CPt3d(jd.YH_x, jd.YH_y));
		dk = jd.YH + m_distEases;
		while (dk<jd.HZ)
		{
			double* xys = m_curveElement.Calc_Curve_xy(dk, 0, m_breakBegin, m_breakEnd);
			oPointArray.push_back(CPt3d(xys[0], xys[1]));

			dk += m_distEases;
		};
		oPointArray.push_back(CPt3d(jd.HZ_x, jd.HZ_y));
		AddPolyline(oPointArray);
	}

	msgInf(L"���߻�����ϣ�");
}

void ArxRleUiTdcCurveElement::OnBnClickedShowdata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nJDNum = m_curveElement.m_vecJDElement.size();
	m_pGridCtrl->SetRowCount(nJDNum+1);
	for (int row = 0; row < nJDNum; row++)
	{
		JDELEMENT jd = m_curveElement.m_vecJDElement[row];
		m_pGridCtrl->SetRowHeight(row + 1, 25);//�и�
		m_pGridCtrl->SetItemText(row + 1, 0, jd.JD);
		m_pGridCtrl->SetItemText(row + 1, 1, ToString(jd.DK));
		m_pGridCtrl->SetItemText(row + 1, 2, ToString(jd.x));
		m_pGridCtrl->SetItemText(row + 1, 3, ToString(jd.y));
		m_pGridCtrl->SetItemText(row + 1, 4, ToString(jd.T1));
		m_pGridCtrl->SetItemText(row + 1, 5, ToString(jd.T2));
		m_pGridCtrl->SetItemText(row + 1, 6, ToString(jd.R1));
		m_pGridCtrl->SetItemText(row + 1, 7, ToString(jd.R2));
		m_pGridCtrl->SetItemText(row + 1, 8, ToString(jd.Rc));
		m_pGridCtrl->SetItemText(row + 1, 9, ToString(jd.Ls1));
		m_pGridCtrl->SetItemText(row + 1, 10, ToString(jd.Ls2));
		m_pGridCtrl->SetItemText(row + 1, 11, ToString(jd.Lc));
		m_pGridCtrl->SetItemText(row + 1, 12, ToString(jd.Lz));
		m_pGridCtrl->SetItemText(row + 1, 13, ToString(jd.E));
		m_pGridCtrl->SetItemText(row + 1, 14, ToString(jd.pj));
		m_pGridCtrl->SetItemText(row + 1, 15, ToString(jd.fwj));
		m_pGridCtrl->SetItemText(row + 1, 16, ToString(jd.QD));
		m_pGridCtrl->SetItemText(row + 1, 17, ToString(jd.ZH));
		m_pGridCtrl->SetItemText(row + 1, 18, ToString(jd.HY));
		m_pGridCtrl->SetItemText(row + 1, 19, ToString(jd.QZ));
		m_pGridCtrl->SetItemText(row + 1, 20, ToString(jd.YH));
		m_pGridCtrl->SetItemText(row + 1, 21, ToString(jd.HZ));
		m_pGridCtrl->SetItemText(row + 1, 22, ToString(jd.ZD));
	}
	m_pGridCtrl->Invalidate(FALSE);
}

void ArxRleUiTdcCurveElement::OnBnClickedAddrow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nRow = m_pGridCtrl->GetFocusCell().row;
	CString tmp;
	if (nRow >= 0)
	{
		m_gvItem.row = nRow;
		tmp.Format(_T("JD%d"),nRow);
		m_pGridCtrl->InsertRow(tmp,nRow);
		for (int i = nRow; i<m_pGridCtrl->GetRowCount()+1;i++)
		{
			tmp.Format(_T("JD%d"),i + 1);
			m_pGridCtrl->SetItemText(i + 1,0,tmp);
		}
		m_pGridCtrl->SetRowHeight(nRow,30);
	}
	m_pGridCtrl->SetFocusCell(nRow,1);
	m_pGridCtrl->Invalidate();
}

void ArxRleUiTdcCurveElement::OnBnClickedDelrow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nRow = m_pGridCtrl->GetFocusCell().row;
	if  (nRow == m_pGridCtrl->GetRowCount()-1) return;
	CString tmp;
	if (nRow >= 0)
	{
		m_pGridCtrl->DeleteRow(nRow);

		for (int i = nRow; i<m_pGridCtrl->GetRowCount()+1;i++)
		{
			tmp.Format(_T("JD%d"),i);
			m_pGridCtrl->SetItemText(i,0,tmp);
		}
		m_pGridCtrl->SetRowHeight(nRow,30);

	}
	m_pGridCtrl->SetFocusCell(nRow,1);
	m_pGridCtrl->Invalidate();
}

void ArxRleUiTdcCurveElement::OnBnClickedSavechange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	setlocale(LC_ALL,"");

	CStdioFile file;
	if(file.Open(m_openPathName, CFile::modeCreate | CFile::modeReadWrite))
	{
		file.Seek(CFile::begin,0);
		CString strTemp;
		int row = m_pGridCtrl->GetRowCount() - 1;
		int col = m_pGridCtrl->GetColumnCount();
		for(int i = 0; i<row;i++)
		{
			JDELEMENT& jd = m_curveElement.m_vecJDElement[i];
			jd.DK = _tstof(m_pGridCtrl->GetItemText(i+1, 1));
			jd.x = _tstof(m_pGridCtrl->GetItemText(i+1, 2));
			jd.y = _tstof(m_pGridCtrl->GetItemText(i+1, 3));
			jd.T1 = _tstof(m_pGridCtrl->GetItemText(i+1, 4));
			jd.T2 = _tstof(m_pGridCtrl->GetItemText(i+1, 5));
			jd.R1 = _tstof(m_pGridCtrl->GetItemText(i+1, 6));
			jd.R2 = _tstof(m_pGridCtrl->GetItemText(i+1, 7));
			jd.Rc = _tstof(m_pGridCtrl->GetItemText(i+1, 8));
			jd.Ls1 = _tstof(m_pGridCtrl->GetItemText(i+1, 9));
			jd.Ls2 = _tstof(m_pGridCtrl->GetItemText(i+1, 10));
			jd.Lc = _tstof(m_pGridCtrl->GetItemText(i+1, 11));
			jd.Lz = _tstof(m_pGridCtrl->GetItemText(i+1, 12));
			strTemp.Format(L"%5s;%10.3f;%10.4f;%10.4f;%10.3f;%10.3f;%10.3f;%10.3f;%10.3f;%10.3f;%10.3f;%10.3f;%10.3f\n", jd.JD, jd.DK, jd.x, jd.y, jd.T1, jd.T2, jd.R1, jd.R2, jd.Rc, jd.Ls1, jd.Ls2, jd.Lc, jd.Lz);
			file.WriteString(strTemp);
		}

		file.Close();
	}

	msgInf(L"�ļ�����ɹ���");
}