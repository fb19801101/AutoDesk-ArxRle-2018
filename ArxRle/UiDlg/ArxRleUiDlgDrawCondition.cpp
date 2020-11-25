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

#include "ArxRleUiDlgDrawCondition.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleApply.h"
#include "AcadUtils/ArxRleSmartPtr.h"
#include "AcadUtils/ArxRleSelSet.h"
#include "AcadUtils/ArxRleRbList.h"
#include "DbEntity/ArxRleEntityClass.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

/**************************************************************************
**
**  cdrawDlg
**
**  **通用绘图对话框
**
*************************************/
void drawCondition() //通用绘图对话框
{
	ArxRleUiDlgDrawCondition dlg(acedGetAcadDwgView());
	dlg.DoModal();
}


// ArxRleUiDlgDrawCondition 对话框

IMPLEMENT_DYNAMIC(ArxRleUiDlgDrawCondition, CAcUiDialog)

ArxRleUiDlgDrawCondition::ArxRleUiDlgDrawCondition(CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/)
	: CAcUiDialog(ArxRleUiDlgDrawCondition::IDD, pParent, hInstance)
	, m_strDataFileName(_T(""))
{
	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);

	m_strDataFilePathName = GetCurDwgFilePath().t_str() + m_strDataFileName;

	m_pToolTip = new CToolTipCtrl;
	m_bSmall = TRUE;
	m_bFlag = FALSE;
}

ArxRleUiDlgDrawCondition::~ArxRleUiDlgDrawCondition()
{
	if(m_pToolTip != NULL) delete m_pToolTip;
	m_pToolTip = NULL;
}

void ArxRleUiDlgDrawCondition::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_CB_TYPE,   m_cbType);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_CK_TEXT,   m_ckDrawText);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_BN_PT1,    m_bnPt1);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_BN_PT2,    m_bnPt2);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_X1,     m_etX1);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_Y1,     m_etY1);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_Z1,     m_etZ1);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_X2,     m_etX2);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_Y2,     m_etY2);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_Z2,     m_etZ2);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_A,      m_etParamets[0]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_B,      m_etParamets[1]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_C,      m_etParamets[2]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_D,      m_etParamets[3]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_E,      m_etParamets[4]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_F,      m_etParamets[5]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_G,      m_etParamets[6]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_EB_H,      m_etParamets[7]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_CK_A,      m_ckParamets[0]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_CK_B,      m_ckParamets[1]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_CK_C,      m_ckParamets[2]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_CK_D,      m_ckParamets[3]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_CK_E,      m_ckParamets[4]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_CK_F,      m_ckParamets[5]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_CK_G,      m_ckParamets[6]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_CK_H,      m_ckParamets[7]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_SC_A,      m_scParamets[0]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_SC_B,      m_scParamets[1]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_SC_C,      m_scParamets[2]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_SC_D,      m_scParamets[3]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_SC_E,      m_scParamets[4]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_SC_F,      m_scParamets[5]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_SC_G,      m_scParamets[6]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_SC_H,      m_scParamets[7]);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_BN_CALC,   m_bnCalc);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_BN_SEL,    m_bnSel);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_BN_EXEC,   m_bnExec);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_LC_RESULT, m_wndList);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_BN_ROLL,   m_bnRoll);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_BN_EXPORT, m_bnExport);
	DDX_Control(pDX, ARXRLE_DRAW_CONDITION_BN_CLEAR,  m_bnClear);
}


BEGIN_MESSAGE_MAP(ArxRleUiDlgDrawCondition, CAcUiDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_BN_PT1, OnBnClickedBtnPt1)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_BN_PT2, OnBnClickedBtnPt2)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_BN_CALC, OnBnClickedBtnCalc)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_BN_SEL, OnBnClickedBtnSel)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_BN_EXEC, OnBnClickedBtnExec)
	ON_CBN_SELCHANGE(ARXRLE_DRAW_CONDITION_CB_TYPE, OnCbnSelchangeCbType)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_BN_ROLL, OnBnClickedBtnRoll)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_BN_EXPORT, OnBnClickedBtnExport)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_BN_CLEAR, OnBnClickedBtnClear)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_CK_A, OnBnClickedBtnCheck)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_CK_B, OnBnClickedBtnCheck)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_CK_C, OnBnClickedBtnCheck)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_CK_D, OnBnClickedBtnCheck)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_CK_E, OnBnClickedBtnCheck)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_CK_F, OnBnClickedBtnCheck)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_CK_G, OnBnClickedBtnCheck)
	ON_BN_CLICKED(ARXRLE_DRAW_CONDITION_CK_H, OnBnClickedBtnCheck)
END_MESSAGE_MAP()


// ArxRleUiDlgDrawCondition 消息处理程序
BOOL ArxRleUiDlgDrawCondition::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	::SetWindowLong(m_hWnd, GWL_EXSTYLE, ::GetWindowLong(m_hWnd, GWL_EXSTYLE) |  WS_EX_LAYERED );
	SetLayeredWindowAttributes(0, 255 * 100/100 , LWA_ALPHA );

	// TODO:  在此添加额外的初始化
	 SetIcon(m_hIcon,TRUE);
	 SetIcon(m_hIcon,FALSE);

	 m_pToolTip->Create(this);

	//加载默认的位图
	m_bnPt1.AutoLoad();
	m_bnPt2.AutoLoad();
	m_pToolTip->AddTool(&m_bnPt1,L"选择点实体");
	m_pToolTip->AddTool(&m_bnPt2,L"选择点实体");

	m_bnCalc.SetIcon(ARXRLE_ICON_SET);
	m_bnCalc.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnCalc.SetFlat();
	m_bnCalc.ActivateTooltip();
	m_bnCalc.SetTooltipText(L"计算数据");

	m_bnSel.SetIcon(ARXRLE_ICON_SELECT);
	m_bnSel.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnSel.SetFlat();
	m_bnSel.ActivateTooltip();
	m_bnSel.SetTooltipText(L"选择文件");

	m_bnExec.SetIcon(ARXRLE_ICON_CORRECT);
	m_bnExec.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnExec.SetFlat();
	m_bnExec.ActivateTooltip();
	m_bnExec.SetTooltipText(L"执行程序");

	m_bnRoll.SetIcon(ARXRLE_ICON_LEFT);
	m_bnRoll.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnRoll.SetFlat();
	m_bnRoll.ActivateTooltip();
	m_bnRoll.SetTooltipText(L"折叠结果");

	m_bnExport.SetIcon(ARXRLE_ICON_FOLDER);
	m_bnExport.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnExport.SetFlat();
	m_bnExport.ActivateTooltip();
	m_bnExport.SetTooltipText(L"导出结果");

	m_bnClear.SetIcon(ARXRLE_ICON_CANCLE);
	m_bnClear.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnClear.SetFlat();
	m_bnClear.ActivateTooltip();
	m_bnClear.SetTooltipText(L"清空结果");

	m_cbType.InsertString(0,L"直线路径不定间距绘制矩形");
	m_cbType.InsertString(1,L"多段线路径不定间距绘制矩形");
	m_cbType.InsertString(2,L"多段线不定间距等分");
	m_cbType.InsertString(3,L"竖曲线计算程序");
	m_cbType.SetCurSel(0);
	m_pToolTip->AddTool(&m_cbType,L"选择执行程序功能");

	m_bnPt1.EnableWindow(TRUE);
	m_bnPt2.EnableWindow(TRUE);
	m_etX1.EnableWindow(TRUE);
	m_etY1.EnableWindow(TRUE);
	m_etZ1.EnableWindow(TRUE);
	m_etX2.EnableWindow(TRUE);
	m_etY2.EnableWindow(TRUE);
	m_etZ2.EnableWindow(TRUE);

	CString strs[4] = {L"矩形宽度",L"矩形长度",L"起点桩号",L"终点桩号"};
	SetParamets(4, strs);

	m_bnCalc.EnableWindow(FALSE);
	m_bnExec.EnableWindow(TRUE);

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

