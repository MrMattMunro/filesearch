; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=9
Class1=CFsUiApp
LastClass=CLicenseDlg
NewFileInclude2=#include "FsUi.h"
ResourceCount=7
NewFileInclude1=#include "stdafx.h"
Class2=CCreateIndexDlg
LastTemplate=CDialog
Resource1=IDD_DIALOG_CREATE_INDEX
Class3=CCustomCiHuiDlg
Resource2=IDD_DIALOG_SET_ATTR
Class4=CModifyIndexDlg
Resource3=IDD_DIALOG_MODIFY_INDEX
Class5=CShowAllCiHuiDlg
Resource4=IDD_DIALOG_ALL_CIHUI
Class6=CSetAttributeDlg
Resource5=IDD_DIALOG_FAST_SEARCH
Class7=CFastSearchDlg
Class8=CSearchThread
Resource6=IDD_DIALOG_CUSTOM_DICT
Class9=CLicenseDlg
Resource7=IDD_DIALOG_LICENSE

[CLS:CFsUiApp]
Type=0
HeaderFile=FsUi.h
ImplementationFile=FsUi.cpp
Filter=N
LastObject=CFsUiApp
BaseClass=CWinApp
VirtualFilter=AC

[DLG:IDD_DIALOG_CREATE_INDEX]
Type=1
Class=CCreateIndexDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_SEARCH_PATH,edit,1350633600
Control5=IDC_BUTTON_BROWSE,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CHECK_EXCEL,button,1342242819
Control8=IDC_CHECK_WORD,button,1342242819
Control9=IDC_CHECK_PPT,button,1342242819
Control10=IDC_CHECK_PDF,button,1342242819
Control11=IDC_CHECK_HTML,button,1342242819
Control12=IDC_CHECK_TXT,button,1342242819

[CLS:CCreateIndexDlg]
Type=0
HeaderFile=CreateIndexDlg.h
ImplementationFile=CreateIndexDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CCreateIndexDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_CUSTOM_DICT]
Type=1
Class=CCustomCiHuiDlg
ControlCount=13
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_CIHUI_PATH,edit,1350633600
Control5=IDC_BUTTON_BROWSE_CIHUI,button,1342242816
Control6=IDC_CHECK_OVERCIHUI,button,1342242819
Control7=IDC_BUTTON_CHECK_EXISTCIHUI,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352

[CLS:CCustomCiHuiDlg]
Type=0
HeaderFile=CustomCiHuiDlg.h
ImplementationFile=CustomCiHuiDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCustomCiHuiDlg

[DLG:IDD_DIALOG_MODIFY_INDEX]
Type=1
Class=CModifyIndexDlg
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC_SEARCHPATH,static,1342308352
Control6=IDC_CHECK_EXCEL,button,1342242819
Control7=IDC_CHECK_WORD,button,1342242819
Control8=IDC_CHECK_PDF,button,1342242819
Control9=IDC_CHECK_PPT,button,1342242819
Control10=IDC_CHECK_HTML,button,1342242819
Control11=IDC_CHECK_TXT_MODIFY,button,1342242819
Control12=IDC_CHECK_CHM,button,1342242819
Control13=IDC_BUTTON_DEL_INDEX,button,1342242816

[CLS:CModifyIndexDlg]
Type=0
HeaderFile=ModifyIndexDlg.h
ImplementationFile=ModifyIndexDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CModifyIndexDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_ALL_CIHUI]
Type=1
Class=CShowAllCiHuiDlg
ControlCount=4
Control1=IDCANCEL,button,1342242816
Control2=IDC_LIST_ALL_CIHUI,listbox,1352728835
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_KEY_WORD,edit,1350631552

[CLS:CShowAllCiHuiDlg]
Type=0
HeaderFile=ShowAllCiHuiDlg.h
ImplementationFile=ShowAllCiHuiDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CShowAllCiHuiDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_SET_ATTR]
Type=1
Class=CSetAttributeDlg
ControlCount=23
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_IE_PATH,edit,1350633600
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_WORD_PATH,edit,1350633600
Control12=IDC_EDIT_EXCEL_PATH,edit,1350633600
Control13=IDC_EDIT_PPT_PATH,edit,1350633600
Control14=IDC_EDIT_PDF_PATH,edit,1350633600
Control15=IDC_EDIT_TXT_PATH,edit,1350633600
Control16=IDC_BUTTON_BROWSER_IE,button,1342242816
Control17=IDC_BUTTON_BROWSER_WORD,button,1342242816
Control18=IDC_BUTTON_BROWSER_EXCEL,button,1342242816
Control19=IDC_BUTTON_BROWSER_PPT,button,1342242816
Control20=IDC_BUTTON_BROWSER_PDF,button,1342242816
Control21=IDC_BUTTON_BROWSER_TXT,button,1342242816
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352

[CLS:CSetAttributeDlg]
Type=0
HeaderFile=SetAttributeDlg.h
ImplementationFile=SetAttributeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSetAttributeDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_FAST_SEARCH]
Type=1
Class=CFastSearchDlg
ControlCount=2
Control1=IDC_EDIT_SEARCH_KEY,edit,1350631552
Control2=IDC_COMBO_PATH,combobox,1344340226

[CLS:CFastSearchDlg]
Type=0
HeaderFile=FastSearchDlg.h
ImplementationFile=FastSearchDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO_PATH

[CLS:CSearchThread]
Type=0
HeaderFile=SearchThread.h
ImplementationFile=SearchThread.cpp
BaseClass=CWinThread
Filter=N
LastObject=CSearchThread

[DLG:IDD_DIALOG_LICENSE]
Type=1
Class=CLicenseDlg
ControlCount=13
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_NUM,edit,1350631552
Control7=IDC_EDIT_EMAIL,edit,1350631552
Control8=IDC_STATIC_ENDTIME,static,1342308352
Control9=IDC_BUTTON_REG,button,1342242816
Control10=IDC_STATIC_BEGINTIME_CONTENT,static,1342308352
Control11=IDC_STATIC_ENTTIME_CONTENT,static,1342308352
Control12=IDC_STATIC_BEGINTIME,static,1342308352
Control13=IDC_STATIC_ERROR_INFO,static,1342308352

[CLS:CLicenseDlg]
Type=0
HeaderFile=LicenseDlg.h
ImplementationFile=LicenseDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CLicenseDlg
VirtualFilter=dWC

