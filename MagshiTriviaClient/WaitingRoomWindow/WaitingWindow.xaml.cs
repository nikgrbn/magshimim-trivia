using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
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
        bool isAdmin = false;
        private static BackgroundWorker backgroundWorker;
        public WaitingWindow(Communicator com, RoomData room)
        {
            this._communicator = com;
            this.roomData = room;
            InitializeComponent();
            initializeRoomData();
            getUserType();

            backgroundWorker = new BackgroundWorker { WorkerSupportsCancellation = true };
            backgroundWorker.DoWork += new DoWorkEventHandler(getRoomUsers); ;
            backgroundWorker.RunWorkerAsync();
        }

        private void getUserType()
        {
            GetHandlerTypeResponse res = Deserializer.DeserializeGetHandlerTypeResponse(this._communicator.sendPacketToServer(Serializer.SerializeGetHandlerTypeRequest()));
            if (res.handler_type == "admin")
                isAdmin = true;
            else
                bt_start_game.IsEnabled = false;
        }

        private void getRoomUsers(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if (backgroundWorker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                GetPlayersInRoomRequest req = new GetPlayersInRoomRequest();
                req.roomId = this.roomData.id;
                GetPlayersInRoomResponse res = Deserializer.DeserializeGetPlayersInRoomResponse(this._communicator.sendPacketToServer(Serializer.SerializeGetPlayersInRoomRequest(req)));

                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    if (res.players == null || res.players == "")
                    {
                        LeaveRoomResponse res_leave = Deserializer.DeserializeLeaveRoomResponse(this._communicator.sendPacketToServer(Serializer.SerializeLeaveRoomRequest()));
                        backgroundWorker.CancelAsync();
                        JoinRoomWindow joinWindow = new JoinRoomWindow(this._communicator);
                        Visibility = Visibility.Hidden;
                        joinWindow.Show();
                    }
                    else 
                    {
                        players_list.Items.Clear();
                        string[] users = res.players.Split(',');
                        foreach (var user in users)
                        {
                            // Create stack panel
                            StackPanel user_panel = new StackPanel();
                            user_panel.Orientation = Orientation.Horizontal;
                            user_panel.Margin = new Thickness(2);

                            // Add image to stack panel
                            Image img = new Image();
                            img.Source = new BitmapImage(new Uri("pack://application:,,,/MagshiTriviaClient;component/Resources/user_icon_2.png"));
                            img.Width = 50;
                            img.Height = 50;
                            img.Margin = new Thickness(10, 0, 0, 0);
                            user_panel.Children.Add(img);

                            // Add username to stack panel
                            TextBlock username = new TextBlock();
                            username.Text = user;
                            username.VerticalAlignment = VerticalAlignment.Center;
                            username.HorizontalAlignment = HorizontalAlignment.Center;
                            username.Margin = new Thickness(10, 0, 0, 5);
                            username.FontSize = 22;
                            username.Foreground = System.Windows.Media.Brushes.White;
                            user_panel.Children.Add(username);

                            // Add stack panel to players list
                            players_list.Items.Add(user_panel);
                        }
                    }
                }));

                Thread.Sleep(3000);
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
            backgroundWorker.CancelAsync();
            this._communicator.sendPacketToServer(Serializer.SerializeLogoutRequest());
            this.Close();
        }

        private void clicked_leave(object sender, RoutedEventArgs e)
        {
            // Close or Leave room
            if (isAdmin)
            {
                CloseRoomResponse res = Deserializer.DeserializeCloseRoomResponse(this._communicator.sendPacketToServer(Serializer.SerializeCloseRoomRequest()));
            }
            else
            {
                LeaveRoomResponse res = Deserializer.DeserializeLeaveRoomResponse(this._communicator.sendPacketToServer(Serializer.SerializeLeaveRoomRequest()));
            }

            backgroundWorker.CancelAsync();
            JoinRoomWindow joinWindow = new JoinRoomWindow(this._communicator);
            Visibility = Visibility.Hidden;
            joinWindow.Show();
        }

        private void clicked_start_game(object sender, RoutedEventArgs e)
        {
            if (!isAdmin)
            {
                label_error.Content = "Only admin can start the game!";
                return;
            }
        }
    }
}
