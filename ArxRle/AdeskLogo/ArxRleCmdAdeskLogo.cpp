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

#include "ArxRleCmdAdeskLogo.h"
#include "ArxRleDbAdeskLogo.h"
#include "ArxRleDbAdeskLogoStyle.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleSelSet.h"
#include "Prompt/ArxRleKeywordArray.h"
#include "ArxRle.h"
#include "UiDlg/ArxRleUiDlgGenericDefId.h"



/****************************************************************************
**
**  ArxRleCmdAdeskLogo::registerCommandLineFunctions
**
**  **jma
**
*************************************/

void
ArxRleCmdAdeskLogo::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
	cmdStack->addCommand(appname, _T("ArxRleAdeskLogo"),            _T("AdeskLogo"),            ACRX_CMD_MODAL, &cmdLineMain);
	cmdStack->addCommand(appname, _T("ArxRleAdeskLogoAdd"),         _T("AdeskLogoAdd"),         ACRX_CMD_MODAL, &add);
	cmdStack->addCommand(appname, _T("ArxRleAdeskLogoModify"),      _T("AdeskLogoModify"),      ACRX_CMD_MODAL, &modify);

	cmdStack->addCommand(appname, _T("ArxRleAdeskLogoStyle"),		_T("AdeskLogoStyle"),       ACRX_CMD_MODAL, &styles);
	cmdStack->addCommand(appname, _T("ArxRleAdeskLogoStyleAdd"),    _T("AdeskLogoStyleAdd"),    ACRX_CMD_MODAL, &styleAdd);
	cmdStack->addCommand(appname, _T("ArxRleAdeskLogoStyleModify"), _T("AdeskLogoStyleModify"), ACRX_CMD_MODAL, &styleModify);

	cmdStack->addCommand(appname, _T("ArxRleAdeskLogoHardwire1"),   _T("AdeskLogoHardwire1"),   ACRX_CMD_MODAL, &hardwire);
	cmdStack->addCommand(appname, _T("ArxRleAdeskLogoHardwire2"),   _T("AdeskLogoHardwire2"),   ACRX_CMD_MODAL, &hardwire2);
}

/****************************************************************************
**
**  ArxRleCmdAdeskLogo::cmdLineMain
**
**  **jma
**
*************************************/

void
ArxRleCmdAdeskLogo::cmdLineMain()
{
		// ArxRleKeyword array allows us to use Global and Local keywords (i.e., English
		// and another language) without the need to worry about how it was picked.  In
		// this case, we haven't translated anything, so the keywords are the same.
		// see ArxRleKeywordArray for more details.
	ArxRleKeywordArray kwords(ArxRleApp::getApp()->dllInstance());
    kwords.append(_T("Add"),    _T("Add"));
    kwords.append(_T("Modify"), _T("Modify"));
    kwords.append(_T("Styles"), _T("Styles"));

    CString optionsStr, kwordStr;
    kwords.makeOptionsList(optionsStr);
    kwords.makeKeywordList(kwordStr);

	CString promptStr;
    promptStr.Format(_T("Adesk Logo options %s"), optionsStr);

    ArxRleUiPrKeyWord prCmd(promptStr, kwordStr);
    if (prCmd.go() != ArxRleUiPrBase::kOk)
        return;

    int keywordIndex;
    if (kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
        ASSERT(0);
        return;
    }

    if (keywordIndex == 0)
        add();
    else if (keywordIndex == 1)
        modify();
    else if (keywordIndex == 2)
        styles();
    else {
        ASSERT(0);
        return;
    }
}

/****************************************************************************
**
**  ArxRleCmdAdeskLogo::add
**
**  **jma
**
*************************************/

