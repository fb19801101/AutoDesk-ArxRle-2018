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
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include "ArxRleViewportDraw.h"
#include "AcadUtils/ArxRleUtils.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleGiViewportDraw,AcGiViewportDraw)
ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleGiViewportGeometry,AcGiViewportGeometry)

/****************************************************************************
**
**    ArxRleGiViewportDraw::ArxRleGiViewportDraw
**
**    **jma
**
*************************************/

ArxRleGiViewportDraw::ArxRleGiViewportDraw()
:    m_regenType(kAcGiStandardDisplay),
    m_isDragging(Adesk::kFalse),
    m_deviation(0.5),
    m_isolines(16),
    m_seqNum(0)
{
    m_geom = new ArxRleGiViewportGeometry;
    m_traits = new ArxRleGiSubEntityTraits;
    //m_viewport = new AcGiViewport;
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::~ArxRleGiViewportDraw
**
**    **jma
**
*************************************/

ArxRleGiViewportDraw::~ArxRleGiViewportDraw()
{
    delete m_geom;
    delete m_traits;
//    delete m_viewport;
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::geometry
**
**    **jma
**
*************************************/

AcGiViewportGeometry&
ArxRleGiViewportDraw::geometry() const
{
    printViewportDrawMsg(_T("--> geometry()"));
    return *m_geom;
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::regenType
**
**    **jma
**
*************************************/

AcGiRegenType
ArxRleGiViewportDraw::regenType() const
{
    printViewportDrawMsg(_T("--> regenType()"));
    return(m_regenType);
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::regenAbort
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportDraw::regenAbort() const
{
    printViewportDrawMsg(_T("--> regenAbort()"));
    return(Adesk::kFalse);
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::subEntityTraits
**
**    **jma
**
*************************************/

AcGiSubEntityTraits&
ArxRleGiViewportDraw::subEntityTraits() const
{
    printViewportDrawMsg(_T("--> subEntityTraits()"));
    return *m_traits;
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::isDragging
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportDraw::isDragging() const
{
    printViewportDrawMsg(_T("--> isDragging()"));
    return(m_isDragging);
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::deviation
**
**    **jma
**
*************************************/

double
ArxRleGiViewportDraw::deviation(const AcGiDeviationType devType, const AcGePoint3d& samplePt) const
{
    printViewportDrawMsg(_T("--> deviation(devType, samplePt)"));
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("DEV TYPE"), deviationTypeToStr(devType, str));
        printParamMsg(_T("SAMPLE PT"), ArxRleUtils::ptToStr(samplePt, str));
    }
    return(m_deviation);
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::numberOfIsolines
**
**    **jma
**
*************************************/

Adesk::UInt32
ArxRleGiViewportDraw::numberOfIsolines() const
{
    printViewportDrawMsg(_T("--> numberOfIsolines()"));
    return(m_isolines);
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::viewport
**
**    **jma
**
*************************************/

AcGiViewport&
ArxRleGiViewportDraw::viewport() const
{
    printViewportDrawMsg(_T("--> viewport()"));
    return(*m_viewport);
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::sequenceNumber
**
**    **jma
**
*************************************/

Adesk::UInt32
ArxRleGiViewportDraw::sequenceNumber() const
{
    printViewportDrawMsg(_T("--> sequenceNumber()"));
    return(m_seqNum);
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::isValidId
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportDraw::isValidId(const Adesk::ULongPtr acgiId) const
{
    printViewportDrawMsg(_T("--> isValidId()"));
    return(Adesk::kTrue);    // what else to do??
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::viewportObjectId
**
**    **jma
**
*************************************/

AcDbObjectId
ArxRleGiViewportDraw::viewportObjectId() const
{
    printViewportDrawMsg(_T("--> viewportObjectId()"));
    return(AcDbObjectId::kNull);
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::printViewportDrawMsg
**
**    **jma
**
*************************************/

void
ArxRleGiViewportDraw::printViewportDrawMsg(LPCTSTR event) const
{
    if (ArxRleGiWorldDraw::m_showWorldDrawMsg)
        acutPrintf(_T("\n%-15s : %s "), _T("ViewportDraw"), event);
}

/****************************************************************************
**
**    ArxRleGiViewportDraw::setInitialProps
**
**    **jma
**
*************************************/

void
ArxRleGiViewportDraw::setInitialProps(AcDbEntity* ent)
{
        // temporarily disable messaging
    BOOL tmpFlag = ArxRleGiWorldDraw::m_showSubentsMsg;
    ArxRleGiWorldDraw::m_showSubentsMsg = FALSE;

    m_traits->setLayer(ent->layerId());
    m_traits->setColor(ent->colorIndex());
    m_traits->setLineType(ent->linetypeId());

    ArxRleGiWorldDraw::m_showSubentsMsg = tmpFlag;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////



/****************************************************************************
**
**    ArxRleGiViewportGeometry::getModelToWorldTransform
**
**    **jma
**
*************************************/

void
ArxRleGiViewportGeometry::getModelToWorldTransform(AcGeMatrix3d&) const
{
    printGeomMsg(_T("--> getModelToWorldTransform()"));
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::getWorldToModelTransform
**
**    **jma
**
*************************************/

void
ArxRleGiViewportGeometry::getWorldToModelTransform(AcGeMatrix3d&) const
{
    printGeomMsg(_T("--> getWorldToModelTransform()"));
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::circle
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::circle(const AcGePoint3d& center, const double radius,
                            const AcGeVector3d& normal) const
{
    printGeomMsg(_T("--> circle(center, radius, normal)"));
    ArxRleGiWorldGeometry::printCircle(center, radius, normal);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::circle
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::circle(const AcGePoint3d& p1, const AcGePoint3d& p2,
                        const AcGePoint3d& p3) const
{
    printGeomMsg(_T("--> circle(pt1, pt2, pt3)"));
    ArxRleGiWorldGeometry::printCircle(p1, p2, p3);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::circularArc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::circularArc(const AcGePoint3d& center, const double radius,
                        const AcGeVector3d& normal, const AcGeVector3d& startVector,
                        const double sweepAngle, const AcGiArcType arcType) const
{
    printGeomMsg(_T("--> circularArc(center, radius, normal, startVec, sweepAngle, arcType)"));
    ArxRleGiWorldGeometry::printArc(center, radius, normal, startVector,
                                sweepAngle, arcType);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::circularArc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::circularArc(const AcGePoint3d& pt1, const AcGePoint3d& pt2,
                        const AcGePoint3d& pt3, const AcGiArcType arcType) const
{
    printGeomMsg(_T("--> circularArc(pt1, pt2, pt3, arcType)"));
    ArxRleGiWorldGeometry::printArc(pt1, pt2, pt3, arcType);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::polyline
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::polyline(const Adesk::UInt32 nbPoints,
                        const AcGePoint3d* pVertexList,
                        const AcGeVector3d* pNormal) const
{
    printGeomMsg(_T("--> polyline(numPoints, ptArray, normal)"));
    ArxRleGiWorldGeometry::printPolyline(nbPoints, pVertexList, pNormal);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::polygon
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::polygon(const Adesk::UInt32 nbPoints,
                    const AcGePoint3d* pVertexList) const
{
    printGeomMsg(_T("--> polygon(numPoints, ptArray)"));
    ArxRleGiWorldGeometry::printPolygon(nbPoints, pVertexList);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::mesh
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::mesh(const Adesk::UInt32 rows,
                    const Adesk::UInt32 columns,
                    const AcGePoint3d* pVertexList,
                    const AcGiEdgeData* pEdgeData,
                    const AcGiFaceData* pFaceData,
                    const AcGiVertexData* pVertexData,
                    const bool bAutoGenerateNormals) const
{
    printGeomMsg(_T("--> mesh(rows, cols, pts, edges, faces, vertexData)"));
    ArxRleGiWorldGeometry::printMesh(rows, columns, pVertexList,
                            pEdgeData, pFaceData, pVertexData);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiWorldGeometry::shell
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::shell(const Adesk::UInt32 nbVertex,
                        const AcGePoint3d* pVertexList,
                        const Adesk::UInt32 faceListSize,
                        const Adesk::Int32* pFaceList,
                        const AcGiEdgeData* pEdgeData,
                        const AcGiFaceData* pFaceData,
                        const AcGiVertexData* pVertexData,
                        const struct resbuf* pResBuf,
                        const bool bAutoGenerateNormals) const
{
    printGeomMsg(_T("--> shell(nbVertex, pts, faceListSize, faceList, edges, faces, vertexData, resbuf)"));
    ArxRleGiWorldGeometry::printShell(nbVertex, pVertexList, faceListSize, pFaceList,
                            pEdgeData, pFaceData, pVertexData, pResBuf);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::text
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::text(const AcGePoint3d& position,
                        const AcGeVector3d& normal,
                        const AcGeVector3d& direction,
                        const double height,
                        const double width,
                        const double oblique,
                        const TCHAR* pMsg) const
{
    printGeomMsg(_T("--> text(position, normal, dir, ht, wd, obliq, msg)"));
    ArxRleGiWorldGeometry::printText(position, normal, direction, height, width,
                            oblique, pMsg);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::text
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::text(const AcGePoint3d& position,
                        const AcGeVector3d& normal,
                        const AcGeVector3d& direction,
                        const TCHAR* pMsg,
                        const Adesk::Int32 length,
                        const Adesk::Boolean raw,
                        const AcGiTextStyle& pTextStyle) const
{
    printGeomMsg(_T("--> text(position, normal, msg, len, raw, textStyle)"));
    ArxRleGiWorldGeometry::printText(position, normal, direction, pMsg, length,
                            raw, pTextStyle);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::xline
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::xline(const AcGePoint3d& a, const AcGePoint3d& b) const
{
    printGeomMsg(_T("--> xline(pt1, pt2)"));
    ArxRleGiWorldGeometry::printXline(a, b);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::ray
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::ray(const AcGePoint3d& start, const AcGePoint3d& other) const
{
    printGeomMsg(_T("--> ray(start, otherPt)"));
    ArxRleGiWorldGeometry::printRay(start, other);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::pline
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::pline(const AcDbPolyline& lwBuf,
                        Adesk::UInt32 fromIndex, Adesk::UInt32 numSegs) const
{
    printGeomMsg(_T("--> pline(AcDbPolyline&, fromIndex, numSegs)"));
    ArxRleGiWorldGeometry::printPline(lwBuf, fromIndex, numSegs);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::polylineEye
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::polylineEye(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const
{
    printGeomMsg(_T("--> polylineEye(numPoints, ptArray)"));
    if (ArxRleGiWorldDraw::m_showDetailsMsg) 
        ArxRleGiWorldGeometry::printPtArray(nbPoints, pPoints);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::polygonEye
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::polygonEye(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const
{
    printGeomMsg(_T("--> polygonEye(numPoints, ptArray)"));
    if (ArxRleGiWorldDraw::m_showDetailsMsg) 
        ArxRleGiWorldGeometry::printPtArray(nbPoints, pPoints);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::polylineDc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::polylineDc(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const
{
    printGeomMsg(_T("--> polylineDc(numPoints, ptArray)"));
    if (ArxRleGiWorldDraw::m_showDetailsMsg) 
        ArxRleGiWorldGeometry::printPtArray(nbPoints, pPoints);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::polygonDc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::polygonDc(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pPoints) const
{
    printGeomMsg(_T("--> polygonDc(numPoints, ptArray)"));
    if (ArxRleGiWorldDraw::m_showDetailsMsg) 
        ArxRleGiWorldGeometry::printPtArray(nbPoints, pPoints);
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::rasterImageDc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::rasterImageDc(
                                    const AcGePoint3d& origin,
                                    const AcGeVector3d& u,
                                    const AcGeVector3d& v,
                                    const AcGeMatrix2d& pixelToDc,
                                    AcDbObjectId entityId,
                                    AcGiImageOrg imageOrg,
                                    Adesk::UInt32 imageWidth,
                                    Adesk::UInt32 imageHeight,
                                    Adesk::Int16 imageColorDepth,
                                    Adesk::Boolean transparency) const
{
    printGeomMsg(_T("--> rasterImageDc()"));

    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("ORIGIN"), ArxRleUtils::ptToStr(origin, str));
        printParamMsg(_T("U"), ArxRleUtils::vectorToStr(u, str));
        printParamMsg(_T("V"), ArxRleUtils::vectorToStr(v, str));
        printParamMsg(_T("PIXEL2DC MAT"), _T("Not Yet..."));
        printParamMsg(_T("ENTITY ID"), _T("Not Yet..."));
        printParamMsg(_T("IMAGE ORG"), _T("Not Yet..."));
        printParamMsg(_T("IMAGE WDITH"), ArxRleUtils::intToStr(imageWidth, str));
        printParamMsg(_T("IMAGE HEIGHT"), ArxRleUtils::intToStr(imageHeight, str));
        printParamMsg(_T("COLOR DEPTH"), ArxRleUtils::intToStr(imageColorDepth, str));
        printParamMsg(_T("TRANSPARENCY"), ArxRleUtils::booleanToStr(transparency, str));
    }
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::ownerDrawDc
**
**    **jma
**
*************************************/

Adesk::Boolean
ArxRleGiViewportGeometry::ownerDrawDc(long vpnumber, 
                                    long left, long top, 
                                    long right, long bottom, 
                                    const OwnerDraw* pOwnerDraw) const
{
    printGeomMsg(_T("--> ownerDrawDc()"));

    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("VPNUMBER"), ArxRleUtils::intToStr(vpnumber, str));
        printParamMsg(_T("LEFT"), ArxRleUtils::intToStr(left, str));
        printParamMsg(_T("TOP"), ArxRleUtils::intToStr(top, str));
        printParamMsg(_T("RIGHT"), ArxRleUtils::intToStr(right, str));
        printParamMsg(_T("BOTTOM"), ArxRleUtils::intToStr(bottom, str));
    }
    return Adesk::kFalse;
}

/****************************************************************************
**
**    ArxRleGiViewportGeometry::printGeomMsg
**
**    **jma
**
*************************************/

void
ArxRleGiViewportGeometry::printGeomMsg(LPCTSTR event) const
{
    if (ArxRleGiWorldDraw::m_showGeomMsg)
        acutPrintf(_T("\n%-15s : %s "), _T("VportGeometry"), event);
}

Adesk::Boolean ArxRleGiViewportGeometry::edge (const AcArray<AcGeCurve2d*>& edge) const
{
    printGeomMsg(_T("--> edge(edge)"));
    return Adesk::kFalse;
}
