#include <Windows.h>
//_T("")宏在tchar.h中定义
#include <tchar.h>
#include <iostream>
PROCESS_INFORMATION myFirefox();
typedef struct EnumFunArg
{
	HWND      hWnd;
	DWORD    dwProcessId;
}EnumFunArg, *LPEnumFunArg;
BOOL CALLBACK EnumWindowsProc(_In_ HWND   hwnd, _In_ LPARAM windowInfo) {
	//如果是桌面图标的窗口;
	EnumFunArg  *pArg = (LPEnumFunArg)windowInfo;

	//WCHAR path[256] = {};
	//拿不到。只能得到自己程序路径
	//if (GetWindowModuleFileName(hwnd, path, 256))
	//{
		//std::wcout << path << std::endl;
		//pArg->hWnd = hwnd;
		//return false;
	//}

	//只能拿到单进程程序的窗口
	//DWORD  processId;
	//GetWindowThreadProcessId(hwnd, &processId);
	//if (processId == pArg->dwProcessId) {
		//pArg->hWnd = hwnd;
		//return false;
	//}
	//这里必须返回TRUE,返回FALSE就不在枚举了
	return true;
}



HWND GetWallpaperHWND(PROCESS_INFORMATION processInfo) {
	//找到火狐窗口的
	HWND firefox = nullptr;

	//EnumFunArg windowInfo;
	//windowInfo.dwProcessId = processInfo.dwProcessId;
	//windowInfo.hWnd = nullptr;
	//while (!windowInfo.hWnd)
	//{
		//EnumWindows(EnumWindowsProc, (LPARAM)&windowInfo);
		//Sleep(0);
	//}
	while (!firefox)
	{
		//找不到就放弃CPU执行时间，等会再找
		Sleep(0);
		firefox = FindWindow(_T("MozillaWindowClass"), _T("Silver·湫澲 - Mozilla Firefox"));
	}
	return firefox;
}

int main() {
	PROCESS_INFORMATION processInfo = myFirefox();
	GetWallpaperHWND(processInfo);
	return 0;
}

PROCESS_INFORMATION myFirefox() {
	//使用
	//CreateProcess();
	PROCESS_INFORMATION processInfo = {};
	STARTUPINFO startInfo = {};
	//隐藏进程窗口
	startInfo.cb = sizeof(STARTUPINFO);
	startInfo.lpReserved = NULL;
	startInfo.lpDesktop = NULL;
	startInfo.lpTitle = NULL;
	startInfo.dwFlags = STARTF_USESHOWWINDOW;
	startInfo.wShowWindow = SW_SHOW;
	startInfo.cbReserved2 = NULL;
	startInfo.lpReserved2 = NULL;
	//BOOL ret =CreateProcess(NULL, _T("notepad.exe"), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	//WCHAR cmdline []= _T("notepad.exe");
	//WCHAR cmdline[] = _T("D:\\Files\\doc\\GitHub\\newDesktop\\firefox\\FirefoxPortable.exe");
	WCHAR cmdline[] = _T("D:/Files/doc/GitHub/newDesktop/firefox/FirefoxPortable.exe");

	//WCHAR cmdline[] = _T("D:/Files/doc/GitHub/newDesktop/firefox/App/Firefox/firefox.exe");
	BOOL ret = CreateProcess(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &startInfo, &processInfo);
	//尝试等一下，好像效果不明显哦，不过还是放着，心理安慰
	DWORD result = WaitForInputIdle(processInfo.hProcess, 3000);

	//使用这个方法的缺陷是，当运行的程序包含不止一个进程时，会造成参数错误，无法得到正确的窗口句柄。
	//GUITHREADINFO gui = {};
	//gui.cbSize = sizeof(gui);
	//Sleep(3000);
	//ret=GetGUIThreadInfo(processInfo.dwThreadId, &gui);
	//result=GetLastError();
	//return gui.hwndActive;
	return processInfo;
}