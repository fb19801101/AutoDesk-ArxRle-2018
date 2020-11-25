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

#include "ArxRleCommon.h"
#include "ArxRleSystemInfo.h"


/*
int system( const char *command );
int _wsystem( const wchar_t *command );
command: Command to be executed
sample:
//system.c
#include <process.h>
void main()
{
	system( "type system.c" );
}
system函数 是可以调用一些DOS命令,比如
	system("cls");//清屏,等于在DOS上使用cls命令
下面列出常用的DOS命令,都可以用system函数调用:
ASSOC 显示或修改文件扩展名关联。
	AT 计划在计算机上运行的命令和程序。
	ATTRIB 显示或更改文件属性。
	BREAK 设置或清除扩展式 CTRL+C 检查。
	CACLS 显示或修改文件的访问控制列表(ACLs)。
	CALL 从另一个批处理程序调用这一个。
	CD 显示当前目录的名称或将其更改。
	CHCP 显示或设置活动代码页数。
	CHDIR 显示当前目录的名称或将其更改。
	CHKDSK 检查磁盘并显示状态报告。
	CHKNTFS 显示或修改启动时间磁盘检查。
	CLS 清除屏幕。
	CMD 打开另一个 Windows 命令解释程序窗口。
	COLOR 设置默认控制台前景和背景颜色。
	COMP 比较两个或两套文件的内容。
	COMPACT 显示或更改 NTFS 分区上文件的压缩。
	CONVERT 将 FAT 卷转换成 NTFS。您不能转换当前驱动器。
	COPY 将至少一个文件复制到另一个位置。
	DATE 显示或设置日期。
	DEL 删除至少一个文件。
	DIR 显示一个目录中的文件和子目录。
	DISKCOMP 比较两个软盘的内容。
	DISKCOPY 将一个软盘的内容复制到另一个软盘。
	DOSKEY 编辑命令行、调用 Windows 命令并创建宏。
	ECHO 显示消息，或将命令回显打开或关上。
	ENDLOCAL 结束批文件中环境更改的本地化。
	ERASE 删除至少一个文件。
	EXIT 退出 CMD.EXE 程序(命令解释程序)。
	FC 比较两个或两套文件，并显示不同处。
	FIND 在文件中搜索文字字符串。
	FINDSTR 在文件中搜索字符串。
	FOR 为一套文件中的每个文件运行一个指定的命令
	FORMAT 格式化磁盘，以便跟 Windows 使用。
	FTYPE 显示或修改用于文件扩展名关联的文件类型。
	GOTO 将 Windows 命令解释程序指向批处理程序中某个标明的行。
	GRAFTABL 启用 Windows 来以图像模式显示扩展字符集。
	HELP 提供 Windows 命令的帮助信息。
	IF 执行批处理程序中的条件性处理。
	LABEL 创建、更改或删除磁盘的卷标。
	MD 创建目录。
	MKDIR 创建目录。
	MODE 配置系统设备。
	MORE 一次显示一个结果屏幕。
	MOVE 将文件从一个目录移到另一个目录。
	PATH 显示或设置可执行文件的搜索路径。
	PAUSE 暂停批文件的处理并显示消息。
	POPD 还原 PUSHD 保存的当前目录的上一个值。
	PRINT 打印文本文件。
	PROMPT 更改 Windows 命令提示符。
	PUSHD 保存当前目录，然后对其进行更改。
	RD 删除目录。
	RECOVER 从有问题的磁盘恢复可读信息。
	REM 记录批文件或 CONFIG.SYS 中的注释。
	REN 重命名文件。
	RENAME 重命名文件。
	REPLACE 替换文件。
	RMDIR 删除目录。
	SET 显示、设置或删除 Windows 环境变量。
	SETLOCAL 开始批文件中环境更改的本地化。
	SHIFT 更换批文件中可替换参数的位置。
	SORT 对输入进行分类。
	START 启动另一个窗口来运行指定的程序或命令。
	SUBST 将路径跟一个驱动器号关联。
	TIME 显示或设置系统时间。
	TITLE 设置 CMD.EXE 会话的窗口标题。
	TREE 以图形模式显示驱动器或路径的目录结构。
	TYPE 显示文本文件的内容。
	VER 显示 Windows 版本。
	VERIFY 告诉 Windows 是否验证文件是否已正确写入磁盘。
	VOL 显示磁盘卷标和序列号。
	XCOPY 复制文件和目录树。
	system（执行shell 命令）
	相关函数 fork，execve，waitpid，popen
	表头文件 #include<stdlib.h>
	定义函数 int system(const char * string);
函数说明 system()会调用fork()产生子进程，由子进程来调用/bin/sh-c string来执行参数string字符串所代表的命令，此命令执行完后随即返回原调用的进程。在调用system()期间SIGCHLD 信号会被暂时搁置，SIGINT和SIGQUIT 信号则会被忽略。
	返回值 如果system()在调用/bin/sh时失败则返回127，其他失败原因返回-1。若参数string为空指针(NULL)，则返回非零值。如果system()调用成功则最后会返回执行shell命令后的返回值，但是此返回值也有可能为system()调用/bin/sh失败所返回的127，因此最好能再检查errno 来确认执行成功。
	附加说明 在编写具有SUID/SGID权限的程序时请勿使用system()，system()会继承环境变量，通过环境变量可能会造成系统安全的问题。
	范例
#include<stdlib.h>
	main()
{
	system(“ls -al /etc/passwd /etc/shadow”);
}
*/

// 单字节转宽字节
bool charTowchar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
	DWORD dwMinSize = MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, NULL, 0);

	if(dwSize < dwMinSize) return FALSE;

	MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);  
	return TRUE;
}

//宽字节转单字节
bool wcharTochar(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize) 
{   
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,NULL,0,NULL,FALSE);
	if(dwSize < dwMinSize) return FALSE;

	WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,lpszStr,dwSize,NULL,FALSE);
	return TRUE;
} 

// 获取Office安装路径
char* GetOfficePath()
{
	TCHAR szProductType[MAX_BUFSIZE];
	DWORD dwBufLen = MAX_BUFSIZE;
	LONG lRet;
	HKEY hKey;

	// 下面是打开注册表, 只有打开后才能做其他操作 
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,   // 要打开的根键 
		TEXT("SOFTWARE\\Microsoft\\Office\\11.0\\Excel\\InstallRoot"), // 要打开的子子键 
		0,                    // 这个一定要为0 
		KEY_QUERY_VALUE,      // 指定打开方式,此为读 
		&hKey);               // 用来返回句柄 

	if(lRet == ERROR_SUCCESS) // 判断是否打开成功 
	{
		// 下面开始查询 
		lRet = RegQueryValueEx(hKey,                  // 打开注册表时返回的句柄 
			TEXT("Path"),       //要查询的名称,qq安装目录记录在这个保存 
			NULL,                  // 一定为NULL或者0 
			NULL, 
			(LPBYTE)szProductType, // 我们要的东西放在这里
			&dwBufLen);

		if(lRet == ERROR_SUCCESS) // 判断是否查询成功
			RegCloseKey(hKey);
	}

	USES_CONVERSION;
	return T2A(szProductType);
}

//显示进程的所有环境变量    
DWORD EnumEnvironmentVariables()
{     
	// 获取环境变量
	LPTCH pEv = GetEnvironmentStrings();//获取所有环境变量字符串
	char* szEnvs;
	// 显示     
	for(szEnvs = (char*) pEv; *szEnvs;)      
	{      
		printf("%sn",szEnvs);
		while (*szEnvs++);
	}
	// 释放     
	FreeEnvironmentStrings(pEv);//释放由GetEnvironmentStrings返回的内存块

	//获取环境变量
	//char* szPath = NULL;
	//size_t requiredSize = 0;
	//getenv_s(&requiredSize, NULL, 0, "Path");
	//szPath = (char*)malloc(requiredSize * sizeof(char));
	//getenv_s(&requiredSize, szPath, requiredSize, "Path");

	return 0;
}

//改变环境变量
//@ LPSTR szName    需要改变的环境    
//@ LPSTR szNewValue    新的变量值    
//@ DWORD dwFlag    附加、重置还是清零，相关常量在env.h在定义    
DWORD ChangeEnviromentVariables(char* szName, char* szNewValue, DWORD dwFlag)  
{
	DWORD dwErr;
	LPVOID szVal;
	DWORD dwReturn;      
	DWORD dwNewValSize;

	int num = MultiByteToWideChar(0,0,szName,-1,NULL,0);
	wchar_t *strName = new wchar_t[num];
	MultiByteToWideChar(0,0,szName,-1,strName,num);
	num = MultiByteToWideChar(0,0,szNewValue,-1,NULL,0);
	wchar_t *strNewValue = new wchar_t[num];
	MultiByteToWideChar(0,0,szNewValue,-1,strNewValue,num);

	// 如果标志为附加则则先获取，然后将szNewValue附加到末尾
	if(dwFlag == VARIABLES_APPEND)
	{
		dwNewValSize = strlen(szNewValue)+1;   // 新变量值的大小     
		// 分配内存     
		szVal = HeapAlloc(GetProcessHeap(),0,MAX_BUFSIZE+dwNewValSize);     
		// 获取值     
		dwReturn = GetEnvironmentVariable(strName,(LPTSTR)szVal,MAX_BUFSIZE);//获取指定的环境变量

		if(dwReturn == 0)   // 出错
		{     
			dwErr = GetLastError();     
			if( ERROR_ENVVAR_NOT_FOUND == dwErr)     
			{     
				printf("Environment variable %s does not exist.n", szName);     
			}     
			else
			{     
				printf("error: %d",dwErr);     
			}     
			return FALSE;     
		}     
		else if(MAX_BUFSIZE < dwReturn)  // 缓冲区太小     
		{     
			szVal = (LPTSTR)HeapReAlloc(GetProcessHeap(), 0,szVal, dwReturn+dwNewValSize);     
			if(NULL == szVal)     
			{     
				printf("Memory errorn");
				return FALSE;     
			}     
			dwReturn = GetEnvironmentVariable(strName, (LPTSTR)szVal, dwReturn);     
			if(!dwReturn)     
			{     
				printf("GetEnvironmentVariable failed (%d)n", GetLastError());     
				return FALSE;     
			}     
		}     
		lstrcat((LPWSTR)szVal,L";");     // 分隔符
		lstrcat((LPWSTR)szVal,strNewValue);  // 附加
		//设置
		if(!SetEnvironmentVariable(strName,(LPWSTR)szVal))//设置指定的环境变量
		{     
			printf("Set Value Error %d",GetLastError());
		}

		// 释放内存
		HeapFree(GetProcessHeap(),0,szVal);     
		return TRUE;
	}     
	// 如果是重置，则直接设置     
	else if(dwFlag == VARIABLES_RESET)
	{     
		if(!SetEnvironmentVariable(strName,strNewValue))     
		{     
			printf("Set value error %d",GetLastError());     
		}     
	}     
	// 清零，忽略szNewValue     
	else if(dwFlag == VARIABLES_NULL)     
	{     
		if(!SetEnvironmentVariable(strName,NULL))     
		{
			printf("Set value error %d",GetLastError());     
		}
	}      

	//添加环境变量
	//char* szOfficePath = GetOfficePath();
	//char szStr[MAX_BUFSIZE];
	//sprintf_s(szStr,"%s%s%s",szPath,";",szOfficePath);
	//_putenv_s("Path",szStr);
	return TRUE;
}

void ShellExecuteOpen(const char* fileName, const char* exeName)
{
	USES_CONVERSION;
	if(strlen(exeName) > 0)
		::ShellExecute(NULL, L"open", A2T(exeName), A2T(fileName), NULL, SW_SHOWNORMAL);
	else
		::ShellExecute(NULL, L"open", A2T(fileName), NULL, NULL, SW_SHOWNORMAL);
}

void ShellExecuteOpen(LPCTSTR fileName, LPCTSTR exeName)
{
	USES_CONVERSION;
	ShellExecuteOpen(T2A(fileName),T2A(exeName));
}

//1、K#+###.###  2、+###.###  3、K#  4、+#
CString FormatStat(double fStat, int mode, CString prefix)
{
	CString strStat,strKm,strHm;
	double stat = fabs(fStat) + 0.0005;

	int km = INT(stat/1000);
	int hm = INT((stat-km*1000)/100);
	int sm = INT(stat-km*1000-hm*100);
	double gm = stat-INT(stat);

	switch (mode)
	{
	case 1:
		strStat.Format(_T("%sK%d+%.3d.%.3d"),prefix,fStat < 0 ? -km:km,hm*100+sm,INT(gm*1000));
		break;
	case 2:
		strStat.Format(_T("+%.3d.%.3d"),hm*100+sm,INT(gm*1000));
		break;
	case 3:
		strStat.Format(_T("%sK%d"),prefix,fStat < 0 ? -km:km);
		break;
	case 4:
		strStat.Format(_T("+%d"),hm);
		break;
	case 5:
		strStat.Format(_T("%sK%d+%.3d"),prefix,fStat < 0 ? -km:km,hm*100+sm);
		break;
	}

	return strStat;
}

