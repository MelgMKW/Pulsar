using System;
using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace Pulsar_Pack_Creator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    partial class MainWindow : Window
    {
        //CTsGhosts
        private void SetGhostLabelName(int row, string text)
        {
            TextBlock ghostLabel = GhostGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row + firstTrackRow && Grid.GetColumn(x) == 0) as TextBlock;
            ghostLabel.Text = text == "Name" ? $"Track {row + 1}" : text;
        }

        private void SetExpertName(string text, int row, int col)
        {
            TextBox ghostBox = GhostGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row + firstTrackRow && Grid.GetColumn(x) == col + 1) as TextBox;
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

        //RegsGhosts
        private void OnRegsGhostChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.IsKeyboardFocused)
            {
                int row = Grid.GetRow(box) - 1;
                int col = Grid.GetColumn(box) - 1;
                //string oldText = cups[curCup].expertFileNames[row, col];
                string text = box.Text;
                regsExperts[curRegsCup, row, col] = text;
            }
        }

        private void OnLeftRegsArrowClick(object sender, RoutedEventArgs e)
        {
            UpdateCurRegsPage(-1);
        }
        private void OnRightRegsArrowClick(object sender, RoutedEventArgs e)
        {
            UpdateCurRegsPage(1);
        }
        private void SetRegsExpertName(string text, int row, int col)
        {
            TextBox ghostBox = RegsGhostGrid.Children.Cast<UIElement>().First(x => Grid.GetRow(x) == row + firstTrackRow && Grid.GetColumn(x) == col + 1) as TextBox;
            if (text == "" || text == null) ghostBox.Text = "RKG File";
            else ghostBox.Text = text;
        }

        private void UpdateCurRegsPage(short direction)
        {
            curRegsCup = (ushort)((curRegsCup + 8 + direction) % 8);

            RegsGhostTrackName1.Text = PulsarGame.MarioKartWii.idxToFullNames[curRegsCup * 4];
            RegsGhostTrackName2.Text = PulsarGame.MarioKartWii.idxToFullNames[curRegsCup * 4 + 1];
            RegsGhostTrackName3.Text = PulsarGame.MarioKartWii.idxToFullNames[curRegsCup * 4 + 2];
            RegsGhostTrackName4.Text = PulsarGame.MarioKartWii.idxToFullNames[curRegsCup * 4 + 3];

            for (int row = 0; row < 4; row++)
            {
                for (int col = 0; col < 4; col++)
                {
                    SetRegsExpertName(regsExperts[curRegsCup, row, col], row, col);
                }
            }
        }
    }
}