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

#include "ArxRleAttributeList.h"
#include "DbEntity/ArxRleEntityClass.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleApply.h"
#include "NetPlan\ArxRleNetPlanWorkStyle.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRleAttributeList

ArxRleAttributeList::ArxRleAttributeList()
{
}

ArxRleAttributeList::~ArxRleAttributeList()
{
	m_pStatic != NULL ? delete m_pStatic : 0;
	m_pComboBox != NULL ? delete m_pComboBox : 0;
	m_pEditBox != NULL ? delete m_pEditBox : 0;
	m_pButton != NULL ? delete m_pButton : 0;
	m_pSymbolComboBox != NULL ? delete m_pSymbolComboBox : 0;
	m_pColorComboBox != NULL ? delete m_pColorComboBox : 0;
	m_pLineTypeComboBox != NULL ? delete m_pLineTypeComboBox : 0;
	m_pLineWeightComboBox != NULL ? delete m_pLineWeightComboBox : 0;

	m_pStatic = NULL;
	m_pComboBox = NULL;
	m_pEditBox = NULL;
	m_pButton = NULL;
	m_pSymbolComboBox = NULL;
	m_pColorComboBox = NULL;
	m_pLineTypeComboBox = NULL;
	m_pLineWeightComboBox = NULL;

	m_vecItems.DelItems();
}


BEGIN_MESSAGE_MAP(ArxRleAttributeList, CAcUiListBox)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_VSCROLL()
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnLbnSelchange)
	ON_CBN_SELCHANGE(IDC_PROP_COMBBOX, OnSelchangeCmbBox)
	ON_EN_CHANGE(IDC_PROP_EDITBOX, OnChangeEditBox)
	ON_BN_CLICKED(IDC_PROP_BUTTON, OnClickButton)
	ON_EN_KILLFOCUS(IDC_PROP_STATIC, OnKillfocusStatic)
	ON_CBN_KILLFOCUS(IDC_PROP_COMBBOX, OnKillfocusCmbBox)
	ON_EN_KILLFOCUS(IDC_PROP_EDITBOX, OnKillfocusEditBox)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleAttributeList Attributes handlers

int ArxRleAttributeList::AddPropItem(ArxRleAttributeListItem *&pItem)
{
	int idx = AddString(_T(""));
	m_vecItems.AddItem(pItem);
	SetItemDataPtr(idx, pItem);
	m_itemCount++;
	return idx;
}

int ArxRleAttributeList::InsertPropItem(int index, ArxRleAttributeListItem *&pItem)
{
	int idx = InsertString(index,_T(""));
	m_vecItems.InsertItem(index,pItem);
	SetItemDataPtr(idx, pItem);
	m_itemCount++;
	return idx;
}

int ArxRleAttributeList::GetCurSel()
{
	return m_curSel;
}

void ArxRleAttributeList::SetItemHeight(double height)
{
	m_nItemHeight = height;
}

double ArxRleAttributeList::GetItemHeight() const
{
	return m_nItemHeight;
}

void ArxRleAttributeList::DelItem(int index)
{
	DeleteString(index);
	m_vecItems.DelItem(index);
	m_itemCount--;
}

void ArxRleAttributeList::DelItems()
{
	for(; m_itemCount > 0; m_itemCount--)
		DeleteString(0);
	m_vecItems.DelItems();
}

void ArxRleAttributeList::SetGridColor(COLORREF clrGrid)
{
	m_clrGrid = clrGrid;
}

COLORREF ArxRleAttributeList::GetGridColor() const
{
	return m_clrGrid;
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleAttributeList message handlers

void ArxRleAttributeList::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = m_nItemHeight;	//默认属性条高度为20个像素
}

