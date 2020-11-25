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
    //�ļ���ȡ������ָ��
    if (NULL != m_pIFStream)
    {
        m_pIFStream->close();
        delete m_pIFStream;
        m_pIFStream = NULL;
    }

    //�ļ����������ָ��
    if (NULL != m_pOFStream)
    {
        m_pOFStream->close();
        delete m_pOFStream;
        m_pOFStream = NULL;
    }
}

//�����ļ����ļ����ƺ�·����
bool ArxRleFile::CreateFile(ArxRleString strPathFileName, short nMode)
{
    if (NULL != m_pIFStream || NULL != m_pOFStream)
    {
        ArxRleString::Print("���ļ������Ѿ����ļ�%s�������ظ������ļ���", m_strFileName.c_ptr());
        
		return false;
    }

    switch (nMode)
    {
    case 0:           //���ļ���Ĭ��ģʽд�ļ�
        m_pOFStream = new fstream(strPathFileName.c_ptr(), ios::out);
        break;
    case 1:           //���ļ���׷��ģʽд�ļ�
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

//�����ļ�
bool ArxRleFile::CreateFile(ArxRleString strPathDir, ArxRleString strFileName, short nMode)
{
    if (NULL != m_pIFStream || NULL != m_pOFStream)
    {
        ArxRleString::Print("���ļ������Ѿ����ļ�%s�������ظ������ļ���", m_strFileName.c_ptr());
        return false;
    }

    strPathDir.Append("\\");
    strPathDir.Append(strFileName);
    switch (nMode)
    {
    case 0:           //��Ĭ��ģʽд�ļ�
        m_pOFStream = new fstream(strPathDir.c_ptr(), ios::out);
        break;
    case 1:           //��׷��ģʽд�ļ�
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

//���ļ����ļ����ƺ�·����
bool ArxRleFile::OpenFile(ArxRleString strPathFileName, short nMode)
{
    if (NULL != m_pIFStream || NULL != m_pOFStream)
    {
        ArxRleString::Print("���ļ������Ѿ����ļ�%s�������ظ����ļ���", m_strFileName.c_ptr());
        return false;
    }

    ArxRleFileSys *pFileSys = ArxRleFileSys::GetInstance();
    if (0 == pFileSys->FindFile(strPathFileName))
    {
        return false;
    }

    switch (nMode)
    {
    case 0:           //��Ĭ�϶��ļ�ģʽ���ļ�
        m_pIFStream = new fstream(strPathFileName.c_ptr(), ios::in|ios::out);
        break;
    case 1:           //�Զ����ƶ��ļ���ʽ���ļ�
        m_pIFStream = new fstream(strPathFileName.c_ptr(), ios::in|ios::binary);
        break;
    case 2:           //��д�ļ���ʽ���ļ�
        m_pOFStream = new fstream(strPathFileName.c_ptr(), ios::in|ios::out);
        break;
    case 3:           //�Զ�����д�ļ���ʽ���ļ�
        m_pOFStream = new fstream(strPathFileName.c_ptr(), ios::in|ios::out|ios::binary);
        break;
    default:          //��Ĭ�϶��ļ�ģʽ���ļ�
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

//���ļ�
bool ArxRleFile::OpenFile(ArxRleString strPathDir, ArxRleString strFileName, short nMode)
{
    if (NULL != m_pIFStream || NULL != m_pOFStream)
    {
        ArxRleString::Print("���ļ������Ѿ����ļ�%s�������ظ����ļ���", m_strFileName.c_ptr());
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
    case 0:           //��Ĭ�϶��ļ�ģʽ���ļ�
        m_pIFStream = new fstream(strPathDir.c_ptr(), ios::in|ios::out);
        break;
    case 1:           //�Զ����ƶ��ļ���ʽ���ļ�
        m_pIFStream = new fstream(strPathDir.c_ptr(), ios::in|ios::binary);
        break;
    case 2:           //��д�ļ���ʽ���ļ�
        m_pOFStream = new fstream(strPathDir.c_ptr(), ios::in|ios::out);
        break;
    case 3:           //�Զ�����д�ļ���ʽ���ļ�
        m_pOFStream = new fstream(strPathDir.c_ptr(), ios::out|ios::binary);
        break;
    default:          //��Ĭ�϶��ļ�ģʽ���ļ�
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

//���ļ���ÿ�ζ�һ��
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

//���ļ���ÿ�ζ�һ�У�����ÿһ�е����ݲ�ֵ��ַ����б���
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

//���ļ���ÿ�ζ�һ�У�����ÿһ�е����ݲ�ֵ��ַ���������
bool ArxRleFile::ReadLine(ArxRleString *pSubStrList, int nSubStrSize, char cDelimiter)
{
	setlocale(LC_ALL,"");

    if (nSubStrSize < 1)
    {
        pSubStrList = NULL;
        ArxRleString strMsg;
        strMsg.Print("���ļ�ʱ�����ַ��������п��Դ洢���ַ���������������ΪС�� 1 ��");

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

//д�ļ���ÿ��дһ��
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

//�ر��ļ�
void ArxRleFile::CloseFile()
{
    //�ļ���ȡ������ָ��
    if (NULL != m_pIFStream)
    {
        m_pIFStream->close();
        m_pIFStream = NULL;
    }
    
    //�ļ����������ָ��
    if (NULL != m_pOFStream)
    {
        m_pOFStream->close();
        m_pOFStream = NULL;
    }
}

//�ļ���ȡ������ָ��
fstream* ArxRleFile::GetIFStream()
{
    return m_pIFStream;
}

//�ļ����������ָ��
fstream* ArxRleFile::GetOFStream()
{
    return m_pOFStream;
}

//��ȡ�ļ�����
ArxRleString ArxRleFile::GetFileName()
{
    return m_strFileName;
}

