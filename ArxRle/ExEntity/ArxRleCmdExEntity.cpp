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
//
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRle.h"
#include "ArxRleCmdExEntity.h"
#include "ArxRleBrokenLine.h"
#include "ArxRleTitleLabel.h"
#include "ArxRleLeadDimension.h"
#include "AcadUtils\ArxRleUtils.h"
#include "Prompt\ArxRleKeywordArray.h"
#include "DbEntity\ArxRleEntityClass.h"
#include "AcadUtils\ArxRleSelSet.h"



/****************************************************************************
**
**  ArxRleCmdExEntity::registerCommandLineFunctions
**
**  **000
**
*************************************/

void ArxRleCmdExEntity::registerCommandLineFunctions(AcEdCommandStack* cmdStack, LPCTSTR appname)
{
	cmdStack->addCommand(appname, _T("ArxRleTitleLabel"),                 _T("TitleLabel"),                ACRX_CMD_MODAL, &cmdLineTitle);
	cmdStack->addCommand(appname, _T("ArxRleBroken"),                     _T("Broken"),                    ACRX_CMD_MODAL, &cmdLineBroken);
	cmdStack->addCommand(appname, _T("ArxRleLeadDimension"),              _T("LeadDimension"),             ACRX_CMD_MODAL, &cmdLineLeadDimension);

	cmdStack->addCommand(appname, _T("ArxRleAddTitleLabel"),              _T("AddTitleLabel"),             ACRX_CMD_MODAL, &addTitle);
    cmdStack->addCommand(appname, _T("ArxRleModifyTitleLabel"),           _T("ModifyTitleLabel"),          ACRX_CMD_MODAL, &modifyTitle);

	cmdStack->addCommand(appname, _T("ArxRleAddBroken"),		          _T("AddBroken"),                 ACRX_CMD_MODAL, &addBroken);
	cmdStack->addCommand(appname, _T("ArxRleModifyBroken"),               _T("ModifyBroken"),              ACRX_CMD_MODAL, &modifyBroken);

	cmdStack->addCommand(appname, _T("ArxRleAddLeadDimension"),           _T("AddLeadDimension"),          ACRX_CMD_MODAL, &addLeadDimension);
	cmdStack->addCommand(appname, _T("ArxRleModifyLeadDimension"),        _T("ModifyLeadDimension"),       ACRX_CMD_MODAL, &modifyLeadDimension);

	cmdStack->addCommand(appname, _T("ArxRleChangeToPolyline"),           _T("ChangeToPolyline"),          ACRX_CMD_MODAL, &changeToPolyline);
}

/****************************************************************************
**
**  ArxRleCmdExEntity::cmdLineTitle
**
**  **000
**
*************************************/

void ArxRleCmdExEntity::cmdLineTitle()
{
		// ArxRleKeyword array allows us to use Global and Local keywords (i.e., English
		// and another language) without the need to worry about how it was picked.  In
		// this case, we haven't translated anything, so the keywords are the same.
		// see ArxRleKeywordArray for more details.
	ArxRleKeywordArray kwords(ArxRleApp::getApp()->dllInstance());
    kwords.append(_T("Add"),    _T("Add"));
    kwords.append(_T("Modify"), _T("Modify"));

    CString optionsStr, kwordStr;
    kwords.makeOptionsList(optionsStr);
    kwords.makeKeywordList(kwordStr);

	CString promptStr;
    promptStr.Format(_T("Title Label options %s"), optionsStr);

    ArxRleUiPrKeyWord prCmd(promptStr, kwordStr);
    if(prCmd.go() != ArxRleUiPrBase::kOk)
        return;

    int keywordIndex;
    if(kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
        ASSERT(0);
        return;
    }

    if(keywordIndex == 0)
        addTitle();
    else if(keywordIndex == 1)
        modifyTitle();
    else {
        ASSERT(0);
        return;
    }
}

/****************************************************************************
**
**  ArxRleCmdExEntity::cmdLineBroken
**
**  **000
**
*************************************/

void ArxRleCmdExEntity::cmdLineBroken()
{
	// ArxRleKeyword array allows us to use Global and Local keywords (i.e., English
	// and another language) without the need to worry about how it was picked.  In
	// this case, we haven't translated anything, so the keywords are the same.
	// see ArxRleKeywordArray for more details.
	ArxRleKeywordArray kwords(ArxRleApp::getApp()->dllInstance());
	kwords.append(_T("Add"),    _T("Add"));
	kwords.append(_T("Modify"), _T("Modify"));

	CString optionsStr, kwordStr;
	kwords.makeOptionsList(optionsStr);
	kwords.makeKeywordList(kwordStr);

	CString promptStr;
	promptStr.Format(_T("Broken Line options %s"), optionsStr);

	ArxRleUiPrKeyWord prCmd(promptStr, kwordStr);
	if(prCmd.go() != ArxRleUiPrBase::kOk)
		return;

	int keywordIndex;
	if(kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
		ASSERT(0);
		return;
	}

	if(keywordIndex == 0)
		addBroken();
	else if(keywordIndex == 1)
		modifyBroken();
	else {
		ASSERT(0);
		return;
	}
}

