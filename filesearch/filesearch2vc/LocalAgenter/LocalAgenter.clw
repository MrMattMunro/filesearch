; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCyberDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LocalAgenter.h"

ClassCount=5
Class1=CLocalAgenterApp
Class2=CLocalAgenterDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_MENU_DROPDOWN
Class4=CGroupDlg
Resource4=IDD_DIALOG_CYBER
Resource5=IDD_DIALOG_GROUP
Resource6=IDD_LOCALAGENTER_DIALOG
Class5=CCyberDlg
Resource7=IDR_MENU_TREE

[CLS:CLocalAgenterApp]
Type=0
HeaderFile=LocalAgenter.h
ImplementationFile=LocalAgenter.cpp
Filter=N

[CLS:CLocalAgenterDlg]
Type=0
HeaderFile=LocalAgenterDlg.h
ImplementationFile=LocalAgenterDlg.cpp
Filter=W
LastObject=IDC_REPORTCTRL
BaseClass=CXTResizeDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=LocalAgenterDlg.h
ImplementationFile=LocalAgenterDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LOCALAGENTER_DIALOG]
Type=1
Class=CLocalAgenterDlg
ControlCount=11
Control1=IDC_REPORTCTRL,XTPReport,1342242816
Control2=IDC_BUTTON_EXPORT,button,1342242816
Control3=IDC_BUTTON_DELETE,button,1342242816
Control4=IDC_BUTTON_SET,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO_GROUP,combobox,1344340226
Control7=IDC_COMBO_TYPE,combobox,1344340226
Control8=IDC_COMBO_TIME,combobox,1344340226
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_KEYWORD,edit,1350631552
Control11=IDC_BUTTON_SEARCH,button,1342242816

[DLG:IDD_DIALOG_GROUP]
Type=1
Class=CGroupDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_GROUP_NAME,edit,1350631552
Control3=IDOK,button,1342242816

[CLS:CGroupDlg]
Type=0
HeaderFile=GroupDlg.h
ImplementationFile=GroupDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CGroupDlg
VirtualFilter=dWC

[MNU:IDR_MENU_DROPDOWN]
Type=1
Class=?
Command1=ID_DROPDOWNMENU_OPTIONITEM1
Command2=ID_DROPDOWNMENU_OPTIONITEM2
CommandCount=2

[MNU:IDR_MENU_TREE]
Type=1
Class=?
Command1=ID_EDIT_ADD
Command2=ID_EDIT_DEL
Command3=ID_EDIT_RENAME
CommandCount=3

[DLG:IDD_DIALOG_CYBER]
Type=1
Class=CCyberDlg
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_CYBER_NAME,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_TREE_KEYWORDS,SysTreeView32,1350631463
Control7=IDC_TREE_WEBSITE,SysTreeView32,1350631463
Control8=IDC_STATIC,static,1342177288
Control9=IDC_STATIC,static,1342177288
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_CYBER_FREQUENCY,edit,1350633600
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_SPIN_FREQUENCY,msctls_updown32,1342177318
Control17=IDC_EDIT_CYBER_LAYER,edit,1350633600
Control18=IDC_SPIN_LAYER,msctls_updown32,1342177318

[CLS:CCyberDlg]
Type=0
HeaderFile=CyberDlg.h
ImplementationFile=CyberDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CCyberDlg
VirtualFilter=dWC

