#pragma once
#include <Windows.h>

class GameWindow
{
public:
	HWND hwnd = nullptr;  // ��Ϸ���ھ��

	// ��ʼ����Ϸ���ھ��
	void Initialize();
};

extern GameWindow gameWindow;