void ArxRleAttributeList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	UINT index = lpDrawItemStruct->itemID;
	if (index != (UINT) - 1)
	{
		// get the ArxRleAttributeListItem for the current row
		ArxRleAttributeListItem *pItem = (ArxRleAttributeListItem*)GetItemDataPtr(index);
	
		// Create rectangle for two row column
		CRect rcFull = lpDrawItemStruct->rcItem;
		rcFull.DeflateRect(3,0);
		CRect rcVal = rcFull;
		if (m_nDivider == 0) m_nDivider = rcVal.Width() / 2;
		rcVal.left = m_nDivider;
		CRect rcKey = rcFull;
		rcKey.left += 13;
		rcKey.right = rcVal.left;

		if(pItem->m_itemType != PIT_SEPARATOR)
		{
			CPen pen(PS_SOLID,1,m_clrGrid);
			CPen *pOldPen = dc.SelectObject(&pen);

			// draw two rectangles, one for each row column
			dc.FillSolidRect(rcKey, pItem->m_bkKeyColor);
			dc.DrawEdge(rcKey,EDGE_SUNKEN,BF_BOTTOMRIGHT);
			dc.FillSolidRect(rcVal, pItem->m_bkValColor);
			dc.DrawEdge(rcVal,EDGE_SUNKEN,BF_BOTTOM);

			if(pItem->m_itemType == PIT_NULL)
			{
				MoveToEx(lpDrawItemStruct->hDC,rcKey.left,rcKey.top,NULL);
				LineTo(lpDrawItemStruct->hDC,rcKey.right-2,rcKey.bottom-2);
			}

			MoveToEx(lpDrawItemStruct->hDC,rcKey.left,rcKey.top,NULL);
			LineTo(lpDrawItemStruct->hDC,rcVal.right,rcVal.top);
			LineTo(lpDrawItemStruct->hDC,rcVal.right,rcVal.bottom);
			LineTo(lpDrawItemStruct->hDC,rcKey.left,rcKey.bottom);
			LineTo(lpDrawItemStruct->hDC,rcKey.left,rcKey.top);

			MoveToEx(lpDrawItemStruct->hDC,rcVal.left,rcVal.top,NULL);
			LineTo(lpDrawItemStruct->hDC,rcVal.left,rcVal.bottom);
			dc.SelectObject(pOldPen);

			// Customize the text size
			CFont font;
			LOGFONT lf;
			memset(&lf,0,sizeof(lf));
			lf.lfWeight = pItem->m_ftWeight;
			lf.lfHeight = pItem->m_ftHeight;
			lf.lfWidth = pItem->m_ftWidth;
			lf.lfItalic = pItem->m_ftItalic;
			wcsncpy(lf.lfFaceName, pItem->m_ftName, _tcslen(lf.lfFaceName));
			font.CreateFontIndirect(&lf);
			CFont *pOldFont;

			if(pItem->m_ftKeyVal == 0 || pItem->m_ftKeyVal == 1)
				pOldFont = dc.SelectObject(&font);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(pItem->m_txtKeyColor);
			dc.DrawText(pItem->m_curKey, CRect(rcKey.left+3,rcKey.top+3,
				rcKey.right-3,rcKey.bottom-3), DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			if(pItem->m_ftKeyVal == 0 || pItem->m_ftKeyVal == 1)
				dc.SelectObject(pOldFont);

			if(pItem->m_ftKeyVal == 0 || pItem->m_ftKeyVal == 2)
				pOldFont = dc.SelectObject(&font);

			if(pItem->m_itemType == PIT_COLOR)
			{
				CRect rcClr = rcVal;
				int wh = rcClr.Height()-10;
				rcClr.left = rcClr.left+5;
				rcClr.right = rcClr.left+wh;
				rcClr.top = rcClr.top+5;
				rcClr.bottom = rcClr.top+wh;
				rcVal.left = rcClr.right+3;

				CPen pen(PS_SOLID,1,m_clrGrid);
				CPen *pOldPen = dc.SelectObject(&pen);
				dc.FillSolidRect(rcClr, pItem->m_txtValColor);
				MoveToEx(lpDrawItemStruct->hDC,rcClr.left,rcClr.top,NULL);
				LineTo(lpDrawItemStruct->hDC,rcClr.right,rcClr.top);
				LineTo(lpDrawItemStruct->hDC,rcClr.right,rcClr.bottom);
				LineTo(lpDrawItemStruct->hDC,rcClr.left,rcClr.bottom);
				LineTo(lpDrawItemStruct->hDC,rcClr.left,rcClr.top);
				dc.SelectObject(pOldPen);

				dc.SetTextColor(pItem->m_txtKeyColor);
			}
			else
				dc.SetTextColor(pItem->m_txtValColor);

			dc.DrawText(pItem->m_curValue,CRect(rcVal.left+3,rcVal.top+3,
				rcVal.right-3,rcVal.bottom-3), DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			if(pItem->m_ftKeyVal == 0 || pItem->m_ftKeyVal == 2)
				dc.SelectObject(pOldFont);
		}
		else
		{
			CPen pen(PS_SOLID,1,m_clrGrid);
			CPen *pOldPen = dc.SelectObject(&pen);

			rcFull.top += 3;
			dc.FillSolidRect(rcFull, pItem->m_bkKeyColor);

			MoveToEx(lpDrawItemStruct->hDC,rcFull.left,rcFull.top,NULL);
			LineTo(lpDrawItemStruct->hDC,rcFull.right,rcFull.top);
			LineTo(lpDrawItemStruct->hDC,rcFull.right,rcFull.bottom);
			LineTo(lpDrawItemStruct->hDC,rcFull.left,rcFull.bottom);
			LineTo(lpDrawItemStruct->hDC,rcFull.left,rcFull.top);
			dc.SelectObject(pOldPen);

			CBrush brush(pItem->m_txtValColor);
			CBrush *pOldBrush = dc.SelectObject(&brush);
			int gap = rcFull.Height()/6;
			int x = rcFull.right-rcFull.Height()/2;
			int y = rcFull.top+rcFull.Height()/2;
			if(pItem->m_isExpand)
			{
				POINT point[3] = {
					{x,y+gap/2},
					{x+gap/2+2,y-gap/2},
					{x-gap/2-2,y-gap/2}};
				dc.Polygon(point,3);
			}
			else
			{
				POINT point[3] = {
					{x,y-gap/2},
					{x+gap/2+2,y+gap/2},
					{x-gap/2-2,y+gap/2}};
				dc.Polygon(point,3);
			}
			dc.SelectObject(pOldBrush);

			// Customize the text size
			CFont font;
			LOGFONT lf;
			memset(&lf,0,sizeof(lf));
			lf.lfWeight = pItem->m_ftWeight;
			lf.lfHeight = pItem->m_ftHeight;
			lf.lfWidth = pItem->m_ftWidth;
			lf.lfItalic = pItem->m_ftItalic;
			wcsncpy(lf.lfFaceName, pItem->m_ftName, _tcslen(lf.lfFaceName));
			font.CreateFontIndirect(&lf);
			CFont *pOldFont;

			if(pItem->m_ftKeyVal == 0 || pItem->m_ftKeyVal == 1)
				pOldFont = dc.SelectObject(&font);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(pItem->m_txtKeyColor);
			dc.DrawText(pItem->m_curKey, CRect(rcFull.left+3,rcFull.top+3,
				rcFull.right-3,rcFull.bottom-3), DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			if(pItem->m_ftKeyVal == 0 || pItem->m_ftKeyVal == 1)
				dc.SelectObject(pOldFont);
		}
	}

	dc.Detach();
}

BOOL ArxRleAttributeList::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CAcUiListBox::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~(LBS_OWNERDRAWVARIABLE | LBS_SORT);
	cs.style |= LBS_OWNERDRAWFIXED;

	m_bDivIsSet = FALSE;
	m_nDivider = 0;
	m_nItemHeight = 20;
	m_bTracking = FALSE;
	m_curSel = -1;
	m_itemCount = 0;
	m_bItemActive = FALSE;
	m_clrGrid = RGB(0,0,0);

	m_pStatic = NULL;
	m_pComboBox = NULL;
	m_pEditBox = NULL;
	m_pButton = NULL;
	m_pSymbolComboBox = NULL;
	m_pColorComboBox = NULL;
	m_pLineTypeComboBox = NULL;
	m_pLineWeightComboBox = NULL;

	m_hCursorSize = AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
	m_hCursorArrow = AfxGetApp()->LoadStandardIcon(IDC_ARROW);

	m_ftSerif8Font = new CFont;
	m_ftSerif8Font->CreateFont(
		12, 0, 0, 0, FW_NORMAL, FALSE,
		FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY,                         
		DEFAULT_PITCH | FF_SWISS, _T("MS Sans Serif"));

	return TRUE;
}

void ArxRleAttributeList::PreSubclassWindow()
{
	m_bDivIsSet = FALSE;
	m_nDivider = 0;
	m_nItemHeight = 20;
	m_bTracking = FALSE;
	m_curSel = -1;
	m_itemCount = 0;
	m_bItemActive = FALSE;
	m_clrGrid = RGB(0,0,0);

	m_pStatic = NULL;
	m_pComboBox = NULL;
	m_pEditBox = NULL;
	m_pButton = NULL;
	m_pSymbolComboBox = NULL;
	m_pColorComboBox = NULL;
	m_pLineTypeComboBox = NULL;
	m_pLineWeightComboBox = NULL;

	m_hCursorSize = AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
	m_hCursorArrow = AfxGetApp()->LoadStandardIcon(IDC_ARROW);

	m_ftSerif8Font = new CFont;
	m_ftSerif8Font->CreateFont(
		12, 0, 0, 0, FW_NORMAL, FALSE,
		FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY,                         
		DEFAULT_PITCH | FF_SWISS, _T("MS Sans Serif"));
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleAttributeList Generated message map function

int ArxRleAttributeList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAcUiListBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_bDivIsSet = FALSE;
	m_nDivider = 0;
	m_nItemHeight = 20;
	m_bTracking = FALSE;
	m_curSel = -1;
	m_itemCount = 0;
	m_bItemActive = FALSE;
	m_clrGrid = RGB(0,0,0);

	m_pStatic = NULL;
	m_pComboBox = NULL;
	m_pEditBox = NULL;
	m_pButton = NULL;
	m_pSymbolComboBox = NULL;
	m_pColorComboBox = NULL;
	m_pLineTypeComboBox = NULL;
	m_pLineWeightComboBox = NULL;

	m_hCursorSize = AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
	m_hCursorArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);

	m_ftSerif8Font = new CFont;
	m_ftSerif8Font->CreateFont(
		12, 0, 0, 0, FW_NORMAL, FALSE,
		FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY,                         
		DEFAULT_PITCH | FF_SWISS, _T("MS Sans Serif"));

	return 0;
}

