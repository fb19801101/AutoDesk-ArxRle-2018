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

#ifndef ARXRLEUIPRSTRING_H
#define ARXRLEUIPRSTRING_H

#include "ArxRleUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxRleUiPrString:
**
**  **jma
**
*************************************/

class ArxRleUiPrString : public ArxRleUiPrBase {

public:
                    ArxRleUiPrString(LPCTSTR msg, bool allowSpaces = true);
    virtual         ~ArxRleUiPrString();

    virtual Status  go();       // issue the prompt
    LPCTSTR         value();

        // overridden because this class does not support keywords
    virtual LPCTSTR				keyWords() const;
    virtual Acad::ErrorStatus   setKeyWords(LPCTSTR keyWordList);

    virtual LPCTSTR             keyWordPicked();
    virtual bool		        isKeyWordPicked(LPCTSTR matchKeyWord);

protected:
    CString		m_value;
    bool		m_allowSpaces;

private:
        // outlawed functions
						ArxRleUiPrString(const ArxRleUiPrString&);
    ArxRleUiPrString&	operator=(const ArxRleUiPrString&);
};

#endif  // ARXRLEUIPRSTRING_H
