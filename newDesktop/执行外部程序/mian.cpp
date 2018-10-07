#include <Windows.h>
//_T("")宏在tchar.h中定义
#include <tchar.h>
void myFirefox();
int main() {
	myFirefox();
	return 0;
}

void myFirefox() {
	//使用
	//CreateProcess();
	PROCESS_INFORMATION pi; 
	STARTUPINFO si;
	//隐藏进程窗口
	si.cb = sizeof(STARTUPINFO);
	si.lpReserved = NULL; 
	si.lpDesktop =NULL; 
	si.lpTitle = NULL; 
	si.dwFlags =	STARTF_USESHOWWINDOW; 
	si.wShowWindow = SW_SHOW;
	si.cbReserved2 =	NULL;
	si.lpReserved2 = NULL; 
	//BOOL ret =CreateProcess(NULL, _T("notepad.exe"), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	WCHAR cmdline []= _T("notepad.exe");
	BOOL ret = CreateProcess(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}