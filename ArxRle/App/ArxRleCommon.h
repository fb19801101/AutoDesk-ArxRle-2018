//ArxRleBaseFunc.h  公共基础函数头文件
//
#ifndef ARXRLE_BASEFUNC_H
#define ARXRLE_BASEFUNC_H

#pragma warning(disable:4005)   //禁用警告
#pragma warning(disable:4049)   //禁用警告
#pragma warning(disable:4056)   //禁用警告
#pragma warning(disable:4089)   //禁用警告
#pragma warning(disable:4244)   //禁用警告
#pragma warning(disable:4251)   //禁用警告
#pragma warning(disable:4305)   //禁用警告
#pragma warning(disable:4756)   //禁用警告
#pragma warning(disable:4761)   //禁用警告
#pragma warning(disable:4786)   //禁用警告
#pragma warning(disable:4800)   //禁用警告
#pragma warning(disable:4996)   //禁用警告

#include "stdlib.h"
#include "atlbase.h"
#include "afxinet.h"
#include <process.h>
#include <direct.h>
#include <atltime.h>
#include <stdarg.h>    // 变参函数必须包含的头文件
#include <tchar.h>
#include <string>
#include <mbstring.h>
#include <fstream>
#include <iostream>
#include <strstream>
#include <io.h>
#include <math.h>
#include <cmath>
#include <map>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <vector>
#include <list>
#include <windows.h>
#include <algorithm>
#include <ctype.h>
#include <locale.h>
using namespace std;

#ifndef _printf
#define _printf acutPrintf
#endif

#define MAX_BUFSIZE 4096                          //char*最大字节数
#define MAX_STRSIZE 256                           //char*最大字节数
#define MAX_FFIX_LENGTH 16                        //文件前缀或后缀最大长度
#define MAX_SMSG_LENGTH 1024                      //短消息最大长度
#define MAX_LMSG_LENGTH 10240                     //长消息最大长度
#define MAX_NAME_LENGTH 256                       //最大名称长度
#define MAX_PATH_LENGTH 2048                      //路径最大长度
#define MAX_FILESIZE_1MB    1048576               //1MB，也就是1兆字节
#define MAX_FILESIZE_10MB   10485760              //10MB，也就是10兆字节
#define MAX_FILESIZE_100MB  104857600             //100MB，也就是100兆字节
#define MAX_FILESIZE_1000MB 1048576000            //1000MB，也就是1000兆字节=1GB
#define MAX_FILESIZE_1000GB 1048576000000         //1000GB，也就是1TB
#define MIN_CHECK_BYTE_IN_ROW 64                  //一行中需要检查的最小字节数
#define FACTOR_HUNDRED 100                        //系数100
#define FACTOR_THOUSAND 1000                      //系数1000
#define FACTOR_MEMORY_USED 2.5                    //内存使用与判断系数
#define FACTOR_MEMORY_USED_LESS_1MIL 2.75         //内存使用与判断系数
#define FACTOR_MEMORY_USED_MORE_1MIL 3.75         //内存使用与判断系数
#define INVALID_VALUE -9999                       //无效值，最大支持32位整型数据
#define DISTANCE_PRECISION  0.000001              //距离精度
#define ANGLE_PRECISION     0.000001              //角度精度
#define ZERO_PRECISION      0.000001              //表示零的精度
#define COOR_PRECISION      0.000005              //坐标误差的精度
#define WIDTH_PRECISION     0.000005              //宽度精度
#define RADIUS_PRECISION    0.000005              //半径精度
#define PI 3.141592653589793238462643383279502884197169399375105820974944592308   //圆周率 PI
#define SQUAREROOTTWO 1.4142135623730950488016887242096980785696718753769480732      //2的平方根
#define EXCELDATETIME 29221  //CTime(1980,1,1,0,0,0)对应EXCEL代表的整型值
#define VARIABLES_APPEND 1
#define VARIABLES_RESET 2
#define VARIABLES_NULL 3

