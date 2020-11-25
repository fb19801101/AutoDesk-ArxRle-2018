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

#include "ArxRleUiDlgObjState.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiDlgObjState::ArxRleUiDlgObjState
**
**  **jma
**
*************************************/

ArxRleUiDlgObjState::ArxRleUiDlgObjState(CWnd* parent, const AcDbObjectId& objId, LPCTSTR dboxTitle)
:   CAcUiDialog(ArxRleUiDlgObjState::IDD, parent, ArxRleApp::getApp()->dllInstance()),
    m_obj(NULL),
    m_objId(objId),
    m_wasOpenOnConstruct(false),
    m_dboxTitle(dboxTitle),
	m_bUpgradedFromNotify(false)
{
    //{{AFX_DATA_INIT(ArxRleUiDlgObjState)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

    SetPersistency(FALSE);
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::ArxRleUiDlgObjState
**
**  **jma
**
*************************************/

ArxRleUiDlgObjState::ArxRleUiDlgObjState(CWnd* parent, AcDbObject* obj, LPCTSTR dboxTitle)
:   CAcUiDialog(ArxRleUiDlgObjState::IDD, parent, ArxRleApp::getApp()->dllInstance()),
    m_obj(obj),
    m_objId(obj->objectId()),
    m_wasOpenOnConstruct(true),
    m_dboxTitle(dboxTitle)
{
    //{{AFX_DATA_INIT(ArxRleUiDlgObjState)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::~ArxRleUiDlgObjState
**
**  **jma
**
*************************************/

ArxRleUiDlgObjState::~ArxRleUiDlgObjState()
{
    if (m_wasOpenOnConstruct == false) {
            // if left open, the next person to try to access it
            // fails miserably, so try to close it all the way
        if (m_obj != NULL) {
            Acad::ErrorStatus es = Acad::eOk;
            while (!m_obj->isReallyClosing()) {
                es = m_obj->cancel();
                if (es == Acad::eCloseWasNotifying)
                    return;
                if (es != Acad::eOk)
                    ArxRleUtils::rxErrorAlert(es);
                else
                    acutPrintf(_T("\nCalling obj->cancel()."));
            }
            es = m_obj->cancel();
            if (es == Acad::eCloseWasNotifying)
                return;

            if (es != Acad::eOk)
                ArxRleUtils::rxErrorAlert(es);
            else
                acutPrintf(_T("\nCalling obj->cancel()."));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgObjState)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgObjState message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgObjState, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxRleUiDlgObjState)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_CLOSE, OnCloseObj)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_CANCEL, OnCancelObj)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_CLOSE_PAGE, OnCloseAndPageObj)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_DOWNGRADE_TO_N, OnDowngradeToNotify)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_DOWNGRADE_W, OnDowngradeWrite)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_ERASE, OnEraseObj)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_UNERASE, OnUneraseObj)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_MODIFY, OnModifyObj)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_NOTIFY, OnOpenForNotify)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_READ, OnOpenForRead)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_UPGRADE_FROM_N, OnUpgradeFromNotify)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_UPGRADE_TO_W, OnUpgradeToWrite)
	ON_BN_CLICKED(ARXRLE_RXSTATE_BN_WRITE, OnOpenForWrite)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgObjState message handlers

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgObjState::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();

    if (m_dboxTitle)
        SetWindowText(m_dboxTitle);
    
    display();
    
    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::objIsOpen
**
**  **jma
**
*************************************/