BOOL ArxRleUiDlgDrawCondition::PreTranslateMessage(MSG *pMsg)
{
	if( pMsg->message == WM_MOUSEMOVE || pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP)
	{
		m_pToolTip->RelayEvent(pMsg);
	}
	return CAcUiDialog::PreTranslateMessage(pMsg);
}

LRESULT ArxRleUiDlgDrawCondition::OnAcadKeepFocus(WPARAM, LPARAM)
{
	return TRUE;
}

void ArxRleUiDlgDrawCondition::OnShowWindow(BOOL bShow, UINT nStatus)
{
	// TODO: 在此处添加消息处理程序代码
	if(!m_bFlag)
	{
		m_bFlag = TRUE;
		CRect rcLarge,rcSmall;
		GetWindowRect(&rcLarge);
		GetDlgItem(ARXRLE_DRAW_CONDITION_PC_SEPARATOR)->GetWindowRect(&rcSmall);
		m_nHeight = rcLarge.bottom - rcSmall.bottom;
		rcSmall.top = rcLarge.top;
		rcSmall.left = rcLarge.left;
		rcSmall.right = rcLarge.right;
		CRect rc(rcSmall.CenterPoint().x,rcSmall.CenterPoint().y,rcSmall.CenterPoint().x,rcSmall.CenterPoint().y);
		int Width = rcSmall.Width();
		int Height = rcSmall.Height();
		for(int n=20; n>=1; n--)
		{
			rc.InflateRect(Width/40,Height/40);
			MoveWindow(&rc);
			ShowWindow(SW_SHOW);
			Sleep(10);
		}
		MoveWindow(&rcSmall);
		ShowWindow(SW_SHOW);
	}

	CAcUiDialog::OnShowWindow(bShow, nStatus);
}

void ArxRleUiDlgDrawCondition::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rc;
	GetWindowRect(&rc);

	int Width = rc.Width();
	int Height = rc.Height();
	for(int n=20; n>=1; n--)
	{
		rc.DeflateRect(Width/40,Height/40);
		MoveWindow(&rc);
		ShowWindow(SW_SHOW);
		Sleep(10);
	}

	//for(int nPercent=100; nPercent >= 0 ;nPercent--)
	//	SetLayeredWindowAttributes(0, 255 * nPercent/100, LWA_ALPHA);

	CAcUiDialog::OnClose();
}

void ArxRleUiDlgDrawCondition::OnBnClickedBtnPt1()
{
	// TODO: 在此添加控件通知处理程序代码

	//隐藏对话框把控制权交给AutoCad
	BeginEditorCommand();

	//提示用户输入一个点
	ads_point pt;
	if(acedGetPoint(NULL,_T("\n输入一个点："),pt) == RTNORM)
	{
		//如果点有效，继续执行
		CompleteEditorCommand();
		CString str;

		str.Format(_T("%.3f"),pt[X]);
		m_etX1.SetWindowText(str);
		m_etX1.Convert();//更新控件和其关联的成员变量
		str.Format(_T("%.3f"),pt[Y]);
		m_etY1.SetWindowText(str);
		m_etY1.Convert();
		str.Format(_T("%.3f"),pt[Z]);
		m_etZ1.SetWindowText(str);
		m_etZ1.Convert();
	}
	else
		CancelEditorCommand();
}

void ArxRleUiDlgDrawCondition::OnBnClickedBtnPt2()
{
	// TODO: 在此添加控件通知处理程序代码

	//隐藏对话框把控制权交给AutoCad
	BeginEditorCommand();

	//提示用户输入一个点
	ads_point pt;
	if(acedGetPoint(NULL,_T("\n输入一个点："),pt) == RTNORM)
	{
		//如果点有效，继续执行
		CompleteEditorCommand();
		CString str;

		str.Format(_T("%.3f"),pt[X]);
		m_etX2.SetWindowText(str);
		m_etX2.Convert();//更新控件和其关联的成员变量
		str.Format(_T("%.3f"),pt[Y]);
		m_etY2.SetWindowText(str);
		m_etY2.Convert();
		str.Format(_T("%.3f"),pt[Z]);
		m_etZ2.SetWindowText(str);
		m_etZ2.Convert();
	}
	else
		CancelEditorCommand();
}

void ArxRleUiDlgDrawCondition::OnBnClickedBtnSel()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置文件过滤器
	CompleteEditorCommand();
	m_bnSel.SetCheck(0);

	TCHAR szFilter[] = _T("数据文件|*.dat|文本文件|*.txt|所有文件|*.*||");
	// 构造打开文件对话框
	CFileDialog FileDlg(TRUE, _T("ArxRle"), NULL, 0, szFilter, this);

	// 设置默认路径
	FileDlg.m_ofn.lpstrInitialDir = GetCurDwgFilePath().t_str();

	// 显示打开文件对话框
	if(IDOK == FileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里
		m_strDataFileName = FileDlg.GetFileName();
		m_strDataFilePathName = FileDlg.GetPathName();
	}
}

