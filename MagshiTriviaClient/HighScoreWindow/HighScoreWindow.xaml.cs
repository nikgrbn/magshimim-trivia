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
            SetHighScore();
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

        private void SetHighScore()
        {
            string[] rooms_names_arr;
            int tmp = 0;

            // Hide gui 
            group_user_1.Visibility = Visibility.Hidden;
            group_user_2.Visibility = Visibility.Hidden;
            group_user_3.Visibility = Visibility.Hidden;
            group_user_4.Visibility = Visibility.Hidden;

            // Get high scores
            HighScoreResponse response = Deserializer.DeserializeHighScoreResponse(_communicator.sendPacketToServer(Serializer.SerializeHighScoreRequest()));
            rooms_names_arr = response.HighScore.Split(',');

            // Display scores
            for (int i = 0; i < rooms_names_arr.Length; i+=6)
            {
                switch (tmp)
                {
                    case 0:
                        group_user_1.Visibility = Visibility.Visible;
                        label_name_user1.Content = rooms_names_arr[i];
                        label_score_user1.Content = rooms_names_arr[i + 5];
                        break;
                    case 1:
                        group_user_2.Visibility = Visibility.Visible;
                        label_name_user2.Content = rooms_names_arr[i];
                        label_score_user2.Content = rooms_names_arr[i + 5];
                        break;
                    case 2:
                        group_user_3.Visibility = Visibility.Visible;
                        label_name_user3.Content = rooms_names_arr[i];
                        label_score_user3.Content = rooms_names_arr[i + 5];
                        break;
                    case 3:
                        group_user_4.Visibility = Visibility.Visible;
                        label_name_user4.Content = rooms_names_arr[i];
                        label_score_user4.Content = rooms_names_arr[i + 5];
                        break;
                    default:
                        break;
                }
                tmp++;
            }
        }
    }
}
