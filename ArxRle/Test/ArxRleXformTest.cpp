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

#include "ArxRleXformTest.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleUtilsGe.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**    XformDbox::XformDbox    (constructor)
**
**    **jma
**
*************************************/

XformDbox::XformDbox(CWnd* pParent)
:    CDialog(_T("ARXRLE_DLG_XFORM"), pParent)
{
    //{{AFX_DATA_INIT(XformDbox)
    m_rotateType = kRbUcsZAxis;
    m_transType = kRbFromTo;
    m_xformCopy = FALSE;
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**    XformDbox::DoModal
**
**    **jma
**
*************************************/

INT_PTR
XformDbox::DoModal()
{
    INT_PTR retCode;

    while (1) {
        retCode = CDialog::DoModal();
		if (retCode == ARXRLE_XFORM_BN_ROTATE)
			rotate();
		else if (retCode == ARXRLE_XFORM_BN_MOVE)
			move();
		else if (retCode == ARXRLE_XFORM_BN_SCALE)
			scale();
		else if (retCode == ARXRLE_XFORM_BN_MIRROR)
			mirror();
		else if (retCode == ARXRLE_XFORM_BN_WCS_ORIGIN)
			wcsOrigin();
        else
            return(IDOK);

        ArxRleUtils::debugPause(NULL);    // allow user to see changes before returning dialog
    }
}

/****************************************************************************
**
**    XformDbox::OnCmdMsg
**
**    **jma
**
*************************************/

BOOL
XformDbox::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    m_buttonId = nID;
    return(CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo));
}

/****************************************************************************
**
**    XformDbox::DoDataExchange
**
**    **jma
**
*************************************/

void
XformDbox::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(XformDbox)
	DDX_Radio(pDX, ARXRLE_XFORM_RB_UCS_X, m_rotateType);
	DDX_Radio(pDX, ARXRLE_XFORM_RB_FROM_TO, m_transType);
	DDX_Check(pDX, ARXRLE_XFORM_CB_XFORM_COPY, m_xformCopy);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// XformDbox message map

BEGIN_MESSAGE_MAP(XformDbox, CDialog)
    //{{AFX_MSG_MAP(XformDbox)
	ON_BN_CLICKED(ARXRLE_XFORM_BN_MIRROR, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_XFORM_BN_MOVE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_XFORM_BN_ROTATE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_XFORM_BN_SCALE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_XFORM_BN_WCS_ORIGIN, OnButtonClicked)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XformDbox message handlers


/****************************************************************************
**
**    XformDbox::OnButtonClicked
**
**    **jma
**
*************************************/

void
XformDbox::OnButtonClicked() 
{
    UpdateData(TRUE);
    EndDialog(m_buttonId);
}

/****************************************************************************
**
**    XformDbox::rotate
**
**    **jma
**
*************************************/

void
XformDbox::rotate()
{
    AcGeMatrix3d xform;
    AcDbEntity* obj;
    AcGeVector3d axis;

    if ((obj = ArxRleUtils::selectEntity(NULL, AcDb::kForRead)) == NULL)
        return;

    if (m_rotateType == kRbUcsXAxis)
        axis = ArxRleUtils::getUcsXAxis(acdbHostApplicationServices()->workingDatabase());
    else if (m_rotateType == kRbUcsYAxis)
        axis = ArxRleUtils::getUcsYAxis(acdbHostApplicationServices()->workingDatabase());
    else if (m_rotateType == kRbUcsZAxis)
        axis = ArxRleUtils::getUcsZAxis(acdbHostApplicationServices()->workingDatabase());
    else if (m_rotateType == kRbEcsZAxis) {
        AcGeMatrix3d ecsMat;
        obj->getEcs(ecsMat);
        AcGePoint3d origin;
        AcGeVector3d xAxis;
        AcGeVector3d yAxis;
        ecsMat.getCoordSystem(origin, xAxis, yAxis, axis);

            // temporarily print out normal vector for debugging
        ArxRleUtils::stopAlertBox(_T("Doesn't work correctly yet...\nWaiting on AcDbEntity::ecs()"));
        CString str;
        acutPrintf(_T("\nECS X-AXIS: %s"), ArxRleUtils::vectorToStr(xAxis, str));
        acutPrintf(_T("\nECS Y-AXIS: %s"), ArxRleUtils::vectorToStr(yAxis, str));
        acutPrintf(_T("\nECS Z-AXIS: %s"), ArxRleUtils::vectorToStr(axis, str));
    }
    else {
        ASSERT(0);
    }

    ArxRleUiPrPoint prBasePt(_T("Base point"), NULL);
    ArxRleUiPrAngleDef prRotAng(_T("Rotation angle "), NULL, ArxRleUiPrAngle::kAny, ArxRleUtilsGe::kRad45);

    if ((prBasePt.go() == ArxRleUiPrBase::kOk) &&
        (prRotAng.go() == ArxRleUiPrBase::kOk)) {
        xform.setToRotation(prRotAng.value(), axis,
                        ArxRleUtils::ucsToWcs(prBasePt.value()));
        doXform(obj, xform);
    }
    obj->close();
}

