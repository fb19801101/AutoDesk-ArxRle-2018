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

#include "ArxRleUtils.h"
#include "AcadStr.h"
#include "Prompt/ArxRleKeywordArray.h"
#include "ArxRle.h"




/****************************************************************************
**
**  ArxRleUtils::rxErrorMsg
**
**  **jma
**
*************************************/

void
ArxRleUtils::rxErrorMsg(Acad::ErrorStatus msgId)
{
    if (msgId != Acad::eOk)
        acutPrintf(_T("\nARX ERROR: %s"), acadErrorStatusText(msgId));
}

/****************************************************************************
**
**  ArxRleUtils::rxErrorAlert
**
**  **jma
**
*************************************/

void
ArxRleUtils::rxErrorAlert(Acad::ErrorStatus msgId)
{
    CString str;

    if (msgId != Acad::eOk){
        str.Format(_T("ARX ERROR: %s"), acadErrorStatusText(msgId));
        ArxRleUtils::alertBox(str);
    }
}

/****************************************************************************
**
**  ArxRleUtils::rxErrorStr
**
**  **jma
**
*************************************/

const TCHAR*
ArxRleUtils::rxErrorStr(Acad::ErrorStatus msgId)
{
    return acadErrorStatusText(msgId);
}

/****************************************************************************
**
**  ArxRleUtils::stubMsg
**
**  **jma
**
*************************************/

void
ArxRleUtils::stubMsg(LPCTSTR msg)
{
    acutPrintf(_T("\nNot Implemented Yet: %s"), msg);
}

/****************************************************************************
**
**  ArxRleUtils::findStandardAcadFile
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleUtils::findStandardAcadFile(LPCTSTR fileToFind, CString& foundFile)
{
    CString str;
    TCHAR tmpFile[512];

    ASSERT(fileToFind != NULL);
// Following Assert not liked by VC7
#if _MSC_VER < 1300    
    ASSERT(foundFile != NULL);
#endif

    if (acedFindFile(fileToFind, tmpFile) != RTNORM) {
        str.Format(_T("Could not find standard AutoCAD file \"%s\"."), fileToFind);
        ArxRleUtils::alertBox(str);
        return Acad::eInvalidInput;
    }
    else {
        foundFile = tmpFile;
        return Acad::eOk;
    }
}

/****************************************************************************
**
**  ArxRleUtils::selectEntity
**
**  **jma
**
*************************************/

AcDbEntity*
ArxRleUtils::selectEntity(LPCTSTR prompt, AcDb::OpenMode openMode)
{
    int rc;
    ads_name ename;
    ads_point pt;

    if (prompt)
        rc = acedEntSel(prompt, ename, pt);
    else
        rc = acedEntSel(_T("\nSelect an entity: "), ename, pt);

    if (rc != RTNORM){
        acutPrintf(_T("\nNothing selected."));
        return NULL;
    }

    AcDbObjectId objId;
    Acad::ErrorStatus es = ArxRleUtils::enameToObjId(ename, objId);
    if (es != Acad::eOk)
        return NULL;

    AcDbEntity* ent;
    es = acdbOpenAcDbEntity(ent, objId, openMode);
    if (es != Acad::eOk) {
        ArxRleUtils::rxErrorMsg(es);
        return NULL;
    }
    else
        return ent;
}

/****************************************************************************
**
**  ArxRleUtils::selectEntity
**
**  **jma
**
*************************************/

bool
ArxRleUtils::selectEntity(LPCTSTR prompt, AcDbObjectId& objId)
{
    int rc;
    ads_name ent;
    ads_point pt;

    if (prompt)
        rc = acedEntSel(prompt, ent, pt);
    else
        rc = acedEntSel(_T("\nSelect an entity: "), ent, pt);

    if (rc != RTNORM){
        acutPrintf(_T("\nNothing selected."));
        return false;
    }
    Acad::ErrorStatus es;
    es = acdbGetObjectId(objId, ent);
    if (es != Acad::eOk){
        rxErrorMsg(es);
        return false;
    }
    else
        return true;
}

/****************************************************************************
**
**  ArxRleUtils::selectEntityOrObject
**      allow user to select an entity or specify an object by its handle
**
**  **jma
**
*************************************/

bool
ArxRleUtils::selectEntityOrObject(AcDbObjectId& objId)
{
    ArxRleUiPrEntity prEnt(_T("Select an entity (or RETURN for Handle)"), NULL);
    prEnt.setAllowNone(true);
    ArxRleUiPrBase::Status stat = prEnt.go();

    if (stat == ArxRleUiPrBase::kNone) {
        ArxRleUiPrString prHandle(_T("Handle of database object"), false);
        if (prHandle.go() == ArxRleUiPrBase::kOk) {
            if (ArxRleUtils::handleStrToObjId(acdbHostApplicationServices()->workingDatabase(),
                            prHandle.value(), objId) != Acad::eOk) {
                ArxRleUtils::alertBox(_T("Couldn't find that handle!"));
                return false;
            }
            return true;
        }
        return false;
    }
    else if (stat == ArxRleUiPrBase::kOk) {
        objId = prEnt.objectId();
        return true;
    }
    else {
        return false;
    }
}

