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

#ifndef ARXRLEUIPRBASE_H
#define ARXRLEUIPRBASE_H

/****************************************************************************
**
**  CLASS ArxRleUiPrBase:
**      base class for prompts. Holds keyword mechanism and basic
**  status return value.
**
**  **jma
**
*************************************/

class ArxRleUiPrBase {

public:

    enum Status {
        kCancel    = 0,
        kNone,        // not returned unless explicitly enabled
        kKeyWord,
        kOk
    };

    virtual LPCTSTR				keyWords() const;
    virtual Acad::ErrorStatus   setKeyWords(LPCTSTR keyWordList);

    virtual LPCTSTR		        message() const;
    virtual Acad::ErrorStatus   setMessage(LPCTSTR message);

    virtual LPCTSTR             keyWordPicked() const;
    virtual bool		        isKeyWordPicked(LPCTSTR matchKeyWord);

    virtual Status              go() = 0;   // issue the prompt

protected:
                    ArxRleUiPrBase(LPCTSTR msg, LPCTSTR keyWordList);
    virtual         ~ArxRleUiPrBase();    // must be public to call delete on base class pointer

        // data members
    CString		m_keyWords;
    CString		m_message;
    CString		m_keyWordPicked;

private:
        // outlawed functions
                    ArxRleUiPrBase(const ArxRleUiPrBase&);
    ArxRleUiPrBase&	operator=(const ArxRleUiPrBase&);
};

#endif //   ARXRLEUIPRBASE_H
