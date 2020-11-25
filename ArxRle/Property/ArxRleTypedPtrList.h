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

#ifndef ARXRLE_TYPE_PTR_LIST_H
#define ARXRLE_TYPE_PTR_LIST_H

#include <afxtempl.h>

//////////////////////////////////////////////////////////////////////
// ArxRleTypedPtrList

template<class BASE_CLASS, class TYPE>
class ArxRleTypedPtrList : public CTypedPtrList<BASE_CLASS, TYPE>
{
public:
	ArxRleTypedPtrList(int nBlockSize = 10) 
		: CTypedPtrList<BASE_CLASS, TYPE>(nBlockSize) 
	{
	}

	~ArxRleTypedPtrList()
	{
		Destroy();
	}

	void Destroy()
	{
		POSITION pos = GetHeadPosition();

		while(pos != NULL)
		{
			TYPE node = GetNext(pos);
			delete node;
		}

		RemoveAll();
	}
};

#endif // ARXRLE_TYPE_PTR_LIST_H