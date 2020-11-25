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

#include "ArxRleEntMakeTest.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleUtilsGe.h"
#include "AcadUtils/ArxRleSelSet.h"
#include "ArxRle.h"
#include "acedCmdNF.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//
//    NOTES:
//        The entmake functions in this module are designed to show how to create
//    entities based on user input.  Therefore, things like the current UCS are
//    of concern because points input by the user are in UCS, but points in the
//    database must be in WCS.  The general strategy is:
//
//        1) acquire points from the user in UCS without translating them to WCS.
//        2) do not set the Normal for any entity explicitly.  Instead, let it
//           default to (0, 0, 1).
//        3) transform the entity from the UCS to WCS to get the correct points,
//           normals, and angles that the database will expect.
//
//    This method allows you to "pretend" that everything is in WCS and you don't
//    have to bother with trasforming individual points and reverse engineering
//    any angles input by the user.  Huge improvement over old LISP/ADS days when
//  ECS information and reverse engineering was crucial.
//
//    **jma
//
//////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  EntMakeDbox::EntMakeDbox    (constructor)
**
**  **jma
**
*************************************/

EntMakeDbox::EntMakeDbox(CWnd* pParent)
:   CAcUiDialog(EntMakeDbox::IDD, pParent, ArxRleApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(EntMakeDbox)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

    SetPersistency(FALSE);
}

/****************************************************************************
**
**  EntMakeDbox::DoDataExchange
**
**  **jma
**
*************************************/

void
EntMakeDbox::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(EntMakeDbox)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

/****************************************************************************
**
**  EntMakeDbox::OnCmdMsg
**      record the id of the button pushed so we can temporarily dismiss the
**  dialog for graphics screen input and the bring it back again.
**
**  **jma
**
*************************************/

BOOL
EntMakeDbox::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    m_buttonId = nID;
    return CAcUiDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


/////////////////////////////////////////////////////////////////////////////
// EntMakeDbox message map

BEGIN_MESSAGE_MAP(EntMakeDbox, CAcUiDialog)
    //{{AFX_MSG_MAP(EntMakeDbox)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_POLYLINE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_2DPOLYLINE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_3DPOLYLINE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_3DSOLID, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_3POINTANGULAR, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_ALIGNED, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_ARC, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_ATTDEF, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_BLKREF, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_CIRCLE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_DIAMETRIC, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_ELLIPSE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_FACE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_FCF, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_HATCH, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_LEADER, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_LINE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_MINSERT, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_MLINE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_MTEXT, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_ORDINATE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_POINT, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_POLYFACE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_POLYGON, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_RADIAL, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_RAY, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_REGION, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_ROTATED, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_SOLID, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_SPLINE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_TEXT, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_TRACE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_VIEWPORT, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_XLINE, OnButtonClicked)
	ON_BN_CLICKED(ARXRLE_ENTMAKE_BN_2LINEANGULAR, OnButtonClicked)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EntMakeDbox message handlers

/****************************************************************************
**
**  EntMakeDbox::OnButtonClicked
**
**  **jma
**
*************************************/

void
EntMakeDbox::OnButtonClicked() 
{
    BeginEditorCommand();

	if (m_buttonId == ARXRLE_ENTMAKE_BN_POLYLINE)
		makePolyline();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_2DPOLYLINE)
		make2dPolyline();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_3DPOLYLINE)
		make3dPolyline();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_3DSOLID)
		make3dSolid();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_3POINTANGULAR)
		make3PointAngularDim();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_ALIGNED)
		makeAlignedDim();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_ARC)
		makeArc();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_ATTDEF)
		makeAttributeDefinition();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_BLKREF)
		makeBlockReference();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_CIRCLE)
		makeCircle();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_DIAMETRIC)
		makeDiametricDim();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_ELLIPSE)
		makeEllipse();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_FACE)
		makeFace();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_FCF)
		makeFcf();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_HATCH)
		makeHatch();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_LEADER)
		makeLeader();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_LINE)
		makeLine();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_MINSERT)
		makeMInsertBlock();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_MLINE)
		makeMline();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_MTEXT)
		makeMText();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_ORDINATE)
		makeOrdinateDim();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_POINT)
		makePoint();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_POLYFACE)
		makePolyFaceMesh();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_POLYGON)
		makePolygonMesh();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_RADIAL)
		makeRadialDim();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_RAY)
		makeRay();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_REGION)
		makeRegion();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_ROTATED)
		makeRotatedDim();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_SOLID)
		makeSolid();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_SPLINE)
		makeSpline();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_TEXT)
		makeText();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_TRACE)
		makeTrace();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_VIEWPORT)
		makeViewport();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_XLINE)
		makeXline();
	else if (m_buttonId == ARXRLE_ENTMAKE_BN_2LINEANGULAR)
		make2LineAngularDim();
    else {
        ASSERT(0);
    }

    ArxRleUtils::debugPause(NULL);

    CompleteEditorCommand();
}

/****************************************************************************
**
**  EntMakeDbox::getPointArray
**      get a series of points from the user, mimicking what the pline command
**  would do for straight line segments.
**
**  **jma
**
*************************************/

Acad::ErrorStatus
EntMakeDbox::getPointArray(AcGePoint3dArray& vertices, int& ptCount)
{
    int i = 0;

    ArxRleUiPrPoint prPoint(_T("Point"), NULL);
    prPoint.setAllowNone(true);
    while (prPoint.go() == ArxRleUiPrBase::kOk) {
        vertices.append(prPoint.value());
        if (i > 0)
            acedGrDraw(asDblArray(vertices[i-1]), asDblArray(vertices[i]), -1, 0);
        i++;
        prPoint.setBasePt(prPoint.value());
    }
    ptCount = vertices.length();
    if (ptCount < 2) {
        acutPrintf(_T("\nMust pick at least two points!"));
        return(Acad::eInvalidInput);
    }

    i = 1;
    while (i < ptCount) {
        acedGrDraw(asDblArray(vertices[i-1]), asDblArray(vertices[i]), -1, 0);
        i++;
    }
    return Acad::eOk;
}

/****************************************************************************
**
**  EntMakeDbox::makePolyline
**
**  **jma
**
*************************************/

