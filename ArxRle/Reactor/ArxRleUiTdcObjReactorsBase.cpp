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

#include "ArxRleUiTdcObjReactorsBase.h"
#include "Snoop/ArxRleUiDlgObjState.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"
#include "ArxRleUiTdmREactors.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::ArxRleUiTdcObjReactorsBase
**
**  **jma
**
*************************************/

ArxRleUiTdcObjReactorsBase::ArxRleUiTdcObjReactorsBase()
:   CAcUiTabChildDialog(NULL, ArxRleApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxRleUiTdcObjReactorsBase)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjReactorsBase::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabChildDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcObjReactorsBase)
	DDX_Control(pDX, ARXRLE_REACTORS_BN_ATTACH_ENT, m_attachEntButton);
	DDX_Control(pDX, ARXRLE_REACTORS_BN_DETACH_ENT, m_detachEntButton);
	DDX_Control(pDX, ARXRLE_REACTORS_BN_DETACH_SEL_ENTS, m_detachSelectedEntsButton);
	DDX_Control(pDX, ARXRLE_REACTORS_BN_DETACH_SEL_OBJS, m_detachSelectedObjsButton);
	DDX_Control(pDX, ARXRLE_REACTORS_LB_OBJS, m_lbObjList);
	DDX_Control(pDX, ARXRLE_REACTORS_LB_ENTS, m_lbEntList);
	DDX_Control(pDX, ARXRLE_REACTORS_EB_HANDLE, m_ebHandle);
    //}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcObjReactorsBase message handlers

BEGIN_MESSAGE_MAP(ArxRleUiTdcObjReactorsBase, CAcUiTabChildDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdcObjReactorsBase)
	ON_BN_CLICKED(ARXRLE_REACTORS_BN_ATTACH_OBJ, OnObjAttach)
	ON_BN_CLICKED(ARXRLE_REACTORS_BN_ATTACH_ENT, OnEntAttach)
	ON_BN_CLICKED(ARXRLE_REACTORS_BN_DETACH_ENT, OnEntDetach)
	ON_BN_CLICKED(ARXRLE_REACTORS_BN_DETACH_SEL_ENTS, OnEntDetachSelected)
	ON_BN_CLICKED(ARXRLE_REACTORS_BN_DETACH_SEL_OBJS, OnObjDetachSelected)
	ON_LBN_SELCHANGE(ARXRLE_REACTORS_LB_OBJS, setButtonModes)
	ON_LBN_SELCHANGE(ARXRLE_REACTORS_LB_ENTS, setButtonModes)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcObjReactorsBase message handlers


