using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using static Pulsar_Pack_Creator.MainWindow;
using static Pulsar_Pack_Creator.MainWindow.Cup.Track;

namespace Pulsar_Pack_Creator
{
    /// <summary>
    /// Interaction logic for parent.xaml
    /// </summary>
    public partial class ImportWindow : Window
    {
        public enum Type
        {
            MASSIMPORT = 0,
            VARIANT = 1,
        }
        private Type type;
        public static MainWindow parent;
        private static readonly string[] fileLabels = { "File Names (optional)", "File Names" };
        private static readonly string[] nameLabels = { "Track Names", "Full Variant Names" };

        //MassImport Data
        public string filesImportString;
        public string namesImportString;
        public string authorsImportString;
        public string versionsImportString;
        public string slotsImportString;
        public string musicSlotsImportString;

        //Variant data
        private static readonly string defaultFileName = "AnimalCrossing1.szs";
        private static readonly string defaultName = "Animal Crossing (Summer)";
        private int row;

        public ImportWindow(MainWindow parentWindow)
        {
            parent = parentWindow;
            InitializeComponent();
            this.Height = SystemParameters.PrimaryScreenHeight * 0.7;
        }
        public void FillMassImport(string[] data)
        {
            filesImportString = data[0];
            namesImportString = data[1];
            authorsImportString = data[2];
            versionsImportString = data[3];
            slotsImportString = data[4];
            musicSlotsImportString = data[5];
        }
        private void FillVariant(Cup.Track.Variant variant)
        {

            FilesImport.Text += variant.fileName + "\n";
            NamesImport.Text += variant.trackName + "\n";
            AuthorsImport.Text += variant.authorName + "\n";
            VersionsImport.Text += variant.versionName != Cup.defaultVersion ? variant.versionName + "\n" : null;
            SlotsImport.Text += PulsarGame.MarioKartWii.idxToFullNames[Array.IndexOf(PulsarGame.MarioKartWii.idxToCourseId, variant.slot)] + "\n";
            MusicSlotsImport.Text += PulsarGame.MarioKartWii.musicIdxToFullNames[Array.IndexOf(PulsarGame.MarioKartWii.musicIdxToCourseId, variant.musicSlot)] + "\n";
        }
        public void Init(int idx = 0xff)
        {
            this.type = idx == 0xff ? Type.MASSIMPORT : Type.VARIANT;
            if (type == Type.MASSIMPORT)
            {
                CommonName.Visibility = Visibility.Hidden;
                CommonNameLabel.Visibility = Visibility.Hidden;
                FilesImport.Text = filesImportString;
                NamesImport.Text = namesImportString;
                AuthorsImport.Text = authorsImportString;
                VersionsImport.Text = versionsImportString;
                SlotsImport.Text = slotsImportString;
                MusicSlotsImport.Text = musicSlotsImportString;
            }
            else
            {
                CommonName.Visibility = Visibility.Visible;
                CommonNameLabel.Visibility = Visibility.Visible;
                this.row = idx - 1;
                foreach (Border border in GridImport.Children.OfType<Border>())
                {
                    (border.Child as TextBox).Text = "";
                }
                Cup.Track track = parent.cups[parent.curCup].tracks[row];
                Cup.Track.Variant main = track.main;
                CommonName.Text = track.commonName;
                bool hasFile = main.fileName != "" && main.fileName != Cup.defaultFile;
                bool hasName = main.trackName != "" && main.trackName != Cup.defaultTrack;
                if (!(hasFile || hasName) && track.variants.Count == 0)
                {
                    FilesImport.Text = defaultFileName;
                    NamesImport.Text = defaultName;
                }
                else
                {
                    FillVariant(main);
                    foreach (Cup.Track.Variant variant in track.variants) { FillVariant(variant); }
                }
            }
            FilesImportLabel.Text = fileLabels[(int)type];
            NamesImportLabel.Text = nameLabels[(int)type];
        }
        protected override void OnClosing(CancelEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        private void OnSaveImportClick(object sender, RoutedEventArgs e)
        {
            //Need to add checks here i.e. slot validity, number of lines in each text box
            string[] filesImport = FilesImport.Text.Replace("\r", "").Trim('\n').Split("\n").ToArray();
            string[] namesImport = NamesImport.Text.Replace("\r", "").Trim('\n').Split("\n").ToArray();
            string[] authorsImport = AuthorsImport.Text.Replace("\r", "").Trim('\n').Split("\n").ToArray();
            string[] versionsImport = VersionsImport.Text.Replace("\r", "").Trim('\n').Split("\n").ToArray();
            string[] slotsImport = SlotsImport.Text.Replace("\r", "").Trim('\n').ToUpperInvariant().Split("\n").ToArray();
            string[] musicSlotsImport = MusicSlotsImport.Text.Replace("\r", "").Trim('\n').ToUpperInvariant().Split("\n").ToArray();

            List<string[]> importStringArrays = new List<string[]> { namesImport, authorsImport, slotsImport, musicSlotsImport };

            if (type == Type.VARIANT)
            {
                if (filesImport.Length > 8)
                {
                    MsgWindow.Show("Cannot have more than 8 variants", this);
                    return;
                }
                string commonName = CommonName.Text;
                if (commonName == "")
                {
                    MsgWindow.Show("A Common Name needs to be provided.", this);
                    return;
                }
                parent.cups[parent.curCup].tracks[this.row].commonName = commonName;
            }
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
            if (isVersionsFilled)
            {
                importStringArrays.Add(versionsImport);
                imports.Add(VersionsImport);
                labels.Add(VersionsImportLabel);
            }
            bool isFilesUsed = type == Type.VARIANT || FilesImport.Text != "";
            if (isFilesUsed)
            {
                importStringArrays.Add(filesImport);
                imports.Add(FilesImport);
                labels.Add(FilesImportLabel);
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
            int baseLength = importStringArrays[1].Length;
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

            byte[] slotArray = new byte[namesImport.Length];
            byte[] musicSlotArray = new byte[namesImport.Length];
            for (int line = 0; line < namesImport.Length; line++)
            {
                slotArray[line] = FindSlotIndex(importStringArrays[2][line]);
                if (slotArray[line] == 0xFF)
                {
                    MsgWindow.Show($"Track Slot {importStringArrays[2][line]} (Line {line + 1}) is invalid.");
                    return;
                }
                musicSlotArray[line] = FindMusicSlotIndex(importStringArrays[3][line]);
                if (musicSlotArray[line] == 0xFF)
                {
                    MsgWindow.Show($"Music Slot {importStringArrays[3][line]} (Line {line + 1}) is invalid.");
                    return;
                }
            }

            Hide();
            int cupIdx = 0;
            if (type == Type.VARIANT)
            {
                cupIdx = parent.curCup;
                parent.cups[cupIdx].tracks[this.row].variants = new List<Variant>();
            }
            for (int line = 0; line < namesImport.Length; line++)
            {

                Cup.Track.Variant variant;
                if (type == Type.MASSIMPORT)
                {
                    variant = parent.cups[cupIdx].tracks[row].main;
                }
                else
                {
                    if (line == 0) variant = parent.cups[cupIdx].tracks[this.row].main;
                    else variant = new Variant();
                }
                if (cupIdx == parent.ctsCupCount)
                {
                    MsgWindow.Show("Tracklist exceeded existing number of cups.");
                    return;
                }

                variant.trackName = importStringArrays[0][line];
                variant.authorName = importStringArrays[1][line];
                if (isVersionsFilled) variant.versionName = importStringArrays[4][line];
                if (isFilesUsed) variant.fileName = importStringArrays[4 + Convert.ToInt32(isVersionsFilled)][line];
                variant.slot = PulsarGame.MarioKartWii.idxToCourseId[slotArray[line]];
                variant.musicSlot = PulsarGame.MarioKartWii.musicIdxToCourseId[musicSlotArray[line]];

                if (type == Type.MASSIMPORT)
                {
                    if (cupIdx == parent.curCup)
                    {
                        parent.UpdateCurCup(0);
                    }
                    row++;
                    if (row == 4)
                    {
                        row = 0;
                        cupIdx = (cupIdx + 1 + parent.ctsCupCount) % (parent.ctsCupCount);
                    }
                }
                else if (type == Type.VARIANT && line > 0) parent.cups[cupIdx].tracks[this.row].variants.Add(variant);
            }
            if (type == Type.VARIANT) parent.UpdateCurCupTrack(this.row);
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