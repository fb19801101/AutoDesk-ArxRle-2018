//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRlePaletteAttribute.h"
#include "ArxRleProfileSection.h"
#include "DbEntity\ArxRleEntityClass.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleApply.h"
#include "AcadUtils\ArxRleSmartPtr.h"
#include "AcadUtils\ArxRleSelSet.h"
#include "AcadUtils\ArxRleRbList.h"
#include "ExEntity\ArxRleTitleLabel.h"
#include "ExEntity\ArxRleBrokenLine.h"
#include "ExEntity\ArxRleLeadDimension.h"
#include "NetPlan\ArxRleNetPlanWork.h"
#include "NetPlan\ArxRleNetPlanWorkStyle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

ArxRlePaletteSet* ArxRlePaletteAttribute::m_pPaletteSet = NULL;
ArxRlePaletteAttribute* ArxRlePaletteAttribute::m_pPaletteAttribute = NULL;
void ArxRlePaletteAttribute::entAttribute()
{
	if(m_pPaletteSet == NULL)
	{
		acedGetAcadFrame()->EnableDocking(CBRS_ALIGN_ANY);
		acedGetAcadFrame()->RecalcLayout();

		m_pPaletteSet = new ArxRlePaletteSet;
		m_pPaletteSet->Create(acedGetAcadFrame(),CRect(0,0,200,400),_T("ʵ������"));
	}

	if(m_pPaletteAttribute == NULL)
	{
		m_pPaletteSet->ClearPalettes();
		m_pPaletteAttribute = new ArxRlePaletteAttribute;
		m_pPaletteAttribute->Create(WS_CHILD | WS_VISIBLE, L"ʵ������", m_pPaletteSet, PS_EDIT_NAME);
		m_pPaletteAttribute->SelEntity(AcDbObjectIdArray());
		m_pPaletteSet->AddPalette(m_pPaletteAttribute);
		m_pPaletteSet->EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
		m_pPaletteSet->RestoreControlBar(AFX_IDW_DOCKBAR_RIGHT);
		acedGetAcadFrame()->ShowControlBar(m_pPaletteSet,TRUE,FALSE);
	}
	else
	{
		if(m_pPaletteAttribute->SelEntity(AcDbObjectIdArray()))
			acedGetAcadFrame()->ShowControlBar(m_pPaletteSet,TRUE,FALSE);
	}
}

IMPLEMENT_DYNAMIC (ArxRlePaletteAttribute, CAdUiPalette)


ArxRlePaletteAttribute::ArxRlePaletteAttribute()
{
	m_cbName = NULL;
	m_bnUpList = NULL;
	m_bnSelect = NULL;
	m_bnUpEntity = NULL;
	m_lstAttrib = NULL;
	m_tipControl = NULL;

	m_autoUpEntity = TRUE;
}

ArxRlePaletteAttribute::~ArxRlePaletteAttribute()
{
	if(m_cbName != NULL) delete m_cbName;
	if(m_bnUpList != NULL) delete m_bnUpList;
	if(m_bnSelect != NULL) delete m_bnSelect;
	if(m_bnUpEntity != NULL) delete m_bnUpEntity;
	if(m_lstAttrib != NULL) delete m_lstAttrib;
	if(m_tipControl != NULL) delete m_tipControl;
}

BEGIN_MESSAGE_MAP(ArxRlePaletteAttribute, CAdUiPalette)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_GETMINMAXINFO()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(ARXRLE_ENTATTRIBUTE_CB_NAME, OnCbnSelchangeCsentsetCbName)
	ON_BN_CLICKED(ARXRLE_ENTATTRIBUTE_BN_UPLIST, OnBnClickedCsentsetBnUpList)
	ON_BN_CLICKED(ARXRLE_ENTATTRIBUTE_BN_SELECT, OnBnClickedCsentsetBnSelect)
	ON_BN_CLICKED(ARXRLE_ENTATTRIBUTE_BN_UPENTITY, OnBnClickedCsentsetBnUpEntity)