/****************************************************************************
**
**  ArxRleUtils::ptToStr (3D)
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::ptToStr(const AcGePoint3d& pt, CString& str, int unit, int prec)
{
    TCHAR xstr[100], ystr[100], zstr[100];

    acdbRToS(pt.x, unit, prec, xstr);
    acdbRToS(pt.y, unit, prec, ystr);
    acdbRToS(pt.z, unit, prec, zstr);

    str.Format(_T("(%s, %s, %s)"), xstr, ystr, zstr);
    return str;
}

/****************************************************************************
**
**  ArxRleUtils::ptToStr (2D)
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::ptToStr(const AcGePoint2d& pt, CString& str, int unit, int prec)
{
    TCHAR xstr[100], ystr[100];

    acdbRToS(pt.x, unit, prec, xstr);
    acdbRToS(pt.y, unit, prec, ystr);

    str.Format(_T("(%s, %s)"), xstr, ystr);
    return str;
}

/****************************************************************************
**
**  ArxRleUtils::vectorToStr (3D)
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::vectorToStr(const AcGeVector3d& vec, CString& str, int unit, int prec)
{
    TCHAR xstr[100], ystr[100], zstr[100];

    acdbRToS(vec.x, unit, prec, xstr);
    acdbRToS(vec.y, unit, prec, ystr);
    acdbRToS(vec.z, unit, prec, zstr);

    str.Format(_T("(%s, %s, %s)"), xstr, ystr, zstr);
    return str;
}

/****************************************************************************
**
**  ArxRleUtils::vectorToStr (2D)
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::vectorToStr(const AcGeVector2d& vec, CString& str, int unit, int prec)
{
    TCHAR xstr[100], ystr[100];

    acdbRToS(vec.x, unit, prec, xstr);
    acdbRToS(vec.y, unit, prec, ystr);

    str.Format(_T("(%s, %s)"), xstr, ystr);
    return str;
}

/****************************************************************************
**
**  ArxRleUtils::angleToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::angleToStr(const double angle, CString& str, int unit, int prec)
{
    TCHAR tmpStr[100];

    acdbAngToS(angle, unit, prec, tmpStr);
    str = tmpStr;
    return str;
}

/****************************************************************************
**
**  ArxRleUtils::doubleToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::doubleToStr(const double realVal, CString& str, int unit, int prec)
{
    TCHAR tmpStr[100];

    acdbRToS(realVal, unit, prec, tmpStr);
    str = tmpStr;
    return str;
}

/****************************************************************************
**
**  ArxRleUtils::intToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::intToStr(const int intVal, CString& str)
{
    str.Format(_T("%d"), intVal);
    return str;
}

/****************************************************************************
**
**  ArxRleUtils::intDbIdToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::intDbIdToStr(const Adesk::IntDbId intVal, CString& str)
{
#if !defined(_WIN64) && !defined (_AC64)
    str.Format(_T("%d"), intVal);
#else
    str.Format(_T("%I64d"), intVal);
#endif
    return str;
}

/****************************************************************************
**
**  ArxRleUtils::booleanToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::booleanToStr(bool b, CString& str)
{
    if (b)
        str = _T("True");
    else
        str = _T("False");

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::colorToStr
**      Convert a color index into a string. You must pass in
**  the buffer for the string, but the string pointer is also returned
**  incase you want to use it in a cascading expression.
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::colorToStr(int color, CString& str, bool convertStandard)
{
    color = abs(color);    // in case used from Layer table

    ASSERT((color >= 0) && (color <= 256));

    if (color == ArxRleUtils::kByblock)
        str = _T("ByBlock");
    else if (color == ArxRleUtils::kBylayer)
        str = _T("ByLayer");
    else if (convertStandard) {
        if (color == ArxRleUtils::kRed)
            str = _T("1-Red");
        else if (color == ArxRleUtils::kYellow)
            str = _T("2-Yellow");
        else if (color == ArxRleUtils::kGreen)
            str = _T("3-Green");
        else if (color == ArxRleUtils::kCyan)
            str = _T("4-Cyan");
        else if (color == ArxRleUtils::kBlue)
            str = _T("5-Blue");
        else if (color == ArxRleUtils::kMagenta)
            str = _T("6-Magenta");
        else if (color == ArxRleUtils::kWhite)
            str = _T("7-White");
        else
            intToStr(color, str);
    }
    else
        intToStr(color, str);

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::objToHandleStr
**      Obtain an old-style handle string from an object pointer.
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::objToHandleStr(const AcDbObject* obj, CString& str)
{
    ASSERT(obj != NULL);

    AcDbHandle handle;

    obj->getAcDbHandle(handle);
    TCHAR tmpStr[256];
    handle.getIntoAsciiBuffer(tmpStr);
    str = tmpStr;
    return str;
}

/***********************************************************************
**
**  ArxRleUtils::objToEnameStr
**      Obtain an old-style ename string from an object pointer.
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::objToEnameStr(const AcDbObject* obj, CString& str)
{
    ASSERT(obj != NULL);

    ads_name ent;
    acdbGetAdsName(ent, obj->objectId());
    str.Format(_T("%lx"), ent[0]);
    return str;
}

/***********************************************************************
**
**  ArxRleUtils::objToClassStr
**      Obtain a class name string from an object pointer.
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::objToClassStr(const AcRxObject* obj)
{
    ASSERT(obj != NULL);

    AcRxClass* rxClass = obj->isA();
    if (rxClass == NULL) {
        ASSERT(0);
        ArxRleUtils::stopAlertBox(_T("AcRxObject class has not called rxInit()!"));
        return _T("*Unknown*");
    }

    return obj->isA()->name();
}

/****************************************************************************
**
**  ArxRleUtils::objToClassAndHandleStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::objToClassAndHandleStr(const AcDbObjectId& objId, CString& str)
{
    CString tmpStr;
    AcDbObject* tmpObj;

    if (objId.isNull()) {
        str = _T("AcDbObjectId::kNull");
    }
    else {
            // open up even if erased
        Acad::ErrorStatus es = acdbOpenObject(tmpObj, objId, AcDb::kForRead, true);
        if (es == Acad::eOk) {
            str.Format(_T("<%-20s %-4s>"),
                    ArxRleUtils::objToClassStr(tmpObj), ArxRleUtils::objToHandleStr(tmpObj, tmpStr));
            tmpObj->close();
        }
        else
            str = ArxRleUtils::rxErrorStr(es);
    }

    return str;
}

/****************************************************************************
**
**  ArxRleUtils::objToClassAndHandleStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::objToClassAndHandleStr(const AcDbObject* obj, CString& str)
{
    CString tmpStr;

    str.Format(_T("<%-20s %-4s>"),
                ArxRleUtils::objToClassStr(obj), ArxRleUtils::objToHandleStr(obj, tmpStr));

    return str;
}

/****************************************************************************
**
**  ArxRleUtils::ptrToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::ptrToStr(void* ptr, CString& str)
{
    str.Format(_T("%p"), ptr);
    return str;
}

/****************************************************************************
**
**  ArxRleUtils::dbToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::dbToStr(AcDbDatabase* db, CString& str)
{
    if (db == NULL) {
        str = _T("NULL");
        return str;
    }

    const TCHAR* fname;
    Acad::ErrorStatus es = db->getFilename(fname);
    if (es == Acad::eOk)
        str.Format(_T("%p  \"%s\""), db, fname);
    else {
            // see if we can get name from a document
        AcApDocument* doc = acDocManager->document(db);
        if (doc) {
            str.Format(_T("%p  \"%s\""), db, doc->fileName());
        }
        else {
                // last resort, just use the pointer value.  eNotApplicable
                // happens frequently on temporary databases, otherwise we
                // would like to know what is going on.
            if (es == Acad::eNotApplicable)
                str.Format(_T("%p"), db);
            else {
                ASSERT(0);
                str.Format(_T("%p  %s"), db, ArxRleUtils::rxErrorStr(es));
            }
        }
    }

    return str;
}

/****************************************************************************
**
**  ArxRleUtils::vertexTypeToStr
**      convert a vertex type to its string value
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::vertexTypeToStr(AcDb::Vertex3dType vertexType, CString& str)
{
    if (vertexType == AcDb::k3dSimpleVertex)
        str = _T("3D Vertex");
    else if (vertexType == AcDb::k3dControlVertex)
        str = _T("3D Control Vertex");
    else if (vertexType == AcDb::k3dFitVertex)
        str = _T("3D Fit Vertex");
    else {
        ASSERT(0);
        str = _T("*Unknown*");
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::textModeToStr        HORIZONTAL
**      Convert a text mode value into a string for printing
**  purposes.
**
**    **jma
**
****************************************/

LPCTSTR
ArxRleUtils::textModeToStr(AcDb::TextHorzMode horizMode, CString& str)
{
    switch (horizMode) {
        case AcDb::kTextLeft:
            str = _T("Left");
            break;
        case AcDb::kTextCenter:
            str = _T("Center");
            break;
        case AcDb::kTextRight:
            str = _T("Right");
            break;
        case AcDb::kTextAlign:
            str = _T("Align");
            break;
        case AcDb::kTextMid:
            str = _T("Mid");
            break;
        case AcDb::kTextFit:
            str = _T("Fit");
            break;
        default:
            ASSERT(0);
            str = _T("*Unknown*");
    }
    return str;
}

