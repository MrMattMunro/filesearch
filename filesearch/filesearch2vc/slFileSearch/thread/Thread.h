// Thread.h: interface for the Thread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__DBC308DC_FAE8_4448_B3C7_5733F3A6D3AE__INCLUDED_)
#define AFX_THREAD_H__DBC308DC_FAE8_4448_B3C7_5733F3A6D3AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Exception.h"
STANDARD_EXCEPTION(ThreadException);

class Thread  
{
public: 
	enum Priority {
		IDLE = THREAD_PRIORITY_IDLE,
		LOW = THREAD_PRIORITY_BELOW_NORMAL,
		NORMAL = THREAD_PRIORITY_NORMAL,
		HIGH = THREAD_PRIORITY_ABOVE_NORMAL
	};
	
	Thread() throw() : threadHandle(NULL), threadId(0){ };
	virtual ~Thread() 
	{ 
		if(threadHandle)
			CloseHandle(threadHandle);
	};
	
	void start() throw(ThreadException);
	void join() throw(ThreadException) {
		if(threadHandle == NULL) {
			return;
		}
		
		WaitForSingleObject(threadHandle, INFINITE);
		CloseHandle(threadHandle);
		threadHandle = NULL;
	}
	void shutdown() throw(ThreadException)
	{
		if(threadHandle!=NULL)
		{
			TerminateThread(threadHandle, 0);
			CloseHandle(threadHandle);
			threadHandle = NULL;
		}		
	}
	void setThreadPriority(Priority p) throw() { ::SetThreadPriority(threadHandle, p); };
	
	static void sleep(DWORD millis) { ::Sleep(millis); };
	static void yield() { ::Sleep(0); };
	static long safeInc(volatile long& v) { return InterlockedIncrement((LPLONG)&v); };
	static long safeDec(volatile long& v) { return InterlockedDecrement((LPLONG)&v); };
	static long safeExchange(volatile long& target, long value) { return InterlockedExchange((LPLONG)&target, value); };
	
	
protected:
	virtual int run() = 0;
	
private:
	Thread(const Thread&);
	Thread& operator=(const Thread&);
	
	HANDLE threadHandle;
	DWORD threadId;
	static DWORD WINAPI starter(void* p) {
		Thread* t = (Thread*)p;
		t->run();
		return 0;
	}
	
};

#endif // !defined(AFX_THREAD_H__DBC308DC_FAE8_4448_B3C7_5733F3A6D3AE__INCLUDED_)
