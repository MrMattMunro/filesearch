// sloMysqlAgent.h: interface for the sloMysqlAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOMYSQLAGENT_H__AEF1B6B2_35E4_4E71_82E5_87DC6155159E__INCLUDED_)
#define AFX_SLOMYSQLAGENT_H__AEF1B6B2_35E4_4E71_82E5_87DC6155159E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class sloMysqlAgent  :public mysqlcomm
{
public:
	sloMysqlAgent();
	virtual ~sloMysqlAgent();
	
	static sloMysqlAgent* GetInstance();
	static sloMysqlAgent* m_hinstance;
public:
	BOOL AddDoucmentRecord(DocumentItem docitem);
};

#endif // !defined(AFX_SLOMYSQLAGENT_H__AEF1B6B2_35E4_4E71_82E5_87DC6155159E__INCLUDED_)
