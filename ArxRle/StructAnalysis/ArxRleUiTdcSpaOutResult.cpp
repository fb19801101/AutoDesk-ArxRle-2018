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

#include "ArxRleUiTdcSpaOutResult.h"


extern float GetConcretFc(int Fcuk);
extern float GetConcretFt(int Fcuk);
extern float GetConcretFck(int Fcuk);
extern float GetGjKanglaFy(CString &cs);
extern float GetGjKanglaFyc(CString &cs);
extern float GetGjKanglaEs(CString &cs);
// ArxRleUiTdcSpaOutResult 对话框

IMPLEMENT_DYNAMIC(ArxRleUiTdcSpaOutResult, CAcUiTabChildDialog)

ArxRleUiTdcSpaOutResult::ArxRleUiTdcSpaOutResult()
	: CAcUiTabChildDialog(NULL, ArxRleApp::m_hInstance)
{
	m_size_DlgMinSize.cx    = 0;
	m_size_DlgMinSize.cy    = 0;
	m_size_DlgClientSize.cx = 0;
	m_size_DlgClientSize.cy = 0;
	m_size_EditMinSize.cx   = 0;
	m_size_EditMinSize.cy   = 0;
	m_rect_EditMinRect.SetRectEmpty();
}

ArxRleUiTdcSpaOutResult::~ArxRleUiTdcSpaOutResult()
{
}

void ArxRleUiTdcSpaOutResult::DoDataExchange(CDataExchange* pDX)
{
	CAcUiTabChildDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ArxRleUiTdcSpaOutResult, CAcUiTabChildDialog)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_OPEN, OnClickBtnOpen)
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_SAVE, OnClickBtnSave)
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_BOLD, OnClickBtnBold)
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_ITALIC, OnClickBtnItalic)
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_UNDERLINE, OnClickBtnUnderline)
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_STRIKEOUT, OnClickBtnStrikeout)
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_FONT, OnClickBtnFont)
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_COLOR, OnClickBtnColor)
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_LEFT, OnClickBtnLeft)
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_CENTER, OnClickBtnCenter)
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_RIGHT, OnClickBtnRight)
	ON_BN_CLICKED(ARXRLE_SPA_OUTRESULT_BN_BULLET, OnClickBtnBullet)
END_MESSAGE_MAP()


// ArxRleUiTdcSpaOutResult 消息处理程序

int ArxRleUiTdcSpaOutResult::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//	  m_wndFormatBar.Create(this);
	//	  m_wndFormatBar.LoadToolBar(IDR_TOOLBAR_FORMAT);
	//	  m_wndFormatBar.SetBarStyle(CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_FLYBY);
	//	  RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	//	  m_wndFormatBar.ShowWindow(SW_SHOW);

	// Initializing the static RichEditControl
	//	  m_pRichEdit->SetWordWrap();// Default is on
	// Calculating minimum sizes for RichEdit control, dialog and dialog client area
	CRect rectDlg;
	WINDOWPLACEMENT wpl;
	GetWindowPlacement(&wpl);
	rectDlg = wpl.rcNormalPosition;
	rectDlg.NormalizeRect();
	m_size_DlgMinSize    = rectDlg.Size();
	GetClientRect(rectDlg);
	m_size_DlgClientSize = rectDlg.Size();

	//	  m_pRichEdit->GetWindowPlacement(&wpl);
	m_rect_EditMinRect = wpl.rcNormalPosition;
	m_size_EditMinSize = m_rect_EditMinRect.Size();

	m_pRichEdit = new ArxRleRichEditCtrl;
	m_pRichEdit->Create(ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | 
						WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL | WS_TABSTOP | WS_VISIBLE, rectDlg, this, ARXRLE_SPA_OUTRESULT_RICHEDIT);

	m_imgList.Create(ARXRLE_BMP_SPABAR, 32, 1, ILC_COLOR8 | ILC_MASK);
	return 0;
}

BOOL ArxRleUiTdcSpaOutResult::OnInitDialog()
{
	CAcUiTabChildDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作

	// TODO: 在此添加额外的初始化代码
	VERIFY(m_ButtonOpen.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_OPEN, this));
	m_ButtonOpen.SetIcon(m_imgList.ExtractIcon(0));

	VERIFY(m_ButtonSave.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_SAVE, this));
	m_ButtonSave.SetIcon(m_imgList.ExtractIcon(1));

	VERIFY(m_ButtonBold.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_BOLD, this));
	m_ButtonBold.SetIcon(m_imgList.ExtractIcon(2));

	VERIFY(m_ButtonXieTi.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_ITALIC, this));
	m_ButtonXieTi.SetIcon(m_imgList.ExtractIcon(3));

	VERIFY(m_ButtonUnderLine.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_UNDERLINE, this));
	m_ButtonUnderLine.SetIcon(m_imgList.ExtractIcon(4));

	VERIFY(m_ButtonMiddleLine.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_STRIKEOUT, this));
	m_ButtonMiddleLine.SetIcon(m_imgList.ExtractIcon(5));

	VERIFY(m_ButtonFont.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_FONT, this));
	m_ButtonFont.SetIcon(m_imgList.ExtractIcon(6));

	VERIFY(m_ButtonColor.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_COLOR, this));
	m_ButtonColor.SetIcon(m_imgList.ExtractIcon(7));

	VERIFY(m_ButtonLeft.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_LEFT, this));
	m_ButtonLeft.SetIcon(m_imgList.ExtractIcon(8));

	VERIFY(m_ButtonCenter.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_CENTER, this));
	m_ButtonCenter.SetIcon(m_imgList.ExtractIcon(9));

	VERIFY(m_ButtonRight.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_RIGHT, this));
	m_ButtonRight.SetIcon(m_imgList.ExtractIcon(10));

	VERIFY(m_ButtonNumber.SubclassDlgItem(ARXRLE_SPA_OUTRESULT_BN_BULLET, this));
	m_ButtonNumber.SetIcon(m_imgList.ExtractIcon(11));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ArxRleUiTdcSpaOutResult::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if( !IsWindow(m_pRichEdit->GetSafeHwnd()) )
		return;

	int iDeltaX = 0;
	int iDeltaY = 0;
	if( cx > m_size_DlgClientSize.cx )
		iDeltaX = cx - m_size_DlgClientSize.cx;
	if( cy > m_size_DlgClientSize.cy )
		iDeltaY = cy - m_size_DlgClientSize.cy;

	CRect rectPos;
	rectPos.left = m_rect_EditMinRect.left+10;
	rectPos.top= m_rect_EditMinRect.top+40;
	rectPos.right  = m_rect_EditMinRect.left + m_size_EditMinSize.cx + iDeltaX-10;
	rectPos.bottom = m_rect_EditMinRect.top  + m_size_EditMinSize.cy + iDeltaY-10;
	m_pRichEdit->MoveWindow(rectPos);
	m_pRichEdit->SetRedraw(true);
	m_pRichEdit->Invalidate();	
	// TODO: Add your message handler code here
}

void ArxRleUiTdcSpaOutResult::OnClickBtnOpen() 
{
	// TODO: Add your control notification handler code here
	static CString strInitDir = _T("");
	static CString strInitExt = _T(".rtf");
	static CString strInitFil = _T("*.rtf");
	static CString strInitNamen = _T("RTF-Files (*.rtf)|All files (*.*)|*.*||");
	CString strDateiname;
	if( strInitDir.IsEmpty() )	 
	{ 
		LPTSTR pstr = strInitDir.GetBuffer(1032);
		GetCurrentDirectory(1024,pstr);
		strInitDir.ReleaseBuffer();
	}
	CFileDialog DateiDlg (true, strInitExt ,strInitFil,0,strInitNamen);
	DateiDlg.m_ofn.Flags |= OFN_FILEMUSTEXIST;
	DateiDlg.m_ofn.Flags |= OFN_NOCHANGEDIR;
	// DateiDlg.m_ofn.Flags |= OFN_NOREADONLYRETURN;
	DateiDlg.m_ofn.Flags |= OFN_PATHMUSTEXIST;
	// DateiDlg.m_ofn.Flags |= OFN_HIDEREADONLY;
	// DateiDlg.m_ofn.Flags |= OFN_OVERWRITEPROMPT;
	DateiDlg.m_ofn.lpstrInitialDir = strInitDir;
	if(IDOK == DateiDlg.DoModal())
	{ 
		strDateiname = DateiDlg.GetPathName();
		int iPos = strDateiname.ReverseFind(TCHAR('\\'));
		if( -1 != iPos )
		{
			strInitDir = strDateiname.Left(iPos);
		}
		m_pRichEdit->LoadRTF(strDateiname);
	}		
}

void ArxRleUiTdcSpaOutResult::OnClickBtnSave() 
{
	// TODO: Add your control notification handler code here
	static CString strInitDir = _T("");
	static CString strInitExt = _T("rtf");
	static CString strInitFil = _T("*.rtf");
	static CString strInitNamen = _T("RTF-Files (*.rtf)|All files (*.*)|*.*||");
	CString strDateiname;
	if( strInitDir.IsEmpty() )	 
	{ LPTSTR pstr = strInitDir.GetBuffer(1032);
	GetCurrentDirectory(1024,pstr);
	strInitDir.ReleaseBuffer();
	}
	if( !UpdateData(true) )
	{ return;
	}
	CFileDialog DateiDlg (false, strInitExt ,strInitFil,0,strInitNamen);
	//  DateiDlg.m_ofn.Flags |= OFN_FILEMUSTEXIST;
	//  DateiDlg.m_ofn.Flags |= OFN_NOCHANGEDIR;
	// DateiDlg.m_ofn.Flags |= OFN_NOREADONLYRETURN;
	DateiDlg.m_ofn.Flags |= OFN_PATHMUSTEXIST;
	// DateiDlg.m_ofn.Flags |= OFN_HIDEREADONLY;
	// DateiDlg.m_ofn.Flags |= OFN_OVERWRITEPROMPT;
	DateiDlg.m_ofn.lpstrInitialDir = strInitDir;
	if(IDOK == DateiDlg.DoModal())
	{ strDateiname = DateiDlg.GetPathName();
	int iPos = strDateiname.ReverseFind(TCHAR('\\'));
	if( -1 != iPos )
	{ strInitDir = strDateiname.Left(iPos);
	}
	CFileStatus fileStatus;
	BOOL bReturnStatus = FALSE;
	bReturnStatus = CFile::GetStatus(strDateiname,fileStatus);
	if( bReturnStatus )
	{ int iReturn = AfxMessageBox(_T("This file already exists!\n Do you want to overwrite it?"),MB_YESNOCANCEL);
	if( IDCANCEL == iReturn ) return;
	if( IDNO == iReturn )
	{ return;
	}
	}
	m_pRichEdit->WriteRTF(strDateiname);
	} 		
}