void ArxRleAttributeList::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bTracking)
	{
		// move divider line to the mouse pos. if columns are currently being resized
		CClientDC dc(this);
		// remove old divider line
		InvertLine(&dc,CPoint(m_nOldDivX,m_nDivTop),CPoint(m_nOldDivX,m_nDivBtm));
		// draw new divider line
		InvertLine(&dc,CPoint(point.x,m_nDivTop),CPoint(point.x,m_nDivBtm));
		m_nOldDivX = point.x;
	}
	else if ((point.x >= m_nDivider-5) && (point.x <= m_nDivider+5))
		// set the cursor to a sizing cursor if the cursor is over the row divider
		::SetCursor(m_hCursorSize);
	else
		CAcUiListBox::OnMouseMove(nFlags, point);
}

void ArxRleAttributeList::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((point.x>=m_nDivider-5) && (point.x<=m_nDivider+5))
	{
		// if mouse clicked on divider line, then start resizing

		::SetCursor(m_hCursorSize);

		CRect windowRect;
		GetWindowRect(windowRect);
		windowRect.left += 10; windowRect.right -= 20;
		// do not let mouse leave the list box boundary
		::ClipCursor(windowRect);

		m_pStatic != NULL ? m_pStatic->ShowWindow(SW_HIDE) : 0;
		m_pComboBox != NULL ? m_pComboBox->ShowWindow(SW_HIDE) : 0;
		m_pEditBox != NULL ? m_pEditBox->ShowWindow(SW_HIDE) : 0;
		m_pButton != NULL ? m_pButton->ShowWindow(SW_HIDE) : 0;
		m_pSymbolComboBox != NULL ? m_pSymbolComboBox->ShowWindow(SW_HIDE) : 0;
		m_pColorComboBox != NULL ? m_pColorComboBox->ShowWindow(SW_HIDE) : 0;
		m_pLineTypeComboBox != NULL ? m_pLineTypeComboBox->ShowWindow(SW_HIDE) : 0;
		m_pLineWeightComboBox != NULL ? m_pLineWeightComboBox->ShowWindow(SW_HIDE) : 0;

		CRect clientRect;
		GetClientRect(clientRect);

		m_bTracking = TRUE;
		m_bItemActive = FALSE;
		m_nDivTop = clientRect.top;
		m_nDivBtm = clientRect.bottom;
		m_nOldDivX = point.x;

		CClientDC dc(this);
		InvertLine(&dc,CPoint(m_nOldDivX,m_nDivTop),CPoint(m_nOldDivX,m_nDivBtm));

		// capture the mouse
		SetCapture();
	}
	else
	{
		m_bTracking = FALSE;

		BOOL loc;
		int index = ItemFromPoint(point,loc);
		CRect rect;
		GetItemRect(index,&rect);
		rect.left += m_nDivider;
		if(rect.PtInRect(point))
		{
			m_curSel = index;
			m_bItemActive = TRUE;

			ArxRleAttributeListItem *pItem = (ArxRleAttributeListItem*)GetItemData(m_curSel);
			if(pItem->m_idxExpand != -1)
			{
				rect.top += 3;
				int x = rect.right-rect.Height()/2;
				int y = rect.top+rect.Height()/2;
				pItem->m_rcExpand = CRect(x-rect.Height()/2,y-rect.Height()/2,x+rect.Height()/2,y+rect.Height()/2);
				if(pItem->m_rcExpand.PtInRect(point))
				{
					int idx = m_curSel;
					//展开或收缩相应属性条目
					if(pItem->m_isExpand) //展开
					{
						for(int i=pItem->m_idxExpand+1; i<m_itemCount; i++)
						{
							if(m_vecItems[i]->m_idxExpand == -1)
							{
								idx++;
								InsertString(idx,L"");
								SetItemDataPtr(idx, m_vecItems[i]);
							}
							else
								break;
						}
					}
					else     //收缩
					{
						for(int i = pItem->m_idxExpand+1; i<m_itemCount; i++)
						{
							if(m_vecItems[i]->m_idxExpand == -1)
							{
								DeleteString(idx);
							}
							else
								break;
						}
					}
					pItem->m_isExpand = !pItem->m_isExpand;
					m_vecItems.SetItem(pItem->m_idxExpand,pItem);
					SetItemDataPtr(m_curSel, pItem);
				}
			}
		}
		else
		{
			m_bItemActive = FALSE;
			m_pStatic != NULL ? m_pStatic->ShowWindow(SW_HIDE) : 0;
			m_pComboBox != NULL ? m_pComboBox->ShowWindow(SW_HIDE) : 0;
			m_pEditBox != NULL ? m_pEditBox->ShowWindow(SW_HIDE) : 0;
			m_pButton != NULL ? m_pButton->ShowWindow(SW_HIDE) : 0;
			m_pSymbolComboBox != NULL ? m_pSymbolComboBox->ShowWindow(SW_HIDE) : 0;
			m_pColorComboBox != NULL ? m_pColorComboBox->ShowWindow(SW_HIDE) : 0;
			m_pLineTypeComboBox != NULL ? m_pLineTypeComboBox->ShowWindow(SW_HIDE) : 0;
			m_pLineWeightComboBox != NULL ? m_pLineWeightComboBox->ShowWindow(SW_HIDE) : 0;
		}

		CAcUiListBox::OnLButtonDown(nFlags, point);
	}
}

