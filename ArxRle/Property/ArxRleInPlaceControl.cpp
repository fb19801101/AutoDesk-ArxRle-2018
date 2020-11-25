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

#include "ArxRleInPlaceControl.h"
#include "ArxRleUserMessage.h"

#define DEFAULT_IPLISTBOX_HEIGHT		16 * 8

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceEdit


ArxRleInPlaceEdit::ArxRleInPlaceEdit()
	: m_strInitText(_T(""))
{
}

ArxRleInPlaceEdit::ArxRleInPlaceEdit(const CString& strInitText)
	: m_strInitText(strInitText)
{
}

ArxRleInPlaceEdit::~ArxRleInPlaceEdit()
{
}


BEGIN_MESSAGE_MAP(ArxRleInPlaceEdit, CAdUiEdit)
	//{{AFX_MSG_MAP(ArxRleInPlaceEdit)
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceEdit message handlers

int ArxRleInPlaceEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CAdUiEdit::OnCreate(lpCreateStruct) == -1) 
		return -1;

	CFont* pFont = GetParent()->GetFont();
	SetFont(pFont);

	SetWindowText(m_strInitText);

	return 0;
}


void ArxRleInPlaceEdit::ProcessData()
{
}

void ArxRleInPlaceEdit::SetText(const CString& strText)
{
	m_strInitText = strText;

	SetWindowText(strText);
	SetSel(0, -1);
}

CString ArxRleInPlaceEdit::GetText()
{
	return m_strInitText;
}

BOOL ArxRleInPlaceEdit::PreTranslateMessage(MSG* pMsg)
{
	CWnd* pOwner = GetOwner();
	WPARAM nChar = pMsg->wParam;
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
		case VK_TAB:
			::PeekMessage(pMsg, NULL, NULL, NULL, PM_REMOVE);
			GetParent()->SetFocus();
			return TRUE;
		case VK_UP:
		case VK_DOWN:
			pOwner->SendMessage(WM_USER_ON_NEW_SELECTION, nChar);
			return TRUE;
		default:
			;
		}
	}

	return CAdUiEdit::PreTranslateMessage(pMsg);
}

void ArxRleInPlaceEdit::OnKillFocus(CWnd* pNewWnd)
{
	CAdUiEdit::OnKillFocus(pNewWnd);

	ProcessData();
}

BOOL ArxRleInPlaceEdit::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceListBox

ArxRleInPlaceListBox::ArxRleInPlaceListBox()
{
}

ArxRleInPlaceListBox::~ArxRleInPlaceListBox()
{
}

BEGIN_MESSAGE_MAP(ArxRleInPlaceListBox, CAdUiListBox)
	//{{AFX_MSG_MAP(ArxRleInPlaceListBox)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceListBox message handlers

void ArxRleInPlaceListBox::ProcessSelected(bool bProcess)
{
	ReleaseCapture();

	CWnd* pOwner = GetOwner();

	if(bProcess)
	{
		int nSelectedItem = GetCurSel();
		pOwner->SendMessage(WM_USER_ON_SELECTION_OK, nSelectedItem, GetItemData(nSelectedItem));
	}
	else
		pOwner->SendMessage(WM_USER_ON_SELECTION_CANCEL);
}

void ArxRleInPlaceListBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CAdUiListBox::OnLButtonUp(nFlags, point);

	CRect rect;
	GetClientRect(rect);

	if(rect.PtInRect(point))
		ProcessSelected();
	//else
	//	ReleaseCapture();
}

BOOL ArxRleInPlaceListBox::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
			case VK_RETURN:
				ProcessSelected();
				return TRUE;
			case VK_ESCAPE:
			case VK_TAB:
				ProcessSelected(false);
				return TRUE;
			default:
				;
		}
	}

	return CAdUiListBox::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceListCtrl

ArxRleInPlaceListCtrl::ArxRleInPlaceListCtrl()
{
}

ArxRleInPlaceListCtrl::~ArxRleInPlaceListCtrl()
{
}

int ArxRleInPlaceListCtrl::GetCount() const
{
	return GetItemCount();
}

void ArxRleInPlaceListCtrl::GetText(int nIndex, CString& strText) const
{
	strText = GetItemText(nIndex, 0);
}

