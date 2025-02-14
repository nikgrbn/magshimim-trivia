﻿using System;
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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MagshiTriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        // Members
        Communicator _communicator_obj;

        public MainWindow(Communicator com)
        {
            _communicator_obj = com;
            InitializeComponent();
        }

        public MainWindow()
        {
            InitializeComponent();
        }

        private void logout(object sender, EventArgs e)
        {
            this._communicator_obj.sendPacketToServer(Serializer.SerializeLogoutRequest());
            this.Close();
        }

        private void clicked_join_room(object sender, RoutedEventArgs e)
        {
            JoinRoomWindow join_room_window = new JoinRoomWindow(this._communicator_obj);
            Visibility = Visibility.Hidden;
            join_room_window.Show();
        }

        private void clicked_create_room(object sender, RoutedEventArgs e)
        {
            CreateRoomWindow create_room_window = new CreateRoomWindow(this._communicator_obj);
            Visibility = Visibility.Hidden;
            create_room_window.Show();
        }

        private void clicked_high_score(object sender, RoutedEventArgs e)
        {
            HighScoreWindow high_score_window = new HighScoreWindow(this._communicator_obj);
            Visibility = Visibility.Hidden;
            high_score_window.Show();
        }

        private void clicked_statistics(object sender, RoutedEventArgs e)
        {
            StatisticsWindow statistics_window = new StatisticsWindow(this._communicator_obj);
            Visibility = Visibility.Hidden;
            statistics_window.Show();
        }

        private void clicked_logout(object sender, RoutedEventArgs e)
        {
            this._communicator_obj.sendPacketToServer(Serializer.SerializeLogoutRequest());
            LoginWindow login_window = new LoginWindow();
            Visibility = Visibility.Hidden;
            login_window.Show();
        }

        private void clicked_exit(object sender, RoutedEventArgs e)
        {
            this._communicator_obj.sendPacketToServer(Serializer.SerializeLogoutRequest());
            this.Close();
        }
    }
}