void ArxRleUiTdcSpaOutResult::OnClickBtnBold() 
{
	// TODO: Add your control notification handler code here
	m_pRichEdit->SetBold();

}

void ArxRleUiTdcSpaOutResult::OnClickBtnItalic() 
{
	// TODO: Add your control notification handler code here
	m_pRichEdit->SetItalic();

}

void ArxRleUiTdcSpaOutResult::OnClickBtnUnderline() 
{
	// TODO: Add your control notification handler code here
	m_pRichEdit->SetUnderlined();

}

void ArxRleUiTdcSpaOutResult::OnClickBtnStrikeout() 
{
	// TODO: Add your control notification handler code here
	m_pRichEdit->SetStrikeout();

}

void ArxRleUiTdcSpaOutResult::OnClickBtnFont() 
{
	// TODO: Add your control notification handler code here
	CFontDialog FontDlg;
	LOGFONT     logFont;
	int         iFormat;
	CString     strFontName = m_pRichEdit->GetFontName();
	wchar_t *      pStr = strFontName.GetBuffer(32);
	wcscmp(logFont.lfFaceName,pStr);
	strFontName.ReleaseBuffer();

	logFont.lfHeight    = -m_pRichEdit->GetFontSize();
	iFormat = m_pRichEdit->IsItalic();
	if( -1 == iFormat )
	{ FontDlg.m_cf.Flags       |= CF_NOSTYLESEL;
	}
	else
	{ logFont.lfItalic = iFormat;
	}
	logFont.lfWeight    = FW_REGULAR;
	iFormat = m_pRichEdit->IsBold();
	if( 1 == iFormat)
	{ logFont.lfWeight = FW_BOLD;
	}
	if( -1 == iFormat )
	{ FontDlg.m_cf.Flags       |= CF_NOSTYLESEL;
	}
	logFont.lfUnderline = m_pRichEdit->IsUnderlined();
	logFont.lfStrikeOut = m_pRichEdit->IsStrikeout();

	FontDlg.m_cf.lStructSize = sizeof(CHOOSEFONT);
	FontDlg.m_cf.hwndOwner   = GetSafeHwnd();
	FontDlg.m_cf.lpLogFont   = &logFont;
	FontDlg.m_cf.Flags       |= CF_INITTOLOGFONTSTRUCT;
	//  FontDlg.m_cf.iPointSize  = m_pRichEdit->GetSelectionFontSize()*10;
	if( IDOK == FontDlg.DoModal() )
	{ m_pRichEdit->SetRedraw(false);
	m_pRichEdit->SetFontName(FontDlg.m_cf.lpLogFont->lfFaceName);
	m_pRichEdit->SetFontSize(abs(FontDlg.m_cf.lpLogFont->lfHeight));
	m_pRichEdit->SetColour(FontDlg.m_cf.rgbColors);
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	m_pRichEdit->GetSelectionCharFormat(cf);
	cf.dwMask = cf.dwEffects = 0;
	if( (FontDlg.m_cf.nFontType & ITALIC_FONTTYPE) )
	{ cf.dwMask    |= CFM_ITALIC;
	cf.dwEffects |= CFE_ITALIC;
	}
	if( (FontDlg.m_cf.nFontType & BOLD_FONTTYPE) )
	{ cf.dwMask    |= CFM_BOLD;
	cf.dwEffects |= CFE_BOLD;
	}
	if( FontDlg.m_cf.lpLogFont->lfStrikeOut )
	{ cf.dwMask    |= CFM_STRIKEOUT;
	cf.dwEffects |= CFE_STRIKEOUT;
	}
	if( FontDlg.m_cf.lpLogFont->lfUnderline )
	{ cf.dwMask    |= CFM_UNDERLINE;
	cf.dwEffects |= CFE_UNDERLINE;
	}
	m_pRichEdit->SetSelectionCharFormat(cf);
	m_pRichEdit->SetRedraw(true);
	m_pRichEdit->Invalidate();
	}	
}

void ArxRleUiTdcSpaOutResult::OnClickBtnColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog FarbDlg;
	if( FarbDlg.DoModal() == IDOK )
	{ m_pRichEdit->SetColour(FarbDlg.GetColor());
	}		
}

void ArxRleUiTdcSpaOutResult::OnClickBtnLeft() 
{
	// TODO: Add your control notification handler code here
	m_pRichEdit->SetLeft();

}

void ArxRleUiTdcSpaOutResult::OnClickBtnCenter() 
{
	// TODO: Add your control notification handler code here
	m_pRichEdit->SetCenter();	
}

void ArxRleUiTdcSpaOutResult::OnClickBtnRight() 
{
	// TODO: Add your control notification handler code here
	m_pRichEdit->SetRight();

}

void ArxRleUiTdcSpaOutResult::OnClickBtnBullet() 
{
	// TODO: Add your control notification handler code here
	m_pRichEdit->SetBullet();	
}

void ArxRleUiTdcSpaOutResult::SetLeft()
{
	PARAFORMAT pf;
	pf.dwMask=PFM_ALIGNMENT;
	pf.wAlignment=PFA_LEFT;	
	m_pRichEdit->SetParaFormat(pf);
}

void ArxRleUiTdcSpaOutResult::SetCenter()
{
	PARAFORMAT pf;
	pf.dwMask=PFM_ALIGNMENT;
	pf.wAlignment=PFA_CENTER;	
	m_pRichEdit->SetParaFormat(pf);
}

void ArxRleUiTdcSpaOutResult::SetRight()
{
	PARAFORMAT pf;
	pf.dwMask=PFM_ALIGNMENT;
	pf.wAlignment=PFA_RIGHT;
	m_pRichEdit->SetParaFormat(pf);
}

void ArxRleUiTdcSpaOutResult::SetFontSize(int iSize)
{
	CHARFORMAT cf;
	cf.dwMask=CFM_BOLD | CFM_SIZE | CFM_CHARSET | CFM_FACE;
	cf.dwEffects=0;
	cf.yHeight=iSize;	//200－10号；210－五号；220－11号;
	//240－小四;260－13号;280－四号;
	//300－小三；320－三号
	cf.bCharSet=GB2312_CHARSET;
	lstrcpy(cf.szFaceName,L"宋体");

	m_pRichEdit->SetWordCharFormat(cf);
}

void ArxRleUiTdcSpaOutResult::SetFontColor(COLORREF rgb)
{
	CHARFORMAT cf;
	cf.dwMask=CFM_COLOR;
	cf.dwEffects=0;
	cf.crTextColor=rgb;
	m_pRichEdit->SetWordCharFormat(cf);
}

void ArxRleUiTdcSpaOutResult::SimplifyString(CString &cs)
{
	CString csTmp=cs;
	cs=L"";
	while(csTmp.Find(L".") > 0)
	{
		int i=csTmp.Find(L".");
		cs+=csTmp.Left(i+3);
		csTmp.Delete(0,i+3);
		if(csTmp.GetLength() < 4) break;
		csTmp.Delete(0,4);
	}
	cs+=csTmp;
	int i=cs.Find(L"：");
	while(i<20)
	{
		cs=L" "+cs;
		i++;
	}
}

/////////////////////////////////////////////////////////////////////////////
//c			  --  BEAM_MOMENT_GBJ10  --		             		    
//c     GB50010-2001受弯构件正截面配筋计算
//c-----------------------------------------------------------------
//c  输入参数：
//c             B/H: 截面腹板宽/截面总高(mm) 
//c  BFUI/HFUI/BHCU: 截面上翼缘宽/上翼缘高,钢筋合力点至边缘距离(mm)
//c  BFDI/HFDI/BHCD: 截面下翼缘宽/下翼缘高,钢筋合力点至边缘距离(mm)
//c			   SPAN: 计算跨度(mm)
//c			   FCUK: 混凝土强度等级C (N/mm2) 
//c			 FY/YFC: 纵向受拉筋/纵向受压筋 强度设计值(N/mm2)
//c			   ASCI: 输入的受压钢筋面积(mm2)
//c			   KZDJ: 抗震等级 (0-九度区/框支梁特一级,1,2,3,4,5-非抗震)
//c			   KZZH: 0--非地震组合；1--地震组合；2--人防设计
//c			     JM: 0--非箍筋加密区,1箍筋加密区,2--框支梁 
//c			   KLXL: 0--普通梁; 1--肋形梁; 
//c			     AM: 弯矩设计值(下腋缘受拉为+) M(kN-m)
//c--------------------------------------------------------------------
//c  输出结果：
//C          BFUE: 修整后的翼缘宽度(mm)
//C	       RE: 承载力抗震调整系数
//C            H0: 截面有效高度(mm)      
//C           ZMU: 截面极限最大弯矩设计值Mu(kN.m)      
//c   ARFA1/BATA1: 系数α1/系数β1
//C           XIE: 箍筋加密区抗震考虑受压钢筋计算的混凝土相对受压区高度ξe      
//C          XIEB: 箍筋加密区抗震容许的混凝土相对受压区高度ξbe
//c                注：当ξe>ξbe时截面不满足抗震要求，应加大截面      
//c	       XI: 截面混凝土的计算相对受压区高度ξ 
//c	      XIB: 截面混凝土的界限相对受压区高度ξb 
//c	       RO: 计算受拉钢筋配筋百分率ρ(%) As/A*100
//C                注：当RO>RMAX时表示超筋(配筋率大于最大配筋率)
//c	       RC: 计算受压钢筋配筋百分率ρc(%) Asc/A*100
//c	     RMAX: 最大受拉钢筋配筋百分率ρmax(%) 
//c	      AS1: 计算单排受拉钢筋面积(mm2) 
//c	      AS2: 计算双排受拉钢筋面积(mm2)
//c                注：当AS1，AS2=99999时表示超筋(设计弯矩AM>极限最大弯矩ZMU) 
//c	      ASC: 计算受压钢筋面积 (mm2) 
//c	    ASMIN: 受拉钢筋最小面积 (mm2) 
//c	   ASCMIN: 受压钢筋最小面积 (mm2) 
//c  注：设计受拉钢筋应取max(AS1,AS2,ASMIN), 设计受压钢筋应取max(ASC,ASCMIN)
//c                     
/////////////////////////////////////////////////////////////////////////////
extern "C" void __stdcall BEAM_MOMENT_GBJ10(float &B,float &H,float &BFUI,float &HFUI,
											float &BFDI,float &HFDI,float &BHCUI,float &BHCDI,float &SPAN,float &FCUK,float &FY,
											float &FYC,float &ASCI,long &KZDJ,long &KZZH,long &JM,long &KLXL,float &AM,
											float &BFUE,float &RE,float &H0,float &ZMU,float &ARFA1,float &BATA1,float &XIE,
											float &XIEB,float &XI,float &XIB,float &RO,float &RC,float &RMAX,float &AS1,float &AS2,
											float &ASC,float &ASMIN,float &ASCMIN);

