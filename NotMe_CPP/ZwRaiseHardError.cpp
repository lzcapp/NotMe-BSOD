#include <windows.h>
#include "RaiseHardError.h"

int main() {
    auto ntdll = LoadLibraryA("ntdll.dll");
    if (ntdll == nullptr) {
        return 0;
    }

    auto RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege) GetProcAddress(ntdll, "RtlAdjustPrivilege");
    BOOLEAN enabled;
    if (RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &enabled) != 0) {
        return 0;
    }

    auto ZwRaiseHardError = (pdef_ZwRaiseHardError) GetProcAddress(ntdll, "ZwRaiseHardError");
    ULONG response;
    ZwRaiseHardError(Error_Status, 0, 0, nullptr, OPTION_SHUTDOWN, &response);
}