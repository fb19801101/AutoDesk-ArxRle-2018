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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleDbAdeskLogoStyle.h"
#include "AcadUtils/ArxRleUtils.h"



     // MDI safe statics
Adesk::Int16    ArxRleDbAdeskLogoStyle::m_version = 0;
LPCTSTR			ArxRleDbAdeskLogoStyle::m_dictName = _T("ARXRLE_ADESK_LOGO_STYLES");


ACRX_DXF_DEFINE_MEMBERS(ArxRleDbAdeskLogoStyle, ArxRleDbDictRecord,
                        AcDb::kDHL_1015, AcDb::kMRelease0,
                        0, ARXRLE_ADESK_LOGO_STYLE, ArxRle)

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::ArxRleDbAdeskLogoStyle
**
**  **jma
**
*************************************/

ArxRleDbAdeskLogoStyle::ArxRleDbAdeskLogoStyle()
:   m_solidFill(true),
    m_label(_T("Autodesk"))
{
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::ArxRleDbAdeskLogoStyle
**
**  **jma
**
*************************************/

ArxRleDbAdeskLogoStyle::~ArxRleDbAdeskLogoStyle()
{
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::isSolidFill
**
**  **jma
**
*************************************/

bool
ArxRleDbAdeskLogoStyle::isSolidFill() const
{
    assertReadEnabled();
    return m_solidFill;
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::setSolidFill
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDbAdeskLogoStyle::setSolidFill(bool doIt)
{
    if (m_solidFill != doIt) {
        assertWriteEnabled();
        m_solidFill = doIt;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::label
**
**  **jma
**
*************************************/

LPCTSTR
ArxRleDbAdeskLogoStyle::label() const
{
    assertReadEnabled();
    return m_label;
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::setLabel
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDbAdeskLogoStyle::setLabel(LPCTSTR newLabel)
{
        // we allow a null string label, so check for NULL
        // and turn it into NullString
    if (newLabel == NULL) {
        if (m_label.IsEmpty() == FALSE) {   // make sure it will actually change
            assertWriteEnabled();
            m_label.Empty();
        }
        return Acad::eOk;
    }

        // don't allow to be longer than 255 for DXF simplicity
    int len = _tcslen(newLabel);
    if (len > 255)
        return Acad::eStringTooLong;

    if (m_label.Compare(newLabel)) {
        assertWriteEnabled();
        m_label = newLabel;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::textStyleId
**
**  **jma
**
*************************************/

AcDbObjectId
ArxRleDbAdeskLogoStyle::textStyleId() const
{
    assertReadEnabled();
    return m_textStyleId;
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::setTextStyleId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDbAdeskLogoStyle::setTextStyleId(const AcDbObjectId& styleId)
{
    if (styleId == AcDbObjectId::kNull)
        return Acad::eNullObjectId;

    if (styleId != m_textStyleId) {  // don't force notifications if nothing has changed
        assertWriteEnabled();
        m_textStyleId = styleId;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::dwgInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDbAdeskLogoStyle::dwgInFields(AcDbDwgFiler* filer)
{
    Acad::ErrorStatus es;
    if ((es = ArxRleDbDictRecord::dwgInFields(filer)) != Acad::eOk)
        return es;

    Adesk::Int16 version;
    filer->readItem(&version);
    if (version > m_version)
        return Acad::eMakeMeProxy;

    TCHAR* tmpStr = NULL;    // must explicitly set to NULL or readItem() crashes!

    filer->readItem(&tmpStr);
    m_label = tmpStr;
    acutDelString(tmpStr);

    filer->readItem(&m_solidFill);
    filer->readItem(&m_textStyleId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::dwgOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDbAdeskLogoStyle::dwgOutFields(AcDbDwgFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxRleDbDictRecord::dwgOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(m_version);

    filer->writeItem(static_cast<const TCHAR*>(m_label));
    filer->writeItem(m_solidFill);
    filer->writeItem(m_textStyleId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::dxfInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDbAdeskLogoStyle::dxfInFields(AcDbDxfFiler* filer)
{
    Acad::ErrorStatus es;
    if (((es = ArxRleDbDictRecord::dxfInFields(filer)) != Acad::eOk) ||
        (filer->atSubclassData(this->desc()->name()) != Adesk::kTrue))
        return filer->filerStatus();

    resbuf rb;

    while ((es == Acad::eOk) && ((es = filer->readResBuf(&rb)) == Acad::eOk)) {
        if (rb.restype == kDxfSolidFill) {
            bool doSolidFill = (rb.resval.rint == 0) ? false : true;
            setSolidFill(doSolidFill);
        }
        else if (rb.restype == kDxfLabel)
            setLabel(rb.resval.rstring);        // NOTE: normally have to free string from resbuf... not in this case, DXF Filer does
        else if (rb.restype == kDxfTextStyle) {
            AcDbObjectId tmpId;
            tmpId.setFromOldId(rb.resval.mnLongPtr);
            setTextStyleId(tmpId);
        }
        else {
            filer->pushBackItem();
            es = Acad::eEndOfFile;
        }
    }

    if (es != Acad::eEndOfFile)
        return Acad::eInvalidResBuf;

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::dxfOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDbAdeskLogoStyle::dxfOutFields(AcDbDxfFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxRleDbDictRecord::dxfOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(AcDb::kDxfSubclass, this->desc()->name());

    filer->writeItem(kDxfLabel, static_cast<const TCHAR*>(m_label));
    filer->writeItem(kDxfSolidFill, static_cast<int>(m_solidFill));
    filer->writeItem(kDxfTextStyle, m_textStyleId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::subSetDatabaseDefaults
**      if text style id hasn't yet been initialized, then set it to be
**  whatever the current textstyle is for this database.
**
**  **jma
**
*************************************/

void
ArxRleDbAdeskLogoStyle::subSetDatabaseDefaults(AcDbDatabase* pDb)
{
        // get past ARX bug of calling this on Undo/Redo
        // without opening for Write!  See AecDbAdeskLogo.cpp
        // for details.
    if (isWriteEnabled() == Adesk::kFalse)
        return;

    ASSERT(pDb != NULL);
    if (m_textStyleId == AcDbObjectId::kNull)
        m_textStyleId = pDb->textstyle();
}

/****************************************************************************
**
**  ArxRleDbAdeskLogoStyle::getStandardStyle
**		look up the style "STANDARD" so that we can set it as the default
**	logoStyle for new objects.
**
**  **jma
**
*************************************/

AcDbObjectId
ArxRleDbAdeskLogoStyle::getStandardStyle(AcDbDatabase* db, bool makeIfNotThere)
{
    Acad::ErrorStatus es;
    AcDbObjectId styleId;
    AcDbDictionary* dict;

    const TCHAR* standardStrPtr = acdbGetReservedString(AcDb::kStandard, false);
    ASSERT(standardStrPtr != NULL);
    
    dict = ArxRleUtils::openDictionaryForRead(m_dictName, db);
    if (dict) {
        es = dict->getAt(standardStrPtr, styleId);
        dict->close();

        if (es == Acad::eOk)
            return styleId;

        if (makeIfNotThere == false)
            return AcDbObjectId::kNull;
    }

        // wasn't already there, so we need to make it
    dict = ArxRleUtils::openDictionaryForWrite(m_dictName, true, db);
    if (dict) {
        ArxRleDbAdeskLogoStyle* newRec = new ArxRleDbAdeskLogoStyle;
        es = dict->setAt(standardStrPtr, newRec, styleId);
        dict->close();
        if (es == Acad::eOk) {
            newRec->close();
            return styleId;
        }
        else {
            acutPrintf(_T("\nERROR: Could not add new ArxRleDbAdeskLogoStyle (%s)"), ArxRleUtils::rxErrorStr(es));
            delete newRec;
        }
    }

    return AcDbObjectId::kNull;
}