void ArxRleUiDlgDrawCondition::OnBnClickedBtnCalc()
{
	// TODO: 在此添加控件通知处理程序代码
	CompleteEditorCommand();
	m_bnCalc.SetCheck(0);
	UpdateData(TRUE);

	if(!m_bSmall)
		return;
	CRect rc;
	GetWindowRect(&rc);
	rc.bottom += m_nHeight;
	MoveWindow(rc);
	ShowWindow(SW_SHOW);
	m_bSmall = FALSE;

	switch (m_cbType.GetCurSel())
	{
	case 3:
		{
			m_wndList.SetColumnHeader(_T("桩号, 150; 高程, 100; 竖曲线, 100"));
			m_wndList.SetImageList(ARXRLE_BMP_POKER);
			m_wndList.SetHeaderImageList(ARXRLE_BMP_HEADER);
			m_wndList.SetHeaderImage(0, 0);
			m_wndList.SetHeaderImage(1, 2);
			m_wndList.SetHeaderImage(2, 1);
			m_wndList.SetGridLines(TRUE); // SHow grid lines
			m_wndList.SetCheckboxeStyle(RC_CHKBOX_NORMAL); // Enable checkboxes
			m_wndList.SetEditable(TRUE); // Allow sub-text edit
			m_wndList.SortItems(0, TRUE); // sort the 1st column, ascending
			m_wndList.IsSortable();

			int a = GetParametsUnCheck(0,4);
			if(GetParametsUnCheck(0,4) == 5 && FileExist(m_strDataFilePathName))
			{
				vector<SQX> vecSqx = GetSqxs(m_strDataFilePathName);
				CString str;
				m_etParamets[5].Convert();
				m_etParamets[5].GetWindowText(str);
				double begin_stat = _tstof(str);
				m_etParamets[6].Convert();
				m_etParamets[6].GetWindowText(str);
				double end_stat = _tstof(str);
				m_etParamets[7].Convert();
				m_etParamets[7].GetWindowText(str);
				double stat_gap = _tstof(str);

				CStdioFile file;
				if(file.Open(m_strDataFilePathName, CFile::modeRead))
				{
					if (fabs(stat_gap) > 0.000001)
					{
						int rows = INT(((end_stat - begin_stat) / stat_gap)+1);
						for (int i = 0; i <= rows; i++)
						{
							str = FormatStat(begin_stat + stat_gap * i);
							double h = SqxCalc(begin_stat + stat_gap * i, GetSqx(begin_stat + stat_gap * i, vecSqx));
							if(begin_stat + stat_gap * i >= end_stat)
							{
								str = FormatStat(end_stat);
								h = SqxCalc(end_stat, GetSqx(end_stat, vecSqx));
							}
							const int idx = m_wndList.InsertItem(i, str);
							str.Format(_T("%.4f"),h);
							m_wndList.SetItemText(idx, 1, str);
							CString strs = L"竖曲线;直坡段";
							m_wndList.SetItemComboData(idx,2,strs,IsSqx(begin_stat + stat_gap * i, GetSqx(begin_stat + stat_gap * i, vecSqx)) ? 0:1);
							m_wndList.SetItemImage(idx, 0, idx%5);

							// Set the 3rd column background color to yellow, text color to blue
							m_wndList.SetItemTextColor( idx, 0, idx%2 ? RGB(0, 0, 255) : RGB(0, 0, 0));
							m_wndList.SetItemTextColor( idx, 1, idx%2 ? RGB(0, 0, 255) : RGB(0, 0, 0));
							m_wndList.SetItemTextColor( idx, 2, idx%2 ? RGB(0, 0, 255) : RGB(0, 0, 0));
							m_wndList.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(255, 255, 255));
							m_wndList.SetItemBkColor(idx, 1, idx%2 ? RGB(218, 218, 218) : RGB(255, 255, 255));
							m_wndList.SetItemBkColor(idx, 2, idx%2 ? RGB(218, 218, 218) : RGB(255, 255, 255));

							if(begin_stat + stat_gap * i >= end_stat)
							break;
						}
					}
					file.Close();
				}
			}
			else
			{
				CString str;
				SQX sqx;
				m_etParamets[0].Convert();
				m_etParamets[0].GetWindowText(str);
				sqx.S = _tstof(str);
				m_etParamets[1].Convert();
				m_etParamets[1].GetWindowText(str);
				sqx.H = _tstof(str);
				m_etParamets[2].Convert();
				m_etParamets[2].GetWindowText(str);
				sqx.R = _tstof(str);
				m_etParamets[3].Convert();
				m_etParamets[3].GetWindowText(str);
				sqx.I1 = _tstof(str)/1000;
				m_etParamets[4].Convert();
				m_etParamets[4].GetWindowText(str);
				sqx.I2 = _tstof(str)/1000;
				sqx.L = fabs(sqx.R * (sqx.I1 - sqx.I2));
				sqx.T = sqx.L / 2;
				if(sqx.R != 0) sqx.E = sqx.T * sqx.T / 2 / sqx.R;

				if(GetParametsUnCheck(5,7) == 3 && FileExist(m_strDataFilePathName))
				{
					CStdioFile file;
					if(file.Open(m_strDataFilePathName, CFile::modeRead))
					{
						int i = 0;
						while(file.ReadString(str))
						{
							str.Trim();
							double s = _tstof(str);
							str = FormatStat(s);
							double h = SqxCalc(s, sqx);
							const int idx = m_wndList.InsertItem(i, str);
							i++;
							str.Format(_T("%.4f"),h);
							m_wndList.SetItemText(idx, 1, str);
							CString strs = L"竖曲线;直坡段";
							m_wndList.SetItemComboData(idx,2,strs,IsSqx(s, sqx) ? 0:1);
							m_wndList.SetItemImage(idx, 0, idx%5);

							// Set the 3rd column background color to yellow, text color to blue
							m_wndList.SetItemTextColor( idx, 0, idx%2 ? RGB(0, 0, 255) : RGB(0, 0, 0));
							m_wndList.SetItemTextColor( idx, 1, idx%2 ? RGB(0, 0, 255) : RGB(0, 0, 0));
							m_wndList.SetItemTextColor( idx, 2, idx%2 ? RGB(0, 0, 255) : RGB(0, 0, 0));
							m_wndList.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(255, 255, 255));
							m_wndList.SetItemBkColor(idx, 1, idx%2 ? RGB(218, 218, 218) : RGB(255, 255, 255));
							m_wndList.SetItemBkColor(idx, 2, idx%2 ? RGB(218, 218, 218) : RGB(255, 255, 255));
						}

						file.Close();
					}
				}
				else
				{
					m_etParamets[5].Convert();
					m_etParamets[5].GetWindowText(str);
					double begin_stat = _tstof(str);
					m_etParamets[6].Convert();
					m_etParamets[6].GetWindowText(str);
					double end_stat = _tstof(str);
					m_etParamets[7].Convert();
					m_etParamets[7].GetWindowText(str);
					double stat_gap = _tstof(str);

					if (fabs(stat_gap) > 0.000001)
					{
						int rows = INT(((end_stat - begin_stat) / stat_gap)+1);
						for (int i = 0; i <= rows; i++)
						{
							str = FormatStat(begin_stat + stat_gap * i);
							double h = SqxCalc(begin_stat + stat_gap * i, sqx);
							if(begin_stat + stat_gap * i >= end_stat)
							{
								str = FormatStat(end_stat);
								h = SqxCalc(end_stat, sqx);
							}
							int idx = m_wndList.InsertItem(i, str);
							str.Format(_T("%.4f"),h);
							m_wndList.SetItemText(idx, 1, str);
							CString strs = L"竖曲线;直坡段";
							m_wndList.SetItemComboData(idx,2,strs,IsSqx(begin_stat + stat_gap * i, sqx) ? 0:1);
							m_wndList.SetItemImage(idx, 0, idx%5);

							// Set the 3rd column background color to yellow, text color to blue
							m_wndList.SetItemTextColor( idx, 0, idx%2 ? RGB(0, 0, 255) : RGB(0, 0, 0));
							m_wndList.SetItemTextColor( idx, 1, idx%2 ? RGB(0, 0, 255) : RGB(0, 0, 0));
							m_wndList.SetItemTextColor( idx, 2, idx%2 ? RGB(0, 0, 255) : RGB(0, 0, 0));
							m_wndList.SetItemBkColor(idx, 0, idx%2 ? RGB(218, 218, 218) : RGB(255, 255, 255));
							m_wndList.SetItemBkColor(idx, 1, idx%2 ? RGB(218, 218, 218) : RGB(255, 255, 255));
							m_wndList.SetItemBkColor(idx, 2, idx%2 ? RGB(218, 218, 218) : RGB(255, 255, 255));

							if(begin_stat + stat_gap * i >= end_stat)
								break;
						}
					}
				}
			}
		}

		break;
	}
}

