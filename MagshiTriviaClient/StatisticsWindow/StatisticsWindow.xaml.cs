using Newtonsoft.Json;
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
    public struct UserStatistics
    {
        public float average_answer_time;
        public int games_played;
        public int correct_answers;
        public int total_answers;
        public int score;
    }

    /// <summary>
    /// Interaction logic for StatisticsWindow.xaml
    /// </summary>
    public partial class StatisticsWindow : Window
    {
        Communicator _communicator;
        UserStatistics _stats;
        public StatisticsWindow(Communicator com)
        {
            // Initialize communicator
            _communicator = com;
            // Intialize WFM
            InitializeComponent();
            // Set statistics
            setStatistics();
        }

        public StatisticsWindow()
        {
            InitializeComponent();
        }

        private void setStatistics()
        {
            StatisticsResponse response = Deserializer.DeserializeStatisticsResponse(_communicator.sendPacketToServer(Serializer.SerializeStatisticsRequest()));
            string[] stats_arr = response.statistics.Split(',');
            _stats.average_answer_time = float.Parse(stats_arr[0]);
            _stats.games_played = Int32.Parse(stats_arr[1]);
            _stats.correct_answers = Int32.Parse(stats_arr[2]);
            _stats.total_answers = Int32.Parse(stats_arr[3]);
            _stats.score = Int32.Parse(stats_arr[4]);

            counter_answer_time.Content = _stats.average_answer_time;
            counter_correct_answers.Content = _stats.correct_answers;
            counter_score.Content = _stats.score;
            counter_total_games.Content = _stats.games_played;
            counter_wrong_answers.Content = _stats.total_answers - _stats.correct_answers;
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
