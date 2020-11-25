///////////////////////////////////////////////////////////////////////////////
// ArxRleListCtrl.cpp
//
// ArxRleListCtrl, a CAdUiListCtrl derived class that is specialized on "Report View"
// style. 
//
// Features:
//
// 1, Item sorting by clicking on column header.
// 2, Sub-item text edit.
// 3, Item repositioning.
// 4, Customizing checkbox styles, including "single" and "disabled".
// 5, Sending a message to parent window when user clicks on a checkbox.
// 6, Convenient item insertion, deletion, moving, and sub-item text changing.
// 7, Sub-item images and color
// 8, And much more... 
//
// This code may be used in compiled form in any way you desire. This file may be
// redistributed unmodified by any means PROVIDING it is not sold for profit without
// the authors written consent, and providing that this notice and the authors name 
// is included. If the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file .
//
// This file is provided "as is" with no expressed or implied warranty.
//
// Written by Bin Liu (abinn32@yahoo.com)
//
// History
//
// Nov. 26, 2003 - Initial release.
// Dec. 03, 2003 - Fixed a bug in "EndEdit" where item text were not preperly committed.
//               - Completed the implementation of the "Sort-Separator" feature.
// Jan. 01, 2004 - Fixed a bug in "SetItemData".
//               - Added message "WM_EDIT_COMMITTED" which is sent to the parent window
//                 when an item text editing is committed.
//               - Fixed a bug in "SetItemText"(double type).
//               - Fixed a bug where item sorting does not work properly when there
//                 are multiple ArxRleListCtrl objects on same window.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArxRleListCtrl.h"
#include <afxtempl.h>

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


// Below styles MUST be present in a report ctrl
#define MUST_STYLE			(WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | LVS_REPORT)
#define MUST_EX_STYLE		(LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES)

// Below styles MUST NOT be present in a report ctrl
#define MUST_NOT_STYLE		(LVS_EDITLABELS | LVS_ICON | LVS_SMALLICON | LVS_LIST | LVS_NOSCROLL)
#define MUST_NOT_EX_STYLE	(0)


/////////////////////////////////////////////////////////////////////////////
// CItemData Implementation
/////////////////////////////////////////////////////////////////////////////
class CItemData
{
public:
	CItemData();
	CItemData(int cols);
	CItemData(const CItemData& data);

	CItemData& operator= (const CItemData& data);

	void InsertColumn(int nColumn);
	void DeleteColumn(int nColumn);

public:
	DWORD dwData;                              // Item data
	DWORD dwStates;                            // Item states
	CArray<int, int> aImages;                  // Sub item image
	CArray<CString,CString> aTexts;            // Sub item text
	CArray<BOOL, BOOL> aChecks;                // Sub item checkbox
	CArray<BOOL, BOOL> aCombos;                // Sub item combobox
	CArray<CString, CString> aDatas;           // Sub item datas
	CArray<COLORREF, COLORREF> aTextColors;    // Sub item text color
	CArray<COLORREF, COLORREF> aBkColors;      // Sub item text background color
};

CItemData::CItemData()
{
	dwData = 0;
	dwStates = 0;
}

CItemData::CItemData(int cols)
{
	dwData = 0;
	dwStates = 0;
	aImages.SetSize(cols);
	aTexts.SetSize(cols);
	aChecks.SetSize(cols);
	aCombos.SetSize(cols);
	aDatas.SetSize(cols);
	aTextColors.SetSize(cols);
	aBkColors.SetSize(cols);
	for(int i=0; i<cols; i++)
	{
		aImages[i] = -1;
		aTexts[i] = L"";
		aChecks[i] = FALSE;
		aCombos[i] = FALSE;
		aDatas[i] = L"";
		aTextColors[i] = ::GetSysColor(COLOR_WINDOWTEXT);
		aBkColors[i] = ::GetSysColor(COLOR_WINDOW);
	}
}

CItemData::CItemData(const CItemData& data)
{
	dwData = data.dwData;
	dwStates = data.dwStates;
	aImages.Copy(data.aImages);
	aTexts.Copy(data.aTexts);
	aChecks.Copy(data.aChecks);
	aCombos.Copy(data.aCombos);
	aDatas.Copy(data.aDatas);
	aTextColors.Copy(data.aTextColors);
	aBkColors.Copy(data.aBkColors);
}

CItemData& CItemData::operator= (const CItemData& data)
{
	dwData = data.dwData;
	dwStates = data.dwStates;
	aImages.Copy(data.aImages);
	aTexts.Copy(data.aTexts);
	aChecks.Copy(data.aChecks);
	aCombos.Copy(data.aCombos);
	aDatas.Copy(data.aDatas);
	aTextColors.Copy(data.aTextColors);
	aBkColors.Copy(data.aBkColors);
	return *this;
}

void CItemData::InsertColumn(int nColumn)
{
	aTextColors.InsertAt(nColumn, ::GetSysColor(COLOR_WINDOWTEXT));
	aBkColors.InsertAt(nColumn, ::GetSysColor(COLOR_WINDOW));
}

void CItemData::DeleteColumn(int nColumn)
{
	aTextColors.RemoveAt(nColumn);
	aBkColors.RemoveAt(nColumn);
}


/////////////////////////////////////////////////////////////////////////////
// ArxRleListCtrl Implementation
/////////////////////////////////////////////////////////////////////////////
ArxRleListCtrl::ArxRleListCtrl(): m_pWndEdit(NULL)
{
	m_pWndEdit = new CEdit;
	m_pWndCombo = new CComboBox;
	VERIFY(m_pWndEdit != NULL);
	m_pszSeparator = NULL;
	m_bAllowEdit = FALSE;
	m_ptEditting.x = -1;
	m_ptEditting.y = -1;
	m_ptComboing.x = -1;
	m_ptComboing.y = -1;
	m_nChkStyle = RC_CHKBOX_NORMAL;
	m_dwPrevEditFmt = ES_LEFT;
	m_nSortCol = -1;
	m_bSortAscending = TRUE;
}

ArxRleListCtrl::~ArxRleListCtrl()
{	
	if (m_pszSeparator != NULL)
		delete [] m_pszSeparator;

	if (m_pWndEdit != NULL)
		delete m_pWndEdit;

	if (m_pWndCombo != NULL)
		delete m_pWndCombo;
}

CString ArxRleListCtrl::GenRandStr()
{
	const CString LETTERS = _T("abcdefghijklm nopqrstuvwxy z0123456789");
	const int LEN = 16;

	CString str;
	for (int i = 0; i < LEN; i++)
	{
		str += LETTERS[rand() % LETTERS.GetLength()];
	}

	return str;
}

COleDateTime ArxRleListCtrl::GenRandDate()
{
	COleDateTime now = COleDateTime::GetCurrentTime();
	COleDateTimeSpan span(rand() % 3650, rand() % 24, rand() % 60, rand() % 60);
	now -= span;
	return now;
}


BEGIN_MESSAGE_MAP(ArxRleListCtrl, CAdUiListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
//       ArxRleListCtrl message handlers
/////////////////////////////////////////////////////////////////////////////
void ArxRleListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;

	if (lplvcd->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
	    *pResult = CDRF_NOTIFYITEMDRAW;
	}
    else if (lplvcd->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
	    *pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
    else if (lplvcd->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
    {
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(lplvcd->nmcd.dwItemSpec));
		ASSERT(p != NULL);
		ASSERT(lplvcd->iSubItem >= 0 && lplvcd->iSubItem < p->aTextColors.GetSize());
		lplvcd->clrText = p->aTextColors[lplvcd->iSubItem];
		lplvcd->clrTextBk = p->aBkColors[lplvcd->iSubItem];

		*pResult = CDRF_DODEFAULT;
	}
}

void ArxRleListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	const int COL = pNMListView->iSubItem;
	SortItems(COL, COL == m_nSortCol ? !m_bSortAscending : TRUE);
	*pResult = 0;
}

void ArxRleListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_LBUTTONDOWN, nFlags, point, TRUE);
}

void ArxRleListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_LBUTTONDBLCLK, nFlags, point, TRUE);
}

void ArxRleListCtrl::OnMButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_MBUTTONDOWN, nFlags, point, FALSE);
}

void ArxRleListCtrl::OnMButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_MBUTTONDBLCLK, nFlags, point, FALSE);
}

void ArxRleListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_RBUTTONDOWN, nFlags, point, FALSE);
}

void ArxRleListCtrl::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_RBUTTONDBLCLK, nFlags, point, FALSE);
}

int ArxRleListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style &= ~MUST_NOT_STYLE;
	lpCreateStruct->style |= MUST_STYLE;
	if (CAdUiListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetExtendedStyle(GetExtendedStyle());
	ASSERT(GetHeaderCtrl() != NULL);
	return 0;
}

void ArxRleListCtrl::OnDestroy() 
{
	DeleteAllItems();
	m_pWndEdit->DestroyWindow();
	m_pWndCombo->DestroyWindow();
	m_imgList.DeleteImageList();
	m_headerImgList.DeleteImageList();
	CAdUiListCtrl::OnDestroy();
	// TODO: Add your message handler code here	
}

