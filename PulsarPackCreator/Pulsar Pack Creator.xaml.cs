using Microsoft.Win32;
using System;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using static PulsarPackCreator.MsgWindow;

namespace PulsarPackCreator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public int firstTrackRow = 1;
        public int firstTrackCol = 1;
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

        private void OnGhostsClick(object sender, RoutedEventArgs e)
        {

        }

        private void OnDropFile(object sender, DragEventArgs e)
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

        private void OpenPulFile(string path)
        {
            byte[] raw = File.ReadAllBytes(path);
            int magic = raw[3] | (raw[2] << 8) | (raw[1] << 16) | (raw[0] << 24);
  
            if (magic == 0x50554c53)
            {
                ImportConfigFile(raw);
            }
                               
            else if (magic == 0x50554c44)
            {
                crashWindow.Show();
                crashWindow.ImportCrash(raw);
            }
            else if(magic == 0x50554C4C)
            {
                ImportLeaderboard(raw);
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

    }
}