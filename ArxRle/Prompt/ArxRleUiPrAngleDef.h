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

#ifndef ARXRLEUIPRANGLEDEF_H
#define ARXRLEUIPRANGLEDEF_H

#include "ArxRleUiPrAngle.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrAngleDef:
**
**  **jma
**
*************************************/

class ArxRleUiPrAngleDef : public ArxRleUiPrAngle {

public:
                    ArxRleUiPrAngleDef(LPCTSTR msg, LPCTSTR keyWordList, AngleType type, double def);
                    ArxRleUiPrAngleDef(LPCTSTR msg, LPCTSTR keyWordList, AngleType type,
                            const AcGePoint3d& basePt, double def);
    virtual        ~ArxRleUiPrAngleDef();

    virtual Status  go();       // issue the prompt

private:
        // data members
    double          m_default;

        // outlawed functions
                        ArxRleUiPrAngleDef(const ArxRleUiPrAngleDef&);
    ArxRleUiPrAngleDef&	operator=(const ArxRleUiPrAngleDef&);
};

#endif  // ARXRLEUIPRANGLEDEF_H