/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcObjReactorsBase::OnInitDialog() 
{
	CAcUiTabChildDialog::OnInitDialog();

    m_attachEntButton.AutoLoad();
    m_detachEntButton.AutoLoad();
    m_detachSelectedEntsButton.AutoLoad();
    m_detachSelectedObjsButton.AutoLoad();

	displayObjList();
	displayEntList();

	return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::PreTranslateMessage
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcObjReactorsBase::PreTranslateMessage(MSG* pMsg) 
{
    if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN)) {
        CWnd *pWnd = GetFocus();
        if (pWnd != NULL) {
            UINT nID = pWnd->GetDlgCtrlID();
            if (nID == ARXRLE_REACTORS_BN_ATTACH_ENT) {
                ::PostMessage(m_attachEntButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
            if (nID == ARXRLE_REACTORS_BN_DETACH_ENT) {
                ::PostMessage(m_detachEntButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
            if (nID == ARXRLE_REACTORS_BN_DETACH_SEL_ENTS) {
                ::PostMessage(m_detachSelectedEntsButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
            if (nID == ARXRLE_REACTORS_BN_DETACH_SEL_OBJS) {
                ::PostMessage(m_detachSelectedObjsButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
        }
    }
	
	return CAcUiTabChildDialog::PreTranslateMessage(pMsg);
}

/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::displayObjList
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjReactorsBase::displayObjList() 
{
	m_objsAttached.setLogicalLength(0);
	m_lbObjList.ResetContent();

	getAttachedObjects(m_objsAttached);

	CString str;
	Acad::ErrorStatus es;
	AcDbObject* obj;

    int len = m_objsAttached.length();
    for (int i=0; i<len; i++) {
		es = acdbOpenAcDbObject(obj, m_objsAttached[i], AcDb::kForRead, true);
		if (es == Acad::eOk) {
			ArxRleUtils::objToClassAndHandleStr(obj, str);
			if (obj->isErased())
				str += _T("  (erased)");

			m_lbObjList.AddString(str);

			obj->close();
		}
    }

	setButtonModes();
}

/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::displayEntList
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjReactorsBase::displayEntList() 
{
	m_entsAttached.setLogicalLength(0);
	m_lbEntList.ResetContent();

	getAttachedEntities(m_entsAttached);

	CString str;
	Acad::ErrorStatus es;
	AcDbObject* obj;

    int len = m_entsAttached.length();
    for (int i=0; i<len; i++) {
		es = acdbOpenAcDbObject(obj, m_entsAttached[i], AcDb::kForRead, true);
		if (es == Acad::eOk) {
			ArxRleUtils::objToClassAndHandleStr(obj, str);

			if (obj->isErased())
				str += _T("  (erased)");

			m_lbEntList.AddString(str);

			obj->close();
		}
    }

	setButtonModes();
}

/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::setButtonModes
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjReactorsBase::setButtonModes()
{
	m_detachSelectedObjsButton.EnableWindow((m_lbObjList.GetSelCount() > 0));
    m_detachSelectedEntsButton.EnableWindow((m_lbEntList.GetSelCount() > 0));

	m_detachEntButton.EnableWindow((m_entsAttached.isEmpty() != true));
}

/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::OnObjAttach
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjReactorsBase::OnObjAttach() 
{
    CString newHandle, str;
    AcDbObjectId objId;

        // see if specified handle is valid
    m_ebHandle.GetWindowText(newHandle);
    if (ArxRleUtils::handleStrToObjId(acdbHostApplicationServices()->workingDatabase(),
					newHandle, objId, false) != Acad::eOk) {
        str.Format(_T("\"%s\" is not a valid handle."), newHandle);
        ArxRleUtils::alertBox(str);
        m_ebHandle.SetSel(0, -1); // reset to select all
        m_ebHandle.SetFocus();
        return;
    }

	AcDbObjectIdArray newObjIds;
	newObjIds.append(objId);

	attachObjReactors(newObjIds);

    m_ebHandle.SetWindowText(_T(""));    // reset edit box to be empty for new handle

	displayObjList();
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::OnEntAttach
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjReactorsBase::OnEntAttach()
{
	attachEntReactors();
	displayEntList();
}

/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::OnEntDetach
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjReactorsBase::OnEntDetach()
{
	detachEntReactors();
	displayEntList();
}

/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::OnEntDetachSelected
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjReactorsBase::OnEntDetachSelected() 
{
	AcDbObjectIdArray selObjIds;

    int count = m_lbEntList.GetSelCount();
    if (count > 0) {
        int* intArray = new int[count];
        if (m_lbEntList.GetSelItems(count, intArray) != LB_ERR) {
            for (int i=0; i<count; i++) {
                selObjIds.append(m_entsAttached[intArray[i]]);
            }
        }
        delete [] intArray;
	}

	detachSelectedEnts(selObjIds);
	displayEntList();
}

/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::OnObjDetachSelected
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjReactorsBase::OnObjDetachSelected() 
{
	AcDbObjectIdArray selObjIds;

    int count = m_lbObjList.GetSelCount();
    if (count > 0) {
        int* intArray = new int[count];
        if (m_lbObjList.GetSelItems(count, intArray) != LB_ERR) {
            for (int i=0; i<count; i++) {
                selObjIds.append(m_objsAttached[intArray[i]]);
            }
        }
        delete [] intArray;
	}

	detachSelectedObjs(selObjIds);
	displayObjList();
}


/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::doStateDbox
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjReactorsBase::doStateDbox(const AcDbObject* obj, LPCTSTR dboxTitle)
{
        // purposely throw away const for testing purposes
    ArxRleUiDlgObjState dbox(acedGetAcadDwgView(), const_cast<AcDbObject*>(obj), dboxTitle);
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxRleUiTdcObjReactorsBase::doStateDbox
**
**  **jma
**
*************************************/

void
ArxRleUiTdcObjReactorsBase::doStateDbox(const AcDbObjectId& objId, LPCTSTR dboxTitle)
{
    ArxRleUiDlgObjState dbox(acedGetAcadDwgView(), objId, dboxTitle);
    dbox.DoModal();
}

