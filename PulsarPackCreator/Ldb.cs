using System;
using System.Globalization;
using System.Linq;
using System.Runtime.InteropServices;
using System.Windows;

namespace PulsarPackCreator
{
    public partial class MainWindow : Window
    {
        
        private string DisplayTimes(PulsarGame.TimeEntry[] entries, int idx)
        {
            
            string times = "";
            for (int i = 0; i < 11; i++)
            {
                PulsarGame.TimeEntry entry = entries[i + 11 * idx];
                if (entry.isActive == 0) break;
                TextInfo info = new CultureInfo("en-GB", false).TextInfo;
                
                string chara = info.ToTitleCase(((PulsarGame.MarioKartWii.CharacterId)entry.character).ToString().Replace('_', ' ').ToLower());
                string kart = info.ToTitleCase(((PulsarGame.MarioKartWii.KartId)entry.kart).ToString().Replace('_', ' ').ToLower());
                times += $"{String.Format("{0,2}", (i + 1))}. {entry.minutes}:{entry.seconds.ToString().PadLeft(2, '0')}.{entry.milliseconds.ToString().PadLeft(3, '0')} " +
                    $"on {chara} + {kart}\n";
                

            }
            return times;
        }
        private void ImportLeaderboard(byte[] raw)
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

        private T CreateSubCat<T>(byte[] raw, int offset) where T : struct
        {
            byte[] catRaw = raw.Skip(offset).Take(Marshal.SizeOf(typeof(T))).ToArray();
            return PulsarGame.BytesToStruct<T>(catRaw);         
        }
    }
}