void ArxRleAttributeList::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bTracking)
	{
		// if columns were being resized then this indicates
		// that mouse is up so resizing is dong. Need to redraw
		// columns to reflect their new widths.

		m_bTracking = FALSE;
		// if mouse was captured then release it
		if (GetCapture() == this)
			::ReleaseCapture();

		::ClipCursor(NULL);

		CClientDC dc(this);
		InvertLine(&dc,CPoint(point.x,m_nDivTop),CPoint(point.x,m_nDivBtm));
		// set the divider position to the new value
		m_nDivider = point.x;
		// redraw
		Invalidate();
	}
	else
	{
		CAcUiListBox::OnLButtonUp(nFlags, point);
	}
}

void ArxRleAttributeList::OnKillFocus(CWnd* pNewWnd)
{
	CAcUiListBox::OnKillFocus(pNewWnd);
}

void ArxRleAttributeList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_pStatic != NULL ? m_pStatic->ShowWindow(SW_HIDE) : 0;
	m_pComboBox != NULL ? m_pComboBox->ShowWindow(SW_HIDE) : 0;
	m_pEditBox != NULL ? m_pEditBox->ShowWindow(SW_HIDE) : 0;
	m_pButton != NULL ? m_pButton->ShowWindow(SW_HIDE) : 0;
	m_pSymbolComboBox != NULL ? m_pSymbolComboBox->ShowWindow(SW_HIDE) : 0;
	m_pColorComboBox != NULL ? m_pColorComboBox->ShowWindow(SW_HIDE) : 0;
	m_pLineTypeComboBox != NULL ? m_pLineTypeComboBox->ShowWindow(SW_HIDE) : 0;
	m_pLineWeightComboBox != NULL ? m_pLineWeightComboBox->ShowWindow(SW_HIDE) : 0;

	CAcUiListBox::OnVScroll(nSBCode, nPos, pScrollBar);
}

