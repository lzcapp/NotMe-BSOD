#include <windows.h>

int main() {
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
    HWINSTA hWinSta = CreateWindowStation("WindowStation", NULL, dwDesiredAccess, nullptr);
    SetHandleInformation(hWinSta, HANDLE_FLAG_PROTECT_FROM_CLOSE, HANDLE_FLAG_PROTECT_FROM_CLOSE);
    return CloseWindowStation(hWinSta);
}