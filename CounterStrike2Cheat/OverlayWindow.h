#pragma once
#include <Windows.h>

class OverlayWindow
{
public:
	HWND overlayHwnd;  // �ɰ洰�ھ��
	RECT gameRect;	   // cs2��Ϸ���ڴ�С��Ϣ
};

extern OverlayWindow overlayWindow;