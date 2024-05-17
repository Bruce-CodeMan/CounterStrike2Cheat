#pragma once
#include <Windows.h>

class GameWindow
{
public:
	HWND hwnd = nullptr;  // 游戏窗口句柄

	// 初始化游戏窗口句柄
	void Initialize();
};

extern GameWindow gameWindow;

