///////////////////////////////////////////////////////////////////////////////
// ArxRleMenuBar.h : header file
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
//  An ownerdraw ToolBarXP that have a ToolBarXP attach in it.For using,create a 
//	ToolBarXP or ArxRleMenuXP object,then load it in ArxRleMenuBar.It also can't docked by
//	framewindow,should used in a container wndow.
//
//  ArxRleMenuBar.h Declaration of CMenuXP¡¢CToolBarEX¡¢CToolBarCtrlEx¡¢ArxRleMenuBar
//
///////////////////////////////////////////////////////////////////////////////

#ifndef ARXRLE_MENUBAR_H
#define ARXRLE_MENUBAR_H

#ifndef MB_POPUPMENU
#define	MB_POPUPMENU  WM_USER +1101
#endif

///////////////////////////////////////////////////////////////////////////////
// CBCGKeyHelper
class CBCGKeyHelper : public CObject
{
public:
	CBCGKeyHelper();
	CBCGKeyHelper(LPACCEL lpAccel);
	virtual ~CBCGKeyHelper();

// Operations:
public:
	void Format (CString& str) const;

protected:
	void AddVirtKeyStr (CString& str, UINT uiVirtKey, BOOL bLast = FALSE) const;

// Atttributes:
public:
	void SetAccelerator (LPACCEL lpAccel)
	{
		m_lpAccel = lpAccel;
	}

protected:
	LPACCEL m_lpAccel;
};

///////////////////////////////////////////////////////////////////////////////
// CMenuXP
class CMenuXPItem
{
public:
	DWORD		m_dwMagicNum;
	DWORD		m_dwID;
	bool		m_bSeparator;
	bool		m_bSideBar;
	bool		m_bButtonOnly;
	CString		m_strText;
	HICON		m_hIcon;
	int			m_nSize;

public:
	CMenuXPItem() 
	{
		m_dwMagicNum = 0x0505a0a0;
		m_dwID = 0;
		m_bSeparator = false;
		m_bSideBar = false;
		m_bButtonOnly = false;
		m_hIcon = NULL;
		m_nSize = 16;
	};

	virtual ~CMenuXPItem()
	{
		if (m_hIcon)
			::DestroyIcon(m_hIcon);
	}

	BOOL	IsMyData(void) { return m_dwMagicNum == 0x0505a0a0; };
};

class CMenuXPText : public CMenuXPItem	//Normal item with text and an optional icon
{
public:
	CMenuXPText(DWORD dwID, LPCTSTR strText, HICON hIcon = NULL) : CMenuXPItem()
	{
		m_dwID = dwID;
		m_strText = strText;
		m_hIcon = hIcon;
	}

	CMenuXPText(DWORD dwID, LPCTSTR strText, HBITMAP hBmp) : CMenuXPItem()
	{
		m_dwID = dwID;
		m_strText = strText;
		Gdiplus::Bitmap* pTmpBitmap=Gdiplus::Bitmap::FromHBITMAP(hBmp,NULL);
		pTmpBitmap->GetHICON(&m_hIcon);
		delete pTmpBitmap;
	}
};

class CMenuXPSeparator : public CMenuXPItem //A separator item
{
public:
	CMenuXPSeparator() : CMenuXPItem()
	{
		m_bSeparator = true;
	}
};

class CMenuXPSideBar : public CMenuXPItem //A gradient sidebar
{
public:
	CMenuXPSideBar(int nSize = 32, LPCTSTR strText = NULL, HICON hIcon=NULL, DWORD dwID=0) : CMenuXPItem()
	{
		m_dwID = dwID;
		m_bSideBar = true;
		m_strText = strText;
		m_hIcon = hIcon;
		m_nSize = nSize;
		m_dwID = dwID;
	}
};

class CMenuXPButton : public CMenuXPItem //A button only item
{
public:
	CMenuXPButton(DWORD dwID, HICON hIcon = NULL) : CMenuXPItem()
	{
		m_dwID = dwID;
		m_bButtonOnly = true;
		m_hIcon = hIcon;
	}
};

