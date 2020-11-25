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

#include "ArxRleUiDlgSelSet.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"
#include "AcadUtils/ArxRleSelSet.h"
#include "Snoop/ArxRleUiTdmObjects.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiDlgSelSet::ArxRleUiDlgSelSet
**
**  **jma
**
*************************************/

ArxRleUiDlgSelSet::ArxRleUiDlgSelSet(CWnd* parent)
:	CAcUiDialog(ArxRleUiDlgSelSet::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxRleUiDlgSelSet)
    m_puMainSelectTypeIndex = 0;		// default to User Select
	m_filterLockedLayers = FALSE;
	m_rejectNonCurrent = FALSE;
	m_rejectPaperSpaceViewport = FALSE;
	m_useKwordCallback = FALSE;
	m_useOtherCallback = FALSE;
	m_allowDuplicates = FALSE;
	m_allowSingleOnly = FALSE;
	m_useSelectPrompt = FALSE;
	m_useRemovePrompt = FALSE;
	m_useFilter = FALSE;
	m_doIsKindOfTest = FALSE;
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSelSet::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgSelSet)
	DDX_Control(pDX, ARXRLE_SSGET_BN_SELECT_OBJS, m_selectButton);
	DDX_Control(pDX, ARXRLE_SSGET_CB_CLASSTYPE, m_puClassType);
	DDX_Control(pDX, ARXRLE_SSGET_CB_MAIN_SELECT_METHOD, m_puMainSelectType);
	DDX_CBIndex(pDX, ARXRLE_SSGET_CB_MAIN_SELECT_METHOD, m_puMainSelectTypeIndex);
	DDX_CBIndex(pDX, ARXRLE_SSGET_CB_CLASSTYPE, m_puClassTypeIndex);
	DDX_Check(pDX, ARXRLE_SSGET_CK_FILTER_LOCKED, m_filterLockedLayers);
	DDX_Check(pDX, ARXRLE_SSGET_CK_REJECT_NON_CURRENT, m_rejectNonCurrent);
	DDX_Check(pDX, ARXRLE_SSGET_CK_REJECT_PSPACE_VPORT, m_rejectPaperSpaceViewport);
	DDX_Check(pDX, ARXRLE_SSGET_CK_ALLOW_DUPS, m_allowDuplicates);
	DDX_Check(pDX, ARXRLE_SSGET_CK_SINGLE_ONLY, m_allowSingleOnly);
	DDX_Check(pDX, ARXRLE_SSGET_CK_KEYWORD_CALLBACK, m_useKwordCallback);
	DDX_Check(pDX, ARXRLE_SSGET_CK_OTHER_CALLBACK, m_useOtherCallback);
	DDX_Check(pDX, ARXRLE_SSGET_CK_USE_SELECT_PROMPT, m_useSelectPrompt);
	DDX_Check(pDX, ARXRLE_SSGET_CK_USE_REMOVE_PROMPT, m_useRemovePrompt);
	DDX_Text(pDX, ARXRLE_SSGET_EB_SELECT_PROMPT, m_selectPrompt);
	DDX_Text(pDX, ARXRLE_SSGET_EB_REMOVE_PROMPT, m_removePrompt);
	DDX_Check(pDX, ARXRLE_SSGET_CK_USE_FILTER, m_useFilter);
	DDX_Check(pDX, ARXRLE_SSGET_CK_DO_ISKINDOF_TEST, m_doIsKindOfTest);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgSelSet message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgSelSet, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxRleUiDlgSelSet)
	ON_BN_CLICKED(ARXRLE_SSGET_BN_SELECT_OBJS, OnSelectObjects)
	ON_BN_CLICKED(ARXRLE_SSGET_CK_USE_SELECT_PROMPT, OnPromptToggle)
	ON_BN_CLICKED(ARXRLE_SSGET_CK_USE_REMOVE_PROMPT, OnPromptToggle)
	ON_BN_CLICKED(ARXRLE_SSGET_CK_USE_FILTER, OnFilterToggle)
	ON_CBN_SELENDOK(ARXRLE_SSGET_CB_MAIN_SELECT_METHOD, OnSelendokSelectType)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgSelSet message handlers

