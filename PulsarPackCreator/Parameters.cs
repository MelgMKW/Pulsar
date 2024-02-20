using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;

namespace PulsarPackCreator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    partial class MainWindow : Window
    {
        public class Parameters
        {
            public byte regsMode = 0;
            public bool hasTTTrophies = false;
            public bool has200cc = false;
            public bool hasUMTs = false;
            public bool hasFeather = false;
            public bool hasMegaTC = false;
            public int prob100cc = 10;
            public int prob150cc = 65; //mirror = 100 - (100cc + 150cc)
            public int probMirror = 25;
            public int wiimmfiRegion = -1;
            public int trackBlocking = 0;
            public string modFolderName;
        };
        private void OnOptionsClick(object sender, RoutedEventArgs e)
        {

        }
        private void OnDateChange(object sender, SelectionChangedEventArgs e)
        {
            DatePicker datePicker = sender as DatePicker;
            date = DateOnly.FromDateTime((DateTime)datePicker.SelectedDate).ToString();
        }

        private void OnTrackBlockingChange(object sender, SelectionChangedEventArgs e)
        {
            ComboBox box = sender as ComboBox;
            parameters.trackBlocking = (UInt16)box.SelectedValue;
        }

        private void OnWiimmfiRegionChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            if (box.Text == "") return;

            parameters.wiimmfiRegion = int.Parse(box.Text);
        }

        private void OnModFolderChange(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            string text = box.Text;
            if (text.Length > 12)
            {
                MsgWindow.Show("Name is too long. Maximum length is 12 characters.");
                box.Text = "";
            }
            else parameters.modFolderName = $"{text}";
        }
        private void OnRegsChange(object sender, RoutedEventArgs e)
        {
            ComboBox box = sender as ComboBox;
            parameters.regsMode = (byte)box.SelectedIndex;
            RegsGhosts.Visibility = box.SelectedIndex > 0 ? Visibility.Visible : Visibility.Collapsed;            
        }
        private void OnTrophiesToggle(object sender, RoutedEventArgs e)
        {
            if ((sender as CheckBox).IsKeyboardFocused)
            {
                parameters.hasTTTrophies = !parameters.hasTTTrophies;
            }
        }
        private void On200CCToggle(object sender, RoutedEventArgs e)
        {
            if ((sender as CheckBox).IsKeyboardFocused)
            {
                parameters.has200cc = !parameters.has200cc;
                if (parameters.has200cc) CC100Label.Text = "% 200cc";
                else CC100Label.Text = "% 100cc";
            }
        }

        private void OnUMTToggle(object sender, RoutedEventArgs e)
        {
            if ((sender as CheckBox).IsKeyboardFocused)
            {
                parameters.hasUMTs = !parameters.hasUMTs;
            }
        }

        private void OnFeatherToggle(object sender, RoutedEventArgs e)
        {
            if ((sender as CheckBox).IsKeyboardFocused)
            {
                parameters.hasFeather = !parameters.hasFeather;
            }
        }

        private void OnMegaTCToggle(object sender, RoutedEventArgs e)
        {
            CheckBox box = sender as CheckBox;
            if ((sender as CheckBox).IsKeyboardFocused)
            {
                parameters.hasMegaTC = !parameters.hasMegaTC;
            }
        }

        private void On100ccChange(object sender, TextChangedEventArgs e)
        {
            TextBox CC100Box = sender as TextBox;
            TextBox CC150Box = CC150;
            if (CC100Box.Text == "")
            {
                CC100Box.Text = $"{parameters.prob100cc}";
            }
            if (CC100Box != null && CC150Box != null && CC100Box.Text != "" && CC150Box.Text != "")
            {
                int Prob100 = int.Parse(CC100Box.Text);
                if (Prob100 == 100) CC150Box.Text = "0";
                int Prob150 = int.Parse(CC150Box.Text);
                if (Prob100 + Prob150 > 100)
                {
                    MsgWindow.Show("The sum of all probabilities should not exceed 100");
                    CC100Box.Text = $"{parameters.prob100cc}";
                    return;
                }
                int ProbMirror = 100 - (Prob100 + Prob150);
                parameters.prob100cc = Prob100;
                parameters.probMirror = ProbMirror;
                CCMirror.Text = $"{parameters.probMirror}";
            }
        }
        private void On150ccChange(object sender, TextChangedEventArgs e)
        {
            TextBox CC150Box = sender as TextBox;
            TextBox CC100Box = CC100;
            if (CC150Box.Text == "")
            {
                CC150Box.Text = $"{parameters.prob150cc}";
            }
            if (CC100Box != null && CC150Box != null && CC100Box.Text != "" && CC150Box.Text != "")
            {
                int Prob150 = int.Parse(CC150Box.Text);
                if (Prob150 == 100) CC100Box.Text = "0";
                int Prob100 = int.Parse(CC100Box.Text);
                if (Prob100 + Prob150 > 100)
                {
                    MsgWindow.Show("The sum of all info.probabilities should not exceed 100");
                    CC150Box.Text = $"{parameters.prob150cc}";
                    return;
                }
                int ProbMirror = 100 - (Prob100 + Prob150);
                parameters.prob150cc = Prob150;
                parameters.probMirror = ProbMirror;
                CCMirror.Text = $"{parameters.probMirror}";
            }


        }

        private void OnEditPulsarBMGsClick(object sender, RoutedEventArgs e)
        {
            try
            {
                System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();
                startInfo.FileName = Path.GetFullPath("temp/PulsarBMG.txt");
                startInfo.UseShellExecute = true;
                System.Diagnostics.Process.Start(startInfo);
            }
            catch(Exception ex)
            {
                MsgWindow.Show(ex.ToString());
            }
        }
    }
}