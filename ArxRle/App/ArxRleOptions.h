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

#ifndef ARXRLEOPTIONS_H
#define ARXRLEOPTIONS_H

/****************************************************************************
**
**  CLASS ArxRleOptions:
**
**  **jma
**
*************************************/

class ArxRleOptions {

public:
				ArxRleOptions();
	virtual		~ArxRleOptions()	{}

        // data members (public since this is just a simple container)
    bool    m_showDwgFilerMessages;
    bool    m_showWblockCloneDetails;
    bool    m_showDeepCloneDetails;
    bool    m_doDictRecordInsertByHand;

	static ArxRleOptions	m_instance;
};

#endif  // ARXRLEOPTIONS_H
