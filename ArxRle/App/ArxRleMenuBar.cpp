///////////////////////////////////////////////////////////////////////////////
// ArxRleMenuBar.h : source file
// 
// Description:
// This file include the following class that can be used:
// 1. CMenuXP:
//    An ownerdraw menu that can have sidebar,menu-button and menuitem-icon,
//	also can be created by normal method.The general use same as normal menu,
//	can be used seperately.
// 2. CToolBarEx:
//    An ownerdraw toolbar. It can't docking by framewindow. So,if you use,should
//	place it in a container window(CReBar,CDialogbar ect).The creation method same
//	as normal ToolBar.
// 3. CToolBarCtrlEx:
//	An ownerdraw ToolBarCtrl that have a CMenuXP attach in it.For using,create a 
//	CMenuXP or CMenu object,then load it in CToolBarCtrlEx.It also can't docked by
//	framewindow,should used in a container wndow.
// 4. ArxRleMenuBar:
//    An ownerdraw ToolBarXP that have a ToolBarXP attach in it.For using,create a 
//	ToolBarXP or ArxRleMenuXP object,then load it in ArxRleMenuBar.It also can't docked by
//	framewindow,should used in a container wndow.
//
//  ArxRleBrokenLine.cpp  Implementation of CMenuXP��CToolBarEX��CToolBarCtrlEx��ArxRleMenuBar
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleMenuBar.h"


/////////////////////////////////////////////////////////////////////////////
// CBCGKeyHelper
CBCGKeyHelper::CBCGKeyHelper(LPACCEL lpAccel) :	m_lpAccel (lpAccel)
{
}

CBCGKeyHelper::CBCGKeyHelper() : m_lpAccel (NULL)
{
}

CBCGKeyHelper::~CBCGKeyHelper()
{
}

