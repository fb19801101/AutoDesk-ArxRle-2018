//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"
#include "ArxRle.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "AcExtensionModule.h"
#include "App/ArxRleEdUiContext.h"
#include "App/ArxRleMsgHandler.h"
#include "App/ArxRlePaletteAttribute.h"
#include "Cmd\ArxRleCmdLayer.h"
#include "Cmd\ArxRleCmdText.h"
#include "Cmd\ArxRleCmdDim.h"
#include "Cmd\ArxRleCmdEnt.h"
#include "Cmd\ArxRleCmdBlock.h"
#include "Cmd\ArxRleCmdDraw.h"
#include "Cmd\ArxRleCmdMeasure.h"
#include "AdeskLogo/ArxRleDbAdeskLogo.h"
#include "AdeskLogo/ArxRleDbAdeskLogoStyle.h"
#include "AdeskLogo/ArxRleCmdAdeskLogo.h"
#include "DbEntity/ArxRleDbDictRecord.h"
#include "DbEntity/ArxRleDbEntity.h"
#include "Filer/ArxRleDwgFiler.h"
#include "Filer/ArxRleReferenceFiler.h"
#include "Reactor/ArxRleAppEditorReactor.h"
#include "Reactor/ArxRleDatabaseReactor.h"
#include "Reactor/ArxRleDLinkerReactor.h"
#include "Reactor/ArxRleDocumentReactor.h"
#include "Reactor/ArxRleEditorReactor.h"
#include "Reactor/ArxRleEventReactor.h"
#include "Reactor/ArxRleGsReactor.h"
#include "Reactor/ArxRleLayoutManagerReactor.h"
#include "Reactor/ArxRleLongTransactionReactor.h"
#include "Reactor/ArxRleTransactionReactor.h"
#include "Reactor/ArxRlePersistentEntReactor.h"
#include "Reactor/ArxRlePersistentObjReactor.h"
#include "Reactor/ArxRleTransientEntReactor.h"
#include "Reactor/ArxRleTransientObjReactor.h"
#include "Reactor/ArxRleUiTdmReactors.h"
#include "Reactor/ArxRleCmdReactors.h"
#include "Reactor/ArxRleEdMapReactor.h"
#include "Reactor/ArxRleDbDoubleClickEdit.h"
#include "Reactor/ArxRleInputPointMonitor.h"
#include "NetPlan\ArxRleCmdNetPlanWork.h"
#include "NetPlan\ArxRleNetPlanWork.h"
#include "NetPlan\ArxRleNetPlanWorkStyle.h"
#include "StructAnalysis\ArxRleCmdStructAnalysis.h"
#include "ExEntity/ArxRleCmdExEntity.h"
#include "ExEntity/ArxRleBrokenLine.h"
#include "ExEntity/ArxRleTitleLabel.h"
#include "ExEntity/ArxRleLeadDimension.h"
#include "Test/ArxRleCmdTests.h"
#include "Test/ArxRleWorldDraw.h"
#include "Snoop/ArxRleCmdSnoop.h"
#include "TdClone/ArxRleUiTdcOptions.h"
#include "UiDlg/ArxRleUiDlgSplash.h"
#include "UiDlg/ArxRleUiDlgWindoType.h"
#include "UiDlg/ArxRleUiDlgAboutBox.h"
#include "UiDlg/ArxRleUiDlgReg.h"


HINSTANCE ArxRleApp::m_hInstance = NULL;
CXTPToolBar* ArxRleApp::m_pToolBar = NULL;
CXTPCommandBars* ArxRleApp::m_pCommandBars = NULL;
CXTPDockingPaneManager* ArxRleApp::m_pPanePaintManager = NULL;
BOOL ArxRleApp::m_bFilterWinMsg = FALSE;
BOOL ArxRleApp::m_bWatchWinMsg = FALSE;
BOOL ArxRleApp::m_bIsAdmin = TRUE;

#pragma data_seg("SharedDataName")
HHOOK ArxRleApp::m_hWndProcHook = NULL;
#pragma comment(linker,"/section:.SharedDataName,rws")
#pragma data_seg()


extern void LoadMenuThroughCom();
extern void ArxReg();
extern void TableDataLink();
extern void ImportExcel1();
extern void ImportExcel2();
extern void ExportExcel1();
extern void ExportExcel2();
extern void entProperty();
extern void LoadLisp();

extern void cmdAboutBox();
extern void mapTestExportDwg();
extern void mapTestImportDwg();
extern void testApply();


AC_IMPLEMENT_EXTENSION_MODULE(ArxRleDll);

ArxRleApp*    ThisApp = NULL;

/****************************************************************************
**
**  DllMain
**
**  **jma
**
*************************************/

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        ArxRleDll.AttachInstance(hInstance);
        ThisApp = new ArxRleApp;
		ArxRleApp::m_hInstance = hInstance;
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        ArxRleDll.DetachInstance();  
        if (ThisApp) {
            delete ThisApp;
            ThisApp = NULL;
			ArxRleApp::m_hInstance = NULL;
        }
    }
    return 1;   // ok
}

/****************************************************************************
**
**  acrxEntryPoint:
**
**  **jma
**
*************************************/

extern "C" __declspec(dllexport) AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pPkt)
{
    return ThisApp->entryPoint(msg, pPkt);
}

/****************************************************************************
**
**  ArxRleApp::getApp
**      static function to get access to this module in general
**
**  **jma
**
*************************************/

