// ArxRleUiTdcNetPlanWorkInput.h: interface for the ArxRleUiTdcNetPlanWorkInput class.
//

#ifndef ARXRLE_UITDC_NETPLAN_WORKINPUT_H
#define ARXRLE_UITDC_NETPLAN_WORKINPUT_H

#include "Resource.h"


// ArxRleUiTdcNetPlanWorkInput 对话框

class ArxRleUiTdcNetPlanWorkInput : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcNetPlanWorkInput)

public:
	ArxRleUiTdcNetPlanWorkInput();   // 标准构造函数
	virtual ~ArxRleUiTdcNetPlanWorkInput();

// 对话框数据
	enum { IDD = ARXRLE_TDC_NETPLAN_WORKINPUT };


protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	CXTPReportControl* m_xtpReport;
	CImageList m_imgList;
};

#endif //ARXRLE_UITDC_NETPLAN_WORKINPUT_H