void CBCGKeyHelper::Format (CString& str) const
{
	str.Empty ();

	if (m_lpAccel == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	if (m_lpAccel->fVirt & FCONTROL)
	{
		str += _T("Ctrl+");
	}

	if (m_lpAccel->fVirt & FSHIFT)
	{
		str += _T("Shift+");
	}

	if (m_lpAccel->fVirt & FALT)
	{
		str += _T("Alt+");
	}

	if (m_lpAccel->fVirt & FVIRTKEY)
	{
		TCHAR keyname[64];
		UINT vkey = MapVirtualKey(m_lpAccel->key, 0)<<16;
		GetKeyNameText(vkey, keyname, sizeof(keyname));
		str += keyname;
	}
	else if (m_lpAccel->key != 27)
	{
		str += (char) m_lpAccel->key;
	}
}

void CBCGKeyHelper::AddVirtKeyStr (CString& str, UINT uiVirtKey, BOOL bLast) const
{
	#define BUFFER_LEN 50
	TCHAR szBuffer [BUFFER_LEN + 1];

	TRACE("KeyboardLayout: 0x%x\n", ::GetKeyboardLayout (0));

	UINT nScanCode = ::MapVirtualKeyEx (uiVirtKey, 0, 
		::GetKeyboardLayout (0)) <<16 | 0x1;
	
	if (uiVirtKey >= VK_PRIOR && uiVirtKey <= VK_HELP)
	{
		nScanCode |= 0x01000000;
	}
	
	::GetKeyNameText (nScanCode, szBuffer, BUFFER_LEN);
	
	CString strKey(szBuffer);
	strKey.MakeLower();
	
	for (int nCount = 0; nCount < strKey.GetLength(); nCount++)
	{
		TCHAR c = strKey[nCount];
		if (IsCharLower (c))
		{
			c = (TCHAR) toupper (c);
			strKey.SetAt (nCount, c);
			break;
		}
	}

	str += strKey;	
	if (!bLast)
	{
		str += '+';
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMenuXP

IMPLEMENT_DYNCREATE(CMenuXP, CMenu)

const int CXGAP = 0;			// num pixels between button and text
const int CXTEXTMARGIN = 2;		// num pixels after hilite to start text
const int CXBUTTONMARGIN = 2;	// num pixels wider button is than bitmap
const int CYBUTTONMARGIN = 2;	// ditto for height

const int DT_MYSTANDARD = DT_SINGLELINE|DT_LEFT|DT_VCENTER;

CMenuXP::CMenuXP()
{
	//initialize menu font with the default
	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);
	VERIFY(m_fontMenu.CreateFontIndirect(&info.lfMenuFont));

	//initialize colors with system default
	m_clrBackGround = ::GetSysColor(COLOR_MENU);
	//m_clrSelectedBar = ::GetSysColor(COLOR_HIGHLIGHT);
	m_clrSelectedBar = RGB(193, 210, 238);   //����Ĭ�ϵ�ֵ��ΪXP��ɫ��
	m_clrSelectedText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_clrText = ::GetSysColor(COLOR_MENUTEXT);
	m_clrDisabledText = ::GetSysColor(COLOR_GRAYTEXT);
	m_clrIconArea = m_clrBackGround;

	//initialize sidebar colors
	m_clrSideBarStart = RGB(0, 0, 192);
	m_clrSideBarEnd = RGB(0, 0, 0);

	//the default sytle is office style
	//Ĭ����Office�ֽ����ΪXP
	m_Style = STYLE_XP;

	m_bBreak = false;
	m_bBreakBar = false;
}

CMenuXP::~CMenuXP()
{
	m_fontMenu.DeleteObject();
	Clear();
}

void CMenuXP::MeasureItem( LPMEASUREITEMSTRUCT lpms )
{
	if (lpms->CtlType != ODT_MENU)
		return;

	CMenuXPItem	*pItem = (CMenuXPItem *)lpms->itemData;
	
	if (!pItem || !pItem->IsMyData())
		return;

	if (pItem->m_bSideBar)
	{
		lpms->itemWidth = pItem->m_nSize;
		lpms->itemHeight = 0;
	}
	else if (pItem->m_bSeparator)
	{
		lpms->itemHeight = ::GetSystemMetrics(SM_CYMENUCHECK)>>1;
		lpms->itemWidth  = 0;
	}
	else
	{
		CWindowDC dc(NULL);
		CRect rcText(0,0,0,0);
		CFont* pOldFont = dc.SelectObject(&m_fontMenu);
		dc.DrawText(pItem->m_strText, rcText, DT_MYSTANDARD|DT_CALCRECT);
		dc.SelectObject(pOldFont);

		lpms->itemHeight = max(rcText.Height(), pItem->m_nSize + (CYBUTTONMARGIN<<1));
		if (pItem->m_bButtonOnly)
		{
			lpms->itemWidth = lpms->itemHeight;
		}
		else
		{			
			int cx = rcText.Width();
			cx += CXTEXTMARGIN<<1;
			cx += CXGAP;
			cx += (pItem->m_nSize + CYBUTTONMARGIN * 2) <<1;
			lpms->itemWidth = cx;
		}
	}
	
	lpms->itemWidth -= GetSystemMetrics(SM_CXMENUCHECK)-1;
}

void CMenuXP::DrawItem( LPDRAWITEMSTRUCT lpds )
{
	ASSERT(lpds);
	if (lpds->CtlType != ODT_MENU)
		return;
	CMenuXPItem * pItem = (CMenuXPItem *)lpds->itemData;
	if (!pItem)
		return;
	
	ASSERT(lpds->itemAction != ODA_FOCUS);
	ASSERT(lpds->hDC);
	CDC dc;
	dc.Attach(lpds->hDC);

	CRect rcItem = lpds->rcItem;

	TRACE("DrawItem: ID(%d), Widht(%d),  Height(%d)\n", 
		lpds->itemID, rcItem.Width(), rcItem.Height());

	if (pItem->m_bSideBar)
	{
		CRect rcClipBox;
		dc.GetClipBox(rcClipBox);
		
		CRect rc = rcItem;
		rc.top = rcClipBox.top;
		rc.bottom = rcClipBox.bottom;
		DrawSideBar(&dc, rc, pItem->m_hIcon, pItem->m_strText);
	}
	else if (pItem->m_bSeparator) 
	{
		DrawBackGround(&dc, rcItem, FALSE, FALSE);
		CRect rc = rcItem;
		rc.top += rc.Height()>>1;
		dc.DrawEdge(&rc, EDGE_ETCHED, BF_TOP);
		
	/*	if (m_Style == STYLE_XP)   //�����XP���ͽ��ָ��߻浽BackGround���������ｫ��ȡ����
		{
			CRect rcArea(rcItem.TopLeft(),
				CSize(pItem->m_nSize + (CYBUTTONMARGIN<<1), 
				pItem->m_nSize + (CYBUTTONMARGIN<<1)));
			DrawIconArea(&dc, rcArea, FALSE, FALSE, FALSE);
		}*/
	} 
	else
	{
		BOOL bDisabled = lpds->itemState & ODS_GRAYED;
		BOOL bSelected = lpds->itemState & ODS_SELECTED;
		BOOL bChecked  = lpds->itemState & ODS_CHECKED;

		DrawBackGround(&dc, rcItem, bSelected, bDisabled);
		
		if (m_Style == STYLE_XP)
		{
			CRect rcArea(rcItem.TopLeft(), CSize(rcItem.Height(), rcItem.Height()));
			DrawIconArea(&dc, rcArea, bSelected, bDisabled, bChecked);
		}

		CRect rcButton(rcItem.TopLeft(), CSize(rcItem.Height(), rcItem.Height()));
		if (pItem->m_bButtonOnly)
			rcButton = rcItem;
		if (pItem->m_hIcon || bChecked)
		{
			DrawButton(&dc, rcButton, bSelected, bDisabled, bChecked);
		}
		if (pItem->m_hIcon)
		{
			CRect	rcIcon = rcButton;
			rcIcon.DeflateRect(2, 2);
			DrawIcon(&dc, rcIcon, pItem->m_hIcon, bSelected, bDisabled);
		}
		else if (bChecked)	
		{
			CRect	rcCheck = rcButton;
			rcCheck.DeflateRect(2, 2);
			DrawCheckMark(&dc, rcCheck, bSelected);
		}

		if (!pItem->m_bButtonOnly)
		{
			CRect rcText = rcItem;
			rcText.left += rcButton.Width() + CXGAP + CXTEXTMARGIN;
			rcText.right -= pItem->m_nSize;
			DrawText(&dc, rcText, pItem->m_strText, bSelected, bDisabled, lpds->itemState&ODS_DEFAULT ? 1 : 0);
		}
	}
	dc.Detach();
}

void CMenuXP::DrawBackGround(CDC *pDC, CRect rect, BOOL bSelected, BOOL bDisabled)
{
	if (bSelected)
	{
		FillRect(pDC, rect, bDisabled? ((m_Style==STYLE_XP)?m_clrBackGround:m_clrSelectedBar) : m_clrSelectedBar);
	}
	else
	{
		FillRect(pDC, rect, m_clrBackGround);
	}

	if (m_Style == STYLE_XP && bSelected && !bDisabled)
	{
		CGdiObject *pOldBrush = pDC->SelectStockObject(HOLLOW_BRUSH);
		CGdiObject	*pOldPen = pDC->SelectStockObject(BLACK_PEN);
		pDC->Rectangle(rect);
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
	}
}

void CMenuXP::DrawButton(CDC *pDC, CRect rect, BOOL bSelected, BOOL bDisabled, BOOL bChecked)
{
	if (m_Style == STYLE_OFFICE)
	{
		FillRect(pDC, rect, (bChecked && !bSelected) ? m_clrBackGround+RGB(2, 2, 2) : m_clrBackGround);	
		if (!bDisabled && (bSelected || bChecked) )
		{
			pDC->DrawEdge(rect, bChecked ? BDR_SUNKENOUTER : BDR_RAISEDINNER,
				BF_RECT);
		}
	}
	else if (m_Style == STYLE_XP && !bSelected)
	{
		if (bChecked && !bDisabled)
		{
			DrawBackGround(pDC, rect, TRUE, FALSE);
		}
	}
	
}

void CMenuXP::DrawIconArea(CDC *pDC, CRect rect, BOOL bSelected, BOOL bDisabled, BOOL bChecked)
{
	if (m_Style != STYLE_XP)
		return;

	if (!bSelected || bDisabled)
	{
		FillRect(pDC, rect, m_clrIconArea);
	}
}

void CMenuXP::DrawIcon(CDC *pDC, CRect rect, HICON hIcon, BOOL bSelected, BOOL bDisabled)
{
	if (bDisabled)
	{
		DrawEmbossed(pDC, hIcon, rect);
	}
	else
	{
		::DrawIconEx(pDC->m_hDC, rect.left, rect.top, hIcon,
			rect.Width(), rect.Height(), 0, NULL,
			DI_NORMAL);
	}
}

void CMenuXP::DrawSideBar(CDC *pDC, CRect rect, HICON hIcon, CString strText)
{
	rect.right += 3;

	HBITMAP	bmpBar = CreateGradientBMP(
		pDC->m_hDC, m_clrSideBarStart, m_clrSideBarEnd,
		rect.Width(), rect.Height(),
		0, 256);
	if (bmpBar)
	{
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		HBITMAP hOldBmp = (HBITMAP)::SelectObject(memDC.m_hDC, bmpBar);
		pDC->BitBlt(rect.left, rect.top,
			rect.Width(), rect.Height(),
			&memDC, 0, 0, SRCCOPY);
		::SelectObject(memDC, hOldBmp);
		::DeleteObject(bmpBar);
	}
	CFont	vertFont;
	vertFont.CreateFont(12, 0, 900, 900, FW_BOLD,
		0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH|FIXED_PITCH, _T("����"));
	CFont *pOldFont = pDC->SelectObject(&vertFont);
	COLORREF oldColor = pDC->GetTextColor();
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(rect.left+2, rect.bottom-4, strText);
	pDC->SetTextColor(oldColor);	
	pDC->SelectObject(pOldFont);
	vertFont.DeleteObject();
}

void CMenuXP::DrawCheckMark(CDC *pDC, CRect rect, BOOL bSelected)
{
	CRect	rcDest = rect;
	pDC->DrawFrameControl(rcDest, DFC_MENU, DFCS_MENUCHECK);
}

void CMenuXP::DrawText(CDC *pDC, CRect rect, CString strText, BOOL bSelected, BOOL bDisabled, BOOL bBold)
{
	CFont*	pOldFont;
	CFont	fontBold;

	if (bBold)
	{
		LOGFONT	logFont;
		m_fontMenu.GetLogFont(&logFont);
		logFont.lfWeight = FW_BOLD;
		fontBold.CreateFontIndirect(&logFont);

		pOldFont = pDC->SelectObject(&fontBold);
	}
	else
	{
		pOldFont = pDC->SelectObject(&m_fontMenu);
	}

	pDC->SetBkMode(TRANSPARENT);
	if (bDisabled && (!bSelected || m_Style == STYLE_XP))
	{
		DrawMenuText(*pDC, rect + CPoint(1, 1), strText, m_clrSelectedText);
	}
	if (bDisabled)
	{
		DrawMenuText(*pDC, rect, strText, m_clrDisabledText);
	}
	else
	{
		DrawMenuText(*pDC, rect, strText, bSelected? m_clrSelectedText : m_clrText);
	}

	pDC->SelectObject(pOldFont);

	if (bBold)
		fontBold.DeleteObject();
}

BOOL CMenuXP::SetMenuFont(LOGFONT	lgfont)
{
	m_fontMenu.DeleteObject();
	return m_fontMenu.CreateFontIndirect(&lgfont);
}

void CMenuXP::Clear(void)
{
	UINT	nCount = GetMenuItemCount();
	for (UINT i=0; i<nCount; i++)
	{
		MENUITEMINFO	info;
		memset(&info, 0, sizeof(MENUITEMINFO));
		info.cbSize = sizeof(MENUITEMINFO);
		info.fMask = MIIM_DATA | MIIM_TYPE;
		GetMenuItemInfo(i, &info, TRUE);
		
		CMenuXPItem *pData = (CMenuXPItem *)info.dwItemData;
		if ((info.fType & MFT_OWNERDRAW) && pData && pData->IsMyData())
		{
			delete pData;
		}

		CMenu	*pSubMenu = GetSubMenu(i);
		if (pSubMenu && pSubMenu->IsKindOf(RUNTIME_CLASS(CMenuXP)))
			delete pSubMenu;
	}
}

const DWORD	MAGICROP   = 0xb8074a;
const COLORREF CWHITE  = RGB(255,255,255);

void CMenuXP::DrawEmbossed(CDC *pDC, HICON hIcon, CRect rect, BOOL bColor)
{
	CDC	memdc;
	memdc.CreateCompatibleDC(pDC);
	int cx = rect.Width();
	int cy = rect.Height();

	CBitmap bm;
	if (bColor)
		bm.CreateCompatibleBitmap(pDC, cx, cy);
	else
		bm.CreateBitmap(cx, cy, 1, 1, NULL);

	CBitmap* pOldBitmap = memdc.SelectObject(&bm);
	memdc.PatBlt(0, 0, cx, cy, WHITENESS);
	::DrawIconEx(memdc.m_hDC, 0, 0, hIcon, cx, cy, 1, NULL, DI_NORMAL);

	COLORREF colorOldBG = pDC->SetBkColor(CWHITE);

	CBrush brShadow(GetSysColor(COLOR_3DSHADOW));
	CBrush brHilite(GetSysColor(COLOR_3DHIGHLIGHT));
	CBrush* pOldBrush = pDC->SelectObject(&brHilite);
	pDC->BitBlt(rect.left+1, rect.top+1, cx, cy, &memdc, 0, 0, MAGICROP);
	pDC->SelectObject(&brShadow);
	pDC->BitBlt(rect.left, rect.top, cx, cy, &memdc, 0, 0, MAGICROP);
	pDC->SelectObject(pOldBrush);
	pDC->SetBkColor(colorOldBG);
	memdc.SelectObject(pOldBitmap);
	bm.DeleteObject();
	brShadow.DeleteObject();
	brHilite.DeleteObject();
}

void CMenuXP::FillRect(CDC *pDC, const CRect& rc, COLORREF color)
{
	CBrush brush(color);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();
}

HBITMAP CMenuXP::CreateGradientBMP(HDC hDC,COLORREF cl1,COLORREF cl2,int nWidth,int nHeight,int nDir,int nNumColors)
{
	if(nNumColors > 256)
		nNumColors = 256;

	COLORREF		PalVal[256];
	memset(PalVal, 0, sizeof(COLORREF)*256);

	int nIndex;
	BYTE peRed=0,peGreen=0,peBlue=0;

	int r1=GetRValue(cl1);
	int r2=GetRValue(cl2);
	int g1=LOBYTE(cl1<<8);//GetGValue(cl1);
	int g2=LOBYTE(cl2>>8);//GetGValue(cl2);
	int b1=GetBValue(cl1);
	int b2=GetBValue(cl2);

    for (nIndex = 0; nIndex < nNumColors; nIndex++)
    {
        peRed = (BYTE) (r1 + MulDiv((r2-r1),nIndex,nNumColors-1));
        peGreen = (BYTE) (g1 + MulDiv((g2-g1),nIndex,nNumColors-1));
        peBlue = (BYTE) (b1 + MulDiv((b2-b1),nIndex,nNumColors-1));

		PalVal[nIndex]=(peRed << 16) | (peGreen << 8) | (peBlue);
	}

	int x,y,w,h;
	w=nWidth;
	h=nHeight;
	
	LPDWORD			pGradBits;
	BITMAPINFO		GradBitInfo;

	pGradBits=(DWORD*) malloc(w*h*sizeof(DWORD));
	memset(&GradBitInfo,0,sizeof(BITMAPINFO));

	GradBitInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	GradBitInfo.bmiHeader.biWidth=w;
	GradBitInfo.bmiHeader.biHeight=h;
	GradBitInfo.bmiHeader.biPlanes=1;
	GradBitInfo.bmiHeader.biBitCount=32;
	GradBitInfo.bmiHeader.biCompression=BI_RGB;
	
	if(nDir==0) 
	{
		for(y=0;y<h;y++) 
		{
			for(x=0;x<w;x++) 
			{
				*(pGradBits+(y*w)+x)=PalVal[MulDiv(nNumColors,y,h)];
			}
		}
	}
	else if(nDir==1) 
	{
		for(y=0;y<h;y++)
		{
			int l,r;
			l=MulDiv((nNumColors/2),y,h);
			r=l+(nNumColors/2)-1;
			for(x=0;x<w;x++)
			{
				*(pGradBits+(y*w)+x)=PalVal[l+MulDiv((r-l),x,w)];
			}
		}
	}
	else if(nDir==2)
	{
		for(x=0;x<w;x++)
		{
			for(y=0;y<h;y++)
			{
				*(pGradBits+(y*w)+x)=PalVal[MulDiv(nNumColors,x,w)];
			}
		}
	}
	else if(nDir==3)
	{
		for(y=0;y<h;y++)
		{
			int l,r;
			r=MulDiv((nNumColors/2),y,h);
			l=r+(nNumColors/2)-1;
			for(x=0;x<w;x++)
			{
				*(pGradBits+(y*w)+x)=PalVal[l+MulDiv((r-l),x,w)];
			}
		}
	}

	HBITMAP hBmp = CreateDIBitmap(hDC,&GradBitInfo.bmiHeader,CBM_INIT,
						pGradBits,&GradBitInfo,DIB_RGB_COLORS);

	free(pGradBits);

	return hBmp;
}

LRESULT CMenuXP::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	UINT iCurrentItem = (UINT)-1;
	CUIntArray arItemsMatched;

	UINT nItem = pMenu->GetMenuItemCount();
	for (UINT i=0; i< nItem; i++) 
	{
		MENUITEMINFO	info;
		memset(&info, 0, sizeof(info));
		info.cbSize = sizeof(info);
		info.fMask = MIIM_DATA | MIIM_TYPE | MIIM_STATE;
		::GetMenuItemInfo(*pMenu, i, TRUE, &info);

		CMenuXPItem	*pData = (CMenuXPItem *)info.dwItemData;
		if ((info.fType & MFT_OWNERDRAW) && pData && pData->IsMyData())
		{
			CString	text = pData->m_strText;
			int iAmpersand = text.Find('&');
			if (iAmpersand >=0 && toupper(nChar)==toupper(text[iAmpersand+1]))
				arItemsMatched.Add(i);
		}
		if (info.fState & MFS_HILITE)
			iCurrentItem = i;
	}
	
	UINT nFound = arItemsMatched.GetSize();
	if (nFound == 0)
		return 0;

	else if (nFound==1)
		return MAKELONG(arItemsMatched[0], MNC_EXECUTE);

	UINT iSelect = 0;
	for (UINT i=0; i < nFound; i++)
	{
		if (arItemsMatched[i] > iCurrentItem)
		{
			iSelect = i;
			break;
		}
	}
	return MAKELONG(arItemsMatched[iSelect], MNC_SELECT);
}

void CMenuXP::DrawMenuText(CDC& dc, CRect rc, CString text,
	COLORREF color)
{
	CString left = text;
	CString right;
	int iTabPos = left.Find('\t');
	if (iTabPos >= 0)
	{
		right = left.Right(left.GetLength() - iTabPos - 1);
		left  = left.Left(iTabPos);
	}
	dc.SetTextColor(color);
	dc.DrawText(left, &rc, DT_MYSTANDARD);
	if (iTabPos > 0)
		dc.DrawText(right, &rc, DT_MYSTANDARD|DT_RIGHT);
}

CMenuXP *CMenuXP::FindSubMenuFromID(DWORD dwID)
{
	CMenuXP	*pSubMenu;
	CMenuXP	*pResult;
	for (int i=0; i<GetMenuItemCount(); i++)
	{
		if (GetMenuItemID(i) == dwID)
				return this;
	}

	for (int i=0; i<GetMenuItemCount(); i++)
	{
		pSubMenu = (CMenuXP *)GetSubMenu(i);
		if (pSubMenu)
		{
			pResult = pSubMenu->FindSubMenuFromID(dwID);
			if (pResult)
				return pResult;
		}
	}

	return NULL;
}

BOOL CMenuXP::AddSideBar(CMenuXPSideBar *pItem)
{
	ASSERT(pItem);

	m_bBreak = TRUE;
	m_bBreakBar = FALSE;

	return AppendMenu(MF_OWNERDRAW, pItem->m_dwID, (LPCTSTR)pItem);
}

BOOL CMenuXP::AppendODMenu(UINT nFlags, CMenuXPItem *pItem, ACCEL *pAccel)
{
	ASSERT(pItem);

	nFlags |= MF_OWNERDRAW;
	if (m_bBreak) 
		nFlags |= MF_MENUBREAK;
	if (m_bBreakBar)
		nFlags |= MF_MENUBARBREAK;
	m_bBreak = m_bBreakBar = FALSE;

	if (pAccel)
	{
		CBCGKeyHelper	keyhelper(pAccel);
		CString	strAccel;
		keyhelper.Format(strAccel);
		if (strAccel.GetLength()>0)
		{
			pItem->m_strText += _T("\t");
			pItem->m_strText += strAccel;
		}
	}
	return AppendMenu(nFlags, pItem->m_dwID, (LPCTSTR)pItem);
}

BOOL CMenuXP::AppendSeparator(void)	
{
	m_bBreak = m_bBreakBar = FALSE;
	CMenuXPSeparator *pItem = new CMenuXPSeparator;
	return AppendMenu(MF_OWNERDRAW | MF_SEPARATOR, 0, (LPCTSTR)pItem);
}

BOOL CMenuXP::AppendODPopup(UINT nFlags, CMenuXP *pPopup, CMenuXPItem *pItem)
{
	ASSERT(pPopup);
	ASSERT(pItem);

	nFlags |= MF_OWNERDRAW;
	nFlags |= MF_POPUP;
	if (m_bBreak) 
		nFlags |= MF_MENUBREAK;
	if (m_bBreakBar)
		nFlags |= MF_MENUBARBREAK;
	m_bBreak = m_bBreakBar = FALSE;

	return AppendMenu(nFlags, (UINT)pPopup->m_hMenu, (LPCTSTR)pItem);
}

void CMenuXP::Break(void)
{
	m_bBreak = TRUE;
}

void CMenuXP::BreakBar(void)	
{
	m_bBreakBar = TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CToolBarCtrlEx

IMPLEMENT_DYNCREATE(CToolBarCtrlEx, CToolBarCtrl)

CToolBarCtrlEx*	    CToolBarCtrlEx::m_pToolBarCtrlEx = NULL;
HHOOK               CToolBarCtrlEx::m_hCBTHook = NULL;

CToolBarCtrlEx::CToolBarCtrlEx()
{
	m_pMenu = NULL;
	m_bTrack = FALSE;
	m_nItemCount = 0;
	m_nPressed = 0;
	m_ptMouse.x = 0;
	m_ptMouse.y = 0;

	m_clrBack = RGB(158,158,158);
	m_clrHot = RGB(238, 238, 238);
	m_clrChecked = m_clrHot;
	m_clrSelected = RGB(218, 218, 218);
	m_clrLine = RGB(0,128,0);
	m_clrText = RGB(255,0,0);
}

CToolBarCtrlEx::~CToolBarCtrlEx()
{
	if (m_pMenu) delete m_pMenu;
	m_pMenu = NULL;
}

BEGIN_MESSAGE_MAP(CToolBarCtrlEx, CToolBarCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	ON_WM_INITMENUPOPUP()
	ON_WM_EXITMENULOOP()
	ON_WM_ENTERMENULOOP()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_MESSAGE(MB_POPUPMENU, OnPopupMenu)
END_MESSAGE_MAP()

BOOL CToolBarCtrlEx::LoadToolBar(UINT nID)
{
	if(!m_hWnd)return FALSE;

	HRSRC hRsrc = ::FindResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(nID), RT_TOOLBAR);
	if (hRsrc == NULL)
		return FALSE;

	HGLOBAL hGlobal = LoadResource(AfxGetInstanceHandle(), hRsrc);
	if (hGlobal == NULL)
		return FALSE;

	TBDATAINFO* pData = (TBDATAINFO*)LockResource(hGlobal);
	if (pData == NULL)
		return FALSE;

	BOOL bResult;
	TBBUTTON tbb;
	memset(&tbb,0,sizeof(TBBUTTON));
	tbb.iString = -1;
	int iImage = 0;

	for (int i = 0; i < pData->wItemCount; i++)
	{
		tbb.fsState = TBSTATE_ENABLED;
		tbb.idCommand = pData->items()[i];
		if(tbb.idCommand == 0)
		{
			tbb.fsStyle = TBSTYLE_SEP;
			tbb.iBitmap = -1;
		}
		else
		{
			tbb.fsStyle = TBSTYLE_BUTTON;
			tbb.iBitmap = iImage++;
		}

		bResult = AddButtons(1,&tbb);

		if(!bResult)return FALSE;
	}

	if(bResult)
	{
		TBADDBITMAP tbab;

		tbab.hInst = AfxGetInstanceHandle();
		tbab.nID = nID;
		SendMessage(TB_ADDBITMAP,(WPARAM)pData->wItemCount,(LPARAM)&tbab);
	}

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return bResult;
}

void CToolBarCtrlEx::OnCustomDraw( NMHDR *pNotifyStruct, LRESULT *pResult )
{
	NMTBCUSTOMDRAW *pnmcd = (NMTBCUSTOMDRAW *)pNotifyStruct;

	CDC	dc;
	dc.Attach(pnmcd->nmcd.hdc);
	dc.FillSolidRect(&pnmcd->nmcd.rc,m_clrBack);

	switch (pnmcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		PreDrawItem(&dc, pnmcd->nmcd.rc, pnmcd->nmcd.uItemState);
		*pResult = TBCDRF_NOEDGES;
		break;
	case CDDS_ITEMPOSTPAINT:
		break;
	}

	dc.Detach();
}

void CToolBarCtrlEx::PreDrawItem(CDC *pDC, const RECT &rect, UINT uState)
{
	if (uState & CDIS_HOT)
	{
		CBrush brush(m_clrHot);
		CBrush	*pOldBr = pDC->SelectObject(&brush);
		pDC->DrawEdge(CRect(rect),BDR_RAISEDINNER|BDR_RAISEDOUTER,BF_BOTTOMLEFT|BF_TOPRIGHT);    //��������Ч��
		pDC->SelectObject(pOldBr);
	}
	else if (uState & CDIS_CHECKED)
	{
		CPen	pen(PS_SOLID, 1, m_clrLine); 
		CPen	*pOldPen = pDC->SelectObject(&pen);
		CBrush	brush(m_clrChecked);
		CBrush	*pOldBr = pDC->SelectObject(&brush);
		pDC->Rectangle(&rect);
		pDC->SelectObject(pOldBr);
		pDC->SelectObject(pOldPen);
	}
	else if (uState & CDIS_SELECTED)
	{
		CPen	pen(PS_SOLID, 1, m_clrLine);
		CPen	*pOldPen = pDC->SelectObject(&pen);
		CBrush	brush(m_clrSelected);
		CBrush	*pOldBr = pDC->SelectObject(&brush);
		pDC->Rectangle(&rect);
		pDC->SelectObject(pOldBr);
		pDC->SelectObject(pOldPen);
	}
}

CSize CToolBarCtrlEx::GetBarSize()
{
	CSize size;

	GetMaxSize(&size);
	return size;
}

BOOL CToolBarCtrlEx::ShowMText(HINSTANCE hInst, UINT nID)
{
	// determine location of the bitmap in resource fork
	HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(nID), RT_TOOLBAR);
	if (hRsrc == NULL)
		return FALSE;

	HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
	if (hGlobal == NULL)
		return FALSE;

	TBDATAINFO* pData = (TBDATAINFO*)LockResource(hGlobal);
	if (pData == NULL)
		return FALSE;
	ASSERT(pData->wVersion == 1);

	// �õ�������ť��ͼ���С
	CSize sizeImage(pData->wWidth, pData->wHeight);

	// release the resource
	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	// �õ� ToolBarCtrl��DC
	CDC *pdcCtrl = /*this->*/GetDC();
	CDC dcDst;		// Ŀ��DC , ����������λͼ
	dcDst.CreateCompatibleDC(pdcCtrl);

	// �½�����
	LOGFONT logFont;
	ZeroMemory(&logFont,sizeof(logFont));
	logFont.lfWidth = 6;
	logFont.lfHeight = 12;
	logFont.lfCharSet = GB2312_CHARSET;
	wcscpy(logFont.lfFaceName, L"����" );
	CFont fntNew;
	fntNew.CreateFontIndirect(&logFont);
	CFont *pfntOld = dcDst.SelectObject(&fntNew);

	// �µ�����ť��ͼƬ��С
	CSize sizeNewImage(sizeImage.cx, 0);

	// �����ַ�������
	const int nCount = GetButtonCount();
	CStringArray *pstrArray = new CStringArray[nCount];
	int nLines = 0;			// ��������
	int	nIndex = 0;		
	int nCharHeight = 0;	// �����ַ��߶�	
	TBBUTTON	tb;
	int nBtnCount = 0;		// ��ť��������ȥ�ָ�����
	for (int i = 0; i < nCount; ++ i)
	{
		ZeroMemory(&tb, sizeof(TBBUTTON));
		GetButton(i, &tb);

		// ����Ƿָ���
		if ((tb.fsStyle & TBSTYLE_SEP) ==  TBSTYLE_SEP)
		{	 
			continue;
		}

		CString strT;
		strT.LoadString(tb.idCommand);
		int nPos = strT.Find(_T('\n')) + 1;
		while(nPos > 0)
		{
			int nPos2 = strT.Find(_T('\n'), nPos);
			int nIndex;
			if(nPos2>nPos)
			{
				nIndex = pstrArray[nBtnCount].Add( strT.Mid(nPos, nPos2-nPos) );
				nPos = nPos2 + 1;
			}
			else if(strT.GetLength() > nPos)
			{
				nIndex = pstrArray[nBtnCount].Add( strT.Mid(nPos) );
				nPos = -1;
			}
			nLines = max(nLines, nIndex+1);
			CSize size = dcDst.GetTextExtent(pstrArray[nBtnCount][nIndex]);
			nCharHeight = max(size.cy, nCharHeight);
			sizeNewImage.cx = max(size.cx, sizeNewImage.cx);
		}
		nBtnCount ++;
	}
	// �����ʵ������
	sizeNewImage.cy = nLines*nCharHeight;


	// ��ȡ������λͼ��Դ
	CBitmap		bmpToolBar;
	BITMAP		bmBitmap;
	if (!bmpToolBar.Attach(LoadImage(hInst,
		MAKEINTRESOURCE(nID),
		IMAGE_BITMAP, 0, 0,
		LR_DEFAULTSIZE|LR_CREATEDIBSECTION
		|LR_LOADMAP3DCOLORS )) ||
		!bmpToolBar.GetBitmap(&bmBitmap))
		return FALSE;


	// ȡ��λͼ�ܿ��
	int nWidth = bmBitmap.bmWidth;
	int nHeight = bmBitmap.bmHeight;

	// ��λͼ���ܿ��
	int nWidthNew = sizeNewImage.cx * nBtnCount;
	sizeNewImage.cy += nHeight;
	int nHeightNew = sizeNewImage.cy;

	CDC dcSrc;	// ԴDC
	dcSrc.CreateCompatibleDC(pdcCtrl);
	CBitmap *pbmpOldSrc = dcSrc.SelectObject(&bmpToolBar);

	CBitmap bmpDst;	// ��λͼ
	bmpDst.CreateCompatibleBitmap(&dcSrc, nWidthNew, nHeightNew);
	CBitmap *pbmpOldDst = dcDst.SelectObject(&bmpDst);

	// ����䱳��ɫ
	dcDst.FillSolidRect(CRect(0, 0, nWidthNew, nHeightNew), ::GetSysColor(COLOR_BTNFACE));
	dcDst.SetBkMode(TRANSPARENT);	// ����͸��������ʽ

	int nStartX = (sizeNewImage.cx-sizeImage.cx)/2;	// ���㿪ʼ�����꣬���ھ��д���
	// ��ʼ����������λͼ
	for(int i = 0; i < nBtnCount; ++ i)
	{
		dcDst.BitBlt(i*sizeNewImage.cx+nStartX, 0, sizeImage.cx, sizeImage.cy, 
			&dcSrc, i*sizeImage.cx, 0, SRCCOPY);
		int j;
		for(j = 0; j < pstrArray[i].GetSize(); j ++)
		{
			CSize size = dcDst.GetTextExtent(pstrArray[i][j]);
			int nStratX = (sizeNewImage.cx-size.cx)/2;
			dcDst.TextOut(i*sizeNewImage.cx+nStratX, sizeImage.cy+j*nCharHeight, pstrArray[i][j]);
		}

		TBREPLACEBITMAP placeBmp;
		placeBmp.hInstOld = hInst;
		placeBmp.nIDOld = nID;
		placeBmp.hInstNew = hInst;
		placeBmp.nIDNew = nID;
		placeBmp.nButtons = i;
		ReplaceBitmap(&placeBmp);
	}

	// �ָ�DC���ͷ���Դ
	dcSrc.SelectObject(pbmpOldSrc);
	dcDst.SelectObject(pbmpOldDst);
	dcDst.SelectObject(pfntOld);
	this->ReleaseDC(pdcCtrl);
	delete [] pstrArray;

	// �������ô�С
	SetButtonSize(sizeNewImage + CSize(7,7));
	SetButtonSize(sizeNewImage);

	return TRUE;
}

BOOL CToolBarCtrlEx::LoadMenu(CMenu *pMenu)
{
	if (!m_hWnd)
		return FALSE;

	if (!pMenu)
		return FALSE;

	if (m_pMenu)
		delete m_pMenu;

	m_pMenu = pMenu;

	TRACE("MainMenu Handle: 0x%x\n", m_pMenu->GetSafeHmenu());

	TBBUTTON		tbb; 
	int				i,nStr;
	BOOL			bRet = FALSE;
	char			szText[_MAX_PATH];

	memset(&tbb, 0, sizeof(TBBUTTON));

	tbb.fsState = TBSTATE_ENABLED;
	tbb.fsStyle = TBSTYLE_BUTTON|TBSTYLE_AUTOSIZE;

	m_nItemCount = m_pMenu->GetMenuItemCount();
	SetBitmapSize(CSize(0, 0));

	m_ilIcons.Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 1);

	for(i=0; i<m_nItemCount; i++)
	{
		memset(szText, 0, _MAX_PATH);

		MENUITEMINFO	info;
		memset(&info, 0, sizeof(MENUITEMINFO));
		info.cbSize = sizeof(MENUITEMINFO);
		info.fMask = MIIM_DATA | MIIM_TYPE;
		m_pMenu->GetMenuItemInfo(i, &info, TRUE);
		
		CMenuXPItem *pData = (CMenuXPItem *)info.dwItemData;
		if (pData && (info.fType & MFT_OWNERDRAW))
		{
			USES_CONVERSION;
			strcpy_s(szText, T2A(pData->m_strText));
			if (pData->m_hIcon)
			{
				tbb.iBitmap = m_ilIcons.Add(pData->m_hIcon);
			}
			else
				tbb.iBitmap = -1;
		}
		else
		{
			USES_CONVERSION;
			m_pMenu->GetMenuString(i, A2T(szText), 80, MF_BYPOSITION);
		}

		USES_CONVERSION;
		nStr = AddStrings(A2T(szText));

		tbb.dwData = NULL;
		tbb.iString = nStr;
		tbb.idCommand = i; 

		bRet = AddButtons(1, &tbb);

		COLORSCHEME cs;
		cs.dwSize = sizeof(COLORSCHEME);
		cs.clrBtnHighlight = RGB(239, 237, 222);
		cs.clrBtnShadow = RGB(193, 210, 238);
		SetColorScheme(&cs);

		if(!bRet)
			return FALSE;
	}

	if (m_ilIcons.GetImageCount()>0)
		SetImageList(&m_ilIcons);

	return bRet;
}