/***********************************************************************
**
**  ArxRleUtils::textModeToStr       VERTICAL
**      Convert a text mode value into a string for printing
**  purposes.
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::textModeToStr(AcDb::TextVertMode vertMode, CString& str)
{
    switch (vertMode) {
        case AcDb::kTextBase:
            str = _T("Baseline");
            break;
        case AcDb::kTextBottom:
            str = _T("Bottom");
            break;
        case AcDb::kTextVertMid:
            str = _T("Vertical Mid");
            break;
        case AcDb::kTextTop:
            str = _T("Top");
            break;
        default:
            ASSERT(0);
            str = _T("*Unknown*");
    }
    return str;
}

/***********************************************************************
**
**  ArxRleUtils::hatchTypeToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::hatchTypeToStr(AcDbHatch::HatchPatternType hatchType, CString& str)
{
    if (hatchType == AcDbHatch::kUserDefined)
        str = _T("User Defined");
    else if (hatchType == AcDbHatch::kPreDefined)
        str = _T("Pre Defined");
    else if (hatchType == AcDbHatch::kCustomDefined)
        str = _T("Custom Defined");
    else {
        ASSERT(0);
        ArxRleUtils::intToStr(hatchType, str);
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::hatchStyleToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::hatchStyleToStr(AcDbHatch::HatchStyle style, CString& str)
{
    if (style == AcDbHatch::kNormal)
        str = _T("Normal");
    else if (style == AcDbHatch::kOuter)
        str = _T("Outer");
    else if (style == AcDbHatch::kIgnore)
        str = _T("Ignore");
    else {
        ASSERT(0);
        ArxRleUtils::intToStr(style, str);
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::hatchLoopTypeToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::hatchLoopTypeToStr(Adesk::Int32 loopType, CString& str)
{
    if (loopType == AcDbHatch::kDefault)
        str = _T("Default");
    else if (loopType == AcDbHatch::kExternal)
        str = _T("External");
    else if (loopType == AcDbHatch::kPolyline)
        str = _T("Polyline");
    else if (loopType == AcDbHatch::kDerived)
        str = _T("Derived");
    else if (loopType == AcDbHatch::kTextbox)
        str = _T("Textbox");
    else if (loopType == AcDbHatch::kOutermost)
        str = _T("Outermost");
    else if (loopType == AcDbHatch::kNotClosed)
        str = _T("Not Closed");
    else if (loopType == AcDbHatch::kSelfIntersecting)
        str = _T("Self Intersecting");
    else {
        ASSERT(0);
        ArxRleUtils::intToStr(loopType, str);
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::mtextAttachmentTypeToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::mtextAttachmentTypeToStr(AcDbMText::AttachmentPoint type, CString& str)
{
    if (type == AcDbMText::kTopLeft)
        str = _T("Top Left");
    else if (type == AcDbMText::kTopCenter)
        str = _T("Top Center");
    else if (type == AcDbMText::kTopRight)
        str = _T("Top Right");
    else if (type == AcDbMText::kMiddleLeft)
        str = _T("Middle Left");
    else if (type == AcDbMText::kMiddleCenter)
        str = _T("Middle Center");
    else if (type == AcDbMText::kMiddleRight)
        str = _T("Middle Right");
    else if (type == AcDbMText::kBottomLeft)
        str = _T("Bottom Left");
    else if (type == AcDbMText::kBottomCenter)
        str = _T("Bottom Center");
    else if (type == AcDbMText::kBottomRight)
        str = _T("Bottom Right");
    else {
        ASSERT(0);
        str = _T("*Unknown*");
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::mtextFlowDirTypeToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::mtextFlowDirTypeToStr(AcDbMText::FlowDirection type, CString& str)
{
    if (type == AcDbMText::kLtoR)
        str = _T("Left to Right");
    else if (type == AcDbMText::kRtoL)
        str = _T("Right to Left");
    else if (type == AcDbMText::kTtoB)
        str = _T("Top to Bottom");
    else if (type == AcDbMText::kBtoT)
        str = _T("Bottom to Top");
    else if (type == AcDbMText::kByStyle)
        str = _T("By Style");
    else {
        ASSERT(0);
        str  = _T("*Unknown*");
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::lineSpacingTypeToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::lineSpacingTypeToStr(AcDb::LineSpacingStyle type, CString& str)
{
    if (type == AcDb::kAtLeast)
        str = _T("At Least");
    else if (type == AcDb::kExactly)
        str = _T("Exactly");
    else {
        ASSERT(0);
        str  = _T("*Unknown*");
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::proxyMetafileTypeToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::proxyMetafileTypeToStr(AcDbProxyEntity::GraphicsMetafileType type, CString& str)
{
    if (type == AcDbProxyEntity::kNoMetafile)
        str = _T("No Metafile");
    else if (type == AcDbProxyEntity::kBoundingBox)
        str = _T("Bounding Box");
    else if (type == AcDbProxyEntity::kFullGraphics)
        str = _T("Full Graphics");
    else {
        ASSERT(0);
        ArxRleUtils::intToStr(type, str);
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::lineWeightTypeToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::lineWeightTypeToStr(AcDb::LineWeight type, CString& str)
{
    if (type == AcDb::kLnWt000)
        str = _T("0.00 mm");
    else if (type == AcDb::kLnWt005)
        str = _T("0.05 mm");
    else if (type == AcDb::kLnWt009)
        str = _T("0.09 mm");
    else if (type == AcDb::kLnWt013)
        str = _T("0.13 mm");
    else if (type == AcDb::kLnWt015)
        str = _T("0.15 mm");
    else if (type == AcDb::kLnWt018)
        str = _T("0.18 mm");
    else if (type == AcDb::kLnWt020)
        str = _T("0.20 mm");
    else if (type == AcDb::kLnWt025)
        str = _T("0.25 mm");
    else if (type == AcDb::kLnWt030)
        str = _T("0.30 mm");
    else if (type == AcDb::kLnWt035)
        str = _T("0.35 mm");
    else if (type == AcDb::kLnWt040)
        str = _T("0.40 mm");
    else if (type == AcDb::kLnWt050)
        str = _T("0.50 mm");
    else if (type == AcDb::kLnWt053)
        str = _T("0.53 mm");
    else if (type == AcDb::kLnWt060)
        str = _T("0.60 mm");
    else if (type == AcDb::kLnWt070)
        str = _T("0.70 mm");
    else if (type == AcDb::kLnWt080)
        str = _T("0.80 mm");
    else if (type == AcDb::kLnWt090)
        str = _T("0.90 mm");
    else if (type == AcDb::kLnWt100)
        str = _T("1.00 mm");
    else if (type == AcDb::kLnWt106)
        str = _T("1.06 mm");
    else if (type == AcDb::kLnWt120)
        str = _T("1.20 mm");
    else if (type == AcDb::kLnWt140)
        str = _T("1.40 mm");
    else if (type == AcDb::kLnWt158)
        str = _T("1.58 mm");
    else if (type == AcDb::kLnWt200)
        str = _T("2.00 mm");
    else if (type == AcDb::kLnWt211)
        str = _T("2.11 mm");
    else if (type == AcDb::kLnWtByLayer)
        str = _T("ByLayer");
    else if (type == AcDb::kLnWtByBlock)
        str = _T("ByBlock");
    else if (type == AcDb::kLnWtByLwDefault)
        str = _T("ByLwDefault");
    else {
        ASSERT(0);
        str = _T("*Unknown*");
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::mergeStyleToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::mergeStyleToStr(AcDb::DuplicateRecordCloning type, CString& str)
{
    if (type == AcDb::kDrcNotApplicable)
        str = _T("Not Applicable");
    else if (type == AcDb::kDrcIgnore)
        str = _T("Ignore");
    else if (type == AcDb::kDrcReplace)
        str = _T("Replace");
    else if (type == AcDb::kDrcXrefMangleName)
        str = _T("Xref Mangle Name");
    else if (type == AcDb::kDrcMangleName)
        str = _T("Mangle Name");
    else if (type == AcDb::kDrcUnmangleName)
        str = _T("Unmangle Name");
    else {
        //ASSERT(0);
        str.Format(_T("*Unknown* (%d)"), type);
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::standardScaleTypeToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::standardScaleTypeToStr(AcDbViewport::StandardScaleType type, CString& str)
{
    if (type == AcDbViewport::kScaleToFit)
        str = _T("Scaled To Fit");
    else if (type == AcDbViewport::kCustomScale)
        str = _T("Custom Scale");
    else if (type == AcDbViewport::k1_1)
        str = _T("1:1");
    else if (type == AcDbViewport::k1_2)
        str = _T("1:2");
    else if (type == AcDbViewport::k1_4)
        str = _T("1:4");
    else if (type == AcDbViewport::k1_8)
        str = _T("1:8");
    else if (type == AcDbViewport::k1_10)
        str = _T("1:10");
    else if (type == AcDbViewport::k1_16)
        str = _T("1:16");
    else if (type == AcDbViewport::k1_20)
        str = _T("1:20");
    else if (type == AcDbViewport::k1_30)
        str = _T("1:30");
    else if (type == AcDbViewport::k1_40)
        str = _T("1:40");
    else if (type == AcDbViewport::k1_50)
        str = _T("1:50");
    else if (type == AcDbViewport::k1_100)
        str = _T("1:100");
    else if (type == AcDbViewport::k2_1)
        str = _T("2:1");
    else if (type == AcDbViewport::k4_1)
        str = _T("4:1");
    else if (type == AcDbViewport::k8_1)
        str = _T("8:1");
    else if (type == AcDbViewport::k10_1)
        str = _T("10:1");
    else if (type == AcDbViewport::k100_1)
        str = _T("100:1");
    else if (type == AcDbViewport::k1_128in_1ft)
        str = _T("1/128\"= 1'");
    else if (type == AcDbViewport::k1_64in_1ft)
        str = _T("1/64\"= 1'");
    else if (type == AcDbViewport::k1_32in_1ft)
        str = _T("1/32\"= 1'");
    else if (type == AcDbViewport::k1_16in_1ft)
        str = _T("1/16\"= 1'");
    else if (type == AcDbViewport::k3_32in_1ft)
        str = _T("3/32\"= 1'");
    else if (type == AcDbViewport::k1_8in_1ft)
        str = _T("1/8\" = 1'");
    else if (type == AcDbViewport::k3_16in_1ft)
        str = _T("3/16\"= 1'");
    else if (type == AcDbViewport::k1_64in_1ft)
        str = _T("1/64\" = 1'");
    else if (type == AcDbViewport::k1_4in_1ft)
        str = _T("1/4\" = 1'");
    else if (type == AcDbViewport::k3_8in_1ft)
        str = _T("3/8\" = 1'");
    else if (type == AcDbViewport::k1_2in_1ft)
        str = _T("1/2\" = 1'");
    else if (type == AcDbViewport::k3_4in_1ft)
        str = _T("3/4\" = 1'");
    else if (type == AcDbViewport::k1in_1ft)
        str = _T("1\"= 1'");
    else if (type == AcDbViewport::k3in_1ft)
        str = _T("3\"= 1'");
    else if (type == AcDbViewport::k6in_1ft)
        str = _T("6\"= 1'");
    else if (type == AcDbViewport::k1ft_1ft)
        str = _T("1'= 1'");
    else {
        ASSERT(0);
        str = _T("*Unknown*");
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::dwgVersionToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::dwgVersionToStr(AcDb::AcDbDwgVersion type, CString& str)
{
    CString verStr;

    if (type == AcDb::kDHL_MC0_0)
        verStr = _T("kDHL_MC0_0");
    else if (type == AcDb::kDHL_AC1_2)
        verStr = _T("kDHL_AC1_2");
    else if (type == AcDb::kDHL_AC1_40)
        verStr = _T("kDHL_AC1_40");
    else if (type == AcDb::kDHL_AC1_50)
        verStr = _T("kDHL_AC1_50");
    else if (type == AcDb::kDHL_AC2_20)
        verStr = _T("kDHL_AC2_20");
    else if (type == AcDb::kDHL_AC2_10)
        verStr = _T("kDHL_AC2_10");
    else if (type == AcDb::kDHL_AC2_21)
        verStr = _T("kDHL_AC2_21");
    else if (type == AcDb::kDHL_AC2_22)
        verStr = _T("kDHL_AC2_22");
    else if (type == AcDb::kDHL_1001)
        verStr = _T("kDHL_1001");
    else if (type == AcDb::kDHL_1002)
        verStr = _T("kDHL_1002  (AutoCAD 2.5)");
    else if (type == AcDb::kDHL_1003)
        verStr = _T("kDHL_1003  (AutoCAD 2.6)");
    else if (type == AcDb::kDHL_1004)
        verStr = _T("kDHL_1004  (Release 9)");
    else if (type == AcDb::kDHL_1005)
        verStr = _T("kDHL_1005");
    else if (type == AcDb::kDHL_1006)
        verStr = _T("kDHL_1006  (Release 10)");
    else if (type == AcDb::kDHL_1007)
        verStr = _T("kDHL_1007");
    else if (type == AcDb::kDHL_1008)
        verStr = _T("kDHL_1008");
    else if (type == AcDb::kDHL_1009)
        verStr = _T("kDHL_1009  (R11 and R12)");
    else if (type == AcDb::kDHL_1010)
        verStr = _T("kDHL_1010");
    else if (type == AcDb::kDHL_1011)
        verStr = _T("kDHL_1011");
    else if (type == AcDb::kDHL_1012)
        verStr = _T("kDHL_1012  (Release 13)");
    else if (type == AcDb::kDHL_1013)
        verStr = _T("kDHL_1013  (R14 Mid Version)");
    else if (type == AcDb::kDHL_1014)
        verStr = _T("kDHL_1014  (R14 Final Version)");
    else if (type == AcDb::kDHL_1500)
        verStr = _T("kDHL_1500  (R2000 Development)");
    else if (type == AcDb::kDHL_1015)
        verStr = _T("kDHL_1015  (R2000 Final Version)");
    else if (type == AcDb::kDHL_1800a)
        verStr = _T("kDHL_1800a (R2004 Development Version)");
     else if (type == AcDb::kDHL_1800)
        verStr = _T("kDHL_1800 (R2004  Final Version)");
     else if (type == AcDb::kDHL_2100a)
        verStr = _T("kDHL_2100a (R2007 Development Version)");
     else if (type == AcDb::kDHL_1021)
        verStr = _T("kDHL_1021 (R2007 Final Version)");
     else if (type == AcDb::kDHL_2400a)
        verStr = _T("kDHL_2400a (R2010 Development Version)");
     else if (type == AcDb::kDHL_1024)
        verStr = _T("kDHL_1024 (R2010 Final Version)");
     else if (type == AcDb::kDHL_2700a)
        verStr = _T("kDHL_2700a (R2013 Development Version)");
     else if (type == AcDb::kDHL_1027)
        verStr = _T("kDHL_1027 (R2013 Final Version)");
     else if (type == AcDb::kDHL_3200a)
        verStr = _T("kDHL_3200a (R2018 Development Version)");
     else if (type == AcDb::kDHL_1032)
        verStr = _T("kDHL_1032 (R2018 Final Version)");
     else {
        ASSERT(0);
        ASSERT(AcDb::kDHL_Newest == AcDb::kDHL_1032); // update needed above
        verStr = _T("*Unknown*");
    }

    str.Format(_T("%d = %s"), type, verStr);
    return str;
}

/***********************************************************************
**
**  ArxRleUtils::orthoViewToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::orthoViewToStr(AcDb::OrthographicView type, CString& str)
{
    if (type == AcDb::kNonOrthoView)
        str = _T("Non Ortho");
    else if (type == AcDb::kTopView)
        str = _T("Top");
    else if (type == AcDb::kBottomView)
        str = _T("Bottom");
    else if (type == AcDb::kFrontView)
        str = _T("Front");
    else if (type == AcDb::kBackView)
        str = _T("Back");
    else if (type == AcDb::kLeftView)
        str = _T("Left");
    else if (type == AcDb::kRightView)
        str = _T("Right");
    else {
        ASSERT(0);
        str = _T("*Unknown*");
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::measurementTypeToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::measurementTypeToStr(AcDb::MeasurementValue type, CString& str)
{
    if (type == AcDb::kEnglish)
        str = _T("English");
    else if (type == AcDb::kMetric)
        str = _T("Metric");
    else {
        ASSERT(0);
        str = _T("*Unknown*");
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::unitTypeToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::unitTypeToStr(AcDb::UnitsValue type, CString& str)
{
    if (type == AcDb::kUnitsUndefined)
        str = _T("Undefined");
    else if (type == AcDb::kUnitsInches)
        str = _T("Inches");
    else if (type == AcDb::kUnitsFeet)
        str = _T("Feet");
    else if (type == AcDb::kUnitsMiles)
        str = _T("Miles");
    else if (type == AcDb::kUnitsMillimeters)
        str = _T("Millimeters");
    else if (type == AcDb::kUnitsCentimeters)
        str = _T("Centimeters");
    else if (type == AcDb::kUnitsMeters)
        str = _T("Meters");
    else if (type == AcDb::kUnitsKilometers)
        str = _T("Kilometers");
    else if (type == AcDb::kUnitsMicroinches)
        str = _T("Microinches");
    else if (type == AcDb::kUnitsMils)
        str = _T("Mils");
    else if (type == AcDb::kUnitsYards)
        str = _T("Yards");
    else if (type == AcDb::kUnitsAngstroms)
        str = _T("Angstroms");
    else if (type == AcDb::kUnitsNanometers)
        str = _T("Nanometers");
    else if (type == AcDb::kUnitsMicrons)
        str = _T("Microns");
    else if (type == AcDb::kUnitsDecimeters)
        str = _T("Decimeters");
    else if (type == AcDb::kUnitsDekameters)
        str = _T("Dekameters");
    else if (type == AcDb::kUnitsHectometers)
        str = _T("Hectometers");
    else if (type == AcDb::kUnitsGigameters)
        str = _T("Gigameters");
    else if (type == AcDb::kUnitsAstronomical)
        str = _T("Astronomical");
    else if (type == AcDb::kUnitsLightYears)
        str = _T("Light Years");
    else if (type == AcDb::kUnitsParsecs)
        str = _T("Parsecs");
    else {
        ASSERT(0);
        str = _T("*Unknown*");
    }

    return str;
}

/****************************************************************************
**
**  ArxRleUtils::xrefStatusToSTr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::xrefStatusToStr(AcDb::XrefStatus stat, CString& str)
{
    if (stat == AcDb::kXrfNotAnXref)
        str = _T("Not An Xref");
    else if (stat == AcDb::kXrfResolved)
        str = _T("Xref Resolved");
    else if (stat == AcDb::kXrfUnloaded)
        str = _T("Xref Unloaded");
    else if (stat == AcDb::kXrfUnreferenced)
        str = _T("Xref Unreferenced");
    else if (stat == AcDb::kXrfFileNotFound)
        str = _T("Xref File Not Found");
    else if (stat == AcDb::kXrfUnresolved)
        str = _T("Xref Unresolved");
    else {
        ASSERT(0);
        str = _T("*Unknown*");
    }

    return str;
}

/****************************************************************************
**
**  ArxRleUtils::saveFormatToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::saveFormatToStr(AcApDocument::SaveFormat type, CString& str)
{
    if (type == AcApDocument::kUnknown)
        str = _T("Invalid");
    else if (type == AcApDocument::kR12_dxf)
        str = _T("AutoCAD R12/LT2 DXF (*.dxf)");
    else if (type == AcApDocument::kR13_dwg)
        str = _T("AutoCAD R13/LT95 Drawing (*.dwg)");
    else if (type == AcApDocument::kR13_dxf)
        str = _T("AutoCAD R13/LT95 DXF (*.dxf)");
    else if (type == AcApDocument::kR14_dwg)
        str = _T("AutoCAD R14/LT97 Drawing (*.dwg)");
    else if (type == AcApDocument::kR14_dxf)
        str = _T("AutoCAD R14/LT97 DXF (*.dxf)");
    else if (type == AcApDocument::k2000_dwg)
        str = _T("AutoCAD 2000 Drawing (*.dwg)");
    else if (type == AcApDocument::k2000_dxf)
        str = _T("AutoCAD 2000 DXF (*.dxf)");
    else if (type == AcApDocument::k2000_Template)
        str = _T("AutoCAD 2000 Drawing Template File (*.dwt)");
    else if (type == AcApDocument::k2004_dwg)
        str = _T("AutoCAD 2004 Drawing (*.dwg)");
    else if (type == AcApDocument::k2004_dxf)
        str = _T("AutoCAD 2004 DXF (*.dxf)");
    else if (type == AcApDocument::k2004_Template)
        str = _T("AutoCAD 2004 Drawing Template File (*.dwt)");
    else if (type == AcApDocument::k2007_dwg)
        str = _T("AutoCAD 2007 Drawing (*.dwg)");
    else if (type == AcApDocument::k2007_dxf)
        str = _T("AutoCAD 2007 DXF (*.dxf)");
    else if (type == AcApDocument::k2007_Template)
        str = _T("AutoCAD 2007 Drawing Template File (*.dwt)");
    else if (type == AcApDocument::k2010_dwg)
        str = _T("AutoCAD 2010 Drawing (*.dwg)");
    else if (type == AcApDocument::k2010_dxf)
        str = _T("AutoCAD 2010 DXF (*.dxf)");
    else if (type == AcApDocument::k2010_Template)
        str = _T("AutoCAD 2010 Drawing Template File (*.dwt)");
    else if (type == AcApDocument::k2013_dwg)
        str = _T("AutoCAD 2013 Drawing (*.dwg)");
    else if (type == AcApDocument::k2013_dxf)
        str = _T("AutoCAD 2013 DXF (*.dxf)");
    else if (type == AcApDocument::k2013_Template)
        str = _T("AutoCAD 2013 Drawing Template File (*.dwt)");
    else if (type == AcApDocument::k2018_dwg)
        str = _T("AutoCAD 2018 Drawing (*.dwg)");
    else if (type == AcApDocument::k2018_dxf)
        str = _T("AutoCAD 2018 DXF (*.dxf)");
    else if (type == AcApDocument::k2018_Template)
        str = _T("AutoCAD 2018 Drawing Template File (*.dwt)");
    else {
        ASSERT(0);
        str = _T("*Unknown*");
	}

    return str;
}

/****************************************************************************
**
**  ArxRleUtils::longTransactionTypeToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::longTransactionTypeToStr(int type, CString& str)
{
    if (type == AcDbLongTransaction::kSameDb)
        str = _T("Same Database");
    else if (type == AcDbLongTransaction::kXrefDb)
        str = _T("Xref Database");
    else if (type == AcDbLongTransaction::kUnrelatedDb)
        str = _T("Unrelated Database");
    else {
        ASSERT(0);
        str = _T("*Unknown*");
    }

    return str;
}

/****************************************************************************
**
**  ArxRleUtils::docLockModeToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::docLockModeToStr(AcAp::DocLockMode mode, CString& str)
{
    str.Empty();

    if (mode & AcAp::kNone)
        str += _T("None");

    if (mode & AcAp::kAutoWrite) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("Auto Write");
    }

    if (mode & AcAp::kNotLocked) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("Not Locked");
    }

    if (mode & AcAp::kWrite) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("Write");
    }

    if (mode & AcAp::kProtectedAutoWrite) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("Protected Auto Write");
    }

    if (mode & AcAp::kRead) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("Read");
    }

    if (mode & AcAp::kXWrite) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("X Write");
    }


    return str;
}

/***********************************************************************
**
**  ArxRleUtils::deepCloneContextToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::deepCloneContextToStr(AcDb::DeepCloneType context, CString& str)
{
    if (context == AcDb::kDcCopy)
        str = _T("Copy");
    else if (context == AcDb::kDcExplode)
        str = _T("Explode");
    else if (context == AcDb::kDcBlock)
        str = _T("Block");
    else if (context == AcDb::kDcSymTableMerge)
        str = _T("Sym Tbl Merge");
    else if (context == AcDb::kDcInsert)
        str = _T("Insert");
    else if (context == AcDb::kDcInsertCopy)
        str = _T("Insert Copy");
    else if (context == AcDb::kDcWblock)
        str = _T("Wblock");
    else if (context == AcDb::kDcObjects)
        str = _T("Objects");
    else if (context == AcDb::kDcXrefInsert)
        str = _T("XRef Insert");
    else if (context == AcDb::kDcXrefBind)
        str = _T("Xref Bind");
    else if (context == AcDb::kDcWblkObjects)
        str = _T("Wblock Objects");
    else {
        ASSERT(0);
        str = _T("*Unknown*");
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::dateToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::dateToStr(const AcDbDate& date, CString& str)
{
    str.Format(_T("%d Hr., %d Min., %d Sec, %d Msec"),
                date.hour(), date.minute(), date.second(), date.millisecond());
    return str;
}

/***********************************************************************
**
**  ArxRleUtils::promptStatusToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::promptStatusToStr(Acad::PromptStatus stat, CString& str)
{
    if (stat == Acad::eNone)
        str = _T("None");
    else if (stat == Acad::eNormal)
        str = _T("Normal");
    else if (stat == Acad::eError)
        str = _T("Error");
    else if (stat == Acad::eCancel)
        str = _T("Cancel");
    else if (stat == Acad::eRejected)
        str = _T("Rejected");
    else if (stat == Acad::eFailed)
        str = _T("Failed");
    else if (stat == Acad::eKeyword)
        str = _T("Keyword");
    else if (stat == Acad::eDirect)
        str = _T("Direct");
    else {
        ASSERT(0);
        str.Format(_T("*Unknown* (%d)"), stat);
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::initFlagsToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::initFlagsToStr(int initFlags, CString& str)
{
    str.Empty();

    if (initFlags & RSG_NONULL)
        str += _T("NoNull");

    if (initFlags & RSG_NOZERO) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("NoZero");
    }

    if (initFlags & RSG_NONEG) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("NoNeg");
    }

    if (initFlags & RSG_NOLIM) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("NoLim");
    }

    if (initFlags & RSG_GETZ) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("GetZ");
    }

    if (initFlags & RSG_DASH) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("Dash");
    }

    if (initFlags & RSG_2D) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("2D");
    }

    if (initFlags & RSG_OTHER) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("Other");
    }

    if (initFlags & RSG_DDISTFIRST) {
        if (str.IsEmpty() == false)
            str += _T(" | ");
        str += _T("DdDistFirst");
    }

    return str;
}

/***********************************************************************
**
**  ArxRleUtils::promptStatusToStr
**
**  **jma
**
****************************************/