BOOL ArxRleListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if (!_IsEditVisible())
		{
			// disable user from check/uncheck the checkboxes using space key
			// things get nasty if the user is HOLDING the space bar down
			if (pMsg->wParam == VK_SPACE)
				return TRUE;
		}
		else
		{
			POINT pt = m_ptEditting;
			switch (pMsg->wParam)
			{
			case VK_ESCAPE: // Cancel edit
				EndEdit(FALSE);
				EndCombo(FALSE);
				return TRUE;

			case VK_RETURN: // Commit edit
				EndEdit(TRUE);
				EndCombo(TRUE);
				return TRUE;

			case VK_TAB: // switch edit sub items
				if (pt.y == GetColumnCount() - 1)
					pt.y = 0;
				else
					pt.y++;
				EndEdit(TRUE);
				EndCombo(TRUE);
				StartEdit(pt.x, pt.y);
				return TRUE;

			case VK_UP: // edit upper item
				if (pt.x > 0)
				{
					pt.x--;
					EndEdit(TRUE);
					EndCombo(TRUE);
					StartEdit(pt.x, pt.y);
					EnsureVisible(pt.x, FALSE);
					return TRUE;
				}
				break;

			case VK_DOWN: // edit lower item
				if (pt.x < CAdUiListCtrl::GetItemCount() - 1)
				{
					pt.x++;
					EndEdit(TRUE);
					EndCombo(TRUE);
					StartEdit(pt.x, pt.y);
					EnsureVisible(pt.x, FALSE);
					return TRUE;
				}
				break;			

			default:
				break;				
			}
		}
	}

	return CAdUiListCtrl::PreTranslateMessage(pMsg);
}

BOOL ArxRleListCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style &= ~MUST_NOT_STYLE;
	cs.style |= MUST_STYLE;
	return CAdUiListCtrl::PreCreateWindow(cs);
}

void ArxRleListCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	LONG lStyle = ::GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	lStyle &= ~MUST_NOT_STYLE;
	lStyle |= MUST_STYLE;
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, lStyle);
	SetExtendedStyle(0);
	ASSERT(GetHeaderCtrl() != NULL);
	CAdUiListCtrl::PreSubclassWindow();
}


//////////////////////////////////////////////////////////////////////
//		Run-time Creation
//////////////////////////////////////////////////////////////////////
BOOL ArxRleListCtrl::Create(CWnd* pParentWnd, UINT nID, LPCRECT lpRect, DWORD dwStyle) 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT(pParentWnd != NULL);

	dwStyle &= ~MUST_NOT_STYLE;
	dwStyle |= MUST_STYLE;

	CRect rect;
	if (lpRect == NULL)
		pParentWnd->GetClientRect(&rect);
	else
		rect = *lpRect;

	return CAdUiListCtrl::Create(dwStyle, rect, pParentWnd, nID);
}


///////////////////////////////////////////////////////////////////////
//		Column Header attributes
///////////////////////////////////////////////////////////////////////
// the heading text is in the format of "text,width,format;text,width,format;..."
BOOL ArxRleListCtrl::SetColumnHeader(const CString& strHeadings)
{
	DeleteAllItems();
	DeleteAllColumns();
	EndEdit(TRUE);
	EndCombo(TRUE);
	BOOL bInserted = FALSE;
	CStringArray aLong, aShort;
	_StringSplit(strHeadings, aLong, _T(';'));
	for (int i = 0; i < aLong.GetSize(); i++)
	{
		_StringSplit(aLong[i], aShort, _T(','));
		if (aShort.GetSize() > 0)
		{
			const int width = aShort.GetSize() > 1 ? _ttoi(aShort[1]) : 100;
			int nFormat = aShort.GetSize() > 2 ? _ttoi(aShort[2]) : 0;

			if (nFormat == 1)
				nFormat = LVCFMT_CENTER;
			else if (nFormat == 2)
				nFormat = LVCFMT_RIGHT;
			else
				nFormat = LVCFMT_LEFT;

			bInserted |= (InsertColumn(GetColumnCount(), aShort[0], nFormat, width) >= 0);
		}
	}
	return bInserted;
}

int ArxRleListCtrl::GetColumnCount() const
{
	return GetHeaderCtrl()->GetItemCount();
}

BOOL ArxRleListCtrl::DeleteAllColumns()
{
	while (GetColumnCount() > 0)
		DeleteColumn(0);		
	return TRUE;
}

CString ArxRleListCtrl::GetHeaderText(int nColumn) const
{
	if (!HasColumnHeader())
		return _T("");

	HDITEM hd;
	TCHAR  szBuffer[256] = _T("");
	hd.mask = HDI_TEXT;
	hd.pszText = szBuffer;
	hd.cchTextMax = 255;
	return GetHeaderCtrl()->GetItem(nColumn, &hd) ? hd.pszText : _T("");
}

BOOL ArxRleListCtrl::SetHeaderText(int nColumn, LPCTSTR lpText)
{
	if (!HasColumnHeader())
		return FALSE;

	LPTSTR psz = NULL;
	if (lpText == NULL)
	{
		psz = new TCHAR[1];
		*psz = _T('\0');
	}
	else
	{
		psz = _tcsdup(lpText);
	}
	HDITEM hd;
	hd.mask = HDI_TEXT;
	hd.pszText = psz;
	hd.cchTextMax = _tcslen(psz);
	const BOOL res = CAdUiListCtrl::GetHeaderCtrl()->SetItem(nColumn, &hd);
	delete [] psz;
	return res;
}

BOOL ArxRleListCtrl::HasColumnHeader() const
{
	return (GetStyle() & LVS_NOCOLUMNHEADER) == 0;
}

const CHeaderCtrl* ArxRleListCtrl::GetHeaderCtrl() const
{
	// Yes, CAdUiListCtrl already provides "GetHeaderCtrl", but not const.	
	// I desperately need a "const" version of "GetHeaderCtrl" because that's the
	// only way to make "GetColumnCount" const, which, in turn, is being called by
	// A LOT of const member functions. So if "GetHeaderCtrl" is not const, there will
	// be almost no const member function at all in this class. Terrible.
	return (const CHeaderCtrl*)(CWnd::FromHandle(ListView_GetHeader(GetSafeHwnd())));
}


///////////////////////////////////////////////////////////////////////
//		Images & Color
///////////////////////////////////////////////////////////////////////
BOOL ArxRleListCtrl::SetHeaderImage(int nColumn, int nImageIndex, BOOL bLeftSide)
{
	if (GetHeaderCtrl()->GetImageList() == NULL)
		CAdUiListCtrl::GetHeaderCtrl()->SetImageList(GetImageList());

	HDITEM hi;
	::memset(&hi, 0, sizeof(HDITEM));
	hi.mask = HDI_FORMAT;
	if (!GetHeaderCtrl()->GetItem(nColumn, &hi))
		return FALSE;

	hi.mask |= HDI_IMAGE;		
	hi.fmt |= HDF_IMAGE;

	if (!bLeftSide)
		hi.fmt |= HDF_BITMAP_ON_RIGHT; // draw the image on right side of text

	hi.iImage = nImageIndex;
	return CAdUiListCtrl::GetHeaderCtrl()->SetItem(nColumn, &hi);
}

int ArxRleListCtrl::GetHeaderImage(int nColumn) const
{
	HDITEM hi;
	::memset(&hi, 0, sizeof(HDITEM));
	hi.mask = HDI_IMAGE;
	return !GetHeaderCtrl()->GetItem(nColumn, &hi) ? hi.iImage : -1;
}

CImageList* ArxRleListCtrl::SetHeaderImageList(CImageList *pImageList)
{
	return CAdUiListCtrl::GetHeaderCtrl()->SetImageList(pImageList);
}

CImageList* ArxRleListCtrl::SetHeaderImageList(UINT nBitmapID, COLORREF crMask)
{
	m_headerImgList.Create(nBitmapID, 16, 4, crMask);
	return SetHeaderImageList(&m_headerImgList);
}

// Sub-item images
BOOL ArxRleListCtrl::SetItemImage(int nItem, int nSubItem, int nImageIndex)
{
	const int rows = GetItemCount();
	const int cols = GetColumnCount();
	BOOL bRowValid = nItem >= 0 && nItem < rows;
	BOOL bColValid = nSubItem >= 0 && nSubItem < cols;

	if (bRowValid && bColValid)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
		if(p != NULL)
		{
			p->aImages[nSubItem] = nImageIndex;
			CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
		}

		return CAdUiListCtrl::SetItem(nItem, nSubItem, LVIF_IMAGE, NULL, nImageIndex, 0, 0, 0);
	}
	
	return FALSE;
}

int ArxRleListCtrl::GetItemImage(int nItem, int nSubItem) const
{
	LVITEM lvi;
	lvi.iItem = nItem;
	lvi.iSubItem = nSubItem;
	lvi.mask = LVIF_IMAGE;
	return CAdUiListCtrl::GetItem(&lvi) ? lvi.iImage : -1;
}

