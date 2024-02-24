using System;
using System.Windows;

namespace Pulsar_Pack_Creator
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private void OnExit(object sender, ExitEventArgs e)
        {
            Pulsar_Pack_Creator.Properties.Settings.Default.Save();
        }

        private void OnAppDeactivated(object sender, EventArgs e)
        {
            //Pulsar_Pack_Creator.MainWindow.messageWindow.Hide();
        }
    }
}
