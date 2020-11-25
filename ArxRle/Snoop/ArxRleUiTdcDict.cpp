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

#include "ArxRleUiTdcDict.h"
#include "AcadUtils/ArxRleUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiTdcDict::ArxRleUiTdcDict
**
**  **jma
**
*************************************/

ArxRleUiTdcDict::ArxRleUiTdcDict(const AcDbObjectId& dictId, bool isExtDict)
:   m_isRoot(!isExtDict),
    m_curIndex(0)
{
    m_rootObjId = dictId;

    //{{AFX_DATA_INIT(ArxRleUiTdcDict)
    m_dictIsHardOwner = FALSE;
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcDict::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDict::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiTdcDbObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcDict)
	DDX_Control(pDX, ARXRLE_DICTS_TR_DICT, m_dictTree);
	DDX_Control(pDX, ARXRLE_DICTS_LC_DICT_VALUES, m_dataList);
	DDX_Check(pDX, ARXRLE_DICTS_CK_HARDOWNER, m_dictIsHardOwner);
	DDX_Control(pDX, ARXRLE_DICTS_CB_MERGESTYLE, m_puMergeStyle);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcDict message map

BEGIN_MESSAGE_MAP(ArxRleUiTdcDict, ArxRleUiTdcDbObjectBase)
    //{{AFX_MSG_MAP(ArxRleUiTdcDict)
	ON_BN_CLICKED(ARXRLE_DICTS_CK_HARDOWNER, OnSetHardOwner)
	ON_CBN_SELENDOK(ARXRLE_DICTS_CB_MERGESTYLE, OnMergeStyleChanged)
	ON_NOTIFY(TVN_SELCHANGED, ARXRLE_DICTS_TR_DICT, OnSelchangedDict)
	ON_NOTIFY(TVN_ENDLABELEDIT, ARXRLE_DICTS_TR_DICT, OnEndlabeleditTreeDict)
	ON_NOTIFY(TVN_KEYDOWN, ARXRLE_DICTS_TR_DICT, OnKeydownTreeDict)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcDict message handlers

/****************************************************************************
**
**  ArxRleUiTdcDict::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcDict::OnInitDialog() 
{
    ArxRleUiTdcDbObjectBase::OnInitDialog();

    HTREEITEM rootItem;
    if (m_isRoot)
        rootItem = addOneTreeItem(_T("<Root Dictionary>"), m_rootObjId, TVI_ROOT);
    else
        rootItem = addOneTreeItem(_T("<Extension Dictionary>"), m_rootObjId, TVI_ROOT);

    addOneDictionary(m_rootObjId, rootItem);
    m_dictTree.SelectItem(rootItem);    // make this one the currently selected one

	buildColumns(m_dataList);
    displayCurrent(m_curIndex);    // 0

    m_dictTree.Expand(m_dictTree.GetRootItem(), TVE_EXPAND);

    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcDict::addOneTreeItem
**
**  **jma
**
*************************************/

HTREEITEM
ArxRleUiTdcDict::addOneTreeItem(LPCTSTR name, const AcDbObjectId& objId, HTREEITEM parent)
{
    m_dictObjIdList.append(objId);    // keep track of the objectId for each entry
    int index = m_dictObjIdList.length() - 1;
    ASSERT(index >= 0);

    TV_ITEM    tvItem;
    TV_INSERTSTRUCT tvInsert;

    tvItem.mask = TVIF_TEXT | TVIF_PARAM;
    tvItem.pszText = const_cast<TCHAR*>(name);
    tvItem.cchTextMax = lstrlen(name);
    tvItem.lParam = (LPARAM)index;        //index of AcDbObjectId
    
    tvInsert.item = tvItem;
    tvInsert.hInsertAfter = TVI_LAST;
    tvInsert.hParent = parent;

    return m_dictTree.InsertItem(&tvInsert);            
}