LPCTSTR
ArxRleUtils::filerTypeToStr(AcDb::FilerType type, CString& str)
{
    if (type == AcDb::kFileFiler)
        str = _T("File");
    else if (type == AcDb::kCopyFiler)
        str = _T("Copy");
    else if (type == AcDb::kUndoFiler)
        str = _T("Undo");
    else if (type == AcDb::kBagFiler)
        str = _T("Bag");
    else if (type == AcDb::kIdXlateFiler)
        str = _T("IdXlate");
    else if (type == AcDb::kPageFiler)
        str = _T("Page");
    else if (type == AcDb::kIdFiler)
        str = _T("Id");
    else if (type == AcDb::kDeepCloneFiler)
        str = _T("DeepClone");
    else if (type == AcDb::kPurgeFiler)
        str = _T("Purge");
    else if (type == AcDb::kWblockCloneFiler)
        str = _T("WblockClone");
    else {
        ASSERT(0);
        str.Format(_T("*Unknown* (%d)"), type);
    }

    return str;
}

/****************************************************************************
**
**  ArxRleUtils::osnapToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::osnapToStr(int osnapMode, CString& str)
{
    if (osnapMode == AcDb::kOsModeEnd)
        str = _T("End");
    else if (osnapMode == AcDb::kOsModeMid)
        str = _T("Mid");
    else if (osnapMode == AcDb::kOsModeCen)
        str = _T("Cen");
    else if (osnapMode == AcDb::kOsModeNode)
        str = _T("Node");
    else if (osnapMode == AcDb::kOsModeQuad)
        str = _T("Quad");
    else if (osnapMode == AcDb::kOsModeIns)
        str = _T("Ins");
    else if (osnapMode == AcDb::kOsModePerp)
        str = _T("Perp");
    else if (osnapMode == AcDb::kOsModeTan)
        str = _T("Tan");
    else if (osnapMode == AcDb::kOsModeNear)
        str = _T("Near");
    else
        str.Format(_T("*Unknown* (%d)"), osnapMode);

    return str;
}

/****************************************************************************
**
**  ArxRleUtils::doubleArray3dToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::doubleArray3dToStr(double array[], CString& str)
{
    str.Format(_T("(%.15g, %.15g, %.15g)"), array[0], array[1], array[2]);
    return str;
}

/****************************************************************************
**
**  ArxRleUtils::doubleArray2dToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleUtils::doubleArray2dToStr(double array[], CString& str)
{
    str.Format(_T("(%.15g, %.15g)"), array[0], array[1]);
    return str;
}

/***********************************************************************
**
**  ArxRleUtils::printIdMap
**
**  **jma
**
****************************************/

