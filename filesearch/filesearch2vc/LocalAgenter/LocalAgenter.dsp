# Microsoft Developer Studio Project File - Name="LocalAgenter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LocalAgenter - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LocalAgenter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LocalAgenter.mak" CFG="LocalAgenter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LocalAgenter - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LocalAgenter - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LocalAgenter - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../Source" /I "../../AboutDlg" /I "comm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../publish/LocalAgenter.exe"

!ELSEIF  "$(CFG)" == "LocalAgenter - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../Source" /I "../../AboutDlg" /I "comm" /I "Cabinet" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../bin/LocalAgenter.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "LocalAgenter - Win32 Release"
# Name "LocalAgenter - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CyberDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalAgenter.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalAgenter.rc
# End Source File
# Begin Source File

SOURCE=.\LocalAgenterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ShortcutPaneBase.cpp
# End Source File
# Begin Source File

SOURCE=.\ShortcutPaneCalendar.cpp
# End Source File
# Begin Source File

SOURCE=.\ShortcutPaneContacts.cpp
# End Source File
# Begin Source File

SOURCE=.\ShortcutPaneFolders.cpp
# End Source File
# Begin Source File

SOURCE=.\sloMysqlAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\StateTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\XTPReportControlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\XTPShortcutBarEx.cpp
# End Source File
# Begin Source File

SOURCE=.\XTTreeCtrlEx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CyberDlg.h
# End Source File
# Begin Source File

SOURCE=.\GroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\LocalAgenter.h
# End Source File
# Begin Source File

SOURCE=.\LocalAgenterDlg.h
# End Source File
# Begin Source File

SOURCE=.\ReportRecord.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SelectTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ShortcutPaneBase.h
# End Source File
# Begin Source File

SOURCE=.\ShortcutPaneCalendar.h
# End Source File
# Begin Source File

SOURCE=.\ShortcutPaneContacts.h
# End Source File
# Begin Source File

SOURCE=.\ShortcutPaneFolders.h
# End Source File
# Begin Source File

SOURCE=.\sloMysqlAgent.h
# End Source File
# Begin Source File

SOURCE=.\StateTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\XTPReportControlEx.h
# End Source File
# Begin Source File

SOURCE=.\XTPShortcutBarEx.h
# End Source File
# Begin Source File

SOURCE=.\XTTreeCtrlEx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\account_actions24_h.bmp
# End Source File
# Begin Source File

SOURCE=.\res\check.cur
# End Source File
# Begin Source File

SOURCE=.\res\check_none.cur
# End Source File
# Begin Source File

SOURCE=.\res\copy_to24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Delete1.ico
# End Source File
# Begin Source File

SOURCE=.\res\delete24_h.bmp
# End Source File
# Begin Source File

SOURCE=".\res\e-2.ico"
# End Source File
# Begin Source File

SOURCE=.\res\icon10.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon11.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon14.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon17.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon6.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon8.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon9.ico
# End Source File
# Begin Source File

SOURCE=.\res\LocalAgenter.ico
# End Source File
# Begin Source File

SOURCE=.\res\LocalAgenter.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PaneIcons.bmp
# End Source File
# Begin Source File

SOURCE=.\res\search24_h.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Shortcuts_big.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Shortcuts_big_alpha.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Shortcuts_small.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Shortcuts_small_alpha.bmp
# End Source File
# Begin Source File

SOURCE=.\res\state_images.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree_images.bmp
# End Source File
# Begin Source File

SOURCE=.\res\word.ico
# End Source File
# Begin Source File

SOURCE=.\res\WRITE3.ICO
# End Source File
# End Group
# Begin Group "mysql"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\comm\mysqlcomm.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\mysqlcomm.h
# End Source File
# Begin Source File

SOURCE=.\comm\MySQLDB.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\MySQLDB.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloCommAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloCommAgent.h
# End Source File
# Begin Source File

SOURCE=.\comm\sloRegAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\sloRegAgent.h
# End Source File
# End Group
# Begin Group "comm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\comm\TTComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\TTComboBox.h
# End Source File
# End Group
# Begin Group "cab"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Cabinet\Blowfish.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\Cache.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\Compress.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\Error.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\Extract.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\ExtractMemory.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\ExtractResource.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\ExtractStream.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\ExtractUrl.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\FCI.H
# End Source File
# Begin Source File

SOURCE=.\Cabinet\FDI.H
# End Source File
# Begin Source File

SOURCE=.\Cabinet\File.hpp
# End Source File
# Begin Source File

SOURCE=.\HYResources.cpp
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=.\HYResources.h
# End Source File
# Begin Source File

SOURCE=.\Cabinet\Internet.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\Map.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\String.hpp
# End Source File
# Begin Source File

SOURCE=.\Cabinet\Trace.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
