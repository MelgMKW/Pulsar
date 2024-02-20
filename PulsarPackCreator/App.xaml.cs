using System;
using System.Diagnostics;
using System.IO;
using System.Windows;

namespace PulsarPackCreator
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private void OnExit(object sender, ExitEventArgs e)
        {
            PulsarPackCreator.Properties.Settings.Default.Save();
        }

        private void OnAppDeactivated(object sender, EventArgs e)
        {
            //PulsarPackCreator.MainWindow.messageWindow.Hide();
        }
    }
}
