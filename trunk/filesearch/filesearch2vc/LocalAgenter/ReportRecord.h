// ReportRecord.h: interface for the CReportRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTRECORD_H__B94A4501_0508_4443_834C_8CD9D2652165__INCLUDED_)
#define AFX_REPORTRECORD_H__B94A4501_0508_4443_834C_8CD9D2652165__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CReportRecord  : public CXTPReportRecord
{
public:
	CReportRecord(CString strName, CString strDate);
	virtual ~CReportRecord();

};

#endif // !defined(AFX_REPORTRECORD_H__B94A4501_0508_4443_834C_8CD9D2652165__INCLUDED_)
