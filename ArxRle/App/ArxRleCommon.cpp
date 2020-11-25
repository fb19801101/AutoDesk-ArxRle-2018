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
system���� �ǿ��Ե���һЩDOS����,����
	system("cls");//����,������DOS��ʹ��cls����
�����г����õ�DOS����,��������system��������:
ASSOC ��ʾ���޸��ļ���չ��������
	AT �ƻ��ڼ���������е�����ͳ���
	ATTRIB ��ʾ������ļ����ԡ�
	BREAK ���û������չʽ CTRL+C ��顣
	CACLS ��ʾ���޸��ļ��ķ��ʿ����б�(ACLs)��
	CALL ����һ����������������һ����
	CD ��ʾ��ǰĿ¼�����ƻ�����ġ�
	CHCP ��ʾ�����û����ҳ����
	CHDIR ��ʾ��ǰĿ¼�����ƻ�����ġ�
	CHKDSK �����̲���ʾ״̬���档
	CHKNTFS ��ʾ���޸�����ʱ����̼�顣
	CLS �����Ļ��
	CMD ����һ�� Windows ������ͳ��򴰿ڡ�
	COLOR ����Ĭ�Ͽ���̨ǰ���ͱ�����ɫ��
	COMP �Ƚ������������ļ������ݡ�
	COMPACT ��ʾ����� NTFS �������ļ���ѹ����
	CONVERT �� FAT ��ת���� NTFS��������ת����ǰ��������
	COPY ������һ���ļ����Ƶ���һ��λ�á�
	DATE ��ʾ���������ڡ�
	DEL ɾ������һ���ļ���
	DIR ��ʾһ��Ŀ¼�е��ļ�����Ŀ¼��
	DISKCOMP �Ƚ��������̵����ݡ�
	DISKCOPY ��һ�����̵����ݸ��Ƶ���һ�����̡�
	DOSKEY �༭�����С����� Windows ��������ꡣ
	ECHO ��ʾ��Ϣ����������Դ򿪻���ϡ�
	ENDLOCAL �������ļ��л������ĵı��ػ���
	ERASE ɾ������һ���ļ���
	EXIT �˳� CMD.EXE ����(������ͳ���)��
	FC �Ƚ������������ļ�������ʾ��ͬ����
	FIND ���ļ������������ַ�����
	FINDSTR ���ļ��������ַ�����
	FOR Ϊһ���ļ��е�ÿ���ļ�����һ��ָ��������
	FORMAT ��ʽ�����̣��Ա�� Windows ʹ�á�
	FTYPE ��ʾ���޸������ļ���չ���������ļ����͡�
	GOTO �� Windows ������ͳ���ָ�������������ĳ���������С�
	GRAFTABL ���� Windows ����ͼ��ģʽ��ʾ��չ�ַ�����
	HELP �ṩ Windows ����İ�����Ϣ��
	IF ִ������������е������Դ���
	LABEL ���������Ļ�ɾ�����̵ľ�ꡣ
	MD ����Ŀ¼��
	MKDIR ����Ŀ¼��
	MODE ����ϵͳ�豸��
	MORE һ����ʾһ�������Ļ��
	MOVE ���ļ���һ��Ŀ¼�Ƶ���һ��Ŀ¼��
	PATH ��ʾ�����ÿ�ִ���ļ�������·����
	PAUSE ��ͣ���ļ��Ĵ�����ʾ��Ϣ��
	POPD ��ԭ PUSHD ����ĵ�ǰĿ¼����һ��ֵ��
	PRINT ��ӡ�ı��ļ���
	PROMPT ���� Windows ������ʾ����
	PUSHD ���浱ǰĿ¼��Ȼ�������и��ġ�
	RD ɾ��Ŀ¼��
	RECOVER ��������Ĵ��ָ̻��ɶ���Ϣ��
	REM ��¼���ļ��� CONFIG.SYS �е�ע�͡�
	REN �������ļ���
	RENAME �������ļ���
	REPLACE �滻�ļ���
	RMDIR ɾ��Ŀ¼��
	SET ��ʾ�����û�ɾ�� Windows ����������
	SETLOCAL ��ʼ���ļ��л������ĵı��ػ���
	SHIFT �������ļ��п��滻������λ�á�
	SORT ��������з��ࡣ
	START ������һ������������ָ���ĳ�������
	SUBST ��·����һ���������Ź�����
	TIME ��ʾ������ϵͳʱ�䡣
	TITLE ���� CMD.EXE �Ự�Ĵ��ڱ��⡣
	TREE ��ͼ��ģʽ��ʾ��������·����Ŀ¼�ṹ��
	TYPE ��ʾ�ı��ļ������ݡ�
	VER ��ʾ Windows �汾��
	VERIFY ���� Windows �Ƿ���֤�ļ��Ƿ�����ȷд����̡�
	VOL ��ʾ���̾������кš�
	XCOPY �����ļ���Ŀ¼����
	system��ִ��shell ���
	��غ��� fork��execve��waitpid��popen
	��ͷ�ļ� #include<stdlib.h>
	���庯�� int system(const char * string);
