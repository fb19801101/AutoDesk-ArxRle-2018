// ArxRlePropertyView.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRlePropertyView.h"
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

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyView

ArxRlePropertyView::ArxRlePropertyView()
{
	m_bUpdate = FALSE;
}

ArxRlePropertyView::~ArxRlePropertyView()
{
}


BEGIN_MESSAGE_MAP(ArxRlePropertyView, ArxRlePaneView)
	//{{AFX_MSG_MAP(ArxRlePropertyView)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_MESSAGE(XTPWM_PROPERTYGRID_NOTIFY, OnGridNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyView message handlers

CWnd* ArxRlePropertyView::OnCreateView()
{
	if (m_wndPropertyGrid.Create(CRect(), this, 10))
	{
		//m_wndPropertyGrid.SetOwner(GetTopLevelFrame());
		m_wndPropertyGrid.ModifyStyle(0, XTP_PGS_OWNERDRAW);
		m_wndPropertyGrid.ShowToolBar(TRUE);
		m_wndPropertyGrid.SetBorderStyle(xtpGridBorderFlat);

		// Visual Studio 2005 "Whidbey" style theme.
		m_wndPropertyGrid.SetTheme(xtpGridThemeWhidbey);

		return &m_wndPropertyGrid;
	}

	return NULL;
}

