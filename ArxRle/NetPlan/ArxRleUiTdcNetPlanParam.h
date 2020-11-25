// ArxRleUiTdcNetPlanParam.h: interface for the ArxRleUiTdcNetPlanParam class.
//

#ifndef ARXRLE_UITDC_NETPLAN_PARAM_H
#define ARXRLE_UITDC_NETPLAN_PARAM_H

#include "Resource.h"


// ArxRleUiTdcNetPlanParam �Ի���

// ͼֽ��С
typedef struct STRU_PAPERSIZE
{
	CString strName;                        // ����
	WORD wWidth;                            // ��
	WORD wHeight;                           // ��
	CString strUnit;                        // ��λ ֻ��������3��:MM��INCH��PIXEL
	CString PaperSize()
	{
		CString strPaperSize;
		strPaperSize.Format(_T("%s_(%d.00_x_%d.00_%s)"), strName, wWidth, wHeight, strUnit);
		return strPaperSize;
	}

	STRU_PAPERSIZE()
	{
		strName = _T("A3");
		wWidth = 420;
		wHeight = 297;
		strUnit = _T("mm");
	}
	STRU_PAPERSIZE(CString szName, const int nWidth, const int nHeight, CString szUnit)
	{
		strName = szName;
		wWidth = nWidth;
		wHeight = nHeight;
		strUnit = szUnit;
	}
	STRU_PAPERSIZE(const char* szPaperSize)
	{
		CString strPaperSize,str,str1;
		USES_CONVERSION;
		strPaperSize.Format(_T("%s"),A2T(szPaperSize));
		AfxExtractSubString(strPaperSize, str, 0 , '-');
		strName = str;
		AfxExtractSubString(strPaperSize, str, 1 , '_');
		AfxExtractSubString(str, str1, 1 , '(');
		wWidth = _tstoi(str1);
		AfxExtractSubString(strPaperSize, str, 3 , '_');
		wHeight = _tstoi(str);
		AfxExtractSubString(strPaperSize, str, 4 , '_');
		AfxExtractSubString(str, str1, 0 , '_');
		strUnit = str1;
	}
	STRU_PAPERSIZE(const STRU_PAPERSIZE& src)
	{
		strName = src.strName;
		wWidth = src.wWidth;
		wHeight = src.wHeight;
		strUnit = src.strUnit;
	}
	STRU_PAPERSIZE& operator = (STRU_PAPERSIZE& src)
	{
		strName = src.strName;
		wWidth = src.wWidth;
		wHeight = src.wHeight;
		strUnit = src.strUnit;
		return *this;
	}
	STRU_PAPERSIZE& operator = (const char* szPaperSize)
	{
		CString strPaperSize,str,str1;
		USES_CONVERSION;
		strPaperSize.Format(_T("%s"),A2T(szPaperSize));
		AfxExtractSubString(strPaperSize, str, 0 , '_');
		strName = str;
		AfxExtractSubString(strPaperSize, str, 1 , '_');
		AfxExtractSubString(str, str1, 1 , '(');
		wWidth = _tstoi(str1);
		AfxExtractSubString(strPaperSize, str, 3 , '_');
		wHeight = _tstoi(str);
		AfxExtractSubString(strPaperSize, str, 4 , '_');
		AfxExtractSubString(str, str1, 0 , '_');
		strUnit = str1;
		return *this;
	}
}PAPERSIZE;

class ArxRleUiTdcNetPlanParam : public CAcUiTabChildDialog
{
	DECLARE_DYNAMIC(ArxRleUiTdcNetPlanParam)

public:
	ArxRleUiTdcNetPlanParam();   // ��׼���캯��
	virtual ~ArxRleUiTdcNetPlanParam();

// �Ի�������
	enum { IDD = ARXRLE_TDC_NETPLAN_PARAM };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString m_strProject;
	double m_fBeginStat;
	double m_fEndStat;
	double m_fStatLen;
	CString m_strStatGap;
	CTime m_tBeginDay;
	CTime m_tEndDay;
	int m_nPlaneTime;
	CString m_strDayGap;

	CString m_strPaperSize;
	BOOL m_bDayLine;
	BOOL m_bWeekLine;
	BOOL m_bMonthLine;
	BOOL m_bYearLine;

	CDateTimeCtrl m_dtBeginDay;
	CDateTimeCtrl m_dtEndDay;
	CComboBox m_cbPaperSize;
	CComboBox m_cbDayGap;
	CComboBox m_cbStatGap;

	afx_msg void OnEnChangeNetplanParamEbPlanetime();
	afx_msg void OnDtnDatetimechangeNetplanParamDtEnddate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeNetplanParamDtBggindate(NMHDR *pNMHDR, LRESULT *pResult);
};

#endif //ARXRLE_UITDC_NETPLAN_PARAM_H
