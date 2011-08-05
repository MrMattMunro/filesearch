// sloFilterAgent.h: interface for the sloFilterAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOFILTERAGENT_H__0E1985DA_A484_41DE_AD41_97CB551A74A8__INCLUDED_)
#define AFX_SLOFILTERAGENT_H__0E1985DA_A484_41DE_AD41_97CB551A74A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _Ext_Filters
{
	std::string strType;
	std::string strExts;
}Ext_Filters, *LPExt_Filters;

class sloFilterAgent  
{
public:
	sloFilterAgent();
	virtual ~sloFilterAgent();

	void Init();

	std::string GetExtsFromTypes(char* szTypes);
	std::string GetAllExts();
	std::string GetFileTypeFromExt(char* szExt);

protected:
	void GetExtsFromFile(char* szKeyName, char* szType);
	void GetExcludesFromFile(char* szKeyName);

	BOOL GetProFilePath();

public:
	char m_szExcludes[4096];

private:
	BOOL m_bInit;
	std::vector<Ext_Filters> m_exts;
	char m_szpropertiesPath[MAX_PATH];

};

#endif // !defined(AFX_SLOFILTERAGENT_H__0E1985DA_A484_41DE_AD41_97CB551A74A8__INCLUDED_)
