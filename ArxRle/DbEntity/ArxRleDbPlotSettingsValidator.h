// ArxRleDbPlotSettingsValidator.h: interface for the ArxRleDbPlotSettingsValidator class.
//

#ifndef ARXRLE_DBPLOTSETTINGSVALIDATOR_H
#define ARXRLE_DBPLOTSETTINGSVALIDATOR_H

#include "dblayout.h"
#include "acaplmgr.h"
#include "dbplotsetval.h"
#include "dbplotsettings.h"


// ArxRleDbPlotSettingsValidator

class ArxRleDbPlotSettingsValidator : public AcDbPlotSettingsValidator
{
public:
	ArxRleDbPlotSettingsValidator(){m_pValidator = acdbHostApplicationServices()->plotSettingsValidator();}
	virtual ~ArxRleDbPlotSettingsValidator(){m_pValidator = NULL;}
	void mplotzzmplots()
	{
		AcApLayoutManager *pLayMan = (AcApLayoutManager*)acdbHostApplicationServices()->layoutManager();

		//get the active layout
		AcDbLayout *pLayout = pLayMan->findLayoutNamed(pLayMan->findActiveLayout(TRUE),TRUE);

		AcDbPlotSettings* pPlotSetting = (AcDbPlotSettings*)pLayout;
		const ACHAR* mediaName;
		pPlotSetting->getCanonicalMediaName(mediaName);
		acutPrintf(L"\nMedia Name:%s", mediaName);

		const ACHAR* styleSheetName;
		pPlotSetting->getCurrentStyleSheet(styleSheetName);
		acutPrintf(L"\nStyleSheet Name:%s", styleSheetName);
		const ACHAR* plotCfgname;
		pPlotSetting->getPlotCfgName(plotCfgname);          // Output pointer to name of configured system or PC3 plot device
		acutPrintf(L"\nPlotCfg Name:%s", plotCfgname);

		//get the PlotSettingsValidator
		AcDbPlotSettingsValidator *pPSV = acdbHostApplicationServices()->plotSettingsValidator();
		//refresh the Plot Config list
		pPSV->refreshLists(pLayout);

		//get all the Plot Configurations
		AcArray<const ACHAR*> mDeviceList;
		pPSV->plotDeviceList(mDeviceList);

		acutPrintf(L"\nPlot Configuration List :");
		int nLength = mDeviceList.length();

		const ACHAR* localeName;
		pPSV->getLocaleMediaName(pLayout, 0, localeName);
		acutPrintf(L"\nCur Midia Name:%s", localeName);

		pPlotSetting->close();
		pLayout->close();
		return;
		for(int nCtr = 0;nCtr < nLength; nCtr++)
		{
			acutPrintf(L"\n %i) - %s",(nCtr + 1), mDeviceList.at(nCtr));
		}

		//get the user input for listing the Media Names
		int nSel;
		int mRes = RTNONE;

		while(RTNORM != mRes)
		{
			acedInitGet((RSG_NONULL + RSG_NONEG + RSG_NOZERO),NULL);
			mRes = acedGetInt(L"\nSelect the Plot Configuration number to list the Media names: ", &nSel);
			if (nSel > nLength) 
			{
				acutPrintf(L"\nEnter a number between 1 to %i",nLength);
				mRes = RTNONE;
			}
		}

		//select the selected Plot configuration
		pPSV->setPlotCfgName(pLayout,mDeviceList.at(--nSel));
		//list all the paper sizes in the given Plot configuration
		AcArray<const ACHAR*> mMediaList;
		const ACHAR *pLocaleName;
		pPSV->canonicalMediaNameList(pLayout,mMediaList);

		acutPrintf(L"\nMedia list for Plot Configuration - %s:",mDeviceList.at(nSel));

		nLength = mMediaList.length();
		for(int nCtr = 0; nCtr < nLength; nCtr++)
		{
			//get the localename
			pPSV->getLocaleMediaName(pLayout,mMediaList.at(nCtr),pLocaleName);
			acutPrintf(L"\n %i)\n   Name: %s \n   Locale Name: %s ",(nCtr + 1),mMediaList.at(nCtr),pLocaleName);
		}
		mRes = RTNONE;
		while(RTNORM != mRes)
		{
			acedInitGet((RSG_NONULL + RSG_NONEG + RSG_NOZERO),NULL);
			mRes = acedGetInt(L"\nSelect the Media by entering the number: ", &nSel);
			if (nSel > nLength) 
			{
				acutPrintf(L"\nEnter a number between 1 to %i",nLength);
				mRes = RTNONE;
			}
		}
		//set selected Media for the layout
		pPSV->setCanonicalMediaName(pLayout,mMediaList.at(--nSel));
		pLayout->close();
	}

public:
	Acad::ErrorStatus SetPlotCfgName(AcDbPlotSettings* pPlotSet, const ACHAR* plotDeviceName, const ACHAR* mediaName = NULL)
		{m_pValidator->setPlotCfgName(pPlotSet, plotDeviceName, mediaName);}
	Acad::ErrorStatus SetCanonicalMediaName(AcDbPlotSettings* pPlotSet, const ACHAR* mediaName)
		{m_pValidator->setCanonicalMediaName(pPlotSet, mediaName);}
	Acad::ErrorStatus SetPlotOrigin(AcDbPlotSettings *pPlotSet, const double xCoordinate, const double yCoordinate)
		{m_pValidator->setPlotOrigin(pPlotSet, xCoordinate, yCoordinate);}
	Acad::ErrorStatus SetPlotPaperUnits(AcDbPlotSettings* pPlotSet, const PlotPaperUnits units)
		{m_pValidator->setPlotPaperUnits(pPlotSet, units);}
	Acad::ErrorStatus SetPlotRotation(AcDbPlotSettings* pPlotSet, const PlotRotation rotationType)
		{m_pValidator->setPlotRotation(pPlotSet, rotationType);}
	Acad::ErrorStatus SetPlotCentered(AcDbPlotSettings* pPlotSet, Adesk::Boolean isCentered)
		{m_pValidator->setPlotCentered(pPlotSet, isCentered);}
	Acad::ErrorStatus SetPlotType(AcDbPlotSettings* pPlotSet, const PlotType plotAreaType)
		{m_pValidator->setPlotType(pPlotSet, plotAreaType);}
	Acad::ErrorStatus SetPlotWindowArea(AcDbPlotSettings* pPlotSet, const double xmin, const double ymin, const double xmax, const double ymax)
		{m_pValidator->setPlotWindowArea(pPlotSet, xmin, ymin, xmax, ymax);}
	Acad::ErrorStatus SetPlotViewName(AcDbPlotSettings* pPlotSet,const ACHAR* viewName)
		{m_pValidator->setPlotViewName(pPlotSet, viewName);}
	Acad::ErrorStatus SetUseStandardScale(AcDbPlotSettings* pPlotSet, Adesk::Boolean useStandard)
		{m_pValidator->setUseStandardScale(pPlotSet, useStandard);}
	Acad::ErrorStatus SetCustomPrintScale(AcDbPlotSettings* pPlotSet, const double numerator, const double denominator)
		{m_pValidator->setCustomPrintScale(pPlotSet, numerator, denominator);}
	Acad::ErrorStatus SetCurrentStyleSheet(AcDbPlotSettings* pPlotSet, const ACHAR* styleSheetName)
		{m_pValidator->setCurrentStyleSheet(pPlotSet, styleSheetName);}
	Acad::ErrorStatus SetStdScaleType(AcDbPlotSettings* pPlotSet, const StdScaleType scaleType)
		{m_pValidator->setStdScaleType(pPlotSet, scaleType);}
	Acad::ErrorStatus SetStdScale(AcDbPlotSettings* pPlotSet, const double standardScale)
		{m_pValidator->setStdScale(pPlotSet, standardScale);}
	Acad::ErrorStatus PlotDeviceList(AcArray<const ACHAR*>& deviceList)
		{m_pValidator->plotDeviceList(deviceList);}

