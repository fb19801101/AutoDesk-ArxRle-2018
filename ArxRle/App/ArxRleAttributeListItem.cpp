// ArxRleAttributeListItem.cpp : implementation file
//

#include "stdafx.h"
#include "ArxRleAttributeListItem.h"
#include "DbEntity/ArxRleEntityClass.h"

/////////////////////////////////////////////////////////////////////////////
//ArxRleAttributeList Item
/////////////////////////////////////////////////////////////////////////////
ArxRleAttributeListItem::ArxRleAttributeListItem(CString curKey, CString curValue, int itemType, CString cmbItems,
												 long ftWeight, long ftHeight, long ftWidth, BOOL ftItalic, CString ftName, COLORREF ftColor, int ftKeyVal,
												 BOOL isExpand, int idxExpand, CRect rcExpand,
												 COLORREF bkKeyColor, COLORREF bkValColor, COLORREF txtKeyColor, COLORREF txtValColor)
{
	m_idxItem = -1;

	m_curKey = curKey;
	m_curValue = curValue;
	m_itemType = itemType;
	m_cmbItems = cmbItems;
	m_sufName = cmbItems;

	m_ftWeight = ftWeight;
	m_ftHeight = ftHeight;
	m_ftWidth = ftWidth;
	m_ftItalic = ftItalic;
	m_ftName = ftName;
	m_ftColor = ftColor;
	m_ftKeyVal = ftKeyVal;

	m_isExpand = isExpand;
	m_idxExpand = idxExpand;
	m_rcExpand = rcExpand;

	m_bkKeyColor = bkKeyColor;
	m_bkValColor = bkValColor;
	m_txtKeyColor = txtKeyColor;
	m_txtValColor = txtValColor;
};

ArxRleAttributeListItem::ArxRleAttributeListItem(const ArxRleAttributeListItem &item)
{
	m_idxItem = item.m_idxItem;

	m_curKey = item.m_curKey;
	m_curValue = item.m_curValue;
	m_itemType = item.m_itemType;
	m_cmbItems = item.m_cmbItems;
	m_sufName = item.m_cmbItems;

	m_ftWeight = item.m_ftWeight;
	m_ftHeight = item.m_ftHeight;
	m_ftWidth = item.m_ftWidth;
	m_ftItalic = item.m_ftItalic;
	m_ftName = item.m_ftName;
	m_ftColor = item.m_ftColor;
	m_ftKeyVal = item.m_ftKeyVal;

	m_isExpand = item.m_isExpand;
	m_idxExpand = item.m_idxExpand;
	m_rcExpand = item.m_rcExpand;

	m_bkKeyColor = item.m_bkKeyColor;
	m_bkValColor = item.m_bkValColor;
	m_txtKeyColor = item.m_txtKeyColor;
	m_txtValColor = item.m_txtValColor;

	m_objId = item.m_objId;
};

ArxRleAttributeListItem& ArxRleAttributeListItem::operator=(const ArxRleAttributeListItem &item)
{
	m_idxItem = item.m_idxItem;

	m_curKey = item.m_curKey;
	m_curValue = item.m_curValue;
	m_itemType = item.m_itemType;
	m_cmbItems = item.m_cmbItems;
	m_sufName = item.m_cmbItems;

	m_ftWeight = item.m_ftWeight;
	m_ftHeight = item.m_ftHeight;
	m_ftWidth = item.m_ftWidth;
	m_ftItalic = item.m_ftItalic;
	m_ftName = item.m_ftName;
	m_ftColor = item.m_ftColor;
	m_ftKeyVal = item.m_ftKeyVal;

	m_isExpand = item.m_isExpand;
	m_idxExpand = item.m_idxExpand;
	m_rcExpand = item.m_rcExpand;

	m_bkKeyColor = item.m_bkKeyColor;
	m_bkValColor = item.m_bkValColor;
	m_txtKeyColor = item.m_txtKeyColor;
	m_txtValColor = item.m_txtValColor;

	m_objId = item.m_objId;
	return *this;
};

bool ArxRleAttributeListItem::operator<(const ArxRleAttributeListItem &item) const
{
	return m_idxItem < item.m_idxItem;
};

bool ArxRleAttributeListItem::operator==(const ArxRleAttributeListItem &item) const
{
	return m_idxItem == item.m_idxItem;
};

bool ArxRleAttributeListItem::compare(const ArxRleAttributeListItem* first,const ArxRleAttributeListItem* second)
{
	return first->m_idxItem < second->m_idxItem;
};

