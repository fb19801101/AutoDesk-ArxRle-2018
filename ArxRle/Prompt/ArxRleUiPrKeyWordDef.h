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

#ifndef ARXRLEUIPRKEYWORDEF_H
#define ARXRLEUIPRKEYWORDEF_H

#include "ArxRleUiPrKeyWord.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrKeyWordDef:
**      a keyword prompt with a default response
**
**  **jma
**
*************************************/

class ArxRleUiPrKeyWordDef : public ArxRleUiPrKeyWord {

public:
                    ArxRleUiPrKeyWordDef(LPCTSTR msg, LPCTSTR keyWordList, LPCTSTR def);
    virtual         ~ArxRleUiPrKeyWordDef();

    virtual Status  go();             // issue the prompt

private:
    CString    m_default;

    bool	   keyWordMatch();

        // outlawed functions
							ArxRleUiPrKeyWordDef(const ArxRleUiPrKeyWordDef&);
    ArxRleUiPrKeyWordDef&	operator=(const ArxRleUiPrKeyWordDef&);
};

#endif  // ARXRLEUIPRKEYWORDEF_H