BOOL CToolBarCtrlEx::LoadMenu(UINT id)
{
	if (!m_hWnd)
		return FALSE;

	CMenuXP* pMenu = new CMenuXP();
	pMenu->LoadMenu(id);
	if (!pMenu)
		return FALSE;

	if (m_pMenu)
		delete m_pMenu;

	m_pMenu = pMenu;

	TRACE("MainMenu Handle: 0x%x\n", m_pMenu->GetSafeHmenu());

	TBBUTTON		tbb; 
	int				i,nStr;
	BOOL			bRet = FALSE;
	char			szText[_MAX_PATH];

	memset(&tbb, 0, sizeof(TBBUTTON));

	tbb.fsState = TBSTATE_ENABLED;
	tbb.fsStyle = TBSTYLE_BUTTON|TBSTYLE_AUTOSIZE;

	m_nItemCount = m_pMenu->GetMenuItemCount();
	SetBitmapSize(CSize(0, 0));

	m_ilIcons.Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 1);

	for(i=0; i<m_nItemCount; i++)
	{
		memset(szText, 0, _MAX_PATH);

		MENUITEMINFO	info;
		memset(&info, 0, sizeof(MENUITEMINFO));
		info.cbSize = sizeof(MENUITEMINFO);
		info.fMask = MIIM_DATA | MIIM_TYPE;
		m_pMenu->GetMenuItemInfo(i, &info, TRUE);

		CMenuXPItem *pData = (CMenuXPItem *)info.dwItemData;
		if (pData && (info.fType & MFT_OWNERDRAW))
		{
			USES_CONVERSION;
			strcpy_s(szText, T2A(pData->m_strText));
			if (pData->m_hIcon)
			{
				tbb.iBitmap = m_ilIcons.Add(pData->m_hIcon);
			}
			else
				tbb.iBitmap = -1;
		}
		else
		{
			USES_CONVERSION;
			m_pMenu->GetMenuString(i, A2T(szText), 80, MF_BYPOSITION);
		}

		USES_CONVERSION;
		nStr = AddStrings(A2T(szText));

		tbb.dwData = (DWORD)szText;
		tbb.iString = nStr;
		tbb.idCommand = i;

		bRet = AddButtons(1, &tbb);

		COLORSCHEME cs;
		cs.dwSize = sizeof(COLORSCHEME);
		cs.clrBtnHighlight = RGB(239, 237, 222);
		cs.clrBtnShadow = RGB(193, 210, 238);
		SetColorScheme(&cs);

		if(!bRet)
			return FALSE;
	}

	if (m_ilIcons.GetImageCount()>0)
		SetImageList(&m_ilIcons);

	return bRet;
}

