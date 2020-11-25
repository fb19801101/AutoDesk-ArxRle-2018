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

#ifndef ARXRLEUIPRDISTDEF_H
#define ARXRLEUIPRDISTDEF_H

#include "ArxRleUiPrDist.h"


/****************************************************************************
**
**  CLASS ArxRleUiPrDistDef:
**
**  **jma
**
*************************************/

class ArxRleUiPrDistDef : public ArxRleUiPrDist {

public:
                ArxRleUiPrDistDef(LPCTSTR msg, LPCTSTR keyWordList, DistType type, double def);
                ArxRleUiPrDistDef(LPCTSTR msg, LPCTSTR keyWordList, DistType type,
                        const AcGePoint3d& basePt, double def);
    virtual     ~ArxRleUiPrDistDef();

    virtual Status go();       // issue the prompt

private:
        // data members
    double      m_default;

        // outlawed functions
                        ArxRleUiPrDistDef(const ArxRleUiPrDistDef&);
    ArxRleUiPrDistDef&	operator=(const ArxRleUiPrDistDef&);
};

#endif  // ARXRLEUIPRDISTDEF_H
