//---------------------------------------------------------------------------
// wzQueue.h
// Author       : Park Dong Ro
// LastModify   : 2006.1
// Comment      : 
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef _WZ_QUEUE_H_
#define _WZ_QUEUE_H_
//---------------------------------------------------------------------------

#ifndef _USE_OLD_RW_STL
#define _USE_OLD_RW_STL
#endif

#include <SyncObjs.hpp>
#include <vector>
using namespace std;

//----------------------------------------------------------------------------
template<class _T>
class wzQueue
{

private:
	//typedef vector< _T > VQueue;
    //VQueue *q;
    vector< _T > *q;
    unsigned int lockOwner;
    TCriticalSection *lock;

public:
    //typedef _T value_type;
    //typedef value_type* pointer;
    //typedef const value_type* const_pointer;
    //typedef value_type* iterator;
    //typedef const value_type* const_iterator;

    typedef vector<_T>::pointer     pointer;
    typedef vector<_T>::iterator    iterator;

public:
    typedef vector<_T>::reference   reference;
    //typedef value_type& reference;
    //typedef const value_type& const_reference;


    wzQueue()
    {
	    lock = new TCriticalSection();
	    q = new vector< _T >;
    };

    ~wzQueue(){
        delete q;
        delete lock;
    };

    int size(){ return q->size(); };
    bool empty() const { return q->empty(); };
    reference operator[](int n) { return *q[n]; };
    void clear(){ q->clear(); };
    iterator erase(iterator it) { return q->erase(it); };

    void Lock()
    {
	    lock->Enter();
        lockOwner=GetCurrentThreadId();
    }

    void UnLock()
    {
	    lockOwner=NULL;
	    lock->Leave();
    }

    bool isLock()
    {
        if( GetCurrentThreadId() == lockOwner ) return true;
	    return false;
    }

    /*
	void globalLock();
	void globalUnLock();
    bool isGlobalLock();
	void push( const _T& t );
    bool pop(pointer t);
    */

    void push( const _T& t  )
    {
	    lock->Enter();
	    try{
	    	q->push_back(t);
	    }
        __finally {
		    lock->Leave();
	    }
    };

    bool pop( pointer t)
    {
	    lock->Enter();
        wzQueue<_T>::iterator it;
	    try{
		    it=q->begin();
            if( it != q->end() ) {
                *t = *it;
                q->erase(it);
                return true;
            }
	    }
        __finally {
		    lock->Leave();
	    }
        return false;
    };

    iterator begin(){ return q->begin(); };
    iterator next( iterator it ) {
        if( it != q->end() ) {
            it++;
        }
        return it;
    };

    bool isEnd(iterator it) {
        if( it == q->end() ) return true;
        return false;
    }
};

//----------------------------------------------------------------------------
#endif

