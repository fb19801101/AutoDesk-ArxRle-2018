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
    void SetYear(short nYear);              //年
    void SetMonth(short nMonth);            //月份
    void SetMDay(short nMDay);              //月中的天
    void SetHour(short nHour);              //时
    void SetMinute(short nMinute);          //分
    void SetSecond(short nSecond);          //秒
    void SetMilliSecond(long nMilliSecond); //毫秒

    short GetYear();          //年
    short GetMonth();         //月份
    short GetMDay();          //月中的天
    short GetHour();          //时
    short GetMinute();        //分
    short GetSecond();        //秒
    long GetMilliSecond();    //毫秒
    void GetTime(short &nYear, short &nMonth, short &nMDay, short &nHour, short &nMinute, short &nSecond, long &nMilliSecond);
    LARGE_INTEGER GetFrequency();       //retrieves the frequency of the high-resolution performance counter, if one exists.
    LARGE_INTEGER GetLargeBeginTime();  //retrieves the current value of the high-resolution performance counter, if one exists. 
    LARGE_INTEGER GetLargeEndTime();    //retrieves the current value of the high-resolution performance counter, if one exists. 
    long GetSeconds(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime);       //秒
    long GetMilliSeconds(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime);  //毫秒
    long GetMicroSeconds(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime);  //微秒
    ArxRleString GetUsedTime(LARGE_INTEGER lLargeBeginTime, LARGE_INTEGER lLargeEndTime);  //计算耗费时间并返回字符串
    //格式化为字符串形式
    ArxRleString Format2String();

protected:
    short m_nYear;          //年
    short m_nMonth;         //月份
    short m_nMDay;          //月中的天
    short m_nHour;          //时
    short m_nMinute;        //分
    short m_nSecond;        //秒
    long m_nMilliSecond;    //毫秒

    LARGE_INTEGER m_lLargeFreq;
    LARGE_INTEGER m_lLargeBeginTime;
    LARGE_INTEGER m_lLargeEndTime;
};

#endif  // ARXRLE_TIME_H
