// ReportRecord.cpp: implementation of the CReportRecord class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LocalAgenter.h"
#include "ReportRecord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportRecord::CReportRecord(CString strName, CString strDate)
{
	//最前面显示的图标
	AddItem(new CXTPReportRecordItem());
	AddItem(new CXTPReportRecordItem());
	
	AddItem(new CXTPReportRecordItem());
	AddItem(new CXTPReportRecordItem());

	AddItem(new CXTPReportRecordItemText(strName));				//学员编号
	AddItem(new CXTPReportRecordItemText(strDate));			//学员姓名	
}

CReportRecord::~CReportRecord()
{

}
