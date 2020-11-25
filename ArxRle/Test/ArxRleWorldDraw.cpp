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


#include "ArxRleWorldDraw.h"
#include "AcadUtils/ArxRleUtils.h"



BOOL    ArxRleGiWorldDraw::m_showWorldDrawMsg = FALSE;
BOOL    ArxRleGiWorldDraw::m_showGeomMsg = TRUE;
BOOL    ArxRleGiWorldDraw::m_showSubentsMsg = TRUE;
BOOL    ArxRleGiWorldDraw::m_showDetailsMsg = FALSE;


ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleGiContext, AcGiContext)
ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleGiWorldDraw, AcGiWorldDraw)
ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleGiWorldGeometry, AcGiWorldGeometry)
ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleGiSubEntityTraits, AcGiSubEntityTraits)

/****************************************************************************
**
**  ArxRleGiContext::isPsOut
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiContext::isPsOut() const
{
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxRleGiContext::isPlotGeneration
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiContext::isPlotGeneration() const
{
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxRleGiContext::database
**
**  **jma
**
*************************************/

AcDbDatabase*
ArxRleGiContext::database() const
{
    return acdbHostApplicationServices()->workingDatabase();    // TBD: ??
}

/****************************************************************************
**
**  ArxRleGiContext::isBoundaryClipping
**
**  **jma
**
*************************************/

bool
ArxRleGiContext::isBoundaryClipping() const
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/****************************************************************************
**
**  ArxRleGiWorldDraw::ArxRleGiWorldDraw
**
**  **jma
**
*************************************/