void
ArxRleUtils::printIdMap(AcDbIdMapping* idMap, LPCTSTR msgStr)
{
    AcDbObject* obj;
    Acad::ErrorStatus es;

    acutPrintf(_T("\n*********************************************\n"));
    acutPrintf(_T("\nEVENT: %s"), msgStr);

    AcDbIdPair idPair;
    AcDbIdMappingIter mapIter(*idMap);
    for (mapIter.start(); !mapIter.done(); mapIter.next()) {
        if (mapIter.getMap(idPair)) {
            es = acdbOpenAcDbObject(obj, idPair.value(), AcDb::kForRead);
            if (es == Acad::eOk) {
                acutPrintf(_T("\nCloned:   <%-20s>"), ArxRleUtils::objToClassStr(obj));
                acutPrintf(_T("\n%ld  -->  %ld"), idPair.key().asOldId(), idPair.value().asOldId());
                acutPrintf(_T("\nIsCloned: %ld"), idPair.isCloned());
                acutPrintf(_T("\nIsXlated: %ld"), idPair.isOwnerXlated());
                obj->close();
            }
        }
    }

    acutPrintf(_T("\n*********************************************\n"));
}

/***********************************************************************
**
**  ArxRleUtils::grdrawPline
**
**  **jma
**
****************************************/