����˵�� system()�����fork()�����ӽ��̣����ӽ���������/bin/sh-c string��ִ�в���string�ַ�������������������ִ������漴����ԭ���õĽ��̡��ڵ���system()�ڼ�SIGCHLD �źŻᱻ��ʱ���ã�SIGINT��SIGQUIT �ź���ᱻ���ԡ�
	����ֵ ���system()�ڵ���/bin/shʱʧ���򷵻�127������ʧ��ԭ�򷵻�-1��������stringΪ��ָ��(NULL)���򷵻ط���ֵ�����system()���óɹ������᷵��ִ��shell�����ķ���ֵ�����Ǵ˷���ֵҲ�п���Ϊsystem()����/bin/shʧ�������ص�127�����������ټ��errno ��ȷ��ִ�гɹ���
	����˵�� �ڱ�д����SUID/SGIDȨ�޵ĳ���ʱ����ʹ��system()��system()��̳л���������ͨ�������������ܻ����ϵͳ��ȫ�����⡣
	����
#include<stdlib.h>
	main()
{
	system(��ls -al /etc/passwd /etc/shadow��);
}
*/

// ���ֽ�ת���ֽ�
bool charTowchar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
	DWORD dwMinSize = MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, NULL, 0);

	if(dwSize < dwMinSize) return FALSE;

	MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);  
	return TRUE;
}

//���ֽ�ת���ֽ�
bool wcharTochar(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize) 
{   
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,NULL,0,NULL,FALSE);
	if(dwSize < dwMinSize) return FALSE;

	WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,lpszStr,dwSize,NULL,FALSE);
	return TRUE;
} 

// ��ȡOffice��װ·��
char* GetOfficePath()
{
	TCHAR szProductType[MAX_BUFSIZE];
	DWORD dwBufLen = MAX_BUFSIZE;
	LONG lRet;
	HKEY hKey;

	// �����Ǵ�ע���, ֻ�д򿪺�������������� 
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,   // Ҫ�򿪵ĸ��� 
		TEXT("SOFTWARE\\Microsoft\\Office\\11.0\\Excel\\InstallRoot"), // Ҫ�򿪵����Ӽ� 
		0,                    // ���һ��ҪΪ0 
		KEY_QUERY_VALUE,      // ָ���򿪷�ʽ,��Ϊ�� 
		&hKey);               // �������ؾ�� 

	if(lRet == ERROR_SUCCESS) // �ж��Ƿ�򿪳ɹ� 
	{
		// ���濪ʼ��ѯ 
		lRet = RegQueryValueEx(hKey,                  // ��ע���ʱ���صľ�� 
			TEXT("Path"),       //Ҫ��ѯ������,qq��װĿ¼��¼��������� 
			NULL,                  // һ��ΪNULL����0 
			NULL, 
			(LPBYTE)szProductType, // ����Ҫ�Ķ�����������
			&dwBufLen);

		if(lRet == ERROR_SUCCESS) // �ж��Ƿ��ѯ�ɹ�
			RegCloseKey(hKey);
	}

	USES_CONVERSION;
	return T2A(szProductType);
}

