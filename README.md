# NotMe

**:warning: SOLELY FOR SECURITY RESEARCH PURPOSES. DO NOT USE THIS REPO FOR ILLEGAL PURPOSES. :warning:**

The name "**NotMe**" is inspired by the Microsoft tool "**NotMyFault**", also a tool that can cause BSOD (Blue Screen of Death) on Windows system.

## Project Structure

### NotMe_CMake

Orginal `C++` project that uses `CMake` to build.

### NotMe_VCPP

`C++` project created with `Visual Studio 2010` on `Windows XP`.

### NotMe_GUI

`C#` and `.Net Framework 4`.

### NotMe_Console

`C#` and `.Net Framework 4`.

## NtRaiseHardError & ZwRaiseHardError

Both functions are undocumented `Windows APIs (NTAPI)` included in `ntdll.dll`, which can
cause `BlueScreen (BSOD, Blue Screen of Death)` with certain parameters.

### NtRaiseHardError

```C++
NtRaiseHardError(
  IN  NTSTATUS                  ErrorStatus,
  IN  ULONG                     NumberOfParameters,
  IN  PUNICODE_STRING           UnicodeStringParameterMask OPTIONAL,
  IN  PVOID                     *Parameters,
  IN  HARDERROR_RESPONSE_OPTION ResponseOption,
  OUT PHARDERROR_RESPONSE       Response
);
```

### ZwRaiseHardError

```C++
ZwRaiseHardError(
  IN  NTSTATUS                  ErrorStatus,
  IN  ULONG                     NumberOfParameters,
  IN  PUNICODE_STRING           UnicodeStringParameterMask OPTIONAL,
  IN  PVOID                     *Parameters,
  IN  HARDERROR_RESPONSE_OPTION ResponseOption,
  OUT PHARDERROR_RESPONSE       Response
);
```

### Parameters

#### PUNICODE_STRING

```C++
#include <SubAuth.h>
```

```C++
typedef struct _UNICODE_STRING {
 USHORT Length;
 USHORT MaximumLength;
 PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;
```

#### HARDERROR_RESPONSE_OPTION

```C++
typedef enum _HARDERROR_RESPONSE_OPTION {
 OptionAbortRetryIgnore,
 OptionOk,
 OptionOkCancel,
 OptionRetryCancel,
 OptionYesNo,
 OptionYesNoCancel,
 OptionShutdownSystem
} HARDERROR_RESPONSE_OPTION, *PHARDERROR_RESPONSE_OPTION;
```

#### PHARDERROR_RESPONSE

```C++
typedef enum _HARDERROR_RESPONSE {
 ResponseReturnToCaller,
 ResponseNotHandled,
 ResponseAbort,
 ResponseCancel,
 ResponseIgnore,
 ResponseNo,
 ResponseOk,
 ResponseRetry,
 ResponseYes
} HARDERROR_RESPONSE, *PHARDERROR_RESPONSE;
```

## RtlSetProcessIsCritical

`RtlSetProcessIsCritical` is yet another undocumented function hidden in the Windows kernel. It is one of the few which
do not have a kernel32 equivalent.

`RtlSetProcessIsCritical` sets a process to a system critical status. This means that the process is now "critical" to
the running of Windows, which also means that on termination of your process, Windows itself terminates as well. When a
system critical process ends/terminates, the stop code is CRITICAL_PROCESS_DIED (0xEF) for process exiting, and
CRITICAL_OBJECT_TERMINATION (0xF4) if the process was abnormally terminated.

```C++
NTSTATUS RtlSetProcessIsCritical (
    BOOLEAN bNew,     // new setting for process
    BOOLEAN *pbOld,     // pointer which receives old setting (can be null)
    BOOLEAN bNeedScb    // need system critical breaks
);
```

This means that calling `RtlSetProcessIsCritical(TRUE, NULL, FALSE)` would make a process critical, while another call
to `RtlSetProcessIsCritical(FALSE, NULL, FALSE)` would return the process to normal. When critical status is set,
termination or ending of the process in any way will usually cause either a BSOD (if BSOD-ing is enabled), or will cause
the system to reboot itself.

### Usage

The use of this function requires the `SE_DEBUG_NAME` privilege in the calling process. This can easily be obtained
using `AdjustTokenPrivileges`.

First obtain the privilege, then set the process itself to be critical. Simply ending the process by `return 0;` will
cause the BSOD.

```C++
AdjustPrivilege(20UL, TRUE, FALSE, &b);

SetCriticalProcess(TRUE, NULL, FALSE);

return 0;
```

## Compatibility

Assumingly, works on all Windows systems with `Windows NT kernel`, tested on `Windows XP`, `Windows 7`, `Windows 10` and `Windows 11`.

### NtRaiseHardError & ZwRaiseHardError

Does not triger the `UAC (User Account Control) prompt`.

### RtlSetProcessIsCritical

Needs `Administrator privilege` / trigers `UAC (User Account Control)` on `Winodws 10` and `Windows 11`.
