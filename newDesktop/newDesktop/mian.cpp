#include "main.h"
#include<iostream>

int main()
{
	//获取桌面句柄
	HWND desktophHwnd =GetDesktopWindow();
	//获取窗口句柄
	HWND wallpaperParentHWND = GetWallpaperParentHWND();


	HWND wallpaperHwnd = nullptr;
	//获取要嵌入窗口的句柄，这里本来是一个很简单的操作，但是为了增加超时等功能，将它独立出去
	//HWND wallpaperHwnd = FindWindow(_T("WMP Skin Host"), _T("Windows Media Player"));
	wallpaperHwnd =GetWallpaperHWND();

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
		//计算桌布的位置
		RECT pos = caculatePos(wallpaperHwnd);

		if (GetParent(wallpaperHwnd) != wallpaperHwnd)
		{
			//嵌入，如果成功返回父窗口句柄
			resultHwnd = SetParent(wallpaperHwnd, wallpaperParentHWND);
			//设置位置并显示
			SetWindowPos(wallpaperHwnd, NULL, pos.left, pos.top, pos.right, pos.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
		}
	}
	
	return  0;
}
