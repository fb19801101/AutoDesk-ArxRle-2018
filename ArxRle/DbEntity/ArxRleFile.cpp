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

ArxRleFile::ArxRleFile()
{
    m_pIFStream = NULL;
    m_pOFStream = NULL;
    m_strFileName = "";
}

ArxRleFile::ArxRleFile(ArxRleFile* pFile)
{
    m_pIFStream = pFile->GetIFStream();
    m_pOFStream = pFile->GetOFStream();
    m_strFileName = pFile->GetFileName();
}

ArxRleFile::~ArxRleFile()
{
    //文件读取流对象指针
    if (NULL != m_pIFStream)
    {
        m_pIFStream->close();
        delete m_pIFStream;
        m_pIFStream = NULL;
    }

    //文件输出流对象指针
    if (NULL != m_pOFStream)
    {
        m_pOFStream->close();
        delete m_pOFStream;
        m_pOFStream = NULL;
    }
}

//创建文件（文件名称含路径）
bool ArxRleFile::CreateFile(ArxRleString strPathFileName, short nMode)
{
    if (NULL != m_pIFStream || NULL != m_pOFStream)
    {
        ArxRleString::Print("此文件对象已经打开文件%s，不能重复创建文件！", m_strFileName.c_ptr());
        
		return false;
    }

    switch (nMode)
    {
    case 0:           //打开文件以默认模式写文件
        m_pOFStream = new fstream(strPathFileName.c_ptr(), ios::out);
        break;
    case 1:           //打开文件以追加模式写文件
        m_pOFStream = new fstream(strPathFileName.c_ptr(), ios_base::app);
        break;
    default:
        m_pOFStream = new fstream(strPathFileName.c_ptr(), ios::out);
        break;
    }
    if (NULL == m_pOFStream)
    {
        return false;
    }
    m_strFileName = strPathFileName;
    return true;
}

//创建文件
bool ArxRleFile::CreateFile(ArxRleString strPathDir, ArxRleString strFileName, short nMode)
{
    if (NULL != m_pIFStream || NULL != m_pOFStream)
    {
        ArxRleString::Print("此文件对象已经打开文件%s，不能重复创建文件！", m_strFileName.c_ptr());
        return false;
    }

    strPathDir.Append("\\");
    strPathDir.Append(strFileName);
    switch (nMode)
    {
    case 0:           //以默认模式写文件
        m_pOFStream = new fstream(strPathDir.c_ptr(), ios::out);
        break;
    case 1:           //以追加模式写文件
        m_pOFStream = new fstream(strPathDir.c_ptr(), ios_base::app);
        break;
    default:
        m_pOFStream = new fstream(strPathDir.c_ptr(), ios::out);
        break;
    }
    if (NULL == m_pOFStream)
    {
        return false;
    }
    m_strFileName = strPathDir;
    return true;
}

//打开文件（文件名称含路径）
bool ArxRleFile::OpenFile(ArxRleString strPathFileName, short nMode)
{
    if (NULL != m_pIFStream || NULL != m_pOFStream)
    {
        ArxRleString::Print("此文件对象已经打开文件%s，不能重复打开文件！", m_strFileName.c_ptr());
        return false;
    }

    ArxRleFileSys *pFileSys = ArxRleFileSys::GetInstance();
    if (0 == pFileSys->FindFile(strPathFileName))
    {
        return false;
    }

    switch (nMode)
    {
    case 0:           //以默认读文件模式打开文件
        m_pIFStream = new fstream(strPathFileName.c_ptr(), ios::in|ios::out);
        break;
    case 1:           //以二进制读文件方式打开文件
        m_pIFStream = new fstream(strPathFileName.c_ptr(), ios::in|ios::binary);
        break;
    case 2:           //以写文件方式打开文件
        m_pOFStream = new fstream(strPathFileName.c_ptr(), ios::in|ios::out);
        break;
    case 3:           //以二进制写文件方式打开文件
        m_pOFStream = new fstream(strPathFileName.c_ptr(), ios::in|ios::out|ios::binary);
        break;
    default:          //以默认读文件模式打开文件
        m_pIFStream = new fstream(strPathFileName.c_ptr(), ios::in);
        break;
    }
    if (NULL == m_pIFStream && NULL == m_pOFStream)
    {
        return false;
    }
    m_strFileName = strPathFileName;
    return true;
}

