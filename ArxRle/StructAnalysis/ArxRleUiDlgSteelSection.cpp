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


#include "ArxRleUiDlgSteelSection.h"
#include "AcadUtils\ArxRleUtils.h"
#include "DbEntity\ArxRleEntityClass.h"


// ArxRleUiDlgSteelSection 对话框
IMPLEMENT_DYNAMIC(ArxRleUiDlgSteelSection, CAcUiDialog)

ArxRleUiDlgSteelSection::ArxRleUiDlgSteelSection(CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/)
	: CAcUiDialog(ArxRleUiDlgSteelSection::IDD, pParent, hInstance)
{
	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);
	m_pToolTip = new CToolTipCtrl;
	m_item = 0;
}

ArxRleUiDlgSteelSection::~ArxRleUiDlgSteelSection()
{
	if(m_pToolTip != NULL) delete m_pToolTip;
	m_pToolTip = NULL;
}

void ArxRleUiDlgSteelSection::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_STEEL_SECTION_SC_PREVIEW, m_wndPreview);
	DDX_Control(pDX, ARXRLE_STEEL_SECTION_CB_TYPE,    m_cbType);
	DDX_Control(pDX, ARXRLE_STEEL_SECTION_BN_DRAW,    m_bnDraw);
	DDX_Control(pDX, ARXRLE_STEEL_SECTION_LC_TYPES,   m_lstTypes);
	DDX_Control(pDX, ARXRLE_STEEL_SECTION_LC_VALUES,  m_lstValues);
}


BEGIN_MESSAGE_MAP(ArxRleUiDlgSteelSection, CAcUiDialog)
	ON_WM_PAINT()
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(ARXRLE_STEEL_SECTION_BN_DRAW, OnBnClickedBtnDraw)
	ON_CBN_SELCHANGE(ARXRLE_STEEL_SECTION_CB_TYPE, OnCbnSelchangeCbType)
	ON_NOTIFY(NM_CLICK, ARXRLE_STEEL_SECTION_LC_TYPES,OnNMClickSteelSectionLcTypes)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// ArxRleUiDlgSteelSection 消息处理程序
BOOL ArxRleUiDlgSteelSection::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	::SetWindowLong(m_hWnd, GWL_EXSTYLE, ::GetWindowLong(m_hWnd, GWL_EXSTYLE) |  WS_EX_LAYERED );
	SetLayeredWindowAttributes(0, 255 * 100/100 , LWA_ALPHA );

	// TODO:  在此添加额外的初始化
	SetIcon(m_hIcon,TRUE);
	SetIcon(m_hIcon,FALSE);

	m_pToolTip->Create(this);

	m_bnDraw.SetIcon(ARXRLE_ICON_CORRECT);
	m_bnDraw.SetAlign(ArxRleButton::ST_ALIGN_HORIZ);
	m_bnDraw.SetFlat();
	m_bnDraw.ActivateTooltip();
	m_bnDraw.SetTooltipText(L"绘制型钢界面");

	m_cbType.InsertString(0,L"热轧普通工字钢");
	m_cbType.InsertString(1,L"热轧轻型工字钢");
	m_cbType.InsertString(2,L"热轧普通槽钢");
	m_cbType.InsertString(3,L"热轧轻型槽钢");
	m_cbType.InsertString(4,L"热轧等边角钢");
	m_cbType.InsertString(5,L"热轧不等边角钢");
	m_cbType.InsertString(6,L"热轧宽翼缘H形钢");
	m_cbType.InsertString(7,L"热轧窄翼缘H形钢");
	m_cbType.InsertString(8,L"普通无缝圆钢管");
	m_cbType.InsertString(9,L"普通焊接圆钢管");
	m_cbType.SetCurSel(0);
	m_pToolTip->AddTool(&m_cbType,L"选择型钢类型");

	m_lstTypes.SetColumnHeader(_T("型钢型号, 80"));
	m_lstTypes.SetGridLines(TRUE); // SHow grid lines
	for(int i=0; i<31; i++)
	{
		const int idx = m_lstTypes.InsertItem(i, steel_gzg[i].s);
		// Set the 3rd column background color to yellow, text color to blue
		m_lstTypes.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(238, 238, 238));
	}

	m_lstValues.SetColumnHeader(_T("参数, 100; 数值, 150"));
	m_lstValues.SetGridLines(TRUE); // SHow grid lines
	m_lstValues.SetEditable(TRUE); // Allow sub-text edit

	LPCTSTR name[16] = {L"h (mm)",L"b(mm)",L"d(mm)",L"t(mm)",L"r(mm)",L"r1(mm)",L"As(cm2)",L"G (Kg/m)",L"Af (m2/m)",L"Ix (cm4)",L"Wx (cm3)",L"Sx (cm3)",L"ix (cm3)",L"Iy (cm4)",L"Wy (cm3)",L"iy (cm)"};
	double vals[16] = {steel_gzg[m_item].h,steel_gzg[m_item].b,steel_gzg[m_item].d,steel_gzg[m_item].t,steel_gzg[m_item].r,steel_gzg[m_item].r1,steel_gzg[m_item].As,steel_gzg[m_item].G,steel_gzg[m_item].Af,steel_gzg[m_item].Ix,steel_gzg[m_item].Wx,steel_gzg[m_item].Sx,steel_gzg[m_item].ix,steel_gzg[m_item].Iy,steel_gzg[m_item].Wy,steel_gzg[m_item].iy};

	m_lstValues.InsertItem(0, L"s");
	m_lstValues.SetItemText(0, 1, steel_gzg[m_item].s);

	for(int i=0; i<16; i++)
	{
		const int idx = m_lstValues.InsertItem(i+1, name[i]);
		m_lstValues.SetItemText(idx, 0, name[i]);
		m_lstValues.SetItemText(idx, 1, vals[i]);
	}

	// 	m_etParamets[0].SetWindowText(L"290000");
	// 	m_etParamets[1].SetWindowText(L"614.3789");
	// 	m_etParamets[2].SetWindowText(L"30000");
	// 	m_etParamets[3].SetWindowText(L"3.5345");
	// 	m_etParamets[4].SetWindowText(L"-20");
	// 	m_etParamets[5].SetWindowText(L"289000");
	// 	m_etParamets[6].SetWindowText(L"290000");
	// 	m_etParamets[7].SetWindowText(L"200");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ArxRleUiDlgSteelSection::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	
	CString path = GetCurPath()+L"\\ArxRle\\steel.dwg";
	if(FileExist(path))
	{
		m_wndPreview.EnableWindow(TRUE);
		if(!acdbDisplayPreviewFromDwg(path, m_wndPreview.m_hWnd))
			ArxRleUtils::stopAlertBox(_T("ERROR: Could not display preview image!"));
	}
	else
		m_wndPreview.EnableWindow(FALSE);
}

