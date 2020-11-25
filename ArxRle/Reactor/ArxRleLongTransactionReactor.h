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

#ifndef ARXRLELONGTRANSACTIONREACTOR_H
#define ARXRLELONGTRANSACTIONREACTOR_H

/****************************************************************************
**
**  CLASS ArxRleLongTransactionReactor:
**
**  **jma
**
*************************************/

class ArxRleLongTransactionReactor: public AcApLongTransactionReactor { 

public:
    ACRX_DECLARE_MEMBERS(ArxRleLongTransactionReactor);

					ArxRleLongTransactionReactor();
	virtual			~ArxRleLongTransactionReactor();

    virtual void	beginCheckOut(AcDbLongTransaction& lt, AcDbObjectIdArray& originList);
    virtual void	endCheckOut(AcDbLongTransaction& lt);
    virtual void	beginCheckIn(AcDbLongTransaction& lt);
    virtual void	endCheckIn(AcDbLongTransaction& lt);
    virtual void	abortLongTransaction(AcDbLongTransaction& lt);

	bool			showDetails() const;
	void			setShowDetails(bool showThem);

private:
		// data members
	bool	m_showDetails;

	void	printReactorMessage(AcDbLongTransaction& lt, LPCTSTR event) const;

        // outlawed functions
									ArxRleLongTransactionReactor(const ArxRleLongTransactionReactor &copy);
    ArxRleLongTransactionReactor&	operator=(const ArxRleLongTransactionReactor &copy);        

};

#endif  // ARXRLELONGTRANSACTIONREACTOR_H
