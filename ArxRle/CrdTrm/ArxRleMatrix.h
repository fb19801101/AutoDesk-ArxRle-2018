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
	// 从data文件中读取数组,主意它们的分隔符
	BOOL LoadFromDatFile(CString szPath,const CString& sDelim= L" ", BOOL bLineBreak= TRUE);
	//存储数组到data文件中,主意它们的分隔符
	BOOL SaveToFile(CString szPathname,int nWidth=0,int precision=0,const CString& sDelim= L" ", BOOL bLineBreak= TRUE);
	//将矩阵数据输出到文件
	BOOL SaveToFile(CString szPath);

	ArxRleMatrix();										// 基础构造函数
	ArxRleMatrix(int nRows, int nCols);					// 指定行列构造函数
	ArxRleMatrix(int nRows, int nCols, double value[]);	// 指定数据构造函数
	ArxRleMatrix(int nSize);							// 方阵构造函数
	ArxRleMatrix(int nSize, double value[]);			// 指定数据方阵构造函数
	ArxRleMatrix(const ArxRleMatrix& other);			// 拷贝构造函数
	BOOL	Init(int nRows, int nCols);				    // 初始化矩阵	
	BOOL	MakeUnitMatrix(int nSize);				    // 将方阵初始化为单位矩阵
	virtual ~ArxRleMatrix();						    // 析构函数

	//在DOS情况下将矩阵的值输出;
	void Show(int width=4,int precision = 2,int flag=ios::fixed/*ios::scientific*/);

	// 将字符串转换为矩阵数据
	BOOL FromString(CString s, const CString& sDelim = L" ", BOOL bLineBreak = TRUE);	
	// 将矩阵转换为字符串
	CString ToString(int nWidth=6,int precision=0,const CString& sDelim = L" ", BOOL bLineBreak = TRUE) const;
	// 将矩阵的指定行转换为字符串
	CString RowToString(int nRow, const CString& sDelim = L" ") const;
	// 将矩阵的指定列转换为字符串
	CString ColToString(int nCol, const CString& sDelim = L" ") const;

	//
	// 元素与值操作
	//

	BOOL	SetElement(int nRow, int nCol, double value);	// 设置指定元素的值
	double	GetElement(int nRow, int nCol) const;			// 获取指定元素的值
	void    SetData(double value[]);						// 设置矩阵的值
	void    SetData(double x);								// 置x初值
	void    SetRow(int nRow,double *pData);					// 设置矩阵行值
	void    SetCol(int nCol,double *pData);					// 设置矩阵列值

	int		GetNumColumns() const;							// 获取矩阵的列数
	int		GetNumRows() const;								// 获取矩阵的行数
	int     GetRowVector(int nRow, double* pVector) const;	// 获取矩阵的指定行矩阵
	int     GetColVector(int nCol, double* pVector) const;	// 获取矩阵的指定列矩阵
	double* GetData() const;								// 获取矩阵的值
	BOOL    GetSubMatrix(ArxRleMatrix& other,int i,int j,int nHight,int nWidth);// 获取矩阵指定部分的矩阵块
	ArxRleMatrix GetSubMatrix(int i,int j,int nHight,int nWidth);// 获取矩阵指定部分的矩阵块

	//
	// 数学操作
	//

	ArxRleMatrix& operator=(const ArxRleMatrix& other);
	ArxRleMatrix& operator=(double* pData);
	BOOL operator==(const ArxRleMatrix& other) const;
	BOOL operator!=(const ArxRleMatrix& other) const;
	ArxRleMatrix	operator+(const ArxRleMatrix& other) const;
	ArxRleMatrix	operator-(const ArxRleMatrix& other) const;
	ArxRleMatrix	operator*(double value) const;
	ArxRleMatrix	operator*(const ArxRleMatrix& other) const;
	double operator()(int i,int j)const;//矩阵的下标操作符()重载
	double* operator[](int i)const;//返回矩阵第i行指针;

	// 复矩阵乘法
	BOOL CMul(const ArxRleMatrix& AR, const ArxRleMatrix& AI, const ArxRleMatrix& BR, const ArxRleMatrix& BI, ArxRleMatrix& CR, ArxRleMatrix& CI) const;
	// 矩阵的转置
	ArxRleMatrix T() const;

	//
	// 算法
	//

	// 实矩阵求逆的全选主元高斯－约当法
	BOOL InvertGaussJordan();                                               
	// 复矩阵求逆的全选主元高斯－约当法
	BOOL InvertGaussJordan(ArxRleMatrix& mtxImag);                                 
	// 对称正定矩阵的求逆
	BOOL InvertSsgj();
	//以引用型返回结果                                             
	//以高精度求取矩阵的逆,原矩阵将改变
	BOOL inv();
	//原矩阵不改变
	ArxRleMatrix&  Getinv();
	// 托伯利兹矩阵求逆的埃兰特方法
	BOOL InvertTrench();                                                    
	// 求行列式值的全选主元高斯消去法
	double DetGauss();                                                              
	// 求矩阵秩的全选主元高斯消去法
	int RankGauss();
	// 对称正定矩阵的乔里斯基分解与行列式的求值
	BOOL DetCholesky(double* dblDet);                                                               
	// 矩阵的三角分解
	BOOL SplitLU(ArxRleMatrix& mtxL, ArxRleMatrix& mtxU); 
	// 有效LU分解
	BOOL LU(ArxRleMatrix& mtxL, ArxRleMatrix& mtxU); 
	// 一般实矩阵的QR分解
	BOOL SplitQR(ArxRleMatrix& mtxQ);                                                      
	// 一般实矩阵的奇异值分解
	BOOL SplitUV(ArxRleMatrix& mtxU, ArxRleMatrix& mtxV, double eps = 0.000001);                                       
	// 求广义逆的奇异值分解法
	BOOL GInvertUV(ArxRleMatrix& mtxAP, ArxRleMatrix& mtxU, ArxRleMatrix& mtxV, double eps = 0.000001);
	// 约化对称矩阵为对称三对角阵的豪斯荷尔德变换法
	BOOL MakeSymTri(ArxRleMatrix& mtxQ, ArxRleMatrix& mtxT, double dblB[], double dblC[]);
	// 实对称三对角阵的全部特征值与特征向量的计算
	BOOL SymTriEigenv(double dblB[], double dblC[], ArxRleMatrix& mtxQ, int nMaxIt = 60, double eps = 0.000001);
	// 约化一般实矩阵为赫申伯格矩阵的初等相似变换法
	void MakeHberg();
	// 求赫申伯格矩阵全部特征值的QR方法
	BOOL HBergEigenv(double dblU[], double dblV[], int nMaxIt = 60, double eps = 0.000001);
	// 求实对称矩阵特征值与特征向量的雅可比法
	BOOL JacobiEigenv(double dblEigenValue[], ArxRleMatrix& mtxEigenVector, int nMaxIt = 60, double eps = 0.000001);
	// 求实对称矩阵特征值与特征向量的雅可比过关法
	BOOL JacobiEigenv2(double dblEigenValue[], ArxRleMatrix& mtxEigenVector, double eps = 0.000001);

	//
	// 保护性数据成员
	//
protected:
	int	m_nNumColumns;			// 矩阵列数
	int	m_nNumRows;				// 矩阵行数
	double*	m_pData;			// 矩阵数据缓冲区

	//
	// 内部函数
	//
private:
	void ppp(double a[], double e[], double s[], double v[], int m, int n);
	void sss(double fg[2], double cs[2]);

};
#endif // ARXRLE_MATRIX_H