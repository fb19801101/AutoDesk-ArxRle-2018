//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef ARXRLE_UIDLG_PROPERTY_H
#define ARXRLE_UIDLG_PROPERTY_H

#include "Resource.h"
#include "ArxRlePropertyData.h"
#include "ArxRlePropertyData.h"

/////////////////////////////////////////////////////////////////////////////
// ArxRleUiDlgProperty dialog

class ArxRleUiDlgProperty : public CAcUiDialog
{
	DECLARE_DYNAMIC(ArxRleUiDlgProperty)
public:
	ArxRleUiDlgProperty(CWnd* pParent = NULL);	// standard constructor
	virtual ~ArxRleUiDlgProperty();

	enum { IDD = ARXRLE_DLG_ENTPROPERTY };

	BOOL SelEntity();

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:

	afx_msg void OnSize (UINT nType, int cx, int cy);
	afx_msg void OnCbnSelchangeCsentsetCbName();
	afx_msg void OnBnClickedCsentsetBnUpList();
	afx_msg void OnBnClickedCsentsetBnSelect();
	afx_msg void OnBnClickedCsentsetBnUpEntity();
	DECLARE_MESSAGE_MAP()

private:
	CAcUiComboBox m_cbName;
	CAcUiPickButton m_bnUpList;
	CAcUiSelectButton m_bnSelect;
	CAcUiPickButton m_bnUpEntity;
	ArxRlePropertyListBox m_lbProperty;

	ArxRleWorkPropertyItemManager m_workManager;
	ArxRlePropertyData m_data;

	CToolTipCtrl* m_tipControl;

	int m_xBtn,m_yBtn;

	AcDbObjectIdArray m_objList;
	CRect m_rcProperty,m_rcName;
};

#endif // ARXRLE_UIDLG_PROPERTY_H
