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

#include "ArxRleUiTdcInsert.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"
#include "Reactor/ArxRleAppEditorReactor.h"
#include "Snoop/ArxRleUiTdmObjects.h"
#include "Snoop/ArxRleUiTdmDatabase.h"
#include "ArxRleUiTdmTransDbClones.h"
#include "AcadUtils/ArxRleDocLockWrite.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**  ArxRleUiTdcInsert::ArxRleUiTdcInsert
**
**  **jma
**
*************************************/

ArxRleUiTdcInsert::ArxRleUiTdcInsert()
:   CAcUiTabChildDialog(NULL, ArxRleApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxRleUiTdcInsert)
    m_preserveOriginalDb = FALSE;
    m_saveAsDwg = FALSE;
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::~ArxRleUiTdcInsert
**
**  **jma
**
*************************************/

ArxRleUiTdcInsert::~ArxRleUiTdcInsert()
{
        // we need to delete any external databases that we allocated.
    AcDbDatabase* tmpDb;

    INT_PTR len = m_extDwgNames.GetSize();
    ASSERT( len <= INT_MAX );
    for (int i=0; i<(int)len; i++) {
        if (m_extDwgNames[i] != _T("")) {
            tmpDb = static_cast<AcDbDatabase*>(m_dbPtrs[i]);
            delete tmpDb;
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabChildDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcInsert)
	DDX_Control(pDX, ARXRLE_INSERT_EB_DESTNAME1, m_ebDestName1);
	DDX_Control(pDX, ARXRLE_INSERT_EB_DESTNAME2, m_ebDestName2);
	DDX_Control(pDX, ARXRLE_INSERT_LB_SOURCE_DB, m_lbSourceDb);
	DDX_Control(pDX, ARXRLE_INSERT_LB_DEST_DB, m_lbDestDb);
	DDX_Control(pDX, ARXRLE_INSERT_CB_BLKDEFS, m_puBlockDef);
	DDX_Check(pDX, ARXRLE_INSERT_CB_PRESERVE_SRC_DB, m_preserveOriginalDb);
	DDX_Check(pDX, ARXRLE_INSERT_CK_SAVE_AS_DWG, m_saveAsDwg);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcInsert message handlers

BEGIN_MESSAGE_MAP(ArxRleUiTdcInsert, CAcUiTabChildDialog)
    //{{AFX_MSG_MAP(ArxRleUiTdcInsert)
	ON_LBN_SELCHANGE(ARXRLE_INSERT_LB_SOURCE_DB, OnSourceDatabaseChanged)
	ON_LBN_SELCHANGE(ARXRLE_INSERT_LB_DEST_DB, OnDestDatabaseChanged)
	ON_BN_CLICKED(ARXRLE_INSERT_BN_INSERT_ALL, OnInsertDb)
	ON_BN_CLICKED(ARXRLE_INSERT_BN_INSERT_AS_BLOCK, OnInsertBlkDef)
	ON_BN_CLICKED(ARXRLE_INSERT_BN_TRANSFER_BLKDEF, OnTransferBlkDef)
	ON_BN_CLICKED(ARXRLE_INSERT_BN_EXTDWG, OnAddExternalDwg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcInsert message handlers


/****************************************************************************
**
**  ArxRleUiTdcInsert::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcInsert::OnInitDialog() 
{
    CAcUiTabChildDialog::OnInitDialog();

    displayDbLists();

    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::displayDbLists
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::displayDbLists() 
{
    m_dbPtrs.setLogicalLength(0);
    m_lbSourceDb.ResetContent();
    m_lbDestDb.ResetContent();

    m_dbPtrs = acdbActiveDatabaseArray();

    CString str;
    AcDbDatabase* tmpDb;

    int len = m_dbPtrs.length();
    for (int i=0; i<len; i++) {
        tmpDb = static_cast<AcDbDatabase*>(m_dbPtrs[i]);

        ArxRleUtils::dbToStr(tmpDb, str);
        m_lbSourceDb.AddString(str);
        m_lbDestDb.AddString(str);

        m_extDwgNames.Add(_T(""));	// add bogus dwgName to keep these in sync when we
                                    // later add external drawings.
    }

    m_lbSourceDb.SetCurSel(0);
    m_lbDestDb.SetCurSel(0);

    fillBlockList();
    setButtonModes();
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::fillBlockList
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::fillBlockList() 
{
    m_blockList.RemoveAll();

    bool isExternal;
    AcDbDatabase* curDb = getSourceDb(isExternal);
    ASSERT(curDb != NULL);

    Acad::ErrorStatus es;
    es = ArxRleUtils::collectBlockIds(m_blockList, false, false, false, curDb);

    ASSERT(es == Acad::eOk);

    ArxRleUtils::fillListBox(m_blockList, m_puBlockDef, 0);
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::OnSourceDatabaseChanged
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::OnSourceDatabaseChanged() 
{
    fillBlockList();
    setButtonModes();
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::OnDestDatabaseChanged
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::OnDestDatabaseChanged() 
{
    setButtonModes();
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::setButtonModes
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::setButtonModes()
{
    bool isExternal;
    AcDbDatabase* sourceDb = getSourceDb(isExternal);
    AcDbDatabase* destDb = getDestDb();

    bool allowClones;
    if (sourceDb == destDb)
        allowClones = false;
    else
        allowClones = true;

	ArxRleUtils::enableDlgItem(this, ARXRLE_INSERT_BN_INSERT_ALL, allowClones);
	ArxRleUtils::enableDlgItem(this, ARXRLE_INSERT_BN_INSERT_AS_BLOCK, allowClones);
	ArxRleUtils::enableDlgItem(this, ARXRLE_INSERT_BN_TRANSFER_BLKDEF, allowClones);
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::OnInsertDb
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::OnInsertDb() 
{
    UpdateData(TRUE);

    bool isExternal;
    AcDbDatabase* sourceDb = getSourceDb(isExternal);
    AcDbDatabase* destDb = getDestDb();
    ASSERT(sourceDb != destDb);

    Acad::ErrorStatus es;

        // lock the document we are inserting into
    ArxRleDocLockWrite docLock(destDb);
    if (docLock.lockAndSetCurrent() != Acad::eOk)
        return;

    bool preserveSrcDb = intToBool(m_preserveOriginalDb);
    if (!preserveSrcDb && !isExternal) {
        ArxRleUtils::alertBox(_T("Ignoring setting of \"Preserve source database\" since destroying\na database associated with a Document would be harsh."));
        preserveSrcDb = true;
    }

    // restore database to non-xref state (xes returns eOk if this
    // was necessary, and something else if it wasn't).
    Acad::ErrorStatus xes = sourceDb->restoreOriginalXrefSymbols();
    Acad::ErrorStatus xes2 = destDb->restoreOriginalXrefSymbols();
    es = destDb->insert(AcGeMatrix3d::kIdentity, sourceDb, preserveSrcDb);
    if (xes == Acad::eOk)
        xes = sourceDb->restoreForwardingXrefSymbols();
    if (xes2 == Acad::eOk)
        xes2 = destDb->restoreForwardingXrefSymbols();
    if (es == Acad::eOk) {
        ArxRleUiTdmDatabase dbox(destDb, this, _T("Inserted Database"));
        dbox.DoModal();

        doSaveOption(destDb);

        if (isExternal && !preserveSrcDb)
            reloadRaidedExternalDwg(sourceDb);
    }
    else {
        CString str;
        str.Format(_T("Insert failed: %s"), ArxRleUtils::rxErrorStr(es));
        ArxRleUtils::stopAlertBox(str);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcTransientReactors::OnInsertBlkDef
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::OnInsertBlkDef()
{
    CString blkName;
    m_ebDestName1.GetWindowText(blkName);

    if (!acdbSNValid(blkName, false)) {
        CString str;
        str.Format(_T("%s is not a valid block name."), blkName);
        ArxRleUtils::alertBox(str);
        return;
    }

    UpdateData(TRUE);

    bool isExternal;
    AcDbDatabase* sourceDb = getSourceDb(isExternal);
    AcDbDatabase* destDb = getDestDb();
    ASSERT(sourceDb != destDb);

    Acad::ErrorStatus es;

        // lock the document we are inserting into
    ArxRleDocLockWrite docLock(destDb);
    if (docLock.lockAndSetCurrent() != Acad::eOk)
        return;

    bool preserveSrcDb = intToBool(m_preserveOriginalDb);
    if (!preserveSrcDb && !isExternal) {
        ArxRleUtils::alertBox(_T("Ignoring setting of \"Preserve source database\" since destroying\na database associated with a Document would be harsh."));
        preserveSrcDb = true;
    }

    AcDbObjectId blkId;
    es = destDb->insert(blkId, blkName, sourceDb, preserveSrcDb);
    if (es == Acad::eOk) {
        ArxRleUiTdmDatabase dbox(destDb, this, _T("Inserted Database"));
        dbox.DoModal();

        doSaveOption(destDb);

        if (isExternal && !preserveSrcDb)
            reloadRaidedExternalDwg(sourceDb);
    }
    else {
        CString str;
        str.Format(_T("Insert failed: %s"), ArxRleUtils::rxErrorStr(es));
        ArxRleUtils::stopAlertBox(str);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::OnTransferBlkDef
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::OnTransferBlkDef()
{
        // get the block we're suppose to be wblocking
    int index = m_puBlockDef.GetCurSel();
    ASSERT(index != CB_ERR);

    CString srcBlkName;
    AcDbObjectId blkDefId;
    if (!m_blockList.GetAtIndex(index, srcBlkName, blkDefId)) {
        ASSERT(0);
        return;
    }

        // get name of destination block name
    CString destBlkName;
    m_ebDestName2.GetWindowText(destBlkName);

    if (!acdbSNValid(destBlkName, false)) {
        CString str;
        str.Format(_T("%s is not a valid block name."), destBlkName);
        ArxRleUtils::alertBox(str);
        return;
    }

    UpdateData(TRUE);

    bool isExternal;
    AcDbDatabase* sourceDb = getSourceDb(isExternal);
    AcDbDatabase* destDb = getDestDb();
    ASSERT(sourceDb != destDb);

        // lock the document we are inserting into
    ArxRleDocLockWrite docLock(destDb);
    if (docLock.lockAndSetCurrent() != Acad::eOk)
        return;

        // lock the document we are inserting from
    ArxRleDocLockWrite docLock2(sourceDb);
    if (docLock2.lock() != Acad::eOk)
        return;

    bool preserveSrcDb = intToBool(m_preserveOriginalDb);
    if (!preserveSrcDb && !isExternal) {
        ArxRleUtils::alertBox(_T("Ignoring setting of \"Preserve source database\" since destroying\na database associated with a Document would be harsh."));
        preserveSrcDb = true;
    }

    AcDbObjectId blkId;
    Acad::ErrorStatus es;
    es = destDb->insert(blkId, srcBlkName, destBlkName, sourceDb, preserveSrcDb);
    if (es == Acad::eOk) {
        ArxRleUiTdmDatabase dbox(destDb, this, _T("Inserted Database"));
        dbox.DoModal();

        doSaveOption(destDb);

        if (isExternal && !preserveSrcDb)
            reloadRaidedExternalDwg(sourceDb);
    }
    else {
        CString str;
        str.Format(_T("Insert failed: %s"), ArxRleUtils::rxErrorStr(es));
        ArxRleUtils::stopAlertBox(str);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::OnAddExternalDwg
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::OnAddExternalDwg()
{
    CString fname;
    Acad::ErrorStatus es;
    es = ArxRleUtils::getFileNameForRead(_T("Drawing File"), NULL, _T("dwg"),
                       fname, false, false);

    if (es == Acad::eOk) {
        if (hasDwgFile(m_extDwgNames, fname))
            ArxRleUtils::alertBox(_T("That DWG file is already in the list."));
        else {
            AcDbDatabase* db = new AcDbDatabase(false, true);
            es = db->readDwgFile(fname);

            if (es == Acad::eOk) {
                m_dbPtrs.append(db);
                m_extDwgNames.Add(fname);

                CString str;
                ArxRleUtils::dbToStr(db, str);
                m_lbSourceDb.AddString(str);
                m_lbDestDb.AddString(str);
            }
            else {
                CString str;
                str.Format(_T("ERROR: could not read DWG file: %s"), ArxRleUtils::rxErrorStr(es));
                ArxRleUtils::alertBox(str);
            }
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::reloadRaidedExternalDwg
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::reloadRaidedExternalDwg(AcDbDatabase* db)
{
    AcDbDatabase* tmpDb = NULL;

    const int len = m_dbPtrs.length();
    int i=0;
    for ( ; i<len; i++) {
        tmpDb = static_cast<AcDbDatabase*>(m_dbPtrs[i]);
        if (tmpDb == db)
            break;
    }

    delete db;    // delete this old damaged database;

    db = new AcDbDatabase(false, false);
    Acad::ErrorStatus es = db->readDwgFile(m_extDwgNames[i]);
    if (es == Acad::eOk)
        m_dbPtrs[i] = db;
    else {
        CString str;
        str.Format(_T("ERROR: could not reopen drawing file: %s"), ArxRleUtils::rxErrorStr(es));
        ArxRleUtils::alertBox(str);

            // get this out of the lists now.
        m_dbPtrs.removeAt(i);
        m_extDwgNames.RemoveAt(i);

        m_lbSourceDb.DeleteString(i);
        m_lbDestDb.DeleteString(i);

        m_lbSourceDb.SetCurSel(0);
        m_lbDestDb.SetCurSel(0);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::hasDwgFile
**
**  **jma
**
*************************************/

bool
ArxRleUiTdcInsert::hasDwgFile(CStringArray& dwgFiles, const CString& str)
{
    INT_PTR len = dwgFiles.GetSize();
    for (INT_PTR i = 0; i < len; i++) {
        if (dwgFiles[i] == str)
            return true;
    }

    return false;
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::doSaveOption
**
**  **jma
**
*************************************/

void
ArxRleUiTdcInsert::doSaveOption(AcDbDatabase* tmpDb)
{
    UpdateData(TRUE);

    if (m_saveAsDwg) {
        CString fname;
        Acad::ErrorStatus es;
        es = ArxRleUtils::getFileNameForWrite(_T("Save Database As"), NULL, _T("dwg"),
                                        fname, false, false);

        if (es == Acad::eOk) {
            es = tmpDb->saveAs(fname);
            if (es != Acad::eOk) {
                CString str;
                str.Format(_T("SaveAs failed: %s"), ArxRleUtils::rxErrorStr(es));
                ArxRleUtils::stopAlertBox(str);
            }
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::getSourceDb
**
**  **jma
**
*************************************/

AcDbDatabase*
ArxRleUiTdcInsert::getSourceDb(bool& isExternal) 
{
    isExternal = false;

    int index = m_lbSourceDb.GetCurSel();
    if (index == LB_ERR) {
        ASSERT(0);
        return NULL;
    }

    if (m_extDwgNames[index] != _T(""))
        isExternal = true;

    AcDbDatabase* curDb = static_cast<AcDbDatabase*>(m_dbPtrs[index]);
    ASSERT(curDb != NULL);
    return curDb;
}

/****************************************************************************
**
**  ArxRleUiTdcInsert::getDestDb
**
**  **jma
**
*************************************/

AcDbDatabase*
ArxRleUiTdcInsert::getDestDb() 
{
    int index = m_lbDestDb.GetCurSel();
    if (index == LB_ERR) {
        ASSERT(0);
        return NULL;
    }

    AcDbDatabase* curDb = static_cast<AcDbDatabase*>(m_dbPtrs[index]);
    ASSERT(curDb != NULL);
    return curDb;
}