void ArxRleAttributeList::OnLbnSelchange()
{
	CRect rect;
	CString lBoxSelText;

	if(!m_bItemActive) return;
	GetItemRect(m_curSel, rect);
	rect.DeflateRect(3,0);
	rect.left = m_nDivider;
	rect.top += 1;

	ArxRleAttributeListItem *pItem = (ArxRleAttributeListItem*)GetItemDataPtr(m_curSel);

	m_pButton != NULL ? m_pButton->ShowWindow(SW_HIDE) : 0;
	if (pItem->m_itemType == PIT_COMBO)
	{
		// display the combo box. If the combo box has already been
		// created then simply move it to the new location, else create it
		m_nLastBox = 0;
		if(m_pComboBox == NULL)
		{
			m_pComboBox = new CAcUiComboBox;
			rect.bottom += 100;
			m_pComboBox->Create(CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD | WS_BORDER,
				rect,this,IDC_PROP_COMBBOX);

			m_pComboBox->SetFont(m_ftSerif8Font);
			m_pComboBox->SetItemHeight(-1,13);
		}
		else
			m_pComboBox->MoveWindow(rect);

		// add the choices for this particular property
		CString cmbItems = pItem->m_cmbItems;
		lBoxSelText = pItem->m_curValue;

		m_pComboBox->ResetContent();
		int i = 0,j = 0;
		while ((j=cmbItems.Find('|',i)) != -1)
		{
			m_pComboBox->AddString(cmbItems.Mid(i,j-i));
			i=j+1;
		}

		m_pComboBox->AddString(cmbItems.Mid(i,cmbItems.GetLength()-i));

		m_pComboBox->ShowWindow(SW_SHOW);
		m_pComboBox->SetFocus();

		// jump to the property's current value in the combo box
		int k = m_pComboBox->FindStringExact(0,lBoxSelText);
		if (k != CB_ERR)
			m_pComboBox->SetCurSel(k);
		else
			m_pComboBox->SetCurSel(0);
	}
	else if (pItem->m_itemType==PIT_EDIT)
	{
		// display edit box
		m_nLastBox = 1;
		m_prevSel = m_curSel;

		if(m_pEditBox == NULL)
		{
			m_pEditBox = new CAcUiEdit;
			m_pEditBox->Create(ES_LEFT | ES_AUTOHSCROLL | WS_VISIBLE | WS_CHILD | WS_BORDER,
				rect,this,IDC_PROP_EDITBOX);

			m_pEditBox->SetFont(m_ftSerif8Font);
		}
		else
			m_pEditBox->MoveWindow(rect);

		lBoxSelText = pItem->m_curValue;

		m_pEditBox->ShowWindow(SW_SHOW);
		m_pEditBox->SetFocus();
		// set the text in the edit box to the property's current value
		m_pEditBox->SetWindowText(lBoxSelText);
	}
	else if (pItem->m_itemType == PIT_LAYER)
	{
		// display the combo box. If the combo box has already been
		// created then simply move it to the new location, else create it
		m_nLastBox = 0;
		if(m_pSymbolComboBox == NULL)
		{
			m_pSymbolComboBox = new CAcUiSymbolComboBox;
			rect.bottom += 100;
			m_pSymbolComboBox->Create(CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD | WS_BORDER,
				rect,this,IDC_PROP_COMBBOX);

			m_pSymbolComboBox->SetFont(m_ftSerif8Font);
			m_pSymbolComboBox->SetItemHeight(-1,13);
		}
		else
			m_pSymbolComboBox->MoveWindow(rect);

		// add the choices for this particular property
		CString cmbItems = pItem->m_cmbItems;
		lBoxSelText = pItem->m_curValue;

		m_pSymbolComboBox->ResetContent();
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
							m_pSymbolComboBox->AddString(sName);
						elem->close();
					}
				}
				delete iter;
				pLt->close();
			}
		}

		m_pSymbolComboBox->ShowWindow(SW_SHOW);
		m_pSymbolComboBox->SetFocus();

		// jump to the property's current value in the combo box
		int i = m_pSymbolComboBox->FindStringExact(0,lBoxSelText);
		if (i != CB_ERR)
			m_pSymbolComboBox->SetCurSel(i);
		else
			m_pSymbolComboBox->SetCurSel(0);
	}
	else if (pItem->m_itemType == PIT_TEXTSTYLE)
	{
		// display the combo box. If the combo box has already been
		// created then simply move it to the new location, else create it
		m_nLastBox = 0;
		if(m_pSymbolComboBox == NULL)
		{
			m_pSymbolComboBox = new CAcUiSymbolComboBox;
			rect.bottom += 100;
			m_pSymbolComboBox->Create(CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD | WS_BORDER,
				rect,this,IDC_PROP_COMBBOX);

			m_pSymbolComboBox->SetFont(m_ftSerif8Font);
			m_pSymbolComboBox->SetItemHeight(-1,13);
		}
		else
			m_pSymbolComboBox->MoveWindow(rect);

		// add the choices for this particular property
		CString cmbItems = pItem->m_cmbItems;
		lBoxSelText = pItem->m_curValue;

		m_pSymbolComboBox->ResetContent();
		AcDbTextStyleTable *pTt;
		if (Acad::eOk == ARXRLEDB->getTextStyleTable( pTt, AcDb::kForRead ))
		{
			ArxRleApply<TextStyleTable> apply = ArxRleApply<TextStyleTable>( pTt, AcDb::kForRead );
			TextStyleTable::Iterator* iter;
			apply.createIterator( iter );
			if (NULL != iter)
			{
				CString strs;
				for ( ; !iter->done(); apply.stepIterator( iter ))
				{
					TextStyleTable::Element* elem = apply.getElement( iter );
					if (NULL != elem)
					{
						ACHAR* sName;
						elem->getName(sName);
						if(ArxRleString(sName).GetLength() > 0)
							m_pSymbolComboBox->AddString(sName);
						elem->close();
					}
				}
				delete iter;
				pTt->close();
			}
		}

		m_pSymbolComboBox->ShowWindow(SW_SHOW);
		m_pSymbolComboBox->SetFocus();

		// jump to the property's current value in the combo box
		int i = m_pSymbolComboBox->FindStringExact(0,lBoxSelText);
		if (i != CB_ERR)
			m_pSymbolComboBox->SetCurSel(i);
		else
			m_pSymbolComboBox->SetCurSel(0);
	}
	else if (pItem->m_itemType == PIT_DIMSTYLE)
	{
		// display the combo box. If the combo box has already been
		// created then simply move it to the new location, else create it
		m_nLastBox = 0;
		if(m_pSymbolComboBox == NULL)
		{
			m_pSymbolComboBox = new CAcUiSymbolComboBox;
			rect.bottom += 100;
			m_pSymbolComboBox->Create(CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD | WS_BORDER,
				rect,this,IDC_PROP_COMBBOX);

			m_pSymbolComboBox->SetFont(m_ftSerif8Font);
			m_pSymbolComboBox->SetItemHeight(-1,13);
		}
		else
			m_pSymbolComboBox->MoveWindow(rect);

		// add the choices for this particular property
		CString cmbItems = pItem->m_cmbItems;
		lBoxSelText = pItem->m_curValue;

		m_pSymbolComboBox->ResetContent();
		AcDbDimStyleTable *pDt;
		if (Acad::eOk == ARXRLEDB->getDimStyleTable( pDt, AcDb::kForRead ))
		{
			ArxRleApply<DimStyleTable> apply = ArxRleApply<DimStyleTable>( pDt, AcDb::kForRead );
			DimStyleTable::Iterator* iter;
			apply.createIterator( iter );
			if (NULL != iter)
			{
				CString strs;
				for ( ; !iter->done(); apply.stepIterator( iter ))
				{
					DimStyleTable::Element* elem = apply.getElement( iter );
					if (NULL != elem)
					{
						ACHAR* sName;
						elem->getName(sName);
						if(ArxRleString(sName).GetLength() > 0)
							m_pSymbolComboBox->AddString(sName);
						elem->close();
					}
				}
				delete iter;
				pDt->close();
			}
		}

		m_pSymbolComboBox->ShowWindow(SW_SHOW);
		m_pSymbolComboBox->SetFocus();

		// jump to the property's current value in the combo box
		int i = m_pSymbolComboBox->FindStringExact(0,lBoxSelText);
		if (i != CB_ERR)
			m_pSymbolComboBox->SetCurSel(i);
		else
			m_pSymbolComboBox->SetCurSel(0);
	}
	else if (pItem->m_itemType == PIT_WORKSTYLE)
	{
		// display the combo box. If the combo box has already been
		// created then simply move it to the new location, else create it
		m_nLastBox = 0;
		if(m_pSymbolComboBox == NULL)
		{
			m_pSymbolComboBox = new CAcUiSymbolComboBox;
			rect.bottom += 100;
			m_pSymbolComboBox->Create(CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD | WS_BORDER,
				rect,this,IDC_PROP_COMBBOX);

			m_pSymbolComboBox->SetFont(m_ftSerif8Font);
			m_pSymbolComboBox->SetItemHeight(-1,13);
		}
		else
			m_pSymbolComboBox->MoveWindow(rect);

		// add the choices for this particular property
		CString cmbItems = pItem->m_cmbItems;
		lBoxSelText = pItem->m_curValue;

		m_pSymbolComboBox->ResetContent();
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
							m_pSymbolComboBox->AddString(sName);
						elem->close();
					}
				}
				delete iter;
				pDict->close();
			}
		}

		m_pSymbolComboBox->ShowWindow(SW_SHOW);
		m_pSymbolComboBox->SetFocus();

		// jump to the property's current value in the combo box
		int i = m_pSymbolComboBox->FindStringExact(0,lBoxSelText);
		if (i != CB_ERR)
			m_pSymbolComboBox->SetCurSel(i);
		else
			m_pSymbolComboBox->SetCurSel(0);
	}
	else if (pItem->m_itemType == PIT_COLOR)
	{
		if (FALSE)
		{
			COLORREF initClr;
			CString currClr = pItem->m_curValue;
			// parse the property's current color value
			if (currClr.Find(L"RGB") > -1)
			{
				int j = currClr.Find(',',3);
				CString bufr = currClr.Mid(4,j-4);
				int RVal = _tstoi(bufr);
				int j2 = currClr.Find(',',j+1);
				bufr = currClr.Mid(j+1,j2-(j+1));
				int GVal = _tstoi(bufr);
				int j3 = currClr.Find(')',j2+1);
				bufr = currClr.Mid(j2+1,j3-(j2+1));
				int BVal = _tstoi(bufr);
				initClr = RGB(RVal,GVal,BVal);
			}
			else
				initClr = 0;

			CColorDialog ClrDlg(initClr);

			if (IDOK == ClrDlg.DoModal())
			{
				COLORREF selClr = ClrDlg.GetColor();
				CString clrStr;
				clrStr.Format(L"RGB(%d,%d,%d)",GetRValue(selClr),
					GetGValue(selClr),GetBValue(selClr));
				m_pButton->ShowWindow(SW_HIDE);

				pItem->m_curValue = clrStr;
				pItem->m_txtValColor = selClr;
				m_vecItems.SetItem(m_curSel,pItem);
				Invalidate();
			}
		}

		if(m_pColorComboBox == NULL)
		{
			m_pColorComboBox = new CAcUiColorComboBox;
			rect.bottom += 100;
			m_pColorComboBox->Create(CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS | WS_VISIBLE | WS_CHILD | WS_BORDER,
				rect,this,IDC_PROP_COMBBOX);

			m_pColorComboBox->SetFont(m_ftSerif8Font);
			m_pColorComboBox->SetItemHeight(-1,13);
		}
		else
			m_pColorComboBox->MoveWindow(rect);

		m_pColorComboBox->ShowWindow(SW_SHOW);
		m_pColorComboBox->SetFocus();

		// jump to the property's current value in the combo box
		int i = m_pColorComboBox->FindItemByColorIndex(m_pColorComboBox->GetColorIndex(pItem->m_txtValColor));
		if (i != CB_ERR)
			m_pColorComboBox->SetCurSel(i);
		else
			m_pColorComboBox->SetCurSel(0);
	}
	else if (pItem->m_itemType == PIT_LINETYPE)
	{
		if(m_pLineTypeComboBox == NULL)
		{
			m_pLineTypeComboBox = new CAcUiLineTypeComboBox;
			rect.bottom += 100;
			m_pLineTypeComboBox->Create(CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS | WS_VISIBLE | WS_CHILD | WS_BORDER,
				rect,this,IDC_PROP_COMBBOX);

			m_pLineTypeComboBox->SetFont(m_ftSerif8Font);
			m_pLineTypeComboBox->SetItemHeight(-1,13);
		}
		else
			m_pLineTypeComboBox->MoveWindow(rect);

		m_pLineTypeComboBox->ShowWindow(SW_SHOW);
		m_pLineTypeComboBox->SetFocus();

		// jump to the property's current value in the combo box
		lBoxSelText = pItem->m_curValue;
		int i = m_pLineTypeComboBox->FindStringExact(0,lBoxSelText);
		if (i != CB_ERR)
			m_pLineTypeComboBox->SetCurSel(i);
		else
			m_pLineTypeComboBox->SetCurSel(0);
	}
	else if (pItem->m_itemType == PIT_LINEWEIGHT)
	{
		if(m_pLineWeightComboBox == NULL)
		{
			m_pLineWeightComboBox = new CAcUiLineWeightComboBox;
			rect.bottom += 100;
			m_pLineWeightComboBox->Create(CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS | WS_VISIBLE | WS_CHILD | WS_BORDER,
				rect,this,IDC_PROP_COMBBOX);

			m_pLineWeightComboBox->SetFont(m_ftSerif8Font);
			m_pLineWeightComboBox->SetItemHeight(-1,13);
		}
		else
			m_pLineWeightComboBox->MoveWindow(rect);

		m_pLineWeightComboBox->ShowWindow(SW_SHOW);
		m_pLineWeightComboBox->SetFocus();

		// jump to the property's current value in the combo box
		lBoxSelText = pItem->m_curValue;
		int i = m_pLineWeightComboBox->FindItemByLineWeight(_tstoi(lBoxSelText));
		if (i != CB_ERR)
			m_pLineWeightComboBox->SetCurSel(i);
		else
			m_pLineWeightComboBox->SetCurSel(0);
	}
	else if(pItem->m_itemType == PIT_SEPARATOR)
	{

	}
	else if(pItem->m_itemType == PIT_BLANK || pItem->m_itemType == PIT_NULL)
	{

	}
	else
		DisplayButton(rect, pItem->m_itemType);
}

