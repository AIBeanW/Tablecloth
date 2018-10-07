#include "main.h"
#include<iostream>

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
	HWND wallpaperHwnd = (HWND)0x00200ADC;

	RECT pos = caculatePos(wallpaperHwnd);

	//获得要嵌入窗口的边框
	HWND resultHwnd = nullptr;
	if (GetParent(wallpaperHwnd)!= wallpaperHwnd)
	{
		//嵌入，如果成功返回父窗口句柄
		resultHwnd = SetParent(wallpaperHwnd, wallpaperParentHWND);
		//设置位置并显示
		SetWindowPos(wallpaperHwnd, NULL, pos.left, pos.top, pos.right, pos.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
	}
	else
	{
		//还原，如果成功返回父窗口句柄
		resultHwnd = SetParent(wallpaperHwnd, desktophHwnd);
	}
	return  0;
}
