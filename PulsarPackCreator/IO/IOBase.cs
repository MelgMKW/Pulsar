using PulsarPackCreator;
using System;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;
using System.Windows.Media;
using System.Threading;
using System.Configuration;


namespace PulsarPackCreator.IO
{
    public enum Result
    {
        Success,
        AlreadyInUse,
        FileNotFound,
        NoDate,
        NoWiimmfi,
        NoModName,

        InvalidConfigFile,
        BadInfo,
        BadCups,
        BadText,
        BadBMG,
        BadFile,
        

        UnknownError,
    };
    abstract class IOBase
    {
        

        public IOBase(MainWindow window)
        {
            parameters = window.parameters;
            ctsCupCount = window.ctsCupCount;

        }
        protected MainWindow.Parameters parameters;
        protected readonly UInt16 ctsCupCount;
        protected const int binMagic =  0x50554C53;
        protected const int infoMagic = 0x494E464F;
        protected const int cupsMagic = 0x43555053;
        protected const int textMagic = 0x54455854;
        protected const int fileMagic = 0x46494C45;
        protected const ulong bmgMagic = 0x4D455347626D6731;


        protected static readonly int SECTIONCOUNT = 4;
        protected static readonly int CONFIGVERSION = 2;
        protected static readonly int INFOVERSION = 1;
        protected static readonly int CUPSVERSION = 2;
        protected static readonly int TEXTVERSION = 1;

        public string error;
        public static CancellationTokenSource cancelToken = new CancellationTokenSource();

        protected static void RequestBMGAction(bool isEncode) //else will decode
        {
            File.WriteAllBytes("temp/wbmgt.exe", PulsarRes.wbmgt);
            ProcessStartInfo processInfo = new ProcessStartInfo();
            processInfo.FileName = @"wbmgt.exe";
            processInfo.Arguments = isEncode ? "encode BMG.txt" : "decode bmg.bmg --no-header --export";
            processInfo.WorkingDirectory = @"temp/";
            processInfo.CreateNoWindow = true;
            processInfo.WindowStyle = ProcessWindowStyle.Hidden;
            processInfo.UseShellExecute = false;

            Process process = new Process();
            process.StartInfo = processInfo;
            process.Start();
            process.WaitForExit();
        }
        public long RoundUp(long value, uint aligment)
        {
            return value + (aligment - 1) & ~(aligment - 1);
        }
        public static void OpenDir(string path) => Process.Start("explorer.exe", path);

        public static string DisplayTimes(PulsarGame.TimeEntry[] entries, int idx)
        {

            string times = "";
            for (int i = 0; i < 11; i++)
            {
                PulsarGame.TimeEntry entry = entries[i + 11 * idx];
                if (entry.isActive == 0) break;
                TextInfo info = new CultureInfo("en-GB", false).TextInfo;

                string chara = info.ToTitleCase(((PulsarGame.MarioKartWii.CharacterId)entry.character).ToString().Replace('_', ' ').ToLower());
                string kart = info.ToTitleCase(((PulsarGame.MarioKartWii.KartId)entry.kart).ToString().Replace('_', ' ').ToLower());
                times += $"{string.Format("{0,2}", i + 1)}. {entry.minutes}:{entry.seconds.ToString().PadLeft(2, '0')}.{entry.milliseconds.ToString().PadLeft(3, '0')} " +
                    $"on {chara} + {kart}\n";


            }
            return times;
        }
        public static void ImportLeaderboard(byte[] raw)
        {
            PulsarGame.Leaderboard ldb = PulsarGame.BytesToStruct<PulsarGame.Leaderboard>(raw);
            string display = ldb.trackName;

            PulsarGame.TimeEntry[] entries = ldb.entries;
            for (int i = 0; i < 4; i++)
            {
                if (entries[11 * i].isActive == 0) continue;
                display += $"\n{PulsarGame.ttModes[i]}\n{DisplayTimes(entries, i)}";
            }
            MsgWindow.Show(display, $"{ldb.trackName} Leaderboard");
        }

        public static T CreateSubCat<T>(byte[] raw, int offset) where T : struct
        {
            byte[] catRaw = raw.Skip(offset).Take(Marshal.SizeOf(typeof(T))).ToArray();
            return PulsarGame.BytesToStruct<T>(catRaw);
        }

        public async static Task ExtractDefaultTPLs()
        {
            await File.WriteAllBytesAsync("temp/wszst.exe", PulsarRes.wszst);
            await File.WriteAllBytesAsync("temp/wimgt.exe", PulsarRes.wimgt);
            await File.WriteAllBytesAsync("temp/UIAssets.szs", PulsarRes.UIAssets);

            ProcessStartInfo wszstProcessInfo = new ProcessStartInfo();
            wszstProcessInfo.FileName = @"wszst.exe";
            wszstProcessInfo.Arguments = "extract UIAssets.szs";
            wszstProcessInfo.WorkingDirectory = @"temp/";
            wszstProcessInfo.CreateNoWindow = true;
            wszstProcessInfo.WindowStyle = ProcessWindowStyle.Hidden;
            wszstProcessInfo.UseShellExecute = false;

            Process wszstProcess = new Process();
            wszstProcess.StartInfo = wszstProcessInfo;
            wszstProcess.Start();
            await wszstProcess.WaitForExitAsync();

            ProcessStartInfo wimgtProcessInfo = new ProcessStartInfo();
            wimgtProcessInfo.FileName = @"temp/wimgt.exe";
            wimgtProcessInfo.CreateNoWindow = true;
            wimgtProcessInfo.WindowStyle = ProcessWindowStyle.Hidden;
            wimgtProcessInfo.UseShellExecute = false;

            Process wimgtProcess = new Process();
            wimgtProcess.StartInfo = wimgtProcessInfo;

            for (int i = 0; i < MainWindow.Cup.maxCupIcons; i++)
            {
                if (cancelToken.IsCancellationRequested)
                {
                    return;
                }
                wimgtProcessInfo.Arguments = $"decode temp/UIAssets.d/button/timg/icon_{i:D2}.tpl --dest \"temp/{MainWindow.Cup.defaultNames[i]}.png\" -o";
                wimgtProcess.Start();
                if (i == 0)
                {
                    wimgtProcess.WaitForExit();
                    MainWindow window = System.Windows.Application.Current.MainWindow as MainWindow;
                    window.DisplayImage(window.CupIcon.Text);
                }
                else await wimgtProcess.WaitForExitAsync(cancelToken.Token);
            }

        }



    }



}
