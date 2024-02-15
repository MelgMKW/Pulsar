using System;
using System.ComponentModel;
using System.Linq;
using System.Windows;

namespace PulsarPackCreator
{
    public partial class MsgWindow : Window
    {
        bool? result = false;
        public enum MsgWindowButton
        {
            OK = 0,
            YesNo = 1
        }

        public enum MsgWindowResult
        {
            OK = 1,
            Yes = 2,
            No = 3
        }

        public MsgWindow()
        {
            InitializeComponent();
        }

        private void MsgWindowClosing(object sender, CancelEventArgs e)
        {
            e.Cancel = true;
            this.Visibility = Visibility.Hidden;
        }

        private void MsgWindowDeactivated(object sender, EventArgs e)
        {
            Window window = (Window)sender;
            window.Topmost = true;
        }

        public static MsgWindowResult Show(string text, string caption, MsgWindowButton button, Window owner = null) //specify owner if the "window" this box appears onto needs to stay visible
        {
            MainWindow main = GetWindow(App.Current.MainWindow) as MainWindow;
            if (owner == null || !owner.IsLoaded)
            {
                owner = Application.Current.Windows.OfType<Window>().SingleOrDefault(x => x.IsActive);
                if(owner == null) owner = main;
            }
            MsgWindow window = MainWindow.messageWindow;
            window.Owner = owner;       
            window.Title = caption;
            window.TextSpace.Text = text;
            window.result = false;

            Thickness margin = new Thickness(0,0,10,5);
            if (button == MsgWindowButton.OK)
            {
                window.No.Visibility = Visibility.Hidden;
                window.OK.Content = "OK";
            }
            else
            {
                window.OK.Content = "Yes";
                window.No.Visibility = Visibility.Visible;
                margin.Right = 90;
            }
            window.OK.Margin = margin;


            window.ShowDialog();
            window.Close();

            if (window.result == true || window.DialogResult == true)
            {
                return button == MsgWindowButton.OK ? MsgWindowResult.OK : MsgWindowResult.Yes;
            }
            else return MsgWindowResult.No;

        }

        public void OnOKClick(object sender, RoutedEventArgs e)
        {
            result = true;
            DialogResult = true;
        }
        public void OnNoClick(object sender, RoutedEventArgs e)
        {
            result = false;
            DialogResult = false;
        }

        public static MsgWindowResult Show(string text, MsgWindowButton button, Window owner = null)
        {
            return Show(text, "", button, owner);
        }

        public static MsgWindowResult Show(string text, string caption, Window owner = null)
        {
            return Show(text, caption, MsgWindowButton.OK, owner);
        }

        public static MsgWindowResult Show(string text, Window owner = null)
        {
            return Show(text, "", MsgWindowButton.OK, owner);
        }

    }
}
