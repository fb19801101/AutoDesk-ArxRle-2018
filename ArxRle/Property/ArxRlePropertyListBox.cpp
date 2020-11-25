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

#include "ArxRlePropertyListBox.h"
#include "ArxRlePropertyItem.h"
#include "ArxRleUserMessage.h"

#define PROPERTY_LEFT_BORDER 16


/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyListBox

ArxRlePropertyListBox::ArxRlePropertyListBox()
{
	m_nSelectedItem = -1;
	m_pWndInPlaceControl = NULL;
	m_pPropertyItemManager = NULL;
}


inline void ArxRlePropertyListBox::InsertPropertyItem(ArxRlePropertyItem* pPropertyItem, int nIndex)
{
	ASSERT(pPropertyItem != NULL);
	InsertString(nIndex, (LPCTSTR)pPropertyItem);
}

void ArxRlePropertyListBox::MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/)
{
}

int ArxRlePropertyListBox::CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/)
{
	return 0;
}

ArxRlePropertyItem* ArxRlePropertyListBox::GetPropertyItem(int nIndex)
{
	return nIndex >= 0 && nIndex < GetCount() ? reinterpret_cast<ArxRlePropertyItem*>(GetItemData(nIndex)) : NULL;
}

void ArxRlePropertyListBox::SetPropertyItemManager(ArxRlePropertyItemManager* pPropertyItemManager)
{
	m_pPropertyItemManager = pPropertyItemManager;
	m_pPropertyItemManager->InitControl(this);
}

void ArxRlePropertyListBox::GetItemValueRect(CRect& rect)
{
	rect.left += PROPERTY_LEFT_BORDER;
	rect.left += rect.Width() / 2;

	rect.DeflateRect(3, 0, 0, 1);
}

void ArxRlePropertyListBox::NoInPlaceControl()
{
	delete m_pWndInPlaceControl;
	m_pWndInPlaceControl = NULL;
}

void ArxRlePropertyListBox::ResetContent()
{
	NoInPlaceControl();

	m_nSelectedItem = -1;

	CAdUiListBox::ResetContent();
}

void ArxRlePropertyListBox::PreSubclassWindow() 
{	
	CAdUiListBox::PreSubclassWindow();

	ModifyStyle(0, LBS_OWNERDRAWFIXED|LBS_NOINTEGRALHEIGHT|LBS_NOTIFY);
}

BEGIN_MESSAGE_MAP(ArxRlePropertyListBox, CAdUiListBox)
	//{{AFX_MSG_MAP(ArxRlePropertyListBox)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelChange)
	ON_MESSAGE(WM_USER_SET_DATA, OnSetData)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyListBox message handlers

void ArxRlePropertyListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
#if 1
	if(lpDrawItemStruct->itemAction & ODA_FOCUS)
		return;
