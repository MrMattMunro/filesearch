// slXmlAgent.cpp: implementation of the slXmlAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "slXmlAgent.h"
#include "slRegAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

slXmlAgent::slXmlAgent()
{
	m_pxmlfilter = NULL;
	m_nCount = 0;
	m_bInit = FALSE;
}

slXmlAgent::~slXmlAgent()
{
	Clear();
}

void slXmlAgent::Clear()
{
	for (int i = 0; i < m_nCount; i++)
	{
		delete &m_pxmlfilter[i];
	}
	m_nCount = 0;
	m_bInit = FALSE;
}

void slXmlAgent::LoadXML()
{
	if (m_bInit)
		return ;

	Clear();

	m_bInit = TRUE;
	MSXML2::IXMLDOMDocument2Ptr pDoc;         //文档对象

	//初始化端口
	CoInitialize(NULL);	
	
	//创建DOMDocument对象
	HRESULT hr = -1;
	hr = pDoc.CreateInstance(_uuidof(DOMDocument30));
	if(!SUCCEEDED(hr))
	{
		log.Print(LL_DEBUG_INFO,"Error in slXmlAgent::LoadXML!DOMDocument CreateInstance Failed!hr=0x%x,GetLastError=%d\r\n",
			hr, GetLastError());
		return;
	}
	
	//导入XML文件
	if(!pDoc->load(GetXmlPath().c_str()))
	{
		log.Print(LL_DEBUG_INFO,"Error in slXmlAgent::LoadXML!load Failed,File Not Exist!XmlFilePath=%s\r\n",GetXmlPath().c_str());
		return;
	}

	IXMLDOMNodeListPtr ptrNodeList = pDoc->selectNodes("//Searchers/searcher");
	
	CString strSearchPath,strSearchName, strTypes;
	_variant_t variantValue;

	long lCount = ptrNodeList->Getlength();
	m_nCount = lCount;
	m_pxmlfilter = new XmlFilter[lCount];
	memset(m_pxmlfilter, NULL, sizeof(XmlFilter)*lCount);
	for (int i = 0; i < lCount; i++)
	{
		MSXML2::IXMLDOMNodePtr pNode = ptrNodeList->Getitem(i);
		MSXML2::IXMLDOMNodePtr pSearchPathNode = pNode->selectSingleNode("searchpath");
		MSXML2::IXMLDOMNodePtr pSearchNameNode = pNode->selectSingleNode("searchname");
		MSXML2::IXMLDOMNodePtr pTypesNode = pNode->selectSingleNode("types");

		pSearchPathNode->get_nodeTypedValue(&variantValue);				
		strSearchPath =(char *)(_bstr_t)variantValue;	
		
		pSearchNameNode->get_nodeTypedValue(&variantValue);				
		strSearchName =(char *)(_bstr_t)variantValue;	
		
		pTypesNode->get_nodeTypedValue(&variantValue);				
		strTypes =(char *)(_bstr_t)variantValue;

		XmlFilter FilterItem;
		memset(&FilterItem, NULL, sizeof(XmlFilter));
		FilterItem.nIndex = i;
		memcpy(FilterItem.szSearceName, strSearchName.GetBuffer(0), strSearchName.GetLength());
		memcpy(FilterItem.szSearchPath, strSearchPath.GetBuffer(0), strSearchPath.GetLength());
		memcpy(FilterItem.szSearchType, strTypes.GetBuffer(0), strTypes.GetLength());
		memcpy(&m_pxmlfilter[i], &FilterItem, sizeof(XmlFilter));
		log.Print(LL_DEBUG_INFO,"XmlItem(%d):SearchName=%s,SearchPath=%s,SearchType=%s\r\n",
			i+1,FilterItem.szSearceName,FilterItem.szSearchPath,FilterItem.szSearchType);
	}

	return;
}

