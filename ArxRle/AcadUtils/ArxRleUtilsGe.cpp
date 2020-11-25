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

#include "ArxRleUtilsGe.h"



// predefined constants for common angles
const double ArxRleUtilsGe::kPi       = 3.14159265358979323846;
const double ArxRleUtilsGe::kHalfPi   = 3.14159265358979323846 / 2.0;
const double ArxRleUtilsGe::kTwoPi	  = 3.14159265358979323846 * 2.0;

const double ArxRleUtilsGe::kRad0     = 0.0;
const double ArxRleUtilsGe::kRad45    = 3.14159265358979323846 / 4.0;
const double ArxRleUtilsGe::kRad90    = 3.14159265358979323846 / 2.0;
const double ArxRleUtilsGe::kRad135   = (3.14159265358979323846 * 3.0) / 4.0;
const double ArxRleUtilsGe::kRad180   = 3.14159265358979323846;
const double ArxRleUtilsGe::kRad270   = 3.14159265358979323846 * 1.5;
const double ArxRleUtilsGe::kRad360   = 3.14159265358979323846 * 2.0;


/****************************************************************************
**
**  ArxRleUtilsGe::radiansToDegrees
**
**  **jma
**
*************************************/

double
ArxRleUtilsGe::radiansToDegrees(const double rads)
{
    return rads * (180.0 / kPi);
}

/****************************************************************************
**
**  ArxRleUtilsGe::degreesToRadians
**
**  **jma
**
*************************************/

double
ArxRleUtilsGe::degreesToRadians(const double degrees)
{
    return degrees * (kPi / 180.0);
}

/****************************************************************************
**
**  ArxRleUtilsGe::fuzzyEqual (DOUBLES)
**
**  **jma
**
*************************************/

bool
ArxRleUtilsGe::fuzzyEqual(double x1, double x2)
{
    return (fabs(x1 - x2) <= AcGeContext::gTol.equalPoint());
}

/****************************************************************************
**
**  ArxRleUtilsGe::midpoint
**
**  **jma
**
*************************************/

AcGePoint3d
ArxRleUtilsGe::midpoint(const AcGePoint3d& pt1, const AcGePoint3d& pt2)
{
    AcGePoint3d newPt;

    newPt.x =(pt1.x + pt2.x) / 2.0;
    newPt.y =(pt1.y + pt2.y) / 2.0;
    newPt.z =(pt1.z + pt2.z) / 2.0;

    return newPt;
}