ArxRleApp*
ArxRleApp::getApp()
{
    return ThisApp;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  ArxRleApp::ArxRleApp
**
**  **jma
**
*************************************/

ArxRleApp::ArxRleApp()
:   m_isUnlockable(true),
    m_acadAppPtr(NULL),
    m_appServicePtr(NULL),
    m_appName(_T("ArxRle")),
    m_verStr(_T("5.0")),
    m_appId(0),
    m_didInit(false),
	m_pUiTdcOptions(NULL)
{
	m_moduleName = m_appName;
#ifdef _DEBUG
    m_moduleName += _T("D");
#endif
}

/****************************************************************************
**
**  ArxRleApp::~ArxRleApp
**
**  **jma
**
*************************************/

ArxRleApp::~ArxRleApp()
{
	//ASSERT(m_pUiTdcOptions == NULL);	// TBD: should have been deleted by a call to endDialog

	if (m_pUiTdcOptions)
		delete m_pUiTdcOptions;
}

/****************************************************************************
**
**  ArxRleApp::entryPoint
**      print out message saying that we recieved the app message from ARX
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::entryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    if (msg == AcRx::kInitAppMsg) {
		m_acadAppPtr = pkt;	// keep track of this for later use
        acutPrintf(_T("\nAPPMSG: %s, kInitAppMsg"), m_appName);
        return initApp();
    }
    else if (msg == AcRx::kUnloadAppMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kUnloadAppMsg"), m_appName);
        return exitApp();
    }
    else if (msg == AcRx::kLoadDwgMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kLoadDwgMsg"), m_appName);
        return initDwg();
    }
    else if (msg == AcRx::kUnloadDwgMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kUnloadDwgMsg"), m_appName);
        return exitDwg();
    }
    else if (msg == AcRx::kInvkSubrMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kInvkSubrMsg"), m_appName);
        return invokeSubr();
    }
    else if (msg == AcRx::kCfgMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kCfgMsg"), m_appName);
        return config();
    }
    else if (msg == AcRx::kEndMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kEndMsg"), m_appName);
        return endDwg();
    }
    else if (msg == AcRx::kQuitMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kQuitMsg"), m_appName);
        return quitDwg();
    }
    else if (msg == AcRx::kSaveMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kSaveMsg"), m_appName);
        return saveDwg();
    }
    else if (msg == AcRx::kDependencyMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kDependencyMsg"), m_appName);

        if (m_appServicePtr == pkt) {
            acutPrintf(_T("\nLocking app: %s"), m_appName);
            acrxDynamicLinker->lockApplication(m_acadAppPtr);
        }

        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kNoDependencyMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kNoDependencyMsg"), m_appName);

        if (m_appServicePtr == pkt) {
            acutPrintf(_T("\nUnlocking app: %s"), m_appName);
            acrxDynamicLinker->unlockApplication(m_acadAppPtr);
        }

        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kOleUnloadAppMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kOleUnloadAppMsg"), m_appName);
        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kPreQuitMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kPreQuitMsg"), m_appName);
        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kInitDialogMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kInitDialogMsg"), m_appName);
        return initDialog(pkt);
    }
    else if (msg == AcRx::kEndDialogMsg) {
        acutPrintf(_T("\nAPPMSG: %s, kEndDialogMsg"), m_appName);
        return endDialog(pkt);
    }
    else {
        ASSERT(0);        // just see if it ever happens
        return AcRx::kRetOK;
    }
}

/****************************************************************************
**
**  ArxRleApp::initApp
**      Called one time only each time the application is loaded. Init
**  only those things that are specific to the application itself, not the
**  current drawing.
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::initApp()
{
    acrxUnlockApplication(m_acadAppPtr);
    acrxDynamicLinker->registerAppMDIAware(m_acadAppPtr);

    // get the name of this app so we can find where other
    // things are located.
    CString appFileName = acedGetAppName();

    TCHAR dir[_MAX_DIR], drive[_MAX_DRIVE], path[_MAX_PATH];
    _tsplitpath_s(appFileName, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0);
    _tmakepath(path, drive, dir, NULL, NULL);
    m_appPath = path;

	CWnd* splashScreen = startSplashScreen();

	CTime tmBegin(2017,10,1,0,0,0);
	CTime tmEnd = CTime(2017,12,31,0,0,0);
	DelRegSoft(tmBegin);

	if(m_bIsAdmin)
	{
		_printf(L"\n************************** WARING **************************");
		_printf(L"\n********  欢迎使用施工绘图辅助软件 v8.0  [专业版]！ ********");
		_printf(L"\n************************************************************\n");

		registerClasses(); //注册类
		registerCommands(); //注册命令
		acrxBuildClassHierarchy(); //加载类对象啊
	}
	else
	{
		if(IsRegSoft())
		{
			_printf(L"\n************************** WARING **************************");
			_printf(L"\n********  欢迎使用施工绘图辅助软件 v8.0  [注册版]！ ********");
			_printf(L"\n************************************************************\n");
			registerClasses(); //注册类
			registerCommands(); //注册命令
			acrxBuildClassHierarchy(); //加载类对象
		}
		else
		{
			_printf(L"\n************************** WARING **************************");
			_printf(L"\n********  欢迎使用施工绘图辅助软件 v8.0  [试用版]！ ********");
			_printf(L"\n************************************************************\n");

			CTime tm = CTime::GetCurrentTime();
			if(tm > tmBegin && tm < tmEnd)
			{
				registerClasses(); //注册类
				registerCommands(); //注册命令
				acrxBuildClassHierarchy(); //加载类对象
			}
			else
			{
				_printf(L"\n************************* WARING ************************");
				_printf(L"\n********  您的试用有效期至   2017-12-31   结束！ ********");
				_printf(L"\n********  您的试用权限已过期，请联系管理员注册！ ********");
				_printf(L"\n*********************************************************\n");
			}
		}
	}

    m_appServicePtr = acrxRegisterService(_T("ArxRleServices"));

    ArxRleAppEditorReactor::getInstance();
    ArxRleEdMapReactor::getInstance();

	registerDialogExtensions();
	registerAppMenu();
	registerContextMenu();

	endSplashScreen(splashScreen);

    m_didInit = true;
	//ArxRleMsgHandler::CreateMsgHandler();
	//RegisterFilterWinMsg();
	//RegisterWatchWinMsg();

    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxRleApp::exitApp:
**      Clean up any application related stuff.  Note that we must
**  be unlocked in order to allow unloading.
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::exitApp()
{
	unRegisterContextMenu();
	unRegisterAppMenu();

	// delete any of the notification spies that have been allocated
	ArxRleUiTdmReactors::cleanUpReactors();
	ArxRleAppEditorReactor::destroyInstance();
	ArxRleEdMapReactor::destroyInstance();

    if (m_didInit) {
        unRegisterCommands();
        unRegisterClasses();

        acutPrintf(_T("\n%s has been unloaded ... "), appName());
    }

	ArxRleMsgHandler::DestroyMsgHandler();
	//RemoveFilterWinMsg();
	//RemoveWatchWinMsg();

    return AcRx::kRetOK;
}

/****************************************************************************
**
**  ArxRleApp::initDwg:
**      Called each time a drawing is loaded. Initialize drawing
**  specific information.
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::initDwg()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxRleApp::exitDwg:
**      Called each time a drawing is exited. Clean up anything
**  that is drawing specific.
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::exitDwg()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxRleApp::saveDwg:
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::saveDwg()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxRleApp::endDwg:
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::endDwg()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxRleApp::quitDwg
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::quitDwg()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxRleApp::config
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::config()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxRleApp::invokeSubr
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::invokeSubr()
{
		// this is just a place-holder for tests
    return AcRx::kRetOK;
}

/****************************************************************************
**
**  ArxRleApp::initDialog
**      Called indirectly from a tab-extensible dialog (during initialization) 
**      that this app is registered with.
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::initDialog(void* pkt)
{
    CAdUiTabExtensionManager* pTabExtMgr = static_cast<CAdUiTabExtensionManager*>(pkt);

        // Get name of extensible dialog
    CString tabDlgName = pTabExtMgr->GetDialogName();

        // Add the "ArxRle" tab to the Options dialog
    if (!tabDlgName.CompareNoCase(_T("OptionsDialog"))) {

			// TBD: It seems that we have to hold on to the dialog between invocations.
			// I would think that we would get a call to endDialog that would allow us
			// to delete the dialog after it closes... but that doesn't appear to be
			// the case.
		if (m_pUiTdcOptions == NULL)
			m_pUiTdcOptions = new ArxRleUiTdcOptions;

        if (m_pUiTdcOptions) {
            pTabExtMgr->AddTab(dllInstance(), ARXRLE_TDC_OPTIONS, _T("ArxRle"), m_pUiTdcOptions);
        }
    }

    return AcRx::kRetOK;
}

/****************************************************************************
**
**  ArxRleApp::endDialog
**
**  **jma
**
*************************************/

AcRx::AppRetCode
ArxRleApp::endDialog(void* pTabExtMgr)
{
		// TBD: why does this never get called?
	delete m_pUiTdcOptions;
    m_pUiTdcOptions = NULL;

    return AcRx::kRetOK;
}

/**************************************************************************
**
**  ArxRleApp::registerClasses:
**		call rxInit on all classes we have defined that are derived
**	from AcRxObject or any of its descendants
**
**  **jma
**
*************************************/

void
ArxRleApp::registerClasses()
{
	ArxRlePersistentObjReactor::rxInit();    // our test case for persistent object reactors
	ArxRlePersistentEntReactor::rxInit();    // our test case for persistent entity reactors
	ArxRleTransientObjReactor::rxInit();     // our test case for transient object reactors
	ArxRleTransientEntReactor::rxInit();     // our test case for transient entity reactors

	ArxRleDwgFiler::rxInit();
	ArxRleReferenceFiler::rxInit();

	ArxRleGiContext::rxInit();
	ArxRleGiSubEntityTraits::rxInit();
	ArxRleGiWorldGeometry::rxInit();
	ArxRleGiWorldDraw::rxInit();

	ArxRleDbDictRecord::rxInit();    // test case for basic dictionary entry
	ArxRleDbEntity::rxInit();
	ArxRleDbAdeskLogo::rxInit();
	ArxRleDbAdeskLogoStyle::rxInit();
	ArxRleNetPlanWork::rxInit();
	ArxRleNetPlanWorkStyle::rxInit();
	ArxRleTitleLabel::rxInit();
	ArxRleBrokenLine::rxInit();
	ArxRleLeadDimension::rxInit();

	ArxRleAppEditorReactor::rxInit();
	ArxRleDatabaseReactor::rxInit();
	ArxRleDLinkerReactor::rxInit();
	ArxRleDocumentReactor::rxInit();
	ArxRleEditorReactor::rxInit();
	ArxRleEventReactor::rxInit();
	ArxRleLayoutManagerReactor::rxInit();
	ArxRleLongTransactionReactor::rxInit();
	ArxRleTransactionReactor::rxInit();
	ArxRleDbDoubleClickEdit::rxInit();
	ArxRleInputPointMonitor::rxInit();
}

/**************************************************************************
**
**  ArxRleApp::unRegisterClasses:
**      reverse everything done in ArxRleApp::registerClasses()
**
**  **jma
**
*************************************/

void
ArxRleApp::unRegisterClasses()
{
	deleteAcRxClass(ArxRlePersistentEntReactor::desc());
	deleteAcRxClass(ArxRlePersistentObjReactor::desc());
	deleteAcRxClass(ArxRleTransientEntReactor::desc());
	deleteAcRxClass(ArxRleTransientObjReactor::desc());

	deleteAcRxClass(ArxRleDwgFiler::desc());
	deleteAcRxClass(ArxRleReferenceFiler::desc());

	deleteAcRxClass(ArxRleGiWorldDraw::desc());
	deleteAcRxClass(ArxRleGiWorldGeometry::desc());
	deleteAcRxClass(ArxRleGiSubEntityTraits::desc());
	deleteAcRxClass(ArxRleGiContext::desc());

	deleteAcRxClass(ArxRleDbAdeskLogo::desc());
	deleteAcRxClass(ArxRleDbAdeskLogoStyle::desc());
	deleteAcRxClass(ArxRleNetPlanWork::desc());
	deleteAcRxClass(ArxRleNetPlanWorkStyle::desc());
	deleteAcRxClass(ArxRleDbDictRecord::desc());
	deleteAcRxClass(ArxRleDbEntity::desc());
	deleteAcRxClass(ArxRleTitleLabel::desc());
	deleteAcRxClass(ArxRleBrokenLine::desc());
	deleteAcRxClass(ArxRleLeadDimension::desc());

	deleteAcRxClass(ArxRleAppEditorReactor::desc());
	deleteAcRxClass(ArxRleDatabaseReactor::desc());
	deleteAcRxClass(ArxRleDLinkerReactor::desc());
	deleteAcRxClass(ArxRleDocumentReactor::desc());
	deleteAcRxClass(ArxRleEditorReactor::desc());
	deleteAcRxClass(ArxRleEventReactor::desc());
	deleteAcRxClass(ArxRleLayoutManagerReactor::desc());
	deleteAcRxClass(ArxRleLongTransactionReactor::desc());
	deleteAcRxClass(ArxRleTransactionReactor::desc());
	deleteAcRxClass(ArxRleDbDoubleClickEdit::desc());
	deleteAcRxClass(ArxRleInputPointMonitor::desc());
}

/**************************************************************************
**
**  ArxRleApp::registerCommands:
**
**  **jma
**
*************************************/

void
ArxRleApp::registerCommands()
{
	// allocate the command classes.  These will in turn register their own
	// group of CmdLine functions through AcEd::addCommand()
	m_cmdClasses.append(new ArxRleCmdAdeskLogo);
	m_cmdClasses.append(new ArxRleCmdNetPlanWork);
	m_cmdClasses.append(new ArxRleCmdStructAnalysis);
	m_cmdClasses.append(new ArxRleCmdExEntity);
	m_cmdClasses.append(new ArxRleCmdSnoop);
	m_cmdClasses.append(new ArxRleCmdReactors);
	m_cmdClasses.append(new ArxRleCmdTests);
	m_cmdClasses.append(new ArxRleCmdLayer);
	m_cmdClasses.append(new ArxRleCmdEnt);
	m_cmdClasses.append(new ArxRleCmdDim);
	m_cmdClasses.append(new ArxRleCmdText);
	m_cmdClasses.append(new ArxRleCmdBlock);
	m_cmdClasses.append(new ArxRleCmdDraw);
	m_cmdClasses.append(new ArxRleCmdMeasure);

	AcEdCommandStack* cmdStack = acedRegCmds;
	VERIFY(cmdStack != NULL);

	ArxRleCmd* tmpCmdClass;
	int len = m_cmdClasses.length();
	for (int i=0; i<len; i++)
	{
		tmpCmdClass = static_cast<ArxRleCmd*>(m_cmdClasses[i]);
		tmpCmdClass->registerCommandLineFunctions(cmdStack, m_appName);
	}

	// add in a few stragglers that don't have their own ArxRleCmd class yet
	cmdStack->addCommand(m_appName, _T("ArxRleAbout"),                 _T("ArxAbout"),              ACRX_CMD_MODAL, &cmdAboutBox);

	// GIS Map tests for ADE									  	    	      			        
	cmdStack->addCommand(m_appName, _T("ArxRleMapTestExport"),         _T("MapExport"),             ACRX_CMD_MODAL, &mapTestExportDwg);
	cmdStack->addCommand(m_appName, _T("ArxRleMapTestImport"),         _T("MapImport"),             ACRX_CMD_MODAL, &mapTestImportDwg);

	// 添加菜单命令
	cmdStack->addCommand(m_appName, _T("ArxRleArxReg"),                _T("ArxReg"),                ACRX_CMD_MODAL, &ArxReg);
	cmdStack->addCommand(m_appName, _T("ArxRleTableDataLink"),         _T("TableDataLink"),         ACRX_CMD_MODAL, &TableDataLink);
	cmdStack->addCommand(m_appName, _T("ArxRleImportExcel1"),          _T("ImportExcel1"),          ACRX_CMD_MODAL, &ImportExcel1);
	cmdStack->addCommand(m_appName, _T("ArxRleImportExcel2"),          _T("ImportExcel2"),          ACRX_CMD_MODAL, &ImportExcel2);
	cmdStack->addCommand(m_appName, _T("ArxRleExportExcel1"),          _T("ExportExcel1"),          ACRX_CMD_MODAL, &ExportExcel1);
	cmdStack->addCommand(m_appName, _T("ArxRleExportExcel2"),          _T("ExportExcel2"),          ACRX_CMD_MODAL, &ExportExcel2);
	cmdStack->addCommand(m_appName, _T("ArxRleEntAttribute"),          _T("EntAttribute"),          ACRX_CMD_MODAL, &ArxRlePaletteAttribute::entAttribute);
	cmdStack->addCommand(m_appName, _T("ArxRleEntProperty"),           _T("EntProperty"),           ACRX_CMD_MODAL, &entProperty);
	cmdStack->addCommand(m_appName, _T("ArxRleLoadLisp"),              _T("LoadLisp"),              ACRX_CMD_MODAL, &LoadLisp);

	// 添加实体命令
	cmdStack->addCommand(m_appName, _T("ArxRleTestApply"),             _T("TestApply"),             ACRX_CMD_MODAL, &testApply);

	//外部调用命令
	cmdStack->addCommand(m_appName, _T("ArxRleWindoDlg"),              _T("WinDo"),                 ACRX_CMD_MODAL, &ArxRleUiDlgWindoType::showWindoDlg);
}

/**************************************************************************
**
**  ArxRleApp::unRegisterCommands:
**
**  **jma
**
*************************************/

void
ArxRleApp::unRegisterCommands()
{
		// delete any command classes we have allocated
	ArxRleCmd* tmpCmdClass;
	int len = m_cmdClasses.length();
	for (int i=0; i<len; i++) {
		tmpCmdClass = static_cast<ArxRleCmd*>(m_cmdClasses[i]);
		delete tmpCmdClass;
	}

	m_cmdClasses.setLogicalLength(0);

    acedRegCmds->removeGroup(m_appName);    // remove any registered commands
}

/**************************************************************************
**
**  ArxRleApp::startSplashScreen
**
**  **jma
**
*************************************/

CWnd*
ArxRleApp::startSplashScreen()
{
    CString bmpFileName = appPath();
    bmpFileName += _T("support\\ArxRle\\Splash.bmp");    // TBD: make this better later!

        // make sure file is there (either in a main directory, which is
		// where someone would install it, or for developers, go out of 
		// "Debug" directory and up to the main directory.
    CFileStatus status;
    // Watch out for exceptions from GetStatus() due to bad date fields on the file.
    BOOL success = false;
    try {
        success = CFile::GetStatus(bmpFileName, status); // try/catch safe
        if (success == FALSE) {
    	    bmpFileName = appPath();
    	    //x64 binaries are created within x64\ folder
#if defined(_WIN64) || defined(_AC64)
        	bmpFileName += _T("ArxRle\\Splash.bmp");  // TBD: make this better later!
#else
        	bmpFileName += _T("ArxRle\\Splash.bmp");  // TBD: make this better later!
#endif
    	    success = CFile::GetStatus(bmpFileName, status);  // try/catch safe
        }
    }
    catch (COleException* e) {
        e->Delete();
        // If we get here the file exists but it has a bad date field
        success = true;
    }

	if (success) {
        ArxRleUiDlgSplash* dbox = new ArxRleUiDlgSplash(bmpFileName);
        dbox->setTextStrings(appName(), versionStr(), _T(""), _T(""));

			// TBD: have to do this manually right now, although it should
			// have worked to pass up resource handle through the constructor!
		acDocManager->pushAcadResourceHandle(/*dllInstance()*/);
        dbox->Create(acedGetAcadDwgView());
		acDocManager->popResourceHandle();

        dbox->ShowWindow(SW_SHOW);
        dbox->UpdateWindow();

        return dbox;
    }
    else {        // intended a splash screen but could not find it!
        acutPrintf(_T("\nCould not find splash box image: \"%s\""), bmpFileName);
        return NULL;
    }
}

/**************************************************************************
**
**  ArxRleApp::endSplashScreen
**
**  **jma
**
*************************************/

void
ArxRleApp::endSplashScreen(CWnd* splashScreen)
{
    if (splashScreen) {
        Sleep(1000);    // waste a little bit of time to ensure that they see it
        splashScreen->ShowWindow(SW_HIDE);
        splashScreen->UpdateWindow();
        splashScreen->DestroyWindow();
        delete splashScreen;
        acedGetAcadDwgView()->Invalidate();
        acedGetAcadDwgView()->UpdateWindow();
    }
}

/**************************************************************************
**
**  ArxRleApp::registerMenu
**
**  **000
**
*************************************/

void
ArxRleApp::registerContextMenu()
{
	m_pEdUiContext = new ArxRleEdUiContext();
	if ((m_pEdUiContext->isValid() == false) ||
		(acedAddDefaultContextMenu(m_pEdUiContext, m_acadAppPtr, _T("ArxRle")) == false)) {
			ASSERT(0);

			delete m_pEdUiContext;
			m_pEdUiContext = NULL;
	}

	m_pEntContext = new ArxRleEdUiContext(1);
	if ((m_pEntContext->isValid() == false) ||
		(acedAddObjectContextMenu(AcDbEntity::desc(),m_pEntContext, m_acadAppPtr) == false)) {
		ASSERT(0);

		delete m_pEntContext;
		m_pEntContext = NULL;
	}
}

/**************************************************************************
**
**  ArxRleApp::unRegisterMenu
**
**  **000
**
*************************************/

void
ArxRleApp::unRegisterContextMenu()
{
	if(m_pEdUiContext)
	{
		acedRemoveDefaultContextMenu(m_pEdUiContext);
		delete m_pEdUiContext;
		m_pEdUiContext = NULL;
	}

	if(m_pEntContext)
	{
		acedRemoveObjectContextMenu(AcDbEntity::desc(), m_pEntContext);
		delete m_pEntContext;
		m_pEntContext = NULL;
	}
}

/**************************************************************************
**
**  ArxRleApp::registerAppMenu
**
**  **000
**
*************************************/

void
ArxRleApp::registerAppMenu()
{
	acutPrintf(_T("XTPToolkitPro CommandBars Test; Type XTPCommandBars to execute"));
	CreateCommandBars();
	LoadMenuThroughCom();
}

/**************************************************************************
**
**  ArxRleApp::unRegisterAppMenu
**
**  **000
**
*************************************/

void
ArxRleApp::unRegisterAppMenu()
{
	if(m_pToolBar != NULL)
		CMDTARGET_RELEASE(m_pToolBar);

	if(m_pPanePaintManager != NULL)
		CMDTARGET_RELEASE(m_pPanePaintManager);

	if(m_pCommandBars != NULL)
		CMDTARGET_RELEASE(m_pCommandBars);

	if(m_hWndProcHook != NULL)
		UnhookWindowsHookEx(m_hWndProcHook);
}

/**************************************************************************
**
**  ArxRleApp::registerDialogExtensions
**
**  **jfk
**
*************************************/

void
ArxRleApp::registerDialogExtensions()
{
        // Register the fact that we want to add a tab to the following dialogs
    acedRegisterExtendedTab(m_moduleName, _T("OptionsDialog"));
}

/**************************************************************************
**
**  ArxRleApp::dllInstance
**
**  **jma
**
*************************************/

HINSTANCE
ArxRleApp::dllInstance() const
{
	return ArxRleDll.ModuleResourceInstance();
}

bool
ArxRleApp::IsRegSoft()
{
	HKEY key;
	DWORD size = MAX_PATH;
	char data[MAX_PATH];
	DWORD type=REG_SZ;
	ArxRleString skey=L"Software\\Autodesk\\ArxRleSoft";
	if(RegOpenKeyEx(HKEY_CURRENT_USER,skey,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,&key) == ERROR_SUCCESS)
	{
		if(RegQueryValueEx(key,L"RegSerial",NULL,&type,(BYTE*)data,&size) == ERROR_SUCCESS)
		{
			ArxRleString serial = SnKey(DiskSerial().Mid(3,4)+MacAddress().Mid(4,6));
			char* szStr = new char[size/2+1];
			for(DWORD i=0; i<size/2; i++)
			{
				szStr[i] = data[i*2];
			}
			szStr[size/2] = '\0';
			ArxRleString reg_serial(szStr);
			int index = reg_serial.Find(L"_");
			reg_serial = reg_serial.Right(index+1);
			if(RegQueryValueEx(key,L"IsReged",NULL,&type,(BYTE*)data,&size) == ERROR_SUCCESS)
			{
				szStr = new char[2];
				szStr[0] = data[0];
				szStr[1] = '\0';
				ArxRleString reg_reged(szStr);

				if(serial == reg_serial && reg_reged == ArxRleString("1"))
				{
					RegCloseKey(key);
					return true;
				}
			}
		}
	}

	RegCloseKey(key);
	return false;
}

bool
ArxRleApp::DelRegSoft(CTime tm)
{
	HKEY key;
	DWORD size = MAX_PATH;
	char data[MAX_PATH];
	DWORD type=REG_SZ;
	ArxRleString skey=L"Software\\Autodesk\\ArxRleSoft";
	if(RegOpenKeyEx(HKEY_CURRENT_USER,skey,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,&key) == ERROR_SUCCESS)
	{
		if(RegQueryValueEx(key,L"RegDate",NULL,&type,(BYTE*)data,&size) == ERROR_SUCCESS)
		{
			char* szStr = new char[size/2+1];
			for(DWORD i=0; i<size/2; i++)
			{
				szStr[i] = data[i*2];
			}
			szStr[size/2] = '\0';
			ArxRleString reg_date(szStr);
			RegCloseKey(key);

			ArxRleString year = reg_date.Lefts(4);
			ArxRleString month = reg_date.Mid(5,2);
			ArxRleString day = reg_date.Rights(2);
			CTime tm_reged(year.ToInt(),month.ToInt(),day.ToInt(),0,0,0);
			if(tm_reged < tm)
			{
				skey=L"Software\\Autodesk";
				if(RegOpenKeyEx(HKEY_CURRENT_USER,skey,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,&key) == ERROR_SUCCESS)
				{
					if(RegDeleteKeyEx(key,L"ArxRleSoft",KEY_ALL_ACCESS,0) == ERROR_SUCCESS)
					{
						RegCloseKey(key);
						return true;
					}
				}
			}
		}
	}

	RegCloseKey(key);
	return false;
}

void
ArxRleApp::OnCommands(UINT nID)
{
	// TODO: 在此添加专用代码和/或调用基类
	LPCTSTR cmdStr = NULL;
	CString str;
	switch (nID)
	{
		//////////////图层管理 菜单//////////////
	case ARXRLE_MENU_LAYER:
	case ARXRLE_LAYER_SETCUR:
		cmdStr = _T("ArxRleLayerSetCur");
		break;
	case ARXRLE_LAYER_SHOWALL:
		cmdStr = _T("ArxRleLayerShowAll");
		break;
	case ARXRLE_LAYER_HIDEALL:
		cmdStr = _T("ArxRleLayerHideAll");
		break;
	case ARXRLE_LAYER_HIDEPART:
		cmdStr = _T("ArxRleLayerHidePart");
		break;
	case ARXRLE_LAYER_SHOWBYLAYER:
		cmdStr = _T("ArxRleLayerShowByLayer");
		break;
	case ARXRLE_LAYER_HIDEBYLAYER:
		cmdStr = _T("ArxRleLayerHideByLayer");
		break;
	case ARXRLE_LAYER_SHOWBYCOLOR:
		cmdStr = _T("ArxRleLayerShowByColor");
		break;
	case ARXRLE_LAYER_HIDEBYCOLOR:
		cmdStr = _T("ArxRleLayerHideByColor");
		break;
	case ARXRLE_LAYER_LOCK:
		cmdStr = _T("ArxRleLayerLock");
		break;
	case ARXRLE_LAYER_UNLOCK:
		cmdStr = _T("ArxRleLayerUnLock");
		break;

		//////////////文字管理 菜单//////////////
	case ARXRLE_MENU_TEXT:
	case ARXRLE_TEXT_SETCUR:
		cmdStr = _T("ArxRleTextSetCur");
		break;
	case ARXRLE_TEXT_STYLES:
		cmdStr = _T("ArxRleTextStyles");
		break;
	case ARXRLE_TEXT_SHOWALL:
		cmdStr = _T("ArxRleTextShowAll");
		break;
	case ARXRLE_TEXT_HIDEALL:
		cmdStr = _T("ArxRleTextHideAll");
		break;
	case ARXRLE_TEXT_HIDEPART:
		cmdStr = _T("ArxRleTextHidePart");
		break;
	case ARXRLE_TEXT_SHOWBYSTYLE:
		cmdStr = _T("ArxRleTextShowByStyle");
		break;
	case ARXRLE_TEXT_HIDEBYSTYLE:
		cmdStr = _T("ArxRleTextHideByStyle");
		break;
	case ARXRLE_TEXT_SHOWBYHEIGHT:
		cmdStr = _T("ArxRleTextShowByHeight");
		break;
	case ARXRLE_TEXT_HIDEBYHEIGHT:
		cmdStr = _T("ArxRleTextHideByHeight");
		break;
	case ARXRLE_TEXT_SHOWBYANGLE:
		cmdStr = _T("ArxRleTextShowByAngle");
		break;
	case ARXRLE_TEXT_HIDEBYANGLE:
		cmdStr = _T("ArxRleTextHideByAngle");
		break;
	case ARXRLE_TEXT_SHOWBYSTR:
		cmdStr = _T("ArxRleTextShowByStr");
		break;
	case ARXRLE_TEXT_HIDEBYSTR:
		cmdStr = _T("ArxRleTextHideByStr");
		break;
	case ARXRLE_TEXT_FLUSH:
		cmdStr = _T("ArxRleTextFlush");
		break;
	case ARXRLE_TEXT_CALC:
		cmdStr = _T("ArxRleTextCalc");
		break;
	case ARXRLE_TEXT_IMPORT:
		cmdStr = _T("ArxRleTextImport");
		break;
	case ARXRLE_TEXT_EXPORT:
		cmdStr = _T("ArxRleTextExport");
		break;

		//////////////标注管理 菜单//////////////
	case ARXRLE_MENU_DIM:
	case ARXRLE_DIM_SETCUR:
		cmdStr = _T("ArxRleDimSetCur");
		break;
	case ARXRLE_DIM_SHOWALL:
		cmdStr = _T("ArxRleDimShowAll");
		break;
	case ARXRLE_DIM_HIDEALL:
		cmdStr = _T("ArxRleDimHideAll");
		break;
	case ARXRLE_DIM_HIDEPART:
		cmdStr = _T("ArxRleDimHidePart");
		break;
	case ARXRLE_DIM_SHOWBYSTYLE:
		cmdStr = _T("ArxRleDimShowByStyle");
		break;
	case ARXRLE_DIM_HIDEBYSTYLE:
		cmdStr = _T("ArxRleDimHideByStyle");
		break;
	case ARXRLE_DIM_ENTITY:
		cmdStr = _T("ArxRleDimEntity");
		break;
	case ARXRLE_DIM_LEAD:
		cmdStr = _T("ArxRleLeadDimension");
		break;
	case ARXRLE_DIM_SECTION:
		cmdStr = _T("ArxRleDimSection");
		break;
	case ARXRLE_DIM_PAPER:
		cmdStr = _T("ArxRleTitleLabel");
		break;
	case ARXRLE_DIM_SETSTR:
		cmdStr = _T("ArxRleDimSetStr");
		break;

		//////////////图元管理 菜单//////////////
	case ARXRLE_MENU_ENT:
	case ARXRLE_ENT_DELALL:
		cmdStr = _T("ArxRleEntDelAll");
		break;
	case ARXRLE_ENT_DELBYLAYER:
		cmdStr = _T("ArxRleEntDelByLayer");
		break;
	case ARXRLE_ENT_DELBYCOLOR:
		cmdStr = _T("ArxRleEntDelByColor");
		break;
	case ARXRLE_ENT_CPYBYDIST:
		cmdStr = _T("ArxRleEntCpyByDist");
		break;
	case ARXRLE_ENT_CPYBYANGLE:
		cmdStr = _T("ArxRleEntCpyByAngle");
		break;
	case ARXRLE_ENT_CPYBYIF:
		cmdStr = _T("ArxRleEntCpyByIf");
		break;
	case ARXRLE_ENT_CLRSETBYLAYER:
		cmdStr = _T("ArxRleEntClrSetByLayer");
		break;
	case ARXRLE_ENT_CLRSETBYCOLOR:
		cmdStr = _T("ArxRleEntClrSetByColor");
		break;
	case ARXRLE_ENT_CLRSETBYENTITY:
		cmdStr = _T("ArxRleEntClrSetByEntity");
		break;
	case ARXRLE_ENT_LTSETBYLAYER:
		cmdStr = _T("ArxRleEntLtSetByLayer");
		break;
	case ARXRLE_ENT_LTSETBYCOLOR:
		cmdStr = _T("ArxRleEntLtSetByColor");
		break;
	case ARXRLE_ENT_LTSETBYENTITY:
		cmdStr = _T("ArxRleEntLtSetByEntity");
		break;
	case ARXRLE_ENT_INFOTIP_SHOW:
		cmdStr = _T("ArxRleEntInfoTipShow");
		break;
	case ARXRLE_ENT_INFOTIP_HIDE:
		cmdStr = _T("ArxRleEntInfoTipHide");
		break;
	case ARXRLE_ENT_ATTRIBUTE:
		cmdStr = _T("ArxRleEntAttribute");
		break;
	case ARXRLE_ENT_3DTO2D:
		cmdStr = _T("ArxRleEntConvertTo2d");
		break;

		//////////////测量工具 菜单//////////////
	case ARXRLE_MENU_MEASURE:
	case ARXRLE_MEASURE_CRDTRM:
		cmdStr = _T("ArxRleMeasureCrdTrm");
		break;
	case ARXRLE_MEASURE_CURVE:
		cmdStr = _T("ArxRleMeasureCurve");
		break;
	case ARXRLE_MEASURE_PTINDATA:
		cmdStr = _T("ArxRleMeasurePtInData");
		break;
	case ARXRLE_MEASURE_PTOUTDATA:
		cmdStr = _T("ArxRleMeasurePtOutData");
		break;
	case ARXRLE_MEASURE_DIMXYZ:
		cmdStr = _T("ArxRleMeasureDimXYZ");
		break;
	case ARXRLE_MEASURE_DIMH:
		cmdStr = _T("ArxRleMeasureDimH");
		break;
	case ARXRLE_MEASURE_AREA:
		cmdStr = _T("ArxRleMeasureArea");
		break;
	case ARXRLE_MEASURE_LENGTH:
		cmdStr = _T("ArxRleMeasureLength");
		break;
	case ARXRLE_MEASURE_ALL_AREA:
		cmdStr = _T("ArxRleMeasureAllArea");
		break;
	case ARXRLE_MEASURE_ALL_LENGTH:
		cmdStr = _T("ArxRleMeasureAllLength");
		break;

		//////////////通用绘图 菜单//////////////
	case ARXRLE_DRAW_HATCH:
		cmdStr = _T("ArxRleDrawHatch");
		break;
	case ARXRLE_DRAW_NUMBER:
		cmdStr = _T("ArxRleDrawNumber");
		break;
	case ARXRLE_DRAW_BROKEN:
		cmdStr = _T("ArxRleBroken");
		break;
	case ARXRLE_DRAW_DIMLAND:
		cmdStr = _T("ArxRleDrawDimLand");
		break;
	case ARXRLE_MENU_DRAW:
	case ARXRLE_DRAW_CONDITION:
		cmdStr = _T("ArxRleDrawCondition");
		break;
	case ARXRLE_DRAW_TOPLINE:
		cmdStr = _T("ArxRleChangeToPolyline");
		break;

		//////////////网络计划 菜单//////////////
	case ARXRLE_MENU_NETPLAN:
	case ARXRLE_NETPLAN_PARAM:
		cmdStr = _T("ArxRleNetPlanInitParam");
		break;
	case ARXRLE_NETPLAN_IMPORT_WORK:
		cmdStr = _T("ArxRleNetPlanImportWork");
		break;
	case ARXRLE_NETPLAN_EXPORT_WORK:
		cmdStr = _T("ArxRleNetPlanExportWork");
		break;
	case ARXRLE_NETPLAN_IMPORT_STYLE:
		cmdStr = _T("ArxRleNetPlanImportStyle");
		break;
	case ARXRLE_NETPLAN_EXPORT_STYLE:
		cmdStr = _T("ArxRleNetPlanExportStyle");
		break;
	case ARXRLE_NETPLAN_GRID:
		cmdStr = _T("ArxRleNetPlanInsertGrid");
		break;
	case ARXRLE_NETPLAN_RENR:
		cmdStr = _T("ArxRleNetPlanReNumber");
		break;
	case ARXRLE_NETPLAN_TABLE:
		cmdStr = _T("ArxRleNetPlanInsertTable");
		break;
	case ARXRLE_NETPLAN_DATA:
		cmdStr = _T("ArxRleNetPlanBatchWork");
		break;
	case ARXRLE_NETPLAN_PROC:
		cmdStr = _T("ArxRleNetPlanBatchProc");
		break;
	case ARXRLE_NETPLAN_RESET:
		cmdStr = _T("ArxRleNetPlanReSetProc");
		break;
	case ARXRLE_NETPLAN_WORK:
		cmdStr = _T("ArxRleNetPlanCmdWork");
		break;
	case ARXRLE_NETPLAN_STYLE:
		cmdStr = _T("ArxRleNetPlanFlushStyle");
		break;
	case ARXRLE_NETPLAN_BIND:
		cmdStr = _T("ArxRleNetPlanBindWork");
		break;

		//////////////通用图块 菜单//////////////
	case ARXRLE_MENU_BLOCK:
	case ARXRLE_BLOCK_TK:
		cmdStr = _T("ArxRleBlockTK");
		break;
	case ARXRLE_BLOCK_BTL:
		cmdStr = _T("ArxRleBlockBTL");
		break;
	case ARXRLE_BLOCK_ZBZ:
		cmdStr = _T("ArxRleBlockZBZ");
		break;

		//////////////结构分析 菜单//////////////
	case ARXRLE_STRUCT_CONCRETE:
		cmdStr = _T("ArxRleAnalysisConcrete");
		break;
	case ARXRLE_STRUCT_STEEL:
		cmdStr = _T("ArxRleAnalysisSteel");
		break;
	case ARXRLE_MENU_STRUCT:
	case ARXRLE_STRUCT_SECTION:
		cmdStr = _T("ArxRleSteelSection");
		break;


		//////////////菜单 风格//////////////
	case ARXRLE_MENU_XTPTHEME:
	case ARXRLE_XTPTHEME_ACEDSTYLE:
		CXTPPaintManager::SetCustomTheme(new CAcadStyleTheme);
		break;
	case ARXRLE_XTPTHEME_OFFICE2000:
		CXTPPaintManager::SetTheme(xtpThemeOffice2000);
		break;
	case ARXRLE_XTPTHEME_OFFICEXP:
		CXTPPaintManager::SetTheme(xtpThemeOfficeXP);
		break;
	case ARXRLE_XTPTHEME_OFFICE2003:
		CXTPPaintManager::SetTheme(xtpThemeOffice2003);
		break;
	case ARXRLE_XTPTHEME_WINXP:
		CXTPPaintManager::SetTheme(xtpThemeNativeWinXP);
		break;
	case ARXRLE_XTPTHEME_WHIDBEY:
		CXTPPaintManager::SetTheme(xtpThemeWhidbey);
		break;
	case ARXRLE_XTPTHEME_VS2008:
		CXTPPaintManager::SetTheme(xtpThemeVisualStudio2008);
		break;
	case ARXRLE_XTPTHEME_VS6:
		CXTPPaintManager::SetTheme(xtpThemeVisualStudio6);
		break;
	case ARXRLE_XTPTHEME_VS2010:
		CXTPPaintManager::SetTheme(xtpThemeVisualStudio2010);
		break;
	case ARXRLE_XTPTHEME_CUSTOM:
		CXTPPaintManager::SetTheme(xtpThemeCustom);
		break;


		//////////////应用程序//////////////
	case ARXRLE_PROGRAM_TABLE_IMPORT_1:
		cmdStr = _T("ArxRleImportExcel1");
		break;
	case ARXRLE_PROGRAM_TABLE_IMPORT_2:
		cmdStr = _T("ArxRleImportExcel2");
		break;
	case ARXRLE_PROGRAM_TABLE_IMPORT_3:
		cmdStr = _T("ArxRleTableDataLink");
		break;
	case ARXRLE_PROGRAM_TABLE_EXPORT_1:
		cmdStr = _T("ArxRleExportExcel1");
		break;
	case ARXRLE_PROGRAM_TABLE_EXPORT_2:
		cmdStr = _T("ArxRleExportExcel2");
		break;
	case ARXRLE_MENU_PROGRAM:
	case ARXRLE_PROGRAM_ENTPROTITY:
		cmdStr = _T("ArxRleEntProperty");
		break;
	case ARXRLE_PROGRAM_LOADLISP:
		cmdStr = _T("ArxRleLoadLisp");
		break;


		//////////////帮助 菜单//////////////
	case ARXRLE_HELP_HELP:
		{
			CString filePath = GetCurPath()+ L"\\ArxRle\\help.pdf";
			ShellExecuteOpen(filePath);
		}
		break;
	case ARXRLE_HELP_REG:
		{
			ArxRleUiDlgReg dreg(acedGetAcadDwgView());
			dreg.DoModal();
		}
		break;
	case ARXRLE_HELP_NET:
		{
			ShellExecuteOpen("http://www.cr121.com/");
		}
		break;
	case ARXRLE_MENU_HELP:
	case ARXRLE_HELP_ABOUT:
		{
			ArxRleUiDlgAboutBox dbox(acedGetAcadDwgView());
			dbox.DoModal();
		}
		break;
	default:
		{
			if(ARXRLE_NORM_00 <= nID && nID <= ARXRLE_NORM_49)
			{
				CString filePath = GetCurPath()+ L"\\ArxRle\\norm.dat";
				CStdioFile file;
				if(file.Open(filePath, CFile::modeRead))
				{
					CString str;
					while(file.ReadString(str))
					{
						str.Trim();
						int number = _tstoi(str.Mid(0,2));
						if(nID-ARXRLE_NORM_00 == number)
						{
							ShellExecuteOpen(GetCurPath()+L"\\ArxRle\\"+str);
							break;
						}
					}

					file.Close();
				}
			}
		}
		break;
	}

	if(cmdStr != NULL)
	{
		str.Format(_T("%s\n"), cmdStr);
		acDocManager->sendStringToExecute(acDocManager->curDocument(), str, false, false);
	}
}

LRESULT
CALLBACK ArxRleApp::CallWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(m_pPanePaintManager != NULL && m_pCommandBars != NULL)
	{
		if (nCode<0)
			return CallNextHookEx(m_hWndProcHook, nCode, wParam, lParam);

		CWPSTRUCT* pMsg = (CWPSTRUCT*)lParam;
		if(pMsg->message == WM_COMMAND)
			OnCommands((UINT)pMsg->wParam);

		if (pMsg->message == XTPWM_DOCKINGPANE_NOTIFY/* && pMsg->hwnd == adsw_acadMainWnd()*/)
		{
			if (pMsg->wParam == XTP_DPN_SHOWWINDOW)
			{
				CXTPDockingPane* xtpPane = (CXTPDockingPane*)(pMsg->lParam);

				//也可以不用hook, 直接调用Attach
				//推荐在XTPWM_DOCKINGPANE_NOTIFY消息响应时Attach
				//所以才用hook捕捉 XTPWM_DOCKINGPANE_NOTIFY 消息

				if (!xtpPane->IsValid())
				{
					switch (xtpPane->GetID())
					{
					case ARXRLE_PANE_EXPLORER:
						break;
					case ARXRLE_PANE_ICONS:
						break;
					case ARXRLE_PANE_TOOLS:
						break;
					case ARXRLE_PANE_COLORS:
						break;
					case ARXRLE_PANE_PROPERTIES:
						break;
					}
				}
				return 1;
			}
		}

		return CallNextHookEx(m_hWndProcHook, nCode, wParam, lParam);
	}

	return 0;
}