#endif

	ArxRlePropertyItem* pPropertyItem = (ArxRlePropertyItem*)lpDrawItemStruct->itemData;
	ASSERT(pPropertyItem != NULL);

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	// Rámèek
	CRect rect;
	GetClientRect(rect);

	int nLeftBorder = rect.left + PROPERTY_LEFT_BORDER;

	// + / -
	BOOL bTabItem = pPropertyItem->IsKindOf(RUNTIME_CLASS(ArxRlePropertyItemCategory));

	if(bTabItem)
	{
		CRect rcSign(lpDrawItemStruct->rcItem);
		rcSign.right = nLeftBorder;

		rcSign.DeflateRect(4, 4);

		rcSign.right += 1;
		rcSign.bottom += 1;

		dc.FillRect(rcSign, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
		dc.FrameRect(rcSign, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
		
		CPoint ptCenter(rcSign.CenterPoint());

		// minus		
		dc.MoveTo(ptCenter.x - 2, ptCenter.y);
		dc.LineTo(ptCenter.x + 3, ptCenter.y);

		if(!static_cast<ArxRlePropertyItemCategory*>(pPropertyItem)->GetChildrenVisible())
		{
			// plus
			dc.MoveTo(ptCenter.x, ptCenter.y - 2);
			dc.LineTo(ptCenter.x, ptCenter.y + 3);
		}
	}

	// Vertikála v ¾avo
	CPen pen(PS_SOLID, 1, RGB(198, 198, 198));
	CPen* pOldPen = dc.SelectObject(&pen);

	dc.MoveTo(nLeftBorder, rect.top);
	dc.LineTo(nLeftBorder, rect.bottom);

	// Spodn?èiara
	rect = lpDrawItemStruct->rcItem;
	rect.left += PROPERTY_LEFT_BORDER;

	int nBottom = rect.bottom - 1;

	dc.MoveTo(nLeftBorder, nBottom);
	dc.LineTo(rect.right, nBottom);

	// Odde¾ova?ståpcov
	nLeftBorder += rect.Width() / 2;

	dc.MoveTo(nLeftBorder, rect.top);
	dc.LineTo(nLeftBorder, nBottom);

	// Text položky
	rect.left += 1;
	rect.bottom -= 1;
	rect.right = nLeftBorder;

	int nCrBackground, nCrText;

	if((lpDrawItemStruct->itemAction | ODA_SELECT) && (lpDrawItemStruct->itemState & ODS_SELECTED))
	{
		nCrBackground = COLOR_HIGHLIGHT;
		nCrText = COLOR_HIGHLIGHTTEXT;
	}
	else
	{
		nCrBackground = COLOR_WINDOW;
		nCrText = COLOR_WINDOWTEXT;
	}

	COLORREF crBackground = ::GetSysColor(nCrBackground);
	COLORREF crText = ::GetSysColor(nCrText);

	dc.FillSolidRect(rect, crBackground);
	COLORREF crOldBkColor = dc.SetBkColor(crBackground);
	COLORREF crOldTextColor = dc.SetTextColor(crText);

	rect.left += 3;
	rect.right -= 3;

	CFont* pOldFont = NULL;
	CFont fontLabel;

	if(bTabItem)
	{
		LOGFONT logFont;
		CFont* pFont = GetFont();
		pFont->GetLogFont(&logFont);

		logFont.lfWeight = FW_BOLD;
		fontLabel.CreateFontIndirect(&logFont);

		pOldFont = dc.SelectObject(&fontLabel);
	}

	// Popis položky
	dc.DrawText(pPropertyItem->GetName(), &rect, DT_SINGLELINE|DT_VCENTER);

	dc.SelectObject(pOldPen);
	dc.SetTextColor(crOldTextColor);
	dc.SetBkColor(crOldBkColor);
	//dc.SetBkMode(TRANSPARENT);

	if(pOldFont != NULL)
		dc.SelectObject(pOldFont);

	// Hodnota položky
	if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
	{
		rect = lpDrawItemStruct->rcItem;
		GetItemValueRect(rect);
		pPropertyItem->DrawValue(&dc, rect);

		TRACE("\nDraw value of %s", pPropertyItem->GetName());
	}

	dc.Detach();
}

void ArxRlePropertyListBox::DoCollapse(ArxRlePropertyItemCategory* pPropertyItemTab, int nItem)
{
	ASSERT(pPropertyItemTab->GetChildrenVisible());

	nItem++;

	for(int nNumber = pPropertyItemTab->GetNumberEnabledItems(); nNumber > 0; nNumber--)
		DeleteString(nItem);

	pPropertyItemTab->SetChildrenVisible(false);
}

void ArxRlePropertyListBox::DoExpand(ArxRlePropertyItemCategory* pPropertyItemTab, int& nItem)
{
	POSITION pos = pPropertyItemTab->GetHeadPosition();

	while(pos != NULL)
	{
		ArxRlePropertyItem* pPropertyItem = pPropertyItemTab->GetNext(pos);

		if(pPropertyItem->GetEnabled())
			InsertPropertyItem(pPropertyItem, ++nItem);
	}

	pPropertyItemTab->SetChildrenVisible();
}

void ArxRlePropertyListBox::DoCollapseExpand(int nItem, ArxRlePropertyItem* pPropertyItem)
{	
	if(pPropertyItem == NULL)
		pPropertyItem = GetPropertyItem(nItem);

	ASSERT(pPropertyItem != NULL);

	if(pPropertyItem->IsKindOf(RUNTIME_CLASS(ArxRlePropertyItemCategory)))
	{
		if(SetCurrentData())
			NoInPlaceControl();

		ArxRlePropertyItemCategory* pPropertyItemTab = static_cast<ArxRlePropertyItemCategory*>(pPropertyItem);

		if(pPropertyItemTab->GetChildrenVisible())
			DoCollapse(pPropertyItemTab, nItem);
		else
			DoExpand(pPropertyItemTab, nItem);
	}
}

void ArxRlePropertyListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	CAdUiListBox::OnLButtonDown(nFlags, point);

	if(point.x <= PROPERTY_LEFT_BORDER)
	{
		DoCollapseExpand(GetCurSel());
	}
}

void ArxRlePropertyListBox::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CAdUiListBox::OnLButtonDblClk(nFlags, point);

	DoCollapseExpand(GetCurSel());
}

