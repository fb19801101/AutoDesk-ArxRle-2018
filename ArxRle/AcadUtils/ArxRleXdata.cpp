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

#include "ArxRleXdata.h"
#include "ArxRleUtils.h"
#include "AcadStr.h"




/////////////////////////////////////////////////////////////////////////////
/////////////////////////////  ArxRleAppXdata  //////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  ArxRleAppXdata::ArxRleAppXdata
**
**  **jma
**
*************************************/

ArxRleAppXdata::ArxRleAppXdata(LPCTSTR appName, AcDbDatabase* db)
:   m_xdata(NULL)
{
    ASSERT(db != NULL);

        // make sure application name is registered
    AcDbRegAppTable* regAppTbl;
    Acad::ErrorStatus es = db->getSymbolTable(regAppTbl, AcDb::kForRead);
    if (es == Acad::eOk) {
        if (regAppTbl->has(appName) == false) {
            es = regAppTbl->upgradeOpen();
            if (es == Acad::eOk) {
                AcDbRegAppTableRecord* newRec = new AcDbRegAppTableRecord;
                es = newRec->setName(appName);
                if (es == Acad::eOk) {
                    es = regAppTbl->add(newRec);
                    if (es == Acad::eOk)
                        newRec->close();
                    else {
                        ASSERT(0);
                        delete newRec;
                    }
                }
                else {
                    ASSERT(0);
                    delete newRec;
                }
            }
            else {
                ASSERT(0);
            }
        }
        regAppTbl->close();
    }
    else {
        ASSERT(0);
    }

        // add 1001 code for application name
    m_appNameNode = acutNewRb(1001);
    acutNewString(appName, m_appNameNode->resval.rstring);
}

/****************************************************************************
**
**  ArxRleAppXdata::~ArxRleAppXdata
**
**  **jma
**
*************************************/

ArxRleAppXdata::~ArxRleAppXdata()
{
    if (m_appNameNode)
        acutRelRb(m_appNameNode);
}

/****************************************************************************
**
**  ArxRleAppXdata::findItemStart
**      look to see if a tag already exists in this chain.  If so,
**  return a pointer to the first node of the tag, and a lag pointer
**  to the node before the tag, in case we need to chop it out.
**
**  **jma
**
*************************************/

resbuf*
ArxRleAppXdata::findItemStart(int tag)
{
    int nestedLists = 0;
    resbuf* tmp = m_xdata.data();
    while (tmp) {
			// keep track of nested lists
        if (tmp->restype == 1002) {
            if (!_tcscmp(tmp->resval.rstring, AcadString::openBrace))
                nestedLists++;
            else if(!_tcscmp(tmp->resval.rstring, AcadString::endBrace))
                nestedLists--;
            tmp = tmp->rbnext;
        }
			// make sure it is not within a list and is not the int value
			// of another tag
        else if ((tmp->restype == 1070) && (nestedLists == 0)) {
            if (tmp->resval.rint == tag)
                return tmp;

				// skip around value of the tag
            if (tmp->rbnext) {
                tmp = tmp->rbnext;
                if (tmp->restype == 1002)
                    ;    // start of a list, do nothing
                else {        // skip next rb which is tag value
                    if (tmp->rbnext == NULL)
                        return NULL;    // never found it
                    tmp = tmp->rbnext;
                }
            }
            else
                return NULL;        // never found it
        }
        else
            tmp = tmp->rbnext;
    }
    return NULL;    // never found it
}

/****************************************************************************
**
**  ArxRleAppXdata::findItemEnd
**      find the last value node of a tagged xdata item.
**
**  **jma
**
*************************************/

resbuf*
ArxRleAppXdata::findItemEnd(resbuf* startPtr)
{
    int nestedLists = 0;
    resbuf* tmp = startPtr;

		// skip past tag node
    if (tmp->rbnext)
        tmp = tmp->rbnext;

    while (tmp) {
        if (tmp->restype == 1002) {
            if (!_tcscmp(tmp->resval.rstring, AcadString::openBrace))
                nestedLists++;
            else if (!_tcscmp(tmp->resval.rstring, AcadString::endBrace))
                nestedLists--;
        }
        if (nestedLists == 0)// found end of list or it was a single item, stop looking
            return(tmp);

        tmp = tmp->rbnext;
    }
    return NULL;
}

