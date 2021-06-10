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
    /// Interaction logic for WaitingWindow.xaml
    /// </summary>
    public partial class WaitingWindow : Window
    {
        Communicator _communicator;
        RoomData roomData;
        public WaitingWindow(Communicator com, RoomData room)
        {
            this._communicator = com;
            this.roomData = room;
            InitializeComponent();
            initializeRoomData();
            getRoomUsers();
        }

        private void getRoomUsers()
        {
            GetPlayersInRoomRequest req = new GetPlayersInRoomRequest();
            req.roomId = this.roomData.id;
            GetPlayersInRoomResponse res = Deserializer.DeserializeGetPlayersInRoomResponse(this._communicator.sendPacketToServer(Serializer.SerializeGetPlayersInRoomRequest(req)));
            
            string[] users = res.players.Split(',');
            foreach (var user in users)
            {

            }
        }

        private void initializeRoomData()
        {
            label_room_name.Content = roomData.name;
            label_max_players.Content = roomData.maxPlayers;
            label_questions_amount.Content = roomData.numOfQuestionsInGame;
        }

        public WaitingWindow()
        {
            InitializeComponent();
        }

        private void logout(object sender, EventArgs e)
        {
            this._communicator.sendPacketToServer(Serializer.SerializeLogoutRequest());
            this.Close();
        }

        private void clicked_leave(object sender, RoutedEventArgs e)
        {
            JoinRoomWindow joinWindow = new JoinRoomWindow(this._communicator);
            Visibility = Visibility.Hidden;
            joinWindow.Show();
        }

        private void clicked_start_game(object sender, RoutedEventArgs e)
        {

        }
    }
}