ArxRleGiWorldDraw::ArxRleGiWorldDraw()
:   m_regenType(kAcGiStandardDisplay),
    m_isDragging(Adesk::kFalse),
    m_deviation(0.5),
    m_isolines(16)
{
    m_geom = new ArxRleGiWorldGeometry;
    m_traits = new ArxRleGiSubEntityTraits;
    m_context = new ArxRleGiContext;
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::~ArxRleGiWorldDraw
**
**  **jma
**
*************************************/

ArxRleGiWorldDraw::~ArxRleGiWorldDraw()
{
    delete m_geom;
    delete m_traits;
    delete m_context;
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::rawGeometry
**
**  **jma
**
*************************************/

AcGiGeometry*
ArxRleGiWorldDraw::rawGeometry() const
{
    printWorldDrawMsg(_T("--> rawGeometry()"));
    return m_geom;
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::geometry
**
**  **jma
**
*************************************/

AcGiWorldGeometry&
ArxRleGiWorldDraw::geometry() const
{
    printWorldDrawMsg(_T("--> geometry()"));
    return *m_geom;
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::context
**
**  **jma
**
*************************************/

AcGiContext*
ArxRleGiWorldDraw::context()
{
    printWorldDrawMsg(_T("--> context()"));
    return m_context;
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::regenType
**
**  **jma
**
*************************************/

AcGiRegenType
ArxRleGiWorldDraw::regenType() const
{
    printWorldDrawMsg(_T("--> regenType()"));
    return(m_regenType);
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::regenAbort
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldDraw::regenAbort() const
{
    printWorldDrawMsg(_T("--> regenAbort()"));
    return(Adesk::kFalse);
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::subEntityTraits
**
**  **jma
**
*************************************/

AcGiSubEntityTraits&
ArxRleGiWorldDraw::subEntityTraits() const
{
    printWorldDrawMsg(_T("--> subEntityTraits()"));
    return *m_traits;
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::isDragging
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldDraw::isDragging() const
{
    printWorldDrawMsg(_T("--> isDragging()"));
    return(m_isDragging);
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::deviation
**
**  **jma
**
*************************************/

double
ArxRleGiWorldDraw::deviation(const AcGiDeviationType devType, const AcGePoint3d& samplePt) const
{
    printWorldDrawMsg(_T("--> deviation(devType, samplePt)"));
    if (m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("DEV TYPE"), deviationTypeToStr(devType, str));
        printParamMsg(_T("SAMPLE PT"), ArxRleUtils::ptToStr(samplePt, str));
    }
    return(m_deviation);
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::numberOfIsolines
**
**  **jma
**
*************************************/

Adesk::UInt32
ArxRleGiWorldDraw::numberOfIsolines() const
{
    printWorldDrawMsg(_T("--> numberOfIsolines()"));
    return(m_isolines);
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::printWorldDrawMsg
**
**  **jma
**
*************************************/

void
ArxRleGiWorldDraw::printWorldDrawMsg(LPCTSTR event) const
{
    if (m_showWorldDrawMsg)
        acutPrintf(_T("\n%-15s : %s "), _T("WorldDraw"), event);
}

/****************************************************************************
**
**  ArxRleGiWorldDraw::setInitialProps
**
**  **jma
**
*************************************/

void
ArxRleGiWorldDraw::setInitialProps(AcDbEntity* ent)
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
**  ArxRleGiSubEntityTraits::setColor
**
**  **jma
**
*************************************/

void
ArxRleGiSubEntityTraits::setColor(const Adesk::UInt16 color)
{
    m_color = color;

    CString str;
    str.Format(_T("--> setColor() = %d"), static_cast<int>(color));
    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxRleGiSubEntityTraits::setTrueColor
**
**  **jma
**
*************************************/

void
ArxRleGiSubEntityTraits::setTrueColor(const AcCmEntityColor& color)
{
    m_trueColor = color;

    printSubentMsg(_T("--> setTrueColor"));
}

/****************************************************************************
**
**  ArxRleGiSubEntityTraits::setLayer
**
**  **jma
**
*************************************/

void
ArxRleGiSubEntityTraits::setLayer(const AcDbObjectId layerId)
{
    m_layerId = layerId;

    CString layerName;
    ArxRleUtils::symbolIdToName(layerId, layerName);

    CString str;
    str.Format(_T("--> setLayer() = %s"),
                            static_cast<const TCHAR*>(layerName));
    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxRleGiSubEntityTraits::setLineType
**
**  **jma
**
*************************************/

void
ArxRleGiSubEntityTraits::setLineType(const AcDbObjectId linetypeId)
{
    m_ltypeId = linetypeId;

    CString ltypeName;
    ArxRleUtils::symbolIdToName(linetypeId, ltypeName);

    CString str;
    str.Format(_T("--> setLineType() = %s"),
                            static_cast<const TCHAR*>(ltypeName));
    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxRleGiSubEntityTraits::setLineWeight
**
**  **jma
**
*************************************/

void
ArxRleGiSubEntityTraits::setLineWeight(const AcDb::LineWeight lw)
{
    m_lineWt = lw;

    CString str, str2;
    str.Format(_T("--> setLineWeight() = %s"), ArxRleUtils::lineWeightTypeToStr(lw, str2));

    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxRleGiSubEntityTraits::setLineTypeScale
**
**  **jma
**
*************************************/

void
ArxRleGiSubEntityTraits::setLineTypeScale(double ltScale)
{
    m_ltypeScale = ltScale;

    CString str, str2;
    str.Format(_T("--> setLineTypeScale() = %s"), ArxRleUtils::doubleToStr(ltScale, str2));

    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxRleGiSubEntityTraits::setThickness
**
**  **jma
**
*************************************/

void
ArxRleGiSubEntityTraits::setThickness(double thick)
{
    m_thickness = thick;

    CString str, str2;
    str.Format(_T("--> setThickness() = %s"), ArxRleUtils::doubleToStr(thick, str2));

    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxRleGiSubEntityTraits::setSelectionMarker
**
**  **jma
**
*************************************/

void
ArxRleGiSubEntityTraits::setSelectionMarker(const Adesk::LongPtr markerId)
{
    CString str;
    str.Format(_T("--> setSelectionMarker() = %Id"), markerId);
    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxRleGiSubEntityTraits::setFillType
**
**  **jma
**
*************************************/

void
ArxRleGiSubEntityTraits::setFillType(const AcGiFillType fillType)
{
    CString str, str2;
    str.Format(_T("--> setFillType() = %s"),
                            fillTypeToStr(fillType, str2));
    printSubentMsg(str);
}

/****************************************************************************
**
**  ArxRleGiSubEntityTraits::printSubentMsg
**
**  **jma
**
*************************************/

void
ArxRleGiSubEntityTraits::printSubentMsg(LPCTSTR event) const
{
    if (ArxRleGiWorldDraw::m_showSubentsMsg)
        acutPrintf(_T("\n%-15s : %s "), _T("SubEntTraits"), event);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


/****************************************************************************
**
**  ArxRleGiWorldGeometry::getModelToWorldTransform
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::getModelToWorldTransform(AcGeMatrix3d&) const
{
    printGeomMsg(_T("--> getModelToWorldTransform()"));
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::getWorldToModelTransform
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::getWorldToModelTransform(AcGeMatrix3d&) const
{
    printGeomMsg(_T("--> getWorldToModelTransform()"));
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::setModelToWorldTransform
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::setModelToWorldTransform(const AcGeMatrix3d&)
{
    printGeomMsg(_T("--> setModelToWorldTransform()"));
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::pushModelTransform
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::pushModelTransform(const AcGeVector3d & vNormal)
{
    printGeomMsg(_T("--> pushModelTransform(const AcGeVector3d)"));

    return Adesk::kTrue;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::pushModelTransform
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::pushModelTransform(const AcGeMatrix3d & xMat)
{
    printGeomMsg(_T("--> pushModelTransform(const AcGeMatrix3d)"));

    return Adesk::kTrue;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::popModelTransform
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::popModelTransform()
{
    printGeomMsg(_T("--> popModelTransform()"));

    return Adesk::kTrue;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::draw
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::draw(AcGiDrawable*) const
{
    printGeomMsg(_T("--> draw()"));

    return Adesk::kTrue;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::pushClipBoundary
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::pushClipBoundary(AcGiClipBoundary* pBoundary)
{
    printGeomMsg(_T("--> pushClipBoundary()"));

    return Adesk::kTrue;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::popClipBoundary
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::popClipBoundary()
{
    printGeomMsg(_T("--> popClipBoundary()"));
}

Adesk::Boolean
ArxRleGiWorldGeometry::image   (
                const AcGiImageBGRA32& imageSource,
                const AcGePoint3d& position,
                const AcGeVector3d& u,
                const AcGeVector3d& v,
                AcGiGeometry::TransparencyMode transparencyMode
                ) const
{
    printGeomMsg(_T("--> image(imageSource,position,width,height,transparencyMode"));
    return Adesk::kFalse;
}

Adesk::Boolean 
ArxRleGiWorldGeometry::rowOfDots   (
                int count,
                const AcGePoint3d&     start,
                const AcGeVector3d&     step
                ) const
{
    printGeomMsg(_T("--> rowOfDots(count,start,step)"));
    return Adesk::kFalse;
}


Adesk::Boolean 
ArxRleGiWorldGeometry::ellipticalArc   (
                 const AcGePoint3d&         center,
                 const AcGeVector3d&        normal,
                 double                     majorAxisLength,
                 double                     minorAxisLength,
                 double                     startDegreeInRads,
                 double                     endDegreeInRads,
                 double                     tiltDegreeInRads,
                 AcGiArcType                arcType) const
{
    printGeomMsg(_T("--> ellipticalArc(center,normal,majorAxisLength,")
        _T("minorAxisLength,startDegreeInRads,endDegreeInRads,tiltDegreeInRads,arcType)"));
    return Adesk::kFalse;
}

AcGeMatrix3d 
ArxRleGiWorldGeometry::pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint3d& offset)
{
    printGeomMsg(_T("--> pushPositionTransform(behavior,offset)"));
    return AcGeMatrix3d::kIdentity;
}

AcGeMatrix3d 
ArxRleGiWorldGeometry::pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset)
{
    printGeomMsg(_T("--> pushPositionTransform(behavior,offset)"));
    return AcGeMatrix3d::kIdentity;
}

AcGeMatrix3d 
ArxRleGiWorldGeometry::pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint3d& extents)
{
    printGeomMsg(_T("--> pushScaleTransform(behavior,extents)"));
    return AcGeMatrix3d::kIdentity;
}

AcGeMatrix3d 
ArxRleGiWorldGeometry::pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents)
{
    printGeomMsg(_T("--> pushScaleTransform(behavior,extents)"));
    return AcGeMatrix3d::kIdentity;
}

AcGeMatrix3d 
ArxRleGiWorldGeometry::pushOrientationTransform (AcGiOrientationTransformBehavior behavior)
{
    printGeomMsg(_T("--> pushOrientationTransform(behavior)"));
    return AcGeMatrix3d::kIdentity;
}
/****************************************************************************
**
**  ArxRleGiWorldGeometry::setExtents
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::setExtents(AcGePoint3d* pNewExtents) const
{
    printGeomMsg(_T("--> setExtents(pNewExtents)"));
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("EXTMIN"), ArxRleUtils::ptToStr(pNewExtents[0], str));
        printParamMsg(_T("EXTMAX"), ArxRleUtils::ptToStr(pNewExtents[1], str));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::circle
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::circle(const AcGePoint3d& center, const double radius,
                            const AcGeVector3d& normal) const
{
    printGeomMsg(_T("--> circle(center, radius, normal)"));
    ArxRleGiWorldGeometry::printCircle(center, radius, normal);
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::circle
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::circle(const AcGePoint3d& p1, const AcGePoint3d& p2,
                        const AcGePoint3d& p3) const
{
    printGeomMsg(_T("--> circle(pt1, pt2, pt3)"));
    ArxRleGiWorldGeometry::printCircle(p1, p2, p3);
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::circularArc
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::circularArc(const AcGePoint3d& center, const double radius,
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
**  ArxRleGiWorldGeometry::circularArc
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::circularArc(const AcGePoint3d& pt1, const AcGePoint3d& pt2,
                        const AcGePoint3d& pt3, const AcGiArcType arcType) const
{
    printGeomMsg(_T("--> circularArc(pt1, pt2, pt3, arcType)"));
    ArxRleGiWorldGeometry::printArc(pt1, pt2, pt3, arcType);
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::polyline
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::polyline(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList,
                                const AcGeVector3d* pNormal,
                                Adesk::LongPtr lBaseSubEntMarker) const
{
    printGeomMsg(_T("--> polyline(numPoints, ptArray, normal, baseSubEntMarker)"));
    ArxRleGiWorldGeometry::printPolyline(nbPoints, pVertexList, pNormal);
    return Adesk::kFalse;
}

Adesk::Boolean 
ArxRleGiWorldGeometry::polyline (const AcGiPolyline& polylineObj) const
{
    printGeomMsg(_T("--> polyline(polyline)"));

    return polyline(polylineObj.points(), polylineObj.vertexList(),
                    polylineObj.normal(), polylineObj.baseSubEntMarker());
}

Adesk::Boolean 
ArxRleGiWorldGeometry::polyPolyline (Adesk::UInt32 nbPolylines,
                                  const AcGiPolyline * pPolylines) const
{
    printGeomMsg(_T("--> polylines(nbPolylines, pPolylines)"));

    Adesk::Boolean bAborting = false;

    for (Adesk::UInt32 i = 0; i < nbPolylines && !bAborting; ++i) 
        bAborting = polyline(pPolylines[i]);

    return bAborting;
}


/****************************************************************************
**
**  ArxRleGiWorldGeometry::polygon
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::polygon(const Adesk::UInt32 nbPoints,
                    const AcGePoint3d* pVertexList) const
{
    printGeomMsg(_T("--> polygon(numPoints, ptArray)"));
    ArxRleGiWorldGeometry::printPolygon(nbPoints, pVertexList);
    return Adesk::kFalse;
}

Adesk::Boolean 
ArxRleGiWorldGeometry::polyPolygon   (
                                      const Adesk::UInt32 numPolygonIndices,
                                      const Adesk::UInt32* numPolygonPositions,
                                      const AcGePoint3d* polygonPositions,
                                      const Adesk::UInt32* numPolygonPoints,
                                      const AcGePoint3d* polygonPoints,
                                      const AcCmEntityColor* outlineColors,
                                      const AcGiLineType* outlineTypes,
                                      const AcCmEntityColor* fillColors,
                                      const AcCmTransparency* fillOpacities) const
{
    printGeomMsg(_T("--> polyPolygon (numPolygonIndices,numPolygonPositions,polygonPositions,numPolygonPoints,outlineColors,outlineTypes,fillColors,fillOpacities)"));
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::mesh
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::mesh(const Adesk::UInt32 rows,
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
**  ArxRleGiWorldGeometry::shell
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::shell(const Adesk::UInt32 nbVertex,
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
**  ArxRleGiWorldGeometry::text
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::text(const AcGePoint3d& position,
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
**  ArxRleGiWorldGeometry::text
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::text(const AcGePoint3d& position,
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
**  ArxRleGiWorldGeometry::xline
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::xline(const AcGePoint3d& a, const AcGePoint3d& b) const
{
    printGeomMsg(_T("--> xline(pt1, pt2)"));
    ArxRleGiWorldGeometry::printXline(a, b);
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::ray
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::ray(const AcGePoint3d& start, const AcGePoint3d& other) const
{
    printGeomMsg(_T("--> ray(start, otherPt)"));
    ArxRleGiWorldGeometry::printRay(start, other);
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::pline
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxRleGiWorldGeometry::pline(const AcDbPolyline& lwBuf,
                        Adesk::UInt32 fromIndex, Adesk::UInt32 numSegs) const
{
    printGeomMsg(_T("--> pline(AcDbPolyline&, fromIndex, numSegs)"));
    ArxRleGiWorldGeometry::printPline(lwBuf, fromIndex, numSegs);
    return Adesk::kFalse;
}

Adesk::Boolean ArxRleGiWorldGeometry::edge (const AcArray<AcGeCurve2d*>& edge) const
{
    printGeomMsg(_T("--> edge(edge)"));
    return Adesk::kFalse;
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printGeomMsg
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printGeomMsg(LPCTSTR event) const
{
    if (ArxRleGiWorldDraw::m_showGeomMsg)
        acutPrintf(_T("\n%-15s : %s "), _T("WorldGeometry"), event);
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printCircle
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printCircle(const AcGePoint3d& center,
                                const double radius,
                                const AcGeVector3d& normal)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("CENTER PT"), ArxRleUtils::ptToStr(center, str));
        printParamMsg(_T("RADIUS"), ArxRleUtils::doubleToStr(radius, str));
        printParamMsg(_T("NORMAL"), ArxRleUtils::vectorToStr(normal, str));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printCircle
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printCircle(const AcGePoint3d& p1,
                                const AcGePoint3d& p2,
                                const AcGePoint3d& p3)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("PT 1"), ArxRleUtils::ptToStr(p1, str));
        printParamMsg(_T("PT 2"), ArxRleUtils::ptToStr(p2, str));
        printParamMsg(_T("PT 3"), ArxRleUtils::ptToStr(p3, str));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printArc
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printArc(const AcGePoint3d& center,
                                const double radius, const AcGeVector3d& normal,
                                const AcGeVector3d& startVector,
                                const double sweepAngle,
                                const AcGiArcType arcType)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("CENTER"), ArxRleUtils::ptToStr(center, str));
        printParamMsg(_T("RADIUS"), ArxRleUtils::doubleToStr(radius, str));
        printParamMsg(_T("NORMAL"), ArxRleUtils::vectorToStr(normal, str));
        printParamMsg(_T("START VEC"), ArxRleUtils::vectorToStr(startVector, str));
        printParamMsg(_T("SWEEP ANG"), ArxRleUtils::angleToStr(sweepAngle, str));
        printParamMsg(_T("ARC TYPE"), arcTypeToStr(arcType, str));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printArc
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printArc(const AcGePoint3d& pt1,
                                const AcGePoint3d& pt2,
                                const AcGePoint3d& pt3,
                                const AcGiArcType arcType)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("PT 1"), ArxRleUtils::ptToStr(pt1, str));
        printParamMsg(_T("PT 2"), ArxRleUtils::ptToStr(pt2, str));
        printParamMsg(_T("PT 3"), ArxRleUtils::ptToStr(pt3, str));
        printParamMsg(_T("ARC TYPE"), arcTypeToStr(arcType, str));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printPolyline
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printPolyline(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList,
                                const AcGeVector3d* pNormal)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;

        ArxRleGiWorldGeometry::printPtArray(nbPoints, pVertexList);

        if (pNormal)
            printParamMsg(_T("NORMAL"), ArxRleUtils::vectorToStr(*pNormal, str));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printPolygon
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printPolygon(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        ArxRleGiWorldGeometry::printPtArray(nbPoints, pVertexList);
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printMesh
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printMesh(const Adesk::UInt32 rows,
                                const Adesk::UInt32 columns,
                                const AcGePoint3d* pVertexList,
                                const AcGiEdgeData* pEdgeData,
                                const AcGiFaceData* pFaceData,
                                const AcGiVertexData* pVertexData)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("ROWS"), ArxRleUtils::intToStr(rows, str));
        printParamMsg(_T("COLUMNS"), ArxRleUtils::intToStr(columns, str));

        ArxRleGiWorldGeometry::printPtArray(rows*columns, pVertexList);

        if (pEdgeData)
            printParamMsg(_T("EDGE DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("EDGE DATA"), _T("NULL"));

        if (pFaceData)
            printParamMsg(_T("FACE DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("FACE DATA"), _T("NULL"));

        if (pVertexData)
            printParamMsg(_T("VERT DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("VERT DATA"), _T("NULL"));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printShell
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printShell(const Adesk::UInt32 nbVertex,
                                const AcGePoint3d* pVertexList,
                                const Adesk::UInt32 faceListSize,
                                const Adesk::Int32* pFaceList,
                                const AcGiEdgeData* pEdgeData,
                                const AcGiFaceData* pFaceData,
                                const AcGiVertexData* pVertexData,
                                const struct resbuf* pResBuf)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str, str2;

        ArxRleGiWorldGeometry::printPtArray(nbVertex, pVertexList);

        printParamMsg(_T("FACE LIST SIZE"), ArxRleUtils::intToStr(faceListSize, str));
        for (int j=0; j < static_cast<int>(faceListSize); j++) {
            str2.Format(_T("FACE LIST [%d]"), j);
            printParamMsg(str2, ArxRleUtils::intToStr(pFaceList[j], str));
        }

        if (pEdgeData)
            printParamMsg(_T("EDGE DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("EDGE DATA"), _T("NULL"));

        if (pFaceData)
            printParamMsg(_T("FACE DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("FACE DATA"), _T("NULL"));

        if (pVertexData)
            printParamMsg(_T("VERT DATA"), _T("Not NULL"));
        else
            printParamMsg(_T("VERT DATA"), _T("NULL"));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printText
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printText(const AcGePoint3d& position,
                                const AcGeVector3d& normal,
                                const AcGeVector3d& direction,
                                const double height,
                                const double width,
                                const double oblique,
                                const TCHAR* pMsg)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("POSITION"), ArxRleUtils::ptToStr(position, str));
        printParamMsg(_T("NORMAL"), ArxRleUtils::vectorToStr(normal, str));
        printParamMsg(_T("DIRECTION"), ArxRleUtils::vectorToStr(direction, str));
        printParamMsg(_T("HEIGHT"), ArxRleUtils::doubleToStr(height, str));
        printParamMsg(_T("WDITH"), ArxRleUtils::doubleToStr(width, str));
        printParamMsg(_T("OBLIQUE"), ArxRleUtils::angleToStr(oblique, str));
        printParamMsg(_T("MSG"), pMsg);
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printText
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printText(const AcGePoint3d& position,
                                const AcGeVector3d& normal,
                                const AcGeVector3d& direction,
                                const TCHAR* pMsg,
                                const Adesk::Int32 length,
                                const Adesk::Boolean raw,
                                const AcGiTextStyle& pTextStyle)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("POSITION"), ArxRleUtils::ptToStr(position, str));
        printParamMsg(_T("NORMAL"), ArxRleUtils::vectorToStr(normal, str));
        printParamMsg(_T("DIRECTION"), ArxRleUtils::vectorToStr(direction, str));
        printParamMsg(_T("MSG"), pMsg);
        printParamMsg(_T("LENGTH"), ArxRleUtils::intToStr(length, str));
        printParamMsg(_T("RAW"), ArxRleUtils::booleanToStr(raw, str));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printRay
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printRay(const AcGePoint3d& start, const AcGePoint3d& other)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("START PT"), ArxRleUtils::ptToStr(start, str));
        printParamMsg(_T("OTHER PT"), ArxRleUtils::ptToStr(other, str));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printXline
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printXline(const AcGePoint3d& a, const AcGePoint3d& b)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("PT1"), ArxRleUtils::ptToStr(a, str));
        printParamMsg(_T("PT2"), ArxRleUtils::ptToStr(b, str));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printPline
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printPline(const AcDbPolyline& lwBuf,
                                    Adesk::UInt32 fromIndex,
                                    Adesk::UInt32 numSegs)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg) {
        CString str;
        printParamMsg(_T("FROM INDEX"), ArxRleUtils::intToStr(fromIndex, str));
        printParamMsg(_T("NUM SEGS"), ArxRleUtils::intToStr(numSegs, str));
    }
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::printPtArray
**
**  **jma
**
*************************************/

void
ArxRleGiWorldGeometry::printPtArray(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pVertexList)
{
    CString str;
    printParamMsg(_T("NUM PTS"), ArxRleUtils::intToStr(nbPoints, str));

    CString str2;
    for (int i=0;i<static_cast<int>(nbPoints);i++) {
        str2.Format(_T("PT [%d]"), i);
        printParamMsg(str2, ArxRleUtils::ptToStr(pVertexList[i], str));
    }
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////// GLOBAL FUNCS ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  arcTypeToStr
**
**  **jma
**
*************************************/

LPCTSTR
arcTypeToStr(AcGiArcType type, CString& str)
{
    if (type == kAcGiArcSimple)
        str = _T("kAcGiArcSimple");
    else if (type == kAcGiArcSector)
        str = _T("kAcGiArcSector");
    else if (type == kAcGiArcChord)
        str = _T("kAcGiArcChord");
    else {
        ASSERT(0);
        str = _T("UNKNOWN");
    }

    return(str);
}

/****************************************************************************
**
**  ArxRleGiWorldGeometry::fillTypeToStr
**
**  **jma
**
*************************************/

LPCTSTR
fillTypeToStr(AcGiFillType fillType, CString& str)
{
    if (fillType == kAcGiFillAlways)
        str = _T("kAcGiFillAlways");
    else if (fillType == kAcGiFillNever)
        str = _T("kAcGiFillNever");
    else {
        ASSERT(0);
        str = _T("UNKNOWN");
    }
    return(str);
}

/****************************************************************************
**
**  deviationTypeToStr:
**
**  **jma
**
*************************************/

LPCTSTR
deviationTypeToStr(AcGiDeviationType devType, CString& str)
{
    if (devType == kAcGiMaxDevForCircle)
        str = _T("kAcGiMaxDevForCircle");
    else if (devType == kAcGiMaxDevForCurve)
        str = _T("kAcGiMaxDevForCurve");
    else if (devType == kAcGiMaxDevForBoundary)
        str = _T("kAcGiMaxDevForBoundary");
    else if (devType == kAcGiMaxDevForFacet)
        str = _T("kAcGiMaxDevForFacet");
    else if (devType == kAcGiMaxDevForIsoline)
        str = _T("kAcGiMaxDevForIsoline");
    else {
        ASSERT(0);
        str = _T("UNKNOWN");
    }
    return(str);
}

/****************************************************************************
**
**  printParamMsg
**
**  **jma
**
*************************************/

void
printParamMsg(LPCTSTR tag, LPCTSTR msg)
{
    if (ArxRleGiWorldDraw::m_showDetailsMsg)
        acutPrintf(_T("\n  %-13s : %s "), tag, msg);
}
