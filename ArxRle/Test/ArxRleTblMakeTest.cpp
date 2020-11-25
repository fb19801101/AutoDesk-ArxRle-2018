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

#include "ArxRleTblMakeTest.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleSelSet.h"
#include "AcadUtils/ArxRleUtilsGe.h"
#include "AcadUtils/AcadStr.h"
#include "acedCmdNF.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**    cmdTestTblMake:
**
**    **jma
**
*************************************/

void
cmdTestTblMake()
{
    TblMakeDbox dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

/****************************************************************************
**
**    TblMakeDbox::TblMakeDbox    (constructor)
**
**    **jma
**
*************************************/

TblMakeDbox::TblMakeDbox(CWnd* pParent)
:    CDialog(_T("ARXRLE_DLG_TBLMAKE"), pParent)
{
    //{{AFX_DATA_INIT(TblMakeDbox)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**    TblMakeDbox::DoModal
**
**    **jma
**
*************************************/

INT_PTR
TblMakeDbox::DoModal()
{
    INT_PTR retCode;

    while (1) {
        retCode = CDialog::DoModal();
		if (retCode == ARXRLE_TBLMAKE_BN_ANONBLOCK)
			makeAnonymousBlock();
		else if (retCode == ARXRLE_TBLMAKE_BN_APPID)
			makeAppid();
		else if (retCode == ARXRLE_TBLMAKE_BN_BLOCK)
			makeNamedBlock();
		else if (retCode == ARXRLE_TBLMAKE_BN_DIMSTYLE)
			makeDimstyle();
		else if (retCode == ARXRLE_TBLMAKE_BN_LAYER)
			makeLayer();
		else if (retCode == ARXRLE_TBLMAKE_BN_LINETYPE)
			makeLinetype();
		else if (retCode == ARXRLE_TBLMAKE_BN_TEXTSTYLE)
			makeTextstyle();
		else if (retCode == ARXRLE_TBLMAKE_BN_UCS)
			makeUcs();
		else if (retCode == ARXRLE_TBLMAKE_BN_VIEW)
			makeView();
		else if (retCode == ARXRLE_TBLMAKE_BN_VIEWPORT)
			makeViewport();
        else
            return(IDOK);

        ArxRleUtils::debugPause(NULL);    // allow graphics to update and user to see entity
    }
}

/****************************************************************************
**
**    TblMakeDbox::OnCmdMsg
**
**    **jma
**
*************************************/

BOOL
TblMakeDbox::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    m_buttonId = nID;
    return(CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo));
}


/****************************************************************************
**
**    TblMakeDbox::DoDataExchange
**
**    **jma
**
*************************************/

void
TblMakeDbox::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(TblMakeDbox)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TblMakeDbox message map

BEGIN_MESSAGE_MAP(TblMakeDbox, CDialog)
    //{{AFX_MSG_MAP(TblMakeDbox)
	ON_BN_CLICKED(ARXRLE_TBLMAKE_BN_ANONBLOCK, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_TBLMAKE_BN_APPID, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_TBLMAKE_BN_BLOCK, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_TBLMAKE_BN_DIMSTYLE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_TBLMAKE_BN_LAYER, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_TBLMAKE_BN_LINETYPE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_TBLMAKE_BN_TEXTSTYLE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_TBLMAKE_BN_UCS, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_TBLMAKE_BN_VIEW, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_TBLMAKE_BN_VIEWPORT, OnButtonClicked)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TblMakeDbox message handlers

/****************************************************************************
**
**    TblMakeDbox::OnButtonClicked
**
**    **jma
**
*************************************/

void
TblMakeDbox::OnButtonClicked() 
{
    EndDialog(m_buttonId);
}

