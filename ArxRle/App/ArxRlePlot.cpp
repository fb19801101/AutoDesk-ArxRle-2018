//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AcPlPlotEngine.h"
#include "AcPlplotFactory.h"
#include "AcPlplotInfo.h"
#include "AcPlPlotInfoValidator.h"
#include "AcPlPlotProgress.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRlePlot.h"

/****************************************************************************
**
**  ArxRlePlot::ArxRlePlot(CString strPath)
**
**  **000
**
*************************************/

ArxRlePlot::ArxRlePlot(CString strPath)
{
	m_strDevice = _T("DWF6 eplot.pc3");
	m_strPath = strPath;
	m_pPSV = acdbHostApplicationServices()->plotSettingsValidator(); 

	// 取得当前layout
	AcDbLayoutManager *pLayoutManager = acdbHostApplicationServices()->layoutManager(); 
	AcDbObjectId btrId = pLayoutManager->getActiveLayoutBTRId();
	AcDbBlockTableRecord *pBTR;
	Acad::ErrorStatus es=acdbOpenObject(pBTR,btrId,AcDb::kForRead);
	m_layoutId = pBTR->getLayoutId();
	AcDbLayout *pLayout=NULL;
	acdbOpenObject(pLayout,m_layoutId,AcDb::kForRead);

#pragma warning (disable: 4800)

	m_pPlotSettings = new AcDbPlotSettings(pLayout->modelType());

#pragma warning (default: 4800)

	m_pPlotSettings->copyFrom(pLayout);
	pLayout->close();
	pBTR->close();
}

/****************************************************************************
**
**  ArxRlePlot::~ArxRlePlot()
**
**  **000
**
*************************************/

ArxRlePlot::~ArxRlePlot()
{
	delete m_pPlotSettings;
}

/****************************************************************************
**
**  ArxRlePlot::Start()
**
**  **000
**
*************************************/

