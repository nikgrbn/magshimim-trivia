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
    /// Interaction logic for JoinRoomWindow.xaml
    /// </summary>
    
    public partial class JoinRoomWindow : Window
    {
        // Members
        Communicator _communicator;

        public JoinRoomWindow(Communicator com)
        {
            this._communicator = com;
            InitializeComponent();

            GetRoomsResponse response = Deserializer.DeserializeGetRoomsResponse(this._communicator.sendPacketToServer(Serializer.SerializeGetRoomsRequest()));
            ShowRoomsList(response);
        }

        public void ShowRoomsList(GetRoomsResponse response)
        {
            string[] rooms_names_arr;
            string room_name;

            if (response.status == 401)
            {
                get_rooms_error.Content = "Failed to get rooms list from the server";
                return;
            }
            
            if (response.Rooms.Contains(','))
            {
                rooms_names_arr = response.Rooms.Split(',');
                foreach (var room in rooms_names_arr)
                {
                    RoomsList.Items.Add(room);
                }
            } else if(response.Rooms != "")
            {
                room_name = response.Rooms;
                RoomsList.Items.Add(room_name);
            }
        }

        private void clicked_refresh(object sender, RoutedEventArgs e)
        {
            loading.Content = "Loading...";
            RoomsList.Items.Clear();

            GetRoomsResponse response = Deserializer.DeserializeGetRoomsResponse(this._communicator.sendPacketToServer(Serializer.SerializeGetRoomsRequest()));
            ShowRoomsList(response);
        }

        private void clicked_menu(object sender, RoutedEventArgs e)
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

        private void MouseDoubleClick_Event(object sender, MouseButtonEventArgs e)
        {
            JoinRoomRequest req;
            req.roomId = 1; // TEST
            JoinRoomResponse response = Deserializer.DeserializeJoinRoomResponse(this._communicator.sendPacketToServer(Serializer.SerializeJoinRoomRequest(req)));
            
            if (response.status == 501)
            {
                MessageBox.Show("Failed to enter the room!", "Error", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                return;
            }
        }
    }
}
