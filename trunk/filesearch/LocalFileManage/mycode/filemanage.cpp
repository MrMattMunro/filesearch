#include "stdafx.h"
#include "filemanage.h"
#include "maindlg.h"

// ³ÌÐòÈë¿Ú
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CMainDlg dlg;
	dlg.DoModal();
	
	return 0;
}
