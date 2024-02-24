using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using static Pulsar_Pack_Creator.MainWindow;

namespace Pulsar_Pack_Creator
{
    /// <summary>
    /// Interaction logic for parent.xaml
    /// </summary>
    public partial class MassImportWindow : Window
    {
        public static MainWindow parent;


        public MassImportWindow(MainWindow parentWindow)
        {
            parent = parentWindow;
            InitializeComponent();
        }
        protected override void OnClosing(CancelEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        private void OnSaveImportClick(object sender, RoutedEventArgs e)
        {
            //Need to add checks here i.e. slot validity, number of lines in each text box

            string[] namesImport = NamesImport.Text.Replace("\r", "").Trim('\n').Split("\n").ToArray();
            string[] authorsImport = AuthorsImport.Text.Replace("\r", "").Trim('\n').Split("\n").ToArray();
            string[] versionsImport = VersionsImport.Text.Replace("\r", "").Trim('\n').Split("\n").ToArray();
            string[] slotsImport = SlotsImport.Text.Replace("\r", "").Trim('\n').ToUpperInvariant().Split("\n").ToArray();
            string[] musicSlotsImport = MusicSlotsImport.Text.Replace("\r", "").Trim('\n').ToUpperInvariant().Split("\n").ToArray();

            string[][] importStringArrays = { namesImport, authorsImport, versionsImport, slotsImport, musicSlotsImport };

            foreach (string cur in namesImport)
            {
                if (!CheckTrackName(cur))
                {
                    MsgWindow.Show($"Track {cur} has an invalid name as it contains one of <>:\"/|?*", this);
                    return;
                }
            }
            TextBox[] imports = new TextBox[] { NamesImport, AuthorsImport, SlotsImport, MusicSlotsImport };
            TextBlock[] labels = new TextBlock[] { NamesImportLabel, AuthorsImportLabel, SlotsImportLabel, MusicSlotsImportLabel };

            List<TextBox> emptyBoxes = imports.Where(x => x.Text.Length == 0).ToList();

            if (emptyBoxes.Count > 0)
            {
                string message = "";
                for (int i = 0; i < emptyBoxes.Count; i++)
                {
                    if (i != 0)
                    {
                        message += ", ";
                    }
                    int emptyBoxIdx = Array.IndexOf(imports, emptyBoxes[i]);

                    message += labels[emptyBoxIdx].Text;
                }
                if (emptyBoxes.Count == 1)
                {
                    message += " is empty";
                }
                else
                {
                    message += " are empty";
                }
                MsgWindow.Show(message);
                return;
            }

            List<int> differentLengthIdxs = new List<int>();
            int baseLength = importStringArrays[0].Length;
            for (int i = 0; i < imports.Length; i++)
            {
                if (importStringArrays[i].Length != baseLength)
                {
                    differentLengthIdxs.Add(Array.IndexOf(imports, imports[i]));
                }
            }

            if (differentLengthIdxs.Count > 0)
            {
                string message = "";

                foreach (int idx in differentLengthIdxs)
                {
                    int curLength = importStringArrays[idx].Length;
                    string plural = "";
                    if (Math.Abs(curLength - baseLength) > 1) plural = "s";
                    if (curLength > baseLength)
                    {
                        message += $"{labels[idx].Text} has {curLength - baseLength} line{plural} too many.\n";
                    }
                    else
                    {
                        message += $"{labels[idx].Text} is missing {baseLength - curLength} line{plural}.\n";
                    }
                }
                MsgWindow.Show(message);
                return;
            }

            //NamesImport
            int row = 0;
            int cupIdx = parent.curCup;
            for (int line = 0; line < namesImport.Length; line++)
            {
                byte slotIdx = FindSlotIndex(importStringArrays[3][line]);
                if (slotIdx == 0xFF)
                {
                    MsgWindow.Show($"Track Slot {importStringArrays[3][line]} (Line {line}) is invalid.");
                    return;
                }
                byte musicSlotIdx = FindSlotIndex(importStringArrays[4][line]);
                if (musicSlotIdx == 0xFF)
                {
                    MsgWindow.Show($"Music Slot {importStringArrays[4][line]} (Line {line}) is invalid.");
                    return;
                }
            }

            Hide();

            for (int line = 0; line < namesImport.Length; line++)
            {
                if (cupIdx == parent.ctsCupCount)
                {
                    MsgWindow.Show("Tracklist exceeded existing number of cups.");
                    return;
                }
                byte slotIdx = FindSlotIndex(importStringArrays[3][line]);
                byte musicSlotIdx = FindSlotIndex(importStringArrays[4][line]);
                parent.cups[cupIdx].trackNames[row] = importStringArrays[0][line];
                parent.cups[cupIdx].authorNames[row] = importStringArrays[1][line];
                parent.cups[cupIdx].versionNames[row] = importStringArrays[2][line];
                parent.cups[cupIdx].slots[row] = PulsarGame.MarioKartWii.idxToCourseId[slotIdx];
                parent.cups[cupIdx].musicSlots[row] = PulsarGame.MarioKartWii.idxToCourseId[musicSlotIdx];
                if (cupIdx == parent.curCup)
                {
                    parent.UpdateCurCup(0);
                    /*
                    TextBox nameBox = parent.CupsGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row && Grid.GetColumn(x) == 2) as TextBox;
                    nameBox.Text = importStringArrays[0][line];
                    TextBox authorBox = parent.CupsGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row && Grid.GetColumn(x) == 3) as TextBox;
                    authorBox.Text = importStringArrays[1][line];
                    ComboBox slotBox = parent.CupsGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row && Grid.GetColumn(x) == 4) as ComboBox;
                    slotBox.SelectedIndex = slotIdx;
                    ComboBox musicSlotBox = parent.CupsGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row && Grid.GetColumn(x) == 5) as ComboBox;
                    musicSlotBox.SelectedIndex = musicSlotIdx;
                    */


                }
                row++;
                if (row == 4)
                {
                    row = 0;
                    cupIdx++;
                }
            }
        }

        private byte FindSlotIndex(string slot)
        {
            byte slotIdx = (byte)Array.FindIndex(PulsarGame.MarioKartWii.idxToFullNames, x => x.ToLowerInvariant() == slot.ToLowerInvariant());
            if (slotIdx == 0xFF) slotIdx = (byte)Array.FindIndex(PulsarGame.MarioKartWii.idxToAbbrev, x => x.ToLowerInvariant() == slot.ToLowerInvariant());
            return slotIdx;
        }
    }
}