typedef enum _LOCATION
{
	E_LEFT = -1,    //左侧
	E_MID = 0,      //中间或在其上
	E_RIGHT = 1     //右侧
} ENUM_LOCATION;    //位置（左侧、中间、右侧）

//二元组结构体
typedef struct STRUCT_TWO_ELEMENTGROUP
{
	double fFirstValue;
	double fSecondValue;
	STRUCT_TWO_ELEMENTGROUP()
	{
		fFirstValue = 0;
		fSecondValue = 0;
	}
	STRUCT_TWO_ELEMENTGROUP(double fKeyValue1, double fValue2)
	{
		fFirstValue = fKeyValue1;
		fSecondValue = fValue2;
	}

	STRUCT_TWO_ELEMENTGROUP(const STRUCT_TWO_ELEMENTGROUP& oValueGroup)
	{
		fFirstValue = oValueGroup.fFirstValue;
		fSecondValue = oValueGroup.fSecondValue;
	}

	//重载 < 运算
	bool operator < (const STRUCT_TWO_ELEMENTGROUP& oValueGroup) const
	{
		if (fFirstValue < oValueGroup.fFirstValue)
		{
			return true;
		}
		return false;
	}

}STRU_TWO_ELEMENTGROUP;
//三元组结构体
typedef struct STRUCT_THREE_ELEMENTGROUP
{
	double fFirstValue;
	double fSecondValue;
	double fThirdValue;
	STRUCT_THREE_ELEMENTGROUP()
	{
		fFirstValue = 0;
		fSecondValue = 0;
		fThirdValue = 0;
	}
	STRUCT_THREE_ELEMENTGROUP(double fKeyValue1, double fValue2, double fValue3)
	{
		fFirstValue = fKeyValue1;
		fSecondValue = fValue2;
		fThirdValue = fValue3;
	}

	STRUCT_THREE_ELEMENTGROUP(const STRUCT_THREE_ELEMENTGROUP& oValueGroup)
	{
		fFirstValue = oValueGroup.fFirstValue;
		fSecondValue = oValueGroup.fSecondValue;
		fThirdValue = oValueGroup.fThirdValue;
	}

	//重载 < 运算
	bool operator<(const STRUCT_THREE_ELEMENTGROUP& oValueGroup) const
	{
		if (fFirstValue < oValueGroup.fFirstValue)
		{
			return true;
		}
		return false;
	}
}STRU_THREE_ELEMENTGROUP;

//三维地形数据在建模中的设置
typedef struct STRUCT_TOPOLAYER_TYPE_IN_DTM
{
	char strLayerName[MAX_NAME_LENGTH];         //图层名称
	char strLayerDescription[MAX_NAME_LENGTH];  //图层描述
	short nType;                //数据类型，1——地形点，2——约束线，3——非约束线，4——不参与建模
	double fMaxDistanceBetweenPointOnLine;      //线上点最大间距
	STRUCT_TOPOLAYER_TYPE_IN_DTM()
	{
		strLayerName[0] = '\0';         //图层名称
		strLayerDescription[0] = '\0';  //图层描述
		nType = 4;              //数据类型，1——地形点，2——约束线，3——非约束线，4——不参与建模
		fMaxDistanceBetweenPointOnLine = 5; //线上点最大间距
	}
	STRUCT_TOPOLAYER_TYPE_IN_DTM(const STRUCT_TOPOLAYER_TYPE_IN_DTM& oTopoLayerTypeInDTM)
	{
		strcpy(strLayerName, oTopoLayerTypeInDTM.strLayerName);         //图层名称
		strcpy(strLayerDescription, oTopoLayerTypeInDTM.strLayerDescription);  //图层描述
		nType = oTopoLayerTypeInDTM.nType;                //数据类型，1——地形点，2——约束线，3——非约束线，4——不参与建模
		fMaxDistanceBetweenPointOnLine = oTopoLayerTypeInDTM.fMaxDistanceBetweenPointOnLine; //线上点最大间距
	}
	STRUCT_TOPOLAYER_TYPE_IN_DTM(char* szLayerName, char* szLayerDescription, short nTopoType, double fMaxDistance)
	{
		strcpy(strLayerName, szLayerName);         //图层名称
		strcpy(strLayerDescription, szLayerDescription);  //图层描述
		nType = nTopoType;      //数据类型，1——地形点，2——约束线，3——非约束线，4——不参与建模
		fMaxDistanceBetweenPointOnLine = fMaxDistance; //线上点最大间距
	}
}STRU_TOPOLAYER_TYPE_IN_DTM;

