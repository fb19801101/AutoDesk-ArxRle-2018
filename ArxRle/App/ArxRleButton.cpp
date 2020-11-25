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
//

#include "stdafx.h"
#include "ArxRleButton.h"

#ifdef	BTNST_USE_SOUND
#pragma comment(lib, "winmm.lib")
#include <Mmsystem.h>
#endif

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

/////////////////////////////////////////////////////////////////////////////
// ArxRleButton

// Mask for control's type
#define __BS_TYPEMASK SS_TYPEMASK

ArxRleButton::ArxRleButton()
{
	m_bIsPressed		= FALSE;
	m_bIsFocused		= FALSE;
	m_bIsDisabled		= FALSE;
	m_bMouseOnButton	= FALSE;

	FreeResources(FALSE);

	// Default type is "flat" button
	m_bIsFlat = TRUE;
	// Button will be tracked also if when the window is inactive(like Internet Explorer)
	m_bAlwaysTrack = TRUE;
  
	// By default draw border in "flat" button 
	m_bDrawBorder = TRUE; 
  
	// By default icon is aligned horizontally
	m_byAlign = ST_ALIGN_HORIZ; 

	// By default use usual pressed style
	SetPressedStyle(BTNST_PRESSED_LEFTRIGHT, FALSE);
  
	// By default, for "flat" button, don't draw the focus rect
	m_bDrawFlatFocus = FALSE;

	// By default the button is not the default button
	m_bIsDefault = FALSE;
	// Invalid value, since type still unknown
	m_nTypeStyle =BS_TYPEMASK;

	// By default the button is not a checkbox
	m_bIsCheckBox = FALSE;
	m_nCheck = 0;

	// Set default colors
	SetDefaultColors(FALSE);

	// No tooltip created
	m_ToolTip.m_hWnd = NULL;

	// Do not draw as a transparent button
	m_bDrawTransparent = FALSE;
	m_pbmpOldBk = NULL;

	// No URL defined
	SetURL(NULL);

	// No cursor defined
	m_hCursor = NULL;

	// No associated menu
#ifndef	BTNST_USE_BCMENU
	m_hMenu = NULL;
#endif
	m_hParentWndMenu = NULL;
	m_bMenuDisplayed = FALSE;

	m_bShowDisabledBitmap = TRUE;

	m_ptImageOrg.x = 3;
	m_ptImageOrg.y = 3;

	m_crBkColor = RGB(238,238,238);
	m_bSetBkColor = FALSE;
	m_iBitmapID = 0;
	m_bSetBkBitmap = FALSE;

	// No defined callbacks
	::ZeroMemory(&m_csCallbacks, sizeof(m_csCallbacks));

#ifdef	BTNST_USE_SOUND
	// No defined sounds
	::ZeroMemory(&m_csSounds, sizeof(m_csSounds));
#endif
} // End of ArxRleButton

ArxRleButton::~ArxRleButton()
{
	// Restore old bitmap(if any)
	if(m_dcBk.m_hDC && m_pbmpOldBk)
	{
		m_dcBk.SelectObject(m_pbmpOldBk);
	} // if

	FreeResources();

	// Destroy the cursor(if any)
	if(m_hCursor) ::DestroyCursor(m_hCursor);

	// Destroy the menu(if any)
#ifdef	BTNST_USE_BCMENU
	if(m_menuPopup.m_hMenu)	m_menuPopup.DestroyMenu();
#else
	if(m_hMenu)	::DestroyMenu(m_hMenu);
#endif
} // End of ~ArxRleButton

BEGIN_MESSAGE_MAP(ArxRleButton, CButton)
	ON_WM_SETCURSOR()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	ON_WM_SYSCOLORCHANGE()
	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
	ON_WM_ACTIVATE()
	ON_WM_ENABLE()
	ON_WM_CANCELMODE()
	ON_WM_GETDLGCODE()
	ON_WM_CTLCOLOR_REFLECT()

#ifdef	BTNST_USE_BCMENU
	ON_WM_MENUCHAR()
	ON_WM_MEASUREITEM()
#endif

	ON_MESSAGE(BM_SETSTYLE, OnSetStyle)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(BM_SETCHECK, OnSetCheck)
	ON_MESSAGE(BM_GETCHECK, OnGetCheck)
END_MESSAGE_MAP()

void ArxRleButton::FreeResources(BOOL bCheckForNULL)
{
	if(bCheckForNULL)
	{
		// Destroy icons
		// Note: the following two lines MUST be here! even if
		// BoundChecker says they are unnecessary!
		if(m_csIcons[0].hIcon)	::DestroyIcon(m_csIcons[0].hIcon);
		if(m_csIcons[1].hIcon)	::DestroyIcon(m_csIcons[1].hIcon);

		// Destroy bitmaps
		if(m_csBitmaps[0].hBitmap)	::DeleteObject(m_csBitmaps[0].hBitmap);
		if(m_csBitmaps[1].hBitmap)	::DeleteObject(m_csBitmaps[1].hBitmap);

		// Destroy mask bitmaps
		if(m_csBitmaps[0].hMask)	::DeleteObject(m_csBitmaps[0].hMask);
		if(m_csBitmaps[1].hMask)	::DeleteObject(m_csBitmaps[1].hMask);
	} // if

	::ZeroMemory(&m_csIcons, sizeof(m_csIcons));
	::ZeroMemory(&m_csBitmaps, sizeof(m_csBitmaps));
} // End of FreeResources

void ArxRleButton::PreSubclassWindow() 
{
	UINT nBS;

	nBS = GetButtonStyle();

	// Set initial control type
	m_nTypeStyle = nBS &BS_TYPEMASK;

	// Check if this is a checkbox
	if(nBS & BS_CHECKBOX) m_bIsCheckBox = TRUE;

	// Set initial default state flag
	if(m_nTypeStyle == BS_DEFPUSHBUTTON)
	{
		// Set default state for a default button
		m_bIsDefault = TRUE;

		// Adjust style for default button
		m_nTypeStyle = BS_PUSHBUTTON;
	} // If

	// You should not set the Owner Draw before this call
	//(don't use the resource editor "Owner Draw" or
	// ModifyStyle(0, BS_OWNERDRAW) before calling PreSubclassWindow() )
	ASSERT(m_nTypeStyle != BS_OWNERDRAW);

	// Switch to owner-draw
	ModifyStyle(BS_TYPEMASK, BS_OWNERDRAW, SWP_FRAMECHANGED);

	CButton::PreSubclassWindow();
} // End of PreSubclassWindow

UINT ArxRleButton::OnGetDlgCode() 
{
	UINT nCode = CButton::OnGetDlgCode();

	// Tell the system if we want default state handling
	//(losing default state always allowed)
	nCode |=(m_bIsDefault ? DLGC_DEFPUSHBUTTON : DLGC_UNDEFPUSHBUTTON);

	return nCode;
} // End of OnGetDlgCode

BOOL ArxRleButton::PreTranslateMessage(MSG* pMsg) 
{
	InitToolTip();
	m_ToolTip.RelayEvent(pMsg);
	
	if(pMsg->message == WM_LBUTTONDBLCLK)
		pMsg->message = WM_LBUTTONDOWN;

	return CButton::PreTranslateMessage(pMsg);
} // End of PreTranslateMessage

LRESULT ArxRleButton::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(message >= WM_MOUSEFIRST &&message <= WM_MOUSELAST ) //VM_MOUSEMOVE
	{
		MSG  msg;   
		msg.hwnd  =  m_hWnd;   
		msg.message  =  message;   
		msg.wParam  =  wParam;   
		msg.lParam  =  lParam; 

		m_ToolTip.RelayEvent(&msg);
	}

	return CButton::WindowProc(message, wParam, lParam);
}

HBRUSH ArxRleButton::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	return(HBRUSH)::GetStockObject(NULL_BRUSH); 
} // End of CtlColor

void ArxRleButton::OnSysColorChange() 
{
	CButton::OnSysColorChange();

	m_dcBk.DeleteDC();
	m_bmpBk.DeleteObject();	
	SetDefaultColors();
} // End of OnSysColorChange

LRESULT ArxRleButton::OnSetStyle(WPARAM wParam, LPARAM lParam)
{
	UINT nNewType =(wParam &BS_TYPEMASK);

	// Update default state flag
	if(nNewType == BS_DEFPUSHBUTTON)
	{
		m_bIsDefault = TRUE;
	} // if
	else if(nNewType == BS_PUSHBUTTON)
	{
		// Losing default state always allowed
		m_bIsDefault = FALSE;
	} // if

	// Can't change control type after owner-draw is set.
	// Let the system process changes to other style bits
	// and redrawing, while keeping owner-draw style
	return DefWindowProc(BM_SETSTYLE,
		(wParam & ~BS_TYPEMASK) | BS_OWNERDRAW, lParam);
} // End of OnSetStyle

LRESULT ArxRleButton::OnSetCheck(WPARAM wParam, LPARAM lParam)
{
	ASSERT(m_bIsCheckBox);

	switch(wParam)
	{
		case BST_CHECKED:
		case BST_INDETERMINATE:	// Indeterminate state is handled like checked state
			SetCheck(1);
			break;
		default:
			SetCheck(0);
			break;
	} // switch

	return 0;
} // End of OnSetCheck

LRESULT ArxRleButton::OnGetCheck(WPARAM wParam, LPARAM lParam)
{
	ASSERT(m_bIsCheckBox);
	return GetCheck();
} // End of OnGetCheck

#ifdef	BTNST_USE_BCMENU
LRESULT ArxRleButton::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	LRESULT lResult;
	if(ArxRleMenuXP::IsMenu(pMenu))
		lResult = ArxRleMenuXP::FindKeyboardShortcut(nChar, nFlags, pMenu);
	else
		lResult = CButton::OnMenuChar(nChar, nFlags, pMenu);
	return lResult;
} // End of OnMenuChar
#endif

#ifdef	BTNST_USE_BCMENU
void ArxRleButton::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	BOOL bSetFlag = FALSE;
	if(lpMeasureItemStruct->CtlType == ODT_MENU)
	{
		if(IsMenu((HMENU)lpMeasureItemStruct->itemID) && ArxRleMenuXP::IsMenu((HMENU)lpMeasureItemStruct->itemID))
		{
			m_menuPopup.MeasureItem(lpMeasureItemStruct);
			bSetFlag = TRUE;
		} // if
	} // if
	if(!bSetFlag) CButton::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
} // End of OnMeasureItem
#endif

void ArxRleButton::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
	
	if(bEnable == FALSE)	
	{
		CWnd*	pWnd = GetParent()->GetNextDlgTabItem(this);
		if(pWnd)
			pWnd->SetFocus();
		else
			GetParent()->SetFocus();

		CancelHover();
	} // if
} // End of OnEnable

void ArxRleButton::OnKillFocus(CWnd * pNewWnd)
{
	CButton::OnKillFocus(pNewWnd);
	CancelHover();
} // End of OnKillFocus

void ArxRleButton::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CButton::OnActivate(nState, pWndOther, bMinimized);
	if(nState == WA_INACTIVE)	CancelHover();
} // End of OnActivate

void ArxRleButton::OnCancelMode() 
{
	CButton::OnCancelMode();
	CancelHover();
} // End of OnCancelMode

BOOL ArxRleButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// If a cursor was specified then use it!
	if(m_hCursor != NULL)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	} // if

	return CButton::OnSetCursor(pWnd, nHitTest, message);
} // End of OnSetCursor

