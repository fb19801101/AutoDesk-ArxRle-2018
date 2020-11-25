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

#ifndef ARXRLEUIPRENTITY_H
#define ARXRLEUIPRENTITY_H

#include "ArxRleUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrEntity:
**
**  **jma
**
*************************************/

class ArxRleUiPrEntity : public ArxRleUiPrBase {

public:
                        ArxRleUiPrEntity(LPCTSTR msg, LPCTSTR keyWordList);
    virtual             ~ArxRleUiPrEntity();

    virtual Status      go();       // issue the prompt

    Acad::ErrorStatus   addAllowedClass(AcRxClass* classType, bool doIsATest = false);

    bool		        filterLockedLayers() const;
    Acad::ErrorStatus   setFilterLockedLayers(bool filterThem);

    AcDbObjectId        objectId() const;
    AcGePoint3d         pickPoint() const;

    void                setAllowNone(bool allowIt);

protected:
        // data members
    bool			    m_filterLockedLayers;
    AcDbVoidPtrArray    m_allowedClassTypes;
    AcDbIntArray        m_doIsATest;
    AcDbObjectId        m_objId;
    bool			    m_allowNone;
    AcGePoint3d         m_pickPt;

        // helper functions
    bool		        correctClass(AcDbEntity* ent);

private:
        // outlawed functions
                        ArxRleUiPrEntity(const ArxRleUiPrEntity&);
    ArxRleUiPrEntity&	operator=(const ArxRleUiPrEntity&);
};


#endif  // ARXRLEUIPRENTITY_H
