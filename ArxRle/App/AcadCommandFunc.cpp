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
#include "Resource.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxRleMenuBar.h"
#include "ArxRleToolBarGenWnd.h"
#include "AcadUtils/ArxRleUtils.h"
#include "AcadUtils/ArxRleApply.h"
#include "AcadUtils/ArxRleSmartPtr.h"
#include "AcadUtils/ArxRleSelSet.h"
#include "AcadUtils/ArxRleRbList.h"
#include "Prompt\ArxRleKeywordArray.h"
#include "DbEntity/ArxRleEntityClass.h"
#include "DbEntity/ArxRleString.h"
#include "DockingPane/ArxRleDockingPaneManager.h"
#include "DockingPane/ArxRleExplorerView.h"
#include "DockingPane/ArxRleIconsView.h"
#include "DockingPane/ArxRleToolsView.h"
#include "DockingPane/ArxRleColorsView.h"
#include "DockingPane/ArxRlePropertyView.h"



//利用MFC加载CAD主菜单
void LoadMenuThroughMfc()
{
	acedGetAcadFrame()->EnableDocking(CBRS_ALIGN_ANY);
	acedGetAcadFrame()->RecalcLayout();

	ArxRleMenuBar* pAcedMenuBar = new ArxRleMenuBar(ARXRLE_MENU_MENUBAR);
	pAcedMenuBar->Create(acedGetAcadFrame(), "ArxRle工具菜单");
	pAcedMenuBar->EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	pAcedMenuBar->RestoreControlBar(AFX_IDW_DOCKBAR_TOP);

	acedGetAcadFrame()->ShowControlBar(pAcedMenuBar,TRUE,FALSE);
}
ArxRleExplorerView g_wndExplorerView;
ArxRleIconsView g_wndIconsView;
ArxRleColorsView g_wndColorsView;
ArxRleToolsView g_wndToolsView;
ArxRlePropertyView g_wndPropertyView;