/////////////////////////////////////////////////////////////////////////////
//c			  --  BEAM_MOMENT_TENSE_GBJ10  --		             		    c
//C   GB50010-2001偏拉构件(非对称配筋)正截面配筋计算
//c-----------------------------------------------------------------
//c  输入参数：
//c           B,H: 截面宽高(mm) width, height of section 
//c          BHCU: 受压钢筋合力点至边缘距离(mm)
//c          BHCD: 受拉钢筋合力点至边缘距离(mm)
//c	     FCUK: 混凝土强度等级C (N/mm2) 
//c	   FY/YFC: 纵向受拉筋/纵向受压筋 强度设计值(N/mm2)
//c	     KZDJ: 抗震等级 (0-九度区/框支梁特一级,1,2,3,4,5-非抗震)
//c	     KZZH: 0--非地震组合；1--地震组合；2--人防设计
//c	       JM: 0--非箍筋加密区,1箍筋加密区,2--框支梁 
//c	       XM: 弯矩设计值 M(kN-m)
//c	       XN: 轴力拉设计值(受拉为-) N(kN)
//c
//c  输出结果：
//C	       RE: 承载力抗震调整系数
//C            H0: 截面有效高度(mm)      
//c   ARFA1/BATA1: 系数α1/系数β1
//C           XIE: 箍筋加密区抗震考虑受压钢筋计算的混凝土相对受压区高度ξe      
//C          XIEB: 箍筋加密区抗震容许的混凝土相对受压区高度ξbe      
//c                注：当ξe>ξbe时截面不满足抗震要求，应加大截面      
//c	       XI: 截面混凝土的计算相对受压区高度ξ 
//c	      XIB: 截面混凝土的界限相对受压区高度ξb 
//c	       RO: 计算受拉钢筋配筋率ρ As/A
//c	       RC: 计算受压钢筋配筋率ρc Asc/A
//c	     RMAX: 最大受拉钢筋配筋率ρmax 
//C                注：当RO>RMAX时表示超筋(配筋率大于最大配筋率)
//c	      AS1: 计算单排受拉钢筋面积(mm2) 
//c	      AS2: 计算双排受拉钢筋面积(mm2) 
//c                注：当AS1，AS2=99999时表示超筋(设计弯矩AM>极限最大弯矩ZMU) 
//c	      ASC: 计算受压钢筋面积 (mm2) 
//c	    ASMIN: 受拉钢筋最小面积 (mm2) 
//c	   ASCMIN: 受压钢筋最小面积 (mm2) 
//c  注：设计受拉钢筋应取max(AS1,AS2,ASMIN), 设计受压钢筋应取max(ASC,ASCMIN)
extern "C" void __stdcall BEAM_MOMENT_TENSE_GBJ10(float &B,float &H,float &BHCUI,float &BHCDI,
												  float &FCUK,float &FY,float &FYC,long &KZDJ,long &KZZH,long &JM,float &AM,float &XN,
												  float &RE,float &H0,float &ARFA1,float &BATA1,float &XIE,
												  float &XIEB,float &XI,float &XIB,float &RO,float &RC,float &RMAX,float &AS1,float &AS2,
												  float &ASC,float &ASMIN,float &ASCMIN);

/////////////////////////////////////////////////////////////////////////////
//c			  --  SHEAR_TORSION_GBJ10  --				    c
//c	  GB50010-2001梁、柱、墙、板斜截面受剪/受扭/受剪扭 配筋计算  	                    c
//c-----------------------------------------------------------------
//c  输入参数：
//c	     IBCW: 1-梁，2-柱，3-墙，4-板, 5-框支柱, 6-框支梁, 7-墙连梁 
//c	      B/H: 截面腹板宽度(圆: 直径)/高度(圆:  0)
//c	  BFU/HFU: 受压区翼缘宽度(圆: 0)/高度(圆: 0)
//c	  BFD/HFD: 受拉区翼缘宽度(圆: 0)/高度(圆: 0)
//c          BHCX: 钢筋合力点至边缘距离(mm)
//c	     SPAN: 计算跨度(mm)
//c	    RMDλ: 剪跨比,梁均荷载取λ≤1; 柱λ=Hn/2ho; 剪力墙λ=M/Vho
//c	     FCUK: 混凝土强度等级C (N/mm2) 
//c	  FYV/FYB: 箍筋/弯起筋 强度设计值(N/mm2)
//c		    S: 箍筋间距 
//c	     KZDJ: 抗震等级 (0-九度区/框支梁特一级,1,2,3,4,5-非抗震)
//c	     KZZH: 0--非地震组合；1--地震组合；2--人防设计
//c	      ASB: 弯起钢筋面积 (mm2)
//c	      ARF: 弯起钢筋角度 (degree)
//c		   VX: X向(水平与截面宽度对应)剪力设计值 (kN)
//c		   VY: Y向(垂直与截面高度对应)剪力设计值 (kN)
//c		    T: 扭矩设计值(kN.m)
//c	       XN: 轴力设计值(kN)(+ 压,- 拉) 
//c	       PN: 预应力筋及非预应力筋的合力(+ 压,- 拉)(kN)
//c		 WZYB: 墙肢底截面轴压比(输入0自动按轴力计算)
//c
//c--------------------------------------------------------------------
//c  输出结果：
//C	       RE: 承载力抗震调整系数
//c         BATAH: 截面高度影响系数βh
//c         BATAT: 剪扭承载力降低系数βt
//c          R_HB: =99999:受剪截面超限(V/bho+T/Wt>0.25bho)
//c		 VMAX: 截面容许的最大剪应力(0.25fc或0.2fc或0.15fc)
//c          ASVT: 受剪扭总的计算箍筋面积 (Asv+2Ast1)(mm2)
//C			   剪力墙为水平分布筋面积(mm2)
//c          AST1: 受扭沿周边单肢箍筋面积(mm2)   
//c          ASTL: 计算受扭纵筋面积Astl(mm2),应沿截面周边均匀布置
//c        ASVMIN: 最小剪扭箍筋面积(=b.s.ρv) (mm2)
//C         RMINS: 梁箍筋/剪力墙水平分布筋/最小配筋率ρv
//C        RMINSW: 柱箍筋加密区/剪力墙约束边缘构件箍筋最小体积配筋率ρv
//c       ASTLMIN: 最小受扭纵筋面积 (b.s.ρtl  mm2) 
//c       K_YS_GZ: 0/1 剪力墙构造边缘构件/约束边缘构件
//c  注：设计箍筋应取max(ASVT,ASVMIN),且周边单肢箍筋面积应>AST1; 
//c      设计纵筋应取max(ASTL,ASTLMIN),且应与受弯纵筋迭加.
extern "C" void __stdcall SHEAR_TORSION_GBJ10(long &IBCW,float &B,float &H,float &BFU,
											  float &HFU,float &BFD,float &HFD,float &BHCX,float &RMD,float &SPAN,float &FCUK,
											  float &FYV,float &FY,float &S,long &KZDJ,long &KZZH,float &ASB,float &ARF,float &VY,
											  float &VX,float &T,float &XN,float &PN,float &WZYB,
											  float &RE,float &BATAH,float &BATAT,float &R_HB,float &RMINS,float &VMAX,float &ASVT,
											  float &ASVMIN,float &AST1,float &ASTL,float &ASTLMIN,float &RMINSW,float &K_YS_GZ);

/////////////////////////////////////////////////////////////////////////////
//c			  --  CRACK_WIDE_GBJ10  --
//c 计算最大裂缝宽度	     
//c-------------------------------------------------------------------
//c  输入参数：
//c           B,H: 截面宽高(mm)  
//c  BFU,HFU,BHCS: 截面上腋缘宽,高,钢筋合力点至边缘距离(mm)
//c  BFD,HFD,BHCX: 截面下腋缘宽,高,钢筋合力点至边缘距离(mm)
//c	     SPAN: 计算跨度(mm)
//c	     FCUK: 混凝土强度等级C(N/mm2) 
//c	       FY: 主筋强度设计值 fy(N/mm2)
//c	       AS: 受拉钢筋面积 As (mm2)
//c		  Deq: 受拉钢筋等效直径 deq(mm)
//c         Cover: 外层纵向受拉钢筋边缘至受拉区底边的距离(mm)
//c	       AN: 标准组合轴力   Nk(kN)  
//c	       AM: 标准组合弯矩   Mk(kN-m)
//c
//c	     Wmax: 最大裂缝宽度the width of crack (mm)
/////////////////////////////////////////////////////////////////////////////
extern "C" void __stdcall CRACK_WIDE_GBJ10(float &B,float &H,float &BFU,float &HFU,
										   float &BFD,float &HFD,float &BHCS,float &BHCX,float &SPAN,float &FCUK,float &FY,
										   float &AS,float &Deq,float &COVER,float &AN,float &AM,
										   float &ARF,float &PTE,float &XGM,float &FAI,float &WMAX);
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//c			  --  DEFLECTION_B --
//c------------------------------------------------------------------
//c  输入参数：
//c           B,H: 截面宽高(mm)  
//c  BFU,HFU,BHCX: 截面上腋缘宽,高,受拉钢筋合力点至边缘距离(mm)
//c       BFD,HFD: 截面下腋缘宽,高
//c	     SPAN: 计算跨度(mm)
//c	     FCUK: 混凝土强度等级C(N/mm2) 
//c	       FY: 主筋强度设计值 fy(N/mm2)
//c	       ASA: 受拉钢筋面积 As (mm2)
//c	      ASB: 受压钢筋面积As`(mm2)
//C	        U: 梁端支承系数(简支1,固端0.8,肋形梁固端0.65)
//c	      AMS: 标准组合弯矩Mk(kN-m)(下边受拉为+，上边受拉为-)   
//c	      AML: 准永久组合弯矩 Mq(kN-m)
//c--------------------------------------------------------------------
//c  输出结果：
//c	       Bs: 受弯构件的短期刚度Bs(kN/m2)
//c	       Bl: 受弯构件长期刚度Bl(kN/m2)
//c		    f: 受弯构件挠度值(mm)
//c	      fl0: 受弯构件相对挠度的倒数(lo/f)

