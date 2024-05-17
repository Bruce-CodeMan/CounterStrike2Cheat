#include "ExternalWindow.h"

/*
	1. ע�ᴰ����
	2. ��������
	3. ��ʾ�͸��´���
	4. ������Ϣѭ��
	5. ʵ�ִ��ڹ��̵���
	6. ���ٴ���
*/

// ʵ�ִ��ڹ��̺���
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_PAINT:
		break;
	case WM_CREATE:
		break;
	case WM_DESTROY:
		// ��WM_DETROY��Ϣ�����յ�ʱ��,��ʾ�������ڱ�����,֪ͨӦ�ó�������Ϣѭ������
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		// ��ӦWM_CLOSE��ʱ�����ٴ���
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void CreateExternalWindow()
{
	MSG msg;
	// ���ڴ���������
	ZeroMemory(&msg, sizeof(msg));
	// ���ڻ�ȡ���ڵ��ⲿ����ߴ�
	GetWindowRect(gameWindow.hwnd, &overlayWindow.gameRect);

	// ��ƴ���
	WNDCLASSEX wce;
	ZeroMemory(&wce, sizeof(wce));
	wce.cbSize = sizeof(wce);  // ���ô��ڵĴ�С
	wce.style = CS_HREDRAW | CS_VREDRAW;
	wce.lpfnWndProc = (WNDPROC)WindowProc;
	wce.hInstance = GetModuleHandle(NULL);
	wce.hCursor = LoadCursor(NULL, IDC_ARROW);  // ���������ʽ
	wce.hbrBackground = (HBRUSH)RGB(0, 0, 0);   // ���ڱ�����ɫ
	wce.lpszClassName = L"ExternalWindow";

	// ע�ᴰ����
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

	// ���ô���͸��
	SetLayeredWindowAttributes(overlayWindow.overlayHwnd, RGB(0, 0, 0), 0, LWA_ALPHA);

	// ��ʾ����
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
		// ����Ϣ�����л�ȡ��Ϣ(PeekMessage / GetMessage)
		if (PeekMessage(&msg, overlayWindow.overlayHwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UnregisterClass(wce.lpszClassName, wce.hInstance);
}