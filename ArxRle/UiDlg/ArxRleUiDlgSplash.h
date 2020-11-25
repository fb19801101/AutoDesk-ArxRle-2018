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

#ifndef ARXRLEUIDLGSPLASH_H
#define ARXRLEUIDLGSPLASH_H

#include "Resource.h"

/****************************************************************************
**
**	CLASS ArxRleUiDlgSplash:
**
**	**jma
**
*************************************/

class ArxRleUiDlgSplash : public CAcUiDialog {

public:
                    ArxRleUiDlgSplash(LPCTSTR bmpFileName);        // modeless version
    virtual			~ArxRleUiDlgSplash()    {}

    void            setTextStrings(LPCTSTR str1, LPCTSTR str2, LPCTSTR str3, LPCTSTR str4);

    //{{AFX_DATA(ArxRleUiDlgSplash)
    enum { IDD = ARXRLE_DLG_SPLASH };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxRleUiDlgSplash)
    public:
    virtual BOOL Create(CWnd* parent);
    virtual BOOL DestroyWindow();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxRleUiDlgSplash)
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    LPCTSTR		m_bmpFileName;
    CWnd*       m_parentWnd;
    CString     m_str1;
    CString     m_str2;
    CString     m_str3;
    CString     m_str4;

        // low level file reading vars    (ask wth for details!)
    HANDLE				m_fh;
    BITMAPFILEHEADER    m_bmfh;
    BITMAPINFO          m_bmi;
    ULONG               m_nBytesRead;
    LONG                m_picWidth;
    LONG                m_picHeight;

    static const int kBorderX;
    static const int kBorderY;

    void    displayTextLines();
    void    processTextLine(CString& str, UINT dlgItemId, int& numLines, int ht);
};

#endif    // ARXRLEUIDLGSPLASH_H