void ArxRlePropertyView::UpdateContent(AcDbObjectId& id)
{
	if (!m_wndPropertyGrid.m_hWnd) return;
	if (m_bUpdate) return;
	m_bUpdate = TRUE;

	CXTPPropertyGridUpdateContext m_stateExpanding;
	m_wndPropertyGrid.BeginUpdate(m_stateExpanding);

	if (id.isNull())
	{
		m_wndPropertyGrid.EndUpdate(m_stateExpanding);
		m_bUpdate = FALSE;

		CXTPPropertyGridItem* pCategory = m_wndPropertyGrid.AddCategory(L"ѡ��ʵ��");
		CXTPPropertyGridItem* pItem = pCategory->AddChildItem(new CXTPPropertyGridItem(L"ʵ������", L""));
		pItem->SetFlags(xtpGridItemHasExpandButton | xtpGridItemHasEdit);
		pItem->SetID(20);
		pCategory->Expand();

		return;
	}

	AcDbEntity* ent;
	Acad::ErrorStatus es = OpenEntity(ent, id, AcDb::kForRead);		// might have passed in erased ones
	if(es == Acad::eOk) {
		CXTPPropertyGridItem* pCategory = m_wndPropertyGrid.AddCategory(L"ʵ������");
		CXTPPropertyGridItem* pItem = pCategory->AddChildItem(new CXTPPropertyGridItem(L"ʵ������",ent->isA()->name()));
		pCategory->Expand();

		pCategory = m_wndPropertyGrid.AddCategory(L"����");
		pItem = pCategory->AddChildItem(new CXTPPropertyGridItem(L"ͼ��",ent->layer()));
		pItem->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);
		CXTPPropertyGridItemConstraints* pList = pItem->GetConstraints();
		AcDbLayerTable *pLt;
		if (Acad::eOk == ARXRLEDB->getLayerTable( pLt, AcDb::kForRead ))
		{
			ArxRleApply<LayerTable> applyLt = ArxRleApply<LayerTable>( pLt, AcDb::kForRead );
			LayerTable::Iterator* iter;
			applyLt.createIterator( iter );
			if (NULL != iter)
			{
				CString strs;
				for ( ; !iter->done(); applyLt.stepIterator( iter ))
				{
					LayerTable::Element* elem = applyLt.getElement( iter );
					if (NULL != elem)
					{
						ACHAR* sName;
						elem->getName(sName);
						if(ArxRleString(sName).GetLength() > 0)
							pList->AddConstraint(ArxRleString(sName).t_str());
						elem->close();
					}
				}
				delete iter;
				pLt->close();
			}
		}
		pCategory->AddChildItem(new CXTPPropertyGridItemColor(L"��ɫ", AcCmColorToRefColor(ent->color(), ent->layerId())));
		pCategory->AddChildItem(new CXTPPropertyGridItem(L"����",ent->linetype()));
		pCategory->AddChildItem(new CXTPPropertyGridItem(L"����", ToString(ent->linetypeScale())));
		pCategory->AddChildItem(new CXTPPropertyGridItemDouble(L"���", ent->lineWeight()));
		pCategory->Expand();

		// �ж������������ʵ�����ҵ��Զ���ʵ�壬������޸Ĳ���
		if(ent->isKindOf(ArxRleTitleLabel::desc())) {
			ArxRleTitleLabel* pTitleLabel = ArxRleTitleLabel::cast(ent);

			pCategory = m_wndPropertyGrid.AddCategory(L"����ͼ��");
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� X",pTitleLabel->getPointBegin().sPt(0)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� Y",pTitleLabel->getPointBegin().sPt(1)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� Z",pTitleLabel->getPointBegin().sPt(2)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� X",pTitleLabel->getPointBegin().sPt(0)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� Y",pTitleLabel->getPointBegin().sPt(1)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� Z",pTitleLabel->getPointBegin().sPt(2)));
			pCategory->Expand();

			pCategory = m_wndPropertyGrid.AddCategory(L"��������");
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�����ı�",pTitleLabel->getLabelUp()));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�����ı�",pTitleLabel->getLabelDown()));
			pCategory->Expand();

			pCategory = m_wndPropertyGrid.AddCategory(L"�ı���ʽ");
			pCategory->AddChildItem(new CXTPPropertyGridItemDouble(L"�ı��߶�", pTitleLabel->getTextSize()));
			pCategory->AddChildItem(new CXTPPropertyGridItemDouble(L"�ı��Ƕ�", pTitleLabel->getTextAngle()));
			pCategory->Expand();
		}
		else if(ent->isKindOf(ArxRleBrokenLine::desc())) {
			ArxRleBrokenLine* pBrokenLine = ArxRleBrokenLine::cast(ent);

			pCategory = m_wndPropertyGrid.AddCategory(L"����ͼ��");
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� X",pBrokenLine->getPointBegin().sPt(0)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� Y",pBrokenLine->getPointBegin().sPt(1)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� Z",pBrokenLine->getPointBegin().sPt(2)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� X",pBrokenLine->getPointBegin().sPt(0)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� Y",pBrokenLine->getPointBegin().sPt(1)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� Z",pBrokenLine->getPointBegin().sPt(2)));
			pCategory->Expand();

			pCategory = m_wndPropertyGrid.AddCategory(L"��������");
			pCategory->AddChildItem(new CXTPPropertyGridItemDouble(L"��С H", pBrokenLine->getBrokenSize()));
			pCategory->Expand();
		}
		else if(ent->isKindOf(ArxRleLeadDimension::desc())) {
			ArxRleLeadDimension* pLeadDim = ArxRleLeadDimension::cast(ent);

			pCategory = m_wndPropertyGrid.AddCategory(L"����ͼ��");
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"���� X",pLeadDim->getPointBase().sPt(0)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"���� Y",pLeadDim->getPointBase().sPt(1)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"���� Z",pLeadDim->getPointBase().sPt(2)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� X",pLeadDim->getPointBegin().sPt(0)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� Y",pLeadDim->getPointBegin().sPt(1)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� Z",pLeadDim->getPointBegin().sPt(2)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� X",pLeadDim->getPointBegin().sPt(0)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� Y",pLeadDim->getPointBegin().sPt(1)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� Z",pLeadDim->getPointBegin().sPt(2)));
			pCategory->Expand();

			pCategory = m_wndPropertyGrid.AddCategory(L"��������");
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�����ı�",pLeadDim->getLabelUp()));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�����ı�",pLeadDim->getLabelDown()));
			pCategory->Expand();

			pCategory = m_wndPropertyGrid.AddCategory(L"�ı���ʽ");
			pCategory->AddChildItem(new CXTPPropertyGridItemDouble(L"�ı��߶�", pLeadDim->getTextSize()));
			pCategory->AddChildItem(new CXTPPropertyGridItemDouble(L"�ı��Ƕ�", pLeadDim->getTextAngle()));
			pCategory->Expand();
		}
		else if(ent->isKindOf(ArxRleNetPlanWork::desc())) {
			ArxRleNetPlanWork* pNetPlanWork = ArxRleNetPlanWork::cast(ent);

			pCategory = m_wndPropertyGrid.AddCategory(L"����ͼ��");
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� X",pNetPlanWork->getPointBegin().sPt(0)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� Y",pNetPlanWork->getPointBegin().sPt(1)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��� Z",pNetPlanWork->getPointBegin().sPt(2)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� X",pNetPlanWork->getPointBegin().sPt(0)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� Y",pNetPlanWork->getPointBegin().sPt(1)));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ� Z",pNetPlanWork->getPointBegin().sPt(2)));
			pCategory->Expand();

			pCategory = m_wndPropertyGrid.AddCategory(L"��������");
			pItem = pCategory->AddChildItem(new CXTPPropertyGridItem(L"������ʽ",pNetPlanWork->getWorkStyle()));
			pItem->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);
			pList = pItem->GetConstraints();
			AcDbDictionary *pDict;
			pDict = ArxRleUtils::openDictionaryForRead(ArxRleNetPlanWorkStyle::dictName(), ARXRLEDB);
			if(pDict != NULL)
			{
				ArxRleApply<Dictionary> apply = ArxRleApply<Dictionary>( pDict, AcDb::kForRead );
				Dictionary::Iterator* iter;
				apply.createIterator( iter );
				if (NULL != iter)
				{
					CString strs;
					for ( ; !iter->done(); apply.stepIterator( iter ))
					{
						Dictionary::Element* elem = apply.getElement( iter );
						if (NULL != elem)
						{
							ArxRleString sName = ((ArxRleNetPlanWorkStyle*)elem)->name();
							if(sName.GetLength() > 0)
								pList->AddConstraint(sName.t_str());
							elem->close();
						}
					}
					delete iter;
					pDict->close();
				}
			}
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�����", pNetPlanWork->getLabelBegin()));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"�յ���", pNetPlanWork->getLabelEnd()));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��������", pNetPlanWork->getLabelUp()));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"������ʱ", pNetPlanWork->getLabelDown()));
			pCategory->AddChildItem(new CXTPPropertyGridItem(L"��������", pNetPlanWork->getWorkDes()));
			pCategory->Expand();

			pCategory = m_wndPropertyGrid.AddCategory(L"����Ҫ��");
			pCategory->AddChildItem(new CXTPPropertyGridItemDouble(L"����Ҫ��", pNetPlanWork->getResMens()));
			pCategory->AddChildItem(new CXTPPropertyGridItemDouble(L"�豸Ҫ��", pNetPlanWork->getResTools()));
			pCategory->AddChildItem(new CXTPPropertyGridItemDouble(L"�ʽ�Ҫ��", pNetPlanWork->getResMoney()));
			pCategory->Expand();

			pCategory = m_wndPropertyGrid.AddCategory(L"�����ϵ");
			pCategory->AddChildItem(new CXTPPropertyGridItemNumber(L"������", (long)pNetPlanWork->getWorkCode()));
			if(!pNetPlanWork->getBindWorkRefId().isNull())
				pCategory->AddChildItem(new CXTPPropertyGridItem(L"���ӹ���", pNetPlanWork->getBindWorkRef()));
			pCategory->Expand();
		}

		CloseEntity(ent);
	}

	m_wndPropertyGrid.EndUpdate(m_stateExpanding);
	m_bUpdate = FALSE;
}

