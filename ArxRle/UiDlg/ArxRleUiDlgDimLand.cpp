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

#include "ArxRleUiDlgDimLand.h"
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
**  drawDimLand
**
**  **用地标注对话框
**
*************************************/
void drawDimLand() //用地标注对话框
{
	ArxRleUiDlgDimLand dlg(acedGetAcadDwgView());
	dlg.DoModal();
}


// ArxRleUiDlgDimLand 对话框

IMPLEMENT_DYNAMIC(ArxRleUiDlgDimLand, CAcUiDialog)

ArxRleUiDlgDimLand::ArxRleUiDlgDimLand(CWnd* pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/)
	: CAcUiDialog(ArxRleUiDlgDimLand::IDD, pParent, hInstance)
	, m_strDataFileName(_T(""))
{
	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);

	m_strDataFilePathName = GetCurDwgFilePath().t_str() + m_strDataFileName;

	m_pToolTip = new CToolTipCtrl;
	m_bFileSel = FALSE;
	m_bFlag = FALSE;
}

ArxRleUiDlgDimLand::~ArxRleUiDlgDimLand()
{
	if(m_pToolTip != NULL) delete m_pToolTip;
	m_pToolTip = NULL;
}

void ArxRleUiDlgDimLand::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_DIMLAND_BN_PT1,    m_bnPt1);
	DDX_Control(pDX, ARXRLE_DIMLAND_BN_PT2,    m_bnPt2);
	DDX_Control(pDX, ARXRLE_DIMLAND_EB_X1,     m_etX1);
	DDX_Control(pDX, ARXRLE_DIMLAND_EB_Y1,     m_etY1);
	DDX_Control(pDX, ARXRLE_DIMLAND_EB_Z1,     m_etZ1);
	DDX_Control(pDX, ARXRLE_DIMLAND_EB_X2,     m_etX2);
	DDX_Control(pDX, ARXRLE_DIMLAND_EB_Y2,     m_etY2);
	DDX_Control(pDX, ARXRLE_DIMLAND_EB_Z2,     m_etZ2);
	DDX_Control(pDX, ARXRLE_DIMLAND_EB_PRIX,   m_etPrix);
	DDX_Control(pDX, ARXRLE_DIMLAND_EB_GAP,    m_etGap);
	DDX_Control(pDX, ARXRLE_DIMLAND_EB_FONT,   m_etFont);
	DDX_Control(pDX, ARXRLE_DIMLAND_EB_SIZE,   m_etSize);
	DDX_Control(pDX, ARXRLE_DIMLAND_BN_ENT,    m_bnEnt);
	DDX_Control(pDX, ARXRLE_DIMLAND_BN_DIMLAND,m_bnDimLand);
	DDX_Control(pDX, ARXRLE_DIMLAND_LC_RESULT, m_wndList);
	DDX_Control(pDX, ARXRLE_DIMLAND_BN_IMPORT, m_bnImport);
	DDX_Control(pDX, ARXRLE_DIMLAND_BN_EXPORT, m_bnExport);
	DDX_Control(pDX, ARXRLE_DIMLAND_BN_CLEAR,  m_bnClear);
}


