// sloFileOpenAddin.cpp: implementation of the sloFileOpenAddin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "officesearch.h"
#include "sloFileOpenAddin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloFileOpenAddin::sloFileOpenAddin()
{

}

sloFileOpenAddin::~sloFileOpenAddin()
{

}

/*
返回值：
     0 成功
*/
DWORD sloFileOpenAddin::OpenFile_WORD(char* pFileName, int nPage, char* pKeyWords /*= NULL*/)
{
	log.Print(LL_DEBUG_INFO, "[info]OpenFile_WORD enter!pFileName=%s, nPage=%d, pKeyWords=%s\r\n", pFileName, nPage, pKeyWords);
	DWORD dwRet = 0;
	do 
	{
		try
		{
			CoInitialize(NULL);
			
			HRESULT hr = S_OK;
			//创建word实例
			Word::_ApplicationPtr spWordApp = NULL;
			{
				hr = spWordApp.CreateInstance(L"Word.Application");
			}
			if (FAILED(hr))
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_WORD CreateInstance failed!GetLastError=0x%x\r\n", GetLastError());

				dwRet = -1;
				break;
			}
			spWordApp->put_Visible(VARIANT_TRUE);
			
			//打开word文档
			CComPtr<Word::_Document> document;
			CComPtr<Documents> spDocs = NULL;
			spWordApp->get_Documents(&spDocs);
			if (spDocs == NULL)
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_WORD get_Documents failed!GetLastError=0x%x\r\n", GetLastError());

				dwRet = -2;
				break;
			}
			
			CComVariant filename(pFileName);
			document = spDocs->Open(&filename, &vtMissing, &vtMissing, &CComVariant(VARIANT_TRUE));
			if (document == NULL)
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_WORD open document failed!GetLastError=0x%x\r\n", GetLastError());

				dwRet = -3;
				break;
			}

			//光标执行第几页
			CComPtr<Word::Selection> sel;
			spWordApp->get_Selection(&sel);
			
			CComVariant vName(nPage);
			CComVariant count(1);
			CComVariant What(wdGoToPage);
			CComVariant Which(wdGoToNext);
			CComPtr<Word::Range> range;
			range = sel->GoTo(&What, &Which, &count, &vName);
			
			//没有关键字查找功能
			if (!pKeyWords)
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_WORD pKeyWords null!GetLastError=0x%x\r\n", GetLastError());

				dwRet = 0;
				break;
			}
/*
			//查找功能
			VARIANT pagecount;
			sel->get_Information(wdNumberOfPagesInDocument, &pagecount);
			int nPagecount = pagecount.lVal;
			
			CComPtr<Word::Find> find;
			sel->get_Find(&find);
			find->ClearFormatting();
			
			CComVariant vFindText(pKeyWords), vForward(VARIANT_TRUE);
			CComVariant   Warp(_T( "wdFindContinue "));
			hr = find->Execute( &vFindText, 
				&vtMissing, 
				&vtMissing, 
				&vtMissing, 
				&vtMissing, 
				&vtMissing, 
				&vForward, 
				&Warp,
				&vtMissing,
				&vtMissing,
				&vtMissing,
				&vtMissing, 
				&vtMissing, 
				&vtMissing,
				&vtMissing);
*/
		}
		catch (...)
		{
			log.Print(LL_DEBUG_INFO, "[error]exception in OpenFile_WORD!GetLastError=0x%x\r\n", GetLastError());
			dwRet = -1;
			break;
		}
	} while (0);
	
	CoUninitialize();

	log.Print(LL_DEBUG_INFO, "[info]OpenFile_WORD leave!pFileName=%s, nPage=%d, pKeyWords=%s\r\n", pFileName, nPage, pKeyWords);

	return dwRet;
	
}

