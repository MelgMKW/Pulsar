using Microsoft.Win32;
using System;
using System.ComponentModel;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using static Pulsar_Pack_Creator.MsgWindow;

namespace Pulsar_Pack_Creator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    partial class MainWindow : Window
    {
        public int firstTrackRow = 1;
        public int firstTrackCol = 1;

        protected override void OnClosing(CancelEventArgs e)
        {
            IO.IOBase.cancelToken.Cancel();
            Directory.Delete("temp/", true);
        }

        private void OnMassImportClick(object sender, RoutedEventArgs e)
        {
            importWindow.Show();
        }
        private void OnCrashClick(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog();
            openFile.DefaultExt = ".pul";
            openFile.Filter = "Pulsar Crash File (*.pul)|*.pul";
            if (openFile.ShowDialog() == true)
            {
                crashWindow.Load(openFile.FileName);
            }
        }

        public void OnSettingsClick(object sender, RoutedEventArgs e)
        {
            settingsWindow.Load();
        }



        private void NumbersOnlyBox(object sender, TextCompositionEventArgs e)
        {
            string text = e.Text;
            bool isNotNumber = Regex.IsMatch(text, "[^0-9]+");
            e.Handled = isNotNumber;
        }

        private void NumbersOnlyPasting(object sender, DataObjectPastingEventArgs e)
        {
            if (e.DataObject.GetDataPresent(typeof(String)))
            {
                String text = (String)e.DataObject.GetData(typeof(String));
                if (Regex.IsMatch(text, "[^0-9]+"))
                {
                    e.CancelCommand();
                }
            }
            else
            {
                e.CancelCommand();
            }
        }

        private void OnGhostsClick(object sender, RoutedEventArgs e)
        {

        }

        private void OnDropFile(object sender, DragEventArgs e)
        {
            try
            {
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                {
                    string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
                    if (Path.GetExtension(files[0]).ToLowerInvariant() == ".pul")
                    {
                        OpenPulFile(files[0]);
                    }
                }
            }
            catch (Exception ex)
            {
                MsgWindow.Show(ex.ToString());
            }
        }

        private void OpenPulFile(string path)
        {
            byte[] raw = File.ReadAllBytes(path);
            int magic = raw[3] | (raw[2] << 8) | (raw[1] << 16) | (raw[0] << 24);

            if (magic == 0x50554c53)
            {
                Import(raw);
            }

            else if (magic == 0x50554c44)
            {
                crashWindow.Show();
                crashWindow.ImportCrash(raw);
            }
            else if (magic == 0x50554C4C)
            {
                IO.IOBase.ImportLeaderboard(raw);
            }
        }


        private void OnSZSDrop(object sender, DragEventArgs e)
        {
            string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
            if (files == null) return;
            TextBox box = sender as TextBox;
            int row = Grid.GetRow(box);
            int cupIdx = curCup;
            foreach (string file in files)
            {
                if (Path.GetExtension(file).ToLowerInvariant() == ".szs")
                {
                    string fileName = Path.GetFileNameWithoutExtension(file);
                    if (cupIdx == curCup)
                    {
                        box = CupsGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row && Grid.GetColumn(x) == 1) as TextBox;
                        box.Text = fileName;

                    }
                    cups[cupIdx].fileNames[row - firstTrackRow] = fileName;
                    row++;
                    if (row == 4 + firstTrackRow)
                    {
                        row = firstTrackRow;
                        cupIdx++;
                    }
                    if (cupIdx >= ctsCupCount) break;
                }
            }

        }

        private void OnRKGDrop(object sender, DragEventArgs e)
        {
            string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
            if (files == null) return;
            TextBox box = sender as TextBox;

            int col = Grid.GetColumn(box);
            int cupIdx = curCup;

            bool isOnlyRkgs = true;
            bool hasARKG = false;
            foreach (string file in files)
            {
                if (Path.GetExtension(file).ToLowerInvariant() != ".rkg")
                {
                    isOnlyRkgs = false;
                    break;
                }
                else hasARKG = true;
            }
            if (!isOnlyRkgs && hasARKG)
            {
                MsgWindow.Show("Dropped Files contain non .rkg files");
                return;
            }
            else if (!hasARKG) return;

            bool hasAllRkgs = cupIdx == 0 && files.Length == ctsCupCount * 4;

            int row = 0;
            foreach (string file in files)
            {
                string fileName = Path.GetFileNameWithoutExtension(file);
                if (hasAllRkgs)
                {
                    if (cupIdx == curCup)
                    {
                        box = GhostGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row + 1 && Grid.GetColumn(x) == col) as TextBox;
                        TextBlock block = GhostGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row + 1 && Grid.GetColumn(x) == 0) as TextBlock;
                        box.Text = fileName;

                    }

                    if (cups[cupIdx].expertFileNames[row, col - 1] != "RKG File" && cups[cupIdx].expertFileNames[row, col - 1] != "")
                    {
                        trophyCount[col - 1]++;
                    }

                    cups[cupIdx].expertFileNames[row, col - 1] = fileName;
                    row++;
                    if (row == 4)
                    {
                        row = 0;
                        cupIdx++;
                    }
                    if (cupIdx >= ctsCupCount) break;

                }
                else for (int i = 0; i < ctsCupCount * 4; i++)
                    {

                        int curRow = i % 4;
                        //TextBlock ghostLabel = GhostGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == curRow + 1 && Grid.GetColumn(x) == 0) as TextBlock;
                        string curTrack = cups[i / 4].trackNames[curRow];
                        if (fileName.Contains(curTrack, StringComparison.InvariantCultureIgnoreCase))
                        {
                            //int idx = cups.FindIndex(x => x.trackNames[0] == curTrack || x.trackNames[1] == curTrack || x.trackNames[2] == curTrack || x.trackNames[3] == curTrack);
                            if (i / 4 == 0)
                            {
                                box = GhostGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == curRow + 1 && Grid.GetColumn(x) == col) as TextBox;
                                box.Text = fileName;
                            }
                            if (cups[i / 4].expertFileNames[curRow, col - 1] != "RKG File" && cups[i / 4].expertFileNames[curRow, col - 1] != "")
                            {
                                trophyCount[col - 1]++;
                            }
                        }
                    }
            }
            /*
            if (Path.GetExtension(files[0]).ToLowerInvariant() == ".rkg")
            {
                string fileName = Path.GetFileNameWithoutExtension(files[0]);
                //cups[curCup].expertFileNames[Grid.GetRow(box), Grid.GetColumn(box)] = fileName;
                box.Text = fileName;
            }
            */
        }

        private void OnDrag(object sender, DragEventArgs e)
        {
            e.Effects = DragDropEffects.All;
            e.Handled = true;
        }

        private void OnMainWindowClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (Pulsar_Pack_Creator.Properties.Settings.Default.ExitRemind == true)
            {
                MsgWindowResult ret = MsgWindow.Show("Are you sure you want to close the creator?", MsgWindowButton.YesNo);
                if (ret == MsgWindowResult.No)
                {
                    e.Cancel = true;
                }
            }
        }

        private void OnWindowLoaded(object sender, RoutedEventArgs e)
        {
            BitmapImage image = new BitmapImage();
            image.BeginInit();
            image.UriSource = new Uri("pack://application:,,,/Resources/transparent.png");
            image.EndInit();
            Application.Current.Resources["imageBg"] = image;
            SettingsWindow.ApplyColorMode();
        }

        private void OnImportConfigClick(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog openFile = new Microsoft.Win32.OpenFileDialog();
            openFile.DefaultExt = ".pul";
            openFile.Filter = "Pulsar Config File(*.pul) | *.pul";
            if (openFile.ShowDialog() == true)
            {
                Import(File.ReadAllBytes(openFile.FileName));
            }
        }
        private void OnOpenInputClick(object sender, RoutedEventArgs e)
        {
            IO.IOBase.OpenDir($"{Directory.GetCurrentDirectory()}\\input");
        }

        private void Import(byte[] raw)
        {
            curCup = 0;

            IO.Importer importer = new IO.Importer(this, raw);
            IO.Result ret = importer.Import();
            if (ret == IO.Result.Success)
            {
                ctsCupCount = importer.ctsCupCount;
                date = importer.date;

                //Clear
                CC100.TextChanged -= On100ccChange;
                CC150.TextChanged -= On150ccChange;
                CC100.Text = "0";
                CC150.Text = "0";

                CupCount.Text = $"{ctsCupCount}";
                Regs.SelectedIndex = parameters.regsMode;
                TTTrophies.IsChecked = parameters.hasTTTrophies;
                CC200.IsChecked = parameters.has200cc;
                UMT.IsChecked = parameters.hasUMTs;
                Feather.IsChecked = parameters.hasFeather;
                MegaTC.IsChecked = parameters.hasMegaTC;
                CC100.Text = $"{parameters.prob100cc}";
                if (parameters.has200cc) CC100Label.Text = "% 200cc";
                else CC100Label.Text = "% 100cc";
                CC150.Text = $"{parameters.prob150cc}";
                CCMirror.Text = $"{parameters.probMirror}";
                ModFolder.Text = $"{parameters.modFolderName}";
                Wiimmfi.Text = $"{parameters.wiimmfiRegion}";
                TrackBlocking.SelectedValue = blockingValues[Array.IndexOf(blockingValues, (ushort)parameters.trackBlocking)];

                Array.Copy(importer.regsExperts, regsExperts, regsExperts.Length);
                
                DateTime importDate;
                bool dateParse = DateTime.TryParse(date, out importDate);
                if (dateParse)
                {
                    dateSelector.SelectedDate = importDate;
                }
                CC100.TextChanged += On100ccChange;
                CC150.TextChanged += On150ccChange;
                UpdateCurCup(0);
                UpdateCurRegsPage(0);
            }
            string msg = "";
            switch (ret)
            {
                case IO.Result.Success:
                    msg = "Configuration successfully imported.";
                    break;
                case IO.Result.InvalidConfigFile:
                    msg = "Invalid config file.";
                    break;
                case IO.Result.UnknownError:
                    msg = importer.error;
                    break;
            }
            MsgWindow.Show(msg);
        }

        private void OnBuildConfigClick(object sender, RoutedEventArgs e)
        {
            MsgWindowResult result = MsgWindow.Show("Do you also want to create the XML?", MsgWindowButton.YesNo);
            IO.Builder builder = new IO.Builder(this, result == MsgWindowResult.Yes ? IO.Builder.BuildParams.ConfigAndXML : IO.Builder.BuildParams.ConfigOnly);
            IO.Result ret = builder.Build();
            HandleBuildRet(ret, builder.error);
        }

        private void OnBuildFullPackClick(object sender, RoutedEventArgs e)
        {
            IO.Builder builder = new IO.Builder(this, IO.Builder.BuildParams.Full);
            IO.Result ret = builder.Build();
            HandleBuildRet(ret, builder.error);
        }

        private void HandleBuildRet(IO.Result ret, string error)
        {
            if (ret == IO.Result.Success)
            {
                MsgWindowResult result = MsgWindow.Show("Pack successfully created. Do you want to open the output folder?", "Pack created", MsgWindowButton.YesNo);
                if (result == MsgWindowResult.Yes)
                {
                    IO.IOBase.OpenDir($"{Directory.GetCurrentDirectory()}\\output");
                }
            }
            else
            {
                string message = "Unknown build error";
                bool isOptionsError = false;
                switch (ret)
                {
                    case IO.Result.UnknownError:
                        message = error;
                        break;
                    case IO.Result.AlreadyInUse:
                        message = "Output folder is in use.";
                        break;
                    case IO.Result.FileNotFound:
                        message = $"{error} was not found.";
                        break;
                    case IO.Result.NoDate:
                        message = "Please select a date.";
                        isOptionsError = true;
                        break;
                    case IO.Result.NoWiimmfi:
                        message = "Please select a Wiimfi region";
                        isOptionsError = true;
                        break;
                    case IO.Result.NoModName:
                        message = "Please specify a mod folder name.";
                        isOptionsError = true;
                        break;
                    case IO.Result.NoIcon:
                        message = $"{error} cup icon was not found.";
                        break;
                    case IO.Result.WBMGT:
                        message = $"{error} Please do not remove the #BMG header at the top of the pulsar bmg text file.";
                        break;
                    case IO.Result.WIMGT:
                        message = $"Custom cup icon creation failure: {error}.";
                        break;
                    case IO.Result.WSZST:
                        message = $"{error}";
                        break;
                }
                if (isOptionsError)
                {
                    TabController.SelectedItem = Options;
                    ((TabItem)TabController.SelectedItem).Focus();
                }
                MsgWindow.Show(message, "Build failure");
            }
        }

        public bool DisplayImage(string path)
        {
            if (path == "") return false;
            bool isDefault = Cup.defaultNames.Contains(path.Remove(path.Length - 4));
            string filePath = isDefault ? $"temp/{path}" : $"input/CupIcons/{path}";

            if (!File.Exists(filePath))
            {
                if (isDefault) //has not finished extracting all default tpls
                {
                    return false;
                }
                else
                {
                    MsgWindow.Show($"{path} does not exist.");
                    return false;
                }
            }
            BitmapImage src = new BitmapImage();
            src.BeginInit();
            src.UriSource = new Uri(filePath, UriKind.Relative);
            src.CacheOption = BitmapCacheOption.OnLoad;
            src.EndInit();
            IconDisplay.Source = src;
            IconDisplay.Stretch = Stretch.Uniform;
            return true;

        }

    }
}