/
	//////////////////////////////////////////////////////////////////////////////
	//
	//  Copyright 2015 Autodesk, Inc.  All rights reserved.
	//
	//  Use of this software is subject to the terms of the Autodesk license 
	//  agreement provided at the time of installation or download, or which 
	//  otherwise accompanies this software in either electronic or hard copy form.   
	//
	//////////////////////////////////////////////////////////////////////////////
	//
#include "StdAfx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleTabCtrl.h"

// constant string definitions here (or you can put it into resource string table)
#define IDS_UTIL_TAB            "TAB"
#define IDS_UTIL_UXTHEME        "UxTheme.dll"
#define IDS_UTIL_THEMEACT       "IsThemeActive"
#define IDS_UTIL_THEMEOPN       "OpenThemeData"
#define IDS_UTIL_THEMEBCKG      "DrawThemeBackground"

// ArxRleTablCtrl

IMPLEMENT_DYNAMIC(ArxRleTablCtrl, CTabCtrl)

ArxRleTablCtrl::ArxRleTablCtrl()
{
	m_clrBKGrnd = RGB(68,128,128);
	m_clrText = RGB(255,255,255);
	m_nTextHeight = 13;
	m_nTextWidth = 6;
	m_bItalic = FALSE;
	m_bUnderline = FALSE;
	m_nTextWeight = FW_NORMAL;
	m_strTextStyle = _T("仿宋");
}

ArxRleTablCtrl::~ArxRleTablCtrl()
{
}


BEGIN_MESSAGE_MAP(ArxRleTablCtrl, CTabCtrl)
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// ArxRleTablCtrl 消息处理程序

BOOL ArxRleTablCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	dwStyle |= TCS_OWNERDRAWFIXED;  

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);  
}

void ArxRleTablCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0, TCS_OWNERDRAWFIXED);  

	CTabCtrl::PreSubclassWindow();
}

void ArxRleTablCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	if(lpDrawItemStruct->CtlType == ODT_TAB)  
	{   
		CRect rect = lpDrawItemStruct->rcItem;  
		INT nTabIndex = lpDrawItemStruct->itemID;  
		if (nTabIndex < 0) return;  

		TCHAR label[64];  
		TC_ITEM tci;  
		tci.mask = TCIF_TEXT|TCIF_IMAGE;  
		tci.pszText = label;       
		tci.cchTextMax = 63;          
		GetItem(nTabIndex, &tci );

		CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);  
		if(!pDC) return;  
		int nSavedDC = pDC->SaveDC();  

		//填充背景色   
		COLORREF rcBack;  
		if (lpDrawItemStruct->itemState & CDIS_SELECTED  )   
		{  
			rcBack = m_clrBKGrnd;  
		}  
		else if(lpDrawItemStruct->itemState & (CDIS_DISABLED | CDIS_GRAYED) )   
		{  
			rcBack = RGB(0, 255, 0);
		}  
		else  
		{  
			rcBack = GetSysColor(COLOR_BTNFACE);  
		}      
		pDC->FillSolidRect(rect, rcBack);

		rect.top += ::GetSystemMetrics(SM_CYEDGE);  

		int nOldMode = pDC->SetBkMode(TRANSPARENT);  

		//绘制图片   
		CImageList* pImageList = GetImageList();  
		if (pImageList && tci.iImage >= 0)
		{  
			rect.left += pDC->GetTextExtent(_T(" ")).cx;       // Margin   

			// Get height of image so we    
			IMAGEINFO info;
			pImageList->GetImageInfo(tci.iImage, &info);  
			CRect ImageRect(info.rcImage);  
			HIMAGELIST hImgs = (HIMAGELIST)TabCtrl_GetImageList(GetSafeHwnd());
			ImageList_Draw(hImgs,tci.iImage, *pDC, rect.left, rect.top, ILD_TRANSPARENT);  
			rect.left += ImageRect.Width();
		}

		// 设置字体对象
		CFont font,*oldFont;
		font.CreateFont(
			m_nTextHeight,             // nHeight 字体高度
			m_nTextWidth,              // nWidth 字体平均宽度
			0,                         // nEscapement 角度，矢量图像和的X轴之间显示面
			0,                         // nOrientation 角度，字符的基线并将X轴之间
			m_nTextWeight,             // nWeight 字体权重
			m_bItalic,                 // bItalic 是否倾斜 
			m_bUnderline,              // bUnderline 是否设置下划线
			0,                         // cStrikeOut 字符是否已触击，删除线字体
			ANSI_CHARSET,              // nCharSet Windows SDK 的 LOGFONT 结构指定字体的字符
			OUT_DEFAULT_PRECIS,        // nOutPrecision 预期输出精度
			CLIP_DEFAULT_PRECIS,       // nClipPrecision 所需的剪辑精度
			DEFAULT_QUALITY,           // nQuality 字体的输出质量
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily 字体的间距和系列
			m_strTextStyle);           // lpszFacename 字体的字样名称
		oldFont = pDC->SelectObject(&font); //选中字体，选中新字体时返回旧字体，要保存
		LOGFONT lf;
		font.GetLogFont(&lf);
		LONG lfHeight = lf.lfHeight;
		LONG lfWidth = lf.lfWidth;

		//绘制字体   
		COLORREF txtColor;  
		if (lpDrawItemStruct->itemState & CDIS_SELECTED  )   
		{  
			rect.top -= ::GetSystemMetrics(SM_CYEDGE);

			txtColor = m_clrText;
		}  
		else if(lpDrawItemStruct->itemState & (CDIS_DISABLED | CDIS_GRAYED) )   
		{  
			txtColor = RGB(128, 128, 128);
		}  
		else  
		{  
			txtColor = GetSysColor(COLOR_WINDOWTEXT);  
		}
		pDC->SetTextColor(txtColor);  
		pDC->DrawText(label, rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);  
		pDC->SelectObject(oldFont);
		font.DeleteObject();

		pDC->SetBkMode(nOldMode);
		pDC->RestoreDC(nSavedDC);
	}
}

