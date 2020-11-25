// ArxRleUiTdmNetPlan.h: interface for the ArxRleUiTdmNetPlan class.
//

#ifndef ARXRLE_UITDM_NETPLAN_H
#define ARXRLE_UITDM_NETPLAN_H

#include "Resource.h"
#include "ArxRleTabCtrl.h"
#include "ArxRleNetPlanWork.h"
#include "ArxRleNetPlanWorkStyle.h"
#include "ArxRleUiTdcNetPlanParam.h"
#include "ArxRleUiTdcNetPlanWorkData.h"
#include "ArxRleUiTdcNetPlanWorkStyle.h"
#include "ArxRleUiTdcNetPlanWorkInput.h"


//工序类型
enum ArxNetPlanWorkType
{
	ArxStandard   = 0,
	ArxGeneral    = 1,
	ArxKey        = 2,
	ArxVirtual    = 3,
	ArxFree       = 4,
};

class ArxRleNetPlanDataItem
{
public:
	ArxRleNetPlanDataItem()
	{
		fBeginStat = 0;
		fEndStat = 10000;
		fStatLen = 10000;
		fStatGap = 100;
		tBeginDay = GetCurrentTime();
		tEndDay = GetCurrentTime();
		nPlanTime = 0;
		nDayGap = 1;
		nPaperWidth = 420;
		nPaperHeight = 297;
		bDayLine = FALSE;
		bWeekLine = TRUE;
		bMonthLine = TRUE;
		bYearLine = TRUE;
		nWorkNameCol1 = 0;
		nWorkNameCol2 = 0;
		nNodeBeginCol = 0;
		nNodeEndCol = 0;
		nTimeBeginCol = 0;
		nTimeEndCol = 0;
		nWorkBeginRow = 0;
		nWorkEndRow = 0;
	}
	ArxRleNetPlanDataItem(CString prj, CString paper, CTime t1, CTime t2)
	{
		strProject = prj;
		strPaperSize = paper;
		fBeginStat = 0;
		fEndStat = 10000;
		fStatLen = 10000;
		fStatGap = 100;
		tBeginDay = t1;
		tEndDay = t2;
		nPlanTime = 0;
		nDayGap = 1;
		bDayLine = FALSE;
		bWeekLine = TRUE;
		bMonthLine = TRUE;
		bYearLine = TRUE;
		nWorkNameCol1 = 0;
		nWorkNameCol2 = 0;
		nNodeBeginCol = 0;
		nNodeEndCol = 0;
		nTimeBeginCol = 0;
		nTimeEndCol = 0;
		nWorkBeginRow = 0;
		nWorkEndRow = 0;
		
		CStringArray strArray;
		ParseSubStrByDelimiter(strPaperSize,strArray,'_');
		nPaperWidth = _tstoi(strArray[1]);
		nPaperHeight = _tstoi(strArray[3]);
	}
	ArxRleNetPlanDataItem(CString prj, CString paper, double st1, double st2, CTime t1, CTime t2)
	{
		strProject = prj;
		strPaperSize = paper;
		fBeginStat = st1;
		fEndStat = st2;
		fStatLen = 10000;
		fStatGap = 100;
		tBeginDay = t1;
		tEndDay = t2;
		nPlanTime = 0;
		nDayGap = 1;
		bDayLine = FALSE;
		bWeekLine = TRUE;
		bMonthLine = TRUE;
		bYearLine = TRUE;
		nWorkNameCol1 = 0;
		nWorkNameCol2 = 0;
		nNodeBeginCol = 0;
		nNodeEndCol = 0;
		nTimeBeginCol = 0;
		nTimeEndCol = 0;
		nWorkBeginRow = 0;
		nWorkEndRow = 0;

		CStringArray strArray;
		ParseSubStrByDelimiter(strPaperSize,strArray,'_');
		nPaperWidth = _tstoi(strArray[1]);
		nPaperHeight = _tstoi(strArray[3]);
	}
	ArxRleNetPlanDataItem(const ArxRleNetPlanDataItem& src)
	{
		strProject = src.strProject;
		strPaperSize = src.strPaperSize;
		fBeginStat = src.fBeginStat;
		fEndStat = src.fEndStat;
		fStatLen = src.fStatLen;
		fStatGap = src.fStatGap;
		tBeginDay = src.tBeginDay;
		tEndDay = src.tEndDay;
		nPlanTime = src.nPlanTime;
		nDayGap = src.nDayGap;
		nPaperWidth = src.nPaperWidth;
		nPaperHeight = src.nPaperHeight;
		bDayLine = src.bDayLine;
		bWeekLine = src.bWeekLine;
		bMonthLine = src.bMonthLine;
		bYearLine = src.bYearLine;
		strXlsFilePath = src.strXlsFilePath;
		strXlsFileName = src.strXlsFileName;
		strXlsSheetName  = src.strXlsSheetName;
		nWorkNameCol1 = src.nWorkNameCol1;
		nWorkNameCol2 = src.nWorkNameCol2;
		nNodeBeginCol = src.nNodeBeginCol;
		nNodeEndCol = src.nNodeEndCol;
		nTimeBeginCol = src.nTimeBeginCol;
		nTimeEndCol = src.nTimeEndCol;
		nWorkBeginRow = src.nWorkBeginRow;
		nWorkEndRow = src.nWorkEndRow;
		objIdList = src.objIdList;
	}
	ArxRleNetPlanDataItem& operator=(const ArxRleNetPlanDataItem& src)
	{
		strProject = src.strProject;
		strPaperSize = src.strPaperSize;
		fBeginStat = src.fBeginStat;
		fEndStat = src.fEndStat;
		fStatLen = src.fStatLen;
		fStatGap = src.fStatGap;
		tBeginDay = src.tBeginDay;
		tEndDay = src.tEndDay;
		nPlanTime = src.nPlanTime;
		nDayGap = src.nDayGap;
		nPaperWidth = src.nPaperWidth;
		nPaperHeight = src.nPaperHeight;
		bDayLine = src.bDayLine;
		bWeekLine = src.bWeekLine;
		bMonthLine = src.bMonthLine;
		bYearLine = src.bYearLine;
		strXlsFilePath = src.strXlsFilePath;
		strXlsFileName = src.strXlsFileName;
		strXlsSheetName  = src.strXlsSheetName;
		nWorkNameCol1 = src.nWorkNameCol1;
		nWorkNameCol2 = src.nWorkNameCol2;
		nNodeBeginCol = src.nNodeBeginCol;
		nNodeEndCol = src.nNodeEndCol;
		nTimeBeginCol = src.nTimeBeginCol;
		nTimeEndCol = src.nTimeEndCol;
		nWorkBeginRow = src.nWorkBeginRow;
		nWorkEndRow = src.nWorkEndRow;
		objIdList = src.objIdList;
		return *this;
	}

public:
	//TabPage参数
	CString strProject;
	CString strPaperSize;
	double fBeginStat;
	double fEndStat;
	double fStatLen;
	double fStatGap;
	CTime tBeginDay;
	CTime tEndDay;
	int nPlanTime;
	int nDayGap;
	int nPaperWidth;
	int nPaperHeight;
	BOOL bDayLine;
	BOOL bWeekLine;
	BOOL bMonthLine;
	BOOL bYearLine;
	//TabPage1参数
	CString strXlsFilePath;
	CString strXlsFileName;
	CString strXlsSheetName;
	int nWorkNameCol1;
	int nWorkNameCol2;
	int nNodeBeginCol;
	int nNodeEndCol;
	int nTimeBeginCol;
	int nTimeEndCol;
	int nWorkBeginRow;
	int nWorkEndRow;

