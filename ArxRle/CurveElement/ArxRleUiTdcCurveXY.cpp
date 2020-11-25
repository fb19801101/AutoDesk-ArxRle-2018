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

#include "ArxRleUiTdcCurveXY.h"
#include "ArxRleUiTdmCurveElement.h"
#include "DbEntity\ArxRleEntityClass.h"



// ArxRleUiTdcCurveXY �Ի���

IMPLEMENT_DYNAMIC(ArxRleUiTdcCurveXY, CAcUiTabChildDialog)

ArxRleUiTdcCurveXY::ArxRleUiTdcCurveXY()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
{
	m_openPathName.Empty();
	m_savePathName.Empty();
	m_jdPathName.Empty();

	m_x1=m_y1=m_x2=m_y2=m_x3=m_y3 = 0;
	m_R=m_ls=m_L=m_A=m_T=m_E=m_W = 0;
	m_QD=m_ZD=m_ZH=m_HY=m_QZ=m_YH=m_HZ = 0;
	m_mDist = 10;
	m_mOffset = 0;
}

ArxRleUiTdcCurveXY::~ArxRleUiTdcCurveXY()
{
}

void ArxRleUiTdcCurveXY::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_CURVE_XY_SC_GRIDCTRL, m_gpGridCtrl);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_X1, m_x1);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_Y1, m_y1);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_X2, m_x2);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_Y2, m_y2);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_X3, m_x3);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_Y3, m_y3);
	DDV_MinMaxDouble(pDX, m_R, 0., 10000000000.);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_R, m_R);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_LO, m_ls);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_L, m_L);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_A, m_A);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_T, m_T);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_E, m_E);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_W, m_W);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_QD, m_QD);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_ZD, m_ZD);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_ZH, m_ZH);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_HY, m_HY);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_QZ, m_QZ);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_YH, m_YH);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_HZ, m_HZ);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_MDIST, m_mDist);
	DDX_Text(pDX, ARXRLE_CURVE_XY_EB_MOFFSET, m_mOffset);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcCurveXY, CAcUiTabChildDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(ARXRLE_CURVE_XY_BN_DATA, OnBnClickedCurveXyBnData)
	ON_BN_CLICKED(ARXRLE_CURVE_XY_BN_IMPORT, OnBnClickedCurveXyBnImport)
	ON_BN_CLICKED(ARXRLE_CURVE_XY_BN_CALC, OnBnClickedCurveXyBnCalc)
	ON_NOTIFY(NM_DBLCLK, ARXRLE_CURVE_XY_GRIDCTRL, OnGridDblClick)
	ON_NOTIFY(NM_RCLICK, ARXRLE_CURVE_XY_GRIDCTRL, OnGridRClick)
END_MESSAGE_MAP()


// ArxRleUiTdcCurveXY ��Ϣ�������

BOOL ArxRleUiTdcCurveXY::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect rc;
	m_gpGridCtrl.GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.DeflateRect(8,15,8,8);
	m_pGridCtrl->MoveWindow(rc);

	InitGridCtrl();

	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

int ArxRleUiTdcCurveXY::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAcUiTabChildDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_pGridCtrl = new CXTPGridControl;
	m_pGridCtrl->Create(CRect(),this,ARXRLE_CURVE_XY_GRIDCTRL);

	m_imgList.Create(ARXRLE_BMP_POKER, 16, 1, ILC_COLOR8 | ILC_MASK);
	m_pGridCtrl->SetImageList(&m_imgList);

	return 0;
}

void ArxRleUiTdcCurveXY::InitGridCtrl()
{
	m_pGridCtrl->SetEditable(FALSE);
	m_pGridCtrl->EnableSelection(FALSE);
	m_pGridCtrl->SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));
	m_pGridCtrl->SetRowCount(1); //��ʼΪ1��
	m_pGridCtrl->SetColumnCount(6); //��ʼ��Ϊ5��
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
					m_gvItem.strText.Format(_T("���"),col);
					m_pGridCtrl->SetColumnWidth(col,40);//�п�
				}
				else if(col == 1)
					m_gvItem.strText.Format(_T("���S"),col);
				else if(col == 2)
					m_gvItem.strText.Format(_T("ƫ��D"),col);
				else if(col == 3)
					m_gvItem.strText.Format(_T("����N/X"),col);
				else if(col == 4)
					m_gvItem.strText.Format(_T("����E/Y"),col);
				else if(col == 5)
					m_gvItem.strText.Format(_T("�����W"),col);
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
	m_curveElement.m_vecJDElement.clear();

	JDELEMENT jd;
	jd.JD = L"QD";
	jd.x = m_x1;
	jd.y = m_y1;
	jd.DK = m_QD;
	m_curveElement.m_vecJDElement.push_back(jd);
	jd.JD = L"JD";
	jd.x = m_x2;
	jd.y = m_y2;
	jd.DK = m_QZ;
	jd.Rc = m_R;
	jd.Ls1 = m_ls;
	m_curveElement.m_vecJDElement.push_back(jd);
	jd.JD = L"ZD";
	jd.x = m_x3;
	jd.y = m_y3;
	jd.DK = m_ZD;
	m_curveElement.m_vecJDElement.push_back(jd);
}

