// ArxRleUiPage.h: interface for the ArxRleUiPage class.
//

#ifndef ARXRLE_UIPAGE_H
#define ARXRLE_UIPAGE_H


// ArxRleUiPage �Ի���

class ArxRleUiPage : public CDialogEx
{
	DECLARE_DYNAMIC(ArxRleUiPage)

public:
	ArxRleUiPage();
	ArxRleUiPage(UINT nIDTemplate, CWnd *pParent = NULL);
	ArxRleUiPage(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);
	virtual ~ArxRleUiPage();

// �Ի�������

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
};

#endif //ARXRLE_UIPAGE_H