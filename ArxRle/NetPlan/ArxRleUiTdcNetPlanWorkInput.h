// ArxRleUiTdcNetPlanWorkInput.h: interface for the ArxRleUiTdcNetPlanWorkInput class.
//

#ifndef ARXRLE_UITDC_NETPLAN_WORKINPUT_H
#define ARXRLE_UITDC_NETPLAN_WORKINPUT_H

#include "Resource.h"


// ArxRleUiTdcNetPlanWorkInput �Ի���

class ArxRleUiTdcNetPlanWorkInput : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcNetPlanWorkInput)

public:
	ArxRleUiTdcNetPlanWorkInput();   // ��׼���캯��
	virtual ~ArxRleUiTdcNetPlanWorkInput();

// �Ի�������
	enum { IDD = ARXRLE_TDC_NETPLAN_WORKINPUT };


protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	CXTPReportControl* m_xtpReport;
	CImageList m_imgList;
};

#endif //ARXRLE_UITDC_NETPLAN_WORKINPUT_H