void ArxRlePropertyView::UpdateEntity(AcDbObjectId& id)
{
	AcDbEntity* ent;
	Acad::ErrorStatus es = OpenEntity(ent, id, AcDb::kForWrite);		// might have passed in erased ones
	if(es == Acad::eOk) {
		CXTPPropertyGridItem* item = m_wndPropertyGrid.GetItem(1);
		CXTPPropertyGridItems* items = item->GetChilds();
		ArxRleString layer(items->GetAt(0)->GetValue());
		ent->setLayer(layer.w_ptr());
		ent->setColor(RefColorToAcCmColor(((CXTPPropertyGridItemColor*)items->GetAt(1))->GetColor()));
		ArxRleString lt(items->GetAt(2)->GetValue());
		ent->setLinetype(lt);
		ent->setLinetypeScale(((CXTPPropertyGridItemDouble*)items->GetAt(3))->GetDouble());
		ent->setLineWeight((AcDb::LineWeight)((CXTPPropertyGridItemNumber*)items->GetAt(4))->GetNumber());

		// �ж������������ʵ�����ҵ��Զ���ʵ�壬������޸Ĳ���
		if(ent->isKindOf(ArxRleTitleLabel::desc())) {
			ArxRleTitleLabel* pTitleLabel = ArxRleTitleLabel::cast(ent);

			item = m_wndPropertyGrid.GetItem(2);
			items = item->GetChilds();
			pTitleLabel->setPointBegin(CPt3d(((CXTPPropertyGridItemDouble*)items->GetAt(0))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(1))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(2))->GetDouble()));
			pTitleLabel->setPointEnd(CPt3d(((CXTPPropertyGridItemDouble*)items->GetAt(3))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(4))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(5))->GetDouble()));

			item = m_wndPropertyGrid.GetItem(3);
			items = item->GetChilds();
			pTitleLabel->setLabelUp(items->GetAt(0)->GetValue());
			pTitleLabel->setLabelDown(items->GetAt(1)->GetValue());

			item = m_wndPropertyGrid.GetItem(4);
			items = item->GetChilds();
			pTitleLabel->setTextSize(((CXTPPropertyGridItemDouble*)items->GetAt(0))->GetDouble());
			pTitleLabel->setTextAngle(((CXTPPropertyGridItemDouble*)items->GetAt(1))->GetDouble());
		}
		else if(ent->isKindOf(ArxRleBrokenLine::desc())) {
			ArxRleBrokenLine* pBrokenLine = ArxRleBrokenLine::cast(ent);

			item = m_wndPropertyGrid.GetItem(2);
			items = item->GetChilds();
			pBrokenLine->setPointBegin(CPt3d(((CXTPPropertyGridItemDouble*)items->GetAt(0))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(1))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(2))->GetDouble()));
			pBrokenLine->setPointEnd(CPt3d(((CXTPPropertyGridItemDouble*)items->GetAt(3))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(4))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(5))->GetDouble()));

			item = m_wndPropertyGrid.GetItem(3);
			items = item->GetChilds();
			pBrokenLine->setBrokenSize(((CXTPPropertyGridItemDouble*)items->GetAt(0))->GetDouble());
		}
		else if(ent->isKindOf(ArxRleLeadDimension::desc())) {
			ArxRleLeadDimension* pLeadDim = ArxRleLeadDimension::cast(ent);

			item = m_wndPropertyGrid.GetItem(2);
			items = item->GetChilds();
			pLeadDim->setPointBase(CPt3d(((CXTPPropertyGridItemDouble*)items->GetAt(0))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(1))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(2))->GetDouble()));
		   pLeadDim->setPointBegin(CPt3d(((CXTPPropertyGridItemDouble*)items->GetAt(3))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(4))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(5))->GetDouble()));
			pLeadDim->setPointEnd(CPt3d(((CXTPPropertyGridItemDouble*)items->GetAt(6))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(7))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(8))->GetDouble()));

			item = m_wndPropertyGrid.GetItem(3);
			items = item->GetChilds();
			pLeadDim->setLabelUp(items->GetAt(0)->GetValue());
			pLeadDim->setLabelDown(items->GetAt(1)->GetValue());

			item = m_wndPropertyGrid.GetItem(4);
			items = item->GetChilds();
			pLeadDim->setTextSize(((CXTPPropertyGridItemDouble*)items->GetAt(0))->GetDouble());
			pLeadDim->setTextAngle(((CXTPPropertyGridItemDouble*)items->GetAt(1))->GetDouble());
		}
		else if(ent->isKindOf(ArxRleNetPlanWork::desc())) {
			ArxRleNetPlanWork* pNetPlanWork = ArxRleNetPlanWork::cast(ent);

			item = m_wndPropertyGrid.GetItem(2);
			items = item->GetChilds();
			pNetPlanWork->setPointBegin(CPt3d(((CXTPPropertyGridItemDouble*)items->GetAt(0))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(1))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(2))->GetDouble()));
			pNetPlanWork->setPointEnd(CPt3d(((CXTPPropertyGridItemDouble*)items->GetAt(3))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(4))->GetDouble(),
				((CXTPPropertyGridItemDouble*)items->GetAt(5))->GetDouble()));

			item = m_wndPropertyGrid.GetItem(3);
			items = item->GetChilds();
			pNetPlanWork->setWorkStyle(items->GetAt(0)->GetValue());
			pNetPlanWork->setLabelBegin(items->GetAt(1)->GetValue());
			pNetPlanWork->setLabelEnd(items->GetAt(2)->GetValue());
			pNetPlanWork->setLabelUp(items->GetAt(3)->GetValue());
			pNetPlanWork->setLabelDown(items->GetAt(4)->GetValue());
			pNetPlanWork->setWorkDes(items->GetAt(5)->GetValue());

			item = m_wndPropertyGrid.GetItem(4);
			items = item->GetChilds();
			pNetPlanWork->setResMens(((CXTPPropertyGridItemDouble*)items->GetAt(0))->GetDouble());
			pNetPlanWork->setResTools(((CXTPPropertyGridItemDouble*)items->GetAt(1))->GetDouble());
			pNetPlanWork->setResMoney(((CXTPPropertyGridItemDouble*)items->GetAt(2))->GetDouble());

			item = m_wndPropertyGrid.GetItem(5);
			items = item->GetChilds();
			pNetPlanWork->setWorkCode(((CXTPPropertyGridItemDouble*)items->GetAt(0))->GetDouble());
		}

		CloseEntity(ent);
	}
}

