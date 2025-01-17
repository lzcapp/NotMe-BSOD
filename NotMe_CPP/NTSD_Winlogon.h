#ifndef TRIGGER_BSOD_NTSD_WINLOGON_H
#define TRIGGER_BSOD_NTSD_WINLOGON_H

#include <windows.h>
#include <tlhelp32.h>
#include <cstdio>

inline DWORD FindPID(const char *procname) {
    PROCESSENTRY32 pe;
    DWORD pid = NULL;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return NULL;
    }

    pe.dwSize = sizeof(PROCESSENTRY32);
    BOOL hResult = Process32First(hSnapshot, &pe);

    while (hResult) {
        if (strcmp(procname, pe.szExeFile) == 0) {
            pid = pe.th32ProcessID;
            break;
        }
        hResult = Process32Next(hSnapshot, &pe);
    }

    CloseHandle(hSnapshot);

    return pid;
}

#endif //TRIGGER_BSOD_NTSD_WINLOGON_H
