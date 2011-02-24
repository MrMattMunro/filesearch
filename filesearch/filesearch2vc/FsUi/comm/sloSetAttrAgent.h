// sloSetAttrAgent.h: interface for the sloSetAttrAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOSETATTRAGENT_H__6BF5F4B1_F5C3_4341_A9AD_7A0A9145B2CE__INCLUDED_)
#define AFX_SLOSETATTRAGENT_H__6BF5F4B1_F5C3_4341_A9AD_7A0A9145B2CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sloSetAttrAgent  : public mysqlcomm
{
public:
	sloSetAttrAgent();
	virtual ~sloSetAttrAgent();

	int GetSoftPath(char* szFileType, char* szPath);

};

#endif // !defined(AFX_SLOSETATTRAGENT_H__6BF5F4B1_F5C3_4341_A9AD_7A0A9145B2CE__INCLUDED_)
