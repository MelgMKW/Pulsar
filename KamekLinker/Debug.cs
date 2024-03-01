using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace Kamek
{
    class Debug
    {
        public Debug(string mapPath, string readElfPath)
        {
            this.mapPath = mapPath;
            this.readElfPath = readElfPath;
            map = File.ReadAllLines($"{mapPath}").ToList();
            mapAddr = new List<uint>();
            map.RemoveAt(0);
            map.RemoveAt(map.Count - 1);
            for (int i = 0; i < map.Count; i++)
            {
                string mapEntry = map[i];
                try { 
                uint gameAddr = uint.Parse(mapEntry.Split(' ')[0], System.Globalization.NumberStyles.HexNumber);
                if (gameAddr > 0x80390000 && gameAddr < endAddr)
                {
                    map.Remove(mapEntry);
                    i--;
                }
                else
                {
                    mapAddr.Add(gameAddr);
                }
                }
                catch
                {
                    continue;
                }          
            }
            readElf = new Process();
            readElf.StartInfo.FileName = @"powershell.exe";
            readElf.StartInfo.Verb = "runas";
            readElf.StartInfo.CreateNoWindow = true;
            readElf.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            readElf.StartInfo.UseShellExecute = false;
            readElf.StartInfo.RedirectStandardOutput = true;


        }

        public void SetMap(string mapPath)
        {
            this.mapPath = mapPath;
        }

        public void SetReadElf(string readElfPath)
        {
            this.readElfPath = readElfPath;
        }
        public async Task AnalyzeFile(string path)
        {
            string output = "";
                         
            readElf.StartInfo.Arguments = $@"{readElfPath} {path} -s";
            readElf.Start();
            output = readElf.StandardOutput.ReadToEnd();
            await readElf.WaitForExitAsync();
            
            string[] lines = output.Split("\r\n");
            List<string> funcLines = new List<string>();
            foreach (string line in lines)
            {
                if (line != ""  && line.Substring(0, 31).Contains("FUNC"))
                {
                    funcLines.Add(line);
                }
            }
            uint funcAddr = 0;
            uint length = 0;
            uint realFuncLength = 0;
            uint totalLow = 0;
            funcLines = funcLines.OrderBy(x => uint.Parse(x.Substring(8, 8), NumberStyles.HexNumber)).ToList();
            foreach (string funcLine in funcLines)
            {
                uint offset;
                uint prio;
                bool offsetRet = uint.TryParse(funcLine.Substring(8, 8), NumberStyles.HexNumber, CultureInfo.InvariantCulture, out offset);
                bool lengthRet = uint.TryParse(funcLine.Substring(16, 7), CultureInfo.InvariantCulture, out length);
                bool prioRet = uint.TryParse(funcLine.Substring(47, 3), CultureInfo.InvariantCulture, out prio);
                if (!offsetRet || !lengthRet) continue;
                if(prio > 1)
                {
                    totalLow += length;
                    continue;
                }
                realFuncLength = length;
                funcAddr = curAddr + offset;

                string[] cols = funcLine.Split(' ');
                string funcName = cols[cols.Length - 1];

                for (int i = 0; i < mapAddr.Count - 1; i++)
                {
                    uint gameFunc = mapAddr[i];
                    if (gameFunc <= funcAddr && mapAddr[i + 1] > funcAddr)
                    {
                        map.Insert(i, $"{funcAddr:X} {realFuncLength:X8} {funcAddr:X} 0 {funcName.Trim('_')}");
                        break;
                    }
                }
            }
            curAddr = funcAddr + realFuncLength + totalLow;
        }

        public void Save()
        {
            map.RemoveAll(x => x == "");
            map = map.OrderBy(x => uint.Parse(x.Split(' ')[0], NumberStyles.HexNumber)).ToList();
            map.Insert(0, ".text section layout");
            map.Insert(map.Count, ".data section layout");
            File.WriteAllLines(@$"{mapPath}", map);
        }
        //Very bad and hardcoded but hard to guess where the binary gets allocated in a heap we do not know about yet
        static uint startAddr = 0x803992e0;
        static uint endAddr = 0x80510238;
        Process readElf;
        List<string> map;
        List<uint> mapAddr;
        uint curAddr = startAddr;
        string mapPath;
        string readElfPath;
    }
}
