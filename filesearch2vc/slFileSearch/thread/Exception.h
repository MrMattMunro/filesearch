
#ifndef TY_EXCEPTION_H
#define TY_EXCEPTION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define dcdebug if(false) printf

class Exception  
{
public:
	Exception() { };
	Exception(const std::string& aError) throw() : error(aError) { if(error.size()>0) dcdebug("Thrown: %s\n", error.c_str()); };
	virtual ~Exception() throw() { };
	virtual const std::string& getError() const throw() { return error; };
protected:
	std::string error;
};

#ifdef _DEBUG

#define STANDARD_EXCEPTION(name) class name : public Exception { \
public:\
	name() throw() : Exception(#name) { } \
	name(const std::string& aError) throw() : Exception(#name ": " + aError) { } \
	virtual ~name() throw() { } \
}

#else // _DEBUG

#define STANDARD_EXCEPTION(name) class name : public Exception { \
public:\
	name() throw() : Exception() { } \
	name(const std::string& aError) throw() : Exception(aError) { } \
	virtual ~name() throw() { } \
}
#endif

#endif // EXCEPTION_H