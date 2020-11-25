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

#ifndef ARXRLE_PROPERTY_ITEM_H
#define ARXRLE_PROPERTY_ITEM_H

#include "ArxRleTypedPtrList.h"
#include "ArxRleSmartString.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItem

class ArxRlePropertyItem : public CObject
{
	ArxRlePropertyItem(const ArxRlePropertyItem& d);
	ArxRlePropertyItem& operator=(const ArxRlePropertyItem& d);

protected:
	DECLARE_DYNAMIC(ArxRlePropertyItem)

public:
	ArxRlePropertyItem(LPCTSTR pStrName = NULL);
	ArxRlePropertyItem(int val);
	ArxRlePropertyItem(long val);
	ArxRlePropertyItem(double val);
	virtual ~ArxRlePropertyItem();

	// Attributes
	const CString& GetName() const;
	void SetName(LPCTSTR pStrName);

	bool GetEnabled() const;
	bool SetEnabled(bool bEnable = true);

	BYTE GetPropertyID() const;
	void SetPropertyID(BYTE nPropertyID);

	// Operations
	virtual void DrawValue(CDC* pDC, CRect& rect);
	virtual void CreateInPlaceControl(CWnd* pWndParent, CRect& rect, CWnd*& pWndInPlaceControl);
	virtual void SetData(CWnd* pWndInPlaceControl);

protected:
	void DestroyInPlaceControl(CWnd*& pWndInPlaceControl);

	// Data
private:
	CString m_strName;
	bool m_bEnabled;
	BYTE m_nPropertyID;
};

/////////////////////////////////////////////////////////////////////////////
// ArxRleListPropertyItems

typedef ArxRleTypedPtrList<CObList, ArxRlePropertyItem*> ArxRleListPropertyItems;

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemCategory

class ArxRlePropertyItemCategory : public ArxRlePropertyItem
{
	ArxRlePropertyItemCategory(const ArxRlePropertyItemCategory& d);
	ArxRlePropertyItemCategory& operator=(const ArxRlePropertyItemCategory& d);

protected:
	DECLARE_DYNAMIC(ArxRlePropertyItemCategory)

public:
	ArxRlePropertyItemCategory(LPCTSTR pStrName = NULL);
	virtual ~ArxRlePropertyItemCategory();

	// Attributes
	void AddPropertyItem(ArxRlePropertyItem* pPropertyItem);

	bool GetChildrenVisible() const;
	void SetChildrenVisible(bool bVisible = true);

	ArxRleListPropertyItems* GetListPropertyItems();

	int GetNumberItems() const;
	int GetNumberEnabledItems() const;

	POSITION GetHeadPosition() const;

	// Operations
	ArxRlePropertyItem* GetNext(POSITION& rPosition) const;
	ArxRlePropertyItem* GetPropertyItem(int nPropertyID);

	// Data
private:
	ArxRleListPropertyItems m_listPropertyItems;
	bool m_bChildrenVisible;
};

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemString

class ArxRlePropertyItemString : public ArxRlePropertyItem
{
	ArxRlePropertyItemString(const ArxRlePropertyItemString& d);
	ArxRlePropertyItemString& operator=(const ArxRlePropertyItemString& d);

protected:
	DECLARE_DYNAMIC(ArxRlePropertyItemString)

public:
	ArxRlePropertyItemString(LPCTSTR pStrName = NULL);
	virtual ~ArxRlePropertyItemString();

	// Attributes
	const CString& GetData() const;
	void SetData(const CString& strText);

	// Operations
	virtual void DrawValue(CDC* pDC, CRect& rect);
	virtual void CreateInPlaceControl(CWnd* pWndParent, CRect& rect, CWnd*& pWndInPlaceControl);
	virtual void SetData(CWnd* pWndInPlaceControl);

	// Data
private:
	CString m_strText;
};

class ArxRleInPlaceComboBox;

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemList

class ArxRlePropertyItemList : public ArxRlePropertyItem
{
	ArxRlePropertyItemList(const ArxRlePropertyItemList& d);
	ArxRlePropertyItemList& operator=(const ArxRlePropertyItemList& d);

protected:
	DECLARE_DYNAMIC(ArxRlePropertyItemList)

public:
	ArxRlePropertyItemList(LPCTSTR pStrName = NULL);
	virtual ~ArxRlePropertyItemList();

	// Attributes
	template <class ctype>
	void GetData(ctype& nItem) const
	{
		nItem = ctype(m_nItem);
	}

	void GetData(bool& nItem) const;

	template <class ctype>
	void SetData(ctype nItem)
	{
		m_nItem = int(nItem);
	}

	virtual LPCTSTR GetItemData(int nItem) const;

	// Operations
	virtual void DrawValue(CDC* pDC, CRect& rect);
	virtual void CreateInPlaceControl(CWnd* pWndParent, CRect& rect, CWnd*& pWndInPlaceControl);
	virtual void SetData(CWnd* pWndInPlaceControl);

	void SetItemListData(ArxRleInPlaceComboBox* pWndInPlaceControl);

	// Data
private:
	int m_nItem;
};

/////////////////////////////////////////////////////////////////////////////

#define BEGIN_LIST_ITEM_DATA_TYPE(new_class) \
class new_class : public ArxRlePropertyItemList \
{ \
	new_class(const new_class& d); \
	new_class& operator=(const new_class& d); \
public: \
	new_class(LPCTSTR pStrName = NULL) : ArxRlePropertyItemList(pStrName) {}; \
	virtual ~new_class() {}; \
	virtual LPCTSTR GetItemData(int nItem) const; \
private: \
	static ArxRleSmartString m_data[]; \
}; \
ArxRleSmartString new_class::m_data[] = { 
#define ID_STRING_ITEM_DATA(idString) \
	ArxRleSmartString(UINT(idString))
#define LPCTSTR_STRING_ITEM_DATA(string) \
	ArxRleSmartString(LPCTSTR(string))
#define END_LIST_ITEM_DATA_TYPE(new_class) \
}; \
LPCTSTR new_class::GetItemData(int nItem) const \
{ \
	return nItem < sizeof(new_class::m_data)/sizeof(ArxRleSmartString) ? LPCTSTR(m_data[nItem]) : NULL; \
}

/////////////////////////////////////////////////////////////////////////////

#endif // ARXRLE_PROPERTY_ITEM_H