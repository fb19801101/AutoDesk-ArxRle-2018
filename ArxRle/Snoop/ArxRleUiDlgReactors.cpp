//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//  ArxRleUiDlgReactors.cpp
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleUiDlgReactors.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiDlgReactors::ArxRleUiDlgReactors
**
**  **jma
**
*************************************/

ArxRleUiDlgReactors::ArxRleUiDlgReactors(CWnd* parent, AcDbObject* obj)
:   CAcUiDialog(ArxRleUiDlgReactors::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
    ASSERT(obj != NULL);
    m_objPtr = obj;

    //{{AFX_DATA_INIT(ArxRleUiDlgReactors)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiDlgReactors::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgReactors::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgReactors)
	DDX_Control(pDX, ARXRLE_REACTORS_LB_TRANSIENT, m_transList);
	DDX_Control(pDX, ARXRLE_REACTORS_LB_PERSISTENT, m_persistList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgReactors message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgReactors, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxRleUiDlgReactors)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgReactors message handlers


/****************************************************************************
**
**  ArxRleUiDlgReactors::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgReactors::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();

    m_persistList.SetTabStops(45);
    
    CString str, str2;

    void* pSomething;
    AcDbObjectReactor* pObjReactor;
    AcDbObject* obj;
    Acad::ErrorStatus es;

    const AcDbVoidPtrArray* reactors = m_objPtr->reactors();
    if (reactors != nullptr) {
        for (int i = 0; i < reactors->length(); i++) {
            pSomething = reactors->at(i);
            if (acdbIsPersistentReactor(pSomething)) {
                es = acdbOpenObject(obj, acdbPersistentReactorObjectId(pSomething), AcDb::kForRead);
                if ((es == Acad::eOk) && obj) {
                    str.Format(_T("%s\t%s"), ArxRleUtils::objToHandleStr(obj, str2),
                                ArxRleUtils::objToClassStr(obj));
                    m_persistList.AddString(str);
                    obj->close();
                }
            }
            else {
                pObjReactor = static_cast<AcDbObjectReactor*>(reactors->at(i));
                m_transList.AddString(ArxRleUtils::objToClassStr(pObjReactor));
            }
        }
    }
    return TRUE;
}
