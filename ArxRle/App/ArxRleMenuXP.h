//*************************************************************************
// ArxRleMenuXP.h : header file
// Version : 3.034
// Date : May 2002
// Author : Brent Corkum
// Email :  corkum@rocscience.com
// Latest Version : http://www.rocscience.com/~corkum/ArxRleMenuXP.html
// 
// Bug Fixes and portions of code supplied by:
//
// Ben Ashley,Girish Bharadwaj,Jean-Edouard Lachand-Robert,
// Robert Edward Caldecott,Kenny Goers,Leonardo Zide,
// Stefan Kuhr,Reiner Jung,Martin Vladic,Kim Yoo Chul,
// Oz Solomonovich,Tongzhe Cui,Stephane Clog,Warren Stevens,
// Damir Valiulin,David Kinder,Marc Loiry
//
// You are free to use/modify this code but leave this header intact.
// This class is public domain so you are free to use it any of
// your applications (Freeware,Shareware,Commercial). All I ask is
// that you let me know so that if you have a real winner I can
// brag to my buddies that some of my code is in your app. I also
// wouldn't mind if you sent me a copy of your application since I
// like to play with new stuff.
//*************************************************************************

#ifndef ARXRLE_MENUXP_H
#define ARXRLE_MENUXP_H

#include <afxtempl.h>

#define ArxRleMenuXP_USE_MEMDC
#ifdef ArxRleMenuXP_USE_MEMDC
#include "ArxRleMemDC.h"
class ArxRleMemDC;
#endif

// ArxRleMenuXPData class. Fill this class structure to define a single menu item:
class ArxRleMenuXPData
{
	wchar_t *m_szMenuText;
public:
	ArxRleMenuXPData () {menuIconNormal=-1;xoffset=-1;bitmap=NULL;pContext=NULL;
	nFlags=0;nID=0;syncflag=0;m_szMenuText=NULL;global_offset=-1;};
	void SetAnsiString(LPCSTR szAnsiString);
	void SetWideString(const wchar_t *szWideString);
	const wchar_t *GetWideString(void) {return m_szMenuText;};
	~ArxRleMenuXPData ();
	CString GetString(void);//returns the menu text in ANSI or UNICODE
	int xoffset,global_offset;
	int menuIconNormal;
	UINT nFlags,nID,syncflag;
	CImageList *bitmap;
	void *pContext; // used to attach user data
};

//struct ArxRleMenuItemInfo : public MENUITEMINFO {
struct ArxRleMenuItemInfo : public 
//MENUITEMINFO 
#ifndef UNICODE   //SK: this fixes warning C4097: typedef-name 'MENUITEMINFO' used as synonym for class-name 'tagMENUITEMINFOA'
tagMENUITEMINFOA
#else
tagMENUITEMINFOW
#endif
{
	ArxRleMenuItemInfo()
	{
		memset(this, 0, sizeof(MENUITEMINFO));
		cbSize = sizeof(MENUITEMINFO);
	}
};

// how the menu's are drawn, either original or XP style
typedef enum {CMenuXP_DRAWMODE_ORIGINAL,CMenuXP_DRAWMODE_XP} BC_MenuDrawMode;

// how seperators are handled when removing a menu (Tongzhe Cui)
typedef enum {CMenuXP_NONE, CMenuXP_HEAD, CMenuXP_TAIL, CMenuXP_BOTH} BC_Seperator;

// defines for unicode support
#ifndef UNICODE
#define AppendMenu AppendMenuA
#define InsertMenu InsertMenuA
#define InsertODMenu InsertODMenuA
#define AppendODMenu AppendODMenuA
#define AppendODPopupMenu AppendODPopupMenuA
#define ModifyODMenu ModifyODMenuA
#else
#define AppendMenu AppendMenuW
#define InsertMenu InsertMenuW
#define InsertODMenu InsertODMenuW
#define AppendODMenu AppendODMenuW
#define ModifyODMenu ModifyODMenuW
#define AppendODPopupMenu AppendODPopupMenuW
#endif


