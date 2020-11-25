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

#ifndef ARXRLE_SDSTRLIST_H
#define ARXRLE_SDSTRLIST_H


/****************************************************************************
**
**    CLASS ArxRleSdStrList:
**        Abstract base class for a list of strings.  It inherits for CStringList
**    so that we can add a few useful functions and can work on Alphabetized and
**    non-alphabetized lists without functions having to know whether they are
**    supposed to insert in order or not. You can use all the striaght MFC calls
**    to CStringList, but if use ArxRleSdStrList::Insert() it will either call AddTail()
**    or Insert alphabetically, depending on what the derived class is.
**
**    **jma
**
*************************************/

class ArxRleSdStrList : public CStringList {

public:
        // constructors/destructors
                ArxRleSdStrList()        {};
    virtual        ~ArxRleSdStrList()    {};

    virtual POSITION    Insert(const CString& str)    = 0;
    virtual BOOL        GetAtIndex(int index, CString& str) const;
    virtual POSITION    FindNoCase(LPCTSTR searchValue, POSITION startAfter = NULL) const;
};


/****************************************************************************
**
**    CLASS SdUnsortedStrList:
**        Insert function does not sort alphabetically
**
**    **jma
**
*************************************/

class SdUnsortedStrList : public ArxRleSdStrList {

public:
        // constructors/destructors
                SdUnsortedStrList()        {};
    virtual        ~SdUnsortedStrList()    {};

        // overridden from ArxRleSdStrList
    virtual POSITION    Insert(const CString& str) { return(AddTail(str)); }
};


/****************************************************************************
**
**    CLASS SdSortedStrList:
**        Insert function does sort alphabetically
**
**    **jma
**
*************************************/

class SdSortedStrList : public ArxRleSdStrList {

public:
        // constructors/destructors
                SdSortedStrList(BOOL caseSensitive = FALSE);
    virtual        ~SdSortedStrList()    {};

        // overridden from ArxRleSdStrList
    virtual POSITION    Insert(const CString& str);

private:
        // data members
    BOOL    m_caseSensitive;
};

/****************************************************************************
**
**    CLASS ArxRleSdStrListIterator:
**        can be used on a straight MFC CStringList or on one of our derived
**    classes.
**
**    **jma
**
*************************************/

class ArxRleSdStrListIterator {

public:
        // constructors/destructor
                ArxRleSdStrListIterator(const CStringList& strList);
    virtual        ~ArxRleSdStrListIterator()    {};

    virtual void        toFirst()        { m_pos = m_strList.GetHeadPosition(); }
    virtual void        toLast()        { m_pos = m_strList.GetTailPosition(); }
    virtual void        previous()        { m_strList.GetPrev(m_pos); }
    virtual void        next()            { m_strList.GetNext(m_pos); }
    virtual CString        item() const    { return(m_strList.GetAt(m_pos)); }
    virtual BOOL        done() const    { return(m_pos == NULL); }

private:
        // data members
    POSITION            m_pos;
    const CStringList&    m_strList;

        // outlawed functions    (for now)
                        ArxRleSdStrListIterator(const ArxRleSdStrListIterator&);
    ArxRleSdStrListIterator&    operator=(const ArxRleSdStrListIterator&);
};


//////////////////////////////////////////////////////////////////////////////
///// GLOBAL UTILITY FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

inline LPCTSTR
asConstChar(const CString& str)
{
    return(static_cast<LPCTSTR>(str));
}



#endif    // ARXRLE_SDSTRLIST_H
