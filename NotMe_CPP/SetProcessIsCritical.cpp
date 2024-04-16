#include <windows.h>

typedef long (WINAPI *RtlSetProcessIsCritical)(IN BOOLEAN bNew, OUT BOOLEAN *pbOld, IN BOOLEAN bNeedScb);

BOOL AdjustProcessTokenPrivilege(LPCSTR lpszPriv) {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    ZeroMemory(&tkp, sizeof(tkp));

    if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken)) {
        return FALSE;
    }

    if (!LookupPrivilegeValue(nullptr, lpszPriv, &tkp.Privileges[0].Luid)) {
        CloseHandle(hToken);
        return FALSE;
    }
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), nullptr, nullptr);
    CloseHandle(hToken);
    return bRet;
}

int main() {
    // Enable the SE_DEBUG_NAME privilege
    if (AdjustProcessTokenPrivilege((LPCSTR) SE_DEBUG_NAME) != TRUE) {
        return -1;
    }

    auto hNtdll = LoadLibraryA("ntdll.dll");
    if (hNtdll == nullptr) {
        FreeLibrary(hNtdll);
        return -1;
    }

    // Declare the function and obtain it using GetProcAddress
    auto SetCriticalProcess = (RtlSetProcessIsCritical) GetProcAddress(hNtdll, "RtlSetProcessIsCritical");
    if (!SetCriticalProcess) {
        FreeLibrary(hNtdll);
        return -1;
    }
    FreeLibrary(hNtdll);
    SetCriticalProcess(TRUE, nullptr, FALSE);

    // Now the process is critical, simply end it
    return 0;
}
