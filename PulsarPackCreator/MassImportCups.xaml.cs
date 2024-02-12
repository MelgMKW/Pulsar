using Microsoft.VisualBasic;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Windows;
using System.Drawing;
using static PulsarPackCreator.MainWindow;
using System.Windows.Shapes;


namespace PulsarPackCreator
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
        }
        protected override void OnClosing(CancelEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        private void OnSaveCupsImportClick(object sender, RoutedEventArgs e)
        {

            //Need to add checks here i.e. slot validity, number of lines in each text box

            string[] tplsImport = CupsTPLImport.Text.Replace("\r", "").Trim('\n').Split("\n").ToArray();
            string[] namesImport = CupsNameImport.Text.Replace("\r", "").Trim('\n').Split("\n").ToArray();

            foreach (string cur in namesImport)
            {
                if (!CheckTrackName(cur))
                {
                    MsgWindow.Show($"Track {cur} has an invalid name as it contains one of <>:\"/\\|?*", this);
                    return;
                }
            }
            if (namesImport.Length != tplsImport.Length)
            {
                MsgWindow.Show("Not an equal amount of entries in both columns");
            }

            if (namesImport.Length > parent.ctsCupCount || tplsImport.Length > parent.ctsCupCount)
            {
                MsgWindow.Show("Entries exceeded existing number of cups.");
                return;
            }

            if (namesImport.Length > 100 || tplsImport.Length > 100)
            {
                MsgWindow.Show("You can only customize the names and images of up to 100 cups.");
                return;
            }

            for (int i = 0; i < tplsImport.Length; i++)
            {
                string curIMGPath = $"input/CupIcons/{tplsImport[i]}";
                if (!File.Exists(curIMGPath))
                {
                    MsgWindow.Show($"{curIMGPath} could not be found in the input folder. Make sure to specify .tpl at the end of your tpl names.");
                    return;
                }
                //parent.cups[i].imgPath = curIMGPath;
                //parent.cupNames[i] = namesImport[i];
            }
            Hide();
        }

        public bool IsCorrectCupIcon(string path)
        {
            Image image = Image.FromFile(path);
            if (image.Width != image.Height)
            {
                MsgWindow.Show($"The image resolution for {path} is not a square.");
                return false;
            }
            return true;
        }

        public static System.Drawing.Image ResizeImage(string path)
        {
            try
            {
                Image imgToResize = Image.FromFile(path);
                // Get the image current width
                int sourceWidth = imgToResize.Width;
                // Get the image current height
                int sourceHeight = imgToResize.Height;
                float nPercent = 0;
                float nPercentW = 0;
                float nPercentH = 0;
                // Calculate width and height with new desired size
                nPercentW = (128.0f / sourceWidth);
                nPercentH = (128.0f / sourceHeight);
                nPercent = Math.Min(nPercentW, nPercentH);
                // New Width and Height
                int destWidth = (int)(sourceWidth * nPercent);
                int destHeight = (int)(sourceHeight * nPercent);
                Bitmap b = new Bitmap(destWidth, destHeight);
                Graphics g = Graphics.FromImage(b);
                g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
                // Draw image with new width and height
                g.DrawImage(imgToResize, 0, 0, destWidth, destHeight);
                g.Dispose();
                return (Image)b;
            }
            catch
            {
                return null;
            }
        }

    }
}