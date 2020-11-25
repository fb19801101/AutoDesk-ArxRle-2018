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

#include "ArxRleUiTdcOvalElement.h"
#include "ArxRleUiTdmCurveElement.h"



// ArxRleUiTdcOvalElement �Ի���

IMPLEMENT_DYNAMIC(ArxRleUiTdcOvalElement, CAcUiTabChildDialog)

ArxRleUiTdcOvalElement::ArxRleUiTdcOvalElement()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
{
	m_A = 0.0;
	m_R1 = 2510.0;
	m_R2 = 750.0;
	m_HY_x = 0.0;
	m_HY_y = 0.0;
	m_x2 = 3521758.7959;
	m_x1 = 3520536.5760;
	m_y1 = 478164.7625;
	m_y2 = 476902.4628;
	m_YH_x = 0.0;
	m_YH_fwj = 0.0;
	m_YH_y = 0.0;
	m_dOpr = 0;
	m_HY_fwj = 0.0;
	m_ml_10 = _T("");
}

ArxRleUiTdcOvalElement::~ArxRleUiTdcOvalElement()
{
}

void ArxRleUiTdcOvalElement::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_ZA, m_A);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_R1, m_R1);
	DDV_MinMaxDouble(pDX, m_R1, 0., 10000000000.);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_R2, m_R2);
	DDV_MinMaxDouble(pDX, m_R2, 0., 10000000000.);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_HY_N, m_HY_x);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_HY_E, m_HY_y);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_N1, m_x1);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_N2, m_x2);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_E1, m_y1);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_E2, m_y2);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_YH_N, m_YH_x);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_YH_W, m_YH_fwj);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_YH_E, m_YH_y);
	DDX_Radio(pDX, ARXRLE_OVAL_ELEMENT_RO_ZR, m_dOpr);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_HY_W, m_HY_fwj);
	DDX_Text(pDX, ARXRLE_OVAL_ELEMENT_EB_RET, m_ml_10);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcOvalElement, CAcUiTabChildDialog)
	ON_BN_CLICKED(ARXRLE_OVAL_ELEMENT_BN_CALC, OnBnClickedOvalElementBnCalc)
END_MESSAGE_MAP()


// ArxRleUiTdcOvalElement ��Ϣ�������

BOOL ArxRleUiTdcOvalElement::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void ArxRleUiTdcOvalElement::OnBnClickedOvalElementBnCalc() 
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	int k = 1;

	m_fwj = fwj( m_x1, m_y1,m_x2,m_y2);//����Բ�����ߵ����귽λ��

	m_E_R = sqrt((m_x1 - m_x2) * (m_x1 - m_x2) + (m_y1 - m_y2) * (m_y1 - m_y2));//�����Բ�ĵľ���

	m_E = fabs(fabs(m_R1 - m_R2) - m_E_R);//����Բ����ľ���

	m_A1 = pow(24.0 * m_E  *m_R1 * m_R1 * m_R1 * m_R2 * m_R2 * m_R2
		/ (m_R2 - m_R1) / (m_R2 - m_R1) / fabs(m_R2 - m_R1), 0.25);//�����A�Ľ���ֵ

	if(min(m_R1, m_R2) / max(m_R1, m_R2) < 0.2||min(m_R1, m_R2) / max(m_R1, m_R2) > 0.8)
	{
		msgErr(L"��ȷ����Բ���߰뾶֮����0.2��0.8֮�䣬������淶Ҫ��");//����뾶֮���Ƿ���0.2��0.8֮��
	}

	else if (m_E_R==0||m_E_R>=fabs(m_R1 - m_R2))
	{
		AfxMessageBox(L"�����������Բλ�ù�ϵ�����ں����޷����������ߣ�����������");//�ж��ܷ񹹳���������

	}
	else if(m_E / min(m_R1, m_R2) < 0.003||m_E / min(m_R1, m_R2) > 0.03)
	{
		AfxMessageBox(L"��ȷ����Բ���ߵ���С�����СԲ�뾶֮����0.003��0.03֮�䣬������淶Ҫ��");//������Բ���ߵ���С�����СԲ�뾶֮����0.003��0.03֮��
	}

	else
	{
		do
		{
			m_A2 = m_A1;
			m_A1 = m_A2-f(m_A2, m_R1, m_R2, m_E_R * m_E_R) / df(m_A2, m_R1, m_R2);//ţ�ٵ�����ʽ
			k++;
		}
		while(fabs(m_A1  -m_A2) > 0.00000001&&k < 10000000);//���0.001m,��������1000000
		if(k>=10000000)//��������Ƿ�ɹ�
		{
			AfxMessageBox(L"ţ�ٵ���ʧ��");

		}
		else
		{
			m_A = m_A1;
			if (m_A > min(m_R1, m_R2)||m_A < min(m_R1, m_R2) /2.0)//��������Ĳ���A�Ƿ�����淶Ҫ��
			{
				AfxMessageBox(L"ע�⣺�������Aֵ������淶Ҫ��,A�����㣺С�뾶/2<= A <=С�뾶");
			}
			else
			{
				m_lo = m_A * m_A * fabs(m_R1 - m_R2) / m_R1/ m_R2;//�󻺺����߳�
			}
		}

		int n = m_lo /10;//���㻺������10m�ε�����
		double **Point;
		Point = new double*[n];
		for(int i = 0;i< n;i++) //������̬����,�洢����YH����10�״���׮�ŵ����ꡢ���߷�λ��
		{
			Point[i] = new double[3];
		}
		for(int i = 0;i < n;i++)//����Ԫ�س�ʼ��
		{
			for(int j = 0;j < 3;j++)
			{
				Point[i][j] = 0;
			}
		}
		switch (m_dOpr)
		{
		case 0:  //��ת
			if(m_R1 > m_R2)
			{
				m_YH_x = m_x1 + m_R1 * cos(m_fwj * PI / 180.0 + (atan((d_t(m_A, 
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A, 
					m_R1) - e_r(m_A, m_R2))) - m_A*m_A / 2 / m_R1 / m_R1));//YH�㾭��

				m_YH_y = m_y1 + m_R1 * sin(m_fwj * PI / 180.0  +(atan((d_t(m_A, 
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A*m_A / 2 / m_R1 / m_R1));//YH��γ��

				m_HY_x = m_x2 + m_R2 * cos(m_fwj * PI / 180.0 + (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A*m_A / 2 / m_R2 / m_R2));//HY�㾭��

				m_HY_y = m_y2 + m_R2 * sin(m_fwj * PI / 180.0 + (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R2 / m_R2));//HY��γ��

				m_YH_fwj = ((m_fwj * PI / 180.0 + (atan((d_t(m_A, 
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A, 
					m_R1) - e_r(m_A,m_R2))) - m_A * m_A /2 / m_R1 / m_R1))) * 180 / PI - 90;//YH�����߷�λ��
				if(m_YH_fwj>=360)//�ѷ�λ��ת����0-360֮��
				{
					m_YH_fwj = m_YH_fwj - 360;
				}
				if(m_YH_fwj < 0)
				{
					m_YH_fwj = m_YH_fwj + 360;
				}
				m_HY_fwj = ((m_fwj * PI / 180.0 + (atan((d_t(m_A,
					m_R2) - d_t(m_A,m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A , m_R2))) - m_A*m_A / 2/ m_R2/ m_R2))) * 180 / PI - 90;//HY�����߷�λ��
				if(m_HY_fwj>=360)//�ѷ�λ��ת����0-360֮��
				{
					m_HY_fwj = m_HY_fwj - 360;
				}
				if(m_HY_fwj < 0)
				{
					m_HY_fwj = m_HY_fwj + 360;
				}

				for(int i = 0;i < n; i++)
				{
					Point[i][0] = x1_r1_big_r2(m_YH_x, m_R1, m_YH_fwj * PI / 180, m_A, 10 * (i +1 ), -1);//����YH����10�״���׮�ŵľ���
					Point[i][1] = y1_r1_big_r2(m_YH_y, m_R1, m_YH_fwj * PI / 180, m_A, 10 * (i + 1), -1);//����YH����10�״���׮�ŵ�γ��
					Point[i][2] = fwj_t1(m_YH_fwj * PI / 180, m_A, m_R1, 10 * (i + 1), -1);//����YH����10�״������߷�λ��
				}
			}



			//--------------------------------------------------------------------------------------------------------------------------------------
			if(m_R1 < m_R2)
			{
				m_YH_x = m_x1 + m_R1 * cos(m_fwj * PI / 180.0 + PI - (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A, 
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R1 / m_R1));//YH�㾭��

				m_YH_y = m_y1 + m_R1 * sin(m_fwj * PI / 180.0 + PI - (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R1 / m_R1));//YH��γ��

				m_HY_x = m_x2 + m_R2 * cos(m_fwj * PI / 180.0 + PI-(atan((d_t(m_A, 
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A, 
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R2 / m_R2));//HY�㾭��

				m_HY_y = m_y2 + m_R2 * sin(m_fwj * PI / 180.0 + PI - (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A, 
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2/ m_R2 / m_R2));//HY��γ��

				m_YH_fwj = ((m_fwj * PI / 180.0 + PI - (atan((d_t(m_A, 
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A, 
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R1 / m_R1))) * 180 / PI - 90;//YH�����߷�λ��
				if(m_YH_fwj >= 360)//�ѷ�λ��ת����0-360֮��
				{
					m_YH_fwj = m_YH_fwj - 360;
				}
				if(m_YH_fwj < 0)
				{
					m_YH_fwj = m_YH_fwj + 360;
				}
				m_HY_fwj = ((m_fwj * PI/180.0 + PI - (atan((d_t(m_A, 
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R2 / m_R2))) * 180 / PI - 90;//HY�����߷�λ��
				if(m_HY_fwj>=360)//�ѷ�λ��ת����0-360֮��
				{
					m_HY_fwj = m_HY_fwj - 360;
				}
				if(m_HY_fwj < 0)
				{
					m_HY_fwj = m_HY_fwj + 360;
				}	
				for(int i = 0;i < n; i++)
				{
					Point[i][0] = x2_r2_big_r1(m_YH_x, m_R1, m_YH_fwj * PI / 180, m_A, 10 * (i + 1), -1);//����YH����10�״���׮�ŵľ���
					Point[i][1] = y2_r2_big_r1(m_YH_y, m_R1, m_YH_fwj * PI / 180, m_A, 10 * (i + 1), -1);//����YH����10�״���׮�ŵ�γ��
					Point[i][2] = fwj_t2(m_YH_fwj * PI /180, m_A, m_R1, 10 * (i + 1), -1);//����YH����10�״������߷�λ��
				}
			}		
			//-------------------------------------------------------------------------------------------------------------------------------------------
			break;
			//------------------------------------------------------------------------------------------------------------------------------------------------------------------
		case 1://��ת

			//--------------------====================================-----------------------------------------------------------------------------------------
			if(m_R1 > m_R2)
			{
				m_YH_x = m_x1 + m_R1 * cos(m_fwj * PI / 180.0 - (atan((d_t(m_A, 
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A, 
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R1 / m_R1));//YH�㾭��

				m_YH_y = m_y1 + m_R1 * sin(m_fwj * PI / 180.0 - (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R1 / m_R1));//YH��γ��

				m_HY_x = m_x2 + m_R2 * cos(m_fwj * PI / 180.0 - (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 /m_R2 / m_R2));//HY�㾭��

				m_HY_y = m_y2 + m_R2 * sin(m_fwj * PI / 180.0 - (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 /m_R2 / m_R2));//HY��γ��

				m_YH_fwj = ((m_fwj * PI / 180.0 - (atan((d_t(m_A, 
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R1 / m_R1))) * 180 / PI + 90;//YH�����߷�λ��
				if(m_YH_fwj>=360)//�ѷ�λ��ת����0-360֮��
				{
					m_YH_fwj = m_YH_fwj - 360;
				} 
				if(m_YH_fwj < 0)
				{
					m_YH_fwj = m_YH_fwj + 360;
				}

				m_HY_fwj = ((m_fwj * PI / 180.0 - (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R2 / m_R2))) * 180 / PI + 90;//HY�����߷�λ��
				if(m_HY_fwj>=360)//�ѷ�λ��ת����0-360֮��
				{
					m_HY_fwj = m_HY_fwj - 360;
				}
				if(m_HY_fwj < 0)
				{
					m_HY_fwj = m_HY_fwj + 360;
				}
				for(int i = 0;i < n; i++)
				{
					Point[i][0] = x1_r1_big_r2(m_YH_x, m_R1, m_YH_fwj * PI / 180, m_A, 10 * ( i + 1), 1);//����YH����10�״���׮�ŵľ���
					Point[i][1] = y1_r1_big_r2(m_YH_y, m_R1, m_YH_fwj * PI / 180, m_A, 10 * (i + 1), 1);//����YH����10�״���׮�ŵ�γ��
					Point[i][2] = fwj_t1(m_YH_fwj * PI / 180, m_A, m_R1, 10 * (i + 1),1);//����YH����10�״������߷�λ��
				}
			}
			if(m_R1 < m_R2)
			{
				//	double a=atan((d_t(m_A,m_R2)-d_t(m_A,m_R1))/(m_R1-m_R2+e_r(m_A,m_R1)-e_r(m_A,m_R2)))*180/PI;

				m_YH_x = m_x1 + m_R1 * cos(m_fwj * PI / 180.0 + PI + (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A, 
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R1 / m_R1));//YH�㾭��

				m_YH_y = m_y1 + m_R1 * sin(m_fwj * PI / 180.0 + PI + (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R1 / m_R1));//YH��γ��

				m_HY_x = m_x2 + m_R2 * cos(m_fwj * PI / 180.0 + PI + (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R2 / m_R2));//HY�㾭��

				m_HY_y = m_y2 + m_R2 * sin(m_fwj * PI / 180.0 + PI + (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R2 / m_R2));//HY��γ��

				m_YH_fwj = ((m_fwj * PI / 180.0 + PI + (atan((d_t(m_A,
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R1 / m_R1))) * 180 / PI + 90;//YH�����߷�λ��
				if(m_YH_fwj >= 360)//�ѷ�λ��ת����0-360֮��
				{
					m_YH_fwj = m_YH_fwj - 360;
				}
				if(m_YH_fwj < 0)
				{
					m_YH_fwj = m_YH_fwj + 360;
				}

				m_HY_fwj = ((m_fwj * PI / 180.0 + PI + (atan((d_t(m_A, 
					m_R2) - d_t(m_A, m_R1)) / (m_R1 - m_R2 + e_r(m_A,
					m_R1) - e_r(m_A, m_R2))) - m_A * m_A / 2 / m_R2 / m_R2))) * 180 / PI + 90;//HY�����߷�λ��
				if(m_HY_fwj >= 360)//�ѷ�λ��ת����0-360֮��
				{
					m_HY_fwj = m_HY_fwj - 360;
				}
				if(m_HY_fwj < 0)
				{
					m_HY_fwj = m_HY_fwj + 360;
				}
				for(int i = 0;i < n; i++)
				{
					Point[i][0] = x2_r2_big_r1(m_YH_x, m_R1, m_YH_fwj * PI/180, m_A, 10 * (i + 1), 1);//����YH����10�״���׮�ŵľ���
					Point[i][1] = y2_r2_big_r1(m_YH_y, m_R1, m_YH_fwj * PI/180, m_A, 10 * (i + 1), 1);//����YH����10�״���׮�ŵ�γ��
					Point[i][2] = fwj_t2(m_YH_fwj * PI / 180, m_A, m_R1, 10*  (i + 1), 1);//����YH����10�״������߷�λ��
				}
			}

			break;
		}

		//-----------------------------------------------------------------------------------------------------------------------------------
		CString tmp,tmp1,tmp2,str;
		tmp = str = tmp1 = tmp2 = "";//��ʼ��
		//g="����YH��";
		str = str + "                     ����(E/X)";
		str = str + "         γ��(N/Y)"+"         ���߷�λ��";
		str = str + "\r\n" + "����YH��10�״� ";
		for(int t = 0;t < n;t++)
		{
			if(t < n - 1)
			{
				tmp1.Format(L"%d", 10 * (t + 2));
				tmp2 = tmp1;
			}
			for(int j = 0;j < 3;j++)
			{
				tmp.Format(L"%lf ", Point[t][j]);
				str+=tmp;
			}
			str = str + "\r\n";

			if(t < n - 1)
			{
				str = str + "����YH��" + tmp2 + "�״� ";
			}
			//this->m_ml_10 = str;//�ѽ��������༭����
		}
		this->m_ml_10 = str;//�ѽ��������༭����
	}	
	UpdateData(false);
}

double ArxRleUiTdcOvalElement::e_r(double x,double r)//��Բ����������
{
	return pow(x, 4) / 24 / pow(r, 3);
}

double ArxRleUiTdcOvalElement::d_t(double x,double r)//���д���
{
	return x * x/ 2 / r - pow(x, 6) / 240 / pow(r, 5);
}

double ArxRleUiTdcOvalElement::f(double x,double r1,double r2,double l)//ţ�ٵ������е�ԭ����
{
	return pow((r1 - r2 + e_r(x, r1) - e_r(x, r2)), 2) + pow((d_t(x, r2) - d_t(x, r1)),2) - l;
}

double ArxRleUiTdcOvalElement::df(double x,double r1,double r2)//ţ�ٵ������еĵ�����
{
	return 2 * (r1 - r2 + e_r(x, r1) - e_r(x, r2)) * (4*e_r(x, r1) / x - 4 * e_r(x, r2) / x)
		+ 2 * (d_t(x, r2) - d_t(x, r1)) * (x / r2 - pow(x, 5)/ 40 / pow(r2, 5)- x / r1 + pow(x, 5) / 40 / pow(r1, 5));
}

double ArxRleUiTdcOvalElement::fwj(double x1,double y1,double x2,double y2)//��λ��                  
{
	if((x2 - x1) > 0&&(y2 - y1) >= 0)
		return atan((y2 - y1) / (x2 - x1)) * 180 / PI;

	else if((x2 - x1) > 0&&(y2 - y1) < 0)
		return atan((y2 - y1) / (x2 - x1)) * 180 / PI + 360;

	else if((x2 - x1) < 0&&(y2 - y1) != 0)
		return atan((y2 - y1) / (x2 - x1)) * 180 / PI + 180;

	else if((x2 - x1) < 0&&(y2 - y1) == 0)
		return 180;

	else if((x2 - x1) == 0&&(y2 - y1) > 0)
		return 90; 

	else if((x2 - x1) == 0&&(y2 - y1) < 0)
		return 270;
	else
		msgErr(L"Ϊͬһ��");

	return 0;
}

double ArxRleUiTdcOvalElement::x1_r1_big_r2(double x,double r,double a,double A,double l,int sf)//���R1>R2ʱ������������һ��X����
{
	double ls = A * A / r;
	double lb = ls + l;
	double x1 = ls - pow(ls, 5) / 40 / pow(A, 4) + pow(ls, 9) / 3456 / pow(A, 8);
	double y1=pow(ls, 3) / 6 / A / A - pow(ls, 7) / 336 / pow(A, 6) + pow(ls, 11) / 42240 / pow(A, 10);

	double x2 = lb - pow(lb, 5) / 40 / pow(A, 4) + pow(lb, 9) / 3456 / pow(A, 8);
	double y2 = pow(lb, 3) / 6 / A / A - pow(lb, 7) / 336 / pow(A, 6) + pow(lb, 11) / 42240 / pow(A, 10);
	double ab = a + sf * (lb * lb / 2 / r / ls - ls / 2 / r);
	return x + (x2 - x1) * cos(a - sf * ls / 2 / r) + (y2 - y1) * cos(a - sf * ls / 2 / r + sf * 0.5 * PI);
}

double ArxRleUiTdcOvalElement::y1_r1_big_r2(double y,double r,double a,double A,double l,int sf)//���R1>R2ʱ������������һ��Y����
{
	double ls = A * A / r;
	double lb = ls + l;
	double x1 = ls - pow(ls, 5) / 40 / pow(A, 4) + pow(ls, 9) / 3456 / pow(A, 8);
	double y1 = pow(ls, 3) / 6 / A / A - pow(ls, 7) / 336 / pow(A, 6) + pow(ls, 11) / 42240 / pow(A, 10);

	double x2 = lb - pow(lb, 5) / 40 / pow(A, 4) + pow(lb, 9) / 3456 / pow(A, 8);
	double y2=pow(lb, 3) / 6 / A / A - pow(lb, 7) / 336 / pow(A, 6) + pow(lb, 11) / 42240 / pow(A, 10);
	double ab = a + sf * (lb * lb / 2 / r / ls - ls / 2 / r);
	return y + (x2 - x1) * sin(a - sf * ls / 2 / r) + (y2 - y1) * sin(a - sf * ls / 2 / r + sf * 0.5 * PI);
}

double ArxRleUiTdcOvalElement::x2_r2_big_r1(double x,double r,double a,double A,double l,int sf)//���R1<R2ʱ������������һ��X����
{
	double ls = A * A / r;
	double lb = ls - l;
	double x1 = ls - pow(ls, 5) / 40 / pow(A, 4) + pow(ls, 9) / 3456 / pow(A, 8);
	double y1 = pow(ls, 3) / 6 / A / A - pow(ls, 7) / 336 / pow(A, 6) + pow(ls, 11) / 42240 / pow(A, 10);

	double x2 = lb - pow(lb, 5) / 40 / pow(A, 4) + pow(lb, 9) / 3456 / pow(A, 8);
	double y2 = pow(lb, 3) / 6 / A / A - pow(lb, 7) / 336 / pow(A, 6) + pow(lb, 11) / 42240 / pow(A, 10);
	double ab = a + sf * (ls / 2 / r - lb * lb / 2/ r / ls);
	return x + (x1 - x2) * cos(a + sf * ls / 2 / r) + (y1 - y2) * cos(a + sf * ls / 2 / r - sf * 0.5 * PI);
}

double ArxRleUiTdcOvalElement::y2_r2_big_r1(double y,double r,double a,double A,double l,int sf)//���R1<R2ʱ������������һ��Y����
{
	double ls = A * A / r;
	double lb = ls - l;
	double x1 = ls - pow(ls, 5) / 40 / pow(A, 4) + pow(ls, 9) / 3456 / pow(A, 8);
	double y1 = pow(ls, 3) / 6 / A / A - pow(ls, 7) / 336 / pow(A, 6) + pow(ls, 11) / 42240 / pow(A, 10);

	double x2 = lb - pow(lb, 5) / 40 / pow(A, 4) + pow(lb, 9) / 3456 / pow(A, 8);
	double y2 = pow(lb, 3) / 6 / A / A - pow(lb, 7) / 336 / pow(A, 6) + pow(lb, 11) / 42240 / pow(A, 10);
	double ab = a + sf * (ls / 2 / r - lb * lb / 2 / r / ls);
	return y + (x1 - x2) * sin(a + sf * ls / 2 / r) + (y1 - y2) * sin(a + sf * ls / 2 / r - sf * 0.5 * PI);
}

double ArxRleUiTdcOvalElement::fwj_t1(double a,double A,double r,double l,int sf)//��R1>R2ʱ���������������������߷�λ��
{
	double ls = A * A / r;
	double lb = ls + l;
	return (a + sf * (lb * lb / 2 / r / ls - ls / 2 / r)) * 180 / PI;
}

double ArxRleUiTdcOvalElement::fwj_t2(double a,double A,double r,double l,int sf)//��R1<R2ʱ���������������������߷�λ��
{
	double ls = (A * A / r);
	double lb = (ls - l);
	return (a + sf * ((A * A / r) / 2 / r - lb * lb / 2 / r / (A * A / r))) * 180 / PI;
}