/////////////////////////////////////////////////////////////////////////////
//ArxRleAttributeList Items
/////////////////////////////////////////////////////////////////////////////
ArxRleAttributeListItems::ArxRleAttributeListItems()
{
	m_vecItems.clear();
	m_itemCount = 0;
	m_nCItems = 0;
}

ArxRleAttributeListItems::~ArxRleAttributeListItems()
{
	m_vecItems.clear();
	m_itemCount = 0;
	m_nCItems = 0;
}

ArxRleAttributeListItems::ArxRleAttributeListItems(const ArxRleAttributeListItems &items)
{
	m_itemCount = items.GetItemCount();
	m_vecItems.clear();
	for(int i=0; i<m_itemCount; i++)
		m_vecItems.push_back(items[i]);
}

ArxRleAttributeListItems& ArxRleAttributeListItems::operator=(const ArxRleAttributeListItems &items)
{
	m_itemCount = items.GetItemCount();
	m_vecItems.clear();
	for(int i=0; i<m_itemCount; i++)
		m_vecItems.push_back(items[i]);
	return *this;
}

ArxRleAttributeListItem* ArxRleAttributeListItems::operator[](int index) const
{
	return m_vecItems[index];
}

void ArxRleAttributeListItems::AddComboValue(CString propName, CString curValue, CString cmbItems)
{
	AddItem(propName, curValue, PIT_COMBO, cmbItems);
}

void ArxRleAttributeListItems::AddEditValue(CString propName, CString curValue)
{
	AddItem(propName, curValue, PIT_EDIT);
}

void ArxRleAttributeListItems::AddLayerValue(CString propName, CString curValue)
{
	AddItem(propName, curValue, PIT_LAYER);
}

void ArxRleAttributeListItems::AddTextStyleValue(CString propName, CString curValue)
{
	AddItem(propName, curValue, PIT_TEXTSTYLE);
}

void ArxRleAttributeListItems::AddDimStyleValue(CString propName, CString curValue)
{
	AddItem(propName, curValue, PIT_DIMSTYLE);
}

void ArxRleAttributeListItems::AddWorkStyleValue(CString propName, CString curValue)
{
	AddItem(propName, curValue, PIT_WORKSTYLE);
}

void ArxRleAttributeListItems::AddColorValue(CString propName, COLORREF txtValColor)
{
	AddItem(propName, "", PIT_COLOR, "", RGB(238,238,238),RGB(255,255,255),RGB(0,0,0),txtValColor);
}

void ArxRleAttributeListItems::AddLineTypeValue(CString propName, CString curValue)
{
	AddItem(propName, curValue, PIT_LINETYPE);
}

void ArxRleAttributeListItems::AddLineWeightValue(CString propName, int curValue)
{
	AddItem(propName, ToString(curValue,0), PIT_LINEWEIGHT);
}

void ArxRleAttributeListItems::AddFontValue(CString propName, CString curValue)
{
	AddItem(propName, curValue, PIT_FONT);
}

void ArxRleAttributeListItems::AddFileValue(CString propName, CString curValue, CString sufName)
{
	AddItem(propName, curValue, PIT_FILE, sufName);
}

void ArxRleAttributeListItems::AddPathValue(CString propName, CString curValue)
{
	AddItem(propName, curValue, PIT_PATH);
}

void ArxRleAttributeListItems::AddPointValue(CString propName, CString curValue)
{
	AddItem(propName, curValue, PIT_POINT);
}

void ArxRleAttributeListItems::AddSeparator(CString propName)
{
	int index = AddItem(propName, L"", PIT_SEPARATOR, L"",
		RGB(168,168,168), RGB(238,238,238), RGB(0,0,0), RGB(0,0,0));
	SetFont(index, 900, 12, 0, FALSE, L"ºÚÌå");
}

void ArxRleAttributeListItems::InsertComboValue(int index, CString propName, CString curValue, CString cmbItems)
{
	InsertItem(index, propName, curValue, PIT_COMBO, cmbItems);
}

void ArxRleAttributeListItems::InsertEditValue(int index, CString propName, CString curValue)
{
	InsertItem(index, propName, curValue, PIT_EDIT);
}

void ArxRleAttributeListItems::InsertLayerValue(int index, CString propName, CString curValue)
{
	InsertItem(index, propName, curValue, PIT_LAYER);
}

void ArxRleAttributeListItems::InsertTextStyleValue(int index, CString propName, CString curValue)
{
	InsertItem(index, propName, curValue, PIT_TEXTSTYLE);
}

