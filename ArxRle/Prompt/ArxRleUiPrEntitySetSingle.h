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

#ifndef ARXRLEUIPRENTITYSETSINGLE_H
#define ARXRLEUIPRENTITYSETSINGLE_H

#include "ArxRleUiPrEntitySet.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrEntitySetSingle:
**
**  **jma
**
****************************/

class ArxRleUiPrEntitySetSingle : public ArxRleUiPrEntitySet {

friend class ArxRleUiPrSubentity;

public:
                    ArxRleUiPrEntitySetSingle(LPCTSTR msg);
    virtual         ~ArxRleUiPrEntitySetSingle();

    virtual Status  go();

    AcDbObjectId    objectId() const;

    void            setAllowNone(bool allowIt);

protected:
        // data members
    bool			m_allowNone;

private:
        // outlawed functions
								ArxRleUiPrEntitySetSingle(const ArxRleUiPrEntitySetSingle&);
    ArxRleUiPrEntitySetSingle&	operator=(const ArxRleUiPrEntitySetSingle&);
};


#endif    // ARXRLEUIPRENTITYSETSINGLE_H

