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

#ifndef ARXRLE_ARXRLEAPPEDREACTOR_H
#define ARXRLE_ARXRLEAPPEDREACTOR_H

#include "Snoop/ArxRleCloneSet.h"

/****************************************************************************
**
**  CLASS ArxRleAppEditorReactor:
**      needed for our app itself to track when databases are constructed,
**  or destructed so we can put our db reactor on it.
**
**  **jma
**
*************************************/

class ArxRleAppEditorReactor : public AcEditorReactor {

public:
    ACRX_DECLARE_MEMBERS(ArxRleAppEditorReactor);

        // messages that are sent by notification
    virtual void    databaseConstructed(AcDbDatabase*);
    virtual void    databaseToBeDestroyed(AcDbDatabase* pDwg);

	virtual void	endDeepClone(AcDbIdMapping& idMap);

    virtual void    beginDeepCloneXlation(AcDbIdMapping& pIdMap, Acad::ErrorStatus* pRetStatus);

		// used by our test function to add extra objects to the cloneSet of things
		// to be included in Wblock.
	ArxRleCloneSet&	cloneSet()		{ return m_cloneSet; }

private:
        // singleton class, so no one can call constructor/destructors
                ArxRleAppEditorReactor();
    virtual     ~ArxRleAppEditorReactor();

        // data members
    ArxRleCloneSet		m_cloneSet;
    AcDbObjectIdArray	m_didTheseDicts;

		// helper functions
    void    insertCloneOwnerDict(const AcDbObjectId& dictId, AcDbDatabase* destDb,
                                        AcDbIdMapping& idMap);
    void    insertCloneMergeDicts(AcDbDictionary* srcDict, AcDbDictionary* destDict,
                                        AcDbIdMapping& idMap);
    void    collectAllDictRecords(AcDbDatabase* db, AcDbObjectIdArray& objIds);
    void    searchOneDictionary(AcDbDictionary* dict, AcDbObjectIdArray& objIds);

	void	verifyClonedReferences(AcDbIdMapping& idMap);

        // outlawed functions
    ArxRleAppEditorReactor(const ArxRleAppEditorReactor &copy);
    ArxRleAppEditorReactor& operator=(const ArxRleAppEditorReactor &copy);


    // static functions for constructing/retrieving/destroying singleton instance
public:
    static ArxRleAppEditorReactor*  getInstance();
    static void                     destroyInstance();

private:
    static ArxRleAppEditorReactor*  m_instance;        // singleton instance

};

#endif    // ARXRLE_ARXRLEAPPEDREACTOR_H
