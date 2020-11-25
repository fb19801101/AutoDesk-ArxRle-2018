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
// ArxRleUiTdcSpaOutResult �Ի���

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


// ArxRleUiTdcSpaOutResult ��Ϣ�������

int ArxRleUiTdcSpaOutResult::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
	cf.yHeight=iSize;	//200��10�ţ�210����ţ�220��11��;
	//240��С��;260��13��;280���ĺ�;
	//300��С����320������
	cf.bCharSet=GB2312_CHARSET;
	lstrcpy(cf.szFaceName,L"����");

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
	int i=cs.Find(L"��");
	while(i<20)
	{
		cs=L" "+cs;
		i++;
	}
}

/////////////////////////////////////////////////////////////////////////////
//c			  --  BEAM_MOMENT_GBJ10  --		             		    
//c     GB50010-2001���乹��������������
//c-----------------------------------------------------------------
//c  ���������
//c             B/H: ���渹���/�����ܸ�(mm) 
//c  BFUI/HFUI/BHCU: ��������Ե��/����Ե��,�ֽ����������Ե����(mm)
//c  BFDI/HFDI/BHCD: ��������Ե��/����Ե��,�ֽ����������Ե����(mm)
//c			   SPAN: ������(mm)
//c			   FCUK: ������ǿ�ȵȼ�C (N/mm2) 
//c			 FY/YFC: ����������/������ѹ�� ǿ�����ֵ(N/mm2)
//c			   ASCI: �������ѹ�ֽ����(mm2)
//c			   KZDJ: ����ȼ� (0-�Ŷ���/��֧����һ��,1,2,3,4,5-�ǿ���)
//c			   KZZH: 0--�ǵ�����ϣ�1--������ϣ�2--�˷����
//c			     JM: 0--�ǹ��������,1���������,2--��֧�� 
//c			   KLXL: 0--��ͨ��; 1--������; 
//c			     AM: ������ֵ(��ҸԵ����Ϊ+) M(kN-m)
//c--------------------------------------------------------------------
//c  ��������
//C          BFUE: ���������Ե���(mm)
//C	       RE: �������������ϵ��
//C            H0: ������Ч�߶�(mm)      
//C           ZMU: ���漫�����������ֵMu(kN.m)      
//c   ARFA1/BATA1: ϵ����1/ϵ����1
//C           XIE: �����������������ѹ�ֽ����Ļ����������ѹ���߶Ȧ�e      
//C          XIEB: �����������������Ļ����������ѹ���߶Ȧ�be
//c                ע������e>��beʱ���治���㿹��Ҫ��Ӧ�Ӵ����      
//c	       XI: ����������ļ��������ѹ���߶Ȧ� 
//c	      XIB: ����������Ľ��������ѹ���߶Ȧ�b 
//c	       RO: ���������ֽ����ٷ��ʦ�(%) As/A*100
//C                ע����RO>RMAXʱ��ʾ����(����ʴ�����������)
//c	       RC: ������ѹ�ֽ����ٷ��ʦ�c(%) Asc/A*100
//c	     RMAX: ��������ֽ����ٷ��ʦ�max(%) 
//c	      AS1: ���㵥�������ֽ����(mm2) 
//c	      AS2: ����˫�������ֽ����(mm2)
//c                ע����AS1��AS2=99999ʱ��ʾ����(������AM>����������ZMU) 
//c	      ASC: ������ѹ�ֽ���� (mm2) 
//c	    ASMIN: �����ֽ���С��� (mm2) 
//c	   ASCMIN: ��ѹ�ֽ���С��� (mm2) 
//c  ע����������ֽ�Ӧȡmax(AS1,AS2,ASMIN), �����ѹ�ֽ�Ӧȡmax(ASC,ASCMIN)
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
//C   GB50010-2001ƫ������(�ǶԳ����)������������
//c-----------------------------------------------------------------
//c  ���������
//c           B,H: ������(mm) width, height of section 
//c          BHCU: ��ѹ�ֽ����������Ե����(mm)
//c          BHCD: �����ֽ����������Ե����(mm)
//c	     FCUK: ������ǿ�ȵȼ�C (N/mm2) 
//c	   FY/YFC: ����������/������ѹ�� ǿ�����ֵ(N/mm2)
//c	     KZDJ: ����ȼ� (0-�Ŷ���/��֧����һ��,1,2,3,4,5-�ǿ���)
//c	     KZZH: 0--�ǵ�����ϣ�1--������ϣ�2--�˷����
//c	       JM: 0--�ǹ��������,1���������,2--��֧�� 
//c	       XM: ������ֵ M(kN-m)
//c	       XN: ���������ֵ(����Ϊ-) N(kN)
//c
//c  ��������
//C	       RE: �������������ϵ��
//C            H0: ������Ч�߶�(mm)      
//c   ARFA1/BATA1: ϵ����1/ϵ����1
//C           XIE: �����������������ѹ�ֽ����Ļ����������ѹ���߶Ȧ�e      
//C          XIEB: �����������������Ļ����������ѹ���߶Ȧ�be      
//c                ע������e>��beʱ���治���㿹��Ҫ��Ӧ�Ӵ����      
//c	       XI: ����������ļ��������ѹ���߶Ȧ� 
//c	      XIB: ����������Ľ��������ѹ���߶Ȧ�b 
//c	       RO: ���������ֽ�����ʦ� As/A
//c	       RC: ������ѹ�ֽ�����ʦ�c Asc/A
//c	     RMAX: ��������ֽ�����ʦ�max 
//C                ע����RO>RMAXʱ��ʾ����(����ʴ�����������)
//c	      AS1: ���㵥�������ֽ����(mm2) 
//c	      AS2: ����˫�������ֽ����(mm2) 
//c                ע����AS1��AS2=99999ʱ��ʾ����(������AM>����������ZMU) 
//c	      ASC: ������ѹ�ֽ���� (mm2) 
//c	    ASMIN: �����ֽ���С��� (mm2) 
//c	   ASCMIN: ��ѹ�ֽ���С��� (mm2) 
//c  ע����������ֽ�Ӧȡmax(AS1,AS2,ASMIN), �����ѹ�ֽ�Ӧȡmax(ASC,ASCMIN)
extern "C" void __stdcall BEAM_MOMENT_TENSE_GBJ10(float &B,float &H,float &BHCUI,float &BHCDI,
												  float &FCUK,float &FY,float &FYC,long &KZDJ,long &KZZH,long &JM,float &AM,float &XN,
												  float &RE,float &H0,float &ARFA1,float &BATA1,float &XIE,
												  float &XIEB,float &XI,float &XIB,float &RO,float &RC,float &RMAX,float &AS1,float &AS2,
												  float &ASC,float &ASMIN,float &ASCMIN);