void
ArxRleUtils::grdrawPline(const AcGePoint3dArray& pts, BOOL close, BOOL hilite)
{
    int len;
    if ((len = pts.length()) == 0)
        return;

    int color;
    if (hilite)
        color = 6;
    else
        color = 7;

    for (int i=1;i<len;i++)
        acedGrDraw(asDblArray(pts.at(i-1)), asDblArray(pts.at(i)), color, 0);

    if (close)
        acedGrDraw(asDblArray(pts.at(0)), asDblArray(pts.at(len-1)), color, 0);
}

/***********************************************************************
**
**  ArxRleUtils::stuffAcadCmdLine
**
**  **jma
**
****************************************/

void
ArxRleUtils::stuffAcadCmdLine(const CString& str)
{
    if (str.IsEmpty())
        return;

    CString tmpStr = str;
    tmpStr += _T("\n");

    Acad::ErrorStatus es;
    es = acDocManager->sendStringToExecute(acDocManager->curDocument(), tmpStr, false, true);
    if (es != Acad::eOk)
        ArxRleUtils::rxErrorMsg(es);
}

/***********************************************************************
**
**  ArxRleUtils::clearAcadCmdLine
**
**  **jma
**
****************************************/

void
ArxRleUtils::clearAcadCmdLine()
{
    acedGetAcadTextCmdLine()->PostMessage(WM_CHAR, VK_ESCAPE, 0);
    acedGetAcadTextCmdLine()->PostMessage(WM_CHAR, VK_ESCAPE, 0);
}