/****************************************************************************
**
**  ArxRleUiDlgSelSet::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgSelSet::OnInitDialog() 
{
	CAcUiDialog::OnInitDialog();

    m_selectButton.AutoLoad();

		// do initial disabling
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_EB_SELECT_PROMPT, m_useSelectPrompt);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_EB_REMOVE_PROMPT, m_useRemovePrompt);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CB_CLASSTYPE, m_useFilter);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_DO_ISKINDOF_TEST, m_useFilter);

	m_puClassType.ResetContent();

	AcDbVoidPtrArray allEntClasses;
	getClassesDerivedFrom(AcDbEntity::desc(), allEntClasses);

	int index;
	AcRxClass* rxClass;
	int len = allEntClasses.length();
	for (int i=0; i<len; i++) {
		rxClass = static_cast<AcRxClass*>(allEntClasses[i]);
	    index = m_puClassType.AddString(rxClass->name());
		m_puClassType.SetItemDataPtr(index, rxClass);
	}

		// make AcDbEntity be the default selected class type
	m_puClassType.SelectString(-1, AcDbEntity::desc()->name());

	m_puMainSelectType.SetCurSel(0);	// set to "User"
	OnSelendokSelectType();				// fake out an event to update enabled modes

	return TRUE;
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::OnPromptToggle
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSelSet::OnPromptToggle() 
{
	UpdateData(TRUE);

	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_EB_SELECT_PROMPT, m_useSelectPrompt);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_EB_REMOVE_PROMPT, m_useRemovePrompt);
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::OnFilterToggle
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSelSet::OnFilterToggle() 
{
	UpdateData(TRUE);

	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CB_CLASSTYPE, m_useFilter);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_DO_ISKINDOF_TEST, m_useFilter);
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::setFlagModes
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSelSet::setFlagModes(bool allowed) 
{
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_FILTER_LOCKED, allowed);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_REJECT_NON_CURRENT, allowed);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_REJECT_PSPACE_VPORT, allowed);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_ALLOW_DUPS, allowed);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_SINGLE_ONLY, allowed);
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::setKeywordModes
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSelSet::setKeywordModes(bool allowed) 
{
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_KEYWORD_CALLBACK, allowed);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_OTHER_CALLBACK, allowed);
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::setPromptModes
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSelSet::setPromptModes(bool allowed) 
{
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_USE_SELECT_PROMPT, allowed);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_USE_REMOVE_PROMPT, allowed);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_EB_SELECT_PROMPT, (allowed && m_useSelectPrompt));
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_EB_REMOVE_PROMPT, (allowed && m_useRemovePrompt));
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::setFilterModes
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSelSet::setFilterModes(bool allowed) 
{
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_USE_FILTER, allowed);
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CB_CLASSTYPE, (allowed && m_useFilter));
	ArxRleUtils::enableDlgItem(this, ARXRLE_SSGET_CK_DO_ISKINDOF_TEST, (allowed && m_useFilter));
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::OnSelendokSelectType
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSelSet::OnSelendokSelectType()
{
	int index = m_puMainSelectType.GetCurSel();
	if (index != CB_ERR) {
		if (index == 0) {			// User
			setFlagModes(true);
			setKeywordModes(true);
			setPromptModes(true);
			setFilterModes(true);
		}
		else if (index == 5) {		// Last
			setFlagModes(false);
			setKeywordModes(false);
			setPromptModes(false);
			setFilterModes(false);
		}
		else if (index == 6) {		// Point
			setFlagModes(true);
			setKeywordModes(false);
			setPromptModes(false);
			setFilterModes(true);
		}
		else {
			setFlagModes(false);
			setKeywordModes(false);
			setPromptModes(false);
			setFilterModes(true);
		}
	}
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::OnSelectObjects
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSelSet::OnSelectObjects() 
{
	UpdateData(TRUE);	// make DDX calls happen so we have current data

	BeginEditorCommand();

	AcGePoint3d pt1, pt2;
	AcGePoint3dArray pts;
	Acad::ErrorStatus es;

    ArxRleSelSet::SelSetStatus stat = ArxRleSelSet::kNone;
	ArxRleSelSet ss;

	ss.setFilterLockedLayers(intToBool(m_filterLockedLayers));
	ss.setRejectNonCurrentSpace(intToBool(m_rejectNonCurrent));
	ss.setRejectPaperSpaceViewport(intToBool(m_rejectPaperSpaceViewport));
	ss.setAllowDuplicates(intToBool(m_allowDuplicates));
	ss.setAllowSingleOnly(intToBool(m_allowSingleOnly), true);

	if (m_useKwordCallback)
		ss.setKeywordCallback(_T("MYkeyword _ MYkeyword"), ArxRleUiDlgSelSet::keywordCallback);

	if (m_useOtherCallback)
		ss.setOtherCallback(ArxRleUiDlgSelSet::otherCallback);

	ArxRleRbList filterRbList;		// this will be NULL by default unless filter is present
	if (m_useFilter)
		getFilter(filterRbList);

	if (m_puMainSelectTypeIndex == 0) {			// User
		if (!m_useSelectPrompt && !m_useRemovePrompt)
			stat = ss.userSelect(filterRbList.data());
		else {
				// obviously, this would be much easier in real usage scenarios
				// since we would already know the value of the prompts.
			CString tmpStr1, tmpStr2;
			if (m_useSelectPrompt && (m_selectPrompt.IsEmpty() == FALSE))
				tmpStr1.Format(_T("\n%s"), m_selectPrompt);

			if (m_useRemovePrompt && (m_removePrompt.IsEmpty() == FALSE))
				tmpStr2.Format(_T("\n%s"), m_removePrompt);

			stat = ss.userSelect(tmpStr1, tmpStr2, filterRbList.data());
		}
	}
	else if (m_puMainSelectTypeIndex == 1) {		// Implied
		stat = ss.impliedSelect(filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 2) {		// Crossing
		if (!getBoxPoints(pt1, pt2, true))
			stat = ArxRleSelSet::kCanceled;
		else
			stat = ss.crossingSelect(pt1, pt2, filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 3) {		// Crossing Poly
		es = ArxRleUtils::getPlinePointArrayFromUser(pts);
		if (es != Acad::eOk)
			stat = ArxRleSelSet::kCanceled;
		else
			stat = ss.crossingPolygonSelect(pts, filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 4) {		// Fence
		es = ArxRleUtils::getPlinePointArrayFromUser(pts);
		if (es != Acad::eOk)
			stat = ArxRleSelSet::kCanceled;
		else
			stat = ss.fenceSelect(pts, filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 5) {		// Last
		stat = ss.lastSelect();
	}
	else if (m_puMainSelectTypeIndex == 6) {		// Point
		ArxRleUiPrPoint prPt(_T("Specify point"), NULL);
		if (prPt.go() != ArxRleUiPrBase::kOk)
			stat = ArxRleSelSet::kCanceled;
		else
			stat = ss.pointSelect(prPt.value(), filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 7) {		// Previous
		stat = ss.previousSelect(filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 8) {		// Window
		if (!getBoxPoints(pt1, pt2, false))
			stat = ArxRleSelSet::kCanceled;
		else
			stat = ss.windowSelect(pt1, pt2, filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 9) {		// Window Poly
		es = ArxRleUtils::getPlinePointArrayFromUser(pts);
		if (es != Acad::eOk)
			stat = ArxRleSelSet::kCanceled;
		else
			stat = ss.windowPolygonSelect(pts, filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 10) {		// Filter Only
		stat = ss.filterOnlySelect(filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 11) {		// All
		stat = ss.allSelect(filterRbList.data());
	}
	else if (m_puMainSelectTypeIndex == 12) {		// Box
		if (!getBoxPoints(pt1, pt2, false))
			stat = ArxRleSelSet::kCanceled;
		else
			stat = ss.boxSelect(pt1, pt2, filterRbList.data());
	}
	else {
		ASSERT(0);
	}

	if (stat == ArxRleSelSet::kSelected) {
		AcDbObjectIdArray objIds;
		ss.asArray(objIds);
		ArxRleUiTdmObjects dbox(objIds, acedGetAcadDwgView(), _T("Selected Objects"));
		dbox.DoModal();
	}
	else if (stat == ArxRleSelSet::kNone) {
		ArxRleUtils::alertBox(_T("Nothing selected!"));
	}
	else if (stat == ArxRleSelSet::kRejected) {
		acutPrintf(_T("\nRejected."));
	}
	else {
		acutPrintf(_T("\nCanceled."));
	}

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::getFilter
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSelSet::getFilter(ArxRleRbList& rbList)
{
	if (m_useFilter == false)
		return;

	void* tmpPtr = m_puClassType.GetItemDataPtr(m_puClassTypeIndex);
	if (tmpPtr == NULL) {
		ASSERT(0);
		return;
	}

	AcRxClass* classType = static_cast<AcRxClass*>(tmpPtr);
	
	AcDbVoidPtrArray filterClasses;
	filterClasses.append(classType);	// add our class for sure

		// if doing isKindOf test
	if (m_doIsKindOfTest == TRUE)
		getClassesDerivedFrom(classType, filterClasses);

	resbuf* tmpRb;

	tmpRb = acutNewRb(-4);
	acutNewString(_T("<or"), tmpRb->resval.rstring);
	rbList.addTail(tmpRb);

	const TCHAR* dxfStr;
	int len = filterClasses.length();
	for (int i=0; i<len; i++) {
		dxfStr = static_cast<AcRxClass*>(filterClasses[i])->dxfName();
		if (dxfStr) {
			tmpRb = acutNewRb(0);
			acutNewString(dxfStr, tmpRb->resval.rstring);
			rbList.addTail(tmpRb);
		}
		//else {
			//ASSERT(0);    // can't assert because AcDbCurve has no DXF name
		//}
	}

	tmpRb = acutNewRb(-4);
	acutNewString(_T("or>"), tmpRb->resval.rstring);
	rbList.addTail(tmpRb);
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::getBoxPoints
**
**  **jma
**
*************************************/

