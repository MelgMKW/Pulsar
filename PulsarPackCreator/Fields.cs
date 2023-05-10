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

namespace PulsarPackCreator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        /*
        struct SlotParams
        {
            int magic;  //MELG
            bool areRegsEnabled;
            int trackBlocking;
            int ctsCupCount;
            int extSlotToTrackId;
            u8 extSlotToMusicSlot
            BMGHeader *bmg
        };
        */

        public static int SECTIONCOUNT = 3;
        public static int BINVERSION = 1;
        public static int INFOVERSION = 1;
        public static int CUPSVERSION = 1;
        public static string[] idxToAbbrev =
        {
            "LC", "MMM", "MG", "TF",
            "MC","CM","DKS","WGM",
            "DC","KC","MT","GV",
            "DDR","MH","BC","RR",
            "rPB","rYF","rGV2","rMR",
            "rSL","rSGB","rDS","rWS",
            "rDH","rBC3","rDKJP","rMC",
            "rMC3","rPG","rDKM","rBC",
            "aBP","aDP","aFS","aCCW","aTD",
            "arBC4","arBC3","arS","arCL","arTH"
        };
        public static string[] idxToFullNames =
        {
            "Luigi Circuit", "Moo Moo Meadows", "Mushroom Gorge", "Toad's Factory",
            "Mario Circuit", "Coconut Mall", "DK Summit", "Wario's Gold Mine",
            "Daisy Circuit", "Koopa Cape", "Maple Treeway", "Grumble Volcano",
            "Dry Dry Ruins", "Moonview Highway", "Bowser's Castle", "Rainbow Road",
            "GCN Peach Beach", "DS Yoshi Falls", "SNES Ghost Valley 2", "N64 Mario Raceway",
            "N64 Sherbet Land", "GBA Shy Guy Beach", "DS Delfino Square", "GCN Waluigi Stadium",
            "DS Desert Hills", "GBA Bowser Castle 3", "N64 DK's Jungle Parkway", "GCN Mario Circuit",
            "SNES Mario Circuit 3", "DS Peach Gardens", "GCN DK Mountain", "N64 Bowser's Castle",
            "Block Plaza", "Delfino Pier", "Funky Stadium", "Chain Chomp Wheel", "Thwomp Desert",
            "SNES Battle Course 4", "GBA Battle Course 3", "N64 Skyscraper", "GCN Cookie Land", "DS Twilight House"
        };

        private static string[] ttModeFolders = { "150", "200", "150F", "200F" };
        public static byte[] idxToGameId =
        {
            0x08,0x01,0x02,0x04,
            0x00,0x05,0x06,0x07,
            0x09,0x0f,0x0b,0x03,
            0x0e,0x0a,0x0c,0x0d,
            0x10,0x14,0x19,0x1a,
            0x1b,0x1f,0x17,0x12,
            0x15,0x1e,0x1d,0x11,
            0x18,0x16,0x13,0x1c,
            0x21,0x20,0x23,0x22,0x24,
            0x27,0x28,0x29,0x25,0x26
        };
        public static UInt16[] blockingValues = { 0, 2, 4, 8, 16, 32 };
        public static string[] regsValues = { "No regular tracks", "8 first cups = regular cups", "8 last cups = regular cups" };

        //Dynamic
        public UInt16 curCup = 0;

        //Userdata
        //Options
        public UInt16 ctsCupCount = 1;
        public string date = "01/01/2000";
        public UInt16[] trophyCount;

        //Info
        Parameters parameters;

        //Tracks
        public List<Cup> cups;

        //ImportWindow
        public static MassImportWindow importWindow;
        public static CrashWindow crashWindow;

        //public List<byte> extSlotToTrackId;
        //public List<byte> extSlotToMusicSlot;
        //public List<string> fileNames;
        //public List<string> trackNames;
        //public List<string> authorNames;



        public MainWindow()
        {
            trophyCount = new UInt16[4];
            parameters = new Parameters();
            cups = new List<Cup>();
            Cup initial = new Cup(0);
            cups.Add(initial);
            InitializeComponent();
            importWindow = new MassImportWindow(this);
            crashWindow = new CrashWindow();

            TrackBlocking.ItemsSource = blockingValues;
            TrackBlocking.SelectedValue = blockingValues[0];

            Regs.ItemsSource = regsValues;
            Regs.SelectedValue = regsValues[0];

            Slot1.ItemsSource = idxToAbbrev;
            Slot2.ItemsSource = idxToAbbrev;
            Slot3.ItemsSource = idxToAbbrev;
            Slot4.ItemsSource = idxToAbbrev;
            Music1.ItemsSource = idxToAbbrev;
            Music2.ItemsSource = idxToAbbrev;
            Music3.ItemsSource = idxToAbbrev;
            Music4.ItemsSource = idxToAbbrev;

            File1.Text = initial.fileNames[0];
            File2.Text = initial.fileNames[0];
            File3.Text = initial.fileNames[0];
            File4.Text = initial.fileNames[0];
            Name1.Text = initial.trackNames[0];
            Name2.Text = initial.trackNames[0];
            Name3.Text = initial.trackNames[0];
            Name4.Text = initial.trackNames[0];
            Author1.Text = initial.authorNames[0];
            Author2.Text = initial.authorNames[0];
            Author3.Text = initial.authorNames[0];
            Author4.Text = initial.authorNames[0];

            Slot1.SelectedValue = idxToAbbrev[0];
            Slot2.SelectedValue = idxToAbbrev[0];
            Slot3.SelectedValue = idxToAbbrev[0];
            Slot4.SelectedValue = idxToAbbrev[0];
            Music1.SelectedValue = idxToAbbrev[0];
            Music2.SelectedValue = idxToAbbrev[0];
            Music3.SelectedValue = idxToAbbrev[0];
            Music4.SelectedValue = idxToAbbrev[0];

            CC100.Text = $"{parameters.prob100cc}";
            CC150.Text = $"{parameters.prob150cc}";
            CCMirror.Text = $"{parameters.probMirror}";
            CupCount.Text = $"{ctsCupCount}";

            if (!Directory.Exists("input"))
            {
                Directory.CreateDirectory("input");
            }
        }


    }
}