/////////////////////////////////////////////////////////////////////////////
//c			  --  SHEAR_TORSION_GBJ10  --				    c
//c	  GB50010-2001��������ǽ����б�����ܼ�/��Ť/�ܼ�Ť ������  	                    c
//c-----------------------------------------------------------------
//c  ���������
//c	     IBCW: 1-����2-����3-ǽ��4-��, 5-��֧��, 6-��֧��, 7-ǽ���� 
//c	      B/H: ���渹����(Բ: ֱ��)/�߶�(Բ:  0)
//c	  BFU/HFU: ��ѹ����Ե���(Բ: 0)/�߶�(Բ: 0)
//c	  BFD/HFD: ��������Ե���(Բ: 0)/�߶�(Բ: 0)
//c          BHCX: �ֽ����������Ե����(mm)
//c	     SPAN: ������(mm)
//c	    RMD��: �����,��������ȡ�ˡ�1; ����=Hn/2ho; ����ǽ��=M/Vho
//c	     FCUK: ������ǿ�ȵȼ�C (N/mm2) 
//c	  FYV/FYB: ����/����� ǿ�����ֵ(N/mm2)
//c		    S: ������ 
//c	     KZDJ: ����ȼ� (0-�Ŷ���/��֧����һ��,1,2,3,4,5-�ǿ���)
//c	     KZZH: 0--�ǵ�����ϣ�1--������ϣ�2--�˷����
//c	      ASB: ����ֽ���� (mm2)
//c	      ARF: ����ֽ�Ƕ� (degree)
//c		   VX: X��(ˮƽ������ȶ�Ӧ)�������ֵ (kN)
//c		   VY: Y��(��ֱ�����߶ȶ�Ӧ)�������ֵ (kN)
//c		    T: Ť�����ֵ(kN.m)
//c	       XN: �������ֵ(kN)(+ ѹ,- ��) 
//c	       PN: ԤӦ�����ԤӦ����ĺ���(+ ѹ,- ��)(kN)
//c		 WZYB: ǽ֫�׽�����ѹ��(����0�Զ�����������)
//c
//c--------------------------------------------------------------------
//c  ��������
//C	       RE: �������������ϵ��
//c         BATAH: ����߶�Ӱ��ϵ����h
//c         BATAT: ��Ť����������ϵ����t
//c          R_HB: =99999:�ܼ����泬��(V/bho+T/Wt>0.25bho)
//c		 VMAX: �������������Ӧ��(0.25fc��0.2fc��0.15fc)
//c          ASVT: �ܼ�Ť�ܵļ��㹿����� (Asv+2Ast1)(mm2)
//C			   ����ǽΪˮƽ�ֲ������(mm2)
//c          AST1: ��Ť���ܱߵ�֫�������(mm2)   
//c          ASTL: ������Ť�ݽ����Astl(mm2),Ӧ�ؽ����ܱ߾��Ȳ���
//c        ASVMIN: ��С��Ť�������(=b.s.��v) (mm2)
//C         RMINS: ������/����ǽˮƽ�ֲ���/��С����ʦ�v
//C        RMINSW: �����������/����ǽԼ����Ե����������С�������ʦ�v
//c       ASTLMIN: ��С��Ť�ݽ���� (b.s.��tl  mm2) 
//c       K_YS_GZ: 0/1 ����ǽ�����Ե����/Լ����Ե����
//c  ע����ƹ���Ӧȡmax(ASVT,ASVMIN),���ܱߵ�֫�������Ӧ>AST1; 
//c      ����ݽ�Ӧȡmax(ASTL,ASTLMIN),��Ӧ�������ݽ����.
extern "C" void __stdcall SHEAR_TORSION_GBJ10(long &IBCW,float &B,float &H,float &BFU,
											  float &HFU,float &BFD,float &HFD,float &BHCX,float &RMD,float &SPAN,float &FCUK,
											  float &FYV,float &FY,float &S,long &KZDJ,long &KZZH,float &ASB,float &ARF,float &VY,
											  float &VX,float &T,float &XN,float &PN,float &WZYB,
											  float &RE,float &BATAH,float &BATAT,float &R_HB,float &RMINS,float &VMAX,float &ASVT,
											  float &ASVMIN,float &AST1,float &ASTL,float &ASTLMIN,float &RMINSW,float &K_YS_GZ);