//利用COM接口加载CAD主菜单
void LoadMenuThroughCom()
{
	TRY
	{
		CAcadApplication IAcad(acedGetAcadWinApp()->GetIDispatch(TRUE));
		CAcadMenuGroups IMenuGroups(IAcad.get_MenuGroups());
		CAcadMenuBar IMenuBar(IAcad.get_MenuBar());
		long nMenuCnt;
		nMenuCnt = IMenuBar.get_Count();

		VARIANT index;
		VariantInit(&index);
		V_VT(&index) = VT_I4;
		V_I4(&index) = 0;
		CAcadMenuGroup IMenuGroup(IMenuGroups.Item(index));
		CAcadPopupMenus IPopUpMenus(IMenuGroup.get_Menus());
		ArxRleString cstrMenuName("ArxRle (&A)");

		V_VT(&index) = VT_BSTR;
		V_BSTR(&index) = cstrMenuName.b_str();
		IDispatch* pDisp = NULL;

		//see if the menu is already there
		TRY	pDisp = IPopUpMenus.Item(index); pDisp->AddRef();
		CATCH(COleDispatchException,e) {} END_CATCH;

		if (pDisp == NULL)
		{
			//create it
			CAcadPopupMenu IPopUpMenu(IPopUpMenus.Add(cstrMenuName));

			V_VT(&index) = VT_I4;
			V_I4(&index) = 0;
			CAcadPopupMenu IPopUpSubMenu = IPopUpMenu.AddSubMenu(index, _T("CAD病毒专杀工具")); //添加子菜单

			//子菜单索引
			VARIANT iSubIndex;
			VariantInit(&iSubIndex);
			V_VT(&iSubIndex) = VT_I4;
			V_I4(&iSubIndex) = 0;
			IPopUpSubMenu.AddMenuItem(iSubIndex, _T("工具一 (FAS病毒) (&A)"), _T("ArxRleVirusKiller1 "));

			V_VT(&iSubIndex) = VT_I4;
			V_I4(&iSubIndex) = 1;
			IPopUpSubMenu.AddMenuItem(iSubIndex, _T("工具二 (ASP病毒) (&B)"), _T("ArxRleVirusKiller2 "));

			V_VT(&index) = VT_I4;
			V_I4(&index) = 1;
			IPopUpMenu.AddSeparator(index);

			V_VT(&index) = VT_I4;
			V_I4(&index) = 2;
			IPopUpSubMenu = IPopUpMenu.AddSubMenu(index, _T("导入Excel表格")); //添加子菜单
			CAcadPopupMenuItem IPopUpMenuItem(IPopUpMenu.Item(index));
			//IPopUpMenuItem.put_Check(TRUE);

			//子菜单索引
			V_VT(&iSubIndex) = VT_I4;
			V_I4(&iSubIndex) = 0;
			IPopUpSubMenu.AddMenuItem(iSubIndex, _T("方法一 (CAD表格) (&A)"), _T("ArxRleImportExcel1 "));
			CAcadPopupMenuItem IPopUpSubMenuItem(IPopUpSubMenu.Item(iSubIndex));
			IPopUpSubMenuItem.put_Check(TRUE);

			V_VT(&iSubIndex) = VT_I4;
			V_I4(&iSubIndex) = 1;
			IPopUpSubMenu.AddMenuItem(iSubIndex, _T("方法二 (线条文字) (&B)"), _T("ArxRleImportExcel2 "));

			V_VT(&iSubIndex) = VT_I4;
			V_I4(&iSubIndex) = 2;
			IPopUpSubMenu.AddMenuItem(iSubIndex, _T("数据联动 (&C)"), _T("ArxRleTableDataLink "));

			V_VT(&index) = VT_I4;
			V_I4(&index) = 3;
			IPopUpSubMenu = IPopUpMenu.AddSubMenu(index, _T("导出Excel表格")); //添加子菜单
			IPopUpMenuItem = CAcadPopupMenuItem(IPopUpMenu.Item(index));

			//子菜单索引
			V_VT(&iSubIndex) = VT_I4;
			V_I4(&iSubIndex) = 0;
			IPopUpSubMenu.AddMenuItem(iSubIndex, _T("方法一 (CAD表格) (&A)"), _T("ArxRleExportExcel1 "));
			IPopUpSubMenuItem = CAcadPopupMenuItem(IPopUpSubMenu.Item(iSubIndex));
			IPopUpSubMenuItem.put_Check(TRUE);

			V_VT(&iSubIndex) = VT_I4;
			V_I4(&iSubIndex) = 1;
			IPopUpSubMenu.AddMenuItem(iSubIndex, _T("方法二 (线条文字) (&B)"), _T("ArxRleExportExcel2 "));

			V_VT(&index) = VT_I4;
			V_I4(&index) = 4;
			IPopUpMenu.AddSeparator(index);

			V_VT(&index) = VT_I4;
			V_I4(&index) = 5;
			IPopUpMenu.AddMenuItem(index, _T("实体属性 (&P)"), _T("ArxRleEntProperty "));

			V_VT(&index) = VT_I4;
			V_I4(&index) = 6;
			IPopUpMenu.AddMenuItem(index, _T("调用Lisp (&L)"), _T("ArxRleLoadLisp "));

			V_VT(&index) = VT_I4;
			V_I4(&index) = 7;
			IPopUpMenu.AddSeparator(index);

			V_VT(&index) = VT_I4;
			V_I4(&index) = 8;
			IPopUpMenu.AddMenuItem(index, _T("注册ArxRle (&R)"), _T("ArxRleArxReg "));

			V_VT(&index) = VT_I4;
			V_I4(&index) = 9;
			IPopUpMenu.AddMenuItem(index, _T("关于ArxRle (&A)"), _T("ArxRleAbout "));

			pDisp = IPopUpMenu.m_lpDispatch;
			pDisp->AddRef();
		}

		CAcadPopupMenu IPopUpMenu(pDisp);
		if (!IPopUpMenu.get_OnMenuBar())
		{
			V_VT(&index) = VT_I4;
			V_I4(&index) = nMenuCnt - 2;
			IPopUpMenu.InsertInMenuBar(index);
		}
		else
		{
			V_VT(&index) = VT_BSTR;
			V_BSTR(&index) = cstrMenuName.b_str();
			IPopUpMenus.RemoveMenuFromMenuBar(index);
			VariantClear(&index);
		}
		pDisp->Release();
	}
	CATCH(COleDispatchException,e)
	{
		e->ReportError();
		e->Delete();
	}
	END_CATCH;
}
void LoadToolBarThroughCom()
{
	CAcadApplication IAcad(acedGetAcadWinApp()->GetIDispatch(TRUE));
	CAcadMenuGroups IMenuGroups(IAcad.get_MenuGroups());
	CAcadMenuGroup IMenuGroup;

	CComVariant vt;
	long cnt = IMenuGroups.get_Count();
	for(long i = 0; i < cnt; i++)
	{
		vt = i;
		IMenuGroup = IMenuGroups.Item(vt);
		ArxRleString cgrpName = IMenuGroup.get_Name();
		if(cgrpName.Compare(_T("Acad")) == 0)
			break;
	}

	CAcadToolbars IToolbars(IMenuGroup.get_Toolbars());
	ArxRleString strToolBarName("ArxRle");
	CAcadToolbar IToolbar;
	cnt = IToolbars.get_Count();
	for(long i = 0; i<cnt; i++)
	{
		vt = i;
		IToolbar = IToolbars.Item(vt);
		if(IToolbar.get_Name() == strToolBarName.t_str())
		{
			IToolbar.Delete();
			return;
		}
	}

	USES_CONVERSION;
	char* szAppFileName = T2A(acedGetAppName()); //取出完整的应用程序名称，含路径
	char szDir[_MAX_DIR], szDrive[_MAX_DRIVE], szPath[_MAX_PATH];
	_splitpath(szAppFileName, szDrive, szDir, NULL, NULL);
	_makepath(szPath, szDrive, szDir, NULL, NULL);

	sprintf_s(szPath,"%sArxRle\\Res",szPath);
	if(!DirExist(szPath))
		ModifyDir(szPath);
	sprintf_s(szPath,"%sBar\\",szPath);
	if(!DirExist(szPath))
		ModifyDir(szPath);

	TRY
	{
		sprintf_s(szPath,"%sArxRle\\",szPath);
		if(!DirExist(szPath))
			ModifyDir(szPath);

		IToolbar = IToolbars.Add(strToolBarName);
		IToolbar.put_Visible(true);
		IToolbar.Dock(AutoCAD::acToolbarDockTop);

		COleVariant flyOutButton;
		CAcadToolbarItem IToolbarItem;
		char szIcoFile[MAX_PATH_LENGTH];
		CImageList imageIcons;
		imageIcons.Create(ARXRLE_BMP_HEADER, 16, 1, 0);
		imageIcons.SetBkColor(CLR_NONE);

		vt = 0;
		IToolbarItem = IToolbar.AddToolbarButton(vt, _T("型钢查询"),_T("可以查询各种型钢规格参数！"), _T("ArxRleLoadSteel "), flyOutButton);
		sprintf_s(szIcoFile,"%ssteel.ico",szPath);
		HICON hIcon = imageIcons.ExtractIcon(12);
		if(!FileExist(szIcoFile))
			SaveIcon(hIcon,szIcoFile);
		//char szCmd[MAX_PATH];
		//sprintf_s(szCmd,"Copy %sbar1.ico %sicon1.ico",szRes, szPath);
		//system(szCmd);
		if(FileExist(szIcoFile))
			IToolbarItem.SetBitmaps(A2T(szIcoFile), A2T(szIcoFile));

		vt = 1;
		IToolbarItem = IToolbar.AddToolbarButton(vt, _T("加载文件"),_T("从xls、txt、dat、doc等文件中读取数据！"), _T("ArxRleLoadFile "), flyOutButton);
		sprintf_s(szIcoFile,"%sfile.ico",szPath);
		hIcon = imageIcons.ExtractIcon(13);
		if(!FileExist(szIcoFile))
			SaveIcon(szIcoFile,hIcon);
		if(FileExist(szIcoFile))
			IToolbarItem.SetBitmaps(A2T(szIcoFile), A2T(szIcoFile));

		vt = 2;
		IToolbarItem = IToolbar.AddToolbarButton(vt, _T("施工网络计划"),_T("显示绘制施工网络计划图的工具条！"), _T("ArxRleNetPlanToolBar "), flyOutButton);
		sprintf_s(szIcoFile,"%snetplan.ico",szPath);
		hIcon = imageIcons.ExtractIcon(14);
		if(!FileExist(szIcoFile))
			SaveIcon(szIcoFile,hIcon);
		if(FileExist(szIcoFile))
			IToolbarItem.SetBitmaps(A2T(szIcoFile), A2T(szIcoFile));

		vt = 3;
		IToolbarItem = IToolbar.AddToolbarButton(vt, _T("施工测量"),_T("读取外部测量数据，转换为CAD点、线形式！"), _T("ArxRleLoadMeasure "), flyOutButton);
		sprintf_s(szIcoFile,"%smeasure.ico",szPath);
		hIcon = imageIcons.ExtractIcon(15);
		if(!FileExist(szIcoFile))
			SaveIcon(szIcoFile,hIcon);
		if(FileExist(szIcoFile))
			IToolbarItem.SetBitmaps(A2T(szIcoFile), A2T(szIcoFile));
	}
	CATCH(COleDispatchException,e)
	{
		acutPrintf(_T("\n创建 ArxRle 工具条失败!"));
		acutPrintf(_T("\n请与作者 方波 联系"));
		e->ReportError();
		e->Delete();
	}
	END_CATCH;
}

