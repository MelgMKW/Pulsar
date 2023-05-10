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
                string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
                BigEndianReader bin = new BigEndianReader(File.Open(files[0], FileMode.Open));
                int magic = bin.ReadInt32();
                bin.BaseStream.Position -= 4;
                if (magic == 0x50554c53) ImportPulsarBin(bin);
                else if (magic == 0x50554c44)
                {
                    bin.Close();
                    crashWindow.Load(files[0]);
                }
                /*
                else
                {
                    bin.Close();
                    string[] lines = File.ReadAllLines(files[0]);
                    string lastFunction = "";
                    for (int i = 0; i < lines.Length; i++)
                    {
                        string curName = lines[i].Split(' ')[4];
                        if (curName.Contains("zz_0"))
                        {
                            lines[i] = lines[i].Replace("zz_0", $"0x80").TrimEnd('_');
                            curName = lines[i].Split(' ')[4];
                        }
                        if (curName.Contains("switchD") || curName.Contains("zz_caseD"))
                        {
                            lines[i] = lines[i].Replace("switchD", $"{lastFunction}_switch");
                            lines[i] = lines[i].Replace("zz_caseD", $"{lastFunction}_caseD");
                        }
                        else lastFunction = curName;
                    }
                    }
                    File.WriteAllLines(files[0], lines);
                }*/

                else
                {
                    bin.Close();
                    string[] lines = File.ReadAllLines(files[0]);
                    char[] delims = new[] { '\r', '\n' };
                    string[] splices = PulsarRes.Port.Replace("-8", " 8").Replace(":", "").Split(delims, StringSplitOptions.RemoveEmptyEntries);
                    char[] regions = new char[] { 'E', 'J', 'K' };
                    foreach (char region in regions)
                    {
                        using StreamWriter stream = new StreamWriter($"RMC{region}01.map");
                        for (int i = 0; i < lines.Length; i++)
                        {
                            string[] curLine = lines[i].Split(' ');
                            UInt32 address = UInt32.Parse(curLine[0], NumberStyles.HexNumber);
                            int idx = Array.IndexOf(splices, $"[{region}]");
                            idx++;
                            UInt32 regionAddress = 0;
                            while (splices[idx] != "#")
                            {
                                string[] curSplice = splices[idx].Split(' ');
                                int isNegative = curSplice[2].Contains('-') ? -1 : 1;
                                regionAddress = (UInt32)((int)address + isNegative * int.Parse(curSplice[2].Replace("-0x", "").Replace("+0x", ""), NumberStyles.HexNumber));
                                if (UInt32.Parse(curSplice[0], NumberStyles.HexNumber) <= address &&
                                address < UInt32.Parse(curSplice[1], NumberStyles.HexNumber))
                                {
                                    stream.WriteLine($"{regionAddress:X8} {curLine[1]} {regionAddress:X8} 0 {curLine[4]}");
                                    break;
                                }
                                idx++;
                            }
                        }

                    }
                }
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