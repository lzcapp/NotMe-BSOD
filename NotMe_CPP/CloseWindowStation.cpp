#include <windows.h>

int main() {
    DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
    HWINSTA hWinSta = CreateWindowStation("WindowStation", NULL, dwDesiredAccess, nullptr);
    SetHandleInformation(hWinSta, HANDLE_FLAG_PROTECT_FROM_CLOSE, HANDLE_FLAG_PROTECT_FROM_CLOSE);
    return CloseWindowStation(hWinSta);
}