//字符数组
typedef vector<string> VecString;

//误差最大值.
const double TOLERANCE = 1e-6;

//最大随机数.
const double INV_RAND_MAX = 1.0 / (RAND_MAX + 1.0);

// 单字节转宽字节
bool charTowchar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);
//宽字节转单字节
bool wcharTochar(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);

// 获取Office安装路径
char* GetOfficePath();
//显示进程的所有环境变量    
DWORD EnumEnvironmentVariables();
//改变环境变量
DWORD ChangeEnviromentVariables(char* szName, char* szNewValue, DWORD dwFlag);
void ShellExecuteOpen(const char* fileName, const char* exeName = "");
void ShellExecuteOpen(LPCTSTR fileName, LPCTSTR exeName = _T(""));
//1、K#+###.###  2、+###.###  3、K#  4、+#  5、 K#+###
CString FormatStat(double fStat, int mode = 1, CString prefix = _T("D"));
CString FormatAngle(double fAng);
CString ToString(double fValue, int nPrec = 3);
//读写注册表工具(Utility Stuff)
LPCTSTR RegGetString(HKEY hKey, LPCTSTR subKey, LPCTSTR name);
int RegPutString(HKEY hKey, LPCTSTR subKey, LPCTSTR name, LPCTSTR value);
int RegGetInt(HKEY hKey, LPCTSTR subKey, LPCTSTR name);
int RegPutInt(HKEY hKey, LPCTSTR subKey, LPCTSTR name, int value);

// 连接字符串
char* StrLink(int nArgCount, char* source,...);

//修改直接在源串上进行 
void StrReplace(string& strText, const string& strOld, const string& strNew);
void StrReplace(char* szText, const char* szOld, const char* szNew);

//四舍五入.
double Round(double fA, int nB);
//将浮点数根据精度取整的函数
bool Integral(double fDouble, long &nInteger, double fIntegralPrecision=0.0005);

int CompareFloat(double f1, double f2, double fPrecision = ZERO_PRECISION);
bool EqualFloat(double f1, double f2, double fPrecision = ZERO_PRECISION);
bool BetweenFloat(double f, double f1, double f2, double fPrecision = ZERO_PRECISION);
double atan4(double y, double x);
int GetIntMultiple(double f1, double f2, double fPrecision = ZERO_PRECISION);
double RoundFloat(double f, double f1, double f2);

double AngletoRadians(double angle);
double RadianstoAngle(double radians);

// 字符转换为数字
int Char2Num(char cNum);
// 数字转为货币数字
char* Num2Char(int nNum, bool bCashNum = true);
// 数字转货币数字
char* Num2Cnum(double fNum);

//long转换为CTime
CTime long2Ctime(double nDateTime);
//CTime转换为long
double Ctime2long(CTime DateTime);

//绝对值模板函数.
template<typename T>
inline T fabs(T val)
{
    if(val < 0)
        return -val;
    else
        return val;
}

//获取两者中最大值的函数模板.
template<typename T>
inline T fmax(T a, T b)
{
    if(a > b)
        return a;
    else
        return b;
}

//获取两者中最小值的函数模板.
template<typename T>
inline T fmin(T a, T b)
{
    if(a > b)
        return b;
    else
        return a;
}

