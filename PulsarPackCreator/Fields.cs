using Pulsar_Pack_Creator;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Windows;
using System.Windows.Media.Imaging;
using static PulsarGame;

namespace PulsarPackCreator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public static int SECTIONCOUNT = 3;
        public static int CONFIGVERSION = 1;
        public static int INFOVERSION = 1;
        public static int CUPSVERSION = 1;

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

        //Windows
        public static MassImportWindow importWindow;
        public static MassCupsImportWindow cupsImportWindow;
        public static CrashWindow crashWindow;
        public static SettingsWindow settingsWindow;
        public static MsgWindow msgWindow;


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
            cupsImportWindow = new MassCupsImportWindow(this);
            crashWindow = new CrashWindow();
            settingsWindow = new SettingsWindow();
            msgWindow = new MsgWindow();


            string version = (Assembly.GetExecutingAssembly().GetCustomAttribute(typeof(AssemblyInformationalVersionAttribute)) as AssemblyInformationalVersionAttribute).InformationalVersion.ToString();
            Title = "Pulsar Pack Creator " + version;

            TrackBlocking.ItemsSource = blockingValues;
            TrackBlocking.SelectedValue = blockingValues[0];

            Regs.ItemsSource = regsValues;
            Regs.SelectedValue = regsValues[0];

            Slot1.ItemsSource = MarioKartWii.idxToAbbrev;
            Slot2.ItemsSource = MarioKartWii.idxToAbbrev;
            Slot3.ItemsSource = MarioKartWii.idxToAbbrev;
            Slot4.ItemsSource = MarioKartWii.idxToAbbrev;
            Music1.ItemsSource = MarioKartWii.idxToAbbrev;
            Music2.ItemsSource = MarioKartWii.idxToAbbrev;
            Music3.ItemsSource = MarioKartWii.idxToAbbrev;
            Music4.ItemsSource = MarioKartWii.idxToAbbrev;

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
            Version1.Text = initial.versionNames[0];
            Version2.Text = initial.versionNames[0];
            Version3.Text = initial.versionNames[0];
            Version4.Text = initial.versionNames[0];

            Slot1.SelectedValue = MarioKartWii.idxToAbbrev[0];
            Slot2.SelectedValue = MarioKartWii.idxToAbbrev[0];
            Slot3.SelectedValue = MarioKartWii.idxToAbbrev[0];
            Slot4.SelectedValue = MarioKartWii.idxToAbbrev[0];
            Music1.SelectedValue = MarioKartWii.idxToAbbrev[0];
            Music2.SelectedValue = MarioKartWii.idxToAbbrev[0];
            Music3.SelectedValue = MarioKartWii.idxToAbbrev[0];
            Music4.SelectedValue = MarioKartWii.idxToAbbrev[0];

            CC100.Text = $"{parameters.prob100cc}";
            CC150.Text = $"{parameters.prob150cc}";
            CCMirror.Text = $"{parameters.probMirror}";
            CupCount.Text = $"{ctsCupCount}";

            Show();
            msgWindow.Owner = this;

            bool checkUpdates = Pulsar_Pack_Creator.Properties.Settings.Default.AutoUpdate;
            string[] args = Environment.GetCommandLineArgs();
            if (args.Length > 1)
            {

                if (args[1].Contains(".pul"))
                {
                    OpenPulFile(args[1]);
                    Environment.CurrentDirectory = args[0].Substring(0, args[0].LastIndexOf('\\') + 1);
                }
                else if (args[1].Contains("Updated"))
                {
                    checkUpdates = false;
                    SettingsWindow.DisplayChangelog(args[3]);
                }
            }

            if (checkUpdates)
            {
                SettingsWindow.TryUpdate();
            }
            Directory.CreateDirectory("input");
            Directory.CreateDirectory("input/CupIcons");
            Directory.CreateDirectory($"input/{ttModeFolders[0, 1]}");
            Directory.CreateDirectory($"input/{ttModeFolders[1, 1]}");
            Directory.CreateDirectory($"input/{ttModeFolders[2, 1]}");
            Directory.CreateDirectory($"input/{ttModeFolders[3, 1]}");



        }
    }
}