#include "main.h"
#include <windows.h>
#include<iostream>

//使用winMain来避免使用控制台
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//把参数露出来看一下
	MessageBox(NULL, lpCmdLine, _T("额外参数"), NULL);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。
	//获取桌面句柄
	HWND desktophHwnd = GetDesktopWindow();
	//获取窗口句柄
	HWND wallpaperParentHWND = GetWallpaperParentHWND();

	HWND wallpaperHwnd = nullptr;
	//获取要嵌入窗口的句柄，这里本来是一个很简单的操作，但是为了增加超时等功能，将它独立出去
	//HWND wallpaperHwnd = FindWindow(_T("WMP Skin Host"), _T("Windows Media Player"));
	wallpaperHwnd = GetWallpaperHWND();

	HWND resultHwnd = nullptr;

	if (!wallpaperHwnd)
	{
		//找不到的话，看一下它在桌面上吗，不在的话就退出，在的话将它还原
		wallpaperHwnd = FindWindowEx(wallpaperParentHWND, nullptr, _T("MozillaWindowClass"), _T("桌布 - Mozilla Firefox"));
		if (!wallpaperHwnd)
		{
			MessageBox(NULL, _T("未找到桌布窗口"), _T("桌布"), NULL);
		}
		else
		{
			//还原，如果成功返回父窗口句柄
			resultHwnd = SetParent(wallpaperHwnd, desktophHwnd);
		}
		return 0;
	}
	else
	{
		//计算桌布的位置，根据需求改。暂时这样子。
		RECT pos = caculatePos(wallpaperHwnd);
		if (GetParent(wallpaperHwnd) != wallpaperHwnd)
		{
			//嵌入，如果成功返回父窗口句柄
			resultHwnd = SetParent(wallpaperHwnd, wallpaperParentHWND);
			//设置位置并显示
			SetWindowPos(wallpaperHwnd, NULL, pos.left, pos.top, pos.right, pos.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
		}
	}
	return 0;
}
