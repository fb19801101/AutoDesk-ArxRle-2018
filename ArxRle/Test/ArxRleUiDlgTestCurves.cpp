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

#include "ArxRleUiDlgTestCurves.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleSelSet.h"
#include "AcadUtils/ArxRleUtilsGe.h"
#include "AcadUtils/AcadStr.h"
#include "AcadUtils/ArxRleSdSysVar.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::ArxRleUiDlgTestCurve
**
**  **jma
**
*************************************/

ArxRleUiDlgTestCurve::ArxRleUiDlgTestCurve(CWnd* parent)
:	CAcUiDialog(ArxRleUiDlgTestCurve::IDD, parent, ArxRleApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxRleUiDlgTestCurve)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgTestCurve)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgTestCurve message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgTestCurve, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxRleUiDlgTestCurve)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_GETPLANE, testGetPlane)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_STARTPARAM, testGetStartParamEndParam)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_STARTPT, testGetStartPtEndPt)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_PTATPARAM, testGetPtAtParam)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_PARAMATPT, testGetParamAtPt)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_DISTATPARAM, testGetDistAtParam)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_PARAMATDIST, testGetParamAtDist)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_DISTATPT, testGetDistAtPt)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_PTATDIST, testGetPtAtDist)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_DERIV, testGetDerivs)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_DERIV2, testGetDerivs2)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_CLOSESTPTTO, testGetClosestPtTo)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_CLOSESTPTTO2, testGetClosestPtTo2)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_ORTHOPROJECTED, testGetOrthoProjectedCurve)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_PROJECTED, testGetProjectedCurve)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_OFFSETCURVES, testGetOffsetCurves)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_SPLINE, testGetSpline)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_SPLITCURVES, testGetSplitCurves)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_SPLITCURVES2, testGetSplitCurves2)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_EXTEND, testExtend)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_EXTEND2, testExtend2)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_AREA, testGetArea)
	ON_BN_CLICKED(ARXRLE_TESTCURVES_BN_CLOSED, testIsClosedPeriodicPlanar)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgTestCurve message handlers

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::selectCurve
**
**  **jma
**
*************************************/

