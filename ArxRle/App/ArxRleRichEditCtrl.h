/********************************************************************
	Copyright (c) 2003 Chao Zuo. All rights reserved.

	Email: suncho@vip.sina.com
	
	Notice:	  If this code works, it was written by Chao Zuo.
		Else, I don't know who wrote it.

			  I Wrote this code for all software developers in civil engineering,
		and hope it help you.

			  Have any question, please email me. 
*********************************************************************/

#ifndef ARXRLE_RICHEDITCTRL_H
#define ARXRLE_RICHEDITCTRL_H

#include <afxpriv.h>
#include <afxcmn.h>
#include <AfxRich.h>


/////////////////////////////////////////////////////////////////////////////
// ArxRleRichEditCtrl window
// Helper Structures
struct SCookieString
{ long lStart;
  long lSize;
  const CString *pInText;
  CString *pOutText;
};
struct SCookieByteArray
{ long lStart;
  long lSize;
  const CByteArray *pInText;
  CByteArray *pOutText;
};

struct SCookieFile
{ long lStart;
  long lSize;
  const CString *pFilename;
  CFile   fileInText;
  CFile   fileOutText;
};

class ArxRleRichEditCtrl : public CRichEditCtrl
{

// Construction / Destruction
public:
	ArxRleRichEditCtrl();
	virtual ~ArxRleRichEditCtrl();

// Attributes
public:
// Character and Font Attributes
	int IsBold(void);
	int IsItalic(void);
	int IsUnderlined(void);
	int IsStrikeout(void);
	int IsProtected(void);
	int IsLinked(void);

    void SetBold(void);
	void SetItalic(void);
	void SetUnderlined(void);
	void SetStrikeout(void);
	void SetProtected(void);
	void SetLink(void);

	int  GetFontSize(void);
	void SetFontSize(int nPointSize);
	CString GetFontName(void);
	void SetFontName(const CString strFontName);
    void SetColour(COLORREF color);

// Paragraph Attributes
	int IsRight(void);
	int IsLeft(void);
	int IsCentered(void);
	int IsJustified(void);
	int IsBulleted(void);
	
	void SetRight(void);
	void SetLeft(void);
	void SetCenter(void);
	void SetJustify(void);
	void SetBullet(void);

//	PARAFORMAT GetParagraphFormat();
// Visual Appearance
    void SetWordWrap(const bool bOn=true, const int iLineWidth=0);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ArxRleRichEditCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
// Reading and Writing
	void SetRTF(const CString strText);
	void SetRTF(const CByteArray& arrRTF);
	void SetRTF(const UINT resID);
    void LoadRTF(const CString strFilename);

    void GetRTF(CString& strText, const bool bAsRTF=true);
    void GetRTF(CByteArray& arrText, const bool bAsRTF=true);
    void WriteRTF(const CString strFilename, const bool bAsRTF=true);

	// Generated message map functions
protected:
	//{{AFX_MSG(ArxRleRichEditCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
// StreamIn and StreamOut methods
	static DWORD CALLBACK StreamInCString(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	static DWORD CALLBACK StreamInCByteArray(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	static DWORD CALLBACK StreamInCFile(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);

	static DWORD CALLBACK StreamOutCString(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb);
	static DWORD CALLBACK StreamOutCByteArray(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb);
	static DWORD CALLBACK StreamOutCFile(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
};

#endif // !ARXRLE_RICHEDITCTRL_H
