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
#include "ArxRleStringSys.h"
#include "ArxRleFile.h"
#include "ArxRleFileSys.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArxRleFileSys::ArxRleFileSys()
{

}

ArxRleFileSys::~ArxRleFileSys()
{

}

ArxRleFileSys* ArxRleFileSys::m_pInstance = NULL;

ArxRleFileSys* ArxRleFileSys::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new ArxRleFileSys();
	} 
	return m_pInstance;
}

//��ȡCARD/1������Ŀ¼���磺 C:\Program Files\IB&T\CARD82\CARDP
ArxRleString ArxRleFileSys::GetCADPath()
{
	USES_CONVERSION;
	char* szAppFileName = T2A(acedGetAppName()); //ȡ��������Ӧ�ó������ƣ���·��
	char szDir[_MAX_DIR], szDrive[_MAX_DRIVE], szPath[_MAX_PATH];
	_splitpath(szAppFileName, szDrive, szDir, NULL, NULL);
	_makepath(szPath, szDrive, szDir, NULL, NULL);

	sprintf_s(szPath,"%sAdlmRes\\",szPath);
	if(!DirExist(szPath))
		ModifyDir(szPath);
	sprintf_s(szPath,"%sBar\\",szPath);
	if(!DirExist(szPath))
		ModifyDir(szPath);

    return szPath;
}

//��ȡ��ǰ����Ŀ¼·��
ArxRleString ArxRleFileSys::GetCurPath()
{
    char strPath[MAX_SMSG_LENGTH];

    return strPath;
}

bool ArxRleFileSys::MakeDir(ArxRleString strPathDir)
{
    return (bool)_mkdir(strPathDir.c_ptr());
}

bool ArxRleFileSys::MakeDir(ArxRleString strPath, ArxRleString strDir)
{
    strPath.Append("\\");
    strPath.Append(strDir);
    return (bool)_mkdir(strPath.c_ptr());
}

//����ĳ���ļ����ҵ��ļ�����1�����򷵻�0
bool ArxRleFileSys::FindFile(ArxRleString strFileName)
{
    return PathFileExists(strFileName.t_str());
}

//��ָ��Ŀ¼�²���ĳ���ļ����ҵ��ļ�����1�����򷵻�0
bool ArxRleFileSys::FindFile(ArxRleString strPathDir, ArxRleString strFileName)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE   hFile = INVALID_HANDLE_VALUE;
    strPathDir.Append("\\");
    strPathDir.Append(strFileName);

    hFile = FindFirstFile(strPathDir.t_str(), &FindFileData);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        FindClose(hFile);
        return false;
    }
    FindClose(hFile);
    return true;
}

//��ָ��Ŀ¼�²��Ҵ���ĳ��ǰ׺(�磺BRT)�����ļ��������ҵ����ļ�������δ�ҵ��κ��ļ�����0
int ArxRleFileSys::FindFilesByPrefix(ArxRleString strPathDir, ArxRleString strPrefix, ArxRleStringList *pFileNameList)
{    
    strPathDir.Append("\\");
    strPathDir.Append(strPrefix);
    strPathDir.Append("*");

	if(pFileNameList == NULL)
		return 0;

	pFileNameList->clear();

    WIN32_FIND_DATA FindFileData;
    HANDLE   hFind = INVALID_HANDLE_VALUE;
    hFind = FindFirstFile(strPathDir.t_str(), &FindFileData);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        pFileNameList->push_back(ArxRleString(FindFileData.cFileName));
        while(FindNextFile(hFind, &FindFileData))
        {
            pFileNameList->push_back(ArxRleString(FindFileData.cFileName));
        }

        FindClose(hFind);
    }

    return pFileNameList->size();
}

//��ָ��Ŀ¼�²��Ҵ���ĳ��ǰ׺(�磺BRT)�����ļ��������ҵ����ļ�������δ�ҵ��κ��ļ�����0
int ArxRleFileSys::FindFilesByPrefix(ArxRleString strPathDir, ArxRleString strPrefix, ArxRleString *pFileNameList, int *nMaxFileSum)
{
    strPathDir.Append("\\");
    strPathDir.Append(strPrefix);
    strPathDir.Append("*");

	if(pFileNameList == NULL)
		return 0;

    int nCount = 0;
    WIN32_FIND_DATA FindFileData;
    HANDLE   hFind = INVALID_HANDLE_VALUE;
    hFind = FindFirstFile(strPathDir.t_str(), &FindFileData);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        pFileNameList[nCount++] = ArxRleString(FindFileData.cFileName);
        while(FindNextFile(hFind, &FindFileData))
        {
            if (nCount < *nMaxFileSum)
            {
                pFileNameList[nCount++] = ArxRleString(FindFileData.cFileName);
            }
            else
            {
                ArxRleString objReport = "[�������]���ļ��������޷�����̫����ļ�����";
				objReport.Print();
                break;
            }
        }

        FindClose(hFind);
    }

	return nCount;
}

