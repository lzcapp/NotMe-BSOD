using System;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows;

namespace NotMe {
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow {
        [DllImport("ntdll.dll")]
        private static extern uint RtlAdjustPrivilege(int privilege, bool bEnablePrivilege, bool isThreadPrivilege, out bool previousValue);

        [DllImport("ntdll.dll")]
        private static extern uint NtRaiseHardError(uint errorStatus, uint numberOfParameters, uint unicodeStringParameterMask, IntPtr parameters, uint validResponseOption, out uint response);

        [DllImport("ntdll.dll")]
        private static extern uint ZwRaiseHardError(uint errorStatus, uint numberOfParameters, uint unicodeStringParameterMask, IntPtr parameters, uint validResponseOption, out uint response);

        [DllImport("ntdll.dll", SetLastError = true)]
        private static extern void RtlSetProcessIsCritical(uint newValue, uint oldValue, uint checkFlag);

        private const int Privilege = 19;

        private const uint ErrorStatus = 0xc0000022;

        private const uint ValidResponseOption = 6;

        public MainWindow() {
            InitializeComponent();
        }

        private void BtnNtRaiseHardError_Click(object sender, RoutedEventArgs e) {
            _ = RtlAdjustPrivilege(Privilege, true, false, out _);

            NtRaiseHardError(ErrorStatus, 0, 0, IntPtr.Zero, ValidResponseOption, out _);
        }

        private void BtnZwRaiseHardError_Click(object sender, RoutedEventArgs e) {
            _ = RtlAdjustPrivilege(Privilege, true, false, out _);

            ZwRaiseHardError(ErrorStatus, 0, 0, IntPtr.Zero, ValidResponseOption, out _);
        }

        private void BtnRtlSetProcessIsCritical_Click(object sender, RoutedEventArgs e) {
            try {
                Process.EnterDebugMode();
            } catch (System.ComponentModel.Win32Exception exception) {
                MessageBox.Show(exception.ToString(), "Error", MessageBoxButton.OK, MessageBoxImage.Stop);

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

        private void BtnNotMyFault_Click(object sender, RoutedEventArgs e) {

        }
    }
}