//加载施工网络计划工具条
static bool g_bNetPlanToolBarShow = true;
void NetPlanToolBar()
{
	CAcadApplication IAcad(acedGetAcadWinApp()->GetIDispatch(TRUE));
	CAcadMenuGroups IMenuGroups(IAcad.get_MenuGroups());
	CAcadMenuGroup IMenuGroup;

	CComVariant vt;
	long cnt = IMenuGroups.get_Count();
	for(long i = 0; i < cnt; i++)
	{
		vt = i;
		IMenuGroup = IMenuGroups.Item(vt);
		ArxRleString cgrpName = IMenuGroup.get_Name();
		if(cgrpName.Compare(_T("Acad")) == 0)
			break;
	}

	CAcadToolbars IToolbars(IMenuGroup.get_Toolbars());
	ArxRleString strToolBarName = _T("ArxRleNetPlan");
	CAcadToolbar IToolbar;
	cnt = IToolbars.get_Count();
	for(long i = 0; i<cnt; i++)
	{
		vt = i;
		IToolbar = IToolbars.Item(vt);
		if(IToolbar.get_Name() == strToolBarName.t_str())
		{
			if(g_bNetPlanToolBarShow)
			{
				IToolbar.put_Visible(false);
				g_bNetPlanToolBarShow = false;
			}
			else
			{
				IToolbar.put_Visible(true);
				g_bNetPlanToolBarShow = true;
			}
			return;
		}
	}

	USES_CONVERSION;
	char* szAppFileName = T2A(acedGetAppName()); //取出完整的应用程序名称，含路径
	char szDir[_MAX_DIR], szDrive[_MAX_DRIVE], szPath[_MAX_PATH];
	_splitpath(szAppFileName, szDrive, szDir, NULL, NULL);
	_makepath(szPath, szDrive, szDir, NULL, NULL);

	TRY
	{
		IToolbar = IToolbars.Add(strToolBarName);
		IToolbar.put_Visible(true);
		IToolbar.Dock(AutoCAD::acToolbarDockTop);

		COleVariant flyOutButton;
		CAcadToolbarItem IToolbarItem;
		char szIcoFile[MAX_PATH_LENGTH];
		sprintf_s(szPath,"%sArxRleRes\\Bar\\NetPlan\\",szPath);

		vt = 0;
		IToolbarItem = IToolbar.AddToolbarButton(vt, _T("基本设置"),_T("设置施工计划网络图各种参数！"), _T("ArxRleNetPlanSetParam "), flyOutButton);
		sprintf_s(szIcoFile,"%sicon17.ico",szPath);
		if(FileExist(szIcoFile))
			IToolbarItem.SetBitmaps(A2T(szIcoFile), A2T(szIcoFile));

		vt = 1;
		IToolbarItem = IToolbar.AddToolbarButton(vt, _T("关键工序"),_T("在CAD中添加一条关键线路！"), _T("ArxRleNetPlanAddKeyWork "), flyOutButton);
		sprintf_s(szIcoFile,"%sicon9.ico",szPath);
		if(FileExist(szIcoFile))
			IToolbarItem.SetBitmaps(A2T(szIcoFile), A2T(szIcoFile));

		vt = 2;
		IToolbarItem = IToolbar.AddToolbarButton(vt, _T("普通工序"),_T("在CAD中添加一条普通工序！"), _T("ArxRleNetPlanAddCommonWork "), flyOutButton);
		sprintf_s(szIcoFile,"%sicon10.ico",szPath);
		if(FileExist(szIcoFile))
			IToolbarItem.SetBitmaps(A2T(szIcoFile), A2T(szIcoFile));

		vt = 3;
		IToolbarItem = IToolbar.AddToolbarButton(vt, _T("虚工序"),_T("在CAD中添加一条虚工序！"), _T("ArxRleNetPlanAddVirtualWork "), flyOutButton);
		sprintf_s(szIcoFile,"%sicon11.ico",szPath);
		if(FileExist(szIcoFile))
			IToolbarItem.SetBitmaps(A2T(szIcoFile), A2T(szIcoFile));

		vt = 4;
		IToolbarItem = IToolbar.AddToolbarButton(vt, _T("自由工序"),_T("在CAD中添加一条自由工序！"), _T("ArxRleNetPlanAddFreeWork "), flyOutButton);
		sprintf_s(szIcoFile,"%sicon12.ico",szPath);
		if(FileExist(szIcoFile))
			IToolbarItem.SetBitmaps(A2T(szIcoFile), A2T(szIcoFile));
	}
	CATCH(COleDispatchException,e)
	{
		acutPrintf(L"\n创建施工网络计划工具条失败!");
		acutPrintf(L"\n请与作者 方波 联系！");
		return;
	}
	END_CATCH;
}
void SaveNetPlanToolBarIco()
{
	USES_CONVERSION;
	char* szAppFileName = T2A(acedGetAppName());
	char szDir[_MAX_DIR], szDrive[_MAX_DRIVE], szPath[_MAX_PATH];
	_splitpath(szAppFileName, szDrive, szDir, NULL, NULL);
	_makepath(szPath, szDrive, szDir, NULL, NULL);

	sprintf_s(szPath,"%sArxRleRes\\",szPath);
	if(!DirExist(szPath))
		ModifyDir(szPath);
	sprintf_s(szPath,"%sBar\\",szPath);
	if(!DirExist(szPath))
		ModifyDir(szPath);
	sprintf_s(szPath,"%sNetPlan\\",szPath);
	if(!DirExist(szPath))
		ModifyDir(szPath);

	char szIcoFile[MAX_PATH_LENGTH];
	CImageList imageIcons;
	imageIcons.Create(ARXRLE_BMP_HEADER, 16, 1, 0);
	imageIcons.SetBkColor(CLR_NONE);

	for(int i=8; i<12; i++)
	{
		sprintf_s(szIcoFile,"%sicon%d.ico",szPath,i+1);
		HICON hIcon = imageIcons.ExtractIcon(i);
		if(!FileExist(szIcoFile))
			SaveIcon(hIcon,szIcoFile);
	}

	sprintf_s(szIcoFile,"%sicon%d.ico",szPath,17);
	HICON hIcon = imageIcons.ExtractIcon(16);
	if(!FileExist(szIcoFile))
		SaveIcon(hIcon,szIcoFile);
}