void ArxRleButton::CancelHover()
{
	// Only for flat buttons
	if(m_bIsFlat)
	{
		if(m_bMouseOnButton)
		{
			m_bMouseOnButton = FALSE;
			Invalidate();
		} // if
	} // if
} // End of CancelHover

void ArxRleButton::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd*				wndUnderMouse = NULL;
	CWnd*				wndActive = this;
	TRACKMOUSEEVENT		csTME;

	CButton::OnMouseMove(nFlags, point);

	ClientToScreen(&point);
	wndUnderMouse = WindowFromPoint(point);

	// If the mouse enter the button with the left button pressed then do nothing
	if(nFlags & MK_LBUTTON && m_bMouseOnButton == FALSE) return;

	// If our button is not flat then do nothing
	if(m_bIsFlat == FALSE) return;

	if(m_bAlwaysTrack == FALSE)	wndActive = GetActiveWindow();

	if(wndUnderMouse && wndUnderMouse->m_hWnd == m_hWnd && wndActive)
	{
		if(!m_bMouseOnButton)
		{
			m_bMouseOnButton = TRUE;

			Invalidate();

#ifdef	BTNST_USE_SOUND
			// Play sound ?
			if(m_csSounds[0].lpszSound)
				::PlaySound(m_csSounds[0].lpszSound, m_csSounds[0].hMod, m_csSounds[0].dwFlags);
#endif

			csTME.cbSize = sizeof(csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = m_hWnd;
			::_TrackMouseEvent(&csTME);
		} // if
	}
	else
	{
		CancelHover();
	}
} // End of OnMouseMove

// Handler for WM_MOUSELEAVE
LRESULT ArxRleButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	CancelHover();
	return 0;
} // End of OnMouseLeave

BOOL ArxRleButton::OnClicked() 
{	
	SetFocus();

#ifdef	BTNST_USE_SOUND
	// Play sound ?
	if(m_csSounds[1].lpszSound)
		::PlaySound(m_csSounds[1].lpszSound, m_csSounds[1].hMod, m_csSounds[1].dwFlags);
#endif

	if(m_bIsCheckBox)
	{
		m_nCheck = !m_nCheck;
		Invalidate();
	} // if
	else
	{
		// Handle the menu(if any)
#ifdef	BTNST_USE_BCMENU
		if(m_menuPopup.m_hMenu)
#else
		if(m_hMenu)
#endif
		{
			CRect	rWnd;
			GetWindowRect(rWnd);

			m_bMenuDisplayed = TRUE;
			Invalidate();

#ifdef	BTNST_USE_BCMENU
			ArxRleMenuXP* psub =(ArxRleMenuXP*)m_menuPopup.GetSubMenu(0);
			if(m_csCallbacks.hWnd)	::SendMessage(m_csCallbacks.hWnd, m_csCallbacks.nMessage,(WPARAM)psub, m_csCallbacks.lParam);
			DWORD dwRetValue = psub->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD, rWnd.left, rWnd.bottom, this, NULL);
#else
			HMENU hSubMenu = ::GetSubMenu(m_hMenu, 0);
			if(m_csCallbacks.hWnd)	::SendMessage(m_csCallbacks.hWnd, m_csCallbacks.nMessage,(WPARAM)hSubMenu, m_csCallbacks.lParam);
			DWORD dwRetValue = ::TrackPopupMenuEx(hSubMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD, rWnd.left, rWnd.bottom, m_hParentWndMenu, NULL);
#endif

			m_bMenuDisplayed = FALSE;
			Invalidate();

			if(dwRetValue)
				::PostMessage(m_hParentWndMenu, WM_COMMAND, MAKEWPARAM(dwRetValue, 0),(LPARAM)NULL);
		} // if
		else
		{
			// Handle the URL(if any)
			if(_tcslen(m_szURL) > 0)
			{
				SHELLEXECUTEINFO	csSEI;

				memset(&csSEI, 0, sizeof(csSEI));
				csSEI.cbSize = sizeof(SHELLEXECUTEINFO);
				csSEI.fMask = SEE_MASK_FLAG_NO_UI;
				csSEI.lpVerb = _T("open");
				csSEI.lpFile = m_szURL;
				csSEI.nShow = SW_SHOWMAXIMIZED;
				::ShellExecuteEx(&csSEI);
			} // if
		} // else
	} // else

	return FALSE;
} // End of OnClicked

void ArxRleButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);
	CPen*	pOldPen;

	// Checkbox?
	if(m_bIsCheckBox)
	{
		m_bIsPressed  =(lpDIS->itemState & ODS_SELECTED) ||(m_nCheck != 0);
	} // if
	else	// Normal button OR other button style ...
	{
		m_bIsPressed =(lpDIS->itemState & ODS_SELECTED);

		// If there is a menu and it's displayed, draw the button as pressed
		if(
#ifdef	BTNST_USE_BCMENU
			m_menuPopup.m_hMenu 
#else
			m_hMenu 
#endif
			&& m_bMenuDisplayed)	m_bIsPressed = TRUE;
	} // else

	m_bIsFocused  =(lpDIS->itemState & ODS_FOCUS);
	m_bIsDisabled =(lpDIS->itemState & ODS_DISABLED);

	CRect itemRect = lpDIS->rcItem;

	pDC->SetBkMode(TRANSPARENT);

	if(m_bIsFlat == FALSE)
	{
		if(m_bIsFocused || m_bIsDefault)
		{
			CBrush br(RGB(0,0,0));  
			pDC->FrameRect(&itemRect, &br);
			itemRect.DeflateRect(1, 1);
		} // if
	} // if

	// Prepare draw... paint button background

	// Draw transparent?
	if(m_bDrawTransparent)
		PaintBk(pDC);
	else
		OnDrawBackground(pDC, &itemRect);

	// Draw pressed button
	if(m_bIsPressed)
	{
		if(m_bIsFlat)
		{
			if(m_bDrawBorder)
				OnDrawBorder(pDC, &itemRect);
		}
		else    
		{
			CBrush brBtnShadow(GetSysColor(COLOR_BTNSHADOW));
			pDC->FrameRect(&itemRect, &brBtnShadow);
		}
	}
	else // ...else draw non pressed button
	{
		CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // White
		CPen pen3DLight(PS_SOLID, 0, GetSysColor(COLOR_3DLIGHT));       // Light gray
		CPen penBtnShadow(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Dark gray
		CPen pen3DDKShadow(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)); // Black

		if(m_bIsFlat)
		{
			if(m_bMouseOnButton && m_bDrawBorder)
				OnDrawBorder(pDC, &itemRect);
		}
		else
		{
			// Draw top-left borders
			// White line
			pOldPen = pDC->SelectObject(&penBtnHiLight);
			pDC->MoveTo(itemRect.left, itemRect.bottom-1);
			pDC->LineTo(itemRect.left, itemRect.top);
			pDC->LineTo(itemRect.right, itemRect.top);
			// Light gray line
			pDC->SelectObject(pen3DLight);
			pDC->MoveTo(itemRect.left+1, itemRect.bottom-1);
			pDC->LineTo(itemRect.left+1, itemRect.top+1);
			pDC->LineTo(itemRect.right, itemRect.top+1);
			// Draw bottom-right borders
			// Black line
			pDC->SelectObject(pen3DDKShadow);
			pDC->MoveTo(itemRect.left, itemRect.bottom-1);
			pDC->LineTo(itemRect.right-1, itemRect.bottom-1);
			pDC->LineTo(itemRect.right-1, itemRect.top-1);
			// Dark gray line
			pDC->SelectObject(penBtnShadow);
			pDC->MoveTo(itemRect.left+1, itemRect.bottom-2);
			pDC->LineTo(itemRect.right-2, itemRect.bottom-2);
			pDC->LineTo(itemRect.right-2, itemRect.top);
			//
			pDC->SelectObject(pOldPen);
		} // else
	} // else

	// Read the button's title
	CString sTitle;
	GetWindowText(sTitle);

	CRect captionRect = lpDIS->rcItem;

	// Draw the icon
	if(m_csIcons[0].hIcon)
	{
		DrawTheIcon(pDC, !sTitle.IsEmpty(), &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	} // if

	if(m_csBitmaps[0].hBitmap)
	{
		pDC->SetBkColor(RGB(255,255,255));
		DrawTheBitmap(pDC, !sTitle.IsEmpty(), &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	} // if

	// Write the button title(if any)
	if(sTitle.IsEmpty() == FALSE)
	{
		DrawTheText(pDC,(LPCTSTR)sTitle, &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	} // if

	if(m_bIsFlat == FALSE ||(m_bIsFlat && m_bDrawFlatFocus))
	{
		// Draw the focus rect
		if(m_bIsFocused)
		{
			CRect focusRect = itemRect;
			focusRect.DeflateRect(3, 3);
			pDC->DrawFocusRect(&focusRect);
		} // if
	} // if
} // End of DrawItem

void ArxRleButton::PaintBk(CDC* pDC)
{
	CClientDC clDC(GetParent());
	CRect rect;
	CRect rect1;

	GetClientRect(rect);

	GetWindowRect(rect1);
	GetParent()->ScreenToClient(rect1);

	if(m_dcBk.m_hDC == NULL)
	{
		m_dcBk.CreateCompatibleDC(&clDC);
		m_bmpBk.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
	} // if

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
} // End of PaintBk

HBITMAP ArxRleButton::CreateBitmapMask(HBITMAP hSourceBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTransColor)
{
	HBITMAP		hMask		= NULL;
	HDC			hdcSrc		= NULL;
	HDC			hdcDest		= NULL;
	HBITMAP		hbmSrcT		= NULL;
	HBITMAP		hbmDestT	= NULL;
	COLORREF	crSaveBk;
	COLORREF	crSaveDestText;

	hMask = ::CreateBitmap(dwWidth, dwHeight, 1, 1, NULL);
	if(hMask == NULL)	return NULL;

	hdcSrc	= ::CreateCompatibleDC(NULL);
	hdcDest	= ::CreateCompatibleDC(NULL);

	hbmSrcT =(HBITMAP)::SelectObject(hdcSrc, hSourceBitmap);
	hbmDestT =(HBITMAP)::SelectObject(hdcDest, hMask);

	crSaveBk = ::SetBkColor(hdcSrc, crTransColor);

	::BitBlt(hdcDest, 0, 0, dwWidth, dwHeight, hdcSrc, 0, 0, SRCCOPY);

	crSaveDestText = ::SetTextColor(hdcSrc, RGB(255, 255, 255));
	::SetBkColor(hdcSrc,RGB(0, 0, 0));

	::BitBlt(hdcSrc, 0, 0, dwWidth, dwHeight, hdcDest, 0, 0, SRCAND);

	SetTextColor(hdcDest, crSaveDestText);

	::SetBkColor(hdcSrc, crSaveBk);
	::SelectObject(hdcSrc, hbmSrcT);
	::SelectObject(hdcDest, hbmDestT);

	::DeleteDC(hdcSrc);
	::DeleteDC(hdcDest);

	return hMask;
} // End of CreateBitmapMask

//
// Parameters:
//		[IN]	bHasTitle
//				TRUE if the button has a text
//		[IN]	rpItem
//				A pointer to a RECT structure indicating the allowed paint area
//		[IN/OUT]rpTitle
//				A pointer to a CRect object indicating the paint area reserved for the
//				text. This structure will be modified if necessary.
//		[IN]	bIsPressed
//				TRUE if the button is currently pressed
//		[IN]	dwWidth
//				Width of the image(icon or bitmap)
//		[IN]	dwHeight
//				Height of the image(icon or bitmap)
//		[OUT]	rpImage
//				A pointer to a CRect object that will receive the area available to the image
//
void ArxRleButton::PrepareImageRect(BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, DWORD dwWidth, DWORD dwHeight, CRect* rpImage)
{
	CRect rBtn;

	rpImage->CopyRect(rpItem);

	switch(m_byAlign)
	{
		case ST_ALIGN_HORIZ:
			if(bHasTitle == FALSE)
			{
				// Center image horizontally
				rpImage->left +=((rpImage->Width() -(long)dwWidth)/2);
			}
			else
			{
				// Image must be placed just inside the focus rect
				rpImage->left += m_ptImageOrg.x;  
				rpTitle->left += dwWidth + m_ptImageOrg.x;
			}
			// Center image vertically
			rpImage->top +=((rpImage->Height() -(long)dwHeight)/2);
			break;

		case ST_ALIGN_HORIZ_RIGHT:
			GetClientRect(&rBtn);
			if(bHasTitle == FALSE)
			{
				// Center image horizontally
				rpImage->left +=((rpImage->Width() -(long)dwWidth)/2);
			}
			else
			{
				// Image must be placed just inside the focus rect
				rpTitle->right = rpTitle->Width() - dwWidth - m_ptImageOrg.x;
				rpTitle->left = m_ptImageOrg.x;
				rpImage->left = rBtn.right - dwWidth - m_ptImageOrg.x;
				// Center image vertically
				rpImage->top +=((rpImage->Height() -(long)dwHeight)/2);
			}
			break;
		
		case ST_ALIGN_VERT:
			// Center image horizontally
			rpImage->left +=((rpImage->Width() -(long)dwWidth)/2);
			if(bHasTitle == FALSE)
			{
				// Center image vertically
				rpImage->top +=((rpImage->Height() -(long)dwHeight)/2);           
			}
			else
			{
				rpImage->top = m_ptImageOrg.y;
				rpTitle->top += dwHeight;
			}
			break;

		case ST_ALIGN_OVERLAP:
			break;
	} // switch
    
	// If button is pressed then press image also
	if(bIsPressed && m_bIsCheckBox == FALSE)
		rpImage->OffsetRect(m_ptPressedOffset.x, m_ptPressedOffset.y);
} // End of PrepareImageRect

void ArxRleButton::DrawTheIcon(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled)
{
	BYTE		byIndex		= 0;

	// Select the icon to use
	if((m_bIsCheckBox && bIsPressed) ||(!m_bIsCheckBox &&(bIsPressed || m_bMouseOnButton)))
		byIndex = 0;
	else
		byIndex =(m_csIcons[1].hIcon == NULL ? 0 : 1);

	CRect	rImage;
	PrepareImageRect(bHasTitle, rpItem, rpCaption, bIsPressed, m_csIcons[byIndex].dwWidth, m_csIcons[byIndex].dwHeight, &rImage);

	// Ole'!
	pDC->DrawState(	rImage.TopLeft(),
					rImage.Size(), 
					m_csIcons[byIndex].hIcon,
					(bIsDisabled ? DSS_DISABLED : DSS_NORMAL), 
					(CBrush*)NULL);
} // End of DrawTheIcon

void ArxRleButton::DrawTheBitmap(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled)
{
	HDC			hdcBmpMem	= NULL;
	HBITMAP		hbmOldBmp	= NULL;
	HDC			hdcMem		= NULL;
	HBITMAP		hbmT		= NULL;

	BYTE		byIndex		= 0;

	// Select the bitmap to use
	if((m_bIsCheckBox && bIsPressed) ||(!m_bIsCheckBox &&(bIsPressed || m_bMouseOnButton)))
		byIndex = 0;
	else
		byIndex =(m_csBitmaps[1].hBitmap == NULL ? 0 : 1);

	CRect	rImage;
	PrepareImageRect(bHasTitle, rpItem, rpCaption, bIsPressed, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, &rImage);

	hdcBmpMem = ::CreateCompatibleDC(pDC->m_hDC);

	hbmOldBmp =(HBITMAP)::SelectObject(hdcBmpMem, m_csBitmaps[byIndex].hBitmap);

	hdcMem = ::CreateCompatibleDC(NULL);

	hbmT =(HBITMAP)::SelectObject(hdcMem, m_csBitmaps[byIndex].hMask);

	if(bIsDisabled && m_bShowDisabledBitmap)
	{
		HDC		hDC = NULL;
		HBITMAP	hBitmap = NULL;

		hDC = ::CreateCompatibleDC(pDC->m_hDC);
		hBitmap = ::CreateCompatibleBitmap(pDC->m_hDC, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight);
		HBITMAP	hOldBmp2 =(HBITMAP)::SelectObject(hDC, hBitmap);

		RECT	rRect;
		rRect.left = 0;
		rRect.top = 0;
		rRect.right = rImage.right + 1;
		rRect.bottom = rImage.bottom + 1;
		::FillRect(hDC, &rRect,(HBRUSH)RGB(255, 255, 255));

		COLORREF crOldColor = ::SetBkColor(hDC, RGB(255,255,255));

		::BitBlt(hDC, 0, 0, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, hdcMem, 0, 0, SRCAND);
		::BitBlt(hDC, 0, 0, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, hdcBmpMem, 0, 0, SRCPAINT);

		::SetBkColor(hDC, crOldColor);
		::SelectObject(hDC, hOldBmp2);
		::DeleteDC(hDC);

		pDC->DrawState(	CPoint(rImage.left/*+1*/, rImage.top), 
						CSize(m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight), 
						hBitmap, DST_BITMAP | DSS_DISABLED);

		::DeleteObject(hBitmap);
	} // if
	else
	{
		::BitBlt(pDC->m_hDC, rImage.left, rImage.top, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, hdcMem, 0, 0, SRCAND);

		::BitBlt(pDC->m_hDC, rImage.left, rImage.top, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, hdcBmpMem, 0, 0, SRCPAINT);
	} // else

	::SelectObject(hdcMem, hbmT);
	::DeleteDC(hdcMem);

	::SelectObject(hdcBmpMem, hbmOldBmp);
	::DeleteDC(hdcBmpMem);
} // End of DrawTheBitmap

void ArxRleButton::DrawTheText(CDC* pDC, LPCTSTR lpszText, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled)
{
	// Draw the button's title
	// If button is pressed then "press" title also
	if(m_bIsPressed && m_bIsCheckBox == FALSE)
		rpCaption->OffsetRect(m_ptPressedOffset.x, m_ptPressedOffset.y);

	// ONLY FOR DEBUG 
	//CBrush brBtnShadow(RGB(255, 0, 0));
	//pDC->FrameRect(rCaption, &brBtnShadow);

	// Center text
	CRect centerRect = rpCaption;
	pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
	rpCaption->OffsetRect((centerRect.Width() - rpCaption->Width())/2,(centerRect.Height() - rpCaption->Height())/2);
	/* RFU
	rpCaption->OffsetRect(0,(centerRect.Height() - rpCaption->Height())/2);
	rpCaption->OffsetRect((centerRect.Width() - rpCaption->Width())-4,(centerRect.Height() - rpCaption->Height())/2);
	*/

	pDC->SetBkMode(TRANSPARENT);
	/*
	pDC->DrawState(rCaption->TopLeft(), rCaption->Size(),(LPCTSTR)sTitle,(bIsDisabled ? DSS_DISABLED : DSS_NORMAL), 
					TRUE, 0,(CBrush*)NULL);
	*/
	if(m_bIsDisabled)
	{
		rpCaption->OffsetRect(1, 1);
		pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
		pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER);
		rpCaption->OffsetRect(-1, -1);
		pDC->SetTextColor(::GetSysColor(COLOR_3DSHADOW));
		pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER);
	} // if
	else
	{
		if(m_bMouseOnButton || m_bIsPressed) 
		{
			pDC->SetTextColor(m_crColors[BTNST_COLOR_FG_IN]);
			pDC->SetBkColor(m_crColors[BTNST_COLOR_BK_IN]);
		} // if
		else 
		{
			pDC->SetTextColor(m_crColors[BTNST_COLOR_FG_OUT]);
			pDC->SetBkColor(m_crColors[BTNST_COLOR_BK_OUT]);
		} // else
		pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER);
	} // if
} // End of DrawTheText

// This function creates a grayscale icon starting from a given icon.
// The resulting icon will have the same size of the original one.
//
// Parameters:
//		[IN]	hIcon
//				Handle to the original icon.
//
// Return value:
//		If the function succeeds, the return value is the handle to the newly created
//		grayscale icon.
//		If the function fails, the return value is NULL.
//
// Updates:
//		03/May/2002	Removed dependancy from m_hWnd
//					Removed 1 BitBlt operation
//
HICON ArxRleButton::CreateGrayscaleIcon(HICON hIcon)
{
	HICON		hGrayIcon = NULL;
	HDC			hMainDC = NULL, hMemDC1 = NULL, hMemDC2 = NULL;
	BITMAP		bmp;
	HBITMAP		hOldBmp1 = NULL, hOldBmp2 = NULL;
	ICONINFO	csII, csGrayII;
	BOOL		bRetValue = FALSE;

	bRetValue = ::GetIconInfo(hIcon, &csII);
	if(bRetValue == FALSE)	return NULL;

	hMainDC = ::GetDC(NULL);
	hMemDC1 = ::CreateCompatibleDC(hMainDC);
	hMemDC2 = ::CreateCompatibleDC(hMainDC);
	if(hMainDC == NULL || hMemDC1 == NULL || hMemDC2 == NULL)	return NULL;
  
	if(::GetObject(csII.hbmColor, sizeof(BITMAP), &bmp))
	{
		DWORD	dwWidth = csII.xHotspot*2;
		DWORD	dwHeight = csII.yHotspot*2;

		csGrayII.hbmColor = ::CreateBitmap(dwWidth, dwHeight, bmp.bmPlanes, bmp.bmBitsPixel, NULL);
		if(csGrayII.hbmColor)
		{
			hOldBmp1 =(HBITMAP)::SelectObject(hMemDC1, csII.hbmColor);
			hOldBmp2 =(HBITMAP)::SelectObject(hMemDC2, csGrayII.hbmColor);

			//::BitBlt(hMemDC2, 0, 0, dwWidth, dwHeight, hMemDC1, 0, 0, SRCCOPY);

			DWORD		dwLoopY = 0, dwLoopX = 0;
			COLORREF	crPixel = 0;
			BYTE		byNewPixel = 0;

			for(dwLoopY = 0; dwLoopY < dwHeight; dwLoopY++)
			{
				for(dwLoopX = 0; dwLoopX < dwWidth; dwLoopX++)
				{
					crPixel = ::GetPixel(hMemDC1, dwLoopX, dwLoopY);

					byNewPixel =(BYTE)((GetRValue(crPixel) * 0.299) +(GetGValue(crPixel) * 0.587) +(GetBValue(crPixel) * 0.114));
					if(crPixel)	::SetPixel(hMemDC2, dwLoopX, dwLoopY, RGB(byNewPixel, byNewPixel, byNewPixel));
				} // for
			} // for

			::SelectObject(hMemDC1, hOldBmp1);
			::SelectObject(hMemDC2, hOldBmp2);

			csGrayII.hbmMask = csII.hbmMask;

			csGrayII.fIcon = TRUE;
			hGrayIcon = ::CreateIconIndirect(&csGrayII);
		} // if

		::DeleteObject(csGrayII.hbmColor);
		//::DeleteObject(csGrayII.hbmMask);
	} // if

	::DeleteObject(csII.hbmColor);
	::DeleteObject(csII.hbmMask);
	::DeleteDC(hMemDC1);
	::DeleteDC(hMemDC2);
	::ReleaseDC(NULL, hMainDC);

	return hGrayIcon;
} // End of CreateGrayscaleIcon