//��ʾ���̵����л�������    
DWORD EnumEnvironmentVariables()
{     
	// ��ȡ��������
	LPTCH pEv = GetEnvironmentStrings();//��ȡ���л��������ַ���
	char* szEnvs;
	// ��ʾ     
	for(szEnvs = (char*) pEv; *szEnvs;)      
	{      
		printf("%sn",szEnvs);
		while (*szEnvs++);
	}
	// �ͷ�     
	FreeEnvironmentStrings(pEv);//�ͷ���GetEnvironmentStrings���ص��ڴ��

	//��ȡ��������
	//char* szPath = NULL;
	//size_t requiredSize = 0;
	//getenv_s(&requiredSize, NULL, 0, "Path");
	//szPath = (char*)malloc(requiredSize * sizeof(char));
	//getenv_s(&requiredSize, szPath, requiredSize, "Path");

	return 0;
}

//�ı价������
//@ LPSTR szName    ��Ҫ�ı�Ļ���    
//@ LPSTR szNewValue    �µı���ֵ    
//@ DWORD dwFlag    ���ӡ����û������㣬��س�����env.h�ڶ���    
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

	// �����־Ϊ���������Ȼ�ȡ��Ȼ��szNewValue���ӵ�ĩβ
	if(dwFlag == VARIABLES_APPEND)
	{
		dwNewValSize = strlen(szNewValue)+1;   // �±���ֵ�Ĵ�С     
		// �����ڴ�     
		szVal = HeapAlloc(GetProcessHeap(),0,MAX_BUFSIZE+dwNewValSize);     
		// ��ȡֵ     
		dwReturn = GetEnvironmentVariable(strName,(LPTSTR)szVal,MAX_BUFSIZE);//��ȡָ���Ļ�������

		if(dwReturn == 0)   // ����
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
		else if(MAX_BUFSIZE < dwReturn)  // ������̫С     
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
		lstrcat((LPWSTR)szVal,L";");     // �ָ���
		lstrcat((LPWSTR)szVal,strNewValue);  // ����
		//����
		if(!SetEnvironmentVariable(strName,(LPWSTR)szVal))//����ָ���Ļ�������
		{     
			printf("Set Value Error %d",GetLastError());
		}

		// �ͷ��ڴ�
		HeapFree(GetProcessHeap(),0,szVal);     
		return TRUE;
	}     
	// ��������ã���ֱ������     
	else if(dwFlag == VARIABLES_RESET)
	{     
		if(!SetEnvironmentVariable(strName,strNewValue))     
		{     
			printf("Set value error %d",GetLastError());     
		}     
	}     
	// ���㣬����szNewValue     
	else if(dwFlag == VARIABLES_NULL)     
	{     
		if(!SetEnvironmentVariable(strName,NULL))     
		{
			printf("Set value error %d",GetLastError());     
		}
	}      

	//��ӻ�������
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

//1��K#+###.###  2��+###.###  3��K#  4��+#
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
	str.Format(L"%d��%d'%.2f''",fAng < 0 ? -a:a,b,c);
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

//��дע�����(Utility Stuff)
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

// �����ַ���
char* StrLink(int nArgCount, char* source, ...)
{
	setlocale(LC_ALL,"");

	va_list arg_ptr;           //����б�ָ��
	va_start(arg_ptr, source); //arg_ptrָ���һ�����
	char szStr1[MAX_BUFSIZE];
	char szStr2[MAX_BUFSIZE];
	strcpy_s(szStr2,source);

	for(; --nArgCount > 0;)
	{
		char* key = va_arg(arg_ptr, char*);

		sprintf_s(szStr1,"%s%s",szStr2,key);
		strcpy_s(szStr2,szStr1);
	}

	va_end(arg_ptr); //��λ���ָ��

	char* pStr = szStr2;
	return pStr;
}

// �ַ�ת��Ϊ����
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

// ����תΪ��������
char* Num2Char(int nNum, bool bCashNum)
{
	char szStr[3];
	switch(nNum)
	{
	case 0:
		if(bCashNum)
			strcpy_s(szStr,"��");
		else
			strcpy_s(szStr,"��");
		break;
	case 1:
		if(bCashNum)
			strcpy_s(szStr,"Ҽ");
		else
			strcpy_s(szStr,"һ");
		break;
	case 2:
		if(bCashNum)
			strcpy_s(szStr,"��");
		else
			strcpy_s(szStr,"��");
		break;
	case 3:
		if(bCashNum)
			strcpy_s(szStr,"��");
		else
			strcpy_s(szStr,"��");
		break;
	case 4:
		if(bCashNum)
			strcpy_s(szStr,"��");
		else
			strcpy_s(szStr,"��");
		break;
	case 5:
		if(bCashNum)
			strcpy_s(szStr,"��");
		else
			strcpy_s(szStr,"��");
		break;
	case 6:
		if(bCashNum)
			strcpy_s(szStr,"½");
		else
			strcpy_s(szStr,"��");
		break;
	case 7:
		if(bCashNum)
			strcpy_s(szStr,"��");
		else
			strcpy_s(szStr,"��");
		break;
	case 8:
		if(bCashNum)
			strcpy_s(szStr,"��");
		else
			strcpy_s(szStr,"��");
		break;
	case 9:
		if(bCashNum)
			strcpy_s(szStr,"��");
		else
			strcpy_s(szStr,"��");
		break;
	}

	char* pStr = szStr;
	return pStr;
}

