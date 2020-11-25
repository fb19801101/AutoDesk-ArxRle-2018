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

#include "ArxRleUiDlgMeasure.h"
#include "AcadUtils\ArxRleSelSet.h"


/**************************************************************************
**
**  measureInData
**
**  **���ز�������ת��ΪCAD��
**
*************************************/
void measurePtInData() //���������
{
	ArxRleUiDlgMeasure dlg(acedGetAcadDwgView());
	dlg.SetInData();
	dlg.SetDataType(1);
	dlg.DoModal();
}
void measurePtOutData() //���������
{
	ArxRleUiDlgMeasure dlg(acedGetAcadDwgView());
	dlg.SetInData(FALSE);
	dlg.SetDataType(1);
	dlg.DoModal();
}

// ArxRleUiDlgMeasure �Ի���

IMPLEMENT_DYNAMIC(ArxRleUiDlgMeasure, CDialogEx)

ArxRleUiDlgMeasure::ArxRleUiDlgMeasure(CWnd* pParent)
	: CDialogEx(ArxRleUiDlgMeasure::IDD, pParent)
	, m_strDataFileName(_T("pt.pt"))
	, m_bInData(TRUE)
	, m_nDataType(1)
{
	m_hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_ARXRLE);
	m_strDataFilePathName = GetCurDwgFilePath().t_str() + m_strDataFileName;
}

ArxRleUiDlgMeasure::~ArxRleUiDlgMeasure()
{
}

void ArxRleUiDlgMeasure::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ARXRLE_MEASURE_CB_DATATYPE, m_cbDataType);
	DDX_Control(pDX, ARXRLE_MEASURE_CB_RESULTTYPE, m_cbResultType);
	DDX_Control(pDX, ARXRLE_MEASURE_BN_DATAFILE, m_bnDataFileSel);
	DDX_Text(pDX, ARXRLE_MEASURE_EB_DATAFILE, m_strDataFilePathName);
	DDX_Control(pDX, ARXRLE_MEASURE_CK_XY, m_ckXY);
	DDX_Control(pDX, ARXRLE_MEASURE_CK_Z, m_ckZ);
	DDX_Control(pDX, ARXRLE_MEASURE_CK_HDM, m_ckHDM);
	DDX_Control(pDX, ARXRLE_MEASURE_CK_ZDM, m_ckZDM);
}

BEGIN_MESSAGE_MAP(ArxRleUiDlgMeasure, CDialogEx)
	ON_BN_CLICKED(ARXRLE_MEASURE_BN_DATAFILE, &ArxRleUiDlgMeasure::OnBnClickedMeasureButtonDatafile)
	ON_BN_CLICKED(IDOK, &ArxRleUiDlgMeasure::OnBnClickedOk)
END_MESSAGE_MAP()


// ArxRleUiDlgMeasure ��Ϣ�������
BOOL ArxRleUiDlgMeasure::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(m_hIcon,TRUE);
	SetIcon(m_hIcon,FALSE);

	HICON hIcon= AfxGetApp()->LoadIcon(ARXRLE_ICON_SELECT);
	m_bnDataFileSel.SetIcon(hIcon);
	m_cbDataType.AddString(_T("---X---Y---Z---"));
	m_cbDataType.AddString(_T("---Y---X---Z---"));
	m_cbDataType.SetCurSel(0);

	m_cbResultType.AddString(_T("����ʽ"));
	m_cbResultType.AddString(_T("����ʽ"));
	m_cbResultType.SetCurSel(1);

	if(IsInData())
	{
		SetWindowText(L"�����������");
		m_cbResultType.EnableWindow(TRUE);
		m_ckXY.EnableWindow(TRUE);
		m_ckZ.EnableWindow(TRUE);
		m_ckHDM.EnableWindow(TRUE);
		m_ckZDM.EnableWindow(TRUE);
	}
	else
	{
		SetWindowText(L"������������");
		m_cbResultType.EnableWindow(FALSE);
		m_ckXY.EnableWindow(FALSE);
		m_ckZ.EnableWindow(FALSE);
		m_ckHDM.EnableWindow(FALSE);
		m_ckZDM.EnableWindow(FALSE);
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void ArxRleUiDlgMeasure::OnBnClickedMeasureButtonDatafile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �����ļ�������
	TCHAR szFilter[] = _T("���ļ�|*.pt|�ı��ļ�|*.txt|�����ļ�|*.*||");
	// ������ļ��Ի���
	CFileDialog FileDlg(IsInData(), _T("pt"), NULL, 0, szFilter, this);

	// ����Ĭ��·��
	FileDlg.m_ofn.lpstrInitialDir = GetCurDwgFilePath();

	// ��ʾ���ļ��Ի���
	if(IDOK == FileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����
		m_strDataFileName = FileDlg.GetFileName();
		m_strDataFilePathName = FileDlg.GetPathName();
		UpdateData(FALSE);
	}
}

