// ArxRleStringSys.h: interface for the ArxRleStringSys class.
//

#ifndef ARXRLE_STRINGSYS_H
#define ARXRLE_STRINGSYS_H

class ArxRleStringSys
{
private:
    ArxRleString m_strCurSubString;                   //当前子字符串
    ArxRleStringList m_vecSubStringList;              //子字符串列表
    ArxRleStringList::iterator m_iterSubStrIter;      //当前子字符串所在子字符串列表中的序号
    int m_nSubStringIndex;                        //当前子字符串所在子字符串列表中的序号

private:
	static ArxRleStringSys *m_pInstance;                           //字符串工具类实例

protected:
	//为了支持单例模式，将构造函数设置为私有函数
	ArxRleStringSys();

public:
    virtual ~ArxRleStringSys();
	//单例模式
	static ArxRleStringSys *GetInstance();

public:
    //将字符串根据给定分隔符分割成多个子字符串（目前默认包括：分号; 逗号, 和空格）
    static int ParseSubStrByDelimiter(ArxRleString strLine, ArxRleString* strArray, char cDelimiter=';');
    //根据给定的字符串分隔符（目前默认包括：分号; 逗号, 和空格）
    bool GetSubStringList(ArxRleString strLine, ArxRleStringList *pSubStrList, char cDelimiter=';');
    //获取下一个子字符串
    ArxRleString* GetNextSubString();
    //清空子字符串列表
    void ClearSubStringList();
    //重置当前子字符串所在子字符串列表中的序号
    void ResetSubStringIndex();

    //修改直接在源串上进行 
    string Replace(string& strText,          //   源字符串 
                   const string& strOld,     //   要被替换的目标串 
                   const string& strNew);    //   替代串

};

#endif  // ARXRLE_STRINGSYS_H