/****************************************************************************
**
**  ArxRleCmdExEntity::cmdLineLeadDimension
**
**  **000
**
*************************************/

void ArxRleCmdExEntity::cmdLineLeadDimension()
{
	// ArxRleKeyword array allows us to use Global and Local keywords (i.e., English
	// and another language) without the need to worry about how it was picked.  In
	// this case, we haven't translated anything, so the keywords are the same.
	// see ArxRleKeywordArray for more details.
	ArxRleKeywordArray kwords(ArxRleApp::getApp()->dllInstance());
	kwords.append(_T("Add"),    _T("Add"));
	kwords.append(_T("Modify"), _T("Modify"));

	CString optionsStr, kwordStr;
	kwords.makeOptionsList(optionsStr);
	kwords.makeKeywordList(kwordStr);

	CString promptStr;
	promptStr.Format(_T("Lead Dimension options %s"), optionsStr);

	ArxRleUiPrKeyWord prCmd(promptStr, kwordStr);
	if(prCmd.go() != ArxRleUiPrBase::kOk)
		return;

	int keywordIndex;
	if(kwords.find(prCmd.keyWordPicked(), keywordIndex) == false) {
		ASSERT(0);
		return;
	}

	if(keywordIndex == 0)
		addLeadDimension();
	else if(keywordIndex == 1)
		modifyLeadDimension();
	else {
		ASSERT(0);
		return;
	}
}

/****************************************************************************
**
**  ArxRleCmdExEntity::addTitle
**
**  **000
**
*************************************/

