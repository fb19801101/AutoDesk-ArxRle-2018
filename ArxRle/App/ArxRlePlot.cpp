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

	// ȡ�õ�ǰlayout
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

	//�������ű���
	es = m_pPSV->setUseStandardScale(m_pPlotSettings, Adesk::kFalse);
	es = m_pPSV->setCustomPrintScale(m_pPlotSettings, 1, 1);
	es = m_pPSV->setPlotCentered(m_pPlotSettings, true);
	es = m_pPSV->setPlotCfgName(m_pPlotSettings,m_strDevice);
	m_pPSV->refreshLists(m_pPlotSettings);
	
	AcPlPlotEngine* pEngine = NULL;
    if(Acad::eOk == AcPlPlotFactory::createPublishEngine(pEngine))
	{
		// ��ӡ���ȶԻ���
		AcPlPlotProgressDialog *pPlotProgDlg = acplCreatePlotProgressDialog(acedGetAcadFrame()->m_hWnd,false,1);
	    
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kDialogTitle,_T("�����DWF"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kCancelJobBtnMsg,_T("�˳�"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kCancelSheetBtnMsg,_T("�˳�"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kSheetSetProgressCaption,_T("���͵�DWF��ӡ��"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kSheetProgressCaption,_T("����"));
	    
		pPlotProgDlg->setPlotProgressRange(0,100);
		pPlotProgDlg->onBeginPlot();
		pPlotProgDlg->setIsVisible(true);
	    
		es = pEngine->beginPlot(pPlotProgDlg);
		
		AcPlPlotPageInfo pageInfo;
		AcPlPlotInfo plotInfo; 
	    
		// ���ò���
		plotInfo.setLayout(m_layoutId);

		// ���ò���
		plotInfo.setOverrideSettings(m_pPlotSettings);
		AcPlPlotInfoValidator validator;
        validator.setMediaMatchingPolicy(AcPlPlotInfoValidator::kMatchEnabled);
		es = validator.validate(plotInfo);

		// ��ʼ��ӡ
		const TCHAR *szDocName = acDocManager->curDocument()->fileName();

		es = pEngine->beginDocument(plotInfo, szDocName, NULL, 1, true, m_strPath);

		// ����ӡ���ͽ��ȶԻ�������Ϣ
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
		acedAlert(_T("��ӡDWFʧ��!"));
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
	//������ӡ
	// ȡ�õ�ǰlayout
	AcDbLayoutManager *pLayoutManager =
		acdbHostApplicationServices()->layoutManager(); //ȡ�ò��ֹ���������
	AcDbObjectId objectId = pLayoutManager->findLayoutNamed(pLayoutManager->findActiveLayout(TRUE));//��õ�ǰ����
	AcDbObject* obj;
	acdbOpenAcDbObject(obj, objectId, AcDb::kForRead);
	AcDbLayout* pLayout = AcDbLayout::cast(obj);
	//��ô�ӡ����֤������
	AcDbPlotSettingsValidator *pPSV =NULL;
	pPSV = acdbHostApplicationServices()->plotSettingsValidator();
	//���´�ӡ�豸�б�
	pPSV->refreshLists(pLayout);
	//��ӡ������
	ACHAR* m_strDevice = _T("DWF6 ePlot.pc3");//��ӡ������
	pPSV->setPlotCfgName(pLayout,m_strDevice);//���ô�ӡ�豸
	ACHAR* m_mediaName = _T("ISO A4");//ͼֽ����
	pPSV->setCanonicalMediaName(pLayout,m_mediaName);//����ͼֽ�ߴ�
	pPSV->setPlotType(pLayout,AcDbPlotSettings::kWindow);//���ô�ӡ��ΧΪ����
	pPSV->setPlotWindowArea(pLayout,100,100,200,200);//���ô�ӡ��Χ,��������Χ�Ľ��򲻳���
	pPSV->setCurrentStyleSheet(pLayout,_T("JSTRI.ctb"));//���ô�ӡ��ʽ��
	pPSV->setPlotCentered(pLayout,true);//�Ƿ���д�ӡ
	pPSV->setUseStandardScale(pLayout,true);//�����Ƿ���ñ�׼����
	pPSV->setStdScaleType(pLayout,AcDbPlotSettings::kScaleToFit);//����ͼֽ
	pPSV->setPlotRotation(pLayout,AcDbPlotSettings::k90degrees);//���ô�ӡ����

	//pPSV->setPlotViewName(pLayout,_T("��ӡ1"));

	//׼����ӡ/////////////////////////////////////////////////////////////////////////
	AcPlPlotEngine* pEngine = NULL;//������ӡ����
	if(AcPlPlotFactory::createPublishEngine(pEngine)!=Acad::eOk)
	{
		acedAlert(_T("��ӡʧ��!"));
		return;
	}
	// ��ӡ���ȶԻ���
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
	AcPlPlotPageInfo pageInfo;//��ӡҳ��Ϣ
	AcPlPlotInfo plotInfo; //��ӡ��Ϣ
	// ���ò���
	plotInfo.setLayout(m_layoutId);
	// ���ò���
	plotInfo.setOverrideSettings(pLayout);
	AcPlPlotInfoValidator validator;//������ӡ��Ϣ��֤��
	validator.setMediaMatchingPolicy(AcPlPlotInfoValidator::kMatchEnabled);
	es = validator.validate(plotInfo);
	// begin document
	const TCHAR *szDocName = acDocManager->curDocument()->fileName();//��õ�ǰ���ļ���
	es = pEngine->beginDocument(plotInfo, szDocName, NULL,1,true,NULL);
	//����ӡ���ͽ��ȶԻ�������Ϣ
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
	//������Դ
	pEngine->destroy();
	pEngine = NULL;
	pPlotProgDlg->destroy();
	pLayout->close();
}

