#include "ExternalWindow.h"

/*
	1. 注册窗口类
	2. 创建窗口
	3. 显示和更新窗口
	4. 创建消息循环
	5. 实现窗口过程调用
	6. 销毁窗口
*/

// 实现窗口过程函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_PAINT:
		break;
	case WM_CREATE:
		break;
	case WM_DESTROY:
		// 当WM_DETROY消息被接收的时候,表示窗口正在被销毁,通知应用程序主消息循环结束
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		// 响应WM_CLOSE的时候销毁窗口
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void CreateExternalWindow()
{
	MSG msg;
	// 将内存区域清零
	ZeroMemory(&msg, sizeof(msg));
	// 用于获取窗口的外部矩阵尺寸
	GetWindowRect(gameWindow.hwnd, &overlayWindow.gameRect);

	// 设计窗口
	WNDCLASSEX wce;
	ZeroMemory(&wce, sizeof(wce));
	wce.cbSize = sizeof(wce);  // 设置窗口的大小
	wce.style = CS_HREDRAW | CS_VREDRAW;
	wce.lpfnWndProc = (WNDPROC)WindowProc;
	wce.hInstance = GetModuleHandle(NULL);
	wce.hCursor = LoadCursor(NULL, IDC_ARROW);  // 窗口鼠标样式
	wce.hbrBackground = (HBRUSH)RGB(0, 0, 0);   // 窗口背景颜色
	wce.lpszClassName = L"ExternalWindow";

	// 注册窗口类
	if (!RegisterClassEx(&wce)) {
		std::cout << "Window Registration Failed!" << std::endl;
		return;
	}
	overlayWindow.overlayHwnd = CreateWindowEx(
		WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
		wce.lpszClassName,
		L"ExWindow",
		WS_POPUP,
		overlayWindow.gameRect.left,
		overlayWindow.gameRect.top,
		overlayWindow.gameRect.right - overlayWindow.gameRect.left,
		overlayWindow.gameRect.bottom - overlayWindow.gameRect.top,
		NULL,
		NULL,
		wce.hInstance,
		NULL
	);

	if (!overlayWindow.overlayHwnd) {
		std::cout << "Window Creation Failed!" << std::endl;
		return;
	}

	// 设置窗口透明
	SetLayeredWindowAttributes(overlayWindow.overlayHwnd, RGB(0, 0, 0), 0, LWA_ALPHA);

	// 显示窗口
	ShowWindow(overlayWindow.overlayHwnd, SW_SHOW);
	UpdateWindow(overlayWindow.overlayHwnd);

	while (msg.message != WM_QUIT) {
		SetWindowPos(
			overlayWindow.overlayHwnd,
			HWND_NOTOPMOST,
			overlayWindow.gameRect.left,
			overlayWindow.gameRect.top,
			overlayWindow.gameRect.right - overlayWindow.gameRect.left,
			overlayWindow.gameRect.bottom - overlayWindow.gameRect.top,
			SWP_SHOWWINDOW);
		GetWindowRect(gameWindow.hwnd, &overlayWindow.gameRect);
		// 从消息队列中获取消息(PeekMessage / GetMessage)
		if (PeekMessage(&msg, overlayWindow.overlayHwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UnregisterClass(wce.lpszClassName, wce.hInstance);
}