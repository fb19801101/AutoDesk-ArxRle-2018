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

#include "ArxRleUiTdcCmds.h"
#include "AcadUtils/ArxRleUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiTdcCmds::ArxRleUiTdcCmds
**
**  **jma
**
*************************************/

ArxRleUiTdcCmds::ArxRleUiTdcCmds()
:   m_curCmdPtr(NULL)
{
    //{{AFX_DATA_INIT(ArxRleUiTdcCmds)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcCmds::~ArxRleUiTdcCmds
**
**  **jma
**
*************************************/

ArxRleUiTdcCmds::~ArxRleUiTdcCmds()
{
	deleteCmdGroupMap();
}

/****************************************************************************
**
**  ArxRleUiTdcCmds::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCmds::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiTdcRxObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcCmds)
	DDX_Control(pDX, ARXRLE_COMMANDS_TR_CMDS, m_cmdTree);
	DDX_Control(pDX, ARXRLE_COMMANDS_LC_DATA, m_dataList);
    //}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcCmds message map

BEGIN_MESSAGE_MAP(ArxRleUiTdcCmds, ArxRleUiTdcRxObjectBase)
    //{{AFX_MSG_MAP(ArxRleUiTdcCmds)
    ON_NOTIFY(TVN_SELCHANGED, ARXRLE_COMMANDS_TR_CMDS, OnSelchangedCmd)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcCmds message handlers

/****************************************************************************
**
**  ArxRleUiTdcCmds::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcCmds::OnInitDialog() 
{
    ArxRleUiTdcRxObjectBase::OnInitDialog();

	buildCmdGroupMap();

    POSITION pos;
    CString str;
    AcDbVoidPtrArray* cmds = NULL;
    HTREEITEM treeItem;
	AcEdCommand* tmpCmd;
	bool isFirst = true;

    for (pos = m_cmdMap.GetStartPosition(); pos != NULL;) {
        m_cmdMap.GetNextAssoc(pos, str, (void*&)cmds);
 		treeItem = addCmdTreeItem(str, NULL, TVI_ROOT, true);
		if (treeItem != NULL) {
			int len = cmds->length();
			for (int i=0; i<len; i++) {
				tmpCmd = static_cast<AcEdCommand*>(cmds->at(i));
				addCmdTreeItem(tmpCmd->localName(), tmpCmd, treeItem, true);
			}

			if (isFirst) {
				m_cmdTree.SelectItem(treeItem);		// make first one selected
				isFirst = false;
			}
		}
   }

	buildColumns(m_dataList);
    displayCurrent();

    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcCmds::addCmdTreeItem
**
**  **jma
**
*************************************/

HTREEITEM
ArxRleUiTdcCmds::addCmdTreeItem(LPCTSTR name, void* objPtr, HTREEITEM parent, bool sort)
{
    TV_ITEM         tvItem;
    TV_INSERTSTRUCT tvInsert;

    tvItem.mask = TVIF_TEXT | TVIF_PARAM;
    tvItem.pszText = const_cast<TCHAR*>(name);
    tvItem.cchTextMax = lstrlen(name);
    tvItem.lParam = (LPARAM)objPtr;        // save ptr of object
    
    tvInsert.item = tvItem;
    if (sort)
        tvInsert.hInsertAfter = TVI_SORT;
    else
        tvInsert.hInsertAfter = TVI_LAST;
    tvInsert.hParent = parent;

    return m_cmdTree.InsertItem(&tvInsert);            
}

/****************************************************************************
**
**  ArxRleUiTdcCmds::displayCurrent
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCmds::displayCurrent()
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

	CString str;

	if (m_curCmdPtr) {
		addToDataList(_T("Global Name"), m_curCmdPtr->globalName());
		addToDataList(_T("Local Name"), m_curCmdPtr->localName());

		Adesk::Int32 flags = m_curCmdPtr->commandFlags();
		addToDataList(_T("Command Flags"), ArxRleUtils::intToStr(flags, str));

		if (flags & ACRX_CMD_TRANSPARENT)
			addToDataList(_T(""), _T("Transparent"));
		else
			addToDataList(_T(""), _T("Modal"));

		if (flags & ACRX_CMD_USEPICKSET)
			addToDataList(NULL, _T("Use Pickset"));
		if (flags & ACRX_CMD_REDRAW)
			addToDataList(NULL, _T("Redraw"));
		if (flags & ACRX_CMD_NOPERSPECTIVE)
			addToDataList(NULL, _T("No Perspective"));
		if (flags & ACRX_CMD_NOMULTIPLE)
			addToDataList(NULL, _T("No Multiple"));
		if (flags & ACRX_CMD_NOTILEMODE)
			addToDataList(NULL, _T("No Tilemode"));
		if (flags & ACRX_CMD_NOPAPERSPACE)
			addToDataList(NULL, _T("No Paper Space"));
		// if (flags & ACRX_CMD_PLOTONLY)  *Obsolete*
	 	//         addToDataList(NULL, _T("Plot Only"));
		if (flags & ACRX_CMD_NOOEM)
			addToDataList(NULL, _T("No OEM"));
		if (flags & ACRX_CMD_UNDEFINED)
			addToDataList(NULL, _T("Undefined"));
		if (flags & ACRX_CMD_INPROGRESS)
			addToDataList(NULL, _T("In Progress"));
		if (flags & ACRX_CMD_DEFUN)
			addToDataList(NULL, _T("Lisp Defun"));
		if (flags & ACRX_CMD_NONEWSTACK)
			addToDataList(NULL, _T("No New Stack"));
		if (flags & ACRX_CMD_NOINTERNALLOCK)
			addToDataList(NULL, _T("No Internal Lock"));

		if (flags & ACRX_CMD_DOCREADLOCK)
			addToDataList(NULL, _T("Doc Read Lock"));
		else
			addToDataList(NULL, _T("Doc Write Lock"));

		if (flags & ACRX_CMD_DOCEXCLUSIVELOCK)
			addToDataList(NULL, _T("Doc Exclusive Lock"));
		else
			addToDataList(NULL, _T("Doc Shared Lock"));

		if (flags & ACRX_CMD_SESSION)
			addToDataList(NULL, _T("Run In Session Fiber"));

		addToDataList(_T("Command App"), ArxRleUtils::ptrToStr(m_curCmdPtr->commandApp(), str));
		addToDataList(_T("UI Context"), ArxRleUtils::ptrToStr(m_curCmdPtr->UIContext(), str));
		addToDataList(_T("Function Code"), ArxRleUtils::intToStr(m_curCmdPtr->functionCode(), str));
	}

	drawPropsList(m_dataList);
}

/****************************************************************************
**
**  ArxRleUiTdcCmds::OnSelchangedCmd
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCmds::OnSelchangedCmd(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    void* tmpPtr = (void*)pNMTreeView->itemNew.lParam;
	if (tmpPtr == NULL)
		m_curCmdPtr = NULL;
	else
		m_curCmdPtr = static_cast<AcEdCommand*>(tmpPtr);

    displayCurrent();

    *pResult = 0;
}

/****************************************************************************
**
**  ArxRleUiTdcCmds::buildCmdGroupMap
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCmds::buildCmdGroupMap()
{
    AcEdCommandIterator* iter = acedRegCmds->iterator();
    if (iter == NULL) {
        ASSERT(0);
        return;
    }
        // walk through the command stack and make a map of
		// command group to command.
	AcDbVoidPtrArray* tmpVoidPtrArray;
    for (; !iter->done(); iter->next()) {
		if (m_cmdMap.Lookup(iter->commandGroup(), (void*&)tmpVoidPtrArray)) {
			tmpVoidPtrArray->append(const_cast<AcEdCommand*>(iter->command()));
		}
		else {
			tmpVoidPtrArray = new AcDbVoidPtrArray;
			tmpVoidPtrArray->append(const_cast<AcEdCommand*>(iter->command()));
			m_cmdMap.SetAt(iter->commandGroup(), tmpVoidPtrArray);
		}
	}
    delete iter;
}

/****************************************************************************
**
**  ArxRleUiTdcCmds::deleteCmdGroupMap
**
**  **jma
**
*************************************/

void
ArxRleUiTdcCmds::deleteCmdGroupMap()
{
    POSITION pos;
    CString str;
    AcDbVoidPtrArray* cmds = NULL;

    for (pos = m_cmdMap.GetStartPosition(); pos != NULL;) {
        m_cmdMap.GetNextAssoc(pos, str, (void*&)cmds);
        delete cmds;
    }

    m_cmdMap.RemoveAll();
}
