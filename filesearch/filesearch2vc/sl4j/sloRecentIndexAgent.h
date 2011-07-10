// sloRecentIndexAgent.h: interface for the sloRecentIndexAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLORECENTINDEXAGENT_H__326AA1C0_8294_48B0_AD87_ED60570BE66F__INCLUDED_)
#define AFX_SLORECENTINDEXAGENT_H__326AA1C0_8294_48B0_AD87_ED60570BE66F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sloRecentIndexAgent  
{
public:
	sloRecentIndexAgent();
	virtual ~sloRecentIndexAgent();
	DWORD CreateRecIndexPath();

protected:
	BOOL GetProFilePath();

	char m_szpropertiesPath[MAX_PATH];
};

#endif // !defined(AFX_SLORECENTINDEXAGENT_H__326AA1C0_8294_48B0_AD87_ED60570BE66F__INCLUDED_)
