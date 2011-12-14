// HYResources.cpp : Defines the entry point for the DLL application.
//
#include "HYResources.h"
#include <shlwapi.h>
#include <fstream>

#pragma comment(lib,"shlwapi.lib")
namespace Cabinet
{
	// declaration of static class pointer
CCompress* CCompress::mp_This = NULL;

}


//Express callback
BOOL  OnBeforeCopyFile(CExtract::kCabinetFileInfo *pk_Info, void* p_Param)
{
	if(stricmp((char*)p_Param,"")== 0)
		return TRUE;
	else if(stricmp((char*)p_Param,"ER")== 0
		&&wcsicmp(pk_Info->u16_RelPath,L"hyresources.xml") == 0)
	{
		return TRUE;	
	}		
	else
		return FALSE;
}

DWORD ConvertUTF8ToGBK(CHAR *strUTF8)
{
	int len=MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL,0); 
	WCHAR * wszGBK = new WCHAR [sizeof(WCHAR) * (len+1)] ; // new unsigned short[len+1]; 
	memset(wszGBK, 0, sizeof(WCHAR) * (len+1)); 
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len); 
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL); 
	WideCharToMultiByte (CP_ACP, 0, wszGBK, -1, strUTF8, len, NULL,NULL); 
	delete [] wszGBK; 
	
	return len;
}

char *MemStr(const char *pBuf,			//源空间
			 const char *cpStr,			//要查找的字串
			 DWORD dwLen,				//源空间长度
			 BOOL bCase					//是否区分大小写
			 )
{
	char * cpReturn=NULL;
	char * cpReturn2=NULL;
	char cHead2=0;
	
	const char * cpSub;
	int dwNextLen;
	int iStrLen;
	
	cpSub = pBuf;
	dwNextLen = dwLen;
	iStrLen = strlen(cpStr);
	while(TRUE){
		cpReturn=(char *)memchr(cpSub,*cpStr,dwNextLen);
		//added by David Lu (lzw) 2005.11.2
		cpReturn2=NULL;
		if (!bCase){
			if (0 != cHead2)
				cpReturn2=(char *)memchr(cpSub,cHead2,dwNextLen);
		}
		
		//modified by David Lu (lzw) 2005.11.2
		if ((NULL == cpReturn) && (NULL == cpReturn2))
			break;
		if ((NULL != cpReturn2) && ((cpReturn2 < cpReturn) || (NULL == cpReturn)))
			cpReturn = cpReturn2;
		
		if (dwNextLen - (cpReturn - cpSub) < iStrLen){
			cpReturn = NULL;
			break;
		}
		if (bCase){
			if (strncmp(cpReturn,cpStr,iStrLen)==0)
				break;
		}else{
			if (strnicmp(cpReturn,cpStr,iStrLen)==0)
				break;
		}
		dwNextLen -= cpReturn - cpSub + 1;
		if (dwNextLen == 0){
			cpReturn = NULL;
			break;
		}
		cpSub = cpReturn+1;
	}
	return cpReturn;
}


///////////////////////////////////////////////////////////
//功能: 判断是否为有效的虎御CAB文件
///////////////////////////////////////////////////////////
BOOL IsValidCab(char* szCabFilePath,char *pKey = NULL)
{
	if(szCabFilePath == NULL)
		return FALSE;
	CExtract i_ExtrFile;
	if(pKey != NULL)
	{
		i_ExtrFile.SetDecryptionKey(pKey, (DWORD)strlen(pKey));
	}
	else
	{
#ifdef	ENCRYPE_VERSION
		i_ExtrFile.SetDecryptionKey("HYResources", (DWORD)strlen("HYResources"));
#endif
	}

	if (!i_ExtrFile.CreateFDIContext())
	{
		OutputDebugString("Extract ERROR: Could not create FDI context");
		return FALSE;
	}
	
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szCabFilePath, -1, NULL, 0 );
	wchar_t* szCabFilePathW = new wchar_t[nLen+1];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szCabFilePath, -1, szCabFilePathW, nLen );
	
	if(!i_ExtrFile.IsCabinetW(szCabFilePathW, NULL))
	{
		OutputDebugString("Extract Error: The file is not a valid Cabinet!");
		return FALSE;
	}
	delete [] szCabFilePathW;
	return TRUE;
}