END_MESSAGE_MAP()


int ArxRlePaletteAttribute::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAdUiPalette::OnCreate(lpCreateStruct) == -1)
		return -1;

	initControl();

	return 0;
}

BOOL ArxRlePaletteAttribute::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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

	return CAdUiPalette::PreTranslateMessage(pMsg);
}

//- Called by AutoCAD to steal focus from the palette
bool ArxRlePaletteAttribute::CanFrameworkTakeFocus ()
{
	if(m_cbName->GetCount() > 0  && m_autoUpEntity)
		UpdateEntity(m_objList[m_cbName->GetCurSel()]);

	return CAdUiPalette::CanFrameworkTakeFocus();
}

void ArxRlePaletteAttribute::OnSize(UINT nType, int cx, int cy) 
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAdUiPalette::OnSize(nType, cx, cy);

	GetClientRect(&m_rcAttrib);
	CWnd* pWnd = GetDlgItem(ARXRLE_ENTATTRIBUTE_CB_NAME);
	if(pWnd != NULL)
	{
		pWnd->GetWindowRect(&m_rcName);
		ScreenToClient(&m_rcName);
		m_rcAttrib.top = m_rcName.bottom+3;
		m_rcName.right = m_rcAttrib.right-2-m_xBtn*3;
		pWnd->MoveWindow(m_rcName);
		pWnd->Invalidate();
	}

	pWnd = NULL;
	pWnd = GetDlgItem(ARXRLE_ENTATTRIBUTE_LB_ATTRIB);
	if(pWnd != NULL)
	{
		pWnd->MoveWindow(m_rcAttrib);
		pWnd->Invalidate();
	}

	pWnd = NULL;
	pWnd = GetDlgItem(ARXRLE_ENTATTRIBUTE_BN_UPLIST);
	if(pWnd != NULL)
	{
		CRect rc;
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);

		POINT pt;
		pt.x = m_rcName.right+2;
		pt.y = rc.top;
		SIZE se;
		se.cx = m_xBtn; se.cy = m_yBtn;
		rc = CRect(pt,se);
		pWnd->MoveWindow(rc);
		pWnd->Invalidate();
	}

	pWnd = NULL;
	pWnd = GetDlgItem(ARXRLE_ENTATTRIBUTE_BN_SELECT);
	if(pWnd != NULL)
	{
		CRect rc;
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);

		POINT pt;
		pt.x = m_rcName.right+2+m_xBtn;
		pt.y = rc.top;
		SIZE se;
		se.cx = m_xBtn; se.cy = m_yBtn;
		rc = CRect(pt,se);
		pWnd->MoveWindow(rc);
		pWnd->Invalidate();
	}

	pWnd = NULL;
	pWnd = GetDlgItem(ARXRLE_ENTATTRIBUTE_BN_UPENTITY);
	if(pWnd != NULL)
	{
		CRect rc;
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);

		POINT pt;
		pt.x = m_rcName.right+2+2*m_xBtn;
		pt.y = rc.top;
		SIZE se;
		se.cx = m_xBtn; se.cy = m_yBtn;
		rc = CRect(pt,se);
		pWnd->MoveWindow(rc);
		pWnd->Invalidate();
	}
}

void ArxRlePaletteAttribute::OnSizing(UINT fwSide, LPRECT pRect)
{
	CAdUiPalette::OnSizing(fwSide, pRect);

	LPARAM lparam = (pRect->right-pRect->left)<<24|(pRect->bottom-pRect->top)<<8;
	if(m_lstAttrib != NULL)
	{
		if ( ::IsWindow (m_lstAttrib->GetSafeHwnd ()) ) {
			LPARAM lparam = (pRect->right-pRect->left)<<24|(pRect->bottom-pRect->top)<<8;
			m_lstAttrib->SendMessage(WM_SIZING, fwSide, lparam);
		}
	}
}

