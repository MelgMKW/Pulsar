using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace PulsarPackCreator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public class Cup
        {
            public Cup(UInt32 idx)
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
            }
            public Cup(BigEndianReader bin) : this(0)
            {
                idx = bin.ReadUInt32();
                for (int i = 0; i < 4; i++)
                {
                    slots[i] = bin.ReadByte();
                    musicSlots[i] = bin.ReadByte();
                    bin.BaseStream.Position += 4;
                }
            }

            public UInt32 idx;
            //Data
            public byte[] slots;
            public byte[] musicSlots;
            public string[] fileNames;
            public string[] trackNames;
            public string[] authorNames;
            public string[] versionNames;
            public string[,] expertFileNames;
        }

        private void OnCupCountChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.Text == "" || box.Text == "0")
            {
                box.Text = "1";
                return;
            }
            UInt16 newCount = UInt16.Parse(box.Text);
            if (newCount > 1000)
            {
                MsgWindow.Show("The maximum number of cups is 1000.");
                box.Text = $"{ctsCupCount}";
                return;
            }
            for (UInt16 ite = ctsCupCount; ite < newCount; ite++)
            {
                cups.Add(new Cup(ite));
            }
            ctsCupCount = newCount;
        }

        private void OnFilenameChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            int idx = Grid.GetRow(box);
            cups[curCup].fileNames[idx - firstTrackRow] = box.Text;
        }

        private void OnTracknameChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.IsKeyboardFocused)
            {
                int idx = Grid.GetRow(box);
                cups[curCup].trackNames[idx - firstTrackRow] = box.Text;
                SetGhostLabelName(idx, box.Text);
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
            cups[curCup].slots[idx - firstTrackRow] = idxToGameId[box.SelectedIndex];
        }

        private void OnMusicChange(object sender, SelectionChangedEventArgs e)
        {
            ComboBox box = sender as ComboBox;
            int idx = Grid.GetRow(box);
            cups[curCup].musicSlots[idx - firstTrackRow] = idxToGameId[box.SelectedIndex];
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
            curCup = (UInt16)((curCup + ctsCupCount + direction) % ctsCupCount);
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

                Slot1.SelectedValue = idxToAbbrev[Array.IndexOf(idxToGameId, cup.slots[0])];
                Slot2.SelectedValue = idxToAbbrev[Array.IndexOf(idxToGameId, cup.slots[1])];
                Slot3.SelectedValue = idxToAbbrev[Array.IndexOf(idxToGameId, cup.slots[2])];
                Slot4.SelectedValue = idxToAbbrev[Array.IndexOf(idxToGameId, cup.slots[3])];
                Music1.SelectedValue = idxToAbbrev[Array.IndexOf(idxToGameId, cup.musicSlots[0])];
                Music2.SelectedValue = idxToAbbrev[Array.IndexOf(idxToGameId, cup.musicSlots[1])];
                Music3.SelectedValue = idxToAbbrev[Array.IndexOf(idxToGameId, cup.musicSlots[2])];
                Music4.SelectedValue = idxToAbbrev[Array.IndexOf(idxToGameId, cup.musicSlots[3])];
                CupIdLabel.Text = $"Cup {curCup + 1}";
            }
        }

        private void OnAlphabetizeClick(object sender, RoutedEventArgs e)
        {
            List<Cup> sortedCups = new List<Cup>(new Cup[cups.Count()]);
            for (UInt16 i = 0; i < cups.Count(); i++)
            {
                sortedCups[i] = new Cup(i);
            }

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
            Array.Sort(sortedArray);
            int cupIdx = 0;
            int trackIdx = 0;
            foreach (string s in sortedArray)
            {
                int idx = Array.IndexOf(indexedArray, s);
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
            MsgWindow.Show("Tracks have been sorted alphabetically.");
        }
    }
}