﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Net.Http;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media.Imaging;
using static Pulsar_Pack_Creator.MsgWindow;

namespace Pulsar_Pack_Creator
{
    public partial class SettingsWindow : Window
    {
        public enum ColorMode
        {
            Dark_Mode,
            Light_Mode,
            Space_Mode
        }

        public SettingsWindow()
        {
            InitializeComponent();
        }

        public void Load()
        {
            AutoUpdater.IsChecked = Pulsar_Pack_Creator.Properties.Settings.Default.AutoUpdate;
            ExitRemindBox.IsChecked = Pulsar_Pack_Creator.Properties.Settings.Default.ExitRemind;
            ColorModeBox.SelectedIndex = Pulsar_Pack_Creator.Properties.Settings.Default.ColorMode;
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
            bool hasUpdate = TryUpdate();
            if (!hasUpdate) MsgWindow.Show("You are already using the latest version.", this);
        }

        private void OnSaveSettingsClick(object sender, RoutedEventArgs e)
        {
            Hide();
        }

        public static bool GetChangelog(out string changelog)
        {
            try { 
                using (HttpClient client = new HttpClient())
                {
                    changelog = client.GetStringAsync("https://pulsar.brawlbox.co.uk/PulsarPackCreatorVERSION.txt").Result; ;
                    return true;
                }
            }
            catch(Exception ex)
            {
                changelog = ex.Message;
                return false;        }
        }

        public static bool GetVersion(out string version)
        {
            bool ret = GetChangelog(out string changelog);
            version = changelog;
            if (ret) version = version.Split("\r\n")[0].Replace("·Updated to ", "");
            return ret;
        }

        public static bool TryUpdate()
        {
            bool hasUpdate = CheckUpdates();
            if (hasUpdate)
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
                return true;
            }
            return false;
        }

