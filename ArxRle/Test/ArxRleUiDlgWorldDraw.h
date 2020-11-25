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

#ifndef ARXRLEUIDLGWORLDDRAW_H
#define ARXRLEUIDLGWORLDDRAW_H

#include "Resource.h"
#include "ArxRleWorldDraw.h"

/****************************************************************************
**
**	CLASS WorldDrawDbox:
**
**	**jma
**
*************************************/

class ArxRleUiDlgWorldDraw : public CAcUiDialog {

public:
    ArxRleUiDlgWorldDraw(ArxRleGiWorldDraw& wd, CWnd* pParent);

    AcGiRegenType    regenType() const;

    //{{AFX_DATA(ArxRleUiDlgWorldDraw)
    enum { IDD = ARXRLE_DLG_WORLD_DRAW };
    BOOL    m_cbDragging;
    double	m_ebDeviation;
    int     m_ebIsolines;
    int     m_rgRegenType;
    BOOL    m_cbShowGeom;
    BOOL    m_cbShowDetail;
    BOOL    m_cbShowSubents;
    BOOL    m_cbShowWorldDraw;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgWorldDraw)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgWorldDraw)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ArxRleGiWorldDraw&    m_wd;
};

#endif    // ARXRLEUIDLGWORLDDRAW_H
