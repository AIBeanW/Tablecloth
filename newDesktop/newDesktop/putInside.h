#pragma once

#include <windows.h>
//_T("")����tchar.h�ж���
#include <tchar.h>

//��������EnumWindows�ص�����EnumWindowsProc
extern BOOL CALLBACK  EnumWindowsProc(HWND hwnd, LPARAM lParam);

//��ȡ���洰��
HWND GetWallpaperParentHWND();

//����Ŀ��POS
RECT caculatePos(HWND wallpaperHwnd);

//��δ�����ʱ������
//ȫ�ֿ�������굱ǰ�����޹�
//while (true)
//{
//	POINT pNow = { 0,0 };
//	if (GetCursorPos(&pNow))  // ��ȡ��굱ǰλ��
//	{
//		HWND hwndPointNow = NULL;
//		hwndPointNow = WindowFromPoint(pNow);  // ��ȡ������ڴ��ڵľ��
//		std::cout << hwndPointNow << std::endl;
//		Sleep(0);
//	}
//}