CString FormatAngle(double fAng)
{
	double ang = fabs(fAng);
	int a = INT(ang);
	int b = INT((ang-a)*60);
	double c = ((ang-a)*60-b)*60;
	CString str;
	str.Format(L"%d°%d'%.2f''",fAng < 0 ? -a:a,b,c);
	return str;
}

CString ToString(double fValue, int nPrec)
{
	CString str,prec;
	prec.Format(L"%d",nPrec);
	prec ? prec = L"%."+prec+L"f" : prec = L"%"+prec+L"d";
	str.Format(prec,fValue);
	return str;
}

//读写注册表工具(Utility Stuff)
LPCTSTR RegGetString(HKEY hKey, LPCTSTR subKey, LPCTSTR name)
{
	HKEY hSubKey;
	DWORD type;
	LPCTSTR value = new wchar_t[4096];
	DWORD size = sizeof(value);

	value = '\0';
	if ( RegOpenKeyEx(hKey, subKey, 0, KEY_QUERY_VALUE, &hSubKey) == ERROR_SUCCESS )
	{
		if ( (RegQueryValueEx(hSubKey, name, 0, &type, (LPBYTE)value, &size) != ERROR_SUCCESS) ||
			(type != REG_SZ) )
			value = '\0';
		RegCloseKey(hSubKey);
	}

	return value;
}

int RegPutString(HKEY hKey, LPCTSTR subKey, LPCTSTR name, LPCTSTR value)
{
	HKEY hSubKey;
	DWORD disp;
	int retval = 0;

	if ( RegCreateKeyEx(hKey, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hSubKey, &disp) == ERROR_SUCCESS )
	{
		if ( RegSetValueEx(hSubKey, name, 0, REG_SZ, (LPBYTE)value, _tclen(value) + 1) == ERROR_SUCCESS )
			retval = 1;
		RegCloseKey(hSubKey);
	}
	return retval;
}

int RegGetInt(HKEY hKey, LPCTSTR subKey, LPCTSTR name)
{
	HKEY hSubKey;
	DWORD type;
	DWORD value;
	DWORD size = sizeof(value);
	if ( RegOpenKeyEx(hKey, subKey, 0, KEY_QUERY_VALUE, &hSubKey) == ERROR_SUCCESS )
	{
		if ( (RegQueryValueEx(hSubKey, name, 0, &type, (LPBYTE)&value, &size) != ERROR_SUCCESS) ||
			(type != REG_DWORD) )
			value = 0;
		RegCloseKey(hSubKey);
	}
	return value;
}

int RegPutInt(HKEY hKey, LPCTSTR subKey, LPCTSTR name, int value)
{
	HKEY hSubKey;
	DWORD disp;
	int retval = 0;
	if ( RegCreateKeyEx(hKey, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hSubKey, &disp) == ERROR_SUCCESS )
	{
		if ( RegSetValueEx(hSubKey, name, 0, REG_DWORD, (LPBYTE)&value, sizeof(value)) == ERROR_SUCCESS )
			retval = 1;
		RegCloseKey(hSubKey);
	}
	return retval;
}

// 连接字符串
char* StrLink(int nArgCount, char* source, ...)
{
	setlocale(LC_ALL,"");

	va_list arg_ptr;           //变参列表指针
	va_start(arg_ptr, source); //arg_ptr指向第一个变参
	char szStr1[MAX_BUFSIZE];
	char szStr2[MAX_BUFSIZE];
	strcpy_s(szStr2,source);

	for(; --nArgCount > 0;)
	{
		char* key = va_arg(arg_ptr, char*);

		sprintf_s(szStr1,"%s%s",szStr2,key);
		strcpy_s(szStr2,szStr1);
	}

	va_end(arg_ptr); //复位变参指针

	char* pStr = szStr2;
	return pStr;
}

// 字符转换为数字
int Char2Num(char cNum)
{
	int nNum = -3;
	if(cNum == '0')
		nNum = 0;
	else if(cNum == '1')
		nNum = 1;
	else if(cNum == '2')
		nNum = 2;
	else if(cNum == '3')
		nNum = 3;
	else if(cNum == '4')
		nNum = 4;
	else if(cNum == '5')
		nNum = 5;
	else if(cNum == '6')
		nNum = 6;
	else if(cNum == '7')
		nNum = 7;
	else if(cNum == '8')
		nNum = 8;
	else if(cNum == '9')
		nNum = 9;
	else if(cNum == '.')
		nNum = -1;
	else if(cNum == '-')
		nNum = -2;

	return nNum;
}

// 数字转为货币数字
char* Num2Char(int nNum, bool bCashNum)
{
	char szStr[3];
	switch(nNum)
	{
	case 0:
		if(bCashNum)
			strcpy_s(szStr,"零");
		else
			strcpy_s(szStr,"○");
		break;
	case 1:
		if(bCashNum)
			strcpy_s(szStr,"壹");
		else
			strcpy_s(szStr,"一");
		break;
	case 2:
		if(bCashNum)
			strcpy_s(szStr,"贰");
		else
			strcpy_s(szStr,"二");
		break;
	case 3:
		if(bCashNum)
			strcpy_s(szStr,"叁");
		else
			strcpy_s(szStr,"三");
		break;
	case 4:
		if(bCashNum)
			strcpy_s(szStr,"肆");
		else
			strcpy_s(szStr,"四");
		break;
	case 5:
		if(bCashNum)
			strcpy_s(szStr,"伍");
		else
			strcpy_s(szStr,"五");
		break;
	case 6:
		if(bCashNum)
			strcpy_s(szStr,"陆");
		else
			strcpy_s(szStr,"六");
		break;
	case 7:
		if(bCashNum)
			strcpy_s(szStr,"柒");
		else
			strcpy_s(szStr,"七");
		break;
	case 8:
		if(bCashNum)
			strcpy_s(szStr,"捌");
		else
			strcpy_s(szStr,"八");
		break;
	case 9:
		if(bCashNum)
			strcpy_s(szStr,"玖");
		else
			strcpy_s(szStr,"九");
		break;
	}

	char* pStr = szStr;
	return pStr;
}

//修改直接在源串上进行 
void StrReplace(string& strText,const string& strOld,const string& strNew)
{ 
	size_t pos = 0; 
	string& tempStr = strText;
	string::size_type oldStrLen = strOld.length();
	string::size_type newStrLen = strNew.length();

	while(true)
	{ 
		pos = tempStr.find(strOld, pos); 
		if(pos == string::npos) break;

		tempStr.replace(pos, oldStrLen, strNew);
		pos += newStrLen;
	}
}
void StrReplace(char* szText,const char* szOld,const char* szNew)
{ 
	size_t pos = 0; 
	string tempStr(szText);
	string strOld(szOld);
	string strNew(szNew);
	string::size_type oldStrLen = strOld.length();
	string::size_type newStrLen = strNew.length();

	while(true)
	{ 
		pos = tempStr.find(strOld, pos); 
		if(pos == string::npos) break; 

		tempStr.replace(pos, oldStrLen, strNew);
		pos += newStrLen;
	}

	strcpy_s(szText,(tempStr.length()+1)*sizeof(char),tempStr.c_str());
}

//四舍五入.
double Round(double fA, int nB)
{
	double exp = 1.0;
	for(int i=0; i<nB; i++)
		exp *= 10.0;
	int nC = INT(fA*exp+0.5);
	return nC/exp;
}
//将浮点数根据精度取整的函数
bool Integral(double fDouble, long &nInteger, double fIntegralPrecision)
{
	if (fabs(fDouble - ((long)fDouble)) < fIntegralPrecision)
	{
		nInteger = ((long)fDouble);
		return true;
	}
	else
		return false;
}

int CompareFloat(double f1, double f2, double fPrecision)
{
	if(fabs(f1 - f2) < fPrecision) return 0;
	else if(f1 > f2) return 1;
	return -1;
}

bool EqualFloat(double f1, double f2, double fPrecision)
{
	if(fabs(f1 - f2) <= fPrecision) return true;
	return false;
}

bool BetweenFloat(double f, double f1, double f2, double fPrecision)
{
	if(fabs(f - f1) <= fPrecision) return true;
	else if(fabs(f - f2) <= fPrecision) return true;
	else if(f > f1 && f < f2) return true;
	return false;
}

double atan4(double y, double x) //0---2*PI
{
	double ang = atan2(y, x);
	if(y > 0)
		return ang;
	return ang + PI * 2;
}

int GetIntMultiple(double f1, double f2, double fPrecision)
{
	if(fabs(f2) < fPrecision)
		return 0;
	int nSign = ((f1 / f2) > 0 ? 1 : -1);
	double f11 = fabs(f1);
	double f22 = fabs(f2);
	double f0 = f11 / f22;
	int n = int(f0 + fPrecision);
	if(fabs(f11 - f22 * n) < fPrecision)
		return n * nSign;

	return 0;
}

double RoundFloat(double f, double f1, double f2)
{
	if(BetweenFloat(f, f1, f1 + (f2 - f1) * 0.5))
		return f1;
	else if(BetweenFloat(f, f1 + (f2 - f1) * 0.5, f2))
		return f2;
	return f;
}

double AngletoRadians(double angle)
{
	return angle*PI / 180;
}
double RadianstoAngle(double radians)
{
	return radians * 180 / PI;
}

 // 数字转货币数字