/****************************************************************************
**
**  ArxRleAppXdata::addTagNode
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::addTagNode(int tag)
{
    resbuf* tagNode = acutNewRb(1070);
    tagNode->resval.rint = static_cast<short>(tag);
    m_xdata.addTail(tagNode);
}

/****************************************************************************
**
**  ArxRleAppXdata::getGenericReal
**      generic function to get a real data type, but from different
**  DXF types
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getGenericReal(int tag, double& value, bool speakIfMissing, int dxfType)
{
    resbuf* itemPtr;

    if ((itemPtr = findItemStart(tag)) == NULL) {
        if (speakIfMissing)
            missingXdataTagWarning(tag);
        return false;
    }
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != dxfType)) {
            malformedXdataTagError(tag);
            return false;
        }
        else {
            value = itemPtr->rbnext->resval.rreal;
            return true;
        }
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::getGenericString
**      generic function to get a string data type, but from different
**  DXF types
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getGenericString(int tag, CString& value, bool speakIfMissing, int dxfType)
{
    resbuf* itemPtr;

    if ((itemPtr = findItemStart(tag)) == NULL) {
        if (speakIfMissing)
            missingXdataTagWarning(tag);
        return false;
    }
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != dxfType)) {
            malformedXdataTagError(tag);
            return false;
        }
        else {
            value = itemPtr->rbnext->resval.rstring;
            return true;
        }
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::getHandle
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getHandle(int tag, AcDbHandle& value, bool speakIfMissing)
{
    CString handleStr;
    if (getGenericString(tag, handleStr, speakIfMissing, 1005) == true) {
        value = handleStr;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleAppXdata::getInteger
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getInteger(int tag, int& value, bool speakIfMissing)
{
    resbuf* itemPtr;

    if ((itemPtr = findItemStart(tag)) == NULL) {
        if (speakIfMissing)
            missingXdataTagWarning(tag);
        return false;
    }
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != 1070)) {
            if (speakIfMissing)
                malformedXdataTagError(tag);
            return false;
        }
        else {
            value = itemPtr->rbnext->resval.rint;
            return true;
        }
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::getLong
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getLong(int tag, long& value, bool speakIfMissing)
{
    resbuf* itemPtr;

    if ((itemPtr = findItemStart(tag)) == NULL) {
        if (speakIfMissing)
            missingXdataTagWarning(tag);
        return false;
    }
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != 1071)) {
            if (speakIfMissing)
                malformedXdataTagError(tag);
            return false;
        }
        else {
            value = itemPtr->rbnext->resval.rlong;
            return true;
        }
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::getGenericPoint
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getGenericPoint(int tag, AcGePoint3d& value, bool speakIfMissing, int dxfType)
{
    resbuf* itemPtr;

    if ((itemPtr = findItemStart(tag)) == NULL) {
        if (speakIfMissing)
            missingXdataTagWarning(tag);
        return false;
    }
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != dxfType)) {
            malformedXdataTagError(tag);
            return false;
        }
        else {
            value = asPnt3d(itemPtr->rbnext->resval.rpoint);
            return true;
        }
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::getDirection
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getDirection(int tag, AcGeVector3d& value, bool speakIfMissing)
{
    resbuf* itemPtr;

    if ((itemPtr = findItemStart(tag)) == NULL) {
        if (speakIfMissing)
            missingXdataTagWarning(tag);
        return false;
    }
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != 1013)) {
            malformedXdataTagError(tag);
            return false;
        }
        else {
            value = asVec3d(itemPtr->rbnext->resval.rpoint);
            return true;
        }
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::setInteger
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setInteger(int tag, int value)
{
    resbuf* itemPtr;

		// if it doesn't already exist, add tag node
		// and value node
    if ((itemPtr = findItemStart(tag)) == NULL) {
        addTagNode(tag);
        itemPtr = acutNewRb(1070);
        itemPtr->resval.rint = static_cast<short>(value);
        m_xdata.addTail(itemPtr);
    }
		// if it does exist, just set to new value
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != 1070)) {
            malformedXdataTagError(tag);
            return;
        }
        itemPtr->rbnext->resval.rint = static_cast<short>(value);
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::setGenericReal
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setGenericReal(int tag, double value, int dxfType)
{
    resbuf* itemPtr;

		// if it doesn't already exist, add tag node
		// and value node
    if ((itemPtr = findItemStart(tag)) == NULL) {
        addTagNode(tag);

        itemPtr = acutNewRb(dxfType);
        itemPtr->resval.rreal = value;
        m_xdata.addTail(itemPtr);
    }
		// if it does exist, just set to new value
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != dxfType)) {
            malformedXdataTagError(tag);
            return;
        }
        itemPtr->rbnext->resval.rreal = value;
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::setLong
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setLong(int tag, long value)
{
    resbuf* itemPtr;

		// if it doesn't already exist, add tag node
		// and value node
    if ((itemPtr = findItemStart(tag)) == NULL) {
        addTagNode(tag);

        itemPtr = acutNewRb(1071);
        itemPtr->resval.rlong = value;
        m_xdata.addTail(itemPtr);
    }
		// if it does exist, just set to new value
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != 1071)) {
            malformedXdataTagError(tag);
            return;
        }
        itemPtr->rbnext->resval.rlong = value;
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::setGenericString
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setGenericString(int tag, const TCHAR* value, int dxfType)
{
    resbuf* itemPtr;

		// if it doesn't already exist, add tag node
		// and value node
    if ((itemPtr = findItemStart(tag)) == NULL) {
        addTagNode(tag);

        itemPtr = acutNewRb(dxfType);
        acutNewString(value,itemPtr->resval.rstring);

        m_xdata.addTail(itemPtr);
    }
		// if it does exist, just set to new value
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != dxfType)) {
            malformedXdataTagError(tag);
            return;
        }

        if (itemPtr->rbnext->resval.rstring)
            acutDelString(itemPtr->rbnext->resval.rstring);
        acutNewString(value,itemPtr->rbnext->resval.rstring);
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::setLayer
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setLayer(int tag, const TCHAR* value)
{
    bool isValid = ArxRleUtils::symbolExists(AcDbLayerTableRecord::desc(), value, acdbHostApplicationServices()->workingDatabase());
    ASSERT(isValid == true);

    if (isValid)
        setGenericString(tag, value, 1003);
    else {
        acutPrintf(_T("\nERROR: Invalid layer %s"), value);
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::setHandle
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setHandle(int tag, const AcDbHandle& value)
{
    TCHAR handleStr[256];

    value.getIntoAsciiBuffer(handleStr);
    setGenericString(tag, handleStr, 1005);
}

/****************************************************************************
**
**  ArxRleAppXdata::setGenericPoint
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setGenericPoint(int tag, const AcGePoint3d& value, int dxfType)
{
    resbuf* itemPtr;

		// if it doesn't already exist, add tag node
		// and value node
    if ((itemPtr = findItemStart(tag)) == NULL) {
        addTagNode(tag);

        itemPtr = acutNewRb(dxfType);
        itemPtr->resval.rpoint[0] = value.x;
        itemPtr->resval.rpoint[1] = value.y;
        itemPtr->resval.rpoint[2] = value.z;
        m_xdata.addTail(itemPtr);
    }
		// if it does exist, just set to new value
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != dxfType)) {
            malformedXdataTagError(tag);
            return;
        }

        itemPtr->rbnext->resval.rpoint[0] = value.x;
        itemPtr->rbnext->resval.rpoint[1] = value.y;
        itemPtr->rbnext->resval.rpoint[2] = value.z;
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::setDirection
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setDirection(int tag, const AcGeVector3d& value)
{
    resbuf* itemPtr;

		// if it doesn't already exist, add tag node
		// and value node
    if ((itemPtr = findItemStart(tag)) == NULL) {
        addTagNode(tag);

        itemPtr = acutNewRb(1013);
        itemPtr->resval.rpoint[0] = value.x;
        itemPtr->resval.rpoint[1] = value.y;
        itemPtr->resval.rpoint[2] = value.z;
        m_xdata.addTail(itemPtr);
    }
		// if it does exist, just set to new value
    else {
        if ((itemPtr->rbnext == NULL) || (itemPtr->rbnext->restype != 1013)) {
            malformedXdataTagError(tag);
            return;
        }

        itemPtr->rbnext->resval.rpoint[0] = value.x;
        itemPtr->rbnext->resval.rpoint[1] = value.y;
        itemPtr->rbnext->resval.rpoint[2] = value.z;
    }
}

/****************************************************************************
**
**  ArxRleAppXdata::detach
**
**  **jma
**
*************************************/

