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

#ifndef ARXRLE_COORD_H
#define ARXRLE_COORD_H

#include <math.h>
#include "ArxRleMatrix.h"
#define ER_VALID		0x000000FFL
#define ER_WGS84        0x00000001L//EllipsoidReference
#define ER_BJ54			0x00000002L
#define ER_C80			0x00000004L

#define CRD_VALID       0x0000FF00L
#define CRD_SPACE		0x00000100L//CoordinateSystem
#define CRD_EARTH		0x00000200L		
#define CRD_GAUSS		0x00000400L

#define DT_VALID		0x00FF0000L
#define DT_DMS			0x00010000L//DataForm
#define DT_RADIAN		0x00020000L 
#define DT_LENGTH		0x00040000L

#define P_2			(3600*180/PI)//��ֵ
#define PI			3.1415926535897932384626433832795
#define WGS84_A		6378137.0000000000 //WGS-84�����峤����a
#define WGS84_E2	0.0066943799013  //WGS-84����ƫ����e��ƽ��
#define C80_A		6378140.0000000000//ȫ��1980��������ϵ(1975����������)����
#define C80_E2		0.006694384999588 
#define BJ54_A		6378245.0000000000//BJ54(��������˹��)����
#define BJ54_E2		0.006693421622966
#define LIMIT		tan(0.0001*PI/(3600*180))//������������0.0001��
typedef struct ROTATE
{
	double dx;
	double dy;
	double dz;
	double rx;
	double ry;
	double rz;
	double m;
}Rot;
class ArxRleCoord : public CObject  
{
private:
   	double val1;
	double val2;
	double val3;//����ֵ�����Ȼ�ȷ�����д��ʽ��
	//����ϵ��ز�������������54��ȫ��80��WGS84�µĿռ�ֱ�ǡ�����������˹ͶӰ���꣩
public:
	void Input(CString val1,CString val2,CString val3,DWORD dwDataType);
	void Output(CString &val1,CString &val2,CString &val3,DWORD dwDataType);

	void SpaceToSpace(Rot &r);
	void CmpRot(ArxRleMatrix &m, Rot &r);
	double GetMeridian();//��ȡ3�ȴ�����������
	double DMSToRadian(double dms);
	double RadianToDMS(double r);
	double RadianToSecond(double r);
	void Init(double val1,double val2,double val3);
	void Input(double val1,double val2,double val3,DWORD dwDataType = DT_RADIAN);
	void Output(double&val1,double&val2,double&val3,DWORD dwDataType);
	void GaussToEarth(double L0);
	void EarthToSpace(double e2, double a);
	void EarthToGauss(double e2, double a, double L0);
	void SpaceToEarth(double e2, double a);
	
	ArxRleCoord();
	ArxRleCoord(double val1,double val2,double val3,DWORD dwDataType = DT_RADIAN);
	
	void SetValue(double val1, double val2,double val3);
	virtual ~ArxRleCoord();
};

#endif // ARXRLE_COORD_H