void ArxRleUiDlgDrawCondition::OnBnClickedBtnExec()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_cbType.GetCurSel())
	{
#pragma region 直线路径不定间距绘制矩形
	case 0:
		{
			struct param
			{
				double h,w,s;
				int n;

				param(double h1,double w1,double s1)
				{
					h = h1;w=w1;s=s1;
					n=3;
				}

				param(double w1,double s1)
				{
					w=w1;s=s1;
					n=2;
				}

				param(double s1)
				{
					s=s1;
					n=1;
				}

				param()
				{
					h=w=s=0;
					n=0;
				}
			};
			vector<param> vecParam;
			if(FileExist(m_strDataFilePathName))
			{
				setlocale(LC_ALL,"");

				CStdioFile file;
				if(file.Open(m_strDataFilePathName, CFile::modeRead))
				{
					CString strLine;
					while(file.ReadString(strLine))
					{
						strLine.Trim();
						strLine.Replace(_T("；"), _T(";"));
						strLine.Replace(_T(","), _T(";"));
						strLine.Replace(_T("，"), _T(";"));
						if(strLine.GetLength() == 0)
							continue;

						CStringArray arrSubStr;
						int cnt = ParseSubStrByDelimiter(strLine, arrSubStr, ';');

						if(cnt == 3)
							vecParam.push_back(param(_tstof(arrSubStr[0]),_tstof(arrSubStr[1]),_tstof(arrSubStr[2])));
						else if(cnt == 2)
							vecParam.push_back(param(_tstof(arrSubStr[0]),_tstof(arrSubStr[1])));
						else if(cnt == 0)
							vecParam.push_back(param(_tstof(strLine)));
					}

					file.Close();
				}
			}

			CPt3d pt1,pt2;
			CString str;
			m_etX1.Convert();
			m_etX1.GetWindowText(str);
			pt1.x = _tstof(str);
			m_etY1.Convert();
			m_etY1.GetWindowText(str);
			pt1.y = _tstof(str);
			m_etZ1.Convert();
			m_etZ1.GetWindowText(str);
			pt1.z = _tstof(str);

			m_etX2.Convert();
			m_etX2.GetWindowText(str);
			pt2.x = _tstof(str);
			m_etY2.Convert();
			m_etY2.GetWindowText(str);
			pt2.y = _tstof(str);
			m_etZ2.Convert();
			m_etZ2.GetWindowText(str);
			pt2.z = _tstof(str);

			double w = 0,h = 0,s1 = 0,s2 = 0;
			m_etParamets[0].Convert();
			m_etParamets[0].GetWindowText(str);
			h = _tstof(str);
			m_etParamets[1].Convert();
			m_etParamets[1].GetWindowText(str);
			w = _tstof(str);
			m_etParamets[2].Convert();
			m_etParamets[2].GetWindowText(str);
			s1 = _tstof(str);
			m_etParamets[3].Convert();
			m_etParamets[3].GetWindowText(str);
			s2 = _tstof(str);

			if(GetParametsUnCheck(0,3) == 0)
			{
				double zw = GetAngleOf2Pts(pt1,pt2);
				CPt3d p = pt1.GetLineEnd(s2-s1,zw);
				CPt3d p1 = p.GetLineEnd(h/2,zw+PI/2);
				CPt3d p2 = p1.GetLineEnd(w,zw);
				CPt3d p3 = p2.GetLineEnd(h,zw-PI/2);
				CPt3d p4 = p3.GetLineEnd(w,zw+PI);
				CPolyline pline;
				pline.AddPoint(p1);
				pline.AddPoint(p2);
				pline.AddPoint(p3);
				pline.AddPoint(p4);
				pline.AddPoint(p1);
				AddEntity(&pline);

				if(m_ckDrawText.GetCheck())
				{
					ArxRleString stat = FormatStat(s2);
					AddText(stat, p, 1, zw, ArxLeftBottom);
				}
			}
			else
			{
				int len = vecParam.size();
				for(int i=0; i<len;i++)
				{
					if(vecParam[i].n == 1)
						s2 = vecParam[i].s;
					else if(vecParam[i].n == 2)
					{
						w = vecParam[i].w;
						s2 = vecParam[i].s;
					}
					else if(vecParam[i].n == 3)
					{
						h = vecParam[i].h;
						w = vecParam[i].w;
						s2 = vecParam[i].s;
					}

					double zw = GetAngleOf2Pts(pt1,pt2);
					CPt3d p = pt1.GetLineEnd(s2-s1,zw);
					CPt3d p1 = p.GetLineEnd(h/2,zw+PI/2);
					CPt3d p2 = p1.GetLineEnd(w,zw);
					CPt3d p3 = p2.GetLineEnd(h,zw-PI/2);
					CPt3d p4 = p3.GetLineEnd(w,zw+PI);
					CPolyline pline;
					pline.AddPoint(p1);
					pline.AddPoint(p2);
					pline.AddPoint(p3);
					pline.AddPoint(p4);
					pline.AddPoint(p1);
					AddEntity(&pline);

					if(m_ckDrawText.GetCheck())
					{
						ArxRleString stat = FormatStat(s2);
						AddText(stat, p, 1, zw, ArxLeftBottom);
					}
				}
			}
		}
		break;
#pragma endregion
	
#pragma region 多段线路径不定间距绘制矩形
	case 1:
		{
			struct param
			{
				double h,w,s;
				int n;

				param(double h1,double w1,double s1)
				{
					h = h1;w=w1;s=s1;
					n=3;
				}

				param(double w1,double s1)
				{
					w=w1;s=s1;
					n=2;
				}

				param(double s1)
				{
					s=s1;
					n=1;
				}

				param()
				{
					h=w=s=0;
					n=0;
				}
			};
			vector<param> vecParam;
			if(FileExist(m_strDataFilePathName))
			{
				setlocale(LC_ALL,"");

				CStdioFile file;
				if(file.Open(m_strDataFilePathName, CFile::modeRead))
				{
					CString strLine;
					while(file.ReadString(strLine))
					{
						strLine.Trim();
						strLine.Replace(_T("；"), _T(";"));
						strLine.Replace(_T(","), _T(";"));
						strLine.Replace(_T("，"), _T(";"));
						if(strLine.GetLength() == 0)
							continue;

						CStringArray arrSubStr;
						int cnt = ParseSubStrByDelimiter(strLine, arrSubStr, ';');

						if(cnt == 3)
							vecParam.push_back(param(_tstof(arrSubStr[0]),_tstof(arrSubStr[1]),_tstof(arrSubStr[2])));
						else if(cnt == 2)
							vecParam.push_back(param(_tstof(arrSubStr[0]),_tstof(arrSubStr[1])));
						else if(cnt == 0)
							vecParam.push_back(param(_tstof(strLine)));
					}

					file.Close();
				}
			}

			CPt3d pt;
			CString str;
			m_etX1.Convert();
			m_etX1.GetWindowText(str);
			pt.x = _tstof(str);
			m_etY1.Convert();
			m_etY1.GetWindowText(str);
			pt.y = _tstof(str);
			m_etZ1.Convert();
			m_etZ1.GetWindowText(str);
			pt.z = _tstof(str);

			double w = 0,h = 0,s1 = 0,s2 = 0;
			m_etParamets[0].Convert();
			m_etParamets[0].GetWindowText(str);
			h = _tstof(str);
			m_etParamets[1].Convert();
			m_etParamets[1].GetWindowText(str);
			w = _tstof(str);
			m_etParamets[2].Convert();
			m_etParamets[2].GetWindowText(str);
			s1 = _tstof(str);
			m_etParamets[3].Convert();
			m_etParamets[3].GetWindowText(str);
			s2 = _tstof(str);

			if(GetParametsUnCheck(0,3) == 0)
			{
				ArxRleSelSet ss;
				AcDbObjectId tsId;
				if(ss.crossingSelect(pt,pt) == ArxRleSelSet::kSelected)
				{    // have user select entities from DWG
					AcDbObjectIdArray objList;
					ss.asArray(objList);
					if(!objList.isEmpty())
					{
						AcDbEntity* ent;
						Acad::ErrorStatus es;

						int len = objList.length();
						double lengths = 0;
						for(int i=0; i<len; i++)
						{
							es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForRead, true);		// might have passed in erased ones
							if(es == Acad::eOk)
							{
								if(ent->isKindOf(AcDbPolyline::desc()) || ent->isKindOf(AcDbLine::desc()))
								{
									double dist = -1;
									AcGePoint3d pt1,pt2;
									((AcDbCurve*)ent)->getDistAtPoint(AcGePoint3d(pt[X],pt[Y],pt[Z]),dist);
									if(dist > -1)
									{
										((AcDbCurve*)ent)->getPointAtDist(dist+s2-s1,pt1);
										((AcDbCurve*)ent)->getPointAtDist(dist+s2-s1+w,pt2);
										double zw = GetAngleOf2Pts(CPt3d(pt1),CPt3d(pt2));
										CPt3d p = CPt3d(pt1);

										if(isUcs())
										{
											p = W2U(p);
											zw = GetAngleOf2Pts(W2U(CPt3d(pt1)),W2U(CPt3d(pt2)));
										}

										CPt3d p1 = p.GetLineEnd(h/2,zw+PI/2);
										CPt3d p2 = p1.GetLineEnd(w,zw);
										CPt3d p3 = p2.GetLineEnd(h,zw-PI/2);
										CPt3d p4 = p3.GetLineEnd(w,zw+PI);
										CPolyline pline;
										pline.AddPoint(p1);
										pline.AddPoint(p2);
										pline.AddPoint(p3);
										pline.AddPoint(p4);
										pline.AddPoint(p1);
										AddEntity(&pline);

										if(m_ckDrawText.GetCheck())
										{
											ArxRleString stat = FormatStat(s2);
											AddText(stat, p, 1, zw, ArxLeftBottom);
										}
									}
								}
								ent->close();
							}
						}
					}
				}
			}
			else
			{
				int len = vecParam.size();
				for(int i=0; i<len;i++)
				{
					if(vecParam[i].n == 1)
						s2 = vecParam[i].s;
					else if(vecParam[i].n == 2)
					{
						w = vecParam[i].w;
						s2 = vecParam[i].s;
					}
					else if(vecParam[i].n == 3)
					{
						h = vecParam[i].h;
						w = vecParam[i].w;
						s2 = vecParam[i].s;
					}

					ArxRleSelSet ss;
					AcDbObjectId tsId;
					if(ss.crossingSelect(pt,pt) == ArxRleSelSet::kSelected)
					{    // have user select entities from DWG
						AcDbObjectIdArray objList;
						ss.asArray(objList);
						if(!objList.isEmpty())
						{
							AcDbEntity* ent;
							Acad::ErrorStatus es;

							int len = objList.length();
							double lengths = 0;
							for(int j=0; j<len; j++)
							{
								es = acdbOpenAcDbEntity(ent, objList[j], AcDb::kForRead, true);		// might have passed in erased ones
								if(es == Acad::eOk)
								{
									if(ent->isKindOf(AcDbPolyline::desc()) || ent->isKindOf(AcDbLine::desc()))
									{
										double dist = -1;
										AcGePoint3d pt1,pt2;
										((AcDbCurve*)ent)->getDistAtPoint(AcGePoint3d(pt[X],pt[Y],pt[Z]),dist);
										if(dist > -1)
										{
											((AcDbCurve*)ent)->getPointAtDist(dist+s2-s1,pt1);
											((AcDbCurve*)ent)->getPointAtDist(dist+s2-s1+w,pt2);

											double zw = GetAngleOf2Pts(CPt3d(pt1),CPt3d(pt2));
											CPt3d p = CPt3d(pt1);

											if(isUcs())
											{
												p = W2U(p);
												zw = GetAngleOf2Pts(W2U(CPt3d(pt1)),W2U(CPt3d(pt2)));
											}

											CPt3d p1 = p.GetLineEnd(h/2,zw+PI/2);
											CPt3d p2 = p1.GetLineEnd(w,zw);
											CPt3d p3 = p2.GetLineEnd(h,zw-PI/2);
											CPt3d p4 = p3.GetLineEnd(w,zw+PI);
											CPolyline pline;
											pline.AddPoint(p1);
											pline.AddPoint(p2);
											pline.AddPoint(p3);
											pline.AddPoint(p4);
											pline.AddPoint(p1);
											AddEntity(&pline);

											if(m_ckDrawText.GetCheck())
											{
												ArxRleString stat = FormatStat(s2);
												AddText(stat, p, 1, zw, ArxLeftBottom);
											}
										}
									}
									ent->close();
								}
							}
						}
					}
				}
			}
		}
		break;
