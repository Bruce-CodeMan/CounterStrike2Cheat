#pragma once
#include <Windows.h>

class OverlayWindow
{
public:
	HWND overlayHwnd;  // 蒙版窗口句柄
	RECT gameRect;	   // cs2游戏窗口大小信息
};

extern OverlayWindow overlayWindow;