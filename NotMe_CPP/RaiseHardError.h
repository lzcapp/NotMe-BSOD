#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-reserved-identifier"
#ifndef TRIGGER_BSOD_RAISEHARDERROR_H
#define TRIGGER_BSOD_RAISEHARDERROR_H

#define Error_Status 0xC0000002
#define SE_SHUTDOWN_PRIVILEGE 0x13

#include <windows.h>
#include <SubAuth.h>

typedef enum _HARDERROR_RESPONSE_OPTION {
    OptionAbortRetryIgnore,
    OptionOk,
    OptionOkCancel,
    OptionRetryCancel,
    OptionYesNo,
    OptionYesNoCancel,
    OptionShutdownSystem
} HARDERROR_RESPONSE_OPTION, * PHARDERROR_RESPONSE_OPTION;

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
} HARDERROR_RESPONSE, * PHARDERROR_RESPONSE;

typedef NTSTATUS(NTAPI *pdef_RtlAdjustPrivilege)(
        ULONG       Privilege,
        BOOLEAN     Enable,
        BOOLEAN     CurrentThread,
        PBOOLEAN    Enabled
);

typedef NTSTATUS(NTAPI *pdef_NtRaiseHardError)(
        NTSTATUS                    ErrorStatus,
        ULONG                       NumberOfParameters,
        PUNICODE_STRING             UnicodeStringParameterMask OPTIONAL,
        PULONG_PTR                  Parameters,
        HARDERROR_RESPONSE_OPTION   ResponseOption,
        PHARDERROR_RESPONSE         Response
);

typedef NTSTATUS(NTAPI *pdef_ZwRaiseHardError)(
        NTSTATUS                    ErrorStatus,
        ULONG                       NumberOfParameters,
        PUNICODE_STRING             UnicodeStringParameterMask OPTIONAL,
        PULONG_PTR                  Parameters,
        HARDERROR_RESPONSE_OPTION   ResponseOption,
        PHARDERROR_RESPONSE         Response
);

#endif //TRIGGER_BSOD_RAISEHARDERROR_H

#pragma clang diagnostic pop