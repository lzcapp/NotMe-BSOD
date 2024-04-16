#include "RaiseHardError.h"

int main() {
    auto hNtdll = LoadLibraryA("ntdll.dll");
    if (hNtdll == nullptr) {
        FreeLibrary(hNtdll);
        return -1;
    }

    auto RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege) GetProcAddress(hNtdll, "RtlAdjustPrivilege");
    BOOLEAN enabled;
    if (RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &enabled) != 0) {
        FreeLibrary(hNtdll);
        return -1;
    }

    auto ZwRaiseHardError = (pdef_ZwRaiseHardError) GetProcAddress(hNtdll, "ZwRaiseHardError");
    FreeLibrary(hNtdll);
    HARDERROR_RESPONSE Response;
    return ZwRaiseHardError(Error_Status, 0, nullptr, nullptr, OptionShutdownSystem, &Response);
}