BOOL ArxRleUiDlgSteelSection::PreTranslateMessage(MSG *pMsg)
{
	if( pMsg->message == WM_MOUSEMOVE || pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP)
	{
		m_pToolTip->RelayEvent(pMsg);
	}
	return CAcUiDialog::PreTranslateMessage(pMsg);
}

LRESULT ArxRleUiDlgSteelSection::OnAcadKeepFocus(WPARAM, LPARAM)
{
	return TRUE;
}

void ArxRleUiDlgSteelSection::OnBnClickedBtnDraw()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginEditorCommand();
	switch (m_cbType.GetCurSel())
	{
	case 0:
		DrawGongSteelSection(steel_gzg[m_item]);
		break;
	case 1:
		DrawGongSteelSection(steel_gzg_[m_item]);
		break;
	case 2:
		DrawCaoSteelSection(steel_cg[m_item]);
		break;
	case 3:
		DrawCaoSteelSection(steel_cg_[m_item]);
		break;
	case 4:
		DrawJiaoSteelSection(steel_jg[m_item]);
		break;
	case 5:
		DrawJiaoSteelSection2(steel_jg_[m_item]);
		break;
	case 6:
		DrawHSteelSection(steel_hg[m_item]);
		break;
	case 7:
		DrawHSteelSection(steel_hg_[m_item]);
		break;
	case 8:
		DrawGuanSteelSection(steel_gg[m_item]);
		break;
	case 9:
		DrawGuanSteelSection(steel_gg_[m_item]);
		break;
	default:
		CancelEditorCommand();
	}
	CompleteEditorCommand();
}

void ArxRleUiDlgSteelSection::OnCbnSelchangeCbType()
{
	// TODO: 在此添加控件通知处理程序代码
	m_lstTypes.DeleteAllItems();
	switch (m_cbType.GetCurSel())
	{
	case 0://普通工字钢
		{
			for(int i=0; i<31; i++)
			{
				const int idx = m_lstTypes.InsertItem(i, steel_gzg[i].s);
				m_lstTypes.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(238, 238, 238));
			}
		}
		break;
	case 1://轻型工字钢
		{
			for(int i=0; i<27; i++)
			{
				const int idx = m_lstTypes.InsertItem(i, steel_gzg_[i].s);
				m_lstTypes.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(238, 238, 238));
			}
		}
		break;
	case 2://普通槽钢
		{
			for(int i=0; i<30; i++)
			{
				const int idx = m_lstTypes.InsertItem(i, steel_cg[i].s);
				m_lstTypes.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(238, 238, 238));
			}
		}
		break;
	case 3://轻型槽钢
		{
			for(int i=0; i<22; i++)
			{
				const int idx = m_lstTypes.InsertItem(i, steel_cg_[i].s);
				m_lstTypes.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(238, 238, 238));
			}
		}
		break;
	case 4://等边角钢
		{
			for(int i=0; i<82; i++)
			{
				const int idx = m_lstTypes.InsertItem(i, steel_jg[i].s);
				m_lstTypes.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(238, 238, 238));
			}
		}
		break;
	case 5://不等边角钢
		{
			for(int i=0; i<65; i++)
			{
				const int idx = m_lstTypes.InsertItem(i, steel_jg_[i].s);
				m_lstTypes.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(238, 238, 238));
			}
		}
		break;
	case 6://宽翼缘H钢
		{
			for(int i=0; i<85; i++)
			{
				const int idx = m_lstTypes.InsertItem(i, steel_hg[i].s);
				m_lstTypes.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(238, 238, 238));
			}
		}
		break;
	case 7://窄翼缘H钢
		{
			for(int i=0; i<18; i++)
			{
				const int idx = m_lstTypes.InsertItem(i, steel_hg_[i].s);
				m_lstTypes.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(238, 238, 238));
			}
		}
		break;
	case 8://无缝钢管
		{
			for(int i=0; i<288; i++)
			{
				const int idx = m_lstTypes.InsertItem(i, steel_gg[i].s);
				m_lstTypes.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(238, 238, 238));
			}
		}
		break;
	case 9://普通焊管
		{
			for(int i=0; i<288; i++)
			{
				const int idx = m_lstTypes.InsertItem(i, steel_gg_[i].s);
				m_lstTypes.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(238, 238, 238));
			}
		}
		break;
	}
}

