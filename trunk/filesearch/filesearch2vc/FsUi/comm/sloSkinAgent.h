// sloSkinAgent.h: interface for the sloSkinAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOSKINAGENT_H__C3DDDE06_6824_4E85_8A4D_31EE5E7E4319__INCLUDED_)
#define AFX_SLOSKINAGENT_H__C3DDDE06_6824_4E85_8A4D_31EE5E7E4319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sloSkinAgent  
{
public:
	sloSkinAgent();
	virtual ~sloSkinAgent();
	
	void InitSkin();
	void UpdateSkin(char* lpSkinName);
	std::string GetVersion();

protected:
	BOOL GetSkinPath();
	BOOL InitSkinProp();
public:
	char m_szSkinPath[MAX_PATH];
	char m_szSkinName[MAX_PATH*2];
	char m_szSkinProPath[MAX_PATH];
	char m_szVerProPath[MAX_PATH];

	std::vector<Skin_Prop> m_skinPropList;
};

#endif // !defined(AFX_SLOSKINAGENT_H__C3DDDE06_6824_4E85_8A4D_31EE5E7E4319__INCLUDED_)
