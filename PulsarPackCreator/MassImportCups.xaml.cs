using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.Versioning;
using System.Windows;
using static Pulsar_Pack_Creator.MainWindow;


namespace Pulsar_Pack_Creator
{
    /// <summary>
    /// Interaction logic for parent.xaml
    /// </summary>
    public partial class MassCupsImportWindow : Window
    {
        public static MainWindow parent;

        public MassCupsImportWindow(MainWindow parentWindow)
        {
            parent = parentWindow;
            InitializeComponent();
            this.Height = SystemParameters.PrimaryScreenHeight * 0.7;
        }
        protected override void OnClosing(CancelEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        private void OnSaveCupsImportClick(object sender, RoutedEventArgs e)
        {

            //Need to add checks here i.e. slot validity, number of lines in each text box

            string[] iconImport = CupsIconImport.Text.Replace("\r", "").Trim('\n').Split("\n").ToArray();
            string[] namesImport = CupsNameImport.Text.Replace("\r", "").Trim('\n').Split("\n").ToArray();

            foreach (string cur in namesImport)
            {
                if (!CheckTrackName(cur))
                {
                    MsgWindow.Show($"Track {cur} has an invalid name as it contains one of <>:\"/|?", this);
                    return;
                }
            }
            if (namesImport.Length != iconImport.Length)
            {
                MsgWindow.Show("Not an equal amount of entries in both columns");
            }

            if (namesImport.Length > parent.ctsCupCount || iconImport.Length > parent.ctsCupCount)
            {
                MsgWindow.Show("Entries exceeded existing number of cups.");
                return;
            }

            /*
            if (namesImport.Length > 100 || iconImport.Length > 100)
            {
                MsgWindow.Show("You can only customize the names and images of up to 100 cups.");
                return;
            }
            */

            for (int i = 0; i < iconImport.Length; i++)
            {
                string curIMGPath = $"input/CupIcons/{iconImport[i]}";
                if (!File.Exists(curIMGPath))
                {
                    MsgWindow.Show($"{iconImport[i]} could not be found in input/CupIcons. Make sure to specify the extension at the end of the filename.");
                    return;
                }
                parent.cups[i].iconName = iconImport[i];
                parent.cups[i].name = namesImport[i];
            }
            Cup curCup = parent.cups[parent.curCup];
            parent.CupName.Text = curCup.name;
            parent.CupIcon.Text = curCup.iconName;
            parent.DisplayImage(curCup.iconName);
            Hide();
        }

    }
}