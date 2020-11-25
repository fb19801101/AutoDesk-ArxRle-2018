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
#include "stdafx.h"
#include "Resource.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleReportRecord.h"


IMPLEMENT_SERIAL(ArxRleReportRecord, CXTPReportRecord, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)
IMPLEMENT_SERIAL(ArxRleReportRecordItemPrice, CXTPReportRecordItemNumber, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)
IMPLEMENT_SERIAL(ArxRleReportRecordItemCheck, CXTPReportRecordItem, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)
IMPLEMENT_SERIAL(ArxRleReportRecordItemImportance, CXTPReportRecordItem, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)
IMPLEMENT_SERIAL(ArxRleReportRecordItemAttachment, CXTPReportRecordItem, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)
IMPLEMENT_SERIAL(ArxRleReportRecordItemIcon, CXTPReportRecordItem, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)
IMPLEMENT_SERIAL(ArxRleReportRecordItemDate, CXTPReportRecordItemDateTime, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)

//////////////////////////////////////////////////////////////////////////
// ArxRleReportRecordItemPrice

ArxRleReportRecordItemPrice::ArxRleReportRecordItemPrice(double dValue)
: CXTPReportRecordItemNumber(dValue, _T("$ %.2f"))
{

}

CString ArxRleReportRecordItemPrice::GetGroupCaption(CXTPReportColumn* /*pColumn*/)
{
	if (m_dValue > 20)
		return _T("Record Price > 20");

	if (m_dValue > 5)
		return _T("Record Price 5 - 20");

	return _T("Record Price < 5");
}

int ArxRleReportRecordItemPrice::CompareGroupCaption(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem)
{
	return GetGroupCaption(pColumn).Compare(pItem->GetGroupCaption(pColumn));
}

//////////////////////////////////////////////////////////////////////////
// ArxRleReportRecordItemCheck

ArxRleReportRecordItemCheck::ArxRleReportRecordItemCheck(BOOL bCheck)
{
	HasCheckbox(TRUE);
	SetChecked(bCheck);
}

int ArxRleReportRecordItemCheck::GetGroupCaptionID(CXTPReportColumn* /*pColumn*/)
{
	return IsChecked() ? ARXRLE_STR_REPORT_CHECKED_TRUE : ARXRLE_STR_REPORT_CHECKED_FALSE;
}

int ArxRleReportRecordItemCheck::Compare(CXTPReportColumn* /*pColumn*/, CXTPReportRecordItem* pItem)
{
	return int(IsChecked()) - int(pItem->IsChecked());
}


//////////////////////////////////////////////////////////////////////////
// ArxRleReportRecordItemImportance

ArxRleReportRecordItemImportance::ArxRleReportRecordItemImportance(ENUM_IMPORTANCE eImportance)
	: m_eImportance(eImportance)
{
	SetIconIndex(eImportance == ImportanceHigh ? 6 : 
		         eImportance == ImportanceLow ? 9: -1);

	SetGroupPriority(m_eImportance == ImportanceHigh? ARXRLE_STR_REPORT_IMPOPRTANCE_HIGH:
					 m_eImportance == ImportanceLow?  ARXRLE_STR_REPORT_IMPOPRTANCE_LOW: ARXRLE_STR_REPORT_IMPOPRTANCE_NORMAL);

	SetSortPriority(GetGroupPriority());
	
	CString strToolTip;
	strToolTip.LoadString(GetGroupPriority());
	
	SetTooltip(strToolTip);
}

void ArxRleReportRecordItemImportance::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPReportRecordItem::DoPropExchange(pPX);

	PX_Enum(pPX, _T("Importance"), m_eImportance, ImportanceNormal);
}


//////////////////////////////////////////////////////////////////////////
// ArxRleReportRecordItemAttachment

ArxRleReportRecordItemAttachment::ArxRleReportRecordItemAttachment(BOOL bHasAttachment)
	: m_bHasAttachment(bHasAttachment)
{
	SetIconIndex(bHasAttachment ? 8 : -1);
	SetGroupPriority(m_bHasAttachment? ARXRLE_STR_REPORT_ATTACHMENTS_TRUE: ARXRLE_STR_REPORT_ATTACHMENTS_FALSE);
	SetSortPriority(GetGroupPriority());
}

