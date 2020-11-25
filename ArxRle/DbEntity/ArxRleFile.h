// ArxRleFile.h: interface for the ArxRleFile class.
//

#ifndef ARXRLE_FILE_H
#define ARXRLE_FILE_H

class ArxRleFile
{
public:
	ArxRleFile();
    ArxRleFile(ArxRleFile* pFile);
	virtual ~ArxRleFile();

public:
    /**********************************************************************************
    函数功能：           //创建文件（文件名称含路径）(如果有此文件，则直接打开文件，但是一个覆盖模式写文件)
    nMode = 0:           //以默认模式写文件
    nMode = 1:           //以追加模式写文件
    */
    bool CreateFile(ArxRleString strPathFileName, short nMode=0);
    /**********************************************************************************
    函数功能：           //创建文件(如果有此文件，则直接打开文件，但是一个覆盖模式写文件)
    nMode = 0:           //以默认模式写文件
    nMode = 1:           //以追加模式写文件
    */
    bool CreateFile(ArxRleString strPathDir, ArxRleString strFileName, short nMode=0);
    /**********************************************************************************
    strFileName:         //文件名称中含文件路径
    nMode = 0:           //以默认读文件模式打开文件
    nMode = 1:           //以二进制读文件方式打开文件
    nMode = 2:           //以写文件方式打开文件
    nMode = 3:           //以二进制写文件方式打开文件
    */
    bool OpenFile(ArxRleString strPathFileName, short nMode=0);
    /**********************************************************************************
    strPathDir:          //文件路径
    strFileName:         //文件名称
    nMode = 0:           //以默认读文件模式打开文件
    nMode = 1:           //以二进制读文件方式打开文件
    nMode = 2:           //以写文件方式打开文件
    nMode = 3:           //以二进制写文件方式打开文件
    */
    bool OpenFile(ArxRleString strPathDir, ArxRleString strFileName, short nMode=0);
    //读文件，每次读一行
    bool ReadLine(ArxRleString &strLine);
    //读文件，每次读一行，并将每一行的数据拆分到字符串列表中，分隔符目前支持分号和逗号（; ,） 
    bool ReadLine(ArxRleStringList *pSubStrList, char cDelimiter);
    //读文件，每次读一行，并将每一行的数据拆分到字符串数组中，分隔符目前支持分号和逗号（; ,）
    bool ReadLine(ArxRleString *pSubStrList, int nSubStrSize, char cDelimiter);
    //写文件
    void WriteLine(ArxRleString strLine);
    //关闭文件
    void CloseFile();

public:
    fstream *GetIFStream();    //文件读取流对象指针
    fstream *GetOFStream();    //文件输出流对象指针
    ArxRleString GetFileName();     //获取文件名称

protected:
    fstream *m_pIFStream;    //文件读取流对象指针
    fstream *m_pOFStream;    //文件输出流对象指针
    ArxRleString m_strFileName;   //文件名称
};

#endif  // ARXRLE_FILE_H
