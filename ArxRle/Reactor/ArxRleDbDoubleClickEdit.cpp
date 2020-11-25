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

#include "ArxRleDbDoubleClickEdit.h"
#include "ExEntity\ArxRleTitleLabel.h"
#include "ExEntity\ArxRleBrokenLine.h"
#include "NetPlan\ArxRleNetPlanWork.h"

ACRX_NO_CONS_DEFINE_MEMBERS(ArxRleDbDoubleClickEdit, AcDbDoubleClickEdit);

/////////////////////////////////////////////////////////////////////////////
//////////// STATIC CONSTRUCTOR/DESTRUCTOR FOR THIS SINGLETON CLASS /////////
/////////////////////////////////////////////////////////////////////////////

ArxRleDbDoubleClickEdit* ArxRleDbDoubleClickEdit::m_instance = NULL;

/****************************************************************************
**
**  ArxRleEditorReactor::getInstance
**
**  **000
**
*************************************/

ArxRleDbDoubleClickEdit* ArxRleDbDoubleClickEdit::getInstance()
{
	if(m_instance)
		return m_instance;

	m_instance = new ArxRleDbDoubleClickEdit;
	return m_instance;
}

/****************************************************************************
**
**  ArxRleEditorReactor::destroyInstance
**
**  **000
**
*************************************/

void ArxRleDbDoubleClickEdit::destroyInstance()
{
	if(m_instance) {
		delete m_instance;
		m_instance = NULL;
	}
	else {
		ASSERT(0);
	}
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  ArxRleDbDoubleClickEdit::ArxRleDbDoubleClickEdit()
**
**  **000
**
*************************************/

ArxRleDbDoubleClickEdit::ArxRleDbDoubleClickEdit()
{
	ArxRleTitleLabel::desc()->addX(AcDbDoubleClickEdit::desc(), this);
	ArxRleBrokenLine::desc()->addX(AcDbDoubleClickEdit::desc(), this);
	ArxRleNetPlanWork::desc()->addX(AcDbDoubleClickEdit::desc(), this);
}

/****************************************************************************
**
**  ArxRleDbDoubleClickEdit::~ArxRleDbDoubleClickEdit()
**
**  **000
**
*************************************/

ArxRleDbDoubleClickEdit::~ArxRleDbDoubleClickEdit()
{
	// 删除输入点监视器
	ArxRleTitleLabel::desc()->delX(AcDbDoubleClickEdit::desc());
	ArxRleBrokenLine::desc()->delX(AcDbDoubleClickEdit::desc());
	ArxRleNetPlanWork::desc()->delX(AcDbDoubleClickEdit::desc());
}

/****************************************************************************
**
**  ArxRleDbDoubleClickEdit::startEdit
**
**  **000
**
*************************************/

void ArxRleDbDoubleClickEdit::startEdit(AcDbEntity *pEnt, AcGePoint3d clickpt)
{
	// 指向这个对象所属的文档
	AcApDocument* pDoc = acDocManager->curDocument();

	// 判断如果传进来的实体是我的自定义实体，便进行修改操作
	if (pEnt->isKindOf(ArxRleNetPlanWork::desc())) 
	{
		ArxRleNetPlanWork* work = ArxRleNetPlanWork::cast(pEnt);

		// 由于要对实体进行编辑，先锁定文档
		acDocManager->lockDocument(pDoc, AcAp::kWrite);
		// 将打开级别升级到可写方式，防止对象以只读模式打开
		if( !upgradeOpen(work)) 
		{
			acDocManager->unlockDocument(pDoc);
			return;
		}

		msgErr(L"ArxRleNetPlanWork");

		work->close();
	}

	// 所有修改完成，解锁文档
	acDocManager->unlockDocument(pDoc);
	// 刷新显示
	actrTransactionManager->flushGraphics();
}

/****************************************************************************
**
**  ArxRleDbDoubleClickEdit::finishEdit
**
**  **000
**
*************************************/

void ArxRleDbDoubleClickEdit::finishEdit()
{
}

/****************************************************************************
**
**  ArxRleDbDoubleClickEdit::upgradeOpen
**
**  **000
**
*************************************/

bool ArxRleDbDoubleClickEdit::upgradeOpen(AcDbObject *pEnt)
{
	if(pEnt->upgradeOpen()!=Acad::eOk)
	{
		acutPrintf(L"错误：不能打开%s实体!", pEnt->isA()->name());
		return FALSE;
	}
	return TRUE;
}