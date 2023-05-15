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
using System.Globalization;
using System.Windows.Controls.Primitives;
using System.Windows.Shapes;
using static System.Windows.Forms.LinkLabel;
using System.ComponentModel;
using System.Dynamic;
using System.Drawing;

namespace PulsarPackCreator
{
    public partial class CrashWindow : Window
    {
        private char region = 'P';
        public CrashWindow()
        {
            InitializeComponent();
        }

        public void Load(string fileName)
        {
            using BigEndianReader bin = new BigEndianReader(File.Open(fileName, FileMode.Open));
            if (bin.ReadInt32() != 0x50554c44)
            {
                bin.Close();
                MessageBox.Show("Invalid Crash File.");
                return;
            }
            Show();
            ImportCrash(bin);
        }
        protected override void OnClosing(CancelEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        private void ImportCrash(BigEndianReader bin)
        {
            bin.BaseStream.Position += 3;
            region = bin.ReadChar();
            bin.BaseStream.Position += 4;
            UInt32 error = bin.ReadUInt32();
            UInt32 srr0 = ReadNext(bin);
            UInt32 srr1 = ReadNext(bin);
            UInt32 msr = ReadNext(bin);
            UInt32 cr = ReadNext(bin);
            UInt32 lr = ReadNext(bin);

            UInt32[] gprs = new UInt32[32];
            for (int i = 0; i < 32; i++)
            {
                gprs[i] = ReadNext(bin);
            }
            double[] fprs = new double[32];
            for (int i = 0; i < 32; i++)
            {
                fprs[i] = ReadNextFPR(bin);
            }
            bin.ReadUInt64();
            UInt64 fscr = bin.ReadUInt64();
            UInt32[,] stackFrame = new UInt32[2, 10];
            for (int i = 0; i < 10; i++)
            {
                stackFrame[0, i] = ReadNext(bin);
                stackFrame[1, i] = ReadNext(bin);
            }
            bin.Close();
            string errorString;
            if (error == 2) errorString = "DSI";
            else if (error == 3) errorString = "ISI";
            else if (error == 7 || error == 8) errorString = "Float";
            else errorString = $"{error}";

            string crash = $"Error: {errorString}\nRegion: {region}\nSRR0: 0x{srr0:X8} {CheckSymbols(srr0)}\nSRR1: 0x{srr1:X8}\nMSR:  0x{msr:X8}\nCR:   0x{cr:X8}\nLR:   0x{lr:X8} {CheckSymbols(lr)}";
            crash = crash + "\n\nGPRs";
            for (int i = 0; i < 8; i++)
            {
                crash = crash + "\n";
                for (int j = 0; j < 4; j++)
                {
                    int idx = i + j * 8;
                    crash = crash + $"R{idx:D2}: 0x{gprs[idx]:X8} ";
                }

            }

            crash = crash + $"\n\nFPRs FSCR: 0x{fscr:X8}";
            for (int i = 0; i < 8; i++)
            {
                crash = crash + "\n";
                for (int j = 0; j < 4; j++)
                {
                    int idx = i + j * 8;
                    crash = crash + $"F{idx:D2}: {fprs[idx].ToString("E2").PadLeft(10)} ";
                }
            }
            crash = crash + "\n\nStack Frame";
            for (int i = 0; i < 10; i++)
            {
                crash = crash + "\n";
                crash = crash + $"SP: 0x{stackFrame[0, i]:X8} LR: 0x{stackFrame[1, i]:X8} {CheckSymbols(stackFrame[1, i])}";
            }
            CrashText.Text = crash;
            bin.Close();
        }


        private UInt32 ReadNext(BigEndianReader bin)
        {
            bin.BaseStream.Position += 4;
            return bin.ReadUInt32();
        }
        private double ReadNextFPR(BigEndianReader bin)
        {
            bin.BaseStream.Position += 8;
            return bin.ReadDouble();
        }

        private void OnDropFile(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
                BigEndianReader bin = new BigEndianReader(File.Open(files[0], FileMode.Open));
                int magic = bin.ReadInt32();
                bin.BaseStream.Position -= 4;
                if (magic == 0x50554c44)
                {
                    bin.Close();
                    Load(files[0]);
                }
            }
        }

        private string CheckSymbols(UInt32 address)
        {
            try
            {
                char[] delims = new[] { '\r', '\n' };
                string[] lines = PulsarRes.MAP.Split(delims, StringSplitOptions.RemoveEmptyEntries);
                string[] splices = PulsarRes.Port.Replace("-8", " 8").Replace(":", "").Split(delims, StringSplitOptions.RemoveEmptyEntries);

                int idx = Array.IndexOf(splices, $"[{region}]");
                if (idx == -1) throw new Exception();
                if (region != 'P')
                {
                    idx++;
                    while (true)
                    {
                        if (splices[idx] == "#") throw new Exception();
                        string[] curSplice = splices[idx].Split(' ');
                        int isNegative = curSplice[2].Contains('-') ? -1 : 1;
                        UInt32 palAddress = (UInt32)((int)address - isNegative * int.Parse(curSplice[2].Replace("-0x", "").Replace("+0x", ""), NumberStyles.HexNumber));
                        if (UInt32.Parse(curSplice[0], NumberStyles.HexNumber) <= palAddress &&
                        palAddress < UInt32.Parse(curSplice[1], NumberStyles.HexNumber))
                        {
                            address = palAddress;
                            break;
                        }
                        idx++;
                    }
                }

                for (int i = 0; i < lines.Length - 1; i++)
                {
                    string[] curLine = lines[i].Split(' ');
                    string[] nextLine = lines[i + 1].Split(' ');

                    if (UInt32.Parse(curLine[0], NumberStyles.HexNumber) <= address &&
                        address < UInt32.Parse(nextLine[0], NumberStyles.HexNumber))
                    {
                        return region == 'P' ? curLine[1] : $"{curLine[1]}(0x{address:X8})";
                    }
                }
                throw new Exception();
            }
            catch
            {
                return "";
            }
        }
    }
}
