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
    �������ܣ�           //�����ļ����ļ����ƺ�·����(����д��ļ�����ֱ�Ӵ��ļ�������һ������ģʽд�ļ�)
    nMode = 0:           //��Ĭ��ģʽд�ļ�
    nMode = 1:           //��׷��ģʽд�ļ�
    */
    bool CreateFile(ArxRleString strPathFileName, short nMode=0);
    /**********************************************************************************
    �������ܣ�           //�����ļ�(����д��ļ�����ֱ�Ӵ��ļ�������һ������ģʽд�ļ�)
    nMode = 0:           //��Ĭ��ģʽд�ļ�
    nMode = 1:           //��׷��ģʽд�ļ�
    */
    bool CreateFile(ArxRleString strPathDir, ArxRleString strFileName, short nMode=0);
    /**********************************************************************************
    strFileName:         //�ļ������к��ļ�·��
    nMode = 0:           //��Ĭ�϶��ļ�ģʽ���ļ�
    nMode = 1:           //�Զ����ƶ��ļ���ʽ���ļ�
    nMode = 2:           //��д�ļ���ʽ���ļ�
    nMode = 3:           //�Զ�����д�ļ���ʽ���ļ�
    */
    bool OpenFile(ArxRleString strPathFileName, short nMode=0);
    /**********************************************************************************
    strPathDir:          //�ļ�·��
    strFileName:         //�ļ�����
    nMode = 0:           //��Ĭ�϶��ļ�ģʽ���ļ�
    nMode = 1:           //�Զ����ƶ��ļ���ʽ���ļ�
    nMode = 2:           //��д�ļ���ʽ���ļ�
    nMode = 3:           //�Զ�����д�ļ���ʽ���ļ�
    */
    bool OpenFile(ArxRleString strPathDir, ArxRleString strFileName, short nMode=0);
    //���ļ���ÿ�ζ�һ��
    bool ReadLine(ArxRleString &strLine);
    //���ļ���ÿ�ζ�һ�У�����ÿһ�е����ݲ�ֵ��ַ����б��У��ָ���Ŀǰ֧�ַֺźͶ��ţ�; ,�� 
    bool ReadLine(ArxRleStringList *pSubStrList, char cDelimiter);
    //���ļ���ÿ�ζ�һ�У�����ÿһ�е����ݲ�ֵ��ַ��������У��ָ���Ŀǰ֧�ַֺźͶ��ţ�; ,��
    bool ReadLine(ArxRleString *pSubStrList, int nSubStrSize, char cDelimiter);
    //д�ļ�
    void WriteLine(ArxRleString strLine);
    //�ر��ļ�
    void CloseFile();

public:
    fstream *GetIFStream();    //�ļ���ȡ������ָ��
    fstream *GetOFStream();    //�ļ����������ָ��
    ArxRleString GetFileName();     //��ȡ�ļ�����

protected:
    fstream *m_pIFStream;    //�ļ���ȡ������ָ��
    fstream *m_pOFStream;    //�ļ����������ָ��
    ArxRleString m_strFileName;   //�ļ�����
};

#endif  // ARXRLE_FILE_H
