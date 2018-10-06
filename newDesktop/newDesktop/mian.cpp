#include "main.h"
#include <windows.h>
//_T("")宏在tchar.h中定义
#include <tchar.h>
#include<iostream>

//声明重载EnumWindows回调函数EnumWindowsProc
extern BOOL CALLBACK  EnumWindowsProc(HWND hwnd, LPARAM lParam);
HWND GetWallpaperParentHWND();

int main()
{
	//获取桌面句柄
	HWND desktophHwnd =GetDesktopWindow();

	//获取窗口句柄
	HWND wallpaperParentHWND = GetWallpaperParentHWND();

	//while (true)
	//{
	//	POINT pNow = { 0,0 };
	//	if (GetCursorPos(&pNow))  // 获取鼠标当前位置
	//	{
	//		HWND hwndPointNow = NULL;
	//		hwndPointNow = WindowFromPoint(pNow);  // 获取鼠标所在窗口的句柄
	//		std::cout << hwndPointNow << std::endl;
	//		Sleep(0);
	//	}
	//}
	
	//获取要嵌入窗口的句柄
	//HWND wallpaperHwnd = FindWindow(_T("WMP Skin Host"), _T("Windows Media Player"));
	HWND wallpaperHwnd = (HWND)0x002F1B1E;

	
	//获得要嵌入窗口的边框
	RECT windowRect = { 0,0,0,0 };
	RECT clientRect = { 0,0,0,0 };
	GetWindowRect(wallpaperHwnd, &windowRect);
	GetClientRect(wallpaperHwnd, &clientRect);
	int borderWidth = (windowRect.right - windowRect.left - clientRect.right) / 2;
	int borderHeight = (windowRect.bottom - windowRect.top - clientRect.bottom) / 2;
	int fullX = GetSystemMetrics(SM_CXFULLSCREEN);
	//这里桌面高度拿到的值莫名其妙比实际值小，,,ԾㅂԾ,,
	int fullY = GetSystemMetrics(SM_CYFULLSCREEN);
	fullY += 23;
	HWND resultHwnd = nullptr;
	//嵌入，如果成功返回父窗口句柄
	resultHwnd=SetParent(wallpaperHwnd, wallpaperParentHWND);
	SetWindowPos(wallpaperHwnd, NULL, -borderWidth, -borderHeight, fullX+2* borderWidth,fullY+3*borderHeight, SWP_NOZORDER|SWP_SHOWWINDOW);
	//system("pause");

	//还原，如果成功返回父窗口句柄
	resultHwnd=SetParent(wallpaperHwnd,desktophHwnd);
	//system("pause");
	return  0;
}

BOOL CALLBACK EnumWindowsProc(_In_ HWND   tophandle, _In_ LPARAM topparamhandle) {
	//如果是桌面图标的窗口;
	if (FindWindowEx(tophandle, 0, L"SHELLDLL_DefView", nullptr) != nullptr)
	{
		//查找tophandle所对应的下一个WorkerW窗口
		 HWND workerw = FindWindowEx(0, tophandle, L"WorkerW", 0);
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
	LRESULT result=SendMessageTimeout(windowHandle, 0x52c, 0, 0, SMTO_NORMAL, 0x3e8, (PDWORD_PTR)&response);
	//找到分离出来的WorkerW并隐藏中间那个WorkerW
	HWND workerW = nullptr;
	EnumWindows(EnumWindowsProc, (LPARAM)&workerW);
	//因为在枚举过程中已经将它隐藏了，这里就不做了
	//ShowWindow(workerw, SW_HIDE);

	return windowHandle;
}