	AcDbObjectIdArray objIdList;
};

class ArxRleNetPlanWorkItem
{
public:
	ArxRleNetPlanWorkItem()
	{
		work_name = "";
		code_begin = 0;
		code_end = 0;
		time_begin = GetCurrentTime();
		time_end = GetCurrentTime();
		time_days = (long)(time_end-time_begin).GetDays();
		work_type = ArxStandard;
	}
	ArxRleNetPlanWorkItem(CString name, double code1, double code2, CTime t1 = GetCurrentTime(), CTime t2 = GetCurrentTime(), ArxNetPlanWorkType type = ArxStandard)
	{
		work_name = name;
		code_begin = code1;
		code_end   = code2;
		time_begin = t1;
		time_end = t2;
		time_days = (long)(time_end-time_begin).GetDays()+1;
		work_type = type;
	}
	ArxRleNetPlanWorkItem(const ArxRleNetPlanWorkItem& src)
	{
		work_name = src.work_name;
		code_begin = src.code_begin;
		code_end   = src.code_end;
		time_begin = src.time_begin;
		time_end = src.time_end;
		time_days = src.time_days;
		work_type = src.work_type;
	}
	ArxRleNetPlanWorkItem& operator = (const ArxRleNetPlanWorkItem& src)
	{
		work_name = src.work_name;
		code_begin = src.code_begin;
		code_end   = src.code_end;
		time_begin = src.time_begin;
		time_end = src.time_end;
		time_days = src.time_days;
		work_type = src.work_type;
		return *this;
	}

public:
	CString work_name;
	double code_begin;
	double code_end;
	CTime time_begin;
	CTime time_end;
	long time_days;
	ArxNetPlanWorkType work_type;
};