//�޸�ֱ����Դ���Ͻ��� 
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

//��������.
double Round(double fA, int nB)
{
	double exp = 1.0;
	for(int i=0; i<nB; i++)
		exp *= 10.0;
	int nC = INT(fA*exp+0.5);
	return nC/exp;
}
//�����������ݾ���ȡ���ĺ���
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

 // ����ת��������
const char hzSymbol[2][3]={"��","��"};
const char hzUnit[15][3]={"��","��","Ԫ","ʰ","��","Ǫ","��","ʰ","��","Ǫ","��","ʰ","��","Ǫ","��"};  
const char hzNum[10][3]={"��","Ҽ","��","��","��","��","½","��","��","��"};  
const char regex1[3][5] = {"��Ǫ", "���", "��ʰ"};
const char regex2[3][5] = {"����", "����", "��Ԫ"};
const char regex3[3][3] = {"��", "��", "Ԫ"};
const char regex4[2][5] = {"���", "���"};
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

	// ��һ��ת���� "��Ǫ", ���","��ʰ"���ַ����滻��һ��"��"   
	for(int i = 0; i < 3; i ++)
	{
		StrReplace(szStr, regex1[i], "��");
	}
	// �ڶ���ת������ "����","����","��Ԫ"�����   
	// "��","��","Ԫ"��Щ��λ��Щ����ǲ���ʡ�ģ���Ҫ��������   
	for(int i = 0; i < 3; i ++)
	{   
		// ����һ��ת�������п����кܶ�������һ��   
		// Ҫ�Ѻܶ���ظ�������һ����   
		StrReplace(szStr, "������", "��");
		StrReplace(szStr, "����", "��");
		StrReplace(szStr, regex2[i], regex3[i]);
	}
	// ������ת����"���","���"�ַ���ʡ��
	for(int i = 0; i < 2; i ++)
	{   
		StrReplace(szStr, regex4[i], "");
	}
	// ��"��"��"��"֮��ȫ����"��"��ʱ�򣬺���"����"��λ��ֻ����һ��"��"   
	StrReplace(szStr, "����", "��");

	char* pStr = szStr;
	return pStr;
}