/****************************************************************************
**
**  ArxRleUtils::getPlinePointArrayFromUser
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleUtils::getPlinePointArrayFromUser(AcGePoint3dArray& vertices)
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
    int ptCount = vertices.length();
    if (ptCount < 2) {
        acutPrintf(_T("\nThere must be at least 2 points."));
        return Acad::eInvalidInput;
    }

    i = 1;
    while(i < ptCount){
        acedGrDraw(asDblArray(vertices[i-1]), asDblArray(vertices[i]), -1, 0);
        i++;
    }
    return Acad::eOk;
}

/************************************************************************
**
**  ArxRleUtils::debugPause
**
**  **jma
**
***********************************/

void
ArxRleUtils::debugPause(LPCTSTR msg)
{
    TCHAR str[256];

    if (msg)
        acedGetString(0, msg, str);
    else
        acedGetString(0, _T("\nPAUSE: Press <RETURN> to continue >>> "), str);
}

/****************************************************************************
**
**  ArxRleUtils::getFileName
**      use AutoCAD's acedGetFileD() to get a file name from the user.  Support
**  drawing preview for AutoCAD DWG files, but looks like Win32 Explorer dialog
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleUtils::getFileName(bool isForWrite, LPCTSTR prompt,
                    LPCTSTR def, LPCTSTR ext, CString& fname,
                    bool defIsDirectory, bool allowArbitraryExt)
{
    resbuf *rb;
    int flags;
    short result;

    flags = 2;          // disable the silly "type it" button
    if (isForWrite)
        flags += 1;
    if (allowArbitraryExt)
        flags += 4;     // enable arbitrary extension
    if (defIsDirectory)
        flags += 16;    // interpret default path as directory, not filename

    rb = acutNewRb(RTSTR);
    rb->resval.rstring = NULL;

    result = acedGetFileD(prompt, def, ext, flags, rb);

    if (result != RTNORM) {
        acutRelRb(rb);
        return Acad::eInvalidInput;
    }
    else {
        fname = rb->resval.rstring;
        acutRelRb(rb);
        return Acad::eOk;
    }
}

/****************************************************************************
**
**  ArxRleUtils::getFileNameForRead
**      wrapper function for opening for read
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleUtils::getFileNameForRead(LPCTSTR prompt, LPCTSTR def, LPCTSTR ext,
                        CString& fname, bool defIsDirectory, bool allowArbitraryExt)
{
    return getFileName(false, prompt, def, ext, fname, defIsDirectory, allowArbitraryExt);
}

/****************************************************************************
**
**  ArxRleUtils::getFileNameForWrite
**      wrapper function for opening for read
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleUtils::getFileNameForWrite(LPCTSTR prompt, LPCTSTR def, LPCTSTR ext,
                        CString& fname, bool defIsDirectory, bool allowArbitraryExt)
{
    return getFileName(true, prompt, def, ext, fname, defIsDirectory, allowArbitraryExt);
}

/****************************************************************************
**
**  ArxRleUtils::yesNoPrompt
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUtils::yesNoPrompt(LPCTSTR msg, bool& answer)
{
    ArxRleKeywordArray kwords(ArxRleApp::getApp()->dllInstance());
    kwords.append(_T("Yes"), _T("Yes"));
    kwords.append(_T("No"),  _T("No"));

    CString optionsStr, kwordStr;
    kwords.makeOptionsList(optionsStr);
    kwords.makeKeywordList(kwordStr);

        // Concatenate original message with options list (in sqr braces)
        // Also prevent any extra white space chars between msg & [op1/op2]
        //    <msg - w/o xtra trailing white space> + <space> + [<options list>]
        //
        // Example: msg = "Do it?" or "Do it? "
        // Prompt String: "Do it? [Yes/No]" and NOT "Do it?  [Yes/No]"
        //
        // Final Prompt from ArxRleUiPrKeyWord::getKeyWord():
        //      "\nDo it? [Yes/No]: "

    CString msgSansTrlSpc, promptStr;
    msgSansTrlSpc = msg;
    msgSansTrlSpc.TrimRight();
    promptStr.Format(_T("%s %s"), msgSansTrlSpc, optionsStr);

    ArxRleUiPrKeyWord prmpt(promptStr, kwordStr);
    if (prmpt.go() == ArxRleUiPrBase::kOk) {
        int keywordIndex;
        if (kwords.find(prmpt.keyWordPicked(), keywordIndex) == Adesk::kFalse) {
            return ArxRleUiPrBase::kCancel;
        }
        if (keywordIndex == 0)      // Yes
            answer = true;
        else                        // No
            answer = false;
        return ArxRleUiPrBase::kOk;
    }
    else
        return ArxRleUiPrBase::kCancel;
}

/****************************************************************************
**
**  ArxRleUtils::yesNoPromptDef
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUtils::yesNoPromptDef(LPCTSTR msg, bool& answer, bool def)
{
    LPCTSTR defStr;

    if (def == true)
        defStr = _T("Y");
    else
        defStr = _T("N");

    ArxRleKeywordArray kwords(ArxRleApp::getApp()->dllInstance());
    kwords.append(_T("Yes"), _T("Yes"));
    kwords.append(_T("No"),  _T("No"));

    CString optionsStr, kwordStr;
    kwords.makeOptionsList(optionsStr);
    kwords.makeKeywordList(kwordStr);

        // Concatenate original message with options list (in sqr braces)
        // Also prevent any extra white space chars between msg & [op1/op2], but
        // add a trailing space to separate the [op1/op2] and default string "<Y>:"
        //    <msg - w/o xtra trailing white space> + <space> + [<options list>] + <space>
        //
        // Example: msg = "Do it?" or "Do it? "
        //          def = TRUE
        // Prompt string: "Do it? [Yes/No]" and NOT "Do it?  [Yes/No]"
        //
        // Final Prompt from ArxRleUiPrKeyWordDef::getKeyWord():
        //      "\nDo it? [Yes/No] <Y>: "

    CString msgSansTrlSpc, promptStr;
    msgSansTrlSpc = msg;
    msgSansTrlSpc.TrimRight();
    promptStr.Format(_T("%s %s "), msgSansTrlSpc, optionsStr);

    ArxRleUiPrKeyWordDef prmpt(promptStr, kwordStr, defStr);
    if (prmpt.go() == ArxRleUiPrBase::kOk) {
        int keywordIndex;
        if (kwords.find(prmpt.keyWordPicked(), keywordIndex) == Adesk::kFalse) {
            return ArxRleUiPrBase::kCancel;
        }
        if (keywordIndex == 0)      // Yes
            answer = true;
        else                        // No
            answer = false;
        return ArxRleUiPrBase::kOk;
    }
    else
        return ArxRleUiPrBase::kCancel;
}

/****************************************************************************
**
**  ArxRleUtils::getNewSymbolName
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUtils::getNewSymbolName(LPCTSTR msg, AcRxClass* symType, CString& symName)
{
    ArxRleUiPrString prName(msg, false);
    while (1) {
        if (prName.go() == ArxRleUiPrBase::kCancel)
            return ArxRleUiPrBase::kCancel;

        if (acdbSNValid(prName.value(), 0) != RTNORM) {
            acutPrintf(_T("\n\"%s\" is not a valid symbol name."), prName.value());
            continue;
        }

        if (ArxRleUtils::symbolExists(symType, prName.value(), acdbHostApplicationServices()->workingDatabase()) == TRUE)
            acutPrintf(_T("\nSymbol \"%s\" already exists."), prName.value());
        else {
            symName = prName.value();
            return ArxRleUiPrBase::kOk;
        }
    }
}

/****************************************************************************
**
**  ArxRleUtils::getExistingSymbolName
**
**  **jma
**
*************************************/