CImageList* ArxRleListCtrl::SetImageList(UINT nBitmapID, COLORREF crMask)
{
	m_imgList.DeleteImageList();
	m_imgList.Create(nBitmapID, 16, 4, crMask);	
	return CAdUiListCtrl::SetImageList(&m_imgList, LVSIL_SMALL);
}

CImageList* ArxRleListCtrl::SetImageList(CImageList *pImageList)
{
	return CAdUiListCtrl::SetImageList(pImageList, LVSIL_SMALL);
}

CImageList* ArxRleListCtrl::GetImageList() const
{
	return CAdUiListCtrl::GetImageList(LVSIL_SMALL);
}

// Sub-item Text & Background Color
void ArxRleListCtrl::SetItemTextColor(int nItem, int nSubItem, COLORREF color, BOOL bRedraw)
{
	if (color == COLOR_INVALID)
		color = ::GetSysColor(COLOR_WINDOWTEXT);
	const int rows = GetItemCount();
	const int cols = GetColumnCount();
	BOOL bRowValid = nItem >= 0 && nItem < rows;
	BOOL bColValid = nSubItem >= 0 && nSubItem < cols;

	if (bRowValid && bColValid)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
		if(p != NULL)
		{
			p->aTextColors[nSubItem] = color;
			CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
		}
	}
	else if (bRowValid && !bColValid)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
		if(p != NULL)
		{
			for (int i = 0; i < cols; i++)	
				p->aTextColors[i] = color;
			CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
		}
	}
	else if (!bRowValid && bColValid)
	{
		// apply to whole column for all existing items
		for (int i = 0; i < rows; i++)
		{
			CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(i));
			if(p != NULL)
			{
				p->aTextColors[nSubItem] = color;
				CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
			}
		}
	}
	else
	{
		// apply to whole table for all existing items
		for (int i = 0; i < rows; i++)
		{
			CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(i));
			if(p != NULL)
			{
				for (int j = 0; j < cols; j++)
					p->aTextColors[j] = color;
				CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
			}
		}
	}

	if (bRedraw)
		RedrawWindow();
}

COLORREF ArxRleListCtrl::GetItemTextColor(int nItem, int nSubItem) const
{
	if (!_IsValidIndex(nItem) || nSubItem < 0 || nSubItem >= GetColumnCount())
		return COLOR_INVALID;
	CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
	if(p != NULL) return p->aTextColors[nSubItem];
	
	return COLOR_INVALID;
}

void ArxRleListCtrl::SetItemBkColor(int nItem, int nSubItem, COLORREF color, BOOL bRedraw)
{
	if (color == COLOR_INVALID)
		color = ::GetSysColor(COLOR_WINDOW);
	const int rows = GetItemCount();
	const int cols = GetColumnCount();
	BOOL bRowValid = nItem >= 0 && nItem < rows;
	BOOL bColValid = nSubItem >= 0 && nSubItem < cols;

	if (bRowValid && bColValid)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
		if(p != NULL)
		{
			p->aBkColors[nSubItem] = color;
			CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
		}
	}
	else if (bRowValid && !bColValid)
	{
		// apply to whole row for the existing item
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
		if(p != NULL)
		{
			for (int i = 0; i < cols; i++)
				p->aBkColors[i] = color;
			CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
		}
	}
	else if (!bRowValid && bColValid)
	{
		// apply to whole column for all existing items
		for (int i = 0; i < rows; i++)
		{
			CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(i));
			if(p != NULL)
			{
				p->aBkColors[nSubItem] = color;
				CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
			}
		}
	}
	else
	{
		// apply to whole table for all existing items
		for (int i = 0; i < rows; i++)
		{
			CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(i));
			if(p != NULL)
			{
				for (int j = 0; j < cols; j++)
					p->aBkColors[j] = color;
				CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
			}
		}
	}

	if (bRedraw)
		RedrawWindow();
}

COLORREF ArxRleListCtrl::GetItemBkColor(int nItem, int nSubItem) const
{
	if (!_IsValidIndex(nItem) || nSubItem < 0 || nSubItem >= GetColumnCount())
		return COLOR_INVALID;
	CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
	if(p != NULL) return p->aBkColors[nSubItem];
	
	return COLOR_INVALID;;
}


//////////////////////////////////////////////////////////////////////
//		Control Styles & Attributes
//////////////////////////////////////////////////////////////////////
void ArxRleListCtrl::ResizeToFitParent()
{
	// resize the list ctrl to fit parent client area
	if (GetSafeHwnd() != NULL)
	{
		CRect rect;
		GetParent()->GetClientRect(&rect);
		MoveWindow(&rect);
	}
}

void ArxRleListCtrl::SetGridLines(BOOL bSet)
{
	DWORD dwStype = GetExtendedStyle();
	if (bSet)
		dwStype |= LVS_EX_GRIDLINES;
	else
		dwStype &= ~LVS_EX_GRIDLINES;

	SetExtendedStyle(dwStype);	
}

void ArxRleListCtrl::SetCheckboxeStyle(int nStyle)
{
	m_nChkStyle = nStyle;
	EndEdit(TRUE);
	EndCombo(TRUE);
	DWORD dwStype = GetExtendedStyle();
	if (nStyle == 0)
	{
		dwStype &= ~LVS_EX_CHECKBOXES;		
	}
	else
	{
		dwStype |= LVS_EX_CHECKBOXES;
		_EnsureSingleCheck(-1);
	}

	SetExtendedStyle(dwStype);
}

int ArxRleListCtrl::GetCheckboxStyle() const
{
	return m_nChkStyle;
}

BOOL ArxRleListCtrl::IsSortable() const
{
	if (!HasColumnHeader())
		return FALSE;

	LONG lStyle = ::GetWindowLong(GetHeaderCtrl()->GetSafeHwnd(), GWL_STYLE);
	return (lStyle & HDS_BUTTONS) != 0;
}

BOOL ArxRleListCtrl::SetSortable(BOOL bSet)
{
	if (!HasColumnHeader())
		return FALSE;

	LONG lStyle = ::GetWindowLong(GetHeaderCtrl()->GetSafeHwnd(), GWL_STYLE);
	if (bSet)
	{
		lStyle |= HDS_BUTTONS;
	}
	else
	{
		lStyle &= ~HDS_BUTTONS;
		_UnsetSortedColumn();
	}
	::SetWindowLong(GetHeaderCtrl()->GetSafeHwnd(), GWL_STYLE, lStyle);
	CAdUiListCtrl::GetHeaderCtrl()->RedrawWindow();
	return TRUE;
}

BOOL ArxRleListCtrl::IsEditable() const
{
	return m_bAllowEdit;
}

void ArxRleListCtrl::SetEditable(BOOL bSet)
{	
	if (!bSet)
	{
		EndEdit(TRUE);
		EndCombo(TRUE);
	}
	m_bAllowEdit = bSet;
}


///////////////////////////////////////////////////////////////////////
//		Item attributes & operations
///////////////////////////////////////////////////////////////////////	
int ArxRleListCtrl::GetFirstItem(DWORD dwStates, int nStartAfter) const
{
	const int items = CAdUiListCtrl::GetItemCount();
	nStartAfter = max(-1, nStartAfter);
	for (int i = nStartAfter + 1; i <items; i++)
	{
		if (ExamItemStates(i, dwStates))
			return i;
	}
	return -1;
}

int ArxRleListCtrl::GetLastItem(DWORD dwStates, int nStartBefore) const
{
	const int items = CAdUiListCtrl::GetItemCount();
	nStartBefore = nStartBefore < 0 ? items - 1 : min(items, nStartBefore);
	for (int i = nStartBefore - 1; i >= 0; i--)
	{
		if (ExamItemStates(i, dwStates))
			return i;
	}
	return -1;
}

int ArxRleListCtrl::GetItemCount(DWORD dwStates) const
{
	const int items = CAdUiListCtrl::GetItemCount();
	if (dwStates == RC_ITEM_ALL)
		return items;

	int nCount = 0;
	for (int i = 0; i <items; i++)
	{
		if (ExamItemStates(i, dwStates))
			nCount++;
	}
	return nCount;
}

DWORD ArxRleListCtrl::GetItemStates(int nItem) const
{
	DWORD dwStates = 0;

	if (CAdUiListCtrl::GetItemState(nItem, LVIS_SELECTED))
		dwStates |= RC_ITEM_SELECTED;
	else
		dwStates |= RC_ITEM_UNSELECTED;

	if (CAdUiListCtrl::GetCheck(nItem) > 0)
		dwStates |= RC_ITEM_CHECKED;
	else
		dwStates |= RC_ITEM_UNCHECKED;

	if (CAdUiListCtrl::GetItemState(nItem, LVIS_FOCUSED))
		dwStates |= RC_ITEM_FOCUSED;
	else
		dwStates |= RC_ITEM_UNFOCUSED;

	return dwStates;
}

