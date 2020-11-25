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

#include "ArxRleUiDlgColor.h"
#include "AcadUtils/AcadStr.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiDlgColor::ArxRleUiDlgColor
**
**  **jma
**
*************************************/

ArxRleUiDlgColor::ArxRleUiDlgColor(CWnd* parent)
:    CAcUiDialog(ArxRleUiDlgColor::IDD, parent, ArxRleApp::getApp()->dllInstance()),
    m_currentIndex(1)
{
    //{{AFX_DATA_INIT(ArxRleUiDlgColor)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiDlgColor::~ArxRleUiDlgColor
**
**  **jma
**
*************************************/

ArxRleUiDlgColor::~ArxRleUiDlgColor()
{
}

/****************************************************************************
**
**  ArxRleUiDlgColor::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgColor::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgColor)
    DDX_Control(pDX, ARXRLE_COLOR_PC_COLOR_SWATCH, m_colorSwatch);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgColor message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgColor, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxRleUiDlgColor)
	ON_BN_CLICKED(ARXRLE_COLOR_BN_BYBLOCK, OnByblock)
	ON_BN_CLICKED(ARXRLE_COLOR_BN_BYLAYER, OnBylayer)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgColor message handlers

/****************************************************************************
**
**  ArxRleUiDlgColor::OnByblock
**
**  **jma
**
*************************************/

void
ArxRleUiDlgColor::OnByblock() 
{
    m_currentIndex = 0;
    display();
}

/****************************************************************************
**
**  ArxRleUiDlgColor::OnBylayer
**
**  **jma
**
*************************************/

void
ArxRleUiDlgColor::OnBylayer() 
{
    m_currentIndex = 256;
    display();
}

/****************************************************************************
**
**  ArxRleUiDlgColor::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgColor::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();

    initColorTileRects();

    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiDlgColor::OnPaint
**
**  **jma
**
*************************************/

void
ArxRleUiDlgColor::OnPaint() 
{
    CPaintDC dc(this);                // device context for painting
    setToAcadColorPalette(&dc);       // make colors match AutoCAD's

        // draw all colors but BYLAYER and BYBLOCK
    for (int j=1; j<=255; j++) {
        dc.FillSolidRect(m_colorTiles[j], PALETTEINDEX(j));
        dc.DrawEdge(m_colorTiles[j], EDGE_SUNKEN, BF_RECT);
    }

    drawCurrentColorSwatch(&dc);    // draw the current color at the bottom

    CString str;
    SetDlgItemText(ARXRLE_COLOR_EB_COLOR, ArxRleUtils::colorToStr(m_currentIndex, str));
}

/****************************************************************************
**
**  ArxRleUiDlgColor::pickedColorSwatch
**      find out if they picked in one of the color swatches and
**  set the current index appropriately
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgColor::pickedColorSwatch(CPoint& point)
{
    if (m_standardColorsRect.PtInRect(point)) {
        for (int i=1;i<=9;i++) {
            if (m_colorTiles[i].PtInRect(point)) {
                m_currentIndex = i;
                return TRUE;
            }
        }
    }
    else if (m_grayColorsRect.PtInRect(point)) {
        for (int i=250;i<=255;i++) {
            if (m_colorTiles[i].PtInRect(point)) {
                m_currentIndex = i;
                return TRUE;
            }
        }
    }
    else if (m_fullPaletteRectTop.PtInRect(point)) {
        for (int i=10;i<250;i+=2) {
            if (m_colorTiles[i].PtInRect(point)) {
                m_currentIndex = i;
                return TRUE;
            }
        }
    }
    else if (m_fullPaletteRectBottom.PtInRect(point)) {
        for (int i=11;i<250;i+=2) {
            if (m_colorTiles[i].PtInRect(point)) {
                m_currentIndex = i;
                return TRUE;
            }
        }
    }
    return FALSE;
}

/****************************************************************************
**
**  ArxRleUiDlgColor::OnLButtonDown
**
**  **jma
**
*************************************/

void
ArxRleUiDlgColor::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if (pickedColorSwatch(point) == TRUE)
        display();
    else
        CAcUiDialog::OnLButtonDown(nFlags, point);
}

/****************************************************************************
**
**  ArxRleUiDlgColor::initColorTileRects
**
**  **jma
**
*************************************/

