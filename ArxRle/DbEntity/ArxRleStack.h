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

#ifndef ARXRLE_STACK_H
#define ARXRLE_STACK_H

#include <assert.h>
#include <crtdbg.h>

template<typename T>
class ArxRleNode
{
public:
    T data;
    ArxRleNode<T> *next;
    ArxRleNode() : data(T()), next(NULL) {}
    ArxRleNode(const T &initdata) : data(initdata), next(NULL) {}
    ArxRleNode(const T &initdata, ArxRleNode<T> *p) : data(initdata), next(p) {}
};

template<typename T>
class ArxRleList
{
public:
    int m_nCount;
    ArxRleNode<T> *m_pNodeHead;

public:
    ArxRleList();
    ArxRleList(const T &initdata);
    ~ArxRleList();

public:
    int     IsEmpty() const;
    int     GetCount() const;
    int     InsertBefore(const int pos, const T data);
    int     InsertAfter(const int pos, const T data);
    int     AddHead(const T data);
    int     AddTail(const T data);
    void    RemoveAt(const int pos);
    void    RemoveHead();
    void    RemoveTail();
    void    RemoveAll();
    T&      GetTail();
    T       GetTail() const;
    T&      GetHead();
    T       GetHead() const;
    T&      GetAt(const int pos);
    T       GetAt(const int pos) const;
    void    SetAt(const int pos, T data);
    int     Find(const T data) const;
};

template<typename T>
inline ArxRleList<T>::ArxRleList() : m_nCount(0), m_pNodeHead(NULL)
{
}

template<typename T>
inline ArxRleList<T>::ArxRleList(const T &initdata) : m_nCount(0), m_pNodeHead(NULL)
{
    AddHead(initdata);
}

template<typename T>
inline ArxRleList<T>::~ArxRleList()
{
    RemoveAll();
}

template<typename T>
inline int ArxRleList<T>::IsEmpty() const
{
    return 0 == m_nCount;
}

template<typename T>
inline int ArxRleList<T>::AddHead(const T data)
{
    ArxRleNode<T> *pNewNode;

    pNewNode = new ArxRleNode<T>;
    if (NULL == pNewNode)
        return 0;

    pNewNode->data = data;
    pNewNode->next = m_pNodeHead;

    m_pNodeHead = pNewNode;
    ++m_nCount;

    return 1;
}

template<typename T>
inline int ArxRleList<T>::AddTail(const T data)
{
    return InsertAfter(GetCount(), data);
}

// if success, return the position of the new node.
// if fail, return 0.
template<typename T>
inline int ArxRleList<T>::InsertBefore(const int pos, const T data)
{
    int i;
    int nRetPos;
    ArxRleNode<T> *pTmpNode1;
    ArxRleNode<T> *pTmpNode2;
    ArxRleNode<T> *pNewNode;

    pNewNode = new ArxRleNode<T>;
    if (NULL == pNewNode)
    {
        nRetPos = 0;
        goto Exit0;
    }

    pNewNode->data = data;

    // if the list is empty, replace the head node with the new node.
    if (NULL == m_pNodeHead)
    {
        pNewNode->next = NULL;
        m_pNodeHead = pNewNode;
        nRetPos = 1;
        goto Exit1;
    }

    // is pos range valid?
    ASSERT(1 <= pos && pos <= m_nCount);

    // insert before head node?
    if (1 == pos)
    {
        pNewNode->next = m_pNodeHead;
        m_pNodeHead = pNewNode;
        nRetPos = 1;
        goto Exit1;
    }

    // if the list is not empty and is not inserted before head node,
    // seek to the pos of the list and insert the new node before it.
    pTmpNode1 = m_pNodeHead;
    for (i = 1; i < pos; ++i)
    {
        pTmpNode2 = pTmpNode1;
        pTmpNode1 = pTmpNode1->next;
    }
    pNewNode->next = pTmpNode1;
    pTmpNode2->next = pNewNode;

    nRetPos = pos;

Exit1:
    ++m_nCount;
Exit0:
    return nRetPos;
}

// if success, return the position of the new node.
// if fail, return 0.
template<typename T>
inline int ArxRleList<T>::InsertAfter(const int pos, const T data)
{
    int i;
    int nRetPos;
    ArxRleNode<T> *pTmpNode;
    ArxRleNode<T> *pNewNode;

    pNewNode = new ArxRleNode<T>;
    if (NULL == pNewNode)
    {
        nRetPos = 0;
        goto Exit0;
    }

    pNewNode->data = data;

    // if the list is empty, replace the head node with the new node.
    if (NULL == m_pNodeHead)
    {
        pNewNode->next = NULL;
        m_pNodeHead = pNewNode;
        nRetPos = 1;
        goto Exit1;
    }

    // is pos range valid?
    ASSERT(1 <= pos && pos <= m_nCount);

    // if the list is not empty,
    // seek to the pos of the list and insert the new node after it.
    pTmpNode = m_pNodeHead;
    for (i = 1; i < pos; ++i)
    {
        pTmpNode = pTmpNode->next;
    }
    pNewNode->next = pTmpNode->next;
    pTmpNode->next = pNewNode;

    nRetPos = pos + 1;

Exit1:
    ++m_nCount;
Exit0:
    return nRetPos;
}