//��ָ��Ŀ¼�²��Ҵ���ĳ����׺(�磺CRD)�����ļ��������ҵ����ļ�������δ�ҵ��κ��ļ�����0
int ArxRleFileSys::FindFilesBySuffix(ArxRleString strPathDir, ArxRleString strSuffix, ArxRleStringList *pFileNameList)
{
    strPathDir.Append("\\");
    strPathDir.Append("*.");
    strPathDir.Append(strSuffix);

	if(pFileNameList == NULL)
		return 0;

    WIN32_FIND_DATA FindFileData;
    HANDLE   hFind = INVALID_HANDLE_VALUE;
    hFind = FindFirstFile(strPathDir.t_str(), &FindFileData);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        pFileNameList->push_back(ArxRleString(FindFileData.cFileName));
        while(FindNextFile(hFind, &FindFileData))
        {
            pFileNameList->push_back(ArxRleString(FindFileData.cFileName));
        }

        FindClose(hFind);
    }
	return pFileNameList->size();
}

//��ָ��Ŀ¼�²��Ҵ���ĳ����׺(�磺CRD)�����ļ��������ҵ����ļ�������δ�ҵ��κ��ļ�����0
int ArxRleFileSys::FindFilesBySuffix(ArxRleString strPathDir, ArxRleString strSuffix, ArxRleString *pFileNameList, int *nMaxFileSum)
{
    strPathDir.Append("\\");
    strPathDir.Append("*.");
    strPathDir.Append(strSuffix);

	if(pFileNameList == NULL)
		return 0;

    int nCount = 0;
    WIN32_FIND_DATA FindFileData;
    HANDLE   hFind = INVALID_HANDLE_VALUE;
    hFind = FindFirstFile(strPathDir.t_str(), &FindFileData);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        pFileNameList[nCount++] = ArxRleString(FindFileData.cFileName);
        while(FindNextFile(hFind, &FindFileData))
        {
            if (nCount < *nMaxFileSum)
            {
                pFileNameList[nCount++] = ArxRleString(FindFileData.cFileName);
            }
            else
            {
                ArxRleString objReport("[�������]���ļ��������޷�����̫����ļ�����");
				objReport.t_str();
                break;
            }
        }

        FindClose(hFind);
    }
	return nCount;
}

//ʹ��Shell��ʽ���ļ���һ��Ĭ����ϵͳĬ�ϳ�����ļ������ļ������к���·��
void ArxRleFileSys::ShellExecuteOpen(ArxRleString strFileName)
{
    ::ShellExecute(NULL, L"open", strFileName.t_str(), NULL, NULL, SW_SHOWNORMAL);
}

