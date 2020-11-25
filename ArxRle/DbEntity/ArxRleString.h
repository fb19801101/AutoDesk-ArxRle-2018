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

#define MAX_FORMAT_LENGTH 8192   //��ʽ���ַ�����󳤶�Ϊ8192

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
	//���ַ���ĩβ׷���ַ���
	void Append(ArxRleString strAfter);
	void Insert(int nPos, ArxRleString strAfter);
	//��ȡָ��λ�õ��ַ�
	char At(int nPos);
	//��ȡָ����ʼλ�úͳ��ȵ����ַ���
	ArxRleString GetSubStr(int nStartPos, int nLength);
	//��ȡ�������͵��ַ���
	char* c_ptr() const;
	wchar_t* w_ptr() const;
	string s_str() const;
	wstring w_str() const;
	CString t_str() const;
	BSTR b_str() const;
	COleVariant o_str() const;
	_variant_t v_str() const;
	AcString a_str() const;
	//��ȡ���ַ���
	ArxRleString Mid(int bgein, int len);
	//��ȡ�ַ�������
	int GetLength() const;

	//��ӡ�ַ���
	static int Print(const char *strFormat, ...);
	static int Print(const wchar_t *strFormat, ...);
	int Print();

public:
	//�ַ����ȽϺ���������ֵ����0��ʾ�����ַ���ȫ��ȣ�
	//����ֵΪ��ֵ��ʾ�ַ���С�ڱȽϵ��ַ���������ֵΪ��ֵ��ʾ�ַ������ڱȽϵ��ַ���
	int Compare(ArxRleString strCompare);
	//�����ַ����е����ַ���������ֵΪ���ҵ������ַ�����һ���ַ����ַ�����λ�ã�����ֵΪ-1��ʾδ�������ַ���
	int Find(ArxRleString strSubStr);
	int FindFirstOf(ArxRleString strSubStr);
	int FindLastOf(ArxRleString strSubStr);
	int FindFirstNotOf(ArxRleString strSubStr);
	int FindLastNotOf(ArxRleString strSubStr);
	int ReverseFind(ArxRleString strSubStr);
	//��Ҫ��Ӹ�ʽ��������trim�������ַ����ָ�ַ�����Сдת����
	ArxRleString Format(const char *strFormat, ...);
	ArxRleString Format(const wchar_t *strFormat, ...);
	short ToShort();
	int ToInt();
	long ToLong();
	double ToDouble();
	ArxRleString ConvertDouble(double fValue, int nPrecision = 3);//ת�����������ַ�������������������С���㼰С��

	//���ַ�����ת����
	ArxRleString Reverse();
	//�ַ���ת��ΪСд����
	ArxRleString ToLower();
	//�ַ���ת��Ϊ��д����
	ArxRleString ToUpper();

	//����ַ���
	ArxRleString Left(int index);
	ArxRleString Lefts(int len);
	//�Ҳ��ַ���
	ArxRleString Right(int index);
	ArxRleString Rights(int len);

	//ȥ���ַ�������ո��ַ�
	ArxRleString Trim(char cTrim = ' ');
	ArxRleString TrimLeft(char cTrim = ' ');
	ArxRleString TrimRight(char cTrim = ' ');

	//�ж��ַ����Ƿ�ȫ������A-Z��a-z�ַ�
	bool IsAlpha();
	//�ж��ַ����Ƿ�ȫ������ASCII���ַ���0x00 �C 0x7F��
	bool IsAscii();
	//ͳ���ַ�����ASCII���ַ�������
	int  GetAsciiCharSum();
	//ͳ���ַ����пո��ַ�������
	int  GetSpaceCharSum();
	//�ж��ַ����Ƿ�Ϊ���ַ���
	bool IsEmpty();
	//���ַ����еľ����ַ����滻Ϊ�����ַ���
	ArxRleString Replace(ArxRleString strOld, ArxRleString strNew);

	//���������ָ��������ں���2�ֽ���һ���֣�
	//nAsciiSum����ascii�ַ�������nSpaceSum���ؿո������nDigitSum�������ָ�����nAlphaSum������ĸ������nAsciiThinnerSum���؏C�ַ�����
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