BOOL ArxRleListCtrl::SetItemStates(int nItem, DWORD dwNewStates)
{
	const int rows = GetItemCount();
	BOOL bRowValid = nItem >= 0 && nItem < rows;

	if (bRowValid)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
		if(p != NULL)
		{
			p->dwStates = dwNewStates;
			CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
		}
		BOOL bResult = _SetItemStatesNoVerify(nItem, dwNewStates);
		if (dwNewStates & RC_ITEM_CHECKED)
			_EnsureSingleCheck(nItem);
		return bResult;
	}

	return FALSE;
}

int ArxRleListCtrl::SetAllItemStates(DWORD dwOldStates, DWORD dwNewStates)
{
	if (dwNewStates == RC_ITEM_NONE || dwOldStates == RC_ITEM_NONE)
		return 0;

	int nCount = 0;
	const int items = CAdUiListCtrl::GetItemCount();
	for (int i = 0; i < items; i++)
	{
		if (dwOldStates == RC_ITEM_ALL || ExamItemStates(i, dwOldStates))
		{
			SetItemStates(i, dwNewStates);
			nCount++;
		}
	}

	if (dwNewStates & RC_ITEM_CHECKED)
		_EnsureSingleCheck(-1);

	return nCount;
}

BOOL ArxRleListCtrl::ExamItemStates(int nItem, DWORD dwStates) const
{
	if (dwStates == RC_ITEM_NONE)
		return FALSE;

	if (dwStates & RC_ITEM_ALL)
		return TRUE;

	return (GetItemStates(nItem) & dwStates) == dwStates;
}

void ArxRleListCtrl::InvertItems(int nType)
{
	const int items = CAdUiListCtrl::GetItemCount();
	if (nType == RC_INVERT_SELECTION)
	{
		for (int i = 0; i < items; i++)
			SetItemStates(i, ExamItemStates(i, RC_ITEM_SELECTED) ? RC_ITEM_UNSELECTED : RC_ITEM_SELECTED);
	}
	else if (nType == RC_INVERT_CHECKMARK)
	{
		for (int i = 0; i < items; i++)
			SetItemStates(i, ExamItemStates(i, RC_ITEM_CHECKED) ? RC_ITEM_UNCHECKED : RC_ITEM_CHECKED);
	}
}

// Item Insertion & Deletion	
int ArxRleListCtrl::InsertItemEx(int nItem, LPCTSTR lpText, ...)
{
	EndEdit(TRUE);
	EndCombo(TRUE);
	_UnsetSortedColumn();
	const int idx = InsertItem(nItem, lpText);
	if (idx < 0)
		return -1;

	va_list list;
	va_start(list, lpText);

	for(int iColumn = 1; iColumn < GetColumnCount(); iColumn++)
	{
		LPCTSTR lp = va_arg(list, LPCTSTR);
		if (lp != NULL)
		{
			SetItemText(idx, iColumn, lp);
		}
		else
		{
			break;
		}
	}

	va_end(list);
	return idx;
}

BOOL ArxRleListCtrl::DeleteItem(int nItem, BOOL bSelectNextItem)
{
	EndEdit(m_ptEditting.x != nItem);

	if (bSelectNextItem)
		SetItemStates(nItem + 1, RC_ITEM_SELECTED);

	_FreeItemMemory(nItem);
	return CAdUiListCtrl::DeleteItem(nItem);
}

int ArxRleListCtrl::DeleteAllItems(DWORD dwStates)
{
	EndEdit(FALSE);
	int nItemCount = CAdUiListCtrl::GetItemCount();
	if (dwStates & RC_ITEM_ALL)
	{
		LockWindowUpdate();
		for (int i = 0; i < nItemCount; i++)
			_FreeItemMemory(i);
		CAdUiListCtrl::DeleteAllItems();
		UnlockWindowUpdate();
		return nItemCount;		
	}

	int nDelCount = 0;
	LockWindowUpdate();

	for (int i = 0; i < nItemCount; i++)
	{
		if (ExamItemStates(i, dwStates))
		{
			DeleteItem(i--);
			nItemCount--;
			nDelCount++;
		}
	}	
	UnlockWindowUpdate();
	return nDelCount;
}

// Item positioning	
int ArxRleListCtrl::MoveTo(int nItem, int nNewPosition)
{
	if (!_IsValidIndex(nItem))
		return -1;

	EndEdit(TRUE);
	EndCombo(TRUE);
	const int rows = CAdUiListCtrl::GetItemCount();
	nNewPosition = max(0, nNewPosition);
	nNewPosition  = min(rows - 1, nNewPosition);

	if (nItem == nNewPosition)
		return nNewPosition;

	_UnsetSortedColumn();

	// Backup all states and attributes
	const int cols = GetColumnCount();
	CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
	if(p != NULL)
	{
		CItemData data = *p;
		// Delete the item
		CAdUiListCtrl::DeleteItem(nItem);

		// Insert a new item to the new position
		const int idx = InsertItem(nNewPosition, L"");

		SetItemStates(idx, GetItemStates(nItem));
		SetItemData(idx, data.dwData);

		// Restore all states & attributes to the newly inserted item
		for (int i = 0; i < cols; i++)
		{
			SetItemData(idx, i, data.aDatas[i]);
			SetItemImage(idx, i, data.aImages[i]);
			SetItemText(idx, i, data.aTexts[i]);
			SetComboStates(idx, i, data.aCombos[i]);
			SetItemTextColor(idx, i, data.aTextColors[i]);
			SetItemBkColor(idx, i, data.aBkColors[i]);
		}

		return idx;
	}

	return -1;
}

int ArxRleListCtrl::MoveUp(int nItem, int nCount)
{	
	return MoveTo(nItem, nItem - nCount);
}

BOOL ArxRleListCtrl::MoveDown(int nItem, int nCount)
{
	return MoveTo(nItem, nItem + nCount);
}

int ArxRleListCtrl::MoveToTop(int nItem)
{
	return MoveTo(nItem, -1);
}

int ArxRleListCtrl::MoveToBottom(int nItem)
{
	return MoveTo(nItem, INT_MAX);
}

BOOL ArxRleListCtrl::SwapItems(int nItem1, int nItem2)
{
	EndEdit(TRUE);
	EndCombo(TRUE);
	if (!_IsValidIndex(nItem1) || !_IsValidIndex(nItem2))
		return FALSE;

	if (nItem1 == nItem2)
		return TRUE;

	_UnsetSortedColumn();

	// record previous states first
	const int rows = GetItemCount();
	BOOL bRow1Valid = nItem1 >= 0 && nItem1 < rows;
	BOOL bRow2Valid = nItem2 >= 0 && nItem2 < rows;

	if (bRow1Valid && bRow2Valid)
	{
		CItemData* p1 = (CItemData*)(CAdUiListCtrl::GetItemData(nItem1));
		CItemData* p2 = (CItemData*)(CAdUiListCtrl::GetItemData(nItem2));
		if(p1 != NULL && p2 != NULL)
		{
			CItemData data1 = *p1;
			CItemData data2 = *p2;
			// restore states
			DWORD states1 = GetItemStates(nItem1);
			DWORD states2 = GetItemStates(nItem2);
			SetItemStates(nItem1, states2);
			SetItemStates(nItem2, states1);

			// swap item data
			SetItemData(nItem1, data2.dwData);
			SetItemData(nItem2, data1.dwData);

			int cols = GetColumnCount();
			for (int i = 0; i < cols; i++)
			{
				SetItemData(nItem1, i, data2.aDatas[i]);
				SetItemData(nItem2, i, data1.aDatas[i]);
				SetItemImage(nItem1, i, data2.aImages[i]);
				SetItemImage(nItem2, i, data1.aImages[i]);
				SetItemText(nItem1, i, data2.aTexts[i]);
				SetItemText(nItem2, i, data1.aTexts[i]);
				SetComboStates(nItem1, i, data2.aCombos[i]);
				SetComboStates(nItem2, i, data1.aCombos[i]);
				SetItemTextColor(nItem1, i, data2.aTextColors[i]);
				SetItemTextColor(nItem2, i, data1.aTextColors[i]);
				SetItemBkColor(nItem1, i, data2.aBkColors[i]);
				SetItemBkColor(nItem2, i, data1.aBkColors[i]);
			}

			return TRUE;
		}
	}

	return FALSE;
}

// Convenient versions of "CAdUiListCtrl::SetItemText"	
BOOL ArxRleListCtrl::SetItemText(int nItem, int nSubItem, LPCTSTR lpText)
{
	EndEdit(TRUE);
	EndCombo(TRUE);
	_UnsetSortedColumn();

	const int rows = GetItemCount();
	const int cols = GetColumnCount();
	BOOL bRowValid = nItem >= 0 && nItem < rows;
	BOOL bColValid = nSubItem >= 0 && nSubItem < cols;

	if (bRowValid && bColValid)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
		if(p != NULL)
		{
			p->aTexts[nSubItem] = lpText;
			CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);

			return CAdUiListCtrl::SetItemText(nItem, nSubItem, lpText);
		}
	}

	return FALSE;
}