/****************************************************************************
**
**  ArxRleUiTdcDict::addOneDictionary
**      iterate over the dictionary and collect all the names contained
**  within it.
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDict::addOneDictionary(const AcDbObjectId& dictId, HTREEITEM parent)
{
    AcDbDictionary* dict;
    Acad::ErrorStatus es;
    es = acdbOpenObject(dict, dictId, AcDb::kForRead);
    if (es != Acad::eOk)
        return;

        // get an iterator over this dictionary
    AcDbDictionaryIterator* dictIter = dict->newIterator();
    ASSERT(dictIter != NULL);

        // walk dictionary and just collect all the names
        // of the entries
    HTREEITEM curItem;
    for (; !dictIter->done(); dictIter->next()) {
        curItem = addOneTreeItem(dictIter->name(), dictIter->objectId(), parent);
        addOneDictionary(dictIter->objectId(), curItem);
    }
    delete dictIter;
    dict->close();
}

/****************************************************************************
**
**  ArxRleUiTdcDict::displayCurrent
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDict::displayCurrent(int index)
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    ASSERT((index >= 0) && (index < m_dictObjIdList.length()));
    m_currentObjId = m_dictObjIdList[index];

    AcDbObject* obj = NULL;
    Acad::ErrorStatus es = acdbOpenObject(obj, m_currentObjId, AcDb::kForRead);
    setExtensionButtons(obj);
	setDictInfoButtons(obj);

    if (es == Acad::eOk) {
		display(obj);
        obj->close();
    }
    else {
        ArxRleUtils::rxErrorAlert(es);
    }

	drawPropsList(m_dataList);
}

/****************************************************************************
**
**  ArxRleUiTdcDict::setDictInfoButtons
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDict::setDictInfoButtons(AcDbObject* obj)
{
    AcDbDictionary* dict;
    if ((dict = AcDbDictionary::cast(obj)) != NULL) {
		m_dictIsHardOwner = dict->isTreatElementsAsHard();

		UpdateData(FALSE);	// update checkbox

		m_puMergeStyle.SetCurSel(drcToIndex(dict->mergeStyle()));	// update pop-up

		ArxRleUtils::hideDlgItem(this, ARXRLE_DICTS_CK_HARDOWNER, FALSE);
		ArxRleUtils::hideDlgItem(this, ARXRLE_DICTS_CB_MERGESTYLE, FALSE);
		ArxRleUtils::hideDlgItem(this, ARXRLE_DICTS_EB_MERGESTYLE_LABEL, FALSE);
	}
	else {
		ArxRleUtils::hideDlgItem(this, ARXRLE_DICTS_CK_HARDOWNER, TRUE);
		ArxRleUtils::hideDlgItem(this, ARXRLE_DICTS_CB_MERGESTYLE, TRUE);
		ArxRleUtils::hideDlgItem(this, ARXRLE_DICTS_EB_MERGESTYLE_LABEL, TRUE);
	}
}

/****************************************************************************
**
**  ArxRleUiTdcDict::OnSelchangedDict
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDict::OnSelchangedDict(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    m_curIndex = (int)(pNMTreeView->itemNew.lParam);
    displayCurrent(m_curIndex);
    *pResult = 0;
}

/****************************************************************************
**
**  ArxRleUiTdcDict::OnEndlabeleditTreeDict
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDict::OnEndlabeleditTreeDict(NMHDR* pNMHDR, LRESULT* pResult) 
{
    TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
    *pResult = 0;

    if (pTVDispInfo->item.mask & TVIF_TEXT) {
        HTREEITEM item = m_dictTree.GetSelectedItem();
        if (item == NULL)
            return;

        CString oldName = m_dictTree.GetItemText(item);
        CString newName = pTVDispInfo->item.pszText;

            // if it hasn't changed, don't do anything
        if (newName.CompareNoCase(oldName) == 0)
            return;

        if (renameCurrentItem(oldName, newName)) {
                // set new item name and re-sort entries in this node of tree
            m_dictTree.SetItem(&(pTVDispInfo->item));
            m_dictTree.SortChildren(m_dictTree.GetParentItem(item));
        }
    }    
}

/****************************************************************************
**
**  ArxRleUiTdcDict::OnKeydownTreeDict
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDict::OnKeydownTreeDict(NMHDR* pNMHDR, LRESULT* pResult) 
{
    TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;

    if (pTVKeyDown->wVKey == VK_DELETE) {
        CString itemName = m_dictTree.GetItemText(m_dictTree.GetSelectedItem());
        CString msg;
        msg.Format(_T("Are you sure you want to delete entry \"%s\"?"), itemName);
        if (ArxRleUtils::yesNoAlert(msg, IDNO) == IDYES)
            deleteCurrentItem();
    }
    
    *pResult = 0;
}

/****************************************************************************
**
**  ArxRleUiTdcDict::renameCurrentItem
**
**  **jma
**
*************************************/