void ArxRleReportRecordItemAttachment::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPReportRecordItem::DoPropExchange(pPX);

	PX_Bool(pPX, _T("HasAttachment"), m_bHasAttachment);
}

//////////////////////////////////////////////////////////////////////////
// ArxRleReportRecordItemIcon

ArxRleReportRecordItemIcon::ArxRleReportRecordItemIcon(BOOL bRead, int nReadIndex, int nUnReadIndex)
	: m_bRead(bRead), m_nReadIndex(nReadIndex), m_nUnReadIndex(nUnReadIndex)
{
	UpdateReadIcon();
}

void ArxRleReportRecordItemIcon::UpdateReadIcon()
{
	SetIconIndex(m_bRead ? m_nReadIndex : m_nUnReadIndex);
}

int ArxRleReportRecordItemIcon::Compare(CXTPReportColumn* /*pColumn*/, CXTPReportRecordItem* pItem)
{
	return int(m_bRead) - int(((ArxRleReportRecordItemIcon*)pItem)->m_bRead);
}

CString ArxRleReportRecordItemIcon::GetGroupCaption(CXTPReportColumn* /*pColumn*/)
{
	if (m_bRead)
		return _T("Record status: Read");
	else
		return _T("Record status: Unread");
}

int ArxRleReportRecordItemIcon::CompareGroupCaption(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem)
{
	return GetGroupCaption(pColumn).Compare(pItem->GetGroupCaption(pColumn));
}

void ArxRleReportRecordItemIcon::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPReportRecordItem::DoPropExchange(pPX);

	PX_Bool(pPX, _T("Read"), m_bRead);
}


//////////////////////////////////////////////////////////////////////////
// CReportGridRecordItemSent

ArxRleReportRecordItemDate::ArxRleReportRecordItemDate(COleDateTime odtValue)
	: CXTPReportRecordItemDateTime(odtValue)
{
}

int ArxRleReportRecordItemDate::GetGroupCaptionID(CXTPReportColumn* /*pColumn*/)
{
	COleDateTime odtNow(COleDateTime::GetCurrentTime());

	if (m_odtValue.GetYear() < odtNow.GetYear())
		return ARXRLE_STR_REPORT_DATE_OLDER;

	if (m_odtValue.GetMonth() < odtNow.GetMonth())
		return ARXRLE_STR_REPORT_DATE_THISYEAR;

	if (m_odtValue.GetDay() < odtNow.GetDay())
		return ARXRLE_STR_REPORT_DATE_THISMONTH;

	if (m_odtValue.m_dt <= odtNow.m_dt)
		return ARXRLE_STR_REPORT_DATE_TODAY;

	return -1;
}



//////////////////////////////////////////////////////////////////////
// ArxRleReportRecord class

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArxRleReportRecord::ArxRleReportRecord()
{
	m_pItemIcon = NULL;
	m_pItemReceived = NULL;
	m_pItemSize = NULL;

	CreateItems();
}

ArxRleReportRecord::ArxRleReportRecord(
					ENUM_IMPORTANCE eImportance, BOOL bChecked, int  nAttachmentBitmap,
					CString strFromName, CString strSubject,
					COleDateTime odtReceived, int nMessageSize, BOOL bRead,
					double dPrice, COleDateTime odtSent, COleDateTime odtCreated,
					CString strConversation, CString strContact, CString strMessage,
					CString strCC, CString strCategories, CString strAutoforward,
					CString strDoNotAutoarch, CString strDueBy,
					CString strPreview)
{
	AddItem(new ArxRleReportRecordItemImportance(eImportance));
	m_pItemIcon = (ArxRleReportRecordItemIcon*)AddItem(new ArxRleReportRecordItemIcon(bRead,0,1));
	AddItem(new ArxRleReportRecordItemAttachment(nAttachmentBitmap));
	AddItem(new CXTPReportRecordItemText(strFromName));
	AddItem(new CXTPReportRecordItemText(strSubject));
	m_pItemReceived = (ArxRleReportRecordItemDate*)AddItem(new ArxRleReportRecordItemDate(odtReceived));
	m_pItemSize = AddItem(new CXTPReportRecordItemNumber(nMessageSize));
	AddItem(new ArxRleReportRecordItemCheck(bChecked));
	AddItem(new ArxRleReportRecordItemPrice(dPrice));
	AddItem(new ArxRleReportRecordItemDate(odtCreated));
	AddItem(new ArxRleReportRecordItemDate(odtSent));
	AddItem(new CXTPReportRecordItemText(strConversation));
	AddItem(new CXTPReportRecordItemText(strContact));
	AddItem(new CXTPReportRecordItemText(strMessage));
	AddItem(new CXTPReportRecordItemText(strCC));
	AddItem(new CXTPReportRecordItemText(strCategories));
	AddItem(new CXTPReportRecordItemText(strAutoforward));
	AddItem(new CXTPReportRecordItemText(strDoNotAutoarch));
	AddItem(new CXTPReportRecordItemText(strDueBy));

	SetPreviewItem(new CXTPReportRecordItemPreview(strPreview));
}

