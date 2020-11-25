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

#ifndef ARXRLEKEYWORDARRAY_H
#define ARXRLEKEYWORDARRAY_H

/****************************************************************************
**
**  ArxRleKeywordInfo::ArxRleKeywordInfo
**
**  **jma
**
*************************************/

class ArxRleKeywordInfo {

public:
                        ArxRleKeywordInfo(const CString& localKword,
                                       const CString& globalKword,
                                       const CString& optionStr);
    virtual             ~ArxRleKeywordInfo();

    const CString&	localKeyword() const;
    void            setLocalKeyword(const CString& kword);

    const CString&	globalKeyword() const;
    void            setGlobalKeyword(const CString& kword);

    const CString&	optionStr() const;
    void            setOptionStr(const CString& str);

    bool			isVisible() const;
    void            setIsVisible(bool itIs);

    bool			isEnabled() const;
    void            setIsEnabled(bool itIs);

    bool			isDefault() const;
    void            setIsDefault(bool itIs);

private:
        // data members
    CString     m_localKword;
    CString     m_globalKword;
    CString     m_optionStr;
    bool	    m_isVisible;
    bool		m_isEnabled;
    bool		m_isDefault;
};


/****************************************************************************
**
**  ArxRleKeywordArray::ArxRleKeywordArray
**
**  **jma
**
*************************************/

class ArxRleKeywordArray {

public:
                    ArxRleKeywordArray(HINSTANCE resDllInstance);
    virtual         ~ArxRleKeywordArray();

    int             count() const;

        // standard way to append keywords as long as the keyword
        // is the same as the option you want displayed
    void            append(LPCTSTR localKword, LPCTSTR globalKword,
                                    bool isVisible = true,
                                    bool isEnabled = true);

    void            append(UINT localKwordResId, LPCTSTR globalKword,
                                    bool isVisible = true,
                                    bool isEnabled = true);

        // use this form if the option to be displayed must vary from
        // they keyword itself.  E.g., it has two words in it.
    void            append(LPCTSTR localKword, LPCTSTR globalKword,
                                    LPCTSTR optionStr,
                                    bool isVisible = true,
                                    bool isEnabled = true);
    void            append(UINT localKwordResId, LPCTSTR globalKword,
                                    UINT optionStrId,
                                    bool isVisible = true,
                                    bool isEnabled = true);

    void            deleteAll();

    ArxRleKeywordInfo* getAt(int index);

    bool		    find(LPCTSTR kwordPicked, int& indexFoundAt);
    bool			findByJigIndex(int jigIndex, int& actualIndex);

        // pass in -1, -1 for start/end index to get all
    void            setVisible(bool isVisible, int startIndex, int endIndex);
    void            setEnabled(bool isEnabled, int startIndex, int endIndex);

    void            setAsDefault(int index);

    void            makeKeywordList(CString& str);
    void            makeOptionsList(CString& optionsStr);
    void            makeOptionsList(CString& optionsStr, CString& defaultStr, bool includeDefInOptions);

private:
        // data members
    HINSTANCE			m_resDllHandle;
    AcDbVoidPtrArray	m_keywordArray;

        // helper functions
    bool      getActualIndexRange(int& startIndex, int& endIndex);
};

#endif  // ARXRLEKEYWORDARRAY_H


