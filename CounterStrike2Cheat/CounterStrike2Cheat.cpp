#include <iostream>
#include <Windows.h>

#include "GameWindow.h"
#include "ExternalWindow.h"

using namespace std;

void Init() 
{
    gameWindow.Initialize();
}

int main()
{
    SetConsoleTitle(L"Bruce Compiler");
    HWND console = GetConsoleWindow();
    // Set the console Size
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.right, 500, 700, TRUE);
    cout << "Bruce Compiler" << endl;
    cout << "\n[*] waiting for cs2..." << endl;

    CreateExternalWindow();
}


