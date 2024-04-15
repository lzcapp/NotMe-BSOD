#include <windows.h>

int main() {
    HWINSTA hWinSta;
    hWinSta = CreateWindowStation("WindowStation", NULL, 55, nullptr);
    SetHandleInformation(hWinSta, HANDLE_FLAG_PROTECT_FROM_CLOSE, HANDLE_FLAG_PROTECT_FROM_CLOSE);
    CloseWindowStation(hWinSta);
    return 0;
}