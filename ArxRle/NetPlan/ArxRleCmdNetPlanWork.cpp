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

#include "ArxRleCmdNetPlanWork.h"
#include "ArxRleUiTdmNetPlan.h"
#include "ArxRleNetPlanWork.h"
#include "ArxRleNetPlanWorkStyle.h"
#include "AcadUtils\ArxRleUtils.h"
#include "AcadUtils\ArxRleSelSet.h"
#include "AcadUtils\ArxRleApply.h"
#include "Prompt\ArxRleKeywordArray.h"
#include "DbEntity\ArxRleEntityClass.h"
#include "DbEntity\ArxRleFile.h"

#define dx        4.0
#define dy        4.0


vector<ArxRleNetPlanWorkItem> ArxRleCmdNetPlanWork::m_itemNetPlanWorkList;



/****************************************************************************
**
**  ArxRleCmdNetPlanWork::registerCommandLineFunctions
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
	cmdStack->addCommand(appname, _T("ArxRleNetPlanInitParam"),           _T("NetPlanInitParam"),           ACRX_CMD_MODAL, &initParam);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanImportWork"),          _T("NetPlanImportWork"),          ACRX_CMD_MODAL, &importWork);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanExportWork"),          _T("NetPlanExportWork"),          ACRX_CMD_MODAL, &exportWork);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanImportStyle"),         _T("NetPlanImportStyle"),         ACRX_CMD_MODAL, &importStyle);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanExportStyle"),         _T("NetPlanExportStyle"),         ACRX_CMD_MODAL, &exportStyle);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanInsertGrid"),          _T("NetPlanInsertGrid"),          ACRX_CMD_MODAL, &insertGrid);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanInsertTable"),         _T("NetPlanInsertTable"),         ACRX_CMD_MODAL, &insertTable);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanBatchWork"),           _T("NetPlanBatchWork"),           ACRX_CMD_MODAL, &batchWork);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanBatchProc"),           _T("NetPlanBatchProc"),           ACRX_CMD_MODAL, &batchProc);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanReSetProc"),           _T("NetPlanReSetProc"),           ACRX_CMD_MODAL, &reSetProc);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanReNumber"),            _T("NetPlanReNumber"),            ACRX_CMD_MODAL, &reNumber);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanBindWork"),            _T("NetPlanBindWork"),            ACRX_CMD_MODAL, &bindWork);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanFlushStyle"),          _T("NetPlanFlushStyle"),          ACRX_CMD_MODAL, &flushStyle);

	cmdStack->addCommand(appname, _T("ArxRleNetPlanCmdWork"),             _T("NetPlanCmdWork"),             ACRX_CMD_MODAL, &cmdLineWork);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanWorkAdd"),             _T("NetPlanWorkAdd"),             ACRX_CMD_MODAL, &workAdd);		

	cmdStack->addCommand(appname, _T("ArxRleNetPlanCmdModify"),           _T("NetPlanCmdModify"),           ACRX_CMD_MODAL, &cmdLineModify);
    cmdStack->addCommand(appname, _T("ArxRleNetPlanWorkModifyWorkInfo"),  _T("NetPlanWorkModifyWorkInfo"),  ACRX_CMD_MODAL, &modifyWorkInfo);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanWorkModifyWorkNodes"), _T("NetPlanWorkModifyWorkNodes"), ACRX_CMD_MODAL, &modifyWorkNodes);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanWorkModifyWorkDays"),  _T("NetPlanWorkModifyWorkDays"),  ACRX_CMD_MODAL, &modifyWorkDays);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanWorkModifyWorkName"),  _T("NetPlanWorkModifyWorkName"),  ACRX_CMD_MODAL, &modifyWorkName);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanWorkModifyWorkStyle"), _T("NetPlanWorkModifyWorkStyle"), ACRX_CMD_MODAL, &modifyWorkStyle);

	cmdStack->addCommand(appname, _T("ArxRleNetPlanCmdStyle"),		      _T("NetPlanCmdStyle"),           ACRX_CMD_MODAL, &cmdLineStyle);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanStyleAdd"),            _T("NetPlanStyleAdd"),           ACRX_CMD_MODAL, &styleAdd);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanStyleModify"),         _T("NetPlanStyleModify"),        ACRX_CMD_MODAL, &styleModify);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanStyleCopy"),           _T("NetPlanStyleCopy"),          ACRX_CMD_MODAL, &styleCopy);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanStyleDelete"),         _T("NetPlanStyleDelete"),        ACRX_CMD_MODAL, &styleDelete);
	cmdStack->addCommand(appname, _T("ArxRleNetPlanStyleCommon"),         _T("NetPlanStyleCommon"),        ACRX_CMD_MODAL, &styleCommon);
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::setParam
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::initParam() //加载施工网络计划基本设置对话框
{
	ArxRleUiTdmNetPlan dlg(acedGetAcadDwgView());
	dlg.DoModal();
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::importWork
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::importWork()
{
	CString path;
	TCHAR szFilter[] = _T("工序文件|*.work|文本文件|*.txt|所有文件|*.*||");
	CFileDialog fileDlg(TRUE, _T("Work Data"), NULL, 0, szFilter);
	fileDlg.m_ofn.lpstrInitialDir = GetCurDwgFilePath();
	if(IDOK == fileDlg.DoModal())
		path = fileDlg.GetPathName();
	else
		return;

	ArxRleFile file;
	if(!file.OpenFile(path)) return;

	ArxRleStringList strs;
	while(file.ReadLine(&strs, ','))
	{
		ArxRleNetPlanWork* work = new ArxRleNetPlanWork;
		file.ReadLine(&strs, ',');
		int cnt = strs.size();
		if(cnt == 2) if(strs[0] == ArxRleString("WorkName")) work->setLabelUp(strs[1]);
		file.ReadLine(&strs, ',');
		cnt = strs.size();
		if(cnt == 2) if(strs[0] == ArxRleString("WorkStyle")) work->setWorkStyle(strs[1]);
		file.ReadLine(&strs, ',');
		if(cnt == 2) if(strs[0] == ArxRleString("BeginNode")) work->setLabelBegin(strs[1]);
		file.ReadLine(&strs, ',');
		if(cnt == 2) if(strs[0] == ArxRleString("EndNode")) work->setLabelEnd(strs[1]);
		file.ReadLine(&strs, ',');
		cnt = strs.size();
		if(cnt == 4) if(strs[0] == ArxRleString("BeginPoint(XYZ)"))
		{
			CPt3d pt;
			pt.x = _tstof(strs[1]);
			pt.y = _tstof(strs[2]);
			pt.z = _tstof(strs[3]);
			work->setPointBegin(pt);
		}
		file.ReadLine(&strs, ',');
		cnt = strs.size();
		if(cnt == 4) if(strs[0] == ArxRleString("EndPoint(XYZ)"))
		{
			CPt3d pt;
			pt.x = _tstof(strs[1]);
			pt.y = _tstof(strs[2]);
			pt.z = _tstof(strs[3]);
			work->setPointEnd(pt);
		}
		file.ReadLine(&strs, ',');
		cnt = strs.size();
		if(cnt == 4) if(strs[0] == ArxRleString("LeftPoint(XYZ)"))
		{
			CPt3d pt;
			pt.x = _tstof(strs[1]);
			pt.y = _tstof(strs[2]);
			pt.z = _tstof(strs[3]);
			work->setPointLeft(pt);
		}
		file.ReadLine(&strs, ',');
		cnt = strs.size();
		if(cnt == 4) if(strs[0] == ArxRleString("MidPoint(XYZ)"))
		{
			CPt3d pt;
			pt.x = _tstof(strs[1]);
			pt.y = _tstof(strs[2]);
			pt.z = _tstof(strs[3]);
			work->setPointMid(pt);
		}
		file.ReadLine(&strs, ',');
		cnt = strs.size();
		if(cnt == 4) if(strs[0] == ArxRleString("RightPoint(XYZ)"))
		{
			CPt3d pt;
			pt.x = _tstof(strs[1]);
			pt.y = _tstof(strs[2]);
			pt.z = _tstof(strs[3]);
			work->setPointRight(pt);
		}

		AddEntity(work);
	}

	file.CloseFile();
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::exportWork
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::exportWork()
{
	ArxRleSelSet ss;
	AcDbObjectId tsId;
	if(ss.userSelect() == ArxRleSelSet::kSelected)
	{    // have user select entities from DWG
		AcDbObjectIdArray objList;
		ss.asArray(objList);
		if(!objList.isEmpty())
		{
			CString path;
			TCHAR szFilter[] = _T("工序文件|*.work|文本文件|*.txt|所有文件|*.*||");
			CFileDialog fileDlg(FALSE, _T("Work Data"), NULL, 0, szFilter);
			fileDlg.m_ofn.lpstrInitialDir = GetCurDwgFilePath();
			if(IDOK == fileDlg.DoModal())
				path = fileDlg.GetPathName();
			else
				return;

			ArxRleFile file;
			if(!file.CreateFile(path)) return;

			AcDbEntity* ent;
			Acad::ErrorStatus es;

			int len = objList.length();
			for(int i=0; i<len; i++)
			{
				es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForWrite, true);		// might have passed in erased ones
				if(es == Acad::eOk)
				{
					CString temp;
					if(ent->isKindOf(ArxRleNetPlanWork::desc()))
					{
						ArxRleNetPlanWork* work = (ArxRleNetPlanWork*)ent;
						temp.Format(_T("%.4d"),i);
						file.WriteLine(temp);
						temp.Format(_T("WorkName,%s"),work->getLabelUp().t_str());
						file.WriteLine(temp);
						temp.Format(_T("WorkStyle,%s"),work->getWorkStyle().t_str());
						file.WriteLine(temp);
						temp.Format(_T("BeginNode,%s"),work->getLabelBegin().t_str());
						file.WriteLine(temp);
						temp.Format(_T("EndNode,%s"),work->getLabelEnd().t_str());
						file.WriteLine(temp);
						temp.Format(_T("BeginPoint(XYZ),%.3f,%.3f,%.3f"),work->getPointBegin().x,work->getPointBegin().y,work->getPointBegin().z);
						file.WriteLine(temp);
						temp.Format(_T("EndPoint(XYZ),%.3f,%.3f,%.3f"),work->getPointEnd().x,work->getPointEnd().y,work->getPointEnd().z);
						file.WriteLine(temp);
						temp.Format(_T("LeftPoint(XYZ),%.3f,%.3f,%.3f"),work->getPointLeft().x,work->getPointLeft().y,work->getPointLeft().z);
						file.WriteLine(temp);
						temp.Format(_T("MidPoint(XYZ),%.3f,%.3f,%.3f"),work->getPointMid().x,work->getPointMid().y,work->getPointMid().z);
						file.WriteLine(temp);
						temp.Format(_T("RightPoint(XYZ),%.3f,%.3f,%.3f"),work->getPointRight().x,work->getPointRight().y,work->getPointRight().z);
						file.WriteLine(temp);
					}
					ent->close();
				}
			}

			file.CloseFile();
		}
	}
}


/****************************************************************************
**
**  ArxRleCmdNetPlanWork::importStyle
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::importStyle()
{
	CString path;
	TCHAR szFilter[] = _T("样式文件|*.style|文本文件|*.txt|所有文件|*.*||");
	CFileDialog fileDlg(TRUE, _T("Work Style"), NULL, 0, szFilter);
	fileDlg.m_ofn.lpstrInitialDir = GetCurDwgFilePath();
	if(IDOK == fileDlg.DoModal())
		path = fileDlg.GetPathName();
	else
		return;

	ArxRleFile file;
	if(!file.OpenFile(path)) return;

	ArxRleStringList strs;
	AcDbDictionary* dict = ArxRleUtils::openDictionaryForWrite(ArxRleNetPlanWorkStyle::dictName(), true, ARXRLEDB);
	if(dict)
	{
		while(file.ReadLine(&strs, ','))
		{
			file.ReadLine(&strs, ',');
			int cnt = strs.size();
			if(cnt == 2) if(strs[0] == ArxRleString("StyleName"))
			{
				CString name = strs[1].t_str();
				if(dict->has(name))
					_printf(_T("Sorry, there is already an entry with %s name."),name);
				else
				{
					ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
					style->setName(name);
					file.ReadLine(&strs, ',');
					cnt = strs.size();
					if(cnt == 2) if(strs[0] == ArxRleString("Layer")) style->setLayer(strs[1]);
					file.ReadLine(&strs, ',');
					cnt = strs.size();
					if(cnt == 2) if(strs[0] == ArxRleString("TextStyleName")) style->setTextStyle(strs[1]);
					file.ReadLine(&strs, ',');
					cnt = strs.size();
					if(cnt == 2) if(strs[0] == ArxRleString("LineTypeName")) style->setLineType(strs[1]);
					file.ReadLine(&strs, ',');
					cnt = strs.size();
					if(cnt == 2) if(strs[0] == ArxRleString("ColorIndex")) style->setColorIndex(_tstoi(strs[1]));
					file.ReadLine(&strs, ',');
					cnt = strs.size();
					if(cnt == 2) if(strs[0] == ArxRleString("LineScale")) style->setLineScale(_tstof(strs[1]));
					file.ReadLine(&strs, ',');
					cnt = strs.size();
					if(cnt == 3) if(strs[0] == ArxRleString("Radius(BE)"))
					{
						style->setRadiusBegin(_tstof(strs[1]));
						style->setRadiusEnd(_tstof(strs[2]));
					}
					file.ReadLine(&strs, ',');
					cnt = strs.size();
					if(cnt == 2) if(strs[0] == ArxRleString("ArrowLen")) style->setLenArrow(_tstof(strs[1]));
					file.ReadLine(&strs, ',');
					cnt = strs.size();
					if(cnt == 3) if(strs[0] == ArxRleString("Size(LN)"))
					{
						style->setSizeLabel(_tstof(strs[1]));
						style->setSizeNode(_tstof(strs[2]));
					}
					file.ReadLine(&strs, ',');
					cnt = strs.size();
					if(cnt == 3) if(strs[0] == ArxRleString("Gap(DL)"))
					{
						style->setDayGap(_tstof(strs[1]));
						style->setLineGap(_tstof(strs[2]));
					}
					file.ReadLine(&strs, ',');
					cnt = strs.size();
					if(cnt == 5) if(strs[0] == ArxRleString("DrawLabel(BEUD)"))
					{
						style->setDrawLabelBegin(_tstoi(strs[1]));
						style->setDrawLabelEnd(_tstoi(strs[2]));
						style->setDrawLabelUp(_tstoi(strs[3]));
						style->setDrawLabelDown(_tstoi(strs[4]));
					}

					AcDbObjectId objId;
					Acad::ErrorStatus es = dict->setAt(name, style, objId);
					if(es == Acad::eOk) {
						_printf(_T("%s NetPlan Work Style successfully!"),name);
						style->close();
					}
					else
						delete style;
				}
			}
		}

		dict->close();
	}

	file.CloseFile();
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::exportStyle
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::exportStyle()
{
	CString path;
	TCHAR szFilter[] = _T("样式文件|*.style|文本文件|*.txt|所有文件|*.*||");
	CFileDialog fileDlg(FALSE, _T("Work Style"), NULL, 0, szFilter);
	fileDlg.m_ofn.lpstrInitialDir = GetCurDwgFilePath();
	if(IDOK == fileDlg.DoModal())
		path = fileDlg.GetPathName();
	else
		return;

	ArxRleFile file;
	if(!file.CreateFile(path)) return;

	AcDbDictionary *dict;
	dict = ArxRleUtils::openDictionaryForRead(ArxRleNetPlanWorkStyle::dictName(), ARXRLEDB);
	if(dict != NULL)
	{
		ArxRleApply<Dictionary> apply = ArxRleApply<Dictionary>( dict, AcDb::kForRead );
		Dictionary::Iterator* iter;
		apply.createIterator(iter);

		if (NULL != iter)
		{
			for ( int i=1; !iter->done(); apply.stepIterator( iter ),i++)
			{
				Dictionary::Element* elem = apply.getElement( iter );
				if (NULL != elem)
				{
					CString temp;
					ArxRleNetPlanWorkStyle* style = (ArxRleNetPlanWorkStyle*)elem;
					temp.Format(_T("%.4d"),i);
					file.WriteLine(temp);
					temp.Format(_T("StyleName,%s"),style->name().t_str());
					file.WriteLine(temp);
					temp.Format(_T("Layer,%s"),style->layer().t_str());
					file.WriteLine(temp);
					temp.Format(_T("TextStyle,%s"),style->textStyle().t_str());
					file.WriteLine(temp);
					temp.Format(_T("LineType,%s"),style->lineType().t_str());
					file.WriteLine(temp);
					temp.Format(_T("ColorIndex,%d"),style->colorIndex());
					file.WriteLine(temp);
					temp.Format(_T("LineScale,%.3f"),style->lineScale());
					file.WriteLine(temp);
					temp.Format(_T("Radius(BE),%.3f,%.3f"),style->radiusBegin(),style->radiusEnd());
					file.WriteLine(temp);
					temp.Format(_T("ArrowLen,%.3f"),style->lenArrow());
					file.WriteLine(temp);
					temp.Format(_T("Size(LN),%.3f,%.3f"),style->sizeLabel(),style->sizeNode());
					file.WriteLine(temp);
					temp.Format(_T("Gap(DL),%.3f,%.3f"),style->dayGap(),style->lineGap());
					file.WriteLine(temp);
					temp.Format(_T("DrawLabel(BEUD),%d,%d,%d,%d"),style->drawLabelBegin(),style->drawLabelEnd(),style->drawLabelUp(),style->drawLabelDown());
					file.WriteLine(temp);

					elem->close();
				}
			}
			delete iter;
		}
		dict->close();
	}

	file.CloseFile();
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::insertGrid
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::insertGrid()
{
	ArxRleUiPrPoint prPt(_T("请输入插入点"), NULL);
	if(prPt.go() != ArxRleUiPrBase::kOk)
		return;

	AddLayer("表头",2,AcDb::kLnWt025);
	AddLayer("文字",3,AcDb::kLnWt025);
	AddLayer("年线",2,AcDb::kLnWt018);
	AddLayer("月线",8,AcDb::kLnWt013);
	AddLayer("日线",8,AcDb::kLnWt009,"DOT");

	CTime tBegin = ArxRleUiTdmNetPlan::m_itemNetPlanData.tBeginDay;
	CTime tEnd = ArxRleUiTdmNetPlan::m_itemNetPlanData.tEndDay;
	long dDay = (long)(tEnd-tBegin).GetDays()/ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap;

	int a=10,b=6;
	CPt3d ptTL(prPt.value());
	ptTL.y -= a;
	CPt3d ptTR(ptTL);
	ptTR.x += (dDay*dx+dx);

	//边框
	SetCurLayer("表头");
	CPolyline oPolyline;
	CPt3d pt1 = CPt3d(ptTL.x,ptTL.y);
	CPt3d pt2 = CPt3d(ptTL.x+dDay*dx+dx,ptTL.y+a-(ArxRleUiTdmNetPlan::m_itemNetPlanData.nPaperHeight-b*2),0);
	oPolyline.ClearPoint();
	oPolyline.AddRectangular(pt1,pt2);
	oPolyline.SetLineWidth(0.1);
	oPolyline.addToSpaceAndClose();

	//年月日线
	CLine oLine;
	pt1 = CPt3d(ptTL.x,ptTL.y-dy);
	pt2 = CPt3d(ptTL.x+dDay*dx+dx,ptTL.y-dy);
	oLine.SetPoint(pt1,pt2);
	oLine.addToSpaceAndClose();
	pt1 = CPt3d(ptTL.x,ptTL.y-dy*2);
	pt2 = CPt3d(ptTL.x+dDay*dx+dx,ptTL.y-dy*2);
	oLine.SetPoint(pt1,pt2);
	oLine.addToSpaceAndClose();
	pt1 = CPt3d(ptTL.x,ptTL.y-dy*3);
	pt2 = CPt3d(ptTL.x+dDay*dx+dx,ptTL.y-dy*3);
	oLine.SetPoint(pt1,pt2);
	oLine.addToSpaceAndClose();

	CTime tNow = tBegin;
	pt1 = CPt3d(ptTL.x+dx,ptTL.y-dy*2);
	pt2 = CPt3d(ptTL.x+dx,ptTL.y-dy*3);
	for(int i=0; i<dDay; i++)
	{
		tNow += CTimeSpan(ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap,0,0,0);

		if(tNow.GetDay() <= ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap)
		{
			if(tNow.GetMonth() == 1)
				pt1.y = ptTL.y;
			else
				pt1.y = ptTL.y-dy;
		}
		else
			pt1.y = ptTL.y-dy*2;

		oLine.SetPoint(pt1,pt2);
		oLine.addToSpaceAndClose();

		pt1 += CPt3d(dx,0,0);
		pt2 += CPt3d(dx,0,0);
	}

	tNow = tBegin;
	pt1 = CPt3d(ptTL.x+dx,ptTL.y-dy*3);
	pt2 = CPt3d(ptTL.x+dx,ptTL.y+a-(ArxRleUiTdmNetPlan::m_itemNetPlanData.nPaperHeight-b*2),0);
	for(int i=0; i<dDay; i++)
	{
		tNow += CTimeSpan(ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap,0,0,0);
		oLine.SetPoint(pt1,pt2);

		if(tNow.GetDay() <= ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap)
		{
			if(tNow.GetMonth() == 1)
			{
				SetCurLayer("年线");
				if(ArxRleUiTdmNetPlan::m_itemNetPlanData.bYearLine)
					oLine.addToSpaceAndClose();
			}
			else
			{
				SetCurLayer("月线");
				if(ArxRleUiTdmNetPlan::m_itemNetPlanData.bMonthLine)
					oLine.addToSpaceAndClose();
			}
		}
		else
		{
			SetCurLayer("日线");
			oLine.setLineTypeScale(0.1);
			if(ArxRleUiTdmNetPlan::m_itemNetPlanData.bDayLine)
				oLine.addToSpaceAndClose();
		}

		pt1 += CPt3d(dx,0);
		pt2 += CPt3d(dx,0);
	}

	tNow = tBegin;
	pt1 = CPt3d(ptTL.x+dx/2,ptTL.y-dx*2-dx/2,0);
	CString str;
	CText oText;
	AddTextStyle("ArxRleNetPlanNodeItem");
	AcDbObjectId tsId = AddTextStyle("NetPlan","仿宋","");
	SetCurTextStyle("NetPlan");
	oText.SetAlignmentMode(ArxCenter);
	oText.SetTextStyle(tsId);
	for(int i=0; i<dDay+1; i++)
	{
		SetCurLayer("文字");
		oText.SetTextHeight(2);
		oText.SetWidthFactor(0.7);
		oText.SetAlignmentMode(ArxCenter);

		str.Format(_T("%d"),tNow.GetDay());
		oText.SetText(str);
		oText.SetPosition(pt1);
		oText.addToSpaceAndClose();

		if(tNow.GetDay() <= ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap)
		{
			pt1.y = ptTL.y-dy-dy/2;
			str.Format(_T("%d月"),tNow.GetMonth());
			oText.SetText(str);
			oText.SetPosition(pt1);
			oText.SetAlignmentMode(ArxLeftMiddle);
			oText.addToSpaceAndClose();

			if(tNow.GetMonth() == 1)
			{
				pt1.y = ptTL.y-dy/2;
				str.Format(_T("%d年"),tNow.GetYear());
				oText.SetText(str);
				oText.SetPosition(pt1);
				oText.SetAlignmentMode(ArxLeftMiddle);
				oText.addToSpaceAndClose();
			}
		}

		if(i == 0 && tNow.GetMonth() > 1)
		{
			pt1.y = ptTL.y-dy/2;
			str.Format(_T("%d年"),tNow.GetYear());
			oText.SetText(str);
			oText.SetPosition(pt1);
			oText.SetAlignmentMode(ArxLeftMiddle);
			oText.addToSpaceAndClose();

			pt1.y = ptTL.y-dy-dy/2;
			str.Format(_T("%d月"),tNow.GetMonth());
			oText.SetText(str);
			oText.SetPosition(pt1);
			oText.SetAlignmentMode(ArxLeftMiddle);
			oText.addToSpaceAndClose();
		}

		pt1.y = ptTL.y-dx*2-dx/2;
		pt1 += CPt3d(dx,0);
		tNow += CTimeSpan(ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap,0,0,0);
	}

	SetCurLayer("文字");
	oText.SetTextHeight(4);
	oText.SetWidthFactor(0.7);
	oText.SetAlignmentMode(ArxCenter);
	str.Format(_T("%d"),tNow.GetDay());
	oText.SetText(ArxRleUiTdmNetPlan::m_itemNetPlanData.strProject);
	pt1 = CPt3d(ptTL.x+dDay*dx/2,ptTL.y+a/2);
	oText.SetPosition(pt1);
	oText.addToSpaceAndClose();
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::insertTable
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::insertTable()
{
	ArxRleUiPrPoint prPt(_T("请输入插入点"), NULL);
	if(prPt.go() != ArxRleUiPrBase::kOk)
		return;

	AddLayer("表头",2,AcDb::kLnWt025);
	AddLayer("文字",3,AcDb::kLnWt025);
	AddLayer("年线",2,AcDb::kLnWt018);
	AddLayer("月线",8,AcDb::kLnWt013);
	AddLayer("日线",8,AcDb::kLnWt009,"DOT");
	AddLayer("里程",1,AcDb::kLnWt025);

	double fBeginStat = ArxRleUiTdmNetPlan::m_itemNetPlanData.fBeginStat;
	double fEndStat =  ArxRleUiTdmNetPlan::m_itemNetPlanData.fEndStat;
	double fStatGap = ArxRleUiTdmNetPlan::m_itemNetPlanData.fStatGap;
	long dStat = (long)(fEndStat-fBeginStat)/fStatGap;

	CTime tBegin = ArxRleUiTdmNetPlan::m_itemNetPlanData.tBeginDay;
	CTime tEnd = ArxRleUiTdmNetPlan::m_itemNetPlanData.tEndDay;
	long dDay = (long)(tEnd-tBegin).GetDays()/ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap;

	CPt3d ptTL(prPt.value());
	ptTL.y -= 10;
	CPt3d ptBL(ptTL);
	ptBL.y -= (dDay*dy+dy);
	CPt3d ptTR(ptTL);
	ptTR.x += (dStat*dx*3+dx*3);
	CPt3d ptBR(ptTL);
	ptBR.x += (dStat*dx*3+dx*3);
	ptBR.y -= (dDay*dy+dy);

	int a=14,b=34,c=2,d=1.5;

	SetCurLayer("表头");
	//年月日线
	CLine oLine;
	CPt3d pt1 = CPt3d(ptTL.x,ptTL.y-a);
	CPt3d pt2 = CPt3d(ptTR.x,ptTL.y-a);
	oLine.SetPoint(pt1,pt2);
	oLine.addToSpaceAndClose();
	pt1 = CPt3d(ptTL.x,ptTL.y-a-b);
	pt2 = CPt3d(ptTR.x,ptTL.y-a-b);
	oLine.SetPoint(pt1,pt2);
	oLine.addToSpaceAndClose();
	pt1 = CPt3d(ptTL.x,ptTL.y-a-b-c);
	pt2 = CPt3d(ptTR.x,ptTL.y-a-b-c);
	oLine.SetPoint(pt1,pt2);
	oLine.addToSpaceAndClose();
	pt1 = CPt3d(ptBL.x, ptBL.y-a-b-c);
	pt2 = CPt3d(ptBR.x, ptBL.y-a-b-c);
	oLine.SetPoint(pt1,pt2);
	oLine.addToSpaceAndClose();
	pt1 = CPt3d(ptBL.x, ptBL.y-a-b-c-c);
	pt2 = CPt3d(ptBR.x, ptBL.y-a-b-c-c);
	oLine.SetPoint(pt1,pt2);
	oLine.addToSpaceAndClose();

	pt1 = CPt3d(ptTL.x+dx,ptTL.y-a-b-c);
	pt2 = CPt3d(ptBL.x+dx,ptBL.y-a-b-c);
	oLine.SetPoint(pt1,pt2);
	oLine.addToSpaceAndClose();
	pt1 = CPt3d(ptTL.x+dx*2,ptTL.y-a-b-c);
	pt2 = CPt3d(ptBL.x+dx*2,ptBL.y-a-b-c);
	oLine.SetPoint(pt1,pt2);
	oLine.addToSpaceAndClose();
	pt1 = CPt3d(ptTL.x+dx*3,ptTL.y);
	pt2 = CPt3d(ptBL.x+dx*3,ptBL.y-a-b-c-c-a);
	oLine.SetPoint(pt1,pt2);
	oLine.addToSpaceAndClose();

	//边框
	CPolyline oPolyline;
	pt1 = ptTL;
	pt2 = CPt3d(ptBR.x, ptBR.y-a-b-c-c-a);
	oPolyline.ClearPoint();
	oPolyline.AddRectangular(pt1,pt2);
	oPolyline.SetLineWidth(0.1);
	oPolyline.addToSpaceAndClose();

	//里程线
	pt1 = CPt3d(ptTL.x+dx*3, ptTL.y-a+d);
	pt2 = CPt3d(ptTL.x+dx*3, ptTL.y-a);
	for(int i=0; i<dStat; i++)
	{
		oLine.SetPoint(pt1,pt2);
		oLine.addToSpaceAndClose();

		pt1 += CPt3d(dx*3,0);
		pt2 += CPt3d(dx*3,0);
	}

	pt1 = CPt3d(ptBL.x+dx*3, ptBL.y-a-b-c-c-a+d);
	pt2 = CPt3d(ptBL.x+dx*3, ptBL.y-a-b-c-c-a);
	for(int i=0; i<dStat; i++)
	{
		oLine.SetPoint(pt1,pt2);
		oLine.addToSpaceAndClose();

		pt1 += CPt3d(dx*3,0);
		pt2 += CPt3d(dx*3,0);
	}
	
	//年月日线
	CTime tNow = tBegin;
	pt1 = CPt3d(ptBL.x, ptBL.y-a-b-c+dy);
	pt2 = CPt3d(ptBL.x+dx*3, ptBL.y-a-b-c+dy);
	for(int i=0; i<dDay; i++)
	{
		tNow += CTimeSpan(ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap,0,0,0);

		if(tNow.GetDay() <= ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap)
		{
			if(tNow.GetMonth() == 1)
				pt1.x = ptBL.x;
			else
				pt1.x = ptBL.x+dx;
		}
		else
			pt1.x = ptBL.x+dx*2;

		oLine.SetPoint(pt1,pt2);
		oLine.addToSpaceAndClose();

		pt1 += CPt3d(0,dy);
		pt2 += CPt3d(0,dy);
	}

	tNow = tBegin;
	pt1 = CPt3d(ptBL.x+dx*3,ptBL.y-a-b-c+dy);
	pt2 = CPt3d(ptBR.x,ptBR.y-a-b-c+dy);
	for(int i=0; i<dDay; i++)
	{
		tNow += CTimeSpan(ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap,0,0,0);

		oLine.SetPoint(pt1,pt2);
		if(tNow.GetDay() <= ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap)
		{
			if(tNow.GetMonth() == 1)
			{
				SetCurLayer("年线");
				if(ArxRleUiTdmNetPlan::m_itemNetPlanData.bYearLine)
					oLine.addToSpaceAndClose();
			}
			else
			{
				SetCurLayer("月线");
				if(ArxRleUiTdmNetPlan::m_itemNetPlanData.bMonthLine)
					oLine.addToSpaceAndClose();
			}
		}
		else
		{
			SetCurLayer("日线");
			if(ArxRleUiTdmNetPlan::m_itemNetPlanData.bDayLine)
			{
				oLine.setLineTypeScale(0.1);
				oLine.addToSpaceAndClose();
			}
		}

		pt1 += CPt3d(0,dy);
		pt2 += CPt3d(0,dy);
	}

	//里程文字
	pt1 = CPt3d(ptTL.x+dx*3,ptTL.y-a+d);
	CString str;
	CText oText;
	AddTextStyle("ArxRleNetPlanNodeItem");
	AcDbObjectId tsId = AddTextStyle("NetPlan","仿宋","");
	SetCurTextStyle("NetPlan");
	oText.SetTextStyle(tsId);
	for(int i=0; i<dStat; i++)
	{
		SetCurLayer("里程");
		oText.SetTextHeight(2);
		oText.SetRotation(PI/2);
		oText.SetWidthFactor(0.7);
		oText.SetAlignmentMode(ArxLeftMiddle);

		str = FormatStat(fBeginStat+fStatGap*i,5);
		oText.SetText(str);
		oText.SetPosition(pt1);
		oText.addToSpaceAndClose();

		pt1 += CPt3d(dx*3,0);
	}

	pt1 = CPt3d(ptBL.x+dx*3,ptBL.y-a-b-c-c-a+d);
	for(int i=0; i<dStat; i++)
	{
		str = FormatStat(fBeginStat+fStatGap*i,5);
		oText.SetText(str);
		oText.SetPosition(pt1);
		oText.addToSpaceAndClose();

		pt1 += CPt3d(dx*3,0);
	}

	//年月日文字
	tNow = tBegin;
	pt1 = CPt3d(ptBL.x+dx*3-dx/2,ptBL.y-a-b-c+dy/2);
	for(int i=0; i<dDay+1; i++)
	{
		SetCurLayer("文字");
		oText.SetTextHeight(2);
		oText.SetRotation(PI/2);
		oText.SetWidthFactor(0.7);
		oText.SetAlignmentMode(ArxCenter);

		str.Format(_T("%d"),tNow.GetDay());
		oText.SetText(str);
		oText.SetPosition(pt1);
		oText.addToSpaceAndClose();

		if(tNow.GetDay() <= ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap)
		{
			pt1.x = ptBL.x+dx+dx/2;
			str.Format(_T("%d月"),tNow.GetMonth());
			oText.SetText(str);
			oText.SetPosition(pt1);
			oText.SetAlignmentMode(ArxLeftMiddle);
			oText.addToSpaceAndClose();

			if(tNow.GetMonth() == 1)
			{
				pt1.x = ptBL.x+dx/2;
				str.Format(_T("%d年"),tNow.GetYear());
				oText.SetText(str);
				oText.SetPosition(pt1);
				oText.SetAlignmentMode(ArxLeftMiddle);
				oText.addToSpaceAndClose();
			}
		}

		if(i == 0 && tNow.GetMonth() > 1)
		{
			pt1.x = ptBL.x+dx/2;
			str.Format(_T("%d年"),tNow.GetYear());
			oText.SetText(str);
			oText.SetPosition(pt1);
			oText.SetAlignmentMode(ArxLeftMiddle);
			oText.addToSpaceAndClose();

			pt1.x = ptBL.x+dx+dx/2;
			str.Format(_T("%d月"),tNow.GetMonth());
			oText.SetText(str);
			oText.SetPosition(pt1);
			oText.SetAlignmentMode(ArxLeftMiddle);
			oText.addToSpaceAndClose();
		}

		pt1.x = ptBL.x+dx*3-dx/2;
		pt1 += CPt3d(0,dy);
		tNow += CTimeSpan(ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap,0,0,0);
	}

	//里程工点文字
	oText.SetTextHeight(2);
	oText.SetWidthFactor(0.7);
	oText.SetRotation(0);
	oText.SetAlignmentMode(ArxCenter);
	oText.SetText(_T("里程"));
	pt1 = CPt3d(ptTL.x+dx*3/2, ptTL.y-a/2);
	oText.SetPosition(pt1);
	oText.addToSpaceAndClose();
	oText.SetText(_T("工点"));
	pt1 = CPt3d(ptTL.x+dx*3/2, ptTL.y-a-b/2);
	oText.SetPosition(pt1);
	oText.addToSpaceAndClose();
	oText.SetText(_T("里程"));
	pt1 = CPt3d(ptBL.x+dx*3/2, ptBL.y-a-b-c-c-a/2);
	oText.SetPosition(pt1);
	oText.addToSpaceAndClose();

	//标题
	oText.SetTextHeight(4);
	oText.SetWidthFactor(0.7);
	oText.SetRotation(0);
	oText.SetAlignmentMode(ArxCenter);
	oText.SetText(ArxRleUiTdmNetPlan::m_itemNetPlanData.strProject);
	pt1 = CPt3d(ptTL.x+dStat*dx*3/2,ptTL.y+5,0);
	oText.SetPosition(pt1);
	oText.addToSpaceAndClose();
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::loadData
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::batchWork()
{
	CXTPExcelUtil xls;
	xls.InitExcel();
	if(FileExist(ArxRleUiTdmNetPlan::m_itemNetPlanData.strXlsFilePath))
	{
		xls.OpenExcel(ArxRleUiTdmNetPlan::m_itemNetPlanData.strXlsFilePath);
		if(xls.LoadSheet(ArxRleUiTdmNetPlan::m_itemNetPlanData.strXlsSheetName));
		{
			m_itemNetPlanWorkList.clear();
			for(int i=ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkBeginRow; i<=ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkEndRow; i++)
			{
				CString name = xls.GetCellString(i,ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkNameCol1)+xls.GetCellString(i,ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkNameCol2);
				int code1 = xls.GetCellDouble(i,ArxRleUiTdmNetPlan::m_itemNetPlanData.nNodeBeginCol);
				int code2 = xls.GetCellDouble(i,ArxRleUiTdmNetPlan::m_itemNetPlanData.nNodeEndCol);
				CTime t1 =  xls.GetCellDateTime(i, ArxRleUiTdmNetPlan::m_itemNetPlanData.nTimeBeginCol);
				CTime t2 =  xls.GetCellDateTime(i, ArxRleUiTdmNetPlan::m_itemNetPlanData.nTimeEndCol);

				ArxRleNetPlanWorkItem work(name, code1, code2, t1, t2, ArxStandard);

				m_itemNetPlanWorkList.push_back(work);
			}
		}
		xls.Save();
		xls.CloseExcel();
	}
	xls.ReleaseExcel();

	ArxRleUiPrDoubleDef prRowGap(_T("RowGap "), NULL,ArxRleUiPrDouble::kAny, 8);
	if(prRowGap.go() != ArxRleUiPrBase::kOk) return;

	ArxRleUiPrPoint prPt(_T("请输入插入点"), NULL);
	if(prPt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleNetPlanWorkStyle::getStandardStyle();
	ArxRleNetPlanWorkStyle::getGeneralStyle(true,false);
	ArxRleNetPlanWorkStyle::getKeyStyle();
	ArxRleNetPlanWorkStyle::getVirtualStyle();
	ArxRleNetPlanWorkStyle::getFreeStyle();

	CPt3d ptTL(prPt.value());
	CTime tBase = ArxRleUiTdmNetPlan::m_itemNetPlanData.tBeginDay;
	int row = 0;
	for(int i=0; i<m_itemNetPlanWorkList.size(); i++)
	{
		ArxRleNetPlanWork* work = new ArxRleNetPlanWork;
		switch(m_itemNetPlanWorkList[i].work_type)
		{
		case ArxStandard:
			work->setWorkStyle("Standard");
			break;
		case ArxGeneral:
			work->setWorkStyle("General");
			break;
		case ArxKey:
			work->setWorkStyle("Key");
			break;
		case ArxVirtual:
			work->setWorkStyle("Virtual");
			break;
		case ArxFree:
			work->setWorkStyle("Free");
			break;
		}

		AcDbObjectId styleId = ArxRleNetPlanWorkStyle::getWorkStyle(work->getWorkStyle());
		ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
		Acad::ErrorStatus es = acdbOpenObject(style, styleId, AcDb::kForRead);
		if(es != Acad::eOk) {
			ArxRleUtils::rxErrorMsg(es);
			delete style;
			return;
		}
		int gap = style->lineGap();
		style->close();

		CTime t = m_itemNetPlanWorkList[i].time_begin;
		int ds1 = (t-tBase).GetDays();
		int ds2 =m_itemNetPlanWorkList[i].time_days;
		CPt3d pt1,pt2;
		if(m_itemNetPlanWorkList[i].code_begin == 0)
		{
			pt1 = CPt3d(ptTL[X]+ds1*gap,ptTL[Y]-row*prRowGap.value());
			pt2 = CPt3d(pt1[X]+ds2*gap,pt1[Y]);
			work->setWorkStyle("General");
		}
		else
		{
			row++;
			pt1 = CPt3d(ptTL[X]+ds1*gap,ptTL[Y]-row*prRowGap.value());
			pt2 = CPt3d(pt1[X]+ds2*gap,pt1[Y]);
			work->setWorkStyle("Standard");
		}

		work->setPoint(pt1,pt2);
		work->setLabel(ToString(m_itemNetPlanWorkList[i].code_begin,0),ToString(m_itemNetPlanWorkList[i].code_end,0),m_itemNetPlanWorkList[i].work_name,ArxRleString());
		AddEntity(work);
	}
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::batchProc
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::batchProc()
{
	CXTPExcelUtil xls;
	xls.InitExcel();
	if(FileExist(ArxRleUiTdmNetPlan::m_itemNetPlanData.strXlsFilePath))
	{
		xls.OpenExcel(ArxRleUiTdmNetPlan::m_itemNetPlanData.strXlsFilePath);
		if(xls.LoadSheet(ArxRleUiTdmNetPlan::m_itemNetPlanData.strXlsSheetName));
		{
			m_itemNetPlanWorkList.clear();
			for(int i=ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkBeginRow; i<=ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkEndRow; i++)
			{
				CString name = xls.GetCellString(i,ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkNameCol1)+xls.GetCellString(i,ArxRleUiTdmNetPlan::m_itemNetPlanData.nWorkNameCol2);
				double s1 = xls.GetCellDouble(i,ArxRleUiTdmNetPlan::m_itemNetPlanData.nNodeBeginCol);
				double s2 = xls.GetCellDouble(i,ArxRleUiTdmNetPlan::m_itemNetPlanData.nNodeEndCol);
				CTime t1 =  xls.GetCellDateTime(i, ArxRleUiTdmNetPlan::m_itemNetPlanData.nTimeBeginCol);
				CTime t2 =  xls.GetCellDateTime(i, ArxRleUiTdmNetPlan::m_itemNetPlanData.nTimeEndCol);

				ArxRleNetPlanWorkItem work(name, s1, s2, t1, t2);

				m_itemNetPlanWorkList.push_back(work);
			}
		}
		xls.Save();
		xls.CloseExcel();
	}
	xls.ReleaseExcel();

	ArxRleUiPrPoint prPt(_T("请输入插入点"), NULL);
	if(prPt.go() != ArxRleUiPrBase::kOk)
		return;

	double sg = ArxRleUiTdmNetPlan::m_itemNetPlanData.fStatGap;
	int dg = ArxRleUiTdmNetPlan::m_itemNetPlanData.nDayGap;

	CTime t = ArxRleUiTdmNetPlan::m_itemNetPlanData.tBeginDay;
	double s = ArxRleUiTdmNetPlan::m_itemNetPlanData.fBeginStat;

	CPt3d ptTL(prPt.value());
	ptTL.y -= 10;
	CPt3d ptBL(ptTL);
	ptBL.y -= (((ArxRleUiTdmNetPlan::m_itemNetPlanData.tEndDay-ArxRleUiTdmNetPlan::m_itemNetPlanData.tBeginDay).GetDays()/dg)*dy+dy);
	int a=14,b=34,c=2;
	ptBL = CPt3d(ptBL.x+dx*3, ptBL.y-a-b-c);

	for(int i=0; i<m_itemNetPlanWorkList.size(); i++)
	{
		CString ss = m_itemNetPlanWorkList[i].work_name;
		double s1 = m_itemNetPlanWorkList[i].code_begin;
		double s2 = m_itemNetPlanWorkList[i].code_end;
		CTime t1 = m_itemNetPlanWorkList[i].time_begin;
		CTime t2 = m_itemNetPlanWorkList[i].time_end;

		int dt1 = (t1-t).GetDays();
		int dt2 = (t2-t).GetDays()+1;
		double ds1 = s1-s;
		double ds2 = s2-s;

		CLine oLine;
		CPt3d pt1(ptBL.x+ds1*dx*3/sg,ptBL.y+dt1*dx/dg);
		CPt3d pt2(ptBL.x+ds2*dx*3/sg,ptBL.y+dt2*dx/dg);
		oLine.SetPoint(pt1,pt2);
		oLine.addToSpaceAndClose();

		double a = pt1.GetAngle(pt2);
		pt1 = pt1.GetLineEnd(3,a+PI/2);
		CText oText;
		oText.SetAlignmentMode(ArxLeftMiddle);
		oText.SetTextHeight(2.5);
		oText.SetWidthFactor(0.7);
		oText.SetRotation(a);
		oText.SetText(ss);
		oText.SetPosition(pt1);
		oText.addToSpaceAndClose();
	}
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::reSetProc
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::reSetProc()
{
	ArxRleSelSet ss;
	AcDbObjectId tsId;
	if(ss.userSelect(_T("Select NetPlan Work Ref"),NULL) == ArxRleSelSet::kSelected)
	{    // have user select entities from DWG
		AcDbObjectIdArray objList;
		ss.asArray(objList);
		if(!objList.isEmpty())
		{
			AcDbEntity* ent;
			Acad::ErrorStatus es;

			int len = objList.length();
			for(int i=0; i<len; i++)
			{
				es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForWrite, true);
				if(es == Acad::eOk)
				{
					if(ent->isKindOf(AcDbPolyline::desc()))
					{
						AcGePoint2d pt;
						((AcDbPolyline*)ent)->getPointAt(0,pt);
						CPt3d pt1 = pt;
						((AcDbPolyline*)ent)->getPointAt(1,pt);
						CPt3d pt2 = pt;
						((AcDbPolyline*)ent)->setPointAt(0,CPt3d(pt1.x,pt2.y));
						((AcDbPolyline*)ent)->setPointAt(1,CPt3d(pt2.x,pt1.y));
					}

					if(ent->isKindOf(AcDbLine::desc()))
					{
						AcGePoint2d pt;
						CPt3d pt1 = ((AcDbLine*)ent)->startPoint();
						CPt3d pt2 = ((AcDbLine*)ent)->endPoint();
						((AcDbLine*)ent)->setStartPoint(CPt3d(pt1.x,pt2.y));
						((AcDbLine*)ent)->setEndPoint(CPt3d(pt2.x,pt1.y));
					}

					ent->close();
				}
			}
		}
	}
}


/****************************************************************************
**
**  ArxRleCmdNetPlanWork::reNumber
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::reNumber()
{
	ArxRleSelSet ss;
	AcDbObjectId tsId;
	AcDbEntity* ent;
	if(ss.userSelect() == ArxRleSelSet::kSelected)
	{
		AcDbObjectIdArray objList;
		vector<ArxRleNetPlanNodeItem> vecNode;
		ss.asArray(objList);
		if(!objList.isEmpty())
		{
			int len = objList.length();
			for(int i=0; i<len; i++)
			{
				Acad::ErrorStatus es = acdbOpenObject(ent, objList[i], AcDb::kForRead);
				if(es == Acad::eOk)
				{
					if(ent->isKindOf(ArxRleNetPlanWork::desc()))
					{
						ArxRleNetPlanWorkStyle* style;
						es = acdbOpenObject(style, ((ArxRleNetPlanWork*)ent)->getWorkStyleId(), AcDb::kForRead);
						ent->close();

						if(es == Acad::eOk)
						{
							if(style->drawLabelBegin())
								vecNode.push_back(ArxRleNetPlanNodeItem(objList[i],1));

							if(style->drawLabelEnd())
								vecNode.push_back(ArxRleNetPlanNodeItem(objList[i],2));

							style->close();
						}
					}
				}
			}
		}
		sort(vecNode.begin(),vecNode.end());

		for(int i=0; i<vecNode.size(); i++)
		{
			ArxRleNetPlanNodeItem& node = vecNode[i];
			Acad::ErrorStatus es = acdbOpenObject(ent, node.id, AcDb::kForWrite);
			if(es == Acad::eOk)
			{
				if(ent->isKindOf(ArxRleNetPlanWork::desc()))
				{
					if(node.b == 1)
						((ArxRleNetPlanWork*)ent)->setLabelBegin(ToString(i,0));

					if(node.b == 2)
						((ArxRleNetPlanWork*)ent)->setLabelEnd(ToString(i,0));
				}

				ent->close();
			}
		}
	}
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::bindWork
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::bindWork()
{
	ArxRleUiPrEntity prEnt(_T("Select NetPlan Work Ref"), NULL);
	prEnt.addAllowedClass(ArxRleNetPlanWork::desc());
	prEnt.setFilterLockedLayers(true);

	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleNetPlanWork* workRef = new ArxRleNetPlanWork;
	Acad::ErrorStatus es = acdbOpenObject(workRef, prEnt.objectId(), AcDb::kForWrite);
	if(es == Acad::eOk)
	{
		ArxRleUiPrEntity prRef(_T("Select Bind NetPlan Work Ref"), NULL);
		prRef.addAllowedClass(ArxRleNetPlanWork::desc());
		prRef.setFilterLockedLayers(true);

		if(prRef.go() != ArxRleUiPrBase::kOk)
		{
			workRef->close();
			return;
		}

		workRef->setBindWorkRefId(prRef.objectId());
		workRef->close();
	}
	else
	{
		ArxRleUtils::rxErrorMsg(es);
		delete workRef;
	}
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::styleWork
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::flushStyle()
{
	ArxRleUiPrEntity prEnt(_T("Select NetPlan Work Ref"), NULL);
	prEnt.addAllowedClass(ArxRleNetPlanWork::desc());
	prEnt.setFilterLockedLayers(true);

	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleNetPlanWork* workRef = new ArxRleNetPlanWork;
	Acad::ErrorStatus es = acdbOpenObject(workRef, prEnt.objectId(), AcDb::kForRead);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete workRef;
		return;
	}

	ArxRleSelSet ss;
	if(ss.userSelect(_T("Select NetPlan Works Modify"),NULL) == ArxRleSelSet::kSelected)
	{    // have user select entities from DWG
		AcDbObjectIdArray objList;
		ss.asArray(objList);
		if(!objList.isEmpty())
		{
			int len = objList.length();
			for(int i=0; i<len; i++)
			{
				ArxRleNetPlanWork* work = new ArxRleNetPlanWork;
				es = acdbOpenObject(work, objList[i], AcDb::kForWrite);
				if(es != Acad::eOk) {
					ArxRleUtils::rxErrorMsg(es);
					delete work;
					workRef->close();
					return;
				}
				else
				{
					work->setWorkStyle(workRef->getWorkStyle());
					work->close();
				}
			}
		}
	}

	workRef->close();
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::cmdLineMain
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::cmdLineWork()
{
		// ArxRleKeyword array allows us to use Global and Local keywords (i.e., English
		// and another language) without the need to worry about how it was picked.  In
		// this case, we haven't translated anything, so the keywords are the same.
		// see ArxRleKeywordArray for more details.
	ArxRleKeywordArray kwords(ArxRleApp::getApp()->dllInstance());
    kwords.append(_T("Add"),    _T("Add"));
    kwords.append(_T("Modify"), _T("Modify"));
    kwords.append(_T("Styles"), _T("Styles"));

    CString optionsStr, kwordStr;
    kwords.makeOptionsList(optionsStr);
    kwords.makeKeywordList(kwordStr);

	CString promptStr;
    promptStr.Format(_T("NetPlan Work options %s"), optionsStr);

    ArxRleUiPrKeyWord prCmd(promptStr, kwordStr);
    if(prCmd.go() != ArxRleUiPrBase::kOk)
        return;

    int keywordIndex;
    if(kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
        ASSERT(0);
        return;
    }

    if(keywordIndex == 0)
        workAdd();
    else if(keywordIndex == 1)
        cmdLineModify();
    else if(keywordIndex == 2)
        cmdLineStyle();
    else {
        ASSERT(0);
        return;
    }
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::add
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::workAdd()
{
    AcDbObjectId styleId;
    if(!ArxRleNetPlanWorkStyle::getWorkStyle(styleId))
        return;

	ArxRleUiPrString prLabelBegin(_T("LabelBegin"), true);
	ArxRleUiPrString prLabelEnd(_T("LabelEnd"), true);
	ArxRleUiPrString prLabelUp(_T("LabelUp"), true);

	if((prLabelBegin.go() != ArxRleUiPrBase::kOk)||
		(prLabelEnd.go() != ArxRleUiPrBase::kOk)||
		(prLabelUp.go() != ArxRleUiPrBase::kOk))
		return;

	ArxRleUiPrPoint prPt(_T("BeginPt"), NULL);
	if(prPt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleJigNetPlanWork *pJig = new ArxRleJigNetPlanWork();

	ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
	Acad::ErrorStatus es = acdbOpenObject(style, styleId, AcDb::kForRead);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete style;
		return;
	}
	pJig->setPoint(prPt.value(), style->name());
	style->close();

	pJig->setLabel(prLabelBegin.value(), prLabelEnd.value(), prLabelUp.value(), ArxRleString());
	pJig->dragIt();
	delete pJig;
}


/****************************************************************************
**
**  ArxRleCmdNetPlanWork::cmdLineModify
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::cmdLineModify()
{
	ArxRleKeywordArray kwords(ArxRleApp::getApp()->dllInstance());
	kwords.append(_T("Info"),  _T("Info"));
	kwords.append(_T("Nodes"),  _T("Nodes"));
	kwords.append(_T("Days"),  _T("Days"));
	kwords.append(_T("Name"),  _T("Name"));
	kwords.append(_T("Style"), _T("Style"));

	CString optionsStr, kwordStr;
	kwords.makeOptionsList(optionsStr);
	kwords.makeKeywordList(kwordStr);

	CString promptStr;
	promptStr.Format(_T("NetPlan Work Info options %s"), optionsStr);

	ArxRleUiPrKeyWord prCmd(promptStr, kwordStr);
	if(prCmd.go() != ArxRleUiPrBase::kOk)
		return;

	int keywordIndex;
	if(kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
		ASSERT(0);
		return;
	}

	if(keywordIndex == 0)
		modifyWorkInfo();
	else if(keywordIndex == 1)
		modifyWorkNodes();
	else if(keywordIndex == 2)
		modifyWorkDays();
	else if(keywordIndex == 3)
		modifyWorkName();
	else if(keywordIndex == 4)
		modifyWorkStyle();
	else {
		ASSERT(0);
		return;
	}
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::modify
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::modifyWorkInfo()
{
	ArxRleUiPrEntity prEnt(_T("Select NetPlan Work to modify"), NULL);
	prEnt.addAllowedClass(ArxRleNetPlanWork::desc());
	prEnt.setFilterLockedLayers(true);

	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleNetPlanWork* work = new ArxRleNetPlanWork;
	Acad::ErrorStatus es = acdbOpenObject(work, prEnt.objectId(), AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete work;
		return;
	}
		// get current values and close (they might pick our object again!)
    AcDbObjectId styleId = work->getWorkStyleId();
	
		// get the work style they want
    if(!ArxRleNetPlanWorkStyle::getWorkStyle(styleId))
        return;

	ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
	es = acdbOpenObject(style, styleId, AcDb::kForRead);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete style;
		return;
	}
	work->setWorkStyle(style->name());
	style->close();

	ArxRleUiPrStringDef prLabelBegin(_T("LabelBegin "), work->getLabelBegin(), true);
	if(prLabelBegin.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrStringDef prLabelEnd(_T("LabelEnd "), work->getLabelEnd(), true);
	if(prLabelEnd.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrStringDef prLabelUp(_T("LabelUp "), work->getLabelUp(), true);
	if(prLabelUp.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrStringDef prLabelDown(_T("LabelDown "), work->getLabelDown(), true);
	if(prLabelDown.go() != ArxRleUiPrBase::kOk)
		return;

	work->setLabel(prLabelBegin.value(),prLabelEnd.value(),prLabelUp.value(),prLabelDown.value());
	work->close();
}

void ArxRleCmdNetPlanWork::modifyWorkNodes()
{
	while(1)
	{
		ArxRleUiPrEntity prEnt(_T("Select NetPlan Work to modify"), NULL);
		prEnt.addAllowedClass(ArxRleNetPlanWork::desc());
		prEnt.setFilterLockedLayers(true);

		if(prEnt.go() != ArxRleUiPrBase::kOk)
			return;

		ArxRleNetPlanWork* work = new ArxRleNetPlanWork;
		Acad::ErrorStatus es = acdbOpenObject(work, prEnt.objectId(), AcDb::kForWrite);
		if(es != Acad::eOk) {
			ArxRleUtils::rxErrorMsg(es);
			delete work;
			return;
		}

		ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
		es = acdbOpenObject(style, work->getWorkStyleId(), AcDb::kForRead);
		if(es != Acad::eOk) {
			ArxRleUtils::rxErrorMsg(es);
			delete style;
			work->close();
			return;
		}

		ArxRleUiPrStringDef prWorkNodeBegin(_T("WorkNodeBegin "), work->getLabelBegin(), true);
		if(style->drawLabelBegin())
		{
			if(prWorkNodeBegin.go() != ArxRleUiPrBase::kOk)
			{
				style->close();
				work->close();
				return;
			}
		}

		ArxRleUiPrStringDef prWorkNodeEnd(_T("WorkNodeEnd "), work->getLabelEnd(), true);
		if(style->drawLabelEnd())
		{
			if(prWorkNodeEnd.go() != ArxRleUiPrBase::kOk)
			{
				style->close();
				work->close();
				return;
			}
		}

		style->close();
		work->setNode(prWorkNodeBegin.value(),prWorkNodeEnd.value());
		work->close();
	}
}

void ArxRleCmdNetPlanWork::modifyWorkDays()
{
	ArxRleUiPrEntity prEnt(_T("Select NetPlan Work to modify"), NULL);
	prEnt.addAllowedClass(ArxRleNetPlanWork::desc());
	prEnt.setFilterLockedLayers(true);

	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleNetPlanWork* work = new ArxRleNetPlanWork;
	Acad::ErrorStatus es = acdbOpenObject(work, prEnt.objectId(), AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete work;
		return;
	}

	ArxRleUiPrStringDef prWorkDays(_T("WorkDays "), work->getLabelDown(), true);
	if(prWorkDays.go() != ArxRleUiPrBase::kOk)
		return;

	work->setLabelDown(prWorkDays.value());
	work->close();
}

void ArxRleCmdNetPlanWork::modifyWorkName()
{
	ArxRleUiPrEntity prEnt(_T("Select NetPlan Work to modify"), NULL);
	prEnt.addAllowedClass(ArxRleNetPlanWork::desc());
	prEnt.setFilterLockedLayers(true);

	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleNetPlanWork* work = new ArxRleNetPlanWork;
	Acad::ErrorStatus es = acdbOpenObject(work, prEnt.objectId(), AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete work;
		return;
	}

	ArxRleUiPrStringDef prWorkName(_T("WorkName "), work->getLabelUp(), true);
	if(prWorkName.go() != ArxRleUiPrBase::kOk)
		return;

	work->setLabelUp(prWorkName.value());
	work->close();
}

void ArxRleCmdNetPlanWork::modifyWorkStyle()
{
	ArxRleUiPrEntity prEnt(_T("Select NetPlan Work to modify"), NULL);
	prEnt.addAllowedClass(ArxRleNetPlanWork::desc());
	prEnt.setFilterLockedLayers(true);

	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleNetPlanWork* work = new ArxRleNetPlanWork;
	Acad::ErrorStatus es = acdbOpenObject(work, prEnt.objectId(), AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete work;
		return;
	}

	ArxRleUiPrStringDef prWorkStyle(_T("WorkStyle "), work->getWorkStyle(), true);
	if(prWorkStyle.go() != ArxRleUiPrBase::kOk)
		return;

	AcDbObjectId styleId;

	// get the work style they want to modify
	if(!ArxRleNetPlanWorkStyle::getWorkStyle(styleId))
		return;

	ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
	es = acdbOpenObject(style, styleId, AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete style;
		work->close();
		return;
	}

	work->setWorkStyle(style->name());
	style->close();
	work->close();
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::styles
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::cmdLineStyle()
{
	ArxRleKeywordArray kwords(ArxRleApp::getApp()->dllInstance());
    kwords.append(_T("Add"),    _T("Add"));
    kwords.append(_T("Modify"), _T("Modify"));
	kwords.append(_T("Copy"),   _T("Copy"));
	kwords.append(_T("Delete"), _T("Delete"));
	kwords.append(_T("Common"), _T("Common"));

    CString optionsStr, kwordStr;
    kwords.makeOptionsList(optionsStr);
    kwords.makeKeywordList(kwordStr);

	CString promptStr;
    promptStr.Format(_T("NetPlan Work Style options %s"), optionsStr);

    ArxRleUiPrKeyWord prCmd(promptStr, kwordStr);
    if(prCmd.go() != ArxRleUiPrBase::kOk)
        return;

    int keywordIndex;
    if(kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
        ASSERT(0);
        return;
    }

    if(keywordIndex == 0)
        styleAdd();
    else if(keywordIndex == 1)
        styleModify();
	else if(keywordIndex == 2)
		styleCopy();
	else if(keywordIndex == 3)
		styleDelete();
	else if(keywordIndex == 4)
		styleCommon();
    else {
        ASSERT(0);
        return;
    }
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::styleAdd
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::styleAdd()
{
    ArxRleUiPrString prName(_T("WorkStyleName"), false);
    ArxRleUiPrString prLayer(_T("LayerName"), true);
	ArxRleUiPrString prTextStyle(_T("TextStyleName"), true);
	ArxRleUiPrString prLineType(_T("LineTypeName"), true);
	ArxRleUiPrInt prColorIndex(_T("ColorIndex"), NULL,ArxRleUiPrInt::kAny);
	ArxRleUiPrDouble prLineScale(_T("LineScalse"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prRadiusBegin(_T("RadiusBegin"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prRadiusEnd(_T("RadiusEnd"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prLenArrow(_T("LenArrow"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prSizeLabel(_T("SizeLabel"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prSizeNode(_T("SizeNode"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prDayGap(_T("DayGap"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prLineGap(_T("LineGap"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrInt prDrawLabelBegin(_T("DrawLabelBegin"), NULL,ArxRleUiPrInt::kAny);
	ArxRleUiPrInt prDrawLabelEnd(_T("DrawLabelEnd"), NULL,ArxRleUiPrInt::kAny);
	ArxRleUiPrInt prDrawLabelUp(_T("DrawLabelUp"), NULL,ArxRleUiPrInt::kAny);
	ArxRleUiPrInt prDrawLabelDown(_T("DrawLabelDown"), NULL,ArxRleUiPrInt::kAny);

    if((prName.go() != ArxRleUiPrBase::kOk) ||
        (prLayer.go() != ArxRleUiPrBase::kOk)||
		(prTextStyle.go() != ArxRleUiPrBase::kOk)||
		(prLineType.go() != ArxRleUiPrBase::kOk)||
		(prColorIndex.go() != ArxRleUiPrBase::kOk)||
		(prLineScale.go() != ArxRleUiPrBase::kOk)||
		(prRadiusBegin.go() != ArxRleUiPrBase::kOk)||
		(prRadiusEnd.go() != ArxRleUiPrBase::kOk)||
		(prLenArrow.go() != ArxRleUiPrBase::kOk)||
		(prSizeLabel.go() != ArxRleUiPrBase::kOk)||
		(prSizeNode.go() != ArxRleUiPrBase::kOk)||
		(prDayGap.go() != ArxRleUiPrBase::kOk)||
		(prLineGap.go() != ArxRleUiPrBase::kOk)||
		(prDrawLabelBegin.go() != ArxRleUiPrBase::kOk)||
		(prDrawLabelEnd.go() != ArxRleUiPrBase::kOk)||
		(prDrawLabelUp.go() != ArxRleUiPrBase::kOk)||
		(prDrawLabelDown.go() != ArxRleUiPrBase::kOk))
        return;

    if(acdbSNValid(prName.value(), false) != RTNORM) {
        acedAlert(_T("Invalid symbol name!"));
        return;
    }

    AcDbDictionary* dict = ArxRleUtils::openDictionaryForWrite(ArxRleNetPlanWorkStyle::dictName(), true, ARXRLEDB);
    if(dict) {
        Acad::ErrorStatus es;

        if(dict->has(prName.value()))
            ArxRleUtils::stopAlertBox(_T("Sorry, there is already an entry with that name."));
        else {
            ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
			style->setName(prName.value());
            style->setLayer(prLayer.value());
			style->setTextStyle(prTextStyle.value());
			style->setLineType(prLineType.value());
			style->setColorIndex(prColorIndex.value());
			style->setLineScale(prLineScale.value());
			style->setRadiusBegin(prRadiusBegin.value());
			style->setRadiusEnd(prRadiusEnd.value());
			style->setLenArrow(prLenArrow.value());
			style->setSizeLabel(prSizeLabel.value());
			style->setSizeNode(prSizeNode.value());
			style->setDayGap(prDayGap.value());
			style->setLineGap(prLineGap.value());
			style->setDrawLabelBegin(prDrawLabelBegin.value());
			style->setDrawLabelEnd(prDrawLabelEnd.value());
			style->setDrawLabelUp(prDrawLabelUp.value());
			style->setDrawLabelDown(prDrawLabelDown.value());

            AcDbObjectId objId;
            es = dict->setAt(prName.value(), style, objId);
            if(es == Acad::eOk) {
                ArxRleUtils::alertBox(_T("NetPlan Work Style successfully!"));
                style->close();
            }
            else {
                ArxRleUtils::rxErrorAlert(es);
                delete style;
            }
        }
        dict->close();
    }
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::styleModify
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::styleModify()
{
	AcDbObjectId styleId;

		// get the work style they want to modify
    if(!ArxRleNetPlanWorkStyle::getWorkStyle(styleId))
        return;

	ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
	Acad::ErrorStatus es = acdbOpenObject(style, styleId, AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete style;
		return;
	}

	ArxRleUiPrStringDef prName(_T("WorkStyleName "), style->name(), true);
	if(prName.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrStringDef prLayer(_T("LayerName "), style->layer(), true);
	if(prLayer.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrStringDef prTextStyle(_T("TextStyleName "), style->textStyle(), true);
	if(prTextStyle.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrStringDef prLineType(_T("LineTypeName "), style->lineType(), true);
	if(prLineType.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrIntDef prColorIndex(_T("ColorIndex "), NULL,ArxRleUiPrInt::kAny, style->colorIndex());
	if(prColorIndex.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrDoubleDef prLineScale(_T("LineScale "), NULL,ArxRleUiPrDouble::kAny, style->lineScale());
	if(prLineScale.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrDoubleDef prRadiusBegin(_T("RadiusBegin "), NULL,ArxRleUiPrDouble::kAny, style->radiusBegin());
	if(prRadiusBegin.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrDoubleDef prRadiusEnd(_T("RadiusEnd "), NULL,ArxRleUiPrDouble::kAny, style->radiusEnd());
	if(prRadiusEnd.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrDoubleDef prLenArrow(_T("LenArrow "), NULL,ArxRleUiPrDouble::kAny, style->lenArrow());
	if(prLenArrow.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrDoubleDef prSizeLabel(_T("SizeLabel "), NULL,ArxRleUiPrDouble::kAny, style->sizeLabel());
	if(prSizeLabel.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrDoubleDef prSizeNode(_T("SizeNode "), NULL,ArxRleUiPrDouble::kAny, style->sizeNode());
	if(prSizeNode.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrDoubleDef prDayGap(_T("DayGap "), NULL,ArxRleUiPrDouble::kAny, style->dayGap());
	if(prDayGap.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrDoubleDef prLineGap(_T("LineGap "), NULL,ArxRleUiPrDouble::kAny, style->lineGap());
	if(prLineGap.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrIntDef prDrawLabelBegin(_T("DrawLabelBegin "), NULL,ArxRleUiPrInt::kAny, style->drawLabelBegin());
	if(prDrawLabelBegin.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrIntDef prDrawLabelEnd(_T("DrawLabelEnd "), NULL,ArxRleUiPrInt::kAny, style->drawLabelEnd());
	if(prDrawLabelEnd.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrIntDef prDrawLabelUp(_T("DrawLabelUp "), NULL,ArxRleUiPrInt::kAny, style->drawLabelUp());
	if(prDrawLabelUp.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	ArxRleUiPrIntDef prDrawLabelDown(_T("DrawLabelDown "), NULL,ArxRleUiPrInt::kAny, style->drawLabelDown());
	if(prDrawLabelDown.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	AcDbDictionary* dict = ArxRleUtils::openDictionaryForWrite(ArxRleNetPlanWorkStyle::dictName(), true, ARXRLEDB);
	if(dict) {
		Acad::ErrorStatus es;

		if(dict->has(styleId)) {
			style->setName(prName.value());
			style->setLayer(prLayer.value());
			style->setTextStyle(prTextStyle.value());
			style->setLineType(prLineType.value());
			style->setColorIndex(prColorIndex.value());
			style->setLineScale(prLineScale.value());
			style->setRadiusBegin(prRadiusBegin.value());
			style->setRadiusEnd(prRadiusEnd.value());
			style->setLenArrow(prLenArrow.value());
			style->setSizeLabel(prSizeLabel.value());
			style->setSizeNode(prSizeNode.value());
			style->setDayGap(prDayGap.value());
			style->setLineGap(prLineGap.value());
			style->setDrawLabelBegin(prDrawLabelBegin.value());
			style->setDrawLabelEnd(prDrawLabelEnd.value());
			style->setDrawLabelUp(prDrawLabelUp.value());
			style->setDrawLabelDown(prDrawLabelDown.value());

			AcDbObjectId objId;
			es = dict->setAt(prName.value(), style, objId);
			if(es == Acad::eOk) {
				ArxRleUtils::alertBox(_T("Modify NetPlan Work Style successfully!"));
				style->close();
			}
			else {
				ArxRleUtils::rxErrorAlert(es);
				delete style;
			}
		}
		else {
			ArxRleUtils::stopAlertBox(_T("Sorry, there is no this style in Dictionary."));
			style->close();
		}
		dict->close();
	}
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::styleCopy
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::styleCopy()
{
	AcDbObjectId styleId;

	// get the work style they want to modify
	if(!ArxRleNetPlanWorkStyle::getWorkStyle(styleId))
		return;

	ArxRleNetPlanWorkStyle* style = new ArxRleNetPlanWorkStyle;
	Acad::ErrorStatus es = acdbOpenObject(style, styleId, AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete style;
		return;
	}

	ArxRleUiPrStringDef prName(_T("WorkStyleName "), style->name(), true);
	if(prName.go() != ArxRleUiPrBase::kOk) {
		style->close();
		return;
	}

	if(acdbSNValid(prName.value(), false) != RTNORM) {
		acedAlert(_T("Invalid symbol name!"));
		return;
	}

	AcDbDictionary* dict = ArxRleUtils::openDictionaryForWrite(ArxRleNetPlanWorkStyle::dictName(), true, ARXRLEDB);
	if(dict) {
		Acad::ErrorStatus es;

		if(dict->has(prName.value()))
			ArxRleUtils::stopAlertBox(_T("Sorry, there is already an entry with that name."));
		else {
			ArxRleNetPlanWorkStyle* styleNew = new ArxRleNetPlanWorkStyle;
			styleNew->setName(prName.value());
			styleNew->setLayer(style->layer());
			styleNew->setTextStyle(style->textStyle());
			styleNew->setLineType(style->lineType());
			styleNew->setColorIndex(style->colorIndex());
			styleNew->setLineScale(style->lineScale());
			styleNew->setRadiusBegin(style->radiusBegin());
			styleNew->setRadiusEnd(style->radiusEnd());
			styleNew->setLenArrow(style->lenArrow());
			styleNew->setSizeLabel(style->sizeLabel());
			styleNew->setSizeNode(style->sizeNode());
			styleNew->setDayGap(style->dayGap());
			styleNew->setLineGap(style->lineGap());
			styleNew->setDrawLabelBegin(style->drawLabelBegin());
			styleNew->setDrawLabelEnd(style->drawLabelEnd());
			styleNew->setDrawLabelUp(style->drawLabelUp());
			styleNew->setDrawLabelDown(style->drawLabelDown());

			AcDbObjectId objId;
			es = dict->setAt(prName.value(), styleNew, objId);
			if(es == Acad::eOk) {
				ArxRleUtils::alertBox(_T("Copy NetPlan Work Style successfully!"));
				styleNew->close();
			}
			else {
				ArxRleUtils::rxErrorAlert(es);
				delete styleNew;
			}
		}
		dict->close();
	}

	style->close();
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::styleDelete
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::styleDelete()
{
	AcDbObjectId styleId;

	// get the work style they want to modify
	if(!ArxRleNetPlanWorkStyle::getWorkStyle(styleId))
		return;

	AcDbDictionary* dict = ArxRleUtils::openDictionaryForWrite(ArxRleNetPlanWorkStyle::dictName(), true, ARXRLEDB);
	if(dict) {
		if(dict->has(styleId))
		{
			dict->remove(styleId);
			ArxRleUtils::alertBox(_T("Delete NetPlan Work Style successfully!"));
		}
		else
			ArxRleUtils::stopAlertBox(_T("Sorry, there is already an entry with that name."));
		dict->close();
	}
}

/****************************************************************************
**
**  ArxRleCmdNetPlanWork::styleCommon
**
**  **000
**
*************************************/