LRESULT CToolBarCtrlEx::CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MSG* pMsg = (MSG*)lParam;

	if(!m_pToolBarCtrlEx || nCode!=MSGF_MENU)
		return CallNextHookEx(m_hCBTHook,nCode,wParam,lParam);
	if(m_pToolBarCtrlEx->OnMenuInput(pMsg))
		return TRUE;
	else
		return CallNextHookEx(m_hCBTHook,nCode,wParam,lParam);
}

void CToolBarCtrlEx::TrackPopup()
{
	CMenu	*pSubMenu = m_pMenu->GetSubMenu(m_nPressed);
	if(pSubMenu == NULL)return;

	TRACE("Tracking Menu handle: 0x%x\n", pSubMenu->GetSafeHmenu());

	m_bTrack = TRUE;
	PressButton(m_nPressed,TRUE);

	CRect rc;
	GetItemRect(m_nPressed,&rc);
	ClientToScreen(&rc);

	CRect rcScreen;
	GetDesktopWindow()->GetWindowRect(rcScreen);
	rc.IntersectRect(rc, rcScreen);

	TPMPARAMS tpm;
	tpm.cbSize = sizeof(tpm);
	tpm.rcExclude = rc;

	m_pToolBarCtrlEx = this;
	m_hCBTHook = SetWindowsHookEx(WH_MSGFILTER,
			CBTProc, NULL, GetCurrentThreadId());

	TrackPopupMenuEx(pSubMenu->GetSafeHmenu(),
				TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON|TPM_VERTICAL,
				rc.left, rc.bottom, m_hWnd, &tpm);

	PressButton(m_nPressed,FALSE);
	UnhookWindowsHookEx(m_hCBTHook);
	m_hCBTHook = NULL;
	m_pToolBarCtrlEx = NULL;
}

