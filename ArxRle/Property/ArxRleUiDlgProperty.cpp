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

#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleUiDlgProperty.h"
#include "App/ArxRleProfileSection.h"
#include "DbEntity\ArxRleEntityClass.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleApply.h"
#include "AcadUtils\ArxRleSmartPtr.h"
#include "AcadUtils\ArxRleSelSet.h"
#include "AcadUtils\ArxRleRbList.h"
#include "ExEntity\ArxRleTitleLabel.h"
#include "ExEntity\ArxRleBrokenLine.h"
#include "NetPlan\ArxRleNetPlanWork.h"
#include "NetPlan\ArxRleNetPlanWorkStyle.h"


void entProperty()
{
	ArxRleUiDlgProperty dlg(acedGetAcadDwgView());
	dlg.DoModal();

}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgProperty dialog

IMPLEMENT_DYNAMIC(ArxRleUiDlgProperty, CAcUiDialog)

ArxRleUiDlgProperty::ArxRleUiDlgProperty(CWnd* pParent /*=NULL*/)
	: CAcUiDialog(ArxRleUiDlgProperty::IDD)
{
	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);
	m_tipControl = NULL;
}

ArxRleUiDlgProperty::~ArxRleUiDlgProperty()
{
	if(m_tipControl != NULL) delete m_tipControl;
}

void ArxRleUiDlgProperty::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);

	DDX_Control(pDX, ARXRLE_ENTPROPERTY_CB_NAME, m_cbName);
	DDX_Control(pDX, ARXRLE_ENTPROPERTY_BN_UPLIST, m_bnUpList);
	DDX_Control(pDX, ARXRLE_ENTPROPERTY_BN_SELECT, m_bnSelect);
	DDX_Control(pDX, ARXRLE_ENTPROPERTY_BN_UPENTITY, m_bnUpEntity);
	DDX_Control(pDX, ARXRLE_ENTPROPERTY_LB_ATTRIB, m_lbProperty);
}

BEGIN_MESSAGE_MAP(ArxRleUiDlgProperty, CAcUiDialog)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(ARXRLE_ENTPROPERTY_CB_NAME, OnCbnSelchangeCsentsetCbName)
	ON_BN_CLICKED(ARXRLE_ENTPROPERTY_BN_UPLIST, OnBnClickedCsentsetBnUpList)
	ON_BN_CLICKED(ARXRLE_ENTPROPERTY_BN_SELECT, OnBnClickedCsentsetBnSelect)
	ON_BN_CLICKED(ARXRLE_ENTPROPERTY_BN_UPENTITY, OnBnClickedCsentsetBnUpEntity)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgProperty message handlers

BOOL ArxRleUiDlgProperty::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	SetIcon(m_hIcon,TRUE);
	SetIcon(m_hIcon,FALSE);

	m_bnUpList.AutoLoad();
	m_bnSelect.AutoLoad();
	m_bnUpEntity.AutoLoad();

	if(m_tipControl == NULL) m_tipControl = new CToolTipCtrl;
	if (FALSE == m_tipControl->Create(this)) return FALSE;
	m_tipControl->Activate(TRUE);
	m_tipControl->AddTool(&m_cbName,L"实体名称");
	m_tipControl->AddTool(&m_bnUpList,L"更新数据");
	m_tipControl->AddTool(&m_bnSelect,L"选择实体");
	m_tipControl->AddTool(&m_bnUpEntity,L"更新实体");

	m_workManager.SetData(&m_data);
	m_lbProperty.SetPropertyItemManager(&m_workManager);

	CRect rc;
	m_bnUpList.GetClientRect(&rc);
	m_xBtn = rc.Width(); m_yBtn = rc.Height();

	return TRUE;
}

BOOL ArxRleUiDlgProperty::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->hwnd == GetFocus()->m_hWnd)
		{
			switch (pMsg->wParam)
			{
			case VK_RETURN:
				SetFocus();
				return TRUE;
			case VK_SPACE:
				SetFocus();
				return TRUE;
			case VK_ESCAPE:
				SetFocus();
				return TRUE;
			}
		}
	}

	return CAcUiDialog::PreTranslateMessage(pMsg);
}

