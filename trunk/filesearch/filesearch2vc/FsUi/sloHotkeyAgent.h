// sloHotkeyAgent.h: interface for the sloHotkeyAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOHOTKEYAGENT_H__CF445E51_5C39_46AE_980D_79FB67CFB092__INCLUDED_)
#define AFX_SLOHOTKEYAGENT_H__CF445E51_5C39_46AE_980D_79FB67CFB092__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sloHotkeyAgent  
{
public:
	sloHotkeyAgent();
	virtual ~sloHotkeyAgent();

	BOOL SaveHotkey(char* pKeyName, WORD vk1, WORD sk1);
	BOOL SetHotkey(char* pKeyName, WORD vk1, WORD sk1);
	BOOL GetHotkey(char* pKeyName, WORD& vk1, WORD& sk1);
public:
	BOOL GetProFilePath();
	
	char m_szpropertiesPath[MAX_PATH];

};

#endif // !defined(AFX_SLOHOTKEYAGENT_H__CF445E51_5C39_46AE_980D_79FB67CFB092__INCLUDED_)
