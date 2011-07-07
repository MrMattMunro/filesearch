
#ifndef TY_EXCEPTION_H
#define TY_EXCEPTION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Exception  
{
public:
	Exception() { };
	Exception(const string& aError) throw() : error(aError) {dcdrun(if(error.size()>0)) dcdebug("Thrown: %s\n", error.c_str()); };
	virtual ~Exception() throw() { };
	virtual const string& getError() const throw() { return error; };
protected:
	string error;
};

#ifdef _DEBUG

#define STANDARD_EXCEPTION(name) class name : public Exception { \
public:\
	name() throw() : Exception(#name) { } \
	name(const string& aError) throw() : Exception(#name ": " + aError) { } \
	virtual ~name() throw() { } \
}

#else // _DEBUG

#define STANDARD_EXCEPTION(name) class name : public Exception { \
public:\
	name() throw() : Exception() { } \
	name(const string& aError) throw() : Exception(aError) { } \
	virtual ~name() throw() { } \
}
#endif

#endif // EXCEPTION_H