//ImportExcel 导入Excel表格
void SetTableDataLink(ArxRleString xlsName)
{
	// Select a table
	AcDbTable *pTbl = AcDbTable::cast(ArxRleUtils::selectEntity(ACRX_T("\nSelect a table: "),AcDb::kForWrite));
	if(pTbl == NULL) 
	{
		ArxRleString::Print("\nSelected entity was not a table!");
		return;
	}

	// Get the Data Link Manager.
	Acad::ErrorStatus es;
	AcDbDataLinkManager* pDlMgr = ARXRLEDLM;
	assert(pDlMgr);

	AcDbObjectId idDL;
	AcDbDataLink *pDL = NULL; 
	static ArxRleString sMyDataLink("MyDataLink");
	// Check if a Data Link with the name already exists. If so, remove it.
	if( pDlMgr->getDataLink(sMyDataLink, pDL, AcDb::kForRead) == Acad::eOk && pDL)
	{
		pDL->close();
		es = pDlMgr->removeDataLink(sMyDataLink, idDL);
		if( es != Acad::eOk )
		{
			pTbl->close();
			ArxRleString::Print("\nError in removing the Data Link!");
			return;
		}
	}

	// Create the Data Link with the name.
	es = pDlMgr->createDataLink(ACRX_T("AcExcel"), sMyDataLink, ACRX_T("This is a test for Excel type data link."), xlsName, idDL);
	if( es != Acad::eOk )
	{
		pTbl->close();
		ArxRleString::Print("\nError in creating Data Link!\nPlease check if there is a sheet named 'Sheet1' in the XLS file.");
		return;
	}

	// Open the Data Link.
	es = acdbOpenObject<AcDbDataLink>(pDL, idDL, AcDb::kForWrite);
	if ( es != Acad::eOk || !pDL )
	{
		pTbl->close();
		ArxRleString::Print("\nError in opening the Data Link object!"); 
		return;
	}

	//  Set options of the Data Link
	pDL->setOption(AcDb::kDataLinkOptionPersistCache);
	pDL->setUpdateOption(pDL->updateOption() | AcDb::kUpdateOptionAllowSourceUpdate);
	// Close the Data Link.
	pDL->close();

	// Set data link to the table object at cell(1,1).
	//es = pTbl->setDataLink(0, 0, idDL, true);
	AcCellRange range = {0,0,pTbl->numRows()-1,pTbl->numColumns()-1};
	es = pTbl->setDataLink(range, idDL, true);
	if( es != Acad::eOk )
	{
		pTbl->close();
		ArxRleString::Print("\nError in setting Data Link to the selected table!\nPlease check if there is a sheet named 'Sheet1' in the XLS file.");
		return;
	}

	// Don't forget to close the table object.
	pTbl->close();
}
void TableDataLink()
{
	// Get an Excel file
	struct resbuf *result; 
	if ((result = acutNewRb(RTSTR)) == NULL)
	{
		ArxRleString::Print("\nUnable to allocate buffer!"); 
		return;
	}
	result->resval.rstring = NULL; 
	int rc = acedGetFileD(ACRX_T("Excel File"), // Title
		ACRX_T("C:\\"),                         // Default pathname  
		ACRX_T("xls"),                          // Default extension
		16,                                     // Control flags
		result);                                // The path selected by the user.
	if (rc != RTNORM) 
	{
		ArxRleString::Print("\nError in selecting an Excel file!"); 
		return;
	}

	// Retrieve the file name from the ResBuf.
	ArxRleString fileName;
	fileName = result->resval.rstring;
	rc = acutRelRb(result);
	SetTableDataLink(fileName);
}
void ImportExcel1()
{
	ads_point pt_insert;
	if(acedGetPoint(NULL,_T("\n请输入表格左上角位置... "),pt_insert)!=RTNORM)
		return;

	//常用变量定义
	XTPREPORTEXCEL::_Application app;    
	XTPREPORTEXCEL::Workbooks    books;
	XTPREPORTEXCEL::_Workbook    book;
	XTPREPORTEXCEL::Worksheets   sheets;
	XTPREPORTEXCEL::_Worksheet   sheet;
	XTPREPORTEXCEL::_Range       select;
	XTPREPORTEXCEL::_Range       range;
	XTPREPORTEXCEL::_Range       cell;
	LPDISPATCH   lpDisp;     
	COleVariant  vTrue((short)TRUE),
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);      
	COleVariant  vResult;
	//采用MFC方式初始化COM库，程序结束时COM库会自动释放
	if(!AfxOleInit())
	{ 
		msgErr(L"初始化COM支持库失败!\n无法控制Excel!");  
		return;
	} 

	//关联已经运行的Excel实例
	CLSID clsid;
	CLSIDFromProgID(L"Excel.Application", &clsid);  
	IUnknown  *pUnk = NULL;
	IDispatch *pRunDisp = NULL;

	for(long i=1;i<=5;i++) //做5次尝试
	{
		HRESULT hr = GetActiveObject(clsid, NULL, (IUnknown**)&pUnk);
		if(SUCCEEDED(hr)) 
		{
			hr = pUnk->QueryInterface(IID_IDispatch, (void **)&pRunDisp);
			break;
		}
		::Sleep(10);
	}

	if (!pRunDisp) 
	{
		msgErr(L"没有发现Excel!");
		return;
	}
	if (pUnk)  pUnk->Release();

	//关联Excel
	app.AttachDispatch (pRunDisp);
	//得到当前活跃sheet
	//如果有单元格正处于编辑状态中，此操作不能返回，会一直等待
	lpDisp=app.GetActiveSheet();
	if(lpDisp==NULL)
	{
		msgErr(L"没有发现有效的表格!"); 
		app.ReleaseDispatch (); 
		return;
	}
	sheet.AttachDispatch(lpDisp);

	//已经选择的行数:
	select.AttachDispatch(app.GetSelection());
	//select.AttachDispatch(sheet.GetUsedRange());
	range.AttachDispatch(select.GetRows());
	long row_nums = range.GetCount();

	//已经选择的列数:
	range.AttachDispatch(select.GetColumns());
	long col_nums = range.GetCount();

	//已经选择的起始行列数:
	long row_start=select.GetRow();       //起始行
	long col_start=select.GetColumn();    //起始列
	//读取sheet名
	ArxRleString SheetName=sheet.GetName();
	if(col_nums<2 && row_nums<2)     //此sheet为空
	{
		msgErr(L"\n当前表格没有数据!"); 
		app.ReleaseDispatch (); 
		return;
	}
	else ads_printf(L"\n表格%s共%d行,%d列",SheetName,row_nums,col_nums);

	AcDbTable* pTable = new AcDbTable;
	pTable->generateLayout(); 

	AcDbDictionary *pDict = new AcDbDictionary;
	AcDbObjectId tblsId;
	ARXRLEDB->getTableStyleDictionary(pDict,AcDb::kForWrite);
	pDict->getAt(_T("Standard"),tblsId);

	AcDbObjectId tsId = AddTextStyle("arx_text");

	if(tblsId.isValid())
	{
		AcDbObject* obj;
		acdbOpenAcDbObject(obj, tblsId, AcDb::kForWrite);
		AcDbTableStyle* tbls = AcDbTableStyle::cast(obj);
 		tbls->suppressTitleRow(true);//禁用标题
 		tbls->suppressHeaderRow(true);//禁用表头
		tbls->setTextStyle(tsId);
		tbls->close();

		pTable->setTableStyle(tblsId);
	}
	pDict->close();

	pTable->setNumRows(row_nums);
	pTable->setNumColumns(col_nums);

	//定义插入点
	pTable->setPosition(AcGePoint3d(pt_insert[X],pt_insert[Y], 0));

	//得到全部Cells，此时,range是cells的集合 
	range.AttachDispatch(sheet.GetCells()); 
	for(int i=0; i<row_nums; i++)
	{
		// 每列写文本
		for(int j=0; j<col_nums; j++)
		{
			cell.AttachDispatch(range.GetItem(COleVariant(row_start+i), COleVariant(col_start+j)).pdispVal);
			XTPREPORTEXCEL::_Font font = cell.GetFont();
			COleVariant fontSize = font.GetSize();
			COleVariant vStyle = cell.GetStyle();
			COleVariant vHeight = cell.GetRowHeight();
			COleVariant vWidth = cell.GetColumnWidth();
			COleVariant merge = cell.GetMergeCells();
			COleVariant val = cell.GetText();
			COleVariant align; align.lVal=0;
			ArxRleString str = val.bstrVal;

			pTable->setRowHeight(i,vHeight.dblVal/2.86);
			pTable->setColumnWidth(j,vWidth.dblVal*2.54);
			if(merge.vt==VT_BOOL && merge.boolVal && val.vt==VT_BSTR)
				if(str.GetLength()<1) continue;

			AcDb::CellAlignment arxAlign;
			//单元格水平对齐方式
			align = cell.GetHorizontalAlignment();
			if(align.lVal != 0)
			{
				switch (align.lVal)
				{
				case 1: //默认
					arxAlign = AcDb::kMiddleCenter;
					break;
				case -4108: //居中
					arxAlign = AcDb::kMiddleCenter;
					break;
				case -4131 : //靠左
					arxAlign = AcDb::kMiddleLeft;
					break;
				case -4152 : //靠右
					arxAlign = AcDb::kMiddleRight;
					break;
				}
			}

			if(merge.vt==VT_BOOL && merge.boolVal)
			{
				XTPREPORTEXCEL::_Range range_merge;
				range_merge.AttachDispatch(cell.GetMergeArea());  //先要获取合并区域

				//合并单元格的行数
				XTPREPORTEXCEL::_Range cell_merge;
				cell_merge.AttachDispatch(range_merge.GetRows());   
				long row_nums_merge = cell_merge.GetCount();

				//合并单元格的列数
				cell_merge.AttachDispatch(range_merge.GetColumns());   
				long col_nums_merge = cell_merge.GetCount();         

				//合并区域的起始行，列   
				long row_start_merge = range_merge.GetRow()-row_start;            //起始行，从1开始   
				long col_start_merge = range_merge.GetColumn()-col_start;         //起始列，从1开始   

				pTable->mergeCells(row_start_merge,row_start_merge+row_nums_merge-1,col_start_merge,col_start_merge+col_nums_merge-1);
			}

			pTable->setTextHeight(i,j,fontSize.dblVal/4);
			pTable->setTextString(i,j,str);
 			pTable->setAutoScale(i,j,true);
			pTable->setAlignment(i,j,arxAlign);
			AcCmColor clr;
			clr.setColorIndex(3);
			pTable->setContentColor(i,j,clr);
		}
	}

	//释放Dispatch 
	cell.ReleaseDispatch ();
	range.ReleaseDispatch ();
	select.ReleaseDispatch ();
	sheet.ReleaseDispatch ();
	sheets.ReleaseDispatch ();
	book.ReleaseDispatch ();
	books.ReleaseDispatch ();
	app.ReleaseDispatch (); 

	AddLayer("arx_line",4);
	SetCurLayer("arx_line");
	for(int i=0; i<col_nums; i++) pTable->setGridVisibility(0,i,AcDb::kHorzTop,AcDb::kInvisible);
	for(int i=0; i<col_nums; i++) pTable->setGridVisibility(0,i,AcDb::kVertLeft,AcDb::kInvisible);
	for(int i=0; i<col_nums; i++) pTable->setGridVisibility(0,i,AcDb::kVertRight,AcDb::kInvisible);
	for(int i=0; i<col_nums; i++) pTable->setGridLineWeight(0,i,AcDb::kHorzBottom,AcDb::kLnWt030);
	for(int i=0; i<col_nums; i++) pTable->setGridLineWeight(row_nums-1,i,AcDb::kHorzBottom,AcDb::kLnWt030);
	for(int i=0; i<row_nums; i++) pTable->setGridLineWeight(i,0,AcDb::kVertLeft,AcDb::kLnWt030);
	for(int i=0; i<row_nums; i++) pTable->setGridLineWeight(i,col_nums-1,AcDb::kVertRight,AcDb::kLnWt030);
	pTable->setRegen();
	AddEntity(pTable);
	ArxRleSave();

	//刷新屏幕
 	actrTransactionManager->flushGraphics(); /*refresh screen*/
 	acedUpdateDisplay(); 
}
void ImportExcel2()
{
	ads_point pt_insert;
	if(acedGetPoint(NULL,_T("\n请输入表格左上角位置... "),pt_insert)!=RTNORM)
		return;

	//常用变量定义
	XTPREPORTEXCEL::_Application app;    
	XTPREPORTEXCEL::Workbooks    books;
	XTPREPORTEXCEL::_Workbook    book;
	XTPREPORTEXCEL::Worksheets   sheets;
	XTPREPORTEXCEL::_Worksheet   sheet;
	XTPREPORTEXCEL::_Range       select;
	XTPREPORTEXCEL::_Range       range;
	XTPREPORTEXCEL::_Range       cell;
	LPDISPATCH   lpDisp;     
	COleVariant  vTrue((short)TRUE),
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);      
	COleVariant  vResult;
	//采用MFC方式初始化COM库，程序结束时COM库会自动释放
	if(!AfxOleInit())
	{ 
		msgErr(L"初始化COM支持库失败!\n无法控制Excel!");  
		return;
	} 

	//关联已经运行的Excel实例
	CLSID clsid;
	CLSIDFromProgID(L"Excel.Application", &clsid);  
	IUnknown  *pUnk = NULL;
	IDispatch *pRunDisp = NULL;

	for(long i=1;i<=5;i++) //做5次尝试
	{
		HRESULT hr = GetActiveObject(clsid, NULL, (IUnknown**)&pUnk);
		if(SUCCEEDED(hr)) 
		{
			hr = pUnk->QueryInterface(IID_IDispatch, (void **)&pRunDisp);
			break;
		}
		::Sleep(10);
	}

	if (!pRunDisp) 
	{
		msgErr(L"没有发现Excel!");
		return;
	}
	if (pUnk)  pUnk->Release();

	//关联Excel
	app.AttachDispatch (pRunDisp);
	//得到当前活跃sheet
	//如果有单元格正处于编辑状态中，此操作不能返回，会一直等待
	lpDisp=app.GetActiveSheet();
	if(lpDisp==NULL)
	{
		msgErr(L"没有发现有效的表格!"); 
		app.ReleaseDispatch (); 
		return;
	}
	sheet.AttachDispatch(lpDisp);

	//已经选择的行数:
	select.AttachDispatch(app.GetSelection());
	//select.AttachDispatch(sheet.GetUsedRange());
	range.AttachDispatch(select.GetRows());
	long row_nums = range.GetCount();

	//已经选择的列数:
	range.AttachDispatch(select.GetColumns());
	long col_nums = range.GetCount();

	//已经使用区域的起始行、列：
	long row_start=select.GetRow();       //起始行
	long col_start=select.GetColumn();    //起始列
	//读取sheet名
	ArxRleString SheetName=sheet.GetName();
	if(col_nums<2 && row_nums<2)     //此sheet为空
	{
		msgErr(L"\n当前表格没有数据!"); 
		app.ReleaseDispatch (); 
		return;
	}
	else
	{
		ads_printf(L"\n表格%s共%d行,%d列",SheetName,row_nums,col_nums);
	}

	//得到全部Cells，此时,range是cells的集合 
	range.AttachDispatch(sheet.GetCells()); 

	AddTextStyle("arx_text");
	AcDbObjectId tsId = SetCurTextStyle("arx_text");
	AcDbTextStyleTableRecord* ts =  (AcDbTextStyleTableRecord*)GetRecordPtr(tsId);

	//获取列宽了
	//Excel列宽使用单位为1/10英寸（既1个单位为2.54mm) 
	CArray<double,double> col_widths;
	double width = 0, height = 0;
	for(long i=col_start;i<col_start+col_nums;i++)
	{
		//读取单元格文本
		cell.AttachDispatch(range.GetItem (COleVariant(row_start),COleVariant(i)).pdispVal);
		vResult = cell.GetColumnWidth();
		col_widths.Add(vResult.dblVal*2.54*ts->xScale());
		width += vResult.dblVal*2.54*ts->xScale();
	}

	//获取行高了
	//Excel行高所使用单位为磅（1cm=28.6磅，既1个单位为1/2.86mm）
	CArray<double,double> row_heights;
	for(long i=row_start;i<row_start+row_nums;i++)
	{
		//读取单元格文本
		cell.AttachDispatch(range.GetItem (COleVariant(i),COleVariant(col_start)).pdispVal );
		vResult = cell.GetRowHeight();
		row_heights.Add(vResult.dblVal/2.86);
		height += vResult.dblVal/2.86;
	}

	AddLayer("arx_line",4);
	SetCurLayer("arx_line");
	AcDbPolyline* plineTK = new AcDbPolyline;
	unsigned int nIndex = plineTK->numVerts();
	plineTK->addVertexAt(nIndex, CPt3d(pt_insert));
	plineTK->setWidthsAt(nIndex,0.5,0.5);
	nIndex = plineTK->numVerts();
	plineTK->addVertexAt(nIndex, CPt3d(pt_insert[X]+width,pt_insert[Y],pt_insert[Z]));
	plineTK->setWidthsAt(nIndex,0.5,0.5);

	CLine line;
	double fRow = 0;
	for(int i = 0;i<row_nums-1;i++)
	{
		fRow += row_heights[i];
		line.SetPoint(CPt3d(pt_insert[X],pt_insert[Y]-fRow,pt_insert[Z]),CPt3d(pt_insert[X]+width,pt_insert[Y]-fRow,pt_insert[Z]));
		AddEntity(&line); //画中间横线
	}
	nIndex = plineTK->numVerts();
	fRow += row_heights[row_nums-1];
	plineTK->addVertexAt(nIndex, CPt3d(pt_insert[X]+width,pt_insert[Y]-fRow,pt_insert[Z]));
	plineTK->setWidthsAt(nIndex,0.5,0.5);

	double fCol = 0;
	for(int i=0;i<col_nums-1;i++)
	{
		fCol += col_widths[i];
		line.SetPoint(CPt3d(pt_insert[X]+fCol,pt_insert[Y],pt_insert[Z]),CPt3d(pt_insert[X]+fCol,pt_insert[Y]-height,pt_insert[Z]));
		AddEntity(&line); //画中间横线
	}
	nIndex = plineTK->numVerts();
	plineTK->addVertexAt(nIndex, CPt3d(pt_insert[X],pt_insert[Y]-height,pt_insert[Z]));
	plineTK->setWidthsAt(nIndex,0.5,0.5);
	nIndex = plineTK->numVerts();
	plineTK->addVertexAt(nIndex, CPt3d(pt_insert));
	plineTK->setWidthsAt(nIndex,0.5,0.5);
	AddEntity(plineTK);

	//写文本
	AddLayer("arx_text",3);
	SetCurLayer("arx_text");
	AcDbObjectIdArray objList;
	for(int i=0;i<row_nums;i++)
	{
		// 每列写文本
		for(int j=0;j<col_nums;j++)
		{
			cell.AttachDispatch(range.GetItem(COleVariant(row_start+i), COleVariant(col_start+j)).pdispVal);
			XTPREPORTEXCEL::_Font font = cell.GetFont();
			COleVariant fontSize = font.GetSize();
			COleVariant merge = cell.GetMergeCells();
			COleVariant val = cell.GetText();
			COleVariant align; align.lVal=0;
			ArxRleString str = val.bstrVal;
			if(merge.vt==VT_BOOL && merge.boolVal && val.vt==VT_BSTR)
				if(str.GetLength()<1) continue;

			ArxAlignment arxAlign;
			//单元格水平对齐方式
			align = cell.GetHorizontalAlignment();
			if(align.lVal != 0)
			{
				switch (align.lVal)
				{
				case 1: //默认
					arxAlign = ArxCenter;
					break;
				case -4108: //居中
					arxAlign = ArxCenter;
					break;
				case -4131 : //靠左
					arxAlign = ArxLeftMiddle;
					break;
				case -4152 : //靠右
					arxAlign = ArxRightMiddle;
					break;
				}
			}

			//单元格垂直对齐方式
			align = cell.GetVerticalAlignment();
			if(align.lVal != 0)
			{
				switch (align.lVal)
				{
				case -4160 : //靠上
					break;
				case -4108 : //居中
					break;
				case -4107 : //靠下
					break;
				}
			}

			double width_merge = 0, height_merge = 0;
			for(int k=0;k<j;k++) width_merge += col_widths.GetAt(k);
			for(int k=0;k<i;k++) height_merge += row_heights.GetAt(k);

			if(merge.vt==VT_BOOL && merge.boolVal)
			{
				XTPREPORTEXCEL::_Range range_merge;
				range_merge.AttachDispatch(cell.GetMergeArea());  //先要获取合并区域

				//合并单元格的行数
				XTPREPORTEXCEL::_Range cell_merge;
				cell_merge.AttachDispatch(range_merge.GetRows());   
				long row_nums_merge = cell_merge.GetCount();     

				//合并单元格的列数   
				cell_merge.AttachDispatch(range_merge.GetColumns());   
				long col_nums_merge = cell_merge.GetCount();         

				//合并区域的起始行，列   
				long row_start_merge = range_merge.GetRow();               //起始行，从1开始   
				long col_start_merge = range_merge.GetColumn();         //起始列，从1开始   

				CPt3d mergeCell[4];
				mergeCell[0].x = pt_insert[X]+width_merge;
				mergeCell[1].y = mergeCell[0].y = pt_insert[Y]-height_merge;
				mergeCell[1].x = mergeCell[0].x;
				for(long k=0;k<col_nums_merge;k++)
				{
					long l=j+k;
					mergeCell[1].x += col_widths.GetAt(l);
				}
				mergeCell[3].x = mergeCell[0].x;
				mergeCell[3].y = mergeCell[0].y;
				mergeCell[2].x = mergeCell[1].x;
				mergeCell[2].y = mergeCell[1].y;

				height_merge = 0;
				for(long k=0;k<row_nums_merge;k++) height_merge += row_heights.GetAt(i+k);
				mergeCell[3].y -= height_merge;
				mergeCell[2].y -= height_merge;

				CPt3d pt;
				pt.x = (mergeCell[0].x+mergeCell[1].x)/2;
				pt.y = (mergeCell[1].y+mergeCell[2].y)/2;
				pt.z = (mergeCell[1].z+mergeCell[2].z)/2;
				if(arxAlign ==  ArxLeftMiddle)
					pt.x = mergeCell[0].x+0.5;
				else if(arxAlign == ArxRightMiddle)
					pt.x = mergeCell[0].x+mergeCell[1].x-0.5;

				CMText text;
				text.SetText(str);
				text.SetTextStyle(ts->objectId());
				text.SetWidth(mergeCell[1].x-mergeCell[0].x-0.5);
				text.SetHeight(mergeCell[1].y-mergeCell[3].y-0.5);
				text.SetTextHeight(fontSize.dblVal/4);
				text.SetPosition(pt);
				text.SetAlignmentMode(arxAlign);
				text.SetBackgroundFill(TRUE, 1, TRUE, RGB(255,255,255));
				AddEntity(&text);

				// 				AcDbPolyline* pPolyline = new AcDbPolyline;
				// 				AcGePoint2d temp;
				// 				for(int k=0;k<=4;k++)
				// 				{
				// 					if(k<4)
				// 					{
				// 						temp.x = mergeCell[k].x;
				// 						temp.y = mergeCell[k].y;
				// 					}
				// 					else
				// 					{
				// 						temp.x = mergeCell[0].x;
				// 						temp.y = mergeCell[0].y;
				// 					}
				// 					unsigned int nIndex = pPolyline->numVerts();
				// 					pPolyline->addVertexAt(nIndex, temp);
				// 				}
				// 				AddEntity(pPolyline);
				// 				objList.append(pPolyline->objectId());
			}
			else
			{
				CPt3d pt;
				pt.x = pt_insert[X]+width_merge+col_widths.GetAt(j)/2;
				pt.y = pt_insert[Y]-height_merge-row_heights.GetAt(i)/2;
				if(arxAlign == ArxLeftMiddle)
					pt.x = pt_insert[X]+width_merge+0.5;
				else if(arxAlign == ArxRightMiddle)
					pt.x = pt_insert[X]+width_merge+col_widths.GetAt(j)-0.5;

				if(str.Find("\n") < 0)
				{
					CText text;
					text.SetText(str);
					text.SetTextStyle(ts->objectId());
					text.SetTextHeight(fontSize.dblVal/4);
					text.SetPosition(pt);
					text.SetAlignmentMode(arxAlign);
					text.SetPosition(pt);
					text.SetWidthFactor(ts->xScale());
					AddEntity(&text);
				}
				else
				{
					CMText text;
					text.SetText(str);
					text.SetTextStyle(ts->objectId());
					text.SetWidth(col_widths.GetAt(j)-0.5);
					text.SetHeight(row_heights.GetAt(i)-0.5);
					text.SetTextHeight(fontSize.dblVal/4);
					text.SetPosition(pt);
					text.SetAlignmentMode(arxAlign);
					AddEntity(&text);
				}
			}
		}
	}

	ts->close();

	//释放Dispatch 
	cell.ReleaseDispatch ();
	range.ReleaseDispatch ();
	select.ReleaseDispatch ();
	sheet.ReleaseDispatch ();
	sheets.ReleaseDispatch ();
	book.ReleaseDispatch ();
	books.ReleaseDispatch ();
	app.ReleaseDispatch (); 
	ArxRleSave();
}

