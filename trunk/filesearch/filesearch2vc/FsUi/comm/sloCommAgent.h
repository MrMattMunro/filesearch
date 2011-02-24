// sloCommAgent.h: interface for the sloCommAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOCOMMAGENT_H__DC6A156B_963F_4AAB_9116_E934A742DE58__INCLUDED_)
#define AFX_SLOCOMMAGENT_H__DC6A156B_963F_4AAB_9116_E934A742DE58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sloCommAgent  
{
public:
	sloCommAgent();
	virtual ~sloCommAgent();
	
	static char* GetCurTime();
	static BOOL DoFileDialog(char *szPath, LPCTSTR lpszFilter );
};

#endif // !defined(AFX_SLOCOMMAGENT_H__DC6A156B_963F_4AAB_9116_E934A742DE58__INCLUDED_)
