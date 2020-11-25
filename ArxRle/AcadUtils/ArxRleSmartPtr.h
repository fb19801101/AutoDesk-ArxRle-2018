#ifndef ARXRLE_SMARTPTR_H
#define ARXRLE_SMARTPTR_H

#ifdef T
#undef T
#endif


struct ArxRleSmart
{
    typedef int Status;
    enum {
        kDoClose       = 1,
        kDontClose     = 2,
    };
};

template <class T>
/////////////////////////////////////////////////////////////////////////////
// class ArxRleSmartPtr

class ArxRleSmartPtr
{
private:

    struct PtrRep
    {
        PtrRep ( T* p )
        : m_ptr( p ), m_flags( ArxRleSmart::kDoClose ), m_refcount( 1 )
        {  }
        virtual ~PtrRep ()
        {  
            if (NULL != m_ptr && m_flags & ArxRleSmart::kDoClose)
            {
                if (m_ptr->objectId() != 0)
                    m_ptr->close();
                else
                    delete m_ptr;
            }
        }

        T   *m_ptr;
        int  m_flags;
        int  m_refcount;
    };

    PtrRep *m_rep;

public:
    ArxRleSmartPtr  ();

    template<class SP>
    ArxRleSmartPtr  (ArxRleSmartPtr<SP>& p2)
    {
        ArxRleSmartPtr<T> *p = (ArxRleSmartPtr<T>*)&p2;
        if (NULL != T::cast( p->m_rep->m_ptr ))
        {
            m_rep = p->m_rep;
            m_rep->m_refcount++;
        }
        else
            m_rep = new PtrRep( NULL );
    }

    ArxRleSmartPtr  (const T*);
    virtual ~ArxRleSmartPtr ();

    template<class SP>
    const ArxRleSmartPtr<T>& operator=  (const ArxRleSmartPtr<SP>& p2)
    {
        ArxRleSmartPtr<T> *p = (ArxRleSmartPtr<T>*)&p2;
        if (m_rep != p->m_rep)
        {
            if (0 == --m_rep->m_refcount)
                delete m_rep;
            
            if (NULL != T::cast( p->m_rep->m_ptr ))
            {
                m_rep = p->m_rep;
                m_rep->m_refcount++;
            }
            else
                m_rep = new PtrRep( NULL );
        }
        return *this;
    }

    T*                 operator=  (const T*);
    T*&                operator*  ();
    T* const &         operator*  ()      const;
    T*                 operator-> ();
    const T*           operator-> ()      const;

    operator       T* ();
    operator const T* () const;

    void setFlags   (ArxRleSmart::Status);
};


/****************************************************************************
    ArxRleSmartPtr::ArxRleSmartPtr();
        default to NULL
    
    ArxRleSmartPtr::ArxRleSmartPtr( const ArxRleSmartPtr<T> &p2 );
        copy constructor
    
    ArxRleSmartPtr::ArxRleSmartPtr( const T *p );
        initialized with address

    ArxRleSmartPtr::~ArxRleSmartPtr();
        destructor closes object
    
    const ArxRleSmartPtr<T>& ArxRleSmartPtr::operator=( const ArxRleSmartPtr<T> &p );
    
    T* ArxRleSmartPtr::operator=( const T *p );
        assigned an address
    
    T*& ArxRleSmartPtr::operator*();
        unary * (indirection)
    
    const T*& ArxRleSmartPtr::operator*() const;
        unary * (indirection)

    ArxRleSmartPtr::operator T*();
        conversion to T*
    
    ArxRleSmartPtr::operator const T*() const;
        conversion to T*

  T* ArxRleSmartPtr::operator->();
        -> operator (indirection)
    
    const T* ArxRleSmartPtr::operator->() const;
        -> operator (indirection)
****************************************************************************/


/////////////////////////////////////////////////////////////////////////////
// ArxRleSmartPtr Inline functions

template <class T>
inline ArxRleSmartPtr<T>::ArxRleSmartPtr()
{
    m_rep = new PtrRep( NULL );
    assert( NULL != m_rep );
}

template <class T>
inline ArxRleSmartPtr<T>::ArxRleSmartPtr(const T *p)
{
    m_rep = new PtrRep( (T*)p );
    ASSERT( NULL != m_rep );
}

template <class T>
T* ArxRleSmartPtr<T>::operator=(const T *p)
{
    if (m_rep->m_ptr == p)
        return m_rep->m_ptr;

    if (0 == --m_rep->m_refcount)
        delete m_rep;
    
    m_rep = new PtrRep( (T*)p );
    ASSERT( NULL != m_rep );
    
    return m_rep->m_ptr;
}

template <class T>
inline T*& ArxRleSmartPtr<T>::operator*()
{  return m_rep->m_ptr;  }

template <class T>
inline T* const & ArxRleSmartPtr<T>::operator*() const
{  return m_rep->m_ptr;  }

template <class T>
inline ArxRleSmartPtr<T>::operator T*()
{  return m_rep->m_ptr;  }

template <class T>
inline ArxRleSmartPtr<T>::operator const T*() const
{  return m_rep->m_ptr;  }

template <class T>
T* ArxRleSmartPtr<T>::operator->()
{
    ASSERT( NULL != m_rep->m_ptr );
    return m_rep->m_ptr;
}

template <class T>
const T* ArxRleSmartPtr<T>::operator->() const
{
    ASSERT( NULL != m_rep->m_ptr );
    return m_rep->m_ptr;
}

template <class T>
ArxRleSmartPtr<T>::~ArxRleSmartPtr()
{
    if (0 == --m_rep->m_refcount)
        delete m_rep;
}

template <class T>
void ArxRleSmartPtr<T>::setFlags( ArxRleSmart::Status s )
{
    switch (s) {
    case ArxRleSmart::kDoClose:
        m_rep->m_flags |= ArxRleSmart::kDoClose;
        break;
    case ArxRleSmart::kDontClose:
        m_rep->m_flags &= ~ArxRleSmart::kDoClose;
        break;
    default:
        ASSERT( 1 == 0 );
        break;
    }
}

#endif  // ARXRLE_SMARTPTR_H