#pragma endregion

#pragma region 多段线不定间距等分
	case 2:
		{
			vector<double> vecDist;
			if(FileExist(m_strDataFilePathName))
			{
				setlocale(LC_ALL,"");

				CStdioFile file;
				if(file.Open(m_strDataFilePathName, CFile::modeRead))
				{
					CString strLine;
					while(file.ReadString(strLine))
					{
						strLine.Trim();
						if(strLine.GetLength() == 0)
							continue;

						vecDist.push_back(_tstof(strLine));
					}

					file.Close();
				}
			}

			CPt3d pt1;
			CString str;
			m_etX1.Convert();
			m_etX1.GetWindowText(str);
			pt1.x = _tstof(str);
			m_etY1.Convert();
			m_etY1.GetWindowText(str);
			pt1.y = _tstof(str);
			m_etZ1.Convert();
			m_etZ1.GetWindowText(str);
			pt1.z = _tstof(str);

			double dist2 = 0;
			m_etParamets[0].Convert();
			m_etParamets[0].GetWindowText(str);
			dist2 = _tstof(str);
			double width = 0;
			m_etParamets[1].Convert();
			m_etParamets[1].GetWindowText(str);
			width = _tstof(str);

			if(GetParametsUnCheck(0,1) == 0)
			{
				ArxRleSelSet ss;
				AcDbObjectId tsId;
				if(ss.crossingSelect(pt1,pt1) == ArxRleSelSet::kSelected)
				{    // have user select entities from DWG
					AcDbObjectIdArray objList;
					ss.asArray(objList);
					if(!objList.isEmpty())
					{
						AcDbEntity* ent;
						Acad::ErrorStatus es;

						int len = objList.length();
						double lengths = 0;
						for(int i=0; i<len; i++)
						{
							es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForRead, true);		// might have passed in erased ones
							if(es == Acad::eOk)
							{
								if(ent->isKindOf(AcDbPolyline::desc()) || ent->isKindOf(AcDbLine::desc()))
								{
									double dist1 = -1;
									AcGePoint3d pt2;
									((AcDbCurve*)ent)->getDistAtPoint(AcGePoint3d(pt1[X],pt1[Y],pt1[Z]),dist1);
									if(dist1 > -1)
									{
										((AcDbCurve*)ent)->getPointAtDist(dist1+dist2,pt2);
										//AddPoint(CPt3d(pt2));

										AcGePoint3d pt_tmp;
										((AcDbCurve*)ent)->getPointAtDist(dist1+dist2+0.01,pt_tmp);
										AcGePoint3dArray pts;
										pts.append(pt2);
										pts.append(pt_tmp);
										AcDbVoidPtrArray segs;
										((AcDbCurve*)ent)->getSplitCurves(pts,	segs);
										if(segs.length() == 3)
										{
											if(((AcDbEntity*)segs[1])->isKindOf(AcDbPolyline::desc()))
											{
												if(((AcDbPolyline*)segs[1])->segType(0) == AcDbPolyline::kArc)
												{
													AcGeCircArc2d seg;
													((AcDbPolyline*)segs[1])->getArcSegAt(0,seg);
													CPt3d cen = seg.center();
													double zw = GetAngleOf2Pts(cen,CPt3d(pt2));
													CPt3d p(pt2);

													if(isUcs())
													{
														p = W2U(p);
														zw = GetAngleOf2Pts(W2U(cen),W2U(CPt3d(pt2)));
													}

													CPolyline pline;
													pline.AddPoint(p.GetLineEnd(width/2,zw+PI));
													pline.AddPoint(p.GetLineEnd(width/2,zw));
													AddEntity(&pline);
												}
												else if(((AcDbPolyline*)segs[1])->segType(0) == AcDbPolyline::kLine)
												{
													AcGeLineSeg3d seg;
													((AcDbPolyline*)segs[1])->getLineSegAt(0,seg);
													CPt3d p1(seg.startPoint());
													CPt3d p2(seg.endPoint());
													double zw = GetAngleOf2Pts(p1,p2);
													CPt3d p(pt2);

													if(isUcs())
													{
														p = W2U(p);
														zw = GetAngleOf2Pts(W2U(p1),W2U(p2));
													}

													CPolyline pline;
													
													pline.AddPoint(p.GetLineEnd(width/2,zw+PI/2));
													pline.AddPoint(p.GetLineEnd(width/2,zw-PI/2));
													AddEntity(&pline);
												}
											}
										}

										if(m_ckDrawText.GetCheck())
										{
											ArxRleString str;
											str.ConvertDouble(dist2);
											AddText(str, CPt3d(pt2), 1, 0, ArxLeftBottom);
										}
									}
								}
								ent->close();
							}
						}
					}
				}
			}
			else
			{
				int cnt = vecDist.size();
				for(int i=0; i<cnt; i++)
				{
					dist2 += vecDist[i];
					ArxRleSelSet ss;
					AcDbObjectId tsId;
					if(ss.crossingSelect(pt1,pt1) == ArxRleSelSet::kSelected)
					{    // have user select entities from DWG
						AcDbObjectIdArray objList;
						ss.asArray(objList);
						if(!objList.isEmpty())
						{
							AcDbEntity* ent;
							Acad::ErrorStatus es;

							int len = objList.length();
							double lengths = 0;
							for(int j=0; j<len; j++)
							{
								es = acdbOpenAcDbEntity(ent, objList[j], AcDb::kForRead, true);		// might have passed in erased ones
								if(es == Acad::eOk)
								{
									if(ent->isKindOf(AcDbPolyline::desc()) || ent->isKindOf(AcDbLine::desc()))
									{
										double dist1 = -1;
										AcGePoint3d pt2;
										((AcDbCurve*)ent)->getDistAtPoint(AcGePoint3d(pt1[X],pt1[Y],pt1[Z]),dist1);
										if(dist1 > -1)
										{
											((AcDbCurve*)ent)->getPointAtDist(dist1+dist2,pt2);
											//AddPoint(CPt3d(pt2));

											AcGePoint3d pt_tmp;
											((AcDbCurve*)ent)->getPointAtDist(dist1+dist2+0.01,pt_tmp);
											AcGePoint3dArray pts;
											pts.append(pt2);
											pts.append(pt_tmp);
											AcDbVoidPtrArray segs;
											((AcDbCurve*)ent)->getSplitCurves(pts,	segs);
											if(segs.length() == 3)
											{
												if(((AcDbEntity*)segs[1])->isKindOf(AcDbPolyline::desc()))
												{
													if(((AcDbPolyline*)segs[1])->segType(0) == AcDbPolyline::kArc)
													{
														AcGeCircArc2d arc;
														((AcDbPolyline*)segs[1])->getArcSegAt(0,arc);
														CPt3d cen = arc.center();
														CPt3d p(pt2);
														double zw = GetAngleOf2Pts(cen,CPt3d(pt2));
														if(isUcs())
															zw = GetAngleOf2Pts(W2U(cen),W2U(CPt3d(pt2)));

														CPolyline pline;
														pline.AddPoint(p.GetLineEnd(width/2,zw+PI));
														pline.AddPoint(p.GetLineEnd(width/2,zw));
														AddEntity(&pline);
													}
													else if(((AcDbPolyline*)segs[1])->segType(0) == AcDbPolyline::kLine)
													{
														AcGeLineSeg3d seg;
														((AcDbPolyline*)segs[1])->getLineSegAt(0,seg);
														CPt3d p1(seg.startPoint());
														CPt3d p2(seg.endPoint());
														double zw = GetAngleOf2Pts(p1,p2);
														if(isUcs())
															zw = GetAngleOf2Pts(W2U(p1),W2U(p2));

														CPolyline pline;
														CPt3d p(pt2);
														pline.AddPoint(p.GetLineEnd(width/2,zw+PI/2));
														pline.AddPoint(p.GetLineEnd(width/2,zw-PI/2));
														AddEntity(&pline);
													}
												}
											}

											if(m_ckDrawText.GetCheck())
											{
												ArxRleString str;
												str.ConvertDouble(vecDist[i]);
												AddText(str, CPt3d(pt2), 1.8, 0, ArxLeftBottom);
											}
										}
									}
									ent->close();
								}
							}
						}
					}
				}
			}
		}
		break;
