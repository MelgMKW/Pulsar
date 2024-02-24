using System;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows;

namespace Pulsar_Pack_Creator
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        /// <summary>
        /// Application Entry Point.
        /// </summary>
        [System.STAThreadAttribute()]
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "8.0.2.0")]
        public static void Main()
        {
            string appGuid = ((GuidAttribute)Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(GuidAttribute), true)[0]).Value;
            using (Mutex mutex = new Mutex(false, "Global\\" + appGuid))
            {
                if (!mutex.WaitOne(0, false))
                {
                    MessageBox.Show("An instance of Pulsar Pack Creator is already running");
                    return;
                }
                Pulsar_Pack_Creator.App app = new Pulsar_Pack_Creator.App();
                app.InitializeComponent();
                app.Run();
            }
        }


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