void ArxRleReportRecord::CreateItems()
{
	// Initialize record items with empty values
	
	COleDateTime dtNow(COleDateTime::GetCurrentTime());

	// 0 
	AddItem(new ArxRleReportRecordItemImportance(ImportanceNormal));

	// 1 ***
	m_pItemIcon = (ArxRleReportRecordItemIcon*)AddItem(new ArxRleReportRecordItemIcon(TRUE));
	
	// 2 
	AddItem(new ArxRleReportRecordItemAttachment(0));
	
	// 3 
	AddItem(new CXTPReportRecordItemText(_T("")));

	// 4 
	AddItem(new CXTPReportRecordItemText(_T("")));

	// 5 ***
	m_pItemReceived = (ArxRleReportRecordItemDate*)AddItem(new ArxRleReportRecordItemDate(dtNow));

	// 6 ***
	m_pItemSize = AddItem(new CXTPReportRecordItemNumber(0));
	
	AddItem(new ArxRleReportRecordItemCheck(FALSE));
	AddItem(new ArxRleReportRecordItemPrice(0));
	AddItem(new ArxRleReportRecordItemDate(dtNow));
	AddItem(new ArxRleReportRecordItemDate(dtNow));
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));

	SetPreviewItem(new CXTPReportRecordItemPreview(_T("")));
}

ArxRleReportRecord::~ArxRleReportRecord()
{

}

BOOL ArxRleReportRecord::SetRead()
{
	ASSERT(m_pItemIcon);
	if (m_pItemIcon->m_bRead)
		return FALSE;

	m_pItemIcon->m_bRead = TRUE;
	m_pItemIcon->UpdateReadIcon();

	return TRUE;
}

void ArxRleReportRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	CXTPReportRecord::GetItemMetrics(pDrawArgs, pItemMetrics);
}

void ArxRleReportRecord::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPReportRecord::DoPropExchange(pPX);

	if (pPX->IsLoading())
	{
		// 1 - m_pItemIcon = (ArxRleReportRecordItemIcon*)AddItem(new ArxRleReportRecordItemIcon(TRUE));
		ASSERT_KINDOF(ArxRleReportRecordItemIcon, GetItem(1));
		m_pItemIcon = DYNAMIC_DOWNCAST(ArxRleReportRecordItemIcon, GetItem(1));
		ASSERT(m_pItemIcon);
		
		// 5 - m_pItemReceived = (ArxRleReportRecordItemDate*)AddItem(new ArxRleReportRecordItemDate(dtNow));
		ASSERT_KINDOF(ArxRleReportRecordItemDate, GetItem(5));
		m_pItemReceived = DYNAMIC_DOWNCAST(ArxRleReportRecordItemDate, GetItem(5));
		ASSERT(m_pItemReceived);
		
		// 6 - m_pItemSize = AddItem(new CXTPReportRecordItemNumber(0));
		ASSERT_KINDOF(CXTPReportRecordItemNumber, GetItem(6));
		m_pItemSize = DYNAMIC_DOWNCAST(CXTPReportRecordItemNumber, GetItem(6));
		ASSERT(m_pItemSize);		
	}
}
