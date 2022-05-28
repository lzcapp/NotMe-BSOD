# NtRaiseHardError (ntdll)
 
This is an undocumented function in ntdll.dll. Causes a BSOD (Blue Screen of Death) with the error specified by the ErrorStatus parameter.

```c++
UINT NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, PUNICODE_STRING UnicodeStringParameterMask OPTIONAL, PVOID Parameters, HARDERROR_RESPONSE_OPTION ResponseOption, PHARDERROR_RESPONSE Response);
```

 - PHARDERROR_RESPONSE_OPTION
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

 - PHARDERROR_RESPONSE
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

 - PUNICODE_STRING
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

# Build

Build with MinGW64 (from MSYS2), C++ 11.

# VirusTotal

![VirusTotal Result](https://user-images.githubusercontent.com/12462465/170809163-5c77a270-7126-4c40-9a18-9eeecfae3d54.png)