const char hzSymbol[2][3]={"整","负"};
const char hzUnit[15][3]={"分","角","元","拾","佰","仟","万","拾","佰","仟","亿","拾","佰","仟","万"};  
const char hzNum[10][3]={"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};  
const char regex1[3][5] = {"零仟", "零佰", "零拾"};
const char regex2[3][5] = {"零亿", "零万", "零元"};
const char regex3[3][3] = {"亿", "万", "元"};
const char regex4[2][5] = {"零角", "零分"};
char* Num2Cnum(double fNum)
{
	setlocale(LC_ALL,"");
	char szStr[MAX_PATH];
	char szStr1[MAX_PATH] = "";
	char szCnum[MAX_PATH];
	bool bIntCash = false;
	bool bIsZero = false;
	int nPrecision = 2;
	if(CompareBothDouble(fNum,INT(fNum)) == 0)
	{
		sprintf_s(szCnum, "%.0f", fNum);
		nPrecision = -1;
		bIntCash = true;
	}
	else if(CompareBothDouble(fNum,INT(fNum*10)/10.0) == 0)
	{
		sprintf_s(szCnum, "%.1f", fNum);
		nPrecision = 1;
	}
	else
	{
		sprintf_s(szCnum, "%.2f", fNum);
		nPrecision = 2;
	}

	int nCnumLen = strlen(szCnum);
	for(int i=0; i<nCnumLen; i++)
	{
		int nNum = Char2Num(szCnum[i]);
		if(nNum > -3)
		{
			if(nNum == -2)
			{
				sprintf_s(szStr,"%s%s",szStr1,hzSymbol[1]);
				strcpy_s(szStr1,szStr);
			}
			else if(nNum == -1)
				nCnumLen = nCnumLen+1;
			else
			{
				sprintf_s(szStr,"%s%s",szStr1,hzNum[nNum]);
				strcpy_s(szStr1,szStr);

				sprintf_s(szStr,"%s%s",szStr1,hzUnit[nCnumLen-i-nPrecision]);
				strcpy_s(szStr1,szStr);
			}
		}
	}

	if(bIntCash)
		sprintf_s(szStr,"%s%s",szStr1,hzSymbol[0]);

	// 第一轮转换把 "零仟", 零佰","零拾"等字符串替换成一个"零"   
	for(int i = 0; i < 3; i ++)
	{
		StrReplace(szStr, regex1[i], "零");
	}
	// 第二轮转换考虑 "零亿","零万","零元"等情况   
	// "亿","万","元"这些单位有些情况是不能省的，需要保留下来   
	for(int i = 0; i < 3; i ++)
	{   
		// 当第一轮转换过后有可能有很多个零叠在一起   
		// 要把很多个重复的零变成一个零   
		StrReplace(szStr, "零零零", "零");
		StrReplace(szStr, "零零", "零");
		StrReplace(szStr, regex2[i], regex3[i]);
	}
	// 第三轮转换把"零角","零分"字符串省略
	for(int i = 0; i < 2; i ++)
	{   
		StrReplace(szStr, regex4[i], "");
	}
	// 当"万"到"亿"之间全部是"零"的时候，忽略"亿万"单位，只保留一个"亿"   
	StrReplace(szStr, "亿万", "亿");

	char* pStr = szStr;
	return pStr;
}

//long转换为CTime
CTime long2Ctime(double ftime)
{
	//获取当前时间并保存到curTime
	//CTime CurTime = CTime::GetCurrentTime();
	//long nBeginYear = CurTime.GetYear();//获取当前年份
	//long nBeginMonth = CurTime.GetMonth();//获取当前月份
	//long nBeginDay = CurTime.GetDay();//获取当前日期
	//long nBeginHour = CurTime.GetHour();//获取当前小时时间
	//long nBeginMin = CurTime.GetMinute();//获取当前分钟时间
	//long nBeginSec = CurTime.GetSecond();//获取当前秒时间
	double fHour = (ftime-INT(ftime))*24;
	int nHour = INT(fHour);
	double fMin = (fHour-nHour)*60;
	int nMin = INT(fMin);
	double fSecond = (fMin-nMin)*60;
	int nSecond = INT(fSecond);
	CTimeSpan timeSpan(ftime-EXCELDATETIME,nHour,nMin,nSecond);
	CTime time = CTime(1980,1,1,0,0,0)+timeSpan;

	return time;
}

//CTime转换为long
double Ctime2long(CTime time)
{
	CTimeSpan timeSpan = time-CTime(1980,1,1,0,0,0);
	double ftime = EXCELDATETIME+timeSpan.GetDays()+(timeSpan.GetHours()+timeSpan.GetMinutes()/60.0+timeSpan.GetSeconds()/3600.0)/24.0;

	return ftime;
}

//当前工作目录路径
char g_strCurrentWorkPath[MAX_PATH_LENGTH] = "";
//数据文件格式模板
extern const char g_strCRDFileTpl[20] = "%s%.3d%.2d.CRD\0";
//自定义后缀的数据文件格式模板
extern const char g_strDataFileTpl[20] = "%s%.3d%.2d.%s\0";

CString GetCurPath()
{
	wchar_t path[MAX_PATH];
	GetModuleFileName(ArxRleApp::m_hInstance, path,MAX_PATH);
	CString cur_path = path;
	int index = cur_path.ReverseFind('\\');
	cur_path = cur_path.Mid(0,index);
	return cur_path;
}
LPTSTR GetFullPathName(LPCTSTR lpFileName)
{
	LPTSTR lpPath = new TCHAR[MAX_PATH];
	GetFullPathName(lpFileName, MAX_PATH, lpPath, NULL );
	return lpPath;
}
LPSTR GetFullPathName(LPCSTR lpFileName)
{
	USES_CONVERSION;
	return T2A(GetFullPathName(A2T(lpFileName)));
}

//判断文件是否存在
bool FileExist(LPCSTR szFilePath)
{
	fstream file;
	file.open(szFilePath,ios::in);

	if(file)
		return true;
	else
		return false;
}
bool FileExist(LPCTSTR strFilePath)
{
	CFileFind finder;
	if (finder.FindFile(strFilePath) != TRUE)
		return FALSE;
	return TRUE;
}

//判断目录是否存在
bool DirExist(LPCSTR szDirPath)
{
	WIN32_FIND_DATA wfd;
	wchar_t wchar[MAX_PATH_LENGTH];
	charTowchar(szDirPath, wchar, MAX_PATH_LENGTH);
	HANDLE hFind = FindFirstFile(wchar, &wfd);

	if((hFind != INVALID_HANDLE_VALUE) &&
	  (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		return true;

	FindClose(hFind);
	return false;
}
bool DirExist(LPCTSTR strDirPath)
{
	//PathIsDirectory(strDirPath);
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(strDirPath, &wfd);

	if((hFind != INVALID_HANDLE_VALUE) &&
		(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		return true;

	FindClose(hFind);
	return false;
}

//创建删除目录是否存在
bool ModifyDir(LPCSTR szDirPath, bool bCreate)
{
	if(bCreate)
	{
		_mkdir(szDirPath);
		return true;
	}
	else
	{
		string str(szDirPath);
		while(true)
		{
			string::size_type pos = str.find_last_of("\\");
			string str1 = str;
			str = str.substr(0,pos);
			if( pos != -1)
			{
				_rmdir(str1.c_str());
			}
			else
				break;
			
			return true;
		}
	}

	return false;
}
bool ModifyDir(LPCTSTR strDirPath, bool bCreate)
{
	USES_CONVERSION;
	if(bCreate)
	{
		_mkdir(T2A(strDirPath));
		return true;
	}
	else
	{
		string str(T2A(strDirPath));
		while(true)
		{
			string::size_type pos = str.find_last_of("\\");
			string str1 = str;
			str = str.substr(0,pos);
			if( pos != -1)
			{
				_rmdir(str1.c_str());
			}
			else
				break;

			return true;
		}
	}

	return false;
}

//文件目录
CString BrowseForFolder(HWND hWnd, LPWSTR lpszTitle, UINT nFlags)
{
	// We're going to use the shell to display a 
	// "Choose Directory" dialog box for the user.
	CString strResult = "";

	LPMALLOC lpMalloc;

	if (::SHGetMalloc(&lpMalloc) != NOERROR)
	{
		// failed to get allocator  
		return strResult; 
	}

	LPWSTR szBuffer = new wchar_t[MAX_PATH];
	LPWSTR szDisplayName = new wchar_t[MAX_PATH];

	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = hWnd;
	// set root at Desktop
	browseInfo.pidlRoot = NULL; 
	browseInfo.pszDisplayName = szDisplayName;
	browseInfo.lpszTitle = lpszTitle;
	browseInfo.ulFlags = nFlags;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;

	LPITEMIDLIST lpItemIDList;

	if ((lpItemIDList = ::SHBrowseForFolder(&browseInfo)) != NULL)
	{
		// Get the path of the selected folder from the item ID list.
		if (::SHGetPathFromIDList(lpItemIDList, szBuffer))
		{
			// At this point, szBuffer contains the path the user chose.
			if (szBuffer[0] == '\0')
			{
				// SHGetPathFromIDList failed, or SHBrowseForFolder failed.
				AfxMessageBox(L"Failed to get directory", MB_ICONSTOP|MB_OK);
				return strResult;
			}

			// We have a path in szBuffer!
			strResult = szBuffer;
			return strResult;
		}
		else
		{
			// The thing referred to by lpItemIDList 
			// might not have been a file system object.
			// For whatever reason, SHGetPathFromIDList didn't work!
			AfxMessageBox(L"Failed to get directory", MB_ICONSTOP|MB_OK);
			return strResult; // strResult is empty 
		}
		lpMalloc->Free(lpItemIDList);
		lpMalloc->Release();      
	}
	return strResult;
}

//获取当前模块路径
CString GetModulePath(HINSTANCE hInstance)
{
	TCHAR path[MAX_PATH];
	int len = GetModuleFileName(hInstance, path, MAX_PATH);
	CString str = path;
	str = str.Left(str.ReverseFind('\\'));
	return str;
}

//Show the help
void ShowUsage()
{
	//Usage information
	_printf( _T("ForceDelete 1.0 for Win7/WinNT/Win2k\n") );
	_printf( _T("\n") );
	_printf( _T("Deletes a given file even if it is locked by another process.\n") );
	_printf( _T("Written by Zoltan Csizmadia, zoltan_csizmadia@yahoo.com\n") );
	_printf( _T("\n") );
	_printf( _T("Usage: FORCEDEL.EXE [/S] filename\n") );
	_printf( _T("\n") );
	_printf( _T("          /S             Soft delete. Like the \"del\" command\n") );
	_printf( _T("          filename       File name you want to delete\n") );
	_printf( _T("\n") );
	_printf( _T("Examples:\n") );
	_printf( _T("\n") );
	_printf( _T("       FORCEDEL.EXE C:\\TEST.TXT\n") );
}

//Enable DEBUG privilege
void EnableDebugPriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	// enable the SeDebugPrivilege
	if ( ! OpenProcessToken( GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
	{
		_printf( _T("OpenProcessToken() failed, Error = %d SeDebugPrivilege is not available.\n"), GetLastError() );
		return;
	}

	if ( ! LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &sedebugnameValue ) )
	{
		_printf( _T("LookupPrivilegeValue() failed, Error = %d SeDebugPrivilege is not available.\n"), GetLastError() );
		CloseHandle( hToken );
		return;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if ( ! AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ) )
		_printf( _T("AdjustTokenPrivileges() failed, Error = %d SeDebugPrivilege is not available.\n"), GetLastError() );

	CloseHandle( hToken );
}

//Close a handle in a remote process
DWORD CloseRemoteHandle( LPCTSTR lpProcessName, DWORD processID, HANDLE handle )
{
	HANDLE ht = 0;
	DWORD rc = 0;

	_printf( _T("Closing handle in process #%d (%s) ... "), processID, lpProcessName );

	// open the process
	HANDLE hProcess = OpenProcess( PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION |
		PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, processID );

	if ( hProcess == NULL )
	{
		rc = GetLastError();
		_printf( _T("OpenProcess() failed\n") );
		return rc;
	}

	// load kernel32.dll
	HMODULE hKernel32 = LoadLibrary( _T("kernel32.dll") );

	// CreateRemoteThread()
	ht = CreateRemoteThread( 
		hProcess, 
		0, 
		0, 
		(DWORD (__stdcall *)( void *))GetProcAddress( hKernel32, "CloseHandle" ),
		handle, 
		0, 
		&rc );

	if ( ht == NULL )
	{
		//Something is wrong with the privileges, or the process doesn't like us
		rc = GetLastError();
		_printf( _T("CreateRemoteThread() failed\n") );
		goto cleanup;
	}

	switch ( WaitForSingleObject( ht, 2000 ) )
	{
	case WAIT_OBJECT_0:
		//Well done
		rc = 0;
		_printf( _T("Ok\n"), rc );

		break;

	default:
		//Oooops, shouldn't be here
		rc = GetLastError();
		_printf( _T("WaitForSingleObject() failed\n") );
		goto cleanup;

		break;
	}

cleanup:

	//Closes the remote thread handle
	CloseHandle( ht );

	//Free up the kernel32.dll
	if ( hKernel32 != NULL)
		FreeLibrary( hKernel32 );

	//Close the process handle
	CloseHandle( hProcess );

	return rc;
}

//Closes the file handles in the processes which are using this file
void CloseRemoteFileHandles( LPCTSTR lpFileName )
{
	CString deviceFileName;
	CString fsFilePath;
	CString name;
	CString processName;
	SystemHandleInformation hi;
	SystemProcessInformation pi;
	SystemProcessInformation::SYSTEM_PROCESS_INFORMATION* pPi;

	//Convert it to device file name
	if ( !SystemInfoUtils::GetDeviceFileName( lpFileName, deviceFileName ) )
	{
		_printf( _T("GetDeviceFileName() failed.\n") );
		return;
	}

	//Query every file handle (system wide)
	if ( !hi.SetFilter( _T("File"), TRUE ) )
	{
		_printf( _T("SystemHandleInformation::SetFilter() failed.\n") );
		return;
	}

	if ( !pi.Refresh() )
	{
		_printf( _T("SystemProcessInformation::Refresh() failed.\n") );
		return;
	}

	//Iterate through the found file handles
	for ( POSITION pos = hi.m_HandleInfos.GetHeadPosition(); pos != NULL; )
	{
		SystemHandleInformation::SYSTEM_HANDLE& h = hi.m_HandleInfos.GetNext(pos);

		if ( !pi.m_ProcessInfos.Lookup( h.ProcessID, pPi ) )
			continue;

		if ( pPi == NULL )
			continue;

		//Get the process name
		SystemInfoUtils::Unicode2CString( &pPi->usName, processName );

		//NT4 Stupid thing if I query the name of a file in services.exe
		//Messengr service brings up a message dialog ??? :(
		if ( INtDll::dwNTMajorVersion == 4 && _tcsicmp( processName, _T("services.exe") ) == 0 )
			continue;

		//what's the file name for this given handle?
		hi.GetName( (HANDLE)h.HandleNumber, name, h.ProcessID );

		//This is what we want to delete, so close the handle
		if ( _tcsicmp( name, deviceFileName ) == 0 )
			CloseRemoteHandle( processName, h.ProcessID, (HANDLE)h.HandleNumber );
	}
}

//Deletes the file
BOOL DeleteTheFile( LPCTSTR lpFileName )
{
	//Deletes the file
	BOOL rc = ::DeleteFile( lpFileName );

	if ( rc )
		_printf( _T("Successfully deleted.\n") );
	else
		_printf( _T("Couldn't delete. Error = %d\n"), GetLastError() );

	return rc;
}

//删除文件
int DelFile(const char* szFilePath)
{
	int rc = 0;
	BOOL bUsage = TRUE;
	BOOL bSoft = FALSE;

	TCHAR lpPath[_MAX_PATH];
	LPCTSTR lpFileName = NULL;

	// check the parameters
	{
		if ( stricmp( szFilePath, "/?" ) == 0 || stricmp( szFilePath, "-?" ) == 0 ||
			 stricmp( szFilePath, "/h" ) == 0 || stricmp( szFilePath, "-h" ) == 0 ||
			 stricmp( szFilePath, "/help" ) == 0 || stricmp( szFilePath, "-help" ) == 0 )
		{
			// help
			bUsage = TRUE;
		}
		else
		{
			if ( stricmp( szFilePath, "/S" ) == 0 || stricmp( szFilePath, "-S" ) == 0 )
			{
				//Soft delete mode enabled
				bSoft = TRUE;
			}
			else
			{
				USES_CONVERSION;
				lpFileName = A2T(szFilePath);
				bUsage = FALSE;
			}
		}
	};

	if ( bUsage )
	{
		ShowUsage();

		return -1;
	}

	//Enable debug privilege
	EnableDebugPriv();

	//Get the full path
	if ( GetFullPathName( lpFileName, _MAX_PATH, lpPath, NULL ) == 0 )
	{
		_printf( _T("GetFullPathName() failed. Error = %d\n"), GetLastError() );
		return 2;
	}

	//Close every handle in the system for this file
	if ( !bSoft )
		CloseRemoteFileHandles( lpPath );

	//Try to delete it
	rc = DeleteTheFile( lpPath );

	return rc ? 0 : 1;
}
int DelFile(LPCTSTR szFilePath)
{
	USES_CONVERSION;
	return DelFile(T2A(szFilePath));
}

//写二进制或文本文件
//@ const char* szFilePath 文件名称含路径
//@ bool bBinaryFile 是否写二进制文件
void WriteFile(const char* szFilePath, bool bBinaryFile)
{
	//文件的打开模式
	//文件操作时，如果不显示指定打开模式，文件流类将使用默认值。
	//在<fstream> 中定义了如下打开模式和文件属性:
	//ios::app // 从后面添加
	//ios::ate // 打开并找到文件尾
	//ios::binary // 二进制模式I/O（与文本模式相对)
	//ios::in // 只读打开
	//ios::out // 写打开
	//ios::trunc // 将文件截为 0 长度
	//可以使用位操作符 OR 组合这些标志，比如
	//ofstream logFile("log.dat", ios::binary | ios::app);

	if(bBinaryFile)
	{
		//写二进制文件应该使用ofstream类，文件的打开模式一定要是 binary，如果传入的不是 binary, 文件将以ASCII方式打开。
		std::ofstream fout(szFilePath, std::ios::binary);
		int nNum = 20;
		std::string str("Hello, world");

		fout.write((char*)&nNum, sizeof(int));
		fout.write(str.c_str(), sizeof(char) * (str.size()));
		fout.close();
	}
	else
	{
		//写文本文件则比较简单
		std::ofstream fout(szFilePath);
		int nNum = 20;
		std::string str("Hello, world");

		fout << nNum << "," << str << std::endl;

		fout.close();
	}
}

//读二进制或文本文件
//@ const char* szFilePath 文件名称含路径
//@ bool bBinaryFile 是否写二进制文件
void ReadFile(const char* szFilePath, bool bBinaryFile)
{
	//文件的打开模式
	//文件操作时，如果不显示指定打开模式，文件流类将使用默认值。
	//在<fstream> 中定义了如下打开模式和文件属性:
	//ios::app // 从后面添加
	//ios::ate // 打开并找到文件尾
	//ios::binary // 二进制模式I/O（与文本模式相对)
	//ios::in // 只读打开
	//ios::out // 写打开
	//ios::trunc // 将文件截为 0 长度
	//可以使用位操作符 OR 组合这些标志，比如
	//ofstream logFile("log.dat", ios::binary | ios::app);

	if(bBinaryFile)
	{
		//读取二进制文件可以使用ifstream 类来进行，文件的打开模式一定要是 binary，如果传入的不是 binary, 文件将以ASCII方式打开
		std::ifstream fin(szFilePath, std::ios::binary);

		if(!fin.bad())  
		{  
			while(!fin.eof())
			{  
				int nNum;
				char szBuf[MAX_STRSIZE] = {0};  
				fin.read((char*)&nNum, sizeof(int));
				fin.read(szBuf, sizeof(char) * MAX_STRSIZE);  

				USES_CONVERSION;
				MessageBox(NULL,A2T(szBuf),L"",MB_OK);
			}
		}

		fin.close();
	}
	else
	{
		//读取文本文件则比较简单
		std::ifstream fin("b.dat");
		int nNum;
		char szBuf[MAX_STRSIZE] = {0};

		fin >> nNum >> szBuf;
		std::cout << "int = " << nNum << std::endl;
		std::cout << "str = " << szBuf << std::endl;

		fin.close();
	}
}

//复制二进制或文本文件
//@ const char* szDestFile 目标文件名称含路径
//@ const char* szOrigFile 源文件名称含路径
//@ bool bBinaryFile 是否写二进制文件
bool CopyFile(const char* szDestFile, const char* szOrigFile)  
{  
	if(szDestFile == NULL)
		return false;  
	if(szOrigFile == NULL)  
		return false;  

	bool bRet = true;  
	std::ofstream fout(szDestFile, std::ios::binary | std::ios::app);  
	std::ifstream fin(szOrigFile, std::ios::binary);  

	if(fin.bad())  
		bRet = false;
	else  
	{  
		while(!fin.eof())  
		{  
			char szBuf[MAX_STRSIZE] = {0};
			fin.read(szBuf, sizeof(char) * MAX_STRSIZE);  
			if(fout.bad())
			{
				bRet = false;  
				break;  
			}

			fout.write(szBuf, sizeof(char) * MAX_STRSIZE);  
		}
	}

	fin.close();  
	fout.close();  
	return bRet;
} 
bool CopyFile(string strDestFile, string strOrigFile)
{
	if(strDestFile.length() == 0)
		return false;  

	if(strOrigFile.length() == 0)  
		return false;

	HANDLE hSrcFile, hDestFile; 
	hSrcFile = CreateFile((LPWSTR)strOrigFile.c_str(),     // open MYFILE.TXT 
		GENERIC_READ,              // open for reading
		FILE_SHARE_READ,           // share for reading 
		NULL,                      // no security 
		OPEN_EXISTING,             // existing file only 
		FILE_ATTRIBUTE_NORMAL,     // normal file
		NULL);                     // no attr. template 
	if (hSrcFile == INVALID_HANDLE_VALUE) 
		return false; 

	hDestFile = CreateFile((LPWSTR)strDestFile.c_str(),           // create MYFILE.TXT 
		GENERIC_WRITE ,                // open for writing
		0,                            // do not share 
		NULL,                         // no security 
		CREATE_ALWAYS,                // overwrite existing 
		FILE_ATTRIBUTE_NORMAL,       // normal file
		NULL);
	if (hDestFile == INVALID_HANDLE_VALUE)
		return false;
	char* buffer = new char[1024]; 

	ULONG lpNumberOfBytesRead, lpNumberOfBytesWritten;
	DWORD fileSize, offset = 0;
	fileSize = GetFileSize(hSrcFile, NULL);
	if (fileSize == INVALID_FILE_SIZE)
		return false;
	while (offset < fileSize) {
		BOOL bFlag = ReadFile(hSrcFile, buffer, 1024, &lpNumberOfBytesRead, NULL);
		if (!bFlag) {
			return false;
		}
		WriteFile(hDestFile, buffer, 1024, &lpNumberOfBytesWritten, NULL);
		offset += 1024;
	}
	CloseHandle(hSrcFile);
	CloseHandle(hDestFile);
	delete[] buffer;
	return true;
}

//获取去除文件路径的真实文件名
char* GetFileNameWithoutPath(string strFilePathName, char* strFileName)
{
	int nPos = 0;
	reverse(strFilePathName.begin(), strFilePathName.end());
	nPos = strFilePathName.find('\\');
	if(nPos > 0)
	{
		strFilePathName = strFilePathName.substr(0, nPos);
		reverse(strFilePathName.begin(), strFilePathName.end());
		strcpy_s(strFileName, sizeof(strFileName),strFilePathName.c_str());
		return strFileName;
	}
    
	return NULL;
}

//获取无后缀的文件名称
string GetFileNameNoSuffix(string strFileName)
{
    string strFileNameNoSuffix;
    int nPointPos = strFileName.find(".");
    strFileNameNoSuffix = strFileName.substr(0, nPointPos);
    
	return strFileNameNoSuffix;
}

//C++语言实现，获取文件总行数，并将每行数据存储在字符串Vector中
long GetFileRowSum(char* strPrePath, char* strFileName, VecString *pStrLineVector)
{
    long nRowSum = 0;
    char strFilePathName[MAX_PATH_LENGTH];
    sprintf_s(strFilePathName, "%s\\%s", strPrePath, strFileName);
    if(!FileExist(strFilePathName))
    {
        return nRowSum;
    }
	
    char strPath[MAX_PATH_LENGTH];
    sprintf_s(strPath, "%s%s%s", strPrePath, "\\", strFileName);
    
    ifstream input(strPath);
    if(!input)
    {
        nRowSum = 0;
    }
    else
    {
        char cLine[MAX_LMSG_LENGTH];
        string strLine;
		//使用STL获取文件长度大小
		int nFilePos = input.tellg(); // 记录下当前位置 
		input.seekg(0, ios_base::end); // 移动到文件尾 
		int nFileSize = input.tellg(); // 取得当前位置的指针长度 即文件长度 
        input.seekg(nFilePos); // 移动到原来的位置

		if(nFileSize > MAX_FILESIZE_1MB*2)
		{
			while (input)
			{
				input.getline(cLine, MAX_PATH_LENGTH);		

				nRowSum++;
				if(NULL != pStrLineVector)
				{
					strLine = cLine;
					pStrLineVector->push_back(strLine);
				}
			}
		}
		else
		{
			while (input)
			{
				input.getline(cLine, MAX_LMSG_LENGTH);
				if(NULL != pStrLineVector)
				{
					strLine = cLine;
					pStrLineVector->push_back(strLine);
				}
				nRowSum++;
			}
		}
    }
    input.close();
	
    return nRowSum;
}

//C++语言实现，去除空行，获取文件(已经包含文件路径)总行数，并将每行数据存储在字符串Vector中
long GetFileRowSum(char* strFileName, VecString *pStrLineVector)
{
    long nRowSum = 0;   
    ifstream input(strFileName);
    if(!input)
    {
        nRowSum = 0;
    }
    else
    {
		//使用STL获取文件长度大小
		int nFilePos = input.tellg();  // 记录下当前位置 
		input.seekg(0, ios_base::end); // 移动到文件尾 
		int nFileSize = input.tellg(); // 取得当前位置的指针长度 即文件长度，单位是字节数 
        input.seekg(nFilePos);         // 移动到原来的位置

        char cLine[MAX_LMSG_LENGTH];
        string strLine;
		if(nFileSize > MAX_FILESIZE_1MB*2)
		{
			while(input)
			{
				input.getline(cLine, MAX_LMSG_LENGTH);
				if(0 != strcmp(cLine, ""))
				{
					nRowSum++;
					if(NULL != pStrLineVector)
					{
						strLine = cLine;
						pStrLineVector->push_back(strLine);
					}
				}
			}
		}
		else
		{
			while(input)
			{
				input.getline(cLine, MAX_LMSG_LENGTH);
				if(0 != strcmp(cLine, ""))
				{
					if(NULL != pStrLineVector)
					{
						strLine = cLine;
						pStrLineVector->push_back(strLine);
					}
					++nRowSum;
				}
			}
		}
    }
    input.close();

    return nRowSum;
}

//仅仅获取文件总行数
long GetFileRowSum(char* strPrePath, char* strFileName)
{
    long nRowSum = 0;
    char strFilePathName[MAX_PATH_LENGTH];
    sprintf_s(strFilePathName, "%s\\%s", strPrePath, strFileName);
    if(!FileExist(strFilePathName))
    {
        return nRowSum;
    }

    char strPath[MAX_PATH_LENGTH];
    sprintf_s(strPath, "%s%s%s", strPrePath, "\\", strFileName);
    
    ifstream input(strPath);
    if(!input)
    {
        nRowSum = 0;
    }
    else
    {
        char cLine[MAX_LMSG_LENGTH];
        string strLine;
        while (input)
        {
            input.getline(cLine, MAX_LMSG_LENGTH);
            nRowSum++;
        }
    }
    input.close();

    return nRowSum;
}

//仅仅获取文件总行数
long GetFileRowSum(char* strPathFileName)
{
    long nRowSum = 0;
    if(!FileExist(strPathFileName))
    {
        return nRowSum;
    }
    
    ifstream input(strPathFileName);
    if(!input)
    {
        nRowSum = 0;
    }
    else
    {
        char cLine[MAX_LMSG_LENGTH];
        string strLine;
        while (input)
        {
            input.getline(cLine, MAX_LMSG_LENGTH);
            nRowSum++;
        }
    }
    input.close();

    return nRowSum;
}


//线性内插计算函数
double Interpolation(STRU_TWO_ELEMENTGROUP *pStruEleGroup, long nEleArraySize, double fFirstValue, double &fSecondValue)
{
    if(nEleArraySize < 2)
    {
		return INVALID_VALUE;
    }
	//开始内插计算
	for(int i = 0; i < nEleArraySize; i++)
	{
		if((0 == i) && (nEleArraySize > 1) && (-1 == CompareBothDouble(fFirstValue, pStruEleGroup[i].fFirstValue)))
		{
			//进行前插操作
			fSecondValue = (((pStruEleGroup[i + 1].fFirstValue * pStruEleGroup[i].fSecondValue) - (fFirstValue * pStruEleGroup[i].fFirstValue) - (pStruEleGroup[i].fFirstValue * pStruEleGroup[i + 1].fSecondValue)  + (fFirstValue * pStruEleGroup[i + 1].fSecondValue)) 
				/ (pStruEleGroup[i + 1].fFirstValue - pStruEleGroup[i].fFirstValue));
			break;
		}
		//如果找到相等的源值，则目标值直接获取
		if(0 == CompareBothDouble(fFirstValue, pStruEleGroup[i].fFirstValue))
		{
			fSecondValue = pStruEleGroup[i].fSecondValue;
			break;
		}
		//内插
		if((i < nEleArraySize - 1) 
			&& (1 == CompareBothDouble(fFirstValue, pStruEleGroup[i].fFirstValue)) 
			&& (-1 == CompareBothDouble(fFirstValue, pStruEleGroup[i + 1].fFirstValue)))
		{
			fSecondValue = (((fFirstValue - pStruEleGroup[i].fFirstValue) * (pStruEleGroup[i + 1].fSecondValue - pStruEleGroup[i].fSecondValue)) 
				/ (pStruEleGroup[i + 1].fFirstValue - pStruEleGroup[i].fFirstValue) + pStruEleGroup[i].fSecondValue);
			break;
		}
	}
	//后插
	if((nEleArraySize > 1) && (1 == CompareBothDouble(fFirstValue, pStruEleGroup[nEleArraySize - 1].fFirstValue)))
	{
		fSecondValue = (((fFirstValue - pStruEleGroup[nEleArraySize - 2].fFirstValue) * (pStruEleGroup[nEleArraySize - 1].fSecondValue - pStruEleGroup[nEleArraySize - 2].fSecondValue)) 
			/ (pStruEleGroup[nEleArraySize - 1].fFirstValue - pStruEleGroup[nEleArraySize - 2].fFirstValue) + (pStruEleGroup[nEleArraySize - 2].fSecondValue));
	}
    
	return fSecondValue;
}

//二次抛物线计算函数
double Parabola2nd(STRU_TWO_ELEMENTGROUP *pStruEleGroup, long nEleArraySize, double fFirstValue, double &fSecondValue)
{
    double fFirstValue1;   //第一个参数输入值
    double fSecondValue1;  //第一个目标值
    double fFirstValue2;   //第二个参数输入值
	double fSecondValue2;  //第二个目标值
	
    fFirstValue1 = pStruEleGroup[0].fFirstValue;
    fSecondValue1 = pStruEleGroup[0].fSecondValue;
	
    for(int i = 1; i < nEleArraySize; i++)
    {
		fFirstValue2 = pStruEleGroup[i].fFirstValue;
		fSecondValue2 = pStruEleGroup[i].fSecondValue;
		
		if(fabs(fSecondValue1 - 0) < 0.001)
		{
            fFirstValue1 = fFirstValue2;
			fSecondValue1 = fSecondValue2;	
            continue;
		}
		
		if(fabs(fSecondValue2 - 0) < 0.001)
		{
			continue;
		}
		
		if((fFirstValue > fFirstValue1) && (fFirstValue < fFirstValue2))
		{
			fSecondValue = fSecondValue1 + (1.1 - 0.1*((fFirstValue-fFirstValue1)/(fFirstValue2-fFirstValue1))) * ((fFirstValue-fFirstValue1)/(fFirstValue2-fFirstValue1)) * (fSecondValue2-fSecondValue1);
			break;
		}
		
		fFirstValue1 = fFirstValue2;
        fSecondValue1 = fSecondValue2;
    }
	
	return fSecondValue;
}

//三次抛物线计算函数
double Parabola3rd(STRU_TWO_ELEMENTGROUP *pStruEleGroup, long nEleArraySize, double fFirstValue, double &fSecondValue)
{
    double fFirstValue1;   //第一个参数输入值
    double fSecondValue1;  //第一个目标值
    double fFirstValue2;   //第二个参数输入值
	double fSecondValue2;  //第二个目标值

    fFirstValue1 = pStruEleGroup[0].fFirstValue;
    fSecondValue1 = pStruEleGroup[0].fSecondValue;

    for(int i = 1; i < nEleArraySize; i++)
    {
		fFirstValue2 = pStruEleGroup[i].fFirstValue;
		fSecondValue2 = pStruEleGroup[i].fSecondValue;

		if(fabs(fSecondValue1) < 0.001)
		{
            fFirstValue1 = fFirstValue2;
			fSecondValue1 = fSecondValue2;	
            continue;
		}
		
		if(fabs(fSecondValue2) < 0.001)
		{
			continue;
		}
		
		if((fFirstValue > fFirstValue1) && (fFirstValue < fFirstValue2))
		{
            fSecondValue = fSecondValue1 + (3 - 2*((fFirstValue-fFirstValue1)/(fFirstValue2-fFirstValue1))) * pow(((fFirstValue-fFirstValue1)/(fFirstValue2-fFirstValue1)), 2) * (fSecondValue2-fSecondValue1);
		    break;
		}
		
		fFirstValue1 = fFirstValue2;
		fSecondValue1 = fSecondValue2;
    }

	return fSecondValue;
}

void SperatorString(string strLine, string& strText, string& strRemark, char cDelimiter)
{
    strText.empty();
    strRemark.empty();
    
    int nSperator = strLine.find(cDelimiter);
    if(nSperator == -1)
        strText = strLine;
    else
    {
        strText = strLine.substr(0, nSperator);
        strRemark = strLine.substr(nSperator + 1);
    }
}

//将字符串根据给定分隔符分割成多个子字符串
int ParseSubStrByDelimiter(string strLine, string* strArray, const char cDelimiter)
{
    int nSeparator = -1;
    int nNextSeparator = -1;
    int nStrLen = strLine.length();
    int nStrArraySize = 0;
    int i = 0;
    
    //strLine replace '\t' to ' '
	int nIndex = strLine.find('\t', 0);
	while(nIndex >= 0)
	{
		strLine.replace(nIndex, 1, " ");
		nIndex = strLine.find('\t', 0);
	}

	for(i = 0; i < nStrLen;)
	{
		if(i == 0)
		{
			if(strLine.at(i) == cDelimiter)
			{
				strArray[nStrArraySize++] = "";
				nSeparator = i;
			}
			else
			{
				nSeparator = strLine.find(cDelimiter, nSeparator + 1);
				if(nSeparator < 0)
					break;

				strArray[nStrArraySize++] = strLine.substr(0, nSeparator);
			}

			i = nSeparator;
		}
		else
		{
			nSeparator = i;
			nNextSeparator = strLine.find(cDelimiter, nSeparator + 1);
			if(nNextSeparator < 0)
			{
				strArray[nStrArraySize++] = strLine.substr(nSeparator + 1, nStrLen - nSeparator - 1);
				break;
			}

			if(nNextSeparator == nSeparator + 1)
				strArray[nStrArraySize++] = "";
			else
				strArray[nStrArraySize++] = strLine.substr(nSeparator + 1, nNextSeparator - nSeparator - 1);

			i = nNextSeparator;
		}
	}

    return nStrArraySize;
}
int ParseSubStrByDelimiter(CString strLine, CStringArray& strArray, const char cDelimiter)
{
	int nSeparator = -1;
	int nNextSeparator = -1;
	int nStrLen = strLine.GetLength();

	//strLine replace '\t' to ' '
	strLine.Replace('\t', ' ');

	for(int i = 0; i < nStrLen;)
	{
		if(i == 0)
		{
			if(strLine[i] == cDelimiter)
			{
				strArray.Add(L"");
				nSeparator = i;
			}
			else
			{
				nSeparator = strLine.Find(cDelimiter, nSeparator + 1);
				if(nSeparator < 0)
					break;

				strArray.Add(strLine.Mid(0, nSeparator));
			}

			i = nSeparator;
		}
		else
		{
			nSeparator = i;
			nNextSeparator = strLine.Find(cDelimiter, nSeparator + 1);
			if(nNextSeparator < 0)
			{
				strArray.Add(strLine.Mid(nSeparator + 1, nStrLen - nSeparator - 1));
				break;
			}

			if(nNextSeparator == nSeparator + 1)
				strArray.Add(L"");
			else
				strArray.Add(strLine.Mid(nSeparator + 1, nNextSeparator - nSeparator - 1));

			i = nNextSeparator;
		}
	}

	return strArray.GetCount();
}

//去除字符串两侧空格字符
string TrimSpace(string strSrc)
{
    if(strSrc.empty())
    {
        return strSrc;
    }
    char cTemp;
    string::iterator iter;
    //清除左侧空格
    for(iter = strSrc.begin(); iter != strSrc.end();iter++)
    {
        cTemp = (char)(*iter);
        if(cTemp == ' ')
        {
            strSrc.erase(iter);
            iter--;
        }
        else
        {
            break;
        }
    }

    //清除右侧空格
    reverse(strSrc.begin(), strSrc.end());
    for(iter = strSrc.begin(); iter != strSrc.end();iter++)
    {
        cTemp = (char)(*iter);
        if(cTemp == ' ')
        {
            strSrc.erase(iter);
            iter--;
        }
        else
        {
            break;
        }
    }
    reverse(strSrc.begin(), strSrc.end());
     
    return strSrc;
}

//去除字符串中所有特殊字符
string TrimSpecialStr(string strSrc, string strSpecial)
{
    if(strSrc.find(strSpecial) < 0)
    {
        return strSrc;
    }
    string strTemp;
    for(string::iterator iter = strSrc.begin(); iter != strSrc.end();iter++)
    {
        strTemp = (char)(*iter);
        if(0 == strTemp.compare(strSpecial))
        {
            strSrc.erase(iter);
            iter--;
        }
    }
    
    return strSrc;
}

//去除字符串左侧指定字符串
string TrimLeftStr(string strSrc, string strSpecial)
{
    if(strSrc.find(strSpecial) < 0)
    {
        return strSrc;
    }
    string strTemp;
    for(string::iterator iter = strSrc.begin(); iter != strSrc.end();iter++)
    {
        strTemp = (char)(*iter);
        if(!strTemp.empty() && 0 == strTemp.compare(strSpecial))
        {
            strSrc.erase(iter);
            iter--;
        }
        else
        {
            break;
        }
    }
    return strSrc;
}

//去除字符串右侧指定字符串
string TrimRightStr(string strSrc, string strSpecial)
{
    reverse(strSrc.begin(), strSrc.end());
    if(strSrc.find(strSpecial) < 0)
    {
        return strSrc;
    }
    string strTemp;
    for(string::iterator iter = strSrc.begin(); iter != strSrc.end(); iter++)
    {
        strTemp = (char)(*iter);
        if(!strTemp.empty() && 0 == strTemp.compare(strSpecial))
        {
            strSrc.erase(iter);
            iter--;
        }
        else
        {
            break;
        }
    }
    reverse(strSrc.begin(), strSrc.end());
    return strSrc;
}

//比较两个浮点数是否相等并且指出比较精度(如0.001)，如果相等则返回0；如果fFirst小于fSecond，则返回-1；如果fFirst大于fSecond，则返回1
short CompareBothDouble(double fFirst, double fSecond, double fDigitAfterPoint)
{
    //浮点精度为fDigitAfterPoint
    if(fabs(fFirst-fSecond) < fDigitAfterPoint)
    {
        return 0;
    }
    
    if(fFirst > fSecond)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

//比较两个浮点数是否相等并且指出比较精度(如0.0000001)，如果相等则返回true，否则返回false
bool Equal(double fFirst, double fSecond, double fDigitAfterPoint)
{
    //浮点精度为fDigitAfterPoint
    if(fabs(fFirst - fSecond) < fDigitAfterPoint)
    {
        return true;
    }
    return false;
}

//将双精度型数据格式换成字符串形式，小数点后数字格式默认为3位
char* FormatDblToStr(double fSrcData, char *strDest, short nDigitAfterPoint)
{
    switch(nDigitAfterPoint)
    {
    case 0:
        sprintf_s(strDest, sizeof(strDest),"%.0f", fSrcData);
		break;
    case 1:
        sprintf_s(strDest, sizeof(strDest),"%.1f", fSrcData);
		break;
    case 2:
        sprintf_s(strDest, sizeof(strDest),"%.2f", fSrcData);
		break;
    case 3:
        sprintf_s(strDest, sizeof(strDest),"%.3f", fSrcData);
		break;
    case 4:
        sprintf_s(strDest, sizeof(strDest),"%.4f", fSrcData);
		break;
    case 5:
        sprintf_s(strDest, sizeof(strDest),"%.5f", fSrcData);
		break;
    case 6:
        sprintf_s(strDest, sizeof(strDest),"%.6f", fSrcData);
		break;
    case 7:
        sprintf_s(strDest, sizeof(strDest),"%.7f", fSrcData);
		break;
    case 8:
        sprintf_s(strDest, sizeof(strDest),"%.8f", fSrcData);
		break;
    case 9:
        sprintf_s(strDest, sizeof(strDest),"%.9f", fSrcData);
		break;
    default:
        sprintf_s(strDest, sizeof(strDest),"%.3f", fSrcData);
		break;
    }
    return strDest;
}

//将整型数据格式换成字符串形式
char* FormatIntToStr(int nSrcData, char *strDest)
{
    sprintf_s(strDest, sizeof(strDest), "%d", nSrcData);
    return strDest;
}

//判断字符串是否全部都是ASCII码字符
bool StrIsAlpha(const char* str)
{
    char* pStr = const_cast<char*>(str);
    while ((NULL != pStr) && ('\0' != *pStr))
    {
        if(!isalpha(*(pStr++)))
        {
            return false;
        }
    }
    
    return true;
}

//将大写字符串转换为小写字符串
char* Str2Lower(char* str)
{
    int i = 0;
    int nStrLen = strlen(str);
    if(nStrLen < 1)
    {
        return str;
    }
    char* pStr = new char[nStrLen+1];
    memset(pStr, 0, nStrLen+1);
    strcpy_s(pStr, sizeof(pStr),str);
    char* pConvStr = pStr;
    while ((NULL != pStr) && ('\0' != *pStr) && i <= nStrLen)
    {
        if(isupper(*pStr))
        {
            *pStr = tolower(*(pStr));
        }
        pStr++;
        i++;
    }
    
    strcpy_s(str, sizeof(str),pConvStr);

    pStr = pConvStr;
    delete []pStr;

    return str;
}

//将大写字符串转换为小写字符串
string Str2Lower(string &str)
{
    int i = 0;
    int nStrLen = str.length();
    if(nStrLen < 1)
    {
        return str;
    }
    char* pStr = new char[nStrLen+1];
    memset(pStr, 0, nStrLen);
    strcpy_s(pStr, sizeof(pStr),str.c_str());
    char* pConvStr = pStr;
    while ((NULL != pStr) && ('\0' != *pStr) && i < nStrLen)
    {
        if(isupper(*pStr))
        {
            *pStr = tolower(*(pStr));
        }
        pStr++;
        i++;
    }
    
    str = pConvStr;

    pStr = pConvStr;
    delete []pStr;

    return str;
}

//将小写字符串转换为大写字符串
char* Str2Upper(char* str)
{
    int i = 0;
    int nStrLen = strlen(str);
    if(nStrLen < 1)
    {
        return str;
    }
    char* pStr = new char[nStrLen+1];
    memset(pStr, 0, nStrLen+1);
    strcpy_s(pStr, sizeof(pStr), str);
    char* pConvStr = pStr;
    while ((NULL != pStr) && ('\0' != *pStr) && i <= nStrLen)
    {
        if(islower(*pStr))
        {
            *pStr = toupper(*(pStr));
        }
        pStr++;
        i++;
    }
    
    strcpy_s(str, sizeof(str), pConvStr);

    pStr = pConvStr;
    delete []pStr;

    return str;
}

//将小写字符串转换为大写字符串
string Str2Upper(string &str)
{
    int i = 0;
    int nStrLen = str.length();
    if(nStrLen < 1)
    {
        return str;
    }
    char* pStr = new char[nStrLen+1];
    memset(pStr, 0, nStrLen);
    strcpy_s(pStr, sizeof(pStr), str.c_str());
    char* pConvStr = pStr;
    while ((NULL != pStr) && ('\0' != *pStr) && i <= nStrLen)
    {
        if(islower(*pStr))
        {
            *pStr = toupper(*(pStr));
        }
        pStr++;
        i++;
    }
    
    str = pConvStr;

    pStr = pConvStr;
    delete []pStr;

    return str;
}

//已使用的物理内存字节数
unsigned long UsedMemory()
{
	MEMORYSTATUS memstatus;
	memset(&memstatus,0,sizeof(MEMORYSTATUS));
	memstatus.dwLength =sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memstatus);
	DWORD ulMem = memstatus.dwTotalPhys-memstatus.dwAvailPhys;
    return ulMem;
}

//未使用的物理内存字节数
unsigned long FreeMemory()
{
	MEMORYSTATUS memstatus;
	memset(&memstatus,0,sizeof(MEMORYSTATUS));
	memstatus.dwLength =sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memstatus);
	DWORD ulMem = memstatus.dwAvailPhys ;
    return ulMem;
}

//从字符串中查找字符的位置
bool GetValueFromString(string strLine, string& strName, string& strValue, const char cIdentify)
{
    if(!strLine.empty())
    {
        string::size_type pos = strLine.find(cIdentify);
        if(pos != string::npos)
        {
            strName = strLine.substr(0, pos);
            strValue = strLine.substr(pos + 1);
            return true;
        }
    }
    return false;
}

//将字符串根据给定分隔符分割成多个子字符串
int SpliteSubStrByDelimiter(string strLine, string* strSubArray, const int nArraySize, const char* lpszDelimiter)
{
    int nSeparator = -1;
    while((nSeparator = strLine.find('\t', nSeparator + 1)) >= 0)
    {
        strLine.replace(nSeparator, 1, " ");
    }
    strLine = TrimSpace(strLine);
    
    int nDelimiterLen = strlen(lpszDelimiter);
    int nCount = 0;
    int nNext = -1;
    while((nNext = strLine.find(lpszDelimiter, 0)) >= 0)
    {
        strSubArray[nCount] = strLine.substr(0, nNext);
        strLine = strLine.substr(nNext + nDelimiterLen);
        strLine = TrimSpace(strLine);
        nCount ++;
        if(nCount == nArraySize)
            return nCount;
    }
    if(strLine.length() > 0)
    {
        strSubArray[nCount] = strLine;
        nCount ++;
    }
    
    return nCount;
}

//时间格式必须是 2013-01-30 18:18:18 的格式
short CompareTime(string strTime1, string strTime2)
{
    if(strTime1.compare(strTime2) == 0)
    {
        return 0;  //两个时间相等
    }
    //第一个时间
    string strTime1PartArray[3];
    SpliteSubStrByDelimiter(strTime1, strTime1PartArray, 3, " ");
    string strYMD1[4];
    SpliteSubStrByDelimiter(strTime1PartArray[0], strYMD1, 4, "-");
    int nYear1 = atoi(strYMD1[0].c_str());
    int nMonth1 = atoi(strYMD1[1].c_str());
    int nMonthDay1 = atoi(strYMD1[2].c_str());

    string strHMS1[4];
    SpliteSubStrByDelimiter(strTime1PartArray[1], strHMS1, 4, ":");
    int nHour1 = atoi(strHMS1[0].c_str());
    int nMinute1 = atoi(strHMS1[1].c_str());
    int nSecond1 = atoi(strHMS1[2].c_str());

    //第二个时间
    string strTime2PartArray[3];
    SpliteSubStrByDelimiter(strTime2, strTime2PartArray, 3, " ");
    string strYMD2[4];
    SpliteSubStrByDelimiter(strTime2PartArray[0], strYMD2, 4, "-");
    int nYear2 = atoi(strYMD2[0].c_str());
    int nMonth2 = atoi(strYMD2[1].c_str());
    int nMonthDay2 = atoi(strYMD2[2].c_str());
    
    string strHMS2[4];
    SpliteSubStrByDelimiter(strTime2PartArray[1], strHMS2, 4, ":");
    int nHour2 = atoi(strHMS2[0].c_str());
    int nMinute2 = atoi(strHMS2[1].c_str());
    int nSecond2 = atoi(strHMS2[2].c_str());

    //比较两个时间
    if(nYear1 > nYear2)
    {
        return 1;
    }
    else
    {
        if(nYear1 < nYear2)
        {
            return -1;
        }
        else  //年相等
        {
            if(nMonth1 > nMonth2)
            {
                return 1;
            }
            else
            {
                if(nMonth1 < nMonth2)
                {
                    return -1;
                }
                else //月相等
                {
                    if(nMonthDay1 > nMonthDay2)
                    {
                        return 1;
                    }
                    else
                    {
                        if(nMonthDay1 < nMonthDay2)
                        {
                            return -1;
                        }
                        else  //日相等
                        {
                            if(nHour1 > nHour2)
                            {
                                return 1;
                            }
                            else
                            {
                                if(nHour1 < nHour2)
                                {
                                    return -1;
                                }
                                else  //时相等
                                {
                                    if(nMinute1 > nMinute2)
                                    {
                                        return 1;
                                    }
                                    else
                                    {
                                        if(nMinute1 < nMinute2)
                                        {
                                            return -1;
                                        }
                                        else //分相等
                                        {
                                            if(nSecond1 > nSecond2)
                                            {
                                                return 1;
                                            }
                                            else
                                            {
                                                if(nSecond1 < nSecond2)
                                                {
                                                    return -1;
                                                }
                                                else
                                                {
                                                    return 0;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//时间格式必须是 2013-01-30 18:18:18 的格式
short CalcDays(string strTime1, string strTime2)
{
    if(strTime1.compare(strTime2) == 0)
    {
        return 0;  //两个时间相等，相差0天
    }
    //第一个时间
    string strTime1PartArray[3];
    SpliteSubStrByDelimiter(strTime1, strTime1PartArray, 3, " ");
    string strYMD1[4];
    SpliteSubStrByDelimiter(strTime1PartArray[0], strYMD1, 4, "-");
    int nYear1 = atoi(strYMD1[0].c_str());
    int nMonth1 = atoi(strYMD1[1].c_str());
    int nMonthDay1 = atoi(strYMD1[2].c_str());

    //第二个时间
    string strTime2PartArray[3];
    SpliteSubStrByDelimiter(strTime2, strTime2PartArray, 3, " ");
    string strYMD2[4];
    SpliteSubStrByDelimiter(strTime2PartArray[0], strYMD2, 4, "-");
    int nYear2 = atoi(strYMD2[0].c_str());
    int nMonth2 = atoi(strYMD2[1].c_str());
    int nMonthDay2 = atoi(strYMD2[2].c_str());

    int nDays = (nYear2*12*31 + nMonth2*31 + nMonthDay2) - (nYear1*12*31 + nMonth1*31 + nMonthDay1);
    return nDays;
}

//乘方函数
double ex(double fValue, int nPower)
{
	double fMultValue = 1;

	if(nPower == 0)
		fMultValue = 1;

	if(nPower == 1)
		fMultValue = fValue;

	if(nPower >= 2)    
	{
		for(int i=0; i<nPower; i++)
			fMultValue=fMultValue*fValue;
	}

	return fMultValue;
}

//图标资源存为文件
struct TCursorOrIcon 
{ 
	WORD Reserved; 
	WORD wType; 
	WORD Count; 
}; 
struct TIconRec 
{ 
	BYTE Width; 
	BYTE Height; 
	WORD Colors; 
	WORD Reserved1; 
	WORD Reserved2; 
	long DIBSize; 
	long DIBOffset; 
}; 
static void InitBmpInfoHeader(HBITMAP Bitmap,BITMAPINFOHEADER& BI, int nBit) 
{ 
	int Bytes; 
	DIBSECTION DS; 

	DS.dsBmih.biSize = 0; 
	Bytes = GetObject(Bitmap, sizeof(DS), &DS); 
	if (Bytes >= sizeof(DS.dsBm)+sizeof(DS.dsBmih) && DS.dsBmih.biSize >= sizeof(DS.dsBmih)) 
		memcpy(&BI, &DS.dsBmih, sizeof(BITMAPINFOHEADER)); 
	else
	{ 
		memset(&BI, 0, sizeof(BI)); 
		BI.biSize = sizeof(BI); 
		BI.biWidth = DS.dsBm.bmWidth; 
		BI.biHeight = DS.dsBm.bmHeight; 
		BI.biBitCount = DS.dsBm.bmPlanes * DS.dsBm.bmBitsPixel; 
	} 
	if(nBit!=0) BI.biBitCount = nBit; 
	if(BI.biBitCount <= 8) 
		BI.biClrUsed = 1 << BI.biBitCount; 
	BI.biPlanes = 1; 
	if(BI.biClrImportant > BI.biClrUsed) 
		BI.biClrImportant = BI.biClrUsed; 
	if(BI.biSizeImage == 0) 
		BI.biSizeImage = ((BI.biWidth*BI.biBitCount+31) / 32) * 4 * BI.biHeight; 
} 
static void GetDIBSizes(HBITMAP Bitmap,DWORD& InfoSize, DWORD& ImageSize,int nBit) 
{ 
	BITMAPINFOHEADER BI; 

	InitBmpInfoHeader(Bitmap, BI, nBit); 
	InfoSize = sizeof(BITMAPINFOHEADER); 
	if (BI.biBitCount > 8)
	{ 
		if(BI.biCompression&BI_BITFIELDS) 
			InfoSize += 12; 
	} 
	else 
		InfoSize += sizeof(RGBQUAD) * (BI.biClrUsed!=0 ? BI.biClrUsed :(1 << BI.biBitCount)); 
	
	ImageSize = BI.biSizeImage; 
} 
static void GetDIB(HBITMAP Bitmap,BITMAPINFO* BmpInfo, void* Bits, int nBit) 
{ 
	HDC DC; 
	DC = CreateCompatibleDC(NULL); 
	InitBmpInfoHeader(Bitmap, BmpInfo-> bmiHeader, nBit); 
	GetDIBits(DC, Bitmap, 0, BmpInfo-> bmiHeader.biHeight, Bits,BmpInfo, DIB_RGB_COLORS); 
	DeleteDC(DC); 
} 
bool SaveIcon(HICON hIcon, char* szFilePath, int nBit) 
{ 
	BOOL ret; 
	UINT nColor = 0; 
	long Length = 0; 
	void *MonoBits; 
	void *ColorBits; 
	DWORD dwWrite; 
	HANDLE hFile; 
	TIconRec List; 
	ICONINFO IconInfo; 
	TCursorOrIcon CI; 
	DWORD MonoInfoSize; 
	DWORD ColorInfoSize; 
	DWORD MonoBitsSize; 
	DWORD ColorBitsSize; 
	BITMAPINFO *MonoInfo; 
	BITMAPINFO *ColorInfo; 

	switch(nBit)
	{ 
	case 0: 
	case 1: 
	case 4: 
	case 8: 
	case 16: 
	case 24: 
	case 32: 
		break; 
	default:
		return FALSE; 
	} 
	if (hIcon == NULL || !szFilePath) 
		return FALSE;

	USES_CONVERSION;
	hFile = CreateFile(A2T(szFilePath),GENERIC_WRITE, FILE_SHARE_READ,0, CREATE_ALWAYS, 0, 0); 
	if (hFile==INVALID_HANDLE_VALUE)
		return false; 
	memset(&CI, 0, sizeof(CI)); 
	memset(&List, 0, sizeof(List)); 
	GetIconInfo(hIcon, &IconInfo); 

	GetDIBSizes(IconInfo.hbmMask,MonoInfoSize, MonoBitsSize, 1); 
	GetDIBSizes(IconInfo.hbmColor,ColorInfoSize, ColorBitsSize,nBit); 
	MonoInfo = (BITMAPINFO*)malloc(MonoInfoSize); 
	ColorInfo = (BITMAPINFO*)malloc(ColorInfoSize); 
	MonoBits = malloc(MonoBitsSize); 
	ColorBits = malloc(ColorBitsSize); 
	GetDIB(IconInfo.hbmMask, MonoInfo,MonoBits, 1); 
	GetDIB(IconInfo.hbmColor, ColorInfo,ColorBits, nBit); 
	CI.wType = (WORD)0x10001;
	CI.Count = 1; 
	ret &= WriteFile(hFile, &CI, sizeof(CI),&dwWrite, NULL); 
	List.Width = ColorInfo-> bmiHeader.biWidth; 
	List.Height = ColorInfo-> bmiHeader.biHeight; 
	List.Colors = ColorInfo-> bmiHeader.biPlanes * ColorInfo-> bmiHeader.biBitCount; 
	List.DIBSize = ColorInfoSize + ColorBitsSize + MonoBitsSize; 
	List.DIBOffset = sizeof(CI) + sizeof(List); 
	ret &= WriteFile(hFile, &List, sizeof(List), &dwWrite, NULL); 
	ColorInfo-> bmiHeader.biHeight *= 2; 
	ret &= WriteFile(hFile, ColorInfo,ColorInfoSize, &dwWrite, NULL); 
	ret &= WriteFile(hFile, ColorBits,ColorBitsSize, &dwWrite, NULL); 
	ret &= WriteFile(hFile, MonoBits,MonoBitsSize, &dwWrite, NULL); 
	free(ColorInfo); 
	free(MonoInfo); 
	free(ColorBits); 
	free(MonoBits); 
	DeleteObject(IconInfo.hbmColor); 
	DeleteObject(IconInfo.hbmMask); 

	CloseHandle(hFile); return ret;
} 
bool SaveIcon(HINSTANCE hInstance, UINT nID, char* szFilePath, int nBit) 
{ 
	HICON hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(nID));

	BOOL ret; 
	UINT nColor = 0; 
	long Length = 0; 
	void *MonoBits; 
	void *ColorBits; 
	DWORD dwWrite; 
	HANDLE hFile; 
	TIconRec List; 
	ICONINFO IconInfo; 
	TCursorOrIcon CI; 
	DWORD MonoInfoSize; 
	DWORD ColorInfoSize; 
	DWORD MonoBitsSize; 
	DWORD ColorBitsSize; 
	BITMAPINFO *MonoInfo; 
	BITMAPINFO *ColorInfo; 

	switch(nBit)
	{ 
	case 0: 
	case 1: 
	case 4: 
	case 8: 
	case 16: 
	case 24: 
	case 32: 
		break; 
	default:
		return FALSE; 
	} 
	if (hIcon == NULL || !szFilePath) 
		return FALSE;

	USES_CONVERSION;
	hFile = CreateFile(A2T(szFilePath),GENERIC_WRITE, FILE_SHARE_READ,0, CREATE_ALWAYS, 0, 0); 
	if (hFile==INVALID_HANDLE_VALUE)
		return false; 
	memset(&CI, 0, sizeof(CI)); 
	memset(&List, 0, sizeof(List)); 
	GetIconInfo(hIcon, &IconInfo); 

	GetDIBSizes(IconInfo.hbmMask,MonoInfoSize, MonoBitsSize, 1); 
	GetDIBSizes(IconInfo.hbmColor,ColorInfoSize, ColorBitsSize,nBit); 
	MonoInfo = (BITMAPINFO*)malloc(MonoInfoSize); 
	ColorInfo = (BITMAPINFO*)malloc(ColorInfoSize); 
	MonoBits = malloc(MonoBitsSize); 
	ColorBits = malloc(ColorBitsSize); 
	GetDIB(IconInfo.hbmMask, MonoInfo,MonoBits, 1); 
	GetDIB(IconInfo.hbmColor, ColorInfo,ColorBits, nBit); 
	CI.wType = (WORD)0x10001;
	CI.Count = 1; 
	ret &= WriteFile(hFile, &CI, sizeof(CI),&dwWrite, NULL); 
	List.Width = ColorInfo-> bmiHeader.biWidth; 
	List.Height = ColorInfo-> bmiHeader.biHeight; 
	List.Colors = ColorInfo-> bmiHeader.biPlanes * ColorInfo-> bmiHeader.biBitCount; 
	List.DIBSize = ColorInfoSize + ColorBitsSize + MonoBitsSize; 
	List.DIBOffset = sizeof(CI) + sizeof(List); 
	ret &= WriteFile(hFile, &List, sizeof(List), &dwWrite, NULL); 
	ColorInfo-> bmiHeader.biHeight *= 2; 
	ret &= WriteFile(hFile, ColorInfo,ColorInfoSize, &dwWrite, NULL); 
	ret &= WriteFile(hFile, ColorBits,ColorBitsSize, &dwWrite, NULL); 
	ret &= WriteFile(hFile, MonoBits,MonoBitsSize, &dwWrite, NULL); 
	free(ColorInfo); 
	free(MonoInfo); 
	free(ColorBits); 
	free(MonoBits); 
	DeleteObject(IconInfo.hbmColor); 
	DeleteObject(IconInfo.hbmMask); 

	CloseHandle(hFile); return ret;
} 
void SaveIcon(char* szFilePath, HICON hIcon)
{
	if(hIcon==NULL || szFilePath==NULL)
		return;
	//warning: this code snippet is not bullet proof.
	//do error check by yourself [masterz]
	PICTDESC picdesc;
	picdesc.cbSizeofstruct = sizeof(PICTDESC);
	picdesc.picType = PICTYPE_ICON ;            
	picdesc.icon.hicon = hIcon;
	IPicture* pPicture=NULL;
	OleCreatePictureIndirect(&picdesc, IID_IPicture, TRUE,(VOID**)&pPicture);
	LPSTREAM pStream;
	CreateStreamOnHGlobal(NULL,TRUE,&pStream);
	LONG size;
	HRESULT hr=pPicture->SaveAsFile(pStream,TRUE,&size);
	char pathbuf[1024];
	strcpy_s(pathbuf,szFilePath);
	CFile iconfile;
	USES_CONVERSION;
	iconfile.Open(A2T(pathbuf), CFile::modeCreate|CFile::modeWrite);
	LARGE_INTEGER li;
	li.HighPart =0;
	li.LowPart =0;
	ULARGE_INTEGER ulnewpos;
	pStream->Seek( li,STREAM_SEEK_SET,&ulnewpos);
	ULONG uReadCount = 1;
	while(uReadCount>0)
	{
		pStream->Read(pathbuf,sizeof(pathbuf),&uReadCount);
		if(uReadCount>0)
			iconfile.Write(pathbuf,uReadCount);
	}
	pStream->Release();
	iconfile.Close();
}
void SaveIcon(char* szFilePath, HINSTANCE hInstance, UINT nID)
{
	HICON hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(nID));

	if(hIcon==NULL || szFilePath==NULL)
		return;
	//warning: this code snippet is not bullet proof.
	//do error check by yourself [masterz]
	PICTDESC picdesc;
	picdesc.cbSizeofstruct = sizeof(PICTDESC);
	picdesc.picType = PICTYPE_ICON ;            
	picdesc.icon.hicon = hIcon;
	IPicture* pPicture=NULL;
	OleCreatePictureIndirect(&picdesc, IID_IPicture, TRUE,(VOID**)&pPicture);
	LPSTREAM pStream;
	CreateStreamOnHGlobal(NULL,TRUE,&pStream);
	LONG size;
	HRESULT hr=pPicture->SaveAsFile(pStream,TRUE,&size);
	char pathbuf[1024];
	strcpy_s(pathbuf,szFilePath);
	CFile iconfile;
	USES_CONVERSION;
	iconfile.Open(A2T(pathbuf), CFile::modeCreate|CFile::modeWrite);
	LARGE_INTEGER li;
	li.HighPart =0;
	li.LowPart =0;
	ULARGE_INTEGER ulnewpos;
	pStream->Seek( li,STREAM_SEEK_SET,&ulnewpos);
	ULONG uReadCount = 1;
	while(uReadCount>0)
	{
		pStream->Read(pathbuf,sizeof(pathbuf),&uReadCount);
		if(uReadCount>0)
			iconfile.Write(pathbuf,uReadCount);
	}
	pStream->Release();
	iconfile.Close();
}
HICON BitmapToIcon(CBitmap& bitmap)
{
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);

	HBITMAP hbmMask = ::CreateCompatibleBitmap(::GetDC(NULL), 
		bmp.bmWidth, bmp.bmHeight);

	ICONINFO ii = {0};
	ii.fIcon = TRUE;
	ii.hbmColor = bitmap;
	ii.hbmMask = hbmMask;

	HICON hIcon = ::CreateIconIndirect(&ii);//一旦不再需要，注意用DestroyIcon函数释放占用的内存及资源
	::DeleteObject(hbmMask);

	return hIcon;
}
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
HICON BitmapToIcon(HBITMAP hBitmap)
{
	Gdiplus::Bitmap* pTmpBitmap=Gdiplus::Bitmap::FromHBITMAP(hBitmap,NULL);
	HICON hIcon=NULL;
	pTmpBitmap->GetHICON(&hIcon);
	delete pTmpBitmap;
	return hIcon;
}
HBITMAP IconToBitmap(HICON  hIcon)
{ 
	HBITMAP   hBmp; 
	BITMAP   bmp; 
	CDC   bmpDC; 
	CDC   iconDC; 
	ICONINFO         csII; 
	int bRetValue   =   ::GetIconInfo(hIcon,   &csII); 
	if   (bRetValue   ==   FALSE)   return   NULL; 
	bmpDC.Attach(::GetDC(NULL)); 
	iconDC.CreateCompatibleDC(&bmpDC); 
	if   (::GetObject(csII.hbmColor,   sizeof(BITMAP),   &bmp)) 
	{ 
		DWORD       dwWidth   =   csII.xHotspot*2; 
		DWORD       dwHeight   =   csII.yHotspot*2; 
		hBmp=   ::CreateBitmap(dwWidth,   dwHeight,   bmp.bmPlanes,   
			bmp.bmBitsPixel,   NULL);
		iconDC.SelectObject(csII.hbmColor); 
		bmpDC.SelectObject(hBmp); 
		bmpDC.BitBlt(0,0,dwWidth,dwHeight,&iconDC,0,0,SRCCOPY); 
		return   hBmp; 
	}
	return NULL;
}

HANDLE DwgToBmp(CString file)
{
	if(FileExist(file))
	{
		CFile fDwg(file,CFile::modeRead);//文件流
		CString bmp=L"preview.tmp";
		CFile fBmp(bmp,CFile::modeCreate|CFile::modeWrite);	

		int   PosSentinel=0;         //文件描述块的位置
		char  *BMPInfo;
		int   TypePreview=0;         //缩略图格式
		int   PosBMP=0;              //缩略图位置
		int   LenBMP=0;              //缩略图大小
		short biBitCount=0;          //缩略图比特深度
		BITMAPFILEHEADER biH;        //BMP文件头，DWG文件中不包含位图文件头，要自行加上

		fDwg.Seek(13,CFile::begin);   //从第13字节开始读取
		fDwg.Read(&PosSentinel,4);    //第13到17字节指示缩略图描述块的位置,读取4个字节的有符号整数的代码

		fDwg.Seek(PosSentinel+30,CFile::begin); //第31字节为缩略图格式信息，2为bmp格式，3为wmf
		fDwg.Read(&TypePreview,1);              //读取一个字节的数据

		switch(TypePreview)
		{
		case 1: 
		case 3: 		
			AfxMessageBox(L"不是bmp图象");
			break;
		case 2: 
			fDwg.Seek(PosSentinel+31,CFile::begin); //DWG文件保存的位图所在位置  
			fDwg.Read(&PosBMP,4);                   //读取4个字节的有符号整数的代码      
			fDwg.Seek(PosSentinel+35,CFile::begin); //位图的大小     
			fDwg.Read(&LenBMP,4);                   //读取4个字节的有符号整数的代码
			fDwg.Seek(PosBMP+14,CFile::begin);      //移动指针到位图块,读取比特深度
			fDwg.Read(&biBitCount,2);               //读取2个字节的有符号整数的代码
			fDwg.Seek(PosBMP, CFile::begin);        //从位图块开始处读取全部位图内容备用,

			//读取LenBMP长度的字节数据到数字BMPInfo中 
			BMPInfo=new char[LenBMP]; 
			fDwg.Read(BMPInfo,LenBMP);			
			//BMPInfo = br.ReadBytes(LenBMP)  '不包含文件头的位图信息
			fDwg.Close();

			//建立位图文件头
			biH.bfType=0x4D42; 
			if(biBitCount<9)
				biH.bfSize=DWORD(54+4*pow(2.0,biBitCount)+LenBMP); 
			else 
				biH.bfSize=54+LenBMP;

			biH.bfReserved1=0;             //保留字节
			biH.bfReserved2=0;             //保留字节 
			biH.bfOffBits=14+0x28+1024;    //图像数据偏移

			fBmp.Write(&biH,sizeof(BITMAPFILEHEADER));	 //写入位图文件头
			fBmp.Write(BMPInfo,LenBMP);                  //写入位图
			delete[] BMPInfo;
			fBmp.Close();

			//加载位图
			HANDLE hbitmap=LoadImage(NULL,bmp,IMAGE_BITMAP,200,300,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			return hbitmap;
		}
	}

	return NULL;
}

bool ExecuteRes(HMODULE hModule, UINT uId, LPCTSTR sType, LPCTSTR sFile)
{
	if(!FileExist(sFile))/* DelFile(sFile);*/
	{
		//资源文件writer.exe长度为204800Byte,在资源文件中定义为"CUSTOM"资源,编号为1111 
		HRSRC     hRes;    //resource handle 
		HGLOBAL   hGpt;    //resource pointer 
		LPVOID    lpBuff;  //resource buffer pointer 
		DWORD     dwSize;  //resource size 
		HANDLE    hFile;   //file to write 
		LPDWORD   dwByte;  //byte size had been write 

		hRes    = FindResource (hModule,MAKEINTRESOURCE(uId),sType); 
		hGpt    = LoadResource (hModule,hRes); 
		dwSize  = SizeofResource (hModule, hRes);
		lpBuff  = LockResource (hGpt);
		hFile   = CreateFile (sFile,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL); 
		dwByte  = &dwSize;
		WriteFile(hFile,lpBuff,dwSize,dwByte,NULL); 
		CloseHandle(hFile); 
	}

	return ShellExecute(NULL, L"open", sFile, NULL, NULL, SW_SHOWNORMAL);
}

CString CpuSerial()
{
	//获取CPU序列号
	unsigned long s1=0,s2=0;     
	char sel;   
	sel='1';   
	CString CpuID,CPUID1,CPUID2;  
	
#ifdef X64
	__asm
	{   
		mov eax,01h   
		xor edx,edx   
		cpuid   
		mov s1,edx   
		mov s2,eax   
	}   
#endif // X64

	CPUID1.Format(L"%08X%08X",s1,s2);

#ifdef X64
	__asm
 	{   
 		mov eax,03h   
 		xor ecx,ecx   
 		xor edx,edx   
 		cpuid   
 		mov s1,edx   
 		mov s2,ecx   
 	}
#endif // X64

	CPUID2.Format(L"%08X%08X",s1,s2);   

	CpuID=CPUID1+CPUID2;
	return CpuID;
}

CString DiskSerial()
{
	DWORD ser;
	wchar_t namebuf[128];
	wchar_t filebuf[128];
	//获取C盘的序列号
	::GetVolumeInformation(L"c:\\",namebuf,128,&ser,0,0,filebuf,128);
	CString DiskID;
	DiskID.Format(L"%08X",ser);

	return DiskID;
}

#include <snmp.h>
#include <conio.h>
#pragma comment(lib, "Snmpapi.lib")
#include "nb30.h"
#pragma comment (lib,"netapi32.lib")
typedef BOOL(WINAPI * pSnmpExtensionInit) (
											IN DWORD dwTimeZeroReference,
											OUT HANDLE * hPollForTrapEvent,
											OUT AsnObjectIdentifier * supportedView);

typedef BOOL(WINAPI * pSnmpExtensionTrap) (
											OUT AsnObjectIdentifier * enterprise,
											OUT AsnInteger * genericTrap,
											OUT AsnInteger * specificTrap,
											OUT AsnTimeticks * timeStamp,
											OUT RFC1157VarBindList * variableBindings);

typedef BOOL(WINAPI * pSnmpExtensionQuery) (
											IN BYTE requestType,
											IN OUT RFC1157VarBindList * variableBindings,
											OUT AsnInteger * errorStatus,
											OUT AsnInteger * errorIndex);

typedef BOOL(WINAPI * pSnmpExtensionInitEx) (OUT AsnObjectIdentifier * supportedView);

struct ADAPTER_INFO
{	
	ADAPTER_STATUS nStatus;
	NAME_BUFFER    nBuffer;
};
CString MacAddress()
{
    pSnmpExtensionInit Init = NULL;
    pSnmpExtensionInitEx InitEx = NULL;
    pSnmpExtensionQuery Query = NULL;
    pSnmpExtensionTrap Trap = NULL;
    HANDLE PollForTrapEvent;
    AsnObjectIdentifier SupportedView;
    UINT OID_ifEntryType[] = {1, 3, 6, 1, 2, 1, 2, 2, 1, 3};
    UINT OID_ifEntryNum[] = {1, 3, 6, 1, 2, 1, 2, 1};
    UINT OID_ipMACEntAddr[] = {1, 3, 6, 1, 2, 1, 2, 2, 1, 6};                          //, 1 ,6 };
    AsnObjectIdentifier MIB_ifMACEntAddr = { sizeof(OID_ipMACEntAddr) / sizeof(UINT), OID_ipMACEntAddr };
    AsnObjectIdentifier MIB_ifEntryType = {sizeof(OID_ifEntryType) / sizeof(UINT), OID_ifEntryType};
    AsnObjectIdentifier MIB_ifEntryNum = {sizeof(OID_ifEntryNum) / sizeof(UINT), OID_ifEntryNum};
    RFC1157VarBindList varBindList;
    RFC1157VarBind varBind[2];
    AsnInteger errorStatus;
    AsnInteger errorIndex;
    AsnObjectIdentifier MIB_NULL = {0, 0};
    int ret;
    int dtmp;
    int i = 0, j = 0;
    BOOL found = FALSE;
    char TempEthernet[13];

    /* Load the SNMP dll and get the addresses of the functions
       necessary */
    HINSTANCE hInst = LoadLibrary(L"inetmib1.dll");
    if (hInst < (HINSTANCE) HINSTANCE_ERROR)
	{
        hInst = NULL;
        return "";
    }
    Init = (pSnmpExtensionInit) GetProcAddress(hInst, "SnmpExtensionInit");
    InitEx = (pSnmpExtensionInitEx) GetProcAddress(hInst,"SnmpExtensionInitEx");
    Query = (pSnmpExtensionQuery) GetProcAddress(hInst,"SnmpExtensionQuery");
    Trap = (pSnmpExtensionTrap) GetProcAddress(hInst, "SnmpExtensionTrap");
    Init(GetTickCount(), &PollForTrapEvent, &SupportedView);

    /* Initialize the variable list to be retrieved by m_Query */
    varBindList.list = varBind;
    varBind[0].name = MIB_NULL;
    varBind[1].name = MIB_NULL;

    /* Copy in the OID to find the number of entries in the
       Inteface table */
    varBindList.len = 1;        /* Only retrieving one item */
    SNMP_oidcpy(&varBind[0].name, &MIB_ifEntryNum);
    ret = Query(ASN_RFC1157_GETNEXTREQUEST, &varBindList, &errorStatus, &errorIndex);
    printf("# of adapters in this system : %i\n", varBind[0].value.asnValue.number);
	varBindList.len = 2;

    /* Copy in the OID of ifType, the type of interface */
    SNMP_oidcpy(&varBind[0].name, &MIB_ifEntryType);

    /* Copy in the OID of ifPhysAddress, the address */
    SNMP_oidcpy(&varBind[1].name, &MIB_ifMACEntAddr);

    do {

        /* Submit the query.  Responses will be loaded into varBindList.
           We can expect this call to succeed a # of times corresponding
           to the # of adapters reported to be in the system */
        ret = Query(ASN_RFC1157_GETNEXTREQUEST, &varBindList, &errorStatus, &errorIndex);
		if (!ret)
			ret = 1;
        else
            /* Confirm that the proper type has been returned */
            ret = SNMP_oidncmp(&varBind[0].name, &MIB_ifEntryType, MIB_ifEntryType.idLength);
		if (!ret)
		{
            j++;
            dtmp = varBind[0].value.asnValue.number;
            printf("Interface #%i type : %i\n", j, dtmp);

            /* Type 6 describes ethernet interfaces */
            if (dtmp == 6)
			{
                /* Confirm that we have an address here */
                ret = SNMP_oidncmp(&varBind[1].name, &MIB_ifMACEntAddr, MIB_ifMACEntAddr.idLength);
                if ((!ret) && (varBind[1].value.asnValue.address.stream != NULL))
				{
                    if ((varBind[1].value.asnValue.address.stream[0] == 0x44)
                        && (varBind[1].value.asnValue.address.stream[1] == 0x45)
                        && (varBind[1].value.asnValue.address.stream[2] == 0x53)
                        && (varBind[1].value.asnValue.address.stream[3] == 0x54)
                        && (varBind[1].value.asnValue.address.stream[4] == 0x00))
					{
                        /* Ignore all dial-up networking adapters */
                        printf("Interface #%i is a DUN adapter\n", j);
                        continue;
                    }

                    if ((varBind[1].value.asnValue.address.stream[0] == 0x00)
                        && (varBind[1].value.asnValue.address.stream[1] == 0x00)
                        && (varBind[1].value.asnValue.address.stream[2] == 0x00)
                        && (varBind[1].value.asnValue.address.stream[3] == 0x00)
                        && (varBind[1].value.asnValue.address.stream[4] == 0x00)
                        && (varBind[1].value.asnValue.address.stream[5] == 0x00))
					{
                        /* Ignore NULL addresses returned by other network
                           interfaces */
                        printf("Interface #%i is a NULL address\n", j);
                        continue;
                    }

                    sprintf(TempEthernet, "%02x%02x%02x%02x%02x%02x",
                            varBind[1].value.asnValue.address.stream[0],
                            varBind[1].value.asnValue.address.stream[1],
                            varBind[1].value.asnValue.address.stream[2],
                            varBind[1].value.asnValue.address.stream[3],
                            varBind[1].value.asnValue.address.stream[4],
                            varBind[1].value.asnValue.address.stream[5]);
                    printf("MAC Address of interface #%i: %s\n", j, TempEthernet);
				}
            }
        }
    } while (!ret);         /* Stop only on an error.  An error will occur
                               when we go exhaust the list of interfaces to
                               be examined */
    getch();

    /* Free the bindings */
    SNMP_FreeVarBind(&varBind[0]);
    SNMP_FreeVarBind(&varBind[1]);

	USES_CONVERSION;
	return A2T(TempEthernet);

	NCB nInfo;
	memset(&nInfo,0,sizeof(NCB));
	nInfo.ncb_command  = NCBRESET;
	nInfo.ncb_lana_num = 0;
	Netbios(&nInfo);
	ADAPTER_INFO AdaINfo;
	//初始化NetBIOS
	memset(&nInfo,0,sizeof(NCB));
	nInfo.ncb_command  = NCBASTAT;
	nInfo.ncb_lana_num = 0;
	nInfo.ncb_buffer   = (unsigned char*)&AdaINfo;
	nInfo.ncb_length   = sizeof(ADAPTER_INFO);
	strncpy((char*)nInfo.ncb_callname,"*",NCBNAMSZ);
	Netbios(&nInfo);

	CString MacAddr;
	MacAddr.Format(L"%02X%02X%02X%02X%02X%02X",
		AdaINfo.nStatus.adapter_address[0],
		AdaINfo.nStatus.adapter_address[1],
		AdaINfo.nStatus.adapter_address[2],
		AdaINfo.nStatus.adapter_address[3],
		AdaINfo.nStatus.adapter_address[4],
		AdaINfo.nStatus.adapter_address[5]);

	return MacAddr;
}

char* SnKey(char* SnCode)
{
	//定义一个密钥数组
	char* code[16] = {
		"ah","tm","ib","nw",
		"rt","vx","zc","gf",
		"pn","xq","fc","oj",
		"wm","eq","np","qw"};

	int len = strlen(SnCode);
	strcpy_s(SnCode, len+1, Str2Upper(SnCode));

	char* SN = new char[2*len+1];
	int num = 0;
	for(int i=0;i<10;i++)
	{
		char p=SnCode[i];
		if(p>='a'&&p<='f')
			num = p - 'a' + 10;
		else
			num = p - '0';

		sprintf_s(SN, 2*len+1,"%s%s",SN,code[i]);
	}

	return Str2Lower(SN);
}

CString SnKey(CString SnCode)
{
	//定义一个密钥数组
	CString code[16] = {
		L"ah",L"tm",L"ib",L"nw",
		L"rt",L"vx",L"zc",L"gf",
		L"pn",L"xq",L"fc",L"oj",
		L"wm",L"eq",L"np",L"qw"};

	SnCode.MakeLower();

	CString SN;
	int num = 0;
	for(int i=0; i<10; i++)
	{
		char p = SnCode.GetAt(i);
		if(p >= 'a' && p <= 'f')
			num = p - 'a' + 10;
		else
			num = p - '0';

		SN += code[num];
	}

	return SN.MakeUpper();
}