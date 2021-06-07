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
            string room_name;

            if (response.status == 401)
            {
                get_rooms_error.Content = "Failed to get rooms list from the server";
                return;
            }
            
            if (response.Rooms != null && response.Rooms.Any())
            {
                foreach (var room in response.Rooms)
                {
                    RoomsList.Items.Add(room.name);
                }
            } else if (response.Rooms != null && response.Rooms.Count == 1)
            {
                room_name = response.Rooms.ElementAt(1).name;
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

        private void switchToMainWindow()
        {
            MainWindow mainWindow = new MainWindow(this._communicator);
            Visibility = Visibility.Hidden;
            mainWindow.Show();
        }

        private void MouseDoubleClick_Event(object sender, MouseButtonEventArgs e)
        {
            JoinRoomRequest req;
            req.roomId = 0;
            GetRoomsResponse rooms_data_response = Deserializer.DeserializeGetRoomsResponse(this._communicator.sendPacketToServer(Serializer.SerializeGetRoomsRequest()));

            foreach(var room in rooms_data_response.Rooms)
            {
                if(room.name == (string)(RoomsList.SelectedItem))
                {
                    req.roomId = room.id;
                    break;
                }
            }

            JoinRoomResponse response = Deserializer.DeserializeJoinRoomResponse(this._communicator.sendPacketToServer(Serializer.SerializeJoinRoomRequest(req)));
            
            if (response.status == 501)
            {
                join_error.Content = "Failed to enter the room!";
                return;
            }

            switchToMainWindow(); // TODO: join to the room
        }
    }
}
