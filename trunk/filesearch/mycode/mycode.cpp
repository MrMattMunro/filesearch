#include "stdafx.h"
#include "mycode.h"
#include "maindlg.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CMainDlg dlg;
	dlg.DoModal();
	return 0;
}
