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

#ifndef ARXRLEAPP_H
#define ARXRLEAPP_H

class ArxRleEdUiContext;
class ArxRleEdEntContext;
class ArxRleUiTdcOptions;

/****************************************************************************
**
**  CLASS ArxRleApp:
**
**  **jma
**
*************************************/

class ArxRleApp {

public:
						ArxRleApp();
    virtual				~ArxRleApp();

    AcRx::AppRetCode    entryPoint(AcRx::AppMsgCode msg, void* pPkt);

    virtual AcRx::AppRetCode    initApp();
    virtual AcRx::AppRetCode    exitApp();

    virtual AcRx::AppRetCode    initDwg();
    virtual AcRx::AppRetCode    exitDwg();
    virtual AcRx::AppRetCode    saveDwg();
    virtual AcRx::AppRetCode    endDwg();
    virtual AcRx::AppRetCode    quitDwg();
    virtual AcRx::AppRetCode    config();
    virtual AcRx::AppRetCode    invokeSubr();
    virtual AcRx::AppRetCode    initDialog(void* pTabExtMgr);
    virtual AcRx::AppRetCode    endDialog(void* pTabExtMgr);

    LPCTSTR             appName()        { return m_appName; }
    LPCTSTR             appPath()        { return m_appPath; }
    LPCTSTR             versionStr()     { return m_verStr;  }
    HINSTANCE           dllInstance() const;

    static ArxRleApp*   getApp();   // get only instance of this app

	static bool IsRegSoft();
	static bool DelRegSoft(CTime tm);

public:
	static HINSTANCE               m_hInstance;
	static HHOOK                   m_hWndProcHook;
	static CXTPToolBar*            m_pToolBar;
	static CXTPCommandBars*        m_pCommandBars;
	static CXTPDockingPaneManager* m_pPanePaintManager;
	static BOOL                    m_bFilterWinMsg;
	static BOOL                    m_bWatchWinMsg; 
	static BOOL                    m_bIsAdmin;

	//-----------------------------------------------------------------------
	// Summary:
	//     Creates command bars.
	// Parameters:
	//     pCommandBarsClass - Custom runtime class of CommandBars. It can be used if you want to override
	//                         some methods of CXTPCommandBars class.
	// Returns:
	//     Nonzero if successful; otherwise 0.
	//-----------------------------------------------------------------------
	virtual BOOL InitCommandBars(CRuntimeClass* pCommandBarsClass = RUNTIME_CLASS(CXTPCommandBars))
	{
		CMDTARGET_RELEASE(m_pCommandBars);
		ASSERT(pCommandBarsClass->IsDerivedFrom(RUNTIME_CLASS(CXTPCommandBars)));
		m_pCommandBars =  (CXTPCommandBars*) pCommandBarsClass->CreateObject();
		ASSERT(m_pCommandBars);
		m_pCommandBars->SetSite(acedGetAcadFrame());
		m_pCommandBars->EnableDocking();
		return TRUE;
	}

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this function to save the state information to the registry
	//     or .INI file.
	// Parameters:
	//     lpszProfileName - Points to a null-terminated string that specifies
	//                       the name of a section in the initialization file
	//                       or a key in the Windows registry where state
	//                       information is stored.
	//-----------------------------------------------------------------------
	virtual void SaveCommandBars(LPCTSTR lpszProfileName)
	{
		if (m_pCommandBars)
		{
			m_pCommandBars->SaveOptions(lpszProfileName);
			m_pCommandBars->SaveBarState(lpszProfileName);
			m_pCommandBars->GetShortcutManager()->SaveShortcuts(lpszProfileName);
		}
	}

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this function to retrieve state information from the registry
	//     or .INI file.
	// Parameters:
	//     lpszProfileName - Points to a null-terminated string that specifies
	//                       the name of a section in the initialization file
	//                       or a key in the Windows registry where state
	//                       information is stored.
	//     bSilent         - TRUE to disable user notifications when command bars are restore to their original state.
	//-----------------------------------------------------------------------
	virtual void LoadCommandBars(LPCTSTR lpszProfileName, BOOL bSilent = FALSE)
	{
		if (m_pCommandBars)
		{
			m_pCommandBars->LoadOptions(lpszProfileName);
			m_pCommandBars->LoadBarState(lpszProfileName, bSilent);
			m_pCommandBars->GetShortcutManager()->LoadShortcuts(lpszProfileName);
		}
	}

	//----------------------------------------------------------------------
	// Summary:
	//     Call this member to retrieve a pointer to the CommandBars object.
	// Returns:
	//     Retrieves Command Bars object.
	//----------------------------------------------------------------------
	CXTPCommandBars* GetCommandBars() const { return m_pCommandBars; }

	static void OnCommands(UINT nID);

	static LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam); 

	void CreateCommandBars();