LRESULT ArxRlePropertyView::OnAcadKeepFocus(WPARAM, LPARAM)
{
	return TRUE;
}

LRESULT ArxRlePropertyView::OnGridNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case XTP_PGN_DRAWITEM:
		DrawItem((LPDRAWITEMSTRUCT)lParam);
		break;
	case XTP_PGN_INPLACEBUTTONDOWN:
		{
			CXTPPropertyGridInplaceButton* pButton = (CXTPPropertyGridInplaceButton*)lParam;
			if (pButton->GetItem()->GetID() == 20 && pButton->GetID() == XTP_ID_PROPERTYGRID_EXPANDBUTTON) // 2 Buttons
			{
				ArxRleSelSet ss;
				if(ss.userSelect() == ArxRleSelSet::kSelected)
				{ 
					AcDbObjectIdArray ids;
					ss.asArray(ids);

					UpdateContent(ids[0]);
				}

				return TRUE;
			}
		}
		break;
	case XTP_PGN_SORTORDER_CHANGED:
		m_wndPropertyGrid.GetPropertySort();
		break;
	case XTP_PGN_ITEMVALUE_CHANGED:
		{
			CXTPPropertyGridItem* pItem = (CXTPPropertyGridItem*)lParam;
			TRACE(_T("Value Changed. Caption = %s, ID = %i, Value = %s\n"), pItem->GetCaption(), pItem->GetID(), pItem->GetValue());

			if (DYNAMIC_DOWNCAST(CXTPPropertyGridItemEnum, pItem))
			{
				if (pItem->GetMetrics(TRUE, FALSE))
					pItem->GetMetrics(TRUE, FALSE)->m_nImage = ((CXTPPropertyGridItemEnum*)pItem)->GetEnum();
			}

			if (pItem->GetID() == 501) // Dynamic Options
			{
				CXTPPropertyGridItems* pSiblingItems = pItem->GetParentItem()->GetChilds();

				for (int i = 0; i < pSiblingItems->GetCount(); i++)
				{
					if (pSiblingItems->GetAt(i) != pItem)
						pSiblingItems->GetAt(i)->SetHidden(!((CXTPPropertyGridItemBool*)pItem)->GetBool());
				}
			}
		}
		break;
	case XTP_PGN_SELECTION_CHANGED:
		{
			CXTPPropertyGridItem* pItem = (CXTPPropertyGridItem*)lParam;
			if (pItem)
			{
				if (pItem->IsKindOf(RUNTIME_CLASS(CXTPPropertyGridItemColor)))
					TRACE(_T("Color Item. Selection Changed. Item = %s\n"), pItem->GetCaption());

				if (pItem->GetID() == 510)
				{
					//pItem->SetDescription(pItem->GetDescription() + "!");
				}
			}
		}
		break;
	case XTP_PGN_EDIT_CHANGED:
		{
			CXTPPropertyGridInplaceEdit* pEdit = DYNAMIC_DOWNCAST(CXTPPropertyGridInplaceEdit, (CWnd*)lParam);
			if (pEdit && pEdit->GetItem())
			{
				// Custom Validation
				if (pEdit->GetItem()->GetID() == 510)
				{
					CString str;
					pEdit->CEdit::GetWindowText(str);

					if (str.GetLength() > 30)
					{
						MessageBeep((UINT)-1);
						pEdit->SetSel(0, -1);
						pEdit->ReplaceSel(str.Left(30));
					}
				}
				// Custom Validation
				if (pEdit->GetItem()->GetCaption() == _T("ItemsInMRUList"))
				{
					CString str;
					pEdit->CEdit::GetWindowText(str);

					int i = _ttoi(str);
					if (i > 20)
					{
						MessageBeep((UINT)-1);
						pEdit->SetSel(0, -1);
						pEdit->ReplaceSel(_T("20"));
					}
				}
			}
		}
		break;
	}

	return FALSE;
}