/****************************************************************************
**
**    TblMakeDbox::makeNamedBlock
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeNamedBlock()
{
        // get block name and make sure they don't redefine it
        // without specifically asking to
    ArxRleUiPrString prBlkname(_T("Block name"), FALSE);
    while (1) {
        if (prBlkname.go() == ArxRleUiPrBase::kCancel)
            return;
        if (ArxRleUtils::symbolExists(AcDbBlockTableRecord::desc(), prBlkname.value(),
						acdbHostApplicationServices()->workingDatabase())) {
            bool redefine;
            acutPrintf(_T("\nBlock \"%s\" already exists."), prBlkname.value());
            if (ArxRleUtils::yesNoPromptDef(_T("Redefine it? "), redefine, false) == ArxRleUiPrBase::kCancel)
                return;
            if (redefine == true)
                break;
        }
        else
            break;
    }
        // get the base point that defines insertion point for block
    ArxRleUiPrPoint prBasePt(_T("Base point"), NULL);
    if (prBasePt.go() != ArxRleUiPrBase::kOk)
        return;
    
        // now get the entities to include in the block
    ArxRleSelSet ss;
    if (ss.userSelect() != ArxRleSelSet::kSelected) {
        acutPrintf(_T("\nNothing selected."));
        return;
    }

    AcDbObjectId newBlkRecId;
    if (ArxRleUtils::defineNewBlock(prBlkname.value(), newBlkRecId,
			acdbHostApplicationServices()->workingDatabase()) != Acad::eOk)
        return;

        // must transform entities to WCS origin to be correct block def
    AcGeMatrix3d xformMat;
    ArxRleUtils::getUcsToWcsOriginMatrix(xformMat,
                            ArxRleUtils::ucsToWcs(prBasePt.value()), acdbHostApplicationServices()->workingDatabase());

    AcDbObjectIdArray entsToClone;
    ss.asArray(entsToClone);
    if (ArxRleUtils::cloneAndXformObjects(acdbHostApplicationServices()->workingDatabase(),
						entsToClone, newBlkRecId, xformMat, true) != Acad::eOk)
        ArxRleUtils::stopAlertBox(_T("ERROR: Could not clone entities into block def!"));

    acutPrintf(_T("\nCreated Block \"%s\"."), prBlkname.value());
}

/****************************************************************************
**
**    TblMakeDbox::makeAnonymousBlock
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeAnonymousBlock()
{
    ArxRleUiPrPoint prBasePt(_T("Base point"), NULL);
    if (prBasePt.go() != ArxRleUiPrBase::kOk)
        return;

        // now get the entities to select
    ArxRleSelSet ss;
    if (ss.userSelect() != ArxRleSelSet::kSelected) {
        acutPrintf(_T("\nNothing selected."));
        return;
    }

    TCHAR* blkName;
    AcDbObjectId newBlkRecId;
    AcDbBlockTableRecord* newBlkRec;
    if (ArxRleUtils::defineNewAnonymousBlock(newBlkRec, newBlkRecId, acdbHostApplicationServices()->workingDatabase()) != Acad::eOk)
        return;

    newBlkRec->getName(blkName);
    newBlkRec->close();    // don't need block rec open for clone

    AcGeMatrix3d xformMat;
    ArxRleUtils::getUcsToWcsOriginMatrix(xformMat,
                            ArxRleUtils::ucsToWcs(prBasePt.value()), acdbHostApplicationServices()->workingDatabase());

    AcDbObjectIdArray entsToClone;
    ss.asArray(entsToClone);
    if (ArxRleUtils::cloneAndXformObjects(acdbHostApplicationServices()->workingDatabase(), entsToClone,
                            newBlkRecId, xformMat, true) != Acad::eOk)
        ArxRleUtils::stopAlertBox(_T("ERROR: Could not clone entities into block def!"));

    acutPrintf(_T("\nCreated Block \"%s\"."), blkName);
    acutDelString(blkName);
}

/****************************************************************************
**
**    TblMakeDbox::makeDimstyle
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeDimstyle()
{
    CString symName;

    if (ArxRleUtils::getNewSymbolName(_T("Dimstyle name"), AcDbDimStyleTableRecord::desc(), symName) != ArxRleUiPrBase::kOk)
        return;

    AcDbDimStyleTableRecord* newRec = new AcDbDimStyleTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }

        // set some colors just for the fun of it
    AcCmColor color;
    color.setColorIndex(1);
    newRec->setDimclrd(color);
    color.setColorIndex(2);
    newRec->setDimclre(color);
    color.setColorIndex(3);
    newRec->setDimclrt(color);

    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nCreated dimstyle: \"%s\""), symName);
    else
        acutPrintf(_T("\nERROR: Could not create dimstyle: \"%s\""), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeLayer
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeLayer()
{
    CString symName;

    if (ArxRleUtils::getNewSymbolName(_T("Layer name"), AcDbLayerTableRecord::desc(), symName) != ArxRleUiPrBase::kOk)
        return;

        // get color in range 1 - 255, and on/off/freeze/etc.
    bool isFrozen, isOff, isLocked, isVPDFLT;
    ArxRleUiPrIntDef prColor(_T("Color number "), NULL, ArxRleUiPrInt::kRange, 7);
    prColor.setRange(1, 255);

    if ((prColor.go() != ArxRleUiPrBase::kOk) ||
        (ArxRleUtils::yesNoPromptDef(_T("Frozen "), isFrozen, false) != ArxRleUiPrBase::kOk) ||
        (ArxRleUtils::yesNoPromptDef(_T("Off "), isOff, false) != ArxRleUiPrBase::kOk) ||
        (ArxRleUtils::yesNoPromptDef(_T("Locked "), isLocked, false) != ArxRleUiPrBase::kOk) ||
        (ArxRleUtils::yesNoPromptDef(_T("VP default "), isVPDFLT, false) != ArxRleUiPrBase::kOk))
        return;

    AcDbLayerTableRecord* newRec = new AcDbLayerTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }

    AcCmColor cmColor;
    cmColor.setColorIndex(prColor.value());
    newRec->setColor(cmColor);

    newRec->setIsFrozen(isFrozen);
    newRec->setIsOff(isOff);
    newRec->setVPDFLT(isLocked);
    newRec->setIsLocked(isVPDFLT);

    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nCreated layer: \"%s\""), symName);
    else
        acutPrintf(_T("\nERROR: Could not create layer: \"%s\""), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeLinetype
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeLinetype()
{
    CString symName;

    if (ArxRleUtils::getNewSymbolName(_T("Linetype name"), AcDbLinetypeTableRecord::desc(), symName) != ArxRleUiPrBase::kOk)
        return;

    AcDbLinetypeTableRecord* newRec = new AcDbLinetypeTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }

    ArxRleUiPrString prDesc(_T("ASCII description"), TRUE);
    ArxRleUiPrDist prPatLength(_T("Pattern length"), NULL, ArxRleUiPrDist::kNoNegNoZero);
    ArxRleUiPrInt prDashCount(_T("Dash count"), NULL, ArxRleUiPrInt::kNoNegNoZero);
    if ((prDesc.go() != ArxRleUiPrBase::kOk) ||
        (prPatLength.go() != ArxRleUiPrBase::kOk) ||
        (prDashCount.go() != ArxRleUiPrBase::kOk)) {
            delete newRec;
        return;
    }

    newRec->setAsciiDescription(prDesc.value());
    newRec->setPatternLength(prPatLength.value());
    newRec->setNumDashes(prDashCount.value());
    
    ArxRleUiPrDist prDashLength(_T("Dash length"), NULL, ArxRleUiPrDist::kAny);
    for (int i=0; i < prDashCount.value(); i++) {
        if (prDashLength.go() != ArxRleUiPrBase::kOk) {
            delete newRec;
            return;
        }
        newRec->setDashLengthAt(i, prDashLength.value());
    }

    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nAdded linetype \"%s\"."), symName);
    else
        acutPrintf(_T("\nERROR: could not add linetype \"%s\"."), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeTextstyle
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeTextstyle()
{
    CString symName;

    if (ArxRleUtils::getNewSymbolName(_T("Textstyle name"), AcDbTextStyleTableRecord::desc(), symName) != ArxRleUiPrBase::kOk)
        return;

    AcDbTextStyleTableRecord* newRec = new AcDbTextStyleTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }

    CString fname;
    if (ArxRleUtils::getFileNameForRead(_T("Font file to use"),
                _T(""), _T("shx;ttf"), fname) != Acad::eOk) {
        delete newRec;
        return;
    }
    Acad::ErrorStatus es = newRec->setFileName(fname);
    if (es != Acad::eOk) {
        ArxRleUtils::rxErrorMsg(es);
        delete newRec;
        return;
    }
    newRec->setBigFontFileName(_T(""));    // must explicitly set to ""

    ArxRleUiPrDistDef    prTextSize(_T("Text size "), NULL, ArxRleUiPrDist::kNoNeg, 0.0);
    ArxRleUiPrAngleDef prOblique(_T("Oblique angle "), NULL, ArxRleUiPrAngle::kAny, 0.0);
    ArxRleUiPrDistDef    prScale(_T("X scale "), NULL, ArxRleUiPrDist::kNoNegNoZero, 1.0);
    prScale.setUnit(ArxRleUtils::kDecimal);
    
    if ((prTextSize.go() != ArxRleUiPrBase::kOk) ||
        (prOblique.go() != ArxRleUiPrBase::kOk) ||
        (prScale.go() != ArxRleUiPrBase::kOk)) {
        delete newRec;
        return;
    }
    newRec->setTextSize(prTextSize.value());
    newRec->setObliquingAngle(prOblique.value());
    newRec->setXScale(prScale.value());

    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nAdded textstyle \"%s\"."), symName);
    else
        acutPrintf(_T("\nERROR: could not add textstyle \"%s\"."), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeAppid
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeAppid()
{
    CString symName;

    if (ArxRleUtils::getNewSymbolName(_T("Application name"), AcDbRegAppTableRecord::desc(), symName) != ArxRleUiPrBase::kOk)
        return;

    AcDbRegAppTableRecord* newRec = new AcDbRegAppTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }
    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nAdded application \"%s\"."), symName);
    else
        acutPrintf(_T("\nERROR: could not add application \"%s\"."), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeUcs
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeUcs()
{
    CString symName;

    if (ArxRleUtils::getNewSymbolName(_T("UCS name"), AcDbUCSTableRecord::desc(), symName) != ArxRleUiPrBase::kOk)
        return;

        // mimic the UCS command's 3point option
    ArxRleUiPrPoint prOrigin(_T("Origin"), NULL);
    if (prOrigin.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrPoint prXAxis(_T("Point on positive portion of the X-axis"), NULL, prOrigin.value());
    ArxRleUiPrPoint prYAxis(_T("Point on positive-Y portion of the UCS XY plane"), NULL, prOrigin.value());

    if ((prXAxis.go() != ArxRleUiPrBase::kOk) ||
        (prYAxis.go() != ArxRleUiPrBase::kOk))
        return;

    AcDbUCSTableRecord* newRec = new AcDbUCSTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }

    AcGePoint3d originPt = ArxRleUtils::ucsToWcs(prOrigin.value());
    newRec->setOrigin(originPt);
    AcGeVector3d xAxis = ArxRleUtils::ucsToWcs(prXAxis.value()) - originPt;
        // calculate pseudo Y axis since it isn't necessarily perpendicular
    AcGeVector3d yAxis = ArxRleUtils::ucsToWcs(prYAxis.value()) - originPt;
    AcGeVector3d zAxis = xAxis.crossProduct(yAxis);
        // calculate true prependicular Y axis
    yAxis = zAxis.crossProduct(xAxis);

    newRec->setXAxis(xAxis.normalize());
    newRec->setYAxis(yAxis.normalize());

    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nAdded UCS \"%s\"."), symName);
    else
        acutPrintf(_T("\nERROR: could not add UCS \"%s\"."), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeView
**        Sample routine to test direct make of a View Table Record.
**    Trying to center the view around the bounding-box extents of a 
**    selected object, with the center of the bounding box in center of
**    the screen (similar to ZOOM,Center).  Doesn't really work yet!
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeView()
{
    AcDbEntity* obj;
    AcDbExtents extents;
    Acad::ErrorStatus es;

    if ((obj = ArxRleUtils::selectEntity(_T("\nSelect entity to center view around: "), AcDb::kForRead)) == NULL)
        return;

    if ((es = obj->getGeomExtents(extents)) != Acad::eOk) {
        ArxRleUtils::rxErrorMsg(es);
        obj->close();
        return;
    }
    obj->close();

    AcGePoint3d centerPt = ArxRleUtilsGe::midpoint(extents.minPoint(), extents.maxPoint());

    double deltaX = fabs(extents.maxPoint().x - extents.minPoint().x);
    double deltaY = fabs(extents.maxPoint().y - extents.minPoint().y);
    double deltaZ = fabs(extents.maxPoint().z - extents.minPoint().z);

    CString symName;
    if (ArxRleUtils::getNewSymbolName(_T("View name"), AcDbViewTableRecord::desc(), symName) != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrKeyWordDef prViewDir(_T("\nView direction [Top/BOttom/Front/BAck/Left/Right]"),
                    _T("Top BOttom Front BAck Left Right"), _T("Top"));
    if (prViewDir.go() != ArxRleUiPrBase::kOk)
        return;

    AcDbViewTableRecord* newRec = new AcDbViewTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }
    newRec->setIsPaperspaceView(Adesk::kFalse);
    newRec->setCenterPoint(ArxRleUtils::ucsToDcs(centerPt));    // how to get correct point?
    newRec->setTarget(centerPt);
    newRec->setHeight(deltaZ);
    newRec->setWidth(max(deltaX, deltaY));

        // get desired view direction
    AcGeVector3d viewDir;
    if (prViewDir.isKeyWordPicked(_T("Top")))
        viewDir = AcGeVector3d::kZAxis;
    else if (prViewDir.isKeyWordPicked(_T("BOttom")))
        viewDir = -AcGeVector3d::kZAxis;
    else if (prViewDir.isKeyWordPicked(_T("BAck")))
        viewDir = AcGeVector3d::kYAxis;
    else if (prViewDir.isKeyWordPicked(_T("Front")))
        viewDir = -AcGeVector3d::kYAxis;
    else if (prViewDir.isKeyWordPicked(_T("Right")))
        viewDir = AcGeVector3d::kXAxis;
    else if (prViewDir.isKeyWordPicked(_T("Left")))
        viewDir = -AcGeVector3d::kXAxis;
    else {
        ASSERT(0);
    }
    newRec->setViewDirection(viewDir);

    if (addToSymbolTableAndClose(newRec)) {
        acutPrintf(_T("\nAdded View \"%s\"."), symName);
        acedCommandS(RTSTR, _T("._-VIEW"), RTSTR, _T("_R"), RTSTR, symName, 0);
    }
    else
        acutPrintf(_T("\nERROR: could not add View \"%s\"."), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeViewport
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeViewport()
{
    ArxRleUtils::stopAlertBox(_T("STUB: viewport"));
}

/****************************************************************************
**
**    TblMakeDbox::addToSymbolTableAndClose
**
**    **jma
**
*************************************/

BOOL
TblMakeDbox::addToSymbolTableAndClose(AcDbSymbolTableRecord* symRec)
{
    BOOL stat = FALSE;

    AcDbSymbolTable* symTbl = ArxRleUtils::openSymbolTable(symRec->isA(),
									AcDb::kForWrite, acdbHostApplicationServices()->workingDatabase());
    if (symTbl) {
        Acad::ErrorStatus es = symTbl->add(symRec);
        if (es == Acad::eOk) {
            stat = TRUE;
            symRec->close();
        }
        else {
            ArxRleUtils::rxErrorAlert(es);
            delete symRec;
        }

        symTbl->close();
    }
    return(stat);
}

/****************************************************************************
**
**    TblMakeDbox::setSymbolName
**
**    **jma
**
*************************************/

BOOL
TblMakeDbox::setSymbolName(AcDbSymbolTableRecord* newRec, LPCTSTR newName)
{
    Acad::ErrorStatus es;
    CString str;

    es = newRec->setName(newName);
    if (es != Acad::eOk) {
        ArxRleUtils::rxErrorAlert(es);
        newRec->close();
        str.Format(_T("Invalid Symbol Name: \"%s\""), newName);
        ArxRleUtils::alertBox(str);
    }
    return(es);
}