ArxRleUiPrBase::Status
ArxRleUtils::getExistingSymbolName(LPCTSTR msg, AcRxClass* symType, CString& symName,
                            bool allowPipes)
{
    ArxRleUiPrString prName(msg, false);
    while (1) {
        if (prName.go() == ArxRleUiPrBase::kCancel)
            return ArxRleUiPrBase::kCancel;

        if (acdbSNValid(prName.value(), allowPipes) != RTNORM) {
            acutPrintf(_T("\n\"%s\" is not a valid symbol name."), prName.value());
            continue;
        }

        if (ArxRleUtils::symbolExists(symType, prName.value(), acdbHostApplicationServices()->workingDatabase()) == false)
            acutPrintf(_T("\nSymbol \"%s\" does not exist."), prName.value());
        else {
            symName = prName.value();
            return ArxRleUiPrBase::kOk;
        }
    }
}

/****************************************************************************
**
**  ArxRleUtils::getEntityOrObject
**
**  **jma
**
*************************************/

bool
ArxRleUtils::getEntityOrObject(AcDbObjectId& objId)
{
    ArxRleUiPrEntity prEnt(_T("Select an entity (or RETURN for Handle)"), NULL);
    prEnt.setAllowNone(true);

    ArxRleUiPrBase::Status stat = prEnt.go();
    if (stat == ArxRleUiPrBase::kNone) {
        ArxRleUiPrString prHandle(_T("Handle of database object"), false);
        if (prHandle.go() == ArxRleUiPrBase::kOk) {
            CString handleStr = prHandle.value();
            if (handleStr.IsEmpty())
                return false;

            if (ArxRleUtils::handleStrToObjId(acdbHostApplicationServices()->workingDatabase(), prHandle.value(), objId) != Acad::eOk) {
                acutPrintf(_T("\nERROR: Couldn't find that handle!"));
                return false;
            }

            return true;
        }

        return false;
    }
    else if (stat == ArxRleUiPrBase::kOk) {
        objId = prEnt.objectId();
        return true;
    }
    else {
        return false;
    }
}