void ArxRleAttributeList::OnSelchangeCmbBox()
{
	ArxRleAttributeListItem *pItem = (ArxRleAttributeListItem*)GetItemDataPtr(m_curSel);

	switch(pItem->m_itemType)
	{
	case PIT_COMBO:
		if(m_pComboBox != NULL) m_pComboBox->GetLBText(m_pComboBox->GetCurSel(),pItem->m_curValue);
		break;
	case PIT_LAYER:
		if(m_pSymbolComboBox != NULL)
		{
			m_pSymbolComboBox->GetLBText(m_pSymbolComboBox->GetCurSel(),pItem->m_curValue);
			pItem->m_objId = FindLayer(pItem->m_curValue);
		}
		break;
	case PIT_TEXTSTYLE:
		if(m_pSymbolComboBox != NULL)
		{
			m_pSymbolComboBox->GetLBText(m_pSymbolComboBox->GetCurSel(),pItem->m_curValue);
			pItem->m_objId = FindTextStyle(pItem->m_curValue);
		}
		break;
	case PIT_DIMSTYLE:
		if(m_pSymbolComboBox != NULL)
		{
			m_pSymbolComboBox->GetLBText(m_pSymbolComboBox->GetCurSel(),pItem->m_curValue);
			pItem->m_objId = GetDimensionStyle(pItem->m_curValue);
		}
		break;
	case PIT_WORKSTYLE:
		if(m_pSymbolComboBox != NULL)
		{
			m_pSymbolComboBox->GetLBText(m_pSymbolComboBox->GetCurSel(),pItem->m_curValue);
			pItem->m_objId = ArxRleNetPlanWorkStyle::getWorkStyle(pItem->m_curValue);
		}
		break;
	case PIT_COLOR:
		if(m_pColorComboBox != NULL)
		{
			m_pColorComboBox->GetLBText(m_pColorComboBox->GetCurSel(),pItem->m_curValue);
			int aci = m_pColorComboBox->GetItemColorIndex(m_pColorComboBox->GetCurSel());
			COLORREF clr = m_pColorComboBox->GetColorFromIndex(aci);
			pItem->m_txtValColor = clr;
		}
		break;
	case PIT_LINETYPE:
		if(m_pLineTypeComboBox != NULL)
		{
			m_pLineTypeComboBox->GetLBText(m_pLineTypeComboBox->GetCurSel(),pItem->m_curValue);
			pItem->m_objId = m_pLineTypeComboBox->getOIDSel(m_pLineTypeComboBox->GetCurSel());
		}
		break;
	case PIT_LINEWEIGHT:
		if(m_pLineWeightComboBox != NULL)
		{
			int lw = m_pLineWeightComboBox->GetItemLineWeight(m_pLineWeightComboBox->GetCurSel());
			pItem->m_curValue.Format(L"%d",lw);
		}
		break;
	}

	m_vecItems.SetItem(m_curSel,pItem);
}