resbuf*
ArxRleAppXdata::detach(int tag)
{
    resbuf* startPtr = findItemStart(tag);
    if (startPtr == NULL)
        return(NULL);    // not on the list

    ASSERT(startPtr->rbnext != NULL);
    if (startPtr->rbnext == NULL) {
        malformedXdataTagError(tag);
        return(NULL);
    }

    resbuf* endPtr = findItemEnd(startPtr);
    ASSERT(endPtr != NULL);
    if (endPtr == NULL) {
        malformedXdataTagError(tag);
        return(NULL);
    }

    return m_xdata.detach(startPtr, endPtr);
}

/****************************************************************************
**
**  ArxRleAppXdata::remove
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::remove(int tag)
{
    resbuf* rb = detach(tag);
    if (rb != NULL) {
        acutRelRb(rb);
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleAppXdata::isBeginList
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::isBeginList(resbuf* rb)
{
    return (rb->restype == 1002) && (!_tcscmp(rb->resval.rstring, AcadString::openBrace));
}

/****************************************************************************
**
**  ArxRleAppXdata::isEndList
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::isEndList(resbuf* rb)
{
    return (rb->restype == 1002) && (!_tcscmp(rb->resval.rstring, AcadString::endBrace));
}

/****************************************************************************
**
**  ArxRleAppXdata::getList
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getList(int tag, ArxRleXdataList& xdataList)
{
    xdataList.removeAll();    // remove one if it is already there

    resbuf* startPtr = findItemStart(tag);
    resbuf* tagPtr = startPtr;    // keep original start point
    if (startPtr == NULL)
        return false;    // not on the list

    ASSERT(startPtr->rbnext != NULL);
    if (startPtr->rbnext == NULL) {
        malformedXdataTagError(tag);
        return false;
    }
    // skip past tag, ensure that it is an open brace
    startPtr = startPtr->rbnext;
    ASSERT(isBeginList(startPtr));
    if (isBeginList(startPtr) == false) {
        malformedXdataTagError(tag);
        return false;
    }
    // find end of item, ensure that it is an end brace
    resbuf* endPtr = findItemEnd(tagPtr);
    ASSERT(endPtr != NULL);
    if (endPtr == NULL){
        malformedXdataTagError(tag);
        return false;
    }
    ASSERT(isEndList(endPtr));
    if (isEndList(endPtr)== false) {
        malformedXdataTagError(tag);
        return false;
    }

    ArxRleRbList xdata(duplicateResbufChain(startPtr, endPtr));
    xdata.removeHead();    // remove opening brace
    xdata.removeTail();    // remove ending brace
    xdataList.adoptResbufChain(xdata.orphanData());

    return true;
}

/****************************************************************************
**
**  ArxRleAppXdata::detachList
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::detachList(int tag, ArxRleXdataList& xdataList)
{
    resbuf* startPtr = detach(tag);
    if(startPtr == NULL)
        return false;

    ASSERT(startPtr->rbnext != NULL);
    ASSERT(isBeginList(startPtr->rbnext));
    if ((startPtr->rbnext == NULL) || (isBeginList(startPtr->rbnext) == false)) {
        malformedXdataTagError(tag);
        return false;
    }
    resbuf* endPtr = tailOfResbufChain(startPtr);

    ASSERT(endPtr != NULL);
    ASSERT(isEndList(endPtr));
    if ((endPtr == NULL) || (isEndList(endPtr) == false)) {
        malformedXdataTagError(tag);
        return false;
    }

    ArxRleRbList xdata(startPtr);      // adopts the resbuf
    xdata.removeHead();            // remove tag
    xdata.removeHead();            // remove opening brace
    xdata.removeTail();            // remove ending brace
    xdataList.adoptResbufChain(xdata.orphanData());
    return true;
}

/****************************************************************************
**
**  ArxRleAppXdata::setList
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setList(int tag, ArxRleXdataList& xdataList)
{
    remove(tag);    // remove one if it is already there

    ArxRleRbList appendList(duplicateResbufChain(xdataList.m_xdata.data()));
    resbuf* newNode;

		// add the opening brace
    newNode = acutNewRb(1002);
    acutNewString(AcadString::openBrace,newNode->resval.rstring);
    appendList.addHead(newNode);

		// add the end brace
    newNode = acutNewRb(1002);
    acutNewString(AcadString::endBrace,newNode->resval.rstring);
    appendList.addTail(newNode);

		// put tag on the front
    newNode = acutNewRb(1070);
    newNode->resval.rint = static_cast<short>(tag);
    appendList.addHead(newNode);

		// glue onto the xdata
    m_xdata.append(appendList);
}

/****************************************************************************
**
**  ArxRleAppXdata::adoptResbufChain
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::adoptResbufChain(resbuf* xdata)
{
    resbuf* tmp;

		// empty previous list
    m_xdata.removeAll();

		// pop -3 code off if it exists(should never happen in Rx)
    if (xdata &&(xdata->restype == -3)) {
        tmp = xdata;
        xdata = xdata->rbnext;
        tmp->rbnext = NULL;
        acutRelRb(tmp);
    }
		// pop 1001 code off if it exists
    if (xdata &&(xdata->restype == 1001)) {
        tmp = xdata;
        xdata = xdata->rbnext;
        tmp->rbnext = NULL;
        acutRelRb(tmp);
    }

    m_xdata.adoptData(xdata);
}

/****************************************************************************
**
**  ArxRleAppXdata::getXdata
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::getXdata(AcDbObject* obj)
{
    ASSERT(obj != NULL);

		// empty previous list
    m_xdata.removeAll();
    resbuf* xdata = obj->xData(getAppName());
    if (xdata != NULL)
        m_xdata.adoptData(xdata);
}

/****************************************************************************
**
**  ArxRleAppXdata::setXdata
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxRleAppXdata::setXdata(AcDbObject* obj)
{
    ASSERT(obj != NULL);
    ASSERT(obj->isWriteEnabled());

		// hook all the components together into one list
    m_appNameNode->rbnext = m_xdata.data();

		// set in object xdata
    Acad::ErrorStatus es = obj->setXData(m_appNameNode);

		// break them apart again
    m_appNameNode->rbnext = NULL;

    if (es != Acad::eOk) {
        acutPrintf(_T("\nERROR: could not set Xdata (%s)"), ArxRleUtils::rxErrorStr(es));
    }
    return es;
}

/****************************************************************************
**
**  ArxRleAppXdata::allocResbufChain
**      use when you need a full copy of the entire resbuf chain
**  including the 1001 appname node.  Does NOT include the -3 marker.
**
**  **jma
**
*************************************/

