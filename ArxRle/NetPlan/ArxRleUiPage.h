// ArxRleUiPage.h: interface for the ArxRleUiPage class.
//

#ifndef ARXRLE_UIPAGE_H
#define ARXRLE_UIPAGE_H


// ArxRleUiPage 对话框

class ArxRleUiPage : public CDialogEx
{
	DECLARE_DYNAMIC(ArxRleUiPage)

public:
	ArxRleUiPage();
	ArxRleUiPage(UINT nIDTemplate, CWnd *pParent = NULL);
	ArxRleUiPage(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);
	virtual ~ArxRleUiPage();

// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
};

#endif //ARXRLE_UIPAGE_H