void ArxRlePaletteAttribute::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 120;
	lpMMI->ptMinTrackSize.y = 200;

	CAdUiPalette::OnGetMinMaxInfo(lpMMI);
}

HBRUSH ArxRlePaletteAttribute::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CAdUiPalette::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	COLORREF clr (RGB(238, 238, 238));
	CBrush* brush = new CBrush;
	brush->CreateSolidBrush(clr);
	pDC->SetBkMode(TRANSPARENT);
	hbr = (HBRUSH)brush->GetSafeHandle();

	return hbr;
}

void ArxRlePaletteAttribute::OnCbnSelchangeCsentsetCbName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_cbName->GetCount() > 0)
		UpdateList(m_objList[m_cbName->GetCurSel()]);
}

void ArxRlePaletteAttribute::OnBnClickedCsentsetBnUpList()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_cbName->GetCount() > 0)
		UpdateList(m_objList[m_cbName->GetCurSel()]);
}

void ArxRlePaletteAttribute::OnBnClickedCsentsetBnSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SelEntity(AcDbObjectIdArray());
}

void ArxRlePaletteAttribute::OnBnClickedCsentsetBnUpEntity()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_autoUpEntity = !m_autoUpEntity;
}

void ArxRlePaletteAttribute::initControl()
{
	if(m_cbName == NULL) m_cbName = new CAcUiComboBox;
	m_cbName->Create(WS_CHILD| CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS | WS_VSCROLL | WS_TABSTOP, CRect(0,0,70,16),this,ARXRLE_ENTATTRIBUTE_CB_NAME);
	m_cbName->SetWindowPos(NULL, 5,5,70,16, SWP_SHOWWINDOW);
	if(m_bnUpList == NULL) m_bnUpList = new CAcUiPickButton;
	m_bnUpList->Create(L"pt", WS_CHILD | BS_OWNERDRAW | WS_TABSTOP, CRect(0,0,16,16), this, ARXRLE_ENTATTRIBUTE_BN_UPLIST);
	m_bnUpList->SetWindowPos(NULL, 75,5,16,16, SWP_SHOWWINDOW);
	if(m_bnSelect == NULL) m_bnSelect = new CAcUiSelectButton;
	m_bnSelect->Create(L"sel", WS_CHILD | BS_OWNERDRAW | WS_TABSTOP,CRect(0,0,16,16), this, ARXRLE_ENTATTRIBUTE_BN_SELECT);
	m_bnSelect->SetWindowPos(NULL, 91,5,16,16, SWP_SHOWWINDOW);
	if(m_bnUpEntity == NULL) m_bnUpEntity = new CAcUiPickButton;
	m_bnUpEntity->Create(L"clr", WS_CHILD | BS_OWNERDRAW | WS_TABSTOP,CRect(0,0,16,16), this, ARXRLE_ENTATTRIBUTE_BN_UPENTITY);
	m_bnUpEntity->SetWindowPos(NULL, 107,5,16,16, SWP_SHOWWINDOW);

	m_bnUpList->AutoLoad();
	m_bnSelect->AutoLoad();
	m_bnUpEntity->AutoLoad();

	if(m_tipControl == NULL) m_tipControl = new CToolTipCtrl;
	if (FALSE == m_tipControl->Create(this)) return;
	m_tipControl->Activate(TRUE);
	m_tipControl->AddTool(m_cbName,L"ʵ������");
	m_tipControl->AddTool(m_bnUpList,L"��������");
	m_tipControl->AddTool(m_bnSelect,L"ѡ��ʵ��");
	m_tipControl->AddTool(m_bnUpEntity,L"����ʵ��");

	GetClientRect(&m_rcAttrib);
	CWnd* pWnd = GetDlgItem(ARXRLE_ENTATTRIBUTE_CB_NAME);
	if(pWnd != NULL) pWnd->GetClientRect(&m_rcName);
	pWnd = GetDlgItem(ARXRLE_ENTATTRIBUTE_BN_UPLIST);
	CRect rc;
	if(pWnd != NULL) pWnd->GetClientRect(&rc);
	m_xBtn = rc.Width(); m_yBtn = rc.Height();
	m_rcAttrib.top = m_rcName.bottom+3;
	if(m_lstAttrib == NULL) m_lstAttrib = new ArxRleAttributeList;
	m_lstAttrib->Create(LBS_NOTIFY | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,m_rcAttrib, this , ARXRLE_ENTATTRIBUTE_LB_ATTRIB);

	m_items.SetCommonItems(5);
}

