using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace MagshiTriviaClient
{
    /// <summary>
    /// Interaction logic for HighScoreWindow.xaml
    /// </summary>
    public partial class HighScoreWindow : Window
    {
        // Members
        Communicator _communicator;
        public HighScoreWindow(Communicator com)
        {
            this._communicator = com;
            InitializeComponent();
        }
        public HighScoreWindow()
        {
            InitializeComponent();
        }

        private void clicked_menu(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = new MainWindow(this._communicator);
            Visibility = Visibility.Hidden;
            mainWindow.Show();
        }
    }
}
