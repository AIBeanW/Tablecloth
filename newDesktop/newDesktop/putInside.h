#pragma once

#include <windows.h>
//_T("")宏在tchar.h中定义
#include <tchar.h>

//声明重载EnumWindows回调函数EnumWindowsProc
extern BOOL CALLBACK  EnumWindowsProc(HWND hwnd, LPARAM lParam);

//获取桌面窗口
HWND GetWallpaperParentHWND();

//计算目标POS
RECT caculatePos(HWND wallpaperHwnd);

//这段代码暂时先留着
//全局可用与鼠标当前焦点无关
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