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

#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRlePropertyItem.h"
#include "ArxRleInPlaceEditString.h"
#include "ArxRleInPlaceControl.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItem

IMPLEMENT_DYNAMIC(ArxRlePropertyItem, CObject)


ArxRlePropertyItem::ArxRlePropertyItem(LPCTSTR pStrName)
{
	m_strName = pStrName;
	m_bEnabled = true;
	m_nPropertyID = 0;
}

ArxRlePropertyItem::ArxRlePropertyItem(int val)
{
	m_strName = ToString(val,0);
	m_bEnabled = true;
	m_nPropertyID = 0;
}

ArxRlePropertyItem::ArxRlePropertyItem(long val)
{
	m_strName = ToString(val,0);
	m_bEnabled = true;
	m_nPropertyID = 0;
}

ArxRlePropertyItem::ArxRlePropertyItem(double val)
{
	m_strName = ToString(val);
	m_bEnabled = true;
	m_nPropertyID = 0;
}

ArxRlePropertyItem::~ArxRlePropertyItem()
{
}

const CString& ArxRlePropertyItem::GetName() const
{
	return m_strName;
}

void ArxRlePropertyItem::SetName(LPCTSTR pStrName)
{
	m_strName = pStrName;
}

bool ArxRlePropertyItem::GetEnabled() const
{
	return m_bEnabled;
}

BYTE ArxRlePropertyItem::GetPropertyID() const
{
	return m_nPropertyID;
}

void ArxRlePropertyItem::SetPropertyID(BYTE nPropertyID)
{
	m_nPropertyID = nPropertyID;
}

void ArxRlePropertyItem::DrawValue(CDC* /*pDC*/, CRect& /*rect*/)
{
}

void ArxRlePropertyItem::SetData(CWnd* /*pWndInPlaceControl*/)
{
}

bool ArxRlePropertyItem::SetEnabled(bool bEnable)
{
	bool bChanged = m_bEnabled != bEnable;
	m_bEnabled = bEnable;

	return bChanged;
}

void ArxRlePropertyItem::CreateInPlaceControl(CWnd* /*pWndParent*/, CRect& /*rect*/, CWnd*& pWndInPlaceControl)
{
	DestroyInPlaceControl(pWndInPlaceControl);
}