// This function assigns icons to the button.
// Any previous icon or bitmap will be removed.
//
// Parameters:
//		[IN]	nIconIn
//				ID number of the icon resource to show when the mouse is over the button.
//				Pass NULL to remove any icon from the button.
//		[IN]	nIconOut
//				ID number of the icon resource to show when the mouse is outside the button.
//				Can be NULL.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDRESOURCE
//			Failed loading the specified resource.
//
DWORD ArxRleButton::SetIcon(int nIconIn, int nIconOut)
{
	HICON		hIconIn			= NULL;
	HICON		hIconOut		= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nIconIn), RT_GROUP_ICON);

	// Set icon when the mouse is IN the button
	hIconIn =(HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconIn), IMAGE_ICON, 0, 0, 0);

  	// Set icon when the mouse is OUT the button
	if(nIconOut)
	{
		if(nIconOut ==(int)BTNST_AUTO_GRAY)
			hIconOut = BTNST_AUTO_GRAY;
		else
			hIconOut =(HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconOut), IMAGE_ICON, 0, 0, 0);
	} // if

	return SetIcon(hIconIn, hIconOut);
} // End of SetIcon

// This function assigns icons to the button.
// Any previous icon or bitmap will be removed.
//
// Parameters:
//		[IN]	hIconIn
//				Handle fo the icon to show when the mouse is over the button.
//				Pass NULL to remove any icon from the button.
//		[IN]	hIconOut
//				Handle to the icon to show when the mouse is outside the button.
//				Can be NULL.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDRESOURCE
//			Failed loading the specified resource.
//
DWORD ArxRleButton::SetIcon(HICON hIconIn, HICON hIconOut)
{
	BOOL		bRetValue;
	ICONINFO	ii;

	// Free any loaded resource
	FreeResources();

	if(hIconIn)
	{
		// Icon when mouse over button?
		m_csIcons[0].hIcon = hIconIn;
		// Get icon dimension
		::ZeroMemory(&ii, sizeof(ICONINFO));
		bRetValue = ::GetIconInfo(hIconIn, &ii);
		if(bRetValue == FALSE)
		{
			FreeResources();
			return BTNST_INVALIDRESOURCE;
		} // if

		m_csIcons[0].dwWidth	=(DWORD)(ii.xHotspot * 2);
		m_csIcons[0].dwHeight	=(DWORD)(ii.yHotspot * 2);
		::DeleteObject(ii.hbmMask);
		::DeleteObject(ii.hbmColor);

		// Icon when mouse outside button?
		if(hIconOut)
		{
			if(hIconOut == BTNST_AUTO_GRAY)
			{
				hIconOut = CreateGrayscaleIcon(hIconIn);
			} // if

			m_csIcons[1].hIcon = hIconOut;
			// Get icon dimension
			::ZeroMemory(&ii, sizeof(ICONINFO));
			bRetValue = ::GetIconInfo(hIconOut, &ii);
			if(bRetValue == FALSE)
			{
				FreeResources();
				return BTNST_INVALIDRESOURCE;
			} // if

			m_csIcons[1].dwWidth	=(DWORD)(ii.xHotspot * 2);
			m_csIcons[1].dwHeight	=(DWORD)(ii.yHotspot * 2);
			::DeleteObject(ii.hbmMask);
			::DeleteObject(ii.hbmColor);
		} // if
	} // if

	Invalidate();

	return BTNST_OK;
} // End of SetIcon

// This function assigns bitmaps to the button.
// Any previous icon or bitmap will be removed.
//
// Parameters:
//		[IN]	nBitmapIn
//				ID number of the bitmap resource to show when the mouse is over the button.
//				Pass NULL to remove any bitmap from the button.
//		[IN]	crTransColorIn
//				Color(inside nBitmapIn) to be used as transparent color.
//		[IN]	nBitmapOut
//				ID number of the bitmap resource to show when the mouse is outside the button.
//				Can be NULL.
//		[IN]	crTransColorOut
//				Color(inside nBitmapOut) to be used as transparent color.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDRESOURCE
//			Failed loading the specified resource.
//		BTNST_FAILEDMASK
//			Failed creating mask bitmap.
//
DWORD ArxRleButton::SetBitmaps(int nBitmapIn, COLORREF crTransColorIn, int nBitmapOut, COLORREF crTransColorOut)
{
	HBITMAP		hBitmapIn		= NULL;
	HBITMAP		hBitmapOut		= NULL;
	HINSTANCE	hInstResource	= NULL;
	
	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmapIn), RT_BITMAP);

	// Load bitmap In
	hBitmapIn =(HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmapIn), IMAGE_BITMAP, 0, 0, 0);

	// Load bitmap Out
	if(nBitmapOut)
		hBitmapOut =(HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmapOut), IMAGE_BITMAP, 0, 0, 0);

	return SetBitmaps(hBitmapIn, crTransColorIn, hBitmapOut, crTransColorOut);
} // End of SetBitmaps

// This function assigns bitmaps to the button.
// Any previous icon or bitmap will be removed.
//
// Parameters:
//		[IN]	hBitmapIn
//				Handle fo the bitmap to show when the mouse is over the button.
//				Pass NULL to remove any bitmap from the button.
//		[IN]	crTransColorIn
//				Color(inside hBitmapIn) to be used as transparent color.
//		[IN]	hBitmapOut
//				Handle to the bitmap to show when the mouse is outside the button.
//				Can be NULL.
//		[IN]	crTransColorOut
//				Color(inside hBitmapOut) to be used as transparent color.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDRESOURCE
//			Failed loading the specified resource.
//		BTNST_FAILEDMASK
//			Failed creating mask bitmap.
//
DWORD ArxRleButton::SetBitmaps(HBITMAP hBitmapIn, COLORREF crTransColorIn, HBITMAP hBitmapOut, COLORREF crTransColorOut)
{
	int		nRetValue;
	BITMAP	csBitmapSize;

	// Free any loaded resource
	FreeResources();

	if(hBitmapIn)
	{
		m_csBitmaps[0].hBitmap = hBitmapIn;
		m_csBitmaps[0].crTransparent = crTransColorIn;
		// Get bitmap size
		nRetValue = ::GetObject(hBitmapIn, sizeof(csBitmapSize), &csBitmapSize);
		if(nRetValue == 0)
		{
			FreeResources();
			return BTNST_INVALIDRESOURCE;
		} // if
		m_csBitmaps[0].dwWidth =(DWORD)csBitmapSize.bmWidth;
		m_csBitmaps[0].dwHeight =(DWORD)csBitmapSize.bmHeight;

		// Create mask for bitmap In
		m_csBitmaps[0].hMask = CreateBitmapMask(hBitmapIn, m_csBitmaps[0].dwWidth, m_csBitmaps[0].dwHeight, crTransColorIn);
		if(m_csBitmaps[0].hMask == NULL)
		{
			FreeResources();
			return BTNST_FAILEDMASK;
		} // if

		if(hBitmapOut)
		{
			m_csBitmaps[1].hBitmap = hBitmapOut;
			m_csBitmaps[1].crTransparent = crTransColorOut;
			// Get bitmap size
			nRetValue = ::GetObject(hBitmapOut, sizeof(csBitmapSize), &csBitmapSize);
			if(nRetValue == 0)
			{
				FreeResources();
				return BTNST_INVALIDRESOURCE;
			} // if
			m_csBitmaps[1].dwWidth =(DWORD)csBitmapSize.bmWidth;
			m_csBitmaps[1].dwHeight =(DWORD)csBitmapSize.bmHeight;

			// Create mask for bitmap Out
			m_csBitmaps[1].hMask = CreateBitmapMask(hBitmapOut, m_csBitmaps[1].dwWidth, m_csBitmaps[1].dwHeight, crTransColorOut);
			if(m_csBitmaps[1].hMask == NULL)
			{
				FreeResources();
				return BTNST_FAILEDMASK;
			} // if
		} // if
	} // if

	Invalidate();

	return BTNST_OK;
} // End of SetBitmaps

// This functions sets the button to have a standard or flat style.
//
// Parameters:
//		[IN]	bFlat
//				If TRUE the button will have a flat style, else
//				will have a standard style.
//				By default, ArxRleButton buttons are flat.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButton::SetFlat(BOOL bFlat, BOOL bRepaint)
{
	m_bIsFlat = bFlat;
	if(bRepaint)	Invalidate();

	return BTNST_OK;
} // End of SetFlat

// This function sets the alignment type between icon/bitmap and text.
//
// Parameters:
//		[IN]	byAlign
//				Alignment type. Can be one of the following values:
//				ST_ALIGN_HORIZ			Icon/bitmap on the left, text on the right
//				ST_ALIGN_VERT			Icon/bitmap on the top, text on the bottom
//				ST_ALIGN_HORIZ_RIGHT	Icon/bitmap on the right, text on the left
//				ST_ALIGN_OVERLAP		Icon/bitmap on the same space as text
//				By default, ArxRleButton buttons have ST_ALIGN_HORIZ alignment.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDALIGN
//			Alignment type not supported.
//
DWORD ArxRleButton::SetAlign(BYTE byAlign, BOOL bRepaint)
{
	switch(byAlign)
	{    
		case ST_ALIGN_HORIZ:
		case ST_ALIGN_HORIZ_RIGHT:
		case ST_ALIGN_VERT:
		case ST_ALIGN_OVERLAP:
			m_byAlign = byAlign;
			if(bRepaint)	Invalidate();
			return BTNST_OK;
			break;
	} // switch

	return BTNST_INVALIDALIGN;
} // End of SetAlign

// This function sets the pressed style.
//
// Parameters:
//		[IN]	byStyle
//				Pressed style. Can be one of the following values:
//				BTNST_PRESSED_LEFTRIGHT		Pressed style from left to right(as usual)
//				BTNST_PRESSED_TOPBOTTOM		Pressed style from top to bottom
//				By default, ArxRleButton buttons have BTNST_PRESSED_LEFTRIGHT style.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDPRESSEDSTYLE
//			Pressed style not supported.
//
DWORD ArxRleButton::SetPressedStyle(BYTE byStyle, BOOL bRepaint)
{
	switch(byStyle)
	{
		case BTNST_PRESSED_LEFTRIGHT:
			m_ptPressedOffset.x = 1;
			m_ptPressedOffset.y = 1;
			break;
		case BTNST_PRESSED_TOPBOTTOM:
			m_ptPressedOffset.x = 0;
			m_ptPressedOffset.y = 2;
			break;
		default:
			return BTNST_INVALIDPRESSEDSTYLE;
	} // switch

	if(bRepaint)	Invalidate();

	return BTNST_OK;
} // End of SetPressedStyle

// This function sets the state of the checkbox.
// If the button is not a checkbox, this function has no meaning.
//
// Parameters:
//		[IN]	nCheck
//				1 to check the checkbox.
//				0 to un-check the checkbox.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButton::SetCheck(int nCheck, BOOL bRepaint)
{
	if(m_bIsCheckBox)
	{
		if(nCheck == 0) m_nCheck = 0;
		else m_nCheck = 1;

		if(bRepaint) Invalidate();
	} // if

	return BTNST_OK;
} // End of SetCheck

// This function returns the current state of the checkbox.
// If the button is not a checkbox, this function has no meaning.
//
// Return value:
//		The current state of the checkbox.
//			1 if checked.
//			0 if not checked or the button is not a checkbox.
//
int ArxRleButton::GetCheck()
{
	return m_nCheck;
} // End of GetCheck