resbuf*
ArxRleAppXdata::allocResbufChain()
{
    resbuf* xdata = duplicateResbufChain(m_appNameNode);
    resbuf* xdataContent = duplicateResbufChain(m_xdata.data());

    // connect them together
    xdata->rbnext = xdataContent;
    return xdata;
}

/****************************************************************************
**
**  ArxRleAppXdata::getAppName
**
**  **jma
**
*************************************/

const TCHAR*
ArxRleAppXdata::getAppName()const
{
    ASSERT(m_appNameNode != NULL);
    return m_appNameNode->resval.rstring;
}

/****************************************************************************
**
**  ArxRleAppXdata::getReal
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getReal(int tag, double& value, bool speakIfMissing)
{
    return getGenericReal(tag, value, speakIfMissing, 1040);
}

/****************************************************************************
**
**  ArxRleAppXdata::getDistance
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getDistance(int tag, double& value, bool speakIfMissing)
{
    return getGenericReal(tag, value, speakIfMissing, 1041);
}

/****************************************************************************
**
**  ArxRleAppXdata::getScale
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getScale(int tag, double& value, bool speakIfMissing)
{
    return getGenericReal(tag, value, speakIfMissing, 1042);
}

/****************************************************************************
**
**  ArxRleAppXdata::getString
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getString(int tag, CString& value, bool speakIfMissing)
{
    return getGenericString(tag, value, speakIfMissing, 1000);
}

/****************************************************************************
**
**  ArxRleAppXdata::getLayer
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getLayer(int tag, CString& value, bool speakIfMissing)
{
    return getGenericString(tag, value, speakIfMissing, 1003);
}

/****************************************************************************
**
**  ArxRleAppXdata::getPoint
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getPoint(int tag, AcGePoint3d& value, bool speakIfMissing)
{
    return getGenericPoint(tag, value, speakIfMissing, 1010);
}

/****************************************************************************
**
**  ArxRleAppXdata::getPosition
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getPosition(int tag, AcGePoint3d& value, bool speakIfMissing)
{
    return getGenericPoint(tag, value, speakIfMissing, 1011);
}

/****************************************************************************
**
**  ArxRleAppXdata::getDisplacement
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::getDisplacement(int tag, AcGePoint3d& value, bool speakIfMissing)
{
    return getGenericPoint(tag, value, speakIfMissing, 1012);
}

/****************************************************************************
**
**  ArxRleAppXdata::setReal
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setReal(int tag, double value)
{
    setGenericReal(tag, value, 1040);
}

/****************************************************************************
**
**  ArxRleAppXdata::setDistance
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setDistance(int tag, double value)
{
    setGenericReal(tag, value, 1041);
}

/****************************************************************************
**
**  ArxRleAppXdata::setScale
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setScale(int tag, double value)
{
    setGenericReal(tag, value, 1042);
}

/****************************************************************************
**
**  ArxRleAppXdata::setString
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setString(int tag, LPCTSTR value)
{
    setGenericString(tag, value, 1000);
}

/****************************************************************************
**
**  ArxRleAppXdata::setPoint
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setPoint(int tag, const AcGePoint3d& value)
{
    setGenericPoint(tag, value, 1010);
}

/****************************************************************************
**
**  ArxRleAppXdata::setPosition
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setPosition(int tag, const AcGePoint3d& value)
{
    setGenericPoint(tag, value, 1011);
}

/****************************************************************************
**
**  ArxRleAppXdata::setDisplacement
**
**  **jma
**
*************************************/