#pragma endregion
	}

	CompleteEditorCommand();
	m_bnExec.SetCheck(0);
}

void ArxRleUiDlgDrawCondition::SetParamets(int count, CString* strs)
{
	for(int i=0; i< PARAMETS_COUNT; i++)
	{
		if(i < count)
		{
			m_etParamets[i].EnableWindow(TRUE);
			m_ckParamets[i].EnableWindow(TRUE);
			m_ckParamets[i].SetCheck(TRUE);
			m_scParamets[i].EnableWindow(TRUE);
			m_scParamets[i].SetWindowText(strs[i]);
		}
		else
		{
			m_etParamets[i].EnableWindow(FALSE);
			m_ckParamets[i].EnableWindow(FALSE);
			m_ckParamets[i].SetCheck(FALSE);
			m_scParamets[i].EnableWindow(FALSE);
			char c = 'A';
			CString str;
			str.Format(L"%c",c+i);
			m_scParamets[i].SetWindowText(str);
		}
	}
}

int ArxRleUiDlgDrawCondition::GetParametsUnCheck(int begin, int end)
{
	int checks = 0;
	for(int i=0; i< PARAMETS_COUNT; i++)
		if(i <= end && i >= begin && !m_ckParamets[i].GetCheck()) checks++;

	return checks;
}

