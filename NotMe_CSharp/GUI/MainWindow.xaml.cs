﻿using System.Windows;

namespace NotMe {
    public partial class MainWindow {
        public MainWindow() {
            InitializeComponent();
        }

        private void BtnNtRaiseHardError_Click(object sender, RoutedEventArgs e) {
            NtRaiseHardError.Program.NtRaiseHardError();
        }

        private void BtnZwRaiseHardError_Click(object sender, RoutedEventArgs e) {
            ZwRaiseHardError.Program.ZwRaiseHardError();
        }

        private void BtnSetProcessIsCritical_Click(object sender, RoutedEventArgs e) {
            SetProcessIsCritical.Program.SetProcessIsCritical();
        }

        private void BtnCloseWindowStation_Click(object sender, RoutedEventArgs e) {
            CloseWindowStation.Program.CloseWindowStation();
        }
    }
}