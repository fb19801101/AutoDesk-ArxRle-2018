//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//  ArxRleUiTdcDbObjectBase.cpp
//
//////////////////////////////////////////////////////////////////////////////
//
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleUiTdcDbObjectBase.h"
#include "AcadUtils/ArxRleUtils.h"
#include "ArxRleUiDlgDxf.h"
#include "ArxRleUiDlgReactors.h"
#include "ArxRleUiDlgXdata.h"
#include "ArxRleUiTdmDatabase.h"
#include "ArxRleUiTdmEditor.h"
#include "ArxRleUiTdmObjects.h"
#include "ArxRleUiTdmReferences.h"
#include "ArxRleUiDlgObjectId.h"
#include "Reactor/ArxRleAppEditorReactor.h"
#include "Filer/ArxRleReferenceFiler.h"
#include "AcExtensionModule.h"
#include "ArxRle.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::ArxRleUiTdcDbObjectBase
**
**  **jma
**
*************************************/

ArxRleUiTdcDbObjectBase::ArxRleUiTdcDbObjectBase()
:   ArxRleUiTdcRxObjectBase()
{
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::DoDataExchange(CDataExchange* pDX)
{
    ArxRleUiTdcRxObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxRleUiTdcDbObjectBase)
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcDbObjectBase message map

BEGIN_MESSAGE_MAP(ArxRleUiTdcDbObjectBase, ArxRleUiTdcRxObjectBase)
    //{{AFX_MSG_MAP(ArxRleUiTdcDbObjectBase)
    ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(ARXRLE_OBJS_BN_DXF, OnDxf)
	ON_BN_CLICKED(ARXRLE_OBJS_BN_EXTDICT, OnExtdict)
	ON_BN_CLICKED(ARXRLE_OBJS_BN_REACTORS, OnReactors)
	ON_BN_CLICKED(ARXRLE_OBJS_BN_XDATA, OnXdata)
	ON_BN_CLICKED(ARXRLE_OBJS_BN_DOCUMENT, OnDocument)
	ON_BN_CLICKED(ARXRLE_OBJS_BN_REFERENCED_OBJS, OnReferencedObjects)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiTdcDbObjectBase message handlers

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::OnDxf
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::OnDxf() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        ArxRleUiDlgDxf dbox(this, obj);
        dbox.DoModal();
        obj->close();
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::OnExtdict
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::OnExtdict() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        AcDbObjectId extDictId = obj->extensionDictionary();
        obj->close();

        ArxRleUiTdmDatabase dbox(extDictId, this, _T("Extension Dictionary"));
        dbox.DoModal();
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::OnReactors
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::OnReactors() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        ArxRleUiDlgReactors dbox(this, obj);
        dbox.DoModal();
        obj->close();
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::OnXdata
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::OnXdata() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        ArxRleUiDlgXdata dbox(this, obj);
        dbox.DoModal();
        obj->close();
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::OnDatabase
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::OnDatabase() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        AcDbDatabase* db = obj->database();
        obj->close();

        if (db != NULL) {
            ArxRleUiTdmDatabase dbox(db, this, _T("Database For Object"));
            dbox.DoModal();
        }
        else {
            ASSERT(0);    // button should have been disabled!
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::OnReferencedObjects
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::OnReferencedObjects() 
{
    AcDbObjectIdArray hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds;
    if (getReferencedObjects(hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds)) {
        ArxRleUiTdmReferences dbox(hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds, this);
        dbox.DoModal();
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::getReferencedObjects
**
**  **jma
**
*************************************/

bool
ArxRleUiTdcDbObjectBase::getReferencedObjects(AcDbObjectIdArray& hardPointerIds,
                                              AcDbObjectIdArray& softPointerIds,
                                              AcDbObjectIdArray& hardOwnershipIds,
                                              AcDbObjectIdArray& softOwnershipIds) 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        ArxRleReferenceFiler filer;
        obj->dwgOut(&filer);
        obj->close();

        hardPointerIds = filer.m_hardPointerIds;
        softPointerIds = filer.m_softPointerIds;
        hardOwnershipIds = filer.m_hardOwnershipIds;
        softOwnershipIds = filer.m_softOwnershipIds;

        return true;
    }
    else
        return false;
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::OnDocument
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::OnDocument() 
{
    AcDbObject* obj = openCurrentItem();
    if (obj != NULL) {
        AcDbDatabase* db = obj->database();
        obj->close();

        AcApDocument* doc = acDocManager->document(db);
        if (doc) {
            ArxRleUiTdmEditor dbox(this, doc);
            dbox.DoModal();
        }
        else {
            ASSERT(0);    // this button should have been disabled!
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::setExtensionButtons
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::setExtensionButtons(AcDbObject* obj)
{
	bool hasDbButton = (this->GetDlgItem(ARXRLE_OBJS_BN_DATABASE) != NULL) ? true : false;
	bool hasDocButton = (this->GetDlgItem(ARXRLE_OBJS_BN_DOCUMENT) != NULL) ? true : false;

    if (obj != NULL) {
            // enable Xdata button if Xdata is present
        resbuf* xdata = obj->xData();
        ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_XDATA, (xdata != NULL));
        acutRelRb(xdata);

            // enable ExtDictionary and Reactor buttons if present
        int reactorCount = 0;
        const AcDbVoidPtrArray* reactors = obj->reactors();
        if (reactors != nullptr)
            reactorCount = reactors->length();

        ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_EXTDICT, (obj->extensionDictionary() != AcDbObjectId::kNull));
        ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_REACTORS, (reactorCount != 0));

            // always make sure DXF button is enabled
        ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_DXF, TRUE);

            // check for references
        AcDbObjectIdArray hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds;
        getReferencedObjects(hardPointerIds, softPointerIds, hardOwnershipIds, softOwnershipIds);
        bool hasReferences = false;
        if (!hardPointerIds.isEmpty() || !softPointerIds.isEmpty() || !hardOwnershipIds.isEmpty() || !softOwnershipIds.isEmpty())
            hasReferences = true;

        ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_REFERENCED_OBJS, hasReferences);

        AcDbDatabase* db = obj->database();

        if (hasDbButton)
            ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_DATABASE, (db != NULL));
        if (hasDocButton)
            ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_DOCUMENT, (db && (acDocManager->document(db) != NULL)));
    }
    else {
		ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_XDATA, FALSE);
		ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_EXTDICT, FALSE);
		ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_REACTORS, FALSE);
		ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_DXF, FALSE);
		ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_REFERENCED_OBJS, FALSE);

		if (hasDbButton)
			ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_DATABASE, FALSE);
		if (hasDocButton)
			ArxRleUtils::enableDlgItem(this, ARXRLE_OBJS_BN_DOCUMENT, FALSE);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::openCurrentItem
**
**  **jma
**
*************************************/

