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

#ifndef ARXRLE_STRING_H
#define ARXRLE_STRING_H

#include <algorithm>
#include <string>
#include <vector>
#include <stdarg.h>
#include <cassert>
using namespace std;

#define MAX_FORMAT_LENGTH 8192   //格式化字符串最大长度为8192

class ArxRleString
{
public:
	ArxRleString();
	ArxRleString(const char cSrc);
	ArxRleString(const char *strSrc);
	ArxRleString(const wchar_t cSrc);
	ArxRleString(const wchar_t *strSrc);
	ArxRleString(const string& strSrc);
	ArxRleString(const wstring& strSrc);
	ArxRleString(const CString& strSrc);
	ArxRleString(const BSTR& strSrc);
	ArxRleString(const AcString& strSrc);
	ArxRleString(const COleVariant& strSrc);
	ArxRleString(const _variant_t& strSrc);
	virtual ~ArxRleString();

public:
	bool operator == (const ArxRleString& strCompare);
	bool operator != (const ArxRleString& strCompare);
	bool operator < (ArxRleString& strCompare);
	char  operator [](const int nPos);
	ArxRleString&  operator = (const char cSrc);
	ArxRleString&  operator = (const char *strSrc);
	ArxRleString&  operator = (const wchar_t cSrc);
	ArxRleString&  operator = (const wchar_t *strSrc);
	ArxRleString&  operator = (const string& strSrc);
	ArxRleString&  operator = (const wstring& strSrc);
	ArxRleString&  operator = (const CString& strSrc);
	ArxRleString&  operator = (const BSTR& strSrc);
	ArxRleString&  operator = (const AcString& strSrc);
	ArxRleString&  operator = (const COleVariant& strSrc);
	ArxRleString&  operator = (const _variant_t& strSrc);
	ArxRleString&  operator = (const ArxRleString& strSrc);
	ArxRleString  operator + (const char cSrc);
	ArxRleString  operator + (const char *strSrc);
	ArxRleString  operator + (const wchar_t cSrc);
	ArxRleString  operator + (const wchar_t *strSrc);
	ArxRleString  operator + (const string& strSrc);
	ArxRleString  operator + (const wstring& strSrc);
	ArxRleString  operator + (const CString& strSrc);
	ArxRleString  operator + (const BSTR& strSrc);
	ArxRleString  operator + (const AcString& strSrc);
	ArxRleString  operator + (const COleVariant& strSrc);
	ArxRleString  operator + (const _variant_t& strSrc);
	ArxRleString  operator + (const ArxRleString& strSrc);
	ArxRleString&  operator += (const char cSrc);
	ArxRleString&  operator += (const char *strSrc);
	ArxRleString&  operator += (const wchar_t cSrc);
	ArxRleString&  operator += (const wchar_t *strSrc);
	ArxRleString&  operator += (const string& strSrc);
	ArxRleString&  operator += (const wstring& strSrc);
	ArxRleString&  operator += (const CString& strSrc);
	ArxRleString&  operator += (const BSTR& strSrc);
	ArxRleString&  operator += (const AcString& strSrc);
	ArxRleString&  operator += (const COleVariant& strSrc);
	ArxRleString&  operator += (const _variant_t& strSrc);
	ArxRleString&  operator += (const ArxRleString& strSrc);
	operator const char();
	operator const char*();
	operator const wchar_t();
	operator const wchar_t*();
	operator wstring() const; 
	operator CString() const;
	operator BSTR() const;
	operator AcString() const;
	operator COleVariant() const;
	operator _variant_t() const;

public:
	//在字符串末尾追加字符串
	void Append(ArxRleString strAfter);
	void Insert(int nPos, ArxRleString strAfter);
	//获取指定位置的字符
	char At(int nPos);
	//获取指定起始位置和长度的子字符串
	ArxRleString GetSubStr(int nStartPos, int nLength);
	//获取各种类型的字符串
	char* c_ptr() const;
	wchar_t* w_ptr() const;
	string s_str() const;
	wstring w_str() const;
	CString t_str() const;
	BSTR b_str() const;
	COleVariant o_str() const;
	_variant_t v_str() const;
	AcString a_str() const;
	//获取子字符串
	ArxRleString Mid(int bgein, int len);
	//获取字符串长度
	int GetLength() const;

	//打印字符串
	static int Print(const char *strFormat, ...);
	static int Print(const wchar_t *strFormat, ...);
	int Print();

public:
	//字符串比较函数，返回值等于0表示两个字符串全相等，
	//返回值为负值表示字符串小于比较的字符串，返回值为正值表示字符串大于比较的字符串
	int Compare(ArxRleString strCompare);
	//查找字符串中的子字符串，返回值为查找到的子字符串第一个字符在字符串的位置，返回值为-1表示未查找子字符串
	int Find(ArxRleString strSubStr);
	int FindFirstOf(ArxRleString strSubStr);
	int FindLastOf(ArxRleString strSubStr);
	int FindFirstNotOf(ArxRleString strSubStr);
	int FindLastNotOf(ArxRleString strSubStr);
	int ReverseFind(ArxRleString strSubStr);
	//需要添加格式化函数、trim函数、字符串分割、字符串大小写转换、
	ArxRleString Format(const char *strFormat, ...);
	ArxRleString Format(const wchar_t *strFormat, ...);
	short ToShort();
	int ToInt();
	long ToLong();
	double ToDouble();
	ArxRleString ConvertDouble(double fValue, int nPrecision = 3);//转换浮点数成字符串，如果是整数不输出小数点及小数

	//将字符串逆转过来
	ArxRleString Reverse();
	//字符串转换为小写函数
	ArxRleString ToLower();
	//字符串转换为大写函数
	ArxRleString ToUpper();

	//左侧字符串
	ArxRleString Left(int index);
	ArxRleString Lefts(int len);
	//右侧字符串
	ArxRleString Right(int index);
	ArxRleString Rights(int len);

	//去除字符串两侧空格字符
	ArxRleString Trim(char cTrim = ' ');
	ArxRleString TrimLeft(char cTrim = ' ');
	ArxRleString TrimRight(char cTrim = ' ');

	//判断字符串是否全部都是A-Z或a-z字符
	bool IsAlpha();
	//判断字符串是否全部都是ASCII码字符（0x00 – 0x7F）
	bool IsAscii();
	//统计字符串中ASCII码字符的总数
	int  GetAsciiCharSum();
	//统计字符串中空格字符的总数
	int  GetSpaceCharSum();
	//判断字符串是否为空字符串
	bool IsEmpty();
	//将字符串中的旧子字符串替换为新子字符串
	ArxRleString Replace(ArxRleString strOld, ArxRleString strNew);

	//函数返回字个数，对于汉字2字节是一个字；
	//nAsciiSum返回ascii字符个数；nSpaceSum返回空格个数；nDigitSum返回数字个数；nAlphaSum返回字母个数；nAsciiThinnerSum返回廋字符个数
	int GetStringInfo(int& nAsciiSum, int& nSpaceSum, int& nDigitSum, int& nAlphaSum, int& nAsciiThinnerSum);
	int ParseSubStrByDelimiter(vector<ArxRleString>& strSubArray, ArxRleString strDelimiter = ";");
	int GetSpecifySubStrSum(ArxRleString strSub);

private:
	string m_strSelf;

public:
	void SetOwner(string strSrc);
};

typedef vector<ArxRleString> ArxRleStringList;

#endif  // ARXRLE_STRING_H