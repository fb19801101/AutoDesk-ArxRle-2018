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

#ifndef ARXRLE_SDSTROBJID_H
#define ARXRLE_SDSTROBJID_H

/****************************************************************************
**
**    CLASS ArxRleSdStrObjIdNode:
**
**    **jma
**
*************************************/

class ArxRleSdStrObjIdNode {

friend class ArxRleSdStrObjIdList;
friend class ArxRleSdStrObjIdListIterator;

private:
    // constructors/destructors
    ArxRleSdStrObjIdNode(LPCTSTR name, const AcDbObjectId& objId);

    // data members
    CString            m_name;
    AcDbObjectId    m_objid;

        // outlawed functions
    ArxRleSdStrObjIdNode(const ArxRleSdStrObjIdNode& copy);
    ArxRleSdStrObjIdNode&  operator=(const ArxRleSdStrObjIdNode& copy);
};

/****************************************************************************
**
**    CLASS ArxRleSdStrObjIdList:
**
**    **jma
**
*************************************/

class ArxRleSdStrObjIdList {

friend class ArxRleSdStrObjIdListIterator;    // allow direct access to underlying list

public:
        // constructors/destructors
            ArxRleSdStrObjIdList(BOOL caseSensitive = TRUE);
    virtual    ~ArxRleSdStrObjIdList();

    // operations
    int Count() const { 
        // 64Bit: I don't think we'll ever need THAT many (2 billion) 
        // objects, especially in samples (this class isn't used any-
        // where else). Keep it as it is for now until I hear shouting.
        return AcIntPtrToInt(m_list.GetCount()); 
    }
    virtual POSITION    AddHead(LPCTSTR str, const AcDbObjectId& objId);
    virtual POSITION    AddTail(LPCTSTR str, const AcDbObjectId& objId);
    virtual POSITION    AddAlpha(LPCTSTR str, const AcDbObjectId& objId);
    virtual BOOL        GetAtIndex(int index, CString& str, AcDbObjectId& objId) const;
    virtual BOOL        GetIndexFor(const CString& str, int& index) const;
    virtual BOOL        GetIndexFor(const AcDbObjectId& objId, int& index) const;
    virtual BOOL        GetMatchFor(const AcDbObjectId& objId, CString& str) const;
    virtual BOOL        GetMatchFor(const CString& str, AcDbObjectId& objId) const;
    virtual BOOL        Rename(const CString& oldName, const CString& newName);
    virtual void        RemoveAt(int index);
    virtual void        RemoveAll();

private:
        // data members
    CPtrList    m_list;
    BOOL        m_caseSensitive;


        // outlawed functions
                    ArxRleSdStrObjIdList(const ArxRleSdStrObjIdList&);
    ArxRleSdStrObjIdList&    operator=(const ArxRleSdStrObjIdList&);
};

/****************************************************************************
**
**    CLASS ArxRleSdStrObjIdListIterator:
**
**    **jma
**
*************************************/

class ArxRleSdStrObjIdListIterator {

public:
    // constructors/destructor
    ArxRleSdStrObjIdListIterator(const ArxRleSdStrObjIdList& list);
    virtual         ~ArxRleSdStrObjIdListIterator()    {};

    virtual void    toFirst()        { m_pos = m_list.GetHeadPosition(); }
    virtual void    toLast()        { m_pos = m_list.GetTailPosition(); }
    virtual void    previous()        { m_list.GetPrev(m_pos); }
    virtual void    next()            { m_list.GetNext(m_pos); }
    virtual void    item(CString& name, AcDbObjectId& objId) const;
    virtual BOOL    done() const    { return(m_pos == NULL); }

private:
        // data members
    POSITION                m_pos;
    const CPtrList&         m_list;

        // outlawed functions    (for now)
                            ArxRleSdStrObjIdListIterator(const ArxRleSdStrObjIdListIterator&);
    ArxRleSdStrObjIdListIterator&    operator=(const ArxRleSdStrObjIdListIterator&);
};




#endif    // ARXRLE_SDSTROBJID_H