void ArxRleAttributeListItems::InsertDimStyleValue(int index, CString propName, CString curValue)
{
	InsertItem(index, propName, curValue, PIT_DIMSTYLE);
}

void ArxRleAttributeListItems::InsertWorkStyleValue(int index, CString propName, CString curValue)
{
	InsertItem(index, propName, curValue, PIT_WORKSTYLE);
}

void ArxRleAttributeListItems::InsertColorValue(int index, CString propName, COLORREF txtValColor)
{
	InsertItem(index, m_vecItems[index]->m_curKey, "", PIT_COLOR, "", RGB(238,238,238),RGB(255,255,255),RGB(0,0,0),txtValColor);
}

void ArxRleAttributeListItems::InsertLineTypeValue(int index, CString propName, CString curValue)
{
	InsertItem(index, propName, curValue, PIT_LINETYPE);
}

void ArxRleAttributeListItems::InsertLineWeightValue(int index, CString propName, int curValue)
{
	InsertItem(index, propName, ToString(curValue,0), PIT_LINEWEIGHT);
}

void ArxRleAttributeListItems::InsertFontValue(int index, CString propName, CString curValue)
{
	InsertItem(index, propName, curValue, PIT_FONT);
}

void ArxRleAttributeListItems::InsertFileValue(int index, CString propName, CString curValue, CString sufName)
{
	InsertItem(index, propName, curValue, PIT_FILE, sufName);
}

void ArxRleAttributeListItems::InsertPathValue(int index, CString propName, CString curValue)
{
	InsertItem(index, propName, curValue, PIT_PATH);
}

void ArxRleAttributeListItems::InsertPointValue(int index, CString propName, CString curValue)
{
	InsertItem(index, propName, curValue, PIT_POINT);
}

void ArxRleAttributeListItems::InsertSeparator(int index, CString propName)
{
	InsertItem(index, propName, L"", PIT_SEPARATOR, L"",
		RGB(168,168,168), RGB(168,168,168), RGB(0,0,0), RGB(0,0,0));
}

void ArxRleAttributeListItems::SetComboValue(int index, CString curValue, CString cmbItems)
{
	SetItem(index, m_vecItems[index]->m_curKey, curValue, PIT_COMBO, cmbItems);
}

void ArxRleAttributeListItems::SetEditValue(int index, CString curValue)
{
	SetItem(index, m_vecItems[index]->m_curKey, curValue, PIT_EDIT);
}

void ArxRleAttributeListItems::SetLayerValue(int index, CString curValue)
{
	SetItem(index, m_vecItems[index]->m_curKey, curValue, PIT_LAYER);
}

void ArxRleAttributeListItems::SetTextStyleValue(int index, CString curValue)
{
	SetItem(index, m_vecItems[index]->m_curKey, curValue, PIT_TEXTSTYLE);
}

void ArxRleAttributeListItems::SetDimStyleValue(int index, CString curValue)
{
	SetItem(index, m_vecItems[index]->m_curKey, curValue, PIT_DIMSTYLE);
}

void ArxRleAttributeListItems::SetWorkStyleValue(int index, CString curValue)
{
	SetItem(index, m_vecItems[index]->m_curKey, curValue, PIT_WORKSTYLE);
}

void ArxRleAttributeListItems::SetColorValue(int index, COLORREF txtValColor)
{
	SetItem(index, m_vecItems[index]->m_curKey, "", PIT_COLOR, "", RGB(238,238,238),RGB(255,255,255),RGB(0,0,0),txtValColor);
}

void ArxRleAttributeListItems::SetLineTypeValue(int index, CString curValue)
{
	SetItem(index, m_vecItems[index]->m_curKey, curValue, PIT_LINETYPE);
}

void ArxRleAttributeListItems::SetLineWeightValue(int index, int curValue)
{
	SetItem(index, m_vecItems[index]->m_curKey, ToString(curValue,0), PIT_LINEWEIGHT);
}

void ArxRleAttributeListItems::SetFontValue(int index, CString curValue)
{
	SetItem(index, m_vecItems[index]->m_curKey, curValue, PIT_FONT);
}

void ArxRleAttributeListItems::SetFileValue(int index, CString curValue, CString sufName)
{
	SetItem(index, m_vecItems[index]->m_curKey, curValue, PIT_FILE, m_vecItems[index]->m_sufName);
}