// This function sets all colors to a default value.
//
// Parameters:
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButton::SetDefaultColors(BOOL bRepaint)
{
	m_crColors[BTNST_COLOR_BK_IN]		= ::GetSysColor(COLOR_BTNFACE);
	m_crColors[BTNST_COLOR_FG_IN]		= ::GetSysColor(COLOR_BTNTEXT);
	m_crColors[BTNST_COLOR_BK_OUT]		= ::GetSysColor(COLOR_BTNFACE);
	m_crColors[BTNST_COLOR_FG_OUT]		= ::GetSysColor(COLOR_BTNTEXT);
	m_crColors[BTNST_COLOR_BK_FOCUS]	= ::GetSysColor(COLOR_BTNFACE);
	m_crColors[BTNST_COLOR_FG_FOCUS]	= ::GetSysColor(COLOR_BTNTEXT);

	if(bRepaint)	Invalidate();

	return BTNST_OK;
} // End of SetDefaultColors

// This function sets the color to use for a particular state.
//
// Parameters:
//		[IN]	byColorIndex
//				Index of the color to set. Can be one of the following values:
//				BTNST_COLOR_BK_IN		Background color when mouse is over the button
//				BTNST_COLOR_FG_IN		Text color when mouse is over the button
//				BTNST_COLOR_BK_OUT		Background color when mouse is outside the button
//				BTNST_COLOR_FG_OUT		Text color when mouse is outside the button
//				BTNST_COLOR_BK_FOCUS	Background color when the button is focused
//				BTNST_COLOR_FG_FOCUS	Text color when the button is focused
//		[IN]	crColor
//				New color.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDINDEX
//			Invalid color index.
//
DWORD ArxRleButton::SetColor(BYTE byColorIndex, COLORREF crColor, BOOL bRepaint)
{
	if(byColorIndex >= BTNST_MAX_COLORS)	return BTNST_INVALIDINDEX;

	// Set new color
	m_crColors[byColorIndex] = crColor;

	if(bRepaint)	Invalidate();

	return BTNST_OK;
} // End of SetColor

// This functions returns the color used for a particular state.
//
// Parameters:
//		[IN]	byColorIndex
//				Index of the color to get.
//				See SetColor for the list of available colors.
//		[OUT]	crpColor
//				A pointer to a COLORREF that will receive the color.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDINDEX
//			Invalid color index.
//
DWORD ArxRleButton::GetColor(BYTE byColorIndex, COLORREF* crpColor)
{
	if(byColorIndex >= BTNST_MAX_COLORS)	return BTNST_INVALIDINDEX;

	// Get color
	*crpColor = m_crColors[byColorIndex];

	return BTNST_OK;
} // End of GetColor

// This function applies an offset to the RGB components of the specified color.
// This function can be seen as an easy way to make a color darker or lighter than
// its default value.
//
// Parameters:
//		[IN]	byColorIndex
//				Index of the color to set.
//				See SetColor for the list of available colors.
//		[IN]	shOffsetColor
//				A short value indicating the offset to apply to the color.
//				This value must be between -255 and 255.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDINDEX
//			Invalid color index.
//		BTNST_BADPARAM
//			The specified offset is out of range.
//
DWORD ArxRleButton::OffsetColor(BYTE byColorIndex, short shOffset, BOOL bRepaint)
{
	BYTE	byRed = 0;
	BYTE	byGreen = 0;
	BYTE	byBlue = 0;
	short	shOffsetR = shOffset;
	short	shOffsetG = shOffset;
	short	shOffsetB = shOffset;

	if(byColorIndex >= BTNST_MAX_COLORS)	return BTNST_INVALIDINDEX;
	if(shOffset < -255 || shOffset > 255)	return BTNST_BADPARAM;

	// Get RGB components of specified color
	byRed = GetRValue(m_crColors[byColorIndex]);
	byGreen = GetGValue(m_crColors[byColorIndex]);
	byBlue = GetBValue(m_crColors[byColorIndex]);

	// Calculate max. allowed real offset
	if(shOffset > 0)
	{
		if(byRed + shOffset > 255)		shOffsetR = 255 - byRed;
		if(byGreen + shOffset > 255)	shOffsetG = 255 - byGreen;
		if(byBlue + shOffset > 255)	shOffsetB = 255 - byBlue;

		shOffset = min(min(shOffsetR, shOffsetG), shOffsetB);
	} // if
	else
	{
		if(byRed + shOffset < 0)		shOffsetR = -byRed;
		if(byGreen + shOffset < 0)		shOffsetG = -byGreen;
		if(byBlue + shOffset < 0)		shOffsetB = -byBlue;

		shOffset = max(max(shOffsetR, shOffsetG), shOffsetB);
	} // else

	// Set new color
	m_crColors[byColorIndex] = RGB(byRed + shOffset, byGreen + shOffset, byBlue + shOffset);

	if(bRepaint)	Invalidate();

	return BTNST_OK;
} // End of OffsetColor

// This function sets the hilight logic for the button.
// Applies only to flat buttons.
//
// Parameters:
//		[IN]	bAlwaysTrack
//				If TRUE the button will be hilighted even if the window that owns it, is
//				not the active window.
//				If FALSE the button will be hilighted only if the window that owns it,
//				is the active window.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButton::SetAlwaysTrack(BOOL bAlwaysTrack)
{
	m_bAlwaysTrack = bAlwaysTrack;
	return BTNST_OK;
} // End of SetAlwaysTrack

// This function sets the cursor to be used when the mouse is over the button.
//
// Parameters:
//		[IN]	nCursorId
//				ID number of the cursor resource.
//				Pass NULL to remove a previously loaded cursor.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDRESOURCE
//			Failed loading the specified resource.
//
DWORD ArxRleButton::SetBtnCursor(int nCursorId, BOOL bRepaint)
{
	HINSTANCE	hInstResource = NULL;
	// Destroy any previous cursor
	if(m_hCursor)
	{
		::DestroyCursor(m_hCursor);
		m_hCursor = NULL;
	} // if

	// Load cursor
	if(nCursorId)
	{
		hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nCursorId), RT_GROUP_CURSOR);
		// Load cursor resource
		m_hCursor =(HCURSOR)::LoadImage(hInstResource, MAKEINTRESOURCE(nCursorId), IMAGE_CURSOR, 0, 0, 0);
		// Repaint the button
		if(bRepaint) Invalidate();
		// If something wrong
		if(m_hCursor == NULL) return BTNST_INVALIDRESOURCE;
	} // if

	return BTNST_OK;
} // End of SetBtnCursor

// This function sets if the button border must be drawn.
// Applies only to flat buttons.
//
// Parameters:
//		[IN]	bDrawBorder
//				If TRUE the border will be drawn.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButton::DrawBorder(BOOL bDrawBorder, BOOL bRepaint)
{
	m_bDrawBorder = bDrawBorder;
	// Repaint the button
	if(bRepaint) Invalidate();

	return BTNST_OK;
} // End of DrawBorder

// This function sets if the focus rectangle must be drawn for flat buttons.
//
// Parameters:
//		[IN]	bDrawFlatFocus
//				If TRUE the focus rectangle will be drawn also for flat buttons.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButton::DrawFlatFocus(BOOL bDrawFlatFocus, BOOL bRepaint)
{
	m_bDrawFlatFocus = bDrawFlatFocus;
	// Repaint the button
	if(bRepaint) Invalidate();

	return BTNST_OK;
} // End of DrawFlatFocus

void ArxRleButton::InitToolTip()
{
	if(m_ToolTip.m_hWnd == NULL)
	{
		// Create ToolTip control
		m_ToolTip.Create(this);
		// Create inactive
		m_ToolTip.Activate(FALSE);
		// Enable multiline
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
	} // if
} // End of InitToolTip

// This function sets the text to show in the button tooltip.
//
// Parameters:
//		[IN]	nText
//				ID number of the string resource containing the text to show.
//		[IN]	bActivate
//				If TRUE the tooltip will be created active.
//
void ArxRleButton::SetTooltipText(int nText, BOOL bActivate)
{
	CString sText;

	// Load string resource
	sText.LoadString(nText);
	// If string resource is not empty
	if(sText.IsEmpty() == FALSE) SetTooltipText((LPCTSTR)sText, bActivate);
} // End of SetTooltipText

// This function sets the text to show in the button tooltip.
//
// Parameters:
//		[IN]	lpszText
//				Pointer to a null-terminated string containing the text to show.
//		[IN]	bActivate
//				If TRUE the tooltip will be created active.
//
void ArxRleButton::SetTooltipText(LPCTSTR lpszText, BOOL bActivate)
{
	// We cannot accept NULL pointer
	if(lpszText == NULL) return;

	// Initialize ToolTip
	InitToolTip();

	// If there is no tooltip defined then add it
	if(m_ToolTip.GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_ToolTip.AddTool(this, lpszText, rectBtn, 1);
	} // if

	// Set text for tooltip
	m_ToolTip.UpdateTipText(lpszText, this, 1);
	m_ToolTip.Activate(bActivate);
} // End of SetTooltipText

// This function enables or disables the button tooltip.
//
// Parameters:
//		[IN]	bActivate
//				If TRUE the tooltip will be activated.
//
void ArxRleButton::ActivateTooltip(BOOL bActivate)
{
	// If there is no tooltip then do nothing
	if(m_ToolTip.GetToolCount() == 0) return;

	// Activate tooltip
	m_ToolTip.Activate(bActivate);
} // End of EnableTooltip

// This function returns if the button is the default button.
//
// Return value:
//		TRUE
//			The button is the default button.
//		FALSE
//			The button is not the default button.
//
BOOL ArxRleButton::GetDefault()
{
	return m_bIsDefault;
} // End of GetDefault

// This function enables the transparent mode.
// Note: this operation is not reversible.
// DrawTransparent should be called just after the button is created.
// Do not use trasparent buttons until you really need it(you have a bitmapped
// background) since each transparent button makes a copy in memory of its background.
// This may bring unnecessary memory use and execution overload.
//
// Parameters:
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
void ArxRleButton::DrawTransparent(BOOL bRepaint)
{
	m_bDrawTransparent = TRUE;

	// Restore old bitmap(if any)
	if(m_dcBk.m_hDC != NULL && m_pbmpOldBk != NULL)
	{
		m_dcBk.SelectObject(m_pbmpOldBk);
	} // if

	m_bmpBk.DeleteObject();
	m_dcBk.DeleteDC();

	// Repaint the button
	if(bRepaint) Invalidate();
} // End of DrawTransparent

DWORD ArxRleButton::SetBk(CDC* pDC)
{
	if(m_bDrawTransparent && pDC)
	{
		// Restore old bitmap(if any)
		if(m_dcBk.m_hDC != NULL && m_pbmpOldBk != NULL)
		{
			m_dcBk.SelectObject(m_pbmpOldBk);
		} // if

		m_bmpBk.DeleteObject();
		m_dcBk.DeleteDC();

		CRect rect;
		CRect rect1;

		GetClientRect(rect);

		GetWindowRect(rect1);
		GetParent()->ScreenToClient(rect1);

		m_dcBk.CreateCompatibleDC(pDC);
		m_bmpBk.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rect1.left, rect1.top, SRCCOPY);

		return BTNST_OK;
	} // if

	return BTNST_BADPARAM;
} // End of SetBk

