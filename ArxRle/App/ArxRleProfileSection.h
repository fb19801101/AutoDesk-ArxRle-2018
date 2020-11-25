#ifndef ARXRLE_PROFILESECTION_H
#define ARXRLE_PROFILESECTION_H
// ArxRleProfileSection.h

class ArxRleProfileSection  
{
public:
	DWORD MapStrings(CMapStringToString & csMap);
	UINT GetKeyValue(LPCTSTR pcszKeyName, INT nDefault);
	CString GetKeyValue(LPCTSTR pcszKeyName, LPCTSTR pcszDefault);
	ArxRleProfileSection(){};
	ArxRleProfileSection(LPCTSTR pcszFilename, LPCTSTR pcszSection);
	virtual ~ArxRleProfileSection();
	void GetAllLines(LPCTSTR pcszFilename, CMapStringToString & csMap);

private:
	TCHAR * FindKey(LPCTSTR pcszKeyName);
	void Trim (CString &csValue);
	DWORD GetIniFileSize(LPCTSTR pcszFilename, CString & csFilePath);
	LPTSTR m_pszSectionBuffer;
	BOOL m_bInitialized;
};


#endif //ARXRLE_PROFILESECTION_H