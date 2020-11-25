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

#ifndef ARXRLEPERSISTENTENTREACTOR_H
#define ARXRLEPERSISTENTENTREACTOR_H

#include "ArxRlePersistentObjReactor.h"

/****************************************************************************
**
**	CLASS ArxRlePersistEntReactor:
**
**	**jma
**
*************************************/

class ArxRlePersistentEntReactor : public ArxRlePersistentObjReactor {

public:
    ACRX_DECLARE_MEMBERS(ArxRlePersistentEntReactor);

        // constructors/destructors
					ArxRlePersistentEntReactor()	{}
    virtual			~ArxRlePersistentEntReactor()	{}

    virtual void    modifiedGraphics(const AcDbObject* obj);

    virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler *filer);
    virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler *filer) const;
    virtual	Acad::ErrorStatus	dxfInFields(AcDbDxfFiler *filer);
    virtual	Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler *filer) const;

protected:
		// helper functions
    virtual void	printReactorMessage(LPCTSTR event, const AcDbObject* obj) const;

private:
		// data members
    static Adesk::Int16 m_version;

        // outlawed functions
                                ArxRlePersistentEntReactor(const ArxRlePersistentEntReactor &copy);
    ArxRlePersistentEntReactor&	operator=(const ArxRlePersistentEntReactor &copy);        

};

#endif    // ARXRLEPERSISTENTENTREACTOR_H
