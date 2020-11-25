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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleCoord.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
ArxRleCoord::ArxRleCoord()
{
	Init(0.0,0.0,0.0);
}

ArxRleCoord::~ArxRleCoord()
{

}

void ArxRleCoord::Init(double val1,double val2,double val3)
{
    this->val1 = val1;
	this->val2 = val2;
    this->val3 = val3;
}

ArxRleCoord::ArxRleCoord(double val1, double val2, double val3, DWORD dwDataType)
{
	if(dwDataType == DT_DMS)
		Init(DMSToRadian(val1),DMSToRadian(val2),DMSToRadian(val3));
	else 
		Init(val1,val2,val3);
}
void ArxRleCoord::Input(double val1, double val2, double val3,DWORD dwDataType )
{
	if(dwDataType == DT_DMS)
		Init(DMSToRadian(val1),DMSToRadian(val2),val3);
	else 
		Init(val1,val2,val3);
}

void ArxRleCoord::SetValue(double val1, double val2, double val3)
{
	Init(val1,val2,val3);
}

double ArxRleCoord::RadianToDMS(double r)
{
   double t = r*180/PI;
   int d = (int)t;
   int m = (int)((t - d ) * 60);
   double s = (((t-d)*60)-m)*60;
   if(60.0-s<0.01)
   {
	   s = 0.0;
	   m ++;
	   if(m = 60)
	   {
		   d++;
		   m = 0;
	   }
   }
   return ((double)d+(double)m*0.01+(double)s*0.0001);
}

double ArxRleCoord::DMSToRadian(double dms)
{
	int d = (int)dms;
	int m = (int)((dms -d) * 100);
	double s = ((dms - d) * 100 - m) * 100;
	return ((double)d+(double)m/60+s/3600)*PI/180;
}

void ArxRleCoord::EarthToSpace(double e2, double a)
{	
	double B = val1;
	double L = val2;
	double H = val3;
	double W = sqrt(1 - e2 * sin(B) * sin(B));
	double N = a / W;
	val1 = (N + H) * cos(B) * cos(L);
	val2 = (N + H) * cos(B) * sin(L);
	val3 = (N * (1-e2) + H) * sin(B);
}


void ArxRleCoord::SpaceToEarth(double e2, double a)
{
    double W = sqrt(1 - e2 * sin(val1) * sin(val1));
    double N = a / W;
	double X = val1;
	double Y = val2;
	double Z = val3;
	double m ;
	m = sqrt(pow(X,2)+pow(Y,2));
	val2 = atan(Y/X);
	if(val2<0) val2 +=PI;
	double e2_ = e2/(1-e2);
	double c = a*sqrt(1+e2_);
	double ce2 = c*e2;
	double k = 1+e2_;
	double front = Z/m;
	double temp = front;
	int count = 0;
	do
	{
		front = temp;
		m = sqrt(pow(X,2)+pow(Y,2));
		temp = Z/m + ce2*front/(m*sqrt(k+pow(front,2)));
		count ++;
	}
	while(fabs(temp - front)>LIMIT&&count<100000);//是否在允许误差内
	val1 = atan(temp);
	if(val1<0) val1 += PI;
	W = sqrt(1 - e2 * sin(val1) * sin(val1));
    N = a / W;
	val3 = m/cos(val1) - N;
}

void ArxRleCoord::EarthToGauss(double e2, double a,double L0)
{	
	double B = val1;
	double L = val2;
	double l = L - L0;
	double B_2=RadianToSecond(B);
	double CB2=cos(B)*cos(B);
	double l2=l*l;
	double N=6399698.902-(21562.267-(108.973-0.612*CB2)*CB2)*CB2;
	double a0=32140.404-(135.3302-(0.7092-0.0040*CB2)*CB2)*CB2;
	double a4=(0.25+0.00252*CB2)*CB2-0.04166;
	double a6=(0.166*CB2-0.084)*CB2;
	double a3=(0.3333333+0.001123*CB2)*CB2-0.1666667;
	double a5=0.0083-(0.1667-(0.1968+0.004*CB2)*CB2)*CB2;
	val1=6367558.4969*B_2/P_2-(a0-(0.5+(a4+a6*l2)*l2)*l2*N)*sin(B)*cos(B);
	val2=(1+(a3+a5*l2)*l2)*l*N*cos(B);	
	val2+=500000;
}

double ArxRleCoord::RadianToSecond(double r)
{
	return r*3600*180/PI;
}


void ArxRleCoord::GaussToEarth(double L0)
{
	val2 -=500000;
	double x = val1;
	double y = val2;
	double b = x/6367558.4969;
	double b_2 = b*180*3600/PI;//b_2以秒为单位
	double Cb2=cos(b)*cos(b);
	double Bf_2=b_2+(50221746+(293622+(2350+22*Cb2)*Cb2)*Cb2)*pow((long double)10,(int)-10)*sin(b)*cos(b)*P_2;
    double Bf=Bf_2*PI/(180*3600);
	double CBf2=cos(Bf)*cos(Bf);
	double Nf=6399698.902-(21562.267-(108.973-0.612*CBf2)*CBf2)*CBf2;
	double Z=y/(Nf*cos(Bf));
	double b2=(0.5+0.003369*CBf2)*sin(Bf)*cos(Bf);
	double b3=0.333333-(0.166667-0.00123*CBf2)*CBf2;
	double b4=0.25+(0.16161+0.00562*CBf2)*CBf2;
	double b5=0.2-(0.1667-0.0088*CBf2)*CBf2;
	double Z2=Z*Z;
	val1=Bf_2-(1-(b4-0.12*Z2)*Z2)*Z2*b2*P_2;
	val1 = val1*PI/(180*3600);
	double l=(1-(b3-b5*Z2)*Z2)*Z*P_2;
	l = l*PI/(180*3600);
	val2=L0+l;	
}

