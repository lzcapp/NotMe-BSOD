#include <Windows.h>
#include <ntstatus.h>

#define SHUTDOWN_PRIVILEGE 19
#define OPTION_SHUTDOWN 6

// function definitions
typedef NTSTATUS(NTAPI *pdef_RtlAdjustPrivilege) (
        ULONG privilege,
        BOOLEAN enable,
        BOOLEAN current_thread,
        PBOOLEAN enabled);
typedef NTSTATUS(NTAPI *pdef_NtRaiseHardError)(
        NTSTATUS error_status,
        ULONG number_of_parameters,
        ULONG unicode_string_parameter_mask,
        PULONG_PTR parameters,
        ULONG response_option,
        PULONG reponse);

int main()
{
    auto RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege)GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
    BOOLEAN enabled;
    if (RtlAdjustPrivilege(SHUTDOWN_PRIVILEGE, TRUE, FALSE, &enabled) == 0)
    {
        auto NtRaiseHardError = (pdef_NtRaiseHardError)GetProcAddress(LoadLibraryA("ntdll.dll"), "NtRaiseHardError");
        ULONG response;
        NtRaiseHardError(STATUS_NOT_IMPLEMENTED, 0, 0, nullptr, OPTION_SHUTDOWN, &response);
    }
}