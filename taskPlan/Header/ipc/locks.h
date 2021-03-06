/******************************************************
NTU EECS Advanced Control Lab, Intelligent Robot Lab

2010 Kuo-Chen Huang

******************************************************/
#ifndef LOCKS_HPP
#define LOCKS_HPP

#ifdef WIN32

#include "windows.h"
#include <cassert>

class win32CriticalSection{
public:
	win32CriticalSection(){
		InitializeCriticalSection( &cs );
	}
	~win32CriticalSection(){
		DeleteCriticalSection( &cs );
	}
	void lock(){
		EnterCriticalSection( &cs );	
	}
	void unlock(){
		LeaveCriticalSection( &cs );
	}
private:
	CRITICAL_SECTION cs;
};


// ---------------------------------//
// rw lock for win xp
// pthread-like
// ---------------------------------//

typedef struct _RW_LOCK {
	CRITICAL_SECTION readerCountLock;
	CRITICAL_SECTION writerLock;
	HANDLE noReaders;
	int readerCount;
} RW_LOCK, *PRW_LOCK;

inline void rwlock_init(PRW_LOCK rwlock)
{
	InitializeCriticalSection(&rwlock->readerCountLock);
	InitializeCriticalSection(&rwlock->writerLock);
	rwlock->readerCount = 0;
	rwlock->noReaders = CreateEvent (NULL, TRUE, TRUE, NULL);
}

inline void rwlock_rdlock(PRW_LOCK rwlock)
{
	EnterCriticalSection(&rwlock->writerLock);
	EnterCriticalSection(&rwlock->readerCountLock);
	if (++rwlock->readerCount == 1){
		ResetEvent(rwlock->noReaders);
	}
	LeaveCriticalSection(&rwlock->readerCountLock);
	LeaveCriticalSection(&rwlock->writerLock);
}

inline void rwlock_wrlock(PRW_LOCK rwlock)
{
	EnterCriticalSection(&rwlock->writerLock);
	if (rwlock->readerCount > 0) {
		WaitForSingleObject(rwlock->noReaders, INFINITE);
	}
}

inline void rwlock_rdunlock(PRW_LOCK rwlock)
{
	EnterCriticalSection(&rwlock->readerCountLock);
	assert (rwlock->readerCount > 0);
	if (--rwlock->readerCount == 0) {
		SetEvent(rwlock->noReaders);
	}
	LeaveCriticalSection(&rwlock->readerCountLock);
}

inline void rwlock_wrunlock(PRW_LOCK rwlock)
{
	LeaveCriticalSection(&rwlock->writerLock);
}


#endif

#endif