void ArxRleCoord::Output(double &val1, double &val2, double &val3, DWORD dwDataType)
{
	CString str;
	if(dwDataType == DT_DMS)
	{
		val1 = RadianToDMS(this->val1);
		val2 = RadianToDMS(this->val2);
		str.Format(L"%.8lf",val1);
		val1 = _tstof(str);
		str.Format(L"%.8lf",val2);
		val2 = _tstof(str);
		str.Format(L"%.4lf",this->val3);
		val3 = _tstof(str);
	}
	else if(dwDataType == DT_LENGTH)
	{
		str.Format(L"%.4lf",this->val1);
		val1 = _tstof(str);
		str.Format(L"%.4lf",this->val2);
		val2 = _tstof(str);
		str.Format(L"%.4lf",this->val3);
		val3 = _tstof(str);
	}
}

double ArxRleCoord::GetMeridian()
{
	if(val2<0)
	{
	AfxMessageBox(L"数据错误");
	return -1;
	}
	double L1= val2*180/PI;
	int L2 = (int)L1;
	double left = L1 - L2;
	int num = L2 / 3;
	left += L2 % 3;
	if (left>=1.5) num++;
	return num*3;
}

void ArxRleCoord::CmpRot(ArxRleMatrix &m, Rot &r)
{
	int n = m.GetNumRows();
	ArxRleMatrix B(3*n,7);
	ArxRleMatrix L(3*n,1);
	for(int i = 0; i<n; i++)
	{
		double a[7] = {1,0,0,m(i,0),0,-m(i,2),m(i,1)};
		double b[7] = {0,1,0,m(i,1),m(i,2),0,-m(i,0)};
		double c[7] = {0,0,1,m(i,2),-m(i,1),m(i,0),0};
		B.SetRow(3*i,a);
		B.SetRow(3*i+1,b);
		B.SetRow(3*i+2,c);
		L.SetElement(3*i,0,m(i,3));
		L.SetElement(3*i+1,0,m(i,4));
		L.SetElement(3*i+2,0,m(i,5));
	}  
	ArxRleMatrix R(7,1);
	R = (B.T()*B).Getinv()*B.T()*L;
	r.dx = -R(0,0);
	r.dy = -R(1,0);
	r.dz = -R(2,0);
	r.m  = 1-R(3,0) ;
	r.rx = -R(4,0)/R(3,0);
	r.ry = -R(5,0)/R(3,0);
	r.rz = -R(6,0)/R(3,0);
	CString str;
	str.Format(L"%8.4lf",r.dx);
	r.dx = _tstof(str);
	str.Format(L"%8.4lf",r.dy);
	r.dy = _tstof(str);
	str.Format(L"%8.4lf",r.dz);
	r.dz = _tstof(str);
	str.Format(L"%8.4lf",r.rx);
	r.rx = _tstof(str);
	str.Format(L"%8.4lf",r.ry);
	r.ry = _tstof(str);
	str.Format(L"%8.4lf",r.rz);
	r.rz = _tstof(str);
	str.Format(L"%8.4lf",r.m);
	r.m = _tstof(str);
}

void ArxRleCoord::SpaceToSpace(Rot&r)
{
	double X = val1;
	double Y = val2;
	double Z = val3;
	val1 = (1+r.m)*(X+r.rz*Y-r.ry*Z)+r.dx;
	val2 = (1+r.m)*(-r.rz*X+Y+r.rx*Z)+r.dy;
	val3 = (1+r.m)*(r.ry*X-r.rx*Y+Z)+r.dz;
}

void ArxRleCoord::Output(CString &val1, CString &val2, CString &val3, DWORD dwDataType)
{	
	CString str;
	if(dwDataType == DT_DMS)
	{
		double temp;
		temp = RadianToDMS(this->val1);
		val1.Format(L"%.8lf",temp);
		temp = RadianToDMS(this->val2);
		val2.Format(L"%.8lf",temp);
		val3.Format(L"%.4lf",this->val3);
	}
	else if(dwDataType == DT_LENGTH)
	{
		val1.Format(L"%.4lf",this->val1);
		val2.Format(L"%.4lf",this->val2);
		val3.Format(L"%.4lf",this->val3);
	}
}

void ArxRleCoord::Input(CString val1, CString val2, CString val3, DWORD dwDataType)
{
	if(dwDataType == DT_DMS)
		Init(DMSToRadian(_tstof(val1)),DMSToRadian(_tstof(val2)),_tstof(val3));
	else 
		Init(_tstof(val1),_tstof(val2),_tstof(val3));
}