void ArxRleUiDlgSteelSection::OnNMClickSteelSectionLcTypes(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_item = pNMItemActivate->iItem;

	m_lstValues.DeleteAllItems();
	switch (m_cbType.GetCurSel())
	{
	case 0:
		{
			LPCTSTR name[16] = {L"h (mm)",L"b(mm)",L"d(mm)",L"t(mm)",L"r(mm)",L"r1(mm)",L"As(cm2)",L"G (Kg/m)",L"Af (m2/m)",L"Ix (cm4)",L"Wx (cm3)",L"Sx (cm3)",L"ix (cm3)",L"Iy (cm4)",L"Wy (cm3)",L"iy (cm)"};
			double vals[16] = {steel_gzg[m_item].h,steel_gzg[m_item].b,steel_gzg[m_item].d,steel_gzg[m_item].t,steel_gzg[m_item].r,steel_gzg[m_item].r1,steel_gzg[m_item].As,steel_gzg[m_item].G,steel_gzg[m_item].Af,steel_gzg[m_item].Ix,steel_gzg[m_item].Wx,steel_gzg[m_item].Sx,steel_gzg[m_item].ix,steel_gzg[m_item].Iy,steel_gzg[m_item].Wy,steel_gzg[m_item].iy};

			m_lstValues.InsertItem(0, L"s");
			m_lstValues.SetItemText(0, 1, steel_gzg[m_item].s);

			for(int i=0; i<16; i++)
			{
				const int idx = m_lstValues.InsertItem(i+1, name[i]);
				m_lstValues.SetItemText(idx, 0, name[i]);
				m_lstValues.SetItemText(idx, 1, vals[i]);
			}
		}
		break;
	case 1:
		{
			LPCTSTR name[16] = {L"h (mm)",L"b(mm)",L"d(mm)",L"t(mm)",L"r(mm)",L"r1(mm)",L"As(cm2)",L"G (Kg/m)",L"Af (m2/m)",L"Ix (cm4)",L"Wx (cm3)",L"Sx (cm3)",L"ix (cm3)",L"Iy (cm4)",L"Wy (cm3)",L"iy (cm)"};
			double vals[16] = {steel_gzg_[m_item].h,steel_gzg_[m_item].b,steel_gzg_[m_item].d,steel_gzg_[m_item].t,steel_gzg_[m_item].r,steel_gzg_[m_item].r1,steel_gzg_[m_item].As,steel_gzg_[m_item].G,steel_gzg_[m_item].Af,steel_gzg_[m_item].Ix,steel_gzg_[m_item].Wx,steel_gzg_[m_item].Sx,steel_gzg_[m_item].ix,steel_gzg_[m_item].Iy,steel_gzg_[m_item].Wy,steel_gzg_[m_item].iy};

			m_lstValues.InsertItem(0, L"s");
			m_lstValues.SetItemText(0, 1, steel_gzg_[m_item].s);

			for(int i=0; i<16; i++)
			{
				const int idx = m_lstValues.InsertItem(i+1, name[i]);
				m_lstValues.SetItemText(idx, 0, name[i]);
				m_lstValues.SetItemText(idx, 1, vals[i]);
			}
		}
		break;
	case 2:
		{
			LPCTSTR name[19] = {L"h (mm)",L"b(mm)",L"d(mm)",L"t(mm)",L"r(mm)",L"r1(mm)",L"As(cm2)",L"G (Kg/m)",L"Af (m2/m)",L"Ix (cm4)",L"Wx (cm3)",L"Sx (cm3)",L"ix (cm3)",L"Iy (cm4)",L"Wy1 (cm3)",L"Wy2 (cm3)",L"iy (cm)",L"Iy1 (cm4)",L"z0 (cm)"};
			double vals[19] = {steel_cg[m_item].h,steel_cg[m_item].b,steel_cg[m_item].d,steel_cg[m_item].t,steel_cg[m_item].r,steel_cg[m_item].r1,steel_cg[m_item].As,steel_cg[m_item].G,steel_cg[m_item].Af,steel_cg[m_item].Ix,steel_cg[m_item].Wx,steel_cg[m_item].Sx,steel_cg[m_item].ix,steel_cg[m_item].Iy,steel_cg[m_item].Wy1,steel_cg[m_item].Wy2,steel_cg[m_item].iy,steel_cg[m_item].Iy1,steel_cg[m_item].z0};

			m_lstValues.InsertItem(0, L"s");
			m_lstValues.SetItemText(0, 1, steel_cg[m_item].s);

			for(int i=0; i<19; i++)
			{
				const int idx = m_lstValues.InsertItem(i+1, name[i]);
				m_lstValues.SetItemText(idx, 0, name[i]);
				m_lstValues.SetItemText(idx, 1, vals[i]);
			}
		}
		break;
	case 3:
		{
			LPCTSTR name[19] = {L"h (mm)",L"b(mm)",L"d(mm)",L"t(mm)",L"r(mm)",L"r1(mm)",L"As(cm2)",L"G (Kg/m)",L"Af (m2/m)",L"Ix (cm4)",L"Wx (cm3)",L"Sx (cm3)",L"ix (cm3)",L"Iy (cm4)",L"Wy1 (cm3)",L"Wy2 (cm3)",L"iy (cm)",L"Iy1 (cm4)",L"z0 (cm)"};
			double vals[19] = {steel_cg_[m_item].h,steel_cg_[m_item].b,steel_cg_[m_item].d,steel_cg_[m_item].t,steel_cg_[m_item].r,steel_cg_[m_item].r1,steel_cg_[m_item].As,steel_cg_[m_item].G,steel_cg_[m_item].Af,steel_cg_[m_item].Ix,steel_cg_[m_item].Wx,steel_cg_[m_item].Sx,steel_cg_[m_item].ix,steel_cg_[m_item].Iy,steel_cg_[m_item].Wy1,steel_cg_[m_item].Wy2,steel_cg_[m_item].iy,steel_cg_[m_item].Iy1,steel_cg_[m_item].z0};

			m_lstValues.InsertItem(0, L"s");
			m_lstValues.SetItemText(0, 1, steel_cg_[m_item].s);

			for(int i=0; i<19; i++)
			{
				const int idx = m_lstValues.InsertItem(i+1, name[i]);
				m_lstValues.SetItemText(idx, 0, name[i]);
				m_lstValues.SetItemText(idx, 1, vals[i]);
			}
		}
		break;
	case 4:
		{
			LPCTSTR name[19] = {L"b(mm)",L"d(mm)",L"r(mm)",L"As(cm2)",L"G (Kg/m)",L"Af (m2/m)",L"Ix (cm4)",L"Wx1 (cm3)",L"Wx2 (cm3)",L"ix (cm3)",L"Ix0 (cm4)",L"Wx0 (cm3)",L"ix0 (cm3)",L"Ix1 (cm4)",L"Iy0 (cm4)",L"Wy01 (cm3)",L"Wy02 (cm3)",L"iy0 (cm3)",L"z0 (cm)"};
			double vals[19] = {steel_jg[m_item].b,steel_jg[m_item].d,steel_jg[m_item].r,steel_jg[m_item].As,steel_jg[m_item].G,steel_jg[m_item].Af,steel_jg[m_item].Ix,steel_jg[m_item].Wx1,steel_jg[m_item].Wx2,steel_jg[m_item].ix,steel_jg[m_item].Ix0,steel_jg[m_item].Wx0,steel_jg[m_item].ix0,steel_jg[m_item].Ix1,steel_jg[m_item].Iy0,steel_jg[m_item].Wy01,steel_jg[m_item].Wy02,steel_jg[m_item].iy0,steel_jg[m_item].z0};

			m_lstValues.InsertItem(0, L"s");
			m_lstValues.SetItemText(0, 1, steel_jg[m_item].s);

			for(int i=0; i<19; i++)
			{
				const int idx = m_lstValues.InsertItem(i+1, name[i]);
				m_lstValues.SetItemText(idx, 0, name[i]);
				m_lstValues.SetItemText(idx, 1, vals[i]);
			}
		}
		break;
	case 5:
		{
			LPCTSTR name[23] = {L"B(mm)",L"b(mm)",L"d(mm)",L"r(mm)",L"As(cm2)",L"G (Kg/m)",L"Af (m2/m)",L"Ix (cm4)",L"Wx1 (cm3)",L"Wx2 (cm3)",L"ix (cm3)",L"Ix1 (cm4)",L"y0 (cm)",L"Iy (cm4)",L"Wy1 (cm3)",L"Wy2 (cm3)",L"iy (cm3)",L"Iy1 (cm4)",L"x0 (cm)",L"Iu (cm4)",L"Wu (cm3)",L"iu (cm3)",L"tag"};
			double vals[23] = {steel_jg_[m_item].B,steel_jg_[m_item].b,steel_jg_[m_item].d,steel_jg_[m_item].r,steel_jg_[m_item].As,steel_jg_[m_item].G,steel_jg_[m_item].Af,steel_jg_[m_item].Ix,steel_jg_[m_item].Wx1,steel_jg_[m_item].Wx2,steel_jg_[m_item].ix,steel_jg_[m_item].Ix1,steel_jg_[m_item].y0,steel_jg_[m_item].Iy,steel_jg_[m_item].Wy1,steel_jg_[m_item].Wy2,steel_jg_[m_item].iy,steel_jg_[m_item].Iy1,steel_jg_[m_item].x0,steel_jg_[m_item].Iu,steel_jg_[m_item].Wu,steel_jg_[m_item].iu,steel_jg_[m_item].tga};

			m_lstValues.InsertItem(0, L"s");
			m_lstValues.SetItemText(0, 1, steel_jg_[m_item].s);

			for(int i=0; i<23; i++)
			{
				const int idx = m_lstValues.InsertItem(i+1, name[i]);
				m_lstValues.SetItemText(idx, 0, name[i]);
				m_lstValues.SetItemText(idx, 1, vals[i]);
			}
		}
		break;
	case 6:
		{
			LPCTSTR name[13] = {L"h (mm)",L"b(mm)",L"d(mm)",L"t(mm)",L"r(mm)",L"As(cm2)",L"G (Kg/m)",L"Ix (cm4)",L"Wx (cm3)",L"ix (cm3)",L"Iy (cm4)",L"Wy (cm3)",L"iy (cm)"};
			double vals[13] = {steel_hg[m_item].h,steel_hg[m_item].b,steel_hg[m_item].d,steel_hg[m_item].t,steel_hg[m_item].r,steel_hg[m_item].As,steel_hg[m_item].G,steel_hg[m_item].Ix,steel_hg[m_item].Wx,steel_hg[m_item].ix,steel_hg[m_item].Iy,steel_hg[m_item].Wy,steel_hg[m_item].iy};

			m_lstValues.InsertItem(0, L"s");
			m_lstValues.SetItemText(0, 1, steel_hg[m_item].s);

			for(int i=0; i<13; i++)
			{
				const int idx = m_lstValues.InsertItem(i+1, name[i]);
				m_lstValues.SetItemText(idx, 0, name[i]);
				m_lstValues.SetItemText(idx, 1, vals[i]);
			}
		}
		break;
	case 7:
		{
			LPCTSTR name[13] = {L"h (mm)",L"b(mm)",L"d(mm)",L"t(mm)",L"r(mm)",L"As(cm2)",L"G (Kg/m)",L"Ix (cm4)",L"Wx (cm3)",L"ix (cm3)",L"Iy (cm4)",L"Wy (cm3)",L"iy (cm)"};
			double vals[13] = {steel_hg_[m_item].h,steel_hg_[m_item].b,steel_hg_[m_item].d,steel_hg_[m_item].t,steel_hg_[m_item].r,steel_hg_[m_item].As,steel_hg_[m_item].G,steel_hg_[m_item].Ix,steel_hg_[m_item].Wx,steel_hg_[m_item].ix,steel_hg_[m_item].Iy,steel_hg_[m_item].Wy,steel_hg_[m_item].iy};

			m_lstValues.InsertItem(0, L"s");
			m_lstValues.SetItemText(0, 1, steel_hg_[m_item].s);

			for(int i=0; i<13; i++)
			{
				const int idx = m_lstValues.InsertItem(i+1, name[i]);
				m_lstValues.SetItemText(idx, 0, name[i]);
				m_lstValues.SetItemText(idx, 1, vals[i]);
			}
		}
		break;
	case 8:
		{
			LPCTSTR name[8] = {L"d(mm)",L"t(mm)",L"As(cm2)",L"G (Kg/m)",L"Af (m2/m)",L"Iu (cm4)",L"Wu (cm3)",L"iu (cm3)"};
			double vals[8] = {steel_gg[m_item].d,steel_gg[m_item].t,steel_gg[m_item].As,steel_gg[m_item].G,steel_gg[m_item].Af,steel_gg[m_item].Iu,steel_gg[m_item].Wu,steel_gg[m_item].iu};

			m_lstValues.InsertItem(0, L"s");
			m_lstValues.SetItemText(0, 1, steel_gg[m_item].s);

			for(int i=0; i<8; i++)
			{
				const int idx = m_lstValues.InsertItem(i+1, name[i]);
				m_lstValues.SetItemText(idx, 0, name[i]);
				m_lstValues.SetItemText(idx, 1, vals[i]);
			}
		}
		break;
	case 9:
		{
			LPCTSTR name[8] = {L"d(mm)",L"t(mm)",L"As(cm2)",L"G (Kg/m)",L"Af (m2/m)",L"Iu (cm4)",L"Wu (cm3)",L"iu (cm3)"};
			double vals[8] = {steel_gg_[m_item].d,steel_gg_[m_item].t,steel_gg_[m_item].As,steel_gg_[m_item].G,steel_gg_[m_item].Af,steel_gg_[m_item].Iu,steel_gg_[m_item].Wu,steel_gg_[m_item].iu};

			m_lstValues.InsertItem(0, L"s");
			m_lstValues.SetItemText(0, 1, steel_gg_[m_item].s);

			for(int i=0; i<8; i++)
			{
				const int idx = m_lstValues.InsertItem(i+1, name[i]);
				m_lstValues.SetItemText(idx, 0, name[i]);
				m_lstValues.SetItemText(idx, 1, vals[i]);
			}
		}
		break;
	}
	*pResult = 0;
}

