//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef ARXRLE_MATRIX_H
#define ARXRLE_MATRIX_H

#include "math.h"
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <iomanip>
#include "Afx.h"
using namespace std;

//#include "stdafx.h"

int		dcinv(double *a,int n)  ; 
 
#if !defined(_BITSET_)
#include <bitset>
#endif // !defined(_BITSET_)

//////////////////////////////////////////////////////////////////////////////////////
//
//(-- class ArxRleTokenizer
//

class  ArxRleTokenizer
{
public:
	ArxRleTokenizer(const CString& cs, const CString& csDelim) : m_cs(cs), m_nCurPos(0)
	{
		SetDelimiters(csDelim);
	}
	void SetDelimiters(const CString& csDelim)
	{
		for(int i = 0; i < csDelim.GetLength(); ++i)
			m_sDelimiter.set(static_cast<BYTE>(csDelim[i]));
	}

	BOOL Next(CString& cs)
	{
		cs.Empty();

		while(m_nCurPos < m_cs.GetLength() && m_sDelimiter[static_cast<BYTE>(m_cs[m_nCurPos])])
			++m_nCurPos;

		if(m_nCurPos >= m_cs.GetLength())
			return FALSE;

		int nStartPos = m_nCurPos;
		while(m_nCurPos < m_cs.GetLength() && !m_sDelimiter[static_cast<BYTE>(m_cs[m_nCurPos])])
			++m_nCurPos;
		
		cs = m_cs.Mid(nStartPos, m_nCurPos - nStartPos);

		return TRUE;
	}

	CString	Tail() const
	{
		int nCurPos = m_nCurPos;

		while(nCurPos < m_cs.GetLength() && m_sDelimiter[static_cast<BYTE>(m_cs[nCurPos])])
			++nCurPos;

		CString csResult;

		if(nCurPos < m_cs.GetLength())
			csResult = m_cs.Mid(nCurPos);

		return csResult;
	}

private:
	CString m_cs;
	std::bitset<256> m_sDelimiter;
	int m_nCurPos;
};
//
//--) // class ArxRleTokenizer
//
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
//
//(-- class ArxRleMatrix
//
class  ArxRleMatrix  
{
public:
	// ��data�ļ��ж�ȡ����,�������ǵķָ���
	BOOL LoadFromDatFile(CString szPath,const CString& sDelim= L" ", BOOL bLineBreak= TRUE);
	//�洢���鵽data�ļ���,�������ǵķָ���
	BOOL SaveToFile(CString szPathname,int nWidth=0,int precision=0,const CString& sDelim= L" ", BOOL bLineBreak= TRUE);
	//����������������ļ�
	BOOL SaveToFile(CString szPath);

	ArxRleMatrix();										// �������캯��
	ArxRleMatrix(int nRows, int nCols);					// ָ�����й��캯��
	ArxRleMatrix(int nRows, int nCols, double value[]);	// ָ�����ݹ��캯��
	ArxRleMatrix(int nSize);							// �����캯��
	ArxRleMatrix(int nSize, double value[]);			// ָ�����ݷ����캯��
	ArxRleMatrix(const ArxRleMatrix& other);			// �������캯��
	BOOL	Init(int nRows, int nCols);				    // ��ʼ������	
	BOOL	MakeUnitMatrix(int nSize);				    // �������ʼ��Ϊ��λ����
	virtual ~ArxRleMatrix();						    // ��������

	//��DOS����½������ֵ���;
	void Show(int width=4,int precision = 2,int flag=ios::fixed/*ios::scientific*/);

	// ���ַ���ת��Ϊ��������
	BOOL FromString(CString s, const CString& sDelim = L" ", BOOL bLineBreak = TRUE);	
	// ������ת��Ϊ�ַ���
	CString ToString(int nWidth=6,int precision=0,const CString& sDelim = L" ", BOOL bLineBreak = TRUE) const;
	// �������ָ����ת��Ϊ�ַ���
	CString RowToString(int nRow, const CString& sDelim = L" ") const;
	// �������ָ����ת��Ϊ�ַ���
	CString ColToString(int nCol, const CString& sDelim = L" ") const;

	//
	// Ԫ����ֵ����
	//

	BOOL	SetElement(int nRow, int nCol, double value);	// ����ָ��Ԫ�ص�ֵ
	double	GetElement(int nRow, int nCol) const;			// ��ȡָ��Ԫ�ص�ֵ
	void    SetData(double value[]);						// ���þ����ֵ
	void    SetData(double x);								// ��x��ֵ
	void    SetRow(int nRow,double *pData);					// ���þ�����ֵ
	void    SetCol(int nCol,double *pData);					// ���þ�����ֵ

