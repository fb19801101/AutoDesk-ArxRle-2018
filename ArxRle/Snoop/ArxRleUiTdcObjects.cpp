//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleUiTdcObjects.h"
#include "AcadUtils/ArxRleUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiTdcObjects::ArxRleUiTdcObjects
**
**  **jma
**
*************************************/

ArxRleUiTdcObjects::ArxRleUiTdcObjects(const AcDbObjectIdArray& objList)
:   m_objList(objList)
{
    //{{AFX_DATA_INIT(ArxRleUiTdcObjects)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcObjects::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjects::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiTdcDbObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcObjects)
	DDX_Control(pDX, ARXRLE_OBJS_EB_ERASE_STATUS, m_txtErased);
	DDX_Control(pDX, ARXRLE_OBJS_LC_DATA, m_dataList);
	DDX_Control(pDX, ARXRLE_OBJS_LB_OBJS, m_lbObjList);

    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcObjects message map

BEGIN_MESSAGE_MAP(ArxRleUiTdcObjects, ArxRleUiTdcDbObjectBase)
    //{{AFX_MSG_MAP(ArxRleUiTdcObjects)
	ON_LBN_SELCHANGE(ARXRLE_OBJS_LB_OBJS, OnSelchangedObjs)
	ON_BN_CLICKED(ARXRLE_OBJS_BN_DATABASE, OnDatabase)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcObjects message handlers

/****************************************************************************
**
**  ArxRleUiTdcObjects::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcObjects::OnInitDialog() 
{
    ArxRleUiTdcDbObjectBase::OnInitDialog();

	m_lbObjList.ResetContent();

	AcDbObject* obj;
	CString str;
	Acad::ErrorStatus es;

	int len = m_objList.length();
	for (int i=0; i<len; i++) {
		es = acdbOpenAcDbObject(obj, m_objList[i], AcDb::kForRead, true);		// might have passed in erased ones
		if (es == Acad::eOk) {
			ArxRleUtils::objToClassAndHandleStr(obj, str);
			m_lbObjList.AddString(str);
			obj->close();
		}
	}

	m_lbObjList.SetCurSel(0);

    buildColumns(m_dataList);
    displayCurrent(0);

    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcObjects::OnSelchangedObjs
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjects::OnSelchangedObjs() 
{
	int index = m_lbObjList.GetCurSel();
	if (index != LB_ERR) {
		displayCurrent(index);
	}
}

/****************************************************************************
**
**  ArxRleUiTdcObjects::displayCurrent
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjects::displayCurrent(int index)
{
	// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    ASSERT((index >= 0) && (index < m_objList.length()));
    if(m_objList.length()==0)
		return;//done


	m_currentObjId = m_objList[index];

    CString str;

    AcDbObject* obj = NULL;
    Acad::ErrorStatus es = acdbOpenObject(obj, m_currentObjId, AcDb::kForRead, true);	// might want to show erased
    setExtensionButtons(obj);

    if (es == Acad::eOk) {
		display(obj);

		    // hide or show the erased entity message
		if (obj->isErased())
			m_txtErased.ShowWindow(SW_SHOW);
		else
			m_txtErased.ShowWindow(SW_HIDE);

        obj->close();
    }

	drawPropsList(m_dataList);
}