void ArxRleUiDlgSteelSection::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rc;
	m_wndPreview.GetWindowRect(&rc);
	ScreenToClient(&rc);
	if(rc.PtInRect(point))
	{
		CString path = GetCurPath()+L"\\ArxRle\\steel.dwg";
		if(FileExist(path))
			ShellExecuteOpen(path);
	}
	CAcUiDialog::OnLButtonDblClk(nFlags, point);
}

void ArxRleUiDlgSteelSection::DrawGongSteelSection(STEELSECTION sec)
{
	ArxRleUiPrPoint prPtBase(_T("插入点"), NULL);
	if(prPtBase.go() != ArxRleUiPrBase::kOk)
		return;

	CPt3d p1(prPtBase.value().x,prPtBase.value().y);
	double b = sec.b;
	double h = sec.h;
	double d = sec.d;
	double t = sec.t;
	double r = sec.r;
	double r1 = sec.r1;
	double h1 = t-(b-d)/4/6;
	double h2 = t+(b-d)/4/6;

	CPt3d p2 = p1+CPt3d(b/2,0);
	CPt3d p3 = p1+CPt3d(b/2,-h1);
	CPt3d p4 = p1+CPt3d(d/2,-h2);
	double a1 = p3.GetAngle(p2);
	double a2 = p3.GetAngle(p4);
	double a = a2-a1;
	double l = r1/tan(a/2);
	CPt3d p31 = p3.GetLineEnd(l,a1);
	CPt3d p32 = p3.GetLineEnd(l,a2);
	CPt3d p5 = p1+CPt3d(d/2,-h+h2);
	a1 = p4.GetAngle(p3);
	a2 = p4.GetAngle(p5);
	a = a2-a1;
	l = r/tan(a/2);
	CPt3d p41 = p4.GetLineEnd(l,a1+PI);
	CPt3d p42 = p4.GetLineEnd(l,a2+PI);
	CPt3d p6 = p1+CPt3d(b/2,-h+h1);
	a1 = p5.GetAngle(p4);
	a2 = p5.GetAngle(p6);
	a = a2-a1;
	l = r/tan(a/2);
	CPt3d p51 = p5.GetLineEnd(l,a1+PI);
	CPt3d p52 = p5.GetLineEnd(l,a2+PI);
	CPt3d p7 = p1+CPt3d(b/2,-h);
	a1 = p6.GetAngle(p5);
	a2 = p6.GetAngle(p7);
	a = a2-a1;
	l = r1/tan(a/2);
	CPt3d p61 = p6.GetLineEnd(l,a1);
	CPt3d p62 = p6.GetLineEnd(l,a2);
	CPt3d p8 = p1+CPt3d(0,-h);
	CPt3d p9 = p1+CPt3d(-b/2,-h);
	CPt3d p10 = p1+CPt3d(-b/2,-h+h1);
	CPt3d p11 = p1+CPt3d(-d/2,-h+h2);
	a1 = p10.GetAngle(p9);
	a2 = p10.GetAngle(p11);
	a = a2-a1;
	l = r1/tan(a/2);
	CPt3d p101 = p10.GetLineEnd(l,a1);
	CPt3d p102 = p10.GetLineEnd(l,a2);
	CPt3d p12 = p1+CPt3d(-d/2,-h2);
	a1 = p11.GetAngle(p10);
	a2 = p11.GetAngle(p12);
	a = a2-a1;
	l = r/tan(a/2);
	CPt3d p111 = p11.GetLineEnd(l,a1+PI);
	CPt3d p112 = p11.GetLineEnd(l,a2+PI);
	CPt3d p13 = p1+CPt3d(-b/2,-h1);
	a1 = p12.GetAngle(p11);
	a2 = p12.GetAngle(p13);
	a = a2-a1;
	l = r/tan(a/2);
	CPt3d p121 = p12.GetLineEnd(l,a1+PI);
	CPt3d p122 = p12.GetLineEnd(l,a2+PI);
	CPt3d p14 = p1+CPt3d(-b/2,0);
	a1 = p13.GetAngle(p12);
	a2 = p13.GetAngle(p14);
	a = a2-a1;
	l = r1/tan(a/2);
	CPt3d p131 = p13.GetLineEnd(l,a1);
	CPt3d p132 = p13.GetLineEnd(l,a2);

	AcDbPolyline* polyline = new AcDbPolyline;
	polyline->addVertexAt(0,p1);
	polyline->addVertexAt(1,p2);
	polyline->addVertexAt(2,p31,-GetArcBulge(p31,p32,r1));
	polyline->addVertexAt(3,p32);
	polyline->addVertexAt(4,p41,GetArcBulge(p41,p42,r));
	polyline->addVertexAt(5,p42);
	polyline->addVertexAt(6,p51,GetArcBulge(p51,p52,r));
	polyline->addVertexAt(7,p52);
	polyline->addVertexAt(8,p61,-GetArcBulge(p61,p62,r1));
	polyline->addVertexAt(9,p62);
	polyline->addVertexAt(10,p7);
	polyline->addVertexAt(11,p8);
	polyline->addVertexAt(12,p9);
	polyline->addVertexAt(13,p101,-GetArcBulge(p101,p102,r1));
	polyline->addVertexAt(14,p102);
	polyline->addVertexAt(15,p111,GetArcBulge(p111,p112,r));
	polyline->addVertexAt(16,p112);
	polyline->addVertexAt(17,p121,GetArcBulge(p121,p122,r));
	polyline->addVertexAt(18,p122);
	polyline->addVertexAt(19,p131,-GetArcBulge(p131,p132,r1));
	polyline->addVertexAt(20,p132);
	polyline->addVertexAt(21,p14);
	polyline->addVertexAt(22,p1);
	AddEntity(polyline);
}

