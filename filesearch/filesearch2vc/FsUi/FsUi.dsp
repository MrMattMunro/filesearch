# Microsoft Developer Studio Project File - Name="FsUi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=FsUi - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FsUi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FsUi.mak" CFG="FsUi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FsUi - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FsUi - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FsUi - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "comm" /I "../mysql" /I "../utils" /I "bitmap" /I "../log" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"../publish/FsUi.dll"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "FsUi - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "comm" /I "../mysql" /I "../utils" /I "bitmap" /I "../log" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "D_STLP_DEBUG" /D "__STL_DEBUG" /Yu"stdafx.h" /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"C:/WINDOWS/system32/FsUi.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "FsUi - Win32 Release"
# Name "FsUi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddinSavefileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateIndexDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomCiHuiDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FastSearchDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FloatWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\FsUi.cpp
# End Source File
# Begin Source File

SOURCE=.\FsUi.def
# End Source File
# Begin Source File

SOURCE=.\FsUi.rc
# End Source File
# Begin Source File

SOURCE=.\HotkeyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\IconEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\LicenseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifyIndexDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\myftpcomm.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\mysqlcomm.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\MySQLDB.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\PropertyPageTaskPanelNavigator.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchThread.cpp
# End Source File
# Begin Source File

SOURCE=.\SetAttributeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowAllCiHuiDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloCommAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloCreateIndexAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloCustomCiHuiAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloFastSearchAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloFilterAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\sloHotkeyAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloLanguageAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloLicenseAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloModifyIndexAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloOpenFileAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloRegAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloSetAttrAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloSkinAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sltFastSearchThread.cpp
# End Source File
# Begin Source File

SOURCE=.\sltHotkeyChangeThread.cpp
# End Source File
# Begin Source File

SOURCE=.\sltLoadwndThread.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\comm\TTComboBox.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddinSavefileDlg.h
# End Source File
# Begin Source File

SOURCE=.\CreateIndexDlg.h
# End Source File
# Begin Source File

SOURCE=.\CustomCiHuiDlg.h
# End Source File
# Begin Source File

SOURCE=.\FastSearchDlg.h
# End Source File
# Begin Source File

SOURCE=.\FloatWnd.h
# End Source File
# Begin Source File

SOURCE=.\FsUi.h
# End Source File
# Begin Source File

SOURCE=.\HotkeyDlg.h
# End Source File
# Begin Source File

SOURCE=.\comm\IconEdit.h
# End Source File
# Begin Source File

SOURCE=.\LicenseDlg.h
# End Source File
# Begin Source File

SOURCE=.\ModifyIndexDlg.h
# End Source File
# Begin Source File

SOURCE=.\comm\myftpcomm.h
# End Source File
# Begin Source File

SOURCE=.\comm\mysqlcomm.h
# End Source File
# Begin Source File

SOURCE=.\comm\PropertyPageTaskPanelNavigator.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SearchThread.h
# End Source File
# Begin Source File

SOURCE=.\SetAttributeDlg.h
# End Source File
# Begin Source File

SOURCE=.\ShowAllCiHuiDlg.h
# End Source File
# Begin Source File

SOURCE=.\SkinDlg.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloCommAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloCreateIndexAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloCustomCiHuiAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloFastSearchAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloFilterAgent.h
# End Source File
# Begin Source File

SOURCE=.\sloHotkeyAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloLanguageAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloLicenseAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloModifyIndexAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloOpenFileAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloRegAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloSetAttrAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloSkinAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sltFastSearchThread.h
# End Source File
# Begin Source File

SOURCE=.\sltHotkeyChangeThread.h
# End Source File
# Begin Source File

SOURCE=.\sltLoadwndThread.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\comm\TTComboBox.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icons\point\addon.ico
# End Source File
# Begin Source File

SOURCE=.\res\AlphaFind.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icons\hotkey\ARROW6A.ICO
# End Source File
# Begin Source File

SOURCE=.\res\icons\point\ARROW6A.ICO
# End Source File
# Begin Source File

SOURCE=.\res\icons\point\ARW03RT.ICO
# End Source File
# Begin Source File

SOURCE=.\res\icons\point\ARW05RT.ICO
# End Source File
# Begin Source File

SOURCE=.\res\back16.bmp
# End Source File
# Begin Source File

SOURCE=".\res\icons\base setting\baseSetting.ico"
# End Source File
# Begin Source File

SOURCE=".\res\icons\base setting\baseSetting2.ico"
# End Source File
# Begin Source File

SOURCE=".\res\icons\base setting\baseSetting5.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Book2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Bookshelf.ico
# End Source File
# Begin Source File

SOURCE=.\res\cancel16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\db_find16_h.bmp
# End Source File
# Begin Source File

SOURCE=.\res\db_register16_h.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delete16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DEVTOOL.ICO
# End Source File
# Begin Source File

SOURCE=.\res\icons\dic\dictionary3.ico
# End Source File
# Begin Source File

SOURCE=.\res\excel.ico
# End Source File
# Begin Source File

SOURCE=.\res\fastsearchback.bmp
# End Source File
# Begin Source File

