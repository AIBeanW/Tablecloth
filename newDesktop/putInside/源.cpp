#pragma once

#include <windows.h>
//_T("")宏在tchar.h中定义
#include <tchar.h>

//获取桌面窗口
HWND GetWallpaperParentHWND();


//使用winMain来避免使用控制台
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//把参数露出来看一下
	//MessageBox(NULL, lpCmdLine, _T("额外参数"), NULL);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。
	//获取桌面句柄
	HWND desktophHwnd = GetDesktopWindow();
	//获取窗口句柄
	HWND wallpaperParentHWND = GetWallpaperParentHWND();
	//wallpaperParentHWND = (HWND)0x008F0756;

	HWND wallpaperHwnd = nullptr;
	//获取要嵌入窗口的句柄，这里本来是一个很简单的操作，但是为了增加超时等功能，将它独立出去
	//HWND wallpaperHwnd = FindWindow(_T("WMP Skin Host"), _T("Windows Media Player"));
wallpaperHwnd  =(HWND)0x00070F3C;

	HWND resultHwnd = nullptr;

		if (GetParent(wallpaperHwnd) != wallpaperHwnd)
		{
			//嵌入，如果成功返回父窗口句柄
			resultHwnd = SetParent(wallpaperHwnd, wallpaperParentHWND);
			//设置位置并显示
			//SetWindowPos(wallpaperHwnd, NULL, 0, 0, 1366, 768, SWP_NOZORDER | SWP_SHOWWINDOW);
		}
	return 0;
}


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
	//DWORD response = 0;
	//LRESULT result = SendMessageTimeout(windowHandle, 0x52c, 0, 0, SMTO_NORMAL, 0x3e8, (PDWORD_PTR)&response);
	//找到分离出来的WorkerW并隐藏中间那个WorkerW
	//HWND workerW = nullptr;
	//EnumWindows(EnumWindowsProc, (LPARAM)&workerW);
	//因为在枚举过程中已经将它隐藏了，这里就不做了
	//ShowWindow(workerw, SW_HIDE);

	return windowHandle;
}
