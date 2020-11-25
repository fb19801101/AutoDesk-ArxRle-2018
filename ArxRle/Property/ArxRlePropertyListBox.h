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

#ifndef ARXRLE_PROPERTY_LISTBOX_H
#define ARXRLE_PROPERTY_LISTBOX_H

#include "ArxRlePropertyItem.h"

class ArxRlePropertyItemManager;

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyListBox

class ArxRlePropertyListBox : public CAdUiListBox
{
	ArxRlePropertyListBox(const ArxRlePropertyListBox& d);
	ArxRlePropertyListBox& operator=(const ArxRlePropertyListBox& d);

public:
	ArxRlePropertyListBox();

	// Attributes
	void SetPropertyItemManager(ArxRlePropertyItemManager* pPropertyItemManager);
	ArxRlePropertyItem* GetPropertyItem(int nIndex);

	// Operations
	void InsertPropertyItem(ArxRlePropertyItem* pPropertyItem, int nIndex = 0);
	void ResetContent();
	void ShowInPlaceControl(bool bShow = true);
	void Refresh();

protected:
	void DoCollapse(ArxRlePropertyItemCategory* pPropertyItemTab, int nItem);
	void DoExpand(ArxRlePropertyItemCategory* pPropertyItemTab, int& nItem);

	void DoCollapseExpand(int nItem, ArxRlePropertyItem* pPropertyItem = NULL);

	void GetItemValueRect(CRect& rect);
	bool SetCurrentData();

	void NoInPlaceControl();

	bool LookupPropertyItem(char nStartChar);
	int FindPropertyItem(char nStartChar, int nFromIndex, int nCount);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRlePropertyListBox)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~ArxRlePropertyListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(ArxRlePropertyListBox)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSelChange();
	afx_msg LRESULT OnSetData(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	// Data
private:
	int m_nSelectedItem;
	CWnd* m_pWndInPlaceControl;

	ArxRlePropertyItemManager* m_pPropertyItemManager;

	friend class ArxRlePropertyItemManager;
};

inline ArxRlePropertyListBox::~ArxRlePropertyListBox()
{
	delete m_pWndInPlaceControl;
}

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemManager

class ArxRlePropertyItemManager
{
	ArxRlePropertyItemManager(const ArxRlePropertyItemManager& d);
	ArxRlePropertyItemManager& operator=(const ArxRlePropertyItemManager& d);

public:
	ArxRlePropertyItemManager();
	~ArxRlePropertyItemManager();

	// Attributes
	ArxRlePropertyItemCategory* GetCategoryTab(int nIndex) const;

	// Operations
	ArxRlePropertyItemCategory* AddNewTab(LPCTSTR pStrTabName);
	void InitControl(ArxRlePropertyListBox* pWndPropertyListCtrl);

	virtual void OnDataChanged(ArxRlePropertyItem* pPropertyItem, ArxRlePropertyListBox* pWndPropertyListCtrl, int nIndex);
	
	virtual bool SetData(const CObject* pData) = 0;
	virtual bool GetData(CObject* pData) const = 0;

	// Data
protected:
	ArxRleTypedPtrList<CObList, ArxRlePropertyItemCategory*> m_listPropertyItemTabs;
};