//ExportExcel 导出Excel表格
void ResetVector(vector<double>& vecDbl)
{
	sort(vecDbl.begin(),vecDbl.end());
	vector<double> vecTemp;
	int nSize = vecDbl.size();
	if (nSize < 1) return;

	for (int i=0; i<nSize-1; i++)
	{
		if(abs(vecDbl[i+1] - vecDbl[i]) > 0.0001)
		{
			vecTemp.push_back(vecDbl[i]);
		}
	}

	if(abs(vecDbl[nSize-1] - vecTemp[vecTemp.size()-1]) > 0.0001)
	{
		vecTemp.push_back(vecDbl[nSize-1]);
	}

	vecDbl.clear();
	vecDbl = vecTemp;
}
int BinaryQuery(vector<double> vecDbl, double dbl)
{
	int nIndex = -1;
	int nSize = vecDbl.size();
	if (nSize < 1) return nIndex;

	double fPrecision = 0.0001;
	int nLeftIndex = 0;
	int nRightIndex = nSize-1;
	int nHalfIndex = (nLeftIndex+nRightIndex)/2;

	for (int i=0; i<nSize; i++)
	{
		if(abs(dbl - vecDbl[nHalfIndex]) < fPrecision)
		{
			nIndex = nHalfIndex;
			break;
		}

		if(dbl < vecDbl[nHalfIndex+1] && dbl > vecDbl[nHalfIndex])
		{
			nIndex = nHalfIndex;
			break;
		}

		if(dbl < vecDbl[nHalfIndex])
		{
			nRightIndex = nHalfIndex;
			nHalfIndex = (nLeftIndex+nRightIndex)/2;
		}

		if(dbl > vecDbl[nHalfIndex])
		{
			nLeftIndex = nHalfIndex;
			nHalfIndex = (nLeftIndex+nRightIndex)/2;
		}
	}

	return nIndex;
}
void BinarySort(vector<double> vecDbl, bool asc = true)
{
	int nSize = vecDbl.size();
	if (nSize < 1) return;

	int nIndex = (nSize+1)/2;
	for (int i=0; i<nSize; i++)
	{
		for (int j=nIndex; j<nSize; j++)
		{
			bool bExchanged = false;
			if(asc) // 升序排列
			{
				for (int k=0; i<nSize-nIndex; k++)
				{
					if (vecDbl[k] > vecDbl[k+nIndex])
					{
						int fTemp = vecDbl[k];
						vecDbl[k] = vecDbl[k+nIndex];
						vecDbl[k+nIndex] = fTemp;
						bExchanged = true;
					}
				}
			}
			else //降序排列
			{
				for (int k=0; i<nSize-nIndex; k++)
				{
					if (vecDbl[k] < vecDbl[k+nIndex])
					{
						int fTemp = vecDbl[k];
						vecDbl[k] = vecDbl[k+nIndex];
						vecDbl[k+nIndex] = fTemp;
						bExchanged = true;
					}
				}
			}

			if (bExchanged) continue;
		}
		nIndex = nIndex / 2;
		if (nIndex == 0) break;
	}
}
void ExportExcel1()
{
	ArxRleSelSet ss;
	if(ss.userSelect() == ArxRleSelSet::kSelected)
	{    // have user select entities from DWG
		AcDbObjectIdArray objList;
		ss.asArray(objList);
		if(!objList.isEmpty())
		{
			TCHAR szFilter[] = _T("Excel 2003|*.xls|Excel 2007|*.xlsx|所有文件|*.*||");
			CFileDialog FileDlg(FALSE, _T("xls"), NULL, 0, szFilter);
			if(IDOK == FileDlg.DoModal())
			{
				CXTPExcelUtil excel;
				excel.InitExcel();

				CString strFileName = FileDlg.GetFileName();
				CString strFilePath = FileDlg.GetPathName();

				excel.CreateExcel(strFilePath);
				excel.OpenExcel(strFilePath);

				AcDbEntity* ent;
				Acad::ErrorStatus es;

				int len = objList.length();
				for(int i=0; i<len; i++)
				{
					es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForRead, true);		// might have passed in erased ones
					if(es == Acad::eOk)
					{
						if(ent->isKindOf(AcDbTable::desc()))
						{
							if(excel.LoadSheet(i+1))
							{
								int rows = ((AcDbTable*)ent)->numRows();
								int cols = ((AcDbTable*)ent)->numColumns();
								for(int j=0; j<rows; j++)
								{
									for(int k=0; k<cols; k++)
									{
										excel.SetCell(((AcDbTable*)ent)->textString(j,k),j+1,k+1);
									}
								}
							}
						}

						ent->close();
					}
				}

				excel.Save();
				excel.CloseExcel();
				excel.ReleaseExcel();

				msgInf(strFileName + " 文件导出成功!");
			}
		}
	}
}
void ExportExcel2()
{
	vector<double> vecX,vecY;
	AcDbObjectIdArray objListText;
	ArxRleSelSet ss;
	if(ss.userSelect() == ArxRleSelSet::kSelected)
	{    // have user select entities from DWG
		AcDbObjectIdArray objList;
		ss.asArray(objList);
		if(!objList.isEmpty())
		{
			AcDbEntity* ent;
			Acad::ErrorStatus es;

			int len = objList.length();
			for(int i=0; i<len; i++)
			{
				es = acdbOpenAcDbEntity(ent, objList[i], AcDb::kForRead, true);		// might have passed in erased ones
				if(es == Acad::eOk)
				{
					if(ent->isKindOf(AcDbLine::desc()))
					{
						vecX.push_back(((AcDbLine*)ent)->startPoint().x);
						vecX.push_back(((AcDbLine*)ent)->endPoint().x);
						vecY.push_back(((AcDbLine*)ent)->startPoint().y);
						vecY.push_back(((AcDbLine*)ent)->endPoint().y);
					}

					if(ent->isKindOf(AcDbPolyline::desc()))
					{
						AcGePoint3d pt;
						((AcDbPolyline*)ent)->getPointAt(0, pt);
						vecX.push_back(pt.x);
						vecY.push_back(pt.y);
						((AcDbPolyline*)ent)->getPointAt(((AcDbPolyline*)ent)->numVerts()-1, pt);
						vecX.push_back(pt.x);
						vecY.push_back(pt.y);
					}

					if(ent->isKindOf(AcDbText::desc()) || ent->isKindOf(AcDbMText::desc()))
						objListText.append(ent->objectId());

					ent->close();
				}
			}
		}
	}

	int row = 0, col = 0;
	TCHAR szFilter[] = _T("Excel 2003|*.xls|Excel 2007|*.xlsx|所有文件|*.*||");
	CFileDialog FileDlg(FALSE, _T("xls"), NULL, 0, szFilter);
	if(IDOK == FileDlg.DoModal())
	{
		CXTPExcelUtil excel;
		excel.InitExcel();

		CString strFileName = FileDlg.GetFileName();
		CString strFilePath = FileDlg.GetPathName();

		excel.CreateExcel(strFilePath);
		excel.OpenExcel(strFilePath);
		excel.LoadSheet(1);

		if(!objListText.isEmpty())
		{
			AcDbEntity* ent;
			Acad::ErrorStatus es;

			int len = objListText.length();
			for(int i=0; i<len; i++)
			{
				es = acdbOpenAcDbEntity(ent, objListText[i], AcDb::kForRead, true);		// might have passed in erased ones
				if(es == Acad::eOk)
				{
					CString str;
					CPt3d pt;
					if(ent->isKindOf(AcDbText::desc()))
					{
						str = ((AcDbText*)ent)->textString();
						pt = ((AcDbText*)ent)->position();
					}

					if(ent->isKindOf(AcDbMText::desc()))
					{
						str = ((AcDbMText*)ent)->text();
						pt = ((AcDbMText*)ent)->location();
					}

					ResetVector(vecX);
					ResetVector(vecY);
					int col = BinaryQuery(vecX,pt.x)+1;
					int row = BinaryQuery(vecY,pt.y)+1;
					for(int j=0; j<vecX.size()-1;j++)
					{
						if(pt.x > vecX[j] && pt.x < vecX[j+1])
						{
							col = j+1;
							break;
						}
					}

					int sizeY = vecY.size()-1;
					for(int j=0; j<sizeY;j++)
					{
						if(pt.y > vecY[j] && pt.y < vecY[j+1])
						{
							row = sizeY-j;
							break;
						}
					}
					excel.SetCell(str,row,col);

					ent->close();
				}
			}
		}

		excel.Save();
		excel.CloseExcel();
		excel.ReleaseExcel();

		msgInf(strFileName + " 文件导出成功!");
	}
}