// This function sets the URL that will be opened when the button is clicked.
//
// Parameters:
//		[IN]	lpszURL
//				Pointer to a null-terminated string that contains the URL.
//				Pass NULL to removed any previously specified URL.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButton::SetURL(LPCTSTR lpszURL)
{
	// Remove any existing URL
	memset(m_szURL, 0, sizeof(m_szURL));

	if(lpszURL)
	{
		// Store the URL
		_tcsncpy_s(m_szURL, lpszURL, _MAX_PATH);
	} // if

	return BTNST_OK;
} // End of SetURL

// This function associates a menu to the button.
// The menu will be displayed clicking the button.
//
// Parameters:
//		[IN]	nMenu
//				ID number of the menu resource.
//				Pass NULL to remove any menu from the button.
//		[IN]	hParentWnd
//				Handle to the window that owns the menu.
//				This window receives all messages from the menu.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDRESOURCE
//			Failed loading the specified resource.
//
#ifndef	BTNST_USE_BCMENU
DWORD ArxRleButton::SetMenu(UINT nMenu, HWND hParentWnd, BOOL bRepaint)
{
	HINSTANCE	hInstResource	= NULL;

	// Destroy any previous menu
	if(m_hMenu)
	{
		::DestroyMenu(m_hMenu);
		m_hMenu = NULL;
		m_hParentWndMenu = NULL;
		m_bMenuDisplayed = FALSE;
	} // if

	// Load menu
	if(nMenu)
	{
		// Find correct resource handle
		hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nMenu), RT_MENU);
		// Load menu resource
		m_hMenu = ::LoadMenu(hInstResource, MAKEINTRESOURCE(nMenu));
		m_hParentWndMenu = hParentWnd;
		// If something wrong
		if(m_hMenu == NULL) return BTNST_INVALIDRESOURCE;
	} // if

	// Repaint the button
	if(bRepaint) Invalidate();

	return BTNST_OK;
} // End of SetMenu
#endif

// This function associates a menu to the button.
// The menu will be displayed clicking the button.
// The menu will be handled by the ArxRleMenuXP class.
//
// Parameters:
//		[IN]	nMenu
//				ID number of the menu resource.
//				Pass NULL to remove any menu from the button.
//		[IN]	hParentWnd
//				Handle to the window that owns the menu.
//				This window receives all messages from the menu.
//		[IN]	bWinXPStyle
//				If TRUE the menu will be displayed using the new Windows XP style.
//				If FALSE the menu will be displayed using the standard style.
//		[IN]	nToolbarID
//				Resource ID of the toolbar to be associated to the menu.
//		[IN]	sizeToolbarIcon
//				A CSize object indicating the size(in pixels) of each icon into the toolbar.
//				All icons into the toolbar must have the same size.
//		[IN]	crToolbarBk
//				A COLORREF value indicating the color to use as background for the icons into the toolbar.
//				This color will be used as the "transparent" color.
//		[IN]	bRepaint
//				If TRUE the control will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDRESOURCE
//			Failed loading the specified resource.
//
#ifdef	BTNST_USE_BCMENU
DWORD ArxRleButton::SetMenu(UINT nMenu, HWND hParentWnd, BOOL bWinXPStyle, UINT nToolbarID, CSize sizeToolbarIcon, COLORREF crToolbarBk, BOOL bRepaint)
{
	BOOL	bRetValue = FALSE;

	// Destroy any previous menu
	if(m_menuPopup.m_hMenu)
	{
		m_menuPopup.DestroyMenu();
		m_hParentWndMenu = NULL;
		m_bMenuDisplayed = FALSE;
	} // if

	// Load menu
	if(nMenu)
	{
		m_menuPopup.SetMenuDrawMode(bWinXPStyle);
		// Load menu
		bRetValue = m_menuPopup.LoadMenu(nMenu);
		// If something wrong
		if(bRetValue == FALSE) return BTNST_INVALIDRESOURCE;

		// Load toolbar
		if(nToolbarID)
		{
			m_menuPopup.SetBitmapBackground(crToolbarBk);
			m_menuPopup.SetIconSize(sizeToolbarIcon.cx, sizeToolbarIcon.cy);

			bRetValue = m_menuPopup.LoadToolbar(nToolbarID);
			// If something wrong
			if(bRetValue == FALSE) 
			{
				m_menuPopup.DestroyMenu();
				return BTNST_INVALIDRESOURCE;
			} // if
		} // if

		m_hParentWndMenu = hParentWnd;
	} // if

	// Repaint the button
	if(bRepaint) Invalidate();

	return BTNST_OK;
} // End of SetMenu
#endif

// This function sets the callback message that will be sent to the
// specified window just before the menu associated to the button is displayed.
//
// Parameters:
//		[IN]	hWnd
//				Handle of the window that will receive the callback message.
//				Pass NULL to remove any previously specified callback message.
//		[IN]	nMessage
//				Callback message to send to window.
//		[IN]	lParam
//				A 32 bits user specified value that will be passed to the callback function.
//
// Remarks:
//		the callback function must be in the form:
//		LRESULT On_MenuCallback(WPARAM wParam, LPARAM lParam)
//		Where:
//				[IN]	wParam
//						If support for ArxRleMenuXP is enabled: a pointer to ArxRleMenuXP
//						else a HMENU handle to the menu that is being to be displayed.
//				[IN]	lParam
//						The 32 bits user specified value.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButton::SetMenuCallback(HWND hWnd, UINT nMessage, LPARAM lParam)
{
	m_csCallbacks.hWnd = hWnd;
	m_csCallbacks.nMessage = nMessage;
	m_csCallbacks.lParam = lParam;

	return BTNST_OK;
} // End of SetMenuCallback

// This function resizes the button to the same size of the image.
// To get good results both the IN and OUT images should have the same size.
//
void ArxRleButton::SizeToContent()
{
	if(m_csIcons[0].hIcon)
	{
		m_ptImageOrg.x = 0;
		m_ptImageOrg.y = 0;
	    SetWindowPos(	NULL, -1, -1, m_csIcons[0].dwWidth, m_csIcons[0].dwHeight,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
	} // if
	else
	if(m_csBitmaps[0].hBitmap)
	{
		m_ptImageOrg.x = 0;
		m_ptImageOrg.y = 0;
	    SetWindowPos(	NULL, -1, -1, m_csBitmaps[0].dwWidth, m_csBitmaps[0].dwHeight,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
	} // if
} // End of SizeToContent

// This function sets the sound that must be played on particular button states.
//
// Parameters:
//		[IN]	lpszSound
//				A string that specifies the sound to play.
//				If hMod is NULL this string is interpreted as a filename, else it
//				is interpreted as a resource identifier.
//				Pass NULL to remove any previously specified sound.
//		[IN]	hMod
//				Handle to the executable file that contains the resource to be loaded.
//				This parameter must be NULL unless lpszSound specifies a resource identifier.
//		[IN]	bPlayOnClick
//				TRUE if the sound must be played when the button is clicked.
//				FALSE if the sound must be played when the mouse is moved over the button.
//		[IN]	bPlayAsync
//				TRUE if the sound must be played asynchronously.
//				FALSE if the sound must be played synchronously. The application takes control
//				when the sound is completely played.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
#ifdef	BTNST_USE_SOUND
DWORD ArxRleButton::SetSound(LPCTSTR lpszSound, HMODULE hMod, BOOL bPlayOnClick, BOOL bPlayAsync)
{
	BYTE	byIndex = bPlayOnClick ? 1 : 0;

	// Store new sound
	if(lpszSound)
	{
		if(hMod)	// From resource identifier ?
		{
			m_csSounds[byIndex].lpszSound = lpszSound;
		} // if
		else
		{
			_tcscpy_s(m_csSounds[byIndex].szSound, lpszSound);
			m_csSounds[byIndex].lpszSound = m_csSounds[byIndex].szSound;
		} // else

		m_csSounds[byIndex].hMod = hMod;
		m_csSounds[byIndex].dwFlags = SND_NODEFAULT | SND_NOWAIT;
		m_csSounds[byIndex].dwFlags |= hMod ? SND_RESOURCE : SND_FILENAME;
		m_csSounds[byIndex].dwFlags |= bPlayAsync ? SND_ASYNC : SND_SYNC;
	} // if
	else
	{
		// Or remove any existing
		::ZeroMemory(&m_csSounds[byIndex], sizeof(STRUCT_SOUND));
	} // else

	return BTNST_OK;
}

DWORD ArxRleButton::SetSound(UINT idSound, HMODULE hMod, BOOL bPlayOnClick, BOOL bPlayAsync)
{
	return SetSound(MAKEINTRESOURCE(idSound),hMod,bPlayOnClick,bPlayAsync);
} // End of SetSound
#endif

// This function is called every time the button background needs to be painted.
// If the button is in transparent mode this function will NOT be called.
// This is a virtual function that can be rewritten in ArxRleButton-derived classes
// to produce a whole range of buttons not available by default.
//
// Parameters:
//		[IN]	pDC
//				Pointer to a CDC object that indicates the device context.
//		[IN]	pRect
//				Pointer to a CRect object that indicates the bounds of the
//				area to be painted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButton::OnDrawBackground(CDC* pDC, LPCRECT pRect)
{
	COLORREF	crColor;

	if(m_bMouseOnButton || m_bIsPressed)
		crColor = m_crColors[BTNST_COLOR_BK_IN];
	else
	{
		if(m_bIsFocused)
			crColor = m_crColors[BTNST_COLOR_BK_FOCUS];
		else
		{
			if(m_bSetBkColor)
				crColor = m_crBkColor;
			else
				crColor = m_crColors[BTNST_COLOR_BK_OUT];
		}
	} // else

	if(m_bSetBkBitmap)
	{
		HBITMAP		hBitmap			= NULL;
		HINSTANCE	hInstResource	= NULL;
		hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(m_iBitmapID), RT_BITMAP);
		hBitmap =(HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(m_iBitmapID), IMAGE_BITMAP, 0, 0, 0);
		
		CBrush brBackground;
		CBitmap* pBitmap = NULL;
		pBitmap = CBitmap::FromHandle(hBitmap);
		brBackground.CreatePatternBrush(pBitmap);
		pDC->FillRect(pRect, &brBackground);
	}
	else
	{
		CBrush brBackground(crColor);
		pDC->FillRect(pRect, &brBackground);
	}

	return BTNST_OK;
} // End of OnDrawBackground

void ArxRleButton::SetBtnBkBitmap(HICON hIcon, BOOL bSetBkBitmap)
{

}

// This function is called every time the button border needs to be painted.
// If the button is in standard(not flat) mode this function will NOT be called.
// This is a virtual function that can be rewritten in ArxRleButton-derived classes
// to produce a whole range of buttons not available by default.
//
// Parameters:
//		[IN]	pDC
//				Pointer to a CDC object that indicates the device context.
//		[IN]	pRect
//				Pointer to a CRect object that indicates the bounds of the
//				area to be painted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButton::OnDrawBorder(CDC* pDC, LPCRECT pRect)
{
	if(m_bIsPressed)
		pDC->Draw3dRect(pRect, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHILIGHT));
	else
		pDC->Draw3dRect(pRect, ::GetSysColor(COLOR_BTNHILIGHT), ::GetSysColor(COLOR_BTNSHADOW));

	return BTNST_OK;
} // End of OnDrawBorder

#undef BS_TYPEMASK

CCeXDib::CCeXDib()
{
	m_hDib = NULL;
	m_dwLineWidth = 0;
	m_wColors = 0;

	m_hMemDC = NULL;
	m_hBitmap = NULL;
	m_lpBits = NULL;

	FreeResources();
}

