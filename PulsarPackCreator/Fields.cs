using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
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

        //Rows
        private UIElement[][] rows;

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
        public static ImportWindow importWindow;
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

            importWindow = new ImportWindow(this);
            cupsImportWindow = new MassCupsImportWindow(this);
            crashWindow = new CrashWindow();
            settingsWindow = new SettingsWindow();

            messageWindow = new MsgWindow();

            rows = new UIElement[4][]{
                new UIElement[]{ File1, Name1, Author1, Version1, Slot1, Music1, Variants1},
                new UIElement[]{ File2, Name2, Author2, Version2, Slot2, Music2, Variants2},
                new UIElement[]{ File3, Name3, Author3, Version3, Slot3, Music3, Variants3},
                new UIElement[]{ File4, Name4, Author4, Version4, Slot4, Music4, Variants4}};

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

            Cup.Track.Variant main = initial.tracks[0].main;
            File1.Text = main.fileName;
            File2.Text = main.fileName;
            File3.Text = main.fileName;
            File4.Text = main.fileName;
            Name1.Text = main.trackName;
            Name2.Text = main.trackName;
            Name3.Text = main.trackName;
            Name4.Text = main.trackName;
            Author1.Text = main.authorName;
            Author2.Text = main.authorName;
            Author3.Text = main.authorName;
            Author4.Text = main.authorName;
            Version1.Text = main.versionName;
            Version2.Text = main.versionName;
            Version3.Text = main.versionName;
            Version4.Text = main.versionName;

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
        public TextBox GetFileBox(int row)
        {
            return (TextBox)rows[row][0];
        }
        public TextBox GetNameBox(int row)
        {
            return (TextBox)rows[row][1];
        }
        public TextBox GetAuthorBox(int row)
        {
            return (TextBox)rows[row][2];
        }
        public TextBox GetVersionBox(int row)
        {
            return (TextBox)rows[row][3];
        }
        public ComboBox GetSlotBox(int row)
        {
            return (ComboBox)rows[row][4];
        }
        public ComboBox GetMusicSlotBox(int row)
        {
            return (ComboBox)rows[row][5];
        }
        public Button GetVariantsButton(int row)
        {
            return (Button)rows[row][6];
        }
    }
}