void ArxRlePlot::StartPlot()
{
	Acad::ErrorStatus es;
		
	es = m_pPSV->setPlotType(m_pPlotSettings, AcDbPlotSettings::kExtents);

	//设置缩放比例
	es = m_pPSV->setUseStandardScale(m_pPlotSettings, Adesk::kFalse);
	es = m_pPSV->setCustomPrintScale(m_pPlotSettings, 1, 1);
	es = m_pPSV->setPlotCentered(m_pPlotSettings, true);
	es = m_pPSV->setPlotCfgName(m_pPlotSettings,m_strDevice);
	m_pPSV->refreshLists(m_pPlotSettings);
	
	AcPlPlotEngine* pEngine = NULL;
    if(Acad::eOk == AcPlPlotFactory::createPublishEngine(pEngine))
	{
		// 打印进度对话框
		AcPlPlotProgressDialog *pPlotProgDlg = acplCreatePlotProgressDialog(acedGetAcadFrame()->m_hWnd,false,1);
	    
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kDialogTitle,_T("输出到DWF"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kCancelJobBtnMsg,_T("退出"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kCancelSheetBtnMsg,_T("退出"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kSheetSetProgressCaption,_T("发送到DWF打印机"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kSheetProgressCaption,_T("进度"));
	    
		pPlotProgDlg->setPlotProgressRange(0,100);
		pPlotProgDlg->onBeginPlot();
		pPlotProgDlg->setIsVisible(true);
	    
		es = pEngine->beginPlot(pPlotProgDlg);
		
		AcPlPlotPageInfo pageInfo;
		AcPlPlotInfo plotInfo; 
	    
		// 设置布局
		plotInfo.setLayout(m_layoutId);

		// 重置参数
		plotInfo.setOverrideSettings(m_pPlotSettings);
		AcPlPlotInfoValidator validator;
        validator.setMediaMatchingPolicy(AcPlPlotInfoValidator::kMatchEnabled);
		es = validator.validate(plotInfo);

		// 开始打印
		const TCHAR *szDocName = acDocManager->curDocument()->fileName();

		es = pEngine->beginDocument(plotInfo, szDocName, NULL, 1, true, m_strPath);

		// 给打印机和进度对话框发送消息
		pPlotProgDlg->onBeginSheet();
		pPlotProgDlg->setSheetProgressRange(0, 100);
		pPlotProgDlg->setSheetProgressPos(0);

		es = pEngine->beginPage(pageInfo, plotInfo, true);    	

		es = pEngine->beginGenerateGraphics();
		es = pEngine->endGenerateGraphics();

		es = pEngine->endPage();

		pPlotProgDlg->setSheetProgressPos(100);
		pPlotProgDlg->onEndSheet();
		pPlotProgDlg->setPlotProgressPos(100);
		es = pEngine->endDocument();
		es = pEngine->endPlot();
		
		pEngine->destroy();
		pEngine = NULL;
		pPlotProgDlg->destroy();
	}
	else
	{
		acedAlert(_T("打印DWF失败!"));
	}
}

/****************************************************************************
**
**  ArxRlePlot::BatPlot()
**
**  **000
**
*************************************/

void ArxRlePlot::BatPlot()
{
	//批量打印
	// 取得当前layout
	AcDbLayoutManager *pLayoutManager =
		acdbHostApplicationServices()->layoutManager(); //取得布局管理器对象
	AcDbObjectId objectId = pLayoutManager->findLayoutNamed(pLayoutManager->findActiveLayout(TRUE));//获得当前布局
	AcDbObject* obj;
	acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
	AcDbLayout* pLayout = AcDbLayout::cast(obj);
	//获得打印机验证器对象
	AcDbPlotSettingsValidator *pPSV =NULL;
	pPSV = acdbHostApplicationServices()->plotSettingsValidator();
	//更新打印设备列表
	pPSV->refreshLists(pLayout);
	//打印机设置
	ACHAR* m_strDevice = _T("DWF6 ePlot.pc3");//打印机名字
	pPSV->setPlotCfgName(pLayout,m_strDevice);//设置打印设备
	ACHAR* m_mediaName = _T("ISO A4");//图纸名称
	pPSV->setCanonicalMediaName(pLayout,m_mediaName);//设置图纸尺寸
	pPSV->setPlotType(pLayout,AcDbPlotSettings::kWindow);//设置打印范围为窗口
	pPSV->setPlotWindowArea(pLayout,100,100,200,200);//设置打印范围,超出给范围的将打不出来
	pPSV->setCurrentStyleSheet(pLayout,_T("JSTRI.ctb"));//设置打印样式表
	pPSV->setPlotCentered(pLayout,true);//是否居中打印
	pPSV->setUseStandardScale(pLayout,true);//设置是否采用标准比例
	pPSV->setStdScaleType(pLayout,AcDbPlotSettings::kScaleToFit);//布满图纸
	pPSV->setPlotRotation(pLayout,AcDbPlotSettings::k90degrees);//设置打印方向

	//pPSV->setPlotViewName(pLayout,_T("打印1"));

	//准备打印/////////////////////////////////////////////////////////////////////////
	AcPlPlotEngine* pEngine = NULL;//创建打印引擎
	if(AcPlPlotFactory::createPublishEngine(pEngine)!=Acad::eOk)
	{
		acedAlert(_T("打印失败!"));
		return;
	}
	// 打印进度对话框
	AcPlPlotProgressDialog *pPlotProgDlg = acplCreatePlotProgressDialog(acedGetAcadFrame()->m_hWnd,false,1);
	pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kDialogTitle,_T("lot API Progress"));
	pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kCancelJobBtnMsg,_T("Cancel Job"));
	pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kCancelSheetBtnMsg,_T("Cancel Sheet"));
	pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kSheetSetProgressCaption,_T("Job Progress"));
	pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kSheetProgressCaption,_T("Sheet Progress"));
	pPlotProgDlg->setPlotProgressRange(0,100);
	pPlotProgDlg->onBeginPlot();
	pPlotProgDlg->setIsVisible(true);
	//begin plot
	Acad::ErrorStatus es = pEngine->beginPlot(pPlotProgDlg);
	AcPlPlotPageInfo pageInfo;//打印页信息
	AcPlPlotInfo plotInfo; //打印信息
	// 设置布局
	plotInfo.setLayout(m_layoutId);
	// 重置参数
	plotInfo.setOverrideSettings(pLayout);
	AcPlPlotInfoValidator validator;//创建打印信息验证器
	validator.setMediaMatchingPolicy(AcPlPlotInfoValidator::kMatchEnabled);
	es = validator.validate(plotInfo);
	// begin document
	const TCHAR *szDocName = acDocManager->curDocument()->fileName();//获得当前的文件名
	es = pEngine->beginDocument(plotInfo, szDocName, NULL,1,true,NULL);
	//给打印机和进度对话框发送消息
	pPlotProgDlg->onBeginSheet();
	pPlotProgDlg->setSheetProgressRange(0, 100);
	pPlotProgDlg->setSheetProgressPos(0);
	//begin page
	es = pEngine->beginPage(pageInfo, plotInfo, true);
	es = pEngine->beginGenerateGraphics();
	es = pEngine->endGenerateGraphics();
	//end page
	es = pEngine->endPage();
	pPlotProgDlg->setSheetProgressPos(100);
	pPlotProgDlg->onEndSheet();
	pPlotProgDlg->setPlotProgressPos(100);
	//end document
	es = pEngine->endDocument();
	//end plot
	es = pEngine->endPlot();
	//返回资源
	pEngine->destroy();
	pEngine = NULL;
	pPlotProgDlg->destroy();
	pLayout->close();
}