CCeXDib::~CCeXDib()
{
	FreeResources();
}

void CCeXDib::FreeResources()
{
	if (m_hMemDC)	::DeleteDC(m_hMemDC);
	if (m_hBitmap)	::DeleteObject(m_hBitmap);
	if (m_hDib)		delete m_hDib;

	m_hDib = NULL;
	m_hMemDC = NULL;
	m_hBitmap = NULL;
	m_lpBits = NULL;
	memset(&m_bi, 0, sizeof(m_bi));
} // End of FreeResources

HDIB CCeXDib::Create(DWORD dwWidth, DWORD dwHeight, WORD wBitCount)
{
    LPBITMAPINFOHEADER  lpbi = NULL;	// Pointer to BITMAPINFOHEADER
    DWORD               dwLen = 0;		// Size of memory block

	FreeResources();

	// Following <switch> is taken from
	// CDIBSectionLite class by Chris Maunder
    switch (wBitCount) 
    {
	    case 1:  m_wColors = 2;   break;
#ifdef _WIN32_WCE
        case 2:  m_wColors = 4;   break;   // winCE only       
#endif
        case 4:  m_wColors = 16;  break;
        case 8:  m_wColors = 256; break;
        case 16:
        case 24:
        case 32: m_wColors = 0;   break;   // 16,24 or 32 bpp have no color table

        default:
           m_wColors = 0;
    } // switch
/*
    // Make sure bits per pixel is valid
    if (wBitCount <= 1)			wBitCount = 1;
    else if (wBitCount <= 4)	wBitCount = 4;
    else if (wBitCount <= 8)	wBitCount = 8;
    else				        wBitCount = 24;

    switch (wBitCount)
	{
        case 1:
            m_wColors = 2;
			break;
        case 4:
            m_wColors = 16;
			break;
        case 8:
            m_wColors = 256;
			break;
        default:
            m_wColors = 0;
			break;
    } // switch
*/
    m_dwLineWidth = WIDTHBYTES(wBitCount * dwWidth);

    // Initialize BITMAPINFOHEADER
    m_bi.biSize = sizeof(BITMAPINFOHEADER);
    m_bi.biWidth = dwWidth;         // fill in width from parameter
    m_bi.biHeight = dwHeight;       // fill in height from parameter
    m_bi.biPlanes = 1;              // must be 1
    m_bi.biBitCount = wBitCount;    // from parameter
    m_bi.biCompression = BI_RGB;    
    m_bi.biSizeImage = m_dwLineWidth * dwHeight;
    m_bi.biXPelsPerMeter = 0;
    m_bi.biYPelsPerMeter = 0;
    m_bi.biClrUsed = 0;
    m_bi.biClrImportant = 0;

    // Calculate size of memory block required to store the DIB.  This
    // block should be big enough to hold the BITMAPINFOHEADER, the color
    // table, and the bits.
    dwLen = GetSize();

	m_hDib = new HDIB[dwLen]; // Allocate memory block to store our bitmap
    if (m_hDib == NULL) return NULL;

    // Use our bitmap info structure to fill in first part of
    // our DIB with the BITMAPINFOHEADER
	lpbi = (LPBITMAPINFOHEADER)(m_hDib);
    *lpbi = m_bi;

    return m_hDib; // Return handle to the DIB
} // End of Create

DWORD CCeXDib::GetSize()
{
	return m_bi.biSize + m_bi.biSizeImage + GetPaletteSize();
} // End of GetSize

DWORD CCeXDib::GetPaletteSize()
{
	return (m_wColors * sizeof(RGBQUAD));
} // End of GetPaletteSize

LPBYTE CCeXDib::GetBits()
{
	if (m_hDib)	return ((LPBYTE)m_hDib + *(LPDWORD)m_hDib + GetPaletteSize()); 

	return NULL;
} // End of GetBits

DWORD CCeXDib::GetWidth()
{
	return m_bi.biWidth;
} // End of GetWidth

DWORD CCeXDib::GetHeight()
{
	return m_bi.biHeight;
} // End of GetHeight

DWORD CCeXDib::GetLineWidth()
{
	return m_dwLineWidth;
} // End of GetLineWidth

void CCeXDib::BlendPalette(COLORREF crColor, DWORD dwPerc)
{
	if (m_hDib == NULL || m_wColors == 0) return;

	LPBYTE iDst = (LPBYTE)(m_hDib) + sizeof(BITMAPINFOHEADER);

	int i,r,g,b;

	RGBQUAD* pPal = (RGBQUAD*)iDst;

	r = GetRValue(crColor);
	g = GetGValue(crColor);
	b = GetBValue(crColor);

	if (dwPerc > 100) dwPerc = 100;

	for (i = 0; i < m_wColors; i++)
	{
		pPal[i].rgbBlue = (BYTE)((pPal[i].rgbBlue * (100 - dwPerc) + b * dwPerc) / 100);
		pPal[i].rgbGreen = (BYTE)((pPal[i].rgbGreen * (100 - dwPerc) + g * dwPerc) / 100);
		pPal[i].rgbRed = (BYTE)((pPal[i].rgbRed * (100 - dwPerc) + r * dwPerc) / 100);
	} // for
} // End of BlendPalette

void CCeXDib::Clear(BYTE byVal)
{
	if (m_hDib) memset(GetBits(), byVal, m_bi.biSizeImage);
} // End of Clear

void CCeXDib::SetPixelIndex(DWORD dwX, DWORD dwY, BYTE byI)
{
	if ((m_hDib == NULL) || (m_wColors == 0) ||
		((long)dwX < 0) || ((long)dwY < 0) || (dwX >= (DWORD)m_bi.biWidth) || (dwY >= (DWORD)m_bi.biHeight)) return;

	LPBYTE iDst = GetBits();
	iDst[(m_bi.biHeight - dwY - 1) * m_dwLineWidth + dwX] = byI;
} // End of SetPixelIndex

void CCeXDib::Clone(CCeXDib* src)
{
	Create(src->GetWidth(), src->GetHeight(), src->GetBitCount());
	if (m_hDib) memcpy(m_hDib, src->m_hDib, GetSize());
} // End of Clone

WORD CCeXDib::GetBitCount()
{
	return m_bi.biBitCount;
} // End of GetBitCount

void CCeXDib::SetPaletteIndex(BYTE byIdx, BYTE byR, BYTE byG, BYTE byB)
{
	if (m_hDib && m_wColors)
	{
		LPBYTE iDst = (LPBYTE)(m_hDib) + sizeof(BITMAPINFOHEADER);
		if ((byIdx >= 0) && (byIdx < m_wColors))
		{	
			long ldx = byIdx * sizeof(RGBQUAD);
			iDst[ldx++] = (BYTE)byB;
			iDst[ldx++] = (BYTE)byG;
			iDst[ldx++] = (BYTE)byR;
			iDst[ldx] = (BYTE)0;
		} // if
	} // if
} // End of SetPaletteIndex

void CCeXDib::Draw(HDC hDC, DWORD dwX, DWORD dwY)
{
	HBITMAP	hBitmap = NULL;
	HBITMAP	hOldBitmap = NULL;
	HDC		hMemDC = NULL;

	if (m_hBitmap == NULL)
	{
		m_hBitmap = CreateDIBSection(hDC, (BITMAPINFO*)m_hDib, DIB_RGB_COLORS, &m_lpBits, NULL, 0);
		if (m_hBitmap == NULL)	return;
		if (m_lpBits == NULL)
		{
			::DeleteObject(m_hBitmap);
			m_hBitmap = NULL;
			return;
		} // if
	} // if

    memcpy(m_lpBits, GetBits(), m_bi.biSizeImage);

	if (m_hMemDC == NULL)
	{
		m_hMemDC = CreateCompatibleDC(hDC);
		if (m_hMemDC == NULL)	return;
	} // if

	hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	BitBlt(hDC, dwX, dwY, m_bi.biWidth, m_bi.biHeight, m_hMemDC, 0, 0, SRCCOPY);

	SelectObject(m_hMemDC, hOldBitmap);
} // End of Draw

void CCeXDib::SetGrayPalette()
{
	RGBQUAD		pal[256];
	RGBQUAD*	ppal;
	LPBYTE		iDst;
	int			ni;

	if (m_hDib == NULL || m_wColors == 0) return;

	ppal = (RGBQUAD*)&pal[0];
	iDst = (LPBYTE)(m_hDib) + sizeof(BITMAPINFOHEADER);
	for (ni = 0; ni < m_wColors; ni++)
	{
		pal[ni] = RGB2RGBQUAD(RGB(ni,ni,ni));
	} // for

	pal[0] = RGB2RGBQUAD(RGB(0,0,0));
	pal[m_wColors-1] = RGB2RGBQUAD(RGB(255,255,255));

	memcpy(iDst, ppal, GetPaletteSize());
} // End of SetGrayPalette

RGBQUAD CCeXDib::RGB2RGBQUAD(COLORREF cr)
{
	RGBQUAD c;
	c.rgbRed = GetRValue(cr);	/* get R, G, and B out of DWORD */
	c.rgbGreen = GetGValue(cr);
	c.rgbBlue = GetBValue(cr);
	c.rgbReserved=0;
	return c;
} // End of RGB2RGBQUAD

WORD CCeXDib::GetNumColors()
{
	return m_wColors;
} // End of GetNumColors

BOOL CCeXDib::WriteBMP(LPCTSTR bmpFileName)
{
	BITMAPFILEHEADER	hdr;
	HANDLE	hFile;
	DWORD	nByteWrite;

	if (*bmpFileName == _T('\0') || m_hDib == 0) return 0;

	hFile=CreateFile(			// open if exist ini file
		bmpFileName,			// pointer to name of the file 
		GENERIC_WRITE,			// access mode 
		0,						// share mode 
		NULL,					// pointer to security descriptor 
		CREATE_ALWAYS,			// how to create 
		FILE_ATTRIBUTE_NORMAL,	// file attributes 
		NULL				 	// handle to file with attributes to copy  
		);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

    // Fill in the fields of the file header
	hdr.bfType = BFT_BITMAP;
	hdr.bfSize = GetSize() + sizeof(BITMAPFILEHEADER);
	hdr.bfReserved1 = hdr.bfReserved2 = 0;
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER)+
					m_bi.biSize + GetPaletteSize();

    // Write the file header
	WriteFile(						// write ini (sync mode <-> no overlapped)
		hFile,						// handle of file to write 
		(LPSTR) &hdr,				// address of buffer that contains data  
		sizeof(BITMAPFILEHEADER),	// number of bytes to write 
		&nByteWrite,				// address of number of bytes written 
		NULL	 					// address of structure for data 
		);

    // Write the DIB header and the bits
	WriteFile(						// write ini (sync mode <-> no overlapped)
		hFile,						// handle of file to write 
		(LPSTR) m_hDib,				// address of buffer that contains data  
		GetSize(),					// number of bytes to write 
		&nByteWrite,				// address of number of bytes written 
		NULL	 					// address of structure for data 
		);

	CloseHandle(hFile);				// free file handle

	return TRUE;
} // End of WriteBMP

ArxRleButtonXP::ArxRleButtonXP()
{
	// No rounded borders
	m_bIsRounded = FALSE;
}

ArxRleButtonXP::~ArxRleButtonXP()
{
}