BOOL ArxRlePropertyListBox::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
	{		
		int nItem = GetCurSel();
		char nChar = char(pMsg->wParam);
		bool bDone = true;

		ArxRlePropertyItem* pPropertyItem = GetPropertyItem(nItem);

		if(pPropertyItem != NULL)
		{
			if(pPropertyItem->IsKindOf(RUNTIME_CLASS(ArxRlePropertyItemCategory)))
			{
				bool bChildrenVisible = static_cast<ArxRlePropertyItemCategory*>(pPropertyItem)->GetChildrenVisible();

				switch(nChar)
				{
					case VK_RETURN:
						DoCollapseExpand(nItem, pPropertyItem);
						break;
					case VK_ADD:
						if(!bChildrenVisible)
							DoExpand((ArxRlePropertyItemCategory*)pPropertyItem, nItem);
						break;
					case VK_SUBTRACT:
						if(bChildrenVisible)
							DoCollapse((ArxRlePropertyItemCategory*)pPropertyItem, nItem);
						break;
					default:
						bDone = false;
				}
			}
			else
			{
				switch(nChar)
				{
					case VK_RETURN:
					case VK_TAB:
						if(m_pWndInPlaceControl != NULL)
							m_pWndInPlaceControl->SetFocus();
						break;
					default:
						bDone = false;
				}
			}
		}
		else
			bDone = false;

		if(bDone)
			return TRUE;
		else
		{
			if(GetFocus() == this && IsCharAlpha(nChar))
			{
				if(LookupPropertyItem(nChar))
					OnSelChange();

				return TRUE;
			}
		}
	}

	return CAdUiListBox::PreTranslateMessage(pMsg);
}

int ArxRlePropertyListBox::FindPropertyItem(char nStartChar, int nFromIndex, int nCount)
{
	const CString strStartChar(nStartChar);

	while(nCount--)
	{
		ArxRlePropertyItem* pPropertyItem = reinterpret_cast<ArxRlePropertyItem*>(GetItemData(nFromIndex));
		ASSERT(pPropertyItem != NULL);
			
		if(pPropertyItem->GetName().Left(1).CompareNoCase(strStartChar) == 0)
			return nFromIndex;

		nFromIndex++;
	}

	return -1;
}

bool ArxRlePropertyListBox::LookupPropertyItem(char nStartChar)
{
	int nCount = GetCount();

	if(nCount)
	{
		int nCurrItem = GetCurSel() + 1;

		if(nCurrItem == nCount)
			nCurrItem = 0;

		int nFindIndex = FindPropertyItem(nStartChar, nCurrItem, nCount - nCurrItem);

		if(nFindIndex == -1 && nCurrItem > 0)
			nFindIndex = FindPropertyItem(nStartChar, 0, nCurrItem);

		if(nFindIndex != -1)
		{
			SetCurSel(nFindIndex);
			return true;
		}
	}

	return false;
}

bool ArxRlePropertyListBox::SetCurrentData()
{
	if(m_pWndInPlaceControl != NULL && m_nSelectedItem != -1)
	{
		ArxRlePropertyItem* pPropertyItemEdited = GetPropertyItem(m_nSelectedItem);
		ASSERT(pPropertyItemEdited != NULL);

		pPropertyItemEdited->SetData(m_pWndInPlaceControl);
		m_pPropertyItemManager->OnDataChanged(pPropertyItemEdited, this, m_nSelectedItem);

		return true;
	}

	return false;
}

LRESULT ArxRlePropertyListBox::OnSetData(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	SetCurrentData();

	return TRUE;
}

void ArxRlePropertyListBox::OnSelChange()
{
	int nItem = GetCurSel();

	if(m_nSelectedItem != nItem)
	{
		//SetCurrentData();

		ArxRlePropertyItem* pPropertyItem = GetPropertyItem(nItem);
		ASSERT(pPropertyItem != NULL);

		CRect rect;

		GetItemRect(nItem, rect);
		GetItemValueRect(rect);

		pPropertyItem->CreateInPlaceControl(this, rect, m_pWndInPlaceControl);

		m_nSelectedItem = nItem;
	}
}

void ArxRlePropertyListBox::ShowInPlaceControl(bool bShow)
{
	if(m_pWndInPlaceControl)
	{
		if(bShow)
		{
			ArxRlePropertyItem* pPropertyItem = GetPropertyItem(m_nSelectedItem);
			ASSERT(pPropertyItem != NULL);

			CRect rect;

			GetItemRect(m_nSelectedItem, rect);
			GetItemValueRect(rect);

			pPropertyItem->CreateInPlaceControl(this, rect, m_pWndInPlaceControl);

		}

		m_pWndInPlaceControl->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
	}
}

