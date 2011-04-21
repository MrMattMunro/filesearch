// ShowAllCiHuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "ShowAllCiHuiDlg.h"
#include "sloCustomCiHuiAgent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowAllCiHuiDlg dialog


CShowAllCiHuiDlg::CShowAllCiHuiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowAllCiHuiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowAllCiHuiDlg)
	m_strKeyWord = _T("");
	//}}AFX_DATA_INIT
}


void CShowAllCiHuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowAllCiHuiDlg)
	DDX_Control(pDX, IDC_LIST_ALL_CIHUI, m_AllCiHuiListBox);
	DDX_Text(pDX, IDC_EDIT_KEY_WORD, m_strKeyWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowAllCiHuiDlg, CDialog)
	//{{AFX_MSG_MAP(CShowAllCiHuiDlg)
	ON_EN_CHANGE(IDC_EDIT_KEY_WORD, OnChangeEditKeyWord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowAllCiHuiDlg message handlers

BOOL CShowAllCiHuiDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString strNewWords, strClose;
	
	strNewWords.LoadString(IDS_NEW_WORDS);
	strClose.LoadString(IDS_CLOSE);
	
	SetDlgItemText(IDC_STATIC_NEW_WORDS, strNewWords);
	SetDlgItemText(IDCANCEL, strClose);

	//////////////////////////////////////////////////////////////////

	ReadAllCiHui();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CShowAllCiHuiDlg::ReadAllCiHui()
{
    FILE *fp;   
    char *content;   
	
	sloCustomCiHuiAgent cus;
	cus.GetProFilePath();
    // 以只读方式打开文件   
    if((fp = fopen(cus.m_szcustomtxtPath, "r")) == NULL) {   
        printf("\r读取文件%s时发生异常");   
        return -1;   
    }   
	
    // 将文件指针移至文件末尾   
    fseek(fp, 0, SEEK_END);   
    // 取得文件指针的当前位置，即文件的长度    
    int len = ftell(fp);   
    // 将文件指针恢复到文件开始处   
    rewind(fp);   
    // 动态分配内存   
    content = (char*)malloc(len + 1);
	memset(content, NULL, len+1);
    // 读取文件内容到content中   
    fread(content, 1, len, fp);    
    // 将content的最后一位设为0，即字符串结束标志   
    content[len] = 0;   
    // 打印文件内容   
    printf("%s\r\n", content);   
	
    // 关闭文件指针   
    fclose(fp);   

	//解析词汇
	char* pBegin = content, 
	char* pCur = pBegin;
	for (int i = 0; i < len; i++)
	{
		if (*pCur == '\n')
		{
			int nLen = pCur-pBegin;
			char* szItem = new char[nLen+1];
			memset(szItem, NULL, nLen+1);
			strncpy(szItem, pBegin, nLen);
			m_AllCiHuiList.push_back(szItem);
			m_AllCiHuiListBox.AddString(szItem);
			if (szItem)
			{
				delete szItem;
				szItem = NULL;
			}

			pBegin = pCur+1;
		}

		if (*pCur == 0x00)
			break ;

		pCur++;
	}


    // 释放content内存   
    free(content); 
	
	return 0;
}

void CShowAllCiHuiDlg::OnChangeEditKeyWord() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	//清空listbox列表
	ClearListBox();
 
	int nCount = m_AllCiHuiList.size();

	for (int i = 0; i < nCount; i++)
	{
		std::string strItem = m_AllCiHuiList[i];
		if (strstr(strItem.c_str(), m_strKeyWord.GetBuffer(0)))
		{
			m_AllCiHuiListBox.AddString(strItem.c_str());
		}
	}

	UpdateData(FALSE);
}


void CShowAllCiHuiDlg::ClearListBox()
{
	// Delete every other item from the list box.
	int nCount = m_AllCiHuiListBox.GetCount();
	for (int i=0;i < nCount; i++)
	{
		m_AllCiHuiListBox.DeleteString( 0 );
	}
}
