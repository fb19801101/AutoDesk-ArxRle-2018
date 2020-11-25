// ArxRleDockingPaneManager.h: interface for the ArxRleDockingPaneManager class.
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

#ifndef ARXRLE_DOCKINGPANE_MANAGER_H
#define ARXRLE_DOCKINGPANE_MANAGER_H

#include "Resource.h"


class ArxRleComandBarsPaintManager : public CXTPVisualStudio2008Theme
{
public:
	ArxRleComandBarsPaintManager();

protected:
	void FillCommandBarEntry(CDC* pDC, CXTPCommandBar* pBar);
	void RoundRect(CDC* pDC, CRect rc, COLORREF clr);
	void DrawRectangle(CDC* pDC, CRect rc, BOOL bSelected, BOOL bPressed, BOOL bEnabled, BOOL bChecked, BOOL bPopuped, XTPBarType barType, XTPBarPosition barPosition);
};

class ArxRleDockingPaneTabbedContainer : public CXTPDockingPaneTabbedContainer
{
public:
	ArxRleDockingPaneTabbedContainer(CXTPDockingPaneLayout* pLayout);

	void OnCaptionButtonClick(CXTPDockingPaneCaptionButton* pButton);
	BOOL IsCaptionButtonVisible(CXTPDockingPaneCaptionButton* pButton);
};

class CDockingPaneMiniWnd : public CXTPDockingPaneMiniWnd
{
public:
	CDockingPaneMiniWnd(CXTPDockingPaneLayout* pLayout);
	void OnCaptionButtonClick(CXTPDockingPaneCaptionButton* pButton);

	void OnNcRButtonDown(UINT nHitTest, CPoint point);

	DECLARE_MESSAGE_MAP()
};

class ArxRleDockingPanePaintManager : public CXTPDockingPaneVisualStudio2008Theme
{
public:
	ArxRleDockingPanePaintManager();

protected:
	void RoundRect(CDC* pDC, CRect rc, COLORREF clr);
	void DrawSplitter(CDC& dc, CXTPDockingPaneSplitterWnd* pSplitter);

	virtual void DrawCaptionButton(CDC* pDC, CXTPDockingPaneCaptionButton* pButton, COLORREF clrText);
	virtual void DrawCaptionButtonEntry(CDC* pDC, CXTPDockingPaneCaptionButton* pButton, CPoint pt, COLORREF clrButton);
};


class ArxRleDockingPaneManager : public CXTPDockingPaneManager
{
public:
	ArxRleDockingPaneManager();
	virtual ~ArxRleDockingPaneManager();

protected:
	virtual CXTPDockingPaneBase* OnCreatePane(XTPDockingPaneType type, CXTPDockingPaneLayout* pLayout);

};

#endif // ARXRLE_DOCKINGPANE_MANAGER_H