void ArxRlePaletteAttribute::updateControl()
{
	CString app = GetModulePath(ArxRleApp::m_hInstance);
	CString ini = app + L"\\" + L"config.ini";
	if (FileExist(ini) == TRUE)
	{
		ArxRleProfileSection * profile = new ArxRleProfileSection();
		CMapStringToString csMap;
		profile->GetAllLines(ini, csMap);

		ArxRleAttributeListItem* pItem;
		// Update CPropertyList item data
		for (int i = 0; i < m_lstAttrib->GetCount(); i++)
		{
			pItem = (ArxRleAttributeListItem*)m_lstAttrib->GetItemDataPtr(i);
			CString key = pItem->m_curKey;
			CString val = pItem->m_curValue;
			csMap.Lookup(key.MakeLower(),pItem->m_curValue);
		}
		csMap.RemoveAll();
	}
}

void ArxRlePaletteAttribute::SetObjId(int index, AcDbObjectId& objId)
{
	if(m_objList.length() < index+1)
		m_objList.append(objId);
	else
		m_objList[index] = objId;
}

AcDbObjectId ArxRlePaletteAttribute::GetObjId(int index) const
{
	if(m_objList.length() < index+1)
		return m_objList[0];
	else
		return m_objList[index];
}

void ArxRlePaletteAttribute::SetItemHeight(double height)
{
	m_lstAttrib->SetItemHeight(height);
}

double ArxRlePaletteAttribute::GetItemHeight() const
{
	return m_lstAttrib->GetItemHeight();
}

BOOL ArxRlePaletteAttribute::SelEntity(AcDbObjectIdArray& objs)
{
	m_objList = objs;
	if(m_objList.isEmpty())
	{
		ArxRleSelSet ss;
		if(ss.userSelect() == ArxRleSelSet::kSelected)
		{ 
			m_objList.removeAll();
			ss.asArray(m_objList);
		}
	}

	if(m_objList.isEmpty()) return FALSE;

	if(m_cbName->GetCount() > 0)
		m_cbName->ResetContent();
	ArxRleString entName;
	for(int i=0; i<m_objList.length(); i++)
	{
		AcDbEntity* ent;
		Acad::ErrorStatus es = OpenEntity(ent, m_objList[i], AcDb::kForWrite);		// might have passed in erased ones
		if(es == Acad::eOk)
		{
			if(ArxRleString(ent->isA()->name()) != entName)
				m_cbName->AddString(ent->isA()->name());
			entName = ent->isA()->name();
			CloseEntity(ent);
		}
	}

	if(m_cbName->GetCount() > 0)
	{
		m_cbName->SetCurSel(0);
		UpdateList(m_objList[0]);
	}

	return TRUE;
}