/****************************************************************************
**
**    XformDbox::scale
**
**    **jma
**
*************************************/

void
XformDbox::scale()
{
    AcGeMatrix3d xform;
    AcDbEntity* obj;

    if ((obj = ArxRleUtils::selectEntity(NULL, AcDb::kForRead)) == NULL)
        return;

    ArxRleUiPrPoint prBasePt(_T("Base point"), NULL);
    ArxRleUiPrDist prScale(_T("Scale multiplier"), NULL, ArxRleUiPrDist::kNoNegNoZero);

    if ((prBasePt.go() == ArxRleUiPrBase::kOk) &&
        (prScale.go() == ArxRleUiPrBase::kOk)) {
        xform.setToScaling(prScale.value(),
                        ArxRleUtils::ucsToWcs(prBasePt.value()));
        doXform(obj, xform);
    }
    obj->close();
}

/****************************************************************************
**
**    XformDbox::move
**
**    **jma
**
*************************************/

void
XformDbox::move()
{
    AcGeMatrix3d xform;
    AcDbEntity* obj;
    AcGeVector3d transVec;

    if ((obj = ArxRleUtils::selectEntity(NULL, AcDb::kForRead)) == NULL)
        return;

    if (m_transType == kRbFromTo) {
        ArxRleUiPrPoint prBasePt(_T("Base point"), NULL);
        if (prBasePt.go() != ArxRleUiPrBase::kOk) {
            obj->close();
            return;
        }
        ArxRleUiPrPoint prToPt(_T("To point"), NULL, prBasePt.value());
        if (prToPt.go() != ArxRleUiPrBase::kOk) {
            obj->close();
            return;
        }
        transVec = (ArxRleUtils::ucsToWcs(prToPt.value()) -
                            ArxRleUtils::ucsToWcs(prBasePt.value()));
    }
    else {
        ArxRleUiPrPoint prDisp(_T("Displacement"), NULL);
        if (prDisp.go() != ArxRleUiPrBase::kOk) {
            obj->close();
            return;
        }
        transVec = ArxRleUtils::ucsToWcs(prDisp.value().asVector());
    }

    xform.setToTranslation(transVec);
    doXform(obj, xform);
    obj->close();
}

/****************************************************************************
**
**    XformDbox::mirror
**
**    **jma
**
*************************************/

void
XformDbox::mirror()
{
    AcGeMatrix3d xform;
    AcDbEntity* obj;

    if ((obj = ArxRleUtils::selectEntity(NULL, AcDb::kForRead)) == NULL)
        return;

    ArxRleUiPrPoint prPt1(_T("First point on mirror line"), NULL);
    if (prPt1.go() != ArxRleUiPrBase::kOk) {
        obj->close();
        return;
    }
    ArxRleUiPrPoint prPt2(_T("Second point on mirror line"), NULL, prPt1.value());
    if (prPt2.go() != ArxRleUiPrBase::kOk) {
        obj->close();
        return;
    }

    AcGeLine3d mirrorLine(ArxRleUtils::ucsToWcs(prPt1.value()),
                            ArxRleUtils::ucsToWcs(prPt2.value()));

    xform.setToMirroring(mirrorLine);
    doXform(obj, xform);
    obj->close();
}

/****************************************************************************
**
**    XformDbox::wcsOrigin
**        this is what you have to do before making a block definition
**    from existing entities.
**
**    **jma
**
*************************************/

void
XformDbox::wcsOrigin()
{
    AcGeMatrix3d xform;
    AcDbEntity* obj;

    if ((obj = ArxRleUtils::selectEntity(NULL, AcDb::kForRead)) == NULL)
        return;

    ArxRleUiPrPoint prBasePt(_T("Base point"), NULL);
    if (prBasePt.go() != ArxRleUiPrBase::kOk) {
        obj->close();
        return;
    }

    ArxRleUtils::getUcsToWcsOriginMatrix(xform,
                        ArxRleUtils::ucsToWcs(prBasePt.value()), acdbHostApplicationServices()->workingDatabase());
    doXform(obj, xform);
    obj->close();
}

/****************************************************************************
**
**    XformDbox::doXform
**
**    **jma
**
*************************************/

void
XformDbox::doXform(AcDbEntity* ent, const AcGeMatrix3d& m)
{
    if (m_xformCopy == FALSE) {
        Acad::ErrorStatus es = ent->upgradeOpen();
        if (es == Acad::eOk) {
            es = ent->transformBy(m);
            if (es != Acad::eOk)
                ArxRleUtils::rxErrorAlert(es);
        }
        else
            ArxRleUtils::rxErrorAlert(es);
    }
    else {
        AcDbObjectId ownerBlockId = ent->blockId();    // compiler complains!
        if (ArxRleUtils::cloneAndXformObjects(acdbHostApplicationServices()->workingDatabase(), ent->objectId(),
                            ownerBlockId, m, true) != Acad::eOk)
            ArxRleUtils::stopAlertBox(_T("ERROR: Couldn't clone entity!"));
    }
}