void ArxRleUiDlgMeasure::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();

	if(IsInData())
	{
		acutPrintf(_T("\n---��ȡ�ļ���ȫ·��: %s---"), m_strDataFilePathName);
		acutPrintf(_T("\n---���ȫ���㵽��ǰDWG�У�---"));

		if(!m_ckHDM.GetCheck() && !m_ckZDM.GetCheck())
		{
			m_vecPt3D = ReadPtDataFile(m_strDataFilePathName, m_cbDataType.GetCurSel() == 1);
		}

		if(m_ckHDM.GetCheck() && !m_ckZDM.GetCheck())
		{
			m_vecPt3D = ReadHdmDataFile(m_strDataFilePathName, m_cbDataType.GetCurSel() == 1);
		}

		if(!m_ckHDM.GetCheck() && m_ckZDM.GetCheck())
		{
			m_vecPt3D = ReadZdmDataFile(m_strDataFilePathName, m_cbDataType.GetCurSel() == 1);
		}

		AddLayer("arx_line",4);
		SetCurLayer("arx_line");
		if(m_cbResultType.GetCurSel() == 1)
			AddPolyline(m_vecPt3D);
		else
			AddPoint(m_vecPt3D);

		AddLayer("arx_text",3);
		SetCurLayer("arx_text");
		AddTextStyle("arx_text");
		AcDbObjectId tsId = SetCurTextStyle("arx_text");
		AcDbTextStyleTableRecord* ts =  (AcDbTextStyleTableRecord*)GetRecordPtr(tsId);
		if(m_ckXY.GetCheck() && !m_ckZ.GetCheck())
		{
			for(int i=0; i<m_vecPt3D.size();i++)
			{
				CPt3d pt = m_vecPt3D[i];
				CText text;
				ArxRleString str;
				str.Format("X=%.4f;Y=%.4f",pt.x,pt.y);
				text.SetText(str);
				text.SetTextStyle(tsId);
				text.SetTextHeight(2);
				text.SetPosition(pt);
				text.SetAlignmentMode(ArxLeftBottom);
				text.SetWidthFactor(ts->xScale());
				AddEntity(&text);
			}
		}

		if(!m_ckXY.GetCheck() && m_ckZ.GetCheck())
		{
			for(int i=0; i<m_vecPt3D.size();i++)
			{
				CPt3d pt = m_vecPt3D[i];
				CText text;
				ArxRleString str;
				str.Format("%.3f",pt.z);
				text.SetText(str);
				text.SetTextStyle(tsId);
				text.SetTextHeight(2);
				text.SetPosition(pt);
				text.SetAlignmentMode(ArxLeftBottom);
				text.SetWidthFactor(ts->xScale());
				AddEntity(&text);
			}
		}

		if(m_ckXY.GetCheck() && m_ckZ.GetCheck())
		{
			for(int i=0; i<m_vecPt3D.size();i++)
			{
				CPt3d pt = m_vecPt3D[i];
				CText text;
				ArxRleString str;
				str.Format("X=%.4f;Y=%.4f;Z=%.3f",pt.x,pt.y,pt.z);
				text.SetText(str);
				text.SetTextStyle(tsId);
				text.SetTextHeight(2);
				text.SetPosition(pt);
				text.SetAlignmentMode(ArxLeftBottom);
				text.SetWidthFactor(ts->xScale());
				AddEntity(&text);
			}
		}
	}
	else
	{
		acutPrintf(_T("\n---����ļ���ȫ·��: %s---"), m_strDataFilePathName);
		acutPrintf(_T("\n---���ȫ���㵽ָ���ļ��У�---"));
		GetPolylineVertexs();
		WritePtDataFile(m_vecPt3D, m_strDataFilePathName);
		ShellExecuteOpen(m_strDataFilePathName, L"notepad.exe");
	}
}

void ArxRleUiDlgMeasure::GetPolylineVertexs()
{
	ArxRleSelSet ss;
	m_vecPt3D.clear();
	if(ss.userSelect() == ArxRleSelSet::kSelected)
	{
		AcDbObjectIdArray objs;
		ss.asArray(objs);
		if(!objs.isEmpty())
		{
			AcDbEntity* ent;
			Acad::ErrorStatus es;

			int len = objs.length();
			for(int i=0; i<len; i++)
			{
				es = acdbOpenAcDbEntity(ent, objs[i], AcDb::kForRead, true);		// might have passed in erased ones
				if(es == Acad::eOk)
				{
					if(ent->isKindOf(AcDbPolyline::desc()))
					{
						AcDbPolyline* polyline = AcDbPolyline::cast(ent);
						int size = polyline->numVerts();
						for(int j=0; j<size; j++)
						{
							AcGePoint2d pt;
							es = polyline->getPointAt(j, pt);
							m_vecPt3D.push_back(CPt3d(pt.x,pt.y,0));
						}
					}

					if(ent->isKindOf(AcDb2dPolyline::desc()) || ent->isKindOf(AcDb3dPolyline::desc()))
					{
						AcDb2dPolyline* pline2d;
						AcDb3dPolyline* pline3d;
						AcDbObjectIterator* vertexIter;

						if((pline2d = AcDb2dPolyline::cast(ent)) != NULL)
							vertexIter = pline2d->vertexIterator();
						else if((pline3d = AcDb3dPolyline::cast(ent)) != NULL)
							vertexIter = pline3d->vertexIterator();
						else
							vertexIter = NULL;

						if(vertexIter != NULL)
						{
							while (vertexIter->done() == false)
							{
								AcDbEntity* vertexEnt;
								es = acdbOpenAcDbEntity(vertexEnt, vertexIter->objectId(), AcDb::kForRead, true);
								if(es == Acad::eOk)
								{
									AcDb2dVertex* vertex = AcDb2dVertex::cast(vertexEnt);
									if(vertex != NULL)
									{
										AcGePoint3d pt = vertex->position();
										m_vecPt3D.push_back(CPt3d(pt.x,pt.y,pt.z));
									}
								}
								vertexIter->step();
							}
						}

						delete vertexIter;
					}

					ent->close();
				}
			}
		}
	}
}
