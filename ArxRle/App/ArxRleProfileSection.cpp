
// ArxRleProfileSection.cpp

#include "stdafx.h"
#include "ArxRleProfileSection.h"

void ArxRleProfileSection::GetAllLines(LPCTSTR pcszFilename, CMapStringToString & csMap)
{
	CString csFilePath;
	DWORD dwSize = GetIniFileSize(pcszFilename, csFilePath);
	if(dwSize) {
		TCHAR * pszBuffer = new TCHAR[dwSize + 2];
		DWORD dwRead = GetPrivateProfileSectionNames(pszBuffer, dwSize, csFilePath);

		if(dwRead == dwSize - 2) {
			delete [] pszBuffer;
			pszBuffer = NULL;
			return;
		}

		m_bInitialized = TRUE;

		TCHAR * pszBuffer2 = new TCHAR[dwSize + 2];
		TCHAR * pszSection = pszBuffer;
		while(*pszSection) {
			dwRead = GetPrivateProfileSection(pszSection, pszBuffer2, dwSize, csFilePath);
			m_pszSectionBuffer = pszBuffer2;
			//DWORD dwTotal = profile->MapStrings(csMap);
			this->MapStrings(csMap);
			pszSection += _tcslen(pszSection) + 1;
		}
	}
	return;
}
// pcszFilename is full path of INI or if INI is in same path as your
// application then can just be the filename itself with no path.
// pcszSection is the section of the INI file you want read.
ArxRleProfileSection::ArxRleProfileSection(LPCTSTR pcszFilename, LPCTSTR pcszSection)
{	
	m_bInitialized = FALSE;
	m_pszSectionBuffer = NULL;
	CString csFilePath;
	DWORD dwSize = GetIniFileSize(pcszFilename, csFilePath);
	if(dwSize) {
		TCHAR * pszBuffer = new TCHAR[dwSize + 2];
		DWORD dwRead = GetPrivateProfileSection(pcszSection, pszBuffer, dwSize, csFilePath);
		
		if(dwRead == dwSize - 2) {
			// need more buffer space. Add code for this condition, though
			// this should not happen. For now just delete the buffer and return
			delete [] pszBuffer;
			pszBuffer = NULL;
			return;
		}
		if(dwRead == 0) {
			// Something went haywire, delete the buffer and return.
			delete [] pszBuffer;
			pszBuffer = NULL;
			return;
		}
		m_pszSectionBuffer = pszBuffer;
		m_bInitialized = TRUE;
	}
}

ArxRleProfileSection::~ArxRleProfileSection()
{
	if(m_pszSectionBuffer) {
		delete [] m_pszSectionBuffer;
		m_pszSectionBuffer = NULL;
	}
}

// Finds the INI file and returns its size, also fully qualifies the path
// in case pcszFilename doesn't include one.
// If the INI file is not found then 0 is returned.
DWORD ArxRleProfileSection::GetIniFileSize(LPCTSTR pcszFilename, CString & csFullPath)
{
	DWORD dwSize = 0;
	CFileFind ff;
	if(ff.FindFile(pcszFilename)) {
		ff.FindNextFile();
		dwSize = ff.GetLength();
		csFullPath = ff.GetFilePath();
	}
	return dwSize;
}

// Scans the each line in the buffer for "=". If found it then
// checks if string proceeding "=" is equal to pcszKeyName. If
// it is then function returns pointer in buffer right after "=".
// If pcszKeyName is not found then returns NULL;
TCHAR * ArxRleProfileSection::FindKey(LPCTSTR pcszKeyName)
{
	TCHAR * pszLine = m_pszSectionBuffer;
	while(*pszLine) {
		TCHAR * pszKey = pszLine;
		while(*pszKey) {
			if(*pszKey == _T('=')) {
                CString csKeyName(pszLine, _tcslen(pcszKeyName));
                Trim(csKeyName);
				if(csKeyName.CompareNoCase(pcszKeyName) == 0)
					return ++pszKey;
			}
			pszKey++;
		}
		pszLine += _tcslen(pszLine) + 1;
	}
	return NULL;
}

void ArxRleProfileSection::Trim (CString &csValue)
{
	csValue.TrimRight();
	csValue.TrimLeft();
}

// Get a string key value or uses pcszDefault if pcszKeyName is
// not found. Trims leading and trailing white space before returning
// value.
CString ArxRleProfileSection::GetKeyValue(LPCTSTR pcszKeyName, LPCTSTR pcszDefault)
{
	CString csValue;
	if(!m_bInitialized)
		csValue = pcszDefault;
	else {
		csValue = FindKey(pcszKeyName);
		if(csValue.IsEmpty())
			csValue = pcszDefault;
	}
	Trim(csValue);
	return csValue;
}

// Get a UINT key value. Mimicks GetPrivateProfileInt function
// on return value.
UINT ArxRleProfileSection::GetKeyValue(LPCTSTR pcszKeyName, INT nDefault)
{
	INT nValue = nDefault;
	if(m_bInitialized) {
		CString csValue = FindKey(pcszKeyName);
		if(!csValue.IsEmpty())
			nValue = _tstoi(csValue);
	}
	
	if(nValue < 0)
		nValue = 0;
	
	return nValue;
}


// Maps a key and its value to CMapStringToString. Be aware
// that keys are case sensitive. See MSDN docs for details.
// This function makes the keys lower case.
DWORD ArxRleProfileSection::MapStrings(CMapStringToString &csMap)
{	
	if(m_bInitialized) {
		TCHAR * pszLine = m_pszSectionBuffer;
		while(*pszLine) {
			TCHAR * pszKey = pszLine;
			while(*pszKey) {
				if(*pszKey == _T('=')) {
					CString csValue(pszLine, pszKey - pszLine);
					csValue.MakeLower();
					csMap.SetAt(csValue, CString(++pszKey));
					break;
				}
				pszKey++;
			}
			pszLine += _tcslen(pszLine) + 1;
		}
	}
	return csMap.GetCount();
}
