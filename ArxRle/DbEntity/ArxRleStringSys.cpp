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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArxRleStringSys::ArxRleStringSys()
{
    m_vecSubStringList.clear();
    m_nSubStringIndex = 0;
}

ArxRleStringSys::~ArxRleStringSys()
{
    m_vecSubStringList.clear();
    m_nSubStringIndex = 0;
}

ArxRleStringSys* ArxRleStringSys::m_pInstance = NULL;

ArxRleStringSys* ArxRleStringSys::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new ArxRleStringSys();
	} 
	return m_pInstance;
}

//将字符串根据给定分隔符分割成多个子字符串
int ArxRleStringSys::ParseSubStrByDelimiter(ArxRleString strText, ArxRleString* strArray, char cDelimiter)
{
    int nSeparator = -1;
    int nNextSeparator = -1;
    strText.Trim();
    string strLine = strText.s_str();
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

    if (-1 == strLine.find(cDelimiter))
    {
        if (-1 == strLine.find(';'))
        {
            if (-1 == strLine.find(','))
            {
                cDelimiter = ' ';
            }
            else
            {
                cDelimiter = ',';
            }
        }
        else
        {
            cDelimiter = ';';
        }
    }
 
    switch (cDelimiter)
    {
    case ' ':
        for (i = 0; i < nStrLen && nStrLen > 1;)
        {
            if (strLine.at(i) != cDelimiter)
            {
                nSeparator = i;
                nNextSeparator = strLine.find(cDelimiter, nSeparator + 1);
                if (nNextSeparator < 0)
                {
                    strArray[nStrArraySize++] = strLine.substr(nSeparator, nStrLen - 1);
                    break;
                }
                if (nNextSeparator-nSeparator < nStrLen)
                {
                    strArray[nStrArraySize++] = strLine.substr(nSeparator, nNextSeparator-nSeparator);
                }
                else
                {
                    break;
                }
                
                i = nNextSeparator;
                if (i >= nStrLen)
                {
                    break;
                }
            }
            else
            {
                i++;
            }
        }
        break;
        
    case ',':
    case ';':
    default:
        for (i = 0; i < nStrLen && nStrLen > 1;)
        {
            if (i == 0)
            {
                if (strLine.at(i) == cDelimiter)
                {
                    strArray[nStrArraySize++] = "";
                    if (i+1 < nStrLen && strLine.at(i+1) == cDelimiter)
                    {
                        i++;
                    }
                    else
                    {
                         while (strLine.at(i+1) == ' ' || strLine.at(i+1) == '\t')
                         {
                             i++;
                             if (strLine.at(i+1) == cDelimiter)
                             {
                                 i++;
                                 break;
                             }
                             
                         }
                    }
                    nSeparator = i;
                }
                else
                {
                    nSeparator = strLine.find(cDelimiter, nSeparator + 1);
                    if (nSeparator < 0 || nSeparator >= nStrLen)
                    {
                        break;
                    }
                    strArray[nStrArraySize++] = strLine.substr(0, nSeparator);
                    i = nSeparator;
                }
            }
            else
            {
                nSeparator = i;
                nNextSeparator = strLine.find(cDelimiter, nSeparator + 1);
                if (nSeparator + 1 < nStrLen && nNextSeparator < 0)
                {
                    strArray[nStrArraySize++] = strLine.substr(nSeparator + 1, nStrLen - nSeparator - 1);
                    break;
                }
                
                if (nNextSeparator == nSeparator + 1)
                {
                    strArray[nStrArraySize++] = "";
                }
                else
                {
                    if (nSeparator + 1 < nStrLen)
                    {
                        strArray[nStrArraySize++] = strLine.substr(nSeparator + 1, nNextSeparator - nSeparator - 1);
                    }
                    else
                    {
                        break;
                    }
                }
                
                i = nNextSeparator;
            }
        }
        break;
    }
    return nStrArraySize;
}

//根据给定的字符串分隔符将字符串分割成多个子字符串（目前默认包括：分号; 逗号, 和空格）
bool ArxRleStringSys::GetSubStringList(ArxRleString strLine, ArxRleStringList *pSubStrList, char cDelimiter)
{
    m_vecSubStringList.clear();
    ArxRleString strArray[1000];
    int nArraySize = this->ParseSubStrByDelimiter(strLine, strArray, cDelimiter);
    if (nArraySize > 0)
    {
        for (int i = 0; i < nArraySize; i++)
        {
            m_vecSubStringList.push_back(strArray[i].s_str());
            pSubStrList->push_back(strArray[i].s_str());
        }

        m_iterSubStrIter = m_vecSubStringList.begin();
        m_nSubStringIndex = 0;

        return true;
    }
    else
    {
        return false;
    }
}

//清空子字符串列表
void ArxRleStringSys::ClearSubStringList()
{
    m_vecSubStringList.clear();
    m_nSubStringIndex = 0;
}

//获取下一个子字符串
ArxRleString* ArxRleStringSys::GetNextSubString()
{
    if (m_vecSubStringList.size() == 0)
    {
        return NULL;
    }

    if (m_nSubStringIndex == 0)
    {
        m_iterSubStrIter = m_vecSubStringList.begin();
    }

    if (m_iterSubStrIter == m_vecSubStringList.end())
    {
        ResetSubStringIndex();
        return NULL;
    }

    //当前
    m_strCurSubString = (*m_iterSubStrIter++);
    m_nSubStringIndex++;

    return &m_strCurSubString;
}

//重置当前子字符串所在子字符串列表中的序号
void ArxRleStringSys::ResetSubStringIndex()
{
    m_iterSubStrIter = m_vecSubStringList.begin();
    m_nSubStringIndex = 0;
}

//修改直接在源串上进行 
string ArxRleStringSys::Replace(string& strText,       //   源串 
                            const string& strOld,  //   要被替换的目标串 
                            const string& strNew)  //   替代串
{ 
    size_t pos = 0; 
    string tempStr = strText; 
    string::size_type oldStrLen = strOld.length();
    string::size_type newStrLen = strNew.length();
    
    while(true) 
    { 
        pos = tempStr.find(strOld, pos); 
        if (pos == string::npos) break; 
        
        tempStr.replace(pos, oldStrLen, strNew);
        pos += newStrLen;
    }

    return tempStr;
}
