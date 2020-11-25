//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleSdStrObjId.h"




/////////////////////////////////////////////////////////////////////////////
/////////////////////////////// ArxRleSdStrObjIdNode //////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**    ArxRleSdStrObjIdNode::ArxRleSdStrObjIdNode (constructor)
**
**    **jma
**
*************************************/

ArxRleSdStrObjIdNode::ArxRleSdStrObjIdNode(LPCTSTR name, const AcDbObjectId& objId)
:    m_name(name),
    m_objid(objId)
{
}


/////////////////////////////////////////////////////////////////////////////
///////////////////////////// ArxRleSdStrObjIdList ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**    ArxRleSdStrObjIdList::ArxRleSdStrObjIdList(constructor)
**
**    **jma
**
*************************************/

ArxRleSdStrObjIdList::ArxRleSdStrObjIdList(BOOL caseSensitive)
:    m_caseSensitive(caseSensitive)
{
}

/****************************************************************************
**
**    ArxRleSdStrObjIdList::~ArxRleSdStrObjIdList (destructor)
**
**    **jma
**
*************************************/

ArxRleSdStrObjIdList::~ArxRleSdStrObjIdList()
{
    RemoveAll();
}

/****************************************************************************
**
**    ArxRleSdStrObjIdList::AddAlpha
**
**    **jma
**
*************************************/

void
ArxRleSdStrObjIdList::RemoveAll()
{
    ArxRleSdStrObjIdNode* nodePtr;

    POSITION pos = m_list.GetHeadPosition();
    while(pos != NULL){
        nodePtr = static_cast<ArxRleSdStrObjIdNode*>(m_list.GetNext(pos));
        delete nodePtr;
    }
    m_list.RemoveAll();
}

/****************************************************************************
**
**    ArxRleSdStrObjIdList::AddAlpha
**
**    **jma
**
*************************************/

POSITION
ArxRleSdStrObjIdList::AddAlpha(LPCTSTR name, const AcDbObjectId& objId)
{
    ArxRleSdStrObjIdNode* newNode = new ArxRleSdStrObjIdNode(name, objId);
    ArxRleSdStrObjIdNode* tmpNode;

    POSITION pos = m_list.GetHeadPosition();

    if (!m_caseSensitive) {
        while (pos != NULL) {
            tmpNode = static_cast<ArxRleSdStrObjIdNode*>(m_list.GetAt(pos));
            if (tmpNode && (tmpNode->m_name.CompareNoCase(name) > 0))
                return(m_list.InsertBefore(pos, static_cast<void*>(newNode)));
            m_list.GetNext(pos);
        }
    }
    else {
        while (pos != NULL) {
            tmpNode = static_cast<ArxRleSdStrObjIdNode*>(m_list.GetAt(pos));
            if (tmpNode && (tmpNode->m_name.Compare(name) > 0))
                return(m_list.InsertBefore(pos, static_cast<void*>(newNode)));
            m_list.GetNext(pos);
        }
    }
    return(m_list.AddTail(static_cast<void*>(newNode)));
}

/****************************************************************************
**
**    ArxRleSdStrObjIdList::AddHead
**
**    **jma
**
*************************************/

POSITION
ArxRleSdStrObjIdList::AddHead(LPCTSTR name, const AcDbObjectId& objId)
{
    ArxRleSdStrObjIdNode* newNode = new ArxRleSdStrObjIdNode(name, objId);
    return(m_list.AddHead(static_cast<void*>(newNode)));
}

/****************************************************************************
**
**    ArxRleSdStrObjIdList::AddTail
**
**    **jma
**
*************************************/

POSITION
ArxRleSdStrObjIdList::AddTail(LPCTSTR name, const AcDbObjectId& objId)
{
    ArxRleSdStrObjIdNode* newNode = new ArxRleSdStrObjIdNode(name, objId);
    return(m_list.AddTail(static_cast<void*>(newNode)));
}

/****************************************************************************
**
**    ArxRleSdStrObjIdList::GetAtIndex
**
**    **jma
**
*************************************/

BOOL
ArxRleSdStrObjIdList::GetAtIndex(int index, CString& str, AcDbObjectId& objId) const
{
    POSITION pos = m_list.FindIndex(index);
    if (pos) {
        ArxRleSdStrObjIdNode* node;
        node = (ArxRleSdStrObjIdNode*)(m_list.GetAt(pos));
        str = node->m_name;
        objId = node->m_objid;
        return(TRUE);
    }
    else
        return(FALSE);
}

/****************************************************************************
**
**    ArxRleSdStrObjIdList::GetIndexFor
**
**    **jma
**
*************************************/

BOOL
ArxRleSdStrObjIdList::GetIndexFor(const CString& str, int& index) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    ArxRleSdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (str.CompareNoCase(tmpStr) == 0) {
            index = i;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    ArxRleSdStrObjIdList::GetIndexFor
**
**    **jma
**
*************************************/

BOOL
ArxRleSdStrObjIdList::GetIndexFor(const AcDbObjectId& objId, int& index) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    ArxRleSdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (tmpId == objId) {
            index = i;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    ArxRleSdStrObjIdList::GetMatchFor
**
**    **jma
**
*************************************/

BOOL
ArxRleSdStrObjIdList::GetMatchFor(const CString& str, AcDbObjectId& objId) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    ArxRleSdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (str.CompareNoCase(tmpStr) == 0) {
            objId = tmpId;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    ArxRleSdStrObjIdList::GetMatchFor
**
**    **jma
**
*************************************/

BOOL
ArxRleSdStrObjIdList::GetMatchFor(const AcDbObjectId& objId, CString& str) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    ArxRleSdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (tmpId == objId) {
            str = tmpStr;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    ArxRleSdStrObjIdList::Rename
**
**    **jma
**
*************************************/

BOOL
ArxRleSdStrObjIdList::Rename(const CString& oldName, const CString& newName)
{
    ArxRleSdStrObjIdNode* nodePtr;

    POSITION pos = m_list.GetHeadPosition();
    while (pos != NULL) {
        nodePtr = static_cast<ArxRleSdStrObjIdNode*>(m_list.GetNext(pos));
        if (nodePtr->m_name == oldName) {
            nodePtr->m_name = newName;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**	ArxRleSdStrObjIdList::RemoveAt
**
**	**jma
**
*************************************/

void
ArxRleSdStrObjIdList::RemoveAt(int index)
{
    POSITION pos = m_list.FindIndex(index);
    if (pos) {
        ArxRleSdStrObjIdNode* node;
        node = static_cast<ArxRleSdStrObjIdNode*>(m_list.GetAt(pos));
        delete node;
        m_list.RemoveAt(pos);
    }
}

/****************************************************************************
**
**    ArxRleSdStrObjIdListIterator::ArxRleSdStrObjIdListIterator
**
**    **jma
**
*************************************/

ArxRleSdStrObjIdListIterator::ArxRleSdStrObjIdListIterator(const ArxRleSdStrObjIdList& list)
:    m_list(list.m_list)
{
    m_pos = m_list.GetHeadPosition();
}

/****************************************************************************
**
**    ArxRleSdStrObjIdListIterator::item
**
**    **jma
**
*************************************/

void
ArxRleSdStrObjIdListIterator::item(CString& name, AcDbObjectId& objId) const
{
    ArxRleSdStrObjIdNode* node;

    node = (ArxRleSdStrObjIdNode*)(m_list.GetAt(m_pos));
    name = node->m_name;
    objId = node->m_objid;
}