void
ArxRleAppXdata::setDisplacement(int tag, const AcGePoint3d& value)
{
    setGenericPoint(tag, value, 1012);
}

/****************************************************************************
**
**  ArxRleAppXdata::isEmpty
**
**  **jma
**
*************************************/

bool
ArxRleAppXdata::isEmpty()
{
    return m_xdata.isEmpty();
}

/////////////////////////////////////////////////////////////////////////////
////////////////////////////  ArxRleXdataList  //////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  ArxRleXdataList::ArxRleXdataList
**
**  **jma
**
*************************************/

ArxRleXdataList::ArxRleXdataList()
{
}

/****************************************************************************
**
**  ArxRleXdataList::~ArxRleXdataList
**
**  **jma
**
*************************************/

ArxRleXdataList::~ArxRleXdataList()
{
}

/****************************************************************************
**
**  ArxRleXdataList::appendInteger
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendInteger(int value)
{
    resbuf* newNode = acutNewRb(1070);

    newNode->resval.rint = static_cast<short>(value);
    m_xdata.addTail(newNode);
}

/****************************************************************************
**
**  ArxRleXdataList::appendLong
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendLong(long value)
{
    resbuf* newNode = acutNewRb(1071);
    newNode->resval.rlong = value;
    m_xdata.addTail(newNode);
}

/****************************************************************************
**
**  ArxRleXdataList::appendGenericReal
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendGenericReal(double value, int dxfType)
{
    resbuf* newNode = acutNewRb(dxfType);
    newNode->resval.rreal = value;
    m_xdata.addTail(newNode);
}

/****************************************************************************
**
**  ArxRleXdataList::appendString
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendString(const TCHAR* value)
{
    resbuf* newNode = acutNewRb(1000);
    acutNewString(value, newNode->resval.rstring);
    m_xdata.addTail(newNode);
}

/****************************************************************************
**
**  ArxRleXdataList::appendLayer
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendLayer(const TCHAR* value)
{
    bool isValid = ArxRleUtils::symbolExists(AcDbLayerTableRecord::desc(), value,
						acdbHostApplicationServices()->workingDatabase());
    ASSERT(isValid == true);

    if (isValid) {
        resbuf* newNode = acutNewRb(1003);
        acutNewString(value, newNode->resval.rstring);
        m_xdata.addTail(newNode);
    }
    else {
        acutPrintf(_T("\nERROR: could not append layer %s in Xdata"), value);
    }
}

/****************************************************************************
**
**  ArxRleXdataList::appendHandle
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendHandle(const AcDbHandle& value)
{
    TCHAR handleStr[256];

    resbuf* newNode = acutNewRb(1005);
    value.getIntoAsciiBuffer(handleStr);
    acutNewString(handleStr, newNode->resval.rstring);
    m_xdata.addTail(newNode);
}

/****************************************************************************
**
**  ArxRleXdataList::appendGenericPoint
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendGenericPoint(const AcGePoint3d& value, int dxfType)
{
    resbuf* newNode = acutNewRb(dxfType);

    newNode->resval.rpoint[0] = value.x;
    newNode->resval.rpoint[1] = value.y;
    newNode->resval.rpoint[2] = value.z;

    m_xdata.addTail(newNode);
}

/****************************************************************************
**
**  ArxRleXdataList::appendDirection
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendDirection(const AcGeVector3d& value)
{
    resbuf* newNode = acutNewRb(1013);

    newNode->resval.rpoint[0] = value.x;
    newNode->resval.rpoint[1] = value.y;
    newNode->resval.rpoint[2] = value.z;

    m_xdata.addTail(newNode);
}

/****************************************************************************
**
**  ArxRleXdataList::appendReal
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendReal(double value)
{
    appendGenericReal(value, 1040);
}

/****************************************************************************
**
**  ArxRleXdataList::appendDirection
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendDistance(double value)
{
    appendGenericReal(value, 1041);
}

/****************************************************************************
**
**  ArxRleXdataList::appendDirection
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendScale(double value)
{
    appendGenericReal(value, 1042);
}

/****************************************************************************
**
**  ArxRleXdataList::appendPoint
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendPoint(const AcGePoint3d& value)
{
    appendGenericPoint(value, 1010);
}

/****************************************************************************
**
**  ArxRleXdataList::appendPosition
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendPosition(const AcGePoint3d& value)
{
    appendGenericPoint(value, 1011);
}

/****************************************************************************
**
**  ArxRleXdataList::appendDisplacement
**
**  **jma
**
*************************************/