template <typename T>
inline bool isSameElement(T a, vector<T> vecT)
{
	for (vector<T>::iterator iter = vecT.begin(); iter != vecT.end(); iter++)
	{
		if (a == *iter)
		{
			return true;
		}
	}
	return false;
}

template <typename T>
inline int isSameElementEx(T a, vector<T> vecT)
{
	int nPos = -1;
	for (vector<T>::iterator iter = vecT.begin(); iter != vecT.end(); iter++)
	{
		nPos++;
		if (a == *iter)
		{
			return nPos;
		}
	}
	return -1;
}

template <typename T>
inline void swapObject(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

//返回给定范围的随机数值.
inline short frand(short start, short end)
{
    assert(end > start);
    return start + rand() % (end - start);
}
inline int frand(int start, int end)
{
	assert(end > start);
	return start + rand() % (end - start);
}
inline long frand(long start, long end)
{
    assert(end > start);
    return start + rand() % (end - start);
}
inline double frand(double start, double end)
{
    assert(end > start);
    if (fabs(start) < 1 && fabs(end) < 1)
    {
        return  rand() * INV_RAND_MAX;
    }
    return start + rand() % ((long)end - (long)start);
    //return  rand() * INV_RAND_MAX;
}
inline double frand()
{
	return  rand() * INV_RAND_MAX;
}

//获取当前工作目录
CString GetCurPath();
LPSTR GetFullPathName(LPCSTR lpFileName);
LPTSTR GetFullPathName(LPCTSTR lpFileName);
//判断文件是否存在
bool FileExist(LPCSTR szFilePath);
bool FileExist(LPCTSTR szFilePath);
//判断目录是否存在
bool DirExist(LPCSTR szDirPath);
bool DirExist(LPCTSTR strDirPath);
//创建删除目录是否存在
bool ModifyDir(LPCSTR szDirPath, bool bCreate = true);
bool ModifyDir(LPCTSTR strDirPath, bool bCreate = true);
//文件目录
CString BrowseForFolder(HWND hWnd, LPCSTR lpszTitle, UINT nFlags);
//获取当前模块路径
CString GetModulePath(HINSTANCE hInstance);
//删除文件
void ShowUsage();
void EnableDebugPriv();
DWORD CloseRemoteHandle( LPCTSTR, DWORD, HANDLE );
void CloseRemoteFileHandles( LPCTSTR );
BOOL DeleteTheFile( LPCTSTR );
int DelFile(const char* szFilePath);
int DelFile(LPCTSTR szFilePath);
//写二进制或文本文件
void WriteFile(const char* szFilePath, bool bBinaryFile = false);
//读二进制或文本文件
void ReadFile(const char* szFilePath, bool bBinaryFile = false);
//复制二进制或文本文件
bool CopyFile(const char* szDestFile, const char* szOrigFile);
bool CopyFile(string strDestFile, string strOrigFile);

//获取去除文件路径的真实文件名
char* GetFileNameWithoutPath(string strFilePathName, char* strFileName);
//获取文件名称（文件名称中不含路径）中的无后缀的文件名称
string GetFileNameNoSuffix(string strFileName);

//C++语言实现，获取文件总行数，并将每行数据存储在字符串Vector中
long GetFileRowSum(char* strPrePath, char* strFileName, VecString *pStrLineVector);
//C++语言实现，去除空行，获取文件(已经包含文件路径)总行数，并将每行数据存储在字符串Vector中
long GetFileRowSum(char* strFileName, VecString *pStrLineVector);
//仅获取文件总行数
long GetFileRowSum(char* strPrePath, char* strFileName);
//仅仅获取文件总行数
long GetFileRowSum(char* strPathFileName);

//线性内插计算函数
double Interpolation(STRU_TWO_ELEMENTGROUP *pStruEleGroup, long nEleArraySize, double fFirstValue, double &fSecondValue);
//二次抛物线计算函数
double Parabola2nd(STRU_TWO_ELEMENTGROUP *pStruEleGroup, long nEleArraySize, double fFirstValue, double &fSecondValue);
//三次抛物线计算函数
double Parabola3rd(STRU_TWO_ELEMENTGROUP *pStruEleGroup, long nEleArraySize, double fFirstValue, double &fSecondValue);

//将字符串根据给定分隔符分割成多个子字符串
int ParseSubStrByDelimiter(string strLine, string* strArray, const char cDelimiter=';');
int ParseSubStrByDelimiter(CString strLine, CStringArray& strArray, const char cDelimiter=';');

//去除字符串两侧空格字符
string TrimSpace(string strSrc);
//去除字符串中所有特殊字符
string TrimSpecialStr(string strSrc, string strSpecial);
//去除字符串左侧指定字符串
string TrimLeftStr(string strSrc, string strSpecial);
//去除字符串右侧指定字符串
string TrimRightStr(string strSrc, string strSpecial);

//比较两个浮点数是否相等并且指出比较精度(如0.0000001)，如果相等则返回0；如果fFirst小于fSecond，则返回-1；如果fFirst大于fSecond，则返回1
short CompareBothDouble(double fFirst, double fSecond, double fDigitAfterPoint = ZERO_PRECISION);
//比较两个浮点数是否相等并且指出比较精度(如0.0000001)，如果相等则返回true，否则返回false
bool Equal(double fFirst, double fSecond, double fDigitAfterPoint = ZERO_PRECISION);
//将双精度型数据格式换成字符串形式，小数点后数字格式默认为3位
char* FormatDblToStr(double fSrcData, char *strDest, short nDigitAfterPoint = 3);
//将整型数据格式换成字符串形式
char* FormatIntToStr(int nSrcData, char *strDest);

//判断字符串是否全部都是ASCII码字符
bool StrIsAlpha(const char* str);
//将大写字符串转换为小写字符串
char* Str2Lower(char* str);
//将大写字符串转换为小写字符串
string Str2Lower(string &str);
//将小写字符串转换为大写字符串
char* Str2Upper(char* str);
//将小写字符串转换为大写字符串
string Str2Upper(string &str);

//获取已经使用的内存字节数
unsigned long UsedMemory();
//获取未使用的物理内存字节数
unsigned long FreeMemory();

//从字符串中查找字符的位置
bool GetValueFromString(string strLine, string& strName, string& strValue, const char cIdentify);

//将字符串根据给定分隔符分割成多个子字符串
int SpliteSubStrByDelimiter(string strLine, string* strSubArray, const int nArraySize, const char* lpszDelimiter);
//时间格式必须是 2013-01-30 18:18:18 的格式
short CompareTime(string strTime1, string strTime2);
//时间格式必须是 2013-01-30 18:18:18 的格式
short CalcDays(string strTime1, string strTime2);

//乘方函数
double ex(double fValue, int nPower);

//图标资源存为文件
bool SaveIcon(HICON hIcon, char* szFilePath, int nBit = 32);
bool SaveIcon(HINSTANCE hInstance, UINT nID, char* szFilePath, int nBit = 32);
void SaveIcon(char* szFilePath, HICON hIcon);
void SaveIcon(char* szFilePath, HINSTANCE hInstance, UINT nID);
HICON BitmapToIcon(CBitmap& bitmap);
HICON BitmapToIcon(HBITMAP hBitmap);
HBITMAP IconToBitmap(HICON hIcon);
HANDLE DwgToBmp(CString file);

bool ExecuteRes(HMODULE hModule, UINT uId, LPCTSTR sType, LPCTSTR sFile);

CString CpuSerial();
CString DiskSerial();
CString MacAddress();
char* SnKey(char* SnCode);
CString SnKey(CString SnCode);

#endif //BASEFUNC_H