void ArxRleAttributeListItems::SetPathValue(int index, CString curValue)
{
	SetItem(index, m_vecItems[index]->m_curKey, curValue, PIT_PATH);
}

void ArxRleAttributeListItems::SetPointValue(int index, CString curValue)
{
	SetItem(index, m_vecItems[index]->m_curKey, curValue, PIT_POINT);
}

void ArxRleAttributeListItems::SetKeyValue(int index, CString keyValue)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	pItem->m_curKey = keyValue;
}

void ArxRleAttributeListItems::SetKeyColor(int index, COLORREF bkKeyColor, COLORREF txtKeyColor)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	pItem->m_bkKeyColor = bkKeyColor;
	pItem->m_txtKeyColor = txtKeyColor;
}

void ArxRleAttributeListItems::SetValColor(int index, COLORREF bkValColor, COLORREF txtValColor)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	pItem->m_bkValColor = bkValColor;
	pItem->m_txtValColor = txtValColor;
	pItem->m_curValue.Format(L"RGB(%d,%d,%d)",GetRValue(txtValColor), GetGValue(txtValColor),GetBValue(txtValColor));
}

void ArxRleAttributeListItems::SetBkKeyColor(int index, COLORREF bkKeyColor)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	pItem->m_bkKeyColor = bkKeyColor;
}

void ArxRleAttributeListItems::SetBkValColor(int index, COLORREF bkValColor)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	pItem->m_bkValColor = bkValColor;
}

void ArxRleAttributeListItems::SetTxtKeyColor(int index, COLORREF txtKeyColor)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	pItem->m_txtKeyColor = txtKeyColor;
}

void ArxRleAttributeListItems::SetTxtValColor(int index, COLORREF txtValColor)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	pItem->m_txtValColor = txtValColor;
	pItem->m_curValue.Format(L"RGB(%d,%d,%d)",GetRValue(txtValColor), GetGValue(txtValColor),GetBValue(txtValColor));
}

void ArxRleAttributeListItems::SetCommonItems(int nCitems)
{
	m_nCItems = nCitems;
}

int ArxRleAttributeListItems::GetCommonItems() const
{
	return m_nCItems;
}

int ArxRleAttributeListItems::GetTrueIndex(int index) const
{
	int rIndex = -1-m_nCItems;
	for(int i=0; i<m_vecItems.size();i++)
	{
		if(m_vecItems[i]->m_itemType != PIT_SEPARATOR)
		{
			rIndex++;
			if(rIndex == index) return i;
		}
	}

	return index+m_nCItems;
}

CString ArxRleAttributeListItems::GetValue(int index) const
{
	return m_vecItems[GetTrueIndex(index)]->m_curValue;
}

CString ArxRleAttributeListItems::GetKeyValue(int index) const
{
	return m_vecItems[index]->m_curKey;
}

CString ArxRleAttributeListItems::GetValValue(int index) const
{
	return m_vecItems[index]->m_curValue;
}

void ArxRleAttributeListItems::GetKeyColor(int index, COLORREF &bkKeyColor, COLORREF &txtKeyColor)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	bkKeyColor = pItem->m_bkKeyColor;
	txtKeyColor = pItem->m_txtKeyColor;
}

void ArxRleAttributeListItems::GetValColor(int index, COLORREF &bkValColor, COLORREF &txtValColor)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	bkValColor = pItem->m_bkValColor;
	txtValColor = pItem->m_txtValColor;
}

COLORREF ArxRleAttributeListItems::GetBkKeyColor(int index) const
{
	ArxRleAttributeListItem *pItem = m_vecItems[index];
	return pItem->m_bkKeyColor;
}

COLORREF ArxRleAttributeListItems::GetBkValColor(int index) const
{
	ArxRleAttributeListItem *pItem = m_vecItems[index];
	return pItem->m_bkValColor;
}

COLORREF ArxRleAttributeListItems::GetTxtKeyColor(int index) const
{
	ArxRleAttributeListItem *pItem = m_vecItems[index];
	return pItem->m_txtKeyColor;
}

COLORREF ArxRleAttributeListItems::GetTxtValColor(int index) const
{
	ArxRleAttributeListItem *pItem = m_vecItems[index];
	return pItem->m_txtValColor;
}

void ArxRleAttributeListItems::Sort()
{
	//sort(m_vecItems.begin(), m_vecItems.end(),>=);//½µÐòÅÅÁÐ
	//sort(m_vecItems.begin(), m_vecItems.end()); //ÉýÐòÅÅÁÐ
	sort(m_vecItems.begin(), m_vecItems.end(),ArxRleAttributeListItem::compare);
}