void
ArxRleApp::CreateCommandBars()
{
	VERIFY(InitCommandBars());

	m_pCommandBars = GetCommandBars();
	m_pCommandBars->GetImageManager()->SetIcons(ARXRLE_MENU_MENUBAR);
	m_pCommandBars->GetImageManager()->SetIcons(ARXRLE_MENU_PROGRAM);
	m_pCommandBars->GetImageManager()->SetIcons(ARXRLE_MENU_NETPLAN);
	CXTPPaintManager::SetCustomTheme(new CAcadStyleTheme);

	//m_pCommandBars->SetMenu(_T("ArxRle"),ARXRLE_MENU_MENUBAR);
	//m_pToolBar = m_pCommandBars->Add(_T("ArxRle"), xtpBarTop);

	m_pToolBar = new CXTPToolBar;
	m_pToolBar->CreateToolBar(WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | TBSTYLE_TRANSPARENT | TBSTYLE_LIST | TBSTYLE_TOOLTIPS | CCS_NODIVIDER | CCS_NORESIZE, acedGetAcadFrame(), ARXRLE_MENU_MENUBAR);
	m_pToolBar->LoadToolBar(ARXRLE_MENU_MENUBAR);

	CMenu menu;
	menu.LoadMenu(ARXRLE_MENU_MENUBAR);
	for(int i=1;i<14;i++)
	{
		m_pToolBar->GetControls()->SetControlType(i,i<4 || i==13 ? xtpControlSplitButtonPopup:xtpControlButtonPopup);
		CXTPControlPopup* pControlPopup = (CXTPControlPopup*)m_pToolBar->GetControls()->GetAt(i);
		pControlPopup->SetCommandBar(menu.GetSubMenu(i-1));
		pControlPopup->SetStyle(i == 13 ? xtpButtonIcon:xtpButtonIconAndCaption);
	}

	CXTPControl* pControl = m_pToolBar->GetControls()->Add(xtpControlLabel,ARXRLE_HELP_REGINFO);
	pControl->SetStyle(xtpButtonCaption);
	if(m_bIsAdmin)
		pControl->SetCaption(_T("  [专业版] "));
	else
	{
		if(IsRegSoft())
			pControl->SetCaption(_T("  [注册版] "));
		else
			pControl->SetCaption(_T("  [试用版] "));
	}

	if(m_pPanePaintManager == NULL)
		m_pPanePaintManager = new CXTPDockingPaneManager;
	m_pPanePaintManager->InstallDockingPanes(acedGetAcadFrame());
	m_pPanePaintManager->SetTheme(xtpPaneThemeVisualStudio2008);

	if(m_hWndProcHook == NULL)
		m_hWndProcHook = SetWindowsHookEx(WH_CALLWNDPROC,  CallWndProc,  m_hInstance, GetCurrentThreadId());
}

