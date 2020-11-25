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

#include "ArxRleUiDlgSplash.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int ArxRleUiDlgSplash::kBorderX = 10;
const int ArxRleUiDlgSplash::kBorderY = 10;


/****************************************************************************
**
**  ArxRleUiDlgSplash::ArxRleUiDlgSplash
**      Modeless version of dbox
**
**  **jma
**
*************************************/

ArxRleUiDlgSplash::ArxRleUiDlgSplash(LPCTSTR bmpFileName)
:	CAcUiDialog(ArxRleUiDlgSplash::IDD, NULL, NULL),
    m_bmpFileName(bmpFileName)
{
    //{{AFX_DATA_INIT(ArxRleUiDlgSplash)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiDlgSplash::Create
**
**  **jma
**
*************************************/

BOOL
ArxRleUiDlgSplash::Create(CWnd* parentWnd) 
{
    return CAcUiDialog::Create(ArxRleUiDlgSplash::IDD, parentWnd);
}

/****************************************************************************
**
**  ArxRleUiDlgSplash::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSplash::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiDlgSplash)
    //}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgSplash message map

BEGIN_MESSAGE_MAP(ArxRleUiDlgSplash, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxRleUiDlgSplash)
    ON_WM_PAINT()
    ON_WM_CLOSE()
    ON_WM_DESTROY()
    ON_WM_SETFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgSplash message handlers

/****************************************************************************
**
**  ArxRleUiDlgSplash::OnInitDialog
**
**  **wth
**
*************************************/

BOOL
ArxRleUiDlgSplash::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();
    
    m_fh = CreateFile(m_bmpFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

    if (m_fh != INVALID_HANDLE_VALUE) {
        ReadFile(m_fh, &m_bmfh, sizeof(BITMAPFILEHEADER), &m_nBytesRead, NULL);
        ReadFile(m_fh, &m_bmi, sizeof(BITMAPINFO), &m_nBytesRead, NULL);
        m_picWidth = m_bmi.bmiHeader.biWidth;
        m_picHeight = m_bmi.bmiHeader.biHeight;
        GetDlgItem(ARXRLE_SPLASH_PC_SPLASHFRAME)->SetWindowPos(NULL, kBorderX, kBorderY, m_picWidth, m_picHeight, SWP_NOZORDER);
        displayTextLines();
        CenterWindow();
    }

    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiDlgSplash::OnPaint
**
**  **wth
**
*************************************/

void
ArxRleUiDlgSplash::OnPaint() 
{
    CPaintDC dc(this);

    HDC hdcBm;
    HPALETTE hPal;
    LOGPALETTE* plgPalette;
    BITMAPINFO* pbmi;
    void* pPixels;
    int nBytes, i;
    int nColors;
    HBITMAP hBm;
    static TCHAR szModuleName[_MAX_PATH];

    plgPalette = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + 256 * sizeof(PALETTEENTRY));

    if (m_fh != INVALID_HANDLE_VALUE && plgPalette) {
        nBytes = GetFileSize(m_fh, NULL) - m_bmfh.bfOffBits;
        pPixels = malloc(nBytes);
        if (pPixels) {
            nColors = (m_bmi.bmiHeader.biClrUsed) ? m_bmi.bmiHeader.biClrUsed : 1 << m_bmi.bmiHeader.biBitCount;

            pbmi = (BITMAPINFO*)malloc( sizeof(BITMAPINFO) + sizeof(RGBQUAD) * nColors);
            SetFilePointer(m_fh, -((long)sizeof(BITMAPINFO)), NULL, FILE_CURRENT);

            ReadFile(m_fh, pbmi, sizeof(BITMAPINFO) + sizeof(RGBQUAD) * nColors, &m_nBytesRead, NULL);
            ReadFile(m_fh, pPixels, nBytes, &m_nBytesRead, NULL);

            plgPalette->palNumEntries = nColors;
            plgPalette->palVersion = 0x300;

            for (i=0;i<nColors;i++) {
                plgPalette->palPalEntry[i].peRed = pbmi->bmiColors[i].rgbRed;
                plgPalette->palPalEntry[i].peGreen = pbmi->bmiColors[i].rgbGreen;
                plgPalette->palPalEntry[i].peBlue = pbmi->bmiColors[i].rgbBlue;
                plgPalette->palPalEntry[i].peFlags = 0;
            }

            hPal = CreatePalette(plgPalette);
            ::SelectPalette(dc.m_hDC, hPal, FALSE);
            RealizePalette(dc.m_hDC);
    
            hdcBm = CreateCompatibleDC(dc.m_hDC);
            
            hBm = CreateDIBitmap(dc.m_hDC, &pbmi->bmiHeader, CBM_INIT, pPixels, pbmi, DIB_RGB_COLORS);

            HGDIOBJ oldBmp = ::SelectObject(hdcBm, hBm);

            CRect rect;
            GetDlgItem(ARXRLE_SPLASH_PC_SPLASHFRAME)->GetClientRect(&rect);
            GetDlgItem(ARXRLE_SPLASH_PC_SPLASHFRAME)->ClientToScreen(&rect);
            ScreenToClient(&rect);

            BitBlt(dc.m_hDC, rect.left, rect.top, rect.Width(), rect.Height(), hdcBm, 0, 0, SRCCOPY);
            //dc.SetTextAlign(TA_LEFT|TA_BOTTOM);
            //dc.TextOut(rect.left,(rect.top+rect.Height()), "Hey Dude");

            // select out the DIB from the HDC
            ::SelectObject(hdcBm, oldBmp);
            // delete the DIB
            BOOL res = ::DeleteObject(hBm);

            // delete the palette
            res = ::DeleteObject(plgPalette);

            // delete the compatible DC
            res = ::DeleteDC(hdcBm);
  
			free(pPixels);
            free(pbmi);
        }
        free(plgPalette);
    }
    else {
        if (plgPalette)
            free(plgPalette);
    }
}

/****************************************************************************
**
**  ArxRleUiDlgSplash::DestroyWindow
**
**  **wth
**
*************************************/

BOOL
ArxRleUiDlgSplash::DestroyWindow() 
{
    if (m_fh != INVALID_HANDLE_VALUE)
        CloseHandle(m_fh);
    
    return CAcUiDialog::DestroyWindow();
}

/****************************************************************************
**
**  ArxRleUiDlgSplash::displayTextLines
**
**  **wth
**
*************************************/

void
ArxRleUiDlgSplash::displayTextLines()
{
    int height;
    CWnd* wnd = GetDlgItem(ARXRLE_SPLASH_EB_LINE1);
    ASSERT(wnd != NULL);
    if (wnd) {
        CRect linerect;
        wnd->GetClientRect(&linerect);
        height = linerect.Height();
    }
    else
        height = 5;

    int numLines = 0;
    processTextLine(m_str1, ARXRLE_SPLASH_EB_LINE1, numLines, height);
    processTextLine(m_str2, ARXRLE_SPLASH_EB_LINE2, numLines, height);
    processTextLine(m_str3, ARXRLE_SPLASH_EB_LINE3, numLines, height);
    processTextLine(m_str4, ARXRLE_SPLASH_EB_LINE4, numLines, height);

    SetWindowPos(NULL, 0, 0, m_picWidth+(3*kBorderX),
                m_picHeight+(3*kBorderY)+(numLines*height), SWP_NOZORDER|SWP_NOMOVE);        
}

/****************************************************************************
**
**  ArxRleUiDlgSplash::processTextLine
**
**  **wth
**
*************************************/

void
ArxRleUiDlgSplash::processTextLine(CString& str, UINT dlgItemId, int& numLines, int ht)
{
    CWnd* wnd = GetDlgItem(dlgItemId);
    ASSERT(wnd != NULL);
    if (wnd) {
        if (str.IsEmpty()) {
            wnd->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOZORDER);
        }
        else {
            wnd->SetWindowPos(NULL, kBorderX, m_picHeight+(kBorderY)+(numLines*ht),
                            m_picWidth, ht, SWP_NOZORDER);
            wnd->SetWindowText(str);
            numLines++;
        }
    }
}

/****************************************************************************
**
**  ArxRleUiDlgSplash::setTextStrings
**
**  **jma
**
*************************************/

void
ArxRleUiDlgSplash::setTextStrings(LPCTSTR str1, LPCTSTR str2, LPCTSTR str3, LPCTSTR str4)
{
    m_str1 = str1;
    m_str2 = str2;
    m_str3 = str3;
    m_str4 = str4;
}

