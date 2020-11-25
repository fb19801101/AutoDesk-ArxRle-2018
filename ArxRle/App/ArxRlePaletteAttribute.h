// ArxRlePaletteAttribute.h: interface for the ArxRlePaletteAttribute class.
//

#ifndef ARXRLE_PALETTE_ATTRIBUTE_H
#define ARXRLE_PALETTE_ATTRIBUTE_H

#include "resource.h"
#include "ArxRleAttributeList.h"
#include "ArxRleButton.h"
#include "ArxRlePaletteSet.h"

// ArxRlePaletteAttribute ¶Ô»°¿ò
class ArxRlePaletteAttribute : public CAdUiPalette
{
	DECLARE_DYNAMIC(ArxRlePaletteAttribute)

public:
	ArxRlePaletteAttribute();
	virtual ~ArxRlePaletteAttribute();

public:
	void initControl();
	void updateControl();

	void SetObjId(int index, AcDbObjectId& objId);
	AcDbObjectId GetObjId(int index) const;

	void SetItemHeight(double height);
	double GetItemHeight() const;

	BOOL SelEntity(AcDbObjectIdArray& objs);
	BOOL UpdateEntity(AcDbObjectId& objId);
	BOOL UpdateList(AcDbObjectId& objId);

	static ArxRlePaletteSet* m_pPaletteSet;
	static ArxRlePaletteAttribute* m_pPaletteAttribute;
	static void entAttribute();

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//- Called by AutoCAD to steal focus from the palette
	virtual bool CanFrameworkTakeFocus () ;

protected:
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize (UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnSelchangeCsentsetCbName();
	afx_msg void OnBnClickedCsentsetBnUpList();
	afx_msg void OnBnClickedCsentsetBnSelect();
	afx_msg void OnBnClickedCsentsetBnUpEntity();
	DECLARE_MESSAGE_MAP()

private:
	CAcUiComboBox* m_cbName;
	CAcUiPickButton* m_bnUpList;
	CAcUiSelectButton* m_bnSelect;
	CAcUiPickButton* m_bnUpEntity;
	ArxRleAttributeList* m_lstAttrib;
	CToolTipCtrl* m_tipControl;

	int m_xBtn,m_yBtn;
	bool m_autoUpEntity;

	AcDbObjectIdArray m_objList;
	CRect m_rcAttrib,m_rcName;
	ArxRleAttributeListItems m_items;
};
#endif //ARXRLE_PALETTE_ATTRIBUTE_H
