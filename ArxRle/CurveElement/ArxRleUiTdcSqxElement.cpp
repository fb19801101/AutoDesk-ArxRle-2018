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

#include "ArxRleUiTdcSqxElement.h"
#include "ArxRleUiTdmCurveElement.h"
#include "DbEntity\ArxRleEntityClass.h"



// ArxRleUiTdcSqxElement �Ի���

IMPLEMENT_DYNAMIC(ArxRleUiTdcSqxElement, CAcUiTabChildDialog)

ArxRleUiTdcSqxElement::ArxRleUiTdcSqxElement()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
{
	m_openPathName.Empty();
	m_savePathName.Empty();
	m_sqxPathName.Empty();

	m_DK = 297600;
	m_H = 567.9737;
	m_R = 30000;
	m_I1 = -3;
	m_I2 = -15.3866;
	m_L=m_T=m_E = 0;
	m_mBegin = 298288.7614;
	m_mEnd = 298779.1694;
	m_mDist = 10;
}

ArxRleUiTdcSqxElement::~ArxRleUiTdcSqxElement()
{
}

void ArxRleUiTdcSqxElement::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_SQX_ELEMENT_SC_GRIDCTRL, m_gpGridCtrl);
	DDX_Control(pDX, ARXRLE_SQX_ELEMENT_BN_DATA,  m_bnData);
	DDX_Control(pDX, ARXRLE_SQX_ELEMENT_BN_IMPORT,  m_bnImport);
	DDX_Control(pDX, ARXRLE_SQX_ELEMENT_BN_CALC,  m_bnCalc);
	DDX_Text(pDX, ARXRLE_SQX_ELEMENT_EB_S, m_DK);
	DDX_Text(pDX, ARXRLE_SQX_ELEMENT_EB_H, m_H);
	DDX_Text(pDX, ARXRLE_SQX_ELEMENT_EB_R, m_R);
	DDX_Text(pDX, ARXRLE_SQX_ELEMENT_EB_I1, m_I1);
	DDX_Text(pDX, ARXRLE_SQX_ELEMENT_EB_I2, m_I2);
	DDX_Text(pDX, ARXRLE_SQX_ELEMENT_EB_L, m_L);
	DDX_Text(pDX, ARXRLE_SQX_ELEMENT_EB_T, m_T);
	DDX_Text(pDX, ARXRLE_SQX_ELEMENT_EB_E, m_E);
	DDV_MinMaxDouble(pDX, m_R, 0., 10000000000.);
	DDX_Text(pDX, ARXRLE_SQX_ELEMENT_EB_MBEGIN, m_mBegin);
	DDX_Text(pDX, ARXRLE_SQX_ELEMENT_EB_MEND, m_mEnd);
	DDX_Text(pDX, ARXRLE_SQX_ELEMENT_EB_MDIST, m_mDist);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcSqxElement, CAcUiTabChildDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(ARXRLE_SQX_ELEMENT_BN_DATA, OnBnClickedSqxElementBnData)
	ON_BN_CLICKED(ARXRLE_SQX_ELEMENT_BN_IMPORT, OnBnClickedSqxElementBnImport)
	ON_BN_CLICKED(ARXRLE_SQX_ELEMENT_BN_CALC, OnBnClickedSqxElementBnCalc)
	ON_NOTIFY(NM_DBLCLK, ARXRLE_SQX_ELEMENT_GRIDCTRL, OnGridDblClick)
	ON_NOTIFY(NM_RCLICK, ARXRLE_SQX_ELEMENT_GRIDCTRL, OnGridRClick)
END_MESSAGE_MAP()


// ArxRleUiTdcSqxElement ��Ϣ�������

BOOL ArxRleUiTdcSqxElement::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_bnData.SetIcon(ARXRLE_ICON_FOLDER);
	m_bnData.SetDefaultColors();
	m_bnData.SetShade(ArxRleButtonXP::SHS_HARDBUMP);
	m_bnData.SetBtnCursor(ARXRLE_CURSOR_STAR);
	m_bnData.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnData.ActivateTooltip();
	m_bnData.SetTooltipText(L"�����������");

	m_bnImport.SetIcon(ARXRLE_ICON_FOLDER);
	m_bnImport.SetDefaultColors();
	m_bnImport.SetShade(ArxRleButtonXP::SHS_HARDBUMP);
	m_bnImport.SetBtnCursor(ARXRLE_CURSOR_STAR);
	m_bnImport.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnImport.ActivateTooltip();
	m_bnImport.SetTooltipText(L"����������");

	m_bnCalc.SetIcon(ARXRLE_ICON_CORRECT);
	m_bnCalc.SetDefaultColors();
	m_bnCalc.SetShade(ArxRleButtonXP::SHS_HARDBUMP);
	m_bnCalc.SetBtnCursor(ARXRLE_CURSOR_STAR);
	m_bnCalc.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnCalc.ActivateTooltip();
	m_bnCalc.SetTooltipText(L"����Ҫ��");

	CRect rc;
	m_gpGridCtrl.GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.DeflateRect(8,15,8,8);
	m_pGridCtrl->MoveWindow(rc);

	InitGridCtrl();

	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

