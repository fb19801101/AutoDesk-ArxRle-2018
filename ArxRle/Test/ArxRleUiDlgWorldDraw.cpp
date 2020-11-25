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

#include "ArxRleUiDlgWorldDraw.h"
#include "ArxRle.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiDlgWorldDraw::ArxRleUiDlgWorldDraw
**
**  **jma
**
*************************************/

ArxRleUiDlgWorldDraw::ArxRleUiDlgWorldDraw(ArxRleGiWorldDraw& wd, CWnd* parent)
:	CAcUiDialog(ArxRleUiDlgWorldDraw::IDD, parent, ArxRleApp::getApp()->dllInstance()),
    m_wd(wd)
{
    //{{AFX_DATA_INIT(ArxRleUiDlgWorldDraw)
    m_cbDragging = FALSE;
    m_ebDeviation = 0.5;
    m_ebIsolines = 16;
    m_rgRegenType = 0;
    m_cbShowWorldDraw = ArxRleGiWorldDraw::m_showWorldDrawMsg;
    m_cbShowGeom = ArxRleGiWorldDraw::m_showGeomMsg;
    m_cbShowSubents = ArxRleGiWorldDraw::m_showSubentsMsg;
    m_cbShowDetail = ArxRleGiWorldDraw::m_showDetailsMsg;
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiDlgWorldDraw::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgWorldDraw::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgWorldDraw)
	DDX_Check(pDX, ARXRLE_WORLD_DRAW_CK_DRAGGING, m_cbDragging);
	DDX_Text(pDX, ARXRLE_WORLD_DRAW_EB_DEVIATION, m_ebDeviation);
	DDV_MinMaxDouble(pDX, m_ebDeviation, 0.1, 10.);
	DDX_Text(pDX, ARXRLE_WORLD_DRAW_EB_ISOLINES, m_ebIsolines);
	DDV_MinMaxInt(pDX, m_ebIsolines, 1, 50);
	DDX_Radio(pDX, ARXRLE_WORLD_DRAW_RB_STANDARD, m_rgRegenType);
	DDX_Check(pDX, ARXRLE_WORLD_DRAW_CK_SHOW_GEOM, m_cbShowGeom);
	DDX_Check(pDX, ARXRLE_WORLD_DRAW_CK_SHOW_PRAMS, m_cbShowDetail);
	DDX_Check(pDX, ARXRLE_WORLD_DRAW_CK_SHOW_SUBENT, m_cbShowSubents);
	DDX_Check(pDX, ARXRLE_WORLD_DRAW_CK_SHOW_WORLDRAW, m_cbShowWorldDraw);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgWorldDraw message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgWorldDraw, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxRleUiDlgWorldDraw)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgWorldDraw message handlers

/****************************************************************************
**
**  ArxRleUiDlgWorldDraw::regenType
**
**  **jma
**
*************************************/

AcGiRegenType
ArxRleUiDlgWorldDraw::regenType() const
{
    if (m_rgRegenType == 0)
        return kAcGiStandardDisplay;
    else if (m_rgRegenType == 1)
        return kAcGiHideOrShadeCommand;
    else if (m_rgRegenType == 2)
        return kAcGiShadedDisplay;
    else if (m_rgRegenType == 3)
        return kAcGiSaveWorldDrawForR12;
    else if (m_rgRegenType == 4)
        return kAcGiSaveWorldDrawForProxy;
    else {
        ASSERT(0);
        return kAcGiStandardDisplay;
    }
}

/****************************************************************************
**
**  ArxRleUiDlgWorldDraw::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgWorldDraw::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    
    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiDlgWorldDraw::OnOK
**
**  **jma
**
*************************************/

void
ArxRleUiDlgWorldDraw::OnOK() 
{
    CAcUiDialog::OnOK();

    m_wd.setIsDragging(!!m_cbDragging);
    m_wd.setDeviation(m_ebDeviation);
    m_wd.setIsolines(m_ebIsolines);
    m_wd.setRegenType(regenType());

        // set global statics that control messages
    ArxRleGiWorldDraw::m_showWorldDrawMsg = m_cbShowWorldDraw;
    ArxRleGiWorldDraw::m_showGeomMsg = m_cbShowGeom;
    ArxRleGiWorldDraw::m_showSubentsMsg = m_cbShowSubents;
    ArxRleGiWorldDraw::m_showDetailsMsg = m_cbShowDetail;
}
