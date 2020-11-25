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

#ifndef ARXRLEDBREACTOR_H
#define ARXRLEDBREACTOR_H

/****************************************************************************
**
**  CLASS DbReactor:
**
**  **jma
**
*************************************/

class ArxRleDatabaseReactor : public AcDbDatabaseReactor {

public:
	ACRX_DECLARE_MEMBERS(ArxRleDatabaseReactor);

        // constructor/destructors
                    ArxRleDatabaseReactor();
    virtual         ~ArxRleDatabaseReactor();

    virtual void    objectAppended(const AcDbDatabase* dwg, const AcDbObject* obj);
    virtual void    objectUnAppended(const AcDbDatabase* dwg, const AcDbObject* obj);
    virtual void    objectReAppended(const AcDbDatabase* dwg, const AcDbObject* obj);
    virtual void    objectOpenedForModify(const AcDbDatabase* dwg, const AcDbObject* obj);
    virtual void    objectModified(const AcDbDatabase* dwg, const AcDbObject* obj);
    virtual void    objectErased(const AcDbDatabase* dwg, const AcDbObject* obj,
                                        Adesk::Boolean pErased = Adesk::kTrue);
    virtual void    headerSysVarWillChange(const AcDbDatabase* dwg, const TCHAR* name);
    virtual void    headerSysVarChanged(const AcDbDatabase* dwg, const TCHAR* name,
                                        Adesk::Boolean bSuccess);
    virtual void    proxyResurrectionCompleted(const AcDbDatabase* dwg,
                                        const TCHAR* appname, AcDbObjectIdArray& objects);
    virtual void	goodbye(const AcDbDatabase* dwg);

	bool			showDetails() const;
	void			setShowDetails(bool showThem);

private:
		// data members
	bool	m_showDetails;

		// helper functions
    void    printReactorMessage(const AcDbDatabase* db, LPCTSTR event, const AcDbObject* obj) const;
    void    printReactorMessage(const AcDbDatabase* db, LPCTSTR event, LPCTSTR str) const;
    void    printReactorMessage(const AcDbDatabase* db, LPCTSTR event) const;

        // outlawed functions
	ArxRleDatabaseReactor(const ArxRleDatabaseReactor &copy);
    ArxRleDatabaseReactor&  operator=(const ArxRleDatabaseReactor &copy);        
};


#endif    // ARXRLEDBREACTOR_H