class CMenuXP : public CMenu  
{
	DECLARE_DYNCREATE(CMenuXP)

public:
	CMenuXP();
	virtual ~CMenuXP();

	typedef	enum 
	{
		STYLE_XP,
		STYLE_OFFICE,
		STYLE_STARTMENU
	} MENUSTYLE;

	BOOL	AddSideBar(CMenuXPSideBar *pItem);
	BOOL	AppendODMenu(UINT nFlags, CMenuXPItem *pItem, ACCEL *pAccel=0);
	BOOL	AppendSeparator(void);	
	BOOL	AppendODPopup(UINT nFlags, CMenuXP *pPopup, CMenuXPItem *pItem);
	void	Break(void);
	void	BreakBar(void);

protected:
	CFont		m_fontMenu;	
	COLORREF	m_clrBackGround;
	COLORREF	m_clrSelectedBar;
	COLORREF	m_clrText;
	COLORREF	m_clrSelectedText;
	COLORREF	m_clrDisabledText;

	COLORREF	m_clrSideBarStart;
	COLORREF	m_clrSideBarEnd;
	COLORREF	m_clrIconArea;

	BOOL		m_bBreak;
	BOOL		m_bBreakBar;

	MENUSTYLE	m_Style;

public:
	void	SetBackColor(COLORREF clr) { m_clrBackGround = clr; }
	void	SetSelectedBarColor(COLORREF clr) { m_clrSelectedBar = clr; }
	void	SetTextColor(COLORREF clr) { m_clrText = clr; }
	void	SetSelectedTextColor(COLORREF clr) { m_clrSelectedText = clr; }
	void	SetDisabledTextColor(COLORREF clr) { m_clrDisabledText = clr; }
	void	SetSideBarStartColor(COLORREF clr) { m_clrSideBarStart = clr; }
	void	SetSideBarEndColor(COLORREF clr) { m_clrSideBarEnd = clr; }
	void	SetIconAreaColor(COLORREF clr) { m_clrIconArea = clr; }
	
	void	SetMenuStyle(MENUSTYLE	style) { m_Style = style; }
	BOOL	SetMenuFont(LOGFONT	lgfont);
	
	CMenuXP	*FindSubMenuFromID(DWORD dwID);

public:
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	virtual void MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct );
	static	LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);

protected:
	virtual void DrawBackGround(CDC *pDC, CRect rect, BOOL bSelected, BOOL bDisabled);
	virtual void DrawButton(CDC *pDC, CRect rect, BOOL bSelected, BOOL bDisabled, BOOL bChecked);
	virtual void DrawIcon(CDC *pDC, CRect rect, HICON hIcon, BOOL bSelected, BOOL bDisabled);
	virtual void DrawSideBar(CDC *pDC, CRect rect, HICON hIcon, CString strText);
	virtual void DrawText(CDC *pDC, CRect rect, CString strText, BOOL bSelected, BOOL bDisabled, BOOL bBold);
	virtual void DrawCheckMark(CDC *pDC, CRect rect, BOOL bSelected);
	virtual void DrawMenuText(CDC& dc, CRect rc, CString text, COLORREF color);
	virtual void DrawIconArea(CDC *pDC, CRect rect, BOOL bSelected, BOOL bDisabled, BOOL bChecked);

	void	Clear(void);

	//helpers 
	HBITMAP		CreateGradientBMP(HDC hDC,COLORREF cl1,COLORREF cl2,int nWidth,int nHeight,int nDir,int nNumColors);
	void		DrawEmbossed(CDC *pDC, HICON hIcon, CRect rect, BOOL bColor = FALSE);
	void		FillRect(CDC *pDC, const CRect& rc, COLORREF color);
};


/////////////////////////////////////////////////////////////////////////////
// CToolBarCtrlEx
struct TBDATAINFO
{
	WORD wVersion;
	WORD wWidth;
	WORD wHeight;
	WORD wItemCount;