void ArxRleAttributeListItems::SetFont(int index, long ftWeight, long ftHeight, long ftWidth, BOOL ftItalic, CString ftName, COLORREF ftColor, int ftKeyVal)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	pItem->m_ftWeight = ftWeight;
	pItem->m_ftHeight = ftHeight;
	pItem->m_ftWidth = ftWidth;
	pItem->m_ftItalic = ftItalic;
	pItem->m_ftName = ftName;
	pItem->m_ftColor = ftColor;
	pItem->m_ftKeyVal = ftKeyVal;
}

void ArxRleAttributeListItems::SetKeyFont(int index, long ftWeight, long ftHeight, long ftWidth, BOOL ftItalic, CString ftName, COLORREF ftColor)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	pItem->m_ftWeight = ftWeight;
	pItem->m_ftHeight = ftHeight;
	pItem->m_ftWidth = ftWidth;
	pItem->m_ftItalic = ftItalic;
	pItem->m_ftName = ftName;
	pItem->m_ftColor = ftColor;
	pItem->m_ftKeyVal = 1;
}

void ArxRleAttributeListItems::SetValFont(int index, long ftWeight, long ftHeight, long ftWidth, BOOL ftItalic, CString ftName, COLORREF ftColor)
{
	ArxRleAttributeListItem *&pItem = m_vecItems[index];
	pItem->m_ftWeight = ftWeight;
	pItem->m_ftHeight = ftHeight;
	pItem->m_ftWidth = ftWidth;
	pItem->m_ftItalic = ftItalic;
	pItem->m_ftName = ftName;
	pItem->m_ftColor = ftColor;
	pItem->m_ftKeyVal = 2;
}

int ArxRleAttributeListItems::AddItem(CString propName, CString curValue, int nItemType, CString cmbItems,
										 COLORREF bkKeyColor, COLORREF bkValColor, COLORREF txtKeyColor, COLORREF txtValColor)
{
	ArxRleAttributeListItem *pItem = new ArxRleAttributeListItem(
		propName, curValue, nItemType, cmbItems,
		0,12,0, FALSE, L"ËÎÌå", RGB(0,0,0), 0,
		FALSE, -1, 0,
		bkKeyColor, bkValColor, txtKeyColor, txtValColor);

	if(pItem->m_itemType == PIT_SEPARATOR)
	{
		pItem->m_isExpand = FALSE;
		pItem->m_idxExpand = m_itemCount;;
	}
	else if(pItem->m_itemType == PIT_COLOR)
	{
		pItem->m_curValue.Format(L"RGB(%d,%d,%d)",GetRValue(txtValColor), GetGValue(txtValColor),GetBValue(txtValColor));
		pItem->m_txtValColor = txtValColor;
	}
	else if(pItem->m_itemType == PIT_LAYER)
	{
		pItem->m_objId = FindLayer(curValue);
	}
	else if(pItem->m_itemType == PIT_LINETYPE)
	{
		pItem->m_objId = GetLineType(curValue);
	}

	pItem->m_idxItem = m_itemCount;
	m_vecItems.push_back(pItem);

	m_itemCount++;
	return m_itemCount-1;;
}

int ArxRleAttributeListItems::InsertItem(int index, CString propName, CString curValue, int nItemType, CString cmbItems,
											COLORREF bkKeyColor, COLORREF bkValColor, COLORREF txtKeyColor, COLORREF txtValColor)
{
	ArxRleAttributeListItem *pItem = new ArxRleAttributeListItem(
		propName, curValue, nItemType, cmbItems,
		0,12,0, FALSE, L"ËÎÌå", RGB(0,0,0), 0,
		FALSE, -1, 0,
		bkKeyColor, bkValColor, txtKeyColor, txtValColor);

	if(pItem->m_itemType == PIT_SEPARATOR)
	{
		pItem->m_isExpand = FALSE;
		pItem->m_idxExpand = index;
	}
	else if(pItem->m_itemType == PIT_COLOR)
	{
		pItem->m_curValue.Format(L"RGB(%d,%d,%d)",GetRValue(txtValColor), GetGValue(txtValColor),GetBValue(txtValColor));
		pItem->m_txtValColor = txtValColor;
	}
	else if(pItem->m_itemType == PIT_LAYER)
	{
		pItem->m_objId = FindLayer(curValue);
	}
	else if(pItem->m_itemType == PIT_LINETYPE)
	{
		pItem->m_objId = GetLineType(curValue);
	}

	pItem->m_idxItem = index;
	m_vecItems.insert(m_vecItems.begin()+index, pItem);

	m_itemCount++;
	return index;
}