BEGIN_MESSAGE_MAP(ArxRleUiDlgDimLand, CAcUiDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(ARXRLE_DIMLAND_BN_PT1, OnBnClickedBtnPt1)
	ON_BN_CLICKED(ARXRLE_DIMLAND_BN_PT2, OnBnClickedBtnPt2)
	ON_BN_CLICKED(ARXRLE_DIMLAND_BN_ENT, OnBnClickedBtnEnt)
	ON_BN_CLICKED(ARXRLE_DIMLAND_BN_DIMLAND, OnBnClickedBtnDimLand)
	ON_BN_CLICKED(ARXRLE_DIMLAND_BN_IMPORT, OnBnClickedBtnImport)
	ON_BN_CLICKED(ARXRLE_DIMLAND_BN_EXPORT, OnBnClickedBtnExport)
	ON_BN_CLICKED(ARXRLE_DIMLAND_BN_CLEAR, OnBnClickedBtnClear)
END_MESSAGE_MAP()


// ArxRleUiDlgDimLand 消息处理程序
BOOL ArxRleUiDlgDimLand::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	//Change style to layered window style...
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

	m_bnEnt.SetIcon(ARXRLE_ICON_SELECT);
	m_bnEnt.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnEnt.SetFlat();
	m_bnEnt.ActivateTooltip();
	m_bnEnt.SetTooltipText(L"实体选择");

	m_bnDimLand.SetIcon(ARXRLE_ICON_CORRECT);
	m_bnDimLand.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnDimLand.SetFlat();
	m_bnDimLand.ActivateTooltip();
	m_bnDimLand.SetTooltipText(L"用地标注");

	m_bnImport.SetIcon(ARXRLE_ICON_FOLDER);
	m_bnImport.SetAlign(ArxRleButton::ST_ALIGN_VERT);
	m_bnImport.SetFlat();
	m_bnImport.ActivateTooltip();
	m_bnImport.SetTooltipText(L"导入参数");

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

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL ArxRleUiDlgDimLand::PreTranslateMessage(MSG *pMsg)
{
	if( pMsg->message == WM_MOUSEMOVE || pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP)
	{
		m_pToolTip->RelayEvent(pMsg);
	}
	return CAcUiDialog::PreTranslateMessage(pMsg);
}

LRESULT ArxRleUiDlgDimLand::OnAcadKeepFocus(WPARAM, LPARAM)
{
	return TRUE;
}

void ArxRleUiDlgDimLand::OnShowWindow(BOOL bShow, UINT nStatus)
{
	// TODO: 在此处添加消息处理程序代码
	if(!m_bFlag)
	{
		m_bFlag = TRUE;
		CRect rect;
		GetWindowRect(&rect);
		CRect rc(rect.CenterPoint().x,rect.CenterPoint().y,rect.CenterPoint().x,rect.CenterPoint().y);
		int Width = rect.Width();
		int Height = rect.Height();
		for(int n=20; n>=1; n--)
		{
			rc.InflateRect(Width/40,Height/40);
			MoveWindow(&rc);
			ShowWindow(SW_SHOW);
			Sleep(10);
		}
		MoveWindow(&rect);
		ShowWindow(SW_SHOW);
	}

	CAcUiDialog::OnShowWindow(bShow, nStatus);
}

void ArxRleUiDlgDimLand::OnClose()
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

void ArxRleUiDlgDimLand::OnBnClickedBtnPt1()
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

void ArxRleUiDlgDimLand::OnBnClickedBtnPt2()
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

void ArxRleUiDlgDimLand::OnBnClickedBtnEnt()
{
	// TODO: 在此添加控件通知处理程序代码

}

void ArxRleUiDlgDimLand::OnBnClickedBtnDimLand()
{
	// TODO: 在此添加控件通知处理程序代码
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

	CString prix = _T("道");
	m_etPrix.GetWindowText(prix);
	m_etGap.GetWindowText(str);
	double gap = _tstof(str);
	m_etFont.GetWindowText(str);
	double font = _tstof(str);
	m_etSize.GetWindowText(str);
	double size = _tstof(str);

	if(!m_bFileSel)
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
								((AcDbCurve*)ent)->getPointAtDist(dist1+gap,pt2);
								//AddPoint(CPt3d(pt2));

								AcGePoint3d pt_tmp;
								((AcDbCurve*)ent)->getPointAtDist(dist1+gap+0.01,pt_tmp);
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
											pline.AddPoint(p.GetLineEnd(5*font/2,zw+PI));
											pline.AddPoint(p.GetLineEnd(5*font/2,zw));
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
													
											pline.AddPoint(p.GetLineEnd(5*font/2,zw+PI/2));
											pline.AddPoint(p.GetLineEnd(5*font/2,zw-PI/2));
											AddEntity(&pline);
										}
									}
								}

								ArxRleString dimtext;
								dimtext.ConvertDouble(gap);
								dimtext += prix;
								AddText(dimtext, CPt3d(pt2), 1, 0, ArxLeftBottom);
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
			gap += vecDist[i];
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
									((AcDbCurve*)ent)->getPointAtDist(dist1+gap,pt2);
									//AddPoint(CPt3d(pt2));

									AcGePoint3d pt_tmp;
									((AcDbCurve*)ent)->getPointAtDist(dist1+gap+0.01,pt_tmp);
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
												pline.AddPoint(p.GetLineEnd(5*font/2,zw+PI));
												pline.AddPoint(p.GetLineEnd(5*font/2,zw));
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
												pline.AddPoint(p.GetLineEnd(5*font/2,zw+PI/2));
												pline.AddPoint(p.GetLineEnd(5*font/2,zw-PI/2));
												AddEntity(&pline);
											}
										}
									}

										ArxRleString dimtext;
										dimtext.ConvertDouble(vecDist[i]);
										dimtext += prix;
										AddText(dimtext, CPt3d(pt2), 1.8, 0, ArxLeftBottom);
								}
							}
							ent->close();
						}
					}
				}
			}
		}
	}

	CompleteEditorCommand();
}

void ArxRleUiDlgDimLand::OnBnClickedBtnImport()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置文件过滤器
	CompleteEditorCommand();
	m_bnEnt.SetCheck(0);

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
		m_bFileSel = TRUE;
	}
	else
		m_bFileSel = FALSE;
}

void ArxRleUiDlgDimLand::OnBnClickedBtnExport()
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

void ArxRleUiDlgDimLand::OnBnClickedBtnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	CompleteEditorCommand();
	m_bnClear.SetCheck(0);

	m_wndList.LockWindowUpdate();	// ***** lock window updates while filling list *****

	m_wndList.DeleteAllItems();
}

LRESULT ArxRleUiDlgDimLand::OnItemSorted(WPARAM wParam, LPARAM lParam)
{
	// Called when a column of list items have been sorted
	int nColumn = (int)wParam;
	BOOL bAscending = (BOOL)lParam;

	// TODO: 在此添加控件通知处理程序代码

	return (LRESULT)0;
}