/////////////////////////////////////////////////////////////////////////////
//	extern "C" void __stdcall DEFLECTION_B_GBJ10(float &B,float &H,float &BFU,float &HFU,
//		float &BFD,float &HFD,float &BHCX,float &SPAN,float &FCUK,float &FY,
//		float &ASA,float &ASB,float &U,float &AMS,float &AML,
//		float &PTE,float &SITA,float &BS,float &BL,float &F,float &FL0);


/////////////////////////////////////////////////////////////////////////////
//c		 --- COLUMN_UNIMOMENT 
//c GB50010-2001/ACI318-1998/BS8110 柱/剪力墙单向偏心受力正截面配筋计算
//c-------------------------------------------------------------------
//c  输入参数：
//C    	NCODE: 规范类别（1-GBJ；2-BS8110；3-TW;4-ACI）
//c	    I_C_W: 0--柱,1--剪力墙
//c       B/H: 截面腹板宽(圆=直径D)/截面总高(mm)(圆=0) 
//c   BFU/HFU: 截面上翼缘宽(圆=0)/上翼缘高,钢筋合力点至边缘距离(mm)(圆=0)
//c   BFD/HFD: 截面下翼缘宽(圆=0)/下翼缘高,钢筋合力点至边缘距离(mm)(圆=0)
//c      BHCX: 钢筋合力点至边缘距离(mm)
//c	  XLE/YLE: 柱弯矩平面内/弯矩平面外的计算长度
//c	     FCUK: 混凝土强度等级C (N/mm2) 
//c	   FY/FYW: 纵向主筋/腹板纵向分布钢筋 强度设计值(N/mm2)
//c	      RWV: 腹板纵向分布钢筋配筋率 ρv(%)
//c	     KZDJ: 抗震等级 (0-九度区,1,2,3,4,5-非抗震)
//c	     KZZH: 0--非地震组合；1--地震组合；2--人防设计
//c	      KCY: 1--计算偏心距增大系数η,0--不计算偏心距增大系数η=1 
//c	      KJZ: 0--普通柱;1--角柱或框支柱 
//c	     JQBW: 0--非剪力墙墙加强区;1--剪力墙墙加强区 
//c	       XN: 轴力设计值(+压,-拉)(kN)
//c	       XM: 弯矩设计值(kN)
//c	     WZYB: 重力荷载代表值作用下墙轴压比(N/fcAw)(输入0时由程序计算)
//c        WC: 混凝土容重(ACI/TW用,普通混凝土=2300)
//c
//c  输出结果：
//c	   FAIMIN: 轴心受压构件稳定系数φ
//c        RE: 正截面承载力抗震调整系数γRE:'      
//c	       XI: 计算相对受压区高度ξ
//C        AT: 偏心矩增大系数 η     
//c	      ZYB: 轴压比(N/fcA)
//c	       RO: 全截面计算配筋率(2*As+Asw)/A
//c	     RMAX: 全截面容许最大配筋率ρmax
//c	    RMINL: 全截面最小配筋率ρmin/剪力墙取一侧边缘约束(暗柱)的最小配筋率
//c	      ASX: 单边计算配筋面积(圆为全截面/2) As(mm2)
//c	    ASMIN: 全截面最小配筋面积(mm2),剪力墙取一侧暗柱的最小配筋面积
//c	      ASA: 按轴压计算的全截面配筋面积 (mm2)
//c	      FN0: 对应截面形心的轴力设计值,(kN)
//c	      XM0: 对应形心主轴X的矢量弯矩设计值(kN.m)
//c	      FAI: 配筋中调整后的强度折减系数(ACI/TW)
extern "C" void __stdcall COLUMN_UNIMOMENT(long &NCODE,long &I_C_W,float &B,float &H,
										   float &BFU,float &HFU,float &BFD,float &HFD,float &BHCX,float &XLE,float &YLE,
										   float &FCUK,float &FY,float &FYW,float &RWV,long &KZDJ,long &KZZH,long &KCY,
										   long &KJZ,long &JQBW,float &WZYB,float &WC,float &XN,float &XM,
										   float &FAIMIN,float &RE,float &XI,float &FC,float &FCS,float &AT,float &ZYB,
										   float &RO,float &RMAX,float &RMINL,float &ASX,float &ASMIN,float &ASA,
										   float &FN0,float &FMX0,float &FAI);

/////////////////////////////////////////////////////////////////////////////
//c		 --- COLUMN_BIMOMENT 
//c  GB50010-2001/ACI318/BS8110 柱双偏压配筋计算 --
//c-------------------------------------------------------------------
//c  输入参数：
//C   		NCODE: 规范类别（1-GBJ；2-BS8110；3-TW;4-ACI）
//C		N_COMBINE: 内力组合总组数
//C	   FORCE(4,*): 内力数组 
//c	            1: 对应截面形心的轴力设计值(+压,-拉)(kN)
//c	            2: 对应形心主轴X的矢量弯矩设计值(kN.m)
//c	            3: 对应形心主轴Y的矢量弯矩设计值(kN.m)
//c	            4: 1/0--是/否地震组合
//C             B: 截面宽度(mm)   
//C             H: 截面高度(mm)   
//C           BFU: 上翼缘宽度(mm)(十字形时为水平肢宽度)
//C           HFU: 上翼缘高度(mm) 
//C           BFD: 下翼缘宽度(mm) (十字形时为0)
//C           HFD: 下翼缘高度(mm) 
//C           DFU: 上翼缘位置(mm)(偏离中心线的距离,右偏为正,左偏为负)
//C           DFD: 下翼缘位置(mm)(十字形时为水平肢离上端距离)
//C          BHCX: 边缘至钢筋合力点距离(mm)
//c		  XLE,YLE: 对应XM弯距计算长度XLE(mm),对应YM弯距的计算长度YLE(mm) 
//c	         CITA: 形心主轴X与截面宽度方向的夹角(弧度)
//c	           FY: 主筋强度设计值 fy(N/mm2)
//c	         FCUK: 混凝土强度(N/mm2)(GBJ--等级C; BS8110--fcu; ACI/TW--fc') 
//c            WC: 混凝土容重(ACI/TW用,普通混凝土=2300)
//c	         KZDJ: 抗震等级 (0-九度,1,2,3,4,5-非抗震)
//c	         KZZH: 0--非地震组合；1--地震组合；2--人防设计
//c	          KCY: 1--计算偏心距增大系数η/0--不计算偏心距增大系数η=1 
//c	          KJZ: 0--普通柱/1--角柱或框支柱 
//C	         KZDG: 矩形截面是否指定钢筋根数（0否/2是）
//c  注: 当已知配筋作截面验算时,取KZDG=2,并输入NO_X,NO_Y,ASC,ASX,ASY的值,
//c      判断输出的全截面配筋率ρ大于原输入配筋率0.1%时,表示原截面配筋不足
//c								   
//c  输出结果：
//c			 ASC: 单根角筋面积 (mm2)
//c			 ASX: 矩形上下边单侧计算配筋面积(不含角筋)/异型固定筋面积(mm2)
//c			 ASY: 矩形边单侧计算配筋面积(不含角筋)/异型附加分布筋面积(mm2)
//c    NO_X/NO_Y: 矩形 上下/左右 钢筋根数（不含角筋）
//c               异型 固定筋/附加分布筋根数
//c      ASTOTAL: 全截面总计算配筋面积
//C           Rs: 全截面计算配筋率 ρ:'      
//c         RMAX: 全截面容许最大配筋率ρmax
//c		   RMINL: 全截面最小配筋率ρmin
//c	       ASMIN: 全截面最小配筋面积(mm2), 
//c	         ZYB: 轴压比(N/fc/A)
//c	      FAIMIN: 轴心受压构件稳定系数φ
//c  ASX_MAX/ASY_MAX/ASC_MAX: 矩形 宽度方向/高度方向/单根角筋 最大配筋面积(mm2)
//c                           异型 固定位置筋/附加分布筋 最大配筋面积(mm2)
//c XN_X,XM_X,YM_X: 对应全截面最大配筋ASTOTAL的内力
//c       N_ASXMAX: 对应ASTOTAL的内力组合号
//c         KZZH_X: 对应内力N_ASXMAX的地震组合信息(0/1)
extern "C" void __stdcall COLUMN_BIMOMENT(long &NCODE,long &N_COMBINE,float *FORCE,
										  float &B,float &H,float &BFU,float &HFU,float &BFD,float &HFD,float &BHCX,
										  float &DFU,float &DFD,float &XLE,float &YLE,float &CITA,float &FY,float &FCUK,
										  float &WC,long &KZDJ,long &KCY,long &KJZ,long &KZDG,float &FCS,float &FC,
										  float &ASC,float &ASX,float &ASY,long &NO_X,long &NO_Y,float &ASTOTAL,float &RS,
										  float &ATX,float &ATY,float &FAIMIN,float &ASA,float &ZYB,float &Asmin,float &RE,
										  float &RMINL,float &RMAX,long &KIND,float &FI);

/////////////////////////////////////////////////////////////////////////////
//c		 --- CIRCLE_GBJ10 
//c  GB50010-2001/ACI318/BS8110 圆形截面正截面计算 --
//c-------------------------------------------------------------------
extern "C" void __stdcall CIRCLE_GBJ10(float &Mx,float &N,float &B,float &Bhcs,
									   float &Span,float &Fcuk,float &Fy,long &Kzdj,long &Kzzh,long &Klxl,long &Kcy,
									   float &ARF,float &RO,float &RMAX,float &ASX1,float &ASA,float &ASMIN,float &ZYB,
									   float &RE,float &ATA,float &FC,float &FCS,float &FAI);