BOOL ArxRleListCtrl::SetItemText(int nItem, int nSubItem, TCHAR val)
{
	return SetItemText(nItem, nSubItem, CString(val));
}

BOOL ArxRleListCtrl::SetItemText(int nItem, int nSubItem, INT val)
{	
	return SetItemText(nItem, nSubItem, (LONG)val);
}

BOOL ArxRleListCtrl::SetItemText(int nItem, int nSubItem, UINT val)
{
	return SetItemText(nItem, nSubItem, (ULONG)val);
}

BOOL ArxRleListCtrl::SetItemText(int nItem, int nSubItem, LONG val)
{
	CString str;
	str.Format(_T("%d"), val);
	return SetItemText(nItem, nSubItem, str);
}

BOOL ArxRleListCtrl::SetItemText(int nItem, int nSubItem, ULONG val)
{
	CString str;
	str.Format(_T("%u"), val);
	return SetItemText(nItem, nSubItem, str);
}

BOOL ArxRleListCtrl::SetItemText(int nItem, int nSubItem, DOUBLE val, int nPrecision)
{
	CString sText, sFmt;

	if (nPrecision >= 0)
	{
		sFmt.Format(_T("%%.%df"), nPrecision);
		sText.Format(sFmt, val);
	}
	else
	{
		sText.Format(_T("%f"), val);
		sText.TrimRight(_T('0'));
		sText.TrimRight(_T('.'));
	}

	return SetItemText(nItem, nSubItem, sText);
}

BOOL ArxRleListCtrl::SetItemText(int nItem, int nSubItem, const COleDateTime &dateTime, DWORD dwFlags)
{
	return SetItemText(nItem, nSubItem, dateTime.GetStatus() == COleDateTime::valid ? dateTime.Format(dwFlags) : _T(""));
}

// Sub-item Text & Combo Data
BOOL ArxRleListCtrl::SetItemComboData(int nItem, int nSubItem, LPCTSTR strs, int nComboSel)
{
	const int rows = GetItemCount();
	const int cols = GetColumnCount();
	BOOL bRowValid = nItem >= 0 && nItem < rows;
	BOOL bColValid = nSubItem >= 0 && nSubItem < cols;

	if (bRowValid && bColValid)
	{
		CStringArray aStr;
		_StringSplit(strs, aStr, _T(';'));

		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
		if(p != NULL)
		{
			p->aDatas[nSubItem] = strs;
			p->aCombos[nSubItem] = TRUE;
			p->aTexts[nSubItem] = aStr[nComboSel];
			CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
		}

		return CAdUiListCtrl::SetItemText(nItem, nSubItem, aStr[nComboSel]);
	}

	return FALSE;
}

LPCTSTR ArxRleListCtrl::GetItemComboData(int nItem, int nSubItem) const
{
	const int rows = GetItemCount();
	const int cols = GetColumnCount();
	BOOL bRowValid = nItem >= 0 && nItem < rows;
	BOOL bColValid = nSubItem >= 0 && nSubItem < cols;

	if (bRowValid && bColValid)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
		if(p != NULL) return p->aDatas[nSubItem];
	}

	return L"";
}

BOOL ArxRleListCtrl::SetComboStates(int nItem, int nSubItem, BOOL bCombo)
{
	CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
	if (p == NULL)
		return FALSE;
	p->aCombos[nSubItem] = bCombo;
	CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
	return TRUE;
}

BOOL ArxRleListCtrl::GetComboStates(int nItem, int nSubItem) const
{
	const int rows = GetItemCount();
	const int cols = GetColumnCount();
	BOOL bRowValid = nItem >= 0 && nItem < rows;
	BOOL bColValid = nSubItem >= 0 && nSubItem < cols;

	if (bRowValid && bColValid)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
		if(p != NULL) return p->aCombos[nSubItem];
	}

	return FALSE;
}

// Sorting	
BOOL ArxRleListCtrl::IsSortAscending() const
{
	return m_bSortAscending;
}

int ArxRleListCtrl::GetSortedColumn() const
{
	return m_nSortCol;
}

void ArxRleListCtrl::SortItems(int nColumn, BOOL bAscending)
{
	EndEdit(TRUE);
	EndCombo(TRUE);
	if (nColumn < 0 || nColumn >= GetColumnCount() || !IsSortable())
		return;	

	// do the sorting	
	m_nSortCol = nColumn;
	m_bSortAscending = bAscending;

	BOOL bEnd = FALSE;
	int nSep1 = -1;
	int nSep2 = _FindSeparator(-1, nColumn);
	do
	{
		if (nSep2 < 0)
		{
			nSep2 = GetItemCount();
			bEnd = TRUE;
		}
		_PartialSort(nSep1 + 1, nSep2 - 1);
		nSep1 = _FindSeparator(nSep2 - 1, nColumn);
		nSep2 = _FindSeparator(nSep1, nColumn);
	} while (!bEnd && nSep1 >= 0);

	GetParent()->SendMessage(WM_ITEM_SORTED, (WPARAM)m_nSortCol, (LPARAM)m_bSortAscending);
}

void ArxRleListCtrl::SetSortSeparator(LPCTSTR lpSortSeparator)
{
	if (m_pszSeparator != NULL)
	{
		delete [] m_pszSeparator;
		m_pszSeparator = NULL;
	}

	if (lpSortSeparator != NULL)
		m_pszSeparator = _tcsdup(lpSortSeparator);
}

LPCTSTR ArxRleListCtrl::GetSortSeparator() const
{
	return m_pszSeparator;
}

// Item text edit/combobox	
BOOL ArxRleListCtrl::StartEdit(int nItem, int nSubItem)
{
	// Get the grid width and height
	if (!m_bAllowEdit || !_IsValidIndex(nItem) || nSubItem < 0 || nSubItem >= GetColumnCount())
		return FALSE;

	if (m_ptEditting.x == nItem && m_ptEditting.y == nSubItem)
		return TRUE;

	EndEdit(TRUE);
	EndCombo(TRUE);
	m_ptEditting.x = nItem;
	m_ptEditting.y = nSubItem;
	SetAllItemStates(RC_ITEM_SELECTED, RC_ITEM_UNSELECTED); // unselect all
	SetItemStates(m_ptEditting.x, RC_ITEM_SELECTED | RC_ITEM_FOCUSED);

	// determine editbox font and alignment
	const DWORD fmt = _GetHeaderTextFormat(nSubItem);
	if (fmt != m_dwPrevEditFmt)
	{
		m_dwPrevEditFmt = fmt;

		// Funny thing:
		// Changing CEdit style among ES_LEFT, ES_CENTER, ES_RIGHT at runtime works
		// sometimes and fails other times. It just cannot guarantee to be succeed.
		// So I decided to destroy and recreate the CEdit every time when the text
		// format changes.
		if (m_pWndEdit->GetSafeHwnd() != NULL)
			m_pWndEdit->DestroyWindow();

		if (!m_pWndEdit->Create(ES_AUTOHSCROLL | ES_NOHIDESEL | WS_CHILD | WS_BORDER | fmt, CRect(0, 0, 1, 1), this, 0))
			return FALSE;
	}
	else
	{
		if (m_pWndEdit->GetSafeHwnd() == NULL
			&& !m_pWndEdit->Create(ES_AUTOHSCROLL | ES_NOHIDESEL | WS_CHILD | WS_BORDER | fmt, CRect(0, 0, 1, 1), this, 0))
		{
			return FALSE;
		}
	}

	m_pWndEdit->SetFont(GetFont());

	CRect rcEdit;
	ListView_GetSubItemRect(GetSafeHwnd(), m_ptEditting.x, m_ptEditting.y, LVIR_LABEL, &rcEdit);
	if (m_ptEditting.y > 0 && GetImageList() != NULL && GetItemImage(m_ptEditting.x, m_ptEditting.y) >= 0)
		rcEdit.DeflateRect(16, 0, 0, 0);

	// Move the editbox to that grid, obtain text from the grid, display the
	// editbox, and, finally, highlights all text in the editbox and set the
	// windows focus to the editbox.
	m_pWndEdit->MoveWindow(&rcEdit);
	m_pWndEdit->SetWindowText(GetItemText(m_ptEditting.x, m_ptEditting.y));
	m_pWndEdit->ShowWindow(SW_SHOW);
	m_pWndEdit->SetSel(0, -1);
	m_pWndEdit->SetFocus();
	return TRUE;
}