void
ArxRleXdataList::appendDisplacement(const AcGePoint3d& value)
{
    appendGenericPoint(value, 1012);
}

/****************************************************************************
**
**  ArxRleXdataList::appendDisplacement
**
**  **jma
**
*************************************/

void
ArxRleXdataList::removeAll()
{
    m_xdata.removeAll();
}

/****************************************************************************
**
**  ArxRleXdataList::appendDisplacement
**    direct access to resbuf chain, use only if absolutely necessary
**  **jma
**
*************************************/

void
ArxRleXdataList::adoptResbufChain(resbuf* xdata)
{
    m_xdata.adoptData(xdata);
}

/****************************************************************************
**
**  ArxRleXdataList::appendDisplacement
**    direct access to resbuf chain, use only if absolutely necessary
**  **jma
**
*************************************/

resbuf*
ArxRleXdataList::orphanResbufChain()
{
    return(m_xdata.orphanData());
}

/////////////////////////////////////////////////////////////////////////////
////////////////////////  ArxRleXdataListIterator  //////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  ArxRleXdataListIterator::ArxRleXdataListIterator
**
**  **jma
**
*************************************/

ArxRleXdataListIterator::ArxRleXdataListIterator(ArxRleXdataList& xdata)
{
		// deal with raw resbufs only
    m_xdata = xdata.m_xdata.data();
    m_curPtr = m_xdata;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::~ArxRleXdataListIterator
**
**  **jma
**
*************************************/

ArxRleXdataListIterator::~ArxRleXdataListIterator()
{
    // somebody else owns the list, so just leave it alone
}

/****************************************************************************
**
**  ArxRleXdataListIterator::getInteger
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::getInteger(int& value)
{
    if (m_curPtr && (m_curPtr->restype == 1070)) {
        value = m_curPtr->resval.rint;
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::getLong
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::getLong(long& value)
{
    if (m_curPtr &&(m_curPtr->restype == 1071)) {
        value = m_curPtr->resval.rlong;
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::getString
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::getReal(double& value)
{
    return getGenericReal(value, 1040);
}

/****************************************************************************
**
**  ArxRleXdataListIterator::getString
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::getString(CString& value)
{
    return getGenericString(value, 1000);
}

/****************************************************************************
**
**  ArxRleXdataListIterator::getGenericReal
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::getGenericReal(double& value, int dxfType)
{
    if (m_curPtr && (m_curPtr->restype == dxfType)) {
        value = m_curPtr->resval.rreal;
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::getGenericString
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::getGenericString(CString& value, int dxfType)
{
    if (m_curPtr && (m_curPtr->restype == dxfType)) {
        value = m_curPtr->resval.rstring;
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::getHandle
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::getHandle(AcDbHandle& value)
{
    CString handleStr;
    if (getGenericString(handleStr, 1005)) {
        value = handleStr;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::getGenericPoint
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::getGenericPoint(AcGePoint3d& value, int dxfType)
{
    if (m_curPtr && (m_curPtr->restype == dxfType)) {
        value = asPnt3d(m_curPtr->resval.rpoint);
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::getDirection
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::getDirection(AcGeVector3d& value)
{
    if (m_curPtr && (m_curPtr->restype == 1013)) {
        value = asVec3d(m_curPtr->resval.rpoint);
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::setInteger
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::setInteger(int value)
{
    if (m_curPtr && (m_curPtr->restype == 1070)) {
        m_curPtr->resval.rint = static_cast<short>(value);
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::setLong
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::setLong(long value)
{
    if (m_curPtr && (m_curPtr->restype == 1071)) {
        m_curPtr->resval.rlong = value;
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::setGenericReal
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::setGenericReal(double value, int dxfType)
{
    if (m_curPtr && (m_curPtr->restype == dxfType)) {
        m_curPtr->resval.rreal = value;
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::setGenericString
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::setGenericString(const TCHAR* value, int dxfType)
{
    if (m_curPtr && (m_curPtr->restype == dxfType)) {
        if (m_curPtr->resval.rstring)
            acutDelString(m_curPtr->resval.rstring);
        acutNewString(value,m_curPtr->resval.rstring);
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::setLayer
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::setLayer(const TCHAR* value)
{
    bool isValid = ArxRleUtils::symbolExists(AcDbLayerTableRecord::desc(), value,
					acdbHostApplicationServices()->workingDatabase());
    ASSERT(isValid == true);

    if (isValid)
        return setGenericString(value, 1003);

    else {
        acutPrintf(_T("\nERROR: could not set layer %s in Xdata"), value);
        return false;
    }
}

/****************************************************************************
**
**  ArxRleXdataListIterator::setHandle
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::setHandle(const AcDbHandle& value)
{
    TCHAR handleStr[256];
    value.getIntoAsciiBuffer(handleStr);
    return setGenericString(handleStr, 1005);
}

/****************************************************************************
**
**  ArxRleXdataListIterator::setGenericPoint
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::setGenericPoint(const AcGePoint3d& value, int dxfType)
{
    if (m_curPtr && (m_curPtr->restype == dxfType)) {
        m_curPtr->resval.rpoint[0] = value.x;
        m_curPtr->resval.rpoint[1] = value.y;
        m_curPtr->resval.rpoint[2] = value.z;
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::setDirection
**
**  **jma
**
*************************************/

bool
ArxRleXdataListIterator::setDirection(const AcGeVector3d& value)
{
    if (m_curPtr && (m_curPtr->restype == 1013)) {
        m_curPtr->resval.rpoint[0] = value.x;
        m_curPtr->resval.rpoint[1] = value.y;
        m_curPtr->resval.rpoint[2] = value.z;
        m_curPtr = m_curPtr->rbnext;
        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleXdataListIterator::start
**    set to start position
**  **jma
**
*************************************/

void
ArxRleXdataListIterator::start()
{
    m_curPtr = m_xdata;
}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////  ArxRleAppXdataList  /////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/****************************************************************************
**
**  ArxRleAppXdataList::ArxRleAppXdataList
**
**  **jma
**
*************************************/

ArxRleAppXdataList::ArxRleAppXdataList(AcDbObject* const obj)
:	m_obj(obj),
	m_xdataStart(NULL)
{
    ASSERT(obj != NULL);

    divideApps(obj->xData());
}

/****************************************************************************
**
**  ArxRleAppXdataList::~ArxRleAppXdataList
**
**  **jma
**
*************************************/

ArxRleAppXdataList::~ArxRleAppXdataList()
{
    if (m_xdataStart != NULL)
        acutRelRb(m_xdataStart);

    removeAndDestroy();
}

/****************************************************************************
**
**  ArxRleAppXdataList::contains
**
**  **jma
**
*************************************/

bool
ArxRleAppXdataList::contains(LPCTSTR appName)const
{
    if (find(appName) == NULL)
        return false;
    else
        return true;
}

/****************************************************************************
**
**  ArxRleAppXdataList::find
**
**  **jma
**
*************************************/

int
ArxRleAppXdataList::find(LPCTSTR appName)const
{
    for (int i = 0; i < m_list.length(); i ++) {
        if (!_tcsicmp(appName, m_list[i]->getAppName()))    
            return i;
    }
    return -1;
}

/****************************************************************************
**
**  ArxRleAppXdataList::removeAndDestroy
**
**  **jma
**
*************************************/

void
ArxRleAppXdataList::removeAndDestroy(LPCTSTR appName)
{
    int pos = find(appName);
    if (pos != -1) {
        delete m_list[pos];
        m_list.removeAt(pos);
    }
}

/****************************************************************************
**
**  ArxRleAppXdataList::removeAndDestroy
**      remove and destroy all elements in the list
**
**  **jma
**
*************************************/

void
ArxRleAppXdataList::removeAndDestroy()
{
    for (ArxRleAppXdata * pDbgData : m_list)
        delete pDbgData;
    m_list.setLogicalLength(0);
}

/****************************************************************************
**
**  ArxRleAppXdataList::divideApps
**      xdata in resbuf format is in one big chain.  Divide it up
**  by application name into several different chains.
**
**  **jma
**
*************************************/

void
ArxRleAppXdataList::divideApps(resbuf* xdata)
{
    ArxRleAppXdata* newApp;

    resbuf* lagPtr = NULL;
    resbuf* appPtr = NULL;
    resbuf* tmp = xdata;
    while (tmp) {
			// if beginning of xdata, save this node for later use
        if (tmp->restype == -3) {
            m_xdataStart = tmp;
            tmp = tmp->rbnext;
            lagPtr = tmp;
            m_xdataStart->rbnext = NULL;
        }
			// start of a new application
        else if (tmp->restype == 1001) {
            if (appPtr != NULL) {            // already seen at least one app
                lagPtr->rbnext = NULL;       // detach this app's list
                newApp = new ArxRleAppXdata(appPtr->resval.rstring, m_obj->database());
                newApp->adoptResbufChain(appPtr);
                append(newApp);
            }
            appPtr = tmp;
            lagPtr = tmp;
            tmp = tmp->rbnext;
        }
        // at end of xdata
        else if (tmp->rbnext == NULL) {
            if (appPtr != NULL) {            // already seen at least one app
                newApp = new ArxRleAppXdata(appPtr->resval.rstring, m_obj->database());
                newApp->adoptResbufChain(appPtr);
                append(newApp);
            }
            tmp = NULL;    // done walking list
        }
			// just advance to next node, looking for next app...
        else {
            lagPtr = tmp;
            tmp = tmp->rbnext;
        }
    }
}

/****************************************************************************
**
**  ArxRleAppXdataList::append
**
**  **jma
**
*************************************/

void
ArxRleAppXdataList::append(ArxRleAppXdata* newApp)
{
    m_list.append(newApp);
}

/****************************************************************************
**
**  ArxRleAppXdataList::prepend
**
**  **jma
**
*************************************/

void
ArxRleAppXdataList::prepend(ArxRleAppXdata* newApp)
{
    m_list.insertAt(0,newApp);
}

/****************************************************************************
**
**  ArxRleAppXdataList::entries
**
**  **jma
**
*************************************/

int
ArxRleAppXdataList::entries() const
{
    return m_list.length();
}

/****************************************************************************
**
**  ArxRleAppXdataList::isEmpty
**
**  **jma
**
*************************************/

bool
ArxRleAppXdataList::isEmpty() const
{
    return m_list.isEmpty();
}

/****************************************************************************
**
**  ArxRleAppXdataList::at
**
**  **jma
**
*************************************/

ArxRleAppXdata*
ArxRleAppXdataList::at(int index)
{
    ASSERT(index >= 0 && index < m_list.length());
    return m_list[index];
}



/////////////////////////////////////////////////////////////////////////////
///////////////////////  ArxRleAppXdataListIterator  ////////////////////////
/////////////////////////////////////////////////////////////////////////////


/****************************************************************************
**
**  ArxRleAppXdataListIterator::ArxRleAppXdataListIterator
**
**  **jma
**
*************************************/

ArxRleAppXdataListIterator::ArxRleAppXdataListIterator(const ArxRleAppXdataList& list)
:   m_xdataList(list)
{
    if (m_xdataList.isEmpty())
        m_pos = -1;
    else 
        m_pos = 0;
}

/****************************************************************************
**
**  ArxRleAppXdataListIterator::ArxRleAppXdataListIterator
**
**  **jma
**
*************************************/

ArxRleAppXdataListIterator::~ArxRleAppXdataListIterator()
{
}

/****************************************************************************
**
**  ArxRleAppXdataListIterator::toFirst
**
**  **jma
**
*************************************/

void
ArxRleAppXdataListIterator::toFirst()
{
    if (m_xdataList.isEmpty())
        m_pos = -1;
    else 
        m_pos = 0;
}

/****************************************************************************
**
**  ArxRleAppXdataListIterator::toLast
**
**  **jma
**
*************************************/

void
ArxRleAppXdataListIterator::toLast()
{
    if (m_xdataList.isEmpty())
        m_pos = -1;
    else 
        m_pos = m_xdataList.m_list.length() - 1;
}

/****************************************************************************
**
**  ArxRleAppXdataListIterator::previous
**
**  **jma
**
*************************************/

void
ArxRleAppXdataListIterator::previous()
{
    m_pos --;
}

/****************************************************************************
**
**  ArxRleAppXdataListIterator::next
**
**  **jma
**
*************************************/

void
ArxRleAppXdataListIterator::next()
{
    m_pos ++;
    if (m_pos == m_xdataList.m_list.length())
        m_pos = -1;
}

/****************************************************************************
**
**  ArxRleAppXdataListIterator::item
**
**  **jma
**
*************************************/

ArxRleAppXdata*
ArxRleAppXdataListIterator::item() const
{
    if (m_pos == -1)
        return NULL;

    return m_xdataList.m_list[m_pos];
}

/****************************************************************************
**
**  ArxRleAppXdataListIterator::done
**
**  **jma
**
*************************************/

bool
ArxRleAppXdataListIterator::done() const
{
    return m_pos == -1;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////  GLOBAL FUNCTIONS  ////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  malformedXdataTagError
**
**  **jma
**
*************************************/

void
malformedXdataTagError(int tag)
{
    acutPrintf(_T("\nERROR: malfomed Xdata tag: %d"), tag);
}

/****************************************************************************
**
**  missingXdataTagWarning
**
**  **jma
**
*************************************/

void
missingXdataTagWarning(int tag)
{
    acutPrintf(_T("\nWARNING: Xdata tag missing: %d"), tag);
}