/////////////////////////////////////////////////////////////////////////////
//c			  --  CRACK_WIDE_GBJ10  --
//c ��������ѷ���	     
//c-------------------------------------------------------------------
//c  ���������
//c           B,H: ������(mm)  
//c  BFU,HFU,BHCS: ������ҸԵ��,��,�ֽ����������Ե����(mm)
//c  BFD,HFD,BHCX: ������ҸԵ��,��,�ֽ����������Ե����(mm)
//c	     SPAN: ������(mm)
//c	     FCUK: ������ǿ�ȵȼ�C(N/mm2) 
//c	       FY: ����ǿ�����ֵ fy(N/mm2)
//c	       AS: �����ֽ���� As (mm2)
//c		  Deq: �����ֽ��Чֱ�� deq(mm)
//c         Cover: ������������ֽ��Ե���������ױߵľ���(mm)
//c	       AN: ��׼�������   Nk(kN)  
//c	       AM: ��׼������   Mk(kN-m)
//c
//c	     Wmax: ����ѷ���the width of crack (mm)
/////////////////////////////////////////////////////////////////////////////
extern "C" void __stdcall CRACK_WIDE_GBJ10(float &B,float &H,float &BFU,float &HFU,
										   float &BFD,float &HFD,float &BHCS,float &BHCX,float &SPAN,float &FCUK,float &FY,
										   float &AS,float &Deq,float &COVER,float &AN,float &AM,
										   float &ARF,float &PTE,float &XGM,float &FAI,float &WMAX);
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//c			  --  DEFLECTION_B --
//c------------------------------------------------------------------
//c  ���������
//c           B,H: ������(mm)  
//c  BFU,HFU,BHCX: ������ҸԵ��,��,�����ֽ����������Ե����(mm)
//c       BFD,HFD: ������ҸԵ��,��
//c	     SPAN: ������(mm)
//c	     FCUK: ������ǿ�ȵȼ�C(N/mm2) 
//c	       FY: ����ǿ�����ֵ fy(N/mm2)
//c	       ASA: �����ֽ���� As (mm2)
//c	      ASB: ��ѹ�ֽ����As`(mm2)
//C	        U: ����֧��ϵ��(��֧1,�̶�0.8,�������̶�0.65)
//c	      AMS: ��׼������Mk(kN-m)(�±�����Ϊ+���ϱ�����Ϊ-)   
//c	      AML: ׼���������� Mq(kN-m)
//c--------------------------------------------------------------------
//c  ��������
//c	       Bs: ���乹���Ķ��ڸն�Bs(kN/m2)
//c	       Bl: ���乹�����ڸն�Bl(kN/m2)
//c		    f: ���乹���Ӷ�ֵ(mm)
//c	      fl0: ���乹������Ӷȵĵ���(lo/f)

/////////////////////////////////////////////////////////////////////////////
//	extern "C" void __stdcall DEFLECTION_B_GBJ10(float &B,float &H,float &BFU,float &HFU,
//		float &BFD,float &HFD,float &BHCX,float &SPAN,float &FCUK,float &FY,
//		float &ASA,float &ASB,float &U,float &AMS,float &AML,
//		float &PTE,float &SITA,float &BS,float &BL,float &F,float &FL0);


/////////////////////////////////////////////////////////////////////////////
//c		 --- COLUMN_UNIMOMENT 
//c GB50010-2001/ACI318-1998/BS8110 ��/����ǽ����ƫ������������������
//c-------------------------------------------------------------------
//c  ���������
//C    	NCODE: �淶���1-GBJ��2-BS8110��3-TW;4-ACI��
//c	    I_C_W: 0--��,1--����ǽ
//c       B/H: ���渹���(Բ=ֱ��D)/�����ܸ�(mm)(Բ=0) 
//c   BFU/HFU: ��������Ե��(Բ=0)/����Ե��,�ֽ����������Ե����(mm)(Բ=0)
//c   BFD/HFD: ��������Ե��(Բ=0)/����Ե��,�ֽ����������Ե����(mm)(Բ=0)
//c      BHCX: �ֽ����������Ե����(mm)
//c	  XLE/YLE: �����ƽ����/���ƽ����ļ��㳤��
//c	     FCUK: ������ǿ�ȵȼ�C (N/mm2) 
//c	   FY/FYW: ��������/��������ֲ��ֽ� ǿ�����ֵ(N/mm2)
//c	      RWV: ��������ֲ��ֽ������ ��v(%)
//c	     KZDJ: ����ȼ� (0-�Ŷ���,1,2,3,4,5-�ǿ���)
//c	     KZZH: 0--�ǵ�����ϣ�1--������ϣ�2--�˷����
//c	      KCY: 1--����ƫ�ľ�����ϵ����,0--������ƫ�ľ�����ϵ����=1 
//c	      KJZ: 0--��ͨ��;1--�������֧�� 
//c	     JQBW: 0--�Ǽ���ǽǽ��ǿ��;1--����ǽǽ��ǿ�� 
//c	       XN: �������ֵ(+ѹ,-��)(kN)
//c	       XM: ������ֵ(kN)
//c	     WZYB: �������ش���ֵ������ǽ��ѹ��(N/fcAw)(����0ʱ�ɳ������)
//c        WC: ����������(ACI/TW��,��ͨ������=2300)
//c
//c  ��������
//c	   FAIMIN: ������ѹ�����ȶ�ϵ����
//c        RE: ������������������ϵ����RE:'      
//c	       XI: ���������ѹ���߶Ȧ�
//C        AT: ƫ�ľ�����ϵ�� ��     
//c	      ZYB: ��ѹ��(N/fcA)
//c	       RO: ȫ������������(2*As+Asw)/A
//c	     RMAX: ȫ���������������ʦ�max
//c	    RMINL: ȫ������С����ʦ�min/����ǽȡһ���ԵԼ��(����)����С�����
//c	      ASX: ���߼���������(ԲΪȫ����/2) As(mm2)
//c	    ASMIN: ȫ������С������(mm2),����ǽȡһ�వ������С������
//c	      ASA: ����ѹ�����ȫ���������� (mm2)
//c	      FN0: ��Ӧ�������ĵ��������ֵ,(kN)
//c	      XM0: ��Ӧ��������X��ʸ��������ֵ(kN.m)
//c	      FAI: ����е������ǿ���ۼ�ϵ��(ACI/TW)
extern "C" void __stdcall COLUMN_UNIMOMENT(long &NCODE,long &I_C_W,float &B,float &H,
										   float &BFU,float &HFU,float &BFD,float &HFD,float &BHCX,float &XLE,float &YLE,
										   float &FCUK,float &FY,float &FYW,float &RWV,long &KZDJ,long &KZZH,long &KCY,
										   long &KJZ,long &JQBW,float &WZYB,float &WC,float &XN,float &XM,
										   float &FAIMIN,float &RE,float &XI,float &FC,float &FCS,float &AT,float &ZYB,
										   float &RO,float &RMAX,float &RMINL,float &ASX,float &ASMIN,float &ASA,
										   float &FN0,float &FMX0,float &FAI);

