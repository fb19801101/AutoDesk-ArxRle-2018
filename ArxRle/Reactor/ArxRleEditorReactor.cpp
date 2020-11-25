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

#include "ArxRleEditorReactor.h"
#include "AcadUtils/ArxRleUtils.h"
#include "Snoop/ArxRleUiTdmIdMap.h"
#include "Snoop/ArxRleUiTdmObjects.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleEditorReactor, AcEditorReactor);

/****************************************************************************
**
**  ArxRleEditorReactor::ArxRleEditorReactor
**
**  **jma
**
*************************************/

ArxRleEditorReactor::ArxRleEditorReactor()
:	m_showDetails(false)
{
    acedEditor->addReactor(this);
}

/****************************************************************************
**
**  ArxRleEditorReactor::~ArxRleEditorReactor
**
**  **jma
**
*************************************/

ArxRleEditorReactor::~ArxRleEditorReactor()
{
    acedEditor->removeReactor(this);
}

/****************************************************************************
**
**  ArxRleEditorReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxRleEditorReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxRleEditorReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxRleEditorReactor::unknownCommand
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::unknownCommand(const TCHAR* cmdStr, AcDbVoidPtrArray *al)
{
    CString str;

    str.Format(_T("Unknown Command: %s"), cmdStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::commandWillStart
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::commandWillStart(const TCHAR* cmdStr)
{
    CString str;

    str.Format(_T("Command Will Start: %s"), cmdStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::commandEnded
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::commandEnded(const TCHAR* cmdStr)
{
    CString str;

    str.Format(_T("Command Ended: %s"), cmdStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::commandCancelled
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::commandCancelled(const TCHAR* cmdStr)
{
    CString str;

    str.Format(_T("Command Cancelled: %s"), cmdStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::commandFailed
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::commandFailed(const TCHAR* cmdStr)
{
    CString str;

    str.Format(_T("Command Failed: %s"), cmdStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::lispWillStart
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::lispWillStart(const TCHAR* firstLine)
{
    CString str;

    str.Format(_T("Lisp Will Start: first line = %s"), firstLine);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::lispEnded
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::lispEnded()
{
    printReactorMessage(_T("Lisp Ended"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::lispCancelled
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::lispCancelled()
{
    printReactorMessage(_T("Lisp Cancelled"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::docCloseWillStart
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::docCloseWillStart(AcDbDatabase* db)
{
    printReactorMessage(_T("Doc Close Will Start"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginDxfIn
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginDxfIn(AcDbDatabase* db)
{
    printReactorMessage(_T("Begin Dxf In"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::abortDxfIn
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::abortDxfIn(AcDbDatabase* db)
{
    printReactorMessage(_T("Abort Dxf In"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::dxfInComplete
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::dxfInComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Dxf In Complete"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginDxfOut
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginDxfOut(AcDbDatabase* db)
{
    printReactorMessage(_T("Begin Dxf Out"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::abortDxfOut
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::abortDxfOut(AcDbDatabase* db)
{
    printReactorMessage(_T("Abort Dxf Out"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::dxfOutComplete
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::dxfOutComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Dxf Out Complete"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginDwgOpen
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginDwgOpen(TCHAR* filename)
{
    CString str;
    str.Format(_T("Begin DWG Open: \"%s\""), filename);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::endDwgOpen
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::endDwgOpen(const TCHAR* filename, AcDbDatabase* /*pDb*/)
{
    CString str;
    str.Format(_T("End DWG Open: \"%s\""), filename);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::dwgFileOpened
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::dwgFileOpened(AcDbDatabase* db, TCHAR* fileName)
{
    CString str;
    str.Format(_T("DWG File Opened: \"%s\""), fileName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::initialDwgFileOpenComplete
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::initialDwgFileOpenComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Initial DWG File Open Complete"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::databaseConstructed
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::databaseConstructed(AcDbDatabase* db)
{
    printReactorMessage(_T("Database Constructed"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::databaseToBeDestroyed
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::databaseToBeDestroyed(AcDbDatabase* db)
{
    printReactorMessage(_T("Database To Be Destroyed"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginSave
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginSave(AcDbDatabase* db, const TCHAR* pIntendedName)
{
    CString str;

    str.Format(_T("Begin Save: intended name = \"%s\""), pIntendedName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::saveComplete
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::saveComplete(AcDbDatabase* db, const TCHAR* pActualName)
{
    CString str;

    str.Format(_T("Save Complete: actual name = \"%s\""), pActualName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::abortSave
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::abortSave(AcDbDatabase* db)
{
    printReactorMessage(_T("AbortSave"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginInsert
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginInsert(AcDbDatabase* pTo, const TCHAR* pBlockName, AcDbDatabase* pFrom)
{
    CString str;

    str.Format(_T("Begin Insert: \"%s\""), pBlockName);
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginInsert
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginInsert(AcDbDatabase* pTo, const AcGeMatrix3d& xform, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Begin Insert (Matrix Form)"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEditorReactor::otherInsert
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::otherInsert(AcDbDatabase* pTo, AcDbIdMapping& idMap, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Other Insert"), pTo, pFrom);

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Other Insert"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEditorReactor::abortInsert
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::abortInsert(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Insert"), pTo);
}

/****************************************************************************
**
**  ArxRleEditorReactor::endInsert
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::endInsert(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Insert"), pTo);
}

/****************************************************************************
**
**  ArxRleEditorReactor::wblockNotice
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::wblockNotice(AcDbDatabase* db)
{
    printReactorMessage(_T("Wblock Notice"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, const AcGePoint3d*& insertionPoint)
{
    CString str, str2;
    str.Format(_T("Begin Wblock (1): insert pt = %s"),
                        ArxRleUtils::ptToStr(*insertionPoint, str2));
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, AcDbObjectId blockId)
{
    CString str, blkName;

    ArxRleUtils::symbolIdToName(blockId, blkName);
    str.Format(_T("Begin Wblock (2): blkname = %s"), blkName);
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Begin Wblock Entire Database"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEditorReactor::otherWblock
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::otherWblock(AcDbDatabase* pTo, AcDbIdMapping& idMap, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Other Wblock"), pTo, pFrom);

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Other Wblock"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEditorReactor::abortWblock
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::abortWblock(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Wblock"), pTo);
}

/****************************************************************************
**
**  ArxRleEditorReactor::endWblock
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::endWblock(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Wblock"), pTo);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginDeepClone
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginDeepClone(AcDbDatabase* pTo, AcDbIdMapping& idMap)
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
**  ArxRleEditorReactor::beginDeepCloneXlation
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginDeepCloneXlation(AcDbIdMapping& idMap, Acad::ErrorStatus* pRetStatus)
{
    printReactorMessage(_T("Begin Deep Clone Translation"));

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Begin Deep Clone Xlation"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEditorReactor::abortDeepClone
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::abortDeepClone(AcDbIdMapping& idMap)
{
    printReactorMessage(_T("Abort Deep Clone"));

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Abort Deep Clone"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEditorReactor::endDeepClone
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::endDeepClone(AcDbIdMapping& idMap)
{
    printReactorMessage(_T("End Deep Clone"));

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("End Deep Clone"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEditorReactor::sysVarChanged
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::sysVarChanged(const TCHAR* varName, Adesk::Boolean success)
{
    CString str;

    str.Format(_T("Sysvar Changed: %s"), varName);
    printReactorMessage(str);
    if (success != Adesk::kTrue)
        acutPrintf(_T("\n*** SYSVAR NOT CHANGED SUCCESSFULLY!!! ***"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::sysVarWillChange
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::sysVarWillChange(const TCHAR* varName)
{
    CString str;

    str.Format(_T("Sysvar Will Change: %s"), varName);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginAttach
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginAttach(AcDbDatabase* pTo, const TCHAR* pName, AcDbDatabase* pFrom)
{
    CString str;

    str.Format(_T("Begin Attach: %s"), pName);
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEditorReactor::otherAttach
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::otherAttach(AcDbDatabase* pTo, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Other Attach"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEditorReactor::abortAttach
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::abortAttach(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Attach"), pTo);
}

/****************************************************************************
**
**  ArxRleEditorReactor::endAttach
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::endAttach(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Attach"), pTo);
}

/****************************************************************************
**
**  ArxRleEditorReactor::redirected
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::redirected(AcDbObjectId newId, AcDbObjectId oldId)
{
    printReactorMessage(_T("Redirected"), oldId);
}

/****************************************************************************
**
**  ArxRleEditorReactor::comandeered
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::comandeered(AcDbDatabase* pTo, AcDbObjectId id, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Comandeered"), id);
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginRestore
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginRestore(AcDbDatabase* pTo, const TCHAR*, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Begin Restore"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxRleEditorReactor::abortRestore
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::abortRestore(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Restore"), pTo);
}

/****************************************************************************
**
**  ArxRleEditorReactor::endRestore
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::endRestore(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Restore"), pTo);
}

/****************************************************************************
**
**  ArxRleEditorReactor::xrefSubcommandBindItem
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::xrefSubcommandBindItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId)
{
    CString str, str2;

    str.Format(_T("Xref sub-command bind item: activity = %s"),
                            xrefActivityToStr(activity, str2));
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::xrefSubcommandAttachItem
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::xrefSubcommandAttachItem(AcDbDatabase* pHost, int activity, const TCHAR* pPath)
{
    CString str, str2;
    LPCTSTR tmpStr;

        // sometimes comes through as null!
    if (pPath == NULL)
        tmpStr = _T("(NULL)");
    else
        tmpStr = pPath;

    str.Format(_T("Xref sub-command attach item: activity = %s, path = %s"), 
                            xrefActivityToStr(activity, str2), tmpStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::xrefSubcommandOverlayItem
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::xrefSubcommandOverlayItem(AcDbDatabase* pHost, int activity, const TCHAR* pPath)
{
    CString str, str2;

    str.Format(_T("Xref sub-command overlay item: activity = %s, path = %s"), 
                            xrefActivityToStr(activity, str2), pPath);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::xrefSubcommandDetachItem
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::xrefSubcommandDetachItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId)
{
    CString str, str2;

    str.Format(_T("Xref sub-command detach item: activity = %s"),
                            xrefActivityToStr(activity, str2));

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::xrefSubcommandPathItem
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::xrefSubcommandPathItem(int activity, AcDbObjectId blockId, const TCHAR* pNewPath)
{
    CString str, str2;

    str.Format(_T("Xref sub-command path item: activity = %s, path = %s"), 
                            xrefActivityToStr(activity, str2), pNewPath);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::xrefSubcommandReloadItem
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::xrefSubcommandReloadItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId)
{
    CString str, str2;

    str.Format(_T("Xref sub-command reload item: activity = %s"), 
                            xrefActivityToStr(activity, str2));
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::xrefSubcommandUnloadItem
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::xrefSubcommandUnloadItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId)
{
    CString str, str2;

    str.Format(_T("Xref sub-command unload item: activity = %s"), 
                            xrefActivityToStr(activity, str2));
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::undoSubcommandAuto
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::undoSubcommandAuto(int activity, Adesk::Boolean state)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Auto: activity = %s, state = %d"),
                    undoActivityToStr(activity, str2), state);

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::undoSubcommandControl
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::undoSubcommandControl(int activity, int option)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Control: activity = %s, option = %d"),
                    undoActivityToStr(activity, str2), option);

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::undoSubcommandBegin
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::undoSubcommandBegin(int activity)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Begin: activity = %s"), undoActivityToStr(activity, str2));

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::undoSubcommandEnd
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::undoSubcommandEnd(int activity)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand End: activity = %s"), undoActivityToStr(activity, str2));

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::undoSubcommandMark
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::undoSubcommandMark(int activity)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Mark: activity = %s"), undoActivityToStr(activity, str2));

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::undoSubcommandBack
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::undoSubcommandBack(int activity)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Back: activity = %s"), undoActivityToStr(activity, str2));

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::undoSubcommandNumber
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::undoSubcommandNumber(int activity, int num)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Number: activity = %s, #%d"),
                        undoActivityToStr(activity, str2), num);

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::pickfirstModified
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::pickfirstModified()
{
    printReactorMessage(_T("Pickfirst Modified"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::layoutSwitched
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::layoutSwitched(const TCHAR* newLayoutName)
{
    CString str;
    str.Format(_T("Layout Switched: %s"), newLayoutName);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxRleEditorReactor::docFrameMovedOrResized
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::docFrameMovedOrResized(long hwndDocFrame, bool bMoved)
{
    if (bMoved)
        printReactorMessage(_T("Doc Frame Moved"));
    else
        printReactorMessage(_T("Doc Frame Resized"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::mainFrameMovedOrResized
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::mainFrameMovedOrResized(long hwndMainFrame, bool bMoved)
{
    if (bMoved)
        printReactorMessage(_T("Main Frame Moved"));
    else
        printReactorMessage(_T("Main Frame Resized"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginDoubleClick
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginDoubleClick(const AcGePoint3d& clickPoint)
{
    printReactorMessage(_T("Begin Double-click"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginRightClick
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginRightClick(const AcGePoint3d& clickPoint)
{
    printReactorMessage(_T("Begin Right-click"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::toolbarBitmapSizeWillChange
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::toolbarBitmapSizeWillChange(Adesk::Boolean bLarge)
{
    printReactorMessage(_T("Toolbar Bitmap Size Will Change"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::toolbarBitmapSizeChanged
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::toolbarBitmapSizeChanged(Adesk::Boolean bLarge)
{
    printReactorMessage(_T("Toolbar Bitmap Size Changed"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginWblockObjects
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginWblockObjects(AcDbDatabase* pFrom, AcDbIdMapping& idMap)
{
    printReactorMessage(_T("Begin Wblock Objects"), pFrom);

	if (m_showDetails) {
		ArxRleUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Begin Wblock Objects"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEditorReactor::partialOpenNotice
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::partialOpenNotice(AcDbDatabase* db)
{
    printReactorMessage(_T("Partial Open Notice"), db);
}

/****************************************************************************
**
**  ArxRleEditorReactor::objectsLazyLoaded
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::objectsLazyLoaded(const AcDbObjectIdArray& idArray)
{
    printReactorMessage(_T("Objects Lazy Loaded"));

	if (m_showDetails) {
		ArxRleUiTdmObjects dbox(idArray, acedGetAcadDwgView(), _T("Objects Lazy Loaded"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEditorReactor::beginQuit
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::beginQuit()
{
    printReactorMessage(_T("Begin Quit"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::quitAborted
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::quitAborted()
{
    printReactorMessage(_T("Quit Aborted"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::quitWillStart
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::quitWillStart()
{
    printReactorMessage(_T("Quit Will Start"));
}

/****************************************************************************
**
**  ArxRleEditorReactor::modelessOperationWillStart
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::modelessOperationWillStart(const TCHAR* contextStr)
{
    printReactorMessage(_T("Modeless Operation Will Start"), contextStr);
}

/****************************************************************************
**
**  ArxRleEditorReactor::modelessOperationEnded
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::modelessOperationEnded(const TCHAR* contextStr)
{
    printReactorMessage(_T("Modeless Operation Ended"), contextStr);
}

/****************************************************************************
**
**  ArxRleEditorReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::printReactorMessage(LPCTSTR event) const
{
    acutPrintf(_T("\n%-15s : [%s] "), _T("[ED REACTOR]"), event);
}

/****************************************************************************
**
**  ArxRleEditorReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::printReactorMessage(LPCTSTR event, LPCTSTR msg) const
{
    acutPrintf(_T("\n%-15s : [%s, %s] "), _T("[EVENT REACTOR]"), event, msg);
}

/****************************************************************************
**
**  ArxRleEditorReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::printReactorMessage(LPCTSTR event, AcDbDatabase* pDb) const
{
    CString str;

    acutPrintf(_T("\n%-15s : [%s]   (Db = %s)"), _T("[ED REACTOR]"), event, ArxRleUtils::dbToStr(pDb, str));
}

/****************************************************************************
**
**  ArxRleEditorReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::printReactorMessage(LPCTSTR event, AcDbDatabase* pTo, AcDbDatabase* pFrom) const
{
    CString tmpStr1, tmpStr2;
	ArxRleUtils::dbToStr(pTo, tmpStr1);
	ArxRleUtils::dbToStr(pFrom, tmpStr2);

    acutPrintf(_T("\n%-15s : [%s]   (To = %s, From = %s)"), _T("[ED REACTOR]"), event, tmpStr1, tmpStr2);
}

/****************************************************************************
**
**  ArxRleEditorReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleEditorReactor::printReactorMessage(LPCTSTR event, const AcDbObjectId& objId) const
{
    CString str;
    AcDbObject* obj;
    Acad::ErrorStatus es = acdbOpenAcDbObject(obj, objId, AcDb::kForRead);
    if (es == Acad::eOk) {
        acutPrintf(_T("\n%-15s : [%-18s: %s, %s] "), _T("[ED REACTOR]"), event,
                ArxRleUtils::objToClassStr(obj), ArxRleUtils::objToHandleStr(obj, str));
        obj->close();
    }
    else {
        ArxRleUtils::rxErrorMsg(es);
        printReactorMessage(event);
    }
}

/****************************************************************************
**
**  ArxRleEditorReactor::xrefActivityToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleEditorReactor::xrefActivityToStr(int activity, CString& str)
{
    if (activity == kStart)
        str = _T("Start");
    else if (activity == kStartItem)
        str = _T("Start Item");
    else if (activity == kEndItem)
        str = _T("End Item");
    else if (activity == kEnd)
        str = _T("End");
    else if (activity == kWillAbort)
        str = _T("Will Abort");
    else if (activity == kAborted)
        str = _T("Aborted");
    else if (activity == kStartXBindBlock)
        str = _T("Start XBind Block");
    else if (activity == kStartXBindSymbol)
        str = _T("Start XBind Symbol");
    else {
        ASSERT(0);
        ArxRleUtils::intToStr(activity, str);
    }

    return str;
}

/****************************************************************************
**
**  ArxRleEditorReactor::undoActivityToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleEditorReactor::undoActivityToStr(int activity, CString& str)
{
    if (activity == kNone)
        str = _T("None");
    else if (activity == kOne)
        str = _T("One");
    else if (activity == kAll)
        str = _T("All");
    else {
        ASSERT(0);
        ArxRleUtils::intToStr(activity, str);
    }

    return str;
}