//longת��ΪCTime
CTime long2Ctime(double ftime)
{
	//��ȡ��ǰʱ�䲢���浽curTime
	//CTime CurTime = CTime::GetCurrentTime();
	//long nBeginYear = CurTime.GetYear();//��ȡ��ǰ���
	//long nBeginMonth = CurTime.GetMonth();//��ȡ��ǰ�·�
	//long nBeginDay = CurTime.GetDay();//��ȡ��ǰ����
	//long nBeginHour = CurTime.GetHour();//��ȡ��ǰСʱʱ��
	//long nBeginMin = CurTime.GetMinute();//��ȡ��ǰ����ʱ��
	//long nBeginSec = CurTime.GetSecond();//��ȡ��ǰ��ʱ��
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

//CTimeת��Ϊlong
double Ctime2long(CTime time)
{
	CTimeSpan timeSpan = time-CTime(1980,1,1,0,0,0);
	double ftime = EXCELDATETIME+timeSpan.GetDays()+(timeSpan.GetHours()+timeSpan.GetMinutes()/60.0+timeSpan.GetSeconds()/3600.0)/24.0;

	return ftime;
}

//��ǰ����Ŀ¼·��
char g_strCurrentWorkPath[MAX_PATH_LENGTH] = "";
//�����ļ���ʽģ��
extern const char g_strCRDFileTpl[20] = "%s%.3d%.2d.CRD\0";
//�Զ����׺�������ļ���ʽģ��
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

//�ж��ļ��Ƿ����
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

//�ж�Ŀ¼�Ƿ����
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

//����ɾ��Ŀ¼�Ƿ����
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

//�ļ�Ŀ¼
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

//��ȡ��ǰģ��·��
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

//ɾ���ļ�
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

//д�����ƻ��ı��ļ�
//@ const char* szFilePath �ļ����ƺ�·��
//@ bool bBinaryFile �Ƿ�д�������ļ�
void WriteFile(const char* szFilePath, bool bBinaryFile)
{
	//�ļ��Ĵ�ģʽ
	//�ļ�����ʱ���������ʾָ����ģʽ���ļ����ཫʹ��Ĭ��ֵ��
	//��<fstream> �ж��������´�ģʽ���ļ�����:
	//ios::app // �Ӻ������
	//ios::ate // �򿪲��ҵ��ļ�β
	//ios::binary // ������ģʽI/O�����ı�ģʽ���)
	//ios::in // ֻ����
	//ios::out // д��
	//ios::trunc // ���ļ���Ϊ 0 ����
	//����ʹ��λ������ OR �����Щ��־������
	//ofstream logFile("log.dat", ios::binary | ios::app);

	if(bBinaryFile)
	{
		//д�������ļ�Ӧ��ʹ��ofstream�࣬�ļ��Ĵ�ģʽһ��Ҫ�� binary���������Ĳ��� binary, �ļ�����ASCII��ʽ�򿪡�
		std::ofstream fout(szFilePath, std::ios::binary);
		int nNum = 20;
		std::string str("Hello, world");

		fout.write((char*)&nNum, sizeof(int));
		fout.write(str.c_str(), sizeof(char) * (str.size()));
		fout.close();
	}
	else
	{
		//д�ı��ļ���Ƚϼ�
		std::ofstream fout(szFilePath);
		int nNum = 20;
		std::string str("Hello, world");

		fout << nNum << "," << str << std::endl;

		fout.close();
	}
}

//�������ƻ��ı��ļ�
//@ const char* szFilePath �ļ����ƺ�·��
//@ bool bBinaryFile �Ƿ�д�������ļ�
void ReadFile(const char* szFilePath, bool bBinaryFile)
{
	//�ļ��Ĵ�ģʽ
	//�ļ�����ʱ���������ʾָ����ģʽ���ļ����ཫʹ��Ĭ��ֵ��
	//��<fstream> �ж��������´�ģʽ���ļ�����:
	//ios::app // �Ӻ������
	//ios::ate // �򿪲��ҵ��ļ�β
	//ios::binary // ������ģʽI/O�����ı�ģʽ���)
	//ios::in // ֻ����
	//ios::out // д��
	//ios::trunc // ���ļ���Ϊ 0 ����
	//����ʹ��λ������ OR �����Щ��־������
	//ofstream logFile("log.dat", ios::binary | ios::app);

	if(bBinaryFile)
	{
		//��ȡ�������ļ�����ʹ��ifstream �������У��ļ��Ĵ�ģʽһ��Ҫ�� binary���������Ĳ��� binary, �ļ�����ASCII��ʽ��
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
		//��ȡ�ı��ļ���Ƚϼ�
		std::ifstream fin("b.dat");
		int nNum;
		char szBuf[MAX_STRSIZE] = {0};

		fin >> nNum >> szBuf;
		std::cout << "int = " << nNum << std::endl;
		std::cout << "str = " << szBuf << std::endl;

		fin.close();
	}
}

//���ƶ����ƻ��ı��ļ�
//@ const char* szDestFile Ŀ���ļ����ƺ�·��
//@ const char* szOrigFile Դ�ļ����ƺ�·��
//@ bool bBinaryFile �Ƿ�д�������ļ�
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

//��ȡȥ���ļ�·������ʵ�ļ���
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

//��ȡ�޺�׺���ļ�����
string GetFileNameNoSuffix(string strFileName)
{
    string strFileNameNoSuffix;
    int nPointPos = strFileName.find(".");
    strFileNameNoSuffix = strFileName.substr(0, nPointPos);
    
	return strFileNameNoSuffix;
}

//C++����ʵ�֣���ȡ�ļ�������������ÿ�����ݴ洢���ַ���Vector��
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
		//ʹ��STL��ȡ�ļ����ȴ�С
		int nFilePos = input.tellg(); // ��¼�µ�ǰλ�� 
		input.seekg(0, ios_base::end); // �ƶ����ļ�β 
		int nFileSize = input.tellg(); // ȡ�õ�ǰλ�õ�ָ�볤�� ���ļ����� 
        input.seekg(nFilePos); // �ƶ���ԭ����λ��

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

//C++����ʵ�֣�ȥ�����У���ȡ�ļ�(�Ѿ������ļ�·��)������������ÿ�����ݴ洢���ַ���Vector��
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
		//ʹ��STL��ȡ�ļ����ȴ�С
		int nFilePos = input.tellg();  // ��¼�µ�ǰλ�� 
		input.seekg(0, ios_base::end); // �ƶ����ļ�β 
		int nFileSize = input.tellg(); // ȡ�õ�ǰλ�õ�ָ�볤�� ���ļ����ȣ���λ���ֽ��� 
        input.seekg(nFilePos);         // �ƶ���ԭ����λ��

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

//������ȡ�ļ�������
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

//������ȡ�ļ�������
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


//�����ڲ���㺯��
double Interpolation(STRU_TWO_ELEMENTGROUP *pStruEleGroup, long nEleArraySize, double fFirstValue, double &fSecondValue)
{
    if(nEleArraySize < 2)
    {
		return INVALID_VALUE;
    }
	//��ʼ�ڲ����
	for(int i = 0; i < nEleArraySize; i++)
	{
		if((0 == i) && (nEleArraySize > 1) && (-1 == CompareBothDouble(fFirstValue, pStruEleGroup[i].fFirstValue)))
		{
			//����ǰ�����
			fSecondValue = (((pStruEleGroup[i + 1].fFirstValue * pStruEleGroup[i].fSecondValue) - (fFirstValue * pStruEleGroup[i].fFirstValue) - (pStruEleGroup[i].fFirstValue * pStruEleGroup[i + 1].fSecondValue)  + (fFirstValue * pStruEleGroup[i + 1].fSecondValue)) 
				/ (pStruEleGroup[i + 1].fFirstValue - pStruEleGroup[i].fFirstValue));
			break;
		}
		//����ҵ���ȵ�Դֵ����Ŀ��ֱֵ�ӻ�ȡ
		if(0 == CompareBothDouble(fFirstValue, pStruEleGroup[i].fFirstValue))
		{
			fSecondValue = pStruEleGroup[i].fSecondValue;
			break;
		}
		//�ڲ�
		if((i < nEleArraySize - 1) 
			&& (1 == CompareBothDouble(fFirstValue, pStruEleGroup[i].fFirstValue)) 
			&& (-1 == CompareBothDouble(fFirstValue, pStruEleGroup[i + 1].fFirstValue)))
		{
			fSecondValue = (((fFirstValue - pStruEleGroup[i].fFirstValue) * (pStruEleGroup[i + 1].fSecondValue - pStruEleGroup[i].fSecondValue)) 
				/ (pStruEleGroup[i + 1].fFirstValue - pStruEleGroup[i].fFirstValue) + pStruEleGroup[i].fSecondValue);
			break;
		}
	}
	//���
	if((nEleArraySize > 1) && (1 == CompareBothDouble(fFirstValue, pStruEleGroup[nEleArraySize - 1].fFirstValue)))
	{
		fSecondValue = (((fFirstValue - pStruEleGroup[nEleArraySize - 2].fFirstValue) * (pStruEleGroup[nEleArraySize - 1].fSecondValue - pStruEleGroup[nEleArraySize - 2].fSecondValue)) 
			/ (pStruEleGroup[nEleArraySize - 1].fFirstValue - pStruEleGroup[nEleArraySize - 2].fFirstValue) + (pStruEleGroup[nEleArraySize - 2].fSecondValue));
	}
    
	return fSecondValue;
}

//���������߼��㺯��
double Parabola2nd(STRU_TWO_ELEMENTGROUP *pStruEleGroup, long nEleArraySize, double fFirstValue, double &fSecondValue)
{
    double fFirstValue1;   //��һ����������ֵ
    double fSecondValue1;  //��һ��Ŀ��ֵ
    double fFirstValue2;   //�ڶ�����������ֵ
	double fSecondValue2;  //�ڶ���Ŀ��ֵ
	
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

//���������߼��㺯��
double Parabola3rd(STRU_TWO_ELEMENTGROUP *pStruEleGroup, long nEleArraySize, double fFirstValue, double &fSecondValue)
{
    double fFirstValue1;   //��һ����������ֵ
    double fSecondValue1;  //��һ��Ŀ��ֵ
    double fFirstValue2;   //�ڶ�����������ֵ
	double fSecondValue2;  //�ڶ���Ŀ��ֵ

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

//���ַ������ݸ����ָ����ָ�ɶ�����ַ���
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

//ȥ���ַ�������ո��ַ�
string TrimSpace(string strSrc)
{
    if(strSrc.empty())
    {
        return strSrc;
    }
    char cTemp;
    string::iterator iter;
    //������ո�
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

    //����Ҳ�ո�
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

//ȥ���ַ��������������ַ�
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

//ȥ���ַ������ָ���ַ���
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

//ȥ���ַ����Ҳ�ָ���ַ���
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

//�Ƚ������������Ƿ���Ȳ���ָ���ȽϾ���(��0.001)���������򷵻�0�����fFirstС��fSecond���򷵻�-1�����fFirst����fSecond���򷵻�1
short CompareBothDouble(double fFirst, double fSecond, double fDigitAfterPoint)
{
    //���㾫��ΪfDigitAfterPoint
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

//�Ƚ������������Ƿ���Ȳ���ָ���ȽϾ���(��0.0000001)���������򷵻�true�����򷵻�false
bool Equal(double fFirst, double fSecond, double fDigitAfterPoint)
{
    //���㾫��ΪfDigitAfterPoint
    if(fabs(fFirst - fSecond) < fDigitAfterPoint)
    {
        return true;
    }
    return false;
}

//��˫���������ݸ�ʽ�����ַ�����ʽ��С��������ָ�ʽĬ��Ϊ3λ
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

//���������ݸ�ʽ�����ַ�����ʽ
char* FormatIntToStr(int nSrcData, char *strDest)
{
    sprintf_s(strDest, sizeof(strDest), "%d", nSrcData);
    return strDest;
}

//�ж��ַ����Ƿ�ȫ������ASCII���ַ�
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

//����д�ַ���ת��ΪСд�ַ���
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

//����д�ַ���ת��ΪСд�ַ���
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

//��Сд�ַ���ת��Ϊ��д�ַ���
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

//��Сд�ַ���ת��Ϊ��д�ַ���
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

//��ʹ�õ������ڴ��ֽ���
unsigned long UsedMemory()
{
	MEMORYSTATUS memstatus;
	memset(&memstatus,0,sizeof(MEMORYSTATUS));
	memstatus.dwLength =sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memstatus);
	DWORD ulMem = memstatus.dwTotalPhys-memstatus.dwAvailPhys;
    return ulMem;
}

//δʹ�õ������ڴ��ֽ���
unsigned long FreeMemory()
{
	MEMORYSTATUS memstatus;
	memset(&memstatus,0,sizeof(MEMORYSTATUS));
	memstatus.dwLength =sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memstatus);
	DWORD ulMem = memstatus.dwAvailPhys ;
    return ulMem;
}

//���ַ����в����ַ���λ��
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

//���ַ������ݸ����ָ����ָ�ɶ�����ַ���
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

//ʱ���ʽ������ 2013-01-30 18:18:18 �ĸ�ʽ
short CompareTime(string strTime1, string strTime2)
{
    if(strTime1.compare(strTime2) == 0)
    {
        return 0;  //����ʱ�����
    }
    //��һ��ʱ��
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

    //�ڶ���ʱ��
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

    //�Ƚ�����ʱ��
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
        else  //�����
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
                else //�����
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
                        else  //�����
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
                                else  //ʱ���
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
                                        else //�����
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

//ʱ���ʽ������ 2013-01-30 18:18:18 �ĸ�ʽ
short CalcDays(string strTime1, string strTime2)
{
    if(strTime1.compare(strTime2) == 0)
    {
        return 0;  //����ʱ����ȣ����0��
    }
    //��һ��ʱ��
    string strTime1PartArray[3];
    SpliteSubStrByDelimiter(strTime1, strTime1PartArray, 3, " ");
    string strYMD1[4];
    SpliteSubStrByDelimiter(strTime1PartArray[0], strYMD1, 4, "-");
    int nYear1 = atoi(strYMD1[0].c_str());
    int nMonth1 = atoi(strYMD1[1].c_str());
    int nMonthDay1 = atoi(strYMD1[2].c_str());

    //�ڶ���ʱ��
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

//�˷�����
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

//ͼ����Դ��Ϊ�ļ�
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

	HICON hIcon = ::CreateIconIndirect(&ii);//һ��������Ҫ��ע����DestroyIcon�����ͷ�ռ�õ��ڴ漰��Դ
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
		CFile fDwg(file,CFile::modeRead);//�ļ���
		CString bmp=L"preview.tmp";
		CFile fBmp(bmp,CFile::modeCreate|CFile::modeWrite);	

		int   PosSentinel=0;         //�ļ��������λ��
		char  *BMPInfo;
		int   TypePreview=0;         //����ͼ��ʽ
		int   PosBMP=0;              //����ͼλ��
		int   LenBMP=0;              //����ͼ��С
		short biBitCount=0;          //����ͼ�������
		BITMAPFILEHEADER biH;        //BMP�ļ�ͷ��DWG�ļ��в�����λͼ�ļ�ͷ��Ҫ���м���

		fDwg.Seek(13,CFile::begin);   //�ӵ�13�ֽڿ�ʼ��ȡ
		fDwg.Read(&PosSentinel,4);    //��13��17�ֽ�ָʾ����ͼ�������λ��,��ȡ4���ֽڵ��з��������Ĵ���

		fDwg.Seek(PosSentinel+30,CFile::begin); //��31�ֽ�Ϊ����ͼ��ʽ��Ϣ��2Ϊbmp��ʽ��3Ϊwmf
		fDwg.Read(&TypePreview,1);              //��ȡһ���ֽڵ�����

		switch(TypePreview)
		{
		case 1: 
		case 3: 		
			AfxMessageBox(L"����bmpͼ��");
			break;
		case 2: 
			fDwg.Seek(PosSentinel+31,CFile::begin); //DWG�ļ������λͼ����λ��  
			fDwg.Read(&PosBMP,4);                   //��ȡ4���ֽڵ��з��������Ĵ���      
			fDwg.Seek(PosSentinel+35,CFile::begin); //λͼ�Ĵ�С     
			fDwg.Read(&LenBMP,4);                   //��ȡ4���ֽڵ��з��������Ĵ���
			fDwg.Seek(PosBMP+14,CFile::begin);      //�ƶ�ָ�뵽λͼ��,��ȡ�������
			fDwg.Read(&biBitCount,2);               //��ȡ2���ֽڵ��з��������Ĵ���
			fDwg.Seek(PosBMP, CFile::begin);        //��λͼ�鿪ʼ����ȡȫ��λͼ���ݱ���,

			//��ȡLenBMP���ȵ��ֽ����ݵ�����BMPInfo�� 
			BMPInfo=new char[LenBMP]; 
			fDwg.Read(BMPInfo,LenBMP);			
			//BMPInfo = br.ReadBytes(LenBMP)  '�������ļ�ͷ��λͼ��Ϣ
			fDwg.Close();

			//����λͼ�ļ�ͷ
			biH.bfType=0x4D42; 
			if(biBitCount<9)
				biH.bfSize=DWORD(54+4*pow(2.0,biBitCount)+LenBMP); 
			else 
				biH.bfSize=54+LenBMP;

			biH.bfReserved1=0;             //�����ֽ�
			biH.bfReserved2=0;             //�����ֽ� 
			biH.bfOffBits=14+0x28+1024;    //ͼ������ƫ��

			fBmp.Write(&biH,sizeof(BITMAPFILEHEADER));	 //д��λͼ�ļ�ͷ
			fBmp.Write(BMPInfo,LenBMP);                  //д��λͼ
			delete[] BMPInfo;
			fBmp.Close();

			//����λͼ
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
		//��Դ�ļ�writer.exe����Ϊ204800Byte,����Դ�ļ��ж���Ϊ"CUSTOM"��Դ,���Ϊ1111 
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
	//��ȡCPU���к�
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
	//��ȡC�̵����к�
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
	//��ʼ��NetBIOS
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
	//����һ����Կ����
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
	//����һ����Կ����
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