void
ArxRleUiDlgColor::initColorTileRects()
{
    long cellWd, cellHt;
    long bookEndGapX, bookEndGapY;
    int index;

        // get info for standard colors 1 thru 9
    calculateRectSize(ARXRLE_COLOR_PC_STANDARD_COLORS, m_standardColorsRect, 9.0, 1.0, cellWd, cellHt,
            bookEndGapX, bookEndGapY);

    int i;
    for (i=0;i<=9;i++) {
        index = i + 1;
        m_colorTiles[index].left = m_standardColorsRect.left  + bookEndGapX + (i * cellWd);
        m_colorTiles[index].top = m_standardColorsRect.top;
        m_colorTiles[index].right = m_colorTiles[index].left + cellWd;
        m_colorTiles[index].bottom = m_standardColorsRect.bottom;
    }

        // get info for gray colors 250 thru 255
    calculateRectSize(ARXRLE_COLOR_PC_GRAY_COLORS, m_grayColorsRect, 6.0, 1.0, cellWd, cellHt,
            bookEndGapX, bookEndGapY);

    for (i=0;i<6;i++) {
        index = i + 250;    // gray shades are 250-255
        m_colorTiles[index].left = m_grayColorsRect.left + bookEndGapX + (i * cellWd);
        m_colorTiles[index].top = m_grayColorsRect.top;
        m_colorTiles[index].right = m_colorTiles[index].left + cellWd;
        m_colorTiles[index].bottom = m_grayColorsRect.bottom;
    }

        // get info for full palette... AutoCAD's color distribution requires us
        // to skip indexes around by 2's
    calculateRectSize(ARXRLE_COLOR_PC_FULL_PALETTE_TOP, m_fullPaletteRectTop, 24.0, 5.0, cellWd, cellHt,
            bookEndGapX, bookEndGapY);

    int startIndex = 18;
    for (i=0;i<5;i++) {
        for (int j=0;j<24;j++) {
            index = startIndex + (j * 10);
            m_colorTiles[index].left = m_fullPaletteRectTop.left + bookEndGapX + (j * cellWd);
            m_colorTiles[index].top = m_fullPaletteRectTop.top + bookEndGapY + (i * cellHt);
            m_colorTiles[index].right = m_colorTiles[index].left + cellWd;
            m_colorTiles[index].bottom = m_colorTiles[index].top + cellHt;
        }
        startIndex -= 2;
    }

    calculateRectSize(ARXRLE_COLOR_PC_FULL_PALETTE_BOTTOM, m_fullPaletteRectBottom, 24.0, 5.0, cellWd, cellHt,
            bookEndGapX, bookEndGapY);

    startIndex = 11;
    for (i=0;i<5;i++) {
        for (int j=0;j<24;j++) {
            index = startIndex + (j * 10);
            m_colorTiles[index].left = m_fullPaletteRectBottom.left + bookEndGapX + (j * cellWd);
            m_colorTiles[index].top = m_fullPaletteRectBottom.top + bookEndGapY + (i * cellHt);
            m_colorTiles[index].right = m_colorTiles[index].left + cellWd;
            m_colorTiles[index].bottom = m_colorTiles[index].top + cellHt;
        }
        startIndex += 2;
    }

        // get rect location for current color swatch
    calculateRectSize(ARXRLE_COLOR_PC_COLOR_SWATCH, m_currentColorRect, 1.0, 1.0, cellWd, cellHt,
            bookEndGapX, bookEndGapY);
}

/****************************************************************************
**
**  ArxRleUiDlgColor::calculateRectSize
**
**  **jma
**
*************************************/

void
ArxRleUiDlgColor::calculateRectSize(UINT controlId, CRect& rect, double gridX, double gridY,
                    long& sizeX, long& sizeY, long& bookEndGapX, long& bookEndGapY)
{
    CWnd* tmpWnd = GetDlgItem(controlId);
    ASSERT(tmpWnd != NULL);

    tmpWnd->GetClientRect(rect);
    tmpWnd->ClientToScreen(rect);
    ScreenToClient(rect);
    rect.DeflateRect(1, 1);

        // get the size of each tile
    double rectWidth = static_cast<double>(rect.Width());
    sizeX = static_cast<long>(rectWidth / gridX);
    double rectHeight = static_cast<double>(rect.Height());
    sizeY = static_cast<long>(rectHeight / gridY);

    bookEndGapX = static_cast<long>((rectWidth - (gridX * sizeX)) / 2.0);
    bookEndGapY = static_cast<long>((rectHeight - (gridY * sizeY)) / 2.0);
}

/****************************************************************************
**
**  ArxRleUiDlgColor::display
**      updates current color after someone has changed the value.
**
**  **jma
**
*************************************/

void
ArxRleUiDlgColor::display()
{
    CDC* dc = GetDC();
    if (dc != NULL) {
        setToAcadColorPalette(dc);
        drawCurrentColorSwatch(dc);
        ReleaseDC(dc);
    }
    CString str;
    SetDlgItemText(ARXRLE_COLOR_EB_COLOR, ArxRleUtils::colorToStr(m_currentIndex, str));
}

/****************************************************************************
**
**  ArxRleUiDlgColor::drawCurrentColorSwatch
**
**  **jma
**
*************************************/

void
ArxRleUiDlgColor::drawCurrentColorSwatch(CDC* dc)
{
    dc->FillSolidRect(m_currentColorRect, PALETTEINDEX(m_currentIndex));
    dc->DrawEdge(m_currentColorRect, EDGE_SUNKEN, BF_RECT);
}

/****************************************************************************
**
**  ArxRleUiDlgColor::setToAcadColorPalette
**      make current CDC match the color palette of AutoCAD
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgColor::setToAcadColorPalette(CDC* dc)
{
    LOGPALETTE* plgPalette = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + 256 * sizeof(PALETTEENTRY));
    plgPalette->palNumEntries = 255;
    plgPalette->palVersion = 0x300;

    for (int i=0; i<256; i++) {
        // Get the RGB for the ACI (AutoCAD color index), except for
        // the first entry (0 -- BYBLOCK). Use color 7 in that case.
        unsigned long tmpColor = (i > 0) ? acedGetRGB(i) : acedGetRGB(7);
        plgPalette->palPalEntry[i].peRed = GetRValue(tmpColor);
        plgPalette->palPalEntry[i].peGreen = GetGValue(tmpColor & 0xffff);
        plgPalette->palPalEntry[i].peBlue = GetBValue(tmpColor);
        plgPalette->palPalEntry[i].peFlags = 0;
    }
    HPALETTE hPal;
    hPal = CreatePalette(plgPalette);
    ::SelectPalette(dc->m_hDC, hPal, FALSE);
    RealizePalette(dc->m_hDC);

    delete plgPalette;

    return TRUE;
}
