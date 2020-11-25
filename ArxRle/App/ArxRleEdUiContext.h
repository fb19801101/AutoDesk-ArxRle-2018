//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef ARXRLEEDUICONTEXT_H
#define ARXRLEEDUICONTEXT_H

/**************************************************************************
**
**  CLASS ArxRleEdUiContext
**
**  **jma
**
*************************************/

class ArxRleEdUiContext : public AcEdUIContext {

public:
				ArxRleEdUiContext(int nSub = 0);
	virtual		~ArxRleEdUiContext();

    //ACRX_DECLARE_MEMBERS(ArxRleEdUiContext);

    virtual void*	getMenuContext(const AcRxClass* classtype, const AcDbObjectIdArray& selectedObjs);
    virtual void	onCommand(Adesk::UInt32 cmdId);

	bool			isValid() const { return (m_cMenu != NULL); }

private:
		// data members
    CMenu*		m_cMenu;
    HMENU		m_hMenu;
	int         m_nSub;
};

#endif // ARXRLEEDUICONTEXT_H