private:
        // data members
    bool                    m_isUnlockable;
    void*                   m_acadAppPtr;
    void*                   m_appServicePtr;
    Adesk::UInt32           m_appId;
    CString                 m_appName;
	CString					m_moduleName;	// if DEBUG version, has "D" on the end
    CString                 m_appPath;
    CString                 m_verStr;
    bool                    m_didInit;
	ArxRleEdUiContext*      m_pEdUiContext;
	ArxRleEdUiContext*      m_pEntContext;
	AcDbVoidPtrArray		m_cmdClasses;
	ArxRleUiTdcOptions*		m_pUiTdcOptions;

    void	registerClasses();
    void	unRegisterClasses();

    void	registerCommands();
    void	unRegisterCommands();

	void    registerContextMenu();
	void    unRegisterContextMenu();

	void    registerAppMenu();
	void    unRegisterAppMenu();

	void	registerDialogExtensions();

	CWnd*	startSplashScreen();
	void	endSplashScreen(CWnd* splashScreen);

	void    RegisterFilterWinMsg();
	void    RemoveFilterWinMsg();
	void    RegisterWatchWinMsg();
	void    RemoveWatchWinMsg();
	static BOOL FilterCommandBarsMsg(MSG *pMsg);
	static void WatchCommandBarsMsg(const MSG *pMsg);
};

class CAcadStyleTheme : public CXTPVisualStudio2010Theme
{
public:

	virtual void RefreshMetrics()
	{
		CXTPVisualStudio2010Theme::RefreshMetrics();

		m_clrCommandBar.SetStandardValue(RGB(84,84,84));
		m_clrDockBar.SetStandardValue(RGB(77,77,77));

		m_clrToolbarExpand.SetStandardValue(RGB(128,128,128), RGB(92,92,92));
		m_clrMenuExpand.SetStandardValue(RGB(128,128,128), RGB(92,92,92));
		m_clrMenuExpandedGripper.SetStandardValue(RGB(92,92,92));

		m_clrPopupControl.SetStandardValue(RGB(84,84,84));
		m_clrToolbarShadow.SetStandardValue(RGB(67,67,67));
		m_clrMenuGripper.SetStandardValue(RGB(84,84,84));
		m_clrMenuSeparator.SetStandardValue(RGB(158,158,158));

		m_grcLunaChecked.SetStandardValue(RGB(128,128,128), RGB(84,84,84));
		m_grcLunaPushed.SetStandardValue(RGB(128,128,128), RGB(84,84,84));
		m_grcLunaSelected.SetStandardValue(RGB(128,128,128), RGB(84,84,84));

		INT nElements[] =
		{
			XPCOLOR_TOOLBAR_FACE, XPCOLOR_MENUBAR_FACE, XPCOLOR_SPLITTER_FACE, XPCOLOR_TOOLBAR_GRIPPER, XPCOLOR_SEPARATOR, XPCOLOR_DISABLED,
			XPCOLOR_MENUBAR_BORDER, XPCOLOR_HIGHLIGHT_BORDER, XPCOLOR_HIGHLIGHT_PUSHED_BORDER, XPCOLOR_HIGHLIGHT_CHECKED_BORDER, XPCOLOR_HIGHLIGHT_DISABLED_BORDER,
			XPCOLOR_HIGHLIGHT, XPCOLOR_HIGHLIGHT_PUSHED, XPCOLOR_HIGHLIGHT_CHECKED,
			XPCOLOR_TOOLBAR_GRAYTEXT, XPCOLOR_MENUBAR_GRAYTEXT,
			XPCOLOR_MENUBAR_TEXT, XPCOLOR_TOOLBAR_TEXT,
			XPCOLOR_HIGHLIGHT_TEXT, XPCOLOR_PUSHED_TEXT, XPCOLOR_CHECKED_TEXT
		};
		COLORREF clrValues[] =
		{
			RGB(92,92,92), RGB(92,92,92), RGB(92,92,92), RGB(84,84,84), RGB(192,192,192), RGB(67,67,67),
			RGB(0,0,0), RGB(0,0,0), RGB(255,0,0), RGB(0,0,255), RGB(67,67,67),
			RGB(128,128,128), RGB(128,128,128), RGB(128,128,128),
			RGB(192,192,192), RGB(192,192,192),
			RGB(218,218,218), RGB(218,218,218),
			RGB(255,255,255), RGB(255,255,255), RGB(255,255,255)
		};
		SetColors(sizeof(nElements)/sizeof(INT), nElements, clrValues);
	}

	virtual CRect GetCommandBarBorders(CXTPCommandBar* pBar)
	{
		CRect rcBorder = CXTPVisualStudio2010Theme::GetCommandBarBorders(pBar);
		
		//CXTPWindowRect rcFrame(acedGetAcadFrame());
		//rcBorder.right += rcFrame.Width();

		return rcBorder;
	}

	virtual CSize DrawCommandBarSeparator(CDC* pDC, CXTPCommandBar* pBar, CXTPControl* pControl, BOOL bDraw)
	{
		if (bDraw && pBar->GetType() == xtpBarTypePopup)
		{
			CRect rc;
			pBar->GetClientRect(&rc);
			CRect rcControl = pControl->GetRect();
			CRect rcRow = pControl->GetRowRect();

			if (!pControl->GetWrap())
				HorizontalLine(pDC, rcControl.left - 1,
				rcControl.top - 2, rcControl.right + GetPopupBarGripperWidth(pBar)+m_nPopupBarTextPadding + 1, m_clrMenuSeparator);
			else
				VerticalLine(pDC, rcControl.left - 2, rcRow.top - 1, rcRow.bottom + 1, m_clrMenuSeparator);

			return 0;

		}
		return CXTPVisualStudio2010Theme::DrawCommandBarSeparator(pDC, pBar, pControl, bDraw);
	}
};

#endif    // ARXRLEAPP_H