bool
ArxRleUiTdcDict::renameCurrentItem(LPCTSTR oldName, LPCTSTR newName)
{
    bool retStatus = false;

    Acad::ErrorStatus es;
    AcDbObject* obj = openCurrentItem();
    if (obj == NULL)
        return retStatus;

        // get owner dictionary for this item
    AcDbObjectId ownerId = obj->ownerId();
    obj->close();

    AcDbDictionary* ownerDict;
    es = acdbOpenObject(ownerDict, obj->ownerId(), AcDb::kForWrite);

    if (es == Acad::eOk) {
        if (ownerDict->setName(oldName, newName) == Adesk::kFalse)
            ArxRleUtils::stopAlertBox(_T("Could not set entry to that name!"));
        else
            retStatus = true;    // everything worked

        ownerDict->close();
    }
    else {
        ArxRleUtils::stopAlertBox(_T("Couldn't rename that entry!"));
        ArxRleUtils::rxErrorAlert(es);
    }

    return retStatus;
}

/****************************************************************************
**
**  ArxRleUiTdcDict::deleteCurrentItem
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDict::deleteCurrentItem()
{
    AcDbObject* obj = openCurrentItem();
    if (obj == NULL)
        return;

        // get owner dictionary and objectId of this entry
    AcDbObjectId entryId = obj->objectId();
    AcDbObjectId ownerId = obj->ownerId();
    obj->close();

    Acad::ErrorStatus es;
    AcDbDictionary* ownerDict;
    es = acdbOpenObject(ownerDict, ownerId, AcDb::kForWrite);
    if (es == Acad::eOk) {
        es = ownerDict->remove(entryId);
        ownerDict->close();
        if (es == Acad::eOk) {
            HTREEITEM item = m_dictTree.GetSelectedItem();
            ASSERT(item);
            if (item)
                m_dictTree.DeleteItem(item);
        }
        else {
            ArxRleUtils::stopAlertBox(_T("Couldn't remove this item!"));
            ArxRleUtils::rxErrorAlert(es);
        }
    }
    else {
        ArxRleUtils::stopAlertBox(_T("Couldn't open parent dictionary of this item!"));
        ArxRleUtils::rxErrorAlert(es);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDict::OnSetHardOwner
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDict::OnSetHardOwner()
{
	UpdateData(TRUE);	// get current value of checkbox

    AcDbObject* obj = openCurrentItem();
    if (obj) {
        AcDbDictionary* dict = AcDbDictionary::cast(obj);
        if (dict) {
            dict->upgradeOpen();
            dict->setTreatElementsAsHard(intToBool(m_dictIsHardOwner));
        }
        obj->close();
        displayCurrent(m_curIndex);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDict::OnMergeStyleChanged
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDict::OnMergeStyleChanged()
{
	int index = m_puMergeStyle.GetCurSel();
	ASSERT(index != CB_ERR);

    AcDbObject* obj = openCurrentItem();
    if (obj) {
        AcDbDictionary* dict = AcDbDictionary::cast(obj);
        if (dict) {
            dict->upgradeOpen();
            dict->setMergeStyle(indexToDrc(index));
        }
        obj->close();
        displayCurrent(m_curIndex);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDict::indexToDrc
**
**  **jma
**
*************************************/

AcDb::DuplicateRecordCloning
ArxRleUiTdcDict::indexToDrc(int index) const
{
	if (index == 0)
		return AcDb::kDrcIgnore;
	else if (index == 1)
		return AcDb::kDrcReplace;
	else if (index == 2)
		return AcDb::kDrcMangleName;
	else {
		ASSERT(0);
		return AcDb::kDrcIgnore;
	}
}

/****************************************************************************
**
**  ArxRleUiTdcDict::drcToIndex
**
**  **jma
**
*************************************/

int
ArxRleUiTdcDict::drcToIndex(AcDb::DuplicateRecordCloning drc) const
{
	if (drc == AcDb::kDrcNotApplicable) {
		ASSERT(0);
		return 0;	// ignore
	}
	else if (drc == AcDb::kDrcIgnore) {
		return 0;
	}
	else if (drc == AcDb::kDrcReplace) {
		return 1;
	}
	else if (drc == AcDb::kDrcXrefMangleName) {
		ASSERT(0);
		return 0;
	}
	else if (drc == AcDb::kDrcMangleName) {
		return 2;
	}
	else if (drc == AcDb::kDrcUnmangleName) {
		ASSERT(0);
		return 0;
	}
	else {
		ASSERT(0);
		return 0;
	}
}
