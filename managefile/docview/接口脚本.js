/*
1.新建
*/
//新建Word
document.all.FramerControl1.CreateNew("Word.Document");
//新建Excel
document.all.FramerControl1.CreateNew("Excel.Sheet");

/*
2.打开文件
*/
//打开制定的本地文件
document.all.FramerControl1.Open("C:\\TestBook.xls");
//制定用Word来打开c:\plain.txt文件
document.all.FramerControl1.Open("C:\\Plain.txt",false, "Word.Document");
//打开服务器的文件 
document.all.FramerControl1.Open "https://secureserver/test/mytest.asp?id=123",true, "Excel.Sheet", "MyUserAccount", "MyPassword");
//打开服务器的文件 
document.all.FramerControl1.Open("http://localhost/1.doc", true);

/*
3.保存文件
*/
//到本地
document.all.FramerControl1.Save("c:\\1.doc",true);
//服务器   
/*增加Http协议Post上传接口,可以Post一个动态页面(jsp,asp,php...),由动态页面负责解析数据
bool HttpInit();
bool HttpAddPostString(BSTR strName, BSTR strValue);
bool HttpAddPostCurrFile(BSTR strFileID, BSTR strFileName);
BSTR HttpPost(BSTR bstr);	
*/

//初始化Http引擎
document.all.FramerControl1.HttpInit();
//增加Post变量
document.all.FramerControl1.HttpAddPostString("RecordID","20060102200);
document.all.FramerControl1.HttpAddPostString("UserID","李局长");
//上传打开的文件
document.all.FramerControl1.HttpAddPostCurrFile("FileData", "文档名.doc");
//执行上传动作
document.all.FramerControl1.HttpPost("http://xxxx.com/uploadfile.asp"); 

/*
4.修订留痕
*/
//进入留痕状态
document.all.FramerControl1.SetTrackRevisions(1);
//进入非留痕状态
document.all.FramerControl1.SetTrackRevisions(0);
//接受当前修订
document.all.FramerControl1.SetTrackRevisions(4);

/*
5.设置当前用户
*/
document.all.FramerControl1.SetCurrUserName("张三");	

/*
6.设置当前时间(笔迹留痕会显示("Like 2006:02:07 11:11:11")
*/
document.all.FramerControl1.SetCurrTime("2006:02:07 11:11:11");

/*
7.设置和创建书签，此功能比较强大，设置书签数据、添加书签和添加红头文件就靠他了
SetFieldValue(BSTR strFieldName, BSTR strValue, BSTR strCmdOrSheetName)
strFieldName:书签名
strValue：要设置的值
strCmdOrSheetName：命令 ::ADDMARK::   ::FILE::
一般来说：WORD中书签是做好的，可以通过此接口把外界数据设置进书签中去。
*/
//在当前WORD位置插入标签,标签名为"book1",数值为"test"
document.all.FramerControl1.SetFieldValue("book1","test","::ADDMARK::");

//设置书签"Time",数值为"2006-03-16 22:22:22"
document.all.FramerControl1.SetFieldValue("Time","2006-03-16 22:22:22","");

//在书签位置"hongtou",插入红头文件"http://222.222.222.222/hongtou1.doc" 这样，红头就自动插进去了
document.all.FramerControl1.SetFieldValue("hongtou","http://222.222.222.222/hongtou1.doc","::FILE::");

/*
8.设置菜单显示情况
BOOL SetMenuDisplay(long lMenuFlag)
lMenuFlag为以下数值的组合
#define MNU_NEW                         0x01
#define MNU_OPEN                        0x02
#define MNU_CLOSE                       0x04
#define MNU_SAVE                        0x08
#define MNU_SAVEAS                      0x16
#define MNU_PGSETUP                     0x64
#define MNU_PRINT                       0x256
#define MNU_PROPS                       0x32
#define MNU_PRINTPV                     0x126
*/
//只有“新建”菜单可用 
document.all.FramerControl1..SetMenuDisplay(1);
//只有“打开”菜单可用 
document.all.FramerControl1.SetMenuDisplay(2);
//只有“打开”和“新建”菜单可用 
document.all.FramerControl1.SetMenuDisplay(3);

/*
9.保护文档和解保护文档
lProOrUn:1:保护文档；0:解除保护
lProType:  
    wdNoProtection = -1,
    wdAllowOnlyRevisions = 0,
    wdAllowOnlyComments = 1,
    wdAllowOnlyFormFields = 2
strProPWD:密码
*/
//完全保护文档，密码为"pwd"    
document.all.FramerControl1.ProtectDoc(1,1,"pwd");
//解除文档保护                 
document.all.FramerControl1.ProtectDoc(0,1,"pwd");

/*
10.显示或隐藏修订内容
ShowRevisions(long nNewValue)
nNewValue = 0 则隐藏修订
          = 1 则显示修订
*/
//显示修订留痕
document.all.FramerControl1.ShowRevisions(1);
//隐藏修订留痕
document.all.FramerControl1.ShowRevisions(0);
/*
*/
document.all.FramerControl1.InSertFile("http://localhost/1.doc");


/*
11.设置文档浏览模式
 ShowView(long dwViewType)

*/
//大纲模式
document.all.FramerControl1.ShowView(5);

/*
12.插入合并文件，
strFieldPath 文件路径,可以是http,ftp的路径

pPos = 0 //当前鼠标位置
1;文件开头
2;文件末尾
 
InSertFile(BSTR strFieldPath, long lPos)
*/
//文件头部
document.all.FramerControl1.InSertFile("http://XX.com/XX.doc",1);
//文件尾部 
document.all.FramerControl1.InSertFile("http://XX.com/XX.doc",2);
//当前光标位置
document.all.FramerControl1.InSertFile("http://XX.com/XX.doc",0);