void ArxRlePropertyListBox::Refresh()
{
	ShowInPlaceControl(false);

	CRect rect;

	CDC dc;
	dc.Attach(*GetDC());
	dc.SelectObject(GetFont());

	int nItems = GetCount();
	COLORREF crBkColor = dc.GetBkColor();

	for(int i = 0; i < nItems; i++)
	{
		ArxRlePropertyItem* pPropertyItem = reinterpret_cast<ArxRlePropertyItem*>(GetItemData(i));

		if(!pPropertyItem->IsKindOf(RUNTIME_CLASS(ArxRlePropertyItemCategory)))
		{
			GetItemRect(i, rect);
			GetItemValueRect(rect);

			rect.DeflateRect(1, 1);
			dc.FillSolidRect(&rect, crBkColor);
			rect.InflateRect(1, 1);

			pPropertyItem->DrawValue(&dc, rect);
		}
	}

	dc.Detach();

	ShowInPlaceControl();
}

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemManager


ArxRlePropertyItemManager::ArxRlePropertyItemManager()
{
}

ArxRlePropertyItemManager::~ArxRlePropertyItemManager()
{
}

void ArxRlePropertyItemManager::OnDataChanged(ArxRlePropertyItem* /*pPropertyItem*/, ArxRlePropertyListBox* /*pWndPropertyListCtrl*/, int /*nIndex*/)
{
}

ArxRlePropertyItemCategory* ArxRlePropertyItemManager::GetCategoryTab(int nIndex) const
{
	POSITION pos = m_listPropertyItemTabs.FindIndex(nIndex);
	ASSERT(pos != NULL);

	return m_listPropertyItemTabs.GetAt(pos);
}

ArxRlePropertyItemCategory* ArxRlePropertyItemManager::AddNewTab(LPCTSTR pStrTabName)
{
	ArxRlePropertyItemCategory* pNewTab = new ArxRlePropertyItemCategory(pStrTabName);

	m_listPropertyItemTabs.AddTail(pNewTab);

	return pNewTab;
}

void ArxRlePropertyItemManager::InitControl(ArxRlePropertyListBox* pWndPropertyListCtrl)
{
	int nItem = 0;
	POSITION pos = m_listPropertyItemTabs.GetHeadPosition();
	
	while(pos != NULL)
	{
		ArxRlePropertyItemCategory* pPropertyItemTab = m_listPropertyItemTabs.GetNext(pos);

		if(pPropertyItemTab->GetEnabled())
		{
			pWndPropertyListCtrl->InsertPropertyItem(pPropertyItemTab, nItem);
			pWndPropertyListCtrl->DoExpand(pPropertyItemTab, nItem);

			nItem++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemManagerAdaptable

void ArxRlePropertyItemManagerAdaptable::CheckState(ArxRlePropertyListBox* pWndPropertyListCtrl, int nFromControlIndex, BYTE nFromPropertyItemID)
{
	bool bDoInsert = false;

	POSITION pos = m_listPropertyItemTabs.GetHeadPosition();
	
	while(pos != NULL)
	{
		ArxRlePropertyItemCategory* pPropertyItemTab = m_listPropertyItemTabs.GetNext(pos);
		POSITION posTab = pPropertyItemTab->GetHeadPosition();

		if(bDoInsert)
		{
			if(pPropertyItemTab->GetEnabled())
			{
				pWndPropertyListCtrl->InsertPropertyItem(pPropertyItemTab, ++nFromControlIndex);
				pPropertyItemTab->SetChildrenVisible();
			}
			else
				// Táto záložka nieje prístupn?
				continue;
		}
		
		while(posTab != NULL)
		{
			ArxRlePropertyItem* pPropertyItem = pPropertyItemTab->GetNext(posTab);

			if(bDoInsert)
			{
				if(pPropertyItem->GetEnabled())
					pWndPropertyListCtrl->InsertPropertyItem(pPropertyItem, ++nFromControlIndex);
			}
			else if(nFromPropertyItemID == pPropertyItem->GetPropertyID())
			{
				// Našiel si položku od ktorej by mali nasledova?zmeny
				int nItems = pWndPropertyListCtrl->GetCount();

				if(nItems != nFromControlIndex + 1)
				{
					// Zma?všetky položky 
					int i = nItems - 1;
					nItems -= (nFromControlIndex + 1);
					
					while(nItems-- > 0)
					{
						pWndPropertyListCtrl->DeleteString(i--);
					}
				}

				bDoInsert = true;
			}
		}
	}
}