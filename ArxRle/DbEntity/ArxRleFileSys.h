// ArxRleFileSys.h: interface for the ArxRleFileSys class.
//

#ifndef ARXRLE_FILESYS_H
#define ARXRLE_FILESYS_H

class ArxRleFileSys
{
private:
    //�ļ�����ϵͳ��ʵ��
	static ArxRleFileSys *m_pInstance;

private:
	//Ϊ��֧�ֵ���ģʽ�������캯������Ϊ˽�к���
	ArxRleFileSys();
	virtual ~ArxRleFileSys();

public:
	//����ģʽ
	static ArxRleFileSys *GetInstance();

public:
    //��ȡCARD/1������Ŀ¼���磺 C:\Program Files\IB&T\CARD82\CARDP
    ArxRleString GetCADPath();
    //��ȡ��ǰ����Ŀ¼·��
    ArxRleString GetCurPath();
    //����Ŀ¼
    bool MakeDir(ArxRleString strPathDir);
    //��ĳĿ¼�´���һ�����ļ���
    bool MakeDir(ArxRleString strPath, ArxRleString strDir);
    //����ĳ���ļ����ҵ��ļ�����1�����򷵻�0
    bool FindFile(ArxRleString strFileName);
    //��ָ��Ŀ¼�²���ĳ���ļ����ҵ��ļ�����1�����򷵻�0
    bool FindFile(ArxRleString strPathDir, ArxRleString strFileName);
    //��ָ��Ŀ¼�²��Ҵ���ĳ��ǰ׺(�磺BRT)�����ļ��������ҵ����ļ�������δ�ҵ��κ��ļ�����0
    int FindFilesByPrefix(ArxRleString strPathDir, ArxRleString strPrefix, ArxRleStringList *pFileNameList);
    //��ָ��Ŀ¼�²��Ҵ���ĳ��ǰ׺(�磺BRT)�����ļ��������ҵ����ļ�������δ�ҵ��κ��ļ�����0
    int FindFilesByPrefix(ArxRleString strPathDir, ArxRleString strPrefix, ArxRleString *pFileNameList, int *nMaxFileSum);
    //��ָ��Ŀ¼�²��Ҵ���ĳ����׺(�磺CRD)�����ļ��������ҵ����ļ�������δ�ҵ��κ��ļ�����0
    int FindFilesBySuffix(ArxRleString strPathDir, ArxRleString strSuffix, ArxRleStringList *pFileNameList);
    //��ָ��Ŀ¼�²��Ҵ���ĳ����׺(�磺CRD)�����ļ��������ҵ����ļ�������δ�ҵ��κ��ļ�����0
    int FindFilesBySuffix(ArxRleString strPathDir, ArxRleString strSuffix, ArxRleString *pFileNameList, int *nMaxFileSum);
    //ʹ��Shell��ʽ���ļ���һ��Ĭ����ϵͳĬ�ϳ�����ļ������ļ������к���·��
    void ShellExecuteOpen(ArxRleString strFileName);
    long ShellExecute(ArxRleString strFileName, ArxRleString strParameter, short nMode);
    //�����ļ��У���Դ�ļ��и��Ƶ�Ŀ���ļ���
    bool CopyDirectory(ArxRleString strSrcPathDir, ArxRleString strDestPathDir);
    //�����ļ��У���Դ�ļ��и��Ƶ�Ŀ���ļ���
    bool CopyDirectory(ArxRleString strSrcPathDir, ArxRleString strSrcDir, ArxRleString strDestPathDir, ArxRleString strDestDir);
    //�ƶ��ļ��У���Դ�ļ����ƶ���Ŀ���ļ���
    bool MoveDirectory(ArxRleString strSrcPathDir, ArxRleString strDestPathDir);
    //�ƶ��ļ��У���Դ�ļ����ƶ���Ŀ���ļ���
    bool MoveDirectory(ArxRleString strSrcPathDir, ArxRleString strSrcDir, ArxRleString strDestPathDir, ArxRleString strDestDir);
    //�����ļ�����Դ�ļ����ļ����ƺ�·��������Ŀ���ļ����ļ����ƺ�·����
    bool CopyFile(ArxRleString strSrcFileName, ArxRleString strDestFileName);
    //�����ļ�����Դ�ļ�����Ŀ���ļ�
    bool CopyFile(ArxRleString strSrcPathDir, ArxRleString strSrcFileName, ArxRleString strDestPathDir, ArxRleString strDestFileName);
    //�ƶ��ļ�����Դ�ļ����ļ����ƺ�·�����ƶ���Ŀ���ļ����ļ����ƺ�·����
    bool MoveFile(ArxRleString strSrcFileName, ArxRleString strDestFileName);
    //�ƶ��ļ�����Դ�ļ��ƶ���Ŀ���ļ�
    bool MoveFile(ArxRleString strSrcPathDir, ArxRleString strSrcFileName, ArxRleString strDestPathDir, ArxRleString strDestFileName);
    //ɾ���ļ���
    bool DeleteDirectory(ArxRleString strPathDir);
    //ɾ���ļ���
    bool DeleteDirectory(ArxRleString strPathDir, ArxRleString strDir);
    //ɾ���ļ����ļ����ƺ�·����
    bool DeleteFile(ArxRleString strFileName);
    //ɾ���ļ�
    bool DeleteFile(ArxRleString strPathDir, ArxRleString strFileName);
    //�������ļ����ļ����ƺ�·����
    bool RenameFile(ArxRleString strSrcFileName, ArxRleString strDestFileName);
    //�������ļ�
    bool RenameFile(ArxRleString strSrcPathDir, ArxRleString strSrcFileName, ArxRleString strDestPathDir, ArxRleString strDestFileName);


public:
    //�ж��ļ��Ƿ����
    bool FileIsExist(ArxRleString strPathFileName);
    //�ж��ļ��Ƿ���Ա�д�������ļ��Ƿ����������ռ���ţ�������ֵ1��ʾ���Ա�д������ֵ0��ʾ�����Ա�д
    bool FileIsInUsed(ArxRleString strPathFileName);

    //�����ļ����ļ����ƺ�·����(����д��ļ�����ֱ�Ӵ��ļ�������һ������ģʽд�ļ�)
    ArxRleFile* CreateFile(ArxRleString strPathFileName, int nMode=0);
    //�����ļ�(����д��ļ�����ֱ�Ӵ��ļ�������һ������ģʽд�ļ�)
    ArxRleFile* CreateFile(ArxRleString strPathDir, ArxRleString strFileName, int nMode=0);
    //���ļ����ļ����ƺ�·����(���û�д��ļ����򴴽��ļ����������и���ģʽ����׷��ģʽд�ļ�)
    ArxRleFile* OpenFile(ArxRleString strPathFileName, int nMode=0);
    //���ļ�(���û�д��ļ����򴴽��ļ����������и���ģʽ����׷��ģʽд�ļ�)
    ArxRleFile* OpenFile(ArxRleString strPathDir, ArxRleString strFileName, int nMode=0);
    //--------------------------------------------------------------------------------------------
    //�������ߴ��ļ���һ��Ҫ�ر��ļ������������޷�������д�뵽�ļ��ж��ҿ��ܻ�ʹϵͳ������
    //--------------------------------------------------------------------------------------------
    void Close(ArxRleFile *pZFile);
};

#endif  // ARXRLE_FILESYS_H
