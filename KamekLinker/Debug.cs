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
        public Debug(string mapPath, string readElf, uint startAddr)
        {
            curAddr = startAddr;
            this.mapPath = mapPath;
            this.readElfPath = readElf;
            map = File.ReadAllLines($"{mapPath}").ToList();
            mapAddr = new List<uint>();
            outputs = new List<(Task<string>, int)>();
            (uint, uint) closestFuncToStartAddr = (0, 0);
            for (int i = 0; i < map.Count; i++)
            {
                string mapEntry = map[i];
                try
                {
                    uint gameAddr = uint.Parse(mapEntry.Split(' ')[0], System.Globalization.NumberStyles.HexNumber);
                    if (gameAddr >= startAddr && gameAddr < endAddr)
                    {
                        map.Remove(mapEntry);
                        i--;
                    }
                    else
                    {
                        if (gameAddr < startAddr && gameAddr > closestFuncToStartAddr.Item2) closestFuncToStartAddr = ((uint)i, gameAddr);
                        mapAddr.Add(gameAddr);
                    }
                }
                catch
                {
                    map.Remove(mapEntry);
                    continue;
                }
            }
            mapLine = closestFuncToStartAddr.Item1 + 1;



        }


        public void AnalyzeFile(string path, int index)
        {
            Process shell = new Process();
            shell.StartInfo.FileName = @"powershell.exe";
            shell.StartInfo.Verb = "runas";
            shell.StartInfo.CreateNoWindow = true;
            shell.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            shell.StartInfo.UseShellExecute = false;
            shell.StartInfo.RedirectStandardOutput = true;
            shell.StartInfo.Arguments = $@"{readElfPath} {path} -s -W -C";
            shell.Start();
            Task<string> output = shell.StandardOutput.ReadToEndAsync();
            outputs.Add((output, index));
        }

        static (string, string) DemangleNode(string node)
        {
            bool pointer = false;
            bool reference = false;
            bool constant = false;
            bool unsignedType = false;

            while (true)
            {
                if (node[0] == 'P')
                {
                    pointer = true;
                }
                else if (node[0] == 'R')
                {
                    reference = true;
                }
                else if (node[0] == 'C')
                {
                    constant = true;
                }
                else if (node[0] == 'U')
                {
                    unsignedType = true;
                }
                else
                {
                    break;
                }
                node = node[1..];
            }

            string pre = string.Empty;
            string post = string.Empty;
            if (reference) post = "&";
            if (pointer) post = "*";
            if (constant) pre = "const ";
            if (unsignedType) pre += "unsigned ";

            switch (node[0])
            {
                case 'i': return (pre + "int" + post, node[1..]);
                case 'b': return (pre + "bool" + post, node[1..]);
                case 'c': return (pre + "char" + post, node[1..]);
                case 's': return (pre + "short" + post, node[1..]);
                case 'l': return (pre + "long" + post, node[1..]);
                case 'f': return (pre + "float" + post, node[1..]);
                case 'd': return (pre + "double" + post, node[1..]);
                case 'w': return (pre + "wchar_t" + post, node[1..]);
                case 'v': return (pre + "void" + post, node[1..]);
                case 'F':
                    if (node.Length == 2) return DemangleNode(node[1..]);
                    else return DemangleFuncNode(node[1..]);
                case 'Q':
                    int compCount = int.Parse(node[1].ToString());
                    node = node[2..];
                    string accum = string.Empty;
                    for (int idx = 0; idx < compCount; idx++)
                    {
                        var (demangle, newNode) = DemangleNode(node);
                        accum += demangle + "::";
                        node = newNode;
                    }
                    return (pre + accum[..^2] + post, node);
                default:
                    if (char.IsDigit(node[0]))
                    {
                        int counter = 1;
                        while (counter < node.Length && char.IsDigit(node[counter]))
                        {
                            counter++;
                        }
                        int length = int.Parse(node[..counter]);
                        if (node[counter] == '>' || node[counter] == ',')
                        {
                            return (length.ToString(), node[counter..]);
                        }
                        return (pre + node[counter..(counter + length)] + post, node[(counter + length)..]);
                    }
                    return (node, string.Empty);
            }
        }

        static (string, string) DemangleFuncNode(string node)
        {
            string args = string.Empty;
            while (node[0] != '_')
            {
                if (args.Length > 0)
                {
                    args += ", ";
                }
                var (arg, newNode) = DemangleNode(node);
                args += arg;
                node = newNode;
            }
            node = node[1..];
            var (returnType, rem) = DemangleNode(node);
            return (string.Format("{0}({1})", returnType, args), rem);
        }

        static int FindSepIdx(string name, int idx)
        {
            int count = 0;
            int retval = 0;
            foreach (char ch in name)
            {
                if (ch == '<' || ch == ',')
                {
                    if (idx == count)
                    {
                        return retval;
                    }
                    count++;
                }
                retval++;
            }
            return -1;
        }

        static string DemangleTemplates(string name)
        {
            int token = 0;
            string accum = name;
            while (true)
            {
                int tidx = FindSepIdx(accum, token);
                token++;
                if (tidx < 0)
                {
                    return accum;
                }
                int sidx = tidx + 1;
                string toDem = accum[sidx..];
                accum = accum[..sidx];
                var (dem, rem) = DemangleNode(toDem);
                accum += dem + rem;
            }
        }

        static string Demangle(string sym)
        {
            if (sym.Contains("__sinit_")) return sym;
            int typeSplit = sym[1..].IndexOf("__");
            string funcName = DemangleTemplates(sym[..(typeSplit + 1)]);
            string rem = sym[(typeSplit + 3)..];
            (string, string) duo;
            if (rem[0] == 'F') duo = ("", rem);
            else duo = DemangleNode(rem);
            var (funcType, rem2) = duo;
            funcType = DemangleTemplates(funcType);
            char objType = rem2[0];
            string post = string.Empty;
            if (objType == 'C')
            {
                post = " const";
                objType = rem2[1];
                rem2 = rem2[1..];
            }
            rem2 = rem2[1..];
            string funcArgs = string.Empty;
            while (rem2.Length > 0)
            {
                if (funcArgs.Length > 0)
                {
                    funcArgs += ", ";
                }
                var (arg, newRem) = DemangleNode(rem2);
                funcArgs += DemangleTemplates(arg);
                rem2 = newRem;
            }
            return $"{funcType}::{funcName}({funcArgs}){post}";
        }



        public void Save()
        {
            outputs.OrderBy(x => x.Item2);
            foreach ((Task<string>, int) output in outputs.ToList())
            {
                output.Item1.Wait();
                List<string> funcLines = new List<string>();
                foreach (string line in output.Item1.Result.Split("\r\n"))
                {
                    if (line != "" && line.Substring(0, 31).Contains("FUNC"))
                    {
                        funcLines.Add(line);
                    }
                }
                uint funcAddr = curAddr;
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
                    if (prio > 1)
                    {
                        totalLow += length;
                        continue;
                    }
                    realFuncLength = length;
                    funcAddr = curAddr + offset;

                    string[] cols = funcLine.Split(' ');
                    string funcName = cols[cols.Length - 1];

                    map.Insert((int)mapLine, $"{funcAddr:X} {realFuncLength:X8} {funcAddr:X} 0 {Demangle(funcName)}");
                    ++mapLine;
                    /*
                     * for (int i = 0; i < mapAddr.Count - 1; i++)
                    {
                        uint gameFunc = mapAddr[i];
                        if (gameFunc <= funcAddr && mapAddr[i + 1] > funcAddr)
                        {
                            map.Insert(i, $"{funcAddr:X} {realFuncLength:X8} {funcAddr:X} 0 {funcName.Trim('_')}");
                            break;
                        }
                    }
                    */
                }
                curAddr = funcAddr + realFuncLength + totalLow;
            }
            //map.RemoveAll(x => x == "" || x == null);
            //map = map.OrderBy(x => uint.Parse(x.Split(' ')[0], NumberStyles.HexNumber)).ToList();
            map.Insert(0, ".text section layout");
            map.Insert(map.Count, ".data section layout");
            File.Copy(@$"{mapPath}", @$"{mapPath}.bak", true);
            File.WriteAllLines(@$"{mapPath}", map);
        }
        //Very bad and hardcoded but hard to guess where the binary gets allocated in a heap we do not know about yet
        static uint endAddr = 0x80510238;
        List<string> map;
        List<(Task<string>, int)> outputs;
        List<uint> mapAddr;
        uint mapLine;
        uint curAddr;
        string mapPath;
        string readElfPath;
    }
}
