// ShowAllCiHuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "ShowAllCiHuiDlg.h"

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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShowAllCiHuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowAllCiHuiDlg)
	DDX_Control(pDX, IDC_LIST_ALL_CIHUI, m_AllCiHuiListBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowAllCiHuiDlg, CDialog)
	//{{AFX_MSG_MAP(CShowAllCiHuiDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowAllCiHuiDlg message handlers

BOOL CShowAllCiHuiDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_AllCiHuiListBox.AddString("11");
	m_AllCiHuiListBox.AddString("22");

	ReadAllCiHui();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CShowAllCiHuiDlg::ReadAllCiHui()
{
    FILE *fp;   
    char *content;   
	
    // 以只读方式打开文件   
    if((fp = fopen("C:\\custom.txt", "r")) == NULL) {   
        printf("\r读取文件D:\\test.txt时发生异常");   
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
		if (*pCur == '\n' || *pCur == 0x00)
		{
			int nLen = pCur-pBegin;
			char* szItem = new char[nLen+1];
			memset(szItem, NULL, nLen+1);
			strncpy(szItem, pBegin, nLen);
			m_AllCiHuiListBox.AddString(szItem);
			if (szItem)
			{
				delete szItem;
				szItem = NULL;
			}

			pBegin = pCur+1;
		}
		pCur++;
	}


    // 释放content内存   
    free(content); 
	
	return 0;
}