/////////////////////////////////////////////////////////////////////////////
extern "C" void __stdcall COLUMN_UNIMOMENT_GBJ10(long &I_C_W,float &B,float &H,float &Bfu,
												 float &Hfu,float &Bfd,float &Hfd,float &Bhcx,float &Elx,float &Ely,float &Fcuk,float &Fy,
												 float &Fyw,float &Ro,long &Kzdj,long &Kzzh,long &Kcy,long &KJZ,long &Klxl,float &N,
												 float &Mx,float &Wzyb,
												 float &FAIMIN,float &RE,float &XI,float &FC,float &FCS,float &AT,float &ZYB,
												 float &RO,float &RMAX,float &RMINL,float &ASX,float &ASMIN,float &ASA);

float Bhcs, Bhcx;
float Fyw, Xm, Xn,Fcuk;
int Kzjm, Kxjm, Kzzh, Khzz, Kcy; 
float Wzyb, Vy, Vx, Pn, Mx, My;
float GjXz,Cover,Deq,Nk,Mk,Mq;
BOOL bNaoDu,bWidth;
BOOL bSigleOrDouble;
float Dfd, Dfu, Elx, Ely, Dimx, Dimy, Dimc;

float B, H, Bfu, Hfu, Bfd, Hfd, Asu, Asd, Span, Fy, Fyc, Fyv, M, N, V, Tt, e0;
BOOL bWan, bXjm, bEq, bNiu, bLa ,bJLoad, bDuiCh, bJunY;
int kFcuk,Klxl, Kzdj, KJmLx;
float Rmd, Arf, S, Asa, Asb ,Ro,pmin;
CString csTringFy,csTringFyc,csTringFyv;

//extern void Beam_Moment_WanJu(float &b,float &h,float &Bfu,float &Hfu,float &Bfd,float &Hfd,
//			float &asu,float &asd,float &Span,int &Fcuk,CString &csTringFy,CString &csTringFyc,
//			float &Asc,float &pmin0,BOOL &bWan,BOOL &bLa,BOOL &bNiu,BOOL &bXjm,BOOL &bEq,int &Kzdj,
//			int &Klxl,float &Ro,float &M,float &N,float &V,float &T);

void ArxRleUiTdcSpaOutResult::ShowBeamSectionText()
{

	Beam_Design(KJmLx,B,H,Bfu,Hfu,Bfd,Hfd,Asu,Asd,Span,e0,kFcuk
		,csTringFy,csTringFyc,csTringFyv,Asa,Asb,Arf,S,pmin,
		bWan,bLa,bNiu,bXjm,bEq,bJLoad, bDuiCh, bJunY,
		Kzdj,Klxl,Rmd, Ro,M,N,V,Tt);
}

void ArxRleUiTdcSpaOutResult::ShowBeamCracksText()
{

}

void ArxRleUiTdcSpaOutResult::ShowColumnStrengthText()
{

}

void ArxRleUiTdcSpaOutResult::ShowCircleStrengthText()
{

}

void ArxRleUiTdcSpaOutResult::ShowWallStrengthText()
{

}

void ArxRleUiTdcSpaOutResult::Beam_Design(int KJmLx,int b,int h,int Bfu,int Hfu,int Bfd,int Hfd,
								int asu,int asd,int Span,float e0,int Fcuk,CString csTringFy,CString csTringFyc,CString csTringFyv,
								float Asc,float Asb,float Arf,float S,float pmin0,BOOL bWan,BOOL bLa,BOOL bNiu,
								BOOL bXjm,BOOL bEq,BOOL bJLoad, BOOL bDuiCh, BOOL bJunY,int Kzdj,
								int Klxl,float Rmd,float Ro,float M,float N,float V,float Tt)
{
	SetCenter();
	SetFontSize(280);
	m_pRichEdit->ReplaceSel(L"粱构件设计\n");
	m_pRichEdit->ReplaceSel(L"\n");
	SetLeft();
	SetFontSize(240);
	m_pRichEdit->ReplaceSel(L"Ⅰ、输入参数：\n\n");

	CString csText,csData;
	SetFontSize(200);
	csText.Format(L"混凝土强度等级：C%d    fc = %fN/mm    ft = %fN/mm\n",Fcuk,GetConcretFc(Fcuk),GetConcretFt(Fcuk));
	m_pRichEdit->ReplaceSel(csText);

	csText.Format(L"受拉钢筋强度设计值：fy = %fN/mm    Es = %fN/mm\n",GetGjKanglaFy(csTringFy),GetGjKanglaEs(csTringFy));
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);

	if(Asc != 0)
	{
		csText.Format(L"受压钢筋面积：As' = %fmm2    受压钢筋强度设计值：fy = %fN/mm    Es = %fN/mm\n",Asc,GetGjKanglaFy(csTringFyc),GetGjKanglaEs(csTringFyc));
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}

	csText.Format(L"结构重要性系数：γo = %f\n",Ro);
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);

	int h0=h-asd;
	int hw=h0;

	if(bWan)
	{
		csText.Format(L"弯矩设计值：M = %fkN·M\n",M);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}
	if(bLa)
	{
		csText.Format(L"拉力设计值：N = %fKN\n",N);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);

		csText.Format(L"轴向拉力作用点至截面重心的距离：e0 = %fmm\n",e0);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);

		if(bDuiCh)
		{
			csText=L"对称配筋\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	
		}
		else if(bJunY) 
		{
			csText=L"纵向钢筋沿腹部均匀布置\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);
		}
	}
	if(bXjm)
	{
		csText.Format(L"剪力设计值：V = %fkN\n",V);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
		if(KJmLx==0) hw=h0;//矩形
		else if(KJmLx==1||KJmLx==3)hw=h0-Hfd;//倒T形 倒L形
		else if(KJmLx==2) hw=h0-Hfu;//T形
		else if(KJmLx==4) hw=H-Hfu-Hfd;//工形
	}
	if(bNiu)
	{
		csText.Format(L"扭距设计值：T = %fkN\n",T);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}

	if(KJmLx==0||KJmLx==1)
	{
		if(KJmLx==0)
			csText.Format(L"矩形截面尺寸：b * h = %d*%d    h0 = %d-%d=%dmm\n",b,h,h,asd,h0);
		else
			csText.Format(L"倒T形截面尺寸：b * h = %d*%d    h0 = %d-%d=%dmm\n",b,h,h,asd,h0);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}
	float ybxsb=0;
	float bta1=0;
	if(Fcuk<=50) bta1=0.8f;
	else if(Fcuk>=80) bta1=0.74f;
	else
	{
		//线性内插法求bta1
	}

	float Ecu=0.0033f-0.5f*(GetConcretFck(Fcuk)-50)*1e-5f;
	ybxsb=bta1/(1+GetGjKanglaFy(csTringFy)/GetGjKanglaEs(csTringFy)/Ecu);
	csText=L"相对界限受压区高度：ξb = β1 / (1 + fy / Es / εcu)    (GB50010  7-1-4-1) \n                                      = ";
	csData.Format(L"%f/(1+%f/%f/%f) = %f\n",bta1,GetGjKanglaFy(csTringFy),GetGjKanglaEs(csTringFy),Ecu,ybxsb);
	SimplifyString(csText+csData);
	m_pRichEdit->ReplaceSel(csText+csData);

	m_pRichEdit->ReplaceSel(L"\n\n");
	SetFontSize(240);
	m_pRichEdit->ReplaceSel(L"Ⅱ、计算结果：\n\n");
	SetFontSize(200);

	float a1=0;
	if(Fcuk<=50) a1=1;
	else if(Fcuk>=80) a1=0.94f;
	else
	{
		//线性内插法求bta1
	}

	float ft=GetConcretFt(Fcuk);
	float fc=GetConcretFc(Fcuk);
	float fy=GetGjKanglaFy(csTringFy);
	float fyc=GetGjKanglaFyc(csTringFyc);
	float fyv=GetGjKanglaFy(csTringFyv);

	M*=1000000;
	V*=1000;
	Tt*=1000000;
	N*=1000;

	if(bWan)
	{
		m_pRichEdit->ReplaceSel(L"1、正截面受弯配筋计算：\n\n");
		if(KJmLx==0||KJmLx==1)//矩形或翼缘位于受拉边的倒T形截面
		{
			if(Span/h >= 5.0)
			{
				csText=L"矩形或翼缘位于受拉边的倒T形截面：按如下方法计算\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);
			}
			else
			{
				csText=L"深受弯构件：按如下方法计算\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);			
			}
		}
		else
		{
			csText=L"T形 倒L形 工形截面：按如下方法计算\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);		
		}
		if(KJmLx==0||KJmLx==1)//矩形或翼缘位于受拉边的倒T形截面
		{
			if(Span/h >= 5.0)
				Beam_Moment_Rectangle(Ro,M,b,h,asd,asu,fc,ft,a1,fy,fyc,Asc,ybxsb,pmin0);
			else
			{
				//深受弯构件
			}
		}
		else if(KJmLx==2||KJmLx==3||KJmLx==4)
		{
			int bf=Bfu;//翼缘计算宽度
			if(KJmLx==3) //倒L形
			{
				//				if(hfu/(h-asd)<0.1 && hfu/(h-asd)>0.05) bf1=b+5*hfu;
				//				else if(hfu/(h-asd) < 0.05) bf1=
				bf=Span/6<b+5*Hfu ? Span/6:b+5*Hfu;
				csText=L"倒L形截面：bf'= min{ lo/6 , b+5*hf'} = ";
			}
			else
			{
				if(Klxl==0) //独立粱
				{
					int bf1;
					if(Hfu/(h-asd)<0.1 && Hfu/(h-asd)>=0.05) bf1=b+6*Hfu;
					else if(Hfu/(h-asd) < 0.05) bf1=b;
					else bf1=b+12*Hfu;

					bf=Span/3<bf1 ? Span/3:bf1;
					csText=L"独立粱T形或I形截面：bf'= min{ lo/3 , 按hf'考虑的bf'} = min{";
					csData.Format(L"%d, %d} = ",Span/3,bf1);
				}
				else 
				{
					bf=Span/3<b+12*Hfu ? Span/3:b+12*Hfu ;//肋形粱
					csText=L"肋形粱T形或I形截面：bf'= min{ lo/3 , b+12hf'} = ";
				}
			}
			csData.Format(L"%d",bf);
			csText+=csData+L"mm    (GB50010  7-2-3)\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);
			Beam_Moment_TSharp(Ro,M,b,h,bf,Hfu,asd,asu,fc,ft, a1,fy,fyc,Asc,ybxsb,pmin0);
		}
	}
	if(bXjm)
	{
		Beam_Vector(V,b,h,hw,asd,Fcuk,fc,ft,fy,Asb,Arf,Rmd,S,fyv,Klxl,bJLoad);
	}
	if(bLa)
	{

	}

	m_pRichEdit->ReplaceSel(L"\n\n\n\n\n");
}