template<typename T>
inline int ArxRleList<T>::GetCount() const
{
    return m_nCount;
}

template<typename T>
inline void ArxRleList<T>::RemoveAt(const int pos)
{
    ASSERT(1 <= pos && pos <= m_nCount);

    int i;
    ArxRleNode<T> *pTmpNode1;
    ArxRleNode<T> *pTmpNode2;

    pTmpNode1 = m_pNodeHead;

    // head node?
    if (1 == pos)
    {
        m_pNodeHead = m_pNodeHead->next;
        goto Exit1;
    }

    for (i = 1; i < pos; ++i)
    {
        // we will get the previous node of the target node after
        // the for loop finished, and it would be stored into pTmpNode2
        pTmpNode2 = pTmpNode1;
        pTmpNode1 = pTmpNode1->next;
    }
    pTmpNode2->next = pTmpNode1->next;

Exit1:
    delete pTmpNode1;
    --m_nCount;
}

template<typename T>
inline void ArxRleList<T>::RemoveHead()
{
    ASSERT(0 != m_nCount);
    RemoveAt(1);
}

template<typename T>
inline void ArxRleList<T>::RemoveTail()
{
    ASSERT(0 != m_nCount);
    RemoveAt(m_nCount);
}

template<typename T>
inline void ArxRleList<T>::RemoveAll()
{
    int i;
    int nCount;
    ArxRleNode<T> *pTmpNode;

    nCount = m_nCount;
    for (i = 0; i < nCount; ++i)
    {
        pTmpNode = m_pNodeHead->next;
        delete m_pNodeHead;
        m_pNodeHead = pTmpNode;
    }

    m_nCount = 0;
}

template<typename T>
inline T& ArxRleList<T>::GetTail()
{
    ASSERT(0 != m_nCount);

    int i;
    int nCount;
    ArxRleNode<T> *pTmpNode = m_pNodeHead;

    nCount = m_nCount;
    for (i = 1; i < nCount; ++i)
    {
        pTmpNode = pTmpNode->next;
    }

    return pTmpNode->data;
}

template<typename T>
inline T ArxRleList<T>::GetTail() const
{
    ASSERT(0 != m_nCount);

    int i;
    int nCount;
    ArxRleNode<T> *pTmpNode = m_pNodeHead;

    nCount = m_nCount;
    for (i = 1; i < nCount; ++i)
    {
        pTmpNode = pTmpNode->next;
    }

    return pTmpNode->data;
}

template<typename T>
inline T& ArxRleList<T>::GetHead()
{
    ASSERT(0 != m_nCount);
    return m_pNodeHead->data;
}

template<typename T>
inline T ArxRleList<T>::GetHead() const
{
    ASSERT(0 != m_nCount);
    return m_pNodeHead->data;
}

template<typename T>
inline T& ArxRleList<T>::GetAt(const int pos)
{
    ASSERT(1 <= pos && pos <= m_nCount);

    int i;
    ArxRleNode<T> *pTmpNode = m_pNodeHead;

    for (i = 1; i < pos; ++i)
    {
        pTmpNode = pTmpNode->next;
    }

    return pTmpNode->data;
}

template<typename T>
inline T ArxRleList<T>::GetAt(const int pos) const
{
    ASSERT(1 <= pos && pos <= m_nCount);

    int i;
    ArxRleNode<T> *pTmpNode = m_pNodeHead;

    for (i = 1; i < pos; ++i)
    {
        pTmpNode = pTmpNode->next;
    }

    return pTmpNode->data;
}

template<typename T>
inline void ArxRleList<T>::SetAt(const int pos, T data)
{
    ASSERT(1 <= pos && pos <= m_nCount);

    int i;
    ArxRleNode<T> *pTmpNode = m_pNodeHead;

    for (i = 1; i < pos; ++i)
    {
        pTmpNode = pTmpNode->next;
    }
    pTmpNode->data = data;
}

template<typename T>
inline int ArxRleList<T>::Find(const T data) const
{
    int i;
    int nCount;
    ArxRleNode<T> *pTmpNode = m_pNodeHead;

    nCount = m_nCount;
    for (i = 0; i < nCount; ++i)
    {
        if (data == pTmpNode->data)
            return i + 1;
        pTmpNode = pTmpNode->next;
    }

    return 0;
}


template<typename T>
class ArxRleStack : public ArxRleList<T>
{
public:
	int push(T data);
	int pop(T *data = NULL);
	int top(T *data) const;
};

template<typename T>
inline int ArxRleStack<T>::push(T data)
{
	return AddTail(data);
}

template<typename T>
inline int ArxRleStack<T>::pop(T *data)
{
	if (IsEmpty())
		return 0;

	if (data)
		top(data);

	RemoveTail();
	return 1;
}

template<typename T>
inline int ArxRleStack<T>::top(T *data) const
{
	ASSERT(data);

	if (IsEmpty())
		return 0;

	*data = GetTail();
	return 1;
}

#endif  // ARXRLE_STACK_H