void ArxRleAttributeList::OnChangeEditBox()
{
	CString newStr;
	m_pEditBox->GetWindowText(newStr);

	ArxRleAttributeListItem *pItem = (ArxRleAttributeListItem*)GetItemDataPtr(m_curSel);
	pItem->m_curValue = newStr;
	m_vecItems.SetItem(m_curSel,pItem);
}

void ArxRleAttributeList::OnClickButton()
{
	ArxRleAttributeListItem *pItem = (ArxRleAttributeListItem*)GetItemDataPtr(m_curSel);

	// display the appropriate common dialog depending on what type 
	// of chooser is associated with the property
	if (pItem->m_itemType == PIT_FILE)
	{
		CString SelectedFile;

		//CString Filter("Gif Files (*.ico)|*.ico|Drawing (*.dwg)|*.dwg||");
		CString Filter(pItem->m_sufName);

		CFileDialog FileDlg(TRUE, NULL, NULL, NULL, Filter);

		CString currPath = pItem->m_curValue;
		FileDlg.m_ofn.lpstrTitle = L"Select File";
		if (currPath.GetLength() > 0)
			FileDlg.m_ofn.lpstrInitialDir = currPath.Left(
			currPath.GetLength() - currPath.ReverseFind('\\'));

		if (IDOK == FileDlg.DoModal())
		{
			SelectedFile = FileDlg.GetPathName();

			m_pButton->ShowWindow(SW_HIDE);

			pItem->m_curValue = SelectedFile;
			m_vecItems.SetItem(m_curSel,pItem);
			Invalidate();
		}
	}
	else if (pItem->m_itemType == PIT_FONT)
	{
		//默认字体对话框字体属性,
		LOGFONT ftTmp;
		memset(&ftTmp,0,sizeof(LOGFONT)); 
		lstrcpy(ftTmp.lfFaceName,pItem->m_curValue);
		ftTmp.lfHeight = pItem->m_ftWidth;
		ftTmp.lfEscapement = 0; 
		ftTmp.lfUnderline = FALSE; 
		ftTmp.lfStrikeOut = FALSE;
		ftTmp.lfClipPrecision = CLIP_LH_ANGLES;     //与坐标映射方式无关
		ftTmp.lfPitchAndFamily = FF_SWISS;
		ftTmp.lfCharSet = GB2312_CHARSET;

		CFontDialog FontDlg(&ftTmp,CF_EFFECTS | CF_SCREENFONTS,NULL,this);

		if(IDOK == FontDlg.DoModal())
		{
			CString faceName = FontDlg.GetFaceName();

			m_pButton->ShowWindow(SW_HIDE);

			pItem->m_curValue = faceName;
			pItem->m_ftName = faceName;

			pItem->m_ftColor = FontDlg.GetColor();           //将字色赋给m_lColor

			// 不能调用CFontDialog::GetSize(), 应该如下取得字体高度,
			memset(&ftTmp,0,sizeof(LOGFONT)); 
			FontDlg.GetCurrentFont(&ftTmp);
			pItem->m_ftWeight = ftTmp.lfWeight;
			pItem->m_ftHeight = ftTmp.lfHeight;
			pItem->m_ftWidth = ftTmp.lfWidth;
			m_vecItems.SetItem(m_curSel,pItem);
			Invalidate();
		}
	}
	else if (pItem->m_itemType == PIT_PATH)
	{
		BROWSEINFO bBinfo;
		memset(&bBinfo,0,sizeof(BROWSEINFO));  //定义结构并初始化
		bBinfo.hwndOwner=m_hWnd;//设置对话框所有者句柄
		CString retStr;
		bBinfo.lpszTitle=L"请选择安装路径：";
		bBinfo.ulFlags = BIF_RETURNONLYFSDIRS; //设置标志只允许选择目录    
		LPITEMIDLIST lpDlist;
		//用来保存返回信息的IDList，使用SHGetPathFromIDList函数转换为字符串
		lpDlist=SHBrowseForFolder(&bBinfo) ; //显示选择对话框
		if(lpDlist!=NULL)
		{
			SHGetPathFromIDList(lpDlist,(LPWSTR)(LPCTSTR)retStr);//把项目标识列表转化成目录
			if (retStr.Trim(_T(" ")).CompareNoCase(L"") != 0)
			{
				pItem->m_curValue = retStr;
				m_vecItems.SetItem(m_curSel,pItem);
			}
			Invalidate();
		}
	}
	else if (pItem->m_itemType == PIT_POINT)
	{
		m_pButton->ShowWindow(SW_HIDE);
		//int xyz = (*fnPtr)(1);
		pItem->m_curValue = L"X:0 Y:0 Z:0";
		m_vecItems.SetItem(m_curSel,pItem);
		Invalidate();
	}
}

