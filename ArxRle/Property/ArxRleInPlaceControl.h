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

#ifndef ARXRLE_INPLACE_CONTROL_H
#define ARXRLE_INPLACE_CONTROL_H

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceEdit
class ArxRleInPlaceEdit : public CAdUiEdit
{
public:
	ArxRleInPlaceEdit();
	ArxRleInPlaceEdit(const CString& srtInitText);
	virtual ~ArxRleInPlaceEdit();

	void SetText(const CString& strText);
	CString GetText();

	virtual void ProcessData();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRleInPlaceEdit)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()

private:
	CString m_strInitText;
};

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceListBox

class ArxRleInPlaceListBox : public CAdUiListBox
{
	ArxRleInPlaceListBox(const ArxRleInPlaceListBox& d);
	ArxRleInPlaceListBox& operator=(const ArxRleInPlaceListBox& d);

public:
	ArxRleInPlaceListBox();
	virtual ~ArxRleInPlaceListBox();

protected:
	void ProcessSelected(bool bProcess = true);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceListCtrl

class ArxRleInPlaceListCtrl : public CListCtrl
{
	ArxRleInPlaceListCtrl(const ArxRleInPlaceListCtrl& d);
	ArxRleInPlaceListCtrl& operator=(const ArxRleInPlaceListCtrl& d);

public:
	ArxRleInPlaceListCtrl();
	virtual ~ArxRleInPlaceListCtrl();

	int GetCount() const;
	void GetText(int nIndex, CString& strText) const;

	int SetCurSel(int nSelect);	
	int AddString(LPCTSTR pStrText);

	void ResetContent();

protected:
	void ProcessSelected();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// ArxRleInPlaceComboBox

class ArxRleInPlaceComboBox : public CWnd
{
	ArxRleInPlaceComboBox(const ArxRleInPlaceComboBox& d);
	ArxRleInPlaceComboBox operator=(const ArxRleInPlaceComboBox& d);

protected:
	DECLARE_DYNAMIC(ArxRleInPlaceComboBox)

public:
	ArxRleInPlaceComboBox();
	virtual ~ArxRleInPlaceComboBox();

public:
	int GetCurrentSelection() const;
	DWORD GetDWordData() const;
	CString GetTextData() const;

public:
	static ArxRleInPlaceComboBox* CreateInPlaceComboBox(CWnd* pWndParent, CRect& rect);

	int SetCurSel(int nSelect, bool bSendSetData = true);
	int AddString(LPCTSTR pStrText, DWORD nData = 0);

	void ResetContent();
	void ResetListBoxHeight();

	void MoveControl(CRect& rect);

private:
	void SetCurSelToEdit(int nSelect);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnSelectionOk(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSelectionCancel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNewSelection(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

	void HideListBox();

private:
	static int m_nButtonDx;

	int m_nCurrentSelection;

	ArxRleInPlaceEdit m_wndEdit;
	ArxRleInPlaceListBox m_wndList;
};

#endif // ARXRLE_INPLACE_CONTROL_H
