// ArxRleUiTdcSpaOutResult.h: interface for the ArxRleUiTdcSpaOutResult class.
//

#ifndef ARXRLE_UITDC_SPA_OUTRESULT_H
#define ARXRLE_UITDC_SPA_OUTRESULT_H

#include "Resource.h"
#include "App/ArxRleRichEditCtrl.h"
#include "App/ArxRleButton.h"


// ArxRleUiTdcSpaOutResult 对话框

class ArxRleUiTdcSpaOutResult : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcSpaOutResult)

public:
	ArxRleUiTdcSpaOutResult();   // 标准构造函数
	virtual ~ArxRleUiTdcSpaOutResult();

	// 对话框数据
	enum { IDD = ARXRLE_TDC_STRUCT_SPA_OUTRESULT };
	
public:
	void ShowBeamSectionText();
	void ShowBeamCracksText();
	void ShowColumnStrengthText();
	void ShowCircleStrengthText();
	void ShowWallStrengthText();

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	void SimplifyString(CString &cs);
	void Beam_Moment_Rectangle(float Ro,float M,int b,int h,int asd,int asu,float Fc,
		float Ft, float a1,float Fy,float Fyc,float Asc,float ybxsb,float pmin0);

	void Beam_Moment_TSharp(float Ro,float M,int b,int h,int bfc,int hfc,
		int asd,int asu,float Fc,float Ft, float a1,float Fy,float Fyc,float Asc,
		float ybxsb,float pmin0);

	void Beam_Design(int KJmLx,int b,int h,int Bfu,int Hfu,int Bfd,int Hfd,
		int asu,int asd,int Span,float e0,int Fcuk,CString csTringFy,CString csTringFyc,CString csTringFyv,
		float Asc,float Asb,float Arf,float S,float pmin0,BOOL bWan,BOOL bLa,BOOL bNiu,
		BOOL bXjm,BOOL bEq,BOOL bJLoad, BOOL bDuiCh, BOOL bJunY,int Kzdj,
		int Klxl,float Rmd,float Ro,float M,float N,float V,float T);
	void Beam_Vector(float V,int b,int h,int hw,int asd,int fcuk,float fc,float ft,float fy,float Asb,float Arf,float Rmd,float S,
		float fyv,int Klxl,BOOL bJLoad);

	// Generated message map functions
	//{{AFX_MSG(COutResultDlg)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClickBtnOpen();
	afx_msg void OnClickBtnSave();
	afx_msg void OnClickBtnBold();
	afx_msg void OnClickBtnItalic();
	afx_msg void OnClickBtnUnderline();
	afx_msg void OnClickBtnStrikeout();
	afx_msg void OnClickBtnFont();
	afx_msg void OnClickBtnColor();
	afx_msg void OnClickBtnLeft();
	afx_msg void OnClickBtnCenter();
	afx_msg void OnClickBtnRight();
	afx_msg void OnClickBtnBullet();
	DECLARE_MESSAGE_MAP()

private:
	// Sizes for Dialog and RichEditControl
	CSize     m_size_DlgMinSize;
	CSize     m_size_DlgClientSize;
	CSize     m_size_EditMinSize;
	CRect     m_rect_EditMinRect;
	// Control bar
	CToolBar	m_wndFormatBar;
	ArxRleRichEditCtrl*	m_pRichEdit;
	CImageList m_imgList;


	ArxRleButton	m_ButtonOpen;
	ArxRleButton	m_ButtonSave;
	ArxRleButton	m_ButtonBold;
	ArxRleButton	m_ButtonXieTi;
	ArxRleButton	m_ButtonUnderLine;
	ArxRleButton	m_ButtonMiddleLine;
	ArxRleButton	m_ButtonFont;
	ArxRleButton	m_ButtonColor;
	ArxRleButton	m_ButtonLeft;
	ArxRleButton	m_ButtonCenter;
	ArxRleButton	m_ButtonRight;
	ArxRleButton	m_ButtonNumber;

	void SetLeft();
	void SetCenter();
	void SetRight();
	void SetFontSize(int iSize);
	void SetFontColor(COLORREF rgb);
};

#endif //ARXRLE_UITDC_SPA_OUTRESULT_H