//�����ļ��У���Դ�ļ��и��Ƶ�Ŀ���ļ��У��ļ����к�·����
bool ArxRleFileSys::CopyDirectory(ArxRleString strSrcPathDir, ArxRleString strDestPathDir)
{
    //return this->CopyFile(strSrcPathDir, strDestPathDir);
    SHFILEOPSTRUCT shFileOpStruct;
    shFileOpStruct.hwnd = NULL;
    shFileOpStruct.wFunc = FO_COPY;
	shFileOpStruct.pFrom = strSrcPathDir.t_str();
	shFileOpStruct.pTo = strDestPathDir.t_str();
    shFileOpStruct.fFlags = FOF_ALLOWUNDO|FOF_NOCONFIRMMKDIR;
    shFileOpStruct.fAnyOperationsAborted = FALSE;
    //shFileOpStruct.lpszProgressTitle = L"���ڸ����ļ�...";
    BOOL bOk = SHFileOperation(&shFileOpStruct);
    if (bOk == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//�����ļ��У���Դ�ļ��и��Ƶ�Ŀ���ļ���
bool ArxRleFileSys::CopyDirectory(ArxRleString strSrcPathDir, ArxRleString strSrcDir, ArxRleString strDestPathDir, ArxRleString strDestDir)
{
    //return this->CopyFile(strSrcPathDir, strSrcDir, strDestPathDir, strDestDir);
    strSrcPathDir.Append("\\");
    strSrcPathDir.Append(strSrcDir);


    strDestPathDir.Append("\\");
    strDestPathDir.Append(strDestDir);


    SHFILEOPSTRUCT shFileOpStruct;
    shFileOpStruct.hwnd = NULL;
    shFileOpStruct.wFunc = FO_COPY;
    shFileOpStruct.pFrom = strSrcPathDir.t_str();
    shFileOpStruct.pTo = strDestPathDir.t_str();
    shFileOpStruct.fFlags = FOF_ALLOWUNDO|FOF_NOCONFIRMMKDIR;
    shFileOpStruct.fAnyOperationsAborted = FALSE;
    //shFileOpStruct.lpszProgressTitle = L"���ڸ����ļ�...";
    BOOL bOk = SHFileOperation(&shFileOpStruct);
    if (bOk == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//�ƶ��ļ��У���Դ�ļ����ƶ���Ŀ���ļ��У��ļ����к�·����
bool ArxRleFileSys::MoveDirectory(ArxRleString strSrcPathDir, ArxRleString strDestPathDir)
{
    if (this->CopyDirectory(strSrcPathDir, strDestPathDir))
    {
        return this->DeleteDirectory(strSrcPathDir);
    }
    else
    {
        return false;
    }

}

//�ƶ��ļ��У���Դ�ļ����ƶ���Ŀ���ļ���
bool ArxRleFileSys::MoveDirectory(ArxRleString strSrcPathDir, ArxRleString strSrcDir, ArxRleString strDestPathDir, ArxRleString strDestDir)
{
    if (this->CopyDirectory(strSrcPathDir, strSrcDir, strDestPathDir, strDestDir))
    {
        return this->DeleteDirectory(strSrcPathDir, strSrcDir);
    }
    else
    {
        return false;
    }
}

//�����ļ�����Դ�ļ����ļ����ƺ�·��������Ŀ���ļ����ļ����ƺ�·����
bool ArxRleFileSys::CopyFile(ArxRleString strSrcFileName, ArxRleString strDestFileName)
{
	if (::CopyFile(strSrcFileName.t_str(), strDestFileName.t_str(), FALSE) != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//�����ļ�����Դ�ļ�����Ŀ���ļ�
bool ArxRleFileSys::CopyFile(ArxRleString strSrcPathDir, ArxRleString strSrcFileName, ArxRleString strDestPathDir, ArxRleString strDestFileName)
{
    strSrcPathDir.Append("\\");
    strSrcPathDir.Append(strSrcFileName);

    strDestPathDir.Append("\\");
    strDestPathDir.Append(strDestFileName);

    if (::CopyFile(strSrcPathDir.t_str(), strDestPathDir.t_str(), FALSE) != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//�ƶ��ļ�����Դ�ļ����ļ����ƺ�·�����ƶ���Ŀ���ļ����ļ����ƺ�·����
bool ArxRleFileSys::MoveFile(ArxRleString strSrcFileName, ArxRleString strDestFileName)
{
    if (::MoveFile(strSrcFileName.t_str(), strDestFileName.t_str()) != 0)
    {
        return this->DeleteFile(strSrcFileName);
    }
    else
    {
        return false;
    }
}

//�ƶ��ļ�����Դ�ļ��ƶ���Ŀ���ļ�
bool ArxRleFileSys::MoveFile(ArxRleString strSrcPathDir, ArxRleString strSrcFileName, ArxRleString strDestPathDir, ArxRleString strDestFileName)
{
    strSrcPathDir.Append("\\");
    strSrcPathDir.Append(strSrcFileName);

    strDestPathDir.Append("\\");
    strDestPathDir.Append(strDestFileName);

    if (::MoveFile(strSrcPathDir.t_str(), strDestPathDir.t_str()) != 0)
    {
        return this->DeleteFile(strSrcPathDir);
    }
    else
    {
        return false;
    }
}

//ɾ���ļ���
bool ArxRleFileSys::DeleteDirectory(ArxRleString strPathDir)
{
    if (::RemoveDirectory(strPathDir.t_str()) != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//ɾ���ļ���
bool ArxRleFileSys::DeleteDirectory(ArxRleString strPathDir, ArxRleString strDir)
{
    strPathDir.Append("\\");
    strPathDir.Append(strDir);
    if (::RemoveDirectory(strPathDir.t_str()) != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//ɾ���ļ����ļ����ƺ�·����
bool ArxRleFileSys::DeleteFile(ArxRleString strFileName)
{
    const char* lpszFile = strFileName.c_ptr();
    char szDrive[10], szDir[MAX_PATH], szName[MAX_PATH], szExt[MAX_PATH];
    memset(szDrive, 0, sizeof(szDrive));
    memset(szDir, 0, sizeof(szDrive));
    memset(szName, 0, sizeof(szName));
    memset(szExt, 0, sizeof(szExt));
    _splitpath(lpszFile, szDrive, szDir, szName, szExt);
    if(szDrive[0] == 0)
        return false;
    if(szName[0] == 0)
        return false;
    if (::DeleteFile(ArxRleString(lpszFile).t_str()) != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//ɾ���ļ�
bool ArxRleFileSys::DeleteFile(ArxRleString strPathDir, ArxRleString strFileName)
{
    strPathDir.Append("\\");
    strPathDir.Append(strFileName);
    const char* lpszFile = strPathDir.c_ptr();
    char szDrive[10], szDir[MAX_PATH], szName[MAX_PATH], szExt[MAX_PATH];
    memset(szDrive, 0, sizeof(szDrive));
    memset(szDir, 0, sizeof(szDrive));
    memset(szName, 0, sizeof(szName));
    memset(szExt, 0, sizeof(szExt));
    _splitpath(lpszFile, szDrive, szDir, szName, szExt);
    if(szDrive[0] == 0)
        return false;
    if(szName[0] == 0)
        return false;
    if (::DeleteFile(ArxRleString(lpszFile).t_str()) != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//�������ļ����ļ����ƺ�·����
bool ArxRleFileSys::RenameFile(ArxRleString strSrcFileName, ArxRleString strDestFileName)
{
    int bRetValue = ::rename(strSrcFileName.c_ptr(), strDestFileName.c_ptr());
    if (bRetValue == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//�������ļ�
bool ArxRleFileSys::RenameFile(ArxRleString strSrcPathDir, ArxRleString strSrcFileName, ArxRleString strDestPathDir, ArxRleString strDestFileName)
{
    strSrcPathDir.Append("\\");
    strSrcPathDir.Append(strSrcFileName);

    strDestPathDir.Append("\\");
    strDestPathDir.Append(strDestFileName);

    int bRetValue = ::rename(strSrcPathDir.c_ptr(), strDestPathDir.c_ptr());
    if (bRetValue == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//�ж��ļ��Ƿ����
bool ArxRleFileSys::FileIsExist(ArxRleString strPathFileName)
{
    return PathFileExists(strPathFileName.t_str());
}


//�ж��ļ��Ƿ���Ա�д�������ļ��Ƿ����������ռ���ţ�������ֵ1��ʾ���Ա�д������ֵ0��ʾ�����Ա�д
bool ArxRleFileSys::FileIsInUsed(ArxRleString strPathFileName)
{   
    if (PathFileExists(strPathFileName.t_str()))
    {
        HANDLE fileHandle = ::CreateFile(strPathFileName.t_str(), 
            GENERIC_READ|GENERIC_WRITE, 
            FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if(fileHandle&&fileHandle!=INVALID_HANDLE_VALUE)
        {
            CloseHandle(fileHandle);
//             DeleteFile(strPathFileName);
            return false;
        }
        else
        {
            return true;
        }
    }
    return false;
}


//�����ļ����ļ����ƺ�·����(����д��ļ�����ֱ�Ӵ��ļ�������һ������ģʽд�ļ�)
ArxRleFile* ArxRleFileSys::CreateFile(ArxRleString strPathFileName, int nMode)
{
    ArxRleFile *pZFile = new ArxRleFile();
    if (NULL != pZFile)
    {
        if (pZFile->CreateFile(strPathFileName, nMode))
        {
            return pZFile;
        }
        delete pZFile;
        return NULL;
    }
    return pZFile;
}

//�����ļ�(����д��ļ�����ֱ�Ӵ��ļ�������һ������ģʽд�ļ�)
ArxRleFile* ArxRleFileSys::CreateFile(ArxRleString strPathDir, ArxRleString strFileName, int nMode)
{
    ArxRleFile *pZFile = new ArxRleFile();
    if (NULL != pZFile)
    {
        if (pZFile->CreateFile(strPathDir, strFileName, nMode))
        {
            return pZFile;
        }
        delete pZFile;
        return NULL;
    }
    return pZFile;
}

//���ļ����ļ����ƺ�·����(���û�д��ļ����򴴽��ļ����������и���ģʽ����׷��ģʽд�ļ�)
ArxRleFile* ArxRleFileSys::OpenFile(ArxRleString strPathFileName, int nMode)
{
    ArxRleFile *pZFile = new ArxRleFile();
    if (NULL != pZFile)
    {
        if (pZFile->OpenFile(strPathFileName, nMode))
        {
            return pZFile;
        }
        delete pZFile;
        return NULL;
    }
    return pZFile;
}

//���ļ�(���û�д��ļ����򴴽��ļ����������и���ģʽ����׷��ģʽд�ļ�)
ArxRleFile* ArxRleFileSys::OpenFile(ArxRleString strPathDir, ArxRleString strFileName, int nMode)
{
    ArxRleFile *pZFile = new ArxRleFile();
    if (NULL != pZFile)
    {
        if (pZFile->OpenFile(strPathDir, strFileName, nMode))
        {
            return pZFile;
        }
        delete pZFile;
        return NULL;
    }
    return pZFile;
}

//�������ߴ��ļ���һ��Ҫ�ر��ļ�����������ϵͳ������
void ArxRleFileSys::Close(ArxRleFile *pZFile)
{
    if (NULL != pZFile)
    {
        pZFile->CloseFile();
        delete pZFile;
        pZFile = NULL;
    }
}