void ArxRleUiDlgSteelSection::DrawCaoSteelSection(STEELSECTION sec)
{
	ArxRleUiPrPoint prPtBase(_T("插入点"), NULL);
	if(prPtBase.go() != ArxRleUiPrBase::kOk)
		return;

	CPt3d p1(prPtBase.value().x,prPtBase.value().y);
	double b = sec.b;
	double h = sec.h;
	double d = sec.d;
	double t = sec.t;
	double r = sec.r;
	double r1 = sec.r1;
	double z0 = sec.z0*10;
	double b1 = b-z0;
	double h1 = t-(b-d)/2/10;
	double h2 = t+(b-d)/2/10;

	CPt3d p2 = p1+CPt3d(b1,0);
	CPt3d p3 = p1+CPt3d(b1,-h1);
	CPt3d p4 = p1+CPt3d(d-z0,-h2);
	double a1 = p3.GetAngle(p2);
	double a2 = p3.GetAngle(p4);
	double a = a2-a1;
	double l = r1/tan(a/2);
	CPt3d p31 = p3.GetLineEnd(l,a1);
	CPt3d p32 = p3.GetLineEnd(l,a2);
	CPt3d p5 = p1+CPt3d(d-z0,-h+h2);
	a1 = p4.GetAngle(p3);
	a2 = p4.GetAngle(p5);
	a = a2-a1;
	l = r/tan(a/2);
	CPt3d p41 = p4.GetLineEnd(l,a1+PI);
	CPt3d p42 = p4.GetLineEnd(l,a2+PI);
	CPt3d p6 = p1+CPt3d(b1,-h+h1);
	a1 = p5.GetAngle(p4);
	a2 = p5.GetAngle(p6);
	a = a2-a1;
	l = r/tan(a/2);
	CPt3d p51 = p5.GetLineEnd(l,a1+PI);
	CPt3d p52 = p5.GetLineEnd(l,a2+PI);
	CPt3d p7 = p1+CPt3d(b1,-h);
	a1 = p6.GetAngle(p5);
	a2 = p6.GetAngle(p7);
	a = a2-a1;
	l = r1/tan(a/2);
	CPt3d p61 = p6.GetLineEnd(l,a1);
	CPt3d p62 = p6.GetLineEnd(l,a2);
	CPt3d p8 = p1+CPt3d(0,-h);
	CPt3d p9 = p1+CPt3d(-z0,-h);
	CPt3d p10 = p1+CPt3d(-z0,0);

	AcDbPolyline* polyline = new AcDbPolyline;
	polyline->addVertexAt(0,p1);
	polyline->addVertexAt(1,p2);
	polyline->addVertexAt(2,p31,-GetArcBulge(p31,p32,r1));
	polyline->addVertexAt(3,p32);
	polyline->addVertexAt(4,p41,GetArcBulge(p41,p42,r));
	polyline->addVertexAt(5,p42);
	polyline->addVertexAt(6,p51,GetArcBulge(p51,p52,r));
	polyline->addVertexAt(7,p52);
	polyline->addVertexAt(8,p61,-GetArcBulge(p61,p62,r1));
	polyline->addVertexAt(9,p62);
	polyline->addVertexAt(10,p7);
	polyline->addVertexAt(11,p8);
	polyline->addVertexAt(12,p9);
	polyline->addVertexAt(13,p10);
	polyline->addVertexAt(14,p1);
	AddEntity(polyline);
}

