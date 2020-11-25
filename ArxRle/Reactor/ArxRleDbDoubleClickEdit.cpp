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
	// ɾ������������
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
	// ָ����������������ĵ�
	AcApDocument* pDoc = acDocManager->curDocument();

	// �ж������������ʵ�����ҵ��Զ���ʵ�壬������޸Ĳ���
	if (pEnt->isKindOf(ArxRleNetPlanWork::desc())) 
	{
		ArxRleNetPlanWork* work = ArxRleNetPlanWork::cast(pEnt);

		// ����Ҫ��ʵ����б༭���������ĵ�
		acDocManager->lockDocument(pDoc, AcAp::kWrite);
		// ���򿪼�����������д��ʽ����ֹ������ֻ��ģʽ��
		if( !upgradeOpen(work)) 
		{
			acDocManager->unlockDocument(pDoc);
			return;
		}

		msgErr(L"ArxRleNetPlanWork");

		work->close();
	}

	// �����޸���ɣ������ĵ�
	acDocManager->unlockDocument(pDoc);
	// ˢ����ʾ
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
		acutPrintf(L"���󣺲��ܴ�%sʵ��!", pEnt->isA()->name());
		return FALSE;
	}
	return TRUE;
}