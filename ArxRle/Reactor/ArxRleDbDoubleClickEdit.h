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

#ifndef ARXRLE_DBDOUBLECLICKEDIT_H
#define ARXRLE_DBDOUBLECLICKEDIT_H

/****************************************************************************
**
**  CLASS ArxRleAppEditorReactor:
**      needed for our app itself to track when databases are constructed,
**  or destructed so we can put our db reactor on it.
**
**  **000
**
*************************************/

class ArxRleDbDoubleClickEdit : public AcDbDoubleClickEdit {

public:
    ACRX_DECLARE_MEMBERS(ArxRleDbDoubleClickEdit);

	ArxRleDbDoubleClickEdit();
	virtual ~ArxRleDbDoubleClickEdit();

	virtual void startEdit(AcDbEntity *pEnt, AcGePoint3d pt); 
	virtual void finishEdit();

	// outlawed functions
	ArxRleDbDoubleClickEdit(const ArxRleDbDoubleClickEdit &copy);
	ArxRleDbDoubleClickEdit&	operator=(const ArxRleDbDoubleClickEdit &copy);

	// static functions for constructing/retrieving/destroying singleton instance
public:
	static ArxRleDbDoubleClickEdit*  getInstance();
	static void                  destroyInstance();

private:
	bool upgradeOpen(AcDbObject *pEnt);
	static ArxRleDbDoubleClickEdit*  m_instance;        // singleton instance
};

#endif  // ARXRLE_DBDOUBLECLICKEDIT_H