int ArxRleInPlaceListCtrl::SetCurSel(int nSelect)
{	 
	return SetItemState(nSelect, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ? 0 : LB_ERR;
}

int ArxRleInPlaceListCtrl::AddString(LPCTSTR pStrText)
{
	return InsertItem(GetItemCount(), pStrText);
}

void ArxRleInPlaceListCtrl::ResetContent()
{
	DeleteAllItems();
}

BEGIN_MESSAGE_MAP(ArxRleInPlaceListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(ArxRleInPlaceListCtrl)
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceListCtrl message handlers

void ArxRleInPlaceListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CListCtrl::OnKillFocus(pNewWnd);

	GetOwner()->SendMessage(WM_USER_ON_SELECTION_CANCEL);
}

void ArxRleInPlaceListCtrl::ProcessSelected()
{
	int nSelectedItem = GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);

	GetOwner()->SendMessage(WM_USER_ON_SELECTION_OK, nSelectedItem, GetItemData(nSelectedItem));
}

void ArxRleInPlaceListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CListCtrl::OnLButtonUp(nFlags, point);

	ProcessSelected();
}

BOOL ArxRleInPlaceListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)
		{
			ProcessSelected();
			return TRUE;
		}
	}

	return CListCtrl::PreTranslateMessage(pMsg);
}


/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceComboBox

int ArxRleInPlaceComboBox::m_nButtonDx = ::GetSystemMetrics(SM_CXHSCROLL);

IMPLEMENT_DYNAMIC(ArxRleInPlaceComboBox, CWnd)

ArxRleInPlaceComboBox::ArxRleInPlaceComboBox()
{
	m_nCurrentSelection = -1;
}

ArxRleInPlaceComboBox::~ArxRleInPlaceComboBox()
{
}

int ArxRleInPlaceComboBox::GetCurrentSelection() const
{
	return m_nCurrentSelection;
}

DWORD ArxRleInPlaceComboBox::GetDWordData() const
{
	return m_nCurrentSelection != -1 ? m_wndList.GetItemData(m_nCurrentSelection) : 0;
}

ArxRleInPlaceComboBox* ArxRleInPlaceComboBox::CreateInPlaceComboBox(CWnd* pWndParent, CRect& rect)
{	
	ArxRleInPlaceComboBox* pInPlaceComboBox = (ArxRleInPlaceComboBox*)new ArxRleInPlaceComboBox;
	
	pInPlaceComboBox->Create(NULL, L"", WS_VISIBLE|WS_CHILD, rect, pWndParent, 1);

	return pInPlaceComboBox;
}

BEGIN_MESSAGE_MAP(ArxRleInPlaceComboBox, CWnd)
	//{{AFX_MSG_MAP(ArxRleInPlaceComboBox)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_USER_ON_SELECTION_OK, OnSelectionOk)
	ON_MESSAGE(WM_USER_ON_SELECTION_CANCEL, OnSelectionCancel)
	ON_MESSAGE(WM_USER_ON_NEW_SELECTION, OnNewSelection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceComboBox message handlers

int ArxRleInPlaceComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if(CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(rect);
	rect.DeflateRect(0, 1);
	rect.right -= m_nButtonDx;

	CWnd* pParent = GetParent();
	ASSERT(pParent != NULL);

	CFont* pFont = pParent->GetFont();

	// Vstupn?riadok
	m_wndEdit.Create(WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL, rect, this, 2);
	m_wndEdit.SetOwner(this);
	m_wndEdit.SetFont(pFont);

	// Zoznam položiek
	rect.right += m_nButtonDx - 1;
	rect.top = rect.bottom + 2;
	rect.bottom += 100;

	ClientToScreen(rect);
	pParent = pParent->GetParent();
	pParent->ScreenToClient(rect);
		
	m_wndList.Create(WS_BORDER|WS_CHILD|WS_VSCROLL, rect, pParent, 3);
	m_wndList.SetOwner(this);
	m_wndList.SetFont(pFont);

	return 0;
}

void ArxRleInPlaceComboBox::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
		
	m_wndEdit.SetWindowPos(NULL, 0, 0, cx - m_nButtonDx, cy, SWP_NOZORDER|SWP_NOMOVE);
}

