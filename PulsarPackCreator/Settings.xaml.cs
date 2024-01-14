using System;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Net.Http;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using static PulsarPackCreator.MsgWindow;

namespace PulsarPackCreator
{
    public partial class SettingsWindow : Window
    {
        public SettingsWindow()
        {
            InitializeComponent();
        }

        public void Load()
        {
            AutoUpdater.IsChecked = Pulsar_Pack_Creator.Properties.Settings.Default.AutoUpdate;
            Show();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }
        private void OnAutoUpdateToggle(object sender, RoutedEventArgs e)
        {
            if ((sender as CheckBox).IsKeyboardFocused)
            {
                Pulsar_Pack_Creator.Properties.Settings.Default.AutoUpdate = !Pulsar_Pack_Creator.Properties.Settings.Default.AutoUpdate;
            }
        }

        public enum UpdateResult
        {
            Success = 0,
            NoServer = 1,
            Other = 2
        }

        private void OnUpdateClick(object sender, RoutedEventArgs e)
        {
            TryUpdate();
        }

        private void OnSaveSettingsClick(object sender, RoutedEventArgs e)
        {
            Hide();
        }

        public static string GetChangelog()
        {
            using (HttpClient client = new HttpClient())
            {
                return client.GetStringAsync("https://pulsar.brawlbox.co.uk/PulsarPackCreatorVERSION.txt").Result;
            }
        }

        public static string GetVersion()
        {
            return GetChangelog().Split("\r\n")[0].Replace("·Updated to ", "");
        }

        public static void TryUpdate()
        {
            if (CheckUpdates())
            {

                MsgWindowResult result = MsgWindow.Show("A new update is available. Updating will close the software and you will lose all current data. Proceed?",
                   "Updater", MsgWindowButton.YesNo, MainWindow.settingsWindow);
                if (result == MsgWindowResult.Yes)
                {
                    UpdateResult ret = Update();

                    string msg;
                    switch (ret)
                    {
                        case UpdateResult.Success:
                            msg = "Update successful";
                            break;
                        case UpdateResult.NoServer:
                            msg = "Unable to contact the update server. You can manually get the latest version at https://github.com/MelgMKW/Pulsar/releases";
                            break;
                        default:
                            msg = "Failed to update.";
                            break;
                    }
                    MsgWindow.Show(msg, MainWindow.settingsWindow);
                }
            }
            else MsgWindow.Show("You are already using the latest version.", MainWindow.settingsWindow);
        }

        public static UpdateResult Update()
        {

            string curExe = $"{AppDomain.CurrentDomain.FriendlyName}";

            using (HttpClient client = new HttpClient())
            {
                try
                {
                    byte[] responseArray = client.GetByteArrayAsync("https://pulsar.brawlbox.co.uk/Pulsar%20Pack%20Creator.exe").Result;
                    File.WriteAllBytes("new.bin", responseArray);
                }
                catch (Exception)
                {
                    return UpdateResult.NoServer;
                }
            }

            string curDir = Directory.GetCurrentDirectory();
            string version = Assembly.GetExecutingAssembly().GetName().Version.ToString();
            version = version.Substring(0, version.Length - 2);
            using Process updater = new Process();
            {
                updater.StartInfo.FileName = @"powershell.exe";
                updater.StartInfo.Arguments = $"Wait-Process -name '{curExe}'; cd {curDir}; del '{curExe}.exe'; ren new.bin '{curExe}.exe'; Start-Process '{curExe}.exe' -ArgumentList '·Updated to {version}'; Wait-Process Notepad;";
                updater.StartInfo.Verb = "runas";
                updater.StartInfo.CreateNoWindow = true;
                updater.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
                updater.StartInfo.UseShellExecute = false;
                updater.Start();
            }

            /*using Process updater = new Process();
            {
                updater.StartInfo.FileName = @"cmd.exe";
                updater.StartInfo.Arguments = $"/c timeout 5 & cd {curDir} & del {curExe} & ren mymap.raw {curExe} & {curExe} ";
                updater.StartInfo.Verb = "runas";
                updater.Start();
            }
            */

            Environment.Exit(0);
            return UpdateResult.Success;
        }

        public static bool CheckUpdates()
        {
            string version = Assembly.GetExecutingAssembly().GetName().Version.ToString();
            string newVersion = GetVersion();
            return newVersion != version.Substring(0, version.Length - 2);
        }

        public static void DisplayChangelog(string oldVersion)
        {
            string allChangelogs = GetChangelog();
            int idxVersion = allChangelogs.IndexOf('·');

            string changelog = allChangelogs.Substring(idxVersion, 17);
            while (idxVersion >= 0)
            {
                string curVersion = allChangelogs.Substring(idxVersion, 17);
                int prevIdxVersion = idxVersion;
                idxVersion = allChangelogs.IndexOf('·', idxVersion + 1);
                if (curVersion != oldVersion)
                {
                    if(idxVersion >= 0)
                    {
                        changelog += allChangelogs.Substring(17 + prevIdxVersion, idxVersion - (prevIdxVersion + 21));
                    }
                    else
                    {
                        changelog += allChangelogs.Substring(prevIdxVersion + 17, allChangelogs.Length - (prevIdxVersion + 17));
                    }
                    
                }

            }

            //string version = allChangelogs
            MsgWindow.Show(changelog);
        }

        private void OnExitRemindToggle(object sender, RoutedEventArgs e)
        {
            if ((sender as CheckBox).IsKeyboardFocused)
            {
                Pulsar_Pack_Creator.Properties.Settings.Default.ExitRemind = !Pulsar_Pack_Creator.Properties.Settings.Default.ExitRemind;
            }
        }
    }
}
