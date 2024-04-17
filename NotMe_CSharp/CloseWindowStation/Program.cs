using System;
using System.Runtime.InteropServices;

namespace CloseWindowStation {
    public abstract class Program  {
        [DllImport("user32.dll")]
        private static extern IntPtr CreateWindowStation(string lpwinsta, uint dwFlags, uint dwDesiredAccess, IntPtr lpsa);

        [DllImport("kernel32.dll")]
        private static extern bool SetHandleInformation(IntPtr hObject, uint dwMask, uint dwFlags);

        [DllImport("user32.dll")]
        private static extern bool CloseWindowStation(IntPtr hWinSta);

        private const long GENERIC_READ = 0x80000000L;

        private const long GENERIC_WRITE = 0x40000000L;

        private const int HANDLE_FLAG_PROTECT_FROM_CLOSE = 0x2;

        private static void Main() {
            CloseWindowStation();
        }

        public static void CloseWindowStation() {
            try {
                const uint dwDesiredAccess = (uint)(GENERIC_READ | GENERIC_WRITE);
                IntPtr hWinSta = CreateWindowStation("WindowStation", 0, dwDesiredAccess, IntPtr.Zero);
                SetHandleInformation(hWinSta, HANDLE_FLAG_PROTECT_FROM_CLOSE, HANDLE_FLAG_PROTECT_FROM_CLOSE);
                CloseWindowStation(hWinSta);
            } catch (Exception) {
                // ignored
            }
        }
    }
}