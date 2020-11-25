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

#include "ArxRleFont.h"

ArxRleFont::ArxRleFont()
{
	lf.lfHeight=-12;
	lf.lfWidth=0;
	lf.lfEscapement=0;
	lf.lfOrientation=0;
	lf.lfWeight=FW_NORMAL;
	lf.lfItalic=0;
	lf.lfUnderline=0;
	lf.lfStrikeOut=0;
	lf.lfCharSet=DEFAULT_CHARSET;	//ANSI_CHARSET;
	lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfQuality=PROOF_QUALITY;
	lf.lfPitchAndFamily=VARIABLE_PITCH | FF_ROMAN;
	wcsncpy(lf.lfFaceName, L"Times New Roman", _tcslen(lf.lfFaceName));

	CreateFontIndirect(&lf);

	fontColor=0;
	hDC=NULL;
}

ArxRleFont::ArxRleFont(CString facename)
{
	lf.lfHeight=-12;
	lf.lfWidth=0;
	lf.lfEscapement=0;
	lf.lfOrientation=0;
	lf.lfWeight=FW_NORMAL;
	lf.lfItalic=0;
	lf.lfUnderline=0;
	lf.lfStrikeOut=0;
	lf.lfCharSet=DEFAULT_CHARSET;	//ANSI_CHARSET;
	lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfQuality=PROOF_QUALITY;
	lf.lfPitchAndFamily=VARIABLE_PITCH | FF_ROMAN;
	wcsncpy(lf.lfFaceName, (LPCTSTR)facename, _tcslen(lf.lfFaceName));

	CreateFontIndirect(&lf);

	fontColor=0;
	hDC=NULL;
}

ArxRleFont::ArxRleFont(LOGFONT& logfont)
{
	lf=logfont;
	CreateFontIndirect(&lf);

	fontColor=0;
	hDC=NULL;
}

ArxRleFont::ArxRleFont(CFont font)
{
	HFONT hFont=(HFONT)font;
	Attach((HFONT)hFont);

	GetLogFont(&lf);

	fontColor=0;
	hDC=NULL;
}

ArxRleFont::~ArxRleFont()
{
}

LONG ArxRleFont::SetHeight(LONG height)
{
	LONG l=lf.lfHeight;

	DeleteObject();
	lf.lfHeight=height;
	CreateFontIndirect(&lf);

	return l;
}

LONG ArxRleFont::SetHeightA(LONG height)
{
	LONG l=lf.lfWidth;

	DeleteObject();
	if (height>0)
		height=0-height;
	lf.lfHeight=height;
	CreateFontIndirect(&lf);

	return l;
}

LONG ArxRleFont::SetWidth(LONG width)
{
	LONG l=lf.lfWidth;

	DeleteObject();
	lf.lfWidth=width;
	CreateFontIndirect(&lf);

	return l;
}

LONG ArxRleFont::SetEscapement(LONG esc)
{
	LONG l=lf.lfEscapement;

	DeleteObject();
	lf.lfEscapement=esc;
	CreateFontIndirect(&lf);

	return l;
}

LONG ArxRleFont::SetOrientation(LONG or)
{
	LONG l=lf.lfOrientation;

	DeleteObject();
	lf.lfOrientation=or;
	CreateFontIndirect(&lf);

	return l;
}

LONG ArxRleFont::SetWeight(LONG weight)
{
	LONG l=lf.lfWeight;

	DeleteObject();
	lf.lfWeight=weight;
	CreateFontIndirect(&lf);

	return l;
}

BYTE ArxRleFont::SetCharset(BYTE charset)
{
	BYTE b=lf.lfCharSet;

	DeleteObject();
	lf.lfCharSet=charset;
	CreateFontIndirect(&lf);

	return b;
}

BYTE ArxRleFont::SetOutPrecision(BYTE op)
{
	BYTE b=lf.lfOutPrecision;

	DeleteObject();
	lf.lfOutPrecision=op;
	CreateFontIndirect(&lf);

	return b;
}

BYTE ArxRleFont::SetClipPrecision(BYTE cp)
{
	BYTE b=lf.lfClipPrecision;

	DeleteObject();
	lf.lfClipPrecision=cp;
	CreateFontIndirect(&lf);

	return b;
}

BYTE ArxRleFont::SetQuality(BYTE qual)
{
	BYTE b=lf.lfQuality;

	DeleteObject();
	lf.lfQuality=qual;
	CreateFontIndirect(&lf);

	return b;
}

BYTE ArxRleFont::SetPitchAndFamily(BYTE paf)
{
	BYTE b=lf.lfPitchAndFamily;

	DeleteObject();
	lf.lfPitchAndFamily=paf;
	CreateFontIndirect(&lf);

	return b;
}

CString ArxRleFont::SetFaceName(CString facename)
{
	CString str=lf.lfFaceName;

	DeleteObject();
	wcsncpy(lf.lfFaceName, (LPCTSTR)facename, _tcslen(lf.lfFaceName));
	CreateFontIndirect(&lf);

	return str;
}

LPCTSTR ArxRleFont::SetFaceName(LPCTSTR facename)
{
	LPCTSTR str=lf.lfFaceName;

	DeleteObject();
	wcsncpy(lf.lfFaceName, (LPCTSTR)facename, _tcslen(lf.lfFaceName));
	CreateFontIndirect(&lf);

	return str;
}

BOOL ArxRleFont::SetBold(BOOL B)
{
	BOOL b;

	if (B)
		b=SetWeight(FW_BOLD);
	else
		b=SetWeight(FW_NORMAL);

	if (b >= FW_MEDIUM)
		return TRUE;
	else
		return FALSE;
}