//矩形或翼缘位于受拉边的倒T形截面受弯构件
//Ro――结构重要性系数
//M――弯距设计值
//b ―― 矩形宽或腹板宽
//h0 ――计算高度
//asu ――受压区纵向普通钢筋合力点
//Fc －－混凝土轴心抗压强度设计值
//Ft －－混凝土轴心抗拉强度设计值
//a1 ――系数
//fy ――受拉筋抗拉强度设计值
//fy' ――受压筋抗压强度设计值
//As' ――受压筋截面面积
//Ξb ――相对界限受压区高度
//Ρmin0 ――输入的最小配筋率
void ArxRleUiTdcSpaOutResult::Beam_Moment_Rectangle(float Ro,float M,int b,int h,int asd,int asu,float Fc,
										  float Ft, float a1,float Fy,float Fyc,float Asc,float ybxsb,float pmin0)
{
	//受压区高度
	//x=2*h0-2*(Ro*M-fy'*As'(h0-as'))/(a1*fc*b)
	//if(As'!=0) {
	//x<=2as'
	//}
	//相对受压区高度 ξ=x/h0  
	CString csText,csData;

	float As=0;
	float x;//受压区高度
	int h0=h-asd;
	//	x=2*-2*(Ro*M-Fy*Asc*((h-asd)-asu))/(a1*Fc*b);//7.2.1-1
	x=(h0)-sqrt((h0)*(h0)-2*Ro*M/(a1*Fc*b));
	csText=L"受压区高度：x = ho - ( ho^2 - 2 * γo * M / (α1 * fc * b))^0.500000		(GB50010  7-2-1-1)\n                                      = ";
	//"β1 / (1 + fy / Es / εcu) = ";
	csData.Format(L"%d",h0);
	csText+=csData+L"-(";
	csData.Format(L"%d",h0);
	csText+=csData+L"^";
	csData.Format(L"%d",2);
	csText+=csData+L"-2*";
	csData.Format(L"%f",Ro);
	csText+=csData+L"*";
	csData.Format(L"%f",M);
	csText+=csData+L"/(";
	csData.Format(L"%f",a1);
	csText+=csData+L"*";
	csData.Format(L"%f",Fc);
	csText+=csData+L"*";
	csData.Format(L"%d",b);
	csText+=csData+L"))^0.500000\n                                      = ";
	csData.Format(L"%f",x);
	csText+=csData+L"mm";

	BOOL bAsCal=FALSE;
	if(Asc!=0)
	{
		if(x<2*asu)//7.2.1-4
		{
			csText+=L" < 2*as' = ";
			csData.Format(L"%f",2*asu);
			csText+=csData+L"mm\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);

			As=M/Fy*((h0)-asu);//7.2.5
			csText=L"受拉钢筋面积：As = M/fy*(h0-as')			(GB50010  7-2-5)\n                                      = ";
			//"β1 / (1 + fy / Es / εcu) = ";
			csData.Format(L"%f",M);
			csText+=csData+L"/";
			csData.Format(L"%f",Fy);
			csText+=csData+L"*(";
			csData.Format(L"%d",(h0));
			csText+=csData+L"-";
			csData.Format(L"%f",asu);
			csText+=csData+L") = ";
			csData.Format(L"%f",As);
			csText+=csData+L"mm2\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);

			x=(Fy*As-Fyc*Asc)/(a1*Fc*b);//7.2.1-2
			csText=L"受压区高度：x = (fy*As-fy'*As')/(a1*fc*b)		(GB50010  7-2-1-2)\n                                      = (";
			//"β1 / (1 + fy / Es / εcu) = ";
			csData.Format(L"%f",Fy);
			csText+=csData+L"*";
			csData.Format(L"%f",As);
			csText+=csData+L"-";
			csData.Format(L"%f",Fyc);
			csText+=csData+L"*";
			csData.Format(L"%f",Asc);
			csText+=csData+L")/(";
			csData.Format(L"%f",a1);
			csText+=csData+L"*";
			csData.Format(L"%f",Fc);
			csText+=csData+L"*";
			csData.Format(L"%d",b);
			csText+=csData+L" = ";
			csData.Format(L"%f",x);
			csText+=csData+L"mm";			

			if(x > ybxsb*(h0))//7.2.1-3
			{
				SetFontColor(RGB(255,0,0));
				csText+=L" > ξb*h0 = ";
				csData.Format(L"%f",ybxsb);
				csText+=csData+L"*";
				csData.Format(L"%d",(h0));				
				csText+=csData+L"mm\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);				
				csText=csData+L"请加大截面或提高混凝土强度\n";
				m_pRichEdit->ReplaceSel(csText);
				SetFontColor(RGB(0,0,0));
				return;
			}
			else
			{
				csText+=L" <= ξb*h0 = ";
				csData.Format(L"%f",ybxsb);
				csText+=csData+L"*";
				csData.Format(L"%f",(h0));				
				csText+=csData+L"mm\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);	
				bAsCal=TRUE;
			}
		}
	}

	if(!bAsCal)
	{
		if(x > ybxsb*(h0))//7.2.1-3
		{
			SetFontColor(RGB(255,0,0));
			csText+=L" > ξb*h0 = ";
			csData.Format(L"%f",ybxsb);
			csText+=csData+L"*";
			csData.Format(L"%f",(h0));				
			csText+=csData+L"mm\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);				

			csText=csData+L"请加大截面或提高混凝土强度\n";
			m_pRichEdit->ReplaceSel(csText);
			SetFontColor(RGB(0,0,0));
			return;
		}
		else
		{
			csText+=L" <= ξb*h0 = ";
			csData.Format(L"%f",ybxsb);
			csText+=csData+L"*";
			csData.Format(L"%d",(h0));				
			csText+=csData+L" = ";
			csData.Format(L"%f",ybxsb*(h0));				
			csText+=csData+L"mm\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	

			As=(a1*Fc*b*x+Fyc*Asc)/Fy;//7.2.1-2
			csText=L"受拉钢筋面积：As = (a1*fc*b*x+fy'*As')/fy		(GB50010  7-2-1-2)\n                        = (";
			csData.Format(L"%f",a1);
			csText+=csData+L"*";
			csData.Format(L"%f",Fc);
			csText+=csData+L"*";
			csData.Format(L"%d",b);
			csText+=csData+L"*";
			csData.Format(L"%f",x);
			csText+=csData+L"+";
			csData.Format(L"%f",Fyc);
			csText+=csData+L"*";
			csData.Format(L"%f",Asc);
			csText+=csData+L")/";
			csData.Format(L"%f",Fy);
			csText+=csData+L" = ";
			csData.Format(L"%f",As);
			csText+=csData+L"mm2\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	
		}
	}
	float tmp=45*Ft/Fy;
	//最小配筋率ρmin
	float pmin=max(pmin0,tmp);
	csText=L"最小配筋率：ρmin = max(ρpmin,0.450000*Ft/Fy) = max(";
	csData.Format(L"%f",pmin0);
	csText+=csData+L"%,";
	csData.Format(L"%f",tmp);
	csText+=csData+L"%) = ";
	csData.Format(L"%f",pmin);
	csText+=csData+L"%\n";
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);	

	//配筋率ρ
	float p=As/b/h*100;
	csText=L"配筋率：ρ = As/b/h = ";
	csData.Format(L"%f",As);
	csText+=csData+L"/";
	csData.Format(L"%d",b);
	csText+=csData+L"/";
	csData.Format(L"%d",h);
	csText+=csData+L" = ";
	csData.Format(L"%f",p);
	csText+=csData+L"%";;
	if(p < pmin )
	{
		csText+=L" < ρmin =";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);

		csText=L"ρ 取 ";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}
	else
	{
		csText+=L" >= ρmin =";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	
	}

	//最小配筋面积
	float Asmin = b * h * pmin /100;

	csText=L"最小配筋面积：Asmin = b * h * ρmin = ";
	csData.Format(L"%d",b);
	csText+=csData+L"*";
	csData.Format(L"%d",h);
	csText+=csData+L"*";
	csData.Format(L"%f",pmin);
	csText+=csData+L"% = ";
	csData.Format(L"%f",Asmin);
	csText+=csData+L"mm2";
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);	
}

