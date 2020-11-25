//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleEventReactor.h"
#include "AcadUtils/ArxRleUtils.h"
#include "Snoop/ArxRleUiTdmIdMap.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleEventReactor, AcRxEventReactor);

/****************************************************************************
**
**  ArxRleEventReactor::ArxRleEventReactor
**
**  **jma
**
*************************************/

ArxRleEventReactor::ArxRleEventReactor()
:	m_showDetails(false)
{
    acrxEvent->addReactor(this);
}

/****************************************************************************
**
**  ArxRleEventReactor::~ArxRleEventReactor
**
**  **jma
**
*************************************/

ArxRleEventReactor::~ArxRleEventReactor()
{
    acrxEvent->removeReactor(this);
}

/****************************************************************************
**
**  ArxRleEventReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxRleEventReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxRleEventReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxRleEventReactor::beginDxfIn
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::beginDxfIn(AcDbDatabase* db)
{
    printReactorMessage(_T("Begin Dxf In"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::abortDxfIn
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::abortDxfIn(AcDbDatabase* db)
{
    printReactorMessage(_T("Abort Dxf In"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::dxfInComplete
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::dxfInComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Dxf In Complete"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::beginDxfOut
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::beginDxfOut(AcDbDatabase* db)
{
    printReactorMessage(_T("Begin Dxf Out"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::abortDxfOut
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::abortDxfOut(AcDbDatabase* db)
{
    printReactorMessage(_T("Abort Dxf Out"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::dxfOutComplete
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::dxfOutComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Dxf Out Complete"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::dwgFileOpened
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::dwgFileOpened(AcDbDatabase* db, TCHAR* fileName)
{
    CString str;
    str.Format(_T("DWG File Opened: \"%s\""), fileName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxRleEventReactor::initialDwgFileOpenComplete
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::initialDwgFileOpenComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Initial DWG File Open Complete"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::databaseConstructed
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::databaseConstructed(AcDbDatabase* db)
{
    printReactorMessage(_T("Database Constructed"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::databaseToBeDestroyed
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::databaseToBeDestroyed(AcDbDatabase* db)
{
    printReactorMessage(_T("Database To Be Destroyed"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::beginSave
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::beginSave(AcDbDatabase* db, const TCHAR* pIntendedName)
{
    CString str;

    str.Format(_T("Begin Save: intended name = \"%s\""), pIntendedName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxRleEventReactor::saveComplete
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::saveComplete(AcDbDatabase* db, const TCHAR* pActualName)
{
    CString str;

    str.Format(_T("Save Complete: actual name = \"%s\""), pActualName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxRleEventReactor::abortSave
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::abortSave(AcDbDatabase* db)
{
    printReactorMessage(_T("AbortSave"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::beginInsert
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::beginInsert(AcDbDatabase* pTo, const TCHAR* pBlockName, AcDbDatabase* pFrom)
{
    CString str;

    str.Format(_T("Begin Insert: \"%s\""), pBlockName);
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEventReactor::beginInsert
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::beginInsert(AcDbDatabase* pTo, const AcGeMatrix3d& xform, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Begin Insert (Matrix Form)"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEventReactor::otherInsert
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::otherInsert(AcDbDatabase* pTo, AcDbIdMapping& idMap, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Other Insert"), pTo, pFrom);

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Other Insert"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEventReactor::abortInsert
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::abortInsert(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Insert"), pTo);
}

/****************************************************************************
**
**  ArxRleEventReactor::endInsert
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::endInsert(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Insert"), pTo);
}

/****************************************************************************
**
**  ArxRleEventReactor::wblockNotice
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::wblockNotice(AcDbDatabase* db)
{
    printReactorMessage(_T("Wblock Notice"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, const AcGePoint3d*& insertionPoint)
{
    CString str, str2;
    str.Format(_T("Begin Wblock (1): insert pt = %s"),
                        ArxRleUtils::ptToStr(*insertionPoint, str2));
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEventReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, AcDbObjectId blockId)
{
    CString str, blkName;

    ArxRleUtils::symbolIdToName(blockId, blkName);
    str.Format(_T("Begin Wblock (2): blkname = %s"), blkName);
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEventReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Begin Wblock Entire Database"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEventReactor::otherWblock
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::otherWblock(AcDbDatabase* pTo, AcDbIdMapping& idMap, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Other Wblock"), pTo, pFrom);

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Other Wblock"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEventReactor::abortWblock
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::abortWblock(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Wblock"), pTo);
}

/****************************************************************************
**
**  ArxRleEventReactor::endWblock
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::endWblock(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Wblock"), pTo);
}

/****************************************************************************
**
**  ArxRleEventReactor::beginDeepClone
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::beginDeepClone(AcDbDatabase* pTo, AcDbIdMapping& idMap)
{
    CString str, str2;

	ArxRleUtils::deepCloneContextToStr(idMap.deepCloneContext(), str2);

    str.Format(_T("Begin Deep Clone: context = %s"), static_cast<LPCTSTR>(str2));
    printReactorMessage(str, pTo);

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Begin Deep Clone"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEventReactor::beginDeepCloneXlation
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::beginDeepCloneXlation(AcDbIdMapping& idMap, Acad::ErrorStatus* pRetStatus)
{
    printReactorMessage(_T("Begin Deep Clone Translation"));

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Begin Deep Clone Xlation"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEventReactor::abortDeepClone
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::abortDeepClone(AcDbIdMapping& idMap)
{
    printReactorMessage(_T("Abort Deep Clone"));

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Abort Deep Clone"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEventReactor::endDeepClone
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::endDeepClone(AcDbIdMapping& idMap)
{
    printReactorMessage(_T("End Deep Clone"));

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("End Deep Clone"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEventReactor::beginWblockObjects
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::beginWblockObjects(AcDbDatabase* pFrom, AcDbIdMapping& idMap)
{
    printReactorMessage(_T("Begin Wblock Objects"), pFrom);

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Begin Wblock Objects"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEventReactor::partialOpenNotice
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::partialOpenNotice(AcDbDatabase* db)
{
    printReactorMessage(_T("Partial Open Notice"), db);
}

/****************************************************************************
**
**  ArxRleEventReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::printReactorMessage(LPCTSTR event) const
{
    acutPrintf(_T("\n%-15s : [%s] "), _T("[EVENT REACTOR]"), event);
}

/****************************************************************************
**
**  ArxRleEventReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::printReactorMessage(LPCTSTR event, AcDbDatabase* pDb) const
{
    CString str;

    acutPrintf(_T("\n%-15s : [%s]   (Db = %s)"), _T("[EVENT REACTOR]"), event, ArxRleUtils::dbToStr(pDb, str));
}

/****************************************************************************
**
**  ArxRleEventReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::printReactorMessage(LPCTSTR event, AcDbDatabase* pTo, AcDbDatabase* pFrom) const
{
    CString tmpStr1, tmpStr2;
	ArxRleUtils::dbToStr(pTo, tmpStr1);
	ArxRleUtils::dbToStr(pFrom, tmpStr2);

    acutPrintf(_T("\n%-15s : [%s]   (To = %s, From = %s)"), _T("[EVENT REACTOR]"), event, tmpStr1, tmpStr2);
}

/****************************************************************************
**
**  ArxRleEventReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleEventReactor::printReactorMessage(LPCTSTR event, const AcDbObjectId& objId) const
{
    CString str;
    AcDbObject* obj;
    Acad::ErrorStatus es = acdbOpenAcDbObject(obj, objId, AcDb::kForRead);
    if (es == Acad::eOk) {
        acutPrintf(_T("\n%-15s : [%-18s: %s, %s] "), _T("[EVENT REACTOR]"), event,
                ArxRleUtils::objToClassStr(obj), ArxRleUtils::objToHandleStr(obj, str));
        obj->close();
    }
    else {
        ArxRleUtils::rxErrorMsg(es);
        printReactorMessage(event);
    }
}

