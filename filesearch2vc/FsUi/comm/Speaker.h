

#ifndef SPEAKER_H
#define SPEAKER_H

#include "CriticalSection.h"

template<typename Listener>
class Speaker 
{ 
	typedef vector<Listener*> ListenerList;
	typedef typename ListenerList::iterator ListenerIter;

public:
	Speaker() throw() { };
	virtual ~Speaker() throw() { };

	template<typename T0>
	void fire(T0 type) throw() 
	{
		Lock l(listenerCS);
		tmp = listeners;
		for(ListenerIter i=tmp.begin(); i != tmp.end(); ++i ) 
		{
			(*i)->on(type);
		}
	}

	template<typename T0, class T1>
	void fire(T0 type, const T1& p1) throw() 
	{
		Lock l(listenerCS);
		tmp = listeners;
		for(ListenerIter i=tmp.begin(); i != tmp.end(); ++i ) 
		{
			(*i)->on(type, p1);
		}
	}

	template<typename T0, class T1, class T2>
	void fire(T0 type, const T1& p1, const T2& p2) throw() 
	{
		Lock l(listenerCS);
		tmp = listeners;
		for(ListenerIter i=tmp.begin(); i != tmp.end(); ++i ) 
		{
			(*i)->on(type, p1, p2);
		}
	}

	template<typename T0, class T1, class T2, class T3>
	void fire(T0 type, const T1& p1, const T2& p2, const T3& p3) throw() 
	{
		Lock l(listenerCS);
		tmp = listeners;
		for(ListenerIter i=tmp.begin(); i != tmp.end(); ++i ) 
		{
			(*i)->on(type, p1, p2, p3);
		}
	}

	template<typename T0, class T1, class T2, class T3, class T4>
	void fire(T0 type, const T1& p1, const T2& p2, const T3& p3, const T4& p4) throw() 
	{
		Lock l(listenerCS);
		tmp = listeners;
		for(ListenerIter i=tmp.begin(); i != tmp.end(); ++i ) 
		{
			(*i)->on(type, p1, p2, p3, p4);
		}
	}

	template<typename T0, class T1, class T2, class T3, class T4, class T5>
	void fire(T0 type, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5) throw() 
	{
		Lock l(listenerCS);
		tmp = listeners;
		for(ListenerIter i=tmp.begin(); i != tmp.end(); ++i ) 
		{
			(*i)->on(type, p1, p2, p3, p4, p5);
		}
	}

	template<typename T0, class T1, class T2, class T3, class T4, class T5, class T6>
	void fire(T0 type, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6) throw() 
	{
		Lock l(listenerCS);
		tmp = listeners;
		for(ListenerIter i=tmp.begin(); i != tmp.end(); ++i ) 
		{
			(*i)->on(type, p1, p2, p3, p4, p5, p6);
		}
	}

	void addListener(Listener* aListener) 
	{
		Lock l(listenerCS);
		if(find(listeners.begin(), listeners.end(), aListener) == listeners.end())
			listeners.push_back(aListener);
	}

	void removeListener(Listener* aListener) {
		Lock l(listenerCS);
		ListenerIter it = find(listeners.begin(), listeners.end(), aListener);
		if(it != listeners.end())
			listeners.erase(it);
	}

	void removeListeners() 
	{
		Lock l(listenerCS);
		listeners.clear();
	}
	
protected:
	ListenerList listeners;
	ListenerList tmp;
	CriticalSection listenerCS;
};

#endif // SPEAKER_H