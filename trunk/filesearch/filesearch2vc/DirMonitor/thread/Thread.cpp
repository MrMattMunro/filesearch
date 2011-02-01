// Thread1.cpp: implementation of the Thread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Thread.h"  

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void Thread::start() throw(ThreadException) {
	join();
	if( (threadHandle = CreateThread(NULL, 0, &starter, this, 0, &threadId)) == NULL) {
		throw ThreadException("UNABLE_TO_CREATE_THREAD");
	}
}
