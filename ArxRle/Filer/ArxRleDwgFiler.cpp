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

#include "ArxRleDwgFiler.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleRbList.h"



ACRX_CONS_DEFINE_MEMBERS(ArxRleDwgFiler, AcDbDwgFiler, 0);

/****************************************************************************
**
**  ArxRleDwgFiler::ArxRleDwgFiler
**
**  **jma
**
*************************************/

ArxRleDwgFiler::ArxRleDwgFiler()
:   m_stat(Acad::eOk),
    m_filerType(AcDb::kCopyFiler)
{
}

/****************************************************************************
**
**  ArxRleDwgFiler::~ArxRleDwgFiler
**
**  **jma
**
*************************************/

ArxRleDwgFiler::~ArxRleDwgFiler()
{
}

/****************************************************************************
**
**  ArxRleDwgFiler::readBytes
**
**  **jma
**
*************************************/

Acad::ErrorStatus ArxRleDwgFiler::readBytes(void *buf, Adesk::UIntPtr cnt)
{
    m_str = _T("");
    printIt(_T("readBytes"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readAddress
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readAddress(void** pp)
{
    m_str = _T("");
    printIt(_T("readAddress"));

    return Acad::eOk;
}


/****************************************************************************
**
**  ArxRleDwgFiler::readString
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readString(ACHAR **pVal)
{
    m_str = _T("");
    printIt(_T("readString"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxRleDwgFiler::readString(AcString & s)
{
    m_str = _T("");
    printIt(_T("readString(AcString &)"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readBChunk
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readBChunk(ads_binary *pVal)
{
    m_str = _T("");
    printIt(_T("readBChunk"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readAcDbHandle
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readAcDbHandle(AcDbHandle *pVal)
{
    m_str = _T("");
    printIt(_T("readAcDbHandle"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxRleDwgFiler::readInt64(Adesk::Int64 *pVal)
{
    m_str = _T("");
    printIt(_T("readInt64"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readInt32
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readInt32(Adesk::Int32 *pVal)
{
    m_str = _T("");
    printIt(_T("readInt32"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readInt16
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readInt16(Adesk::Int16 *pVal)
{
    m_str = _T("");
    printIt(_T("readInt16"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxRleDwgFiler::readInt8(Adesk::Int8 *pVal)
{
    m_str = _T("");
    printIt(_T("readInt8"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxRleDwgFiler::readUInt64(Adesk::UInt64 *pVal)
{
    m_str = _T("");
    printIt(_T("readUInt64"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readUInt32
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readUInt32(Adesk::UInt32 *pVal)
{
    m_str = _T("");
    printIt(_T("readUInt32"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readUInt16
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readUInt16(Adesk::UInt16 *pVal)
{
    m_str = _T("");
    printIt(_T("readUInt16"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readUInt8
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readUInt8(Adesk::UInt8 *pVal)
{
    m_str = _T("");
    printIt(_T("readUInt8"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readBoolean
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readBoolean(Adesk::Boolean *pVal)
{
    m_str = _T("");
    printIt(_T("readBoolean"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readBool
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readBool(bool *pVal)
{
    m_str = _T("");
    printIt(_T("readBool"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readHardOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readHardOwnershipId(AcDbHardOwnershipId* pId)
{
    m_str = _T("");
    printIt(_T("readHardOwnershipId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readSoftOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readSoftOwnershipId(AcDbSoftOwnershipId* pId)
{
    m_str = _T("");
    printIt(_T("readSoftOwnershipId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readHardPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readHardPointerId(AcDbHardPointerId* pId)
{
    m_str = _T("");
    printIt(_T("readHardPointerId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readSoftPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readSoftPointerId(AcDbSoftPointerId* pId)
{
    m_str = _T("");
    printIt(_T("readSoftPointerId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readDouble
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readDouble(double *pVal)
{
    m_str = _T("");
    printIt(_T("readDouble"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readPoint2d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readPoint2d(AcGePoint2d *pVal)
{
    m_str = _T("");
    printIt(_T("readPoint2d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readPoint3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readPoint3d(AcGePoint3d *pVal)
{
    m_str = _T("");
    printIt(_T("readPoint3d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readVector2d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readVector2d(AcGeVector2d *pVal)
{
    m_str = _T("");
    printIt(_T("readVector2d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readVector3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readVector3d(AcGeVector3d *pVal)
{
    m_str = _T("");
    printIt(_T("readVector3d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::readScale3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::readScale3d(AcGeScale3d *pVal)
{
    m_str = _T("");
    printIt(_T("readScale3d"));

    return Acad::eOk;
}



/****************************************************************************
**
**  ArxRleDwgFiler::writeBytes
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeBytes(const void *buf, Adesk::UIntPtr cnt)
{
    m_str.Format(_T("cnt = %ld"), cnt);
    printIt(_T("writeBytes"));

    return Acad::eOk;    
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeAddress
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeAddress(const void* p)
{
    m_str = "";
    m_str.Format(_T("%p"), p);
    printIt(_T("writeAddress"));

    return Acad::eOk;
}


/****************************************************************************
**
**  ArxRleDwgFiler::writeString
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeString(const ACHAR *pVal)
{
    m_str.Format(_T("\"%s\""), pVal);
    printIt(_T("writeString"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxRleDwgFiler::writeString(const AcString &s)
{
    m_str.Format(_T("\"%s\""), s.kTCharPtr());
    printIt(_T("writeString"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeBChunk
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeBChunk(const ads_binary &val)
{
    CString hexStr;

    bytesToHexStr(val.buf, val.clen, hexStr);
    m_str.Format(_T("%s"), hexStr);
    printIt(_T("writeBChunk"));

    return Acad::eOk;
  }

/****************************************************************************
**
**  ArxRleDwgFiler::writeAcDbHandle
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeAcDbHandle(const AcDbHandle& val)
{
    TCHAR tmpStr[256];
    val.getIntoAsciiBuffer(tmpStr);

    m_str.Format(_T("%s"), tmpStr);
    printIt(_T("writeAcDbHandle"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxRleDwgFiler::writeInt64(Adesk::Int64 val)
{
    m_str.Format(_T("%ld"), val);
    printIt(_T("writeInt64"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeInt32
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeInt32(Adesk::Int32 val)
{
    m_str.Format(_T("%ld"), val);
    printIt(_T("writeInt32"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeInt16
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeInt16(Adesk::Int16 val)
{
    m_str.Format(_T("%d"), val);
    printIt(_T("writeInt16"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxRleDwgFiler::writeInt8(Adesk::Int8 val)
{
    m_str.Format(_T("%d"), val);
    printIt(_T("writeInt8"));

    return Acad::eOk;
}

Acad::ErrorStatus
ArxRleDwgFiler::writeUInt64(Adesk::UInt64 val)
{
    m_str.Format(_T("%ld"), val);
    printIt(_T("writeUInt64"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeUInt32
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeUInt32(Adesk::UInt32 val)
{
    m_str.Format(_T("%lu"), val);
    printIt(_T("writeUInt32"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeUInt16
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeUInt16(Adesk::UInt16 val)
{
    m_str.Format(_T("%hu"), val);
    printIt(_T("writeUInt16"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeUInt8
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeUInt8(Adesk::UInt8 val)
{
    m_str.Format(_T("%u"), val);
    printIt(_T("writeUInt8"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeBoolean
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeBoolean(Adesk::Boolean val)
{
    ArxRleUtils::booleanToStr(val, m_str);
    printIt(_T("writeBoolean"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeBool
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeBool(bool val)
{
    ArxRleUtils::booleanToStr(val, m_str);
    printIt(_T("writeBool"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeHardOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeHardOwnershipId(const AcDbHardOwnershipId& id)
{
    objIdToStr(id, m_str);
    printIt(_T("writeHardOwnId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeSoftOwnershipId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeSoftOwnershipId(const AcDbSoftOwnershipId& id)
{
    objIdToStr(id, m_str);
    printIt(_T("writeSoftOwnId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeHardPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeHardPointerId(const AcDbHardPointerId& id)
{
    objIdToStr(id, m_str);
    printIt(_T("writeHardPtrId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeSoftPointerId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeSoftPointerId(const AcDbSoftPointerId& id)
{
    objIdToStr(id, m_str);
    printIt(_T("writeSoftPtrId"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeDouble
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeDouble(double val)
{
    m_str.Format(_T("%lf"), val);
    printIt(_T("writeDouble"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writePoint2d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writePoint2d(const AcGePoint2d& val)
{
    ArxRleUtils::ptToStr(val, m_str);
    printIt(_T("writePoint2d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writePoint3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writePoint3d(const AcGePoint3d& val)
{
    ArxRleUtils::ptToStr(val, m_str);
    printIt(_T("writePoint3d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeVector2d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeVector2d(const AcGeVector2d& val)
{
    ArxRleUtils::vectorToStr(val, m_str);
    printIt(_T("writeVector2d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeVector3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeVector3d(const AcGeVector3d& val)
{
    ArxRleUtils::vectorToStr(val, m_str);
    printIt(_T("writeVector3d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::writeScale3d
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleDwgFiler::writeScale3d(const AcGeScale3d& val)
{
    m_str.Format(_T("%lf, %lf, %lf"), val.sx, val.sy, val.sz);
    printIt(_T("writeScale3d"));

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::tell
**
**  **jma
**
*************************************/

Adesk::Int64 ArxRleDwgFiler::tell() const
{
    acutPrintf(_T("\nArxRleDwgFiler::tell()"));
    return 0L;
}

/****************************************************************************
**
**  ArxRleDwgFiler::seek
**
**  **jma
**
*************************************/

Acad::ErrorStatus ArxRleDwgFiler::seek(Adesk::Int64 nPos, int nMode)
{
    acutPrintf(_T("\nArxRleDwgFiler::seek()"));
    return Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::filerStatus
**
**  **jma
**
*************************************/

Acad::ErrorStatus ArxRleDwgFiler::filerStatus(void) const
{
    return m_stat;
}

/****************************************************************************
**
**  ArxRleDwgFiler::filerType
**
**  **jma
**
*************************************/

AcDb::FilerType
ArxRleDwgFiler::filerType(void) const
{
     return m_filerType;
}

/****************************************************************************
**
**  ArxRleDwgFiler::setFilerStatus
**
**  **jma
**
*************************************/

void
ArxRleDwgFiler::setFilerStatus(Acad::ErrorStatus status)
{
    m_stat = status;
}

/****************************************************************************
**
**  ArxRleDwgFiler::resetFilerStatus
**
**  **jma
**
*************************************/

void
ArxRleDwgFiler::resetFilerStatus(void)
{
    m_stat = Acad::eOk;
}

/****************************************************************************
**
**  ArxRleDwgFiler::printIt
**
**  **jma
**
*************************************/

void
ArxRleDwgFiler::printIt(LPCTSTR labelStr)
{
    acutPrintf(_T("\n%-15s %s"), labelStr, m_str);
}

/****************************************************************************
**
**  ArxRleDwgFiler::objIdToStr
**
**  **jma
**
*************************************/

void
ArxRleDwgFiler::objIdToStr(const AcDbObjectId& objId, CString& str)
{
    AcDbObject* obj;
    Acad::ErrorStatus es = acdbOpenAcDbObject(obj, objId, AcDb::kForRead, Adesk::kTrue);
    if (es == Acad::eOk) {
        CString tmpStr;
        str.Format(_T("<%-25s %-4s>"),
                    ArxRleUtils::objToClassStr(obj),
                    ArxRleUtils::objToHandleStr(obj, tmpStr));

        if (obj->isErased())
            str += CString(_T("  ERASED"));

        obj->close();
    }
    else {
        str = ArxRleUtils::rxErrorStr(es);
    }
}
