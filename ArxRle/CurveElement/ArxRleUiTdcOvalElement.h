// ArxRleUiTdcOvalElement.h: interface for the ArxRleUiTdcOvalElement class.
//

#ifndef ARXRLE_UITDC_OVAL_ELEMENT_H
#define ARXRLE_UITDC_OVAL_ELEMENT_H

#include "Resource.h"
#include "App/ArxRleListCtrl.h" 

// ArxRleUiTdcOvalElement �Ի���

class ArxRleUiTdcOvalElement : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcOvalElement)

public:
	ArxRleUiTdcOvalElement();   // ��׼���캯��
	virtual ~ArxRleUiTdcOvalElement();

	static double e_r(double x,double r);//��������
	static double d_t(double x,double r);//���д���
	static double f(double x,double r1,double r2,double l);//���ڲ���A�ķ���
	static double df(double x,double r1,double r2);//���ڲ���A�ķ��̵���
	static double fwj(double x1,double y1,double x2,double y2);//��λ��  
	static double x1_r1_big_r2(double x0,double r,double a,double A,double l,int sf);//���R1>R2ʱ������������һ��X����
	static double y1_r1_big_r2(double y0,double r,double a,double A,double l,int sf);//���R1>R2ʱ������������һ��Y����
	static double x2_r2_big_r1(double x0,double r,double a,double A,double l,int sf);//���R1<R2ʱ������������һ��X����
	static double y2_r2_big_r1(double y0,double r,double a,double A,double l,int sf);//���R1<R2ʱ������������һ��Y����
	static double fwj_t1(double a,double A,double r,double l,int sf);//��R1>R2ʱ���������������������߷�λ��
	static double fwj_t2(double a,double A,double r,double l,int sf);//��R1<R2ʱ���������������������߷�λ��

// �Ի�������
	enum { IDD = ARXRLE_TDC_OVAL_ELEMENT };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOvalElementBnCalc();
	DECLARE_MESSAGE_MAP()

private:
	ArxRleListCtrl m_wndList;

	double m_fwj;
	double m_A1,m_A2;
	double m_lo;
	double m_E;
	double m_E_R;

	double	m_A;
	double	m_R1,m_R2;
	double	m_HY_x,m_HY_y,m_HY_fwj;
	double	m_x1,m_x2;
	double	m_y1,m_y2;
	double	m_YH_x,m_YH_y,m_YH_fwj;
	int		m_dOpr;
	CString	m_ml_10;
};

#endif //ARXRLE_UITDC_OVAL_ELEMENT_H
