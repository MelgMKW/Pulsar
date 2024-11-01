using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Threading;

namespace Pulsar_Pack_Creator
{

    partial class MainWindow : Window
    {
        public class Cup
        {
            public static readonly string defaultFile = "File";
            public static readonly string defaultTrack = "Name";
            public static readonly string defaultAuthor = "Author";
            public static readonly string defaultVersion = "Version";
            public static readonly string defaultGhost = "";
            public static readonly string[] defaultNames =
            {
                "Amp",
                "Baron Brr",
                "Barribad",
                "Beanie",
                "Blitty",
                "Block",
                "Blooper",
                "Bob-omb King",
                "Boo",
                "Boom Boom",
                "Brick Block",
                "Broggy",
                "Broozer",
                "Broque Madame",
                "Bullet Bill",
                "Chargin' Chuck",
                "Cheep Cheep",
                "Chomp",
                "Chuboomba",
                "Clock",
                "Coin",
                "Cortex",
                "Dimentio",
                "Dixie Kong",
                "Dolphin",
                "Dreambert",
                "Fantasma",
                "Fawful",
                "Feather",
                "Flipbug",
                "Flutter",
                "Fuzzy",
                "Galoomba",
                "Gearmo",
                "Geno",
                "Glamdozer",
                "Glydon",
                "Goob",
                "Goomba",
                "Goombette",
                "Goonie",
                "Grambi",
                "Grubba",
                "Hammer Bro",
                "Hariet",
                "Honeybee",
                "Hootz",
                "Kalimba",
                "Kamella",
                "Krool",
                "Lady Lima",
                "Lakitu",
                "Launch Star",
                "Lord Fredrik",
                "Lubba",
                "Luma",
                "Major Burrows",
                "Mallow",
                "Marilyn",
                "Midbus",
                "Morton",
                "Mouser",
                "Nabbit",
                "Ninji",
                "O'Chunks",
                "Oho Jee",
                "P-Wing",
                "Pa-Patch",
                "Peasley",
                "Penguin",
                "Pianta",
                "Pointy Tucks",
                "Pokey",
                "Polterpup",
                "Pom Pom",
                "Popple",
                "Porcupuffer",
                "Queen Bean",
                "Retrocloud",
                "Retroflower",
                "Rollodillo",
                "Shroob",
                "Shy Guy",
                "Sir Grodus",
                "Spike Blop",
                "Spiky Cheep Cheep",
                "Sprixie",
                "Starlow",
                "Stuffwell",
                "Sumo Bro",
                "Tiki Buzz",
                "Toothberry",
                "Tornado",
                "Tostarenan",
                "Urchin",
                "Wart",
                "Whacka",
                "Whomp",
                "X-Naut",
                "Yoshi Egg"
            };


