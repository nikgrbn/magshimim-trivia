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
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {
        // Members
        Communicator _communicator;
        public CreateRoomWindow(Communicator com)
        {
            this._communicator = com;
            InitializeComponent();
        }

        public CreateRoomWindow()
        {
            InitializeComponent();
        }

        private void logout(object sender, EventArgs e)
        {
            this._communicator.sendPacketToServer(Serializer.SerializeLogoutRequest());
            this.Close();
        }

        private void clicked_create(object sender, RoutedEventArgs e)
        {
            CreateRoomRequest create_room;
            create_room.roomName = this.tb_room_name.Text;
            create_room.maxUsers = Int32.Parse(this.tb_number_of_players.Text);
            create_room.questionCount = Int32.Parse(this.tb_number_of_questions.Text);
            create_room.answerTimeout = Int32.Parse(this.tb_question_time.Text);
            string res = this._communicator.sendPacketToServer(Serializer.SerializeCreateRoomRequest(create_room));

            if (Deserializer.DeserializeCreateRoomResponse(res).status == 601)
            {
                creation_error.Content = "Login error!";
            }
            else
            {
                creation_error.Content = "";
                switchToMainWindow();
            }
        }

        private void switchToMainWindow()
        {
            MainWindow mainWindow = new MainWindow(this._communicator);
            Visibility = Visibility.Hidden;
            mainWindow.Show();
        }
    }
}
