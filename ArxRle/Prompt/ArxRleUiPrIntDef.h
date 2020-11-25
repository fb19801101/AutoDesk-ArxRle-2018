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

#ifndef ARXRLEUIPRINTDEF_H
#define ARXRLEUIPRINTDEF_H

#include "ArxRleUiPrInt.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrIntDef:
**
**  **jma
**
*************************************/

class ArxRleUiPrIntDef : public ArxRleUiPrInt {

public:
                    ArxRleUiPrIntDef(LPCTSTR msg, LPCTSTR keyWordList, IntType type, int def);
    virtual         ~ArxRleUiPrIntDef();

    virtual Status  go();             // issue the prompt

private:
        // data members
    int             m_default;

        // outlawed functions
						ArxRleUiPrIntDef(const ArxRleUiPrIntDef&);
    ArxRleUiPrIntDef&	operator=(const ArxRleUiPrIntDef&);
};


#endif  // ARXRLEUIPRINTDEF_H