int ArxRleUiTdcSqxElement::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAcUiTabChildDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_pGridCtrl = new CXTPGridControl;
	m_pGridCtrl->Create(CRect(),this,ARXRLE_SQX_ELEMENT_GRIDCTRL);

	m_imgList.Create(ARXRLE_BMP_POKER, 16, 1, ILC_COLOR8 | ILC_MASK);
	m_pGridCtrl->SetImageList(&m_imgList);

	return 0;
}

void ArxRleUiTdcSqxElement::InitGridCtrl()
{
	m_pGridCtrl->SetEditable(FALSE);
	m_pGridCtrl->EnableSelection(FALSE);
	m_pGridCtrl->SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));
	m_pGridCtrl->SetRowCount(1); //��ʼΪ1��
	m_pGridCtrl->SetColumnCount(4); //��ʼ��Ϊ5��
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
				m_pGridCtrl->SetColumnWidth(col,80);//�п�
				if(col == 0)
				{
					m_gvItem.nFormat = DT_CENTER|DT_WORDBREAK;
					m_gvItem.strText.Format(_T("���"),col);
					m_pGridCtrl->SetColumnWidth(col,40);//�п�
				}
				else if(col == 1)
					m_gvItem.strText.Format(_T("���S"),col);
				else if(col == 2)
					m_gvItem.strText.Format(_T("�߳�X"),col);
				else if(col == 3)
					m_gvItem.strText.Format(_T("����"),col);
			}
			else
			{
				m_gvItem.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

				if(col == 0)
					m_gvItem.strText.Format(_T("%d"),row);
				else
					m_gvItem.strText.Format(_T(""),2);
			}

			m_pGridCtrl->SetItem(&m_gvItem); 
			m_pGridCtrl->SetRowHeight(row, 25);//�и�
		}
	}

	UpdateData(TRUE);
}

void ArxRleUiTdcSqxElement::OnBnClickedSqxElementBnData()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_openPathName.Empty();
	TCHAR szFilter[] = _T("�����ļ�|*.dat|�ı��ļ�|*.txt|�����ļ�|*.*||");
	CFileDialog dlg(TRUE,_T("dat"), NULL, 0, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString pathName = dlg.GetPathName();
		POSITION po;
		po=dlg.GetStartPosition();//��ȡ��һ���ļ�λ��
		while(po)
		{
			pathName=dlg.GetNextPathName(po);//��ȡѡ���ļ��б��е���һ���ļ���
			m_openPathName=pathName;
		}
	}
}

void ArxRleUiTdcSqxElement::OnBnClickedSqxElementBnImport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("�������ļ�|*.sqx|�ı��ļ�|*.txt|�����ļ�|*.*||");
	CFileDialog dlg(TRUE,_T("sqx"), NULL, 0, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString pathName = dlg.GetPathName();
		POSITION po;
		po=dlg.GetStartPosition();//��ȡ��һ���ļ�λ��
		while(po)
		{
			pathName=dlg.GetNextPathName(po);//��ȡѡ���ļ��б��е���һ���ļ���
			m_sqxPathName=pathName;
		}
		m_curveElement.InputSQXData(m_sqxPathName);

		if(m_curveElement.m_vecSQXElement.size() > 0)
		{
			m_sqx = m_curveElement.m_vecSQXElement[0];
			m_DK = m_sqx.DK;
			m_H = m_sqx.H;
			m_R = m_sqx.R;
			m_I1 = m_sqx.I1*1000;
			m_I2 = m_sqx.I2*1000;
			m_L = m_sqx.L;
			m_T = m_sqx.T;
			m_E = m_sqx.E;
		}

		UpdateData(FALSE);

		msgInf(L"�����ߵ���ɹ���");
	}
}

