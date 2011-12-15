// CyberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LocalAgenter.h"
#include "CyberDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCyberDlg dialog


CCyberDlg::CCyberDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCyberDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCyberDlg)
	m_cyberName = _T("");
	m_strLayerName = _T("3");
	m_strFrequencyName = _T("1");
	//}}AFX_DATA_INIT
	m_pTreeFocus = NULL;

}


void CCyberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCyberDlg)
	DDX_Control(pDX, IDC_TREE_WEBSITE, m_treeWebsite);
	DDX_Control(pDX, IDC_TREE_KEYWORDS, m_treeKeywords);
	DDX_Control(pDX, IDC_EDIT_CYBER_LAYER, m_editLayer);
	DDX_Control(pDX, IDC_EDIT_CYBER_FREQUENCY, m_editFrequency);
	DDX_Control(pDX, IDC_SPIN_LAYER, m_pinLayer);
	DDX_Control(pDX, IDC_SPIN_FREQUENCY, m_pinFrenquency);
	DDX_Text(pDX, IDC_EDIT_CYBER_NAME, m_cyberName);
	DDX_Text(pDX, IDC_EDIT_CYBER_LAYER, m_strLayerName);
	DDX_Text(pDX, IDC_EDIT_CYBER_FREQUENCY, m_strFrequencyName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCyberDlg, CDialog)
	//{{AFX_MSG_MAP(CCyberDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCyberDlg message handlers

BOOL CCyberDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pinFrenquency.SetRange(1, 24);
	m_pinFrenquency.SetBuddy(&m_editFrequency);
	//SetDlgItemInt(IDC_EDIT_CYBER_FREQUENCY, 1, TRUE);

	m_pinLayer.SetRange(3, 5);
	m_pinLayer.SetBuddy(&m_editLayer);
	//SetDlgItemInt(IDC_EDIT_CYBER_LAYER, 3, TRUE);

	////////////////////////////////////////////////////////////////////////////
	//m_treeKeywords
	//读取数据库，获取树基本信息
	sloMysqlAgent::GetInstance()->GetGroupsFromDB();
	HTREEITEM hItemState;

	//获取分组个数
	int nGroupSize = sloMysqlAgent::GetInstance()->m_GroupList.size();
	for (int i = 0; i < nGroupSize; i++)
	{
		int nState = STATE_UNCHECKED;
		sloMysqlAgent::GetInstance()->GetTypesFromDB(sloMysqlAgent::GetInstance()->m_GroupList[i].nID);

		//获取该分组下得类型个数
		int nTypeSize = sloMysqlAgent::GetInstance()->m_TypeList.size();
		for (int j = 0; j < nTypeSize; j++)
		{
			hItemState = m_treeKeywords.InsertItemState(sloMysqlAgent::GetInstance()->m_TypeList[j].szTypeName, 5, 5,nState);
			//获取词汇列表
			sloMysqlAgent::GetInstance()->GetKeyWordsFromTypeName(sloMysqlAgent::GetInstance()->m_TypeList[j].szTypeName);

			int nCount = sloMysqlAgent::GetInstance()->m_KeywordsList.size();
			for(int i = 0; i < nCount; i++)
			{
				if (m_strKeywords.GetLength() != 0 && m_strKeywords.Find(sloMysqlAgent::GetInstance()->m_KeywordsList[i].szKeyName) != -1)
				{
					nState = STATE_CHECKED;
				}else
					nState = STATE_UNCHECKED;
				m_treeKeywords.InsertItemState(sloMysqlAgent::GetInstance()->m_KeywordsList[i].szKeyName, 4, 4, nState, hItemState);
				
				if (nState == STATE_CHECKED)	
					m_treeKeywords.Expand(hItemState, TVE_EXPAND);
			}
		}
		m_treeKeywords.Expand(hItemState, TVE_EXPAND);
	}
	
	//////////////////////////////////////////////////////////////////////////
	//
	//读取数据库，获取树基本信息
	sloMysqlAgent::GetInstance()->GetGroupsFromDB_Website();
	//获取分组个数
	nGroupSize = sloMysqlAgent::GetInstance()->m_GroupListWebsite.size();
	for (i = 0; i < nGroupSize; i++)
	{
		int nState = STATE_UNCHECKED;
		hItemState = m_treeWebsite.InsertItemState (sloMysqlAgent::GetInstance()->m_GroupListWebsite[i].szGroupName, 5, 5, nState);
		//获取网址列表
		sloMysqlAgent::GetInstance()->GetWebsiteFromGroupName(sloMysqlAgent::GetInstance()->m_GroupListWebsite[i].szGroupName);
		
		int nCount = sloMysqlAgent::GetInstance()->m_WebsiteList.size();
		for(int j = 0; j < nCount; j++)
		{
			if (m_strWebsite.GetLength() != 0 && m_strWebsite.Find(sloMysqlAgent::GetInstance()->m_WebsiteList[j].szSiteName) != -1)
			{
				nState = STATE_CHECKED;
			}else
				nState = STATE_UNCHECKED;
		
			m_treeWebsite.InsertItemState(sloMysqlAgent::GetInstance()->m_WebsiteList[j].szSiteName, 4, 4, nState, hItemState);
			if (nState == STATE_CHECKED)	
				m_treeWebsite.Expand(hItemState, TVE_EXPAND);
		}
	}
	m_treeWebsite.Expand(hItemState, TVE_EXPAND);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CCyberDlg::SetTreeFocus(CXTTreeCtrl* pTreeFocus)
{
	ASSERT_VALID(pTreeFocus);
	m_pTreeFocus = pTreeFocus;
	
	m_treeKeywords.SendMessage(WM_NCPAINT);
	m_treeWebsite.SendMessage(WM_NCPAINT);
	
	//EnableProperties();
}

void CCyberDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if (m_cyberName.GetLength() == 0)
	{
		MessageBox("请输入快捕任务名称！");
		return ;
	}

	CString strKeywords, strWebsite;
	//遍历树
	HTREEITEM hNextItem = NULL;
	hNextItem = m_treeKeywords.GetNextItem(NULL);
	while(hNextItem!=NULL)
	{
		CString strText2 = m_treeKeywords.GetItemText(hNextItem);
		int nState = m_treeKeywords.GetItemCheck(hNextItem);
		if (nState == STATE_CHECKED && !m_treeKeywords.ItemHasChildren(hNextItem))
		{
			CString strText = m_treeKeywords.GetItemText(hNextItem);
			strKeywords += strText;
			strKeywords += ";";
		}

		hNextItem = m_treeKeywords.GetNextItem(hNextItem);
	}

	if (strKeywords.GetLength() == 0)
	{
		MessageBox("请至少选择一组词汇！");
		return ;
	}


	hNextItem = m_treeWebsite.GetNextItem(NULL);
	while(hNextItem!=NULL)
	{
		int nState = m_treeWebsite.GetItemCheck(hNextItem);
		if (nState == STATE_CHECKED && !m_treeWebsite.ItemHasChildren(hNextItem))
		{
			CString strText = m_treeWebsite.GetItemText(hNextItem);
			strWebsite += strText;
			strWebsite += ";";
		}
		
		hNextItem = m_treeWebsite.GetNextItem(hNextItem);
	}
	if (strWebsite.GetLength() == 0)
	{
		MessageBox("请至少选择一组网址！");
		return ;
	}

	//录库
	int nFreq = atoi(m_strFrequencyName.GetBuffer(0));
	int nLayer = atoi(m_strLayerName.GetBuffer(0));
	sloMysqlAgent::GetInstance()->AddCyber(m_cyberName.GetBuffer(0), strKeywords.GetBuffer(0), strWebsite.GetBuffer(0), nFreq, nLayer);

	CDialog::OnOK();
}


void CCyberDlg::SetKeywords(CString strKeywords)
{
	m_strKeywords = strKeywords;
}

void CCyberDlg::SetWebsite(CString strWebsite)
{
	m_strWebsite = strWebsite;
}