///////////////////////////////////////////////////////////
//功能: 压缩指定文件或文件夹
///////////////////////////////////////////////////////////
DWORD  Compress(char* szInFilePath,char* szOutCabPath,char* pkey)
{
	CCompress        i_Compress;
	//压缩后的文件cab路径
	if(szOutCabPath == NULL)
	{
		OutputDebugString("Compress ERROR: Output file name can not be NULL!");
		return 2;
	}
	//设置加密KEY
	if(pkey != NULL)
	{
		i_Compress.SetEncryptionKey(pkey, (DWORD)strlen(pkey));
	}
	else
	{
#ifdef	ENCRYPE_VERSION
		i_Compress.SetEncryptionKey("HYResources", (DWORD)strlen("HYResources"));
#endif
	}
	
	//单字符串转换为宽字符串 szOutCabPath
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szOutCabPath, -1, NULL, 0 );
	wchar_t* szOutCabPathW = new wchar_t[nLen+1];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szOutCabPath, -1, szOutCabPathW, nLen );
	//初始化
	if(!i_Compress.CreateFCIContextW(szOutCabPathW))
	{
		OutputDebugString("Compress ERROR: Could not create FCI context!");
		return 3;
	}
	//单字符串转换为宽字符串 szInFilePath
	nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szInFilePath, -1, NULL, 0 );
	wchar_t* szInFilePathW = new wchar_t[nLen+1];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szInFilePath, -1, szInFilePathW, nLen );
	//开始压缩

	//要压缩的文件夹或文件夹
	if(PathIsDirectory(szInFilePath))
	{
		if (!i_Compress.AddFolderW(szInFilePathW))
		{
			OutputDebugString("Compress ERROR:AddFolder fail!\n");
			return 4;
		}
	}
	else
	{
		wchar_t * wpNameInCab= wcsrchr(szInFilePathW,'\\');
		if(wpNameInCab != NULL)
			wpNameInCab++;
		if(!i_Compress.AddFileW(szInFilePathW,wpNameInCab))
		{
			OutputDebugString("Compress ERROR:AddFile fail!\n");
			return 4;
		}
	}
	//释放资源
	if (!i_Compress.DestroyFCIContext())
	{
		OutputDebugString("Compress ERROR: Could not flush Cabinet!\n");
		return 5;
	}
	delete [] szInFilePathW;
	delete [] szOutCabPathW;
	return 0;	
}

///////////////////////////////////////////////////////////
//功能: 解压到指定文件
///////////////////////////////////////////////////////////
DWORD  ExtractToFile(char* szCabFilePath,char *szFileFlag,char *szOutFile,char* pkey)
{
	CExtract         i_ExtrFile;
	CExtract::kCallbacks k_ExtrCallbacks;
	k_ExtrCallbacks.f_OnBeforeCopyFile = &OnBeforeCopyFile;
	
	i_ExtrFile    .SetCallbacks(&k_ExtrCallbacks);
	if(szCabFilePath == NULL || !PathFileExists(szCabFilePath))
	{
		OutputDebugString("Extract Error: cab file not exist!");
		return 1;
	}
	if(pkey != NULL)
	{
		i_ExtrFile.SetDecryptionKey(pkey,(DWORD)strlen(pkey));
	}
	else
	{
#ifdef	ENCRYPE_VERSION
		i_ExtrFile.SetDecryptionKey("HYResources",(DWORD)strlen("HYResources"));
#endif
	}
	if(szFileFlag == NULL)
	{
		OutputDebugString("Extract ERROR: szFileFlag can not be NULL");
		return 2;
	}
	
	if (!i_ExtrFile.CreateFDIContext())
	{
		OutputDebugString("Extract ERROR: Could not create FDI context");
		return 3;
	}

	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szCabFilePath, -1, NULL, 0 );
	wchar_t* szCabFilePathW = new wchar_t[nLen+1];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szCabFilePath, -1, szCabFilePathW, nLen );

	if(!i_ExtrFile.IsCabinetW(szCabFilePathW, NULL))
	{
		OutputDebugString("Extract Error: The file is not a valid Cabinet!");
		return 4;
	}	
	if (!i_ExtrFile.ExtractFileW(szCabFilePathW,L"MEMORY" , szFileFlag))
	{
		OutputDebugString("Extract ERROR: Maybe the key or the FileFlag is wrong!");
		return 5;
	}
	int nFileLen = 0;
	char *pbuf = NULL;
	char *pFile = (char*)i_ExtrFile.mi_ExtractMem.GetData(&nFileLen);   //从内存里面拷贝文件内容
	if(nFileLen == 0 || pFile == NULL)
	{
		OutputDebugString("Extract ERROR: no file is expressed!");
		return 6;
	}
	try
	{
		 pbuf = new char [nFileLen+1];
	}	
	catch(...)
	{
		OutputDebugString("Extract ERROR: express exception");
		delete [] szCabFilePathW;	
		return 7;
	}
	strncpy(pbuf,pFile,nFileLen);
	pbuf[nFileLen] = '\0';
	std::ofstream fp;
	fp.open(szOutFile);
	if(fp.fail())
	{
		OutputDebugString("wsw: open file fail!");
		return 8;
	}
	fp << pbuf;
	fp.close();
	delete [] pbuf;	
	delete [] szCabFilePathW;	
	return 0;
}

