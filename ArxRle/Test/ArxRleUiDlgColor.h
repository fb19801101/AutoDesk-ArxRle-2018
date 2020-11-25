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

#ifndef ARXRLEUIDLGCOLOR_H
#define ARXRLEUIDLGCOLOR_H

#include "Resource.h"

#define WM_COLOR_CHANGED    (WM_USER + 100)    // custom message


/****************************************************************************
**
**	CLASS ArxRleUiDlgColor:
**		just used to test color, not to get/set from an entity
**
**	**jma
**
*************************************/

class ArxRleUiDlgColor : public CAcUiDialog {

public:
                ArxRleUiDlgColor(CWnd* pParent);
    virtual		~ArxRleUiDlgColor();

    //{{AFX_DATA(AecUiPpColor)
    enum { IDD = ARXRLE_DLG_COLOR };
    CStatic    m_colorSwatch;
	int        m_currentIndex;
    //}}AFX_DATA

    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(AecUiPpColor)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgColor)
    afx_msg void OnByblock();
    afx_msg void OnBylayer();
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // member data
    CRect    m_colorTiles[256];         // Array of rects for each color tile in the palette
    CRect    m_fullPaletteRectTop;      // Windows rectangle of full palette region top
    CRect    m_fullPaletteRectBottom;	// Windows rectangle of full palette region bottom
    CRect    m_standardColorsRect;      // Windows rectangle of standard colors region
    CRect    m_grayColorsRect;          // Windows rectangle of gray colors region
    CRect    m_currentColorRect;        // Windows rectangle of current color

        // helper functions
    void    display();
    BOOL    pickedColorSwatch(CPoint& point);
    void    initColorTileRects();
    void    calculateRectSize(UINT controlId, CRect& rect, double gridX, double gridY,
                        long& sizeX, long& sizeY, long& bookEndGapX, long& bookEndGapY);
    BOOL    setToAcadColorPalette(CDC* dc);
    void    drawCurrentColorSwatch(CDC* dc);
};


#endif    // ARXRLEUIDLGCOLOR_H
