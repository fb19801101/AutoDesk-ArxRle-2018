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

#ifndef ARXRLEUIDLGTESTCURVE_H
#define ARXRLEUIDLGTESTCURVE_H

#include "Resource.h"

/****************************************************************************
**
**	CLASS ArxRleUiDlgTestCurve:
**
**	**jma
**
*************************************/

class ArxRleUiDlgTestCurve : public CAcUiDialog {

public:
                ArxRleUiDlgTestCurve(CWnd* pParent);

    //{{AFX_DATA(ArxRleUiDlgTestCurve)
    enum { IDD = ARXRLE_DLG_TESTCURVES };
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgTestCurve)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgTestCurve)
    afx_msg void    testGetPlane();
    afx_msg void    testGetStartParamEndParam();
    afx_msg void    testGetStartPtEndPt();
    afx_msg void    testGetPtAtParam();
    afx_msg void    testGetParamAtPt();
    afx_msg void    testGetDistAtParam();
    afx_msg void    testGetParamAtDist();
    afx_msg void    testGetDistAtPt();
    afx_msg void    testGetPtAtDist();
    afx_msg void    testGetDerivs();
    afx_msg void    testGetDerivs2();
    afx_msg void    testGetClosestPtTo();
    afx_msg void    testGetClosestPtTo2();
    afx_msg void    testGetOrthoProjectedCurve();
    afx_msg void    testGetProjectedCurve();
    afx_msg void    testGetOffsetCurves();
    afx_msg void    testGetSpline();
    afx_msg void    testGetSplitCurves();
    afx_msg void    testGetSplitCurves2();
    afx_msg void    testExtend();
    afx_msg void    testExtend2();
    afx_msg void    testGetArea();
    afx_msg void    testIsClosedPeriodicPlanar();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // helper functions
    AcDbCurve*  selectCurve();
    void        printInfo(LPCTSTR tagStr, LPCTSTR valStr);
    void        makeRay(const AcGePoint3d& origin, const AcGeVector3d& dir, int color);
    void        makePt(const AcGePoint3d& pt, int color);
    BOOL        getCurvePts(AcGePoint3dArray& pts);
    BOOL        getCurveParams(AcGeDoubleArray& params);
    BOOL        getCurveParam(double& param);
    void        printParamInterval(AcDbCurve* curve);
};

#endif    // ARXRLEUIDLGTESTCURVE_H
