// ArxRleUiTdmSpa.h: interface for the ArxRleUiTdmSpa class.
//

#ifndef ARXRLE_UITDM_SPA_H
#define ARXRLE_UITDM_SPA_H

#include "Resource.h"
#include "ArxRleUiTdcSpaBeamCracks.h"
#include "ArxRleUiTdcSpaBeamSection.h"
#include "ArxRleUiTdcSpaCircleStrength.h"
#include "ArxRleUiTdcSpaColumnStrength.h"
#include "ArxRleUiTdcSpaOutResult.h"
#include "ArxRleUiTdcSpaWallStrength.h"

// ArxRleUiTdmSpa �Ի���

class ArxRleUiTdmSpa : public CAcUiTabMainDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdmSpa)

public:
	ArxRleUiTdmSpa(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ArxRleUiTdmSpa();

// �Ի�������
	enum { IDD = ARXRLE_TDM_STRUCT_SPA };

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	CAdUiTab m_tabCtrl;
	ArxRleUiTdcSpaBeamCracks* m_pPageBeamCracks;
	ArxRleUiTdcSpaBeamSection* m_pPageBeamSection;
	ArxRleUiTdcSpaCircleStrength* m_pPageCircleStrength;
	ArxRleUiTdcSpaColumnStrength* m_pPageColumnStrength;
	ArxRleUiTdcSpaWallStrength* m_pPageWallStrength;
	ArxRleUiTdcSpaOutResult* m_pPageOutResult;
};

#endif //ARXRLE_UITDM_NETPLAN_H