BOOL ArxRlePaletteAttribute::UpdateEntity(AcDbObjectId& objId)
{
	AcDbEntity* ent;
	Acad::ErrorStatus es = OpenEntity(ent, objId, AcDb::kForWrite);		// might have passed in erased ones
	if(es == Acad::eOk) {
		ArxRleString layer(m_items.GetValValue(1));
		ent->setLayer(layer.w_ptr());
		COLORREF clr = m_items.GetTxtValColor(2);
		ent->setColor(RefColorToAcCmColor(clr));
		ArxRleString lt(m_items.GetValValue(3));
		ent->setLinetype(lt);
		ent->setLinetypeScale(_tstof(m_items.GetValValue(4)));
		ent->setLineWeight((AcDb::LineWeight)_tstoi(m_items.GetValValue(5)));

		// �ж������������ʵ�����ҵ��Զ���ʵ�壬������޸Ĳ���
		if(ent->isKindOf(ArxRleTitleLabel::desc())) {
			ArxRleTitleLabel* pTitleLabel = ArxRleTitleLabel::cast(ent);

			pTitleLabel->setPoint(CPt3d(_tstof(m_items.GetValue(0)),_tstof(m_items.GetValue(1)),_tstof(m_items.GetValue(2))), CPt3d(_tstof(m_items.GetValue(3)),_tstof(m_items.GetValue(4)),_tstof(m_items.GetValue(5))));
			pTitleLabel->setLabel(m_items.GetValue(6),m_items.GetValue(7),_tstof(m_items.GetValue(9)));
			pTitleLabel->setTextStyle(m_items.GetValue(8));
		}
		else if(ent->isKindOf(ArxRleBrokenLine::desc())) {
			ArxRleBrokenLine* pBrokenLine = ArxRleBrokenLine::cast(ent);

			pBrokenLine->setPointBegin(CPt3d(_tstof(m_items.GetValue(0)),_tstof(m_items.GetValue(1)),_tstof(m_items.GetValue(2))));
			pBrokenLine->setPointEnd(CPt3d(_tstof(m_items.GetValue(3)),_tstof(m_items.GetValue(4)),_tstof(m_items.GetValue(5))));
			pBrokenLine->setBrokenSize(_tstof(m_items.GetValue(6)));
		}
		else if(ent->isKindOf(ArxRleLeadDimension::desc())) {
			ArxRleLeadDimension* pLeadDim = ArxRleLeadDimension::cast(ent);

			pLeadDim->setPoint(CPt3d(_tstof(m_items.GetValue(0)),_tstof(m_items.GetValue(1)),_tstof(m_items.GetValue(2))), CPt3d(_tstof(m_items.GetValue(3)),_tstof(m_items.GetValue(4)),_tstof(m_items.GetValue(5))), CPt3d(_tstof(m_items.GetValue(6)),_tstof(m_items.GetValue(7)),_tstof(m_items.GetValue(8))));
			pLeadDim->setLabel(m_items.GetValue(9),m_items.GetValue(10),_tstof(m_items.GetValue(12)));
			pLeadDim->setTextStyle(m_items.GetValue(11));
		}
		else if(ent->isKindOf(ArxRleNetPlanWork::desc())) {
			ArxRleNetPlanWork* pNetPlanWork = ArxRleNetPlanWork::cast(ent);

			pNetPlanWork->setPointBegin(CPt3d(_tstof(m_items.GetValue(0)),_tstof(m_items.GetValue(1)),_tstof(m_items.GetValue(2))));
			pNetPlanWork->setPointEnd(CPt3d(_tstof(m_items.GetValue(3)),_tstof(m_items.GetValue(4)),_tstof(m_items.GetValue(5))));
			pNetPlanWork->setWorkStyle(m_items.GetValue(6));
			pNetPlanWork->setLabelBegin(m_items.GetValue(7));
			pNetPlanWork->setLabelEnd(m_items.GetValue(8));
			pNetPlanWork->setLabelUp(m_items.GetValue(9));
			pNetPlanWork->setLabelDown(m_items.GetValue(10));
			pNetPlanWork->setWorkDes(m_items.GetValue(11));
			pNetPlanWork->setResMens(_tstof(m_items.GetValue(12)));
			pNetPlanWork->setResTools(_tstof(m_items.GetValue(13)));
			pNetPlanWork->setResMoney(_tstof(m_items.GetValue(14)));
			pNetPlanWork->setWorkCode(_tstol(m_items.GetValue(15)));
		}

		CloseEntity(ent);

		return TRUE;
	}

	return FALSE;
}