BOOL ArxRleListCtrl::EndEdit(BOOL bCommit)
{
	if (!_IsEditVisible())
		return FALSE;

	CString str;
	m_pWndEdit->GetWindowText(str);
	BOOL bChanged = bCommit && str.Compare(GetItemText(m_ptEditting.x, m_ptEditting.y)) != 0;
	if (bChanged)
	{
		// update the list item
		const int rows = GetItemCount();
		const int cols = GetColumnCount();
		BOOL bRowValid = m_ptEditting.x >= 0 && m_ptEditting.x < rows;
		BOOL bColValid = m_ptEditting.y >= 0 && m_ptEditting.y < cols;

		if (bRowValid && bColValid)
		{
			CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(m_ptEditting.x));
			if(p != NULL)
			{
				p->aTexts[m_ptEditting.y] = str;
				CAdUiListCtrl::SetItemData(m_ptEditting.x, (DWORD_PTR)p);
			}

			CAdUiListCtrl::SetItemText(m_ptEditting.x, m_ptEditting.y, str);
		}

		_UnsetSortedColumn();
		GetParent()->SendMessage(WM_EDIT_COMMITTED, (WPARAM)m_ptEditting.x, (LPARAM)m_ptEditting.y);
	}
	m_pWndEdit->ShowWindow(SW_HIDE);
	m_ptEditting.x = -1;
	m_ptEditting.y = -1;
	return bChanged;
}

BOOL ArxRleListCtrl::StartCombo(int nItem, int nSubItem)
{
	// Get the grid width and height
	if (!_IsValidIndex(nItem) || nSubItem < 0 || nSubItem >= GetColumnCount())
		return FALSE;

	if (m_ptComboing.x == nItem && m_ptComboing.y == nSubItem)
		return TRUE;

	EndCombo(TRUE);
	EndEdit(TRUE);
	m_ptComboing.x = nItem;
	m_ptComboing.y = nSubItem;
	SetAllItemStates(RC_ITEM_SELECTED, RC_ITEM_UNSELECTED); // unselect all
	SetItemStates(m_ptComboing.x, RC_ITEM_SELECTED | RC_ITEM_FOCUSED);

	// Funny thing:
	// Changing CEdit style among ES_LEFT, ES_CENTER, ES_RIGHT at runtime works
	// sometimes and fails other times. It just cannot guarantee to be succeed.
	// So I decided to destroy and recreate the CEdit every time when the text
	// format changes.
	if (m_pWndCombo->GetSafeHwnd() != NULL)
		m_pWndCombo->DestroyWindow();

	if (!m_pWndCombo->Create(CBS_DROPDOWNLIST | WS_CHILD, CRect(0, 0, 1, 1), this, 0))
		return FALSE;

	CString strs = GetItemComboData(nItem,nSubItem);
	CStringArray aStr;
	_StringSplit(strs, aStr, _T(';'));
	for (int i = 0; i < aStr.GetSize(); i++)
		m_pWndCombo->AddString(aStr[i]);

	m_pWndCombo->SetFont(GetFont());

	CRect rcCombo;
	ListView_GetSubItemRect(GetSafeHwnd(), m_ptComboing.x, m_ptComboing.y, LVIR_LABEL, &rcCombo);
	if (m_ptComboing.y > 0 && GetImageList() != NULL && GetItemImage(m_ptComboing.x, m_ptComboing.y) >= 0)
		rcCombo.DeflateRect(16, 0, 0, 0);

	// Move the combobox to that grid, obtain text from the grid, display the
	// combobox, and, finally, highlights all text in the combobox and set the
	// windows focus to the combobox.
	m_pWndCombo->MoveWindow(&rcCombo);
	m_pWndCombo->SetWindowText(GetItemText(nItem,nSubItem));
	m_pWndCombo->ShowWindow(SW_SHOW);
	m_pWndCombo->SetFocus();
	return TRUE;
}

BOOL ArxRleListCtrl::EndCombo(BOOL bCommit)
{
	if (!_IsComboVisible())
		return FALSE;

	CString str;
	m_pWndCombo->GetWindowText(str);
	BOOL bChanged = bCommit && str.Compare(GetItemText(m_ptComboing.x, m_ptComboing.y)) != 0;
	if (bChanged)
	{
		// update the list item
		const int rows = GetItemCount();
		const int cols = GetColumnCount();
		BOOL bRowValid = m_ptComboing.x >= 0 && m_ptComboing.x < rows;
		BOOL bColValid = m_ptComboing.y >= 0 && m_ptComboing.y < cols;

		if (bRowValid && bColValid)
		{
			CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(m_ptComboing.x));
			if(p != NULL)
			{
				p->aTexts[m_ptComboing.y] = str;
				CAdUiListCtrl::SetItemData(m_ptComboing.x, (DWORD_PTR)p);
			}

			CAdUiListCtrl::SetItemText(m_ptComboing.x, m_ptComboing.y, str);
		}

		_UnsetSortedColumn();
		GetParent()->SendMessage(WM_COMBO_COMMITTED, (WPARAM)m_ptComboing.x, (LPARAM)m_ptComboing.y);
	}
	m_pWndCombo->ShowWindow(SW_HIDE);
	m_ptComboing.x = -1;
	m_ptComboing.y = -1;
	return bChanged;
}

CEdit* ArxRleListCtrl::GetEditControl()
{
	return m_pWndEdit;
}

CComboBox* ArxRleListCtrl::GetComboControl()
{
	return m_pWndCombo;
}


///////////////////////////////////////////////////////////////////////
//		Necessary overloading but Irrelevant to Users
///////////////////////////////////////////////////////////////////////
int ArxRleListCtrl::InsertColumn(int nCol, const LVCOLUMN *pColumn)
{
	EndEdit(TRUE);
	EndCombo(TRUE);
	const int idx = CAdUiListCtrl::InsertColumn(nCol, pColumn);
	if (idx >= 0)
		_UpdateColumn(idx, TRUE);
	return idx;
}

int ArxRleListCtrl::InsertColumn(int nCol, LPCTSTR lpColumnHeading, int nFormat, int nWidth, int nSubItem)
{
	EndEdit(TRUE);
	EndCombo(TRUE);
	const int idx = CAdUiListCtrl::InsertColumn(nCol, lpColumnHeading, nFormat, nWidth, nSubItem);
	if (idx >= 0)
		_UpdateColumn(idx, TRUE);
	return idx;
}

BOOL ArxRleListCtrl::DeleteColumn(int nCol)
{
	EndEdit(TRUE);
	EndCombo(TRUE);
	const BOOL res = CAdUiListCtrl::DeleteColumn(nCol);
	if (res)
		_UpdateColumn(nCol, FALSE);
	return res;
}

BOOL ArxRleListCtrl::SetCheck(int nItem, BOOL bCheck)
{
	const BOOL res = CAdUiListCtrl::SetCheck(nItem, bCheck);
	if (res && bCheck)
		_EnsureSingleCheck(nItem);
	return res;
}

BOOL ArxRleListCtrl::SetItemData(int nItem, DWORD dwData)
{
	CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
	if (p == NULL)
		return FALSE;
	p->dwData = dwData;
	CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
	return TRUE;
}

DWORD ArxRleListCtrl::GetItemData(int nItem) const
{
	CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
	if(p != NULL) return p->dwData;

	return 0;
}

BOOL ArxRleListCtrl::SetItemData(int nItem, int nSubItem, LPCTSTR lpText)
{
	CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
	if (p == NULL)
		return FALSE;
	p->aDatas[nSubItem] = lpText;
	CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
	return TRUE;
}

LPCTSTR ArxRleListCtrl::GetItemData(int nItem, int nSubItem) const
{
	CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
	if(p != NULL) return p->aDatas[nSubItem];

	return 0;
}

BOOL ArxRleListCtrl::SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem, int nImage, UINT nState, UINT nStateMask, LPARAM lParam)
{
	if ((nMask & LVIF_PARAM) != 0)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
		if (p != NULL)
		{
			p->dwData = lParam;
			lParam = (LPARAM)p;
			CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
		}
	}
	return CAdUiListCtrl::SetItem(nItem, nSubItem, nMask, lpszItem, nImage, nState, nStateMask, lParam);
}

BOOL ArxRleListCtrl::SetItem(const LVITEM *pItem)
{
	if (pItem == NULL)
		return FALSE;

	LVITEM li;
	memcpy(&li, pItem, sizeof(LVITEM));
	if ((li.mask & LVIF_PARAM) != 0)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(li.iItem));
		if (p != NULL)
		{
			p->dwData = li.lParam;
			li.lParam = (LPARAM)p;
			CAdUiListCtrl::SetItemData(li.iItem, (DWORD_PTR)p);
		}		
	}
	return CAdUiListCtrl::SetItem(&li);
}

BOOL ArxRleListCtrl::GetItem(LVITEM *pItem) const
{
	const BOOL res = CAdUiListCtrl::GetItem(pItem);
	if (res && (pItem->mask & LVIF_PARAM) != 0)
	{
		CItemData* p = (CItemData*)(pItem->lParam);
		if (p != NULL) pItem->lParam = p->dwData;
	}
	return res;
}

DWORD ArxRleListCtrl::SetExtendedStyle(DWORD dwNewStyle)
{
	dwNewStyle &= ~MUST_NOT_EX_STYLE;
	dwNewStyle |= MUST_EX_STYLE;
	return CAdUiListCtrl::SetExtendedStyle(dwNewStyle);
}

