#include <Windows.h>
//_T("")����tchar.h�ж���
#include <tchar.h>
#include <iostream>
PROCESS_INFORMATION myFirefox();
typedef struct EnumFunArg
{
	HWND      hWnd;
	DWORD    dwProcessId;
}EnumFunArg, *LPEnumFunArg;
BOOL CALLBACK EnumWindowsProc(_In_ HWND   hwnd, _In_ LPARAM windowInfo) {
	//���������ͼ��Ĵ���;
	EnumFunArg  *pArg = (LPEnumFunArg)windowInfo;

	//WCHAR path[256] = {};
	//�ò�����ֻ�ܵõ��Լ�����·��
	//if (GetWindowModuleFileName(hwnd, path, 256))
	//{
		//std::wcout << path << std::endl;
		//pArg->hWnd = hwnd;
		//return false;
	//}

	//ֻ���õ������̳���Ĵ���
	//DWORD  processId;
	//GetWindowThreadProcessId(hwnd, &processId);
	//if (processId == pArg->dwProcessId) {
		//pArg->hWnd = hwnd;
		//return false;
	//}
	//������뷵��TRUE,����FALSE�Ͳ���ö����
	return true;
}



HWND GetWallpaperHWND(PROCESS_INFORMATION processInfo) {
	//�ҵ�������ڵ�
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
		//�Ҳ����ͷ���CPUִ��ʱ�䣬�Ȼ�����
		Sleep(0);
		firefox = FindWindow(_T("MozillaWindowClass"), _T("Silver���Н� - Mozilla Firefox"));
	}
	return firefox;
}

int main() {
	PROCESS_INFORMATION processInfo = myFirefox();
	GetWallpaperHWND(processInfo);
	return 0;
}

PROCESS_INFORMATION myFirefox() {
	//ʹ��
	//CreateProcess();
	PROCESS_INFORMATION processInfo = {};
	STARTUPINFO startInfo = {};
	//���ؽ��̴���
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
	//���Ե�һ�£�����Ч��������Ŷ���������Ƿ��ţ�����ο
	DWORD result = WaitForInputIdle(processInfo.hProcess, 3000);

	//ʹ�����������ȱ���ǣ������еĳ��������ֹһ������ʱ������ɲ��������޷��õ���ȷ�Ĵ��ھ����
	//GUITHREADINFO gui = {};
	//gui.cbSize = sizeof(gui);
	//Sleep(3000);
	//ret=GetGUIThreadInfo(processInfo.dwThreadId, &gui);
	//result=GetLastError();
	//return gui.hwndActive;
	return processInfo;
}