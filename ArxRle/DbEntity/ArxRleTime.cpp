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

#include "ArxRleString.h"
#include "ArxRleTime.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArxRleTime::ArxRleTime()
{
    GetSysDateTime();
    QueryPerformanceFrequency(&m_lLargeFreq);
    QueryPerformanceCounter(&m_lLargeBeginTime);
}

ArxRleTime::~ArxRleTime()
{

}

void ArxRleTime::GetSysDateTime()
{
	//��ȡϵͳʱ�䣬�������õ�ʱ��� 2012��6��31��֮���������
	struct tm *localtm = NULL;
	time_t local_time;
	
	_tzset();
	
	time(&local_time);
	localtm = localtime(&local_time);
	
	//��ʱ�����Ϊ���ʱ�׼ʱ���ʽ
	localtm->tm_year += 1900;
	localtm->tm_mon += 1;

    m_nYear = (short)(localtm->tm_year);
    m_nMonth = (short)(localtm->tm_mon);
    m_nMDay = (short)(localtm->tm_mday);
    m_nHour = (short)(localtm->tm_hour);
    m_nMinute = (short)(localtm->tm_min);
    m_nSecond = (short)(localtm->tm_sec);
}

void ArxRleTime::SetYear(short nYear)
{
    m_nYear = nYear;
}

void ArxRleTime::SetMonth(short nMonth)
{
    m_nMonth = nMonth;
}

void ArxRleTime::SetMDay(short nMDay)
{
    m_nMDay = nMDay;
}

void ArxRleTime::SetHour(short nHour)
{
    m_nHour = nHour;
}

void ArxRleTime::SetMinute(short nMinute)
{
    m_nMinute = nMinute;
}

void ArxRleTime::SetSecond(short nSecond)
{
    m_nSecond = nSecond;
}

void ArxRleTime::SetMilliSecond(long nMilliSecond)
{
    m_nMilliSecond = nMilliSecond;
}

short ArxRleTime::GetYear()
{
    return m_nYear;
}

short ArxRleTime::GetMonth()
{
    return m_nMonth;
}

short ArxRleTime::GetMDay()
{
    return m_nMDay;
}

short ArxRleTime::GetHour()
{
    return m_nHour;
}

short ArxRleTime::GetMinute()
{
    return m_nMinute;
}

short ArxRleTime::GetSecond()
{
    return m_nSecond;
}

long ArxRleTime::GetMilliSecond()
{
    return m_nMilliSecond;
}

void ArxRleTime::GetTime(short &nYear, short &nMonth, short &nMDay, short &nHour, short &nMinute, short &nSecond, long &nMilliSecond)
{
    GetSysDateTime();
    nYear = m_nYear;               //��
    nMonth = m_nMonth;             //�·�
    nMDay = m_nMDay;               //���е���
    nHour = m_nHour;               //ʱ
    nMinute = m_nMinute;           //��
    nSecond = m_nSecond;           //��
    nMilliSecond = m_nMilliSecond; //����
}

//retrieves the frequency of the high-resolution performance counter, if one exists.
LARGE_INTEGER ArxRleTime::GetFrequency()
{
    QueryPerformanceFrequency(&m_lLargeFreq);
    return m_lLargeFreq;
}

//retrieves the current value of the high-resolution performance counter, if one exists. 
LARGE_INTEGER ArxRleTime::GetLargeBeginTime()
{
    QueryPerformanceCounter(&m_lLargeBeginTime);
    GetSysDateTime();
    return m_lLargeBeginTime;
}

//retrieves the current value of the high-resolution performance counter, if one exists. 
LARGE_INTEGER ArxRleTime::GetLargeEndTime()
{
    QueryPerformanceCounter(&m_lLargeEndTime);
    GetSysDateTime();
    return m_lLargeEndTime;
}

long ArxRleTime::GetSeconds(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime)
{
    long nSeconds = (((lLargeEndTime.QuadPart - lLargeBeginTime.QuadPart)) / m_lLargeFreq.QuadPart);
    return nSeconds;
}

long ArxRleTime::GetMilliSeconds(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime)
{
    long nMilliSeconds = (((lLargeEndTime.QuadPart - lLargeBeginTime.QuadPart)*1000000) / (m_lLargeFreq.QuadPart*1000));
    return nMilliSeconds;
}

long ArxRleTime::GetMicroSeconds(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime)
{
    long nMicroSeconds = (((lLargeEndTime.QuadPart - lLargeBeginTime.QuadPart)*1000000) / (m_lLargeFreq.QuadPart));
    return nMicroSeconds;
}

ArxRleString ArxRleTime::GetUsedTime(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime)
{
    GetLargeEndTime();
    long lMilliSeconds = (((lLargeEndTime.QuadPart - lLargeBeginTime.QuadPart)*1000000) / (m_lLargeFreq.QuadPart*1000));

    long lSeconds = lMilliSeconds / 1000;
    lMilliSeconds %= 1000;
    long lMinutes = lSeconds / 60;
    lSeconds %= 60;
    long lHours = lMinutes / 60;
    lMinutes %= 60;
//     if (lMilliSeconds < 1000)    //��ʱС��1��
//     {
//         lSeconds = 0;
//         lHours = 0;
//         lMinutes = 0;
//     }
//     else if (lMilliSeconds <= (60*1000))   //��ʱС��60��
//     {
//         lSeconds = lMilliSeconds/1000;
//         lMilliSeconds = lMilliSeconds - lSeconds*1000;
//         lHours = 0;
//         lMinutes = 0;
//     }
//     else if (lMilliSeconds <= (3600*1000))  //��ʱС��60����
//     {
//         lMinutes = lMilliSeconds/1000/60;
//         lSeconds = lMilliSeconds/1000 - lMinutes*60;
//         lMilliSeconds = lMilliSeconds - lMinutes;
//         lHours = 0;
//     }
//     else  //��ʱ����1Сʱ
//     {
//         lHours = lMilliSeconds/1000/60/60;
//         lMinutes = lMilliSeconds/1000/60 - lHours*60;
//         lSeconds = lMilliSeconds/1000 - lHours*60*60 - lMinutes*60;
//         lMilliSeconds = lMilliSeconds - lSeconds*1000;
//     }

    ArxRleString strUsedTime;
    strUsedTime.Format("������ʱ�䣺%dСʱ %d ���� %d �� %d ����", lHours, lMinutes, lSeconds, lMilliSeconds);
    return strUsedTime;
}

//��ʽ��Ϊ�ַ�����ʽ
ArxRleString ArxRleTime::Format2String()
{
    ArxRleString strTime;
    GetSysDateTime();
    strTime.Format("%d-%.2d-%.2d %.2d:%.2d:%.2d", m_nYear, m_nMonth, m_nMDay, m_nHour, m_nMinute, m_nSecond);
    return strTime;
}
