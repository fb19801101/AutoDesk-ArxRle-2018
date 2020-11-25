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

#include "ArxRleUiTdcDatabase.h"
#include "AcadUtils/ArxRleUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiTdcDatabase::ArxRleUiTdcDatabase
**
**  **jma
**
*************************************/

ArxRleUiTdcDatabase::ArxRleUiTdcDatabase(AcDbDatabase* db)
:   m_db(db)
{
    //{{AFX_DATA_INIT(ArxRleUiTdcDatabase)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxRleUiTdcDatabase::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDatabase::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiTdcRxObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcDatabase)
	DDX_Control(pDX, ARXRLE_DBMISC_FR_PREVIEW, m_frPreview);
	DDX_Control(pDX, ARXRLE_DBMISC_LC_DBMISC_VALUES, m_dataList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcDatabase message map

BEGIN_MESSAGE_MAP(ArxRleUiTdcDatabase, ArxRleUiTdcRxObjectBase)
    //{{AFX_MSG_MAP(ArxRleUiTdcDatabase)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcDatabase message handlers


/****************************************************************************
**
**  ArxRleUiTdcDatabase::OnPaint
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDatabase::OnPaint() 
{
    CPaintDC dc(this); // device context for painting

	const TCHAR* fname;
	Acad::ErrorStatus es = m_db->getFilename(fname);
	if (es == Acad::eOk) {
        m_frPreview.EnableWindow(TRUE);
        if (!acdbDisplayPreviewFromDwg(fname, m_frPreview.m_hWnd))
            ArxRleUtils::stopAlertBox(_T("ERROR: Could not display preview image!"));
    }
    else {
        m_frPreview.EnableWindow(FALSE);
    }
}

/****************************************************************************
**
**	ArxRleUiTdcDatabase::OnInitDialog
**
**	**jma
**
*************************************/

BOOL
ArxRleUiTdcDatabase::OnInitDialog() 
{
    ArxRleUiTdcRxObjectBase::OnInitDialog();

	buildColumns(m_dataList);
	display();

    return TRUE;
}

/****************************************************************************
**
**  ArxRleUiTdcDatabase::display
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDatabase::display()
{
		// remove any existing data
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    CString str;
	Acad::ErrorStatus es;

    addToDataList(_T("Approx. Number of Objects"), ArxRleUtils::intToStr(m_db->approxNumObjects(), str));
    addToDataList(_T("Number of Saves"), ArxRleUtils::intToStr(m_db->numberOfSaves(), str));
    addToDataList(_T("Maintenance Release Version"), ArxRleUtils::intToStr(m_db->maintenanceReleaseVersion(), str));
    addToDataList(_T("Last Saved As Version"), ArxRleUtils::dwgVersionToStr(m_db->lastSavedAsVersion(), str));
    addToDataList(_T("Last Saved As Maintenance Version"), ArxRleUtils::intToStr(m_db->lastSavedAsMaintenanceVersion(), str));
    addToDataList(_T("Original File Name"), m_db->originalFileName(), true);
    addToDataList(_T("Original File Version"), ArxRleUtils::dwgVersionToStr(m_db->originalFileVersion(), str));
    addToDataList(_T("Original File Maintenance Version"), ArxRleUtils::intToStr(m_db->originalFileMaintenanceVersion(), str));
    addToDataList(_T("Original File Saved By Version"), ArxRleUtils::dwgVersionToStr(m_db->originalFileSavedByVersion(), str));
    addToDataList(_T("Original File Saved By Manintenance Version"), ArxRleUtils::intToStr(m_db->originalFileSavedByMaintenanceVersion(), str));
    addToDataList(_T("DWG Saved By Autodesk Software"), ArxRleUtils::booleanToStr(m_db->dwgFileWasSavedByAutodeskSoftware(), str));

	TCHAR* name = NULL;

		// get projectName
    es = m_db->getProjectName(name);
	if (es == Acad::eOk) {
		addToDataList(_T("Project Name"), name, true);
		acutDelString(name);
	}
	else
		addToDataList(_T("Project Name"), ArxRleUtils::rxErrorStr(es));

		// get hyperlinkBase
    es = m_db->getHyperlinkBase(name);
	if (es == Acad::eOk) {
		addToDataList(_T("Hyperlink Base"), name, true);
		acutDelString(name);
	}
	else
		addToDataList(_T("Hyperlink Base"), ArxRleUtils::rxErrorStr(es));

		// get styleSheet
    es = m_db->getStyleSheet(name);
	if (es == Acad::eOk) {
		addToDataList(_T("Style Sheet"), name, true);
		acutDelString(name);
	}
	else
		addToDataList(_T("Style Sheet"), ArxRleUtils::rxErrorStr(es));

		// get fileName
	const TCHAR* fname;
    es = m_db->getFilename(fname);
	if (es == Acad::eOk)
		addToDataList(_T("File Name"), fname, true);
	else
		addToDataList(_T("File Name"), ArxRleUtils::rxErrorStr(es));

		// get fingerprintGuid
    es = m_db->getFingerprintGuid(name);
	if (es == Acad::eOk) {
		addToDataList(_T("Fingerprint Guid"), name);
		acutDelString(name);
	}
	else
		addToDataList(_T("Fingerprint Guid"), ArxRleUtils::rxErrorStr(es));

		// get versionGuid
    es = m_db->getVersionGuid(name);
	if (es == Acad::eOk) {
		addToDataList(_T("Version Guid"), name);
		acutDelString(name);
	}
	else
		addToDataList(_T("Version Guid"), ArxRleUtils::rxErrorStr(es));


    addToDataList(_T("Is Partially Opened"), ArxRleUtils::booleanToStr(m_db->isPartiallyOpened(), str));
    addToDataList(_T("Retain Original Thumbnail"), ArxRleUtils::booleanToStr(m_db->retainOriginalThumbnailBitmap(), str));
	addToDataList(_T("Xref Block"), ArxRleUtils::objToClassAndHandleStr(m_db->xrefBlockId(), str));
	addToDataList(_T("Transaction Manager"), ArxRleUtils::ptrToStr(m_db->transactionManager(), str));

	addSeperatorLine(_T("Header Variables"));

	addToDataList(_T("Angbase"), ArxRleUtils::doubleToStr(m_db->angbase(), str));
	addToDataList(_T("Angdir"), ArxRleUtils::booleanToStr(m_db->angdir(), str));
	addToDataList(_T("Attdia"), ArxRleUtils::booleanToStr(m_db->attdia(), str));
	addToDataList(_T("Attmode"), ArxRleUtils::intToStr(m_db->attmode(), str));
	addToDataList(_T("Attreq"), ArxRleUtils::booleanToStr(m_db->attreq(), str));
	addToDataList(_T("Aunits"), ArxRleUtils::intToStr(m_db->aunits(), str));
	addToDataList(_T("Auprec"), ArxRleUtils::intToStr(m_db->auprec(), str));
	addToDataList(_T("Blipmode"), ArxRleUtils::booleanToStr(m_db->blipmode(), str));
	addToDataList(_T("Cecolor"), ArxRleUtils::colorToStr(m_db->cecolor().colorIndex(), str));
	addToDataList(_T("Celweight"), ArxRleUtils::lineWeightTypeToStr(m_db->celweight(), str));

	es = ArxRleUtils::symbolIdToName(m_db->clayer(), str);
	addToDataList(_T("Celayer"), str);

	es = ArxRleUtils::symbolIdToName(m_db->celtype(), str);
	addToDataList(_T("Celtype"), str);
	addToDataList(_T("Celtscale"), ArxRleUtils::doubleToStr(m_db->celtscale(), str));

	addToDataList(_T("Chamfera"), ArxRleUtils::doubleToStr(m_db->chamfera(), str));
	addToDataList(_T("Chamferb"), ArxRleUtils::doubleToStr(m_db->chamferb(), str));
	addToDataList(_T("Chamferc"), ArxRleUtils::doubleToStr(m_db->chamferc(), str));
	addToDataList(_T("Chamferd"), ArxRleUtils::doubleToStr(m_db->chamferd(), str));

	es = ArxRleUtils::mlineStyleIdToName(m_db->cmlstyleID(), str);
	addToDataList(_T("Cmlstyleid"), str);

	addToDataList(_T("Cmljust"), ArxRleUtils::intToStr(m_db->cmljust(), str));
	addToDataList(_T("Cmlscale"), ArxRleUtils::doubleToStr(m_db->cmlscale(), str));

	addToDataList(_T("Coords"), ArxRleUtils::intToStr(m_db->coords(), str));
	addToDataList(_T("Dimaso"), ArxRleUtils::booleanToStr(m_db->dimaso(), str));
	addToDataList(_T("Dimsho"), ArxRleUtils::booleanToStr(m_db->dimsho(), str));

	es = ArxRleUtils::symbolIdToName(m_db->dimstyle(), str);
	addToDataList(_T("Dimstyle"), str);

	addToDataList(_T("Dispsilh"), ArxRleUtils::booleanToStr(m_db->dispSilh(), str));
	addToDataList(_T("Delete Used Obj"), ArxRleUtils::booleanToStr(!!m_db->delUsedObj(), str));
	addToDataList(_T("Dragmode"), ArxRleUtils::intToStr(m_db->dragmode(), str));
	addToDataList(_T("Elevation"), ArxRleUtils::doubleToStr(m_db->elevation(), str));
	addToDataList(_T("Endcaps"), ArxRleUtils::intToStr(m_db->endCaps(), str));
	addToDataList(_T("Extmin"), ArxRleUtils::ptToStr(m_db->extmin(), str));
	addToDataList(_T("Extmax"), ArxRleUtils::ptToStr(m_db->extmax(), str));
	addToDataList(_T("Facetres"), ArxRleUtils::doubleToStr(m_db->facetres(), str));
	addToDataList(_T("Fillmode"), ArxRleUtils::booleanToStr(m_db->fillmode(), str));
	addToDataList(_T("Filletrad"), ArxRleUtils::doubleToStr(m_db->filletrad(), str));

	TCHAR tmpStr[256];
    m_db->handseed().getIntoAsciiBuffer(tmpStr);
	addToDataList(_T("Handseed"), tmpStr);

	addToDataList(_T("Insbase"), ArxRleUtils::ptToStr(m_db->insbase(), str));
	addToDataList(_T("Insunits"), ArxRleUtils::intToStr(m_db->insunits(), str));
	addToDataList(_T("Isolines"), ArxRleUtils::intToStr(m_db->isolines(), str));
	addToDataList(_T("Joinstyle"), ArxRleUtils::intToStr(m_db->joinStyle(), str));
	addToDataList(_T("Ltscale"), ArxRleUtils::doubleToStr(m_db->ltscale(), str));
	addToDataList(_T("Limcheck"), ArxRleUtils::booleanToStr(m_db->limcheck(), str));
	addToDataList(_T("Limmin"), ArxRleUtils::ptToStr(m_db->limmin(), str));
	addToDataList(_T("Limmax"), ArxRleUtils::ptToStr(m_db->limmax(), str));
	addToDataList(_T("Lineweight Display"), ArxRleUtils::booleanToStr(m_db->lineWeightDisplay(), str));
	addToDataList(_T("Lunits"), ArxRleUtils::intToStr(m_db->lunits(), str));
	addToDataList(_T("Luprec"), ArxRleUtils::intToStr(m_db->luprec(), str));
	addToDataList(_T("Maxactvp"), ArxRleUtils::intToStr(m_db->maxactvp(), str));
	addToDataList(_T("Measurement"), ArxRleUtils::measurementTypeToStr(m_db->measurement(), str));

	TCHAR* menuName;
	es = m_db->getMenu(menuName);
	if (es == Acad::eOk) {
		addToDataList(_T("Menu"), menuName, true);
		acutDelString(menuName);
	}
	else
		addToDataList(_T("Menu"), ArxRleUtils::rxErrorStr(es));

	addToDataList(_T("Mirrtext"), ArxRleUtils::booleanToStr(m_db->mirrtext(), str));
	addToDataList(_T("OLE Startup"), ArxRleUtils::booleanToStr(m_db->oleStartUp(), str));
	addToDataList(_T("Orthomode"), ArxRleUtils::booleanToStr(m_db->orthomode(), str));
	addToDataList(_T("Pdmode"), ArxRleUtils::intToStr(m_db->pdmode(), str));
	addToDataList(_T("Pdsize"), ArxRleUtils::doubleToStr(m_db->pdsize(), str));
	addToDataList(_T("Pextmin"), ArxRleUtils::ptToStr(m_db->pextmin(), str));
	addToDataList(_T("Pextmax"), ArxRleUtils::ptToStr(m_db->pextmax(), str));
	addToDataList(_T("Pelevation"), ArxRleUtils::doubleToStr(m_db->pelevation(), str));
	addToDataList(_T("Pickstyle"), ArxRleUtils::intToStr(m_db->pickstyle(), str));
	addToDataList(_T("Pinsbase"), ArxRleUtils::ptToStr(m_db->pinsbase(), str));
	addToDataList(_T("Plimcheck"), ArxRleUtils::booleanToStr(m_db->plimcheck(), str));
	addToDataList(_T("Plimmin"), ArxRleUtils::ptToStr(m_db->plimmin(), str));
	addToDataList(_T("Plimmax"), ArxRleUtils::ptToStr(m_db->plimmax(), str));
	addToDataList(_T("PlineEllipse"), ArxRleUtils::booleanToStr(m_db->plineEllipse(), str));
	addToDataList(_T("PlineGen"), ArxRleUtils::booleanToStr(m_db->plinegen(), str));
	addToDataList(_T("Plinewid"), ArxRleUtils::doubleToStr(m_db->plinewid(), str));
	addToDataList(_T("Plot Style Mode"), ArxRleUtils::booleanToStr(m_db->plotStyleMode(), str));
	addToDataList(_T("PsltScale"), ArxRleUtils::booleanToStr(m_db->psltscale(), str));
	addToDataList(_T("Pucsorg"), ArxRleUtils::ptToStr(m_db->pucsorg(), str));
	addToDataList(_T("Pucsxdir"), ArxRleUtils::vectorToStr(m_db->pucsxdir(), str));
	addToDataList(_T("Pucsydir"), ArxRleUtils::vectorToStr(m_db->pucsydir(), str));

	es = ArxRleUtils::symbolIdToName(m_db->pucsname(), str);
	addToDataList(_T("Pucsname"), str);

	addToDataList(_T("Pucsbase"), ArxRleUtils::objToClassAndHandleStr(m_db->pucsBase(), str));

	AcDb::OrthographicView orthoView;
	addToDataList(_T("Pucs Is Orthographic"), ArxRleUtils::booleanToStr(m_db->isPucsOrthographic(orthoView), str));

	addToDataList(_T("Qtextmode"), ArxRleUtils::booleanToStr(m_db->qtextmode(), str));
	addToDataList(_T("Regenmode"), ArxRleUtils::booleanToStr(m_db->regenmode(), str));
	addToDataList(_T("Save Proxy Graphics"), ArxRleUtils::intToStr(m_db->saveproxygraphics(), str));
	addToDataList(_T("Shadedge"), ArxRleUtils::intToStr(m_db->shadedge(), str));
	addToDataList(_T("Shadedif"), ArxRleUtils::intToStr(m_db->shadedif(), str));
	addToDataList(_T("Skpoly"), ArxRleUtils::booleanToStr(m_db->skpoly(), str));
	addToDataList(_T("Sketchinc"), ArxRleUtils::doubleToStr(m_db->sketchinc(), str));
	addToDataList(_T("Splframe"), ArxRleUtils::booleanToStr(m_db->splframe(), str));
	addToDataList(_T("Splinetype"), ArxRleUtils::intToStr(m_db->splinetype(), str));
	addToDataList(_T("Splinesegs"), ArxRleUtils::intToStr(m_db->splinesegs(), str));
	addToDataList(_T("Surfu"), ArxRleUtils::intToStr(m_db->surfu(), str));
	addToDataList(_T("Surfv"), ArxRleUtils::intToStr(m_db->surfv(), str));
	addToDataList(_T("Surftype"), ArxRleUtils::intToStr(m_db->surftype(), str));
	addToDataList(_T("Surftab1"), ArxRleUtils::intToStr(m_db->surftab1(), str));
	addToDataList(_T("Surftab2"), ArxRleUtils::intToStr(m_db->surftab2(), str));
	addToDataList(_T("Tdcreate"), ArxRleUtils::dateToStr(m_db->tdcreate(), str));
	addToDataList(_T("Tdupdate"), ArxRleUtils::dateToStr(m_db->tdupdate(), str));
	addToDataList(_T("Tducreate"), ArxRleUtils::dateToStr(m_db->tducreate(), str));
	addToDataList(_T("Tduupdate"), ArxRleUtils::dateToStr(m_db->tduupdate(), str));
	addToDataList(_T("Tdindwg"), ArxRleUtils::dateToStr(m_db->tdindwg(), str));
	addToDataList(_T("Tdusrtimer"), ArxRleUtils::dateToStr(m_db->tdusrtimer(), str));
	addToDataList(_T("Textsize"), ArxRleUtils::doubleToStr(m_db->textsize(), str));
	addToDataList(_T("Thickness"), ArxRleUtils::doubleToStr(m_db->thickness(), str));
	addToDataList(_T("Tilemode"), ArxRleUtils::booleanToStr(m_db->tilemode(), str));
	addToDataList(_T("Treedepth"), ArxRleUtils::intToStr(m_db->treedepth(), str));
	addToDataList(_T("Tracewidth"), ArxRleUtils::doubleToStr(m_db->tracewid(), str));
	addToDataList(_T("Tstackalign"), ArxRleUtils::intToStr(m_db->tstackalign(), str));
	addToDataList(_T("Tstacksize"), ArxRleUtils::intToStr(m_db->tstacksize(), str));
	addToDataList(_T("Ucsorg"), ArxRleUtils::ptToStr(m_db->ucsorg(), str));
	addToDataList(_T("Ucsxdir"), ArxRleUtils::vectorToStr(m_db->ucsxdir(), str));
	addToDataList(_T("Ucsydir"), ArxRleUtils::vectorToStr(m_db->ucsydir(), str));

	es = ArxRleUtils::symbolIdToName(m_db->ucsname(), str);
	addToDataList(_T("Ucsname"), str);

	addToDataList(_T("Ucsbase"), ArxRleUtils::objToClassAndHandleStr(m_db->ucsBase(), str));
	addToDataList(_T("Ucs Is Orthographic"), ArxRleUtils::booleanToStr(m_db->isUcsOrthographic(orthoView), str));

	addToDataList(_T("Useri1"), ArxRleUtils::intToStr(m_db->useri1(), str));
	addToDataList(_T("Useri2"), ArxRleUtils::intToStr(m_db->useri2(), str));
	addToDataList(_T("Useri3"), ArxRleUtils::intToStr(m_db->useri3(), str));
	addToDataList(_T("Useri4"), ArxRleUtils::intToStr(m_db->useri4(), str));
	addToDataList(_T("Useri5"), ArxRleUtils::intToStr(m_db->useri5(), str));
	addToDataList(_T("Userr1"), ArxRleUtils::doubleToStr(m_db->userr1(), str));
	addToDataList(_T("Userr2"), ArxRleUtils::doubleToStr(m_db->userr2(), str));
	addToDataList(_T("Userr3"), ArxRleUtils::doubleToStr(m_db->userr3(), str));
	addToDataList(_T("Userr4"), ArxRleUtils::doubleToStr(m_db->userr4(), str));
	addToDataList(_T("Userr5"), ArxRleUtils::doubleToStr(m_db->userr5(), str));
	addToDataList(_T("Usrtimer"), ArxRleUtils::booleanToStr(m_db->usrtimer(), str));
	addToDataList(_T("Visretain"), ArxRleUtils::booleanToStr(m_db->visretain(), str));
	addToDataList(_T("Viewport Scale Default"), ArxRleUtils::doubleToStr(m_db->viewportScaleDefault(), str));
	addToDataList(_T("WorldView"), ArxRleUtils::booleanToStr(m_db->worldview(), str));
	addToDataList(_T("Xref Edit Enabled"), ArxRleUtils::booleanToStr(m_db->xrefEditEnabled(), str));

// TBD: getCePlotStyleNameId()

	drawPropsList(m_dataList);
}

