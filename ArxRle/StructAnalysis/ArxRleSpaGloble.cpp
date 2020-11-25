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


float GetConcretFck(int Fcuk)
{
	float fc;//N/mm2
	switch(Fcuk)
	{
	case 15: fc=10.0;break;
	case 20: fc=13.4;break;
	case 25: fc=16.7;break;
	case 30: fc=20.1;break;
	case 35: fc=23.4;break;
	case 40: fc=26.8;break;
	case 45: fc=29.6;break;
	case 50: fc=32.4;break;
	case 55: fc=35.5;break;
	case 60: fc=38.5;break;
	case 65: fc=41.5;break;
	case 70: fc=44.5;break;
	case 75: fc=47.4;break;
	case 80: fc=50.2;break;
	}
	return fc;
}

float GetConcretFc(int Fcuk)
{
	float fc;//N/mm2
	switch(Fcuk)
	{
	case 15: fc=7.2;break;
	case 20: fc=9.6;break;
	case 25: fc=11.9;break;
	case 30: fc=14.3;break;
	case 35: fc=16.7;break;
	case 40: fc=19.1;break;
	case 45: fc=21.1;break;
	case 50: fc=23.1;break;
	case 55: fc=25.3;break;
	case 60: fc=27.5;break;
	case 65: fc=29.7;break;
	case 70: fc=31.8;break;
	case 75: fc=33.8;break;
	case 80: fc=35.9;break;
	}
	return fc;
}

float GetConcretFt(int Fcuk)
{
	float ft;//N/mm2
	switch(Fcuk)
	{
	case 15: ft=0.91;break;
	case 20: ft=1.10;break;
	case 25: ft=1.27;break;
	case 30: ft=1.43;break;
	case 35: ft=1.57;break;
	case 40: ft=1.71;break;
	case 45: ft=1.80;break;
	case 50: ft=1.89;break;
	case 55: ft=1.96;break;
	case 60: ft=2.04;break;
	case 65: ft=2.09;break;
	case 70: ft=2.14;break;
	case 75: ft=2.18;break;
	case 80: ft=2.22;break;
	}
	return ft;
}


float GetGjKanglaFy(CString &cs)
{
	float fy=0;//N/mm2
	if(cs=="HPB235") fy=210;
	if(cs=="HRB335") fy=300;
	if(cs=="HRB400") fy=360;
	if(cs=="RRB400") fy=360;
	return fy;
}
float GetGjKanglaFyc(CString &cs)
{
	float fy=0;//N/mm2
	if(cs=="HPB235") fy=210;
	if(cs=="HRB335") fy=300;
	if(cs=="HRB400") fy=360;
	if(cs=="RRB400") fy=360;
	return fy;
}

float GetGjKanglaEs(CString &cs)
{
	float Es=0;//N/mm2
	if(cs=="HPB235") Es=210000;
	if(cs=="HRB335") Es=200000;
	if(cs=="HRB400") Es=200000;
	if(cs=="RRB400") Es=200000;
	return Es;
}