/////////////////////////////////////////////////////////////////////////////
#define BEGIN_PROPERTY_TAB_IDNAME(idTabName, enabled) \
{ \
	ArxRlePropertyItemCategory* pNewTab = AddNewTab(LoadString(idTabName)); \
	pNewTab->SetEnabled(enabled); \
	ArxRlePropertyItem* pPropertyItem;
#define PROPERTY_ITEM_IDNAME(id, class_name, idItemName, enabled) \
	pPropertyItem = new class_name(LoadString(idItemName)); \
	pPropertyItem->SetEnabled(enabled); \
	pPropertyItem->SetPropertyID(id);\
	pNewTab->AddPropertyItem(pPropertyItem);

#define BEGIN_PROPERTY_TAB(tabName, enabled) \
{ \
	ArxRlePropertyItemCategory* pNewTab = AddNewTab(tabName); \
	pNewTab->SetEnabled(enabled); \
	ArxRlePropertyItem* pPropertyItem;
#define PROPERTY_ITEM(id, class_name, itemName, enabled) \
	pPropertyItem = new class_name(itemName); \
	pPropertyItem->SetEnabled(enabled); \
	pPropertyItem->SetPropertyID(id);\
	pNewTab->AddPropertyItem(pPropertyItem);
#define END_PROPERTY_TAB() \
}

#define BEGIN_ITERATE_PROPERTY_ITEMS() \
	POSITION pos = m_listPropertyItemTabs.GetHeadPosition(); \
	while(pos != NULL) \
	{ \
		ArxRlePropertyItemCategory* pPropertyItemTab = m_listPropertyItemTabs.GetNext(pos); \
		POSITION posItem = pPropertyItemTab->GetHeadPosition(); \
		while(posItem != NULL) \
		{ \
			ArxRlePropertyItem* pPropertyItem = pPropertyItemTab->GetNext(posItem); \
			switch(pPropertyItem->GetPropertyID()) \
			{
#define SET_ITEM_STRING(id, val) \
				case id: \
					static_cast<ArxRlePropertyItemString*>(pPropertyItem)->SetData(val); \
					break;
#define GET_ITEM_STRING(id, val) \
				case id: \
					val = static_cast<ArxRlePropertyItemString*>(pPropertyItem)->GetData(); \
					break;
#define SET_ITEM_INT(id, val) \
				case id: \
				static_cast<ArxRlePropertyItemString*>(pPropertyItem)->SetData(ToString(val,0)); \
				break;
#define GET_ITEM_INT(id, val) \
				case id: \
				val = _tstoi(static_cast<ArxRlePropertyItemString*>(pPropertyItem)->GetData()); \
				break;
#define SET_ITEM_LONG(id, val) \
				case id: \
				static_cast<ArxRlePropertyItemString*>(pPropertyItem)->SetData(ToString(val,0)); \
				break;
#define GET_ITEM_LONG(id, val) \
				case id: \
				val = _tstoi(static_cast<ArxRlePropertyItemString*>(pPropertyItem)->GetData()); \
				break;
#define SET_ITEM_DOUBLE(id, val) \
				case id: \
				static_cast<ArxRlePropertyItemString*>(pPropertyItem)->SetData(ToString(val)); \
				break;
#define GET_ITEM_DOUBLE(id, val) \
				case id: \
				val = _tstof(static_cast<ArxRlePropertyItemString*>(pPropertyItem)->GetData()); \
				break;
#define SET_ITEM_LIST(id, item) \
				case id: \
				static_cast<ArxRlePropertyItemList*>(pPropertyItem)->SetData(item); \
					break;
#define GET_ITEM_LIST(id, item) \
				case id: \
					static_cast<ArxRlePropertyItemList*>(pPropertyItem)->GetData(item); \
					break;
#define END_ITERATE_PROPERTY_ITEMS() \
				default: ; \
			} \
		} \
	}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemManagerAdaptable

class ArxRlePropertyItemManagerAdaptable : public ArxRlePropertyItemManager
{
	ArxRlePropertyItemManagerAdaptable(const ArxRlePropertyItemManagerAdaptable& d);
	ArxRlePropertyItemManagerAdaptable& operator=(const ArxRlePropertyItemManagerAdaptable& d);

public:
	ArxRlePropertyItemManagerAdaptable();
	~ArxRlePropertyItemManagerAdaptable();

	// Operations
	void CheckState(ArxRlePropertyListBox* pWndPropertyListCtrl, int nFromControlIndex, BYTE nFromPropertyItemID);
};

inline ArxRlePropertyItemManagerAdaptable::ArxRlePropertyItemManagerAdaptable()
{
}

inline ArxRlePropertyItemManagerAdaptable::~ArxRlePropertyItemManagerAdaptable()
{
}

#endif // ARXRLE_PROPERTY_LISTBOX_H