void ArxRleCmdNetPlanWork::styleCommon()
{
	AcDbObjectId styleId;

	AcDbDictionary *dict;
	dict = ArxRleUtils::openDictionaryForRead(ArxRleNetPlanWorkStyle::dictName(), ARXRLEDB);
	if(!dict) return;

	ArxRleApply<Dictionary> apply = ArxRleApply<Dictionary>( dict, AcDb::kForWrite );
	Dictionary::Iterator* iter;
	apply.createIterator( iter );
	if (NULL == iter)
		return;

	ArxRleUiPrString prTextStyle(_T("TextStyleName"), true);
	ArxRleUiPrDouble prRadiusBegin(_T("RadiusBegin"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prRadiusEnd(_T("RadiusEnd"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prLenArrow(_T("LenArrow"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prSizeLabel(_T("SizeLabel"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prSizeNode(_T("SizeNode"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prDayGap(_T("DayGap"), NULL,ArxRleUiPrDouble::kAny);
	ArxRleUiPrDouble prLineGap(_T("LineGap"), NULL,ArxRleUiPrDouble::kAny);

	if((prTextStyle.go() != ArxRleUiPrBase::kOk)||
		(prRadiusBegin.go() != ArxRleUiPrBase::kOk)||
		(prRadiusEnd.go() != ArxRleUiPrBase::kOk)||
		(prLenArrow.go() != ArxRleUiPrBase::kOk)||
		(prSizeLabel.go() != ArxRleUiPrBase::kOk)||
		(prSizeNode.go() != ArxRleUiPrBase::kOk)||
		(prDayGap.go() != ArxRleUiPrBase::kOk)||
		(prLineGap.go() != ArxRleUiPrBase::kOk))
		return;

	for ( ; !iter->done(); apply.stepIterator( iter ))
	{
		Dictionary::Element* elem = apply.getElement( iter );
		if (NULL != elem)
		{
			ArxRleString sName = ((ArxRleNetPlanWorkStyle*)elem)->name();

			((ArxRleNetPlanWorkStyle*)elem)->setTextStyle(prTextStyle.value());
			((ArxRleNetPlanWorkStyle*)elem)->setRadiusBegin(prRadiusBegin.value());
			((ArxRleNetPlanWorkStyle*)elem)->setRadiusEnd(prRadiusEnd.value());
			((ArxRleNetPlanWorkStyle*)elem)->setLenArrow(prLenArrow.value());
			((ArxRleNetPlanWorkStyle*)elem)->setSizeLabel(prSizeLabel.value());
			((ArxRleNetPlanWorkStyle*)elem)->setSizeNode(prSizeNode.value());
			((ArxRleNetPlanWorkStyle*)elem)->setDayGap(prDayGap.value());
			((ArxRleNetPlanWorkStyle*)elem)->setLineGap(prLineGap.value());

			elem->close();
		}
	}
	delete iter;
	dict->close();

	ArxRleUtils::alertBox(_T("Modify NetPlan Work Style Common successfully!"));
}