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

#ifndef ARXRLEUIPRCORNER_H
#define ARXRLEUIPRCORNER_H

#include "ArxRleUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrCorner:
**
**  **jma
**
*************************************/

class ArxRleUiPrCorner : public ArxRleUiPrBase {

public:
                        ArxRleUiPrCorner(LPCTSTR msg, LPCTSTR keyWordList, const AcGePoint3d& basePt);
    virtual             ~ArxRleUiPrCorner();

    virtual Status      go();             // issue the prompt
    const AcGePoint3d&  value();

    void                setBasePt(const AcGePoint3d& basePt);
    void                setUseDashedLine(bool useIt);
    void                setNoLimitsCheck(bool noCheck);

protected:
        // data members
    AcGePoint3d         m_value;
    AcGePoint3d         m_basePt;
    bool			    m_useDashedLine;
    bool			    m_noLimCheck;

private:
        // outlawed functions
                        ArxRleUiPrCorner(const ArxRleUiPrCorner&);
    ArxRleUiPrCorner&	operator=(const ArxRleUiPrCorner&);
};


#endif  // ARXRLEUIPRCORNER_H