class ArxRleMenuXP : public CMenu
{
	DECLARE_DYNAMIC( ArxRleMenuXP )
public:
	ArxRleMenuXP(); 
	virtual ~ArxRleMenuXP();

	// Functions for loading and applying bitmaps to menus (see example application)
	virtual BOOL LoadMenu(LPCTSTR lpszResourceName);
	virtual BOOL LoadMenu(int nResource);
	BOOL LoadToolbar(UINT nToolBar);
	BOOL LoadToolbars(const UINT *arID,int n);
	void AddFromToolBar(CToolBar* pToolBar, int nResourceID);
	BOOL LoadFromToolBar(UINT nID,UINT nToolBar,int& xoffset);
	BOOL AddBitmapToImageList(CImageList *list,UINT nResourceID);
	static HBITMAP LoadSysColorBitmap(int nResourceId);
	void LoadCheckmarkBitmap(int unselect,int select); // custom check mark bitmaps
	
	// functions for appending a menu option, use the AppendMenu call (see above define)
	BOOL AppendMenuA(UINT nFlags,UINT nIDNewItem=0,const char *lpszNewItem=NULL,int nIconNormal=-1);
	BOOL AppendMenuA(UINT nFlags,UINT nIDNewItem,const char *lpszNewItem,CImageList *il,int xoffset);
	BOOL AppendMenuA(UINT nFlags,UINT nIDNewItem,const char *lpszNewItem,CBitmap *bmp);
	BOOL AppendMenuW(UINT nFlags,UINT nIDNewItem=0,wchar_t *lpszNewItem=NULL,int nIconNormal=-1);
	BOOL AppendMenuW(UINT nFlags,UINT nIDNewItem,wchar_t *lpszNewItem,CImageList *il,int xoffset);
	BOOL AppendMenuW(UINT nFlags,UINT nIDNewItem,wchar_t *lpszNewItem,CBitmap *bmp);
	BOOL AppendODMenuA(LPCSTR lpstrText,UINT nFlags = MF_OWNERDRAW,UINT nID = 0,int nIconNormal = -1);  
	BOOL AppendODMenuW(wchar_t *lpstrText,UINT nFlags = MF_OWNERDRAW,UINT nID = 0,int nIconNormal = -1);  
	BOOL AppendODMenuA(LPCSTR lpstrText,UINT nFlags,UINT nID,CImageList *il,int xoffset);
	BOOL AppendODMenuW(wchar_t *lpstrText,UINT nFlags,UINT nID,CImageList *il,int xoffset);
	
	// for appending a popup menu (see example application)
	ArxRleMenuXP* AppendODPopupMenuA(LPCSTR lpstrText);
	ArxRleMenuXP* AppendODPopupMenuW(wchar_t *lpstrText);

	// functions for inserting a menu option, use the InsertMenu call (see above define)
	BOOL InsertMenuA(UINT nPosition,UINT nFlags,UINT nIDNewItem=0,const char *lpszNewItem=NULL,int nIconNormal=-1);
	BOOL InsertMenuA(UINT nPosition,UINT nFlags,UINT nIDNewItem,const char *lpszNewItem,CImageList *il,int xoffset);
	BOOL InsertMenuA(UINT nPosition,UINT nFlags,UINT nIDNewItem,const char *lpszNewItem,CBitmap *bmp);
	BOOL InsertMenuW(UINT nPosition,UINT nFlags,UINT nIDNewItem=0,wchar_t *lpszNewItem=NULL,int nIconNormal=-1);
	BOOL InsertMenuW(UINT nPosition,UINT nFlags,UINT nIDNewItem,wchar_t *lpszNewItem,CImageList *il,int xoffset);
	BOOL InsertMenuW(UINT nPosition,UINT nFlags,UINT nIDNewItem,wchar_t *lpszNewItem,CBitmap *bmp);
	BOOL InsertODMenuA(UINT nPosition,LPCSTR lpstrText,UINT nFlags = MF_OWNERDRAW,UINT nID = 0,int nIconNormal = -1); 
	BOOL InsertODMenuW(UINT nPosition,wchar_t *lpstrText,UINT nFlags = MF_OWNERDRAW,UINT nID = 0,int nIconNormal = -1);  
	BOOL InsertODMenuA(UINT nPosition,LPCSTR lpstrText,UINT nFlags,UINT nID,CImageList *il,int xoffset);
	BOOL InsertODMenuW(UINT nPosition,wchar_t *lpstrText,UINT nFlags,UINT nID,CImageList *il,int xoffset);
	
