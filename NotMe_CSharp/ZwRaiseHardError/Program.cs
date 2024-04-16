using System;
using System.Runtime.InteropServices;

namespace ZwRaiseHardError {
    public abstract class Program {
        [DllImport("ntdll.dll")]
        private static extern uint RtlAdjustPrivilege(int privilege, bool bEnablePrivilege, bool isThreadPrivilege, out bool previousValue);

        [DllImport("ntdll.dll")]
        private static extern uint ZwRaiseHardError(uint errorStatus, uint numberOfParameters, uint unicodeStringParameterMask, IntPtr parameters, uint validResponseOption, out uint response);

        private const int Privilege = 19;

        private const uint ErrorStatus = 0xc0000022;

        private const uint ValidResponseOption = 6;

        private static void Main() {
            ZwRaiseHardError();
        }

        public static void ZwRaiseHardError() {
            _ = RtlAdjustPrivilege(Privilege, true, false, out _);

            ZwRaiseHardError(ErrorStatus, 0, 0, IntPtr.Zero, ValidResponseOption, out _);
        }
    }
}