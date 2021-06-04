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
using System.Net;
using System.Net.Sockets;
using System.Windows.Threading;

namespace MagshiTriviaClient
{
    /// <summary>
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        Communicator com = new Communicator();
        public LoginWindow()
        {
            InitializeComponent();
            connectToServer();
        }

        private void rb_register_checked(object sender, RoutedEventArgs e)
        {
            tb_email.IsEnabled = true;
        }

        private void rb_login_checked(object sender, RoutedEventArgs e)
        {
            tb_email.IsEnabled = false;
        }

        private void clicked_enter(object sender, RoutedEventArgs events)
        {
            if (radiobutton_login.IsChecked == true)
            {
                try
                {
                    string msg = "{" + String.Format("\"username\":\"{0}\", \"password\":\"{1}\"", tb_username.Text, tb_password.Text) + "}";
                    l_error.Content = com.sendMsgToServer(11, msg);
                }
                catch (Exception e)
                {
                    l_error.Content = e.Message;
                }
            }

            else if (radiobutton_register.IsChecked == true)
            {

            }
        }

        private void connectToServer()
        {
            try
            {
                com.ConnectToServer();
                l_error.Content = "";
                bt_enter.IsEnabled = true;
            }
            catch (Exception e)
            {
                l_error.Content = "Can't establish connection to a server!";
                bt_enter.IsEnabled = false;
                DelayAction(2000, connectToServer);
            }
        }
        private static void DelayAction(int millisecond, Action action)
        {
            var timer = new DispatcherTimer();
            timer.Tick += delegate

            {
                action.Invoke();
                timer.Stop();
            };

            timer.Interval = TimeSpan.FromMilliseconds(millisecond);
            timer.Start();
        }
    }
}
