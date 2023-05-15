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
using System.IO.Hashing;
using System.Diagnostics.Eventing.Reader;

namespace PulsarPackCreator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private void SetGhostLabelName(int row, string text)
        {
            TextBlock ghostLabel = GhostGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row + 1 && Grid.GetColumn(x) == 0) as TextBlock;
            ghostLabel.Text = text == "Name" ? $"Track {row + 1}" : text;
        }

        private void SetExpertName(string text, int row, int col)
        {
            TextBox ghostBox = GhostGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row + 1 && Grid.GetColumn(x) == col + 1) as TextBox;
            if (text == "") ghostBox.Text = "RKG File";
            else ghostBox.Text = text;
        }
        private void OnGhostChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.IsKeyboardFocused)
            {
                int row = Grid.GetRow(box) - 1;
                int col = Grid.GetColumn(box) - 1;
                string oldText = cups[curCup].expertFileNames[row, col];
                string text = box.Text;
                cups[curCup].expertFileNames[row, col] = text;
                if (text != "RKG File" && text != "" && (oldText == "RKG File" || oldText == ""))
                {
                    trophyCount[col]++;
                }
                else if (trophyCount[col] > 0 && (text == "RKG File" || text == "")) trophyCount[col]--;
            }
        }
    }
}