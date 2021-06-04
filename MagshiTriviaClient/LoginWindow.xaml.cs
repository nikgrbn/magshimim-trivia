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

        System.Net.Sockets.TcpClient clientSocket = new System.Net.Sockets.TcpClient();
        public LoginWindow()
        {
            InitializeComponent();
            StartClient();
        }

        private void rb_register_checked(object sender, RoutedEventArgs e)
        {
            tb_email.IsEnabled = true;
        }

        private void rb_login_checked(object sender, RoutedEventArgs e)
        {
            tb_email.IsEnabled = false;
        }

        private void clicked_enter(object sender, RoutedEventArgs e)
        {
            if (radiobutton_login.IsChecked == true)
            {
                List<byte> temp_buffer = new List<byte>();
                temp_buffer.Add(Convert.ToByte(11));

                string msg = "{\"username\": \"user1\", \"password\": \"1234\"}";
                int len = msg.Length;

                for (int i = 0; i < sizeof(int); i++) {
                    temp_buffer.Add(Convert.ToByte(len & 0xFF)); // pushing back the last byte in the
                    len = len >> 8;
                }

                temp_buffer.AddRange(Encoding.ASCII.GetBytes(msg + "$"));

                NetworkStream serverStream = clientSocket.GetStream();
                serverStream.Write(temp_buffer.ToArray(), 0, temp_buffer.Count());
                serverStream.Flush();

                byte[] inStream = new byte[10025];
                try
                {
                    serverStream.Read(inStream, 0, inStream.Length);
                }
                catch (Exception exc) {

                }
                string returndata = System.Text.Encoding.ASCII.GetString(inStream);

                l_error.Content = returndata;
            }

            else if (radiobutton_register.IsChecked == true)
            {

            }
        }

        private void StartClient()
        {
            byte[] bytes = new byte[1024];

            try
            {
                clientSocket.Connect("127.0.0.1", 8728);
                l_error.Content = "";
                bt_enter.IsEnabled = true;
            }
            catch (Exception e)
            {
                l_error.Content = "Can't establish connection with server!";
                bt_enter.IsEnabled = false;
                DelayAction(2000, StartClient);
            }
        }

        public static void DelayAction(int millisecond, Action action)
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