void ArxRleUiDlgSteelSection::DrawJiaoSteelSection(STEELSECTION sec)
{
	ArxRleUiPrPoint prPtBase(_T("插入点"), NULL);
	if(prPtBase.go() != ArxRleUiPrBase::kOk)
		return;

	CPt3d p1(prPtBase.value().x,prPtBase.value().y);
	double b = sec.b;
	double d = sec.d;
	double r = sec.r;
	double z0 = sec.z0*10;
	double b1 = b-z0;

	CPt3d p2 = p1+CPt3d(b1,0);
	CPt3d p3 = p1+CPt3d(b1,d);
	CPt3d p4 = p1+CPt3d(d-z0,d);
	double a1 = p3.GetAngle(p2);
	double a2 = p3.GetAngle(p4);
	double a = a2-a1;
	double l = d/tan(a/2);
	CPt3d p31 = p3.GetLineEnd(l,a1+PI);
	CPt3d p32 = p3.GetLineEnd(l,a2+PI);
	CPt3d p5 = p1+CPt3d(d-z0,b);
	a1 = p4.GetAngle(p3);
	a2 = p4.GetAngle(p5);
	a = a2-a1;
	l = r/tan(a/2);
	CPt3d p41 = p4.GetLineEnd(l,a1);
	CPt3d p42 = p4.GetLineEnd(l,a2);
	CPt3d p6 = p1+CPt3d(-z0,b);
	a1 = p5.GetAngle(p4);
	a2 = p5.GetAngle(p6);
	a = a2-a1;
	l = d/tan(a/2);
	CPt3d p51 = p5.GetLineEnd(l,a1+PI);
	CPt3d p52 = p5.GetLineEnd(l,a2+PI);
	CPt3d p7 = p1+CPt3d(-z0,0);

	AcDbPolyline* polyline = new AcDbPolyline;
	polyline->addVertexAt(0,p1);
	polyline->addVertexAt(1,p2);
	polyline->addVertexAt(2,p31,GetArcBulge(p31,p32,d));
	polyline->addVertexAt(3,p32);
	polyline->addVertexAt(4,p41,-GetArcBulge(p41,p42,r));
	polyline->addVertexAt(5,p42);
	polyline->addVertexAt(6,p51,GetArcBulge(p51,p52,d));
	polyline->addVertexAt(7,p52);
	polyline->addVertexAt(8,p6);
	polyline->addVertexAt(9,p7);
	polyline->addVertexAt(10,p1);
	AddEntity(polyline);
}

