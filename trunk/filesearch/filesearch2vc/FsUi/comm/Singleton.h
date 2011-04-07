
#ifndef SINGLETON_H
#define SINGLETON_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template<typename T>
class Singleton {
public:
	Singleton() { }
	virtual ~Singleton() { }

	static T* getInstance() {
		dcassert(instance);
		return instance;
	}
	
	static void newInstance() {
		if(instance)
			delete instance;
		
		instance = new T();
	}
	
	static void deleteInstance() {
		if(instance)
			delete instance;
		instance = NULL;
	}
protected:
	static T* instance;
private:
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

};

template<class T> T* Singleton<T>::instance = NULL;

#endif // SINGLETON_H
