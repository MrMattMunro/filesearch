; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=5
Class1=CFsUiApp
LastClass=CShowAllCiHuiDlg
NewFileInclude2=#include "FsUi.h"
ResourceCount=4
NewFileInclude1=#include "stdafx.h"
Class2=CCreateIndexDlg
LastTemplate=CDialog
Resource1=IDD_DIALOG_CUSTOM_DICT
Class3=CCustomCiHuiDlg
Resource2=IDD_DIALOG_CREATE_INDEX
Class4=CModifyIndexDlg
Resource3=IDD_DIALOG_MODIFY_INDEX
Class5=CShowAllCiHuiDlg
Resource4=IDD_DIALOG_ALL_CIHUI

[CLS:CFsUiApp]
Type=0
HeaderFile=FsUi.h
ImplementationFile=FsUi.cpp
Filter=N
LastObject=CFsUiApp

[DLG:IDD_DIALOG_CREATE_INDEX]
Type=1
Class=CCreateIndexDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_SEARCH_PATH,edit,1350631552
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
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_CIHUI_PATH,edit,1350631552
Control6=IDC_BUTTON_BROWSE_CIHUI,button,1342242816
Control7=IDC_CHECK_OVERCIHUI,button,1342242819
Control8=IDC_BUTTON_CHECK_EXISTCIHUI,button,1342242816

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
LastObject=IDC_EDIT_KEY_WORD
VirtualFilter=dWC

