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
// 	for (int i = 0; i < m_nCount; i++)
// 	{
// 		delete &m_pxmlfilter[i];
// 	}

	for (std::vector<XmlFilter>::iterator item = m_searcherList.begin(); item != m_searcherList.end();)
	{
		m_searcherList.erase(item);
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
		m_filterAgent.Init();
		Clear();
		m_nCount = nCount;
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
			std::string strExts = m_filterAgent.GetExtsFromTypes(pFileType);
			memcpy(FilterItem.szExts, strExts.c_str(), strExts.size());
			m_searcherList.push_back(FilterItem);
			log.Print(LL_DEBUG_INFO,"XmlItem(%d):SearchName=%s,SearchPath=%s,SearchType=%s, Exts=%s\r\n",
				i+1,m_searcherList[i].szSearceName,m_searcherList[i].szSearchPath,
				m_searcherList[i].szSearchType, m_searcherList[i].szExts);			
		}
	}else
	{
		log.Print(LL_DEBUG_INFO, "[info]t_searcher no record\r\n");
		return 0;
	}
	
	return 0;	
}

#define ALL_FILE_TYPES		"word,excel,ppt,pdf,txt,html"
#define ADD_FILE_TYPES		"word,excel,ppt,pdf"
//false 记录
//true  过滤掉该记录，不记录
//过滤规则:
//如果该文件在索引目录下，则比较文件类型，符合，则记录，否则，不记录
//如果该文件不再索引目录下，则比较文件类型（索引文件类型），符合，则记录，否则，不记录
//需要建立索引文件类型库
bool slXmlAgent::Filters(char* pszFullPath, BOOL bAdd /*= FALSE*/)
{
	//获取文件路径，和后缀名
	char ext[_MAX_EXT];
	
	_splitpath( pszFullPath, NULL, NULL, NULL, ext );
	if (!strlen(ext))
		return true;
	
	//根据文件路径，查找是否在索引目录队列中
	//检测是否在已建索引库中
	BOOL bInSearcher = FALSE;
	int i = 0;
	for (i; i < m_nCount; i++)
	{
		std::string strFullPath = pszFullPath;
		
		if (strncmp(pszFullPath, m_searcherList[i].szSearchPath, strlen(m_searcherList[i].szSearchPath)) == 0)
		{	
			//索引目录中的文件
			bInSearcher = TRUE;
			break;
		}
	}

	//在索引目录队列中，则获取文档类型
	std::string strExts;
	if (!bInSearcher)
	{
		//最近文档,最近修改的记录 新建的状态下，只记录  office和pdf
		if (bAdd)
		{
			strExts = m_filterAgent.GetExtsFromTypes(ADD_FILE_TYPES);
		}else
			strExts = m_filterAgent.GetAllExts();
	}else
		strExts = m_searcherList[i].szExts;

	//根据文档类型获取过滤后缀名库
	SetFilters(strExts.c_str(), "");

	if(IncludeThisNotification(ext))
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
		if( strncmp(szSearchPath, m_searcherList[i].szSearchPath, strlen(m_searcherList[i].szSearchPath)) == 0 )
		{
			return strSearchName = m_searcherList[i].szSearceName; 
		}
	}

	return DEFAULT_DB_NAME;

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