// This function is called every time the button border needs to be painted.
// If the button is in standard (not flat) mode this function will NOT be called.
// This is a virtual function that can be rewritten in CButtonST-derived classes
// to produce a whole range of buttons not available by default.
//
// Parameters:
//		[IN]	pDC
//				Pointer to a CDC object that indicates the device context.
//		[IN]	pRect
//				Pointer to a CRect object that indicates the bounds of the
//				area to be painted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButtonXP::OnDrawBorder(CDC* pDC, LPCRECT pRect)
{
	ArxRleButton::OnDrawBorder(pDC, pRect);
	return BTNST_OK;
} // End of OnDrawBorder

// This function is called every time the button background needs to be painted.
// If the button is in transparent mode this function will NOT be called.
// This is a virtual function that can be rewritten in CButtonST-derived classes
// to produce a whole range of buttons not available by default.
//
// Parameters:
//		[IN]	pDC
//				Pointer to a CDC object that indicates the device context.
//		[IN]	pRect
//				Pointer to a CRect object that indicates the bounds of the
//				area to be painted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButtonXP::OnDrawBackground(CDC* pDC, LPCRECT pRect)
{
	if (!m_bMouseOnButton && !m_bIsPressed)
		return ArxRleButton::OnDrawBackground(pDC, pRect);

	// Create and select a solid brush for button background
	CBrush brushBK(m_crColors[BTNST_COLOR_BK_IN]);
	CBrush* pOldBrush = pDC->SelectObject(&brushBK);

	// Create and select a thick black pen for button border
	CPen penBorder;
	penBorder.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&penBorder);

	if (m_bIsRounded)
		pDC->RoundRect(pRect, CPoint(8, 8));
	else
		pDC->Rectangle(pRect);

	// Put back the old objects
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	if (m_bMouseOnButton)
	{
		if (m_bIsPressed)
			m_dOver.Draw(pDC->GetSafeHdc(),1,1);
		else
			m_dOver.Draw(pDC->GetSafeHdc(),0,0);
	}
	else
		m_dNormal.Draw(pDC->GetSafeHdc(),0,0);

	return BTNST_OK;
} // End of OnDrawBackground

void ArxRleButtonXP::SetShade(UINT shadeID, BYTE granularity, BYTE highlight, BYTE coloring, COLORREF color)
{
	long	sXSize,sYSize,bytes,j,i,k,h;
	BYTE	*iDst ,*posDst;

	RECT rect;
	GetWindowRect(&rect);
	sYSize=rect.bottom-rect.top;
	sXSize=rect.right-rect.left ;

	m_dh.Create(max(1,sXSize /*-2*m_FocusRectMargin-1*/ ),1,8);	//create the horizontal focus bitmap
	m_dv.Create(1,max(1,sYSize /*-2*m_FocusRectMargin*/),8);	//create the vertical focus bitmap

	m_dNormal.Create(sXSize,sYSize,8);					//create the default bitmap

	COLORREF hicr=GetSysColor(COLOR_BTNHIGHLIGHT);		//get the button base colors
	COLORREF midcr=GetSysColor(COLOR_BTNFACE);
	COLORREF locr=GetSysColor(COLOR_BTNSHADOW);
	int r,g,b;											//build the shaded palette
	int rl = GetRValue(locr), gl = GetRValue(locr), bl = GetRValue(locr);
	int rm = GetRValue(midcr), gm = GetRValue(midcr), bm = GetRValue(midcr);
	int rh = GetRValue(hicr), gh = GetRValue(hicr), bh = GetRValue(hicr);
	for(i=0;i<129;i++){
		r=((128-i)*rl+i*rm)/128;
		g=((128-i)*gl+i*gm)/128;
		b=((128-i)*bl+i*bm)/128;
		m_dNormal.SetPaletteIndex((BYTE)i,(BYTE)r,(BYTE)g,(BYTE)b);
		m_dh.SetPaletteIndex((BYTE)i,(BYTE)r,(BYTE)g,(BYTE)b);
		m_dv.SetPaletteIndex((BYTE)i,(BYTE)r,(BYTE)g,(BYTE)b);
	}
	for(i=1;i<129;i++){
		r=((128-i)*rm+i*rh)/128;
		g=((128-i)*gm+i*gh)/128;
		b=((128-i)*bm+i*bh)/128;
		m_dNormal.SetPaletteIndex((BYTE)(i+127),(BYTE)r,(BYTE)g,(BYTE)b);
		m_dh.SetPaletteIndex((BYTE)(i+127),(BYTE)r,(BYTE)g,(BYTE)b);
		m_dv.SetPaletteIndex((BYTE)(i+127),(BYTE)r,(BYTE)g,(BYTE)b);
	}

	m_dNormal.BlendPalette(color,coloring);	//color the palette

	iDst=m_dh.GetBits();		//build the horiz. dotted focus bitmap
	j=(long)m_dh.GetWidth();
	for(i=0;i<j;i++){
		//		iDst[i]=64+127*(i%2);	//soft
		iDst[i]=255*(i%2);		//hard
	}

	iDst=m_dv.GetBits();		//build the vert. dotted focus bitmap
	j=(long)m_dv.GetHeight();
	for(i=0;i<j;i++){
		//		*iDst=64+127*(i%2);		//soft
		*iDst=255*(i%2);		//hard
		iDst+=4;
	}

	bytes = m_dNormal.GetLineWidth();
	iDst = m_dNormal.GetBits();
	posDst =iDst;
	long a,x,y,d,xs,idxmax,idxmin;

	int grainx2=RAND_MAX/(max(1,2*granularity));
	idxmax=255-granularity;
	idxmin=granularity;

	switch(shadeID){
		//----------------------------------------------------
	case 8:	//SHS_METAL
		m_dNormal.Clear();
		// create the strokes
		k=40;	//stroke granularity
		for(a=0;a<200;a++){
			x=rand()/(RAND_MAX/sXSize); //stroke postion
			y=rand()/(RAND_MAX/sYSize);	//stroke position
			xs=rand()/(RAND_MAX/min(sXSize,sYSize))/2; //stroke lenght
			d=rand()/(RAND_MAX/k);	//stroke color
			for(i=0;i<xs;i++){
				if (((x-i)>0)&&((y+i)<sYSize))
					m_dNormal.SetPixelIndex(x-i,y+i,(BYTE)d);
				if (((x+i)<sXSize)&&((y-i)>0))
					m_dNormal.SetPixelIndex(sXSize-x+i,y-i,(BYTE)d);
			}
		}
		//blend strokes with SHS_DIAGONAL
		posDst =iDst;
		a=(idxmax-idxmin-k)/2;
		for(i = 0; i < sYSize; i++) {
			for(j = 0; j < sXSize; j++) {
				d=posDst[j]+((a*i)/sYSize+(a*(sXSize-j))/sXSize);
				posDst[j]=(BYTE)d;
				posDst[j]+=rand()/grainx2;
			}
			posDst+=bytes;
		}

		break;
		//----------------------------------------------------
	case 7:	// SHS_HARDBUMP
		//set horizontal bump
		for(i = 0; i < sYSize; i++) {
			k=(255*i/sYSize)-127;
			k=(k*(k*k)/128)/128;
			k=(k*(128-granularity*2))/128+128;
			for(j = 0; j < sXSize; j++) {
				posDst[j]=(BYTE)k;
				posDst[j]+=rand()/grainx2-granularity;
			}
			posDst+=bytes;
		}
		//set vertical bump
		d=min(16,sXSize/6);	//max edge=16
		a=sYSize*sYSize/4;
		posDst =iDst;
		for(i = 0; i < sYSize; i++) {
			y=i-sYSize/2;
			for(j = 0; j < sXSize; j++) {
				x=j-sXSize/2;
				xs=sXSize/2-d+(y*y*d)/a;
				if (x>xs) posDst[j]=idxmin+(BYTE)(((sXSize-j)*128)/d);
				if ((x+xs)<0) posDst[j]=idxmax-(BYTE)((j*128)/d);
				posDst[j]+=rand()/grainx2-granularity;
			}
			posDst+=bytes;
		}
		break;
		//----------------------------------------------------
	case 6: //SHS_SOFTBUMP
		for(i = 0; i < sYSize; i++) {
			h=(255*i/sYSize)-127;
			for(j = 0; j < sXSize; j++) {
				k=(255*(sXSize-j)/sXSize)-127;
				k=(h*(h*h)/128)/128+(k*(k*k)/128)/128;
				k=k*(128-granularity)/128+128;
				if (k<idxmin) k=idxmin;
				if (k>idxmax) k=idxmax;
				posDst[j]=(BYTE)k;
				posDst[j]+=rand()/grainx2-granularity;
			}
			posDst+=bytes;
		}
		break;
		//----------------------------------------------------
	case 5: // SHS_VBUMP
		for(j = 0; j < sXSize; j++) {
			k=(255*(sXSize-j)/sXSize)-127;
			k=(k*(k*k)/128)/128;
			k=(k*(128-granularity))/128+128;
			for(i = 0; i < sYSize; i++) {
				posDst[j+i*bytes]=(BYTE)k;
				posDst[j+i*bytes]+=rand()/grainx2-granularity;
			}
		}
		break;
		//----------------------------------------------------
	case 4: //SHS_HBUMP
		for(i = 0; i < sYSize; i++) {
			k=(255*i/sYSize)-127;
			k=(k*(k*k)/128)/128;
			k=(k*(128-granularity))/128+128;
			for(j = 0; j < sXSize; j++) {
				posDst[j]=(BYTE)k;
				posDst[j]+=rand()/grainx2-granularity;
			}
			posDst+=bytes;
		}
		break;
		//----------------------------------------------------
	case 1:	//SHS_DIAGSHADE
		a=(idxmax-idxmin)/2;
		for(i = 0; i < sYSize; i++) {
			for(j = 0; j < sXSize; j++) {
				posDst[j]=(BYTE)(idxmin+a*i/sYSize+a*(sXSize-j)/sXSize);
				posDst[j]+=rand()/grainx2-granularity;
			}
			posDst+=bytes;
		}
		break;
		//----------------------------------------------------
	case 2:	//SHS_HSHADE
		a=idxmax-idxmin;
		for(i = 0; i < sYSize; i++) {
			k=a*i/sYSize+idxmin;
			for(j = 0; j < sXSize; j++) {
				posDst[j]=(BYTE)k;
				posDst[j]+=rand()/grainx2-granularity;
			}
			posDst+=bytes;
		}
		break;
		//----------------------------------------------------
	case 3:	//SHS_VSHADE:
		a=idxmax-idxmin;
		for(j = 0; j < sXSize; j++) {
			k=a*(sXSize-j)/sXSize+idxmin;
			for(i = 0; i < sYSize; i++) {
				posDst[j+i*bytes]=(BYTE)k;
				posDst[j+i*bytes]+=rand()/grainx2-granularity;
			}
		}
		break;
		//----------------------------------------------------
	default:	//SHS_NOISE
		for(i = 0; i < sYSize; i++) {
			for(j = 0; j < sXSize; j++) {
				posDst[j]=128+rand()/grainx2-granularity;
			}
			posDst+=bytes;
		}
	}
	//----------------------------------------------------
	m_dDisabled.Clone(&m_dNormal);	//build the other bitmaps
	m_dOver.Clone(&m_dNormal);
	m_dOver.BlendPalette(hicr,highlight);
	m_dDown.Clone(&m_dOver);
}

// This function enables or disables the rounded border for the button.
//
// Parameters:
//		[IN]	bRounded
//				If TRUE the button will have a round border.
//		[IN]	bRepaint
//				If TRUE the button will be repainted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD ArxRleButtonXP::SetRounded(BOOL bRounded, BOOL bRepaint)
{
	m_bIsRounded = bRounded;
	if (bRepaint)	Invalidate();

	return BTNST_OK;
} // End of SetRounded