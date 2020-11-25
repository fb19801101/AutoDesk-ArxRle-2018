//
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

#include "ArxRleUiDlgWindoInfo.h"
#include "ArxRleUiDlgWindoType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HTREEITEM htCur, htPrev;

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgWindoInfo dialog


ArxRleUiDlgWindoInfo::ArxRleUiDlgWindoInfo(CWnd* pParent /*=NULL*/)
	: CDialog(ArxRleUiDlgWindoInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(ArxRleUiDlgWindoInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ArxRleUiDlgWindoInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ArxRleUiDlgWindoInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ArxRleUiDlgWindoInfo, CDialog)
	//{{AFX_MSG_MAP(ArxRleUiDlgWindoInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgWindoInfo message handlers
BOOL ArxRleUiDlgWindoInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_pTreeCtrl = (CTreeCtrl*)GetDlgItem(ARXRLE_TREEDLG_TR);

	m_imgList.Create(16, 15, FALSE, 9, 3);
	
	CBitmap* pBitmap = new CBitmap;
	pBitmap->LoadBitmap(ARXRLE_BMP_WINDOW);
	m_nIdxWindow = m_imgList.Add(pBitmap, RGB(0, 0, 0));
	pBitmap->LoadBitmap(ARXRLE_BMP_RECT);
	m_nIdxRect = m_imgList.Add(pBitmap, RGB(0, 0, 0));
	pBitmap->LoadBitmap(ARXRLE_BMP_ARCH);
	m_nIdxArch = m_imgList.Add(pBitmap, RGB(0, 0, 0));
	pBitmap->LoadBitmap(ARXRLE_BMP_APEX);
	m_nIdxApex = m_imgList.Add(pBitmap, RGB(0, 0, 0));
	pBitmap->LoadBitmap(ARXRLE_BMP_WIDTH);
	m_nIdxWidth = m_imgList.Add(pBitmap, RGB(0, 0, 0));
	pBitmap->LoadBitmap(ARXRLE_BMP_HEIGHT);
	m_nIdxHeight = m_imgList.Add(pBitmap, RGB(0, 0, 0));
	pBitmap->LoadBitmap(ARXRLE_BMP_ROWS);
	m_nIdxRows = m_imgList.Add(pBitmap, RGB(0, 0, 0));
	pBitmap->LoadBitmap(ARXRLE_BMP_COLS);
	m_nIdxCols = m_imgList.Add(pBitmap, RGB(0, 0, 0));
	pBitmap->LoadBitmap(ARXRLE_BMP_STARTPT);
	m_nIdxStartPt = m_imgList.Add(pBitmap, RGB(0, 0, 0));
	m_pTreeCtrl->SetImageList(&m_imgList, TVSIL_NORMAL);
	delete pBitmap;

	AddTreeViewItems();

	HTREEITEM hRoot = m_pTreeCtrl->GetRootItem();

	m_pTreeCtrl->Expand(hRoot, TVE_EXPAND);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ArxRleUiDlgWindoInfo::AddTreeViewItems()
{
	CString strItem("Window");

	htCur = AddOneItem((HTREEITEM)NULL, strItem, (HTREEITEM)TVI_ROOT, m_nIdxWindow, TRUE);

	switch(windInfo.m_nWindType)
	{
		case 0 :
			strItem = L"Rect";
			htPrev = AddOneItem(htCur, strItem, NULL, m_nIdxRect, FALSE);
		break;

		case 1 :
			strItem = L"Arch";
			htPrev = AddOneItem(htCur, strItem, NULL, m_nIdxArch, FALSE);
		break;

		case 2 :
			strItem = L"Apex";
			htPrev = AddOneItem(htCur, strItem, NULL, m_nIdxApex, FALSE);
		break;
	}


	strItem.Format(L"W = %.2lf", windInfo.m_dWindWt);
	htPrev = AddOneItem(htCur, strItem, NULL, m_nIdxWidth, FALSE);

	strItem.Format(L"H = %.2lf", windInfo.m_dWindHt);
	htPrev = AddOneItem(htCur, strItem, NULL, m_nIdxHeight, FALSE);

	strItem.Format(L"Rows = %d", windInfo.m_nRows);
	htPrev = AddOneItem(htCur, strItem, NULL, m_nIdxRows, FALSE);

	strItem.Format(L"Cols = %d", windInfo.m_nCols);
	htPrev = AddOneItem(htCur, strItem, NULL, m_nIdxCols, FALSE);

	strItem.Format(L"SP = (%.2lf, %.2lf)", windInfo.m_startPt.x, windInfo.m_startPt.y);
	htPrev = AddOneItem(htCur, strItem, NULL, m_nIdxStartPt, FALSE);
}

HTREEITEM ArxRleUiDlgWindoInfo::AddOneItem( HTREEITEM hParent, 
	CString szText, HTREEITEM hInsAfter, int iImage, BOOL bChildren)
{
	HTREEITEM hItem;		// return value
	TV_ITEM tvI;			// item structure
	TV_INSERTSTRUCT tvIns;	// item insert structure
	if(bChildren)			// *** set tvI.mask member ***
		tvI.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_CHILDREN | TVIF_SELECTEDIMAGE;	// item has children
	else					// item has no children
		tvI.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvI.pszText = szText.GetBuffer(szText.GetLength());	// set text, text lenght, image
	tvI.cchTextMax = szText.GetLength();
	tvI.iImage = iImage;
	tvI.iSelectedImage = iImage;
	tvI.cChildren = 1;		// allow one more level down
					// do the insert
	tvIns.item = tvI;
	tvIns.hInsertAfter = hInsAfter;
	tvIns.hParent = hParent;
	hItem = m_pTreeCtrl->InsertItem(&tvIns);
	return (hItem);		// return (add error trap here)
}
