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
            // Check if fields are not empty
            if (!string.IsNullOrWhiteSpace(tb_room_name.Text) &&
                !string.IsNullOrWhiteSpace(tb_number_of_players.Text) &&
                !string.IsNullOrWhiteSpace(tb_number_of_questions.Text) &&
                !string.IsNullOrWhiteSpace(tb_question_time.Text))
            {
                CreateRoomRequest create_room;
                create_room.roomName = this.tb_room_name.Text;
                create_room.maxUsers = Int32.Parse(this.tb_number_of_players.Text);
                create_room.questionCount = Int32.Parse(this.tb_number_of_questions.Text);
                create_room.answerTimeout = Int32.Parse(this.tb_question_time.Text);
                byte[] res = this._communicator.sendPacketToServer(Serializer.SerializeCreateRoomRequest(create_room));
                
                if (Deserializer.DeserializeCreateRoomResponse(res).status == 601)
                {
                    creation_error.Content = "Create room failed!";
                }
                else
                {
                    creation_error.Content = "";
                    switchToRoom(); // TODO: switch window to the new room
                }
            }
            else
            {
                creation_error.Content = "All the fields must be filled!";
            }
        }

        private void switchToMainWindow()
        {
            MainWindow mainWindow = new MainWindow(this._communicator);
            Visibility = Visibility.Hidden;
            mainWindow.Show();
        }

        private void switchToRoom()
        {
            RoomData selected_room = new RoomData();

            GetRoomsResponse rooms_data_response = Deserializer.DeserializeGetRoomsResponse(this._communicator.sendPacketToServer(Serializer.SerializeGetRoomsRequest()));

            foreach (var room in rooms_data_response.Rooms)
            {
                if (room.name == tb_room_name.Text)
                {
                    selected_room = room;
                    break;
                }
            }

            WaitingWindow waiting_window = new WaitingWindow(this._communicator, selected_room);
            Visibility = Visibility.Hidden;
            waiting_window.Show();
        }


        private void clicked_menu(object sender, RoutedEventArgs e)
        {
            switchToMainWindow();
        }
    }
}
