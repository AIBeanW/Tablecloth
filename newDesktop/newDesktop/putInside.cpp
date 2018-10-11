#include"putInside.h"


BOOL CALLBACK EnumWindowsProc(_In_ HWND   tophandle, _In_ LPARAM topparamhandle) {
	//如果是桌面图标的窗口;
	if (FindWindowEx(tophandle, 0, _T("SHELLDLL_DefView"), nullptr) != nullptr)
	{
		//查找tophandle所对应的下一个WorkerW窗口
		HWND workerw = FindWindowEx(0, tophandle, _T("WorkerW"), 0);
		//发消息直接关掉可能并不优雅
		//SendMessage(window_hwnd, 16, 0, 0);
		//将它保存起来，当然你可以像我一样直接在这里将它隐藏
		ShowWindow(workerw, SW_HIDE);
		//保存时注意这里的指针操作
		*(HWND *)topparamhandle = workerw;
	}
	//这里必须返回TRUE,返回FALSE就不在枚举了
	return true;
}

HWND GetWallpaperParentHWND() {
	HWND windowHandle = FindWindow(_T("Progman"), _T("Program Manager"));
	//使用 0x3e8 命令分割出两个WorkerW
	//消息处理结果
	DWORD response = 0;
	LRESULT result = SendMessageTimeout(windowHandle, 0x52c, 0, 0, SMTO_NORMAL, 0x3e8, (PDWORD_PTR)&response);
	//找到分离出来的WorkerW并隐藏中间那个WorkerW
	HWND workerW = nullptr;
	EnumWindows(EnumWindowsProc, (LPARAM)&workerW);
	//因为在枚举过程中已经将它隐藏了，这里就不做了
	//ShowWindow(workerw, SW_HIDE);

	return windowHandle;
}

RECT caculatePos(HWND wallpaperHwnd)
{
	RECT windowRect = { 0,0,0,0 };
	RECT clientRect = { 0,0,0,0 };
	GetWindowRect(wallpaperHwnd, &windowRect);
	GetClientRect(wallpaperHwnd, &clientRect);
	int borderWidth = (windowRect.right - windowRect.left - clientRect.right) / 2;
	int borderHeight = (windowRect.bottom - windowRect.top - clientRect.bottom) / 2;
	int fullX = GetSystemMetrics(SM_CXFULLSCREEN);
	//这里桌面高度拿到的值莫名其妙比实际值小，,,ԾㅂԾ,,
	//int fullY = GetSystemMetrics(SM_CYFULLSCREEN);
	//fullY +=95;

	RECT pos = { -borderWidth,-borderHeight-95,fullX+2* borderWidth,1080+95};
	return pos;
}

HWND GetWallpaperHWND() {
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

	//这里应该有个超时检测，以程序未运行时便报告找不到程序，
	//暂时使用计数菌来计算超时
	int times=0;
	while (!firefox)
	{
		//找不到就放弃CPU执行时间，等会再找
		Sleep(0);
		firefox = FindWindow(_T("MozillaWindowClass"), _T("桌布 - Mozilla Firefox"));
		times++;
		if (times>100)
		{
			break;
		}
	}
	return firefox;
}