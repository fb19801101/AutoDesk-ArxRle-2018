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

#ifndef ARXRLE_TABCTRL_H
#define ARXRLE_TABCTRL_H

// ArxRleTablCtrl

enum ETabOrientation
{	
	e_tabTop=0,
	e_tabBottom,
	e_tabLeft,
	e_tabRight,
	e_tabNOF,
};

class ArxRleTablCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(ArxRleTablCtrl)

public:
	ArxRleTablCtrl();
	virtual ~ArxRleTablCtrl();

	void AddDlg(CDialog* pDlg, UINT nID);
	void InitTab();
	void InitImageList(UINT nBitmapID);

	inline void SetBorderColor(COLORREF clrBKGrnd) {m_clrBKGrnd = clrBKGrnd;}
	inline void SetTextColor(COLORREF clrText) { m_clrText = clrText; }
	inline void SetTextHeidght(int nTextHeight) { m_nTextHeight = nTextHeight; }
	inline void SetTextWidth(int nTextWidth) { m_nTextWidth = nTextWidth; }
	inline void SetTextItalic(BOOL bItalic) { m_bItalic = bItalic; }
	inline void SetTextUnderline(BOOL bUnderline) { m_bUnderline = bUnderline; }
	inline void SetTextWeight(int nTextWeight) { m_nTextWeight = nTextWeight; }
	inline void SetTextStyle(CString strTextStyle) { m_strTextStyle = strTextStyle; }
	inline COLORREF GetBorderColor() { return m_clrBKGrnd;}
	inline COLORREF GetTextColor() { return m_clrText; }
	inline int GetTextHeidght() { return m_nTextHeight; }
	inline int GetTextWidth() { return m_nTextWidth; }
	inline BOOL GetTextItalic() { return m_bItalic; }
	inline BOOL GetTextUnderline() { return m_bUnderline; }
	inline int GetTextWeight() { return m_nTextWeight; }
	inline CString GetTextStyle() { return m_strTextStyle; }

protected:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext);
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

	void DrawThemesXpTabItem(CDC* pDC, int ixItem, const CRect& rcItem, UINT uiFlag);
	void DrawTabItem(CDC* pDC, int ixItem, const CRect& rcItemC, UINT uiFlags);

public:
	COLORREF m_clrBKGrnd;
	COLORREF m_clrText;
	int m_nTextHeight;
	int m_nTextWidth;
	BOOL m_bItalic;
	BOOL m_bUnderline;
	int m_nTextWeight;
	CString m_strTextStyle;
	int m_CurrentTabIndex;
	vector<CDialog*> m_vecTabPage;
};

#endif //ARXRLE_TABCTRL_H