void
ArxRleCmdAdeskLogo::add()
{
    AcDbObjectId styleId;
    if (!getLogoStyle(styleId))
        return;

    ArxRleUiPrPoint prPt(_T("Location"), NULL);
    if (prPt.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrDistDef prScale(_T("Scale "), NULL, ArxRleUiPrDist::kNoNegNoZero, prPt.value(), 1.0);
    if (prScale.go() != ArxRleUiPrBase::kOk)
        return;

	ArxRleUiPrEntity prEnt(_T("Select an arbitrary entity to reference (or RETURN for NONE)"), NULL);
	prEnt.setAllowNone(true);
	if (prEnt.go() == ArxRleUiPrBase::kCancel)
		return;

    ArxRleDbAdeskLogo* logo = new ArxRleDbAdeskLogo;
    logo->setLocation(prPt.value());
    if (styleId != AcDbObjectId::kNull)
        logo->setLogoStyleId(styleId);

    logo->setScale(prScale.value());
	
	if (prEnt.objectId().isNull() == false)
		logo->setArbitraryReferenceId(prEnt.objectId());

    ArxRleUtils::transformToWcs(logo, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(logo);
}

/****************************************************************************
**
**  ArxRleCmdAdeskLogo::modify
**
**  **jma
**
*************************************/

void
ArxRleCmdAdeskLogo::modify()
{
	ArxRleUiPrEntity prEnt(_T("Select Adesk Logo to modify"), NULL);
	prEnt.addAllowedClass(ArxRleDbAdeskLogo::desc());
	prEnt.setFilterLockedLayers(true);

	if (prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleDbAdeskLogo* logo;
	Acad::ErrorStatus es = acdbOpenObject(logo, prEnt.objectId(), AcDb::kForRead);
	if (es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		return;
	}
		// get current values and close (they might pick our object again!)
    AcDbObjectId styleId = logo->logoStyleId();
	AcGeScale3d curScale = logo->scale();
	AcDbObjectId curRefId = logo->arbitraryReferenceId();
	logo->close();

		// get the logo style they want
    if (!getLogoStyle(styleId))
        return;

		// get the individual scale factors
	ArxRleUiPrDistDef prScaleX(_T("Scale X "), NULL, ArxRleUiPrDist::kNoNegNoZero, curScale.sx);
	ArxRleUiPrDistDef prScaleY(_T("Scale Y "), NULL, ArxRleUiPrDist::kNoNegNoZero, curScale.sy);
	ArxRleUiPrDistDef prScaleZ(_T("Scale Z "), NULL, ArxRleUiPrDist::kNoNegNoZero, curScale.sz);
	
	if ((prScaleX.go() != ArxRleUiPrBase::kOk) ||
		(prScaleY.go() != ArxRleUiPrBase::kOk) ||
		(prScaleZ.go() != ArxRleUiPrBase::kOk)) {
		return;
	}

	curScale.sx = prScaleX.value();
	curScale.sy = prScaleY.value();
	curScale.sz = prScaleZ.value();

	ArxRleUiPrEntity prRefEnt(_T("Select an arbitrary entity to reference (or RETURN for NONE)"), _T("Same"));
	prRefEnt.setAllowNone(true);

	ArxRleUiPrBase::Status stat = prRefEnt.go();
	if (stat == ArxRleUiPrBase::kNone) 
		;	// keep same one
	else if (stat == ArxRleUiPrBase::kOk)
		curRefId = prRefEnt.objectId();
	else
		return;

	es = acdbOpenObject(logo, prEnt.objectId(), AcDb::kForWrite);
	if (es == Acad::eOk) {
		logo->setLogoStyleId(styleId);
		logo->setScale(curScale);
		logo->setArbitraryReferenceId(curRefId);
		logo->close();
	}
	else
		ArxRleUtils::rxErrorMsg(es);
}

/****************************************************************************
**
**  ArxRleCmdAdeskLogo::styles
**
**  **jma
**
*************************************/

void
ArxRleCmdAdeskLogo::styles()
{
	ArxRleKeywordArray kwords(ArxRleApp::getApp()->dllInstance());
    kwords.append(_T("Add"),    _T("Add"));
    kwords.append(_T("Modify"), _T("Modify"));

    CString optionsStr, kwordStr;
    kwords.makeOptionsList(optionsStr);
    kwords.makeKeywordList(kwordStr);

	CString promptStr;
    promptStr.Format(_T("Adesk Logo Style options %s"), optionsStr);

    ArxRleUiPrKeyWord prCmd(promptStr, kwordStr);
    if (prCmd.go() != ArxRleUiPrBase::kOk)
        return;

    int keywordIndex;
    if (kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
        ASSERT(0);
        return;
    }

    if (keywordIndex == 0)
        styleAdd();
    else if (keywordIndex == 1)
        styleModify();
    else {
        ASSERT(0);
        return;
    }
}

/****************************************************************************
**
**  ArxRleCmdAdeskLogo::hardwire
**
**  **jma
**
*************************************/

void
ArxRleCmdAdeskLogo::hardwire()
{
	AcDbObjectId aecStyleId, gisStyleId;

    AcDbDictionary* testDict = ArxRleUtils::openDictionaryForWrite(
						ArxRleDbAdeskLogoStyle::dictName(), true,
						acdbHostApplicationServices()->workingDatabase());
    if (testDict) {
        Acad::ErrorStatus es;

        if (testDict->getAt(_T("AEC"), aecStyleId) != Acad::eOk) {
            ArxRleDbAdeskLogoStyle* newRec = new ArxRleDbAdeskLogoStyle;
            newRec->setLabel(_T("AEC"));
            newRec->setSolidFill(true);

            es = testDict->setAt(_T("AEC"), newRec, aecStyleId);
            if (es == Acad::eOk) {
                newRec->close();
            }
            else {
                ArxRleUtils::rxErrorAlert(es);
                delete newRec;
				aecStyleId = AcDbObjectId::kNull;
            }
        }
        if (testDict->getAt(_T("GIS"), gisStyleId) != Acad::eOk) {
            ArxRleDbAdeskLogoStyle* newRec = new ArxRleDbAdeskLogoStyle;
            newRec->setLabel(_T("GIS"));
            newRec->setSolidFill(false);

            es = testDict->setAt(_T("GIS"), newRec, gisStyleId);
            if (es == Acad::eOk) {
                newRec->close();
            }
            else {
                ArxRleUtils::rxErrorAlert(es);
                delete newRec;
				gisStyleId = AcDbObjectId::kNull;
            }
        }
        testDict->close();
    }
	else {
		acutPrintf(_T("\nHardwire test failed!"));
		return;
	}

	ArxRleDbAdeskLogo* logo;

		// add test AEC logo
	logo = new ArxRleDbAdeskLogo;
    logo->setLocation(AcGePoint3d(0.0, 2.0, 0.0));
	logo->setLogoStyleId(aecStyleId);
	logo->setScale(AcGeScale3d(2.0));

    ArxRleUtils::transformToWcs(logo, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(logo);

		// add test GIS logo
	logo = new ArxRleDbAdeskLogo;
    logo->setLocation(AcGePoint3d::kOrigin);
	logo->setLogoStyleId(gisStyleId);

    ArxRleUtils::transformToWcs(logo, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(logo);
}

/****************************************************************************
**
**  ArxRleCmdAdeskLogo::hardwire2
**
**  **jma
**
*************************************/

void
ArxRleCmdAdeskLogo::hardwire2()
{
	AcDbObjectId aecStyleId, gisStyleId;

    AcDbDictionary* testDict = ArxRleUtils::openDictionaryForWrite(
						ArxRleDbAdeskLogoStyle::dictName(), true,
						acdbHostApplicationServices()->workingDatabase());
    if (testDict) {
        Acad::ErrorStatus es;

        if (testDict->getAt(_T("AEC"), aecStyleId) != Acad::eOk) {
            ArxRleDbAdeskLogoStyle* newRec = new ArxRleDbAdeskLogoStyle;
            newRec->setLabel(_T("AEC 2"));
            newRec->setSolidFill(true);

            es = testDict->setAt(_T("AEC"), newRec, aecStyleId);
            if (es == Acad::eOk) {
                newRec->close();
            }
            else {
                ArxRleUtils::rxErrorAlert(es);
                delete newRec;
				aecStyleId = AcDbObjectId::kNull;
            }
        }
        if (testDict->getAt(_T("GIS"), gisStyleId) != Acad::eOk) {
            ArxRleDbAdeskLogoStyle* newRec = new ArxRleDbAdeskLogoStyle;
            newRec->setLabel(_T("GIS 2"));
            newRec->setSolidFill(false);

            es = testDict->setAt(_T("GIS"), newRec, gisStyleId);
            if (es == Acad::eOk) {
                newRec->close();
            }
            else {
                ArxRleUtils::rxErrorAlert(es);
                delete newRec;
				gisStyleId = AcDbObjectId::kNull;
            }
        }
        testDict->close();
    }
	else {
		acutPrintf(_T("\nHardwire test failed!"));
		return;
	}

	ArxRleDbAdeskLogo* logo;

		// add test AEC logo
	logo = new ArxRleDbAdeskLogo;
    logo->setLocation(AcGePoint3d(0.0, 10.0, 0.0));
	logo->setLogoStyleId(aecStyleId);
	logo->setScale(AcGeScale3d(2.0));

    ArxRleUtils::transformToWcs(logo, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(logo);

		// add test GIS logo
	logo = new ArxRleDbAdeskLogo;
    logo->setLocation(AcGePoint3d(0.0, 8.0, 0.0));
	logo->setLogoStyleId(gisStyleId);

    ArxRleUtils::transformToWcs(logo, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(logo);
}

/****************************************************************************
**
**  ArxRleCmdAdeskLogo::getLogoStyle
**
**  **jma
**
*************************************/

bool
ArxRleCmdAdeskLogo::getLogoStyle(AcDbObjectId& styleId)
{
		// try to get the standard style, which will hardwire it if it doesn't
		// yet exist
	AcDbObjectId standardStyleId =
				ArxRleDbAdeskLogoStyle::getStandardStyle(acdbHostApplicationServices()->workingDatabase(), true);

	ArxRleSdStrObjIdList logoStyles;
	AcDbObjectId logoStyleDictId = ArxRleUtils::getRegularDictionaryId(
						ArxRleDbAdeskLogoStyle::dictName(), true, acdbHostApplicationServices()->workingDatabase());

	ArxRleUtils::collectDictionaryEntryNames(logoStyleDictId, logoStyles, ArxRleDbAdeskLogoStyle::desc());

	if (logoStyles.Count() == 0) {
		ArxRleUtils::alertBox(_T("There are no Adesk Logo Styles to choose from."));
		return false;
	}

	ArxRleUiDlgGenericDefId dbox(acedGetAcadDwgView(),
									logoStyles, styleId, false);
	dbox.setDboxTitle(_T("Autodesk Logo Styles"));

	if (dbox.DoModal() == IDOK) {
		styleId = dbox.getSelectedId();
		return true;
	}

	return false;
}

/****************************************************************************
**
**  ArxRleCmdAdeskLogo::styleAdd
**
**  **jma
**
*************************************/

void
ArxRleCmdAdeskLogo::styleAdd()
{
    ArxRleUiPrString prName(_T("Logo Style Name"), false);
    ArxRleUiPrString prLabel(_T("Label"), true);

    if ((prName.go() != ArxRleUiPrBase::kOk) ||
        (prLabel.go() != ArxRleUiPrBase::kOk))
        return;

    if (acdbSNValid(prName.value(), false) != RTNORM) {
        acedAlert(_T("Invalid symbol name!"));
        return;
    }

    bool doSolidFill = true;
    if (ArxRleUtils::yesNoPromptDef(_T("Use solid fill "), doSolidFill, true) != ArxRleUiPrBase::kOk)
        return;

    AcDbDictionary* testDict = ArxRleUtils::openDictionaryForWrite(ArxRleDbAdeskLogoStyle::dictName(), true, acdbHostApplicationServices()->workingDatabase());
    if (testDict) {
        Acad::ErrorStatus es;

        if (testDict->has(prName.value()))
            ArxRleUtils::stopAlertBox(_T("Sorry, there is already an entry with that name."));
        else {
            ArxRleDbAdeskLogoStyle* newRec = new ArxRleDbAdeskLogoStyle;
            newRec->setLabel(prLabel.value());
            newRec->setSolidFill(doSolidFill);

            AcDbObjectId objId;
            es = testDict->setAt(prName.value(), newRec, objId);
            if (es == Acad::eOk) {
                ArxRleUtils::alertBox(_T("Added Logo Style successfully!"));
                newRec->close();
            }
            else {
                ArxRleUtils::rxErrorAlert(es);
                delete newRec;
            }
        }
        testDict->close();
    }
}

/****************************************************************************
**
**  ArxRleCmdAdeskLogo::styleModify
**
**  **jma
**
*************************************/

void
ArxRleCmdAdeskLogo::styleModify()
{
	AcDbObjectId styleId;

		// get the logo style they want to modify
    if (!getLogoStyle(styleId))
        return;

	ArxRleDbAdeskLogoStyle* logoStyle;
	Acad::ErrorStatus es = acdbOpenObject(logoStyle, styleId, AcDb::kForWrite);
	if (es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		return;
	}

    ArxRleUiPrStringDef prLabel(_T("Label "), logoStyle->label(), true);

    if (prLabel.go() != ArxRleUiPrBase::kOk) {
		logoStyle->close();
        return;
	}

    bool doSolidFill = true;
    if (ArxRleUtils::yesNoPromptDef(_T("Use solid fill "), doSolidFill, logoStyle->isSolidFill()) != ArxRleUiPrBase::kOk) {
		logoStyle->close();
        return;
	}

	logoStyle->setLabel(prLabel.value());
	logoStyle->setSolidFill(doSolidFill);
	logoStyle->close();
}