BOOL CToolBarCtrlEx::OnMenuInput(MSG* pMsg)
{
	BOOL bResult = FALSE;
	switch(pMsg->message)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(pMsg->lParam);
			pt.y = HIWORD(pMsg->lParam);
			ScreenToClient(&pt);
			if(m_ptMouse.x == pt.x && m_ptMouse.y == pt.y)
				return TRUE;
		
			m_ptMouse.x = pt.x;
			m_ptMouse.y = pt.y;

			int nTest = HitTest(&pt);

			if(nTest>=0 && nTest<m_nItemCount && nTest != m_nPressed)
			{
				PressButton(m_nPressed,FALSE);
				SendMessage(WM_CANCELMODE,0,0);
				m_nPressed = nTest;
				PostMessage(MB_POPUPMENU,0,0);
				bResult = TRUE;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(pMsg->lParam);
			pt.y = HIWORD(pMsg->lParam);
			ScreenToClient(&pt);

			int nTest = HitTest(&pt);

			if(nTest<0)
				m_bTrack = FALSE;
			else if(nTest == m_nPressed)
			{
				m_bTrack = FALSE;
				PostMessage(WM_CANCELMODE,0,0);
				bResult = TRUE;
			}
		}
		break;
	case WM_KEYDOWN:
		{
			TCHAR vkey = pMsg->wParam;
			if(vkey == VK_LEFT)
			{
				PressButton(m_nPressed,FALSE);
				m_nPressed --;
				PostMessage(WM_CANCELMODE,0,0);
				PostMessage(MB_POPUPMENU,0,0);
				bResult = TRUE;
			}
			else if(vkey == VK_RIGHT)
			{
				PressButton(m_nPressed,FALSE);
				m_nPressed ++;
				PostMessage(WM_CANCELMODE,0,0);
				PostMessage(MB_POPUPMENU,0,0);
				bResult = TRUE;
			}
			else if (vkey == VK_ESCAPE)
			{
				PostMessage(WM_CANCELMODE,0,0);
				m_bTrack = FALSE;
				bResult = TRUE;
			}
		}
		break;
	case WM_MENUSELECT:
		GetOwner()->SendMessage(WM_MENUSELECT, pMsg->wParam, pMsg->lParam);
		bResult = TRUE;
		break;
	default:
		break;
	}

	return bResult;
}

void CToolBarCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int	nTest = HitTest(&point);
	if(nTest<0 || nTest>=m_nItemCount)
		return;
	m_nPressed = nTest;
	TrackPopup();	
}

LRESULT CToolBarCtrlEx::OnPopupMenu(WPARAM wParam, LPARAM lParam)
{
	if(m_nPressed<0)
		m_nPressed = m_nItemCount - 1;
	if(m_nPressed>=m_nItemCount)
		m_nPressed = 0;
	TrackPopup();

	return 0;
}

void CToolBarCtrlEx::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	if (nIDCtl == 0 && m_pMenu)
	{
		m_pMenu->MeasureItem(lpMeasureItemStruct);
	}	
}

void CToolBarCtrlEx::OnExitMenuLoop(BOOL bIsTrackPopupMenu)
{
	GetOwner()->SendMessage(WM_EXITMENULOOP, (WPARAM)bIsTrackPopupMenu);
}

void CToolBarCtrlEx::OnEnterMenuLoop(BOOL bIsTrackPopupMenu)
{
	GetOwner()->SendMessage(WM_ENTERMENULOOP, (WPARAM)bIsTrackPopupMenu);
}

LRESULT CToolBarCtrlEx::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	return CMenuXP::OnMenuChar(nChar, nFlags, pMenu);
}

