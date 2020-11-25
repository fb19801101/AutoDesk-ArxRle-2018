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

#ifndef ARXRLE_REPORT_RECORD_H
#define ARXRLE_REPORT_RECORD_H


//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying prices.
class ArxRleReportRecordItemPrice : public CXTPReportRecordItemNumber
{
	DECLARE_SERIAL(ArxRleReportRecordItemPrice)
public:
	// Constructs record item with the initial decimal price value.
	ArxRleReportRecordItemPrice(double dValue = .0);

	// Provides custom group captions depending on the price.
	virtual CString GetGroupCaption(CXTPReportColumn* pColumn);

	// Provides custom group values comparison based on price value, 
	// instead of based on captions.
	virtual int CompareGroupCaption(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);
};

//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying checkboxes.
class ArxRleReportRecordItemCheck : public CXTPReportRecordItem
{
	DECLARE_SERIAL(ArxRleReportRecordItemCheck)
public:
	// Constructs record item with the initial checkbox value.
	ArxRleReportRecordItemCheck(BOOL bCheck = FALSE);

	// Provides custom group captions depending on checkbox value.
	// Returns caption string ID to be read from application resources.
	virtual int GetGroupCaptionID(CXTPReportColumn* pColumn);

	// Provides custom records comparison by this item based on checkbox value, 
	// instead of based on captions.
	virtual int Compare(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);
};

//////////////////////////////////////////////////////////////////////////
// Enumerates possible Message Importance values for using by 
// ArxRleReportRecordItemImportance class
typedef enum ENUM_IMPORTANCE
{
	ImportanceNormal,
	ImportanceHigh,
	ImportanceLow
};

//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying importance icons.
class ArxRleReportRecordItemImportance : public CXTPReportRecordItem
{
	DECLARE_SERIAL(ArxRleReportRecordItemImportance)
public:
	// Constructs record item with the initial value.
	ArxRleReportRecordItemImportance(ENUM_IMPORTANCE eImportance = ImportanceNormal);
	
	virtual void DoPropExchange(CXTPPropExchange* pPX);
protected:
	ENUM_IMPORTANCE m_eImportance;   // Message importance
};

//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying attachments icons.
class ArxRleReportRecordItemAttachment : public CXTPReportRecordItem
{
	DECLARE_SERIAL(ArxRleReportRecordItemAttachment)
public:
	// Constructs record item with the initial value.
	ArxRleReportRecordItemAttachment(BOOL bHasAttachment = FALSE);

	virtual void DoPropExchange(CXTPPropExchange* pPX);
protected:
	BOOL m_bHasAttachment;	// TRUE when message has attachments, FALSE otherwise.
};

//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying read/unread icons.
class ArxRleReportRecordItemIcon : public CXTPReportRecordItem
{
	DECLARE_SERIAL(ArxRleReportRecordItemIcon)
public:
	// Constructs record item with the initial read/unread value.
	ArxRleReportRecordItemIcon(BOOL bRead = FALSE, int nReadIndex = 0, int nUnReadIndex = 0);

	// Provides custom group captions depending on the read/unread value.
	virtual CString GetGroupCaption(CXTPReportColumn* pColumn);

	// Provides custom group values comparison based on read/unread value, 
	// instead of based on captions.
	virtual int CompareGroupCaption(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);

	// Updates record item icon index depending on read/unread value.
	void UpdateReadIcon();

	// Provides custom records comparison by this item based on read/unread value, 
	// instead of based on captions.
	int Compare(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);

	virtual void DoPropExchange(CXTPPropExchange* pPX);

public:
	BOOL m_bRead;	// TRUE for read, FALSE for unread.
	int m_nReadIndex, m_nUnReadIndex;;
};

//////////////////////////////////////////////////////////////////////////
// Customized record Date/Time item.
// Main customization purpose is overriding GetGroupCaptionID and providing
// application-specific caption when Report control data is grouped via this item.
class ArxRleReportRecordItemDate : public CXTPReportRecordItemDateTime
{
	DECLARE_SERIAL(ArxRleReportRecordItemDate)
public:
	// Construct record item from COleDateTime value.
	ArxRleReportRecordItemDate(COleDateTime odtValue = COleDateTime::GetCurrentTime());

	// Provides custom group captions depending on the item date value.
	virtual int GetGroupCaptionID(CXTPReportColumn* pColumn);
};

//////////////////////////////////////////////////////////////////////////
// This class is your main custom Record class which you'll manipulate with.
// It contains any kind of specific methods like different types of constructors,
// any additional custom data as class members, any data manipulation methods.
class ArxRleReportRecord : public CXTPReportRecord
{
	DECLARE_SERIAL(ArxRleReportRecord)
public:
	
	// Construct record object using empty values on each field
	ArxRleReportRecord();
	
	// Construct record object from detailed values on each field
	ArxRleReportRecord(
		ENUM_IMPORTANCE eImportance, BOOL bChecked, int  nAttachmentBitmap,
		CString strFromName, CString strSubject,
		COleDateTime odtSent, int nMessageSize, BOOL bRead,
		double dPrice, COleDateTime odtReceived, COleDateTime odtCreated,
		CString strConversation, CString strContact, CString strMessage,
		CString strCC, CString strCategories, CString strAutoforward,
		CString strDoNotAutoarch, CString strDueBy,
		CString strPreview
		);

	// Clean up internal objects
	virtual ~ArxRleReportRecord();

	// Create record fields using empty values
	virtual void CreateItems();

	// Set message as read
	BOOL SetRead();

	// Overridden callback method, where we can customize any drawing item metrics.
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics);

	virtual void DoPropExchange(CXTPPropExchange* pPX);

	ArxRleReportRecordItemIcon* m_pItemIcon;	// Display read/unread icon.
	ArxRleReportRecordItemDate* m_pItemReceived;// Contains message receive time.
	CXTPReportRecordItem*	m_pItemSize;	// Message size. 
											// We are storing pointer to this item for further use.
};

#endif // ARXRLE_REPORT_RECORD_H
