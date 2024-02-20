using System;
<<<<<<< Updated upstream
=======
using System.Diagnostics;
using System.IO;
using System.Threading;
>>>>>>> Stashed changes
using System.Windows;

namespace PulsarPackCreator
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {

        static System.Threading.Mutex singleton = new Mutex(true, "Pulsar Pack Creator");
        [System.STAThreadAttribute()]
        public static void Main()
        {
            if (!singleton.WaitOne(TimeSpan.Zero, true))
            {
                MessageBox.Show("An instance of Pulsar Pack Creator is already running.");
                Application.Current.Shutdown();
            }
            PulsarPackCreator.App app = new PulsarPackCreator.App();
            app.InitializeComponent();
            app.Run();
        }

        private void OnExit(object sender, ExitEventArgs e)
        {
            PulsarPackCreator.Properties.Settings.Default.Save();
        }

        private void OnAppDeactivated(object sender, EventArgs e)
        {
            //PulsarPackCreator.MainWindow.msgWindow.Hide();
        }
    }
}