BOOL CToolBarCtrlEx::OpenMenu(UINT nChar)
{
	int		nCount = (int)m_pMenu->GetMenuItemCount();
	char	szText[80];

	for(int i=0; i<m_nItemCount; i++)
	{
		MENUITEMINFO	info;
		memset(&info, 0, sizeof(MENUITEMINFO));
		info.cbSize = sizeof(MENUITEMINFO);
		info.fMask = MIIM_DATA | MIIM_TYPE;
		m_pMenu->GetMenuItemInfo(i, &info, TRUE);
		
		CMenuXPItem *pData = (CMenuXPItem *)info.dwItemData;
		if (pData && (info.fType & MFT_OWNERDRAW))
		{
			USES_CONVERSION;
			strcpy_s(szText, T2A(pData->m_strText));
		}
		else
		{
			USES_CONVERSION;
			m_pMenu->GetMenuString(i, A2T(szText), 80, MF_BYPOSITION);
		}

		CString	text = szText;
		int iAmpersand = text.Find('&');
		if (iAmpersand >=0 && toupper(nChar)==toupper(text[iAmpersand+1]))
		{
			m_nPressed = i;
			PostMessage(MB_POPUPMENU,0,0);
			return TRUE;
		}
	}
	return FALSE;
}

void CToolBarCtrlEx::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CToolBarCtrl::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	GetOwner()->SendMessage(WM_INITMENUPOPUP, (WPARAM)pPopupMenu->GetSafeHmenu(), MAKELONG(nIndex, bSysMenu));
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleMenuBar

IMPLEMENT_DYNCREATE(ArxRleMenuBar, CAcUiDockControlBar)
static CLSID clsArxRleMenuBar ={ 0x6fc57eb6, 0xa881, 0x4ebf, { 0x93, 0xa3, 0x0e, 0xcd, 0xbe, 0x1c, 0x0d, 0xfa } } ;

ArxRleMenuBar::ArxRleMenuBar(UINT id) : CAcUiDockControlBar ()
{
	m_cxDockBar=0;
	m_cyDockBar=0;
	m_cxToolBar=0;
	m_cyToolBar=0;
	m_cBorder=0;
	m_bDrawMenuSidear = FALSE;
	m_cxBarBtn = 2;

	LoadMenuXP(id);
}

ArxRleMenuBar::ArxRleMenuBar(CMenuXP* pMenuXP) : CAcUiDockControlBar ()
{
	m_cxDockBar=0;
	m_cyDockBar=0;
	m_cxToolBar=0;
	m_cyToolBar=0;
	m_cBorder=0;
	m_cxBarBtn = 2;

	LoadMenuXP(pMenuXP);
}

BEGIN_MESSAGE_MAP(ArxRleMenuBar, CAcUiDockControlBar)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL ArxRleMenuBar::Create(CWnd* pParent, LPCSTR lpszTitle)
{
	CString strWndClass ;
	strWndClass =AfxRegisterWndClass (CS_DBLCLKS, LoadCursor (NULL, IDC_ARROW)) ;

	CRect rect (0, 0, 0, 0) ;
	if ( !CAcUiDockControlBar::Create (
		strWndClass,
		(LPCTSTR)lpszTitle,
		WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN,
		rect,
		pParent, 0)
		)
		return (FALSE) ;

	SetToolID (&clsArxRleMenuBar) ;
	//----- TODO: Add your code here
	return (TRUE);
}

int ArxRleMenuBar::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
	if ( CAcUiDockControlBar::OnCreate (lpCreateStruct) == -1 )
		return -1;

	CRect rect;
	GetClientRect(rect);
	if(!m_wndToolBar.Create(WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | TBSTYLE_TRANSPARENT | TBSTYLE_LIST | TBSTYLE_TOOLTIPS | CCS_NODIVIDER | CCS_NORESIZE, rect, this, 10))
		return -1;

	if(m_pMenuXP->GetMenuItemCount() > 0)
		m_wndToolBar.LoadMenu(m_pMenuXP);

	CSize size;
	size = m_wndToolBar.GetBarSize();
	m_cxToolBar=size.cx;
	m_cyToolBar=size.cy;

	long cyTitle=GetSystemMetrics(SM_CYSMCAPTION);
	long cxBorder=GetSystemMetrics(SM_CXBORDER);
	long cyBorder=GetSystemMetrics(SM_CYBORDER);

	m_cxDockBar=m_cxToolBar+2*cxBorder+m_cxBarBtn;
	m_cyDockBar=m_cyToolBar+2*cyBorder+cyTitle;

	SetWindowPos(NULL,rect.left,rect.top,m_cxDockBar,m_cyDockBar,SWP_SHOWWINDOW);
	return 0;
}

void ArxRleMenuBar::OnPaint() 
{
	CPaintDC dc(this);
	//PaintControlBar(&dc);
}