AcDbCurve*
ArxRleUiDlgTestCurve::selectCurve()
{
    AcDbCurve* curve;

    ArxRleUiPrEntity prEnt(_T("Select AcDbCurve"), nullptr);
	prEnt.addAllowedClass(AcDbCurve::desc());
    prEnt.setAllowNone(true);

    if (prEnt.go() != ArxRleUiPrBase::kOk)
        return nullptr;
    else {
        Acad::ErrorStatus es = acdbOpenObject(curve, prEnt.objectId(), AcDb::kForRead);
        if (es == Acad::eOk)
            return curve;
        else
            return nullptr;
    }
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::printInfo
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::printInfo(LPCTSTR tagStr, LPCTSTR valStr)
{
    acutPrintf(_T("\n%-20s : %s"), tagStr, valStr);
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::makeRay
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::makeRay(const AcGePoint3d& origin, const AcGeVector3d& dir, int color)
{
    if (dir.isZeroLength()) {
        acutPrintf(_T("\nSkipping zero length vector (color = %d)"), color);
        return;
    }

    AcDbRay* ray = new AcDbRay;
    ray->setBasePoint(origin);
    ray->setUnitDir(dir.normal());
    ray->setColorIndex(color);
    ArxRleUtils::addToCurrentSpaceAndClose(ray);
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::makePt
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::makePt(const AcGePoint3d& pt, int color)
{
	int mode = 0;
	getSysVar(_T("pdmode"), mode);
	if (mode == 0)
		setSysVar(_T("pdmode"), 99);

    AcDbPoint* ptEnt = new AcDbPoint(pt);
    ptEnt->setColorIndex(color);
    ArxRleUtils::addToCurrentSpaceAndClose(ptEnt);
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetPlane
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetPlane()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getPlane(AcGePlane& plane, AcDb::Planarity& type)...\n"));

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        AcGePlane plane;
        AcDb::Planarity type;
        Acad::ErrorStatus es = curve->getPlane(plane, type);
        if (es == Acad::eOk) {
            CString planeTypeStr;
            if (type == AcDb::kNonPlanar)
                planeTypeStr = _T("Non Planar");
            else if (type == AcDb::kPlanar)
                planeTypeStr = _T("Planar");
            else if (type == AcDb::kLinear)
                planeTypeStr = _T("Linear");
            else {
                ASSERT(0);
                planeTypeStr = _T("*UNKNOWN*");
            }

            printInfo(_T("PLANE TYPE"), planeTypeStr);

            AcGePoint3d origin;
            AcGeVector3d uVec, vVec;
            plane.get(origin, uVec, vVec);

            CString str;
            printInfo(_T("ORIGIN"), ArxRleUtils::ptToStr(origin, str));
            printInfo(_T("U VEC"), ArxRleUtils::vectorToStr(uVec, str));
            printInfo(_T("V VEC"), ArxRleUtils::vectorToStr(vVec, str));

            makeRay(origin, uVec, 1);
            makeRay(origin, vVec, 2);
        }
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetStartParamEndParam
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetStartParamEndParam()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getStartParam(double& param)..."));
    acutPrintf(_T("\nTesting getEndParam(double& param)..."));

    Acad::ErrorStatus es;
    CString str;
    double param;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        es = curve->getStartParam(param);
        if (es == Acad::eOk) {
            printInfo(_T("START PARAM (DOUBLE)"), ArxRleUtils::doubleToStr(param, str));
            printInfo(_T("START PARAM (ANGLE)"), ArxRleUtils::angleToStr(param, str));
        }
        else
            printInfo(_T("START PARAM"), ArxRleUtils::rxErrorStr(es));

        es = curve->getEndParam(param);
        if (es == Acad::eOk) {
            printInfo(_T("END PARAM (DOUBLE)"), ArxRleUtils::doubleToStr(param, str));
            printInfo(_T("END PARAM (ANGLE)"), ArxRleUtils::angleToStr(param, str));
        }
        else
            printInfo(_T("END PARAM"), ArxRleUtils::rxErrorStr(es));

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetStartPtEndPt
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetStartPtEndPt()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getStartPoint(AcGePoint3d& startPt)..."));
    acutPrintf(_T("\nTesting getEndPoint(AcGePoint3d& endPt)..."));

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        CString str;
        Acad::ErrorStatus es1, es2;
        AcGePoint3d startPt, endPt;
        es1 = curve->getStartPoint(startPt);
        if (es1 == Acad::eOk)
            printInfo(_T("START PT"), ArxRleUtils::ptToStr(startPt, str));
        else
            printInfo(_T("START PT"), ArxRleUtils::rxErrorStr(es1));

        es2 = curve->getEndPoint(endPt);
        if (es2 == Acad::eOk)
            printInfo(_T("END PT"), ArxRleUtils::ptToStr(endPt, str));
        else
            printInfo(_T("END PT"), ArxRleUtils::rxErrorStr(es2));

            // if both points are the same, put out only one green point
        if ((es1 == Acad::eOk) && (es2 == Acad::eOk) && (startPt == endPt))
            makePt(startPt, 3);
        else {
                // else put out a red point for start and a yellow for end
            if (es1 == Acad::eOk)
                makePt(startPt, 1);
            if (es2 == Acad::eOk)
                makePt(endPt, 2);
        }
        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetPtAtParam
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetPtAtParam()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getPointAtParam(double param, AcGePoint3d& point)..."));

    double param;
    Acad::ErrorStatus es;
    AcGePoint3d pt;
    CString str;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        printParamInterval(curve);

        if (!getCurveParam(param)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getPointAtParam(param, pt);
        if (es == Acad::eOk) {
            printInfo(_T("PT"), ArxRleUtils::ptToStr(pt, str));
            makePt(pt, 4);
        }
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetParamAtPt
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetParamAtPt()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getParamAtPoint(const AcGePoint3d& point, double& param)..."));

    ArxRleUiPrPoint prPt(_T("Point on curve"), NULL);

    CString str;
    Acad::ErrorStatus es;
    double param;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prPt.go() != ArxRleUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getParamAtPoint(ArxRleUtils::ucsToWcs(prPt.value()), param);
        if (es == Acad::eOk) {
            printInfo(_T("PARAM (DOUBLE)"), ArxRleUtils::doubleToStr(param, str));
            printInfo(_T("PARAM (ANGLE)"), ArxRleUtils::angleToStr(param, str));
        }
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetDistAtParam
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetDistAtParam()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getDistAtParam(double param, double& dist)..."));

    double param;
    double dist;
    Acad::ErrorStatus es;
    CString str;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        printParamInterval(curve);

        if (!getCurveParam(param)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getDistAtParam(param, dist);
        if (es == Acad::eOk)
            printInfo(_T("DIST"), ArxRleUtils::doubleToStr(dist, str));
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetParamAtDist
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetParamAtDist()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getParamAtDist(double dist, double& param)..."));

    ArxRleUiPrDist prDist(_T("Distance"), NULL, ArxRleUiPrDist::kAny);
    CString str;
    Acad::ErrorStatus es;
    double param;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prDist.go() != ArxRleUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getParamAtDist(prDist.value(), param);
        if (es == Acad::eOk) {
            printInfo(_T("PARAM (DOUBLE)"), ArxRleUtils::doubleToStr(param, str));
            printInfo(_T("PARAM (ANGLE)"), ArxRleUtils::angleToStr(param, str));
        }
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetDistAtPt
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetDistAtPt()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getDistAtPoint(const AcGePoint3d& point, double& dist)..."));

    ArxRleUiPrPoint prPt(_T("Point on curve"), NULL);

    CString str;
    Acad::ErrorStatus es;
    double dist;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prPt.go() != ArxRleUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getDistAtPoint(ArxRleUtils::ucsToWcs(prPt.value()), dist);
        if (es == Acad::eOk)
            printInfo(_T("DIST"), ArxRleUtils::doubleToStr(dist, str));
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetPtAtDist
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetPtAtDist()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getPointAtDist(double dist, AcGePoint3d& point)..."));

    ArxRleUiPrDist prDist(_T("Distance"), NULL, ArxRleUiPrDist::kAny);
    CString str;
    Acad::ErrorStatus es;
    AcGePoint3d pt;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prDist.go() != ArxRleUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getPointAtDist(prDist.value(), pt);
        if (es == Acad::eOk) {
            printInfo(_T("PT"), ArxRleUtils::ptToStr(pt, str));
            makePt(pt, 4);
        }
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetDerivs
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetDerivs()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getFirstDeriv(double param, AcGeVector3d& firstDeriv)..."));
    acutPrintf(_T("\nTesting getSecondDeriv(double param, AcGeVector3d& secondDeriv)..."));

    CString str;
    Acad::ErrorStatus es;
    AcGeVector3d deriv1, deriv2;
    double param;
    AcGePoint3d pt;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        printParamInterval(curve);

        if (!getCurveParam(param)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        if (curve->getPointAtParam(param, pt) != Acad::eOk) {
            acutPrintf(_T("\nERROR: getPointAtParam() failed, using origin..."));
            pt = AcGePoint3d::kOrigin;
        }

        es = curve->getFirstDeriv(param, deriv1);
        if (es == Acad::eOk) {
            printInfo(_T("FIRST DERIV"), ArxRleUtils::vectorToStr(deriv1, str));
            makeRay(pt, deriv1, 1);
        }
        else
            printInfo(_T("FIRST DERIV"), ArxRleUtils::rxErrorStr(es));

        es = curve->getSecondDeriv(param, deriv2);
        if (es == Acad::eOk) {
            printInfo(_T("SECOND DERIV"), ArxRleUtils::vectorToStr(deriv2, str));
            makeRay(pt, deriv2, 2);
        }
        else
            printInfo(_T("SECOND DERIV"), ArxRleUtils::rxErrorStr(es));

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetDerivs2
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetDerivs2()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getFirstDeriv(const AcGePoint3d& point, AcGeVector3d& firstDeriv)..."));
    acutPrintf(_T("\nTesting getSecondDeriv(const AcGePoint3d& point, AcGeVector3d& secondDeriv)..."));

    ArxRleUiPrPoint prPt(_T("Point on curve"), NULL);

    CString str;
    Acad::ErrorStatus es;
    AcGeVector3d deriv1, deriv2;
    AcGePoint3d wcsPt;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prPt.go() != ArxRleUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        wcsPt = ArxRleUtils::ucsToWcs(prPt.value());

        es = curve->getFirstDeriv(wcsPt, deriv1);
        if (es == Acad::eOk) {
            printInfo(_T("FIRST DERIV"), ArxRleUtils::vectorToStr(deriv1, str));
            makeRay(wcsPt, deriv1, 1);
        }
        else
            printInfo(_T("FIRST DERIV"), ArxRleUtils::rxErrorStr(es));

        es = curve->getSecondDeriv(wcsPt, deriv2);
        if (es == Acad::eOk) {
            printInfo(_T("SECOND DERIV"), ArxRleUtils::vectorToStr(deriv2, str));
            makeRay(wcsPt, deriv2, 2);
        }
        else
            printInfo(_T("SECOND DERIV"), ArxRleUtils::rxErrorStr(es));

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetClosestPtTo
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetClosestPtTo()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getClosestPointTo(const AcGePoint3d& givenPoint, AcGePoint3d& pointOnCurve, Adesk::Boolean extend = Adesk::kFalse)..."));

    ArxRleUiPrPoint prPt(_T("Point"), NULL);

    CString str;
    Acad::ErrorStatus es;
    AcGePoint3d pt;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prPt.go() != ArxRleUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getClosestPointTo(ArxRleUtils::ucsToWcs(prPt.value()), pt);
        if (es == Acad::eOk) {
            printInfo(_T("PT"), ArxRleUtils::ptToStr(pt, str));
            makePt(pt, 4);
        }
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetClosestPtTo2
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetClosestPtTo2()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getClosestPointTo(const AcGePoint3d&  givenPoint,"));
    acutPrintf(_T("\n                const AcGeVector3d& normal, AcGePoint3d& pointOnCurve,"));
    acutPrintf(_T("\n                Adesk::Boolean extend)..."));

    ArxRleUiPrPoint prPt(_T("Point"), NULL);
    AcGePoint3d tmpPt;
    getSysVar(_T("viewdir"), tmpPt);
    AcGeVector3d viewdir = ArxRleUtils::ucsToWcs(tmpPt.asVector());

    CString str;
    Acad::ErrorStatus es;
    AcGePoint3d pt;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prPt.go() != ArxRleUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getClosestPointTo(ArxRleUtils::ucsToWcs(prPt.value()), viewdir, pt);
        if (es == Acad::eOk) {
            printInfo(_T("PT"), ArxRleUtils::ptToStr(pt, str));
            makePt(pt, 4);
        }
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetOrthoProjectedCurve
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetOrthoProjectedCurve()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getOrthoProjectedCurve()..."));
    acutPrintf(_T("\nProjecting onto current UCS plane..."));

    Acad::ErrorStatus es;

    AcGePlane projPlane = ArxRleUtils::getUcsPlane(acdbHostApplicationServices()->workingDatabase());

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}
    
        AcDbCurve* projCurve = NULL;
        es = curve->getOrthoProjectedCurve(projPlane, projCurve);
        if (es == Acad::eOk) {
            projCurve->setColorIndex(1);
            ArxRleUtils::addToCurrentSpaceAndClose(projCurve);
        }
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetProjectedCurve
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetProjectedCurve()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getProjectedCurve()..."));
    acutPrintf(_T("\nProjecting onto current UCS plane with VIEWDIR as projection direction..."));

    Acad::ErrorStatus es;

    AcGePlane projPlane = ArxRleUtils::getUcsPlane(acdbHostApplicationServices()->workingDatabase());
    AcGePoint3d tmpPt;
    getSysVar(_T("viewdir"), tmpPt);
    AcGeVector3d viewdir = ArxRleUtils::ucsToWcs(tmpPt.asVector());

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}
    
        AcDbCurve* projCurve = NULL;
        es = curve->getProjectedCurve(projPlane, viewdir, projCurve);
        if (es == Acad::eOk) {
            projCurve->setColorIndex(1);
            ArxRleUtils::addToCurrentSpaceAndClose(projCurve);
        }
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetOffsetCurves
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetOffsetCurves()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getOffsetCurves(double offsetDist, AcDbVoidPtrArray& offsetCurves)..."));

    ArxRleUiPrDist prDist(_T("Offset Distance"), NULL, ArxRleUiPrDist::kAny);
    CString str;
    Acad::ErrorStatus es;
    AcDbVoidPtrArray newEnts;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prDist.go() != ArxRleUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        newEnts.setLogicalLength(0);    // reset for each loop
        es = curve->getOffsetCurves(prDist.value(), newEnts);
        if (es == Acad::eOk) {
            for (void *pVoid : newEnts) {
                AcDbEntity* ent = static_cast<AcDbEntity*>(pVoid);
                if (ent) {
                    ent->setColorIndex(1);
                    ArxRleUtils::addToCurrentSpaceAndClose(ent);
                }
            }
        }
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetSpline
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetSpline()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getSpline(AcDbSpline*& spline)..."));

    Acad::ErrorStatus es;
    AcDbSpline* spline;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        es = curve->getSpline(spline);
        if (es == Acad::eOk) {
            spline->setColorIndex(1);
            ArxRleUtils::addToCurrentSpaceAndClose(spline);
        }
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetSplitCurves
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetSplitCurves()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getSplitCurves(const AcGeDoubleArray& params, AcDbVoidPtrArray& curveSegments)..."));

    Acad::ErrorStatus es;
    AcDbVoidPtrArray curveSegs;
    AcDbCurve* tmpCurve;
    AcGeDoubleArray params;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        printParamInterval(curve);

        params.setLogicalLength(0);    // reset for each loop
        if (!getCurveParams(params)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getSplitCurves(params, curveSegs);
        if (es == Acad::eOk) {
                // walk through resultant curves and add them to the database
            int color = 1;
            for (void *pVoid : curveSegs) {
                tmpCurve = static_cast<AcDbCurve*>(pVoid);
                if (tmpCurve) {
                    tmpCurve->setColorIndex(color++);
                    ArxRleUtils::addToCurrentSpaceAndClose(tmpCurve);
                }
            }
            curveSegs.setLogicalLength(0);
        }
        else {
            ArxRleUtils::rxErrorMsg(es);

                // even in error condition, some curves may have been allocated
            for (void *pVoid : curveSegs) {
                tmpCurve = static_cast<AcDbCurve*>(pVoid);
                delete tmpCurve;
            }
            curveSegs.setLogicalLength(0);
        }

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetSplitCurves2
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetSplitCurves2()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getSplitCurves(const AcGePoint3dArray& points, AcDbVoidPtrArray& curveSegments)..."));

    Acad::ErrorStatus es;
    AcDbVoidPtrArray curveSegs;
    AcDbCurve* tmpCurve;
    AcGePoint3dArray pts;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        pts.setLogicalLength(0);    // reset for each loop
        if (!getCurvePts(pts)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getSplitCurves(pts, curveSegs);
        if (es == Acad::eOk) {
                // walk through resultant curves and add them to the database
            int color = 1;
            for (void *pVoid : curveSegs) {
                tmpCurve = static_cast<AcDbCurve*>(pVoid);
                if (tmpCurve) {
                    tmpCurve->setColorIndex(color++);
                    ArxRleUtils::addToCurrentSpaceAndClose(tmpCurve);
                }
            }
            curveSegs.setLogicalLength(0);
        }
        else {
            ArxRleUtils::rxErrorMsg(es);

                // even in error condition, some curves may have been allocated
            for (void *pVoid : curveSegs) {
                tmpCurve = static_cast<AcDbCurve*>(pVoid);
                delete tmpCurve;
            }
            curveSegs.setLogicalLength(0);
        }

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testExtend
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testExtend()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting extend(double toNewParam)..."));

    Acad::ErrorStatus es;
    double param;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        printParamInterval(curve);

        if (!getCurveParam(param)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        if (curve->upgradeOpen() == Acad::eOk) {
            es = curve->extend(param);
            if (es != Acad::eOk)
                ArxRleUtils::rxErrorMsg(es);
        }
        else
            acutPrintf(_T("\nERROR: couldn't open curve for write!"));

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testExtend2
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testExtend2()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting extend(Adesk::Boolean fromStart, const AcGePoint3d& toPt)..."));

    ArxRleUiPrPoint prPt(_T("Point to extend to"), NULL);

    Acad::ErrorStatus es;
    bool fromStart;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (ArxRleUtils::yesNoPromptDef(_T("Extend from start "), fromStart, true) == ArxRleUiPrBase::kCancel) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        if (prPt.go() != ArxRleUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        if (curve->upgradeOpen() == Acad::eOk) {
            es = curve->extend(fromStart, ArxRleUtils::ucsToWcs(prPt.value()));
            if (es != Acad::eOk)
                ArxRleUtils::rxErrorMsg(es);
        }
        else
            acutPrintf(_T("\nERROR: couldn't open curve for write!"));

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testGetArea
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testGetArea()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getArea()..."));

    Acad::ErrorStatus es;
    CString str;
    double area;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        es = curve->getArea(area);
        if (es == Acad::eOk)
            acutPrintf(_T("\nAREA: %s"), ArxRleUtils::doubleToStr(area, str));
        else
            ArxRleUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::testIsClosedPeriodicPlanar
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::testIsClosedPeriodicPlanar()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting isClosed(), isPeriodic(), isPlanar()..."));

    AcDbCurve* curve = selectCurve();
    if (curve) {
        CString str;
        acutPrintf(_T("\nIS CLOSED:   %s"), ArxRleUtils::booleanToStr(curve->isClosed(), str));
        acutPrintf(_T("\nIS PERIODIC: %s"), ArxRleUtils::booleanToStr(curve->isPeriodic(), str));
        acutPrintf(_T("\nIS PLANAR:   %s"), ArxRleUtils::booleanToStr(curve->isPlanar(), str));

        curve->close();
    }

	CompleteEditorCommand();
}


/****************************************************************************
**
**  ArxRleUiDlgTestCurve::getCurvePts
**      this function purposely allows no points to be entered just to thest
**  what the API will do if it gets no points
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgTestCurve::getCurvePts(AcGePoint3dArray& pts)
{
    ArxRleUiPrPoint prPt(_T("Point on curve"), NULL);
    prPt.setAllowNone(TRUE);
    ArxRleUiPrBase::Status stat;

    while (1) {
        stat = prPt.go();
        if (stat == ArxRleUiPrBase::kOk)
            pts.append(ArxRleUtils::ucsToWcs(prPt.value()));
        else if (stat == ArxRleUiPrBase::kNone)    // done inputting points
            return TRUE;
        else
            return FALSE;
    }
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::getCurveParams
**      this function purposely allows no params to be entered just to thest
**  what the API will do if it gets no params
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgTestCurve::getCurveParams(AcGeDoubleArray& params)
{
    bool asAngles;
    if (ArxRleUtils::yesNoPromptDef(_T("Input params as angles "), asAngles, true) == ArxRleUiPrBase::kCancel)
        return FALSE;

    ArxRleUiPrBase::Status stat;

    if (asAngles) {
        ArxRleUiPrAngle prParamAng(_T("Params of curve"), NULL, ArxRleUiPrAngle::kAny);
        prParamAng.setAllowNone(true);

        while (1) {
            stat = prParamAng.go();
            if (stat == ArxRleUiPrBase::kOk)
                params.append(prParamAng.value());
            else if (stat == ArxRleUiPrBase::kNone)    // done inputting params
                return TRUE;
            else
                return FALSE;
        }
    }
    else {
        ArxRleUiPrDist prParam(_T("Params of curve"), NULL, ArxRleUiPrDist::kAny);
        prParam.setAllowNone(true);

        while (1) {
            stat = prParam.go();
            if (stat == ArxRleUiPrBase::kOk)
                params.append(prParam.value());
            else if (stat == ArxRleUiPrBase::kNone)    // done inputting params
                return TRUE;
            else
                return FALSE;
        }
    }
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::getCurveParam
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgTestCurve::getCurveParam(double& param)
{
    bool asAngles;
    if (ArxRleUtils::yesNoPromptDef(_T("Input param as angle "), asAngles, true) == ArxRleUiPrBase::kCancel)
        return FALSE;

    if (asAngles) {
        ArxRleUiPrAngle prParamAng(_T("Param of curve"), NULL, ArxRleUiPrAngle::kAny);
        if (prParamAng.go() == ArxRleUiPrBase::kOk) {
            param = prParamAng.value();
            return TRUE;
        }
    }
    else {
        ArxRleUiPrDist prParam(_T("Param of curve"), NULL, ArxRleUiPrDist::kAny);
        if (prParam.go() == ArxRleUiPrBase::kOk) {
            param = prParam.value();
            return TRUE;
        }
    }
    return FALSE;
}

/****************************************************************************
**
**  ArxRleUiDlgTestCurve::printParamInterval
**
**  **jma
**
*************************************/

void
ArxRleUiDlgTestCurve::printParamInterval(AcDbCurve* curve)
{
    double startParam, endParam;
    CString str, str2;

    if ((curve->getStartParam(startParam) == Acad::eOk) && (curve->getEndParam(endParam) == Acad::eOk)) {
        acutPrintf(_T("\nParam Interval: (%s --> %s) (DOUBLE)"),
                ArxRleUtils::doubleToStr(startParam, str),
                ArxRleUtils::doubleToStr(endParam, str2));
        acutPrintf(_T("\nParam Interval: (%s --> %s) (ANGLE)"),
                ArxRleUtils::angleToStr(startParam, str),
                ArxRleUtils::angleToStr(endParam, str2));
    }
    else
        acutPrintf(_T("\nParam Interval: UNSPECIFIED"));
}


