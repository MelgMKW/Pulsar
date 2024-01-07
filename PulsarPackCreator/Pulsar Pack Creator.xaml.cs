using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using Pulsar_Pack_Creator;
using System.Buffers.Binary;
using System.Globalization;
using System.Drawing;
using System.Windows.Media.Animation;

namespace PulsarPackCreator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
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

        private void NumbersOnlyBox(object sender, TextCompositionEventArgs e)
        {
            string text = e.Text;
            bool isNumber = Regex.IsMatch(text, "[^0-9]+");
            e.Handled = isNumber;
        }

        private void OnGhostsClick(object sender, RoutedEventArgs e)
        {

        }

        private void OnDropFile(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                OpenPulFile(((string[])e.Data.GetData(DataFormats.FileDrop))[0]);
            }
        }

        private void OpenPulFile(string path)
        {
            BigEndianReader bin = new BigEndianReader(File.Open(path, FileMode.Open));
            int magic = bin.ReadInt32();
            bin.BaseStream.Position -= 4;
            if (magic == 0x50554c53) ImportConfigFile(bin);
            else if (magic == 0x50554c44)
            {
                bin.Close();
                crashWindow.Load(path);
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
                    cups[cupIdx].fileNames[row] = fileName;
                    row++;
                    if (row == 4)
                    {
                        row = 0;
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
            if (Path.GetExtension(files[0]).ToLowerInvariant() == ".rkg")
            {
                string fileName = Path.GetFileNameWithoutExtension(files[0]);
                //cups[curCup].expertFileNames[Grid.GetRow(box), Grid.GetColumn(box)] = fileName;
                box.Text = fileName;
            }
        }

        private void OnDrag(object sender, DragEventArgs e)
        {
            e.Effects = DragDropEffects.All;
            e.Handled = true;
        }
    }
}