void ArxRleTablCtrl::AddDlg(CDialog* pDlg, UINT nID)
{
	m_vecTabPage.push_back(pDlg);
	m_vecTabPage[m_vecTabPage.size()-1]->Create(nID,this);
}

void ArxRleTablCtrl::InitTab()
{
	CRect TabRect,ItemRect;
	CPoint PagePos;
	CSize PageSize;

	GetClientRect(&TabRect);
	GetItemRect(0,&ItemRect);
	PagePos.x=ItemRect.left+1;
	PagePos.y=ItemRect.bottom+1;
	PageSize.cx=TabRect.right-ItemRect.left-5;
	PageSize.cy=TabRect.bottom-PagePos.y-5;

	m_vecTabPage[0]->ShowWindow(SW_SHOW);
	for (int i=1;i<m_vecTabPage.size();i++)
		m_vecTabPage[i]->ShowWindow(SW_HIDE);

	m_vecTabPage[0]->SetWindowPos(&wndTop,PagePos.x,PagePos.y,PageSize.cx,PageSize.cy,SWP_SHOWWINDOW);
	for (int i=1;i<m_vecTabPage.size();i++)
		m_vecTabPage[i]->SetWindowPos(&wndTop,PagePos.x,PagePos.y,PageSize.cx,PageSize.cy,SWP_HIDEWINDOW);

	m_CurrentTabIndex=0;
}

void ArxRleTablCtrl::InitImageList(UINT nBitmapID)
{
	CImageList* imgs = new CImageList;
	if(imgs->Create(nBitmapID, 16, 1, RGB(0xFF,0,0xFF)))
		SetImageList(imgs);
}

void ArxRleTablCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTabCtrl::OnLButtonDown(nFlags, point);

	if (GetCurFocus()!=m_CurrentTabIndex)
	{
		m_vecTabPage[m_CurrentTabIndex]->ShowWindow(SW_HIDE);
		m_CurrentTabIndex=GetCurFocus();
		m_vecTabPage[m_CurrentTabIndex]->ShowWindow(SW_SHOW);
		m_vecTabPage[m_CurrentTabIndex]->SetFocus();
	}
}

void ArxRleTablCtrl::OnDestroy()
{
	CTabCtrl::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	for(int i=0;i<m_vecTabPage.size();i++)
	{
		if (m_vecTabPage[i])
		{
			delete m_vecTabPage[i];
			m_vecTabPage[i] = NULL;
		}
	}

	m_vecTabPage.clear();
}