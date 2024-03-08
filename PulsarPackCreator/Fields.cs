using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows;
using static PulsarGame;

namespace Pulsar_Pack_Creator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>

    partial class MainWindow : Window
    {
   
        public static ushort[] blockingValues = { 0, 2, 4, 8, 16, 32 };
        public static string[] regsValues = { "No regular tracks", "8 first cups = regular cups", "8 last cups = regular cups" };

        //Dynamic
        public ushort curCup = 0;

        //Userdata
        //Options
        public ushort ctsCupCount = 1;
        public string date = "01/01/2000";
        public ushort[] trophyCount;

        //Info
        public Parameters parameters { get; private set; }

        //Tracks
        public List<Cup> cups;

        //Regs Ghosts
        public ushort curRegsCup = 0;
        public string[,,] regsExperts = new string[8, 4, 4];

        //Windows
        public static MassImportWindow importWindow;
        public static MassCupsImportWindow cupsImportWindow;
        public static CrashWindow crashWindow;
        public static SettingsWindow settingsWindow;
        public static MsgWindow messageWindow;

        public Task extractTPL;


        //public List<byte> extSlotToTrackId;
        //public List<byte> extSlotToMusicSlot;
        //public List<string> fileNames;
        //public List<string> trackNames;
        //public List<string> authorNames;


        public MainWindow()
        {
            trophyCount = new ushort[4];
            parameters = new Parameters();
            cups = new List<Cup>();
            Cup initial = new Cup(0);
            cups.Add(initial);
            InitializeComponent();

            importWindow = new MassImportWindow(this);
            cupsImportWindow = new MassCupsImportWindow(this);
            crashWindow = new CrashWindow();
            settingsWindow = new SettingsWindow();

            messageWindow = new MsgWindow();

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
            Music1.ItemsSource = MarioKartWii.musicIdxToAbbrev;
            Music2.ItemsSource = MarioKartWii.musicIdxToAbbrev;
            Music3.ItemsSource = MarioKartWii.musicIdxToAbbrev;
            Music4.ItemsSource = MarioKartWii.musicIdxToAbbrev;

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
            Music1.SelectedValue = MarioKartWii.musicIdxToAbbrev[0];
            Music2.SelectedValue = MarioKartWii.musicIdxToAbbrev[0];
            Music3.SelectedValue = MarioKartWii.musicIdxToAbbrev[0];
            Music4.SelectedValue = MarioKartWii.musicIdxToAbbrev[0];

            CupName.Text = Cup.defaultNames[0];
            CupIcon.Text = $"{Cup.defaultNames[0]}.png";

            CC100.Text = $"{parameters.prob100cc}";
            CC150.Text = $"{parameters.prob150cc}";
            CCMirror.Text = $"{parameters.probMirror}";
            CupCount.Text = $"{ctsCupCount}";

            UpdateCurRegsPage(0);

            Show();
            messageWindow.Owner = this;

            Directory.SetCurrentDirectory(AppDomain.CurrentDomain.BaseDirectory);
            Directory.CreateDirectory("temp/");
            Directory.CreateDirectory("input");
            Directory.CreateDirectory("input/CupIcons");
            Directory.CreateDirectory($"input/{ttModeFolders[0, 1]}");
            Directory.CreateDirectory($"input/{ttModeFolders[1, 1]}");
            Directory.CreateDirectory($"input/{ttModeFolders[2, 1]}");
            Directory.CreateDirectory($"input/{ttModeFolders[3, 1]}");
            extractTPL = IO.IOBase.ExtractDefaultTPLs();

            bool checkUpdates = Properties.Settings.Default.AutoUpdate;

            string[] args = Environment.GetCommandLineArgs();
            if (args.Length > 1)
            {
                try
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
                catch (Exception ex)
                {
                    MsgWindow.Show(ex.Message);
                }
            }

            if (checkUpdates)
            {
                SettingsWindow.TryUpdate();
            }

            if (!Directory.Exists("input"))
            {
                Directory.CreateDirectory("input");
                Directory.CreateDirectory($"input/{ttModeFolders[0, 1]}");
                Directory.CreateDirectory($"input/{ttModeFolders[1, 1]}");
                Directory.CreateDirectory($"input/{ttModeFolders[2, 1]}");
                Directory.CreateDirectory($"input/{ttModeFolders[3, 1]}");
            }

            File.WriteAllText("temp/PulsarBMG.txt", PulsarRes.BMG);

        }
    }
}