	WORD* items() { return (WORD*)(this+1); }
};
class  CToolBarCtrlEx : public CToolBarCtrl
{
	DECLARE_DYNCREATE(CToolBarCtrlEx)

public:
	CToolBarCtrlEx();
	virtual ~CToolBarCtrlEx();

public:
	void   SetBackColor(COLORREF clr) { m_clrBack = clr; }
	void   SetHotColor(COLORREF clr) { m_clrHot = clr; }
	void   SetSelectedColor(COLORREF clr) { m_clrSelected = clr; }
	void   SetCheckedColor(COLORREF clr) { m_clrChecked = clr; }
	void   SetTextColor(COLORREF clr) { m_clrText = clr; }
	void   SetLineColor(COLORREF clr) {m_clrLine = clr; }
		   
	void   EnableDrawLine(BOOL bDrawLine) { m_bDrawLine = bDrawLine; };
	BOOL   LoadToolBar(UINT nID);
	CSize  GetBarSize();
		 
	BOOL ShowMText(HINSTANCE hInst, UINT nID);
		 
	BOOL LoadMenu(CMenu *pMenu);
	BOOL LoadMenu(UINT id);
	void TrackPopup();
	BOOL OnMenuInput(MSG* pMsg);
		 
		 
	BOOL OpenMenu(UINT nChar);

protected:
	static LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam);
	void   PreDrawItem(CDC *pDC, const RECT &rect, UINT uState);

protected:   
	afx_msg void    OnCustomDraw( NMHDR *pNotifyStruct, LRESULT *result );
	afx_msg void    OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void    OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void    OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);

	afx_msg LRESULT OnPopupMenu(WPARAM wParam, LPARAM lParam);
	afx_msg void	OnExitMenuLoop(BOOL bTrackPopupMenu);
	afx_msg void	OnEnterMenuLoop(BOOL bTrackPopupMenu);

	DECLARE_MESSAGE_MAP()

private:
	static CToolBarCtrlEx*	m_pToolBarCtrlEx;
	static HHOOK   m_hCBTHook;

	CMenu*		m_pMenu;
	int			m_nItemCount;
	int			m_nPressed;
	POINT		m_ptMouse;
	BOOL		m_bTrack;

	CImageList	m_ilIcons;

	COLORREF	m_clrBack;	
	COLORREF	m_clrHot;
	COLORREF	m_clrSelected;
	COLORREF	m_clrChecked;
	COLORREF	m_clrLine;
	COLORREF    m_clrText;
	BOOL		m_bDrawLine;
};


///////////////////////////////////////////////////////////////////////////////
// ArxRleMenuBar
class ArxRleMenuBar : public CAcUiDockControlBar
{
	DECLARE_DYNCREATE(ArxRleMenuBar)

public:
	ArxRleMenuBar(UINT id = 0) ;
	ArxRleMenuBar(CMenuXP* pMenuXP);

	virtual BOOL Create(CWnd* pParent, LPCSTR lpszTitle);

protected:
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

protected:
	BOOL LoadMenuXP(UINT id = 0);
	BOOL LoadMenuXP(CMenuXP* pMenuXP);
	void MenuItemLoop(CMenuXP* pMenuXP, CMenu* pMenu, int nPos);

	void SetCloseBtnPosition();
	CRect GetInsideRect();

	virtual BOOL AddCustomMenuItems(LPARAM hMenu);
	virtual void PaintControlBar(CDC * pDC);
	virtual void SizeChanged (CRect *lpRect, BOOL bFloating, int flags);
	virtual bool OnClosing();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

private:
	CToolBarCtrlEx  m_wndToolBar;
	CMenuXP*        m_pMenuXP;
	long            m_cxDockBar, m_cyDockBar;
	long            m_cxToolBar, m_cyToolBar;
	int             m_cBorder;
	BOOL            m_bDrawMenuSidear;
	int             m_cxBarBtn;
};

#endif //ARXRLE_MENUBAR_H
