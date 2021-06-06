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
    /// Interaction logic for StatisticsWindow.xaml
    /// </summary>
    public partial class StatisticsWindow : Window
    {
        Communicator _communicator;

        public StatisticsWindow(Communicator com)
        {
            // Initialize communicator
            _communicator = com;

            // Get statistics
            string resp = com.sendPacketToServer(Serializer.SerializeStatisticsRequest());
            StatisticsResponse stats = Deserializer.DeserializeStatisticsResponse(resp);

            InitializeComponent();
        }

        public StatisticsWindow()
        {
            InitializeComponent();
        }

        private void return_to_menu(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = new MainWindow(this._communicator);
            Visibility = Visibility.Hidden;
            mainWindow.Show();
        }

        private void logout(object sender, EventArgs e)
        {
            this._communicator.sendPacketToServer(Serializer.SerializeLogoutRequest());
            this.Close();
        }
    }
}
