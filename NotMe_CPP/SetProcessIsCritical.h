#ifndef TRIGGER_BSOD_SETPROCESSISCRITICAL_H
#define TRIGGER_BSOD_SETPROCESSISCRITICAL_H

#define SE_DEBUG_PRIVILEGE 0x14

#include <windows.h>

typedef NTSTATUS(NTAPI *pdef_RtlAdjustPrivilege)(
        ULONG       Privilege,
        BOOLEAN     Enable,
        BOOLEAN     Client,
        PBOOLEAN    WasEnabled
);

typedef NTSTATUS(NTAPI *pdef_RtlSetProcessIsCritical)(
        IN      BOOLEAN     NewValue,
        OUT     PBOOLEAN    OldValue    OPTIONAL,
        IN      BOOLEAN     CheckFlag
);

#endif //TRIGGER_BSOD_SETPROCESSISCRITICAL_H
