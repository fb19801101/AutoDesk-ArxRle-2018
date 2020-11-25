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

#ifndef ARXRLEUIPRANGLE_H
#define ARXRLEUIPRANGLE_H

#include "ArxRleUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrAngle:
**
**  **jma
**
*************************************/

class ArxRleUiPrAngle : public ArxRleUiPrBase {

public:

    enum AngleType {
        kAny    = 0,
        kNoZero,
        kRange
    };

                    ArxRleUiPrAngle(LPCTSTR msg, LPCTSTR keyWordList, AngleType type);
                    ArxRleUiPrAngle(LPCTSTR msg, LPCTSTR keyWordList, AngleType type, const AcGePoint3d& basePt);
    virtual         ~ArxRleUiPrAngle();

    virtual Status  go();       // issue the prompt
    double          value();

    void            setAngleType(AngleType newType);
    void            setRange(double minVal, double maxVal);
    void            setBasePt(const AcGePoint3d& basePt);
    void            setUseBasePt(bool useIt);
    void            setUseDashedLine(bool useIt);
    void            setUnit(int unit);
    void            setPrecision(int precision);

    void            setAllowNone(bool allowIt);

protected:
        // helper functions
    bool		    inRange();

        // data memebers
    bool			m_allowNone;
    double          m_value;
    double          m_minVal;
    double          m_maxVal;
    AngleType       m_angType;
    AcGePoint3d     m_basePt;
    bool			m_useBasePt;
    bool			m_useDashedLine;
    int             m_unit;
    int             m_precision;

private:
        // helper functions
    void            init();

        // outlawed functions
						ArxRleUiPrAngle(const ArxRleUiPrAngle&);
    ArxRleUiPrAngle&	operator=(const ArxRleUiPrAngle&);
};

#endif  // ARXRLEUIPRANGLE_H
