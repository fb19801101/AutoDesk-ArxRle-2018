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

#include "ArxRleEdInputContextReactor.h"
#include "AcadUtils/ArxRleUtils.h"
#include "Snoop/ArxRleUiTdmObjects.h"
#include "AcadUtils/ArxRleRbList.h"



/****************************************************************************
**
**  ArxRleEdInputContextReactor::ArxRleEdInputContextReactor
**
**  **jma
**
*************************************/

ArxRleEdInputContextReactor::ArxRleEdInputContextReactor()
:	m_showDetails(false),
	m_suppressDetailsDuringDrag(true),
	m_dragJustStarted(false)
{
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::~ArxRleEdInputContextReactor
**
**  **jma
**
*************************************/

ArxRleEdInputContextReactor::~ArxRleEdInputContextReactor()
{
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxRleEdInputContextReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::suppressDetailsDuringDrag
**
**  **jma
**
*************************************/

bool
ArxRleEdInputContextReactor::suppressDetailsDuringDrag() const
{
	return m_suppressDetailsDuringDrag;
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::setSuppressDetailsDuringDrag
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::setSuppressDetailsDuringDrag(bool suppressThem)
{
	m_suppressDetailsDuringDrag = suppressThem;
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printDetails
**
**  **jma
**
*************************************/

bool
ArxRleEdInputContextReactor::printDetails()
{
	if (m_suppressDetailsDuringDrag) {
		if (acedIsDragging()) {
				// print the first drag message, but suppress the rest until the
				// end of the drag sequence
			if (m_dragJustStarted) {
				m_dragJustStarted = false;
				return true;
			}
			return false;
		}
		else
			return m_showDetails;
	}
	else {
		return m_showDetails;
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginGetPoint
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginGetPoint(const AcGePoint3d* pointIn,
					const TCHAR* promptString,
					int initGetFlags,
					const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Point"));

	if (printDetails()) {
		printPointIn(pointIn);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endGetPoint
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endGetPoint(Acad::PromptStatus returnStatus,
					const AcGePoint3d& pointOut,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Point"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("POINT"), ArxRleUtils::ptToStr(pointOut, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginGetAngle
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginGetAngle(const AcGePoint3d* pointIn,
                   const TCHAR* promptString,
                   int initGetFlags,
                   const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Angle"));

	if (printDetails()) {
		printPointIn(pointIn);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endGetAngle
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endGetAngle(Acad::PromptStatus returnStatus,
					double& angle,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Angle"));

	if (m_showDetails) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("ANGLE"), ArxRleUtils::angleToStr(angle, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginGetDistance
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginGetDistance(const AcGePoint3d* pointIn,
                    const TCHAR* promptString,
                    int initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Distance"));

	if (printDetails()) {
		printPointIn(pointIn);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endGetDistance
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endGetDistance(Acad::PromptStatus returnStatus,
                    double& distance,
                    const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Distance"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("DISTANCE"), ArxRleUtils::doubleToStr(distance, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginGetOrientation
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginGetOrientation(const AcGePoint3d* pointIn,
                    const TCHAR* promptString,
                    int   initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Orientation"));

	if (printDetails()) {
		printPointIn(pointIn);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endGetOrientation
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endGetOrientation(Acad::PromptStatus returnStatus,
                    double& angle,
                    const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End GetOrientation"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("ANGLE"), ArxRleUtils::angleToStr(angle, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginGetCorner
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginGetCorner(const AcGePoint3d* firstCorner,
                    const TCHAR* promptString,
                    int   initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Corner"));

	if (printDetails()) {
		printFirstCorner(firstCorner);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endGetCorner
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endGetCorner(Acad::PromptStatus returnStatus,
					AcGePoint3d& secondCorner,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Corner"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("SECOND CORNER"), ArxRleUtils::ptToStr(secondCorner, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginGetScaleFactor
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginGetScaleFactor(const AcGePoint3d* pointIn,
                    const TCHAR* promptString,
                    int initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Scale Factor"));

	if (printDetails()) {
		printPointIn(pointIn);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endGetScaleFactor
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endGetScaleFactor(Acad::PromptStatus returnStatus,
                    double& distance,
                    const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Scale Factor"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("SCALE FACTOR"), ArxRleUtils::doubleToStr(distance, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginGetString
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginGetString(const TCHAR* promptString, int initGetFlags)
{
	printReactorMessage(_T("Begin Get String"));

	if (printDetails()) {
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endGetString
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endGetString(Acad::PromptStatus returnStatus, TCHAR* pString)
{
	printReactorMessage(_T("End Get String"));

	if (printDetails()) {
		printReturnStatus(returnStatus);
		printValue(_T("STRING"), pString);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginGetKeyword
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginGetKeyword(const TCHAR* promptString,
                    int initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Keyword"));

	if (printDetails()) {
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endGetKeyword
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endGetKeyword(Acad::PromptStatus returnStatus, const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Keyword"));

	if (printDetails()) {
		printReturnStatus(returnStatus);
		printValue(_T("KEYWORD"), pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginGetInteger
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginGetInteger(const int* dfault,
					const TCHAR* promptString,
                    int initGetFlags,
                    const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Integer"));

	if (printDetails()) {
		printDefaultInt(dfault);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endGetInteger
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endGetInteger(Acad::PromptStatus returnStatus,
					int& retValue,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Integer"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("INTEGER"), ArxRleUtils::intToStr(retValue, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginGetColor
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginGetColor(const int* dfault,
					const TCHAR* promptString,
					int initGetFlags,
					const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Color"));

	if (printDetails()) {
		printDefaultInt(dfault);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endGetColor
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endGetColor(Acad::PromptStatus returnStatus,
					int& retValue,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Color"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("COLOR"), ArxRleUtils::colorToStr(retValue, str, true));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginGetReal
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginGetReal(const double* dfault,
					const TCHAR* promptString,
					int initGetFlags,
					const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Get Real"));

	if (printDetails()) {
		printDefaultReal(dfault);
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endGetReal
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endGetReal(Acad::PromptStatus returnStatus,
					double& returnValue,
					const TCHAR*& pKeyword)
{
	printReactorMessage(_T("End Get Real"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("REAL"), ArxRleUtils::doubleToStr(returnValue, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginEntsel
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginEntsel(const TCHAR* promptString,
					int initGetFlags,
					const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Entsel"));

	if (printDetails()) {
		printPrompt(promptString);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endEntsel
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endEntsel(Acad::PromptStatus returnStatus,
					AcDbObjectId& entPicked,
					AcGePoint3d& pickPoint,
					const TCHAR* pKeyword)
{
	printReactorMessage(_T("End Entsel"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("ENTITY PICKED"), ArxRleUtils::objToClassAndHandleStr(entPicked, str));
		printValue(_T("PICK POINT"), ArxRleUtils::ptToStr(pickPoint, str));
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginNentsel
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginNentsel(const TCHAR* promptString,
					Adesk::Boolean pickFlag,
					int initGetFlags,
					const TCHAR* pKeywords)
{
	printReactorMessage(_T("Begin Nentsel"));

	if (printDetails()) {
		CString str;
		printPrompt(promptString);
		printValue(_T("PICK FLAG"), ArxRleUtils::booleanToStr(pickFlag, str));
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endNentsel
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endNentsel(Acad::PromptStatus returnStatus,
					AcDbObjectId entPicked,
					const AcGePoint3d&  pickPoint,
					const AcGeMatrix3d& xform,
					const resbuf* referenceStack,
					const TCHAR* pKeyword)
{
	printReactorMessage(_T("End Nentsel"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("ENTITY PICKED"), ArxRleUtils::objToClassAndHandleStr(entPicked, str));
		printValue(_T("PICK POINT"), ArxRleUtils::ptToStr(pickPoint, str));
// TBD: need matrix and ref stack
		printKeywordPicked(pKeyword);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginSSGet
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginSSGet(const TCHAR*  pPrompt,
					int  initGetFlags,
					const TCHAR* pKeywords,
					const TCHAR* pSSControls, // str in ADS
					const AcArray<AcGePoint3d>& points,
					const resbuf* entMask)
{
	printReactorMessage(_T("Begin SSGet"));

	if (printDetails()) {
		CString str;
		printPrompt(pPrompt);
		printInitGetFlags(initGetFlags);
		printKeywords(pKeywords);
		printValue(_T("SS CONTROLS"), pSSControls);
		printPoints(points);
		printResbufs(_T("ENT MASK"), entMask);
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endSSGet
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endSSGet(Acad::PromptStatus returnStatus,
					const AcArray<AcDbObjectId>& ss)
{
	printReactorMessage(_T("End SSGet"));

	if (printDetails()) {
		CString str;
		printReturnStatus(returnStatus);

		ArxRleUiTdmObjects dbox(ss, acedGetAcadDwgView(), _T("SSGet Set"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginDragSequence
**
**  **jma
**
*************************************/
    
void
ArxRleEdInputContextReactor::beginDragSequence(const TCHAR* promptString)
{
	m_dragJustStarted = true;

	printReactorMessage(_T("Begin Drag Sequence"));

	if (m_showDetails)
		printPrompt(promptString);
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endDragSequence
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endDragSequence(Acad::PromptStatus returnStatus,
                    AcGePoint3d& pickPoint, AcGeVector3d& vec)
{
	printReactorMessage(_T("End Drag Sequence"));

	if (m_showDetails) {
		CString str;
		printReturnStatus(returnStatus);
		printValue(_T("PICK POINT"), ArxRleUtils::ptToStr(pickPoint, str));
		printValue(_T("VECTOR"), ArxRleUtils::vectorToStr(vec, str));
	}
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::beginQuiescentState
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::beginQuiescentState()
{
	printReactorMessage(_T("Begin Quiescent State"));
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::endQuiescentState
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::endQuiescentState()
{
	printReactorMessage(_T("End Quiescent State"));
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printReactorMessage(LPCTSTR event) const
{
	if (m_suppressDetailsDuringDrag && acedIsDragging())
		;
	else
		acutPrintf(_T("\n\n%-15s : [%s] "), _T("[ED INPUT REACTOR]"), event);
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printPrompt
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printPrompt(const TCHAR* promptStr) const
{
	if (promptStr)
		acutPrintf(_T("\n   %-20s: \"%s\""), _T("PROMPT"), promptStr);
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printKeywords
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printKeywords(const TCHAR* keywords) const
{
	if (keywords)
		acutPrintf(_T("\n   %-20s: \"%s\""), _T("KEYWORDS"), keywords);
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printKeywordPicked
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printKeywordPicked(const TCHAR*& keywordPicked) const
{
	if (keywordPicked)
		acutPrintf(_T("\n   %-20s: \"%s\""), _T("KEYWORD PICKED"), keywordPicked);
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printInitGetFlags
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printInitGetFlags(int flags) const
{
	CString str;
	acutPrintf(_T("\n   %-20s: %s"), _T("INIT FLAGS"), ArxRleUtils::initFlagsToStr(flags, str));
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printReturnStatus
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printReturnStatus(Acad::PromptStatus returnStatus) const
{
	CString str;
	acutPrintf(_T("\n   %-20s: %s"), _T("RETURN STAT"), ArxRleUtils::promptStatusToStr(returnStatus, str));
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printValue
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printValue(LPCTSTR label, LPCTSTR value) const
{
	if (value)
		acutPrintf(_T("\n   %-20s: %s"), label, value);
	else
		acutPrintf(_T("\n   %-20s: %s"), label, _T("Null"));
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printPointIn
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printPointIn(const AcGePoint3d* pointIn) const
{
	CString str;
	if (pointIn != NULL)
		printValue(_T("POINT IN"), ArxRleUtils::ptToStr(*pointIn, str));
	else
		printValue(_T("POINT IN"), _T("Null"));
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printFirstCorner
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printFirstCorner(const AcGePoint3d* pointIn) const
{
	CString str;
	if (pointIn != NULL)
		printValue(_T("FIRST CORNER"), ArxRleUtils::ptToStr(*pointIn, str));
	else
		printValue(_T("FIRST CORNER"), _T("Null"));
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printDefaultInt
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printDefaultInt(const int* def) const
{
	CString str;
	if (def != NULL)
		printValue(_T("DEFAULT"), ArxRleUtils::intToStr(*def, str));
	else
		printValue(_T("DEFAULT"), _T("Null"));
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printDefaultReal
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printDefaultReal(const double* def) const
{
	CString str;
	if (def != NULL)
		printValue(_T("DEFAULT"), ArxRleUtils::doubleToStr(*def, str));
	else
		printValue(_T("DEFAULT"), _T("Null"));
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printResbufs
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printResbufs(LPCTSTR label, const resbuf* rb) const
{
	printValue(label, _T(""));

    CString dxfCodeStr, valueStr, tmpStr;
    const resbuf* tmp = rb;
    while (tmp) {
        dxfToStr(tmp, dxfCodeStr, valueStr);
        tmpStr.Format(_T("(%s . %s)"), dxfCodeStr, valueStr);
		printValue(_T(""), tmpStr);
        tmp = tmp->rbnext;
    }
}

/****************************************************************************
**
**  ArxRleEdInputContextReactor::printPoints
**
**  **jma
**
*************************************/

void
ArxRleEdInputContextReactor::printPoints(const AcGePoint3dArray& pts) const
{
	int len = pts.length();
	if (len == 0)
		return;

	printValue(_T("POINTS"), _T(""));
	
	CString str;
	for (int i=0; i<len; i++) {
		printValue(_T(""), ArxRleUtils::ptToStr(pts[i], str));
    }
}










