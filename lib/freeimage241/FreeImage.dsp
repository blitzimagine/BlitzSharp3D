# Microsoft Developer Studio Project File - Name="FreeImage" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=FreeImage - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FreeImage.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FreeImage.mak" CFG="FreeImage - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FreeImage - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FreeImage - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FreeImage - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FREEIMAGE_EXPORTS" /YX /FD /c
# ADD CPP /nologo /G6 /Gd /MT /W3 /GX /O1 /I "Source" /I "Source\ZLib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FREEIMAGE_EXPORTS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\FreeImage.dll Dist	copy Release\FreeImage.lib Dist	copy Source\FreeImage.h Dist
# End Special Build Tool

!ELSEIF  "$(CFG)" == "FreeImage - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FREEIMAGE_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "Source" /I "Source\ZLib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FREEIMAGE_EXPORTS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/FreeImaged.dll" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\FreeImaged.dll Dist	copy Debug\FreeImaged.lib Dist	copy Source\FreeImage.h Dist
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "FreeImage - Win32 Release"
# Name "FreeImage - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Plugins"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\FreeImage\Plugin.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginBMP.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginICO.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginIFF.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginJPEG.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginKOALA.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginMNG.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginPCD.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginPCX.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginPNG.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginPNM.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginPSD.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginRAS.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginTARGA.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginTIFF.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\PluginWBMP.cpp
# End Source File
# End Group
# Begin Group "Conversion"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\FreeImage\Conversion.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\Conversion16_555.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\Conversion16_565.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\Conversion24.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\Conversion32.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\Conversion8.cpp
# End Source File
# End Group
# Begin Group "Quantizers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\FreeImage\NNQuantizer.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\WuQuantizer.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Source\FreeImage\BitmapAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\FreeImage.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\FreeImageIO.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\GetType.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImage\LoadFunctions.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Source\FreeImage.h
# End Source File
# Begin Source File

SOURCE=.\Source\FreeImageIO.h
# End Source File
# Begin Source File

SOURCE=.\Source\Plugin.h
# End Source File
# Begin Source File

SOURCE=.\Source\Quantizers.h
# End Source File
# Begin Source File

SOURCE=.\Source\Utilities.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\KnownBugs.txt
# End Source File
# Begin Source File

SOURCE=.\Todo.txt
# End Source File
# Begin Source File

SOURCE=.\Whatsnew.txt
# End Source File
# End Target
# End Project
