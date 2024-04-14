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
            this.Height = SystemParameters.PrimaryScreenHeight * 0.7;
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

            string[][] importStringArrays = { namesImport, authorsImport, slotsImport, musicSlotsImport, versionsImport };

            foreach (string cur in namesImport)
            {
                if (!CheckTrackName(cur))
                {
                    MsgWindow.Show($"Track {cur} has an invalid name as it contains one of <>:\"/|?*", this);
                    return;
                }
            }
            List<TextBox> imports = new List<TextBox> { NamesImport, AuthorsImport, SlotsImport, MusicSlotsImport };
            List<TextBlock> labels = new List<TextBlock> { NamesImportLabel, AuthorsImportLabel, SlotsImportLabel, MusicSlotsImportLabel };

            bool isVersionsFilled = VersionsImport.Text != "";
            if(isVersionsFilled)
            {
                imports.Add(VersionsImport);
                labels.Add(VersionsImportLabel);
            }

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
                    int emptyBoxIdx = imports.IndexOf(emptyBoxes[i]);

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
            for (int i = 0; i < imports.Count; i++)
            {
                if (importStringArrays[i].Length != baseLength)
                {
                    differentLengthIdxs.Add(imports.IndexOf(imports[i]));
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
                byte slotIdx = FindSlotIndex(importStringArrays[2][line]);
                if (slotIdx == 0xFF)
                {
                    MsgWindow.Show($"Track Slot {importStringArrays[2][line]} (Line {line+1}) is invalid.");
                    return;
                }
                byte musicSlotIdx = FindMusicSlotIndex(importStringArrays[3][line]);
                if (musicSlotIdx == 0xFF)
                {
                    MsgWindow.Show($"Music Slot {importStringArrays[3][line]} (Line {line+1}) is invalid.");
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
                byte slotIdx = FindSlotIndex(importStringArrays[2][line]);
                byte musicSlotIdx = FindMusicSlotIndex(importStringArrays[3][line]);
                parent.cups[cupIdx].trackNames[row] = importStringArrays[0][line];
                parent.cups[cupIdx].authorNames[row] = importStringArrays[1][line];
                if(isVersionsFilled) parent.cups[cupIdx].versionNames[row] = importStringArrays[4][line];
                parent.cups[cupIdx].slots[row] = PulsarGame.MarioKartWii.idxToCourseId[slotIdx];
                parent.cups[cupIdx].musicSlots[row] = PulsarGame.MarioKartWii.musicIdxToCourseId[musicSlotIdx];
                if (cupIdx == parent.curCup)
                {
                    parent.UpdateCurCup(0);
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
        private byte FindMusicSlotIndex(string slot)
        {
            byte slotIdx = (byte)Array.FindIndex(PulsarGame.MarioKartWii.musicIdxToFullNames, x => x.ToLowerInvariant() == slot.ToLowerInvariant());
            if (slotIdx == 0xFF) slotIdx = (byte)Array.FindIndex(PulsarGame.MarioKartWii.musicIdxToAbbrev, x => x.ToLowerInvariant() == slot.ToLowerInvariant());
            return slotIdx;
        }
    }
}