void ArxRleUiDlgDrawCondition::OnCbnSelchangeCbType()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_cbType.GetCurSel())
	{
	case 0:
		{
			m_bnPt1.EnableWindow(TRUE);
			m_bnPt2.EnableWindow(TRUE);
			m_etX1.EnableWindow(TRUE);
			m_etY1.EnableWindow(TRUE);
			m_etZ1.EnableWindow(TRUE);
			m_etX2.EnableWindow(TRUE);
			m_etY2.EnableWindow(TRUE);
			m_etZ2.EnableWindow(TRUE);

			CString strs[4] = {L"矩形宽度",L"矩形长度",L"起点桩号",L"终点桩号"};
			SetParamets(4, strs);

			m_bnCalc.EnableWindow(FALSE);
			m_bnExec.EnableWindow(TRUE);
		}
		break;
	case 1:
		{
			m_bnPt1.EnableWindow(TRUE);
			m_bnPt2.EnableWindow(FALSE);
			m_etX1.EnableWindow(TRUE);
			m_etY1.EnableWindow(TRUE);
			m_etZ1.EnableWindow(TRUE);
			m_etX2.EnableWindow(FALSE);
			m_etY2.EnableWindow(FALSE);
			m_etZ2.EnableWindow(FALSE);

			CString strs[4] = {L"矩形宽度",L"矩形长度",L"起点桩号",L"终点桩号"};
			SetParamets(4, strs);

			m_bnCalc.EnableWindow(FALSE);
			m_bnExec.EnableWindow(TRUE);
		}
		break;
	case 2:
		{
			m_bnPt1.EnableWindow(TRUE);
			m_bnPt2.EnableWindow(FALSE);
			m_etX1.EnableWindow(TRUE);
			m_etY1.EnableWindow(TRUE);
			m_etZ1.EnableWindow(TRUE);
			m_etX2.EnableWindow(FALSE);
			m_etY2.EnableWindow(FALSE);
			m_etZ2.EnableWindow(FALSE);

			CString strs[2] = {L"线间距",L"线宽度"};
			SetParamets(2, strs);

			m_bnCalc.EnableWindow(FALSE);
			m_bnExec.EnableWindow(TRUE);
		}
		break;
	case 3:
		{
			m_bnPt1.EnableWindow(FALSE);
			m_bnPt2.EnableWindow(FALSE);
			m_etX1.EnableWindow(FALSE);
			m_etY1.EnableWindow(FALSE);
			m_etZ1.EnableWindow(FALSE);
			m_etX2.EnableWindow(FALSE);
			m_etY2.EnableWindow(FALSE);
			m_etZ2.EnableWindow(FALSE);

			CString strs[8] = {L"交点桩号",L"交点高程",L"曲线半径",L"前坡坡率",
				               L"后坡坡率",L"起点桩号",L"终点桩号",L"桩号间距"};
			SetParamets(8, strs);

			m_bnCalc.EnableWindow(TRUE);
			m_bnExec.EnableWindow(FALSE);
		}
		break;
	}
}