void ArxRleAttributeList::OnKillfocusStatic()
{
	CString newStr;
	m_pStatic->ShowWindow(SW_HIDE);

	Invalidate();
}

void ArxRleAttributeList::OnKillfocusCmbBox()
{
	if(m_pComboBox != NULL) m_pComboBox->ShowWindow(SW_HIDE);
	if(m_pColorComboBox != NULL) m_pColorComboBox->ShowWindow(SW_HIDE);
	if(m_pSymbolComboBox != NULL) m_pSymbolComboBox->ShowWindow(SW_HIDE);
	if(m_pLineTypeComboBox != NULL) m_pLineTypeComboBox->ShowWindow(SW_HIDE);
	if(m_pLineWeightComboBox != NULL) m_pLineWeightComboBox->ShowWindow(SW_HIDE);

	Invalidate();
}

void ArxRleAttributeList::OnKillfocusEditBox()
{
	CString newStr;
	m_pEditBox->ShowWindow(SW_HIDE);

	Invalidate();
}

void ArxRleAttributeList::InvertLine(CDC* pDC,CPoint ptFrom, CPoint ptTo)
{
	int nOldMode = pDC->SetROP2(R2_NOT);

	pDC->MoveTo(ptFrom);
	pDC->LineTo(ptTo);

	pDC->SetROP2(nOldMode);
}

void ArxRleAttributeList::DisplayButton(CRect rcBtn, int itemType)
{
	// display a button if the property is a file/color/font chooser
	m_nLastBox = 2;
	m_prevSel = m_curSel;

	if (rcBtn.Width() > rcBtn.Height())
		rcBtn.left = rcBtn.right - rcBtn.Height();

	if(m_pButton == NULL)
	{
		m_pButton = new CButton;
		m_pButton->Create(L"...",BS_PUSHBUTTON | BS_ICON | BS_CENTER | WS_VISIBLE | WS_CHILD, rcBtn,this,IDC_PROP_BUTTON);
		m_pButton->SetFont(m_ftSerif8Font);
	}
	else
		m_pButton->MoveWindow(rcBtn);

	m_pButton->ShowWindow(SW_SHOW);
	m_pButton->SetFocus();
}