void ArxRleAttributeListItems::SetItem(int index, CString propName, CString curValue, int nItemType, CString cmbItems,
										 COLORREF bkKeyColor, COLORREF bkValColor, COLORREF txtKeyColor, COLORREF txtValColor)
{
	ArxRleAttributeListItem *pItem = new ArxRleAttributeListItem(
		propName, curValue, nItemType, cmbItems,
		0,12,0, FALSE, L"ËÎÌå", RGB(0,0,0), 0,
		FALSE, -1, 0,
		bkKeyColor, bkValColor, txtKeyColor, txtValColor);

	if(pItem->m_itemType == PIT_SEPARATOR)
	{
		pItem->m_isExpand = FALSE;
		pItem->m_idxExpand = index;
	}
	else if(pItem->m_itemType == PIT_COLOR)
	{
		pItem->m_curValue.Format(L"RGB(%d,%d,%d)",GetRValue(txtValColor), GetGValue(txtValColor),GetBValue(txtValColor));
		pItem->m_txtValColor = txtValColor;
	}
	else if(pItem->m_itemType == PIT_LAYER)
	{
		pItem->m_objId = FindLayer(curValue);
	}
	else if(pItem->m_itemType == PIT_LINETYPE)
	{
		pItem->m_objId = GetLineType(curValue);
	}

	pItem->m_idxItem = index;
	m_vecItems[index] = pItem;
}

int ArxRleAttributeListItems::AddItem(ArxRleAttributeListItem *&pItem)
{
	if(pItem->m_itemType == PIT_SEPARATOR)
	{
		pItem->m_isExpand = FALSE;
		pItem->m_idxExpand = m_itemCount;
	}
	else if(pItem->m_itemType == PIT_COLOR)
	{
		COLORREF clr = pItem->m_txtValColor;
		pItem->m_curValue.Format(L"RGB(%d,%d,%d)",GetRValue(clr), GetGValue(clr),GetBValue(clr));
	}
	else if(pItem->m_itemType == PIT_LAYER)
	{
		pItem->m_objId = FindLayer(pItem->m_curValue);
	}
	else if(pItem->m_itemType == PIT_LINETYPE)
	{
		pItem->m_objId = GetLineType(pItem->m_curValue);
	}

	pItem->m_idxItem = m_itemCount;
	m_vecItems.push_back(pItem);

	m_itemCount++;
	return m_itemCount-1;;
}

int ArxRleAttributeListItems::InsertItem(int index, ArxRleAttributeListItem *&pItem)
{
	if(pItem->m_itemType == PIT_SEPARATOR)
	{
		pItem->m_isExpand = FALSE;
		pItem->m_idxExpand = index;
	}
	else if(pItem->m_itemType == PIT_COLOR)
	{
		COLORREF clr = pItem->m_txtValColor;
		pItem->m_curValue.Format(L"RGB(%d,%d,%d)",GetRValue(clr), GetGValue(clr),GetBValue(clr));
	}
	else if(pItem->m_itemType == PIT_LAYER)
	{
		pItem->m_objId = FindLayer(pItem->m_curValue);
	}
	else if(pItem->m_itemType == PIT_LINETYPE)
	{
		pItem->m_objId = GetLineType(pItem->m_curValue);
	}

	pItem->m_idxItem = index;
	m_vecItems.insert(m_vecItems.begin()+index, pItem);

	m_itemCount++;
	return index;
}

void ArxRleAttributeListItems::SetItem(int index, ArxRleAttributeListItem *&pItem)
{
	if(pItem->m_itemType == PIT_SEPARATOR)
	{
		pItem->m_isExpand = FALSE;
		pItem->m_idxExpand = index;
	}

	pItem->m_idxItem = index;
	m_vecItems[index] = pItem;
}

ArxRleAttributeListItem* ArxRleAttributeListItems::GetItem(int index) const
{
	return m_vecItems[index];
}

int ArxRleAttributeListItems::GetItemCount() const
{
	return m_itemCount;
}

void ArxRleAttributeListItems::DelItem(int index)
{
	m_vecItems.erase(m_vecItems.begin()+index);
	m_itemCount--;
}

void ArxRleAttributeListItems::DelItems()
{
	m_vecItems.clear();
	m_itemCount = 0;
}