class ArxRleNetPlanNodeItem
{
public:
	ArxRleNetPlanNodeItem()
	{
		x=y=0;
		b=0;
	}
	ArxRleNetPlanNodeItem(const AcDbObjectId& objId, int node)
	{
		x = 0;
		y = 0;
		b = 0;

		AcDbEntity* ent;
		Acad::ErrorStatus es = acdbOpenObject(ent, objId, AcDb::kForRead);
		if(es == Acad::eOk)
		{
			if(ent->isKindOf(ArxRleNetPlanWork::desc()))
			{
				b = node;
				id = objId;

				if(b == 1)
				{
					x = ((ArxRleNetPlanWork*)ent)->getPointBegin().x;
					y = ((ArxRleNetPlanWork*)ent)->getPointBegin().y;
				}

				if(b == 2)
				{
					x = ((ArxRleNetPlanWork*)ent)->getPointEnd().x;
					y = ((ArxRleNetPlanWork*)ent)->getPointEnd().y;
				}

				ent->close();
			}
		}
	}
	ArxRleNetPlanNodeItem(const ArxRleNetPlanNodeItem& src)
	{
		x = src.x;
		y = src.y;
		b = src.b;
		id = src.id;
	}
	ArxRleNetPlanNodeItem& operator = (const ArxRleNetPlanNodeItem& src)
	{
		x = src.x;
		y = src.y;
		b = src.b;
		id = src.id;
		return *this;
	}
	bool operator < (const ArxRleNetPlanNodeItem& src) const
	{
		if(x < src.x)
			return true;
		else
			if(x == src.x)
				if(y > src.y)
					return true;
				else
					return false;
			else
				return false;
	}

public:
	double x,y;//节点坐标
	int    b;//起点1，终点2
	AcDbObjectId id;
};

// ArxRleUiTdmNetPlan 对话框

class ArxRleUiTdmNetPlan : public CAcUiTabMainDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdmNetPlan)

public:
	ArxRleUiTdmNetPlan(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ArxRleUiTdmNetPlan();

// 对话框数据
	enum { IDD = ARXRLE_TDM_NETPLAN };

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	static ArxRleNetPlanDataItem m_itemNetPlanData;

	CAdUiTab m_tabCtrl;
	ArxRleUiTdcNetPlanParam* m_pPageParam;
	ArxRleUiTdcNetPlanWorkData* m_pPageWorkData;
	ArxRleUiTdcNetPlanWorkStyle* m_pPageWorkStyle;
	ArxRleUiTdcNetPlanWorkInput* m_pPageWorkInput;
};

#endif //ARXRLE_UITDM_NETPLAN_H