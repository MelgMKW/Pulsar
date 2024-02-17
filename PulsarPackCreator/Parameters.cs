using System;
using System.Windows;
using System.Windows.Controls;

namespace PulsarPackCreator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        class Parameters
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

            int.TryParse(box.Text, out parameters.wiimmfiRegion);
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
                CC100Box.Text = $"0";
            }
            if (CC100Box != null && CC150Box != null && CC100Box.Text != "" && CC150Box.Text != "")
            {
                if(!int.TryParse(CC100Box.Text, out int Prob100)) return;
                if (Prob100 == 100) CC150Box.Text = "0";
                if (!int.TryParse(CC150Box.Text, out int Prob150)) return;
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
                CC150Box.Text = $"0";
            }
            if (CC100Box != null && CC150Box != null && CC100Box.Text != "" && CC150Box.Text != "")
            {
                if (!int.TryParse(CC150Box.Text, out int Prob150)) return;
                if (Prob150 == 100) CC100Box.Text = "0";
                if (!int.TryParse(CC100Box.Text, out int Prob100)) return;
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
    }
}
