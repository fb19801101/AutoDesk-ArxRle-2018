// ArxRleUiTdcNetPlanWorkStyle.h: interface for the ArxRleUiTdcNetPlanWorkStyle class.
//

#ifndef ARXRLE_UITDC_NETPLAN_WORKSTYLE_H
#define ARXRLE_UITDC_NETPLAN_WORKSTYLE_H

#include "Resource.h"
#include "App/ArxRleButton.h"


// ArxRleUiTdcNetPlanWorkStyle 对话框

class ArxRleUiTdcNetPlanWorkStyle : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcNetPlanWorkStyle)

public:
	ArxRleUiTdcNetPlanWorkStyle();   // 标准构造函数
	virtual ~ArxRleUiTdcNetPlanWorkStyle();

	// 对话框数据
	enum { IDD = ARXRLE_TDC_NETPLAN_WORKSTYLE };

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	AcDbObjectIdArray m_objIdList;
	CString  m_styleName;
	CString  m_layerName;
	CString  m_textStyleName;
	CString  m_lineTypeName;
	int m_colorIndex;
	double    m_lineScale;
	double    m_radiusBegin;
	double    m_radiusEnd;
	double    m_lenArrow;
	double    m_sizeLabel;
	double    m_sizeNode;
	double    m_dayGap;
	double    m_lineGap;
	BOOL      m_drawLabelBegin;
	BOOL      m_drawLabelEnd;
	BOOL      m_drawLabelUp;
	BOOL      m_drawLabelDown;

	CButton m_btnStyleNew;
	CButton m_btnStyleDel;
	CButton m_btnStyleClrIdx;
	ArxRleButtonXP m_btnStyleApply;
	CComboBox m_cxStyleName;
	CComboBox m_cxStyleLayer;
	CComboBox m_cxStyleLineType;
	CComboBox m_cxStyleTextStyle;

	afx_msg void OnBnClickedNetPlanPage2BnStylenew();
	afx_msg void OnBnClickedNetPlanPage2BnStyledel();
	afx_msg void OnBnClickedNetPlanPage2BnStyleapply();
	afx_msg void OnBnClickedNetPlanPage2BnStyleclridx();
	afx_msg void OnCbnSelchangeNetPlanPage2CxStylename();

	void WriteStyle(int cur, bool alert=false);
	void ReadStyle(int cur, bool alert=false);
	void DeleteStyle(int cur, bool alert=false);
};

#endif //ARXRLE_UITDC_NETPLAN_WORKSTYLE_H