DWORD sloFileOpenAddin::OpenFile_EXCEL(char* pFileName, char* pSheet, int nRow, char* pKeyWords/* = NULL*/)
{
	log.Print(LL_DEBUG_INFO, "[info]OpenFile_EXCEL enter!pFileName=%s,pSheet=%s, nRow=%d, pKeyWords=%s\r\n", 
		pFileName, pSheet , nRow, pKeyWords);

	DWORD dwRet = 0;
	do 
	{
		try
		{
			CoInitialize(NULL);
			
			//创建excel实例
			Excel::_ApplicationPtr spExcelApp;
			HRESULT hr = spExcelApp.CreateInstance(L"Excel.Application");
			if (FAILED(hr))
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_EXCEL CreateInstance failed!GetLastError=0x%x\r\n", GetLastError());
				dwRet = -1;
				break;
			}
			
			spExcelApp->put_Visible(0, VARIANT_TRUE);
			
			//打开excel文档
			CComPtr<Excel::Workbooks> spWorkbooks = NULL;
			spExcelApp->get_Workbooks(&spWorkbooks);
			if (spWorkbooks == NULL)
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_EXCEL get_Workbooks failed!GetLastError=0x%x\r\n", GetLastError());

				dwRet = -2;
				break;
			}
			
			CComPtr<Excel::_Workbook> m_spWb;
			m_spWb = spWorkbooks->Open(pFileName);
			if (m_spWb == NULL)
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_EXCEL Open failed!GetLastError=0x%x\r\n", GetLastError());

				dwRet = -3;
				break;
			}
			
			//定位
			char szSheet[MAX_PATH] = {0};
			sprintf(szSheet, "%s!R%dC1", pSheet, nRow);
			CComVariant vsheet(szSheet);
			spExcelApp->Goto(&vsheet, &vtMissing, 0);
			
			//没有关键字查找功能
			if (!pKeyWords)
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_EXCEL pKeyWords null!GetLastError=0x%x\r\n", GetLastError());

				break;
			}

			//查找关键字 
			CComVariant What(pKeyWords), LookIn(xlFormulas), LookAt(xlPart), SearchOrder(xlByRows);
			CComPtr<Excel::Range> range;
			range = spExcelApp->GetCells()->Find(&What, 
				&vtMissing, 
				&LookIn,
				&LookAt, 
				&SearchOrder, 
				xlNext, 
				&vtMissing, 
				&vtMissing,	
				&vtMissing);

// 			if(range)
// 				range->Activate();

		}
		catch (...)
		{
			log.Print(LL_DEBUG_INFO, "[error]exception in OpenFile_EXCEL!GetLastError=0x%x\r\n", GetLastError());

			dwRet = -1;
			break;	
		}
	} while (0);
	
	CoUninitialize();
	log.Print(LL_DEBUG_INFO, "[info]OpenFile_EXCEL leave!pFileName=%s,pSheet=%s, nRow=%d, pKeyWords=%s\r\n", 
		pFileName, pSheet , nRow, pKeyWords);
	return dwRet;

}

DWORD sloFileOpenAddin::OpenFile_PPT(char* pFileName, int nPage, char* pKeyWords/* = NULL*/)
{
	log.Print(LL_DEBUG_INFO, "[info]OpenFile_PPT enter!pFileName=%s, nPage=%d, pKeyWords=%s\r\n", pFileName, nPage, pKeyWords);

	DWORD dwRet = 0;
	do 
	{
		try
		{
			CoInitialize(NULL);
			PPT::_ApplicationPtr spPPTApp;
			HRESULT hr = spPPTApp.CreateInstance(L"PowerPoint.Application");
			if (FAILED(hr))
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_PPT CreateInstance failed!GetLastError=0x%x\r\n", GetLastError());

				dwRet = -1;
				break;
			}
			
			spPPTApp->put_Visible(msoTrue);
			
			spPPTApp->Activate();
			
			CComPtr<Presentations> spPresents = NULL;
			spPPTApp->get_Presentations(&spPresents);
			if (spPresents == NULL)
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_PPT get_Presentations failed!GetLastError=0x%x\r\n", GetLastError());

				dwRet = -2;
				break;
			}
			
			CComPtr<PPT::_Presentation> m_spPres;
			m_spPres = spPresents->Open(pFileName, msoFalse, msoFalse, msoTrue);
			if (m_spPres == NULL)
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_PPT Open failed!GetLastError=0x%x\r\n", GetLastError());

				dwRet = -3;
				break;
			}
			
			CComVariant item(nPage);
			m_spPres->GetSlides()->Item(&item)->Select();
			
			//查找内容
			CComPtr<PPT::DocumentWindow> docwin;
			spPPTApp->get_ActiveWindow(&docwin);
			
			CComPtr<PPT::Shapes> shapes;
			docwin->GetSelection()->GetSlideRange()->get_Shapes(&shapes);
			
			CComBSTR strText(pKeyWords);
			int nCount = shapes->GetCount();
			for (int i = 0; i < nCount; i++)
			{
				CComVariant index = i+1;
				CComPtr<PPT::Shape> shape = shapes->Item(&index);
				CComPtr<PPT::TextRange> textrange;
				textrange = shape->GetTextFrame()->GetTextRange()->Find(strText.m_str, 1, msoFalse, msoFalse);
				int nCount = textrange->GetLength();
				int nstart = textrange->GetStart();
				
				if (nCount != 0 && nstart != 1)
				{
					textrange->Select();
					break;
				}
			}
		}
		catch (...)
		{
			log.Print(LL_DEBUG_INFO, "[error]exception in OpenFile_PPT!GetLastError=0x%x\r\n", GetLastError());

			dwRet = -1;
			break;
		}

	} while (0);
	log.Print(LL_DEBUG_INFO, "[info]OpenFile_PPT leave!pFileName=%s, nPage=%d, pKeyWords=%s\r\n", pFileName, nPage, pKeyWords);

	return dwRet;
}

