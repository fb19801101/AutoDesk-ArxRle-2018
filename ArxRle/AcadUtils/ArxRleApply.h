class SymbolTable
{
public:
    typedef AcDbSymbolTable         Container;
    typedef AcDbSymbolTableRecord   Element;
    typedef AcDbSymbolTableIterator Iterator;
};

class BlockTable
{
public:
	typedef AcDbBlockTable         Container;
	typedef AcDbBlockTableRecord   Element;
	typedef AcDbBlockTableIterator Iterator;
};

class BlockTableRecord
{
public:
    typedef AcDbBlockTableRecord         Container;
    typedef AcDbEntity                   Element;
    typedef AcDbBlockTableRecordIterator Iterator;
};

class LayerTable
{
public:
    typedef AcDbLayerTable         Container;
    typedef AcDbLayerTableRecord   Element;
    typedef AcDbLayerTableIterator Iterator;
};

class Dictionary
{
public:
    typedef AcDbDictionary         Container;
    typedef AcDbObject             Element;
    typedef AcDbDictionaryIterator Iterator;
};

class GroupDictionary
{
public:
	typedef AcDbDictionary         Container;
	typedef AcDbGroup              Element;
	typedef AcDbDictionaryIterator Iterator;
};

class Group
{
public:
	typedef AcDbGroup               Container;
	typedef AcDbEntity              Element;
	typedef AcDbGroupIterator       Iterator;
};

class TextStyleTable
{
public:
    typedef AcDbTextStyleTable         Container;
    typedef AcDbTextStyleTableRecord   Element;
    typedef AcDbTextStyleTableIterator Iterator;
};

class LinetypeTable
{
public:
    typedef AcDbLinetypeTable         Container;
    typedef AcDbLinetypeTableRecord   Element;
    typedef AcDbLinetypeTableIterator Iterator;
};

class ViewTable
{
public:
    typedef AcDbViewTable         Container;
    typedef AcDbViewTableRecord   Element;
    typedef AcDbViewTableIterator Iterator;
};

class RegAppTable
{
public:
    typedef AcDbRegAppTable         Container;
    typedef AcDbRegAppTableRecord   Element;
    typedef AcDbRegAppTableIterator Iterator;
};

class UCSTable
{
public:
    typedef AcDbUCSTable         Container;
    typedef AcDbUCSTableRecord   Element;
    typedef AcDbUCSTableIterator Iterator;
};

class ViewportTable
{
public:
    typedef AcDbViewportTable         Container;
    typedef AcDbViewportTableRecord   Element;
    typedef AcDbViewportTableIterator Iterator;
};

class DimStyleTable
{
public:
    typedef AcDbDimStyleTable         Container;
    typedef AcDbDimStyleTableRecord   Element;
    typedef AcDbDimStyleTableIterator Iterator;
};


//////////////////////////////////////////////////////////////////////////////

template <class T>
class ArxRleApply
{
public:
	typedef typename T::Element   *ElementPtr;
	typedef typename T::Container *ContainerPtr;
	typedef typename T::Iterator  *IteratorPtr;

	ArxRleApply( ContainerPtr, AcDb::OpenMode );
    typedef Adesk::Boolean ( *ApplyFunc )( ElementPtr );
	ArxRleApply( ContainerPtr, ApplyFunc, AcDb::OpenMode );
	virtual ~ArxRleApply ( );

    void        createIterator  ( IteratorPtr& );
    void        stepIterator    ( IteratorPtr& );
    ElementPtr  getElement      ( IteratorPtr& );

private:
    ContainerPtr   m_cont;
    AcDb::OpenMode m_mode;
};

//////////////////////////////////////////////////////////////////////////////

template<class T>
ArxRleApply<T>::ArxRleApply( ContainerPtr cont, AcDb::OpenMode mode )
: m_cont( cont ), m_mode( mode )
{

}

template<class T>
ArxRleApply<T>::ArxRleApply( ContainerPtr cont, ApplyFunc func, AcDb::OpenMode mode )
	: m_cont( cont ), m_mode( mode )
{
	IteratorPtr iter;
	createIterator( iter );
	if (NULL == iter)
		return;

	for ( ; !iter->done(); stepIterator( iter ))
	{
		ElementPtr elem = getElement( iter );
		if (NULL != elem)
		{
			Adesk::Boolean ret = func( elem );
			elem->close();
			if (!ret)
				break;
		}
	}
	delete iter;
}

template<class T>
ArxRleApply<T>::~ArxRleApply( )
{
	m_cont->close();
}

template<> inline
void ArxRleApply<Dictionary>::createIterator( AcDbDictionaryIterator*& iter )
{
    iter = m_cont->newIterator();
}

template<> inline
void ArxRleApply<Group>::createIterator( AcDbGroupIterator*& iter )
{
	iter = m_cont->newIterator();
}

template<class T>
void ArxRleApply<T>::createIterator( IteratorPtr& iter )
{
    if (Acad::eOk != m_cont->newIterator( iter ))
        iter = NULL;
}

template<> inline
void ArxRleApply<Dictionary>::stepIterator( AcDbDictionaryIterator*& iter )
{
    iter->next();
}

template<> inline
void ArxRleApply<Group>::stepIterator( AcDbGroupIterator*& iter )
{
	iter->next();
}

template<class T>
void ArxRleApply<T>::stepIterator( IteratorPtr& iter )
{
    iter->step();
}

template<> inline
ArxRleApply<BlockTableRecord>::ElementPtr
ArxRleApply<BlockTableRecord>::getElement( AcDbBlockTableRecordIterator *&iter )
{
    ElementPtr elem;
	Acad::ErrorStatus es = iter->getEntity( elem, AcDb::kForWrite);
    if (es == Acad::eOk)
        return elem;
	else if (es == Acad::eOnLockedLayer)
	{
		iter->getEntity( elem, AcDb::kForRead);
		AcDbObjectId entId = elem->objectId();
		if(elem->layerId().isValid())
		{
			AcDbObject* obj;
			acdbOpenAcDbObject(obj, elem->layerId(), AcDb::kForWrite);
			AcDbLayerTableRecord* pRcd = AcDbLayerTableRecord::cast(obj);
			pRcd->setIsLocked(0);
			pRcd->close();
			elem->close();
		}

		es = acdbOpenAcDbEntity(elem, entId, AcDb::kForWrite, true);
		if(es == Acad::eOk) return elem;
	}

    return NULL;
}

template<> inline
ArxRleApply<Dictionary>::ElementPtr
ArxRleApply<Dictionary>::getElement( AcDbDictionaryIterator *&iter)
{
    ElementPtr elem;
    if (Acad::eOk == iter->getObject( elem, m_mode ))
        return elem;
    return NULL;
}

template<> inline
ArxRleApply<Group>::ElementPtr
ArxRleApply<Group>::getElement( AcDbGroupIterator *&iter)
{
	ElementPtr elem;
	if (Acad::eOk == iter->getObject((AcDbObject*&)elem, m_mode ))
	{
		AcDbObjectId id = elem->objectId();
		elem->close();
		Acad::ErrorStatus es = acdbOpenAcDbEntity(elem, id, AcDb::kForWrite, true);
		if(es == Acad::eOk) return elem;
	}
	return NULL;
}

template<class T>
typename ArxRleApply<T>::ElementPtr
ArxRleApply<T>::getElement( IteratorPtr& iter )
{
    ElementPtr elem;
    if (Acad::eOk == iter->getRecord( elem, m_mode ))
        return elem;
    return NULL;
}