void ArxRleInPlaceComboBox::MoveControl(CRect& rect)
{
	CRect prevRect;
	GetClientRect(prevRect);

	CWnd* pParent = GetParent();

	// Prekresli predošl?pozíciu
	ClientToScreen(prevRect);
	pParent->ScreenToClient(prevRect);
	pParent->InvalidateRect(prevRect);

	// Nov?pozícia
	MoveWindow(rect, FALSE);

	pParent->ClientToScreen(rect);
	pParent = pParent->GetParent();	
	pParent->ScreenToClient(rect);

	m_wndList.SetWindowPos(NULL, rect.left, rect.bottom + 1, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
}

void ArxRleInPlaceComboBox::ResetListBoxHeight()
{
	CRect rect;

	GetClientRect(rect);
	rect.right -= 1;

	int nItems = m_wndList.GetCount();
	int nListBoxHeight = nItems > 0 ? nItems * m_nButtonDx : DEFAULT_IPLISTBOX_HEIGHT;

	if(nListBoxHeight > DEFAULT_IPLISTBOX_HEIGHT)
		nListBoxHeight = DEFAULT_IPLISTBOX_HEIGHT;

	m_wndList.SetWindowPos(NULL, 0, 0, rect.Width(), nListBoxHeight, SWP_NOZORDER|SWP_NOMOVE);
}

void ArxRleInPlaceComboBox::OnPaint() 
{
	CPaintDC dc(this);
	
	// Nakresli tlaèítko
	CRect rect;

	GetClientRect(rect);
	rect.left = rect.right - m_nButtonDx;

#if 1
	dc.DrawFrameControl(rect, DFC_SCROLL, m_wndList.IsWindowVisible() ? 
		DFCS_SCROLLDOWN|DFCS_PUSHED : DFCS_SCROLLDOWN);
#else
	dc.DrawFrameControl(rect, DFC_SCROLL, m_wndList.IsWindowVisible() ? 
		DFCS_SCROLLDOWN|DFCS_PUSHED|DFCS_FLAT : DFCS_SCROLLDOWN|DFCS_FLAT);
#endif
}

BOOL ArxRleInPlaceComboBox::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;	
}

void ArxRleInPlaceComboBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point);

	CRect rect;
	GetClientRect(rect);

	CRect rectButton(rect);
	rectButton.left = rectButton.right - m_nButtonDx;

	if(rectButton.PtInRect(point))
	{
		int nDoAction = m_wndList.IsWindowVisible() ? SW_HIDE : SW_SHOW;

		m_wndList.ShowWindow(nDoAction);
		InvalidateRect(rectButton, FALSE);

		if(nDoAction == SW_SHOW)
		{
			m_wndList.SetFocus();
			m_wndList.SetCapture();
		}
	}
}

void ArxRleInPlaceComboBox::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	
	m_wndEdit.SetFocus();
}

void ArxRleInPlaceComboBox::HideListBox()
{
	m_wndList.ShowWindow(SW_HIDE);

	CRect rectButton;

	GetClientRect(rectButton);
	rectButton.left = rectButton.right - m_nButtonDx;

	InvalidateRect(rectButton, FALSE);

	m_wndEdit.SetFocus();
}

LRESULT ArxRleInPlaceComboBox::OnSelectionOk(WPARAM wParam, LPARAM /*lParam*/)
{
	HideListBox();

	SetCurSelToEdit(m_nCurrentSelection = int(wParam));

	GetOwner()->SendMessage(WM_USER_SET_DATA);

	return TRUE;
}

LRESULT ArxRleInPlaceComboBox::OnSelectionCancel(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	HideListBox();

	return TRUE;
}

LRESULT ArxRleInPlaceComboBox::OnNewSelection(WPARAM wParam, LPARAM /*lParam*/)
{
	int nItems = m_wndList.GetCount();

	if(nItems > 0)
	{
		if(wParam == VK_UP)
		{
			if(m_nCurrentSelection > 0)
				SetCurSel(m_nCurrentSelection - 1);
		}
		else
		{
			if(m_nCurrentSelection < nItems - 1)
				SetCurSel(m_nCurrentSelection + 1);
		}
	}

	return TRUE;
}

void ArxRleInPlaceComboBox::SetCurSelToEdit(int nSelect)
{
	CString strText;

	if(nSelect != -1)
		m_wndList.GetText(nSelect, strText);
		
	m_wndEdit.SetWindowText(strText);
	m_wndEdit.SetSel(0, -1); 
}

int ArxRleInPlaceComboBox::SetCurSel(int nSelect, bool bSendSetData)
{
	if(nSelect >= m_wndList.GetCount())
		return CB_ERR;


	int nRet = m_wndList.SetCurSel(nSelect);

	if(nRet != -1)
	{
		SetCurSelToEdit(nSelect);
		m_nCurrentSelection = nSelect;

		if(bSendSetData)
			GetOwner()->SendMessage(WM_USER_SET_DATA);
	}

	return nRet;
}

CString ArxRleInPlaceComboBox::GetTextData() const
{
	CString strText;

	if(m_nCurrentSelection != -1)
		m_wndList.GetText(m_nCurrentSelection, strText);

	return strText;
}

int ArxRleInPlaceComboBox::AddString(LPCTSTR pStrText, DWORD nData)
{
	int nIndex = m_wndList.AddString(pStrText);

	return m_wndList.SetItemData(nIndex, nData);
}

void ArxRleInPlaceComboBox::ResetContent()
{
	m_wndList.ResetContent();

	m_nCurrentSelection = -1;
}