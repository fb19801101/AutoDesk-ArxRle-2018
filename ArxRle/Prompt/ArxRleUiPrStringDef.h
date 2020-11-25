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

#ifndef ARXRLEUIPRSTRINGDEF_H
#define ARXRLEUIPRSTRINGDEF_H

#include "ArxRleUiPrString.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrStringDef:
**
**  **jma
**
*************************************/

class ArxRleUiPrStringDef : public ArxRleUiPrString {

public:
                    ArxRleUiPrStringDef(LPCTSTR msg, LPCTSTR def, bool allowSpaces = true);
    virtual         ~ArxRleUiPrStringDef();

    virtual Status  go();    // issue the prompt

private:
        // data members
    CString		m_default;

        // outlawed functions
							ArxRleUiPrStringDef(const ArxRleUiPrStringDef&);
    ArxRleUiPrStringDef&	operator=(const ArxRleUiPrStringDef&);
};



#endif  // ARXRLEUIPRSTRINGDEF_H
