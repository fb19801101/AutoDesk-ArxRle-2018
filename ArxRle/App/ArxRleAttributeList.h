// ArxRleAttributeList.h : header file
//

#ifndef ARXRLE_ATTRIBUTELIST_H
#define ARXRLE_ATTRIBUTELIST_H

#define IDC_PROP_STATIC   50
#define IDC_PROP_COMBBOX  51
#define IDC_PROP_EDITBOX  52
#define IDC_PROP_BUTTON   53

#include "ArxRleAttributeListItem.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRleAttributeList window

class ArxRleAttributeList : public CAcUiListBox
{
// Construction
public:
	ArxRleAttributeList();
	virtual ~ArxRleAttributeList();

// Attributes
public:
	int AddPropItem(ArxRleAttributeListItem *&pItem);
	int InsertPropItem(int index, ArxRleAttributeListItem *&pItem);
	int GetCurSel();
	void SetItemHeight(double height);
	double GetItemHeight() const;
	void DelItem(int index);
	void DelItems();
	void SetGridColor(COLORREF clrGrid);
	COLORREF GetGridColor() const;

	int (*fnPtr)(int);

	// Generated message function
protected:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();

	// Generated message map function
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnLbnSelchange();
	afx_msg void OnSelchangeCmbBox();
	afx_msg void OnChangeEditBox();
	afx_msg void OnClickButton();

	afx_msg void OnKillfocusStatic();
	afx_msg void OnKillfocusCmbBox();
	afx_msg void OnKillfocusEditBox();


	DECLARE_MESSAGE_MAP();

	void InvertLine(CDC* pDC, CPoint ptFrom, CPoint ptTo);
	void DisplayButton(CRect rcBtn, int itemType);

private:
	CStatic* m_pStatic;
	CAcUiComboBox* m_pComboBox;
	CAcUiSymbolComboBox* m_pSymbolComboBox;
	CAcUiColorComboBox* m_pColorComboBox;
	CAcUiLineTypeComboBox* m_pLineTypeComboBox;
	CAcUiLineWeightComboBox* m_pLineWeightComboBox;
	CAcUiEdit* m_pEditBox;
	CButton* m_pButton;

	CFont* m_ftSerif8Font;
	ArxRleAttributeListItems m_vecItems;

	int m_curSel, m_prevSel,m_itemCount;
	int m_nDivider;
	int m_nDivTop;
	int m_nDivBtm;
	int m_nOldDivX;
	int m_nLastBox;
	int m_nItemHeight;
	BOOL m_bTracking;
	BOOL m_bDivIsSet;
	BOOL m_bItemActive;
	COLORREF m_clrGrid;
	HCURSOR m_hCursorArrow;
	HCURSOR m_hCursorSize;
};

#endif //ARXRLE_ATTRIBUTELIST_H

