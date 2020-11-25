// ArxRleTime.h: interface for the ArxRleTime class.
//

#ifndef ARXRLE_TIME_H
#define ARXRLE_TIME_H

class ArxRleTime  
{
public:
	ArxRleTime();
	virtual ~ArxRleTime();
    void GetSysDateTime();

public:
    void SetYear(short nYear);              //��
    void SetMonth(short nMonth);            //�·�
    void SetMDay(short nMDay);              //���е���
    void SetHour(short nHour);              //ʱ
    void SetMinute(short nMinute);          //��
    void SetSecond(short nSecond);          //��
    void SetMilliSecond(long nMilliSecond); //����

    short GetYear();          //��
    short GetMonth();         //�·�
    short GetMDay();          //���е���
    short GetHour();          //ʱ
    short GetMinute();        //��
    short GetSecond();        //��
    long GetMilliSecond();    //����
    void GetTime(short &nYear, short &nMonth, short &nMDay, short &nHour, short &nMinute, short &nSecond, long &nMilliSecond);
    LARGE_INTEGER GetFrequency();       //retrieves the frequency of the high-resolution performance counter, if one exists.
    LARGE_INTEGER GetLargeBeginTime();  //retrieves the current value of the high-resolution performance counter, if one exists. 
    LARGE_INTEGER GetLargeEndTime();    //retrieves the current value of the high-resolution performance counter, if one exists. 
    long GetSeconds(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime);       //��
    long GetMilliSeconds(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime);  //����
    long GetMicroSeconds(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime);  //΢��
    ArxRleString GetUsedTime(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime);  //����ķ�ʱ�䲢�����ַ���
    //��ʽ��Ϊ�ַ�����ʽ
    ArxRleString Format2String();

protected:
    short m_nYear;          //��
    short m_nMonth;         //�·�
    short m_nMDay;          //���е���
    short m_nHour;          //ʱ
    short m_nMinute;        //��
    short m_nSecond;        //��
    long m_nMilliSecond;    //����

    LARGE_INTEGER m_lLargeFreq;
    LARGE_INTEGER m_lLargeBeginTime;
    LARGE_INTEGER m_lLargeEndTime;
};

#endif  // ARXRLE_TIME_H