BOOL ArxRlePaletteAttribute::UpdateList(AcDbObjectId& objId)
{
	m_items.DelItems();

	AcDbEntity* ent;
	Acad::ErrorStatus es = OpenEntity(ent, objId, AcDb::kForRead);		// might have passed in erased ones
	if(es == Acad::eOk) {
		m_items.AddSeparator(L"����");
		m_items.AddLayerValue(L"ͼ��", ent->layer());
		m_items.AddColorValue(L"��ɫ", AcCmColorToRefColor(ent->color(), ent->layerId()));
		m_items.AddLineTypeValue(L"����", ent->linetype());
		m_items.AddEditValue(L"����", ToString(ent->linetypeScale()));
		m_items.AddLineWeightValue(L"���", ent->lineWeight());

		// �ж������������ʵ�����ҵ��Զ���ʵ�壬������޸Ĳ���
		if(ent->isKindOf(ArxRleTitleLabel::desc())) {
			ArxRleTitleLabel* pTitleLabel = ArxRleTitleLabel::cast(ent);

			m_items.AddSeparator(L"����ͼ��");
			m_items.AddEditValue(L"��� X", pTitleLabel->getPointBegin().sPt(0));
			m_items.AddEditValue(L"��� Y", pTitleLabel->getPointBegin().sPt(1));
			m_items.AddEditValue(L"��� Z", pTitleLabel->getPointBegin().sPt(2));
			m_items.AddEditValue(L"�յ� X", pTitleLabel->getPointEnd().sPt(0));
			m_items.AddEditValue(L"�յ� Y", pTitleLabel->getPointEnd().sPt(1));
			m_items.AddEditValue(L"�յ� Z", pTitleLabel->getPointEnd().sPt(2));
			m_items.AddSeparator(L"��������");
			m_items.AddEditValue(L"�����ı�", pTitleLabel->getLabelUp());
			m_items.AddEditValue(L"�����ı�", pTitleLabel->getLabelDown());
			m_items.AddTextStyleValue(L"�ı���ʽ", pTitleLabel->getTextStyle());
			m_items.AddEditValue(L"�ı��߶�", ToString(pTitleLabel->getTextSize()));
			m_items.AddEditValue(L"�ı��Ƕ�", ToString(pTitleLabel->getTextAngle()));
		}
		else if(ent->isKindOf(ArxRleBrokenLine::desc())) {
			ArxRleBrokenLine* pBrokenLine = ArxRleBrokenLine::cast(ent);

			m_items.AddSeparator(L"����ͼ��");
			m_items.AddEditValue(L"��� X", pBrokenLine->getPointBegin().sPt(0));
			m_items.AddEditValue(L"��� Y", pBrokenLine->getPointBegin().sPt(1));
			m_items.AddEditValue(L"��� Z", pBrokenLine->getPointBegin().sPt(2));
			m_items.AddEditValue(L"�յ� X", pBrokenLine->getPointEnd().sPt(0));
			m_items.AddEditValue(L"�յ� Y", pBrokenLine->getPointEnd().sPt(1));
			m_items.AddEditValue(L"�յ� Z", pBrokenLine->getPointEnd().sPt(2));
			m_items.AddSeparator(L"��������");
			m_items.AddEditValue(L"��С H", ToString(pBrokenLine->getBrokenSize()));
		}
		else if(ent->isKindOf(ArxRleLeadDimension::desc())) {
			ArxRleLeadDimension* pLeadDim = ArxRleLeadDimension::cast(ent);

			m_items.AddSeparator(L"����ͼ��");
			m_items.AddEditValue(L"���� X", pLeadDim->getPointBase().sPt(0));
			m_items.AddEditValue(L"���� Y", pLeadDim->getPointBase().sPt(1));
			m_items.AddEditValue(L"���� Z", pLeadDim->getPointBase().sPt(2));
			m_items.AddEditValue(L"��� X", pLeadDim->getPointBegin().sPt(0));
			m_items.AddEditValue(L"��� Y", pLeadDim->getPointBegin().sPt(1));
			m_items.AddEditValue(L"��� Z", pLeadDim->getPointBegin().sPt(2));
			m_items.AddEditValue(L"�յ� X", pLeadDim->getPointEnd().sPt(0));
			m_items.AddEditValue(L"�յ� Y", pLeadDim->getPointEnd().sPt(1));
			m_items.AddEditValue(L"�յ� Z", pLeadDim->getPointEnd().sPt(2));
			m_items.AddSeparator(L"��������");
			m_items.AddEditValue(L"�����ı�", pLeadDim->getLabelUp());
			m_items.AddEditValue(L"�����ı�", pLeadDim->getLabelDown());
			m_items.AddTextStyleValue(L"�ı���ʽ", pLeadDim->getTextStyle());
			m_items.AddEditValue(L"�ı��߶�", ToString(pLeadDim->getTextSize()));
			m_items.AddEditValue(L"�ı��Ƕ�", ToString(pLeadDim->getTextAngle()));
		}
		else if(ent->isKindOf(ArxRleNetPlanWork::desc())) {
			ArxRleNetPlanWork* pNetPlanWork = ArxRleNetPlanWork::cast(ent);

			m_items.AddSeparator(L"����ͼ��");
			m_items.AddEditValue(L"��� X", pNetPlanWork->getPointBegin().sPt(0));
			m_items.AddEditValue(L"��� Y", pNetPlanWork->getPointBegin().sPt(1));
			m_items.AddEditValue(L"��� Z", pNetPlanWork->getPointBegin().sPt(2));
			m_items.AddEditValue(L"�յ� X", pNetPlanWork->getPointEnd().sPt(0));
			m_items.AddEditValue(L"�յ� Y", pNetPlanWork->getPointEnd().sPt(1));
			m_items.AddEditValue(L"�յ� Z", pNetPlanWork->getPointEnd().sPt(2));
			m_items.AddSeparator(L"��������");
			m_items.AddWorkStyleValue(L"������ʽ", pNetPlanWork->getWorkStyle());
			m_items.AddEditValue(L"�����", pNetPlanWork->getLabelBegin());
			m_items.AddEditValue(L"�յ���", pNetPlanWork->getLabelEnd());
			m_items.AddEditValue(L"��������", pNetPlanWork->getLabelUp());
			m_items.AddEditValue(L"������ʱ", pNetPlanWork->getLabelDown());
			m_items.AddEditValue(L"��������", pNetPlanWork->getWorkDes());
			m_items.AddSeparator(L"����Ҫ��");
			m_items.AddEditValue(L"����Ҫ��", ToString(pNetPlanWork->getResMens()));
			m_items.AddEditValue(L"�豸Ҫ��", ToString(pNetPlanWork->getResTools()));
			m_items.AddEditValue(L"�ʽ�Ҫ��", ToString(pNetPlanWork->getResMoney()));
			m_items.AddSeparator(L"�����ϵ");
			m_items.AddEditValue(L"������", ToString(pNetPlanWork->getWorkCode()));
			if(!pNetPlanWork->getBindWorkRefId().isNull())
				m_items.AddEditValue(L"���ӹ���", pNetPlanWork->getBindWorkRef());
		}

		CloseEntity(ent);

		m_lstAttrib->DelItems();
		m_items.Sort();
		for(int i=0; i<m_items.GetItemCount(); i++)
		{
			ArxRleAttributeListItem *pItem = m_items[i];
			m_lstAttrib->AddPropItem(pItem);
		}

		return TRUE;
	}

	return FALSE;
}