            public class Track
            {
                public class Variant
                {
                    public Variant()
                    {
                        slot = 0x8;
                        musicSlot = 0x8;
                        fileName = defaultFile;
                        trackName = defaultTrack;
                        authorName = defaultAuthor;
                        versionName = defaultVersion;
                    }
                    public Variant(PulsarGame.Variant raw)
                    {
                        slot = raw.slot;
                        musicSlot = raw.musicSlot;
                        fileName = defaultFile;
                        trackName = defaultTrack;
                        authorName = defaultAuthor;
                        versionName = defaultVersion;
                    }
                    public string fileName;
                    public string trackName;
                    public string authorName;
                    public string versionName;
                    public byte slot;
                    public byte musicSlot;
                };
                public Track()
                {
                    main = new Variant();
                    variants = new List<Variant>();
                    expertFileNames = new string[4] { defaultGhost, defaultGhost, defaultGhost, defaultGhost };

                }
                public string commonName = null;
                public Variant main;
                public List<Variant> variants;
                public string[] expertFileNames;
            }
            public const int maxCupIcons = 100;
            public Cup(uint idx)
            {
                this.idx = idx;
                tracks = new Track[4];
                for (int i = 0; i < 4; ++i)
                {
                    tracks[i] = new Track();
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
            public Cup(PulsarGame.TrackV3[] rawTracks, PulsarGame.Variant[] rawVariants) : this(0)
            {
                List<Cup> cups = (GetWindow(App.Current.MainWindow) as MainWindow).cups;
                this.idx = (uint)cups.Count;

                for (int i = 0; i < 4; i++)
                {
                    if (rawTracks[i].slot >= 0x20) this.tracks[i].main.slot = 0x08; //remove battle slots from old config.pul
                    else
                    {
                        this.tracks[i].main.slot = rawTracks[i].slot;
                        for (int j = 0; j < rawTracks[i].variantCount; j++) this.tracks[i].variants.Add(new Track.Variant(rawVariants[j]));

                    }
                    this.tracks[i].main.musicSlot = rawTracks[i].musicSlot;
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
            public Cup(PulsarGame.CupV2 raw) : this(0)
            {
                List<Cup> cups = (GetWindow(App.Current.MainWindow) as MainWindow).cups;
                this.idx = (uint)cups.Count;

                for (int i = 0; i < 4; i++)
                {
                    PulsarGame.Track rawTrack = raw.tracks[i];
                    if (rawTrack.slot >= 0x20) tracks[i].main.slot = 0x08; //remove battle slots from old config.pul
                    else tracks[i].main.slot = rawTrack.slot;
                    tracks[i].main.musicSlot = rawTrack.musicSlot;
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
                    PulsarGame.Track rawTrack = raw.tracks[i];
                    if (rawTrack.slot >= 0x20) tracks[i].main.slot = 0x08; //remove battle slots from old config.pul
                    else tracks[i].main.slot = rawTrack.slot;
                    tracks[i].main.musicSlot = rawTrack.musicSlot;
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
            public Track[] tracks;
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
            cups[curCup].tracks[idx - firstTrackRow].main.fileName = box.Text;
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
        private void OnTrackNameChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.IsKeyboardFocused)
            {
                int idx = Grid.GetRow(box);
                cups[curCup].tracks[idx - firstTrackRow].main.trackName = box.Text;
                SetGhostLabelName(idx - firstTrackRow, box.Text);
            }

        }

        private void OnTrackNamePasting(object sender, DataObjectPastingEventArgs e)
        {
            String text = (String)e.DataObject.GetData(typeof(String));
            if (!CheckTrackName(text))
            {
                e.CancelCommand();
                Dispatcher.BeginInvoke(new Action(() => MsgWindow.Show("Track names cannot contain any of <>\"/|?*")));
            }
        }

        private void OnAuthorChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            int idx = Grid.GetRow(box);
            cups[curCup].tracks[idx - firstTrackRow].main.authorName = box.Text;
        }

        private void OnVersionChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            int idx = Grid.GetRow(box);
            cups[curCup].tracks[idx - firstTrackRow].main.versionName = box.Text;
        }

        private void OnSlotChange(object sender, SelectionChangedEventArgs e)
        {
            ComboBox box = sender as ComboBox;
            int idx = Grid.GetRow(box);
            cups[curCup].tracks[idx - firstTrackRow].main.slot = PulsarGame.MarioKartWii.idxToCourseId[box.SelectedIndex];
        }

        private void OnMusicChange(object sender, SelectionChangedEventArgs e)
        {
            ComboBox box = sender as ComboBox;
            int idx = Grid.GetRow(box);
            cups[curCup].tracks[idx - firstTrackRow].main.musicSlot = PulsarGame.MarioKartWii.musicIdxToCourseId[box.SelectedIndex];
        }

        private void OnLeftArrowClick(object sender, RoutedEventArgs e)
        {
            UpdateCurCup(-1);
        }
        private void OnRightArrowClick(object sender, RoutedEventArgs e)
        {
            UpdateCurCup(1);
        }

        public void UpdateCurCupTrack(int row)
        {
            Cup.Track track = cups[curCup].tracks[row];
            Cup.Track.Variant mainTrack = track.main;
            GetFileBox(row).Text = mainTrack.fileName;
            GetNameBox(row).Text = mainTrack.trackName;
            GetAuthorBox(row).Text = mainTrack.authorName;
            GetVersionBox(row).Text = mainTrack.versionName;
            GetSlotBox(row).SelectedValue = PulsarGame.MarioKartWii.idxToAbbrev[Array.IndexOf(PulsarGame.MarioKartWii.idxToCourseId, mainTrack.slot)];
            GetMusicSlotBox(row).SelectedValue = PulsarGame.MarioKartWii.musicIdxToAbbrev[Array.IndexOf(PulsarGame.MarioKartWii.musicIdxToCourseId, mainTrack.musicSlot)];
            System.Windows.Media.Brush brush = System.Windows.Media.Brushes.Black;
            if (track.variants.Count > 0) brush = System.Windows.Media.Brushes.MediumVioletRed;
            GetVariantsButton(row).Foreground = brush;
            SetGhostLabelName(row, mainTrack.trackName);
            for (int col = 0; col < 4; col++)
            {
                SetExpertName(track.expertFileNames[col], row, col);
            }
        }
        public void UpdateCurCup(Int16 direction)
        {
            curCup = (ushort)((curCup + ctsCupCount + direction) % ctsCupCount);
            if (curCup + 1 <= ctsCupCount)
            {
                Cup cup = cups[curCup];
                for (int row = 0; row < 4; row++)
                {
                    UpdateCurCupTrack(row);
                }
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
                    indexedArray[cup.idx * 4 + i] = cup.tracks[i].main.trackName + (cup.tracks[i].main.versionName == "Version" ? "" : $" {cup.tracks[i].main.versionName}");
                }
            }
            string[] sortedArray = indexedArray.OrderBy(x => Regex.Replace(x, @"\\[mMxzuc]{.*?}", "").Trim()).ToArray();
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

                sortedCups[cupIdx].tracks[trackIdx] = cups[oldCupIdx].tracks[oldTrackIdx];
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