void 
ArxRleApp::RegisterFilterWinMsg()
{
	if(!m_bFilterWinMsg)
	{
		if(!acedRegisterFilterWinMsg(FilterCommandBarsMsg))
			acedPrompt(_T("filter can't be registered!\n"));
		else
		{
			acedPrompt(_T("command msg has been defined!\n"));
			m_bFilterWinMsg = TRUE;
		}
	}
}

void 
ArxRleApp::RemoveFilterWinMsg()
{
	if(m_bFilterWinMsg)
	{
		acedRemoveFilterWinMsg(FilterCommandBarsMsg);
		acutPrintf(_T("\nfilter has been removed!\n"));
	}
}

void 
ArxRleApp::RegisterWatchWinMsg()
{
	if(!m_bWatchWinMsg)
	{
		if(!acedRegisterWatchWinMsg(WatchCommandBarsMsg))
			acedPrompt(_T("watch can't be registered!\n"));
		else
		{
			acedPrompt(_T("command msg has been defined!\n"));
			m_bWatchWinMsg = TRUE;
		}
	}
}

void 
ArxRleApp::RemoveWatchWinMsg()
{
	if(m_bWatchWinMsg)
	{
		acedRemoveWatchWinMsg(WatchCommandBarsMsg);
		acutPrintf(_T("\nwatch has been removed!\n"));
	}
}