bool
ArxRleUiDlgSelSet::getBoxPoints(AcGePoint3d& pt1, AcGePoint3d& pt2, bool useDash)
{
	ArxRleUiPrPoint prPt(_T("Specify first corner"), NULL);
	if (prPt.go() != ArxRleUiPrBase::kOk)
		return false;

	ArxRleUiPrCorner prCorner(_T("Specify other corner"), NULL, prPt.value());
	prCorner.setUseDashedLine(useDash);

	if (prCorner.go() != ArxRleUiPrBase::kOk)
		return false;

	pt1 = prPt.value();
	pt2 = prCorner.value();

	return true;
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::keywordCallback
**
**  **jma
**
*************************************/

struct resbuf*
ArxRleUiDlgSelSet::keywordCallback(const TCHAR* str)
{
	ASSERT(str != NULL);

    acutPrintf(_T("\nKEYWORD: %s"), str);

    return NULL;
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::otherCallback
**
**  **jma
**
*************************************/

struct resbuf*
ArxRleUiDlgSelSet::otherCallback(const TCHAR* str)
{
	ASSERT(str != NULL);

    acutPrintf(_T("\nOTHER INPUT: %s"), str);

    return NULL;
}

/****************************************************************************
**
**  ArxRleUiDlgSelSet::getClassesDerivedFrom
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSelSet::getClassesDerivedFrom(AcRxClass* searchClassType, AcDbVoidPtrArray& derivedClasses)
{
    AcRxDictionaryIterator* iter;
    AcRxDictionary* classDict = acrxClassDictionary;
    if (classDict == NULL) {
        ASSERT(0);
        return;
    }

    iter = classDict->newIterator();
    if (iter != NULL) {
            // iterate over each item and get its info
        AcRxObject* classDictItem;
        AcRxClass* classObj;

        for (; !iter->done(); iter->next()) {
            classDictItem = iter->object();
            if ((classObj = AcRxClass::cast(classDictItem)) != NULL) {
                if (classObj->isDerivedFrom(static_cast<AcRxClass*>(searchClassType))) {
                    if (derivedClasses.contains(classObj) == false) {
                        derivedClasses.append(classObj);
                    }
                }
            }
            else {
                ASSERT(0);
            }
        }
        delete iter;
    }
    else {
        ASSERT(0);
    }
}