///////////////////////////////////////////////////////////
//功能: 解压到指定目录
///////////////////////////////////////////////////////////
DWORD ExtractToDir(char* szCabFilePath,char *szFileFlag,char *szOutDir,char* pkey)
{
	OutputDebugString(szCabFilePath);
	OutputDebugString(szOutDir);
	CExtract         i_ExtrFile;
//	CExtract::kCallbacks k_ExtrCallbacks;
	//k_ExtrCallbacks.f_OnBeforeCopyFile = &OnBeforeCopyFile;
	//k_ExtrCallbacks.f_OnAfterCopyFile  = &OnAfterCopyFile;
	//k_ExtrCallbacks.f_OnCabinetInfo    = &OnCabinetInfo;
	//k_ExtrCallbacks.f_OnNextCabinet    = &OnNextCabinet;
	
//	i_ExtrFile    .SetCallbacks(&k_ExtrCallbacks);
	if(szCabFilePath == NULL || !PathFileExists(szCabFilePath))
	{
		OutputDebugString("Extract Error: cab file not exist!");
		return 1;
	}
	if(pkey != NULL)
	{
		i_ExtrFile.SetDecryptionKey(pkey,(DWORD)strlen(pkey));
	}
	else
	{
//#ifdef	ENCRYPE_VERSION
		i_ExtrFile.SetDecryptionKey("HYResources",(DWORD)strlen("HYResources"));
//#endif
	}
	if (!i_ExtrFile.CreateFDIContext())
	{
		OutputDebugString("Extract ERROR: Could not create FDI context");
		return 3;
	}
	
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szCabFilePath, -1, NULL, 0 );
	wchar_t* szCabFilePathW = new wchar_t[nLen+1];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szCabFilePath, -1, szCabFilePathW, nLen );
	
	if(!i_ExtrFile.IsCabinetW(szCabFilePathW, NULL))
	{
		OutputDebugString("Extract Error: The file is not a valid Cabinet!");
		return 4;
	}
	nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szOutDir, -1, NULL, 0 );
	wchar_t* szOutDirW = new wchar_t[nLen+1];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szOutDir, -1, szOutDirW, nLen );
	
	BOOL bRet = FALSE;
	if(szFileFlag == NULL)
		bRet = i_ExtrFile.ExtractFileW(szCabFilePathW, szOutDirW,NULL);
	else
		bRet = i_ExtrFile.ExtractFileW(szCabFilePathW, szOutDirW,szFileFlag);
	if (!bRet)
	{
		OutputDebugString("Extract ERROR: Maybe the key or the FileFlag is wrong!");
		return 5;
	}
	delete [] szCabFilePathW;
	delete [] szOutDirW;
	return 0;
}

///////////////////////////////////////////////////////////
//功能: 解压到指定流
///////////////////////////////////////////////////////////
DWORD ExtractToStream(char* szCabFilePath,char *szFileFlag,char **szOutStream,char* pkey)
{
	CExtract         i_ExtrFile;
	CExtract::kCallbacks k_ExtrCallbacks;
	k_ExtrCallbacks.f_OnBeforeCopyFile = &OnBeforeCopyFile;
	
	i_ExtrFile    .SetCallbacks(&k_ExtrCallbacks);
	if(szCabFilePath == NULL || !PathFileExists(szCabFilePath))
	{
		OutputDebugString("Extract Error: cab file not exist!");
		return 1;
	}
	if(pkey != NULL)
	{
		i_ExtrFile.SetDecryptionKey(pkey,(DWORD)strlen(pkey));
	}
	else
	{
#ifdef	ENCRYPE_VERSION
		i_ExtrFile.SetDecryptionKey("HYResources",(DWORD)strlen("HYResources"));
#endif
	}
	if(szFileFlag == NULL)
	{
		OutputDebugString("Extract ERROR: szFileFlag can not be NULL");
		return 2;
	}
	if (!i_ExtrFile.CreateFDIContext())
	{
		OutputDebugString("Extract ERROR: Could not create FDI context");
		return 3;
	}
	
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szCabFilePath, -1, NULL, 0 );
	wchar_t* szCabFilePathW = new wchar_t[nLen+1];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szCabFilePath, -1, szCabFilePathW, nLen );
	
	if(!i_ExtrFile.IsCabinetW(szCabFilePathW, NULL))
	{
		OutputDebugString("Extract Error: The file is not a valid Cabinet!");
		return 4;
	}
	if (!i_ExtrFile.ExtractFileW(szCabFilePathW, L"MEMORY", szFileFlag))
	{
		OutputDebugString("Extract ERROR: Maybe the key or the FileFlag is wrong!");
		return 5;
	}
	int nFileLen = 0;
	char *pFile = (char*)i_ExtrFile.mi_ExtractMem.GetData(&nFileLen);
	char* pStream = NULL;
	if(nFileLen == 0 || pFile == NULL)
	{
		OutputDebugString("Extract ERROR: no file is expressed!");
		return 6;
	}
	try
	{
		pStream = new char[nFileLen+1];
	}	
	catch(...)
	{
		OutputDebugString("Extract ERROR: express exception");
		delete [] szCabFilePathW;	
		return 7;
	}
	strncpy(pStream,pFile,nFileLen);	
	pStream[nFileLen] = '\0';
	*szOutStream = pStream;
	delete [] szCabFilePathW;	
	return 0;
}