	// functions for modifying a menu option, use the ModifyODMenu call (see above define)
	BOOL ModifyODMenuA(const char *lpstrText,UINT nID=0,int nIconNormal=-1);
	BOOL ModifyODMenuA(const char *lpstrText,UINT nID,CImageList *il,int xoffset);
	BOOL ModifyODMenuA(const char *lpstrText,UINT nID,CBitmap *bmp);
	BOOL ModifyODMenuA(const char *lpstrText,const char *OptionText,int nIconNormal);
	BOOL ModifyODMenuW(wchar_t *lpstrText,UINT nID=0,int nIconNormal=-1);
	BOOL ModifyODMenuW(wchar_t *lpstrText,UINT nID,CImageList *il,int xoffset);
	BOOL ModifyODMenuW(wchar_t *lpstrText,UINT nID,CBitmap *bmp);
	BOOL ModifyODMenuW(wchar_t *lpstrText,wchar_t *OptionText,int nIconNormal);
	// use this method for adding a solid/hatched colored square beside a menu option
	// courtesy of Warren Stevens
	BOOL ModifyODMenuA(const char *lpstrText,UINT nID,COLORREF fill,COLORREF border,int hatchstyle=-1,CSize *pSize=NULL);
	BOOL ModifyODMenuW(wchar_t *lpstrText,UINT nID,COLORREF fill,COLORREF border,int hatchstyle=-1,CSize *pSize=NULL);
	
	// for deleting and removing menu options
	BOOL	RemoveMenu(UINT uiId,UINT nFlags);
	BOOL	DeleteMenu(UINT uiId,UINT nFlags);
	// sPos means Seperator's position, since we have no way to find the seperator's position in the menu
	// we have to specify them when we call the RemoveMenu to make sure the unused seperators are removed;
	// sPos  = None no seperator removal;
	//       = Head  seperator in front of this menu item;
	//       = Tail  seperator right after this menu item;
	//       = Both  seperators at both ends;
	// remove the menu item based on their text, return -1 if not found, otherwise return the menu position;
	int RemoveMenu(char* pText, BC_Seperator sPos=CMenuXP_NONE);
	int RemoveMenu(wchar_t* pText, BC_Seperator sPos=CMenuXP_NONE);
	int DeleteMenu(char* pText, BC_Seperator sPos=CMenuXP_NONE);
	int DeleteMenu(wchar_t* pText, BC_Seperator sPos=CMenuXP_NONE);
	
	// Destoying
	virtual BOOL DestroyMenu();

	// function for retrieving and setting a menu options text (use this function
	// because it is ownerdrawn)
	BOOL GetMenuText(UINT id,CString &string,UINT nFlags = MF_BYPOSITION);
	BOOL SetMenuText(UINT id,CString string, UINT nFlags = MF_BYPOSITION);

	// Getting a submenu from it's name or position
	ArxRleMenuXP* GetSubCMenuXP(char* lpszSubMenuName);
	ArxRleMenuXP* GetSubCMenuXP(wchar_t* lpszSubMenuName);
	CMenu* GetSubMenu (LPCTSTR lpszSubMenuName);
	CMenu* GetSubMenu (int nPos);
	int GetMenuPosition(char* pText);
	int GetMenuPosition(wchar_t* pText);