void ArxRleCmdExEntity::addTitle()
{
	ArxRleUiPrString prLabelUp(_T("LabelUp"), true);
	ArxRleUiPrString prLabelDown(_T("LabelDown"), true);

	if((prLabelUp.go() != ArxRleUiPrBase::kOk)||
		(prLabelDown.go() != ArxRleUiPrBase::kOk))
		return;

	ArxRleUiPrDoubleDef prSize(_T("TextSize"), NULL,ArxRleUiPrDouble::kAny, 4);
	if(prSize.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrPoint prPt(_T("BeginPt"), NULL);
	if(prPt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleJigTitleLabel *pJig = new ArxRleJigTitleLabel();
	pJig->setPoint(prPt.value());
	pJig->setLabel(prLabelUp.value(), prLabelDown.value(), prSize.value());
	pJig->dragIt();
	delete pJig;
}


/****************************************************************************
**
**  ArxRleCmdExEntity::modifyTitle
**
**  **000
**
*************************************/

void ArxRleCmdExEntity::modifyTitle()
{
	ArxRleUiPrEntity prEnt(_T("Select Title Label to modify"), NULL);
	prEnt.addAllowedClass(ArxRleTitleLabel::desc());
	prEnt.setFilterLockedLayers(true);

	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleTitleLabel* title = new ArxRleTitleLabel;
	Acad::ErrorStatus es = acdbOpenObject(title, prEnt.objectId(), AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete title;
		return;
	}

	ArxRleUiPrStringDef prLabelUp(_T("LabelUp "), title->getLabelUp(), true);
	if(prLabelUp.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrStringDef prLabelDown(_T("LabelDown "), title->getLabelDown(), true);
	if(prLabelDown.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrDoubleDef prTitleSize(_T("TitleSize "), NULL,ArxRleUiPrDouble::kAny, title->getTextSize());
	if(prTitleSize.go() != ArxRleUiPrBase::kOk)
		return;

	title->setLabel(prLabelUp.value(),prLabelDown.value(),prTitleSize.value());
	title->close();
}

/****************************************************************************
**
**  ArxRleCmdExEntity::addBroken
**
**  **000
**
*************************************/

void ArxRleCmdExEntity::addBroken()
{
	ArxRleUiPrDoubleDef prSize(_T("Size "), NULL,ArxRleUiPrDouble::kAny, 4);
	if(prSize.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrPoint prPt(_T("BeginPt"), NULL);
	if(prPt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleJigBrokenLine *pJig = new ArxRleJigBrokenLine();
	pJig->set(prPt.value(), prSize.value());
	pJig->dragIt();
	delete pJig;
}

/****************************************************************************
**
**  ArxRleCmdExEntity::modifyBroken
**
**  **000
**
*************************************/

void ArxRleCmdExEntity::modifyBroken()
{
	ArxRleUiPrEntity prEnt(_T("Select Broken Line to modify"), NULL);
	prEnt.addAllowedClass(ArxRleBrokenLine::desc());
	prEnt.setFilterLockedLayers(true);

	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleBrokenLine* broken = new ArxRleBrokenLine;
	Acad::ErrorStatus es = acdbOpenObject(broken, prEnt.objectId(), AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete broken;
		return;
	}

	ArxRleUiPrDoubleDef prBrokenSize(_T("BrokenSize "), NULL,ArxRleUiPrDouble::kAny, broken->getBrokenSize());
	if(prBrokenSize.go() != ArxRleUiPrBase::kOk)
		return;

	broken->setBrokenSize(prBrokenSize.value());
	broken->close();
}

/****************************************************************************
**
**  ArxRleCmdExEntity::addLeadDimension
**
**  **000
**
*************************************/

void ArxRleCmdExEntity::addLeadDimension()
{
	ArxRleUiPrString prLabelUp(_T("LabelUp"), true);
	ArxRleUiPrString prLabelDown(_T("LabelDown"), true);

	if((prLabelUp.go() != ArxRleUiPrBase::kOk)||
		(prLabelDown.go() != ArxRleUiPrBase::kOk))
		return;

	ArxRleUiPrDoubleDef prSize(_T("TextSize"), NULL,ArxRleUiPrDouble::kAny, 4);
	if(prSize.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrPoint prPtBase(_T("BasePt"), NULL);
	if(prPtBase.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrPoint prPtBegin(_T("BeginPt"), NULL, prPtBase.value());
	if(prPtBegin.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleJigLeadDimension *pJig = new ArxRleJigLeadDimension();
	pJig->setPoint(prPtBase.value(),prPtBegin.value());
	pJig->setLabel(prLabelUp.value(), prLabelDown.value(), prSize.value());
	pJig->dragIt();
	delete pJig;
}

/****************************************************************************
**
**  ArxRleCmdExEntity::modifyLeadDimension
**
**  **000
**
*************************************/

void ArxRleCmdExEntity::modifyLeadDimension()
{
	ArxRleUiPrEntity prEnt(_T("Select Lead Dimension to modify"), NULL);
	prEnt.addAllowedClass(ArxRleLeadDimension::desc());
	prEnt.setFilterLockedLayers(true);

	if(prEnt.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleLeadDimension* dim = new ArxRleLeadDimension;
	Acad::ErrorStatus es = acdbOpenObject(dim, prEnt.objectId(), AcDb::kForWrite);
	if(es != Acad::eOk) {
		ArxRleUtils::rxErrorMsg(es);
		delete dim;
		return;
	}

	ArxRleUiPrStringDef prLabelUp(_T("LabelUp "), dim->getLabelUp(), true);
	if(prLabelUp.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrStringDef prLabelDown(_T("LabelDown "), dim->getLabelDown(), true);
	if(prLabelDown.go() != ArxRleUiPrBase::kOk)
		return;

	ArxRleUiPrDoubleDef prTextSize(_T("TextSize "), NULL,ArxRleUiPrDouble::kAny, dim->getTextSize());
	if(prTextSize.go() != ArxRleUiPrBase::kOk)
		return;

	dim->setLabel(prLabelUp.value(),prLabelDown.value(),prTextSize.value());
	dim->close();
}

/****************************************************************************
**
**  ArxRleCmdExEntity::changeToPolyline
**
**  **000
**
*************************************/

struct PtNr //给所有的点编号，多次出现的点只编一个号，后面用编号来代替点，简化过程
{
	AcGePoint3d pt;	//点
	int nNum;		//编号
};
struct NrMap //相连的点，用编号与编号连表示
{
	int nNum1;		//编号
	int nNum2;		//编号
	double dBulge;	//凸度
};

bool FindNextPointNr(vector<NrMap>& nm, int nThisNum, double& dThisBulge, int& nNextNum)
{
	bool bFind = false;

	//以第一个编号给为起点查找
	vector<NrMap>::iterator itr;
	for (itr = nm.begin(); itr != nm.end(); itr++)
	{
		if ((*itr).nNum1 == nThisNum)
		{
			nNextNum = (*itr).nNum2;
			dThisBulge = (*itr).dBulge;
			bFind = true;
			nm.erase(itr);
			break;
		}
	}

	if (!bFind)//如果以第一个编号给为起点未找到,就以第二个编号给为起点查找
	{
		for (itr = nm.begin(); itr != nm.end(); itr++)
		{
			if ((*itr).nNum2 == nThisNum)
			{
				nNextNum = (*itr).nNum1;
				dThisBulge = -(*itr).dBulge;//凸度取反
				bFind = true;
				nm.erase(itr);
				break;
			}
		}
	}	

	if (bFind)
	{
		return true;
	}
	else
	{
		nNextNum = -1;
		dThisBulge = 0.0;
	}

	return false;
}

bool NrToPoint(vector<PtNr>& vecPt2Num, int nThisNum, AcGePoint3d& ptThis)
{
	bool bFind = false;
	vector<PtNr>::iterator itr;
	for (itr = vecPt2Num.begin(); itr != vecPt2Num.end(); itr++)
	{
		if ((*itr).nNum == nThisNum)
		{
			ptThis = (*itr).pt;
			bFind = true;
			break;
		}
	}

	return bFind;
}

void GetPointInfo(vector<PtNr>& vecPt2Num, vector<NrMap>& vecNumMap, int& nCodeNum,
				  const AcGePoint3d& ptStart, const AcGePoint3d ptEnd, double dBulge)
{
	bool bStartNew = true;	//起点是否编号
	bool bEndNew = true;	//终点是否编号

	NrMap nummap;//两点之间的联系信息
	nummap.dBulge = dBulge;

	//处理起点
	vector<PtNr>::iterator itr;
	for (itr = vecPt2Num.begin(); itr != vecPt2Num.end(); itr++)
	{
		if ((*itr).pt == ptStart)
		{
			bStartNew = false;	
			nummap.nNum1 = (*itr).nNum;
			break;
		}
	}

	if (bStartNew)
	{
		PtNr pn;
		pn.nNum = nCodeNum++;
		pn.pt = ptStart;
		vecPt2Num.push_back(pn);

		nummap.nNum1 = pn.nNum;
	}

	//处理终点
	for (itr = vecPt2Num.begin(); itr != vecPt2Num.end(); itr++)
	{
		if ((*itr).pt == ptEnd)
		{
			bEndNew = false;
			nummap.nNum2 = (*itr).nNum;
			break;
		}
	}

	if (bEndNew)
	{
		PtNr pn;
		pn.nNum = nCodeNum++;
		pn.pt = ptEnd;
		vecPt2Num.push_back(pn);
		nummap.nNum2 = pn.nNum;
	}

	//添加联系信息
	vecNumMap.push_back(nummap);
}

void ArxRleCmdExEntity::changeToPolyline()
{
	ArxRleSelSet ss;
	if(ss.userSelect() == ArxRleSelSet::kSelected)
	{    // have user select entities from DWG
		AcDbObjectIdArray objList;
		ss.asArray(objList);
		if(!objList.isEmpty())
		{
			AcDbObjectId idPolyline;
			
			vector<PtNr> vecPt2Num;//所有点编号
			vector<NrMap> vecNumMap;//所有连接信息
			int nCodeNum = 0;

			int length = objList.length();
			for (int i = 0; i < length; i++) 
			{ 
				// 获得指向当前元素的指针 
				AcDbEntity *pEnt; 
				Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt, objList.at(i), 
					AcDb::kForRead); 

				// 选择到作为边界的多段线了，直接跳过该次循环 
				if (es != Acad::eOk)   
					continue; 		

				if(pEnt->isKindOf(AcDbArc::desc()))//圆弧
				{
					AcDbArc* pArc = AcDbArc::cast(pEnt);
					if (pArc == NULL)
						continue; 

					AcGePoint3d ptStart, ptEnd;
					pArc->getStartPoint(ptStart);
					pArc->getEndPoint(ptEnd);

					double dBulge = 0.0;
					dBulge = GetArcBulge(pArc);	

					GetPointInfo(vecPt2Num, vecNumMap, nCodeNum, ptStart, ptEnd, dBulge);
					pArc->close();			
				} 
				else if (pEnt->isKindOf(AcDbLine::desc()))//直线 
				{
					AcDbLine* pLine = AcDbLine::cast(pEnt);
					if (pLine == NULL)
						continue; 

					AcGePoint3d ptStart, ptEnd;
					pLine->getStartPoint(ptStart);
					pLine->getEndPoint(ptEnd);

					double dBulge = 0.0;

					GetPointInfo(vecPt2Num, vecNumMap, nCodeNum, ptStart, ptEnd, dBulge);

					pLine->close();
				}

				else if (pEnt->isKindOf(AcDbPolyline::desc()))
				{
					AcDbPolyline* pPolyLine = AcDbPolyline::cast(pEnt);
					if (pPolyLine == NULL)
						continue; 

					int nVerCount = 0;
					nVerCount = pPolyLine->numVerts();
					if (nVerCount <= 1)
						continue; 

					AcGePoint3d ptFirst;
					double dBugle = -1000.0;
					pPolyLine->getPointAt(0, ptFirst);
					pPolyLine->getBulgeAt(0,dBugle);

					for (int i = 1; i < nVerCount; i++)
					{
						AcGePoint3d ptVer;
						pPolyLine->getPointAt(i, ptVer);
						GetPointInfo(vecPt2Num, vecNumMap, nCodeNum, ptFirst, ptVer, dBugle);

						ptFirst = ptVer;
						pPolyLine->getBulgeAt(i, dBugle);
					}	
					pPolyLine->close();				
				}

				pEnt->close();
			}			 

			AcGePoint3d pt1, pt2;
			double dBulge = 0.0;

			vector<NrMap>::iterator itr1;// vecNumMap;
			vector<NrMap>::iterator itr2;// vecNumMap;
			struct DrawPoint //转换成多段线的点
			{
				int nNum;		//编号
				double dBulge;	//到下一点的凸度
			};
			vector< vector<DrawPoint> > vecLines;

			if (vecNumMap.size() > 0)
			{
				itr1 = vecNumMap.begin();
			}

			while(itr1 != vecNumMap.end())
			{
				//从某点出发向一个方向搜索
				vector<DrawPoint> vecOneLine;

				int nBegin = (*itr1).nNum1;
				int nThisNum = nBegin;			
				int nLastNum = nThisNum;

				DrawPoint drawpoint;			

				while(vecNumMap.size() > 0)		
				{	
					bool bSuc = false;
					double dThisBulge = 0.0;
					int nNextNum = 0;

					bSuc = FindNextPointNr(vecNumMap, nThisNum, dThisBulge, nNextNum);
					if (bSuc)
					{
						drawpoint.nNum = nThisNum;
						drawpoint.dBulge =dThisBulge;
						vecOneLine.push_back(drawpoint);
						nThisNum = nNextNum;
						nLastNum = nThisNum;
					}				
					else
					{
						break;
					}
				}

				//处理最近一个点
				drawpoint.nNum = nLastNum;
				drawpoint.dBulge = 0.0;
				vecOneLine.push_back(drawpoint);


				//从某点出发向另一个方向搜索
				vector<DrawPoint> vecOtherLine;
				nThisNum = nBegin;
				nLastNum = nThisNum;
				while(vecNumMap.size() > 0)		
				{	
					bool bSuc = false;
					double dThisBulge = 0.0;
					int nNextNum = 0;

					bSuc = FindNextPointNr(vecNumMap, nThisNum, dThisBulge, nNextNum);
					if (bSuc)
					{
						drawpoint.nNum = nNextNum;
						drawpoint.dBulge =dThisBulge;
						vecOtherLine.push_back(drawpoint);
						nThisNum = nNextNum;
					}				
					else
					{
						break;
					}
				}

				//两个方向拼接
				reverse(vecOtherLine.begin(), vecOtherLine.end());
				vector<DrawPoint>::iterator itrTmp;
				for (itrTmp = vecOtherLine.begin(); itrTmp != vecOtherLine.end(); itrTmp++)
				{
					(*itrTmp).dBulge *= -1.0;
				}

				vecOtherLine.insert(vecOtherLine.end(), vecOneLine.begin(), vecOneLine.end());

				vecLines.push_back(vecOtherLine);
				itr1 = vecNumMap.begin();
			}

			//绘制多段线
			vector< vector<DrawPoint> >::iterator itr_1;
			vector<DrawPoint>::iterator itr_2;
			for (itr_1 = vecLines.begin(); itr_1 != vecLines.end(); itr_1++)
			{
				AcDbPolyline* pPolyLine = new AcDbPolyline;
				int i = 0;
				vector<DrawPoint>& vecPoints = (*itr_1);
				for (itr_2 = vecPoints.begin(); itr_2 != vecPoints.end(); itr_2++)
				{
					int nNum = (*itr_2).nNum;
					AcGePoint3d ptVer;
					if (NrToPoint(vecPt2Num, nNum, ptVer))
					{
						pPolyLine->addVertexAt(i++, ptVer.convert2d(AcGePlane::kXYPlane),(*itr_2).dBulge);
					}
				}

				idPolyline = AddEntity(pPolyLine);
				pPolyLine->close();
			}
		}
	}
}