//打开文件
bool ArxRleFile::OpenFile(ArxRleString strPathDir, ArxRleString strFileName, short nMode)
{
    if (NULL != m_pIFStream || NULL != m_pOFStream)
    {
        ArxRleString::Print("此文件对象已经打开文件%s，不能重复打开文件！", m_strFileName.c_ptr());
        return false;
    }

    ArxRleFileSys *pFileSys = ArxRleFileSys::GetInstance();
    if (0 == pFileSys->FindFile(strPathDir, strFileName))
    {
        return false;
    }

    strPathDir.Append("\\");
    strPathDir.Append(strFileName);
    switch (nMode)
    {
    case 0:           //以默认读文件模式打开文件
        m_pIFStream = new fstream(strPathDir.c_ptr(), ios::in|ios::out);
        break;
    case 1:           //以二进制读文件方式打开文件
        m_pIFStream = new fstream(strPathDir.c_ptr(), ios::in|ios::binary);
        break;
    case 2:           //以写文件方式打开文件
        m_pOFStream = new fstream(strPathDir.c_ptr(), ios::in|ios::out);
        break;
    case 3:           //以二进制写文件方式打开文件
        m_pOFStream = new fstream(strPathDir.c_ptr(), ios::out|ios::binary);
        break;
    default:          //以默认读文件模式打开文件
        m_pIFStream = new fstream(strPathDir.c_ptr(), ios::in);
        break;
    }
    if (NULL == m_pIFStream && NULL == m_pOFStream)
    {
        return false;
    }
    m_strFileName = strPathDir;
    return true;
}

//读文件，每次读一行
bool ArxRleFile::ReadLine(ArxRleString &strLine)
{
	setlocale(LC_ALL,"");

    strLine = "";
    if (NULL != m_pIFStream && (0 == m_pIFStream->eof()))
    {
        char strText[MAX_SMSG_LENGTH];
        m_pIFStream->getline(strText, MAX_LMSG_LENGTH);
        int len = strlen(strText);
        if (strText[len-1] == '\n')
        {
            strText[len-1] = '\0';
        }
        len = strlen(strText);
        if (strText[len-1] == '\r')
        {
            strText[len-1] = '\0';
        }
        strLine = strText;
        len = strlen(strText);
        return true;
    }
    return false;
}

//读文件，每次读一行，并将每一行的数据拆分到字符串列表中
bool ArxRleFile::ReadLine(ArxRleStringList *pSubStrList, char cDelimiter)
{
	setlocale(LC_ALL,"");

    if (NULL == pSubStrList)
    {
        return false;
    }
    pSubStrList->clear();
    if (NULL != m_pIFStream && (0 == m_pIFStream->eof()))
    {
        char strText[MAX_LMSG_LENGTH];
        m_pIFStream->getline(strText, MAX_LMSG_LENGTH);
        int len = strlen(strText);
        if (strText[len-1] == '\n')
        {
            strText[len-1] = '\0';
        }
        len = strlen(strText);
        if (strText[len-1] == '\r')
        {
            strText[len-1] = '\0';
        }
        ArxRleString strLine = strText;
        ArxRleStringSys *pCZStringSys = ArxRleStringSys::GetInstance();
        pCZStringSys->GetSubStringList(strLine, pSubStrList, cDelimiter);
        return true;
    }
    return false;
}

//读文件，每次读一行，并将每一行的数据拆分到字符串数组中
bool ArxRleFile::ReadLine(ArxRleString *pSubStrList, int nSubStrSize, char cDelimiter)
{
	setlocale(LC_ALL,"");

    if (nSubStrSize < 1)
    {
        pSubStrList = NULL;
        ArxRleString strMsg;
        strMsg.Print("读文件时，子字符串数组中可以存储的字符串总数不能设置为小于 1 ！");

        return false;
    }
    if (NULL == pSubStrList)
    {
        return false;
    }
    if (NULL != m_pIFStream && (0 == m_pIFStream->eof()))
    {
        char strText[MAX_LMSG_LENGTH];
        m_pIFStream->getline(strText, MAX_LMSG_LENGTH);
        int len = strlen(strText);
        if (strText[len-1] == '\n')
        {
            strText[len-1] = '\0';
        }
        len = strlen(strText);
        if (strText[len-1] == '\r')
        {
            strText[len-1] = '\0';
        }
        ArxRleString strLine = strText;
        ArxRleStringList subStrList;
        nSubStrSize = 0;
        ArxRleStringSys *pCZStringSys = ArxRleStringSys::GetInstance();
        pCZStringSys->GetSubStringList(strLine, &subStrList, cDelimiter);
        for (ArxRleStringList::iterator iter = subStrList.begin(); iter != subStrList.end(); iter++)
        {
            pSubStrList[nSubStrSize++] = (*iter);
        }
        return true;
    }
    return false;
}

//写文件，每次写一行
void ArxRleFile::WriteLine(ArxRleString strLine)
{
	setlocale(LC_ALL,"");

    if (NULL != m_pOFStream)
    {
        strLine.Append("\r\n");
        long nLen = strLine.s_str().size();
		m_pOFStream->write(strLine.c_ptr(), nLen);
	}
}

//关闭文件
void ArxRleFile::CloseFile()
{
    //文件读取流对象指针
    if (NULL != m_pIFStream)
    {
        m_pIFStream->close();
        m_pIFStream = NULL;
    }
    
    //文件输出流对象指针
    if (NULL != m_pOFStream)
    {
        m_pOFStream->close();
        m_pOFStream = NULL;
    }
}

//文件读取流对象指针
fstream* ArxRleFile::GetIFStream()
{
    return m_pIFStream;
}

//文件输出流对象指针
fstream* ArxRleFile::GetOFStream()
{
    return m_pOFStream;
}

//获取文件名称
ArxRleString ArxRleFile::GetFileName()
{
    return m_strFileName;
}

