// sloDiskManager.h: interface for the sloDiskManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLODISKMANAGER_H__41512EA4_15D5_42CA_9737_A198219366D6__INCLUDED_)
#define AFX_SLODISKMANAGER_H__41512EA4_15D5_42CA_9737_A198219366D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sloDiskManager  
{
public:
	sloDiskManager();
	virtual ~sloDiskManager();

	char GetMaxFreeSpaceDisk();
protected:
	//disk
	void FindAllDrivers();
	void GetDrvSpaceInfo(char* pDisk);
public:
	char m_cMaxDriver;
	ULARGE_INTEGER m_uMaxFreeSpace;
};

#endif // !defined(AFX_SLODISKMANAGER_H__41512EA4_15D5_42CA_9737_A198219366D6__INCLUDED_)