DWORD sloFileOpenAddin::OpenFile_PDF(char* pPdfSoftPath, char* pFileName, int nPage, char* pKeyWords/* = NULL*/)
{
	DWORD dwRet =0 ;
	if (nPage <= 0)
	{
		nPage = 1;
	}
//	ShellExecute(NULL, "open", pFileName, "/a page=3", NULL, SW_SHOW);
	//打开进程参数的文件全路径中，如果含有“ ”（空格），则改路径必须用加上“”
	//解决无法打开文件路径中带有空格的文件
	char szCmd[MAX_PATH*4] = {0};
	sprintf(szCmd, "/a page=%d \"%s\"", nPage, pFileName);
	
	ShellExecute(NULL, "open", pPdfSoftPath, szCmd, "",SW_SHOW );

	return dwRet;
}

DWORD sloFileOpenAddin::OpenFile_TXT(char* pFileName, int nRow, char* pKeyWords/* = NULL*/)
{
	log.Print(LL_DEBUG_INFO, "[info]OpenFile_PPT enter!pFileName=%s, nRow=%d, pKeyWords=%s\r\n", pFileName, nRow, pKeyWords);

	DWORD dwRet =0 ;
	do 
	{
		try
		{
			//去掉路径		
			char szWindowsName[MAX_PATH] = {0};
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(pFileName, NULL, NULL, fname, ext);


			sprintf(szWindowsName, "%s%s - 记事本", fname,ext);

			//检测该文本是否打开
			HWND txtwnd = FindWindow("NotePad", szWindowsName);
			if (txtwnd == NULL)
			{
				//获取记事本路径
				char szNotePadPath[MAX_PATH] = {0};
				char szWinDir[MAX_PATH] = {0};
				GetWindowsDirectory(szWinDir, MAX_PATH);
				sprintf(szNotePadPath, "%s\\notepad.exe", szWinDir);
				//打开该文档
				ShellExecute(NULL, "open", szNotePadPath, pFileName, NULL, SW_SHOW);

				Sleep(200);

				//再次检测该文本是否打开
				txtwnd = FindWindow("NotePad", szWindowsName);
				if (txtwnd == NULL)
				{
					log.Print(LL_DEBUG_INFO, "[error]OpenFile_PPT FindWindow NotePad failed!GetLastError=0x%x\r\n", GetLastError());

					dwRet = -3;
					break;
				}
			}

			//查找edit控件句柄
			HWND hwnd = FindWindowEx(txtwnd, NULL, "Edit", "");
			
			CEdit edit;
			edit.Attach(hwnd);
			
			edit.SetFocus();
			
			int nLine = nRow - 1;
			int nIndex = -1;
			//line转换
			nIndex = edit.LineIndex(nLine);
			if (nIndex == -1)
			{
				log.Print(LL_DEBUG_INFO, "[error]OpenFile_PPT LineIndex failed!nIndex = %d, GetLastError=0x%x\r\n",
					nIndex, GetLastError());

				//行数超过了范围
				dwRet = -2;
				break;
			}
			edit.SetSel(nIndex,nIndex);
				
			edit.Detach();
		}
		catch (...)
		{
			log.Print(LL_DEBUG_INFO, "[error]exception in OpenFile_PPT!GetLastError=0x%x\r\n",GetLastError());
			dwRet = -1;
			break;
		}
	} while (0);

	log.Print(LL_DEBUG_INFO, "[info]OpenFile_PPT leave!pFileName=%s, nRow=%d, pKeyWords=%s\r\n", pFileName, nRow, pKeyWords);

	return dwRet;	
}