void ArxRleUiTdcSpaOutResult::Beam_Moment_TSharp(float Ro,float M,int b,int h,int bfc,int hfc,
									   int asd,int asu,float Fc,float Ft, float a1,float Fy,float Fyc,float Asc,
									   float ybxsb,float pmin0)
{
	CString csText,csData;

	float As=0;
	float x;//受压区高度
	int h0=h-asd;

	csText=L"先按b0*bf'的大矩形算：\n";
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);

	x=h0-sqrt(h0*h0-2*(Ro*M-Fyc*Asc*(h0-asu))/(a1*Fc*bfc));
	csText=L"受压区高度：x = ho-{ho^2 - 2*[γo*M-fy'*As'*(ho-as')] / (α1*fc*bf')}^0.500000		(GB50010  7-2-1-1)\n                                      = ";
	//"β1 / (1 + fy / Es / εcu) = ";
	csData.Format(L"%d",h0);
	csText+=csData+L"-{";
	csData.Format(L"%d",h0);
	csText+=csData+L"^";
	csData.Format(L"%d",2);
	csText+=csData+L"-2*[";
	csData.Format(L"%f",Ro);
	csText+=csData+L"*";
	csData.Format(L"%f",M);
	csText+=csData+L"-";
	csData.Format(L"%f",Fyc);
	csText+=csData+L"*";
	csData.Format(L"%f",Asc);
	csText+=csData+L"*(";
	csData.Format(L"%d",h0);
	csText+=csData+L"-";
	csData.Format(L"%d",asu);
	csText+=csData+L")] / (";
	csData.Format(L"%f",a1);
	csText+=csData+L"*";
	csData.Format(L"%f",Fc);
	csText+=csData+L"*";
	csData.Format(L"%d",bfc);
	csText+=csData+L")}^0.500000\n                                      = ";
	csData.Format(L"%f",x);
	csText+=csData+L"mm";

	if(x > ybxsb*(h0))//7.2.1-3
	{
		SetFontColor(RGB(255,0,0));
		csText+=L" > ξb*h0 = ";
		csData.Format(L"%f",ybxsb);
		csText+=csData+L"*";
		csData.Format(L"%f",(h0));				
		csText+=csData+L"mm\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);				

		csText=csData+L"请加大截面或提高混凝土强度\n";
		m_pRichEdit->ReplaceSel(csText);
		SetFontColor(RGB(0,0,0));
		return;
	}
	else
	{
		csText+=L" <= ξb*h0 = ";
		csData.Format(L"%f",ybxsb);
		csText+=csData+L"*";
		csData.Format(L"%d",(h0));				
		csText+=csData+L" = ";
		csData.Format(L"%f",ybxsb*(h0));				
		csText+=csData+L"mm\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	
	}
	if(x > hfc)
	{
		csText=L" x ＞ hf'，所以：应考虑腹板的受压作用，重新计算受压区高度x\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);

		x=h0-sqrt(h0*h0-2*(Ro*M-Fyc*Asc*(h0-asu)-a1*Fc*(bfc-b)*hfc*(h0-hfc/2))/(a1*Fc*bfc));
		csText=L"受压区高度：x = ho-{ho^2 - 2*[γo*M-fy'*As'*(ho-as')-α1*fc*(bf'-b)*hf'*(ho-hf'/2)] / (α1*fc*b)}^0.500000		(GB50010  7-2-2-2)\n                                      = ";
		//"β1 / (1 + fy / Es / εcu) = ";
		csData.Format(L"%d",h0);
		csText+=csData+L"-{";
		csData.Format(L"%f",h0);
		csText+=csData+L"^";
		csData.Format(L"%d",2);
		csText+=csData+L"-2*[";
		csData.Format(L"%f",Ro);
		csText+=csData+L"*";
		csData.Format(L"%f",M);
		csText+=csData+L"-";
		csData.Format(L"%f",Fyc);
		csText+=csData+L"*";
		csData.Format(L"%f",Asc);
		csText+=csData+L"*(";
		csData.Format(L"%d",h0);
		csText+=csData+L"-";
		csData.Format(L"%d",asu);
		csText+=csData+L")-";
		csData.Format(L"%f",a1);
		csText+=csData+L"*";
		csData.Format(L"%f",Fc);
		csText+=csData+L"*(";
		csData.Format(L"%d",bfc);
		csText+=csData+L"-";
		csData.Format(L"%d",b);
		csText+=csData+L")*";
		csData.Format(L"%d",hfc);
		csText+=csData+L"*(";
		csData.Format(L"%d",hfc);
		csText+=csData+L"*(";
		csData.Format(L"%d",h0);
		csText+=csData+L"-";
		csData.Format(L"%d",hfc);
		csText+=csData+L"/";
		csData.Format(L"%d",2);
		csText+=csData+L")] / (";
		csData.Format(L"%f",a1);
		csText+=csData+L"*";
		csData.Format(L"%f",Fc);
		csText+=csData+L"*";
		csData.Format(L"%d",bfc);
		csText+=csData+L")}^0.500000\n                                      = ";
		csData.Format(L"%f",x);
		csText+=csData+L"mm";

		if(x > ybxsb*(h0))//7.2.1-3
		{
			SetFontColor(RGB(255,0,0));
			csText+=L" > ξb*h0 = ";
			csData.Format(L"%f",ybxsb);
			csText+=csData+L"*";
			csData.Format(L"%f",(h0));				
			csText+=csData+L"mm\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);				

			csText=csData+L"请加大截面或提高混凝土强度\n";
			m_pRichEdit->ReplaceSel(csText);
			SetFontColor(RGB(0,0,0));
			return;
		}
		else
		{
			csText+=L" <= ξb*h0 = ";
			csData.Format(L"%f",ybxsb);
			csText+=csData+L"*";
			csData.Format(L"%d",(h0));				
			csText+=csData+L" = ";
			csData.Format(L"%f",ybxsb*(h0));				
			csText+=csData+L"mm\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	

			As=(a1*Fc*(b*x+(bfc-b)*hfc)+Fyc*Asc)/Fy;//7.2.1-2
			csText=L"受拉钢筋面积：As = {α1*fc*[b*x+(bf'-b)*hf']+fy'*As'} / fy		(GB50010  7-2-2-3)\n	                       = {";
			csData.Format(L"%f",a1);
			csText+=csData+L"*";
			csData.Format(L"%f",Fc);
			csText+=csData+L"*[";
			csData.Format(L"%d",b);
			csText+=csData+L"*";
			csData.Format(L"%f",x);
			csText+=csData+L"+(";
			csData.Format(L"%d",bfc);
			csText+=csData+L"-";
			csData.Format(L"%d",b);
			csText+=csData+L")*";
			csData.Format(L"%d",hfc);
			csText+=csData+L"]+";
			csData.Format(L"%f",Fyc);
			csText+=csData+L"*";
			csData.Format(L"%f",Asc);
			csText+=csData+L"}/";
			csData.Format(L"%f",Fy);
			csText+=csData+L" = ";
			csData.Format(L"%f",As);
			csText+=csData+L"mm2\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	
		}
	}
	else//x<hf'时
	{
		As=(a1*Fc*bfc*x+Fyc*Asc)/Fy;//7.2.1-2
		csText=L"受拉钢筋面积：As = (α1*fc*bf'*x+fy'*As') / fy		(GB50010  7-2-1-2)\n                        = (";
		csData.Format(L"%f",a1);
		csText+=csData+L"*";
		csData.Format(L"%f",Fc);
		csText+=csData+L"*";
		csData.Format(L"%d",bfc);
		csText+=csData+L"*";
		csData.Format(L"%f",x);
		csText+=csData+L")/";
		csData.Format(L"%f",Fy);
		csText+=csData+L" = ";
		csData.Format(L"%f",As);
		csText+=csData+L"mm2\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);			
	}

	//配筋率ρ
	float p=As/b/h0*100;
	csText=L"配筋率：ρ = As/b/h0 = ";
	csData.Format(L"%f",As);
	csText+=csData+L"/";
	csData.Format(L"%d",b);
	csText+=csData+L"/";
	csData.Format(L"%d",h0);
	csText+=csData+L" = ";
	csData.Format(L"%f",p);
	csText+=csData+L"%";;
	if(p < pmin )
	{
		csText+=L" < ρmin =";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);

		csText=L"ρ 取 ";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}
	else
	{
		csText+=L" >= ρmin =";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	
	}

	//最小配筋面积
	float Asmin = b * h * pmin /100;

	csText=L"最小配筋面积：Asmin = b * h * ρmin = ";
	csData.Format(L"%d",b);
	csText+=csData+L"*";
	csData.Format(L"%d",h);
	csText+=csData+L"*";
	csData.Format(L"%f",pmin);
	csText+=csData+L"% = ";
	csData.Format(L"%f",Asmin);
	csText+=csData+L"mm2";
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);	
}

