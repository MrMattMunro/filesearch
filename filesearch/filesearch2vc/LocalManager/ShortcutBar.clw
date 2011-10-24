; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGroupDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "shortcutbar.h"
LastPage=0

ClassCount=7
Class1=CMainFrame
Class2=CShortcutBarApp
Class3=CShortcutBarDoc
Class4=CShortcutBarSplitter
Class5=CShortcutBarView
Class6=CShortcutPaneCalendar

ResourceCount=6
Resource1=IDD_DIALOG_GROUP
Resource2=IDR_MENU_POPUP_TREE_PARENT
Resource3=IDR_MENU_POPUP_TREE_CHILD
Resource4=IDR_MENU_POPUP_LIST
Resource5=IDR_POPUP_MENU (English (U.S.))
Class7=CGroupDlg
Resource6=IDR_MAINFRAME (English (U.S.))

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=CMainFrame

[CLS:CShortcutBarApp]
Type=0
BaseClass=CWinApp
HeaderFile=ShortcutBar.h
ImplementationFile=ShortcutBar.cpp

[CLS:CShortcutBarDoc]
Type=0
BaseClass=CDocument
HeaderFile=ShortcutBarDoc.h
ImplementationFile=ShortcutBarDoc.cpp

[CLS:CShortcutBarSplitter]
Type=0
BaseClass=CXTSplitterWndEx
HeaderFile=ShortcutBarSplitter.h
ImplementationFile=ShortcutBarSplitter.cpp

[CLS:CShortcutBarView]
Type=0
BaseClass=CXTListView
HeaderFile=ShortcutBarView.h
ImplementationFile=ShortcutBarView.cpp
Filter=C
VirtualFilter=VWC

[CLS:CShortcutPaneCalendar]
Type=0
BaseClass=CXTPShortcutBarPane
HeaderFile=ShortcutPaneCalendar.h
ImplementationFile=ShortcutPaneCalendar.cpp

[MNU:IDR_POPUP_MENU (English (U.S.))]
Type=1
Class=?
Command1=ID_THEME_OFFICE2000
Command2=ID_THEME_OFFICEXP
Command3=ID_THEME_OFFICE2003
Command4=ID_THEME_OFFICE2007
CommandCount=4

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_THEME_OFFICE2000
Command17=ID_THEME_OFFICEXP
Command18=ID_THEME_OFFICE2003
Command19=ID_THEME_OFFICE2007
Command20=ID_THEME_CLIENTPANE
Command21=ID_THEME_SHOWEXPANDBUTTON
Command22=ID_THEME_SHOWACTIVEITEMONTOP
Command23=ID_THEME_ALLOWFREERESIZE
Command24=ID_APP_ABOUT
CommandCount=24

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[MNU:IDR_MENU_POPUP_LIST]
Type=1
Class=?
Command1=ID_EDIT_ADD
Command2=ID_EDIT_DEL
Command3=ID_EDIT_MODIFY
CommandCount=3

[MNU:IDR_MENU_POPUP_TREE_PARENT]
Type=1
Class=?
Command1=ID_TREE_ADD_TYPE
CommandCount=1

[MNU:IDR_MENU_POPUP_TREE_CHILD]
Type=1
Class=?
Command1=ID_DEL_GROUP
Command2=ID_MODIFY_GROUP
CommandCount=2

[DLG:IDD_DIALOG_GROUP]
Type=1
Class=CGroupDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_GROUP_NAME,edit,1350631552

[CLS:CGroupDlg]
Type=0
HeaderFile=GroupDlg.h
ImplementationFile=GroupDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CGroupDlg
VirtualFilter=dWC