bool
ArxRleUiDlgObjState::objIsOpen()
{
    if (m_obj == NULL) {
        ArxRleUtils::stopAlertBox(_T("The object is not open."));
        return false;
    }
    else
        return true;
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::objIsOpenForWrite
**
**  **jma
**
*************************************/

bool
ArxRleUiDlgObjState::objIsOpenForWrite()
{
    if (!objIsOpen())
        return false;

    if (m_obj->isWriteEnabled())
        return true;
    else {
        ArxRleUtils::stopAlertBox(_T("The object must be open for write."));
        return false;
    }
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::open
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::open(AcDb::OpenMode openMode)
{
    Acad::ErrorStatus es;
    es = acdbOpenObject(m_obj, m_objId, openMode);
    if (es != Acad::eOk)
        ArxRleUtils::rxErrorAlert(es);
    else {
        if (openMode == AcDb::kForRead)
			SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Opened For Read"));
		else if (openMode == AcDb::kForWrite)
			SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Opened For Write"));
		else
			SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Opened For Notify"));
    }
    display();
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::doErase
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::doErase(bool reallyErase)
{
    if (!objIsOpenForWrite())
        return;

    Acad::ErrorStatus es;
    es = m_obj->erase(reallyErase);
    if (es != Acad::eOk)
        ArxRleUtils::rxErrorAlert(es);
    else {
        if (reallyErase == Adesk::kTrue)
			SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Erased"));
		else
			SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Un-Erased"));
    }
    display();
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::display
**      display the current state of the entity
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::display()
{
    CString str;
    LPCTSTR unknown = _T("N/A");

    if ((m_obj != NULL) && m_obj->isReadEnabled()){
		SetDlgItemText(ARXRLE_RXSTATE_EB_CLASS, ArxRleUtils::objToClassStr(m_obj));
		SetDlgItemText(ARXRLE_RXSTATE_EB_NEWOBJ, ArxRleUtils::booleanToStr(m_obj->isNewObject(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_READ_ENABLED, ArxRleUtils::booleanToStr(m_obj->isReadEnabled(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_WRITE_ENABLED, ArxRleUtils::booleanToStr(m_obj->isWriteEnabled(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_NOTIFY_ENABLED, ArxRleUtils::booleanToStr(m_obj->isNotifyEnabled(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_MODIFIED, ArxRleUtils::booleanToStr(m_obj->isModified(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_MOD_XDATA, ArxRleUtils::booleanToStr(m_obj->isModifiedXData(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_MOD_GRAPHICS, ArxRleUtils::booleanToStr(m_obj->isModifiedGraphics(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_PROXY, ArxRleUtils::booleanToStr(m_obj->isAProxy(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_TRANS_RESIDENT, ArxRleUtils::booleanToStr(m_obj->isTransactionResident(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_ERASED, ArxRleUtils::booleanToStr(m_obj->isErased(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_ERASE_TOGGLED, ArxRleUtils::booleanToStr(m_obj->isEraseStatusToggled(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_NOTIFYING, ArxRleUtils::booleanToStr(m_obj->isNotifying(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_UNDOING, ArxRleUtils::booleanToStr(m_obj->isUndoing(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_CANCELLING, ArxRleUtils::booleanToStr(m_obj->isCancelling(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_REALLY_CLOSING, ArxRleUtils::booleanToStr(m_obj->isReallyClosing(), str));
		SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Object pointer is valid"));
	}
	else {
		SetDlgItemText(ARXRLE_RXSTATE_EB_CLASS, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_NEWOBJ, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_READ_ENABLED, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_WRITE_ENABLED, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_NOTIFY_ENABLED, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_MODIFIED, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_MOD_XDATA, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_MOD_GRAPHICS, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_PROXY, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_TRANS_RESIDENT, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_ERASED, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_ERASE_TOGGLED, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_NOTIFYING, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_UNDOING, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_CANCELLING, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_REALLY_CLOSING, unknown);
		SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Object pointer not valid, use object Id"));
    }
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnOpenForRead
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnOpenForRead() 
{
    open(AcDb::kForRead);
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnOpenForWrite
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnOpenForWrite() 
{
    open(AcDb::kForWrite);
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnOpenForNotify
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnOpenForNotify() 
{
    open(AcDb::kForNotify);
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnModifyObj
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnModifyObj() 
{
    if (!objIsOpenForWrite())
        return;

    AcDbEntity* entPtr;
    if ((entPtr = AcDbEntity::cast(m_obj)) == NULL) {
        ArxRleUtils::stopAlertBox(_T("This test requires an AcDbEntity."));
        return;
    }

    Acad::ErrorStatus es;
    int color = entPtr->colorIndex();
    if (color >= 255)
        es = entPtr->setColorIndex(1);
    else
        es = entPtr->setColorIndex(color+1);

    if (es != Acad::eOk)
        ArxRleUtils::rxErrorAlert(es);
    else
        ArxRleUtils::alertBox(_T("The color index was incremented as a test for modification."));

    display();
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnUpgradeToWrite
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnUpgradeToWrite() 
{
    if (!objIsOpen())
        return;

    Acad::ErrorStatus es;
    es = m_obj->upgradeOpen();
    if (es != Acad::eOk)
        ArxRleUtils::rxErrorAlert(es);
    else
        SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Upgraded To Write"));

    display();
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnDowngradeWrite
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnDowngradeWrite() 
{
    if (!objIsOpen())
        return;

    Acad::ErrorStatus es;
    es = m_obj->downgradeOpen();
    if (es != Acad::eOk)
        ArxRleUtils::rxErrorAlert(es);
    else
        SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Downgraded From Write"));

    display();
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnUpgradeFromNotify
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnUpgradeFromNotify() 
{
    if (!objIsOpen())
        return;

    Acad::ErrorStatus es;
    es = m_obj->upgradeFromNotify(m_bWasWritable);
    if (es != Acad::eOk)
        ArxRleUtils::rxErrorAlert(es);
	else {
        SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Upgraded From Notify"));
		m_bUpgradedFromNotify =true ;
	}

    display();
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnDowngradeToNotify
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnDowngradeToNotify() 
{
    if (!objIsOpen())
        return;

	if (!m_bUpgradedFromNotify)
	{
		ArxRleUtils::alertBox(_T("This function must have been preceded by a call to upgradeFromNotify()."));
		return ;
	}
	m_bUpgradedFromNotify =false ;

    Acad::ErrorStatus es;
    es = m_obj->downgradeToNotify(m_bWasWritable);
	if (es != Acad::eOk)
        ArxRleUtils::rxErrorAlert(es);
    else
        SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Downgraded To Notify"));

    display();
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnCancelObj
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnCancelObj() 
{
    if (!objIsOpen())
        return;

    Adesk::Boolean totallyClosed = m_obj->isReallyClosing();
    Adesk::Boolean wasModified = m_obj->isModified();

    Acad::ErrorStatus es;
    es = m_obj->cancel();
    if (es != Acad::eOk)
        ArxRleUtils::rxErrorAlert(es);
    else {
        if (wasModified)
			SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Cancelled, modifications ignored"));
		else
			SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Cancelled"));
    }

    if (totallyClosed)
        m_obj = NULL;

    display();
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnCloseObj
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnCloseObj() 
{
    if (!objIsOpen())
        return;

	Adesk::Boolean totallyClosed = m_obj->isReallyClosing();
    Adesk::Boolean wasModified = m_obj->isModified();

    Acad::ErrorStatus es;
    es = m_obj->close();
    if (es != Acad::eOk)
        ArxRleUtils::rxErrorAlert(es);
    else {
        if (wasModified)
			SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Closed, modifications written to database"));
		else
			SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Closed"));
    }

    if (totallyClosed)
        m_obj = NULL;

    display();
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnCloseAndPageObj
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnCloseAndPageObj() 
{
    if (!objIsOpen())
        return;

	Adesk::Boolean totallyClosed = m_obj->isReallyClosing();
    Adesk::Boolean wasModified = m_obj->isModified();

    Acad::ErrorStatus es;
    es = m_obj->closeAndPage();
    if (es != Acad::eOk)
        ArxRleUtils::rxErrorAlert(es);
    else {
        if (wasModified)
			SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Closed, modifications written to database"));
		else
			SetDlgItemText(ARXRLE_RXSTATE_EB_ERRMSG, _T("Closed"));
    }

    if (totallyClosed)
        m_obj = NULL;

    display();
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnEraseObj
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnEraseObj() 
{
    doErase(true);
}

/****************************************************************************
**
**  ArxRleUiDlgObjState::OnUneraseObj
**
**  **jma
**
*************************************/

void
ArxRleUiDlgObjState::OnUneraseObj() 
{
    doErase(false);
}