void ArxRlePropertyView::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CXTPPropertyGridItem* pItem = (CXTPPropertyGridItem*)lpDrawItemStruct->itemData;

	COLORREF clrWindow = GetSysColor(COLOR_3DFACE);

	ASSERT(pItem != NULL);

	CXTPPropertyGridView* pGrid = pItem->GetGrid();

	CXTPWindowRect rcWindow(pGrid);
	CRect rc = lpDrawItemStruct->rcItem;

	CXTPPropertyGridItemMetrics* pMetrics = pGrid->GetPaintManager()->GetItemMetrics();

	CXTPBufferDC dc(lpDrawItemStruct->hDC, rc);
	CXTPFontDC font(&dc, pItem->IsCategory()? &pMetrics->m_fontBold: &pMetrics->m_fontNormal);

	dc.FillSolidRect(rc, clrWindow);
	dc.SetBkMode(TRANSPARENT);

	CRect rcCaption(rc.left, rc.top, rc.left + pGrid->GetDividerPos(), rc.bottom);

	COLORREF clrFore = GetSysColor(COLOR_BTNTEXT);
	COLORREF clrShadow = GetSysColor(COLOR_3DSHADOW);
	COLORREF clrLight = GetSysColor(COLOR_BTNHIGHLIGHT);

	{
		if (!pItem->IsCategory())
		{

			dc.SetTextColor(pItem->GetReadOnly()? GetSysColor(COLOR_GRAYTEXT): RGB(0, 0, 128));

			CRect rcValue(rc);
			rcValue.left = rcCaption.right + 4;
			rcValue.bottom -= 1;

			if (!pItem->OnDrawItemValue(dc, rcValue))
			{
				dc.DrawText( pItem->GetValue(), rcValue,  DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);
			}
		}

		dc.SetTextColor(clrFore);

		dc.Draw3dRect(rcCaption.right - 1, rc.top, 1, rc.Height(), clrShadow, clrShadow);
		dc.Draw3dRect(rcCaption.right, rc.top, 1, rc.Height(), clrLight, clrLight);

		BOOL bSelected = lpDrawItemStruct->itemState & ODS_SELECTED;
		BOOL bFocused = bSelected && GetFocus() && ((GetFocus() == pGrid) || (GetFocus()->GetParent() == pGrid) || (GetFocus()->GetOwner() == pGrid));
		if (bFocused || bSelected)
		{
			dc.Draw3dRect(rc, clrFore, clrLight);
		}
		else
		{
			// somebody! optimize me!
			for (int i = 0; i < rc.right; i += 2)
				dc.SetPixel(i, rc.bottom - 1, clrShadow);
		}


		CRect rcText(rc);
		rcText.left = max(1, pItem->GetIndent()) * XTP_PGI_EXPAND_BORDER + 3;
		rcText.right = rcCaption.right - 1;
		rcText.bottom -= 1;
		dc.DrawText( pItem->GetCaption(),   rcText,  DT_SINGLELINE|DT_VCENTER);

		CRect rcValue(rcCaption.right, rc.top, rc.right, rc.bottom - 1);
		if (!pItem->IsCategory() && bSelected)
			pGrid->GetPaintManager()->DrawInplaceButtons(&dc, pItem, rcValue);	
	}

	if (pItem->HasChilds())
	{
		CRgn rgn;
		rgn.CreateRectRgnIndirect(&rcCaption);
		dc.SelectClipRgn(&rgn);


		CRect rcSign(CPoint(XTP_PGI_EXPAND_BORDER / 2 - 5, rc.CenterPoint().y - 4), CSize(9, 9));

		if (pItem->GetIndent() > 1)
			rcSign.OffsetRect((pItem->GetIndent() - 1) * XTP_PGI_EXPAND_BORDER, 0);


		CPoint pt = rcSign.CenterPoint();

		CXTPBrushDC brush (dc,  GetSysColor(COLOR_WINDOW));
		CXTPPenDC pen (dc,  clrFore);
		dc.Rectangle(rcSign);

		dc.MoveTo(pt.x - 2, pt.y);
		dc.LineTo(pt.x + 3, pt.y);

		if(!pItem->IsExpanded())
		{
			dc.MoveTo(pt.x, pt.y - 2);
			dc.LineTo(pt.x, pt.y + 3);
		}

		dc.SelectClipRgn(NULL);
	}
}