//调用LISP程序
void LoadLisp()
{
	ArxRleUiPrString prLisp(_T("LispName"), true);
	if((prLisp.go() != ArxRleUiPrBase::kOk))
		return;

	struct resbuf *ptList,*ptResult=NULL;
	//注意，一定要写成_T("c:lisp_test"),写成"c:lisp_test"调用会失败
	//double dx=135.6;
	//double dy=147.5;
	//ptList=acutBuildList(RTSTR,_T("c:lisp_test"),RTREAL,dx,RTREAL,dy,RTNONE);

	CString lsp;
	lsp.Format(_T("c:%s"),prLisp.value());
	ptList=acutBuildList(RTSTR,lsp,RTNONE);

	int rc=acedInvoke(ptList,&ptResult);
	if(rc!=RTNORM)
	{
		acutPrintf(_T("\r\n调用LISP失败,请检查依赖的LISP是否加载"));
		acutRelRb(ptList);
		return;
	}
	acutRelRb(ptList);
	if(ptResult == NULL)
	{
		acutPrintf(_T("\r\n调用LISP失败,返回空值"));
		return;
	}
	if(ptResult->restype != RTSTR)
	{
		acutPrintf(_T("\r\n调用LISP失败,返回错误的值类型"));
		acutRelRb(ptResult);
		return;
	}
	CString strRC=ptResult->resval.rstring;
	acutRelRb(ptResult);
	acutPrintf(_T("\r\n返回值:%s"),strRC);
}