	// Drawing: 
	virtual void DrawItem( LPDRAWITEMSTRUCT);  // Draw an item
	virtual void MeasureItem( LPMEASUREITEMSTRUCT );  // Measure an item

	// Static functions used for handling menu's in the mainframe
	static void UpdateMenu(CMenu *pmenu);
	static BOOL IsMenu(CMenu *submenu);
	static BOOL IsMenu(HMENU submenu);
	static LRESULT FindKeyboardShortcut(UINT nChar,UINT nFlags,CMenu *pMenu);

	// Function to set how menu is drawn, either original or XP style
	static void SetMenuDrawMode(UINT mode){
		ArxRleMenuXP::original_drawmode=mode;
		ArxRleMenuXP::xp_drawmode=mode;
	};
	// Function to set how disabled items are drawn (mode=FALSE means they are not drawn selected)
	static void SetSelectDisableMode(BOOL mode){
		ArxRleMenuXP::original_select_disabled=mode;
		ArxRleMenuXP::xp_select_disabled=mode;
	};

	static int ArxRleMenuXP::GetMenuDrawMode(void);
	static BOOL ArxRleMenuXP::GetSelectDisableMode(void);

	// how the bitmaps are drawn in XP Luna mode
	static void SetXPBitmap3D(BOOL val){
		ArxRleMenuXP::xp_draw_3D_bitmaps=val;
	};
	static BOOL GetXPBitmap3D(void){return ArxRleMenuXP::xp_draw_3D_bitmaps;}

	// Customizing:
	// Set icon size
	static void SetIconSize (int, int); 
	// set the color in the bitmaps that is the background transparent color
	void SetBitmapBackground(COLORREF color);
	static void SetMenuXPItemColor(
		        COLORREF clrMenuXPBk=GetSysColor(COLOR_WINDOW),
		        COLORREF clrMenuXPSideBarBk=GetSysColor(COLOR_3DFACE),
	            COLORREF clrMenuXPText=GetSysColor(COLOR_MENUTEXT),
		        COLORREF clrMenuXPSel=GetSysColor(COLOR_HIGHLIGHT));
	void UnSetBitmapBackground(void);
	// obsolete functions for setting how menu images are dithered for disabled menu options
	BOOL GetDisableOldStyle(void);
	void SetDisableOldStyle(void);
	void UnSetDisableOldStyle(void);
	static COLORREF LightenColor(COLORREF col,double factor);
	static COLORREF DarkenColor(COLORREF col,double factor);

// Miscellaneous Protected Member functions
protected:
	static BOOL IsNewShell(void);
	static BOOL IsWinXPLuna(void);
	static BOOL IsLunaMenuStyle(void);
	static BOOL IsWindowsClassicTheme(void);
	ArxRleMenuXPData *ArxRleMenuXP::FindMenuItem(UINT nID);
	ArxRleMenuXP *FindMenuOption(int nId,int& nLoc);
	ArxRleMenuXP *FindAnotherMenuOption(int nId,int& nLoc,CArray<ArxRleMenuXP*,ArxRleMenuXP*>&bcsubs,
								  CArray<int,int&>&bclocs);
	ArxRleMenuXPData *FindMenuOption(wchar_t *lpstrText);
	void InsertSpaces(void);
	void DrawCheckMark(CDC* pDC,int x,int y,COLORREF color,BOOL narrowflag=FALSE);
	void DrawRadioDot(CDC *pDC,int x,int y,COLORREF color);
	ArxRleMenuXPData *NewODMenu(UINT pos,UINT nFlags,UINT nID,CString string);
	void SynchronizeMenu(void);
	void ArxRleMenuXP::InitializeMenuList(int value);
	void ArxRleMenuXP::DeleteMenuList(void);
	ArxRleMenuXPData *ArxRleMenuXP::FindMenuList(UINT nID);
	void DrawItem_Win9xNT2000 (LPDRAWITEMSTRUCT lpDIS);
	void DrawItem_WinXP (LPDRAWITEMSTRUCT lpDIS);
	BOOL Draw3DCheckmark(CDC *dc, const CRect& rc,BOOL bSelected,HBITMAP hbmCheck);
	BOOL DrawXPCheckmark(CDC *dc, const CRect& rc, HBITMAP hbmCheck,COLORREF &colorout,BOOL selected);
	void DitherBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, 
		int nHeight, HBITMAP hbm, int nXSrc, int nYSrc,COLORREF bgcolor);
	void DitherBlt2(CDC *drawdc, int nXDest, int nYDest, int nWidth, 
		int nHeight, CBitmap &bmp, int nXSrc, int nYSrc,COLORREF bgcolor);
	void DitherBlt3(CDC *drawdc, int nXDest, int nYDest, int nWidth, 
		int nHeight, CBitmap &bmp,COLORREF bgcolor);
	BOOL GetBitmapFromImageList(CDC* pDC,CImageList *imglist,int nIndex,CBitmap &bmp);
	BOOL ImageListDuplicate(CImageList *il,int xoffset,CImageList *newlist);
	static WORD NumBitmapColors(LPBITMAPINFOHEADER lpBitmap);
	void ColorBitmap(CDC* pDC, CBitmap& bmp,CSize bitmap_size,CSize icon_size,COLORREF fill,COLORREF border,int hatchstyle=-1);
	void RemoveTopLevelOwnerDraw(void);
	int GetMenuStart(void);
	void GetFadedBitmap(CBitmap &bmp);
	void GetTransparentBitmap(CBitmap &bmp);
	void GetDisabledBitmap(CBitmap &bmp,COLORREF background=0);
	void GetShadowBitmap(CBitmap &bmp);
	int AddToGlobalImageList(CImageList *il,int xoffset,int nID);
	int GlobalImageListOffset(int nID);
	BOOL CanDraw3DImageList(int offset);
	
