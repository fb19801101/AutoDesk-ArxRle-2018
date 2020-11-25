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

#ifndef ARXRLEUIPRPOINT_H
#define ARXRLEUIPRPOINT_H

#include "ArxRleUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrBase:
**
**  **jma
**
*************************************/

class ArxRleUiPrPoint : public ArxRleUiPrBase {

public:
                        ArxRleUiPrPoint(LPCTSTR msg, LPCTSTR keyWordList);
                        ArxRleUiPrPoint(LPCTSTR msg, LPCTSTR keyWordList, const AcGePoint3d& basePt);
    virtual             ~ArxRleUiPrPoint();

    virtual Status      go();             // issue the prompt
    const AcGePoint3d&  value()    const;

    const AcGePoint3d&  basePt() const;
    void                setBasePt(const AcGePoint3d& basePt);
    void                setUseBasePt(bool useIt);
    void                setUseDashedLine(bool useIt);
    void                setNoLimitsCheck(bool noCheck);
    void                setAllowNone(bool allowIt);

protected:
    AcGePoint3d         m_value;
    AcGePoint3d         m_basePt;
    bool		        m_useBasePt;
    bool		        m_useDashedLine;
    bool			    m_noLimCheck;
    bool			    m_allowNone;

private:
        // helper functions
    void                init();

        // outlawed functions
                        ArxRleUiPrPoint(const ArxRleUiPrPoint&);
    ArxRleUiPrPoint&	operator=(const ArxRleUiPrPoint&);
};

#endif  // ARXRLEUIPRPOINT_H