SOURCE=.\res\feiqclose.bmp
# End Source File
# Begin Source File

SOURCE=.\res\feiqfind.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Find.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Find.ico
# End Source File
# Begin Source File

SOURCE=.\res\find_nextb24_h.bmp
# End Source File
# Begin Source File

SOURCE=.\res\folder_open16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\folder_open24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\forward16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\forward24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FsUi.rc2
# End Source File
# Begin Source File

SOURCE=.\res\fwnd.ico
# End Source File
# Begin Source File

SOURCE=.\res\HAND.ICO
# End Source File
# Begin Source File

SOURCE=.\res\icons\hotkey\hotkey2_48.ico
# End Source File
# Begin Source File

SOURCE=.\res\icons\hotkey\hotkey_32.ico
# End Source File
# Begin Source File

SOURCE=.\res\html.ico
# End Source File
# Begin Source File

SOURCE=.\res\icons\hotkey\Key5.ico
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.ico
# End Source File
# Begin Source File

SOURCE=.\res\logo2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo64.bmp
# End Source File
# Begin Source File

SOURCE=.\res\n33start_find.ico
# End Source File
# Begin Source File

SOURCE=".\res\New Text Doc.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Note.ico
# End Source File
# Begin Source File

SOURCE=.\res\notepad.ico
# End Source File
# Begin Source File

SOURCE=.\res\ok.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PAINT~32.ICO
# End Source File
# Begin Source File

SOURCE=.\res\pdf.ico
# End Source File
# Begin Source File

SOURCE=.\res\icons\point\point.ico
# End Source File
# Begin Source File

SOURCE=.\res\icons\point\points12.ico
# End Source File
# Begin Source File

SOURCE=.\res\ppt.ico
# End Source File
# Begin Source File

SOURCE=.\res\previcw_winxproyale.bmp
# End Source File
# Begin Source File

SOURCE=.\res\preview_office2007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\preview_vista.bmp
# End Source File
# Begin Source File

SOURCE=.\res\preview_winxpluna.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Recycle.ico
# End Source File
# Begin Source File

SOURCE=.\res\icons\register\register.ico
# End Source File
# Begin Source File

SOURCE=.\res\icons\register\register3.ico
# End Source File
# Begin Source File

SOURCE=.\res\Registration.ico
# End Source File
# Begin Source File

SOURCE=".\res\Registry Entries REG.ico"
# End Source File
# Begin Source File

SOURCE=.\res\search.ico
# End Source File
# Begin Source File

SOURCE=.\res\icons\search\search3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icons\search\Search6.ico
# End Source File
# Begin Source File

SOURCE=.\res\searchtool.ico
# End Source File
# Begin Source File

SOURCE=.\res\set_nomarl.ICO
# End Source File
# Begin Source File

SOURCE=".\res\SETUP INFORMATION INF.ICO"
# End Source File
# Begin Source File

SOURCE=.\res\Sherlock.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Sherlock.ico
# End Source File
# Begin Source File

SOURCE=.\res\icons\skin\skins2.ico
# End Source File
# Begin Source File

SOURCE=.\res\SYS_SET.ico
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_2007_Aqua.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_2007_Aqua.JPG
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_2007_Black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_2007_Blue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_2007_LightBlue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_2007_Sliver.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_VISTA_Black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_VISTA_Black2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_VISTA_Blue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_VISTA_Sliver.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_XP_LUNA_Blue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_XP_LUNA_HomeStead.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_XP_LUNA_Metallic.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skin\THREME_NAME_XP_ROYALE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icons\point\TRFFC02.ICO
# End Source File
# Begin Source File

SOURCE=.\res\word.ico
# End Source File
# End Group
# Begin Group "utils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\comm\comm.h
# End Source File
# Begin Source File

SOURCE=.\comm\FilenameEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\FilenameEdit.h
# End Source File
# Begin Source File

SOURCE=.\comm\HYPERLINK.CPP
# End Source File
# Begin Source File

SOURCE=.\comm\HYPERLINK.H
# End Source File
# Begin Source File

SOURCE=..\Utils\Thread.cpp
# End Source File
# End Group
# Begin Group "bitmap"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bitmap\EnBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\bitmap\ImageProcessors.cpp
# End Source File
# End Group
# Begin Group "thread"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\comm\sltCreateIndexDlgThread.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sltCreateIndexDlgThread.h
# End Source File
# Begin Source File

SOURCE=.\comm\sltFastSearchDlgThread.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sltFastSearchDlgThread.h
# End Source File
# Begin Source File

SOURCE=.\comm\sltLicenseThread.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sltLicenseThread.h
# End Source File
# Begin Source File

SOURCE=.\comm\sltModifyIndexDlgThread.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sltModifyIndexDlgThread.h
# End Source File
# Begin Source File

SOURCE=.\comm\sltSetSheetDlgThread.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sltSetSheetDlgThread.h
# End Source File
# End Group
# Begin Group "log"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\comm\Log.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\comm\Log.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\app.manifest
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\Sherlock.PNG
# End Source File
# End Target
# End Project