	Acad::ErrorStatus CanonicalMediaNameList(AcDbPlotSettings* pPlotSet, AcArray<const ACHAR*>& mediaList )
		{m_pValidator->canonicalMediaNameList(pPlotSet, mediaList );}
	Acad::ErrorStatus GetLocaleMediaName(AcDbPlotSettings* pPlotSet, const ACHAR* canonicalName, const ACHAR*& localeName)
		{m_pValidator->getLocaleMediaName(pPlotSet, canonicalName, localeName);}
	Acad::ErrorStatus GetLocaleMediaName(AcDbPlotSettings* pPlotSet, int index, const ACHAR*& localeName)
		{m_pValidator->getLocaleMediaName(pPlotSet, index, localeName);}
	Acad::ErrorStatus SetClosestMediaName(AcDbPlotSettings* pPlotSet, const double paperWidth, const double paperHeight, const PlotPaperUnits units, Adesk::Boolean matchPrintableArea)
		{m_pValidator->setClosestMediaName(pPlotSet, paperWidth, paperHeight, units, matchPrintableArea);}
	Acad::ErrorStatus PlotStyleSheetList(AcArray<const ACHAR*>& styleList)
		{m_pValidator->plotStyleSheetList(styleList);}

	void RefreshLists(AcDbPlotSettings* pPlotSet)
		{m_pValidator->refreshLists(pPlotSet);}
	void SetZoomToPaperOnUpdate(AcDbPlotSettings* pPlotSet, Adesk::Boolean doZoom)
		{m_pValidator->setZoomToPaperOnUpdate(pPlotSet, doZoom);}
	Acad::ErrorStatus SetDefaultPlotConfig(AcDbPlotSettings* pPlotSet)
		{m_pValidator->setDefaultPlotConfig(pPlotSet);}

protected:
	AcDbPlotSettingsValidator* m_pValidator;

};

#endif //ARXRLEDBPLOTSETTINGSVALIDATOR_H