/////////////////////////////////////////////////////////////////////////////
//c		 --- COLUMN_BIMOMENT 
//c  GB50010-2001/ACI318/BS8110 ��˫ƫѹ������ --
//c-------------------------------------------------------------------
//c  ���������
//C   		NCODE: �淶���1-GBJ��2-BS8110��3-TW;4-ACI��
//C		N_COMBINE: �������������
//C	   FORCE(4,*): �������� 
//c	            1: ��Ӧ�������ĵ��������ֵ(+ѹ,-��)(kN)
//c	            2: ��Ӧ��������X��ʸ��������ֵ(kN.m)
//c	            3: ��Ӧ��������Y��ʸ��������ֵ(kN.m)
//c	            4: 1/0--��/��������
//C             B: ������(mm)   
//C             H: ����߶�(mm)   
//C           BFU: ����Ե���(mm)(ʮ����ʱΪˮƽ֫���)
//C           HFU: ����Ե�߶�(mm) 
//C           BFD: ����Ե���(mm) (ʮ����ʱΪ0)
//C           HFD: ����Ե�߶�(mm) 
//C           DFU: ����Եλ��(mm)(ƫ�������ߵľ���,��ƫΪ��,��ƫΪ��)
//C           DFD: ����Եλ��(mm)(ʮ����ʱΪˮƽ֫���϶˾���)
//C          BHCX: ��Ե���ֽ���������(mm)
//c		  XLE,YLE: ��ӦXM�����㳤��XLE(mm),��ӦYM���ļ��㳤��YLE(mm) 
//c	         CITA: ��������X������ȷ���ļн�(����)
//c	           FY: ����ǿ�����ֵ fy(N/mm2)
//c	         FCUK: ������ǿ��(N/mm2)(GBJ--�ȼ�C; BS8110--fcu; ACI/TW--fc') 
//c            WC: ����������(ACI/TW��,��ͨ������=2300)
//c	         KZDJ: ����ȼ� (0-�Ŷ�,1,2,3,4,5-�ǿ���)
//c	         KZZH: 0--�ǵ�����ϣ�1--������ϣ�2--�˷����
//c	          KCY: 1--����ƫ�ľ�����ϵ����/0--������ƫ�ľ�����ϵ����=1 
//c	          KJZ: 0--��ͨ��/1--�������֧�� 
//C	         KZDG: ���ν����Ƿ�ָ���ֽ������0��/2�ǣ�
//c  ע: ����֪�������������ʱ,ȡKZDG=2,������NO_X,NO_Y,ASC,ASX,ASY��ֵ,
//c      �ж������ȫ��������ʦѴ���ԭ���������0.1%ʱ,��ʾԭ��������
//c								   
//c  ��������
//c			 ASC: �����ǽ���� (mm2)
//c			 ASX: �������±ߵ������������(�����ǽ�)/���͹̶������(mm2)
//c			 ASY: ���αߵ������������(�����ǽ�)/���͸��ӷֲ������(mm2)
//c    NO_X/NO_Y: ���� ����/���� �ֽ�����������ǽ
//c               ���� �̶���/���ӷֲ������
//c      ASTOTAL: ȫ�����ܼ���������
//C           Rs: ȫ������������ ��:'      
//c         RMAX: ȫ���������������ʦ�max
//c		   RMINL: ȫ������С����ʦ�min
//c	       ASMIN: ȫ������С������(mm2), 
//c	         ZYB: ��ѹ��(N/fc/A)
//c	      FAIMIN: ������ѹ�����ȶ�ϵ����
//c  ASX_MAX/ASY_MAX/ASC_MAX: ���� ��ȷ���/�߶ȷ���/�����ǽ� ���������(mm2)
//c                           ���� �̶�λ�ý�/���ӷֲ��� ���������(mm2)
//c XN_X,XM_X,YM_X: ��Ӧȫ����������ASTOTAL������
//c       N_ASXMAX: ��ӦASTOTAL��������Ϻ�
//c         KZZH_X: ��Ӧ����N_ASXMAX�ĵ��������Ϣ(0/1)
extern "C" void __stdcall COLUMN_BIMOMENT(long &NCODE,long &N_COMBINE,float *FORCE,
										  float &B,float &H,float &BFU,float &HFU,float &BFD,float &HFD,float &BHCX,
										  float &DFU,float &DFD,float &XLE,float &YLE,float &CITA,float &FY,float &FCUK,
										  float &WC,long &KZDJ,long &KCY,long &KJZ,long &KZDG,float &FCS,float &FC,
										  float &ASC,float &ASX,float &ASY,long &NO_X,long &NO_Y,float &ASTOTAL,float &RS,
										  float &ATX,float &ATY,float &FAIMIN,float &ASA,float &ZYB,float &Asmin,float &RE,
										  float &RMINL,float &RMAX,long &KIND,float &FI);

