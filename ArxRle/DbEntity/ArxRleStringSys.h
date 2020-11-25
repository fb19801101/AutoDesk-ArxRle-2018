// ArxRleStringSys.h: interface for the ArxRleStringSys class.
//

#ifndef ARXRLE_STRINGSYS_H
#define ARXRLE_STRINGSYS_H

class ArxRleStringSys
{
private:
    ArxRleString m_strCurSubString;                   //��ǰ���ַ���
    ArxRleStringList m_vecSubStringList;              //���ַ����б�
    ArxRleStringList::iterator m_iterSubStrIter;      //��ǰ���ַ����������ַ����б��е����
    int m_nSubStringIndex;                        //��ǰ���ַ����������ַ����б��е����

private:
	static ArxRleStringSys *m_pInstance;                           //�ַ���������ʵ��

protected:
	//Ϊ��֧�ֵ���ģʽ�������캯������Ϊ˽�к���
	ArxRleStringSys();

public:
    virtual ~ArxRleStringSys();
	//����ģʽ
	static ArxRleStringSys *GetInstance();

public:
    //���ַ������ݸ����ָ����ָ�ɶ�����ַ�����ĿǰĬ�ϰ������ֺ�; ����, �Ϳո�
    static int ParseSubStrByDelimiter(ArxRleString strLine, ArxRleString* strArray, char cDelimiter=';');
    //���ݸ������ַ����ָ�����ĿǰĬ�ϰ������ֺ�; ����, �Ϳո�
    bool GetSubStringList(ArxRleString strLine, ArxRleStringList *pSubStrList, char cDelimiter=';');
    //��ȡ��һ�����ַ���
    ArxRleString* GetNextSubString();
    //������ַ����б�
    void ClearSubStringList();
    //���õ�ǰ���ַ����������ַ����б��е����
    void ResetSubStringIndex();

    //�޸�ֱ����Դ���Ͻ��� 
    string Replace(string& strText,          //   Դ�ַ��� 
                   const string& strOld,     //   Ҫ���滻��Ŀ�괮 
                   const string& strNew);    //   �����

};

#endif  // ARXRLE_STRINGSYS_H