BOOL ArxRleListCtrl::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	dwRemove &= ~MUST_STYLE;
	dwRemove |= MUST_NOT_STYLE;
	dwAdd &= ~MUST_NOT_STYLE;
	dwAdd |= MUST_STYLE;
	return CAdUiListCtrl::ModifyStyle(dwRemove, dwAdd, nFlags);
}

BOOL ArxRleListCtrl::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	dwRemove &= ~MUST_EX_STYLE;
	dwRemove |= MUST_NOT_EX_STYLE;
	dwAdd &= ~MUST_NOT_EX_STYLE;
	dwAdd |= MUST_EX_STYLE;
	return CAdUiListCtrl::ModifyStyleEx(dwRemove, dwAdd, nFlags);
}

int ArxRleListCtrl::InsertItem(UINT nMask, int nItem, LPCTSTR lpText, UINT nState, UINT nStateMask, int nImage, LPARAM lParam)
{
	EndEdit(TRUE);
	EndCombo(TRUE);
	_UnsetSortedColumn();
	const int idx = CAdUiListCtrl::InsertItem(nMask, nItem, lpText, nState, nStateMask, nImage, lParam);
	if (idx >= 0)
	{
		_AllocItemMemory(idx);

		const int rows = GetItemCount();
		BOOL bRowValid = nItem >= 0 && nItem < rows;

		if (bRowValid)
		{
			CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
			if(p != NULL)
			{
				p->dwStates = nState;
				p->dwData = lParam;
				p->aImages[0] = nImage;
				p->aTexts[0] = lpText;
				CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
			}
		}
	}

	return idx;
}

int ArxRleListCtrl::InsertItem(int nItem, LPCTSTR lpText)
{	
	EndEdit(TRUE);
	EndCombo(TRUE);
	_UnsetSortedColumn();
	const int idx = CAdUiListCtrl::InsertItem(nItem, lpText);
	if (idx >= 0)
	{
		_AllocItemMemory(idx);

		const int rows = GetItemCount();
		BOOL bRowValid = nItem >= 0 && nItem < rows;

		if (bRowValid)
		{
			CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
			if(p != NULL)
			{
				p->aTexts[0] = lpText;
				CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
			}
		}
	}
	return idx;
}

int ArxRleListCtrl::InsertItem(const LVITEM *pItem)
{
	EndEdit(TRUE);
	EndCombo(TRUE);
	_UnsetSortedColumn();
	const int idx = CAdUiListCtrl::InsertItem(pItem);
	if (idx >= 0)
	{
		_AllocItemMemory(idx);

		const int rows = GetItemCount();
		const int cols = GetColumnCount();
		BOOL bRowValid = pItem->iItem >= 0 && pItem->iItem < rows;
		BOOL bColValid = pItem->iSubItem >= 0 && pItem->iSubItem < cols;

		if (bRowValid && bColValid)
		{
			CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(pItem->iItem));
			if(p != NULL)
			{
				p->dwStates = pItem->state;
				p->aImages[pItem->iSubItem] = pItem->iImage;
				p->aTexts[pItem->iSubItem] = pItem->pszText;
				CAdUiListCtrl::SetItemData(pItem->iItem, (DWORD_PTR)p);
			}
		}
	}

	return idx;
}

int ArxRleListCtrl::InsertItem(int nItem, LPCTSTR lpText, int nImage)
{	
	EndEdit(TRUE);
	EndCombo(TRUE);
	_UnsetSortedColumn();
	const int idx = CAdUiListCtrl::InsertItem(nItem, lpText, nImage);
	if (idx >= 0)
	{
		_AllocItemMemory(idx);

		const int rows = GetItemCount();
		BOOL bRowValid = nItem >= 0 && nItem < rows;

		if (bRowValid)
		{
			CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
			if(p != NULL)
			{
				p->aImages[0] = nImage;
				p->aTexts[0] = lpText;
				CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
			}
		}
	}
	return idx;
}


///////////////////////////////////////////////////////////////////////
//		Helper functions for internal use
///////////////////////////////////////////////////////////////////////
BOOL ArxRleListCtrl::_IsValidIndex(int nIndex) const
{
	return nIndex >= 0 && nIndex < CAdUiListCtrl::GetItemCount();
}

BOOL ArxRleListCtrl::_IsEditVisible() const
{
	return m_bAllowEdit
		&& m_ptEditting.x >= 0 && m_ptEditting.x < CAdUiListCtrl::GetItemCount()
		&& m_ptEditting.y >= 0 && m_ptEditting.y < GetColumnCount();
}

BOOL ArxRleListCtrl::_IsComboVisible() const
{
	return m_ptComboing.x >= 0 && m_ptComboing.x < CAdUiListCtrl::GetItemCount()
		&& m_ptComboing.y >= 0 && m_ptComboing.y < GetColumnCount();
}

BOOL ArxRleListCtrl::_ItemCheckMonitor(int nIndex, BOOL bBefore, BOOL bAfter, UINT nMsg)
{
	if (!_IsValidIndex(nIndex)
		|| m_nChkStyle == RC_CHKBOX_NONE
		|| (bBefore && bAfter)
		|| (!bBefore && !bAfter))
	{
		return FALSE;
	}

	if (m_nChkStyle == RC_CHKBOX_SINGLE)
	{
		// Only one item can be checked
		if (!bBefore && bAfter)
		{
			SetAllItemStates(RC_ITEM_CHECKED, RC_ITEM_UNCHECKED); // uncheck all
			SetItemStates(nIndex, RC_ITEM_CHECKED);
		}		
	}
	else if (m_nChkStyle == RC_CHKBOX_DISABLED)
	{
		// Cannot change the item checked/unchecked states by mouse clicks
		SetItemStates(nIndex, bBefore ? RC_ITEM_CHECKED : RC_ITEM_UNCHECKED);
		return TRUE;
	}	

	SetAllItemStates(RC_ITEM_SELECTED, RC_ITEM_UNSELECTED); // unselect all
	SetItemStates(nIndex, RC_ITEM_SELECTED | RC_ITEM_FOCUSED);
	GetParent()->SendMessage(WM_ON_CHKBOX, (WPARAM)nIndex, (LPARAM)nMsg);
	return TRUE;
}

void ArxRleListCtrl::_MouseClkMonitor(UINT nMsg, UINT nFlags, CPoint point, BOOL bTriggerEdit)
{
	LVHITTESTINFO hti;
	hti.pt = point;
	const int idx = SubItemHitTest(&hti);
	const BOOL before = CAdUiListCtrl::GetCheck(idx) > 0;
	if(GetComboStates(idx, hti.iSubItem))
	{
		const BOOL isCombo = _IsComboVisible();
		const BOOL isComboActive = ExamItemStates(idx, RC_ITEM_FOCUSED | RC_ITEM_SELECTED);
		EndEdit(TRUE);
		EndCombo(TRUE);

		switch (nMsg)
		{
		case WM_LBUTTONDOWN:
			CAdUiListCtrl::OnLButtonDown(nFlags, point);
			break;

		case WM_LBUTTONDBLCLK:
			CAdUiListCtrl::OnLButtonDblClk(nFlags, point);
			break;
		}

		const BOOL comboStatsChanged = _ItemCheckMonitor(idx, before, CAdUiListCtrl::GetCheck(idx) > 0, nMsg);
		if(isComboActive && !comboStatsChanged)
			StartCombo(idx, hti.iSubItem);
	}
	else
	{
		const BOOL isEdit = _IsEditVisible();
		EndEdit(TRUE);
		EndCombo(TRUE);
		const BOOL isEditActive = bTriggerEdit ? ExamItemStates(idx, RC_ITEM_FOCUSED | RC_ITEM_SELECTED) : FALSE;

		switch (nMsg)
		{
		case WM_LBUTTONDOWN:
			CAdUiListCtrl::OnLButtonDown(nFlags, point);
			break;

		case WM_LBUTTONDBLCLK:
			CAdUiListCtrl::OnLButtonDblClk(nFlags, point);
			break;

		case WM_MBUTTONDOWN:
			CAdUiListCtrl::OnMButtonDown(nFlags, point);
			break;

		case WM_MBUTTONDBLCLK:
			CAdUiListCtrl::OnMButtonDblClk(nFlags, point);
			break;

		case WM_RBUTTONDOWN:
			CAdUiListCtrl::OnRButtonDown(nFlags, point);
			break;

		case WM_RBUTTONDBLCLK:
			CAdUiListCtrl::OnRButtonDblClk(nFlags, point);
			break;

		default:
			break;
		}

		const BOOL editStatsChanged = _ItemCheckMonitor(idx, before, CAdUiListCtrl::GetCheck(idx) > 0, nMsg);

		if (bTriggerEdit && m_bAllowEdit && !editStatsChanged && !isEdit && isEditActive)
			StartEdit(idx, hti.iSubItem);
	}
}