void ArxRleUiDlgDrawCondition::OnBnClickedBtnCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i=0; i< PARAMETS_COUNT; i++)
	{
		m_etParamets[i].EnableWindow(m_ckParamets[i].GetCheck());
	}
}

void ArxRleUiDlgDrawCondition::OnBnClickedBtnRoll()
{
	// TODO: 在此添加控件通知处理程序代码
	CompleteEditorCommand();
	m_bnRoll.SetCheck(0);

	CRect rc;
	GetWindowRect(&rc);
	rc.bottom-=m_nHeight;
	MoveWindow(&rc);
	m_bSmall = TRUE;
}

void ArxRleUiDlgDrawCondition::OnBnClickedBtnExport()
{
	// TODO: 在此添加控件通知处理程序代码
	CompleteEditorCommand();
	m_bnExport.SetCheck(0);

	TCHAR szFilter[] = _T("数据文件|*.dat|文本文件|*.txt|所有文件|*.*||");
	// 构造打开文件对话框
	CFileDialog FileDlg(FALSE, _T("ArxRle"), NULL, 0, szFilter, this);

	// 设置默认路径
	FileDlg.m_ofn.lpstrInitialDir = GetCurDwgFilePath().t_str();

	// 显示打开文件对话框
	if(IDOK == FileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里
		m_strDataFileName = FileDlg.GetFileName();
		m_strDataFilePathName = FileDlg.GetPathName();
	}

	m_bnCalc.SetCheck(0);

	CStdioFile file;
	if(file.Open(m_strDataFilePathName, CFile::modeCreate | CFile::modeWrite))
	{
		const int rows = m_wndList.GetItemCount();
		const int cols = m_wndList.GetColumnCount();
		CString str;
		for(int i=0; i<cols; i++)
		{
			CString data = m_wndList.GetHeaderText(i);
			if(i == 0)
				str.Format(_T("%s"),data);
			else if(i==cols-1)
				str.Format(_T("%s   %s\n"),str,data);
			else
				str.Format(_T("%s   %s"),str,data);
		}

		file.WriteString(str);
		for (int i = 0; i <= rows; i++)
		{
			for(int j=0; j<cols; j++)
			{
				CString data = m_wndList.GetItemText(i,j);
				if(j == 0)
					str.Format(_T("%s;"),data);
				else if(j==cols-1)
					str.Format(_T("%s   %s\n"),str,data);
				else
					str.Format(_T("%s   %s;"),str,data);
			}

			file.WriteString(str);
		}

		file.Close();
		msgInf(L"计算数据成功导出！");
	}
}

void ArxRleUiDlgDrawCondition::OnBnClickedBtnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	CompleteEditorCommand();
	m_bnClear.SetCheck(0);

	m_wndList.LockWindowUpdate();	// ***** lock window updates while filling list *****

	m_wndList.DeleteAllItems();
}

LRESULT ArxRleUiDlgDrawCondition::OnCheckBox(WPARAM wParam, LPARAM lParam)
{
	// Called when the user clicked on a checkbox in the list control
	int nItem = (int)wParam; // Item index
	UINT nMouseEvent  = (UINT)lParam; // Mouse event, usually being WM_LBUTTONDOWN or WM_RBUTTONDOWN

	// TODO: 在此添加控件通知处理程序代码

	return (LRESULT)0;
}

LRESULT ArxRleUiDlgDrawCondition::OnItemSorted(WPARAM wParam, LPARAM lParam)
{
	// Called when a column of list items have been sorted
	int nColumn = (int)wParam;
	BOOL bAscending = (BOOL)lParam;

	// TODO: 在此添加控件通知处理程序代码

	return (LRESULT)0;
}

double ArxRleUiDlgDrawCondition::SqxCalc(double stat, SQX sqx)
{
	double h = -9999.9999;
	double S = sqx.S, H = sqx.H, R = sqx.R, I1 = sqx.I1, I2 = sqx.I2, T = sqx.T, E = sqx.E, L = sqx.L;

	if(stat < (S - T) || stat > (S + T))
	{
		if (stat < S)
			h = H - (S - stat) * I1;
		else
			h = H + (stat - S) * I2;
	}
	else
	{
		if(stat < S)
			h = H - (S - stat) * I1 + (stat - S + T) * (stat - S + T) / 2 / R * ((I1 > I2) ? -1.0 : 1.0);
		else
			h = H + (stat - S) * I2 + (S + T - stat) * (S + T - stat) / 2 / R * ((I1 > I2) ? -1.0 : 1.0);
	}

	return h;
}

BOOL ArxRleUiDlgDrawCondition::IsSqx(double stat, SQX sqx)
{
	double S = sqx.S, T = sqx.T;

	if(stat < (S - T) || stat > (S + T))
		return FALSE;

	return TRUE;
}

vector<SQX> ArxRleUiDlgDrawCondition::GetSqxs(CString filePath)
{
	vector<SQX> vecSqx;
	CStdioFile file;
	if(file.Open(filePath, CFile::modeRead))
	{
		CString str;
		int nPos = 0;
		while(file.ReadString(str))
		{
			str.Trim();
			SQX sqx;
			if((nPos = str.Find(_T("S"))) >= 0) sqx.S = _tstof(str.Mid(nPos+2));
			if((nPos = str.Find(_T("H"))) >= 0) sqx.H = _tstof(str.Mid(nPos+2));
			if((nPos = str.Find(_T("R"))) >= 0) sqx.R = _tstof(str.Mid(nPos+2));
			if((nPos = str.Find(_T("I1"))) >= 0) sqx.I1 = _tstof(str.Mid(nPos+3))/1000;
			if((nPos = str.Find(_T("I2"))) >= 0) sqx.I2 = _tstof(str.Mid(nPos+3))/1000;
			sqx.L = fabs(sqx.R * (sqx.I1 - sqx.I2));
			sqx.T = sqx.L / 2;
			if(sqx.R != 0) sqx.E = sqx.T * sqx.T / 2 / sqx.R;

			vecSqx.push_back(sqx);
		}

		file.Close();
	}

	return vecSqx;
}

SQX ArxRleUiDlgDrawCondition::GetSqx(double stat, vector<SQX> vecSqx)
{
	if(vecSqx.size() == 0) return SQX();
	if (stat <= vecSqx[0].S) return vecSqx[0];
	if (stat >= vecSqx[vecSqx.size() - 1].S) return vecSqx[vecSqx.size() - 1];
	for (int i = 1; i < vecSqx.size(); i++ )
	{
		SQX sqx1 = vecSqx[i-1], sqx2 = vecSqx[i];
		if (stat >= sqx1.S - sqx1.T && stat <= sqx1.S + sqx1.T)
			return sqx1;
		if (stat > sqx1.S + sqx1.T && stat < sqx2.S - sqx2.T)
			return sqx1;
	}

	return SQX();
}
