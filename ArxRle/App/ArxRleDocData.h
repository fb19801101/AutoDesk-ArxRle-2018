// docdata.h : include file for document specific data
//      an instance of this class is automatically created
//      and managed by the ArxRleDataManager class
//      see the AsdkDmgr.h DocData.cpp for more datail
#ifndef ARXRLE_DOCDATA_H
#define ARXRLE_DOCDATA_H

#include "ArxRleDataManager.h"

////////////////////////////////////////////////////
//
// Here you can store the document / database
// related data.
//
class ArxRleDocData
{
public:
	ArxRleDocData();
	~ArxRleDocData();

	static ArxRleDataManager<ArxRleDocData> m_mgrDocVars;
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_DATA(ArxRleDocData)
	//}}AFX_ARX_DATA

	// TODO: here you can add your variables
	//       which depends on a document / database.
	double			m_dWindHt;
	double			m_dWindWt;
	int				m_nRows;
	int				m_nCols;
	int				m_nWindType;	// 0 = Rect, 1 = Arch, 2 = Apex
	AcGePoint2d		m_startPt;
};

#endif