        public static UpdateResult Update()
        {

            string curExe = $"{AppDomain.CurrentDomain.FriendlyName}";

            using (HttpClient client = new HttpClient())
            {
                try
                {
                    byte[] responseArray = client.GetByteArrayAsync("https://pulsar.brawlbox.co.uk/Pulsar%20Pack%20Creator.exe").Result;
                    File.WriteAllBytes("new.pul", responseArray);
                }
                catch (Exception)
                {
                    return UpdateResult.NoServer;
                }
            }

            string curDir = Directory.GetCurrentDirectory();

            string version = (Assembly.GetExecutingAssembly().GetCustomAttribute(typeof(AssemblyInformationalVersionAttribute)) as AssemblyInformationalVersionAttribute).InformationalVersion.ToString();

            using Process updater = new Process();
            {
                updater.StartInfo.FileName = @"powershell.exe";
                updater.StartInfo.Arguments = $"Wait-Process -name '{curExe}'; cd {curDir}; del '{curExe}.exe'; ren new.pul '{curExe}.exe'; Start-Process '{curExe}.exe' -ArgumentList '·Updated to {version}'; Wait-Process Notepad;";
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
            string version = (Assembly.GetExecutingAssembly().GetCustomAttribute(typeof(AssemblyInformationalVersionAttribute)) as AssemblyInformationalVersionAttribute).InformationalVersion.ToString();
            bool ret = GetVersion(out string newVersion);
            if (!ret)
            {
                MsgWindow.Show(newVersion, "Update server uncontactable");
                return false;
            }
                
                
            return newVersion != version;
        }

        public static void DisplayChangelog(string oldVersion)
        {
            bool ret = GetChangelog(out string changelogRaw);

           if (ret) {
                string[] allChangelogs = changelogRaw.Split("\r\n");
                string changelog = allChangelogs[0];
                for (int i = 1; i < allChangelogs.Length; i++)
                {
                    string curLine = allChangelogs[i];
                    if (curLine.Contains("·Updated"))
                    {
                        string version = curLine.Split(" ")[2];
                        if (version == oldVersion) break;
                    }
                    else if (curLine != "")
                    {
                        changelog += $"\n{curLine}";
                    }
                }

                MsgWindow.Show(changelog);
            }
        }

        private void OnExitRemindToggle(object sender, RoutedEventArgs e)
        {
            if ((sender as CheckBox).IsKeyboardFocused)
            {
                Pulsar_Pack_Creator.Properties.Settings.Default.ExitRemind = !Pulsar_Pack_Creator.Properties.Settings.Default.ExitRemind;
            }
        }

        private void OnColorModeChange(object sender, SelectionChangedEventArgs e)
        {
            ComboBox box = sender as ComboBox;
            if (this.IsLoaded)
            {
                Pulsar_Pack_Creator.Properties.Settings.Default.ColorMode = box.SelectedIndex;
                if (this.IsLoaded) ApplyColorMode();
            }
        }


        [DllImport("dwmapi.dll")]
        private static extern int DwmSetWindowAttribute(IntPtr hwnd, int attr, ref int attrValue, int attrSize);
        private const int DWMWA_USE_IMMERSIVE_DARK_MODE_BEFORE_20H1 = 19;
        private const int DWMWA_USE_IMMERSIVE_DARK_MODE = 20;

        public static void SetWindowTitleBarColor(List<Window> windows, bool isLight)
        {
            if (OperatingSystem.IsWindowsVersionAtLeast(10, 0, 17763))
            {
                int attribute = DWMWA_USE_IMMERSIVE_DARK_MODE_BEFORE_20H1;
                if (OperatingSystem.IsWindowsVersionAtLeast(10, 0, 18985))
                {
                    attribute = DWMWA_USE_IMMERSIVE_DARK_MODE;
                }
                int useImmersiveDarkMode = isLight ? 0 : 1;
                foreach (Window window in windows)
                {
                    WindowInteropHelper helper = new WindowInteropHelper(window);
                    HwndSource source = HwndSource.FromHwnd(helper.EnsureHandle());
                    DwmSetWindowAttribute(source.Handle, attribute, ref useImmersiveDarkMode, sizeof(int));
                }
            }
        }


        public static void ApplyColorMode()
        {

            ColorMode mode = (ColorMode)Pulsar_Pack_Creator.Properties.Settings.Default.ColorMode;

            Window main = GetWindow(App.Current.MainWindow);
            List<Window> windows = new List<Window>
            {
                main,
                MainWindow.settingsWindow,
                MainWindow.crashWindow,
                MainWindow.messageWindow,
                MainWindow.importWindow
            };
            bool isLight = mode == ColorMode.Light_Mode;

            SetWindowTitleBarColor(windows, isLight);




            Color bg = isLight ? Color.FromArgb(unchecked((int)0xFDE0E0E0)) : Color.FromArgb(unchecked((int)0xFD505050)); ;
            Color fg = isLight ? Color.Black : Color.LightGray;
            Color appBg = isLight ? Color.White : Color.FromArgb(unchecked((int)0xFD202020));
            Application.Current.Resources["bg"] = new System.Windows.Media.SolidColorBrush(System.Windows.Media.Color.FromArgb(bg.A, bg.R, bg.G, bg.B));
            Application.Current.Resources["fg"] = new System.Windows.Media.SolidColorBrush(System.Windows.Media.Color.FromArgb(fg.A, fg.R, fg.G, fg.B));
            Application.Current.Resources["AppBg"] = new System.Windows.Media.SolidColorBrush(System.Windows.Media.Color.FromArgb(appBg.A, appBg.R, appBg.G, appBg.B));
            //Application.Current.Resources["ComboBox.Static.Background"] = new System.Windows.Media.SolidColorBrush(System.Windows.Media.Color.FromArgb(bg.A, bg.R, bg.G, bg.B));

            BitmapImage image = new BitmapImage();
            image.BeginInit();
            if (mode == ColorMode.Space_Mode)
            {
                image.UriSource = new Uri("pack://application:,,,/Resources/space.jpg");
                image.EndInit();
                Application.Current.Resources["imageBg"] = image;
            }
            else
            {
                image.UriSource = new Uri("pack://application:,,,/Resources/transparent.png");
                image.EndInit();
                Application.Current.Resources["imageBg"] = image;

            }

        }
    }
}