void ArxRleMenuBar::SetCloseBtnPosition()
{
	CWnd *pBtn;
	CRect rect;

	if(IsFloating())
		return;

	pBtn=GetDlgItem(idCloseBtn);
	if(pBtn==NULL)
		return;

	GetClientRect(&rect);
	rect.DeflateRect(m_cBorder,m_cBorder);
	rect.left=rect.right-btnWidth;
	if(m_dwStyle & CBRS_ORIENT_HORZ)//ˮƽͣ��,��ť�������½�
		rect.top=rect.bottom-btnHeight;
	else//��ֱͣ��,��ť�������Ͻ�
		rect.bottom=rect.top+btnHeight;
	pBtn->MoveWindow(&rect);
	pBtn->ShowWindow(SW_HIDE);  // ��ʾ�����عرհ�Ť
}

CRect ArxRleMenuBar::GetInsideRect()
{
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(m_cBorder,m_cBorder);

	if(IsFloating())
		return rect;

	if(m_dwStyle & CBRS_ORIENT_HORZ)//ˮƽͣ��
		rect.DeflateRect(0, 0, m_cBorder+btnWidth, 0);
	else//��ֱͣ��
		rect.DeflateRect(0, m_cBorder+btnHeight, 0, 0);
	return rect;
}

BOOL ArxRleMenuBar::LoadMenuXP(UINT id)
{
	m_pMenuXP = new CMenuXP();
	m_pMenuXP->CreatePopupMenu();

	if(id > 0)
	{
		CMenu* pMenu = new CMenu();
		pMenu->LoadMenu(id);
		int nItemCount = pMenu->GetMenuItemCount();
		for(int i=0; i<nItemCount; i++)
		{
			m_bDrawMenuSidear = true;
			MenuItemLoop(m_pMenuXP, pMenu, i);
		}
	}

	if(m_pMenuXP->GetMenuItemCount() > 0)
		return TRUE;
	else
		return FALSE;
}

BOOL ArxRleMenuBar::LoadMenuXP(CMenuXP* pMenuXP)
{
	m_pMenuXP = new CMenuXP();
	m_pMenuXP->CreatePopupMenu();

	if(pMenuXP != NULL)
	{
		if(pMenuXP->GetMenuItemCount() > 0)
		{
			m_pMenuXP = pMenuXP;
			return TRUE;
		}
	}

	return FALSE;
}

void ArxRleMenuBar::MenuItemLoop(CMenuXP* pMenuXP, CMenu* pMenu, int nPos)
{
	CMenuXP* pSubMenuXP = new CMenuXP;
	pSubMenuXP->CreatePopupMenu();

	CString strItem;
	pMenu->GetMenuString(nPos,strItem, MF_BYPOSITION);
	if(m_bDrawMenuSidear)
	{
		pSubMenuXP->SetSideBarEndColor(RGB(0, 100, 0));       //������Ľ�����ɫ(�ڲ˵��ϱ�)
		pSubMenuXP->SetSideBarStartColor(RGB(0, 0, 180-10*nPos));  //������Ŀ�ʼ��ɫ
		pSubMenuXP->SetSelectedTextColor(RGB(0, 0, 0));     //�˵�ѡ��ʱ�ı���ɫ
		pSubMenuXP->AddSideBar(new CMenuXPSideBar(20, strItem));
		m_bDrawMenuSidear = false;
	}

	CMenu* pSubMenu = pMenu->GetSubMenu(nPos);
	if(pSubMenu != NULL)
	{
		int nSubItemCount = pSubMenu->GetMenuItemCount();
		for(int i=0; i<nSubItemCount; i++)
		{
			CString strSubItem;
			pSubMenu->GetMenuString(i,strSubItem, MF_BYPOSITION);
			if(pSubMenu->GetSubMenu(i) != NULL)
			{
				MenuItemLoop(pSubMenuXP, pSubMenu, i);
			}
			else
			{
				if(strSubItem.GetLength() == 0)
					pSubMenuXP->AppendODMenu(0, new CMenuXPSeparator());
				else
					pSubMenuXP->AppendODMenu(0, new CMenuXPText(pSubMenu->GetMenuItemID(i), strSubItem));
			}
		}

		pMenuXP->AppendODPopup(0, pSubMenuXP, new CMenuXPText(1, strItem));
	}
}

//���ͣ��ʱ��"����"�Ҽ��˵���
BOOL ArxRleMenuBar::AddCustomMenuItems(LPARAM hMenu)
{
	HMENU hPopMenu;	
	hPopMenu=(HMENU)LOWORD(hMenu);
	CMenu* pMenu= CMenu::FromHandle(hPopMenu);
	pMenu->EnableMenuItem(ID_ADUI_HIDEBAR,MF_GRAYED|MF_BYCOMMAND);
	return TRUE;
}

void ArxRleMenuBar::PaintControlBar(CDC * pDC)
{
	CRect rect;
	GetClientRect(&rect);

	//����ʱ�����ư���(������һ�θ�һ��Ҳ�������Ի���)
	if(IsFloating())
	{
		//������״̬ʱ������ʾ������
		CMDIFrameWnd *pFrm=(CMDIFrameWnd *)GetDockingFrame();
		BOOL bCanHide=pFrm->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd));
		LONG style=::GetWindowLong(pFrm->m_hWnd,GWL_STYLE);
		if(bCanHide) ::SetWindowLong(pFrm->m_hWnd, GWL_STYLE,IsFloating() ? (style & ~WS_CAPTION) : (style | WS_CAPTION));
	}
	else
	{
		//��߽���������һ���߿��
		rect.DeflateRect(m_cBorder,m_cBorder);
		if(m_dwStyle & CBRS_ORIENT_HORZ)//ˮƽͣ��,���ֻ����Ҳ�
		{
			//�������һ���3��3D��,���3,���1
			rect.DeflateRect(0, 0, 0, m_cBorder-btnHeight/2);
			//rect.left=rect.right-3;   //���������
			rect.right=rect.left+3;
			pDC->DrawEdge(rect, BDR_RAISEDINNER|BDR_RAISEDOUTER, BF_BOTTOMLEFT|BF_TOPRIGHT);
			rect.OffsetRect(4, 0);   //���������ʱ��4��Ϊ-4
			//pDC->DrawEdge(rect, BDR_RAISEDINNER|BDR_RAISEDOUTER, BF_BOTTOMLEFT|BF_TOPRIGHT);
		}
		else//��ֱͣ��,���ֻ��ڶ���
		{
			//�Ӷ����׻���3��3D��,���3,���1
			rect.DeflateRect(0, 0, m_cBorder+btnWidth, 0);
			rect.bottom=rect.top+3;
			pDC->DrawEdge(rect, BDR_RAISEDINNER, BF_RECT);
			rect.OffsetRect(0, 4);
			pDC->DrawEdge(rect, BDR_RAISEDINNER, BF_RECT);
		}
	}
}

//���տؼ�����С���ò˵���
void ArxRleMenuBar::SizeChanged (CRect *lpRect, BOOL bFloating, int flags)
{
	CRect rc;

	//�ض�λ�رհ�ť
	SetCloseBtnPosition();
	//��ȡ��ֱ��ʹ�õĿռ�
	rc=GetInsideRect();
	rc.left=m_cxBarBtn;   //�������һ����ʱ���˵������ơ�
	//�ض�λ��״�ؼ��ڿؼ����е�λ��
	m_wndToolBar.MoveWindow (&rc);

	//�ض�λ�رհ�ť
	SetCloseBtnPosition();
	lpRect->InflateRect(-m_cxBarBtn,-m_cxBarBtn);//�ͻ�������
	m_wndToolBar.SetWindowPos(NULL,lpRect->left-btnWidth,lpRect->top,m_cxToolBar,m_cyToolBar,SWP_SHOWWINDOW);
}

//��ֹ/����رղ˵���
bool ArxRleMenuBar::OnClosing()
{
	return false;
}

BOOL ArxRleMenuBar::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	ArxRleApp::OnCommands(LOWORD(wParam));

	return TRUE;//CAcUiDockControlBar::OnCommand(wParam, lParam);
}