void ArxRleUiTdcSqxElement::OnBnClickedSqxElementBnCalc() 
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

	if(m_openPathName.IsEmpty())
	{
		m_sqx.DK = m_DK;
		m_sqx.H = m_H;
		m_sqx.R = m_R;
		m_sqx.I1 = m_I1/1000;
		m_sqx.I2 = m_I2/1000;
		m_sqx.L = fabs(m_sqx.R * (m_sqx.I1 - m_sqx.I2));
		m_sqx.T = m_sqx.L / 2;
		if(m_sqx.R != 0) m_sqx.E = m_sqx.T * m_sqx.T / 2 / m_sqx.R;
	}

	if(!m_openPathName.IsEmpty())
	{
		setlocale(LC_ALL,"");

		CStdioFile file;
		vector<double> vecParam;
		if(file.Open(m_openPathName, CFile::modeRead))
		{
			CString strLine;
			while(file.ReadString(strLine))
			{
				strLine.Trim();
				if(strLine.GetLength() == 0)
					continue;

				vecParam.push_back(_tstof(strLine));
			}

			file.Close();
		}

		m_pGridCtrl->SetRowCount(vecParam.size()+1);
		for (int row = 0; row <= vecParam.size(); row++)
		{
			CString strGrid0,strGrid1,strGrid2,strGrid3;

			strGrid1 = FormatStat(vecParam[row]);
			m_sqx = m_curveElement.GetSqx(vecParam[row]);
			double h = m_curveElement.SqxCalc(vecParam[row], m_sqx);
			if(vecParam[row] >= vecParam[vecParam.size()-1])
			{
				strGrid1 = FormatStat(vecParam[vecParam.size()-1]);
				h = m_curveElement.SqxCalc(vecParam[vecParam.size()-1], m_sqx);
			}

			strGrid0.Format(_T("%d"),row);
			strGrid2.Format(_T("%.4f"),h);
			strGrid3 = m_curveElement.IsSqx(vecParam[row], m_sqx) ? L"������":L"ֱ�¶�";

			m_pGridCtrl->SetItemText(row+1,0,strGrid0);
			m_pGridCtrl->SetItemText(row+1,1,strGrid1);
			m_pGridCtrl->SetItemText(row+1,2,strGrid2);
			m_pGridCtrl->SetItemText(row+1,3,strGrid3);

			m_pGridCtrl->SetItem(&m_gvItem); 
			m_pGridCtrl->SetRowHeight(row+1, 25);//�и�
			m_pGridCtrl->SetItemFormat(row+1,0,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,1,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,2,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,3,DT_CENTER);
		}
		m_pGridCtrl->Invalidate(FALSE);
		m_openPathName.Empty();
	}
	else
	{
		int rows = INT(((m_mEnd -  m_mBegin) / m_mDist)+1);
		m_pGridCtrl->SetRowCount(rows);
		for (int row = 0; row <= rows; row++)
		{
			CString strGrid0,strGrid1,strGrid2,strGrid3;

			strGrid1 = FormatStat( m_mBegin + m_mDist * row);
			double h = m_curveElement.SqxCalc( m_mBegin + m_mDist * row, m_sqx);
			if( m_mBegin + m_mDist * row >= m_mEnd)
			{
				strGrid1 = FormatStat(m_mEnd);
				h = m_curveElement.SqxCalc(m_mEnd, m_sqx);
			}

			strGrid0.Format(_T("%d"),row);
			strGrid2.Format(_T("%.4f"),h);
			strGrid3 = m_curveElement.IsSqx( m_mBegin + m_mDist * row, m_sqx) ? L"������":L"ֱ�¶�";

			m_pGridCtrl->SetItemText(row+1,0,strGrid0);
			m_pGridCtrl->SetItemText(row+1,1,strGrid1);
			m_pGridCtrl->SetItemText(row+1,2,strGrid2);
			m_pGridCtrl->SetItemText(row+1,3,strGrid3);

			m_pGridCtrl->SetItem(&m_gvItem); 
			m_pGridCtrl->SetRowHeight(row+1, 25);//�и�
			m_pGridCtrl->SetItemFormat(row+1,0,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,1,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,2,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,3,DT_CENTER);

			if( m_mBegin + m_mDist * row >= m_mEnd) break;
		}
		m_pGridCtrl->Invalidate(FALSE);
	}

	m_DK = m_sqx.DK;
	m_H = m_sqx.H;
	m_R = m_sqx.R;
	m_I1 = m_sqx.I1*1000;
	m_I2 = m_sqx.I2*1000;
	m_L = m_sqx.L;
	m_T = m_sqx.T;
	m_E = m_sqx.E;

	UpdateData(false);
}

void ArxRleUiTdcSqxElement::OnGridDblClick(NMHDR *pNMHDR, LRESULT* /*pResult*/)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_GRIDVIEW*pNM = (NM_GRIDVIEW*)pNMHDR;
	m_savePathName.Empty();
	TCHAR szFilter[] = _T("�����ļ�|*.dat|�ı��ļ�|*.txt|�����ļ�|*.*||");
	CFileDialog dlg(FALSE,_T("dat"), NULL, 0, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString pathName = dlg.GetPathName();
		POSITION po;
		po=dlg.GetStartPosition();//��ȡ��һ���ļ�λ��
		while(po)
		{
			pathName=dlg.GetNextPathName(po);//��ȡѡ���ļ��б��е���һ���ļ���
			m_savePathName=pathName;;
		}

		if(m_savePathName.IsEmpty()) return;
		setlocale(LC_ALL,"");

		CStdioFile file;
		if(file.Open(m_savePathName, CFile::modeCreate | CFile::modeReadWrite))
		{
			file.Seek(CFile::begin,0);
			CString strTemp;
			file.WriteString(L"���     ��� S    �߳� H     λ��\n");

			for(int i = 1; i<m_pGridCtrl->GetRowCount();i++)
			{
				strTemp.Format(L"%4d  %10s  %10s  %10s\n",i,m_pGridCtrl->GetItemText(i,1),m_pGridCtrl->GetItemText(i,2),m_pGridCtrl->GetItemText(i,3));
				file.WriteString(strTemp);
			}

			file.Close();
		}

		msgInf(L"���ݵ����ɹ���");
	}
}

void ArxRleUiTdcSqxElement::OnGridRClick(NMHDR *pNMHDR, LRESULT* /*pResult*/)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_GRIDVIEW*pNM = (NM_GRIDVIEW*)pNMHDR;

	m_pGridCtrl->OnEditCopy();
}
