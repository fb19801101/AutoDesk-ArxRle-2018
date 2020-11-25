// ArxRleFileSys.h: interface for the ArxRleFileSys class.
//

#ifndef ARXRLE_FILESYS_H
#define ARXRLE_FILESYS_H

class ArxRleFileSys
{
private:
    //文件操作系统类实例
	static ArxRleFileSys *m_pInstance;

private:
	//为了支持单例模式，将构造函数设置为私有函数
	ArxRleFileSys();
	virtual ~ArxRleFileSys();

public:
	//单例模式
	static ArxRleFileSys *GetInstance();

public:
    //获取CARD/1主程序目录，如： C:\Program Files\IB&T\CARD82\CARDP
    ArxRleString GetCADPath();
    //获取当前工作目录路径
    ArxRleString GetCurPath();
    //创建目录
    bool MakeDir(ArxRleString strPathDir);
    //在某目录下创建一个子文件夹
    bool MakeDir(ArxRleString strPath, ArxRleString strDir);
    //查找某个文件，找到文件返回1，否则返回0
    bool FindFile(ArxRleString strFileName);
    //在指定目录下查找某个文件，找到文件返回1，否则返回0
    bool FindFile(ArxRleString strPathDir, ArxRleString strFileName);
    //在指定目录下查找带有某个前缀(如：BRT)所有文件，返回找到的文件总数，未找到任何文件返回0
    int FindFilesByPrefix(ArxRleString strPathDir, ArxRleString strPrefix, ArxRleStringList *pFileNameList);
    //在指定目录下查找带有某个前缀(如：BRT)所有文件，返回找到的文件总数，未找到任何文件返回0
    int FindFilesByPrefix(ArxRleString strPathDir, ArxRleString strPrefix, ArxRleString *pFileNameList, int *nMaxFileSum);
    //在指定目录下查找带有某个后缀(如：CRD)所有文件，返回找到的文件总数，未找到任何文件返回0
    int FindFilesBySuffix(ArxRleString strPathDir, ArxRleString strSuffix, ArxRleStringList *pFileNameList);
    //在指定目录下查找带有某个后缀(如：CRD)所有文件，返回找到的文件总数，未找到任何文件返回0
    int FindFilesBySuffix(ArxRleString strPathDir, ArxRleString strSuffix, ArxRleString *pFileNameList, int *nMaxFileSum);
    //使用Shell方式打开文件，一般默认用系统默认程序打开文件，此文件名称中含有路径
    void ShellExecuteOpen(ArxRleString strFileName);
    long ShellExecute(ArxRleString strFileName, ArxRleString strParameter, short nMode);
    //复制文件夹，从源文件夹复制到目的文件夹
    bool CopyDirectory(ArxRleString strSrcPathDir, ArxRleString strDestPathDir);
    //复制文件夹，从源文件夹复制到目的文件夹
    bool CopyDirectory(ArxRleString strSrcPathDir, ArxRleString strSrcDir, ArxRleString strDestPathDir, ArxRleString strDestDir);
    //移动文件夹，从源文件夹移动到目的文件夹
    bool MoveDirectory(ArxRleString strSrcPathDir, ArxRleString strDestPathDir);
    //移动文件夹，从源文件夹移动到目的文件夹
    bool MoveDirectory(ArxRleString strSrcPathDir, ArxRleString strSrcDir, ArxRleString strDestPathDir, ArxRleString strDestDir);
    //复制文件，从源文件（文件名称含路径）复制目的文件（文件名称含路径）
    bool CopyFile(ArxRleString strSrcFileName, ArxRleString strDestFileName);
    //复制文件，从源文件复制目的文件
    bool CopyFile(ArxRleString strSrcPathDir, ArxRleString strSrcFileName, ArxRleString strDestPathDir, ArxRleString strDestFileName);
    //移动文件，从源文件（文件名称含路径）移动到目的文件（文件名称含路径）
    bool MoveFile(ArxRleString strSrcFileName, ArxRleString strDestFileName);
    //移动文件，从源文件移动到目的文件
    bool MoveFile(ArxRleString strSrcPathDir, ArxRleString strSrcFileName, ArxRleString strDestPathDir, ArxRleString strDestFileName);
    //删除文件夹
    bool DeleteDirectory(ArxRleString strPathDir);
    //删除文件夹
    bool DeleteDirectory(ArxRleString strPathDir, ArxRleString strDir);
    //删除文件（文件名称含路径）
    bool DeleteFile(ArxRleString strFileName);
    //删除文件
    bool DeleteFile(ArxRleString strPathDir, ArxRleString strFileName);
    //重命名文件（文件名称含路径）
    bool RenameFile(ArxRleString strSrcFileName, ArxRleString strDestFileName);
    //重命名文件
    bool RenameFile(ArxRleString strSrcPathDir, ArxRleString strSrcFileName, ArxRleString strDestPathDir, ArxRleString strDestFileName);


public:
    //判断文件是否存在
    bool FileIsExist(ArxRleString strPathFileName);
    //判断文件是否可以被写（或者文件是否被其他软件打开占用着），返回值1表示可以被写，返回值0表示不可以被写
    bool FileIsInUsed(ArxRleString strPathFileName);

    //创建文件（文件名称含路径）(如果有此文件，则直接打开文件，但是一个覆盖模式写文件)
    ArxRleFile* CreateFile(ArxRleString strPathFileName, int nMode=0);
    //创建文件(如果有此文件，则直接打开文件，但是一个覆盖模式写文件)
    ArxRleFile* CreateFile(ArxRleString strPathDir, ArxRleString strFileName, int nMode=0);
    //打开文件（文件名称含路径）(如果没有此文件，则创建文件，并设置有覆盖模式或者追加模式写文件)
    ArxRleFile* OpenFile(ArxRleString strPathFileName, int nMode=0);
    //打开文件(如果没有此文件，则创建文件，并设置有覆盖模式或者追加模式写文件)
    ArxRleFile* OpenFile(ArxRleString strPathDir, ArxRleString strFileName, int nMode=0);
    //--------------------------------------------------------------------------------------------
    //创建或者打开文件后一定要关闭文件函数，否则无法将数据写入到文件中而且可能会使系统将崩溃
    //--------------------------------------------------------------------------------------------
    void Close(ArxRleFile *pZFile);
};

#endif  // ARXRLE_FILESYS_H
