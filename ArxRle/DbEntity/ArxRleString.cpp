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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <windows.h>
#include <comutil.h>
#include "ArxRleString.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArxRleString::ArxRleString()
{
	m_strSelf = "";
}

ArxRleString::~ArxRleString()
{

}

ArxRleString::ArxRleString(const char cSrc)
{
	char szs[2] = {0};
	szs[0] = cSrc;
	m_strSelf = string(szs);
}

ArxRleString::ArxRleString(const char *strSrc)
{
	m_strSelf = string(strSrc);
}

ArxRleString::ArxRleString(const wchar_t cSrc)
{
	//第四个形参设为-1,即可返回所需的宽字符数组空间的个数
	char str[3];
	str[0] = cSrc >> 8;
	str[1] = cSrc;
	str[2] = '\0';

	m_strSelf = string(str);
}

ArxRleString::ArxRleString(const wchar_t *strSrc)
{
	//第四个形参设为-1,即可返回所需的宽字符数组空间的个数
	int num = WideCharToMultiByte (CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	char *str = new char[num];
	if(!str) delete []str;

	WideCharToMultiByte( CP_ACP, 0, strSrc,-1, str, num, NULL, NULL);
	m_strSelf = string(str);
}

ArxRleString::ArxRleString(const string& strSrc)
{
	m_strSelf = strSrc;
}

ArxRleString::ArxRleString(const wstring& strSrc)
{
	//第四个形参设为-1,即可返回所需的宽字符数组空间的个数
	int num = WideCharToMultiByte (CP_ACP, 0, strSrc.c_str(), -1, NULL, 0, NULL, NULL);
	char *str = new char[num];
	if(!str) delete []str;

	WideCharToMultiByte( CP_ACP, 0, strSrc.c_str(),-1, str, num, NULL, NULL);
	m_strSelf = string(str);
}

ArxRleString::ArxRleString(const CString& strSrc)
{
	//第四个形参设为-1,即可返回所需的宽字符数组空间的个数
	int num = WideCharToMultiByte (CP_ACP, 0, strSrc.AllocSysString(), -1, NULL, 0, NULL, NULL);
	char *str = new char[num];
	if(!str) delete []str;

	WideCharToMultiByte( CP_ACP, 0, strSrc.AllocSysString(),-1, str, num, NULL, NULL);
	m_strSelf = string(str);
}

ArxRleString::ArxRleString(const BSTR& strSrc)
{
	char* str = _com_util::ConvertBSTRToString(strSrc);
	m_strSelf = string(str);
}

ArxRleString::ArxRleString(const COleVariant& strSrc)
{
	switch(strSrc.vt) 
	{
	case VT_I2:
		{
			char str[100];
			memset(str, 0, sizeof(str));
			sprintf(str,"%d",strSrc.iVal);
			m_strSelf = str;
		}
		break;
	case VT_I4:
		{
			char str[100];
			memset(str, 0, sizeof(str));
			sprintf(str,"%d",strSrc.lVal);
			m_strSelf = str;
		}
		break;
	case VT_R8:
		{
			char str[100];
			memset(str, 0, sizeof(str));
			sprintf(str,"%.6f",strSrc.dblVal);
			m_strSelf = str;
		}
		break;
	case VT_BSTR:
		{
			_bstr_t b = strSrc.bstrVal;
			char* str = b;
			m_strSelf = string(str);
		}
		break;
	case VT_BOOL:
		{
			char str[100];
			memset(str, 0, sizeof(str));
			sprintf(str,"%d",strSrc.bVal);
			m_strSelf = str;
		}
		break;
	}
}

ArxRleString::ArxRleString(const _variant_t& strSrc)
{
	switch(strSrc.vt) 
	{
	case VT_I2:
		{
			char str[100];
			memset(str, 0, sizeof(str));
			sprintf(str,"%d",strSrc.iVal);
			m_strSelf = str;
		}
		break;
	case VT_I4:
		{
			char str[100];
			memset(str, 0, sizeof(str));
			sprintf(str,"%d",strSrc.lVal);
			m_strSelf = str;
		}
		break;
	case VT_R8:
		{
			char str[100];
			memset(str, 0, sizeof(str));
			sprintf(str,"%.6f",strSrc.dblVal);
			m_strSelf = str;
		}
		break;
	case VT_BSTR:
		{
			_bstr_t b = strSrc.bstrVal;
			char* str = b;
			m_strSelf = string(str);
		}
		break;
	case VT_BOOL:
		{
			char str[100];
			memset(str, 0, sizeof(str));
			sprintf(str,"%d",strSrc.bVal);
			m_strSelf = str;
		}
		break;
	}
}

ArxRleString::ArxRleString(const AcString& strSrc)
{
	m_strSelf = string(strSrc.utf8Ptr());
}

bool ArxRleString::operator == (const ArxRleString& strCompare)
{
	if (0 == this->Compare(strCompare))
	{
		return true;
	}
	return false;
}

bool ArxRleString::operator != (const ArxRleString& strCompare)
{
	if (0 == this->Compare(strCompare))
	{
		return false;
	}
	return true;
}

bool ArxRleString::operator < (ArxRleString& strCompare)
{
	if (this->Compare(strCompare) < 0)
	{
		return true;
	}
	return false;
}

char  ArxRleString::operator [](const int nPos)
{
	return m_strSelf.at(nPos);
}

ArxRleString& ArxRleString::operator = (const char cSrc)
{
	m_strSelf = ArxRleString(cSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator = (const char *strSrc)
{
	m_strSelf = ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator = (const wchar_t cSrc)
{
	m_strSelf = ArxRleString(cSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator = (const wchar_t *strSrc)
{ 
	m_strSelf = ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator = (const string& strSrc)
{
	m_strSelf = strSrc;
	return *this;
}

ArxRleString& ArxRleString::operator = (const wstring& strSrc)
{
	m_strSelf = ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator = (const CString& strSrc)
{
	m_strSelf = ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator = (const BSTR& strSrc)
{
	m_strSelf = ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator = (const COleVariant& strSrc)
{
	m_strSelf = ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator = (const _variant_t& strSrc)
{
	m_strSelf = ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator = (const AcString& strSrc)
{
	m_strSelf = ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator = (const ArxRleString& strSrc)
{
	if (this == &strSrc)
	{
		return *this;
	}
	m_strSelf = strSrc.s_str();
	return *this;
}

ArxRleString ArxRleString::operator + (const char cSrc)
{
	return m_strSelf + ArxRleString(cSrc).s_str();
}

ArxRleString ArxRleString::operator + (const char *strSrc)
{
	return m_strSelf + ArxRleString(strSrc).s_str();
}

ArxRleString ArxRleString::operator + (const wchar_t cSrc)
{
	return m_strSelf + ArxRleString(cSrc).s_str();
}

ArxRleString ArxRleString::operator + (const wchar_t *strSrc)
{
	return m_strSelf + ArxRleString(strSrc).s_str();
}

ArxRleString ArxRleString::operator + (const string& strSrc)
{
	return m_strSelf + ArxRleString(strSrc).s_str();
}

ArxRleString ArxRleString::operator + (const wstring& strSrc)
{
	return m_strSelf + ArxRleString(strSrc).s_str();
}

ArxRleString ArxRleString::operator + (const CString& strSrc)
{
	return m_strSelf + ArxRleString(strSrc).s_str();
}

ArxRleString ArxRleString::operator + (const BSTR& strSrc)
{
	return m_strSelf + ArxRleString(strSrc).s_str();
}

ArxRleString ArxRleString::operator + (const COleVariant& strSrc)
{
	return m_strSelf + ArxRleString(strSrc).s_str();
}

ArxRleString ArxRleString::operator + (const _variant_t& strSrc)
{
	return m_strSelf + ArxRleString(strSrc).s_str();
}

ArxRleString ArxRleString::operator + (const AcString& strSrc)
{
	return m_strSelf + ArxRleString(strSrc).s_str();
}

ArxRleString ArxRleString::operator + (const ArxRleString& strSrc)
{
	return m_strSelf + ArxRleString(strSrc).s_str();
}

ArxRleString& ArxRleString::operator += (const char cSrc)
{
	m_strSelf += ArxRleString(cSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator += (const char *strSrc)
{
	m_strSelf += ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator += (const wchar_t cSrc)
{
	m_strSelf += ArxRleString(cSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator += (const wchar_t *strSrc)
{
	m_strSelf += ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator += (const string& strSrc)
{
	m_strSelf += strSrc;
	return *this;
}

ArxRleString& ArxRleString::operator += (const wstring& strSrc)
{
	m_strSelf += ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator += (const CString& strSrc)
{
	m_strSelf += ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator += (const BSTR& strSrc)
{
	m_strSelf += ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator += (const COleVariant& strSrc)
{
	m_strSelf += ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator += (const _variant_t& strSrc)
{
	m_strSelf += ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator += (const AcString& strSrc)
{
	m_strSelf += ArxRleString(strSrc).s_str();
	return *this;
}

ArxRleString& ArxRleString::operator += (const ArxRleString& strSrc)
{
	m_strSelf += strSrc.s_str();
	return *this;
}

ArxRleString::operator const char()
{
	return m_strSelf.c_str()[0];
};

ArxRleString::operator const char*()
{
	return m_strSelf.c_str();
};

ArxRleString::operator const wchar_t()
{
	int num = MultiByteToWideChar (CP_ACP, 0, m_strSelf.c_str(), -1, NULL, 0);
	wchar_t *str = new wchar_t[num];
	if(!str) delete []str;

	MultiByteToWideChar( CP_ACP, 0, m_strSelf.c_str(),-1, str, num);
	return str[0];
};

ArxRleString::operator const wchar_t*()
{
	//第四个形参设为-1,即可返回所需的宽字符数组空间的个数
	int num = MultiByteToWideChar (CP_ACP, 0, m_strSelf.c_str(), -1, NULL, 0);
	wchar_t *str = new wchar_t[num];
	if(!str) delete []str;

	MultiByteToWideChar( CP_ACP, 0, m_strSelf.c_str(),-1, str, num);
	return str;
}

ArxRleString::operator wstring() const
{
	//第四个形参设为-1,即可返回所需的宽字符数组空间的个数
	int num = MultiByteToWideChar (CP_ACP, 0, m_strSelf.c_str(), -1, NULL, 0);
	wchar_t *str = new wchar_t[num];
	if(!str) delete []str;

	MultiByteToWideChar( CP_ACP, 0, m_strSelf.c_str(),-1, str, num);
	return wstring(str);
}

ArxRleString::operator CString() const 
{
	return CString(m_strSelf.c_str());
};

ArxRleString::operator BSTR() const 
{
	return _bstr_t(m_strSelf.c_str()).GetBSTR();
};

ArxRleString::operator COleVariant() const
{
	VARIANT vt;
	vt.vt = VT_BSTR;
	vt.bstrVal = _bstr_t(m_strSelf.c_str()).GetBSTR();

	return vt;
}

ArxRleString::operator _variant_t() const
{
	VARIANT vt;
	vt.vt = VT_BSTR;
	vt.bstrVal = _bstr_t(m_strSelf.c_str()).GetBSTR();

	return vt;
}

ArxRleString::operator AcString() const 
{
	return AcString(m_strSelf.c_str());
};

//在字符串末尾追加字符串
void ArxRleString::Append(ArxRleString strAfter)
{
	m_strSelf.append(strAfter.s_str());
}

void ArxRleString::Insert(int nPos, ArxRleString strAfter)
{
	m_strSelf.insert(nPos, strAfter.s_str());
}

//获取指定位置的字符
char ArxRleString::At(int nPos)
{
	return m_strSelf.at(nPos);
}

//获取指定起始位置和长度的子字符串
ArxRleString ArxRleString::GetSubStr(int nStartPos, int nLength)
{
	if (nLength > (int)m_strSelf.length()-nStartPos+1)
	{
		nLength = m_strSelf.length()-nStartPos+1;
	}
	if(nLength == -1)
		return m_strSelf.substr(nStartPos);
	else
		return m_strSelf.substr(nStartPos, nLength);
}

//获取各种类型的字符串
char* ArxRleString::c_ptr() const
{
	return const_cast<char*>(m_strSelf.c_str());
}

wchar_t* ArxRleString::w_ptr() const
{
	//第四个形参设为-1,即可返回所需的宽字符数组空间的个数
	int num = MultiByteToWideChar (CP_ACP, 0, m_strSelf.c_str(), -1, NULL, 0);
	wchar_t *str = new wchar_t[num];
	if(!str) delete []str;

	MultiByteToWideChar( CP_ACP, 0, m_strSelf.c_str(),-1, str, num);
	return str;
}

string ArxRleString::s_str() const
{
	return m_strSelf;
}

wstring ArxRleString::w_str() const
{
	wstring ws; 
	int num = MultiByteToWideChar (CP_ACP, 0, m_strSelf.c_str(), -1, NULL, 0);
	wchar_t *str = new wchar_t[num];
	if(!str) delete []str;

	MultiByteToWideChar( CP_ACP, 0, m_strSelf.c_str(),-1, str, num);
	ws = str;
	return ws;
}

CString ArxRleString::t_str() const
{
	return CString(m_strSelf.c_str());
}

BSTR ArxRleString::b_str() const
{
	return _bstr_t(m_strSelf.c_str()).GetBSTR();
}

COleVariant ArxRleString::o_str() const
{
	VARIANT vt;
	vt.vt = VT_BSTR;
	vt.bstrVal = _bstr_t(m_strSelf.c_str()).GetBSTR();

	return vt;
}

_variant_t ArxRleString::v_str() const
{
	VARIANT vt;
	vt.vt = VT_BSTR;
	vt.bstrVal = _bstr_t(m_strSelf.c_str()).GetBSTR();

	return vt;
}

AcString ArxRleString::a_str() const
{
	return AcString(m_strSelf.c_str());
}


ArxRleString ArxRleString::Mid(int bgein, int len)
{
	if(bgein < 0) bgein = 0;
	if(len > (int)m_strSelf.length()-bgein)
		len = m_strSelf.length()-bgein;

	return m_strSelf.substr(bgein, len);
}

int ArxRleString::GetLength() const
{
	return m_strSelf.length();
}

int ArxRleString::Print(const char* strFormat, ...)
{
	char strText[MAX_FORMAT_LENGTH];
	va_list arg_ptr;
	va_start(arg_ptr, strFormat);
	vsprintf_s(strText, strFormat, arg_ptr);
	va_end(arg_ptr);

	string ss(strText);

	int num = MultiByteToWideChar (CP_ACP, 0, ss.c_str(), -1, NULL, 0);
	wchar_t *str = new wchar_t[num];
	if(!str) delete []str;

	MultiByteToWideChar( CP_ACP, 0, ss.c_str(),-1, str, num);

	return acutPrintf(str);
}

int ArxRleString::Print(const wchar_t *strFormat, ...)
{
	wchar_t strText[MAX_FORMAT_LENGTH];
	va_list arg_ptr;
	va_start(arg_ptr, strFormat);
	vswprintf_s(strText, strFormat, arg_ptr);
	va_end(arg_ptr);

	int num = WideCharToMultiByte (CP_ACP, 0, strText, -1, NULL, 0, NULL, NULL);
	char *str = new char[num];
	if(!str) delete []str;

	WideCharToMultiByte( CP_ACP, 0, strText,-1, str, num, NULL, NULL);
	string ss(str);

	return acutPrintf(strText);
}

int ArxRleString::Print()
{
	int num = MultiByteToWideChar (CP_ACP, 0, m_strSelf.c_str(), -1, NULL, 0);
	wchar_t *str = new wchar_t[num];
	if(!str) delete []str;

	MultiByteToWideChar( CP_ACP, 0, m_strSelf.c_str(),-1, str, num);

	return acutPrintf(str);
}

//字符串比较函数
int ArxRleString::Compare(ArxRleString strCompare)
{
	return m_strSelf.compare(strCompare.c_ptr());
}

//查找字符串中的子字符串，返回值为查找到的子字符串第一个字符在字符串的位置
int ArxRleString::Find(ArxRleString strSubStr)
{
	int nPos = m_strSelf.find(strSubStr.c_ptr());
	return nPos;
}

int ArxRleString::FindFirstOf(ArxRleString strSubStr)
{
	int nPos = m_strSelf.find_first_of(strSubStr.c_ptr());
	return nPos;
}

int ArxRleString::FindLastOf(ArxRleString strSubStr)
{
	int nPos = m_strSelf.find_last_of(strSubStr.c_ptr());
	return nPos;
}

int ArxRleString::FindFirstNotOf(ArxRleString strSubStr)
{
	int nPos = m_strSelf.find_first_not_of(strSubStr.c_ptr());
	return nPos;
}

int ArxRleString::FindLastNotOf(ArxRleString strSubStr)
{
	int nPos = m_strSelf.find_last_not_of(strSubStr.c_ptr());
	return nPos;
}

int ArxRleString::ReverseFind(ArxRleString strSubStr)
{
	int nPos = m_strSelf.rfind(strSubStr.c_ptr());
	return nPos;
}

ArxRleString ArxRleString::Format(const char *strFormat, ...)
{
	char strText[MAX_FORMAT_LENGTH];
	va_list arg_ptr;
	va_start(arg_ptr, strFormat);
	vsprintf_s(strText, strFormat, arg_ptr);
	va_end(arg_ptr);

	m_strSelf = string(strText);

	return *this;
}

ArxRleString ArxRleString::Format(const wchar_t *strFormat, ...)
{
	wchar_t strText[MAX_FORMAT_LENGTH];
	va_list arg_ptr;
	va_start(arg_ptr, strFormat);
	vswprintf_s(strText, strFormat, arg_ptr);
	va_end(arg_ptr);

	int num = WideCharToMultiByte (CP_ACP, 0, strText, -1, NULL, 0, NULL, NULL);
	char *str = new char[num];
	if(!str) delete []str;

	WideCharToMultiByte( CP_ACP, 0, strText,-1, str, num, NULL, NULL);
	m_strSelf = string(str);

	return *this;
}

short ArxRleString::ToShort()
{
	return (short)atoi(m_strSelf.c_str());
}

int ArxRleString::ToInt()
{
	return atoi(m_strSelf.c_str());
}

long ArxRleString::ToLong()
{
	return atol(m_strSelf.c_str());
}

double ArxRleString::ToDouble()
{
	return atof(m_strSelf.c_str());
}

ArxRleString ArxRleString::ConvertDouble(double fValue, int nPrecision)
{
	char strText[30];
	if(int(fValue) == int(fValue+0.5))
		sprintf_s(strText, "%d", int(fValue+0.5));
	else if(int(fValue) == int(fValue-0.5))
		sprintf_s(strText, "%d", int(fValue-0.5));
	else
		sprintf_s(strText, "%.*f", nPrecision, fValue);

	m_strSelf = strText;

	return *this;
}

//将字符串逆转过来
ArxRleString ArxRleString::Reverse()
{
	m_strSelf.reserve();
	return *this;
}

//字符串转换为小写函数
ArxRleString ArxRleString::ToLower()
{
	if (m_strSelf.empty())
		return *this;

	for (string::iterator iter = m_strSelf.begin(); iter != m_strSelf.end(); iter++)
	{
		if (isupper((char)(*iter)))
			*iter = tolower(*iter);
	}

	return *this;
}

//字符串转换为大写函数
ArxRleString ArxRleString::ToUpper()
{
	if (m_strSelf.empty())
		return *this;

	for (string::iterator iter = m_strSelf.begin(); iter != m_strSelf.end(); iter++)
	{
		if (islower((char)(*iter)))
			*iter = toupper(*iter);
	}

	return *this;
}

//左侧字符串
ArxRleString ArxRleString::Left(int index)
{
	return Mid(0,index+1);
}

ArxRleString ArxRleString::Lefts(int len)
{
	return Mid(0,len);
}

//右侧字符串
ArxRleString ArxRleString::Right(int index)
{
	return Mid(index,m_strSelf.length()-index);
}

ArxRleString ArxRleString::Rights(int len)
{
	return Mid(m_strSelf.length()-len,len);
}


//去除字符串两侧空格字符
ArxRleString ArxRleString::Trim(char cTrim)
{
	if (m_strSelf.empty())
		return *this;

	//清除左侧空格
	for (string::iterator iter = m_strSelf.begin(); iter != m_strSelf.end();)
	{
		char cTemp = (char)(*iter);
		if (cTemp == cTrim)
			m_strSelf.erase(iter);
		else
			break;
	}

	//清除右侧空格
	reverse(m_strSelf.begin(), m_strSelf.end());
	for (string::iterator iter = m_strSelf.begin(); iter != m_strSelf.end();)
	{
		char cTemp = (char)(*iter);
		if (cTemp == cTrim)
			m_strSelf.erase(iter);
		else
			break;
	}
	reverse(m_strSelf.begin(), m_strSelf.end());

	return *this;
}

ArxRleString ArxRleString::TrimLeft(char cTrim)
{
	if (m_strSelf.empty())
		return *this;

	for (string::iterator iter = m_strSelf.begin(); iter != m_strSelf.end();)
	{
		char cTemp = (char)(*iter);
		if (cTemp == cTrim)
			m_strSelf.erase(iter);
		else
			break;
	}

	return *this;
}

ArxRleString ArxRleString::TrimRight(char cTrim)
{
	if (m_strSelf.empty())
		return *this;

	reverse(m_strSelf.begin(), m_strSelf.end());
	for (string::iterator iter = m_strSelf.begin(); iter != m_strSelf.end();)
	{
		char cTemp = (char)(*iter);
		if (cTemp == cTrim)
			m_strSelf.erase(iter);
		else
			break;
	}
	reverse(m_strSelf.begin(), m_strSelf.end());

	return *this;
}

//判断字符串是否全部都是A-Z或a-z字符
bool ArxRleString::IsAlpha()
{
	if (m_strSelf.empty())
		return false;

	for (string::iterator iter = m_strSelf.begin(); iter != m_strSelf.end(); iter++)
	{
		if (!isalpha((char)(*iter)))
			return false;
	}

	return true;
}

//判断字符串是否全部都是ASCII码字符
bool ArxRleString::IsAscii()
{
	if (m_strSelf.empty())
		return false;

	for (string::iterator iter = m_strSelf.begin(); iter != m_strSelf.end(); iter++)
	{
		if (!__isascii((char)(*iter)))
			return false;
	}

	return true;
}

//统计字符串中ASCII码字符的总数
int  ArxRleString::GetAsciiCharSum()
{
	if (m_strSelf.empty())
		return 0;

	int nAsciiCharSum = 0;
	for (string::iterator iter = m_strSelf.begin(); iter != m_strSelf.end(); iter++)
	{
		if (__isascii((char)(*iter)))
			++nAsciiCharSum;
	}

	return nAsciiCharSum;
}

//统计字符串中空格字符的总数
int  ArxRleString::GetSpaceCharSum()
{
	if (m_strSelf.empty())
		return 0;

	int nSpaceCharSum = 0;
	for (string::iterator iter = m_strSelf.begin(); iter != m_strSelf.end(); iter++)
	{
		if ((char)(*iter) == ' ')
			++nSpaceCharSum;
	}

	return nSpaceCharSum;
}

//判断字符串是否为空字符串
bool ArxRleString::IsEmpty()
{
	return m_strSelf.empty();
}

#include "COMDEF.H"

int ArxRleString::GetStringInfo(int& nAsciiSum, int& nSpaceSum, int& nDigitSum, int& nAlpha, int& nAsciiThinnerSum)
{
	nAsciiSum = 0;
	nSpaceSum = 0;
	nDigitSum = 0;
	nAlpha = 0;
	nAsciiThinnerSum = 0;
	for (string::iterator iter = m_strSelf.begin(); iter != m_strSelf.end(); iter++)
	{
		char cTemp = (char)*iter;
		if (__isascii(cTemp))
		{
			++nAsciiSum;
			if (cTemp >= '0' && cTemp <= '9')
				++nDigitSum;
			else if (cTemp == ' ')
				++nSpaceSum;
			else if((cTemp >= 'A' && cTemp <= 'Z') || (cTemp >= 'a' && cTemp <= 'z'))
				++nAlpha;

			if(cTemp == '1' || cTemp == 'I' || cTemp == 'i' || cTemp == 'l' || cTemp == '.'
				|| cTemp == '|' || cTemp == ':' || cTemp == ';' || cTemp == '!' || cTemp == '('
				|| cTemp == ')' || cTemp == '[' || cTemp == ']' || cTemp == '{' || cTemp == '}'
				|| cTemp == ',' || cTemp == '\'' || cTemp == '\"' || cTemp == '`')
				++nAsciiThinnerSum;
		}
	}

	return m_strSelf.length();
}

int ArxRleString::ParseSubStrByDelimiter(vector<ArxRleString>& strSubArray, ArxRleString strDelimiter)
{
	ArxRleString strLine = *this;
	strLine.Replace("\t", " ");
	strLine.Trim();
	int nDelimiterLen = strDelimiter.GetLength();
	int nNext = -1;
	while((nNext = strLine.Find(strDelimiter)) >= 0)
	{
		strSubArray.push_back(strLine.GetSubStr(0, nNext));
		strLine = strLine.GetSubStr(nNext + nDelimiterLen, -1);
		strLine = strLine.Trim();
	}

	if(strLine.GetLength() > 0)
		strSubArray.push_back(strLine);

	return strSubArray.size();
}

int ArxRleString::GetSpecifySubStrSum(ArxRleString strDelimiter)
{
	string strLine = m_strSelf;
	const char* lpszDelimiter = strDelimiter.c_ptr();
	int nDelimiterLen = strlen(lpszDelimiter);
	int nNext = -1;
	short nSum = 0;
	while((nNext = strLine.find(lpszDelimiter, 0)) >= 0)
	{
		nSum++;
		strLine = strLine.substr(nNext + nDelimiterLen);
	}

	if(strLine.length() > 0)
		nSum++;

	return nSum;
}

ArxRleString ArxRleString::Replace(ArxRleString strOld, ArxRleString strNew)
{
	string _strOld = strOld.s_str();
	string _strNew = strNew.s_str();
	size_t pos = 0; 
	string::size_type oldStrLen = _strOld.length();
	string::size_type newStrLen = _strNew.length();

	while(true) 
	{ 
		pos = m_strSelf.find(_strOld.c_str(), pos); 
		if (pos == string::npos) break; 

		m_strSelf.replace(pos, oldStrLen, _strNew);
		pos += newStrLen;
	}

	return *this;
}

void ArxRleString::SetOwner(string strSrc)
{
	m_strSelf = strSrc;
}