void ArxRleUiDlgSteelSection::DrawJiaoSteelSection2(STEELSECTION sec)
{
	ArxRleUiPrPoint prPtBase(_T("插入点"), NULL);
	if(prPtBase.go() != ArxRleUiPrBase::kOk)
		return;

	CPt3d p1(prPtBase.value().x,prPtBase.value().y);
	double B = sec.B;
	double b = sec.b;
	double d = sec.d;
	double r = sec.r;
	double x0 = sec.x0*10;
	double y0 = sec.y0*10;
	double b1 = b-x0;

	CPt3d p2 = p1+CPt3d(b1,0);
	CPt3d p3 = p1+CPt3d(b1,d);
	CPt3d p4 = p1+CPt3d(d-x0,d);
	double a1 = p3.GetAngle(p2);
	double a2 = p3.GetAngle(p4);
	double a = a2-a1;
	double l = d/tan(a/2);
	CPt3d p31 = p3.GetLineEnd(l,a1+PI);
	CPt3d p32 = p3.GetLineEnd(l,a2+PI);
	CPt3d p5 = p1+CPt3d(d-x0,B);
	a1 = p4.GetAngle(p3);
	a2 = p4.GetAngle(p5);
	a = a2-a1;
	l = r/tan(a/2);
	CPt3d p41 = p4.GetLineEnd(l,a1);
	CPt3d p42 = p4.GetLineEnd(l,a2);
	CPt3d p6 = p1+CPt3d(-x0,B);
	a1 = p5.GetAngle(p4);
	a2 = p5.GetAngle(p6);
	a = a2-a1;
	l = d/tan(a/2);
	CPt3d p51 = p5.GetLineEnd(l,a1+PI);
	CPt3d p52 = p5.GetLineEnd(l,a2+PI);
	CPt3d p7 = p1+CPt3d(-x0,y0);
	CPt3d p8 = p1+CPt3d(-x0,0);

	AcDbPolyline* polyline = new AcDbPolyline;
	polyline->addVertexAt(0,p1);
	polyline->addVertexAt(1,p2);
	polyline->addVertexAt(2,p31,GetArcBulge(p31,p32,d));
	polyline->addVertexAt(3,p32);
	polyline->addVertexAt(4,p41,-GetArcBulge(p41,p42,r));
	polyline->addVertexAt(5,p42);
	polyline->addVertexAt(6,p51,GetArcBulge(p51,p52,d));
	polyline->addVertexAt(7,p52);
	polyline->addVertexAt(8,p6);
	polyline->addVertexAt(9,p7);
	polyline->addVertexAt(10,p8);
	polyline->addVertexAt(11,p1);
	AddEntity(polyline);
}