void ArxRleListCtrl::_StringSplit(const CString &str, CStringArray &arr, TCHAR chDelimitior)
{
	int nStart = 0, nEnd = 0;
	arr.RemoveAll();

	while (nEnd < str.GetLength())
	{
		// determine the paragraph ("xxx,xxx,xxx;")
		nEnd = str.Find(chDelimitior, nStart);
		if( nEnd == -1 )
		{
			// reached the end of string
			nEnd = str.GetLength();
		}

		CString s = str.Mid(nStart, nEnd - nStart);
		if (!s.IsEmpty())
			arr.Add(s);

		nStart = nEnd + 1;
	}
}

void ArxRleListCtrl::_UnsetSortedColumn()
{
	m_nSortCol = -1;
	m_bSortAscending = TRUE;
}

DWORD ArxRleListCtrl::_GetHeaderTextFormat(int nColumn) const
{
	if (!HasColumnHeader())
		return ES_LEFT;

	HDITEM hd;
	hd.mask = HDI_FORMAT;
	if (!GetHeaderCtrl()->GetItem(nColumn, &hd))
		return ES_LEFT;

	if (hd.fmt & HDF_CENTER)
	{	
		return ES_CENTER;
	}
	else if (hd.fmt & HDF_RIGHT)
	{
		return ES_RIGHT;
	}
	else
	{
		return ES_LEFT;
	}
}

BOOL ArxRleListCtrl::_SetItemStatesNoVerify(int nItem, DWORD dwNewStates)
{
	if (dwNewStates == RC_ITEM_NONE)
		return FALSE;

	BOOL bResult = TRUE;

	if (dwNewStates & RC_ITEM_SELECTED)
		bResult &= CAdUiListCtrl::SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED);

	if (dwNewStates & RC_ITEM_UNSELECTED)
		bResult &= CAdUiListCtrl::SetItemState(nItem, 0, LVIS_SELECTED);

	if (dwNewStates & RC_ITEM_CHECKED)
		bResult &= CAdUiListCtrl::SetCheck(nItem, TRUE);

	if (dwNewStates & RC_ITEM_UNCHECKED)
		bResult &= CAdUiListCtrl::SetCheck(nItem, FALSE);

	if (dwNewStates & RC_ITEM_FOCUSED)
		bResult &= CAdUiListCtrl::SetItemState(nItem, LVIS_FOCUSED, LVIS_FOCUSED);

	if (dwNewStates & RC_ITEM_UNFOCUSED)
		bResult &= CAdUiListCtrl::SetItemState(nItem, 0, LVIS_FOCUSED);

	return bResult;
}

void ArxRleListCtrl::_FreeItemMemory(int nItem)
{
	CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(nItem));
	if (p != NULL)
	{
		CAdUiListCtrl::SetItemData(nItem, 0);
		delete p;
	}
}

void ArxRleListCtrl::_AllocItemMemory(int nItem)
{
	ASSERT(_IsValidIndex(nItem));
	const int cols = GetColumnCount();
	ASSERT(cols > 0);
	CItemData* p = new CItemData(cols);
	CAdUiListCtrl::SetItemData(nItem, (DWORD_PTR)p);
}

void ArxRleListCtrl::_EnsureSingleCheck(int nItem)
{
	if (m_nChkStyle == RC_CHKBOX_SINGLE)
	{
		const int FIRST = nItem < 0 ? GetFirstItem(RC_ITEM_CHECKED) : nItem;
		if (FIRST >= 0)
		{
			const int items = CAdUiListCtrl::GetItemCount();
			for (int i = FIRST + 1; i < items; i++)
			{
				if (CAdUiListCtrl::GetCheck(i))
					CAdUiListCtrl::SetCheck(i, FALSE);
			}
		}		
	}
}

void ArxRleListCtrl::_UpdateColumn(int nColumn, BOOL bInsert)
{
	const int items = GetItemCount();
	for (int i = 0; i < items; i++)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(i));
		if(p != NULL)
		{
			if (bInsert)
				p->InsertColumn(nColumn);
			else
				p->DeleteColumn(nColumn);
			CAdUiListCtrl::SetItemData(i, (DWORD_PTR)p);
		}
	}
}

BOOL ArxRleListCtrl::_PartialSort(int nStart, int nEnd)
{
	if (nStart >= nEnd || !_IsValidIndex(nStart) || !_IsValidIndex(nEnd))
		return FALSE;

	const int count = nEnd - nStart + 1;
	int i = 0;
	int* aIndices = new int[count];
	for (i = 0; i < count; i++)
		aIndices[i] = nStart + i;
	
	_QuickSortRecursive(aIndices, 0, count - 1); 

	// rearrange items
	const int cols = GetColumnCount();
	CItemData* items = new CItemData[count];
	for (i = 0; i < count; i++)
	{
		CItemData* p = (CItemData*)(CAdUiListCtrl::GetItemData(aIndices[i]));
		if(p != NULL) items[i] = *p;
		items[i].dwStates = GetItemStates(aIndices[i]);
	}

	for (i = 0; i < count; i++)
	{
		SetItemStates(nStart + i, items[i].dwStates);
		SetItemData(nStart + i, items[i].dwData);
		for (int j = 0; j < cols; j++)
		{
			SetItemData(nStart + i, j, items[i].aDatas[j]);
			SetItemImage(nStart + i, j, items[i].aImages[j]);
			SetItemText(nStart + i, j, items[i].aTexts[j]);
			SetComboStates(nStart + i, j, items[i].aCombos[j]);
			SetItemTextColor(nStart + i, j, items[i].aTextColors[j]);
			SetItemBkColor(nStart + i, j, items[i].aBkColors[j]);
		}
	}
	delete [] items;
	delete [] aIndices;
	return TRUE;
}

int ArxRleListCtrl::_CompareItems(int nItem1, int nItem2)
{
	const CString s1 = GetItemText(nItem1, m_nSortCol);
	const CString s2 = GetItemText(nItem2, m_nSortCol);

	DWORD dw1, dw2;
	if(_IsHexNumber(s1, dw1) && _IsHexNumber(s2, dw2))
		return _HexNumberCompare(dw1, dw2);

	double f1, f2;
	if(_IsDecNumber(s1, f1) && _IsDecNumber(s2, f2))
		return _DecNumberCompare(f1, f2);

	COleDateTime date1, date2;
	if(_IsDate(s1, date1) && _IsDate(s2, date2))
		return _DateCompare(date1, date2);
	
	// plain text.
	return s1.Compare(s2);
}

int ArxRleListCtrl::_FindSeparator(int nStartAfter, int nColumn) const
{
	if (m_pszSeparator == NULL)
		return -1;

	const int items = GetItemCount();
	for (int i = nStartAfter + 1; i < items; i++)
	{
		if (GetItemText(i, nColumn) == m_pszSeparator)
			return i;
	}
	return -1;
}

void ArxRleListCtrl::_QuickSortRecursive(int* pArr, int nLow, int nHigh)
{
	int i = nHigh, j = nLow;
	int n = pArr[(nLow + nHigh) / 2];
	do
	{
		if (m_bSortAscending)
		{
			while (_CompareItems(pArr[j], n) < 0)
				j++;

			while (_CompareItems(pArr[i], n) > 0)
				i--;
		}
		else
		{
			while (_CompareItems(pArr[j], n) > 0)
				j++;

			while (_CompareItems(pArr[i], n) < 0)
				i--;
		}

		if ( i >= j )
		{
			if ( i != j )
			{
				int nTemp = pArr[i];
				pArr[i] = pArr[j];
				pArr[j] = nTemp;
			}

			i--;
			j++;
		}
		
	} while (j <= i);

	if (nLow < i)
		_QuickSortRecursive(pArr,nLow,i);

	if (j < nHigh)
		_QuickSortRecursive(pArr,j,nHigh);
}


///////////////////////////////////////////////////////////////////////
// A set of functions used for item text format determining
///////////////////////////////////////////////////////////////////////
BOOL ArxRleListCtrl::_IsDecNumber(const CString& str, double& f)
{
	if (str.IsEmpty())
		return FALSE;

	LPTSTR p;
	f = _tcstod(str, &p);
	return (*p == _T('\0') || (*p == _T('%') && p[1] == _T('\0')));
}

int ArxRleListCtrl::_DecNumberCompare(double f1, double f2)
{
	if(f1 < f2)
		return -1;

	if(f1 > f2)
		return 1;

	return 0;
}

BOOL ArxRleListCtrl::_IsHexNumber(const CString& str, DWORD& dw)
{
	if (str.IsEmpty())
		return FALSE;

	LPTSTR p;
	dw = _tcstoul(str, &p, 16);
	return *p == _T('\0');
}

int ArxRleListCtrl::_HexNumberCompare(DWORD dw1, DWORD dw2)
{
	if (dw1 > dw2)
		return 1;

	if (dw1 < dw2)
		return -1;

	return 0;
}

BOOL ArxRleListCtrl::_IsDate(const CString& str, COleDateTime& date)
{
	return date.ParseDateTime(str);
}

int ArxRleListCtrl::_DateCompare(const COleDateTime& date1, const COleDateTime& date2)
{
	if (date1 < date2)
		return -1;

	if (date1 > date2)
		return 1;

	return 0;
}