/////////////////////////////////////////////////////////////////////////////
//c		 --- CIRCLE_GBJ10 
//c  GB50010-2001/ACI318/BS8110 Բ�ν������������ --
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
	m_pRichEdit->ReplaceSel(L"���������\n");
	m_pRichEdit->ReplaceSel(L"\n");
	SetLeft();
	SetFontSize(240);
	m_pRichEdit->ReplaceSel(L"�����������\n\n");

	CString csText,csData;
	SetFontSize(200);
	csText.Format(L"������ǿ�ȵȼ���C%d    fc = %fN/mm    ft = %fN/mm\n",Fcuk,GetConcretFc(Fcuk),GetConcretFt(Fcuk));
	m_pRichEdit->ReplaceSel(csText);

	csText.Format(L"�����ֽ�ǿ�����ֵ��fy = %fN/mm    Es = %fN/mm\n",GetGjKanglaFy(csTringFy),GetGjKanglaEs(csTringFy));
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);

	if(Asc != 0)
	{
		csText.Format(L"��ѹ�ֽ������As' = %fmm2    ��ѹ�ֽ�ǿ�����ֵ��fy = %fN/mm    Es = %fN/mm\n",Asc,GetGjKanglaFy(csTringFyc),GetGjKanglaEs(csTringFyc));
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}

	csText.Format(L"�ṹ��Ҫ��ϵ������o = %f\n",Ro);
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);

	int h0=h-asd;
	int hw=h0;

	if(bWan)
	{
		csText.Format(L"������ֵ��M = %fkN��M\n",M);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}
	if(bLa)
	{
		csText.Format(L"�������ֵ��N = %fKN\n",N);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);

		csText.Format(L"�����������õ����������ĵľ��룺e0 = %fmm\n",e0);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);

		if(bDuiCh)
		{
			csText=L"�Գ����\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	
		}
		else if(bJunY) 
		{
			csText=L"����ֽ��ظ������Ȳ���\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);
		}
	}
	if(bXjm)
	{
		csText.Format(L"�������ֵ��V = %fkN\n",V);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
		if(KJmLx==0) hw=h0;//����
		else if(KJmLx==1||KJmLx==3)hw=h0-Hfd;//��T�� ��L��
		else if(KJmLx==2) hw=h0-Hfu;//T��
		else if(KJmLx==4) hw=H-Hfu-Hfd;//����
	}
	if(bNiu)
	{
		csText.Format(L"Ť�����ֵ��T = %fkN\n",T);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}

	if(KJmLx==0||KJmLx==1)
	{
		if(KJmLx==0)
			csText.Format(L"���ν���ߴ磺b * h = %d*%d    h0 = %d-%d=%dmm\n",b,h,h,asd,h0);
		else
			csText.Format(L"��T�ν���ߴ磺b * h = %d*%d    h0 = %d-%d=%dmm\n",b,h,h,asd,h0);
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}
	float ybxsb=0;
	float bta1=0;
	if(Fcuk<=50) bta1=0.8f;
	else if(Fcuk>=80) bta1=0.74f;
	else
	{
		//�����ڲ巨��bta1
	}

	float Ecu=0.0033f-0.5f*(GetConcretFck(Fcuk)-50)*1e-5f;
	ybxsb=bta1/(1+GetGjKanglaFy(csTringFy)/GetGjKanglaEs(csTringFy)/Ecu);
	csText=L"��Խ�����ѹ���߶ȣ���b = ��1 / (1 + fy / Es / ��cu)    (GB50010  7-1-4-1) \n                                      = ";
	csData.Format(L"%f/(1+%f/%f/%f) = %f\n",bta1,GetGjKanglaFy(csTringFy),GetGjKanglaEs(csTringFy),Ecu,ybxsb);
	SimplifyString(csText+csData);
	m_pRichEdit->ReplaceSel(csText+csData);

	m_pRichEdit->ReplaceSel(L"\n\n");
	SetFontSize(240);
	m_pRichEdit->ReplaceSel(L"�򡢼�������\n\n");
	SetFontSize(200);

	float a1=0;
	if(Fcuk<=50) a1=1;
	else if(Fcuk>=80) a1=0.94f;
	else
	{
		//�����ڲ巨��bta1
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
		m_pRichEdit->ReplaceSel(L"1�����������������㣺\n\n");
		if(KJmLx==0||KJmLx==1)//���λ���Եλ�������ߵĵ�T�ν���
		{
			if(Span/h >= 5.0)
			{
				csText=L"���λ���Եλ�������ߵĵ�T�ν��棺�����·�������\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);
			}
			else
			{
				csText=L"�����乹���������·�������\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);			
			}
		}
		else
		{
			csText=L"T�� ��L�� ���ν��棺�����·�������\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);		
		}
		if(KJmLx==0||KJmLx==1)//���λ���Եλ�������ߵĵ�T�ν���
		{
			if(Span/h >= 5.0)
				Beam_Moment_Rectangle(Ro,M,b,h,asd,asu,fc,ft,a1,fy,fyc,Asc,ybxsb,pmin0);
			else
			{
				//�����乹��
			}
		}
		else if(KJmLx==2||KJmLx==3||KJmLx==4)
		{
			int bf=Bfu;//��Ե������
			if(KJmLx==3) //��L��
			{
				//				if(hfu/(h-asd)<0.1 && hfu/(h-asd)>0.05) bf1=b+5*hfu;
				//				else if(hfu/(h-asd) < 0.05) bf1=
				bf=Span/6<b+5*Hfu ? Span/6:b+5*Hfu;
				csText=L"��L�ν��棺bf'= min{ lo/6 , b+5*hf'} = ";
			}
			else
			{
				if(Klxl==0) //������
				{
					int bf1;
					if(Hfu/(h-asd)<0.1 && Hfu/(h-asd)>=0.05) bf1=b+6*Hfu;
					else if(Hfu/(h-asd) < 0.05) bf1=b;
					else bf1=b+12*Hfu;

					bf=Span/3<bf1 ? Span/3:bf1;
					csText=L"������T�λ�I�ν��棺bf'= min{ lo/3 , ��hf'���ǵ�bf'} = min{";
					csData.Format(L"%d, %d} = ",Span/3,bf1);
				}
				else 
				{
					bf=Span/3<b+12*Hfu ? Span/3:b+12*Hfu ;//������
					csText=L"������T�λ�I�ν��棺bf'= min{ lo/3 , b+12hf'} = ";
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

//���λ���Եλ�������ߵĵ�T�ν������乹��
//Ro�D�D�ṹ��Ҫ��ϵ��
//M�D�D������ֵ
//b �D�D ���ο�򸹰��
//h0 �D�D����߶�
//asu �D�D��ѹ��������ͨ�ֽ������
//Fc �������������Ŀ�ѹǿ�����ֵ
//Ft �������������Ŀ���ǿ�����ֵ
//a1 �D�Dϵ��
//fy �D�D�������ǿ�����ֵ
//fy' �D�D��ѹ�ѹǿ�����ֵ
//As' �D�D��ѹ��������
//��b �D�D��Խ�����ѹ���߶�
//��min0 �D�D�������С�����
void ArxRleUiTdcSpaOutResult::Beam_Moment_Rectangle(float Ro,float M,int b,int h,int asd,int asu,float Fc,
										  float Ft, float a1,float Fy,float Fyc,float Asc,float ybxsb,float pmin0)
{
	//��ѹ���߶�
	//x=2*h0-2*(Ro*M-fy'*As'(h0-as'))/(a1*fc*b)
	//if(As'!=0) {
	//x<=2as'
	//}
	//�����ѹ���߶� ��=x/h0  
	CString csText,csData;

	float As=0;
	float x;//��ѹ���߶�
	int h0=h-asd;
	//	x=2*-2*(Ro*M-Fy*Asc*((h-asd)-asu))/(a1*Fc*b);//7.2.1-1
	x=(h0)-sqrt((h0)*(h0)-2*Ro*M/(a1*Fc*b));
	csText=L"��ѹ���߶ȣ�x = ho - ( ho^2 - 2 * ��o * M / (��1 * fc * b))^0.500000		(GB50010  7-2-1-1)\n                                      = ";
	//"��1 / (1 + fy / Es / ��cu) = ";
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
			csText=L"�����ֽ������As = M/fy*(h0-as')			(GB50010  7-2-5)\n                                      = ";
			//"��1 / (1 + fy / Es / ��cu) = ";
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
			csText=L"��ѹ���߶ȣ�x = (fy*As-fy'*As')/(a1*fc*b)		(GB50010  7-2-1-2)\n                                      = (";
			//"��1 / (1 + fy / Es / ��cu) = ";
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
				csText+=L" > ��b*h0 = ";
				csData.Format(L"%f",ybxsb);
				csText+=csData+L"*";
				csData.Format(L"%d",(h0));				
				csText+=csData+L"mm\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);				
				csText=csData+L"��Ӵ�������߻�����ǿ��\n";
				m_pRichEdit->ReplaceSel(csText);
				SetFontColor(RGB(0,0,0));
				return;
			}
			else
			{
				csText+=L" <= ��b*h0 = ";
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
			csText+=L" > ��b*h0 = ";
			csData.Format(L"%f",ybxsb);
			csText+=csData+L"*";
			csData.Format(L"%f",(h0));				
			csText+=csData+L"mm\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);				

			csText=csData+L"��Ӵ�������߻�����ǿ��\n";
			m_pRichEdit->ReplaceSel(csText);
			SetFontColor(RGB(0,0,0));
			return;
		}
		else
		{
			csText+=L" <= ��b*h0 = ";
			csData.Format(L"%f",ybxsb);
			csText+=csData+L"*";
			csData.Format(L"%d",(h0));				
			csText+=csData+L" = ";
			csData.Format(L"%f",ybxsb*(h0));				
			csText+=csData+L"mm\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	

			As=(a1*Fc*b*x+Fyc*Asc)/Fy;//7.2.1-2
			csText=L"�����ֽ������As = (a1*fc*b*x+fy'*As')/fy		(GB50010  7-2-1-2)\n                        = (";
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
	//��С����ʦ�min
	float pmin=max(pmin0,tmp);
	csText=L"��С����ʣ���min = max(��pmin,0.450000*Ft/Fy) = max(";
	csData.Format(L"%f",pmin0);
	csText+=csData+L"%,";
	csData.Format(L"%f",tmp);
	csText+=csData+L"%) = ";
	csData.Format(L"%f",pmin);
	csText+=csData+L"%\n";
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);	

	//����ʦ�
	float p=As/b/h*100;
	csText=L"����ʣ��� = As/b/h = ";
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
		csText+=L" < ��min =";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);

		csText=L"�� ȡ ";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}
	else
	{
		csText+=L" >= ��min =";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	
	}

	//��С������
	float Asmin = b * h * pmin /100;

	csText=L"��С��������Asmin = b * h * ��min = ";
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
	float x;//��ѹ���߶�
	int h0=h-asd;

	csText=L"�Ȱ�b0*bf'�Ĵ�����㣺\n";
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);

	x=h0-sqrt(h0*h0-2*(Ro*M-Fyc*Asc*(h0-asu))/(a1*Fc*bfc));
	csText=L"��ѹ���߶ȣ�x = ho-{ho^2 - 2*[��o*M-fy'*As'*(ho-as')] / (��1*fc*bf')}^0.500000		(GB50010  7-2-1-1)\n                                      = ";
	//"��1 / (1 + fy / Es / ��cu) = ";
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
		csText+=L" > ��b*h0 = ";
		csData.Format(L"%f",ybxsb);
		csText+=csData+L"*";
		csData.Format(L"%f",(h0));				
		csText+=csData+L"mm\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);				

		csText=csData+L"��Ӵ�������߻�����ǿ��\n";
		m_pRichEdit->ReplaceSel(csText);
		SetFontColor(RGB(0,0,0));
		return;
	}
	else
	{
		csText+=L" <= ��b*h0 = ";
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
		csText=L" x �� hf'�����ԣ�Ӧ���Ǹ������ѹ���ã����¼�����ѹ���߶�x\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);

		x=h0-sqrt(h0*h0-2*(Ro*M-Fyc*Asc*(h0-asu)-a1*Fc*(bfc-b)*hfc*(h0-hfc/2))/(a1*Fc*bfc));
		csText=L"��ѹ���߶ȣ�x = ho-{ho^2 - 2*[��o*M-fy'*As'*(ho-as')-��1*fc*(bf'-b)*hf'*(ho-hf'/2)] / (��1*fc*b)}^0.500000		(GB50010  7-2-2-2)\n                                      = ";
		//"��1 / (1 + fy / Es / ��cu) = ";
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
			csText+=L" > ��b*h0 = ";
			csData.Format(L"%f",ybxsb);
			csText+=csData+L"*";
			csData.Format(L"%f",(h0));				
			csText+=csData+L"mm\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);				

			csText=csData+L"��Ӵ�������߻�����ǿ��\n";
			m_pRichEdit->ReplaceSel(csText);
			SetFontColor(RGB(0,0,0));
			return;
		}
		else
		{
			csText+=L" <= ��b*h0 = ";
			csData.Format(L"%f",ybxsb);
			csText+=csData+L"*";
			csData.Format(L"%d",(h0));				
			csText+=csData+L" = ";
			csData.Format(L"%f",ybxsb*(h0));				
			csText+=csData+L"mm\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	

			As=(a1*Fc*(b*x+(bfc-b)*hfc)+Fyc*Asc)/Fy;//7.2.1-2
			csText=L"�����ֽ������As = {��1*fc*[b*x+(bf'-b)*hf']+fy'*As'} / fy		(GB50010  7-2-2-3)\n	                       = {";
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
	else//x<hf'ʱ
	{
		As=(a1*Fc*bfc*x+Fyc*Asc)/Fy;//7.2.1-2
		csText=L"�����ֽ������As = (��1*fc*bf'*x+fy'*As') / fy		(GB50010  7-2-1-2)\n                        = (";
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

	//����ʦ�
	float p=As/b/h0*100;
	csText=L"����ʣ��� = As/b/h0 = ";
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
		csText+=L" < ��min =";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);

		csText=L"�� ȡ ";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);
	}
	else
	{
		csText+=L" >= ��min =";
		csData.Format(L"%f",pmin);
		csText+=csData+L"%\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	
	}

	//��С������
	float Asmin = b * h * pmin /100;

	csText=L"��С��������Asmin = b * h * ��min = ";
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

	m_pRichEdit->ReplaceSel(L"2��б�����ܼ����㣺\n\n");

	CString csText,csData;

	float Asv=0;
	int h0=h-asd;

	BOOL bGouZaoOnly=FALSE;
	float V0=0.7*ft*b*h0;
	if(V0 >= V)
	{
		csText=L"һ�����乹����0.700000 * ft * b * ho 			(GB50010  7-5-7-1)\n			=";
		//"��1 / (1 + fy / Es / ��cu) = ";
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
	if(bJLoad&&Klxl==0)//���к��������µĶ�����
	{
		float V0=1.75/(Rmd+1)*ft*b*h0;
		if(V0 >= V)
		{
			csText=L"���к��������µĶ�������1.750000 * ft * b * ho / (��+1) 		(GB50010  7-5-7-2)\n           �� ";
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
		csText=L"ֻ�谴�������\n";
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
			//�����ڲ巨
		}

		float btac=0;//������ǿ��Ӱ��ϵ��
		if(Fcuk<=50) btac=1.0f;
		else if(Fcuk>=80) btac=0.8f;
		else
		{
			//�����ڲ巨��bta1
		}

		float V0=xs*btac*fc*b*h0;
		csText=L"(GB50010  7-5-1)��xs * ��c * fc * b * ho = ";
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
			csText=L"����Ҫ��\n";
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	
		}
		else
		{
			SetFontColor(RGB(255,0,0));
			csText+=L"�� V =";
			csData.Format(L"%f",V);
			csText+=csData+L"N \n";	
			SimplifyString(csText);
			m_pRichEdit->ReplaceSel(csText);	
			csText=csData+L"������Ҫ��,��Ӵ�������߻�����ǿ��\n";
			m_pRichEdit->ReplaceSel(csText);
			SetFontColor(RGB(0,0,0));
			return;	
		}

		if(Asb==0)//���乿��
		{
			if(bJLoad&&Klxl==0)//���к��������µĶ�����
			{
				csText=L"һ�����乹��ֻ�乿��ʱ�����к��������µĶ�������б�����ܼ������������й�ʽ����\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);
				csText=L"V �� 1.750000 * ft * b * ho / (��+1)+ fyv * Asv / S * ho		(GB50010  7-5-4-4)\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);

				Asv=(V-1.75*ft*b*h0/(Rmd+1))*S/(fyv*h0);

				csText=L"�乿�����Asv �� (V - 1.750000 * ft * b * ho/(��+1)) * S / (Fyv * ho)\n			�� (";
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
				csText+=csData+L"mm��";	
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);					
			}
			else
			{
				csText=L"һ�����乹��ֻ�乿��ʱ����б�����ܼ������������й�ʽ����\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);
				csText=L"V �� 0.700000 * ft * b * ho + 1.250000 * fyv * Asv / S * ho		(GB50010  7-5-4-2)\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);

				Asv=(V-0.7*ft*b*h0)*S/(1.25*fyv*h0);

				csText=L"�乿�����Asv �� (V - 0.700000 * ft * b * ho) * S / (1.250000 * Fyv * ho)\n			�� (";
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
				csText+=csData+L"mm��";	
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);	
			}
		}
		else
		{
			if(bJLoad&&Klxl==0)//���к��������µĶ�����
			{
				csText=L"һ�����乹�����ù���������ʱ�����к��������µĶ�������б�����ܼ������������й�ʽ����\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);
				csText=L"V �� 1.750000*ft*b*ho/(��+1) + fyv*Asv/S*ho + 0.800000*fy*Asb*sin(��s) 		(GB50010  7-5-5)\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);

				Asv=(V-1.75*ft*b*h0/(Rmd+1)-0.8*fy*Asb*sin(Arf))*S/(fyv*h0);

				csText=L"�乿�����Asv �� (V - 1.750000 * ft * b * ho/(��+1) - 0.800000 * fy * Asb * sin(��s)) * S / (Fyv * ho)\n		�� (";
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
				csText+=csData+L"mm��";	
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);					
			}
			else
			{
				csText=L"һ�����乹�����ù���������ʱ����б�����ܼ������������й�ʽ����\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);
				csText=L"V �� 0.7 * ft * b * ho + 1.25 * fyv * Asv / S * ho + 0.8*fy*Asb*sin(��s) 		(GB50010  7-5-5)\n";
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);

				Asv=(V-0.7*ft*b*h0-0.8*fy*Asb*sin(Arf))*S/(1.25*fyv*h0);

				csText=L"�乿�����Asv �� (V - 0.700000 * ft * b * ho - 0.800000 * fy * Asb * sin(��s)) * S / (1.250000 * Fyv * ho)\n			�� (";
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
				csText+=csData+L"mm��";	
				SimplifyString(csText);
				m_pRichEdit->ReplaceSel(csText);	
			}
		}
	}
	m_pRichEdit->ReplaceSel(L"\n");	

	csText=L"�����Ҫ��\n";
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);	
	float Asvmin=0;
	int Dmin=0,Smax=0;
	if(bGouZaoOnly)
	{
		csText=L"��Ϊ��V �� 0.7 * ft * b * ho ��";

		if(h>150 && h<=300){ csText+=L"150 �� h �� 300 \n"; Smax=200;}
		else if(h>300 && h<=500) {csText+=L"300 �� h �� 500 \n"; Smax=300;}
		else if(h>500 && h<=800) {csText+=L"500 �� h �� 800 \n"; Smax=350;}
		else if(h>800) {csText+=L"800 �� h \n"; Smax=400;}
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	

		if(h>800) Dmin=8;
		else Dmin=6;

		csText=L"������Сֱ��Dmin��";
		csData.Format(L"%d",Dmin);
		csText+=csData+L"mm�����������Smax��";
		csData.Format(L"%d",Smax);
		csText+=csData+L"mm\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	

		float Asvmin=Dmin*Dmin*PI/4*S/Smax;

		csText=L"Dmin��Smax���乿�����Asv#�� Dmin ^ 2 * �� / 4 * S / Smax ��";
		csData.Format(L"%f",Asvmin);
		csText+=csData+L"mm\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	
	}
	else
	{
		csText=L"��Ϊ��V �� 0.7 * ft * b * ho ��";

		if(h>150 && h<=300){ csText+=L"150 �� h �� 300 \n"; Smax=200;}
		else if(h>300 && h<=500) {csText+=L"300 �� h �� 500 \n"; Smax=300;}
		else if(h>500 && h<=800) {csText+=L"500 �� h �� 800 \n"; Smax=350;}
		else if(h>800) {csText+=L"800 �� h \n"; Smax=400;}
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	

		if(h>800) Dmin=8;
		else Dmin=6;

		csText=L"������Сֱ��Dmin��";
		csData.Format(L"%d",Dmin);
		csText+=csData+L"mm�����������Smax��";
		csData.Format(L"%d",Smax);
		csText+=csData+L"mm\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	

		Asvmin=(0.24*ft/fyv)*b*Smax;
		csText=L"��С�乿�����Asv,min �� (0.240000 * ft / fyv) * b * Smax\n			��(0.240000*";
		csData.Format(L"%f",ft);
		csText+=csData+L"/";
		csData.Format(L"%f",fyv);
		csText+=csData+L")*";
		csData.Format(L"%d",b);
		csText+=csData+L"*";
		csData.Format(L"%d",Smax);
		csText+=csData+L" �� ";
		csData.Format(L"%f",Asvmin);
		csText+=csData+L"mm\n";
		SimplifyString(csText);
		m_pRichEdit->ReplaceSel(csText);	
	}
	m_pRichEdit->ReplaceSel(L"\n");	
	csText=L"Asv,min �� ";
	csData.Format(L"%f",Asvmin);
	csText+=csData+L"mm	  ������Сֱ����";
	csData.Format(L"%d",Dmin);
	csText+=csData+L"mm    ����� @";
	csData.Format(L"%d",Smax);
	csText+=csData+L"mm\n";
	SimplifyString(csText);
	m_pRichEdit->ReplaceSel(csText);	
}