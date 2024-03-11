using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Pulsar_Pack_Creator
{

    partial class MainWindow : Window
    {
        public class Cup
        {
            public static readonly string[] defaultNames =
            {
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                ""
            };

            public const int maxCupIcons = 100;
            public Cup(uint idx)
            {
                this.idx = idx;
                slots = new byte[4] { 0x8, 0x8, 0x8, 0x8 };
                string defaultFile = "File";
                string defaultTrack = "Name";
                string defaultAuthor = "Author";
                string defaultVersion = "Version";
                string defaultGhost = "";
                musicSlots = new byte[4] { 0x8, 0x8, 0x8, 0x8 };
                fileNames = new string[4] { defaultFile, defaultFile, defaultFile, defaultFile };
                trackNames = new string[4] { defaultTrack, defaultTrack, defaultTrack, defaultTrack };
                authorNames = new string[4] { defaultAuthor, defaultAuthor, defaultAuthor, defaultAuthor };
                versionNames = new string[4] { defaultVersion, defaultVersion, defaultVersion, defaultVersion };
                expertFileNames = new string[4, 4] {{defaultGhost, defaultGhost, defaultGhost, defaultGhost},
                                                    {defaultGhost, defaultGhost, defaultGhost, defaultGhost},
                                                    {defaultGhost, defaultGhost, defaultGhost, defaultGhost},
                                                    {defaultGhost, defaultGhost, defaultGhost,defaultGhost} };
                if (idx < maxCupIcons)
                {
                    name = defaultNames[idx];
                    iconName = $"{name}.png";
                }
                else
                {
                    name = "";
                    iconName = "";
                }
            }

            public Cup(PulsarGame.Cup raw) : this(0)
            {
                List<Cup> cups = (GetWindow(App.Current.MainWindow) as MainWindow).cups;
                this.idx = (uint)cups.Count;

                for (int i = 0; i < 4; i++)
                {
                    PulsarGame.Track track = raw.tracks[i];
                    if (track.slot >= 0x20) slots[i] = 0x08; //remove battle slots from old config.pul
                    else slots[i] = track.slot;
                    musicSlots[i] = track.musicSlot;
                }

                if (idx < maxCupIcons)
                {
                    name = defaultNames[idx];
                    iconName = $"{name}.png";
                }
                else
                {
                    name = "";
                    iconName = "";
                }
            }
            public Cup(PulsarGame.CupV1 raw) : this(0)
            {
                List<Cup> cups = (GetWindow(App.Current.MainWindow) as MainWindow).cups;
                this.idx = (uint)cups.Count;

                for (int i = 0; i < 4; i++)
                {
                    PulsarGame.Track track = raw.tracks[i];
                    if (track.slot >= 0x20) slots[i] = 0x08; //remove battle slots from old config.pul
                    else slots[i] = track.slot;
                    musicSlots[i] = track.musicSlot;
                }

                if (idx < maxCupIcons)
                {
                    name = defaultNames[idx];
                    iconName = $"{name}.png";
                }
                else
                {
                    name = "";
                    iconName = "";
                }
            }

            public uint idx;
            //Data
            public byte[] slots;
            public byte[] musicSlots;
            public string[] fileNames;
            public string[] trackNames;
            public string[] authorNames;
            public string[] versionNames;
            public string[,] expertFileNames;
            public string iconName = "";
            public string name = "";
        }

        private void OnCupCountChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.Text == "" || box.Text == "0")
            {
                box.Text = "1";
                return;
            }
            ushort newCount = ushort.Parse(box.Text);
            if (newCount > 1000)
            {
                MsgWindow.Show("The maximum number of cups is 1000.");
                box.Text = $"{ctsCupCount}";
                return;
            }
            for (ushort ite = (ushort)cups.Count; ite < newCount; ite++)
            {
                cups.Add(new Cup(ite));
            }
            ctsCupCount = newCount;
        }
        private void OnGoToCupPasting(object sender, DataObjectPastingEventArgs e)
        {
            NumbersOnlyPasting(sender, e);
            if (!e.CommandCancelled)
            {
                String text = (String)e.DataObject.GetData(typeof(String));
                TextBox box = sender as TextBox;
                int dest = int.Parse(box.Text + text);
                if (dest > ctsCupCount) e.CancelCommand();
            }
        }

        private void OnGoToCupInput(object sender, TextCompositionEventArgs e)
        {
            NumbersOnlyBox(e.Text, e);
            if (!e.Handled)
            {
                TextBox box = sender as TextBox;
                int dest = int.Parse(box.Text + e.Text);
                if (dest > ctsCupCount) e.Handled = true;
            }
        }
        private void OnGoToCupChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.Text == "")
            {
                return;
            }
            short dest = short.Parse(box.Text);
            UpdateCurCup((short)(dest - 1 - curCup));
        }

        private void OnCupNameChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.IsKeyboardFocused)
            {
                /*
                if (curCup > 100)
                {
                    MsgWindow.Show("Only the first 100 cups have names and icons.");
                    box.Text = "";
                    return;
                }
                */
                if (box.Text == "" && curCup < Cup.maxCupIcons) box.Text = Cup.defaultNames[curCup];
                cups[curCup].name = box.Text;
            }
        }

        private void OnCupIconChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.IsKeyboardFocused)
            {
                /*
                if (curCup > 100)
                {
                    MsgWindow.Show("Only the first 100 cups have names and icons.");
                    box.Text = "";
                    return;
                }
                */
                if (box.Text == "" && curCup < Cup.maxCupIcons) box.Text = $"{Cup.defaultNames[curCup]}.png";
            }

        }
        private void OnCupIconLostKBFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.Text != cups[curCup].iconName && box.Text != "")
            {
                bool ret = DisplayImage(box.Text);
                if (ret) cups[curCup].iconName = box.Text;
            }
        }
        private void OnFilenameChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            int idx = Grid.GetRow(box);
            cups[curCup].fileNames[idx - firstTrackRow] = box.Text;
        }

        public static bool CheckTrackName(string name)
        {
            char[] invalid = Path.GetInvalidFileNameChars();
            invalid = invalid.Where(x => x != '\\' && x != ':').ToArray();
            return name.IndexOfAny(invalid) < 0;
        }
        private void OnTrackNameInput(object sender, TextCompositionEventArgs e)
        {
            string text = e.Text;
            if (!CheckTrackName(text))
            {
                MsgWindow.Show("Track names cannot contain any of <>\"/|?*");
                e.Handled = true;
            }
        }
        private void OnTracknameChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.IsKeyboardFocused)
            {
                int idx = Grid.GetRow(box);
                cups[curCup].trackNames[idx - firstTrackRow] = box.Text;
                SetGhostLabelName(idx - firstTrackRow, box.Text);
            }

        }

        private void OnAuthorChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            int idx = Grid.GetRow(box);
            cups[curCup].authorNames[idx - firstTrackRow] = box.Text;
        }

        private void OnVersionChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            int idx = Grid.GetRow(box);
            cups[curCup].versionNames[idx - firstTrackRow] = box.Text;
        }

        private void OnSlotChange(object sender, SelectionChangedEventArgs e)
        {
            ComboBox box = sender as ComboBox;
            int idx = Grid.GetRow(box);
            cups[curCup].slots[idx - firstTrackRow] = PulsarGame.MarioKartWii.idxToCourseId[box.SelectedIndex];
        }

        private void OnMusicChange(object sender, SelectionChangedEventArgs e)
        {
            ComboBox box = sender as ComboBox;
            int idx = Grid.GetRow(box);
            cups[curCup].musicSlots[idx - firstTrackRow] = PulsarGame.MarioKartWii.musicIdxToCourseId[box.SelectedIndex];
        }

        private void OnLeftArrowClick(object sender, RoutedEventArgs e)
        {
            UpdateCurCup(-1);
        }
        private void OnRightArrowClick(object sender, RoutedEventArgs e)
        {
            UpdateCurCup(1);
        }
        public void UpdateCurCup(Int16 direction)
        {
            curCup = (ushort)((curCup + ctsCupCount + direction) % ctsCupCount);
            if (curCup + 1 <= ctsCupCount)
            {
                Cup cup = cups[curCup];

                File1.Text = cup.fileNames[0];
                File2.Text = cup.fileNames[1];
                File3.Text = cup.fileNames[2];
                File4.Text = cup.fileNames[3];
                Name1.Text = cup.trackNames[0];
                Name2.Text = cup.trackNames[1];
                Name3.Text = cup.trackNames[2];
                Name4.Text = cup.trackNames[3];
                Author1.Text = cup.authorNames[0];
                Author2.Text = cup.authorNames[1];
                Author3.Text = cup.authorNames[2];
                Author4.Text = cup.authorNames[3];
                Version1.Text = cup.versionNames[0];
                Version2.Text = cup.versionNames[1];
                Version3.Text = cup.versionNames[2];
                Version4.Text = cup.versionNames[3];

                for (int row = 0; row < 4; row++)
                {
                    SetGhostLabelName(row, cup.trackNames[row]);
                    for (int col = 0; col < 4; col++)
                    {
                        SetExpertName(cup.expertFileNames[row, col], row, col);
                    }
                }

                Slot1.SelectedValue = PulsarGame.MarioKartWii.idxToAbbrev[Array.IndexOf(PulsarGame.MarioKartWii.idxToCourseId, cup.slots[0])];
                Slot2.SelectedValue = PulsarGame.MarioKartWii.idxToAbbrev[Array.IndexOf(PulsarGame.MarioKartWii.idxToCourseId, cup.slots[1])];
                Slot3.SelectedValue = PulsarGame.MarioKartWii.idxToAbbrev[Array.IndexOf(PulsarGame.MarioKartWii.idxToCourseId, cup.slots[2])];
                Slot4.SelectedValue = PulsarGame.MarioKartWii.idxToAbbrev[Array.IndexOf(PulsarGame.MarioKartWii.idxToCourseId, cup.slots[3])];
                Music1.SelectedValue = PulsarGame.MarioKartWii.musicIdxToAbbrev[Array.IndexOf(PulsarGame.MarioKartWii.musicIdxToCourseId, cup.musicSlots[0])];
                Music2.SelectedValue = PulsarGame.MarioKartWii.musicIdxToAbbrev[Array.IndexOf(PulsarGame.MarioKartWii.musicIdxToCourseId, cup.musicSlots[1])];
                Music3.SelectedValue = PulsarGame.MarioKartWii.musicIdxToAbbrev[Array.IndexOf(PulsarGame.MarioKartWii.musicIdxToCourseId, cup.musicSlots[2])];
                Music4.SelectedValue = PulsarGame.MarioKartWii.musicIdxToAbbrev[Array.IndexOf(PulsarGame.MarioKartWii.musicIdxToCourseId, cup.musicSlots[3])];
                CupIdLabel.Text = $"Cup {curCup + 1}";
                CupName.Text = cup.name;
                CupIcon.Text = cup.iconName;
                DisplayImage(cup.iconName);
            }

        }

        public (string[], string[]) SortTracks() //tuple sorted, unsorted
        {
            string[] indexedArray = new string[ctsCupCount * 4];
            for (int idx = 0; idx < ctsCupCount; idx++)
            {
                Cup cup = cups[idx];
                for (int i = 0; i < 4; i++)
                {
                    indexedArray[cup.idx * 4 + i] = cup.trackNames[i];
                }
            }
            string[] sortedArray = new string[ctsCupCount * 4];
            Array.Copy(indexedArray, sortedArray, indexedArray.Length);
            sortedArray = sortedArray.OrderBy(x =>
            {
                string result = x;
                int startOfSequence = result.IndexOf("\\c{");
                while (startOfSequence != -1)
                {                                      
                    int endOfSequence = result.IndexOf("}");
                    if (endOfSequence == -1) break;
                    result = result.Remove(startOfSequence, endOfSequence + 1 - startOfSequence);                         
                    startOfSequence = result.IndexOf("\\c{");
                }
                return result;
            }).ToArray();
            return (sortedArray, indexedArray);            
        }
        private void OnAlphabetizeClick(object sender, RoutedEventArgs e)
        {
            List<Cup> sortedCups = new List<Cup>(new Cup[cups.Count()]);
            for (ushort i = 0; i < cups.Count(); i++)
            {
                sortedCups[i] = new Cup(i);
                sortedCups[i].name = cups[i].name;
                sortedCups[i].iconName = cups[i].iconName;
            }

           
            (string[], string[]) trackNames = SortTracks();
            int cupIdx = 0;
            int trackIdx = 0;
            foreach (string s in trackNames.Item1)
            {
                int idx = Array.IndexOf(trackNames.Item2, s);
                int oldCupIdx = idx / 4;
                int oldTrackIdx = idx % 4;

                sortedCups[cupIdx].slots[trackIdx] = cups[oldCupIdx].slots[oldTrackIdx];
                sortedCups[cupIdx].musicSlots[trackIdx] = cups[oldCupIdx].musicSlots[oldTrackIdx];
                sortedCups[cupIdx].fileNames[trackIdx] = cups[oldCupIdx].fileNames[oldTrackIdx];
                sortedCups[cupIdx].trackNames[trackIdx] = cups[oldCupIdx].trackNames[oldTrackIdx];
                sortedCups[cupIdx].authorNames[trackIdx] = cups[oldCupIdx].authorNames[oldTrackIdx];
                sortedCups[cupIdx].versionNames[trackIdx] = cups[oldCupIdx].versionNames[oldTrackIdx];
                sortedCups[cupIdx].expertFileNames[trackIdx, 0] = cups[oldCupIdx].expertFileNames[oldTrackIdx, 0];
                sortedCups[cupIdx].expertFileNames[trackIdx, 1] = cups[oldCupIdx].expertFileNames[oldTrackIdx, 1];
                sortedCups[cupIdx].expertFileNames[trackIdx, 2] = cups[oldCupIdx].expertFileNames[oldTrackIdx, 2];
                sortedCups[cupIdx].expertFileNames[trackIdx, 3] = cups[oldCupIdx].expertFileNames[oldTrackIdx, 3];
                trackIdx++;
                if (trackIdx == 4)
                {
                    trackIdx = 0;
                    cupIdx++;
                }
            }
            cups = sortedCups;
            UpdateCurCup(0);
            UpdateMassImport();
            MsgWindow.Show("Tracks have been sorted alphabetically.");
        }
    }
}