// Member Variables
protected:
	CTypedPtrArray<CPtrArray, ArxRleMenuXPData*> m_MenuList;  // Stores list of menu items 
	// When loading an owner-drawn menu using a Resource, ArxRleMenuXP must keep track of
	// the popup menu's that it creates. Warning, this list *MUST* be destroyed
	// last item first :)
	CTypedPtrArray<CPtrArray, HMENU>  m_SubMenus;  // Stores list of sub-menus 
	// Stores a list of all ArxRleMenuXP's ever created 
	static CTypedPtrArray<CPtrArray, HMENU>  m_AllSubMenus;
	// Global ImageList
	static CImageList m_AllImages;
	static CArray<int,int&> m_AllImagesID;
	// icon size
	static int m_iconX;
	static int m_iconY;
	COLORREF m_bitmapBackground;
	static COLORREF m_clrMenuXPBk;
	static COLORREF m_clrMenuXPSideBarBk;
	static COLORREF m_clrMenuXPText;
	static COLORREF m_clrMenuXPSel;
	BOOL m_bitmapBackgroundFlag;
	BOOL disable_old_style;
	static UINT original_drawmode;
	static BOOL original_select_disabled;
	static UINT xp_drawmode;
	static BOOL xp_select_disabled;
	static BOOL xp_draw_3D_bitmaps;
	static BOOL hicolor_bitmaps;
	static BOOL xp_space_accelerators;
	static BOOL original_space_accelerators;
	CImageList *checkmaps;
	BOOL checkmapsshare;
	int m_selectcheck;
	int m_unselectcheck;
	BOOL m_bDynIcons;
	BOOL m_loadmenu;
}; 

#endif

//*************************************************************************