BOOL //定义过滤消息的函数指针
ArxRleApp::FilterCommandBarsMsg(MSG *pMsg)
{
	if(pMsg->message == WM_COMMAND)
	{
		OnCommands((UINT)pMsg->wParam);
		return TRUE;
	}

	if (pMsg->message == XTPWM_DOCKINGPANE_NOTIFY)
	{
		if (pMsg->wParam == XTP_DPN_SHOWWINDOW)
		{
			CXTPDockingPane* xtpPane = (CXTPDockingPane*)(pMsg->lParam);

			if (!xtpPane->IsValid())
			{
				switch (xtpPane->GetID())
				{
				case ARXRLE_PANE_EXPLORER:
					break;
				case ARXRLE_PANE_ICONS:
					break;
				case ARXRLE_PANE_TOOLS:
					break;
				case ARXRLE_PANE_COLORS:
					break;
				case ARXRLE_PANE_PROPERTIES:
					break;
				}
			}
			return TRUE;
		}
	}

	return FALSE;
}

void //定义监视消息的函数指针
ArxRleApp::WatchCommandBarsMsg(const MSG *pMsg)
{
	if(pMsg->message == WM_COMMAND)
	{
		OnCommands((UINT)pMsg->wParam);
	}

	if (pMsg->message == XTPWM_DOCKINGPANE_NOTIFY)
	{
		if (pMsg->wParam == XTP_DPN_SHOWWINDOW)
		{
			CXTPDockingPane* xtpPane = (CXTPDockingPane*)(pMsg->lParam);

			if (!xtpPane->IsValid())
			{
				switch (xtpPane->GetID())
				{
				case ARXRLE_PANE_EXPLORER:
					break;
				case ARXRLE_PANE_ICONS:
					break;
				case ARXRLE_PANE_TOOLS:
					break;
				case ARXRLE_PANE_COLORS:
					break;
				case ARXRLE_PANE_PROPERTIES:
					break;
				}
			}
		}
	}
}