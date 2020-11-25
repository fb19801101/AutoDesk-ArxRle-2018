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

#ifndef ARXRLEUIPRKEYWORD_H
#define ARXRLEUIPRKEYWORD_H

#include "ArxRleUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrKeyWord:
**      A prompt with keywords only. Doesn't do much over what Prompt
**  does except provide a "go" function to issue the prompt.
**
**  **jma
**
*************************************/

class ArxRleUiPrKeyWord : public ArxRleUiPrBase {

public:
                    ArxRleUiPrKeyWord(LPCTSTR msg, LPCTSTR keyWordList);
    virtual         ~ArxRleUiPrKeyWord();

    virtual Status  go();                           // issue the prompt
    LPCTSTR         value();                        // for consistency

    void            setAllowNone(bool allowIt);

protected:
    bool			m_allowNone;

private:
        // outlawed functions
                        ArxRleUiPrKeyWord(const ArxRleUiPrKeyWord&);
    ArxRleUiPrKeyWord&	operator=(const ArxRleUiPrKeyWord&);
};


#endif  // ARXRLEUIPRKEYWORD_H