void ArxRlePropertyItem::DestroyInPlaceControl(CWnd*& pWndInPlaceControl)
{
	if(pWndInPlaceControl != NULL)
	{
		delete pWndInPlaceControl;
		pWndInPlaceControl = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemCategory

IMPLEMENT_DYNAMIC(ArxRlePropertyItemCategory, ArxRlePropertyItem)


ArxRlePropertyItemCategory::ArxRlePropertyItemCategory(LPCTSTR pStrName)
: ArxRlePropertyItem(pStrName)
{
	m_bChildrenVisible = false;
}

ArxRlePropertyItemCategory::~ArxRlePropertyItemCategory()
{
}

ArxRleListPropertyItems* ArxRlePropertyItemCategory::GetListPropertyItems()
{
	return &m_listPropertyItems;
}

void ArxRlePropertyItemCategory::AddPropertyItem(ArxRlePropertyItem* pPropertyItem)
{
	m_listPropertyItems.AddTail(pPropertyItem);
}

bool ArxRlePropertyItemCategory::GetChildrenVisible() const
{
	return m_bChildrenVisible;
}

void ArxRlePropertyItemCategory::SetChildrenVisible(bool bVisible)
{
	m_bChildrenVisible = bVisible;
}

int ArxRlePropertyItemCategory::GetNumberItems() const
{
	return m_listPropertyItems.GetCount();
}

POSITION ArxRlePropertyItemCategory::GetHeadPosition() const
{
	return m_listPropertyItems.GetHeadPosition();
}

ArxRlePropertyItem* ArxRlePropertyItemCategory::GetNext(POSITION& rPosition) const
{	
	return m_listPropertyItems.GetNext(rPosition);
}

int ArxRlePropertyItemCategory::GetNumberEnabledItems() const
{
	int nNumberEnabledItems = 0;
	POSITION pos = m_listPropertyItems.GetHeadPosition();

	while(pos != NULL)
	{
		if(m_listPropertyItems.GetNext(pos)->GetEnabled())
			nNumberEnabledItems++;
	}

	return nNumberEnabledItems;
}

ArxRlePropertyItem* ArxRlePropertyItemCategory::GetPropertyItem(int nPropertyID)
{
	POSITION pos = m_listPropertyItems.GetHeadPosition();

	while(pos != NULL)
	{
		ArxRlePropertyItem* pPropertyItem = m_listPropertyItems.GetNext(pos);

		if(pPropertyItem->GetPropertyID() == nPropertyID)
			return pPropertyItem;
	}

	return NULL;
}


/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemString

IMPLEMENT_DYNAMIC(ArxRlePropertyItemString, ArxRlePropertyItem)


ArxRlePropertyItemString::ArxRlePropertyItemString(LPCTSTR pStrName)
: ArxRlePropertyItem(pStrName)
{
}

ArxRlePropertyItemString::~ArxRlePropertyItemString()
{
}

const CString& ArxRlePropertyItemString::GetData() const
{
	return m_strText;
}

void ArxRlePropertyItemString::SetData(const CString& strText)
{
	m_strText = strText;
}

void ArxRlePropertyItemString::DrawValue(CDC* pDC, CRect& rect)
{
	pDC->DrawText(m_strText, &rect, DT_SINGLELINE|DT_VCENTER);
}

void ArxRlePropertyItemString::CreateInPlaceControl(CWnd* pWndParent, CRect& rect, CWnd*& pWndInPlaceControl)
{
	if(pWndInPlaceControl != NULL && pWndInPlaceControl->IsKindOf(RUNTIME_CLASS(ArxRleInPlaceEditString)))
		((ArxRleInPlaceEditString*)pWndInPlaceControl)->MoveControl(rect);
	else	
	{
		DestroyInPlaceControl(pWndInPlaceControl);

		pWndInPlaceControl = ArxRleInPlaceEditString::CreateInPlaceEditString(m_strText, pWndParent, rect);
	}

	((ArxRleInPlaceEditString*)pWndInPlaceControl)->SetText(m_strText);
}

void ArxRlePropertyItemString::SetData(CWnd* pWndInPlaceControl)
{
	pWndInPlaceControl->GetWindowText(m_strText);
}

/////////////////////////////////////////////////////////////////////////////
// ArxRlePropertyItemList

IMPLEMENT_DYNAMIC(ArxRlePropertyItemList, ArxRlePropertyItem)


ArxRlePropertyItemList::ArxRlePropertyItemList(LPCTSTR pStrName)
: ArxRlePropertyItem(pStrName)
{
	m_nItem = 0;
}

ArxRlePropertyItemList::~ArxRlePropertyItemList()
{
}

void ArxRlePropertyItemList::GetData(bool& nItem) const
{
	nItem = m_nItem;
}

LPCTSTR ArxRlePropertyItemList::GetItemData(int /*nItem*/) const
{
	return NULL;
}

void ArxRlePropertyItemList::DrawValue(CDC* pDC, CRect& rect)
{
	pDC->DrawText(GetItemData(m_nItem), -1, &rect, DT_SINGLELINE|DT_VCENTER);
}

void ArxRlePropertyItemList::CreateInPlaceControl(CWnd* pWndParent, CRect& rect, CWnd*& pWndInPlaceControl)
{
	if(pWndInPlaceControl != NULL && pWndInPlaceControl->IsKindOf(RUNTIME_CLASS(ArxRleInPlaceComboBox)))
	{
		((ArxRleInPlaceComboBox*)pWndInPlaceControl)->MoveControl(rect);
		((ArxRleInPlaceComboBox*)pWndInPlaceControl)->ResetContent();
	}
	else
	{
		DestroyInPlaceControl(pWndInPlaceControl);
		
		pWndInPlaceControl = (CWnd*)ArxRleInPlaceComboBox::CreateInPlaceComboBox(pWndParent, rect);
	}

	SetItemListData((ArxRleInPlaceComboBox*)pWndInPlaceControl);
	((ArxRleInPlaceComboBox*)pWndInPlaceControl)->SetCurSel(m_nItem, false);
	((ArxRleInPlaceComboBox*)pWndInPlaceControl)->ResetListBoxHeight();
}

void ArxRlePropertyItemList::SetData(CWnd* pWndInPlaceControl)
{
	m_nItem = ((ArxRleInPlaceComboBox*)pWndInPlaceControl)->GetCurrentSelection();
}

void ArxRlePropertyItemList::SetItemListData(ArxRleInPlaceComboBox* pWndInPlaceControl)
{
	LPCTSTR pStrText;

	for(int i = 0; (pStrText = GetItemData(i)) != NULL; i++)
		pWndInPlaceControl->AddString(pStrText);
}