void
EntMakeDbox::makePolyline()
{
    acutPrintf(_T("\nTesting make of AcDbPolyline..."));

    AcGePoint3dArray vertices;
    int ptCount;

    if (getPointArray(vertices, ptCount) != Acad::eOk)
        return;

    AcDbPolyline* pline = new AcDbPolyline(ptCount);    // optimized to know how many verts

        // append all the vertices (as 2D)
    Acad::ErrorStatus es;
    AcGePoint2d pt;
    for (int i=0;i<ptCount;i++) {
        pt.set(vertices[i].x, vertices[i].y);    // squash Z's in the current plane
        es = pline->addVertexAt(i, pt);
        if (es != Acad::eOk)
            ArxRleUtils::rxErrorMsg(es);
    }

        // set elevation of pline from elevation of first point's Z (as does PLINE command)
    pline->setElevation(vertices[0].z);

    pline->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(pline, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(pline);
}

/****************************************************************************
**
**  EntMakeDbox::make2dPolyline
**
**  NOTES:
**      This function uses the method of adding the polyline header
**  to the database first, and then adding individual vertices.  See
**  make3dPolyline() for an example of how to make vertices as part of
**  the constructor for the polyline header.
**
**  **jma
**
*************************************/

void
EntMakeDbox::make2dPolyline()
{
    acutPrintf(_T("\nTesting make of AcDb2dPolyline..."));

    AcGePoint3dArray vertices;
    int ptCount;

    if (getPointArray(vertices, ptCount) != Acad::eOk)
        return;

    AcDb2dPolyline* pline = new AcDb2dPolyline;
    pline->setDatabaseDefaults();

        // add polyline header to database
    if (ArxRleUtils::addToCurrentSpace(pline) != Acad::eOk) {
        delete pline;
        return;
    }
        // now append all the vertices
    for (int i=0;i<ptCount;i++) {
        AcDb2dVertex* vertex = new AcDb2dVertex;
        vertex->setPosition(vertices[i]);
        vertex->setPropertiesFrom(pline);
        pline->appendVertex(vertex);
        vertex->close();
    }
    ArxRleUtils::transformToWcs(pline, acdbHostApplicationServices()->workingDatabase());
    pline->close();
}

/****************************************************************************
**
**  EntMakeDbox::make3dPolyline
**
**  NOTES:
**      This method creates the vertices as part of the Polyline
**  header constructor.  See make2dPolyline() for method of adding one
**  vertex at a time.
**
**  **jma
**
*************************************/

void
EntMakeDbox::make3dPolyline()
{
    acutPrintf(_T("\nTesting make of AcDb3dPolyline..."));

    AcGePoint3dArray vertices;
    int ptCount;

    if (getPointArray(vertices, ptCount) != Acad::eOk)
        return;

    ArxRleUtils::ucsToWcs(vertices);

    AcDb3dPolyline* pline = new AcDb3dPolyline(AcDb::k3dSimplePoly, vertices);
    pline->setDatabaseDefaults();
    ArxRleUtils::addToCurrentSpaceAndClose(pline);
}

/****************************************************************************
**
**  EntMakeDbox::makeArc
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeArc()
{
    acutPrintf(_T("\nTesting make of AcDbArc..."));

    ArxRleUiPrPoint prCenterPt(_T("Center point"), NULL);
    if (prCenterPt.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrDist prRadius(_T("Radius"), NULL, ArxRleUiPrDist::kNoNegNoZero, prCenterPt.value());
    ArxRleUiPrAngle prStartAng(_T("Start angle"), NULL, ArxRleUiPrAngle::kAny, prCenterPt.value());
    ArxRleUiPrAngle prEndAng(_T("End angle"), NULL, ArxRleUiPrAngle::kAny, prCenterPt.value());

    if ((prRadius.go() != ArxRleUiPrBase::kOk) ||
        (prStartAng.go() != ArxRleUiPrBase::kOk) ||
        (prEndAng.go() != ArxRleUiPrBase::kOk))
        return;

    AcDbArc* arc = new AcDbArc;
    arc->setDatabaseDefaults();
    arc->setCenter(prCenterPt.value());
    arc->setRadius(prRadius.value());
    arc->setStartAngle(prStartAng.value());
    arc->setEndAngle(prEndAng.value());
    ArxRleUtils::transformToWcs(arc, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(arc);
}

/****************************************************************************
**
**  EntMakeDbox::makeCircle
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeCircle()
{
    acutPrintf(_T("\nTesting make of AcDbCircle..."));

    ArxRleUiPrPoint prCenterPt(_T("Center point"), NULL);
    if (prCenterPt.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrDist prRadius(_T("Radius"), NULL, ArxRleUiPrDist::kNoNegNoZero, prCenterPt.value());
    if (prRadius.go() != ArxRleUiPrBase::kOk)
        return;

    AcDbCircle* circle = new AcDbCircle;
    circle->setDatabaseDefaults();
    circle->setCenter(prCenterPt.value());
    circle->setRadius(prRadius.value());
    ArxRleUtils::transformToWcs(circle, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(circle);
}

/****************************************************************************
**
**  EntMakeDbox::makeEllipse
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeEllipse()
{
    acutPrintf(_T("\nTesting make of AcDbEllipse..."));

    ArxRleUiPrPoint prCenterPt(_T("Center point"), NULL);
    if (prCenterPt.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrPoint prAxis1(_T("Axis endpoint 1"), NULL, prCenterPt.value());
    ArxRleUiPrPoint prAxis2(_T("Axis endpoint 2"), NULL, prCenterPt.value());

    if ((prAxis1.go() != ArxRleUiPrBase::kOk) ||
        (prAxis2.go() != ArxRleUiPrBase::kOk))
        return;

        // figure out major axis and ratio of minor axis
    AcGePoint3d centerPt = prCenterPt.value();
    AcGeVector3d axis1 = prAxis1.value() - centerPt;
    AcGeVector3d axis2 = prAxis2.value() - centerPt;
    AcGeVector3d majorAxis;
    double ratio;
    if (axis1.length() > axis2.length()) {
        majorAxis = axis1;
        ratio = centerPt.distanceTo(prAxis2.value()) / centerPt.distanceTo(prAxis1.value());
    }
    else {
        majorAxis = axis2;
        ratio = centerPt.distanceTo(prAxis1.value()) / centerPt.distanceTo(prAxis2.value());
    }
        // make an ellipse with the specified parameters
    AcDbEllipse* ellipse = new AcDbEllipse;
    Acad::ErrorStatus es;
    es = ellipse->set(centerPt, AcGeVector3d::kZAxis, majorAxis, ratio);
    ArxRleUtils::rxErrorAlert(es);    // does message only if an error

    ellipse->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(ellipse, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(ellipse);
}

/****************************************************************************
**
**  EntMakeDbox::makeLeader
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeLeader()
{
    acutPrintf(_T("\nTesting make of AcDbLeader..."));

    AcGePoint3dArray vertices;
    int ptCount;

    if (getPointArray(vertices, ptCount) != Acad::eOk)
        return;

    AcDbLeader* leader = new AcDbLeader;

    for (int i=0;i<ptCount;i++)
        leader->appendVertex(vertices[i]);

    leader->setToSplineLeader();    // set to spline just for fun

    leader->setDatabaseDefaults();    // pick up default dimstyle, etc.
    ArxRleUtils::transformToWcs(leader, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(leader);
}

/****************************************************************************
**
**  EntMakeDbox::makeLine
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeLine()
{
    acutPrintf(_T("\nTesting make of AcDbLine..."));

    ArxRleUiPrPoint prStartPt(_T("Start point"), NULL);
    if (prStartPt.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrPoint prEndPt(_T("End point"), NULL, prStartPt.value());
    if (prEndPt.go() != ArxRleUiPrBase::kOk)
        return;

    AcDbLine* line = new AcDbLine;
    line->setDatabaseDefaults();
    line->setStartPoint(prStartPt.value());
    line->setEndPoint(prEndPt.value());
    ArxRleUtils::transformToWcs(line, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(line);
}

/****************************************************************************
**
**  EntMakeDbox::makeRay
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeRay()
{
    acutPrintf(_T("\nTesting make of AcDbRay..."));

    ArxRleUiPrPoint prFromPt(_T("From point"), NULL);
    if (prFromPt.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrPoint prThroughPt(_T("Through point"), NULL, prFromPt.value());
    if (prThroughPt.go() != ArxRleUiPrBase::kOk)
        return;

        // figure out the direction vector
    AcGeVector3d dirVec = prThroughPt.value() - prFromPt.value();

        // make a ray with the specified parameters
    AcDbRay* ray = new AcDbRay;
    ray->setBasePoint(prFromPt.value());
    ray->setUnitDir(dirVec);
    ray->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(ray, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(ray);
}

/****************************************************************************
**
**  EntMakeDbox::makeSpline
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeSpline()
{
    acutPrintf(_T("\nTesting make of AcDbSpline..."));

    AcGePoint3dArray vertices;
    int ptCount;

    if (getPointArray(vertices, ptCount) != Acad::eOk)
        return;

    AcDbSpline* spline = new AcDbSpline(vertices);
    spline->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(spline, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(spline);
}

/****************************************************************************
**
**  EntMakeDbox::makeXline
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeXline()
{
    ArxRleUiPrPoint prFromPt(_T("From point"), NULL);
    if (prFromPt.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrPoint prThroughPt(_T("Through point"), NULL, prFromPt.value());
    if (prThroughPt.go() != ArxRleUiPrBase::kOk)
        return;

        // figure out the direction vector
    AcGeVector3d dirVec = prThroughPt.value() - prFromPt.value();

        // make an xline with the specified parameters
    AcDbXline* xline = new AcDbXline;
    xline->setBasePoint(prFromPt.value());
    xline->setUnitDir(dirVec);
    xline->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(xline, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(xline);
}

/****************************************************************************
**
**  EntMakeDbox::makeVface
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeVface(AcDbPolyFaceMesh* pface, const AcGePoint3d& pt1, const AcGePoint3d& pt2,
        const AcGePoint3d& pt3, const AcGePoint3d& pt4)
{
    AcDbPolyFaceMeshVertex* vertex1 = new AcDbPolyFaceMeshVertex;
    AcDbPolyFaceMeshVertex* vertex2 = new AcDbPolyFaceMeshVertex;
    AcDbPolyFaceMeshVertex* vertex3 = new AcDbPolyFaceMeshVertex;
    AcDbPolyFaceMeshVertex* vertex4 = new AcDbPolyFaceMeshVertex;

    vertex1->setPosition(pt1);
    vertex2->setPosition(pt2);
    vertex3->setPosition(pt3);
    vertex4->setPosition(pt4);

    pface->appendVertex(vertex1);
    pface->appendVertex(vertex2);
    pface->appendVertex(vertex3);
    pface->appendVertex(vertex4);

    vertex1->close();
    vertex2->close();
    vertex3->close();
    vertex4->close();
}

/****************************************************************************
**
**  EntMakeDbox::recordVface
**
**  **jma
**
*************************************/

void
EntMakeDbox::recordVface(AcDbPolyFaceMesh* pface, int vertex1, int vertex2, int vertex3, int vertex4)
{
    AcDbFaceRecord* faceRec = new AcDbFaceRecord;

    faceRec->setVertexAt(0, vertex1);
    faceRec->setVertexAt(1, vertex2);
    faceRec->setVertexAt(2, vertex3);
    faceRec->setVertexAt(3, vertex4);

    Acad::ErrorStatus es = pface->appendFaceRecord(faceRec);
    ArxRleUtils::rxErrorMsg(es);

    faceRec->close();
}

/****************************************************************************
**
**  EntMakeDbox::makePolyFaceMesh
**
**  NOTES:
**      The AcDbPolyFaceMesh object must be added to the database
**  before you can add any vertices or faceRecords.  Also, all vertex
**  entities have to be added before ANY faceRecords are added.
**
**  **jma
**
*************************************/

void
EntMakeDbox::makePolyFaceMesh()
{
    acutPrintf(_T("\nTesting make of AcDbPolyFaceMesh..."));
    acutPrintf(_T("\nFaking a slab..."));

    ArxRleUiPrPoint prStartPt(_T("Start point"), NULL);
    if (prStartPt.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrPoint prEndPt(_T("End point"), NULL, prStartPt.value());
    ArxRleUiPrDist prWidth(_T("Width"), NULL, ArxRleUiPrDist::kNoNegNoZero, prStartPt.value());
    ArxRleUiPrDist prHeight(_T("Height"), NULL, ArxRleUiPrDist::kNoNegNoZero, prStartPt.value());

    if ((prEndPt.go() != ArxRleUiPrBase::kOk) ||
        (prWidth.go() != ArxRleUiPrBase::kOk) ||
        (prHeight.go() != ArxRleUiPrBase::kOk))
        return;

        // get Pface header into the database first
    AcDbPolyFaceMesh* pface = new AcDbPolyFaceMesh;
    pface->setDatabaseDefaults();
    if (ArxRleUtils::addToCurrentSpace(pface) != Acad::eOk) {
        delete pface;
        return;
    }

    AcGeLineSeg3d baseline(prStartPt.value(), prEndPt.value());
    AcGeVector3d perpVec = baseline.direction().perpVector();

    double halfWidth = prWidth.value() / 2.0;

    AcGePoint3d ptTop1, ptTop2, ptTop3, ptTop4;
    AcGePoint3d ptBottom1, ptBottom2, ptBottom3, ptBottom4;

        // make bottom of slab
    ptBottom1 = prStartPt.value() + (perpVec * halfWidth);
    ptBottom2 = prStartPt.value() + (-perpVec * halfWidth);
    ptBottom3 = prEndPt.value()   + (-perpVec * halfWidth);
    ptBottom4 = prEndPt.value()   + (perpVec * halfWidth);
    makeVface(pface, ptBottom1, ptBottom2, ptBottom3, ptBottom4);

        // make top of slab
    AcGeVector3d zAxis = AcGeVector3d::kZAxis * prHeight.value();
    ptTop1 = ptBottom1 + zAxis;
    ptTop2 = ptBottom2 + zAxis;
    ptTop3 = ptBottom3 + zAxis;
    ptTop4 = ptBottom4 + zAxis;
    makeVface(pface, ptTop1, ptTop2, ptTop3, ptTop4);

    recordVface(pface, 1, 2, 3, 4);
    recordVface(pface, 5, 6, 7, 8);

        // make sides of slab, re-using previously made vertices
        // (don't blame me, I didn't make up the structure for this!)
    recordVface(pface, 1, 2, 6, 5);
    recordVface(pface, 3, 4, 8, 7);
    recordVface(pface, 4, 1, 5, 8);
    recordVface(pface, 2, 3, 7, 6);

    ArxRleUtils::transformToWcs(pface, acdbHostApplicationServices()->workingDatabase());
    pface->close();
}

/****************************************************************************
**
**  EntMakeDbox::nextNvertex
**
**  **jma
**
*************************************/

void
EntMakeDbox::nextNvertex(int nSize, const AcGePoint3d& pt1, const AcGePoint3d& pt2, AcDbPolygonMesh* mesh)
{
    double xInc, yInc, zInc;
    AcGePoint3d newPt;
    int count = nSize - 1;

    xInc = (pt2.x - pt1.x) / count;
    yInc = (pt2.y - pt1.y) / count;
    zInc = (pt2.z - pt1.z) / count;

    newPt = pt1;
    while (count > 0) {
        newPt.x += xInc;
        newPt.y += yInc;
        newPt.z += zInc;
        addPolygonMeshVertex(mesh, newPt);
        count--;
    }
}

/****************************************************************************
**
**  EntMakeDbox::nextMvertex
**
**  **jma
**
*************************************/

AcGePoint3d
EntMakeDbox::nextMvertex(int mSize, int loop, const AcGePoint3d& pt1, const AcGePoint3d& pt2)
{
    double xInc, yInc, zInc;
    AcGePoint3d newPt;

    if (mSize != loop) {
        xInc = (pt2.x - pt1.x) / (mSize - loop);
        yInc = (pt2.y - pt1.y) / (mSize - loop);
        zInc = (pt2.z - pt1.z) / (mSize - loop);
        newPt.x = pt1.x + xInc;
        newPt.y = pt1.y + yInc;
        newPt.z = pt1.z + zInc;
    }
    else
        newPt = pt1;

    return(newPt);
}

/****************************************************************************
**
**  EntMakeDbox::addPolygonMeshVertex
**
**  **jma
**
*************************************/

void
EntMakeDbox::addPolygonMeshVertex(AcDbPolygonMesh* mesh, const AcGePoint3d& pt)
{
    AcDbPolygonMeshVertex* vertex = new AcDbPolygonMeshVertex;
    vertex->setPosition(pt);
    vertex->setPropertiesFrom(mesh);
    mesh->appendVertex(vertex);
    vertex->close();
}

/****************************************************************************
**
**  EntMakeDbox::makePolygonMesh
**
**  **jma
**
*************************************/

void
EntMakeDbox::makePolygonMesh()
{
    acutPrintf(_T("\nTesting make of AcDbPolygonMesh..."));

    ArxRleUiPrPoint prPt1(_T("First corner point"), NULL);
    ArxRleUiPrPoint prPt2(_T("Second corner point"), NULL);
    ArxRleUiPrPoint prPt3(_T("Third corner point"), NULL);
    ArxRleUiPrPoint prPt4(_T("Fourth corner point"), NULL);
    ArxRleUiPrInt prMSize(_T("Mesh M size"), NULL, ArxRleUiPrInt::kRange);
    ArxRleUiPrInt prNSize(_T("Mesh N size"), NULL, ArxRleUiPrInt::kRange);
    prMSize.setRange(2, 256);
    prNSize.setRange(2, 256);

    if ((prPt1.go() != ArxRleUiPrBase::kOk) ||
        (prPt2.go() != ArxRleUiPrBase::kOk) ||
        (prPt3.go() != ArxRleUiPrBase::kOk) ||
        (prPt4.go() != ArxRleUiPrBase::kOk) ||
        (prMSize.go() != ArxRleUiPrBase::kOk) ||
        (prNSize.go() != ArxRleUiPrBase::kOk))
        return;

    AcDbPolygonMesh* mesh = new AcDbPolygonMesh;
    mesh->setDatabaseDefaults();
    mesh->setMSize(prMSize.value());
    mesh->setNSize(prNSize.value());
    if (ArxRleUtils::addToCurrentSpace(mesh) != Acad::eOk) {
        delete mesh;
        return;
    }
        // set up looping points
    AcGePoint3d pt1 = prPt1.value();
    AcGePoint3d pt2 = prPt2.value();

    addPolygonMeshVertex(mesh, pt1);
    int loop = 1;
    nextNvertex(prNSize.value(), pt1, pt2, mesh);
    while (loop < prMSize.value()) {
        pt1 = nextMvertex(prMSize.value(), loop, pt1, prPt4.value());
        pt2 = nextMvertex(prMSize.value(), loop, pt2, prPt3.value());
        addPolygonMeshVertex(mesh, pt1);
        nextNvertex(prNSize.value(), pt1, pt2, mesh);
        loop++;
    }
    ArxRleUtils::transformToWcs(mesh, acdbHostApplicationServices()->workingDatabase());
    mesh->close();
}

/****************************************************************************
**
**  EntMakeDbox::make2LineAngularDim
**
**  **jma
**
*************************************/

void
EntMakeDbox::make2LineAngularDim()
{
    acutPrintf(_T("\nTesting make of AcDb2LineAngularDimension..."));

    AcGePoint3d pt1, pt2, pt3, pt4;

        // get end points of two lines
    if (getAngularDimLines(pt1, pt2, pt3, pt4) != Acad::eOk)
        return;

    ArxRleUiPrPoint prTextPt(_T("Text point"), NULL);
    if (prTextPt.go() != ArxRleUiPrBase::kOk)
        return;

    AcDb2LineAngularDimension* dim = new AcDb2LineAngularDimension(pt1, pt2, pt3, pt4, prTextPt.value());

        // arcPt automatically set from where text was placed,
        // unless you deliberately set the arcPt
    dim->setHorizontalRotation(getDimHorizRotation());
    dim->setTextPosition(prTextPt.value());
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(dim, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(dim);
}

/****************************************************************************
**
**  EntMakeDbox::make3PointAngularDim
**
**  **jma
**
*************************************/

void
EntMakeDbox::make3PointAngularDim()
{
    acutPrintf(_T("\nTesting make of AcDb3PointAngularDimension..."));

    AcGePoint3d pt1, pt2, centerPt;

        // get ARC
    if (get3PointArc(centerPt, pt1, pt2) != Acad::eOk)
        return;

    ArxRleUiPrPoint prTextPt(_T("Text point"), NULL);
    if (prTextPt.go() != ArxRleUiPrBase::kOk)
        return;

    AcDb3PointAngularDimension* dim =
            new AcDb3PointAngularDimension(centerPt, pt1, pt2, prTextPt.value());

        // arcPt automatically set from where text was placed,
        // unless you deliberately set the arcPt
    dim->setHorizontalRotation(getDimHorizRotation());
    dim->setTextPosition(prTextPt.value());
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();

    ArxRleUtils::transformToWcs(dim, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(dim);
}

/****************************************************************************
**
**  EntMakeDbox::makeAlignedDim
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeAlignedDim()
{
    acutPrintf(_T("\nTesting make of AcDbAlignedDimension..."));

    AcGePoint3d pt1, pt2;

        // get end points and angle for extension lines
    if (getLineOrTwoPoints(pt1, pt2) != Acad::eOk)
        return;

    ArxRleUiPrPoint prTextPt(_T("Text point"), NULL, ArxRleUtilsGe::midpoint(pt1, pt2));
    if (prTextPt.go() != ArxRleUiPrBase::kOk)
        return;

    AcDbAlignedDimension* dim = new AcDbAlignedDimension;
    dim->setXLine1Point(pt1);
    dim->setXLine2Point(pt2);

        // dimLinePt automatically set from where text was placed,
        // unless you deliberately set the dimLinePt
    dim->setHorizontalRotation(getDimHorizRotation());
    dim->setTextPosition(prTextPt.value());
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(dim, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(dim);
}

/****************************************************************************
**
**  EntMakeDbox::makeDiametricDim
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeDiametricDim()
{
    acutPrintf(_T("\nTesting make of AcDbDiametricDimension..."));

    double radius;
    AcGePoint3d centerPt;

    if (getArcCircleCenterRadius(centerPt, radius) != Acad::eOk)
        return;

    ArxRleUiPrPoint prTextPt(_T("Text point and dimension angle"), NULL, centerPt);
    if (prTextPt.go() != ArxRleUiPrBase::kOk)
        return;

        // get direction of dim line
    AcGeVector3d vDir = prTextPt.value() - centerPt;
    vDir.normalize();

    AcDbDiametricDimension* dim = new AcDbDiametricDimension;
    dim->setChordPoint(centerPt + (vDir * radius));
    dim->setFarChordPoint(centerPt + (-vDir * radius));

    dim->setHorizontalRotation(getDimHorizRotation());
    dim->setTextPosition(prTextPt.value());
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(dim, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(dim);
}

/****************************************************************************
**
**  EntMakeDbox::makeOrdinateDim
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeOrdinateDim()
{
    acutPrintf(_T("\nTesting make of AcDbOrdinateDimension..."));

    ArxRleUiPrKeyWordDef prDatumType(_T("Type [X datum/Y datum]"), _T("X Y"), _T("X"));
    if (prDatumType.go() != ArxRleUiPrBase::kOk)
        return;

    Adesk::Boolean useXAxis;
    if (prDatumType.isKeyWordPicked(_T("X")))
        useXAxis = Adesk::kTrue;
    else
        useXAxis = Adesk::kFalse;

    ArxRleUiPrPoint prFeaturePt(_T("Feature point"), NULL);
    if (prFeaturePt.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrPoint prLeaderPt(_T("Leader end point"), NULL);
    if (prLeaderPt.go() != ArxRleUiPrBase::kOk)
        return;

    AcDbOrdinateDimension* dim = new AcDbOrdinateDimension(useXAxis,
                        prFeaturePt.value(), prLeaderPt.value());
    dim->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(dim, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(dim);
}

/****************************************************************************
**
**  EntMakeDbox::makeRadialDim
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeRadialDim()
{
    acutPrintf(_T("\nTesting make of AcDbRadialDimension..."));

    double radius;
    AcGePoint3d centerPt;

    if (getArcCircleCenterRadius(centerPt, radius) != Acad::eOk)
        return;

    ArxRleUiPrPoint prTextPt(_T("Text point and dimension angle"), NULL, centerPt);
    if (prTextPt.go() != ArxRleUiPrBase::kOk)
        return;

        // get direction of dim line
    AcGeVector3d vDir = prTextPt.value() - centerPt;
    vDir.normalize();

    AcDbRadialDimension* dim = new AcDbRadialDimension;
    dim->setCenter(centerPt);
    dim->setChordPoint(centerPt + (vDir * radius));

    dim->setHorizontalRotation(getDimHorizRotation());
    dim->setTextPosition(prTextPt.value());
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(dim, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(dim);
}

/****************************************************************************
**
**  EntMakeDbox::makeRotatedDim
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeRotatedDim()
{
    acutPrintf(_T("\nTesting make of AcDbRotatedDimension..."));

    AcGePoint3d pt1, pt2;
    double ang;

        // get end points and angle for extension lines
    if ((getLineOrTwoPoints(pt1, pt2) != Acad::eOk) ||
        (getDimRotationAngle(ang) != Acad::eOk))
        return;

    ArxRleUiPrPoint prTextPt(_T("Text point"), NULL, ArxRleUtilsGe::midpoint(pt1, pt2));
    if (prTextPt.go() != ArxRleUiPrBase::kOk)
        return;

    AcDbRotatedDimension* dim = new AcDbRotatedDimension;
    dim->setXLine1Point(pt1);
    dim->setXLine2Point(pt2);
    dim->setRotation(ang);

        // dimLinePt automatically set from where text was placed,
        // unless you deliberately set the dimLinePt
    dim->setHorizontalRotation(getDimHorizRotation());
    dim->setTextPosition(prTextPt.value());
    dim->useSetTextPosition();    // make text go where user picked
    dim->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(dim, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(dim);
}

/****************************************************************************
**
**  EntMakeDbox::makeAttributes
**
**  **jma
**
*************************************/

Acad::ErrorStatus
EntMakeDbox::makeAttributes(const AcDbObjectId& blockRecordId, AcDbBlockReference* blkRef)
{
        // open the block record and find all the ATTDEFS
    AcDbObject* obj;
    Acad::ErrorStatus es = acdbOpenAcDbObject(obj, blockRecordId, AcDb::kForRead);
    if (es != Acad::eOk)
        return(Acad::eInvalidInput);

    AcDbBlockTableRecord* blkTblRec = AcDbBlockTableRecord::cast(obj);
    if (obj == NULL) {
        obj->close();
        return(Acad::eInvalidInput);
    }

    AcDbBlockTableRecordIterator* blkIter;
    if (blkTblRec->newIterator(blkIter) != Acad::eOk) {
        obj->close();
        return(Acad::eInvalidInput);
    }

    AcDbEntity* ent;
    AcDbAttributeDefinition* attdef;
    AcGeMatrix3d xformMat = blkRef->blockTransform();

    for (; !blkIter->done(); blkIter->step()) {
        if (blkIter->getEntity(ent, AcDb::kForRead) == Acad::eOk) {
                // deal only with non-constant ATTDEFS
            if (((attdef = AcDbAttributeDefinition::cast(ent)) != NULL) &&
                (attdef->isConstant() == Adesk::kFalse)) {
                        // create a new ATTRIBUTE entity
                AcDbAttribute* attrib = new AcDbAttribute;

                    // set ENTITY common fields
                attrib->setPropertiesFrom(attdef);

                    // set ATTDEF common fields
                attrib->setInvisible(attdef->isInvisible());
                attrib->setFieldLength(attdef->fieldLength());

                    // set TEXT common fields
                attrib->setThickness(attdef->thickness());
                attrib->setOblique(attdef->oblique());
                attrib->setRotation(attdef->rotation());
                attrib->setHeight(attdef->height());
                attrib->setTextStyle(attdef->textStyle());
                attrib->mirrorInX(attdef->isMirroredInX());
                attrib->mirrorInY(attdef->isMirroredInY());
                attrib->setHorizontalMode(attdef->horizontalMode());
                attrib->setVerticalMode(attdef->verticalMode());
                attrib->setPosition(attdef->position());
                attrib->setAlignmentPoint(attdef->alignmentPoint());

                    // put in default value for test
                acutPrintf(_T("\nUsing default ATTRIBUTE value..."));
                const TCHAR* tagStr = attdef->tagConst();
                attrib->setTag(tagStr);
                const TCHAR* valStr = attdef->textStringConst();
                attrib->setTextString(valStr);

                    // add to this block reference
                if (blkRef->appendAttribute(attrib) == Acad::eOk) {
                    attrib->transformBy(xformMat);
                    attrib->setWidthFactor(attdef->widthFactor());    // has to be set after transform
                    attrib->close();
                }
                else {
                    acutPrintf(_T("\nERROR: Could not append ATTRIBUTE."));
                    delete attrib;
                }
            }
            ent->close();
        }
    }

    delete blkIter;
    blkTblRec->close();
    return(Acad::eOk);
}

/****************************************************************************
**
**  EntMakeDbox::getBlockSpecFromUser
**
**  **jma
**
*************************************/

Acad::ErrorStatus
EntMakeDbox::getBlockSpecFromUser(AcDbObjectId& blockId, AcGePoint3d& insertPt,
                        double& scale, double& rotation)
{
    CString blkName;

    if ((ArxRleUtils::getExistingSymbolName(_T("Block name"), AcDbBlockTableRecord::desc(), blkName) != ArxRleUiPrBase::kOk) ||
        (ArxRleUtils::nameToSymbolId(AcDbBlockTableRecord::desc(), blkName, blockId, acdbHostApplicationServices()->workingDatabase()) != Acad::eOk))
        return(Acad::eInvalidInput);

    ArxRleUiPrPoint prInsertPt(_T("Insert point"), NULL);
    ArxRleUiPrDist prScale(_T("Uniform scale"), NULL, ArxRleUiPrDist::kNoNegNoZero);
    
    if ((prInsertPt.go() != ArxRleUiPrBase::kOk) ||
        (prScale.go() != ArxRleUiPrBase::kOk))
        return(Acad::eInvalidInput);

    ArxRleUiPrAngle prRotation(_T("Rotation"), NULL, ArxRleUiPrAngle::kAny, prInsertPt.value());
    if (prRotation.go() != ArxRleUiPrBase::kOk)
        return(Acad::eInvalidInput);

    insertPt = prInsertPt.value();
    scale = prScale.value();
    rotation = prRotation.value();
    return(Acad::eOk);
}

/****************************************************************************
**
**  EntMakeDbox::makeBlockReference
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeBlockReference()
{
    AcDbObjectId blockId;
    double scale, rotation;
    AcGePoint3d insertPt;

    if (getBlockSpecFromUser(blockId, insertPt, scale, rotation) != Acad::eOk)
        return;

    AcDbBlockReference* blkRef = new AcDbBlockReference;

        // set this block to point at the correct block ref
    Acad::ErrorStatus es = blkRef->setBlockTableRecord(blockId);
    if (es != Acad::eOk) {
        delete blkRef;
        ArxRleUtils::rxErrorAlert(es);
        return;
    }

    blkRef->setPosition(insertPt);
    blkRef->setRotation(rotation);
    blkRef->setScaleFactors(scale);

    if (ArxRleUtils::addToCurrentSpace(blkRef) == Acad::eOk) {
        makeAttributes(blockId, blkRef);
        ArxRleUtils::transformToWcs(blkRef, acdbHostApplicationServices()->workingDatabase());
        blkRef->close();
    }
    else
        delete blkRef;
}

/****************************************************************************
**
**  EntMakeDbox::makeMInsertBlock
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeMInsertBlock()
{
    AcDbObjectId blockId;
    double scale, rotation;
    AcGePoint3d insertPt;

    if (getBlockSpecFromUser(blockId, insertPt, scale, rotation) != Acad::eOk)
        return;

    ArxRleUiPrInt prRows(_T("Rows"), NULL, ArxRleUiPrInt::kRange);
    ArxRleUiPrInt prColumns(_T("Columns"), NULL, ArxRleUiPrInt::kRange);
    ArxRleUiPrDist prRowSpace(_T("Distance between rows"), NULL, ArxRleUiPrDist::kNoZero, insertPt);
    ArxRleUiPrDist prColSpace(_T("Distance between columns"), NULL, ArxRleUiPrDist::kNoZero, insertPt);

    prRows.setRange(1, 256);
    prColumns.setRange(1, 256);

    if ((prRows.go() != ArxRleUiPrBase::kOk) ||
        (prColumns.go() != ArxRleUiPrBase::kOk) ||
        (prRowSpace.go() != ArxRleUiPrBase::kOk) ||
        (prColSpace.go() != ArxRleUiPrBase::kOk))
        return;

    AcDbMInsertBlock* blkRef = new AcDbMInsertBlock;

        // set this block to point at the correct block ref
    if (blkRef->setBlockTableRecord(blockId) != Acad::eOk) {
        delete blkRef;
        return;
    }

    blkRef->setPosition(insertPt);
    blkRef->setRotation(rotation);
    blkRef->setScaleFactors(scale);

    blkRef->setColumns(prColumns.value());
    blkRef->setRows(prRows.value());
    blkRef->setColumnSpacing(prColSpace.value());
    blkRef->setRowSpacing(prRowSpace.value());

    if (ArxRleUtils::addToCurrentSpace(blkRef) == Acad::eOk) {
        makeAttributes(blockId, blkRef);
        ArxRleUtils::transformToWcs(blkRef, acdbHostApplicationServices()->workingDatabase());
        blkRef->close();
    }
    else
        delete blkRef;
}

/****************************************************************************
**
**  EntMakeDbox::makeHatch
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeHatch()
{
        // get selection set, but don't do any error checking
        // of the ent types to see how API handles it.
    ArxRleSelSet ss;
    if (ss.userSelect() != ArxRleSelSet::kSelected)
        return;

    AcDbObjectIdArray objIds;
    ss.asArray(objIds);

        // loop until we get a name that works
    ArxRleUiPrStringDef prPat(_T("Predefined pattern name "), _T("HONEY"), FALSE);
    AcDbHatch* hatch = new AcDbHatch;
    Acad::ErrorStatus es;

    while (1) {
        if (prPat.go() != ArxRleUiPrBase::kOk) {
            delete hatch;
            return;
        }
        es = hatch->setPattern(AcDbHatch::kPreDefined, prPat.value());
        if (es != Acad::eOk) {
            ArxRleUtils::rxErrorAlert(es);
            ArxRleUtils::stopAlertBox(_T("ERROR: Can't set it to that name!"));
        }
        else
            break;
    }

    ArxRleUiPrDistDef prScale(_T("Scale "), NULL, ArxRleUiPrDist::kNoNegNoZero, 1.0);
    ArxRleUiPrAngleDef prAng(_T("Angle "), NULL, ArxRleUiPrAngle::kAny, 0.0);
    if ((prScale.go() != ArxRleUiPrBase::kOk) ||
        (prAng.go() != ArxRleUiPrBase::kOk)) {
        delete hatch;
        return;
    }

    hatch->setDatabaseDefaults();
    hatch->setAssociative(Adesk::kTrue);    // BUG: doesn't do squat! have to set the reactor yourself to get associativity!

    es = hatch->appendLoop(AcDbHatch::kExternal, objIds);
    ArxRleUtils::rxErrorAlert(es);

    es = hatch->setPatternScale(prScale.value());
    ArxRleUtils::rxErrorAlert(es);

    es = hatch->setPatternAngle(prAng.value());
    ArxRleUtils::rxErrorAlert(es);

// BUG ALERT: have to set pattern name last in order for scale and angle to take effect
// remove this when bug is fixed!
    es = hatch->setPattern(AcDbHatch::kPreDefined, prPat.value());

// Hatch does not seem to work correctly in non WCS coord system when using
// referenced objects
    hatch->setNormal(ArxRleUtils::getUcsZAxis(acdbHostApplicationServices()->workingDatabase()));
    hatch->evaluateHatch();        // crucial call or nothing gets displayed!

    ArxRleUtils::addToCurrentSpaceAndClose(hatch);
}

/****************************************************************************
**
**  EntMakeDbox::makeFace
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeFace()
{
    acutPrintf(_T("\nTesting make of AcDbFace..."));

    ArxRleUiPrPoint prPt1(_T("Point 1"), NULL);
    ArxRleUiPrPoint prPt2(_T("Point 2"), NULL);
    ArxRleUiPrPoint prPt3(_T("Point 3"), NULL);
    ArxRleUiPrPoint prPt4(_T("Point 4"), NULL);

    if ((prPt1.go() != ArxRleUiPrBase::kOk) ||
        (prPt2.go() != ArxRleUiPrBase::kOk) ||
        (prPt3.go() != ArxRleUiPrBase::kOk) ||
        (prPt4.go() != ArxRleUiPrBase::kOk))
        return;

    AcDbFace* face = new AcDbFace;
    face->setVertexAt(0, prPt1.value());
    face->setVertexAt(1, prPt2.value());
    face->setVertexAt(2, prPt3.value());
    face->setVertexAt(3, prPt4.value());
    acutPrintf(_T("\nSetting edge 2 invisible..."));
    face->makeEdgeInvisibleAt(2);
    face->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(face, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(face);
}

/****************************************************************************
**
**  EntMakeDbox::makeFcf
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeFcf()
{
    acutPrintf(_T("\nTesting make of AcDbFcf..."));

    ArxRleUiPrPoint prPt(_T("Location point"), NULL);
    if (prPt.go() != ArxRleUiPrBase::kOk)
        return;

    AcDbFcf* fcf = new AcDbFcf;

    fcf->setLocation(prPt.value());
    fcf->setText(_T("{\\Fgdt;j}%%v%%v%%v%%v%%v\n{\\Fgdt;t}%%v%%v%%v%%v%%v"));
    fcf->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(fcf, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(fcf);
}

/****************************************************************************
**
**  EntMakeDbox::makeMline
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeMline()
{
    acutPrintf(_T("\nTesting make of AcDbMline..."));

    AcGePoint3dArray vertices;
    int ptCount;

    if (getPointArray(vertices, ptCount) != Acad::eOk)
        return;

    AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if (pDb == NULL)
        return;

    AcDbMline* mline = new AcDbMline;

    mline->setStyle(pDb->cmlstyleID());            // must set explicitly!
    mline->setNormal(AcGeVector3d::kZAxis);        // must set explicitly!
    mline->setScale(pDb->cmlscale());            // must set explicitly!
    mline->setJustification(static_cast<Mline::MlineJustification>(pDb->cmljust()));

        // now append all the vertices
    Acad::ErrorStatus es;
    for (int i=0;i<ptCount;i++)
        es = mline->appendSeg(vertices[i]);

    mline->setDatabaseDefaults();        // should set above params but doesn't
    ArxRleUtils::transformToWcs(mline, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(mline);    
}

/****************************************************************************
**
**  EntMakeDbox::makePoint
**
**  **jma
**
*************************************/

void
EntMakeDbox::makePoint()
{
    AcGePoint3d pt;

    acutPrintf(_T("\nTesting make of AcDbPoint..."));

    ArxRleUiPrPoint prPt(_T("Point"), NULL);
    if (prPt.go() == ArxRleUiPrBase::kOk) {
        AcDbPoint* point = new AcDbPoint;
        point->setPosition(prPt.value());
        point->setEcsRotation(getDimHorizRotation());
        point->setDatabaseDefaults();
        ArxRleUtils::transformToWcs(point, acdbHostApplicationServices()->workingDatabase());
        ArxRleUtils::addToCurrentSpaceAndClose(point);
    }
}

/****************************************************************************
**
**  EntMakeDbox::makeSolid
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeSolid()
{
    acutPrintf(_T("\nTesting make of AcDbSolid..."));

    ArxRleUiPrPoint prPt1(_T("Point 1"), NULL);
    ArxRleUiPrPoint prPt2(_T("Point 2"), NULL);
    ArxRleUiPrPoint prPt3(_T("Point 3"), NULL);
    ArxRleUiPrPoint prPt4(_T("Point 4"), NULL);

    if ((prPt1.go() != ArxRleUiPrBase::kOk) ||
        (prPt2.go() != ArxRleUiPrBase::kOk) ||
        (prPt3.go() != ArxRleUiPrBase::kOk) ||
        (prPt4.go() != ArxRleUiPrBase::kOk))
        return;

    AcDbSolid* solid = new AcDbSolid;
    solid->setPointAt(0, prPt1.value());
    solid->setPointAt(1, prPt2.value());
    solid->setPointAt(2, prPt3.value());
    solid->setPointAt(3, prPt4.value());

    solid->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(solid, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(solid);
}

/****************************************************************************
**
**  EntMakeDbox::makeTrace
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeTrace()
{
    acutPrintf(_T("\nTesting make of AcDbTrace..."));

    ArxRleUiPrPoint prPt1(_T("Point 1"), NULL);
    ArxRleUiPrPoint prPt2(_T("Point 2"), NULL);
    ArxRleUiPrPoint prPt3(_T("Point 3"), NULL);
    ArxRleUiPrPoint prPt4(_T("Point 4"), NULL);

    if ((prPt1.go() != ArxRleUiPrBase::kOk) ||
        (prPt2.go() != ArxRleUiPrBase::kOk) ||
        (prPt3.go() != ArxRleUiPrBase::kOk) ||
        (prPt4.go() != ArxRleUiPrBase::kOk))
        return;

    AcDbTrace* trace = new AcDbTrace;
    trace->setPointAt(0, prPt1.value());
    trace->setPointAt(1, prPt2.value());
    trace->setPointAt(2, prPt3.value());
    trace->setPointAt(3, prPt4.value());

    trace->setDatabaseDefaults();
    ArxRleUtils::transformToWcs(trace, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(trace);
}

/****************************************************************************
**
**  EntMakeDbox::makeViewport
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeViewport()
{
    if (ArxRleUtils::isPaperSpace(acdbHostApplicationServices()->workingDatabase()) == false) {
        ArxRleUtils::stopAlertBox(_T("Can only make an AcDbViewport while in PaperSpace."));
        return;
    }

    AcGePoint3d pt1, pt2;

    ArxRleUiPrPoint prCorner1(_T("First point"), NULL);
    if (prCorner1.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrCorner prCorner2(_T("Other corner"), NULL, prCorner1.value());
    if (prCorner2.go() != ArxRleUiPrBase::kOk)
        return;

    AcDbViewport* vport = new AcDbViewport;

    vport->setHeight(fabs(prCorner2.value().y - prCorner1.value().y));
    vport->setWidth(fabs(prCorner2.value().x - prCorner1.value().x));
    vport->setCenterPoint(ArxRleUtilsGe::midpoint(prCorner1.value(), prCorner2.value()));
    vport->setDatabaseDefaults();

    ArxRleUtils::addToCurrentSpace(vport);
    vport->setOn();        // can't be set until after it is added to database
    int vpNum = vport->number();
    vport->close();

    acedCommandS(RTSTR, _T("_MSPACE"), 0);        // ModelSpace must be active to set current

    Acad::ErrorStatus es = acedSetCurrentVPort(vpNum);
    ArxRleUtils::rxErrorAlert(es);

    acedCommandS(RTSTR, _T("_ZOOM"), RTSTR, _T("_Extents"), 0);    // zoom to a reasonable spot
}

/****************************************************************************
**
**  EntMakeDbox::make3dSolid
**
**  **jma
**
*************************************/

void
EntMakeDbox::make3dSolid()
{
    acutPrintf(_T("\nTesting make of AcDb3dSolid (BOX) ..."));

    ArxRleUiPrPoint prCentroid(_T("Centroid"), NULL);
    ArxRleUiPrDist prXLen(_T("X-length"), NULL, ArxRleUiPrDist::kNoNegNoZero);
    ArxRleUiPrDist prYLen(_T("Y-length"), NULL, ArxRleUiPrDist::kNoNegNoZero);
    ArxRleUiPrDist prZLen(_T("Z-length"), NULL, ArxRleUiPrDist::kNoNegNoZero);

    if ((prCentroid.go() != ArxRleUiPrBase::kOk) ||
        (prXLen.go() != ArxRleUiPrBase::kOk) ||
        (prYLen.go() != ArxRleUiPrBase::kOk) ||
        (prZLen.go() != ArxRleUiPrBase::kOk))
        return;

    AcDb3dSolid* solid = new AcDb3dSolid;
    Acad::ErrorStatus es = solid->createBox(prXLen.value(), prYLen.value(), prZLen.value());
    if (es == Acad::eOk) {
            // solids are always created with centroid (0,0,0)
            // so you must translate it to the place you want it
            // to be.
        AcGeMatrix3d mat;
        mat.setTranslation(prCentroid.value().asVector());
        solid->transformBy(mat);

        solid->setDatabaseDefaults();
        ArxRleUtils::transformToWcs(solid, acdbHostApplicationServices()->workingDatabase());        // could combine with above xform to be optimal
        ArxRleUtils::addToCurrentSpaceAndClose(solid);
    }
}

/****************************************************************************
**
**  EntMakeDbox::makeRegion
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeRegion()
{
    acutPrintf(_T("\nTesting make of AcDbRegion ..."));

        // select curves
    acutPrintf(_T("\nSelect AcDbCurves: "));
    ArxRleSelSet ss;
    if (ss.userSelect() != ArxRleSelSet::kSelected)
        return;

    int rejectCount = 0;
    AcDbVoidPtrArray curveSegs;
    AcDbEntity* ent;
    Acad::ErrorStatus es;

    AcDbObjectIdArray ssEnts;
    ss.asArray(ssEnts);

    int len = ssEnts.length();
    int i;
    for (i=0; i<len; i++) {
        es = acdbOpenAcDbEntity(ent, ssEnts[i], AcDb::kForRead);
        if (es == Acad::eOk) {
            if (ent->isKindOf(AcDbCurve::desc()))
                curveSegs.append(static_cast<void*>(ent));
            else {
                rejectCount++;
                ent->close();    // only close those that we are rejecting
            }
        }
    }
        // print appropriate feedback about what was selected
    if (curveSegs.isEmpty()) {
        ArxRleUtils::alertBox(_T("No curves were selected!"));
        return;
    }
    if (rejectCount > 0)
        acutPrintf(_T("\n%d object(s) were not curves..."), rejectCount);

    AcDbVoidPtrArray regions;
    es = AcDbRegion::createFromCurves(curveSegs, regions);

        // close all open entities used to create the region
    int lenCurves = curveSegs.length();
    for (i=0; i<lenCurves; i++) {
        ent = static_cast<AcDbEntity*>(curveSegs[i]);
        ent->close();
    }

    if (es != Acad::eOk) {
        ArxRleUtils::rxErrorAlert(es);
        return;
    }
        // add all created regions to the database
    AcDbRegion* regionObj;
    int lenRegions = regions.length();
    for (i=0; i<lenRegions; i++) {
        regionObj = static_cast<AcDbRegion*>(regions[i]);
        regionObj->setDatabaseDefaults();
        ArxRleUtils::addToCurrentSpaceAndClose(regionObj);
    }
    acutPrintf(_T("\n%d Region(s) created from %d curve(s)."), lenRegions, lenCurves);
}

/****************************************************************************
**
**  EntMakeDbox::makeText
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeText()
{
    acutPrintf(_T("\nTesting make of AcDbText..."));

    ArxRleUiPrPoint prPos(_T("Position"), NULL);
    if (prPos.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrDist prHeight(_T("Height"), NULL, ArxRleUiPrDist::kNoNegNoZero, prPos.value());
    ArxRleUiPrAngle prRot(_T("Rotation"), NULL, ArxRleUiPrAngle::kAny, prPos.value());
    ArxRleUiPrString prText(_T("Text"), TRUE);

    if ((prHeight.go() != ArxRleUiPrBase::kOk) ||
        (prRot.go() != ArxRleUiPrBase::kOk) ||
        (prText.go() != ArxRleUiPrBase::kOk))
        return;

    AcDbText* text = new AcDbText;
    text->setDatabaseDefaults();
    text->setPosition(prPos.value());
    text->setHeight(prHeight.value());
    text->setRotation(prRot.value());
    text->setTextString(prText.value());
    ArxRleUtils::transformToWcs(text, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(text);
}

/****************************************************************************
**
**  EntMakeDbox::makeMText
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeMText()
{
    acutPrintf(_T("\nTesting make of AcDbMText..."));

    ArxRleUiPrPoint prInsertPt(_T("Insertion point"), NULL);
    if (prInsertPt.go() != ArxRleUiPrBase::kOk)
        return;

    ArxRleUiPrCorner prCorner(_T("Other corner"), NULL, prInsertPt.value());
    ArxRleUiPrString prText(_T("Text"), TRUE);

    if ((prCorner.go() != ArxRleUiPrBase::kOk) ||
        (prText.go() != ArxRleUiPrBase::kOk))
        return;

    AcDbMText* mtext = new AcDbMText;
    mtext->setLocation(prInsertPt.value());
    mtext->setWidth(fabs(prInsertPt.value().x - prCorner.value().x));
    mtext->setContents(prText.value());
    ArxRleUtils::transformToWcs(mtext, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(mtext);
}

/****************************************************************************
**
**  EntMakeDbox::makeAttributeDefinition
**
**  **jma
**
*************************************/

void
EntMakeDbox::makeAttributeDefinition()
{
    acutPrintf(_T("\nTesting make of AcDbAttributeDefinition..."));

    ArxRleUiPrString prTag(_T("Tag"), FALSE);
    ArxRleUiPrString prPrompt(_T("Prompt"), TRUE);
    ArxRleUiPrString prDefault(_T("Default value"), TRUE);
    ArxRleUiPrPoint prPos(_T("Position"), NULL);

    if ((prTag.go() != ArxRleUiPrBase::kOk) ||
        (prPrompt.go() != ArxRleUiPrBase::kOk) ||
        (prDefault.go() != ArxRleUiPrBase::kOk) ||
        (prPos.go() != ArxRleUiPrBase::kOk))
        return;

    ArxRleUiPrDist prHeight(_T("Height"), NULL, ArxRleUiPrDist::kNoNegNoZero, prPos.value());
    ArxRleUiPrAngle prRot(_T("Rotation"), NULL, ArxRleUiPrAngle::kAny, prPos.value());

    if ((prHeight.go() != ArxRleUiPrBase::kOk) ||
        (prRot.go() != ArxRleUiPrBase::kOk))
        return;

    AcDbAttributeDefinition* attdef = new AcDbAttributeDefinition;
    attdef->setDatabaseDefaults();
    attdef->setPosition(prPos.value());
    attdef->setHeight(prHeight.value());
    attdef->setRotation(prRot.value());
    attdef->setTextString(prDefault.value());
    attdef->setPrompt(prPrompt.value());
    attdef->setTag(prTag.value());
    ArxRleUtils::transformToWcs(attdef, acdbHostApplicationServices()->workingDatabase());
    ArxRleUtils::addToCurrentSpaceAndClose(attdef);
}

/****************************************************************************
**
**  EntMakeDbox::getArcCircleCenterRadius
**
**  **jma
**
*************************************/

Acad::ErrorStatus
EntMakeDbox::getArcCircleCenterRadius(AcGePoint3d& centerPt, double& radius)
{
    AcDbCircle* circle;
    AcDbArc* arc;
    Acad::ErrorStatus ret = Acad::eInvalidInput;

    ArxRleUiPrEntity prEnt(_T("Select a CIRCLE or ARC"), NULL);
    prEnt.addAllowedClass(AcDbCircle::desc());
    prEnt.addAllowedClass(AcDbArc::desc());

    if (prEnt.go() == ArxRleUiPrBase::kOk) {
        AcDbEntity* obj;
        Acad::ErrorStatus es = acdbOpenObject(obj, prEnt.objectId(), AcDb::kForRead);
        if (es == Acad::eOk) {
            if ((circle = AcDbCircle::cast(obj)) != NULL) {
                centerPt = ArxRleUtils::wcsToUcs(circle->center());
                radius = circle->radius();
                ret = Acad::eOk;
            }
            else if ((arc = AcDbArc::cast(obj)) != NULL) {
                centerPt = ArxRleUtils::wcsToUcs(arc->center());
                radius = arc->radius();
                ret = Acad::eOk;
            }
            obj->close();
        }
    }
    return ret;
}

/****************************************************************************
**
**  EntMakeDbox::get3PointArc
**
**  **jma
**
*************************************/

Acad::ErrorStatus
EntMakeDbox::get3PointArc(AcGePoint3d& centerPt, AcGePoint3d& pt1, AcGePoint3d& pt2)
{
    AcDbArc* arc;
    Acad::ErrorStatus ret = Acad::eInvalidInput;

    ArxRleUiPrEntity prEnt(_T("Select an ARC"), NULL);
    prEnt.addAllowedClass(AcDbArc::desc());

    if (prEnt.go() == ArxRleUiPrBase::kOk) {
        AcDbEntity* obj;
        Acad::ErrorStatus es = acdbOpenObject(obj, prEnt.objectId(), AcDb::kForRead);
        if (es == Acad::eOk) {
            if ((arc = AcDbArc::cast(obj)) != NULL) {
                centerPt = arc->center();
                arc->getStartPoint(pt1);
                arc->getEndPoint(pt2);

                    // convert points back to current UCS
                ArxRleUtils::wcsToUcs(centerPt);
                ArxRleUtils::wcsToUcs(pt1);
                ArxRleUtils::wcsToUcs(pt2);

                ret = Acad::eOk;
            }
            obj->close();
        }
    }
    return ret;
}

/****************************************************************************
**
**  EntMakeDbox::getLineOrTwoPoints
**
**  **jma
**
*************************************/

Acad::ErrorStatus
EntMakeDbox::getLineOrTwoPoints(AcGePoint3d& pt1, AcGePoint3d& pt2)
{
    ArxRleUiPrPoint prPoint1(_T("First extension line origin or RETURN to select"), NULL);
    prPoint1.setAllowNone(TRUE);

    ArxRleUiPrBase::Status ps = prPoint1.go();

        // user wants to select a line to specify both points
    if (ps == ArxRleUiPrBase::kNone) {
        ArxRleUiPrEntity prEnt(_T("Select a LINE"), NULL);
        prEnt.addAllowedClass(AcDbLine::desc());

        if (prEnt.go() != ArxRleUiPrBase::kOk)
            return Acad::eInvalidInput;

        AcDbEntity* obj;
        Acad::ErrorStatus es = acdbOpenObject(obj, prEnt.objectId(), AcDb::kForRead);
        if (es == Acad::eOk) {
            AcDbLine* line;
            if ((line = AcDbLine::cast(obj)) == NULL) {
                obj->close();
                return Acad::eInvalidInput;
            }
            pt1 = ArxRleUtils::wcsToUcs(line->startPoint());
            pt2 = ArxRleUtils::wcsToUcs(line->endPoint());
            line->close();
            return Acad::eOk;
        }
    }
    else if (ps == ArxRleUiPrBase::kOk) {
        ArxRleUiPrPoint prPoint2(_T("Second extension line origin"), NULL, prPoint1.value());
        if (prPoint2.go() != ArxRleUiPrBase::kOk)
            return Acad::eInvalidInput;

        pt1 = prPoint1.value();
        pt2 = prPoint2.value();
        return Acad::eOk;
    }
    
    return Acad::eInvalidInput;
}

/****************************************************************************
**
**  EntMakeDbox::getAngularDimLines
**
**  **jma
**
*************************************/

Acad::ErrorStatus
EntMakeDbox::getAngularDimLines(AcGePoint3d& pt1, AcGePoint3d& pt2,
                        AcGePoint3d& pt3, AcGePoint3d& pt4)
{
    Acad::ErrorStatus es;

        // get two lines
    ArxRleUiPrEntity prEnt1(_T("Select first LINE"), NULL);
    prEnt1.addAllowedClass(AcDbLine::desc());

    ArxRleUiPrEntity prEnt2(_T("Select second LINE"), NULL);
    prEnt2.addAllowedClass(AcDbLine::desc());

    if ((prEnt1.go() != ArxRleUiPrBase::kOk) ||
        (prEnt2.go() != ArxRleUiPrBase::kOk))
        return Acad::eInvalidInput;

    if (prEnt1.objectId() == prEnt2.objectId()) {
        ArxRleUtils::alertBox(_T("The same line cannot be picked twice."));
        return Acad::eInvalidInput;
    }

    AcDbLine* line;
    es = acdbOpenObject(line, prEnt1.objectId(), AcDb::kForRead);
    if (es != Acad::eOk) {
        ArxRleUtils::rxErrorAlert(es);
        return Acad::eInvalidInput;
    }
    pt1 = ArxRleUtils::wcsToUcs(line->startPoint());
    pt2 = ArxRleUtils::wcsToUcs(line->endPoint());
    line->close();

    es = acdbOpenObject(line, prEnt2.objectId(), AcDb::kForRead);
    if (es != Acad::eOk) {
        ArxRleUtils::rxErrorAlert(es);
        return Acad::eInvalidInput;
    }
    pt3 = ArxRleUtils::wcsToUcs(line->startPoint());
    pt4 = ArxRleUtils::wcsToUcs(line->endPoint());
    line->close();

    return Acad::eOk;
}

/****************************************************************************
**
**  EntMakeDbox::getDimRotationAngle
**
**  **jma
**
*************************************/

Acad::ErrorStatus
EntMakeDbox::getDimRotationAngle(double& ang)
{
    ArxRleUiPrKeyWordDef prRotType(_T("Type [Rotated/Vertical]"),
                    _T("Horizontal Vertical Rotated"), _T("Horizontal"));
    if (prRotType.go() != ArxRleUiPrBase::kOk)
        return Acad::eInvalidInput;

    if (prRotType.isKeyWordPicked(_T("Horizontal")))
        ang = ArxRleUtilsGe::kRad0;
    else if (prRotType.isKeyWordPicked(_T("Vertical")))
        ang = ArxRleUtilsGe::kRad90;
    else if (prRotType.isKeyWordPicked(_T("Rotated"))) {
        ArxRleUiPrAngle prAng(_T("Rotation angle"), NULL, ArxRleUiPrAngle::kAny);
        if (prAng.go() != ArxRleUiPrBase::kOk)
            return Acad::eInvalidInput;

        ang = prAng.value();
    }
    else {
        ASSERT(0);
        return(Acad::eInvalidInput);
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  EntMakeDbox::getDimHorizRotation
**      find out the rotational difference between the current UCS XAxis
**  and the ECS XAxis.  Dimensions need to know this to know which way
**  was horizontal when the dimension text was created.
**
**  **jma
**
*************************************/

double
EntMakeDbox::getDimHorizRotation()
{
    AcGeVector3d ucsZAxis = ArxRleUtils::getUcsZAxis(acdbHostApplicationServices()->workingDatabase());
    AcGeVector3d ucsXAxis = ArxRleUtils::getUcsXAxis(acdbHostApplicationServices()->workingDatabase());
    AcGeVector3d entXAxis;
    ArxRleUtils::getEcsXAxis(ucsZAxis, entXAxis);   // get AutoCAD's arbitrary X-Axis

    return ucsXAxis.angleTo(entXAxis, ucsZAxis);    // get rotation from one to the other
}