BOOL ArxRleFont::SetItalic(BOOL i)
{
	BOOL b=(BOOL)lf.lfItalic;

	DeleteObject();
	lf.lfItalic=i;
	CreateFontIndirect(&lf);

	return b;
}

BOOL ArxRleFont::SetUnderline(BOOL u)
{
	BOOL b=(BOOL)lf.lfUnderline;

	DeleteObject();
	lf.lfUnderline=u;
	CreateFontIndirect(&lf);

	return b;
}

BOOL ArxRleFont::SetStrikeOut(BOOL s)
{
	BOOL b=(BOOL)lf.lfStrikeOut;

	DeleteObject();
	lf.lfStrikeOut=s;
	CreateFontIndirect(&lf);

	return b;
}

void ArxRleFont::SetLogFont(LOGFONT& logfont)
{
	lf=logfont;
	DeleteObject();
	CreateFontIndirect(&lf);
}

LONG ArxRleFont::GetHeight()
{
	return lf.lfHeight;
}

LONG ArxRleFont::GetWidth()
{
	return lf.lfWidth;
}

LONG ArxRleFont::GetEscapement()
{
	return lf.lfEscapement;
}

LONG ArxRleFont::GetOrientation()
{
	return lf.lfEscapement;
}

LONG ArxRleFont::GetWeight()
{
	return lf.lfWeight;
}

BYTE ArxRleFont::GetCharset()
{
	return lf.lfCharSet;
}

BYTE ArxRleFont::GetOutPrecision()
{
	return lf.lfOutPrecision;
}

BYTE ArxRleFont::GetClipPrecision()
{
	return lf.lfClipPrecision;
}

BYTE ArxRleFont::GetQuality()
{
	return lf.lfQuality;
}

BYTE ArxRleFont::GetPitchAndFamily()
{
	return lf.lfPitchAndFamily;
}

LPCTSTR ArxRleFont::GetFaceName()
{
	return lf.lfFaceName;
}

BOOL ArxRleFont::GetBold()
{
	return lf.lfWeight > FW_MEDIUM ? TRUE : FALSE;
}

BOOL ArxRleFont::GetItalic()
{
	return (BOOL)lf.lfItalic;
}

BOOL ArxRleFont::GetUnderline()
{
	return (BOOL)lf.lfUnderline;
}

BOOL ArxRleFont::GetStrikeOut()
{
	return (BOOL)lf.lfStrikeOut;
}

CString ArxRleFont::ContractFont()
{
	CString str, color;

	str.Format(L"%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%s",
		lf.lfHeight,
		lf.lfWidth,
		lf.lfEscapement,
		lf.lfOrientation,
		lf.lfWeight,
		lf.lfItalic,
		lf.lfUnderline,
		lf.lfStrikeOut,
		lf.lfCharSet,
		lf.lfOutPrecision,
		lf.lfClipPrecision,
		lf.lfQuality,
		lf.lfPitchAndFamily,
		lf.lfFaceName);
	color.Format(L"%u", fontColor);
	str+=L",";
	str+=color;

	return str;
}

void ArxRleFont::ExtractFont(CString& str)
{
	lf.lfHeight=_tstol(GetToken(str, L","));
	lf.lfWidth=_tstol(GetToken(str, L","));
	lf.lfEscapement=_tstol(GetToken(str, L","));
	lf.lfOrientation=_tstol(GetToken(str, L","));
	lf.lfWeight=_tstol(GetToken(str, L","));
	lf.lfItalic=_tstoi(GetToken(str, L","));
	lf.lfUnderline=_tstoi(GetToken(str, L","));
	lf.lfStrikeOut=_tstoi(GetToken(str, L","));
	lf.lfCharSet=_tstoi(GetToken(str, L","));
	lf.lfOutPrecision=_tstoi(GetToken(str, L","));
	lf.lfClipPrecision=_tstoi(GetToken(str, L","));
	lf.lfQuality=_tstoi(GetToken(str, L","));
	wcsncpy(lf.lfFaceName, (LPCTSTR)GetToken(str, L","), _tcslen(lf.lfFaceName));

	DeleteObject();
	CreateFontIndirect(&lf);

	fontColor=_tstol(str);
}

CString ArxRleFont::GetToken(CString& str, LPCTSTR c)
{
	int pos;
	CString token;

	pos=str.Find(c);
	token=str.Left(pos);
	str=str.Mid(pos+1);

	return token;
}

void ArxRleFont::GetFontFromDialog(CFont *f, DWORD *color,
								  CDC *pPrinterDC, CWnd *pParentWnd)
{
	LOGFONT tlf;
	if (f==NULL)
		tlf=lf;
	else
		f->GetLogFont(&tlf);

	CFontDialog dlg(&tlf, CF_EFFECTS | CF_SCREENFONTS,
		pPrinterDC, pParentWnd);
	dlg.m_cf.rgbColors=fontColor;

	if (dlg.DoModal()==IDOK)
	{
		dlg.GetCurrentFont(&lf);
		DeleteObject();
		CreateFontIndirect(&lf);
		f=(CFont *)this;
		color=&dlg.m_cf.rgbColors;
		SetFontColor(dlg.m_cf.rgbColors);
	}
}

void ArxRleFont::SetFontColor(COLORREF color)
{
	fontColor=color;
	if (hDC!=NULL)
		::SetTextColor(hDC, color);
}

COLORREF ArxRleFont::GetFontColor()
{
	return fontColor;
}

void ArxRleFont::SetDC(HDC dc)
{
	hDC=dc;
}


