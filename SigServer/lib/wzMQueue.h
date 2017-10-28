//---------------------------------------------------------------------------
// wzMQueue.h
// Author       : Park Dong Ro
// LastModify   : 2005.12
// Comment      :
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef _WZ_MQUEUE_H_
#define _WZ_MQUEUE_H_
//---------------------------------------------------------------------------

#ifndef _USE_OLD_RW_STL
#define _USE_OLD_RW_STL
#endif

#include <map>
//#include <hash_map>
#include <syncobjs.hpp>

using namespace std;

template< class _KEY, class _T>
//----------------------------------------------------------------------------
class wzMQueue
{
public:
    //typedef _T value_type;
    //typedef value_type* pointer;
    //typedef const value_type* const_pointer;
    //typedef value_type* iterator;
    //typedef const value_type* const_iterator;

    typedef map< _KEY, _T >::pointer     m_pointer;
    typedef map< _KEY, _T >::iterator    iterator;

private:
    map< _KEY, _T > *q;

	TCriticalSection *lock;
	unsigned int lockOwner;
    int lastKey;
    map< _KEY, _T >::iterator m_it;
    bool navFirstRemove;



public:
    typedef map< _KEY, _T >::reference   m_reference;
    //typedef value_type& reference;
    //typedef const value_type& const_reference;

private:
	 bool isLock() {
        if( GetCurrentThreadId() == lockOwner ) return true;
	    return false;
    };

public:
	
    wzMQueue(){
        lock = new TCriticalSection();
	    q    = new map< _KEY, _T >;
        lastKey     = 1;
        lockOwner   = 0;
    };
    ~wzMQueue(){
        delete q;
        delete lock;
    };

	void Lock() {
	    lock->Acquire();
        lockOwner=GetCurrentThreadId();
    };

    void UnLock() {
	    lockOwner=0;
	    lock->Release();
    };

	void clear() {
        if( !isLock() ) lock->Acquire();
	    q->clear();
	    if( !isLock() ) lock->Release();
    };

	unsigned int size(){ return q->size(); };
	bool empty(){ return q->empty(); };


    iterator begin(){ return q->begin(); };
    iterator next( iterator it )
    {
        if( it != q->end() ) {
            it++;
        }
        return it;
    };

    bool isEnd( iterator it) {
        if( it == q->end() ) return true;
        return false;
    };

    //------------------------------------------------------------
	bool push( const _KEY& key, const _T& e )
    {
        if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try {
    	    (*q)[key]=e;
            lastKey = key;
        }
        __finally{
	        if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
    };

    //------------------------------------------------------------
	int push( const _T& e )
    {
        if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try {
        	if( lastKey >= 30000 ) lastKey =1;
        	else lastKey++;
    	    (*q)[lastKey]=e;
        }
        __finally{
	        if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
        return lastKey;
    };

    //------------------------------------------------------------
    bool exist( const _KEY& key )
    {
        map< _KEY, _T >::iterator it;
        if( (it=q->find(key))  != q->end() ) return true;
	    return false;
    };


    //------------------------------------------------------------
    bool get( const _KEY& key, _T* e )
    {
        bool ret=false;
        map< _KEY, _T >::iterator it;

        if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try
        {
            it=q->find(key);
	        if( it != q->end() )
	        {
		        *e=it->second;
		        ret=true;
	        }
        }
        __finally{
	        if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
	    return ret;
    };

    //------------------------------------------------------------
    _T* get( const _KEY& key )
    {
        map< _KEY, _T >::iterator it;

        if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try
        {
            it=q->find(key);
	        if( it != q->end() )
	        {
		        return &(it->second);
	        }
        }
        __finally{
	        if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
	    return NULL;
    };

    /*
    //------------------------------------------------------------
    _T* getFirst()
    {
        if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try
        {
            m_it=q->begin();
	        if( m_it != q->end() )
	        {
		        return &(m_it->second);
	        }
        }
        __finally{
	        if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
	    return NULL;
    };

    //------------------------------------------------------------
    _T* getNext()
    {
        if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try
        {
            m_it++;
	        if( m_it != q->end() )
	        {
		        return &(m_it->second);
	        }
        }
        __finally{
	        if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
	    return NULL;
    };
    */

    //------------------------------------------------------------
    _T* navFirst()
    {
        navFirstRemove = false;
        m_it=q->begin();
        if( m_it != q->end() )
        {
            return &(m_it->second);
        }
	    return NULL;
    };

    //------------------------------------------------------------
    _T* navNext()
    {
        if( navFirstRemove ) return navFirst();
        m_it++;
        if( m_it != q->end() )
        {
            return &(m_it->second);
        }
	    return NULL;
    };

    void navRemove()
    {
        map< _KEY, _T >::iterator it;
        if( m_it == q->begin() )
        {
            navFirstRemove = true;
            q->erase(m_it);
        }
        else {
            it = m_it;
            m_it--;
            q->erase(it);
        }
    }


    //------------------------------------------------------------
    _T getValueFirst()
    {
        if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try
        {
            m_it=q->begin();
	        if( m_it != q->end() )
	        {
		        return m_it->second;
	        }
        }
        __finally{
	        if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
	    return NULL;
    };

    //------------------------------------------------------------
    _T getValueNext()
    {
        if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try
        {
            m_it++;
	        if( m_it != q->end() )
	        {
		        return m_it->second;
	        }
        }
        __finally{
	        if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
	    return NULL;
    };

    //------------------------------------------------------------
    bool getIndex(int idx, _T* e )
    {
        bool ret=false;
        map< _KEY, _T >::iterator it;
        int size;

        if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        if( (size = q->size()) >= (idx+1) )
        {
            try
            {
                it=q->begin();
                for( int i=0; i<idx; i++) it++;
	            if( it != q->end() )
	            {
		            *e=it->second;
		            ret=true;
	            }
            }
            __finally{
	            if( GetCurrentThreadId() != lockOwner ) lock->Release();
            }
        }
	    return ret;
    };

    //------------------------------------------------------------
    bool pop ( const _KEY& key, _T* e )
    {
        bool ret=false;
        //if( q->empty() ) return ret;
        map< _KEY, _T >::iterator it;

        if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try
        {
            it=q->find(key);
	        if( it != q->end() )
	        {
		        *e=it->second;
		        q->erase(key);
		        ret=true;
	        }
        }
        __finally{
	        if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
	    return ret;
    };

    //------------------------------------------------------------
    bool popFirst ( _T* e )
    {
        bool ret=false;
        //if( q->empty() ) return ret;
        //map< _KEY, _T >::iterator it;
        iterator it;
        if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try
        {
            it=q->begin();
	        if( it != q->end() )
	        {
		        *e=it->second;
		        q->erase(it);
		        ret=true;
	        }
        }
        __finally{
	        if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
	    return ret;
    };

    //------------------------------------------------------------
    bool remove(const _KEY& key)
    {
        bool ret=false;
        map< _KEY, _T >::iterator it;
	    if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try
        {
	        it=q->find(key);
	        if( it != q->end() ){
                q->erase(key);
                ret = true;
            }
        }
        __finally{
            if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
        return ret;
    };

    //------------------------------------------------------------
    void remove(iterator it)
    {
	    if( GetCurrentThreadId() != lockOwner ) lock->Acquire();
        try
        {
	        q->erase(it);
        }
        __finally{
            if( GetCurrentThreadId() != lockOwner ) lock->Release();
        }
    };
};

//----------------------------------------------------------------------------
#endif