void ArxRleUiDlgSteelSection::DrawHSteelSection(STEELSECTION sec)
{
	ArxRleUiPrPoint prPtBase(_T("插入点"), NULL);
	if(prPtBase.go() != ArxRleUiPrBase::kOk)
		return;

	CPt3d p1(prPtBase.value().x,prPtBase.value().y);
	double b = sec.b;
	double h = sec.h;
	double d = sec.d;
	double t = sec.t;
	double r = sec.r;

	CPt3d p2 = p1+CPt3d(b/2,0);
	CPt3d p3 = p1+CPt3d(b/2,-t);
	CPt3d p4 = p1+CPt3d(d/2,-t);
	CPt3d p5 = p1+CPt3d(d/2,-h+t);
	double a1 = p4.GetAngle(p3);
	double a2 = p4.GetAngle(p5);
	double a = a2-a1;
	double l = r/tan(a/2);
	CPt3d p41 = p4.GetLineEnd(l,a1+PI);
	CPt3d p42 = p4.GetLineEnd(l,a2+PI);
	CPt3d p6 = p1+CPt3d(b/2,-h+t);
	a1 = p5.GetAngle(p4);
	a2 = p5.GetAngle(p6);
	a = a2-a1;
	l = r/tan(a/2);
	CPt3d p51 = p5.GetLineEnd(l,a1+PI);
	CPt3d p52 = p5.GetLineEnd(l,a2+PI);
	CPt3d p7 = p1+CPt3d(b/2,-h);
	CPt3d p8 = p1+CPt3d(0,-h);
	CPt3d p9 = p1+CPt3d(-b/2,-h);
	CPt3d p10 = p1+CPt3d(-b/2,-h+t);
	CPt3d p11 = p1+CPt3d(-d/2,-h+t);
	CPt3d p12 = p1+CPt3d(-d/2,-t);
	a1 = p11.GetAngle(p10);
	a2 = p11.GetAngle(p12);
	a = a2-a1;
	l = r/tan(a/2);
	CPt3d p111 = p11.GetLineEnd(l,a1+PI);
	CPt3d p112 = p11.GetLineEnd(l,a2+PI);
	CPt3d p13 = p1+CPt3d(-b/2,-t);
	a1 = p12.GetAngle(p11);
	a2 = p12.GetAngle(p13);
	a = a2-a1;
	l = r/tan(a/2);
	CPt3d p121 = p12.GetLineEnd(l,a1+PI);
	CPt3d p122 = p12.GetLineEnd(l,a2+PI);
	CPt3d p14 = p1+CPt3d(-b/2,0);

	AcDbPolyline* polyline = new AcDbPolyline;
	polyline->addVertexAt(0,p1);
	polyline->addVertexAt(1,p2);
	polyline->addVertexAt(2,p3);
	polyline->addVertexAt(3,p41,GetArcBulge(p41,p42,r));
	polyline->addVertexAt(4,p42);
	polyline->addVertexAt(5,p51,GetArcBulge(p51,p52,r));
	polyline->addVertexAt(6,p52);
	polyline->addVertexAt(7,p6);
	polyline->addVertexAt(8,p7);
	polyline->addVertexAt(9,p8);
	polyline->addVertexAt(10,p9);
	polyline->addVertexAt(11,p10);
	polyline->addVertexAt(12,p111,GetArcBulge(p111,p112,r));
	polyline->addVertexAt(13,p112);
	polyline->addVertexAt(14,p121,GetArcBulge(p121,p122,r));
	polyline->addVertexAt(15,p122);
	polyline->addVertexAt(16,p13);
	polyline->addVertexAt(17,p14);
	polyline->addVertexAt(18,p1);
	AddEntity(polyline);
}

void ArxRleUiDlgSteelSection::DrawGuanSteelSection(STEELSECTION sec)
{
	ArxRleUiPrPoint prPtBase(_T("插入点"), NULL);
	if(prPtBase.go() != ArxRleUiPrBase::kOk)
		return;

	CPt3d p1(prPtBase.value().x,prPtBase.value().y);
	double d = sec.d;
	double t = sec.t;

	AddCircle(p1,d/2);
	AddCircle(p1,d/2-t);
}