void ArxRleUiTdcSpaOutResult::Beam_Vector(float V,int b,int h,int hw,int asd,int fcuk,float fc,float ft,float fy,float Asb,float Arf,float Rmd,float S,
								float fyv,int Klxl,BOOL bJLoad)
{
	m_pRichEdit->ReplaceSel(L"\n\n");	

	m_pRichEdit->ReplaceSel(L"2、斜截面受剪计算：\n\n");

	CString csText,csData;

	float Asv=0;
	int h0=h-asd;

	BOOL bGouZaoOnly=FALSE;
	float V0=0.7*ft*b*h0;
	if(V0 >= V)
	{
		csText=L"一般受弯构件：0.700000 * ft * b * ho 			(GB50010  7-5-7-1)\n			=";
		//"β1 / (1 + fy / Es / εcu) = ";
		csData.Format(L"%f",0.7);
		csText+=csData+L"*";
		csData.Format(L"%f",ft);
		csText+=csData+L"*";		
		csData.Format(L"%f",b);
		csText+=csData+L"*";		
		csData.Format(L"%f",h0);
		csText+=csData+L" = ";		
		csData.Format(L"%f",V0);
		csText+=csData+L"N >= V =";		
		csData.Format(L"%f",V);
		csText+=csData+L"N\n";	
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	
		bGouZaoOnly=TRUE;
	}
	if(bJLoad&&Klxl==0)//集中荷载作用下的独立梁
	{
		float V0=1.75/(Rmd+1)*ft*b*h0;
		if(V0 >= V)
		{
			csText=L"集中荷载作用下的独立梁：1.750000 * ft * b * ho / (λ+1) 		(GB50010  7-5-7-2)\n           ＝ ";
			csData.Format(L"%f",1.75);
			csText+=csData+L"*";
			csData.Format(L"%f",ft);
			csText+=csData+L"*";		
			csData.Format(L"%d",b);
			csText+=csData+L"*";		
			csData.Format(L"%d",h0);
			csText+=csData+L" / (";		
			csData.Format(L"%f",Rmd);
			csText+=csData+L"+";		
			csData.Format(L"%d",1);
			csText+=csData+L") = ";	
			csData.Format(L"%f",V0);
			csText+=csData+L"N >= V =";	
			csData.Format(L"%f",V);
			csText+=csData+L"N\n";	
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	
			bGouZaoOnly=TRUE;
		}		
	}
	if(bGouZaoOnly)
	{
		csText=L"只需按构造配筋\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	
	}
	else
	{
		float ftmp=(float)hw/(float)b;
		float xs;
		if(ftmp<=4) xs=0.25;
		else if(ftmp>=6) xs=0.2;
		else
		{
			//线性内插法
		}

		float btac=0;//混凝土强度影响系数
		if(Fcuk<=50) btac=1.0f;
		else if(Fcuk>=80) btac=0.8f;
		else
		{
			//线性内插法求bta1
		}

		float V0=xs*btac*fc*b*h0;
		csText=L"(GB50010  7-5-1)：xs * βc * fc * b * ho = ";
		csData.Format(L"%f",xs);
		csText+=csData+L"*";	
		csData.Format(L"%f",btac);
		csText+=csData+L"*";	
		csData.Format(L"%f",fc);
		csText+=csData+L"*";	
		csData.Format(L"%d",b);
		csText+=csData+L"*";	
		csData.Format(L"%d",h0);
		csText+=csData+L" = ";	
		csData.Format(L"%f",V0);
		csText+=csData+L"N ";	
		if(V<=V0)
		{			    
			csText+=L" >= V =";
			csData.Format(L"%f",V);
			csText+=csData+L"N \n";	
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	
			csText=L"满足要求\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	
		}
		else
		{
			SetFontColor(RGB(255,0,0));
			csText+=L"≤ V =";
			csData.Format(L"%f",V);
			csText+=csData+L"N \n";	
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	
			csText=csData+L"不满足要求,请加大截面或提高混凝土强度\n";
			m_pRichEdit->ReplaceSel(csText);
			SetFontColor(RGB(0,0,0));
			return;	
		}

		if(Asb==0)//仅配箍筋
		{
			if(bJLoad&&Klxl==0)//集中荷载作用下的独立梁
			{
				csText=L"一般受弯构件只配箍筋时，集中荷载作用下的独立梁的斜截面受剪承载力按下列公式计算\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);
				csText=L"V ≤ 1.750000 * ft * b * ho / (λ+1)+ fyv * Asv / S * ho		(GB50010  7-5-4-4)\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);

				Asv=(V-1.75*ft*b*h0/(Rmd+1))*S/(fyv*h0);

				csText=L"配箍面积：Asv ＝ (V - 1.750000 * ft * b * ho/(λ+1)) * S / (Fyv * ho)\n			＝ (";
				csData.Format(L"%f",V);
				csText+=csData+L"-";	
				csData.Format(L"%f",1.75);
				csText+=csData+L"*";	
				csData.Format(L"%f",ft);
				csText+=csData+L"*";	
				csData.Format(L"%d",b);
				csText+=csData+L"*";	
				csData.Format(L"%d",h0);
				csText+=csData+L"/(";	
				csData.Format(L"%f",Rmd);
				csText+=csData+L"+";	
				csData.Format(L"%d",1);
				csText+=csData+L"))*";	
				csData.Format(L"%f",S);
				csText+=csData+L"/(";
				csData.Format(L"%f",fyv);
				csText+=csData+L"*";	
				csData.Format(L"%d",h0);
				csText+=csData+L") = ";	
				csData.Format(L"%f",Asv);
				csText+=csData+L"mm";	
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);					
			}
			else
			{
				csText=L"一般受弯构件只配箍筋时，其斜截面受剪承载力按下列公式计算\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);
				csText=L"V ≤ 0.700000 * ft * b * ho + 1.250000 * fyv * Asv / S * ho		(GB50010  7-5-4-2)\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);

				Asv=(V-0.7*ft*b*h0)*S/(1.25*fyv*h0);

				csText=L"配箍面积：Asv ＝ (V - 0.700000 * ft * b * ho) * S / (1.250000 * Fyv * ho)\n			＝ (";
				csData.Format(L"%f",V);
				csText+=csData+L"-";	
				csData.Format(L"%f",0.7);
				csText+=csData+L"*";	
				csData.Format(L"%f",ft);
				csText+=csData+L"*";	
				csData.Format(L"%d",b);
				csText+=csData+L"*";	
				csData.Format(L"%d",h0);
				csText+=csData+L")*";	
				csData.Format(L"%f",S);
				csText+=csData+L"/(";	
				csData.Format(L"%f",1.25);
				csText+=csData+L"*";	
				csData.Format(L"%f",fyv);
				csText+=csData+L"*";	
				csData.Format(L"%d",h0);
				csText+=csData+L") = ";	
				csData.Format(L"%f",Asv);
				csText+=csData+L"mm";	
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);	
			}
		}
		else
		{
			if(bJLoad&&Klxl==0)//集中荷载作用下的独立梁
			{
				csText=L"一般受弯构件配置箍筋和弯起筋时，集中荷载作用下的独立梁的斜截面受剪承载力按下列公式计算\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);
				csText=L"V ≤ 1.750000*ft*b*ho/(λ+1) + fyv*Asv/S*ho + 0.800000*fy*Asb*sin(αs) 		(GB50010  7-5-5)\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);

				Asv=(V-1.75*ft*b*h0/(Rmd+1)-0.8*fy*Asb*sin(Arf))*S/(fyv*h0);

				csText=L"配箍面积：Asv ＝ (V - 1.750000 * ft * b * ho/(λ+1) - 0.800000 * fy * Asb * sin(αs)) * S / (Fyv * ho)\n		＝ (";
				csData.Format(L"%f",V);
				csText+=csData+L"-";	
				csData.Format(L"%f",1.75);
				csText+=csData+L"*";	
				csData.Format(L"%f",ft);
				csText+=csData+L"*";	
				csData.Format(L"%d",b);
				csText+=csData+L"*";	
				csData.Format(L"%d",h0);
				csText+=csData+L"/(";	
				csData.Format(L"%f",Rmd);
				csText+=csData+L"+";	
				csData.Format(L"%d",1);
				csText+=csData+L") - ";	
				csData.Format(L"%f",0.8);
				csText+=csData+L"*";	
				csData.Format(L"%f",fy);
				csText+=csData+L"*";	
				csData.Format(L"%f",Asb);
				csText+=csData+L"* sin(";	
				csData.Format(L"%f",Arf);
				csText+=csData+L"))*";	
				csData.Format(L"%f",S);
				csText+=csData+L"/(";
				csData.Format(L"%f",fyv);
				csText+=csData+L"*";	
				csData.Format(L"%d",h0);
				csText+=csData+L") = ";	
				csData.Format(L"%f",Asv);
				csText+=csData+L"mm";	
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);					
			}
			else
			{
				csText=L"一般受弯构件配置箍筋和弯起筋时，其斜截面受剪承载力按下列公式计算\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);
				csText=L"V ≤ 0.7 * ft * b * ho + 1.25 * fyv * Asv / S * ho + 0.8*fy*Asb*sin(αs) 		(GB50010  7-5-5)\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);

				Asv=(V-0.7*ft*b*h0-0.8*fy*Asb*sin(Arf))*S/(1.25*fyv*h0);

				csText=L"配箍面积：Asv ＝ (V - 0.700000 * ft * b * ho - 0.800000 * fy * Asb * sin(αs)) * S / (1.250000 * Fyv * ho)\n			＝ (";
				csData.Format(L"%f",V);
				csText+=csData+L"-";	

				csData.Format(L"%f",0.7);
				csText+=csData+L"*";	
				csData.Format(L"%f",ft);
				csText+=csData+L"*";	
				csData.Format(L"%d",b);
				csText+=csData+L"*";	
				csData.Format(L"%d",h0);
				csText+=csData+L" - ";	
				csData.Format(L"%f",0.8);
				csText+=csData+L"*";	
				csData.Format(L"%f",fy);
				csText+=csData+L"*";	
				csData.Format(L"%f",Asb);
				csText+=csData+L"* sin(";	
				csData.Format(L"%f",Arf);
				csText+=csData+L"))*";	
				csData.Format(L"%f",S);
				csText+=csData+L"/(";	
				csData.Format(L"%f",1.25);
				csText+=csData+L"*";	
				csData.Format(L"%f",fyv);
				csText+=csData+L"*";	
				csData.Format(L"%d",h0);
				csText+=csData+L") = ";	
				csData.Format(L"%f",Asv);
				csText+=csData+L"mm";	
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);	
			}
		}
	}
	m_pRichEdit->ReplaceSel(L"\n");	

	csText=L"箍筋构造要求：\n";
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);	
	float Asvmin=0;
	int Dmin=0,Smax=0;
	if(bGouZaoOnly)
	{
		csText=L"因为：V ≤ 0.7 * ft * b * ho ，";

		if(h>150 && h<=300){ csText+=L"150 ＜ h ≤ 300 \n"; Smax=200;}
		else if(h>300 && h<=500) {csText+=L"300 ＜ h ≤ 500 \n"; Smax=300;}
		else if(h>500 && h<=800) {csText+=L"500 ＜ h ≤ 800 \n"; Smax=350;}
		else if(h>800) {csText+=L"800 ＜ h \n"; Smax=400;}
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	

		if(h>800) Dmin=8;
		else Dmin=6;

		csText=L"箍筋最小直径Dmin＝";
		csData.Format(L"%d",Dmin);
		csText+=csData+L"mm，箍筋最大间距Smax＝";
		csData.Format(L"%d",Smax);
		csText+=csData+L"mm\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	

		float Asvmin=Dmin*Dmin*PI/4*S/Smax;

		csText=L"Dmin、Smax的配箍面积：Asv#＝ Dmin ^ 2 * π / 4 * S / Smax ＝";
		csData.Format(L"%f",Asvmin);
		csText+=csData+L"mm\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	
	}
	else
	{
		csText=L"因为：V ＞ 0.7 * ft * b * ho ，";

		if(h>150 && h<=300){ csText+=L"150 ＜ h ≤ 300 \n"; Smax=200;}
		else if(h>300 && h<=500) {csText+=L"300 ＜ h ≤ 500 \n"; Smax=300;}
		else if(h>500 && h<=800) {csText+=L"500 ＜ h ≤ 800 \n"; Smax=350;}
		else if(h>800) {csText+=L"800 ＜ h \n"; Smax=400;}
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	

		if(h>800) Dmin=8;
		else Dmin=6;

		csText=L"箍筋最小直径Dmin＝";
		csData.Format(L"%d",Dmin);
		csText+=csData+L"mm，箍筋最大间距Smax＝";
		csData.Format(L"%d",Smax);
		csText+=csData+L"mm\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	

		Asvmin=(0.24*ft/fyv)*b*Smax;
		csText=L"最小配箍面积：Asv,min ＝ (0.240000 * ft / fyv) * b * Smax\n			＝(0.240000*";
		csData.Format(L"%f",ft);
		csText+=csData+L"/";
		csData.Format(L"%f",fyv);
		csText+=csData+L")*";
		csData.Format(L"%d",b);
		csText+=csData+L"*";
		csData.Format(L"%d",Smax);
		csText+=csData+L" ＝ ";
		csData.Format(L"%f",Asvmin);
		csText+=csData+L"mm\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	
	}
	m_pRichEdit->ReplaceSel(L"\n");	
	csText=L"Asv,min ＝ ";
	csData.Format(L"%f",Asvmin);
	csText+=csData+L"mm	  箍筋最小直径";
	csData.Format(L"%d",Dmin);
	csText+=csData+L"mm    最大间距 @";
	csData.Format(L"%d",Smax);
	csText+=csData+L"mm\n";
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);	
}