// Functions which will be called in the test command
Adesk::Boolean testFunc1( AcDbBlockTableRecord *pBtr )
{
	msgInf( L"BTR func called!\n");

	// return kTrue if you want to continue the iteration
	//
	return Adesk::kTrue;
}
Adesk::Boolean testFunc2( AcDbObject *pObj )
{
	msgInf( L"Dictionary func called!\n" );
	return Adesk::kTrue;
}
template<class T>
Adesk::Boolean testFunc3( T* pObj )
{
	acutPrintf( L"Generic function called: %s\n", pObj->isA()->name() );
	return Adesk::kTrue;
}
Adesk::Boolean testFunc4( AcDbTextStyleTableRecord *pTtr )
{
	if(pTtr != NULL)
	{
		try
		{
			AcString AcName;
			pTtr->getName(AcName);
			msgErr(AcName);
		}
		catch(...)
		{
		}
	}

	return Adesk::kTrue;
}
void testApply()
{
	AcDbDatabase* db = ARXRLEDB;
	try
	{
		AcDbBlockTable *pBt;
		if (Acad::eOk != db->getBlockTable( pBt, AcDb::kForRead ))
			return;

		ArxRleApply<BlockTable>(pBt, testFunc1, AcDb::kForRead );
		pBt->close();

		AcDbDictionary *pNOD;
		if (Acad::eOk != db->getNamedObjectsDictionary( pNOD, AcDb::kForRead ))
			return;

		ArxRleApply<Dictionary>( pNOD, testFunc2, AcDb::kForRead );
		pNOD->close();

		AcDbLayerTable *pLt;
		if (Acad::eOk != db->getLayerTable( pLt, AcDb::kForRead ))
			return;

		ArxRleApply<LayerTable>( pLt, testFunc3, AcDb::kForRead );
		pLt->close();

		AcDbTextStyleTable *pTt;
		if (Acad::eOk != db->getTextStyleTable( pTt, AcDb::kForWrite ))
			return;

		ArxRleApply<TextStyleTable>( pTt, testFunc4, AcDb::kForWrite );
		pTt->close();
	}
	catch (...)
	{
		acutPrintf( L"Exception catched.\n" );
	}

	// Even shorter with my ArxUtils helper classes:
	try
	{
		ArxRleSmartPtr<AcDbBlockTable> pBt;
		db->getBlockTable( *pBt, AcDb::kForRead );
		ArxRleApply<BlockTable>( pBt, testFunc1, AcDb::kForRead );

		ArxRleSmartPtr<AcDbDictionary> pNOD;
		db->getNamedObjectsDictionary( *pNOD, AcDb::kForRead );
		ArxRleApply<Dictionary>( pNOD, testFunc2, AcDb::kForRead );

		ArxRleSmartPtr<AcDbLayerTable> pLt;
		db->getLayerTable( *pLt, AcDb::kForRead );
		ArxRleApply<LayerTable>( pLt, testFunc3, AcDb::kForRead );

		ArxRleSmartPtr<AcDbTextStyleTable> pTt;
		db->getTextStyleTable( *pTt, AcDb::kForWrite );
		ArxRleApply<TextStyleTable>( pTt, testFunc4, AcDb::kForWrite );
	}
	catch (const char *szMsg)
	{
		acutPrintf( L"%s\n", szMsg );
	}
}