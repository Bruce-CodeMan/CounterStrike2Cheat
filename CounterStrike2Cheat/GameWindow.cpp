#include "GameWindow.h"

GameWindow gameWindow;

void GameWindow::Initialize()
{
	this->hwnd = FindWindow(NULL, L"Counter-Strike 2");

	if (!this->hwnd) {
		// ¥ÌŒÛ¥¶¿Ì
		MessageBox(NULL, L"Unable to Find the CS2 window", L"ERROR", MB_ICONERROR);
	}
}