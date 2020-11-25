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

#ifndef ARXRLEUIPRDOUBLEDEF_H
#define ARXRLEUIPRDOUBLEDEF_H

#include "ArxRleUiPrDouble.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrDoubleDef:
**
**  **jma
**
*************************************/

class ArxRleUiPrDoubleDef : public ArxRleUiPrDouble {

public:
                    ArxRleUiPrDoubleDef(LPCTSTR msg, LPCTSTR keyWordList, DoubleType type, double def);
    virtual         ~ArxRleUiPrDoubleDef();

    virtual Status  go();             // issue the prompt

private:
        // data members
    double          m_default;

        // outlawed functions
							ArxRleUiPrDoubleDef(const ArxRleUiPrDoubleDef&);
    ArxRleUiPrDoubleDef&	operator=(const ArxRleUiPrDoubleDef&);
};

#endif  // ARXRLEUIPRDOUBLEDEF_H