AcDbObject*
ArxRleUiTdcDbObjectBase::openCurrentItem()
{
    if (m_currentObjId == AcDbObjectId::kNull)
        return NULL;

    AcDbObject* obj;
    Acad::ErrorStatus es = acdbOpenObject(obj, m_currentObjId, AcDb::kForRead, true);    // might want to open erased
    if (es != Acad::eOk) {
        ArxRleUtils::rxErrorAlert(es);
        return NULL;
    }
    else
        return obj;
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::addToSet
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::addToSet()
{
    ArxRleAppEditorReactor* edReactor = ArxRleAppEditorReactor::getInstance();
    if (edReactor)
        edReactor->cloneSet().addObject(m_currentObjId);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::delFromSet
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::delFromSet()
{
    ArxRleAppEditorReactor* edReactor = ArxRleAppEditorReactor::getInstance();
    if (edReactor)
        edReactor->cloneSet().removeObject(m_currentObjId);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::showObjIdDetails
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::showObjIdDetails()
{
    ArxRleUiDlgObjectId dbox(m_currentObjId, this);
    dbox.DoModal();
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::OnCmdMsg
**
**  **jma
**
*************************************/

BOOL
ArxRleUiTdcDbObjectBase::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
    if (nCode == 0) {
        if (nID == ARXRLE_OBJSET_ADDTOSET) {
            addToSet();
            return TRUE;
        }
        else if (nID == ARXRLE_OBJSET_DELFROMSET) {
            delFromSet();
            return TRUE;
        }
        else if (nID == ARXRLE_OBJSET_OBJID_INFO) {
            showObjIdDetails();
            return TRUE;
        }
    }
    
    return ArxRleUiTdcRxObjectBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::OnRButtonDown
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::OnRButtonDown(UINT nFlags, CPoint point) 
{
    if (m_currentObjId.isNull()) {
        ArxRleUiTdcRxObjectBase::OnRButtonDown(nFlags, point);
        return;
    }

    CMenu menu;
    CAcModuleResourceOverride(ArxRleApp::getApp()->dllInstance());

    if (menu.LoadMenu(ARXRLE_MENU_OBJSET)) {
        CMenu* pContextMenu = menu.GetSubMenu(0);
        
        if (pContextMenu) {
            ClientToScreen(&point);
            pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this);
            return;
        }
    }

    ArxRleUiTdcRxObjectBase::OnRButtonDown(nFlags, point);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbObject* obj)
{
    ASSERT(obj != NULL);

    CString str, str2;

    addSeperatorLine(_T("AcDbObject"));

    addToDataList(_T("Class Name"), ArxRleUtils::objToClassStr(obj));
    addToDataList(_T("Entity Name"), ArxRleUtils::objToEnameStr(obj, str));
    addToDataList(_T("Handle"), ArxRleUtils::objToHandleStr(obj, str));
    addToDataList(_T("Database"), ArxRleUtils::dbToStr(obj->database(), str));

    AcDbObject* ownerObj;
    Acad::ErrorStatus es = acdbOpenObject(ownerObj, obj->ownerId(), AcDb::kForRead);
    if (es == Acad::eOk) {
        ArxRleUtils::objToClassAndHandleStr(ownerObj, str);
        ownerObj->close();
        addToDataList(_T("Owner"), str);
    }
    else
        addToDataList(_T("Owner"), ArxRleUtils::rxErrorStr(es));

    addToDataList(_T("Merge Style"), ArxRleUtils::mergeStyleToStr(obj->mergeStyle(), str));
    addToDataList(_T("Has Save Version Override"), ArxRleUtils::booleanToStr(obj->hasSaveVersionOverride(), str));

    AcDb::AcDbDwgVersion dwgVer;
    AcDb::MaintenanceReleaseVersion maintVer;
    es = obj->getObjectBirthVersion(dwgVer, maintVer);
    if (es == Acad::eOk) {
        addToDataList(_T("Birth DWG Version"), ArxRleUtils::dwgVersionToStr(dwgVer, str));
        addToDataList(_T("Birth Maintenance Version"), ArxRleUtils::intToStr(maintVer, str));
    }
    else
        addToDataList(_T("Birth Version"), ArxRleUtils::rxErrorStr(es));

        // now try to get more specific with classes that we know are derived from us
    AcDbDictionary* dict;
    AcDbEntity* ent;
    AcDbFilter* filter;
    AcDbGroup* group;
    AcDbIndex* index;
    AcDbLongTransaction* longTrans;
    AcDbMlineStyle* mlineStyle;
    AcDbPlaceHolder* placeHolder;
    AcDbPlotSettings* plotSettings;
    AcDbProxyObject* proxy;
    AcDbSymbolTable* symTbl;
    AcDbSymbolTableRecord* symTblRec;
    AcDbXrecord* xrec;

    if ((dict = AcDbDictionary::cast(obj)) != NULL)
        display(dict);
    else if ((ent = AcDbEntity::cast(obj)) != NULL)
        display(ent);
    else if ((filter = AcDbFilter::cast(obj)) != NULL)
        display(filter);
    else if ((group = AcDbGroup::cast(obj)) != NULL)
        display(group);
    else if ((index = AcDbIndex::cast(obj)) != NULL)
        display(index);
    else if ((longTrans = AcDbLongTransaction::cast(obj)) != NULL)
        display(longTrans);
    else if ((mlineStyle = AcDbMlineStyle::cast(obj)) != NULL)
        display(mlineStyle);
    else if ((placeHolder = AcDbPlaceHolder::cast(obj)) != NULL)
        display(placeHolder);
    else if ((plotSettings = AcDbPlotSettings::cast(obj)) != NULL)
        display(plotSettings);
    else if ((proxy = AcDbProxyObject::cast(obj)) != NULL)
        display(proxy);
    else if ((symTbl = AcDbSymbolTable::cast(obj)) != NULL)
        display(symTbl);
    else if ((symTblRec = AcDbSymbolTableRecord::cast(obj)) != NULL)
        display(symTblRec);
    else if ((xrec = AcDbXrecord::cast(obj)) != NULL)
        display(xrec);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display (DICTIONARY)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbDictionary* dict)
{
    CString str;

    ASSERT(dict != NULL);

    addSeperatorLine(_T("AcDbDictionary"));

    addToDataList(_T("Treat Elements As Hard"), ArxRleUtils::booleanToStr(dict->isTreatElementsAsHard(), str));

    AcDbDictionaryWithDefault* dictWithDef;

    if ((dictWithDef = AcDbDictionaryWithDefault::cast(dict)) != NULL)
        display(dictWithDef);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display (ENTITY)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbEntity* ent)
{
    ASSERT(ent != NULL);

    CString str, str2;

    addSeperatorLine(_T("AcDbEntity"));

    ArxRleUtils::symbolIdToName(ent->layerId(), str);
    addToDataList(_T("Layer"), str);

    addToDataList(_T("Color"), ArxRleUtils::colorToStr(ent->colorIndex(), str));

    ArxRleUtils::symbolIdToName(ent->linetypeId(), str);
    addToDataList(_T("Linetype"), str);

    addToDataList(_T("Lineweight"), ArxRleUtils::lineWeightTypeToStr(ent->lineWeight(), str));
    addToDataList(_T("Linetype Scale"), ArxRleUtils::doubleToStr(ent->linetypeScale(), str));

    TCHAR *tmpStr = ent->plotStyleName();
    addToDataList(_T("Plot Style"), tmpStr);
    acutDelString(tmpStr);

    addToDataList(_T("Visible"), ArxRleUtils::booleanToStr((ent->visibility() == AcDb::kVisible), str));

    ArxRleUtils::symbolIdToName(ent->blockId(), str);
    addToDataList(_T("Block"), str);

    addToDataList(_T("Is Planar"), ArxRleUtils::booleanToStr(ent->isPlanar(), str));
    addToDataList(_T("Clone For Dragging"), ArxRleUtils::booleanToStr(ent->cloneMeForDragging(), str));

    AcDb3dSolid* solid;
    AcDbBlockBegin* blkBegin;
    AcDbBlockEnd* blkEnd;
    AcDbBlockReference* blkRef;
    AcDbBody* body;
    AcDbCurve* curve;
    AcDbDimension* dim;
    AcDbFace* face;
    AcDbFaceRecord* vface;
    AcDbFcf* fcf;
    AcDbFrame* frame;
    AcDbHatch* hatch;
    AcDbImage* image;
    AcDbMline* mline;
    AcDbMText* mtext;
    AcDbPoint* point;
    AcDbPolyFaceMesh* pface;
    AcDbPolygonMesh* mesh;
    AcDbProxyEntity* proxy;
    AcDbRegion* region;
    AcDbSequenceEnd* seqEnd;
    AcDbShape* shape;
    AcDbSolid* solid2d;
    AcDbText* text;
    AcDbTrace* trace;
    AcDbVertex* vertex;
    AcDbViewport* viewport;

    if ((solid = AcDb3dSolid::cast(ent)) != NULL)
        display(solid);
    else if ((blkBegin = AcDbBlockBegin::cast(ent)) != NULL)
        display(blkBegin);
    else if ((blkEnd = AcDbBlockEnd::cast(ent)) != NULL)
        display(blkEnd);
    else if ((blkRef = AcDbBlockReference::cast(ent)) != NULL)
        display(blkRef);
    else if ((body = AcDbBody::cast(ent)) != NULL)
        display(body);
    else if ((curve = AcDbCurve::cast(ent)) != NULL)
        display(curve);
    else if ((dim = AcDbDimension::cast(ent)) != NULL)
        display(dim);
    else if ((face = AcDbFace::cast(ent)) != NULL)
        display(face);
    else if ((vface = AcDbFaceRecord::cast(ent)) != NULL)
        display(vface);
    else if ((fcf = AcDbFcf::cast(ent)) != NULL)
        display(fcf);
    else if ((frame = AcDbFrame::cast(ent)) != NULL)
        display(frame);
    else if ((hatch = AcDbHatch::cast(ent)) != NULL)
        display(hatch);
    else if ((image = AcDbImage::cast(ent)) != NULL)
        display(image);
    else if ((mline = AcDbMline::cast(ent)) != NULL)
        display(mline);
    else if ((mtext = AcDbMText::cast(ent)) != NULL)
        display(mtext);
    else if ((point = AcDbPoint::cast(ent)) != NULL)
        display(point);
    else if ((pface = AcDbPolyFaceMesh::cast(ent)) != NULL)
        display(pface);
    else if ((mesh = AcDbPolygonMesh::cast(ent)) != NULL)
        display(mesh);
    else if ((proxy = AcDbProxyEntity::cast(ent)) != NULL)
        display(proxy);
    else if ((region = AcDbRegion::cast(ent)) != NULL)
        display(region);
    else if ((seqEnd = AcDbSequenceEnd::cast(ent)) != NULL)
        display(seqEnd);
    else if ((shape = AcDbShape::cast(ent)) != NULL)
        display(shape);
    else if ((solid2d = AcDbSolid::cast(ent)) != NULL)
        display(solid2d);
    else if ((text = AcDbText::cast(ent)) != NULL)
        display(text);
    else if ((trace = AcDbTrace::cast(ent)) != NULL)
        display(trace);
    else if ((vertex = AcDbVertex::cast(ent)) != NULL)
        display(vertex);
    else if ((viewport = AcDbViewport::cast(ent)) != NULL)
        display(viewport);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display (FILTER)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbFilter* filter)
{
    CString str;

    ASSERT(filter != NULL);

    addSeperatorLine(_T("AcDbFilter"));

    AcDbLayerFilter* layFilter;
    AcDbSpatialFilter* spatialFilter;

    if ((layFilter = AcDbLayerFilter::cast(filter)) != NULL)
        display(layFilter);
    else if ((spatialFilter = AcDbSpatialFilter::cast(filter)) != NULL)
        display(spatialFilter);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    (GROUP)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbGroup* group)
{
    CString str;

    ASSERT(group != NULL);

    addSeperatorLine(_T("AcDbGroup"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    (INDEX)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbIndex* index)
{
    CString str;

    ASSERT(index != NULL);

    addSeperatorLine(_T("AcDbIndex"));

// TBD: doesn't link for some reason
    //AcDbLayerIndex* layIndex;
    //AcDbSpatialIndex* spatialIndex;

    //if ((layIndex = AcDbLayerIndex::cast(index)) != NULL)
    //    display(layIndex);
    //else if ((spatialIndex = AcDbSpatialIndex::cast(index)) != NULL)
    //    display(spatialIndex);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    LONG TRANSACTION
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbLongTransaction* lt)
{
    CString str;

    ASSERT(lt != NULL);

    addSeperatorLine(_T("AcDbLongTransaction"));

    TCHAR* tmpName = NULL;
	Acad::ErrorStatus es = lt->getLongTransactionName(tmpName);
	if (es == Acad::eOk) {
		str = tmpName;
		acutDelString(tmpName);
	}
	else
		str = ArxRleUtils::rxErrorStr(es);

    addToDataList(_T("Name"), str);
    addToDataList(_T("Type"), ArxRleUtils::longTransactionTypeToStr(lt->type(), str));

	ArxRleUtils::symbolIdToName(lt->originBlock(), str);
    addToDataList(_T("Origin Block"), str);

	ArxRleUtils::symbolIdToName(lt->destinationBlock(), str);
    addToDataList(_T("Destination Block"), str);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(MLINE STYLE)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbMlineStyle* mlStyle)
{
    CString str;

    ASSERT(mlStyle != NULL);

    addSeperatorLine(_T("AcDbMlineStyle"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(PLACE HOLDER)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbPlaceHolder* placeHolder)
{
    CString str;

    ASSERT(placeHolder != NULL);

    addSeperatorLine(_T("AcDbPlaceHolder"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(PLOT SETTINGS)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbPlotSettings* plotSettings)
{
    CString str;

    ASSERT(plotSettings != NULL);

    addSeperatorLine(_T("AcDbPlotSettings"));

	AcDbLayout* layout;
	if ((layout = AcDbLayout::cast(plotSettings)) != NULL)
		display(layout);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    PROXY
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbProxyObject* proxy)
{
    CString str;

    ASSERT(proxy != NULL);

    addSeperatorLine(_T("AcDbProxyObject"));

    addToDataList(_T("Original Class Name"), proxy->originalClassName());
    addToDataList(_T("Original DXF Name"), proxy->originalDxfName());
    addToDataList(_T("Application Description"), proxy->applicationDescription());
    addToDataList(_T("Proxy Flags"), ArxRleUtils::intToStr(proxy->proxyFlags(), str));
    int flags = proxy->proxyFlags();
    if (flags & AcDbProxyObject::kEraseAllowed)
        addToDataList(NULL, _T("Erase Allowed"));
    if (flags & AcDbProxyObject::kCloningAllowed)
        addToDataList(NULL, _T("Cloning Allowed"));
	if (flags & AcDbProxyObject::kMergeIgnore)
		addToDataList(NULL, _T("Merge Ignore"));
	if (flags & AcDbProxyObject::kMergeReplace)
		addToDataList(NULL, _T("Merge Replace"));
	if (flags & AcDbProxyObject::kMergeMangleName)
		addToDataList(NULL, _T("Merge Mangle Name"));

    AcDbObjectIdArray refIds;
	AcDbIntArray intIds;
	Acad::ErrorStatus es = proxy->getReferences(refIds, intIds);
    if ((es == Acad::eOk) && (refIds.isEmpty() == false)) {
        addSeperatorLine(_T("References"));
        int len = refIds.length();
		AcDbObject* tmpObj;
        for (int i=0; i<len; i++) {
			if (refIds[i].isNull())
				addToDataList(NULL, _T("AcDbObjectId::kNull"));
			else {
				es = acdbOpenObject(tmpObj, refIds[i], AcDb::kForRead);
				if (es == Acad::eOk) {
					ArxRleUtils::objToClassAndHandleStr(tmpObj, str);
					addToDataList(NULL, str);
					tmpObj->close();
				}
				else
					addToDataList(NULL, ArxRleUtils::rxErrorStr(es));
			}
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(SYMBOL TABLE)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbSymbolTable* symTbl)
{
    CString str;

    ASSERT(symTbl != NULL);

    addSeperatorLine(_T("AcDbSymbolTable"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(SYMBOL TABLE RECORD)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbSymbolTableRecord* tblRec)
{
	ASSERT(tblRec != NULL);

    CString str;

	addSeperatorLine(_T("AcDbSymbolTableRecord"));

        // add entries common to all symbol table records
	addToDataList(_T("Is Dependent"), ArxRleUtils::booleanToStr(tblRec->isDependent(), str));
	addToDataList(_T("Is Resolved"), ArxRleUtils::booleanToStr(tblRec->isResolved(), str));

        // dispatch the appropriate display routine (wouldn't a virtual be nice!)
	AcDbAbstractViewTableRecord* abstractViewRecord;
    AcDbBlockTableRecord*  blkRecord;
    AcDbDimStyleTableRecord*  dimStyleRecord;
    AcDbLayerTableRecord*  layerRecord;
    AcDbLinetypeTableRecord*  linetypeRecord;
    AcDbRegAppTableRecord*  regAppRecord;
    AcDbTextStyleTableRecord*  textStyleRecord;
    AcDbUCSTableRecord*  ucsRecord;

    if ((abstractViewRecord = AcDbAbstractViewTableRecord::cast(tblRec)) != NULL)
        display(abstractViewRecord);
    else if ((blkRecord = AcDbBlockTableRecord::cast(tblRec)) != NULL)
        display(blkRecord);
    else if ((dimStyleRecord = AcDbDimStyleTableRecord::cast(tblRec)) != NULL)
        display(dimStyleRecord);
    else if ((layerRecord = AcDbLayerTableRecord::cast(tblRec)) != NULL)
        display(layerRecord);
    else if ((linetypeRecord = AcDbLinetypeTableRecord::cast(tblRec)) != NULL)
        display(linetypeRecord);
    else if ((regAppRecord = AcDbRegAppTableRecord::cast(tblRec)) != NULL)
        display(regAppRecord);
    else if ((textStyleRecord = AcDbTextStyleTableRecord::cast(tblRec)) != NULL)
        display(textStyleRecord);
    else if ((ucsRecord = AcDbUCSTableRecord::cast(tblRec)) != NULL)
        display(ucsRecord);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(XRECORD)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbXrecord* xrec)
{
    CString str;

    ASSERT(xrec != NULL);

    addSeperatorLine(_T("AcDbXrecord"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(DICTIONARY WITH DEFAULT)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbDictionaryWithDefault* dict)
{
    CString str;

    ASSERT(dict != NULL);

    addSeperatorLine(_T("AcDbDictionaryWithDefault"));

	AcDbObject* tmpObj;
	Acad::ErrorStatus es = acdbOpenObject(tmpObj, dict->defaultId(), AcDb::kForRead);
	if (es == Acad::eOk) {
		ArxRleUtils::objToClassAndHandleStr(tmpObj, str);
		addToDataList(_T("Default Object"), str);
		tmpObj->close();
	}
	else
		addToDataList(_T("Default Object"), ArxRleUtils::rxErrorStr(es));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    3DSOLID
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDb3dSolid* solid)
{
    CString str;
    double area, volume;
    AcGePoint3d centroid;
    double momInertia[3];
    double prodInertia[3];
    double prinMoments[3];
    AcGeVector3d prinAxes[3];
    double radiiGyration[3];
    AcDbExtents extents;
    Acad::ErrorStatus es;

    ASSERT(solid != NULL);

    addSeperatorLine(_T("AcDb3dSolid"));

    es = solid->getArea(area);
    if (es == Acad::eOk)
        addToDataList(_T("Area"), ArxRleUtils::doubleToStr(area, str));

    es = solid->getMassProp(volume, centroid, momInertia,
                prodInertia, prinMoments,
                prinAxes, radiiGyration, extents);
    if (es == Acad::eOk) {
        addToDataList(_T("Volume"), ArxRleUtils::doubleToStr(volume, str));
        addToDataList(_T("Centroid"), ArxRleUtils::ptToStr(centroid, str));
        addToDataList(_T("Mom. Of Inertia"), ArxRleUtils::doubleArray3dToStr(momInertia, str));
        addToDataList(_T("Prod. Of Inertia"), ArxRleUtils::doubleArray3dToStr(prodInertia,str));
        addToDataList(_T("Priciple Moments"), ArxRleUtils::doubleArray3dToStr(prinMoments, str));
        addToDataList(_T("Radii Gyration"), ArxRleUtils::doubleArray3dToStr(radiiGyration, str));
        addToDataList(_T("Principle Axes:"), _T(""));
        addToDataList(_T("   X Axis"), ArxRleUtils::vectorToStr(prinAxes[0], str));
        addToDataList(_T("   Y Axis"), ArxRleUtils::vectorToStr(prinAxes[1], str));
        addToDataList(_T("   Z Axis"), ArxRleUtils::vectorToStr(prinAxes[2], str));
        addToDataList(_T("Extmin"), ArxRleUtils::ptToStr(extents.minPoint(), str));
        addToDataList(_T("Extmax"), ArxRleUtils::ptToStr(extents.maxPoint(), str));
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(BLOCK BEGIN)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbBlockBegin* blkBegin)
{
    CString str;

    ASSERT(blkBegin != NULL);

    addSeperatorLine(_T("AcDbBlockBegin"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(BLOCK END)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbBlockEnd* blkEnd)
{
    CString str;

    ASSERT(blkEnd != NULL);

    addSeperatorLine(_T("AcDbBlockEnd"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    BLOCK REFERENCE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbBlockReference* blockRef)
{
    CString str;

    ASSERT(blockRef != NULL);

    addSeperatorLine(_T("AcDbBlockReference"));

    ArxRleUtils::symbolIdToName(blockRef->blockTableRecord(), str);
    addToDataList(_T("Block Name"), str);
    addToDataList(_T("Position"), ArxRleUtils::ptToStr(blockRef->position(), str));
    AcGeScale3d scales = blockRef->scaleFactors();
    addToDataList(_T("X Scale"), ArxRleUtils::doubleToStr(scales.sx, str));
    addToDataList(_T("Y Scale"), ArxRleUtils::doubleToStr(scales.sy, str));
    addToDataList(_T("Z Scale"), ArxRleUtils::doubleToStr(scales.sz, str));
    addToDataList(_T("Rotation"), ArxRleUtils::angleToStr(blockRef->rotation(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(blockRef->normal(), str));
    addToDataList(_T("Treat As BlockRef For Explode"), ArxRleUtils::booleanToStr(blockRef->treatAsAcDbBlockRefForExplode(), str));

    AcDbMInsertBlock* minsert;
    if ((minsert = AcDbMInsertBlock::cast(blockRef)) != NULL)
        display(minsert);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(BODY)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbBody* body)
{
    CString str;

    ASSERT(body != NULL);

    addSeperatorLine(_T("AcDbBody"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    CURVE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbCurve* curve)
{
    ASSERT(curve != NULL);

        // print out curve generic info
    AcGePlane plane;
    AcDb::Planarity planeType;
    double area;
    Acad::ErrorStatus es;
    CString str;

    addSeperatorLine(_T("AcDbCurve"));

    addToDataList(_T("Is Closed"), ArxRleUtils::booleanToStr(curve->isClosed(), str));
    addToDataList(_T("Is Periodic"), ArxRleUtils::booleanToStr(curve->isPeriodic(), str));

    curve->getPlane(plane, planeType);
    if (planeType == AcDb::kNonPlanar)
        str, _T("Non-Planar");
    else if (planeType == AcDb::kPlanar)
        str, _T("Planar");
    else
        str, _T("Linear");
    addToDataList(_T("Plane Type"), str);

    es = curve->getArea(area);
    if (es != Acad::eOk)
        addToDataList(_T("Area"), ArxRleUtils::doubleToStr(area, str));

    AcDb2dPolyline* pline2d;
    AcDb3dPolyline* pline3d;
    AcDbArc* arc;
    AcDbCircle* circle;
    AcDbEllipse* ellipse;
    AcDbLeader* leader;
    AcDbLine* line;
    AcDbPolyline* pline;
    AcDbRay* ray;
    AcDbSpline* spline;
    AcDbXline* xline;

    if ((pline2d = AcDb2dPolyline::cast(curve)) != NULL)
        display(pline2d);
    else if ((pline3d = AcDb3dPolyline::cast(curve)) != NULL)
        display(pline3d);
    else if ((arc = AcDbArc::cast(curve)) != NULL)
        display(arc);
    else if ((circle = AcDbCircle::cast(curve)) != NULL)
        display(circle);
    else if ((ellipse = AcDbEllipse::cast(curve)) != NULL)
        display(ellipse);
    else if ((leader = AcDbLeader::cast(curve)) != NULL)
        display(leader);
    else if ((line = AcDbLine::cast(curve)) != NULL)
        display(line);
    else if ((pline = AcDbPolyline::cast(curve)) != NULL)
        display(pline);
    else if ((ray = AcDbRay::cast(curve)) != NULL)
        display(ray);
    else if ((spline = AcDbSpline::cast(curve)) != NULL)
        display(spline);
    else if ((xline = AcDbXline::cast(curve)) != NULL)
        display(xline);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    DIMENSION
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbDimension"));

    ArxRleUtils::symbolIdToName(dim->dimensionStyle(), str);
    addToDataList(_T("Dimstyle"), str);
    addToDataList(_T("Text Position"), ArxRleUtils::ptToStr(dim->textPosition(), str));
    addToDataList(_T("Is Def Position"), ArxRleUtils::booleanToStr(dim->isUsingDefaultTextPosition(), str));
    ArxRleUtils::symbolIdToName(dim->dimBlockId(), str);
    addToDataList(_T("Block Name"), str);
    addToDataList(_T("Block Insert Pt"), ArxRleUtils::ptToStr(dim->dimBlockPosition(), str));

	TCHAR* tmpStr = dim->dimensionText();
    addToDataList(_T("Dimtext"), tmpStr, true);
	acutDelString(tmpStr);

	addToDataList(_T("Text Attachment"), ArxRleUtils::mtextAttachmentTypeToStr(dim->textAttachment(), str));
	addToDataList(_T("Text Line Spacing Style"), ArxRleUtils::lineSpacingTypeToStr(dim->textLineSpacingStyle(), str));
	addToDataList(_T("Text Line Spacing Factor"), ArxRleUtils::doubleToStr(dim->textLineSpacingFactor(), str));

    addToDataList(_T("Text Rotation"), ArxRleUtils::angleToStr(dim->textRotation(), str));
    addToDataList(_T("Horiz Rotation"), ArxRleUtils::angleToStr(dim->horizontalRotation(), str));
    addToDataList(_T("Elevation"), ArxRleUtils::doubleToStr(dim->elevation(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(dim->normal(), str));

        // dipatch appropriate display routine
    AcDb2LineAngularDimension* dim2Line;
    AcDb3PointAngularDimension* dim3Pt;
    AcDbDiametricDimension* dimDiam;
    AcDbAlignedDimension* dimAligned;    AcDbOrdinateDimension* dimOrdinate;

    AcDbRadialDimension* dimRadial;
    AcDbRotatedDimension* dimRotated;

    if ((dimAligned = AcDbAlignedDimension::cast(dim)) != NULL)
        display(dimAligned);
    else if ((dim3Pt = AcDb3PointAngularDimension::cast(dim)) != NULL)
        display(dim3Pt);
    else if ((dim2Line = AcDb2LineAngularDimension::cast(dim)) != NULL)
        display(dim2Line);
    else if ((dimDiam = AcDbDiametricDimension::cast(dim)) != NULL)
        display(dimDiam);
    else if ((dimRadial = AcDbRadialDimension::cast(dim)) != NULL)
        display(dimRadial);
    else if ((dimRotated = AcDbRotatedDimension::cast(dim)) != NULL)
        display(dimRotated);
    else if ((dimOrdinate = AcDbOrdinateDimension::cast(dim)) != NULL)
        display(dimOrdinate);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    FACE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbFace* face)
{
    CString str, str2;
    AcGePoint3d pt;
    int i;
    Adesk::Boolean visible;

    ASSERT(face != NULL);

    for (i=0;i<4;i++) {
        if (face->getVertexAt(i, pt) == Acad::eOk) {
            str2.Format(_T("Pt #%2d"), i+1);
            addToDataList(str2, ArxRleUtils::ptToStr(pt, str));
        }
    }
    for (i=0;i<4;i++) {
        if (face->isEdgeVisibleAt(i, visible) == Acad::eOk) {
            str2.Format(_T("Edge #%2d Visible"), i+1);
            addToDataList(str2, ArxRleUtils::booleanToStr(visible, str));
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    FACE RECORD
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbFaceRecord* vface)
{
    int i;
    Acad::ErrorStatus es1, es2;
    Adesk::Int16 vtxIndex;
    Adesk::Boolean visible;
    CString str, str2, str3;

    ASSERT(vface != NULL);

    addSeperatorLine(_T("AcDbFaceRecord"));

    for (i=0;i<4;i++) {
        es1 = vface->getVertexAt(i, vtxIndex);
        es2 = vface->isEdgeVisibleAt(i, visible);    
        if ((es1 == Acad::eOk) && (es2 == Acad::eOk)) {
            str.Format(_T("Vface Pt #%2d"), i+1);
            str2.Format(_T("(index=%d, visible=%s)"), vtxIndex,
                        ArxRleUtils::booleanToStr(visible, str3));
            addToDataList(str, str2);
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    FCF
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbFcf* fcf)
{
    CString str, str2;

    ASSERT(fcf != NULL);

    addSeperatorLine(_T("AcDbFcf"));

    addToDataList(_T("Location"), ArxRleUtils::ptToStr(fcf->location(), str));
    ArxRleUtils::symbolIdToName(fcf->dimensionStyle(), str);
    addToDataList(_T("Dimstyle"), str);

    AcGePoint3dArray ptArray;
    fcf->getBoundingPoints(ptArray);
    int i, len;
    len = ptArray.length();
    for (i=0;i<len;i++) {
        str2.Format(_T("Bouding Pt #%2d"), i+1);
        addToDataList(str2, ArxRleUtils::ptToStr(ptArray.at(i), str));
    }

    addToDataList(_T("Direction"), ArxRleUtils::vectorToStr(fcf->direction(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(fcf->normal(), str));

    TCHAR* tmpTxt = fcf->text();
    if (tmpTxt) {
        addToDataList(_T("Text"), tmpTxt, true);
        acutDelString(tmpTxt);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(FRAME)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbFrame* frame)
{
    CString str;

    ASSERT(frame != NULL);

    addSeperatorLine(_T("AcDbFrame"));

	AcDbOleFrame* oleFrame;
	AcDbOle2Frame* ole2Frame;

	if ((oleFrame = AcDbOleFrame::cast(frame)) != NULL)
		display(oleFrame);
	else if ((ole2Frame = AcDbOle2Frame::cast(frame)) != NULL)
		display(ole2Frame);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(IMAGE)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbImage* image)
{
    CString str;

    ASSERT(image != NULL);

    addSeperatorLine(_T("AcDbImage"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    HATCH
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbHatch* hatch)
{
    CString str, str2;
    Adesk::Int32 loopType;
    AcGeVoidPointerArray edgePtrs;
    AcGeIntArray edgeTypes;
    Acad::ErrorStatus es;

	ASSERT(hatch != NULL);

    addSeperatorLine(_T("AcDbHatch"));

        // basic info
    addToDataList(_T("Elevation"), ArxRleUtils::doubleToStr(hatch->elevation(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(hatch->normal(), str));
    addToDataList(_T("Is Associative"), ArxRleUtils::booleanToStr(hatch->associative(), str));

        // pattern info
    addToDataList(_T("Hatch Pattern Type"), ArxRleUtils::hatchTypeToStr(hatch->patternType(), str));
    addToDataList(_T("Pattern Name"), hatch->patternName(), true);
    addToDataList(_T("Pattern Angle"), ArxRleUtils::angleToStr(hatch->patternAngle(), str));
    addToDataList(_T("Pattern Space"), ArxRleUtils::doubleToStr(hatch->patternSpace(), str));
    addToDataList(_T("Pattern Scale"), ArxRleUtils::doubleToStr(hatch->patternScale(), str));
    addToDataList(_T("Is Pattern Double"), ArxRleUtils::booleanToStr(hatch->patternDouble(), str));

        // style info
    addToDataList(_T("Hatch Style"), ArxRleUtils::hatchStyleToStr(hatch->hatchStyle(), str));

        // loop info
    for (int i=0; i<hatch->numLoops(); i++) {
        str2.Format(_T("Loop #%d"), i+1);
        addSeperatorLine(str2);

        es = hatch->getLoopAt(i, loopType, edgePtrs, edgeTypes);
        if (es == Acad::eOk) {
            addToDataList(_T("Loop Type"), ArxRleUtils::hatchLoopTypeToStr(loopType, str));

            int len = edgePtrs.length();
            for (int j=0; j<len; j++) {
                str2.Format(_T("Edge #%d"), j+1);
                addSeperatorLine(str2);
                displayGeCurve2d(static_cast<AcGeCurve2d*>(edgePtrs[j]), edgeTypes[j]);
            }

            edgePtrs.setLogicalLength(0);
            edgeTypes.setLogicalLength(0);
        }
        else
            addToDataList(_T("ERROR"), _T("Could not get loop"));
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    MLINE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbMline* mline)
{
    CString str, str2;

    ASSERT(mline != NULL);

    addSeperatorLine(_T("AcDbMline"));

    ArxRleUtils::mlineStyleIdToName(mline->style(), str);
    addToDataList(_T("Style"), str, true);
    Mline::MlineJustification justif = mline->justification();
    if (justif == Mline::kTop)
        str = _T("Top");
    else if (justif == Mline::kZero)
        str = _T("Zero");
    else if (justif == Mline::kBottom)
        str = _T("Bottom");
    else {
        ASSERT(0);
    }
    addToDataList(_T("Justification"), str);
    addToDataList(_T("Scale"), ArxRleUtils::doubleToStr(mline->scale(), str));
    addToDataList(_T("Is Closed"), ArxRleUtils::booleanToStr(mline->closedMline(), str));
    addToDataList(_T("Suppress Start Caps"), ArxRleUtils::booleanToStr(mline->supressStartCaps(), str));
    addToDataList(_T("Suppress End Caps"), ArxRleUtils::booleanToStr(mline->supressEndCaps(), str));
    int len = mline->numVertices();
    for (int i=0;i<len;i++) {
        str2.Format(_T("Vertex #%2d"), i+1);
        addToDataList(str2, ArxRleUtils::ptToStr(mline->vertexAt(i), str));
    }
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(mline->normal(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    MTEXT
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbMText* mtext)
{
    CString str, str2;

    ASSERT(mtext != NULL);

    addSeperatorLine(_T("AcDbMText"));

    addToDataList(_T("Location"), ArxRleUtils::ptToStr(mtext->location(), str));
    addToDataList(_T("Rotation"), ArxRleUtils::angleToStr(mtext->rotation(), str));
    addToDataList(_T("Width"), ArxRleUtils::doubleToStr(mtext->width(), str));
    addToDataList(_T("Text Height"), ArxRleUtils::doubleToStr(mtext->textHeight(), str));
    ArxRleUtils::symbolIdToName(mtext->textStyle(), str);
    addToDataList(_T("Text Style"), str);

	addToDataList(_T("Attachment"), ArxRleUtils::mtextAttachmentTypeToStr(mtext->attachment(), str));
    addToDataList(_T("Flow Dir"), ArxRleUtils::mtextFlowDirTypeToStr(mtext->flowDirection(), str));

    AcGePoint3dArray ptArray;
    mtext->getBoundingPoints(ptArray);
    int i, len;
    len = ptArray.length();
    for (i=0;i<len;i++) {
        str2.Format(_T("Bounding Pt #%2d"), i+1);
        addToDataList(str2, ArxRleUtils::ptToStr(ptArray.at(i), str));
    }

    addToDataList(_T("Actual Height"), ArxRleUtils::doubleToStr(mtext->actualHeight(), str));
    addToDataList(_T("Actual Width"), ArxRleUtils::doubleToStr(mtext->actualWidth(), str));
    addToDataList(_T("Contents"), mtext->contents());
    addToDataList(_T("Line Spacing Style"), ArxRleUtils::lineSpacingTypeToStr(mtext->lineSpacingStyle(), str));
    addToDataList(_T("Line Spacing Factor"), ArxRleUtils::doubleToStr(mtext->lineSpacingFactor(), str));

    addToDataList(_T("Direction"), ArxRleUtils::vectorToStr(mtext->direction(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(mtext->normal(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    POINT
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbPoint* point)
{
    AcGePoint3d pt;
    CString str;

    ASSERT(point != NULL);

    addSeperatorLine(_T("AcDbPoint"));

    addToDataList(_T("Position"), ArxRleUtils::ptToStr(point->position(), str));
    addToDataList(_T("Thickness"), ArxRleUtils::doubleToStr(point->thickness(), str));
    addToDataList(_T("ECS Rotation"), ArxRleUtils::angleToStr(point->ecsRotation(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(point->normal(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    PFACE MESH
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbPolyFaceMesh* pface)
{
    CString str;

    ASSERT(pface != NULL);

    addSeperatorLine(_T("AcDbPolyFaceMesh"));

    addToDataList(_T("Vertex Count"), ArxRleUtils::intToStr(pface->numVertices(), str));
    addToDataList(_T("Face Count"), ArxRleUtils::intToStr(pface->numFaces(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    POLYGON MESH
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbPolygonMesh* mesh)
{
    CString str;

    ASSERT(mesh != NULL);

    addSeperatorLine(_T("AcDbPolygonMesh"));

    AcDb::PolyMeshType pmeshType = mesh->polyMeshType();
    if (pmeshType == AcDb::kSimpleMesh)
        str = _T("Simple Mesh");
    else if (pmeshType == AcDb::kQuadSurfaceMesh)
        str = _T("Quad Surface Mesh");
    else if (pmeshType == AcDb::kCubicSurfaceMesh)
        str = _T("Cubic Surface Mesh");
    else if (pmeshType == AcDb::kBezierSurfaceMesh)
        str = _T("Bezier Surface Mesh");
	else {
		ASSERT(0);
		str = _T("*Unknown*");
	}

    addToDataList(_T("Pmesh Type"), str);
    addToDataList(_T("M Size"), ArxRleUtils::intToStr(mesh->mSize(), str));
    addToDataList(_T("N Size"), ArxRleUtils::intToStr(mesh->nSize(), str));
    addToDataList(_T("M Is Closed"), ArxRleUtils::booleanToStr(mesh->isMClosed(), str));
    addToDataList(_T("N Is Closed"), ArxRleUtils::booleanToStr(mesh->isNClosed(), str));
    addToDataList(_T("M Surface Density"), ArxRleUtils::intToStr(mesh->mSurfaceDensity(), str));
    addToDataList(_T("N Surface Density"), ArxRleUtils::intToStr(mesh->nSurfaceDensity(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    PROXY
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbProxyEntity* proxy)
{
    CString str;

    ASSERT(proxy != NULL);

    addSeperatorLine(_T("AcDbProxyEntity"));

    addToDataList(_T("Original Class Name"), proxy->originalClassName());
    addToDataList(_T("Original DXF Name"), proxy->originalDxfName());
    addToDataList(_T("Application Description"), proxy->applicationDescription());
    addToDataList(_T("Has Graphics Metafile"), ArxRleUtils::proxyMetafileTypeToStr(proxy->graphicsMetafileType(), str));
    addToDataList(_T("Proxy Flags"), ArxRleUtils::intToStr(proxy->proxyFlags(), str));
    int flags = proxy->proxyFlags();
    if (flags & AcDbProxyEntity::kEraseAllowed)
        addToDataList(_T(""), _T("Erase Allowed"));
    if (flags & AcDbProxyEntity::kTransformAllowed)
        addToDataList(_T(""), _T("Transform Allowed"));
    if (flags & AcDbProxyEntity::kColorChangeAllowed)
        addToDataList(_T(""), _T("Color Change Allowed"));
    if (flags & AcDbProxyEntity::kLayerChangeAllowed)
        addToDataList(_T(""), _T("Layer Change Allowed"));
    if (flags & AcDbProxyEntity::kLinetypeChangeAllowed)
        addToDataList(_T(""), _T("Linetype Change Allowed"));
    if (flags & AcDbProxyEntity::kLinetypeScaleChangeAllowed)
        addToDataList(_T(""), _T("Linetype Scale Change Allowed"));
    if (flags & AcDbProxyEntity::kLineWeightChangeAllowed)
        addToDataList(_T(""), _T("Line Weight Change Allowed"));
    if (flags & AcDbProxyEntity::kPlotStyleNameChangeAllowed)
        addToDataList(_T(""), _T("Plot Style Name Change Allowed"));
    if (flags & AcDbProxyEntity::kVisibilityChangeAllowed)
        addToDataList(_T(""), _T("Visibility Change Allowed"));
    if (flags & AcDbProxyEntity::kCloningAllowed)
        addToDataList(_T(""), _T("Cloning Allowed"));

    AcDbObjectIdArray refIds;
	AcDbIntArray intIds;
	Acad::ErrorStatus es = proxy->getReferences(refIds, intIds);
    if ((es == Acad::eOk) && (refIds.isEmpty() == false)) {
        addSeperatorLine(_T("References"));
        int len = refIds.length();
		AcDbObject* tmpObj;
        for (int i=0; i<len; i++) {
			if (refIds[i].isNull())
				addToDataList(_T(""), _T("AcDbObjectId::kNull"));
			else {
				es = acdbOpenObject(tmpObj, refIds[i], AcDb::kForRead);
				if (es == Acad::eOk) {
					ArxRleUtils::objToClassAndHandleStr(tmpObj, str);
					addToDataList(_T(""), str);
					tmpObj->close();
				}
				else
					addToDataList(_T(""), ArxRleUtils::rxErrorStr(es));
			}
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    REGION
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbRegion* pRegion)
{
    CString str;
    double perimeter, area;
    Acad::ErrorStatus es;
    AcGePoint3d origin;
    AcGeVector3d xAxis, yAxis;
    AcGePoint2d centroid;
    double momInertia[2], prodInertia, prinMoments[2], radiiGyration[2];
    AcGeVector2d prinAxes[2];
    AcGePoint2d extentsLow, extentsHigh;

    ASSERT(pRegion != NULL);

    addSeperatorLine(_T("AcDbRegion"));

    es = pRegion->getPerimeter(perimeter);
    if (es == Acad::eOk)
        addToDataList(_T("Perimeter"), ArxRleUtils::doubleToStr(perimeter, str));

    es = pRegion->getArea(area);
    if (es == Acad::eOk)
        addToDataList(_T("Area"), ArxRleUtils::doubleToStr(area, str));

	// the following 3 lines of code are added to
	// get the proper info (for getAreaProp()) from the plane it is in
	// see solution #44949 for more explanation
	AcGePlane plane;
	pRegion->getPlane(plane);
	plane.getCoordSystem(origin, xAxis, yAxis);

    es = pRegion->getAreaProp(origin, xAxis, yAxis, perimeter, area, centroid, momInertia,
                prodInertia, prinMoments,
                prinAxes, radiiGyration, extentsLow, extentsHigh);
    if (es == Acad::eOk) {
        addToDataList(_T("Origin"), ArxRleUtils::ptToStr(origin, str));
        addToDataList(_T("X Axis"), ArxRleUtils::vectorToStr(xAxis, str));
        addToDataList(_T("Y Axis"), ArxRleUtils::vectorToStr(yAxis, str));
        addToDataList(_T("Perimeter"), ArxRleUtils::doubleToStr(perimeter, str));
        addToDataList(_T("Area"), ArxRleUtils::doubleToStr(area, str));
        addToDataList(_T("Centroid"), ArxRleUtils::ptToStr(centroid, str));
        addToDataList(_T("Mom. Of Inertia"), ArxRleUtils::doubleArray2dToStr(momInertia, str));
        addToDataList(_T("Prod. Of Inertia"), ArxRleUtils::doubleToStr(prodInertia, str));
        addToDataList(_T("Principle Moments"), ArxRleUtils::doubleArray2dToStr(prinMoments, str));
        addToDataList(_T("Radii Gyration"), ArxRleUtils::doubleArray2dToStr(radiiGyration, str));
        addToDataList(_T("Principle Axes:"), _T(""));
        addToDataList(_T("   X Axis"), ArxRleUtils::vectorToStr(prinAxes[0], str));
        addToDataList(_T("   Y Axis"), ArxRleUtils::vectorToStr(prinAxes[1], str));
        addToDataList(_T("Extents Low"), ArxRleUtils::ptToStr(extentsLow, str));
        addToDataList(_T("Extents High"), ArxRleUtils::ptToStr(extentsHigh, str));
    }
    else {
        ArxRleUtils::stopAlertBox(_T("ERROR calling AcDbRegion::getAreaProp()"));
        ArxRleUtils::rxErrorAlert(es);
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    SEQUENCE END
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbSequenceEnd* seqEnd)
{
    ASSERT(seqEnd != NULL);

    addSeperatorLine(_T("AcDbSequenceEnd"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    SHAPE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbShape* shape)
{
    CString str;

    ASSERT(shape != NULL);

    addSeperatorLine(_T("AcDbShape"));

    addToDataList(_T("Position"), ArxRleUtils::ptToStr(shape->position(), str));
    addToDataList(_T("Size"), ArxRleUtils::doubleToStr(shape->size(), str));
    addToDataList(_T("Name"), shape->name(), true);
    addToDataList(_T("Rotation"), ArxRleUtils::angleToStr(shape->rotation(), str));
    addToDataList(_T("Width Factor"), ArxRleUtils::doubleToStr(shape->widthFactor(), str));
    addToDataList(_T("Oblique"), ArxRleUtils::angleToStr(shape->oblique(), str));
    addToDataList(_T("Thickness:"), ArxRleUtils::doubleToStr(shape->thickness(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(shape->normal(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    SOLID
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbSolid* solid)
{
    AcGePoint3d pt;
    int i;
    CString str, str2;

    ASSERT(solid != NULL);

    addSeperatorLine(_T("AcDbSolid"));

    for (i=0;i<4;i++) {
        if (solid->getPointAt(i, pt) == Acad::eOk) {
            str2.Format(_T("Pt #%2d"), i+1);
            addToDataList(str2, ArxRleUtils::ptToStr(pt, str));
        }
    }
    addToDataList(_T("Thickness"), ArxRleUtils::doubleToStr(solid->thickness(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(solid->normal(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    TEXT
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbText* text)
{
    CString str;
    CString tmpStr;

    ASSERT(text != NULL);

    addSeperatorLine(_T("AcDbText"));

    const TCHAR* tmpStr2 = text->textStringConst();
    addToDataList(_T("Text"), tmpStr2, true);

    ArxRleUtils::symbolIdToName(text->textStyle(), str);
    addToDataList(_T("Text Style"), str);
    addToDataList(_T("Position"), ArxRleUtils::ptToStr(text->position(), str));
    addToDataList(_T("Is Def Alignment"), ArxRleUtils::booleanToStr(text->isDefaultAlignment(), str));
    if (text->isDefaultAlignment() == Adesk::kFalse)
        addToDataList(_T("Alignment Pt"), ArxRleUtils::ptToStr(text->alignmentPoint(), str));

    addToDataList(_T("Thickness"), ArxRleUtils::doubleToStr(text->thickness(), str));
    addToDataList(_T("Oblique Angle"), ArxRleUtils::angleToStr(text->oblique(), str));
    addToDataList(_T("Rotation"), ArxRleUtils::angleToStr(text->rotation(), str));
    addToDataList(_T("Height"), ArxRleUtils::doubleToStr(text->height(), str));
    addToDataList(_T("Width Factor"), ArxRleUtils::doubleToStr(text->widthFactor(), str));
    addToDataList(_T("Is Mirrored In X"), ArxRleUtils::booleanToStr(text->isMirroredInX(), str));
    addToDataList(_T("Is Mirrored In Y"), ArxRleUtils::booleanToStr(text->isMirroredInY(), str));
    addToDataList(_T("Horizontal Mode"), ArxRleUtils::textModeToStr(text->horizontalMode(), str));
    addToDataList(_T("Vertical Mode"), ArxRleUtils::textModeToStr(text->verticalMode(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(text->normal(), str));

    AcDbAttribute* attrib;
    AcDbAttributeDefinition* attdef;
    if ((attrib = AcDbAttribute::cast(text)) != NULL)
        display(attrib);
    else if ((attdef = AcDbAttributeDefinition::cast(text)) != NULL)
        display(attdef);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    TRACE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbTrace* trace)
{
    AcGePoint3d pt;
    int i;
    CString str, str2;

    ASSERT(trace != NULL);

    addSeperatorLine(_T("AcDbTrace"));

    for (i=0;i<4;i++) {
        if (trace->getPointAt(i, pt) == Acad::eOk) {
            str2.Format(_T("Pt #%2d"), i+1);
            addToDataList(str2, ArxRleUtils::ptToStr(pt, str));
        }
    }
    addToDataList(_T("Thickness"), ArxRleUtils::doubleToStr(trace->thickness(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(trace->normal(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    VERTEX
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbVertex* vertex)
{
    ASSERT(vertex != NULL);

    addSeperatorLine(_T("AcDbVertex"));

    AcDb2dVertex* vertex2d;
    AcDb3dPolylineVertex* vertex3d;
    AcDbPolyFaceMeshVertex* pface;
    AcDbPolygonMeshVertex* mesh;

    if ((vertex2d = AcDb2dVertex::cast(vertex)) != NULL)
        display(vertex2d);
    else if ((vertex3d = AcDb3dPolylineVertex::cast(vertex)) != NULL)
        display(vertex3d);
    else if ((pface = AcDbPolyFaceMeshVertex::cast(vertex)) != NULL)
        display(pface);
    else if ((mesh = AcDbPolygonMeshVertex::cast(vertex)) != NULL)
        display(mesh);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    VIEWPORT
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbViewport* viewport)
{
    CString str;

    ASSERT(viewport != NULL);

    addSeperatorLine(_T("AcDbViewport"));

    //if (viewport->database() != acdbHostApplicationServices()->workingDatabase()) {
    //    ArxRleUtils::stopAlertBox(_T("This AcDbViewport belongs to a database not currently loaded in the AutoCAD editor.  AutoCAD does not like this, request for info ignored to prevent crash!"));
    //    return;
    //}

    addToDataList(_T("Height"), ArxRleUtils::doubleToStr(viewport->height(), str));
    addToDataList(_T("Width"), ArxRleUtils::doubleToStr(viewport->width(), str));
    addToDataList(_T("Center Pt"), ArxRleUtils::ptToStr(viewport->centerPoint(), str));
    addToDataList(_T("Number"), ArxRleUtils::intToStr(viewport->number(), str));
    addToDataList(_T("Is On"), ArxRleUtils::booleanToStr(viewport->isOn(), str));
    addToDataList(_T("View Target"), ArxRleUtils::ptToStr(viewport->viewTarget(), str));
    addToDataList(_T("View Dir"), ArxRleUtils::vectorToStr(viewport->viewDirection(), str));
    addToDataList(_T("View Height"), ArxRleUtils::doubleToStr(viewport->viewHeight(), str));
    addToDataList(_T("View Center"), ArxRleUtils::ptToStr(viewport->viewCenter(), str));
    addToDataList(_T("Twist Angle"), ArxRleUtils::angleToStr(viewport->twistAngle(), str));
    addToDataList(_T("Lens Length"), ArxRleUtils::doubleToStr(viewport->lensLength(), str));
    addToDataList(_T("Front Clip On"), ArxRleUtils::booleanToStr(viewport->isFrontClipOn(), str));
    addToDataList(_T("Back Clip On"), ArxRleUtils::booleanToStr(viewport->isBackClipOn(), str));
    addToDataList(_T("Front Clip At Eye"), ArxRleUtils::booleanToStr(viewport->isFrontClipAtEyeOn(), str));
    addToDataList(_T("Front Clip Dist"), ArxRleUtils::doubleToStr(viewport->frontClipDistance(), str));
    addToDataList(_T("Back Clip Dist"), ArxRleUtils::doubleToStr(viewport->backClipDistance(), str));
    addToDataList(_T("Perspective On"), ArxRleUtils::booleanToStr(viewport->isPerspectiveOn(), str));
    addToDataList(_T("UCS Follow On"), ArxRleUtils::booleanToStr(viewport->isUcsFollowModeOn(), str));
    addToDataList(_T("UCS Icon Visible"), ArxRleUtils::booleanToStr(viewport->isUcsIconVisible(), str));
    addToDataList(_T("UCS Icon At Origin"), ArxRleUtils::booleanToStr(viewport->isUcsIconAtOrigin(), str));
    addToDataList(_T("Fast Zoom On"), ArxRleUtils::booleanToStr(viewport->isFastZoomOn(), str));
    addToDataList(_T("Circle Sides"), ArxRleUtils::intToStr(viewport->circleSides(), str));
    addToDataList(_T("Snap On"), ArxRleUtils::booleanToStr(viewport->isSnapOn(), str));
    addToDataList(_T("Snap Isometric"), ArxRleUtils::booleanToStr(viewport->isSnapIsometric(), str));
    addToDataList(_T("Snap Angle"), ArxRleUtils::angleToStr(viewport->snapAngle(), str));
    addToDataList(_T("Snap Base Pt"), ArxRleUtils::ptToStr(viewport->snapBasePoint(), str));
    addToDataList(_T("Snap Increment"), ArxRleUtils::vectorToStr(viewport->snapIncrement(), str));
    addToDataList(_T("Snap Iso Pair"), ArxRleUtils::intToStr(viewport->snapIsoPair(), str));
    addToDataList(_T("Grid On"), ArxRleUtils::booleanToStr(viewport->isGridOn(), str));
    addToDataList(_T("Grid Increment"), ArxRleUtils::vectorToStr(viewport->gridIncrement(), str));
    addToDataList(_T("Hidden Lines"), ArxRleUtils::booleanToStr(viewport->hiddenLinesRemoved(), str));
    addToDataList(_T("Is Locked"), ArxRleUtils::booleanToStr(viewport->isLocked(), str));
    addToDataList(_T("Is Transparent"), ArxRleUtils::booleanToStr(viewport->isTransparent(), str));
    addToDataList(_T("Custom Scale"), ArxRleUtils::doubleToStr(viewport->customScale(), str));
    addToDataList(_T("Standard Scale Type"), ArxRleUtils::standardScaleTypeToStr(viewport->standardScale(), str));

    const TCHAR* tmpStr = NULL;
    Acad::ErrorStatus es = viewport->plotStyleSheet(tmpStr);
    if (es == Acad::eOk)
        addToDataList(_T("Plot Style Sheet"), tmpStr, true);
	else
        addToDataList(_T("Plot Style Sheet"), ArxRleUtils::rxErrorStr(es));

    es = viewport->effectivePlotStyleSheet(tmpStr);
    if (es == Acad::eOk)
        addToDataList(_T("Effective Plot Style Sheet"), tmpStr, true);
	else
        addToDataList(_T("Effective Plot Style Sheet"), ArxRleUtils::rxErrorStr(es));

    addToDataList(_T("Non-Rect Clip On"), ArxRleUtils::booleanToStr(viewport->isNonRectClipOn(), str));

	AcDbObject* tmpObj;
	es = acdbOpenObject(tmpObj, viewport->nonRectClipEntityId(), AcDb::kForRead);
	if (es == Acad::eOk) {
		addToDataList(_T("Non-Rect Clip Entity"), ArxRleUtils::objToClassAndHandleStr(tmpObj, str));
		tmpObj->close();
	}
	else
		addToDataList(_T("Non-Rect Clip Entity"), ArxRleUtils::rxErrorStr(es));

	AcGePoint3d origin;
	AcGeVector3d xAxis, yAxis;
	es = viewport->getUcs(origin, xAxis, yAxis);
	if (es == Acad::eOk) {
		addToDataList(_T("UCS Origin"), ArxRleUtils::ptToStr(origin, str));
		addToDataList(_T("UCS X Axis"), ArxRleUtils::vectorToStr(xAxis, str));
		addToDataList(_T("UCS Y Axis"), ArxRleUtils::vectorToStr(yAxis, str));
	}
	else
		addToDataList(_T("UCS Info"), ArxRleUtils::rxErrorStr(es));

	AcDb::OrthographicView orthoView;
	bool ucsIsOrtho = viewport->isUcsOrthographic(orthoView);
	addToDataList(_T("Is UCS Orthographic"), ArxRleUtils::booleanToStr(ucsIsOrtho, str));
	if (ucsIsOrtho)
		addToDataList(_T("UCS Orthographic View"), ArxRleUtils::orthoViewToStr(orthoView, str));
    
	ArxRleUtils::symbolIdToName(viewport->ucsName(), str);
	addToDataList(_T("UCS Name"), str);
	addToDataList(_T("Is UCS Saved With Viewport"), ArxRleUtils::booleanToStr(viewport->isUcsSavedWithViewport(), str));
	addToDataList(_T("Elevation"), ArxRleUtils::doubleToStr(viewport->elevation(), str));

	bool viewIsOrtho = viewport->isViewOrthographic(orthoView);
	addToDataList(_T("Is View Orthographic"), ArxRleUtils::booleanToStr(viewIsOrtho, str));
	if (viewIsOrtho)
		addToDataList(_T("Orthographic View"), ArxRleUtils::orthoViewToStr(orthoView, str));

    AcDbObjectIdArray frozenLayers;
    es = viewport->getFrozenLayerList(frozenLayers);
    if ((es == Acad::eOk) && (frozenLayers.isEmpty() == Adesk::kFalse)) {
        addSeperatorLine(_T("Frozen Layers"));
        int len = frozenLayers.length();
        for (int i=0; i<len; i++) {
            ArxRleUtils::symbolIdToName(frozenLayers[i], str);
            addToDataList(_T(""), str);
        }
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display:    MINSERT BLOCK
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbMInsertBlock* mInsert)
{
    CString str;

    ASSERT(mInsert != NULL);

    addSeperatorLine(_T("AcDbMInsertBlock"));

    addToDataList(_T("Columns"), ArxRleUtils::intToStr(mInsert->columns(), str));
    addToDataList(_T("Rows"), ArxRleUtils::intToStr(mInsert->rows(), str));
    addToDataList(_T("Column Spacing"), ArxRleUtils::doubleToStr(mInsert->columnSpacing(), str));
    addToDataList(_T("Row Spacing"), ArxRleUtils::doubleToStr(mInsert->rowSpacing(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    2D POLYLINE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDb2dPolyline* pline)
{
    CString str;

    ASSERT(pline != NULL);

    addSeperatorLine(_T("AcDb2dPolyline"));

    AcDb::Poly2dType ptype = pline->polyType();
    if (ptype == AcDb::k2dSimplePoly)
        str = _T("Simple");
    else if (ptype == AcDb::k2dFitCurvePoly)
        str = _T("Fit Curve");
    else if (ptype == AcDb::k2dQuadSplinePoly)
        str = _T("Quadratic Spline");
    else if (ptype == AcDb::k2dCubicSplinePoly)
        str = _T("Cubic Spline");
	else {
		ASSERT(0);
		str = _T("*Unknown*");
	}

    addToDataList(_T("2D Pline Type"), str);
    addToDataList(_T("Def Start Width"), ArxRleUtils::doubleToStr(pline->defaultStartWidth(), str));
    addToDataList(_T("Def End Width"), ArxRleUtils::doubleToStr(pline->defaultEndWidth(), str));
    addToDataList(_T("Linetype Gen On"), ArxRleUtils::doubleToStr(pline->isLinetypeGenerationOn(), str));
    addToDataList(_T("Elevation"), ArxRleUtils::doubleToStr(pline->elevation(), str));
    addToDataList(_T("Thickness"), ArxRleUtils::doubleToStr(pline->thickness(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(pline->normal(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    3D POLYLINE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDb3dPolyline* pline)
{
    CString str;

    ASSERT(pline != NULL);

    addSeperatorLine(_T("AcDb3dPolyline"));

    AcDb::Poly3dType ptype = pline->polyType();
    if (ptype == AcDb::k3dSimplePoly)
        str = _T("Simple");
    else if (ptype == AcDb::k3dQuadSplinePoly)
        str = _T("Quadratic Spline");
    else if (ptype == AcDb::k3dCubicSplinePoly)
        str = _T("Cubic Spline");
	else {
		ASSERT(0);
		str = _T("*Unknown*");
	}

    addToDataList(_T("3D Pline Type"), str);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    ARC
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbArc* arc)
{
    CString str;

    ASSERT(arc != NULL);

    addSeperatorLine(_T("AcDbArc"));

    addToDataList(_T("Center Pt"), ArxRleUtils::ptToStr(arc->center(), str));
    addToDataList(_T("Radius"), ArxRleUtils::doubleToStr(arc->radius(), str));
    addToDataList(_T("Start Angle"), ArxRleUtils::angleToStr(arc->startAngle(), str));
    addToDataList(_T("End Angle"), ArxRleUtils::angleToStr(arc->endAngle(), str));
    addToDataList(_T("Thickness"), ArxRleUtils::doubleToStr(arc->thickness(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(arc->normal(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    CIRCLE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbCircle* circle)
{
    CString str;

    ASSERT(circle != NULL);

    addSeperatorLine(_T("AcDbCircle"));

    addToDataList(_T("Center Pt"), ArxRleUtils::ptToStr(circle->center(), str));
    addToDataList(_T("Radius"), ArxRleUtils::doubleToStr(circle->radius(), str));
    addToDataList(_T("Thickness"), ArxRleUtils::doubleToStr(circle->thickness(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(circle->normal(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    ELLIPSE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbEllipse* ellipse)
{
    CString str;

    ASSERT(ellipse != NULL);

    addSeperatorLine(_T("AcDbEllipse"));

    addToDataList(_T("Center Pt"), ArxRleUtils::ptToStr(ellipse->center(), str));
    addToDataList(_T("Major Axis"), ArxRleUtils::vectorToStr(ellipse->majorAxis(), str));
    addToDataList(_T("Minor Axis"), ArxRleUtils::vectorToStr(ellipse->minorAxis(), str));
    addToDataList(_T("Radius Ratio"), ArxRleUtils::doubleToStr(ellipse->radiusRatio(), str));
    addToDataList(_T("Start Angle"), ArxRleUtils::angleToStr(ellipse->startAngle(), str));
    addToDataList(_T("End Angle"), ArxRleUtils::angleToStr(ellipse->endAngle(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(ellipse->normal(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    LEADER
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbLeader* leader)
{
    CString str, str2;

    ASSERT(leader != NULL);

    addSeperatorLine(_T("AcDbLeader"));

    int numVerts = leader->numVertices();
    for (int i=0;i<numVerts;i++) {
        str2.Format(_T("Vertex #%2d"), i+1);
        addToDataList(str2, ArxRleUtils::ptToStr(leader->vertexAt(i), str));
    }
    ArxRleUtils::symbolIdToName(leader->dimensionStyle(), str);
    addToDataList(_T("Dimstyle"), str);
    addToDataList(_T("Has Arrow Head"), ArxRleUtils::booleanToStr(leader->hasArrowHead(), str));
    addToDataList(_T("Has Hook Line"), ArxRleUtils::booleanToStr(leader->hasHookLine(), str));
    addToDataList(_T("Is Splined"), ArxRleUtils::booleanToStr(leader->isSplined(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(leader->normal(), str));

	AcDbLeader::AnnoType type = leader->annoType();
	if (type == AcDbLeader::kMText)
		str = _T("Mtext");
	else if (type == AcDbLeader::kFcf)
		str = _T("Fcf");
	else if (type == AcDbLeader::kBlockRef)
		str = _T("Block Ref");
	else if (type == AcDbLeader::kNoAnno)
		str = _T("None");
	else {
		ASSERT(0);
		str = _T("*Unknown*");
	}

	addToDataList(_T("Annotation"), str);

	if (type != AcDbLeader::kNoAnno) {
		AcDbObject* annoObj;
		Acad::ErrorStatus es = acdbOpenObject(annoObj, leader->annotationObjId(), AcDb::kForRead);
		if (es == Acad::eOk) {
			addToDataList(_T("Annotation"), ArxRleUtils::objToClassAndHandleStr(annoObj, str));
			annoObj->close();
		}
		else 
			addToDataList(_T("Annotation"), ArxRleUtils::rxErrorStr(es));

		addToDataList(_T("Annotation Offset"), ArxRleUtils::vectorToStr(leader->annotationOffset(), str));
		addToDataList(_T("Annotation Width"), ArxRleUtils::doubleToStr(leader->annoWidth(), str));
		addToDataList(_T("Annotation Height"), ArxRleUtils::doubleToStr(leader->annoHeight(), str));
	}

// TBD: still need the dimvars to be complete!
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    POLYLINE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbPolyline* pline)
{
    CString str, str2;
    double tmpDouble;
    AcGePoint3d tmpPt;
    Acad::ErrorStatus es;

    ASSERT(pline != NULL);

    addSeperatorLine(_T("AcDbPolyline"));

    addToDataList(_T("Is Only Lines"), ArxRleUtils::booleanToStr(pline->isOnlyLines(), str));
    addToDataList(_T("Is Closed"), ArxRleUtils::booleanToStr(pline->isClosed(), str));
    addToDataList(_T("Has Pline Gen"), ArxRleUtils::booleanToStr(pline->hasPlinegen(), str));
    addToDataList(_T("Elevation"), ArxRleUtils::doubleToStr(pline->elevation(), str));
    addToDataList(_T("Thickness"), ArxRleUtils::doubleToStr(pline->thickness(), str));
    if (pline->getConstantWidth(tmpDouble) == Acad::eOk)
        addToDataList(_T("Constant Width"), ArxRleUtils::doubleToStr(tmpDouble, str));
    else
        addToDataList(_T("Constant Width"), _T("False"));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(pline->normal(), str));

    addSeperatorLine(_T("Vertices"));
    unsigned int i;
    for (i=0; i<pline->numVerts(); i++) {
        es = pline->getPointAt(i, tmpPt);
        if (es == Acad::eOk) {
            str2.Format(_T("Vertex #%d"), i+1);
            addToDataList(str2, ArxRleUtils::ptToStr(tmpPt, str));
        }
    }
    AcDbPolyline::SegType segType;
    double bulge, startWidth, endWidth;

    unsigned int numSegs;
    if (pline->isClosed())
        numSegs = pline->numVerts();
    else
        numSegs = pline->numVerts() - 1;

    for (i=0; i<numSegs; i++) {
        str2.Format(_T("Segment #%d"), i+1);
        addSeperatorLine(str2);

        segType = pline->segType(i);
        if (segType == AcDbPolyline::kLine) {
            addToDataList(_T("Type"), _T("Line"));
            AcGeLineSeg3d line;
            es = pline->getLineSegAt(i, line);
            if (es == Acad::eOk) {
                addToDataList(_T("Start Point"), ArxRleUtils::ptToStr(line.startPoint(), str));
                addToDataList(_T("End Point"), ArxRleUtils::ptToStr(line.endPoint(), str));
            }
            else
                addToDataList(_T("ERROR"), _T("Could not get Line segment"));
        }
        else if (segType == AcDbPolyline::kArc) {
            addToDataList(_T("Type"), _T("Arc"));
            AcGeCircArc3d arc;
            es = pline->getArcSegAt(i, arc);
            if (es == Acad::eOk) {
                addToDataList(_T("Center Point"), ArxRleUtils::ptToStr(arc.center(), str));
                addToDataList(_T("Start Point"), ArxRleUtils::ptToStr(arc.startPoint(), str));
                addToDataList(_T("End Point"), ArxRleUtils::ptToStr(arc.endPoint(), str));
                addToDataList(_T("Radius"), ArxRleUtils::doubleToStr(arc.radius(), str));
                addToDataList(_T("Start Angle"), ArxRleUtils::angleToStr(arc.startAng(), str));
                addToDataList(_T("End Angle"), ArxRleUtils::angleToStr(arc.endAng(), str));
                addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(arc.normal(), str));
            }
            else
                addToDataList(_T("ERROR"), _T("Could not get Line segment"));
        }
        else if (segType == AcDbPolyline::kCoincident) {
            addToDataList(_T("Type"), _T("Coincident"));

        }
        else if (segType == AcDbPolyline::kPoint) {
            addToDataList(_T("Type"), _T("Point"));
            if (pline->getPointAt(i, tmpPt) == Acad::eOk)
                addToDataList(_T("Point"), ArxRleUtils::ptToStr(tmpPt, str));
            else
                addToDataList(_T("ERROR"), _T("Could not get point"));
        }
        else if (segType == AcDbPolyline::kEmpty) {
            addToDataList(_T("Type"), _T("Empty"));
        }
        else {
            ASSERT(0);
            addToDataList(_T("Type"), _T("*Unknown"));
        }

        es = pline->getBulgeAt(i, bulge);
        if (es == Acad::eOk)
            addToDataList(_T("Bulge"), ArxRleUtils::doubleToStr(bulge, str));
        else
            addToDataList(_T("ERROR"), _T("Could not get bulge"));

        es = pline->getWidthsAt(i, startWidth, endWidth);
        if (es == Acad::eOk) {
            addToDataList(_T("Start Width"), ArxRleUtils::doubleToStr(startWidth, str));
            addToDataList(_T("End Width"), ArxRleUtils::doubleToStr(endWidth, str));
        }
        else
            addToDataList(_T("ERROR"), _T("Could not get widths"));
    }
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    LINE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbLine* line)
{
    CString str;

    ASSERT(line != NULL);

    addSeperatorLine(_T("AcDbLine"));

    addToDataList(_T("Start Pt"), ArxRleUtils::ptToStr(line->startPoint(), str));
    addToDataList(_T("End Pt"), ArxRleUtils::ptToStr(line->endPoint(), str));
    addToDataList(_T("Thickness"), ArxRleUtils::doubleToStr(line->thickness(), str));
    addToDataList(_T("Normal"), ArxRleUtils::vectorToStr(line->normal(), str));
}


/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    RAY
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbRay* ray)
{
    CString str;

    ASSERT(ray != NULL);

    addSeperatorLine(_T("AcDbRay"));

    addToDataList(_T("Base Pt"), ArxRleUtils::ptToStr(ray->basePoint(), str));
    addToDataList(_T("Unit Dir"), ArxRleUtils::vectorToStr(ray->unitDir(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    SPLINE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbSpline* spline)
{
    CString str, str2;
    AcGePoint3d pt;
    AcGeVector3d startTan, endTan;
    int i, count;

    ASSERT(spline != NULL);

    addSeperatorLine(_T("AcDbSpline"));

    int degree;
    Adesk::Boolean rational, closed, periodic;
    AcGePoint3dArray controlPoints; 
    AcGeDoubleArray  knots; 
    AcGeDoubleArray  weights;
    double controlPtTol, knotTol;
    spline->getNurbsData(degree, rational, closed, periodic, controlPoints, 
                                    knots, weights, controlPtTol, knotTol);


    addToDataList(_T("Is Rational"), ArxRleUtils::booleanToStr(rational, str));
    addToDataList(_T("Degree"), ArxRleUtils::intToStr(degree, str));

    count = controlPoints.length();
    for (i=0;i<count;i++) {
        str2.Format(_T("Control Pt #%2d"), i+1);
        addToDataList(str2, ArxRleUtils::ptToStr(controlPoints[i], str));
    }

    count = knots.length();
    for (i=0;i<count;i++) {
        str2.Format(_T("Knot #%2d"), i+1);
        addToDataList(str2, ArxRleUtils::doubleToStr(knots[i], str));
    }

    AcGePoint3dArray  fitPoints; 
    Adesk::Boolean    tangentsExist;
    AcGeVector3d      startTangent;
    AcGeVector3d      endTangent;
    AcGe::KnotParameterization  knotParam;
    double            fitTolerance;
        
    if (!spline->hasFitData())
        return;

    spline->getFitData(fitPoints, tangentsExist, startTangent, endTangent, knotParam, degree, fitTolerance); 

    count = fitPoints.length();
    for (i=0;i<count;i++) {
        str2.Format(_T("Fit Pt #%2d"), i+1);
        addToDataList(str2, ArxRleUtils::ptToStr(fitPoints[i], str));
    }
    addToDataList(_T("Fit Tolerance"), ArxRleUtils::doubleToStr(fitTolerance, str));
    addToDataList(_T("Start Tangent"), ArxRleUtils::vectorToStr(startTan, str));
    addToDataList(_T("End Tangent"), ArxRleUtils::vectorToStr(endTan, str));
    addToDataList(_T("Knot Param"), ArxRleUtils::intToStr(knotParam, str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    XLINE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbXline* xline)
{
    CString str;

    ASSERT(xline != NULL);

    addSeperatorLine(_T("AcDbXline"));

    addToDataList(_T("Base Pt"), ArxRleUtils::ptToStr(xline->basePoint(), str));
    addToDataList(_T("Unit Dir"), ArxRleUtils::vectorToStr(xline->unitDir(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    2 LINE ANGULAR DIMENSION
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDb2LineAngularDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDb2LineAngularDimension"));

    addToDataList(_T("Arc Pt"), ArxRleUtils::ptToStr(dim->arcPoint(), str));
    addToDataList(_T("Xline1 Start"), ArxRleUtils::ptToStr(dim->xLine1Start(), str));
    addToDataList(_T("Xline1 End"), ArxRleUtils::ptToStr(dim->xLine1End(), str));
    addToDataList(_T("Xline2 Start"), ArxRleUtils::ptToStr(dim->xLine2Start(), str));
    addToDataList(_T("Xline2 End"), ArxRleUtils::ptToStr(dim->xLine2End(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    3 POINT ANGULAR DIMENSION
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDb3PointAngularDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDb3PointAngularDimension"));

    addToDataList(_T("Arc Pt"), ArxRleUtils::ptToStr(dim->arcPoint(), str));
    addToDataList(_T("Xline Pt1"), ArxRleUtils::ptToStr(dim->xLine1Point(), str));
    addToDataList(_T("Xline Pt2"), ArxRleUtils::ptToStr(dim->xLine2Point(), str));
    addToDataList(_T("Center Pt"), ArxRleUtils::ptToStr(dim->centerPoint(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    ALIGNED DIMENSION
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbAlignedDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbAlignedDimension"));

    addToDataList(_T("Xline Pt1"), ArxRleUtils::ptToStr(dim->xLine1Point(), str));
    addToDataList(_T("Xline Pt2"), ArxRleUtils::ptToStr(dim->xLine2Point(), str));
    addToDataList(_T("Dimline Pt"), ArxRleUtils::ptToStr(dim->dimLinePoint(), str));
    addToDataList(_T("Oblique Angle"), ArxRleUtils::angleToStr(dim->oblique(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    DIAMETRIC DIMENSION
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbDiametricDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbDiametricDimension"));

    addToDataList(_T("Leader Length"), ArxRleUtils::doubleToStr(dim->leaderLength(), str));
    addToDataList(_T("Chord Pt"), ArxRleUtils::ptToStr(dim->chordPoint(), str));
    addToDataList(_T("Far Chord Pt"), ArxRleUtils::ptToStr(dim->farChordPoint(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    ORDINATE DIMENION
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbOrdinateDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbOrdinateDimension"));

    addToDataList(_T("Is Using X Axis"), ArxRleUtils::booleanToStr(dim->isUsingXAxis(), str));
    addToDataList(_T("Is Using Y Axis"), ArxRleUtils::booleanToStr(dim->isUsingYAxis(), str));
    addToDataList(_T("Origin Pt"), ArxRleUtils::ptToStr(dim->origin(), str));
    addToDataList(_T("Defining Pt"), ArxRleUtils::ptToStr(dim->definingPoint(), str));
    addToDataList(_T("Leader End Pt"), ArxRleUtils::ptToStr(dim->leaderEndPoint(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    RADIAL DIMENSION
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbRadialDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbRadialDimension"));

    addToDataList(_T("Leader Length"), ArxRleUtils::doubleToStr(dim->leaderLength(), str));
    addToDataList(_T("Center"), ArxRleUtils::ptToStr(dim->center(), str));
    addToDataList(_T("Chord Pt"), ArxRleUtils::ptToStr(dim->chordPoint(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    ROTATED DIMENSION
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbRotatedDimension* dim)
{
    CString str;

    ASSERT(dim != NULL);

    addSeperatorLine(_T("AcDbRotatedDimension"));

    addToDataList(_T("Xline Pt1"), ArxRleUtils::ptToStr(dim->xLine1Point(), str));
    addToDataList(_T("Xline Pt2"), ArxRleUtils::ptToStr(dim->xLine2Point(), str));
    addToDataList(_T("Dimline Pt"), ArxRleUtils::ptToStr(dim->dimLinePoint(), str));
    addToDataList(_T("Oblique Angle"), ArxRleUtils::angleToStr(dim->oblique(), str));
    addToDataList(_T("Rotation"), ArxRleUtils::angleToStr(dim->rotation(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(OLE FRAME)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbOleFrame* oleFrame)
{
    CString str;

    ASSERT(oleFrame != NULL);

    addSeperatorLine(_T("AcDbOleFrame"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(OLE 2 FRAME)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbOle2Frame* ole2Frame)
{
    CString str;

    ASSERT(ole2Frame != NULL);

    addSeperatorLine(_T("AcDbOle2Frame"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    ATTRIBUTE
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbAttribute* attrib)
{
    CString str;

    ASSERT(attrib != NULL);

    addSeperatorLine(_T("AcDbAttribute"));

    const TCHAR* tmpStr = attrib->tagConst();
    addToDataList(_T("Tag"), tmpStr, true);

    addToDataList(_T("Invisible"), ArxRleUtils::booleanToStr(attrib->isInvisible(), str));
    addToDataList(_T("Constant"), ArxRleUtils::booleanToStr(attrib->isConstant(), str));
    addToDataList(_T("Verifiable"), ArxRleUtils::booleanToStr(attrib->isVerifiable(), str));
    addToDataList(_T("Preset"), ArxRleUtils::booleanToStr(attrib->isPreset(), str));
    addToDataList(_T("Field Length"), ArxRleUtils::intToStr(attrib->fieldLength(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    ATTDEF
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbAttributeDefinition* attdef)
{
    CString str;

    ASSERT(attdef != NULL);

    addSeperatorLine(_T("AcDbAttributeDefinition"));

    const TCHAR* tmpStr = attdef->promptConst();
    addToDataList(_T("Prompt"), tmpStr, true);

    tmpStr = attdef->tagConst();
    addToDataList(_T("Tag"), tmpStr, true);

    addToDataList(_T("Invisible"), ArxRleUtils::booleanToStr(attdef->isInvisible(), str));
    addToDataList(_T("Constant"), ArxRleUtils::booleanToStr(attdef->isConstant(), str));
    addToDataList(_T("Verifiable"), ArxRleUtils::booleanToStr(attdef->isVerifiable(), str));
    addToDataList(_T("Preset"), ArxRleUtils::booleanToStr(attdef->isPreset(), str));
    addToDataList(_T("Field Length"), ArxRleUtils::intToStr(attdef->fieldLength(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    2D VERTEX
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDb2dVertex* vertex)
{
    CString str;

    ASSERT(vertex != NULL);

    addSeperatorLine(_T("AcDb2dVertex"));

    AcDb::Vertex2dType vertexType = vertex->vertexType();
    if (vertexType == AcDb::k2dVertex)
        str = _T("2D Vertex");
    else if (vertexType == AcDb::k2dSplineCtlVertex)
        str = _T("Spline Control Vertex");
    else if (vertexType == AcDb::k2dSplineFitVertex)
        str = _T("Spline Fit Vertex");
    else if (vertexType == AcDb::k2dCurveFitVertex)
        str = _T("Curve Fit Vertex");
    else
        str = _T("");

    addToDataList(_T("Vertex Type"), str);
    addToDataList(_T("Position"), ArxRleUtils::ptToStr(vertex->position(), str));
    addToDataList(_T("Start Width"), ArxRleUtils::doubleToStr(vertex->startWidth(), str));
    addToDataList(_T("End Width"), ArxRleUtils::doubleToStr(vertex->endWidth(), str));
    addToDataList(_T("Bulge"), ArxRleUtils::doubleToStr(vertex->bulge(), str));
    addToDataList(_T("Is Tangent Used"), ArxRleUtils::booleanToStr(vertex->isTangentUsed(), str));
    if (vertex->isTangentUsed())
        addToDataList(_T("Tangent"), ArxRleUtils::doubleToStr(vertex->tangent(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    3D POLYLINE VERTEX
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDb3dPolylineVertex* vertex)
{
    CString str;

    ASSERT(vertex != NULL);

    addSeperatorLine(_T("AcDb3dPolylineVertex"));

    addToDataList(_T("Vertex Type"), ArxRleUtils::vertexTypeToStr(vertex->vertexType(), str));
    addToDataList(_T("Position"), ArxRleUtils::ptToStr(vertex->position(), str));
}


/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    POLYFACE MESH VERTEX
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbPolyFaceMeshVertex* vertex)
{
    CString str;

    ASSERT(vertex != NULL);

    addSeperatorLine(_T("AcDbPolyFaceMeshVertex"));

    addToDataList(_T("Position"), ArxRleUtils::ptToStr(vertex->position(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display    POLYGON MESH VERTEX
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbPolygonMeshVertex* vertex)
{
    CString str;

    ASSERT(vertex != NULL);

    addSeperatorLine(_T("AcDbPolygonMeshVertex"));

    addToDataList(_T("Vertex Type"), ArxRleUtils::vertexTypeToStr(vertex->vertexType(), str));
    addToDataList(_T("Position"), ArxRleUtils::ptToStr(vertex->position(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(LAYER FILTER)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbLayerFilter* filter)
{
    CString str;

    ASSERT(filter != NULL);

    addSeperatorLine(_T("AcDbLayerFilter"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(SPATIAL FILTER)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbSpatialFilter* filter)
{
    CString str;

    ASSERT(filter != NULL);

    addSeperatorLine(_T("AcDbSpatialFilter"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(LAYER INDEX)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbLayerIndex* index)
{
    CString str;

    ASSERT(index != NULL);

    addSeperatorLine(_T("AcDbLayerIndex"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(SPATIAL INDEX)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbSpatialIndex* index)
{
    CString str;

    ASSERT(index != NULL);

    addSeperatorLine(_T("AcDbSpatialIndex"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display	(LAYOUT)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbLayout* layout)
{
    CString str;

    ASSERT(layout != NULL);

    addSeperatorLine(_T("AcDbLayout"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbAbstractViewTableRecord* view)
{
    CString str;

	addSeperatorLine(_T("AcDbAbstractViewTableRecord"));

    addToDataList(_T("Center Pt"), ArxRleUtils::ptToStr(view->centerPoint(), str));
    addToDataList(_T("Height"), ArxRleUtils::doubleToStr(view->height(), str));
    addToDataList(_T("Width"), ArxRleUtils::doubleToStr(view->width(), str));
    addToDataList(_T("Target"), ArxRleUtils::ptToStr(view->target(), str));
    addToDataList(_T("View Dir"), ArxRleUtils::vectorToStr(view->viewDirection(), str));
    addToDataList(_T("View Twist"), ArxRleUtils::doubleToStr(view->viewTwist(), str));
    addToDataList(_T("Lens Length"), ArxRleUtils::doubleToStr(view->lensLength(), str));
    addToDataList(_T("Front Clip Dist"), ArxRleUtils::doubleToStr(view->frontClipDistance(), str));
    addToDataList(_T("Back Clip Dist"), ArxRleUtils::doubleToStr(view->backClipDistance(), str));
    addToDataList(_T("Perspective On"), ArxRleUtils::booleanToStr(view->perspectiveEnabled(), str));
    addToDataList(_T("Front Clip On"), ArxRleUtils::booleanToStr(view->frontClipEnabled(), str));
    addToDataList(_T("Back Clip On"), ArxRleUtils::booleanToStr(view->backClipEnabled(), str));
    addToDataList(_T("Front Clip At Eye"), ArxRleUtils::booleanToStr(view->frontClipAtEye(), str));

	AcGePoint3d origin;
	AcGeVector3d xAxis, yAxis;
	Acad::ErrorStatus es = view->getUcs(origin, xAxis, yAxis);
	if (es == Acad::eOk) {
		addToDataList(_T("UCS Origin"), ArxRleUtils::ptToStr(origin, str));
		addToDataList(_T("UCS X Axis"), ArxRleUtils::vectorToStr(xAxis, str));
		addToDataList(_T("UCS Y Axis"), ArxRleUtils::vectorToStr(yAxis, str));
	}
	else
		addToDataList(_T("UCS Info"), ArxRleUtils::rxErrorStr(es));

	AcDb::OrthographicView orthoView;
	bool ucsIsOrtho = view->isUcsOrthographic(orthoView);
	addToDataList(_T("Is UCS Orthographic"), ArxRleUtils::booleanToStr(ucsIsOrtho, str));
	if (ucsIsOrtho)
		addToDataList(_T("UCS Orthographic View"), ArxRleUtils::orthoViewToStr(orthoView, str));
    
	ArxRleUtils::symbolIdToName(view->ucsName(), str);
	addToDataList(_T("UCS Name"), str);
	addToDataList(_T("Elevation"), ArxRleUtils::doubleToStr(view->elevation(), str));

	bool viewIsOrtho = view->isViewOrthographic(orthoView);
	addToDataList(_T("Is View Orthographic"), ArxRleUtils::booleanToStr(viewIsOrtho, str));
	if (viewIsOrtho)
		addToDataList(_T("Orthographic View"), ArxRleUtils::orthoViewToStr(orthoView, str));

	AcDbViewportTableRecord* vportRec;
	AcDbViewTableRecord* viewRec;

	if ((vportRec = AcDbViewportTableRecord::cast(view)) != NULL)
		display(vportRec);
	else if ((viewRec = AcDbViewTableRecord::cast(view)) != NULL)
		display(viewRec);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display        (BLOCK)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbBlockTableRecord* blk)
{
    CString str;
    const TCHAR* locName;
    Acad::ErrorStatus es;

    addSeperatorLine(_T("AcDbBlockTableRecord"));

    es = blk->pathName(locName);
    if (es == Acad::eOk) {
        addToDataList(_T("Path Name"), locName, true);
    }

    addToDataList(_T("Origin"), ArxRleUtils::ptToStr(blk->origin(), str));
    addToDataList(_T("Has Attribute Defs"), ArxRleUtils::booleanToStr(blk->hasAttributeDefinitions(), str));
    addToDataList(_T("Has Preview Icon"), ArxRleUtils::booleanToStr(blk->hasPreviewIcon(), str));
    addToDataList(_T("Is Anonymous"), ArxRleUtils::booleanToStr(blk->isAnonymous(), str));
    addToDataList(_T("Is From Xref"), ArxRleUtils::booleanToStr(blk->isFromExternalReference(), str));
    addToDataList(_T("Is From Overlay Ref"), ArxRleUtils::booleanToStr(blk->isFromOverlayReference(), str));
    addToDataList(_T("Is Layout"), ArxRleUtils::booleanToStr(blk->isLayout(), str));

    AcDbObject* tmpObj;
    es = acdbOpenObject(tmpObj, blk->getLayoutId(), AcDb::kForRead);
    if (es == Acad::eOk) {
        addToDataList(_T("Layout Object"), ArxRleUtils::objToClassAndHandleStr(tmpObj, str));
        tmpObj->close();
    }
    else
        addToDataList(_T("Layout Object"), ArxRleUtils::rxErrorStr(es));

    addToDataList(_T("Xref Database"), ArxRleUtils::ptrToStr(blk->xrefDatabase(), str));
    addToDataList(_T("Is Unloaded"), ArxRleUtils::booleanToStr(blk->isUnloaded(), str));
    addToDataList(_T("Xref Status"), ArxRleUtils::xrefStatusToStr(blk->xrefStatus(), str));

    const TCHAR* tmpStr;
    es = blk->comments(tmpStr);
    if (es == Acad::eOk)
        str = tmpStr;
    else
        ArxRleUtils::rxErrorStr(es);

    addToDataList(_T("Comments"), str, true);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display        (DIMSTYLE)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbDimStyleTableRecord* dimStyle)
{
    CString str;

    addSeperatorLine(_T("AcDbDimStyleTableRecord"));

    ArxRleUtils::symbolIdToName(dimStyle->arrowId(AcDb::kFirstArrow), str);
    addToDataList(_T("First Arrow"), str);

    ArxRleUtils::symbolIdToName(dimStyle->arrowId(AcDb::kSecondArrow), str);
    addToDataList(_T("Second Arrow"), str);

    addToDataList(_T("DIMADEC"), ArxRleUtils::intToStr(dimStyle->dimadec(), str));
    addToDataList(_T("DIMALT"), ArxRleUtils::booleanToStr(dimStyle->dimalt(), str));
    addToDataList(_T("DIMALTD"), ArxRleUtils::intToStr(dimStyle->dimaltd(), str));
    addToDataList(_T("DIMALTF"), ArxRleUtils::doubleToStr(dimStyle->dimaltf(), str));
    addToDataList(_T("DIMALTRND"), ArxRleUtils::doubleToStr(dimStyle->dimaltrnd(), str));
    addToDataList(_T("DIMALTTD"), ArxRleUtils::intToStr(dimStyle->dimalttd(), str));
    addToDataList(_T("DIMALTU"), ArxRleUtils::intToStr(dimStyle->dimaltu(), str));
    addToDataList(_T("DIMALTTZ"), ArxRleUtils::intToStr(dimStyle->dimalttz(), str));
    addToDataList(_T("DIMALTZ"), ArxRleUtils::intToStr(dimStyle->dimaltz(), str));
    addToDataList(_T("DIMAPOST"), dimStyle->dimapost(), true);
    addToDataList(_T("DIMASZ"), ArxRleUtils::doubleToStr(dimStyle->dimasz(), str));
    addToDataList(_T("DIMAUNIT"), ArxRleUtils::intToStr(dimStyle->dimaunit(), str));
    addToDataList(_T("DIMAZIN"), ArxRleUtils::intToStr(dimStyle->dimazin(), str));

    ArxRleUtils::symbolIdToName(dimStyle->dimblk(), str);
    addToDataList(_T("DIMBLK"), str);

    ArxRleUtils::symbolIdToName(dimStyle->dimblk1(), str);
    addToDataList(_T("DIMBLK1"), str);

    ArxRleUtils::symbolIdToName(dimStyle->dimblk2(), str);
    addToDataList(_T("DIMBLK2"), str);

    addToDataList(_T("DIMCEN"), ArxRleUtils::doubleToStr(dimStyle->dimcen(), str));
    addToDataList(_T("DIMCLRD"), ArxRleUtils::colorToStr(dimStyle->dimclrd().colorIndex(), str, true));
    addToDataList(_T("DIMCLRE"), ArxRleUtils::colorToStr(dimStyle->dimclre().colorIndex(), str, true));
    addToDataList(_T("DIMCLRT"), ArxRleUtils::colorToStr(dimStyle->dimclrt().colorIndex(), str, true));
    addToDataList(_T("DIMDEC"), ArxRleUtils::intToStr(dimStyle->dimdec(), str));
    addToDataList(_T("DIMDLE"), ArxRleUtils::doubleToStr(dimStyle->dimdle(), str));
    addToDataList(_T("DIMDLI"), ArxRleUtils::doubleToStr(dimStyle->dimdli(), str));
    addToDataList(_T("DIMDSEP"), ArxRleUtils::intToStr(dimStyle->dimdsep(), str));
    addToDataList(_T("DIMEXE"), ArxRleUtils::doubleToStr(dimStyle->dimexe(), str));
    addToDataList(_T("DIMEXO"), ArxRleUtils::doubleToStr(dimStyle->dimexo(), str));
    addToDataList(_T("DIMATFIT"), ArxRleUtils::intToStr(dimStyle->dimatfit(), str));
    addToDataList(_T("DIMFRAC"), ArxRleUtils::intToStr(dimStyle->dimfrac(), str));
    addToDataList(_T("DIMGAP"), ArxRleUtils::doubleToStr(dimStyle->dimgap(), str));
    addToDataList(_T("DIMJUST"), ArxRleUtils::intToStr(dimStyle->dimjust(), str));

    ArxRleUtils::symbolIdToName(dimStyle->dimldrblk(), str);
    addToDataList(_T("DIMLDRBLK"), str);

    addToDataList(_T("DIMLFAC"), ArxRleUtils::doubleToStr(dimStyle->dimlfac(), str));
    addToDataList(_T("DIMLIM"), ArxRleUtils::booleanToStr(dimStyle->dimlim(), str));
    addToDataList(_T("DIMLUNIT"), ArxRleUtils::intToStr(dimStyle->dimlunit(), str));
    addToDataList(_T("DIMLWD"), ArxRleUtils::lineWeightTypeToStr(dimStyle->dimlwd(), str));
    addToDataList(_T("DIMLWE"), ArxRleUtils::lineWeightTypeToStr(dimStyle->dimlwe(), str));
    addToDataList(_T("DIMPOST"), dimStyle->dimpost(), true);
    addToDataList(_T("DIMRND"), ArxRleUtils::doubleToStr(dimStyle->dimrnd(), str));
    addToDataList(_T("DIMSAH"), ArxRleUtils::booleanToStr(dimStyle->dimsah(), str));
    addToDataList(_T("DIMSCALE"), ArxRleUtils::doubleToStr(dimStyle->dimscale(), str));
    addToDataList(_T("DIMSD1"), ArxRleUtils::booleanToStr(dimStyle->dimsd1(), str));
    addToDataList(_T("DIMSD2"), ArxRleUtils::booleanToStr(dimStyle->dimsd2(), str));
    addToDataList(_T("DIMSE1"), ArxRleUtils::booleanToStr(dimStyle->dimse1(), str));
    addToDataList(_T("DIMSE2"), ArxRleUtils::booleanToStr(dimStyle->dimse2(), str));
    addToDataList(_T("DIMSOXD"), ArxRleUtils::booleanToStr(dimStyle->dimsoxd(), str));
    addToDataList(_T("DIMTAD"), ArxRleUtils::intToStr(dimStyle->dimtad(), str));
    addToDataList(_T("DIMTDEC"), ArxRleUtils::intToStr(dimStyle->dimtdec(), str));
    addToDataList(_T("DIMTFAC"), ArxRleUtils::doubleToStr(dimStyle->dimtfac(), str));
    addToDataList(_T("DIMTIH"), ArxRleUtils::booleanToStr(dimStyle->dimtih(), str));
    addToDataList(_T("DIMTIX"), ArxRleUtils::booleanToStr(dimStyle->dimtix(), str));
    addToDataList(_T("DIMTM"), ArxRleUtils::doubleToStr(dimStyle->dimtm(), str));
    addToDataList(_T("DIMTMOVE"), ArxRleUtils::intToStr(dimStyle->dimtmove(), str));
    addToDataList(_T("DIMTOFL"), ArxRleUtils::booleanToStr(dimStyle->dimtofl(), str));
    addToDataList(_T("DIMTOH"), ArxRleUtils::booleanToStr(dimStyle->dimtoh(), str));
    addToDataList(_T("DIMTOL"), ArxRleUtils::booleanToStr(dimStyle->dimtol(), str));
    addToDataList(_T("DIMTOLJ"), ArxRleUtils::intToStr(dimStyle->dimtolj(), str));
    addToDataList(_T("DIMTP"), ArxRleUtils::doubleToStr(dimStyle->dimtp(), str));
    addToDataList(_T("DIMTSZ"), ArxRleUtils::doubleToStr(dimStyle->dimtsz(), str));
    addToDataList(_T("DIMTVP"), ArxRleUtils::doubleToStr(dimStyle->dimtvp(), str));

    ArxRleUtils::symbolIdToName(dimStyle->dimtxsty(), str);
    addToDataList(_T("DIMTXSTY"), str);

    addToDataList(_T("DIMTXT"), ArxRleUtils::doubleToStr(dimStyle->dimtxt(), str));
    addToDataList(_T("DIMTZIN"), ArxRleUtils::intToStr(dimStyle->dimtzin(), str));
    addToDataList(_T("DIMUPT"), ArxRleUtils::booleanToStr(dimStyle->dimupt(), str));
    addToDataList(_T("DIMZIN"), ArxRleUtils::intToStr(dimStyle->dimzin(), str));

    addToDataList(_T("DIMFIT (Deprecated)"), ArxRleUtils::intToStr(dimStyle->dimfit(), str));
    addToDataList(_T("DIMUNIT (Deprecated)"), ArxRleUtils::intToStr(dimStyle->dimunit(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display        (LAYER)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbLayerTableRecord* layer)
{
    CString str;

    addSeperatorLine(_T("AcDbLayerTableRecord"));
    addToDataList(_T("Is Hidden"), ArxRleUtils::booleanToStr(layer->isHidden(), str));
    addToDataList(_T("Is Frozen"), ArxRleUtils::booleanToStr(layer->isFrozen(), str));
    addToDataList(_T("Is Off"), ArxRleUtils::booleanToStr(layer->isOff(), str));
    addToDataList(_T("Is Locked"), ArxRleUtils::booleanToStr(layer->isLocked(), str));
    addToDataList(_T("Is VP Default"), ArxRleUtils::booleanToStr(layer->VPDFLT(), str));
    addToDataList(_T("Color"), ArxRleUtils::intToStr(layer->color().colorIndex(), str));

    ArxRleUtils::symbolIdToName(layer->linetypeObjectId(), str);
    addToDataList(_T("Linetype"), str);

    addToDataList(_T("Lineweight"), ArxRleUtils::lineWeightTypeToStr(layer->lineWeight(), str));
    addToDataList(_T("Is Plottable"), ArxRleUtils::booleanToStr(layer->isPlottable(), str));

    TCHAR* name = layer->plotStyleName();
    addToDataList(_T("Plot Style Name"), name);
    acutDelString(name);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display        (LINETYPE)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbLinetypeTableRecord* linetype)
{
    CString str;
    const TCHAR* locName;
    Acad::ErrorStatus es;

    addSeperatorLine(_T("AcDbLinetypeTableRecord"));

    es = linetype->asciiDescription(locName);
    if (es == Acad::eOk) {
        str = locName;
    }
    else
        str = ArxRleUtils::rxErrorStr(es);
    addToDataList(_T("Description"), str);

    addToDataList(_T("Pattern Length"), ArxRleUtils::doubleToStr(linetype->patternLength(), str));

    AcDbObjectId shapeStyleId;
    const TCHAR* tmpTxt;
    int i, len;
    len = linetype->numDashes();
    for (i=0;i<len;i++) {
        str.Format(_T("--- DASH #%2d ---"), i+1);
        addToDataList(str, _T(""));
        addToDataList(_T("Length"), ArxRleUtils::doubleToStr(linetype->dashLengthAt(i), str));

        shapeStyleId = linetype->shapeStyleAt(i);
        if (shapeStyleId != AcDbObjectId::kNull) {
            if (ArxRleUtils::symbolIdToName(shapeStyleId, str) != Acad::eOk)
                str = _T("*ERROR*");
            addToDataList(_T("Shape Style"), str);
            addToDataList(_T("Shape Number"), ArxRleUtils::intToStr(linetype->shapeNumberAt(i), str));
            addToDataList(_T("Shape Offset"), ArxRleUtils::vectorToStr(linetype->shapeOffsetAt(i), str));
            addToDataList(_T("Shape Scale"), ArxRleUtils::doubleToStr(linetype->shapeScaleAt(i), str));
            addToDataList(_T("Shape UCS Oriented"), ArxRleUtils::booleanToStr(linetype->shapeIsUcsOrientedAt(i), str));
            addToDataList(_T("Shape Rotation"), ArxRleUtils::angleToStr(linetype->shapeRotationAt(i), str));
            es = linetype->textAt(i, tmpTxt);
            if (es == Acad::eOk)
                addToDataList(_T("Text"), tmpTxt, true);
            else
                addToDataList(_T("Text"), ArxRleUtils::rxErrorStr(es));
        }
    }

    addToDataList(_T("Is Scaled To Fit"), ArxRleUtils::booleanToStr(linetype->isScaledToFit(), str));

    const TCHAR* tmpStr;
    es = linetype->comments(tmpStr);
    if (es == Acad::eOk)
        str = tmpStr;
    else
        ArxRleUtils::rxErrorStr(es);

    addToDataList(_T("Comments"), str, true);
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display        (REGAPP)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbRegAppTableRecord* regApp)
{
    addSeperatorLine(_T("AcDbRegAppTableRecord"));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display        (TextStyle)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbTextStyleTableRecord* textStyle)
{
    CString str;
    const TCHAR* locName;
    Acad::ErrorStatus es;

    addSeperatorLine(_T("AcDbTextStyleTableRecord"));

    es = textStyle->fileName(locName);
    if (es == Acad::eOk)
        str = locName;
    else
        str = ArxRleUtils::rxErrorStr(es);
    addToDataList(_T("File Name"), str, true);

    es = textStyle->bigFontFileName(locName);
    if (es == Acad::eOk)
        str = locName;
    else
        str = ArxRleUtils::rxErrorStr(es);
    addToDataList(_T("Big Font File"), str, true);

    TCHAR* typeFace;
    Adesk::Boolean isBold, isItalic;
    Charset charset;
    using namespace Autodesk::AutoCAD::PAL;
    FontUtils::FontPitch  pitch = FontUtils::FontPitch::kDefault;
    FontUtils::FontFamily family = FontUtils::FontFamily::kDoNotCare;
    es = textStyle->font(typeFace, isBold, isItalic, charset, pitch, family);
    if (es == Acad::eOk) {
        addToDataList(_T("Font Typeface"), typeFace, true);
        addToDataList(_T("Font Is Bold"), ArxRleUtils::booleanToStr(isBold, str));
        addToDataList(_T("Font Is Italic"), ArxRleUtils::booleanToStr(isItalic, str));
        addToDataList(_T("Font Charset"), ArxRleUtils::intToStr(charset, str));
        int pitchAndFamily = 0;
        pitchAndFamily |= (int)pitch;
        pitchAndFamily |= (int)family;
        addToDataList(_T("Font Pitch/Family"), ArxRleUtils::intToStr(pitchAndFamily, str));
        acutDelString(typeFace);
    }
    else
        addToDataList(_T("Font"), ArxRleUtils::rxErrorStr(es));

    addToDataList(_T("Is Shape File"), ArxRleUtils::booleanToStr(textStyle->isShapeFile(), str));
    addToDataList(_T("Is Vertical"), ArxRleUtils::booleanToStr(textStyle->isVertical(), str));
    addToDataList(_T("Text Size"), ArxRleUtils::doubleToStr(textStyle->textSize(), str));
    addToDataList(_T("Prior Size"), ArxRleUtils::doubleToStr(textStyle->priorSize(), str));
    addToDataList(_T("X Scale"), ArxRleUtils::doubleToStr(textStyle->xScale(), str));
    addToDataList(_T("Oblique Angle"), ArxRleUtils::angleToStr(textStyle->obliquingAngle(), str));
    addToDataList(_T("Flag Bits"), ArxRleUtils::intToStr(textStyle->flagBits(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display        (UCS)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbUCSTableRecord* ucs)
{
    CString str;

    addSeperatorLine(_T("AcDbUCSTableRecord"));

    addToDataList(_T("Origin"), ArxRleUtils::ptToStr(ucs->origin(), str));
    addToDataList(_T("X Axis"), ArxRleUtils::vectorToStr(ucs->xAxis(), str));
    addToDataList(_T("Y Axis"), ArxRleUtils::vectorToStr(ucs->yAxis(), str));

// TBD: not sure how to call ucsBaseOrigin()
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display        (VIEW)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbViewTableRecord* view)
{
    CString str;

    addSeperatorLine(_T("AcDbViewTableRecord"));

    addToDataList(_T("Is PaperSpace View"), ArxRleUtils::booleanToStr(view->isPaperspaceView(), str));
    addToDataList(_T("Is UCS Associated View"), ArxRleUtils::booleanToStr(view->isUcsAssociatedToView(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::display        (VIEWPORT)
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::display(AcDbViewportTableRecord* viewport)
{
    CString str;

    addSeperatorLine(_T("AcDbViewportTableRecord"));

    addToDataList(_T("Lower Left"), ArxRleUtils::ptToStr(viewport->lowerLeftCorner(), str));
    addToDataList(_T("Upper Right"), ArxRleUtils::ptToStr(viewport->upperRightCorner(), str));
    addToDataList(_T("UCS Follow"), ArxRleUtils::booleanToStr(viewport->ucsFollowMode(), str));
    addToDataList(_T("Circle Sides"), ArxRleUtils::intToStr(viewport->circleSides(), str));
    addToDataList(_T("Fast Zooms"), ArxRleUtils::booleanToStr(viewport->fastZoomsEnabled(), str));
    addToDataList(_T("Icon Enabled"), ArxRleUtils::booleanToStr(viewport->iconEnabled(), str));
    addToDataList(_T("Icon At Origin"), ArxRleUtils::booleanToStr(viewport->iconAtOrigin(), str));
    addToDataList(_T("Grid On"), ArxRleUtils::booleanToStr(viewport->gridEnabled(), str));
    addToDataList(_T("Grid Incr"), ArxRleUtils::ptToStr(viewport->gridIncrements(), str));
    addToDataList(_T("Snap On"), ArxRleUtils::booleanToStr(viewport->snapEnabled(), str));
    addToDataList(_T("ISO Snap On"), ArxRleUtils::booleanToStr(viewport->isometricSnapEnabled(), str));
    addToDataList(_T("Snap Pair"), ArxRleUtils::intToStr(viewport->snapPair(), str));
    addToDataList(_T("Snap Angle"), ArxRleUtils::angleToStr(viewport->snapAngle(), str));
    addToDataList(_T("Snap Base"), ArxRleUtils::ptToStr(viewport->snapBase(), str));
    addToDataList(_T("Snap Incr"), ArxRleUtils::ptToStr(viewport->snapIncrements(), str));
    addToDataList(_T("Is UCS Saved WIth Viewport"), ArxRleUtils::booleanToStr(viewport->isUcsSavedWithViewport(), str));
}

/****************************************************************************
**
**  ArxRleUiTdcDbObjectBase::displayGeCurve3d
**
**  **jma
**
*************************************/

void
ArxRleUiTdcDbObjectBase::displayGeCurve2d(const AcGeCurve2d* curve, int edgeType)
{
    CString curveStr = _T("Curve Type");
    CString str, str2;

    if (curve->isKindOf(AcGe::kLineSeg2d)) {
        ASSERT(edgeType == AcDbHatch::kLine);
        const AcGeLineSeg2d* line = static_cast<const AcGeLineSeg2d*>(curve);
        addToDataList(curveStr, _T("Line"));
        addToDataList(_T("Start Point"), ArxRleUtils::ptToStr(line->startPoint(), str));
        addToDataList(_T("End Point"), ArxRleUtils::ptToStr(line->endPoint(), str));
    }
    else if (curve->isKindOf(AcGe::kCircArc2d)) {
        ASSERT(edgeType == AcDbHatch::kCirArc);
        const AcGeCircArc2d* arc = static_cast<const AcGeCircArc2d*>(curve);
        if (arc->isClosed()) {
            addToDataList(curveStr, _T("Circle"));
            addToDataList(_T("Center"), ArxRleUtils::ptToStr(arc->center(), str));
            addToDataList(_T("Radius"), ArxRleUtils::doubleToStr(arc->radius(), str));

        }
        else {
            addToDataList(curveStr, _T("Arc"));
            addToDataList(_T("Center"), ArxRleUtils::ptToStr(arc->center(), str));
            addToDataList(_T("Radius"), ArxRleUtils::doubleToStr(arc->radius(), str));
            addToDataList(_T("Start Angle"), ArxRleUtils::angleToStr(arc->startAng(), str));
            addToDataList(_T("End Angle"), ArxRleUtils::angleToStr(arc->endAng(), str));
        }
    }
    else if (curve->isKindOf(AcGe::kEllipArc2d)) {
        ASSERT(edgeType == AcDbHatch::kEllArc);
        const AcGeEllipArc2d* ellip = static_cast<const AcGeEllipArc2d*>(curve);
        if (ellip->isClosed()) {
            addToDataList(curveStr, _T("Ellipse"));
            addToDataList(_T("Center"), ArxRleUtils::ptToStr(ellip->center(), str));
            addToDataList(_T("Minor Radius"), ArxRleUtils::doubleToStr(ellip->minorRadius(), str));
            addToDataList(_T("Major Radius"), ArxRleUtils::doubleToStr(ellip->majorRadius(), str));
            addToDataList(_T("Minor Axis"), ArxRleUtils::vectorToStr(ellip->minorAxis(), str));
            addToDataList(_T("Major Axis"), ArxRleUtils::vectorToStr(ellip->majorAxis(), str));
        }
        else {
            addToDataList(curveStr, _T("Elliptical Arc"));
            addToDataList(_T("Center"), ArxRleUtils::ptToStr(ellip->center(), str));
            addToDataList(_T("Minor Radius"), ArxRleUtils::doubleToStr(ellip->minorRadius(), str));
            addToDataList(_T("Major Radius"), ArxRleUtils::doubleToStr(ellip->majorRadius(), str));
            addToDataList(_T("Minor Axis"), ArxRleUtils::vectorToStr(ellip->minorAxis(), str));
            addToDataList(_T("Major Axis"), ArxRleUtils::vectorToStr(ellip->majorAxis(), str));
            addToDataList(_T("Start Angle"), ArxRleUtils::angleToStr(ellip->startAng(), str));
            addToDataList(_T("End Angle"), ArxRleUtils::angleToStr(ellip->endAng(), str));
            addToDataList(_T("Start Point"), ArxRleUtils::ptToStr(ellip->startPoint(), str));
            addToDataList(_T("End Point"), ArxRleUtils::ptToStr(ellip->endPoint(), str));
        }
    }
    else if (curve->isKindOf(AcGe::kSplineEnt2d)) {
        ASSERT(edgeType == AcDbHatch::kSpline);
        const AcGeSplineEnt2d* spline = static_cast<const AcGeSplineEnt2d*>(curve);
        addToDataList(curveStr, _T("Spline"));
        addToDataList(_T("Is Rational"), ArxRleUtils::booleanToStr(spline->isRational(), str));
        addToDataList(_T("Has Fit Data"), ArxRleUtils::booleanToStr(spline->hasFitData(), str));
        addToDataList(_T("Degree"), ArxRleUtils::intToStr(spline->degree(), str));
        addToDataList(_T("Order"), ArxRleUtils::intToStr(spline->order(), str));
        addSeperatorLine(_T("Knots"));
        for (int i=0; i<spline->numKnots(); i++) {
            str2.Format(_T("Knot #%d"), i+1);
            addToDataList(str2, ArxRleUtils::doubleToStr(spline->knotAt(i), str));
        }
        addSeperatorLine(_T("Control Points"));
        for (int ii=0; ii<spline->numControlPoints(); ii++) {
            str2.Format(_T("Control Pt #%d"), ii+1);
            addToDataList(str2, ArxRleUtils::ptToStr(spline->controlPointAt(ii), str));
        }
    }
    else {
        addToDataList(_T("Curve Type"), _T("*Unknown*"));
    }
}