//////////////////////////////////////////////////////////////////////////
//-1 连接数据库失败
//-2 执行sql语句失败
//-3 查询记录为空
//
int slXmlAgent::LoadDB()
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		log.Print(LL_DEBUG_INFO, "[Error]Connect Db Failed!DBName=COMMONINFO\r\n");
		return -1;
	}

	std::string strQuerySQL = "select * from t_searcher";
	HRESULT hr = doSqlExe(FALSE, strQuerySQL.c_str() );
	if (FAILED(hr))
	{
		log.Print(LL_DEBUG_INFO, "[Error]Exe sql(%s) failed!\r\n",strQuerySQL.c_str());
		return -2;
	}
	
	int nCount = m_pMySqlDB->GetRowCount();	//记录条数
	int nFieldCount = m_pMySqlDB->GetFieldCount();

	if(nCount >= 1 && nFieldCount >= 1)
	{
		m_nCount = nCount;
		m_pxmlfilter = new XmlFilter[nCount];
		memset(m_pxmlfilter, NULL, sizeof(XmlFilter)*nCount);
		for (int i = 0; i < nCount; i++)
		{
			bool bSucc = m_pMySqlDB->GetRow();
			if(bSucc==false)
			{
				log.Print(LL_DEBUG_INFO, "[Error]GetRow Failed\r\n");
				return -3;
			}
			
			int nIDLen = 0;
			char* pID = m_pMySqlDB->GetField("id",&nIDLen);

			char szSearchName[MAX_PATH] = {0};
			sprintf(szSearchName,"searcher%s",pID);

			int nFileTypeLen = 0;
			char* pFileType = m_pMySqlDB->GetField("filetype",&nFileTypeLen);
			if (nFileTypeLen == 0)
				continue ;	
		
			int nFilePathLen = 0;
			char* pFilePath = m_pMySqlDB->GetField("path",&nFilePathLen);
			if (nFilePathLen == 0)
				continue;
			
			XmlFilter FilterItem;
			memset(&FilterItem, NULL, sizeof(XmlFilter));
			FilterItem.nIndex = i;
			memcpy(FilterItem.szSearceName, szSearchName, strlen(szSearchName));
			memcpy(FilterItem.szSearchPath, pFilePath, nFilePathLen);
			memcpy(FilterItem.szSearchType, pFileType, nFileTypeLen);
			memcpy(&m_pxmlfilter[i], &FilterItem, sizeof(XmlFilter));
			log.Print(LL_DEBUG_INFO,"XmlItem(%d):SearchName=%s,SearchPath=%s,SearchType=%s\r\n",
				i+1,FilterItem.szSearceName,FilterItem.szSearchPath,FilterItem.szSearchType);			
		}
	}else
	{
		log.Print(LL_DEBUG_INFO, "[Error]t_searcher no record\r\n");
		return -3;
	}
	
	return 0;	
}

bool slXmlAgent::Filters(char* pszFullPath)
{
	OutputDebugStringA(pszFullPath);
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	
	_splitpath( pszFullPath, drive, dir, fname, ext );
	if (!strlen(ext))
		return true;

	if(strchr(fname,'~') != NULL)
		return true;

	std::string strType = ext+1;
	if (strType.find("doc") != -1 || strType.find("docx") != -1)
	{
		strType = "word";
	}

	if (strType.find("xls") != -1 || strType.find("xlsx") != -1)
	{
		strType = "excel";
	}
	
    char szPath[MAX_PATH] = {0};
	sprintf(szPath, "%s%s",drive,dir);
	for (int i = 0; i < m_nCount; i++)
	{
		std::string strFullPath = pszFullPath;
		std::string strSearchType = m_pxmlfilter[i].szSearchType;
		if (strFullPath.find(m_pxmlfilter[i].szSearchPath) != -1 && strSearchType.find(strType) != -1)
			return false;
	}

	return false;
	
	return true;
}

string slXmlAgent::GetDbNameFromPath(char* szFileName)
{
	std::string strSearchName;
	char szSearchPath[MAX_PATH] = {0};

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	
	_splitpath( szFileName, drive, dir, fname, ext );
	sprintf(szSearchPath, "%s%s", drive, dir);

	for (int i = 0; i < m_nCount; i++)
	{
		if( strncmp(szSearchPath, m_pxmlfilter[i].szSearchPath, strlen(m_pxmlfilter[i].szSearchPath)) == 0 )
		{
			return strSearchName = m_pxmlfilter[i].szSearceName; 
		}
	}

	return "";

}

#define XML_PATH "tomcat\\webapps\\slfile\\WEB-INF\\classes\\com\\searchlocal\\properties\\searchers.xml"
std::string slXmlAgent::GetXmlPath()
{
	slRegAgent reg;
	char szRegPath[MAX_PATH] = {0};
	BOOL bRet = reg.ReadXmlPath(szRegPath);
	if (bRet == FALSE)
	{
		log.Print(LL_DEBUG_INFO,"ReadXmlPath Fialed!\r\n");
	}
	
	char szXmlPath[MAX_PATH] = {0};
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	
	_splitpath( szRegPath, drive, dir, fname, ext );
	sprintf(szXmlPath,"%s%s%s",drive, dir,XML_PATH);

	log.Print(LL_DEBUG_INFO,"Xml Path %s\r\n",szXmlPath);

	return szXmlPath;
}