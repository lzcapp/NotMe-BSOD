# Trigger-BSOD

**:warning: SOLELY FOR SECURITY RESEARCH PURPOSES. DO NOT USE THIS REPO FOR ILLEGAL PURPOSES. :warning:**

## NtRaiseHardError & ZwRaiseHardError

Both functions are undocumented `Windows APIs (NTAPI)` included in `ntdll.dll`, which can cause `BlueScreen (BSOD, Blue Screen of Death)` with certain parameters.

**Does not triger the `UAC (User Account Control) prompt`**. Assumingly, it works on all Windows systems with `Windows NT kernel`, tested on `Windows 7`, `Windows 10` and `Windows 11`. 

### NtRaiseHardError

```c++
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

```c++
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

```c++
#include <SubAuth.h>
```

```c++
typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;
```

#### HARDERROR_RESPONSE_OPTION

```c++
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

```c++
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

`RtlSetProcessIsCritical` is yet another undocumented function hidden in the Windows kernel. It is one of the few which do not have a kernel32 equivalent.

- Previously: With `MinGW64` (from MSYS2), `CMake 3.22`, `C++11`.
- Currently : With `Visual Studio 17 2022`, `CMake 3.27.8`, `C++11`.

## VirusTotal
- `NtRaiseHardError.exe`: https://www.virustotal.com/gui/file/ac6bc7eb49c62ef1fe68dd952dbb5091d590bff4215b9417cd4ff71b98a0d249
- `ZwRaiseHardError.exe`: https://www.virustotal.com/gui/file/4398a612f44c3c4fc3c8600dcd2fbc1aba68962c8602e01042dfc86835eec19c