	int		GetNumColumns() const;							// ��ȡ���������
	int		GetNumRows() const;								// ��ȡ���������
	int     GetRowVector(int nRow, double* pVector) const;	// ��ȡ�����ָ���о���
	int     GetColVector(int nCol, double* pVector) const;	// ��ȡ�����ָ���о���
	double* GetData() const;								// ��ȡ�����ֵ
	BOOL    GetSubMatrix(ArxRleMatrix& other,int i,int j,int nHight,int nWidth);// ��ȡ����ָ�����ֵľ����
	ArxRleMatrix GetSubMatrix(int i,int j,int nHight,int nWidth);// ��ȡ����ָ�����ֵľ����

	//
	// ��ѧ����
	//

	ArxRleMatrix& operator=(const ArxRleMatrix& other);
	ArxRleMatrix& operator=(double* pData);
	BOOL operator==(const ArxRleMatrix& other) const;
	BOOL operator!=(const ArxRleMatrix& other) const;
	ArxRleMatrix	operator+(const ArxRleMatrix& other) const;
	ArxRleMatrix	operator-(const ArxRleMatrix& other) const;
	ArxRleMatrix	operator*(double value) const;
	ArxRleMatrix	operator*(const ArxRleMatrix& other) const;
	double operator()(int i,int j)const;//������±������()����
	double* operator[](int i)const;//���ؾ����i��ָ��;

	// ������˷�
	BOOL CMul(const ArxRleMatrix& AR, const ArxRleMatrix& AI, const ArxRleMatrix& BR, const ArxRleMatrix& BI, ArxRleMatrix& CR, ArxRleMatrix& CI) const;
	// �����ת��
	ArxRleMatrix T() const;

	//
	// �㷨
	//

	// ʵ���������ȫѡ��Ԫ��˹��Լ����
	BOOL InvertGaussJordan();                                               
	// �����������ȫѡ��Ԫ��˹��Լ����
	BOOL InvertGaussJordan(ArxRleMatrix& mtxImag);                                 
	// �Գ��������������
	BOOL InvertSsgj();
	//�������ͷ��ؽ��                                             
	//�Ը߾�����ȡ�������,ԭ���󽫸ı�
	BOOL inv();
	//ԭ���󲻸ı�
	ArxRleMatrix&  Getinv();
	// �в����Ⱦ�������İ����ط���
	BOOL InvertTrench();                                                    
	// ������ʽֵ��ȫѡ��Ԫ��˹��ȥ��
	double DetGauss();                                                              
	// ������ȵ�ȫѡ��Ԫ��˹��ȥ��
	int RankGauss();
	// �Գ��������������˹���ֽ�������ʽ����ֵ
	BOOL DetCholesky(double* dblDet);                                                               
	// ��������Ƿֽ�
	BOOL SplitLU(ArxRleMatrix& mtxL, ArxRleMatrix& mtxU); 
	// ��ЧLU�ֽ�
	BOOL LU(ArxRleMatrix& mtxL, ArxRleMatrix& mtxU); 
	// һ��ʵ�����QR�ֽ�
	BOOL SplitQR(ArxRleMatrix& mtxQ);                                                      
	// һ��ʵ���������ֵ�ֽ�
	BOOL SplitUV(ArxRleMatrix& mtxU, ArxRleMatrix& mtxV, double eps = 0.000001);                                       
	// ������������ֵ�ֽⷨ
	BOOL GInvertUV(ArxRleMatrix& mtxAP, ArxRleMatrix& mtxU, ArxRleMatrix& mtxV, double eps = 0.000001);
	// Լ���Գƾ���Ϊ�Գ����Խ���ĺ�˹�ɶ��±任��
	BOOL MakeSymTri(ArxRleMatrix& mtxQ, ArxRleMatrix& mtxT, double dblB[], double dblC[]);
	// ʵ�Գ����Խ����ȫ������ֵ�����������ļ���
	BOOL SymTriEigenv(double dblB[], double dblC[], ArxRleMatrix& mtxQ, int nMaxIt = 60, double eps = 0.000001);
	// Լ��һ��ʵ����Ϊ���겮�����ĳ������Ʊ任��
	void MakeHberg();
	// ����겮�����ȫ������ֵ��QR����
	BOOL HBergEigenv(double dblU[], double dblV[], int nMaxIt = 60, double eps = 0.000001);
	// ��ʵ�Գƾ�������ֵ�������������ſɱȷ�
	BOOL JacobiEigenv(double dblEigenValue[], ArxRleMatrix& mtxEigenVector, int nMaxIt = 60, double eps = 0.000001);
	// ��ʵ�Գƾ�������ֵ�������������ſɱȹ��ط�
	BOOL JacobiEigenv2(double dblEigenValue[], ArxRleMatrix& mtxEigenVector, double eps = 0.000001);

	//
	// ���������ݳ�Ա
	//
protected:
	int	m_nNumColumns;			// ��������
	int	m_nNumRows;				// ��������
	double*	m_pData;			// �������ݻ�����

	//
	// �ڲ�����
	//
private:
	void ppp(double a[], double e[], double s[], double v[], int m, int n);
	void sss(double fg[2], double cs[2]);

};
#endif // ARXRLE_MATRIX_H