void ArxRleUiDlgProperty::OnSize(UINT nType, int cx, int cy) 
{
	CAcUiDialog::OnSize(nType, cx, cy);

	GetWindowRect(&m_rcProperty);
	ScreenToClient(m_rcProperty);
	if(m_cbName.GetSafeHwnd())
	{
		m_cbName.GetWindowRect(&m_rcName);
		m_cbName.ScreenToClient(m_rcName);
		m_rcProperty.top = m_rcName.bottom+3;
		m_rcName.right = m_rcProperty.right-2-m_xBtn*3;
		m_cbName.MoveWindow(m_rcName);
	}

	if(m_lbProperty.GetSafeHwnd())
	{
		m_lbProperty.MoveWindow(m_rcProperty);
	}

	if(m_bnUpList.GetSafeHwnd())
	{
		CRect rc;
		m_bnUpList.GetWindowRect(&rc);
		m_bnUpList.ScreenToClient(rc);

		POINT pt;
		pt.x = m_rcName.right+2;
		pt.y = rc.top;
		SIZE se;
		se.cx = m_xBtn; se.cy = m_yBtn;
		rc = CRect(pt,se);
		m_bnUpList.MoveWindow(rc);
	}

	if(m_bnSelect.GetSafeHwnd())
	{
		CRect rc;
		m_bnSelect.GetWindowRect(&rc);
		m_bnSelect.ScreenToClient(rc);

		POINT pt;
		pt.x = m_rcName.right+2+m_xBtn;
		pt.y = rc.top;
		SIZE se;
		se.cx = m_xBtn; se.cy = m_yBtn;
		rc = CRect(pt,se);
		m_bnSelect.MoveWindow(rc);
	}

	if(m_bnUpEntity.GetSafeHwnd())
	{
		CRect rc;
		m_bnUpEntity.GetWindowRect(&rc);
		m_bnUpEntity.ScreenToClient(rc);

		POINT pt;
		pt.x = m_rcName.right+2+2*m_xBtn;
		pt.y = rc.top;
		SIZE se;
		se.cx = m_xBtn; se.cy = m_yBtn;
		rc = CRect(pt,se);
		m_bnUpEntity.MoveWindow(rc);
	}
}

void ArxRleUiDlgProperty::OnCbnSelchangeCsentsetCbName()
{
	if(m_cbName.GetCount() > 0)
		m_workManager.SetObjId(m_objList[m_cbName.GetCurSel()]);
	else
		m_workManager.SetObjId(m_objList[0]);

	m_workManager.UpdateList();
}

void ArxRleUiDlgProperty::OnBnClickedCsentsetBnUpEntity()
{
	if(m_cbName.GetCount() > 0)
		m_workManager.SetObjId(m_objList[m_cbName.GetCurSel()]);
	else
		m_workManager.SetObjId(m_objList[0]);

	m_workManager.UpdateList();
}

void ArxRleUiDlgProperty::OnBnClickedCsentsetBnSelect()
{
	//隐藏对话框把控制权交给AutoCad
	BeginEditorCommand();

	if(SelEntity())
	{
		//如果点有效，继续执行
		CompleteEditorCommand();
		m_workManager.UpdateList();
	}
	else
		CancelEditorCommand();
}

void ArxRleUiDlgProperty::OnBnClickedCsentsetBnUpList()
{
	m_workManager.UpdateEntity();
}

BOOL ArxRleUiDlgProperty::SelEntity()
{
	ArxRleSelSet ss;
	m_objList.removeAll();
	if(ss.userSelect() == ArxRleSelSet::kSelected) { 
		ss.asArray(m_objList);
		if(!m_objList.isEmpty())
		{
			m_cbName.ResetContent();
			ArxRleString entName;
			BOOL bAdd = FALSE;

			for(int i=0; i<m_objList.length(); i++) {
				AcDbEntity* ent;
				Acad::ErrorStatus es = OpenEntity(ent, m_objList[i], AcDb::kForWrite);		// might have passed in erased ones
				if(es == Acad::eOk) {
					if(ArxRleString(ent->isA()->name()) != entName)
						m_cbName.AddString(ent->isA()->name());

					entName = ent->isA()->name();
					CloseEntity(ent);
				}

				m_cbName.SetCurSel(0);
			}

			if(m_cbName.GetCount() > 0)
				m_workManager.SetObjId(m_objList[m_cbName.GetCurSel()]);
			else
				m_workManager.SetObjId(m_objList[0]);
			return TRUE;
		}
	}
	return FALSE;
}