void ArxRleUiTdcCurveXY::OnBnClickedCurveXyBnData()
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

void ArxRleUiTdcCurveXY::OnBnClickedCurveXyBnImport()
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
			m_jdPathName=pathName;
		}
		m_curveElement.InputJDData(m_jdPathName);

		if(m_curveElement.m_vecJDElement.size() == 3)
		{
			m_x1 = m_curveElement.m_vecJDElement[0].x;
			m_y1 = m_curveElement.m_vecJDElement[0].y;
			m_QD = m_curveElement.m_vecJDElement[0].DK;
			m_x2 = m_curveElement.m_vecJDElement[1].x;
			m_y2 = m_curveElement.m_vecJDElement[1].y;
			m_x3 = m_curveElement.m_vecJDElement[2].x;
			m_y3 = m_curveElement.m_vecJDElement[2].y;
			m_ZD = m_curveElement.m_vecJDElement[2].DK;
			m_R = m_curveElement.m_vecJDElement[1].Rc;
			m_ls = m_curveElement.m_vecJDElement[1].Ls1;
		}

		UpdateData(FALSE);

		msgInf(L"����Ҫ�ص���ɹ���");
	}
}

void ArxRleUiTdcCurveXY::OnBnClickedCurveXyBnCalc() 
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

	m_curveElement.Calc_Point_dk();
	m_curveElement.Calc_Point_xy();
	m_curveElement.Calc_A_E_L();

	if(!m_openPathName.IsEmpty())
	{
		setlocale(LC_ALL,"");

		struct param
		{
			double ml;
			double oft;

			param(double _ml, double _oft)
			{
				ml = _ml;
				oft = _oft;
			}
			param()
			{
				ml = 0;
				oft=0;
			}
		};
		vector<param> vecParam;

		CStdioFile file;
		if(file.Open(m_openPathName, CFile::modeRead))
		{
			CString strLine;
			while(file.ReadString(strLine))
			{
				strLine.Trim();
				strLine.Replace(_T("��"), _T(";"));
				strLine.Replace(_T(","), _T(";"));
				strLine.Replace(_T("��"), _T(";"));
				if(strLine.GetLength() == 0)
					continue;

				CStringArray arrSubStr;
				int cnt = ParseSubStrByDelimiter(strLine, arrSubStr, ';');

				if(cnt == 2)
					vecParam.push_back(param(_tstof(arrSubStr[0]),_tstof(arrSubStr[1])));
				else
					vecParam.push_back(param());
			}

			file.Close();
		}

		m_pGridCtrl->SetRowCount(vecParam.size()+1);

		for (int row = 0; row < vecParam.size(); row++)
		{
			double* xys = m_curveElement.Calc_Curve_xy(vecParam[row].ml);
			CPt3d pt1(xys[0], xys[1]);
			xys = m_curveElement.Calc_Curve_xy(vecParam[row].ml + 0.01);
			CPt3d pt2(xys[0], xys[1]);

			double w = CPt3d::GetAngle(pt1,pt2);
			pt1 = CPt3d::GetLineEnd(pt1,vecParam[row].oft,w+PI/2);

			CString strGrid0,strGrid1,strGrid2,strGrid3,strGrid4,strGrid5;
			strGrid0.Format(_T("%d"),row);
			strGrid1 =  FormatStat(vecParam[row].ml);
			strGrid2.Format(_T("%.4f"),vecParam[row].oft);
			strGrid3.Format(_T("%.6f"),pt1.x);
			strGrid4.Format(_T("%.6f"),pt1.y);
			strGrid5 = FormatAngle(w*180/PI);

			m_pGridCtrl->SetItemText(row+1,0,strGrid0);
			m_pGridCtrl->SetItemText(row+1,1,strGrid1);
			m_pGridCtrl->SetItemText(row+1,2,strGrid2);
			m_pGridCtrl->SetItemText(row+1,3,strGrid3);
			m_pGridCtrl->SetItemText(row+1,4,strGrid4);
			m_pGridCtrl->SetItemText(row+1,5,strGrid5);

			m_pGridCtrl->SetItem(&m_gvItem); 
			m_pGridCtrl->SetRowHeight(row+1, 25);//�и�
			m_pGridCtrl->SetItemFormat(row+1,0,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,1,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,2,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,3,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,4,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,5,DT_CENTER);
		}
		m_pGridCtrl->Invalidate(FALSE);
		m_openPathName.Empty();
	}
	else
	{
		int cnt = INT((m_ZD-m_QD)/m_mDist)+1;
		m_pGridCtrl->SetRowCount(cnt+1);

		double mile = m_QD;
		for (int row = 0; row < cnt; row++)
		{
			double* xys = m_curveElement.Calc_Curve_xy(mile);

			CPt3d pt(xys[0], xys[1]);
			pt = CPt3d::GetLineEnd(pt,m_mOffset,PI/2.0);

			CString strGrid0,strGrid1,strGrid2,strGrid3,strGrid4,strGrid5;
			strGrid0.Format(_T("%d"),row);
			strGrid1 =  FormatStat(mile);
			strGrid2.Format(_T("%.4f"),m_mOffset);
			strGrid3.Format(_T("%.6f"),pt.x);
			strGrid4.Format(_T("%.6f"),pt.y);
			strGrid5 = FormatAngle(180/PI);

			m_pGridCtrl->SetItemText(row+1,0,strGrid0);
			m_pGridCtrl->SetItemText(row+1,1,strGrid1);
			m_pGridCtrl->SetItemText(row+1,2,strGrid2);
			m_pGridCtrl->SetItemText(row+1,3,strGrid3);
			m_pGridCtrl->SetItemText(row+1,4,strGrid4);
			m_pGridCtrl->SetItemText(row+1,5,strGrid4);

			m_pGridCtrl->SetItem(&m_gvItem); 
			m_pGridCtrl->SetRowHeight(row+1, 25);//�и�
			m_pGridCtrl->SetItemFormat(row+1,0,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,1,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,2,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,3,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,4,DT_CENTER);
			m_pGridCtrl->SetItemFormat(row+1,5,DT_CENTER);

			mile+=m_mDist;
		}
		m_pGridCtrl->Invalidate(FALSE);
	}

	m_L = m_curveElement.m_vecJDElement[1].L;
	m_A = m_curveElement.m_vecJDElement[1].A1;
	m_T = m_curveElement.m_vecJDElement[1].T1;
	m_E = m_curveElement.m_vecJDElement[1].E;
	m_W = m_curveElement.m_vecJDElement[1].pj;
	m_ZH = m_curveElement.m_vecJDElement[1].ZH;
	m_HY = m_curveElement.m_vecJDElement[1].HY;
	m_QZ = m_curveElement.m_vecJDElement[1].QZ;
	m_YH = m_curveElement.m_vecJDElement[1].YH;
	m_HZ = m_curveElement.m_vecJDElement[1].HZ;

	UpdateData(false);
}

void ArxRleUiTdcCurveXY::OnGridDblClick(NMHDR *pNMHDR, LRESULT* /*pResult*/)
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
			file.WriteString(L"���     ���     ƫ��     N/X     E/Y     W\n");

			for(int i = 1; i<m_pGridCtrl->GetRowCount();i++)
			{
				strTemp.Format(L"%4d  %10s  %8s  %16s  %16s  %10s\n",i,m_pGridCtrl->GetItemText(i,1),m_pGridCtrl->GetItemText(i,2),m_pGridCtrl->GetItemText(i,3),m_pGridCtrl->GetItemText(i,4),m_pGridCtrl->GetItemText(i,5));
				file.WriteString(strTemp);
			}

			file.Close();
		}

		msgInf(L"���ݵ����ɹ���");
	}
}

void ArxRleUiTdcCurveXY::OnGridRClick(NMHDR *pNMHDR, LRESULT* /*pResult*/)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_GRIDVIEW*pNM = (NM_GRIDVIEW*)pNMHDR;

	m_pGridCtrl->OnEditCopy();
}