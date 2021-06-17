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
using System.IO;
using System.ComponentModel;
using System.Threading;

namespace MagshiTriviaClient
{
    /// <summary>
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        Communicator com = new Communicator();
        private static BackgroundWorker backgroundWorker;
        public LoginWindow()
        {
            InitializeComponent();

            backgroundWorker = new BackgroundWorker { WorkerSupportsCancellation = true };
            backgroundWorker.DoWork += new DoWorkEventHandler(connectToServer); ;
            backgroundWorker.RunWorkerAsync();
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
            try
            {
                if (radiobutton_login.IsChecked == true && !string.IsNullOrWhiteSpace(tb_username.Text) && !string.IsNullOrWhiteSpace(tb_password.Text))
                {
                    byte[] resp = com.sendPacketToServer(Serializer.SerializeLoginRequest(tb_username.Text, tb_password.Text));
                    if (Deserializer.DeserializeLoginResponse(resp).status == 101)
                    {
                        l_error.Content = "Login error!";
                    }
                    else
                    {
                        l_error.Content = "";
                        switchToMainWindow();
                    }
                }

                else if (radiobutton_register.IsChecked == true && !string.IsNullOrWhiteSpace(tb_username.Text) && !string.IsNullOrWhiteSpace(tb_password.Text) && !string.IsNullOrWhiteSpace(tb_email.Text))
                {
                    byte[] resp = com.sendPacketToServer(Serializer.SerializeSignupRequest(tb_username.Text, tb_password.Text, tb_email.Text));
                    if (Deserializer.DeserializeLoginResponse(resp).status == 201)
                    {
                        l_error.Content = "Registration error!";
                    }
                    else
                    {
                        l_error.Content = "";
                        switchToMainWindow();
                    }
                }
                else
                {
                    l_error.Content = "All the fields must be filled!";
                }
            }
            catch (Exception e)
            {
                l_error.Content = e.Message;
            }
        }

        private void switchToMainWindow()
        {
            backgroundWorker.CancelAsync();
            MainWindow mainWindow = new MainWindow(com);
            Visibility = Visibility.Hidden;
            mainWindow.Show();
        }

        void connectToServer(object sender, DoWorkEventArgs e)
        {
            bool isConnected = false;

            while (!isConnected)
            {
                if (backgroundWorker.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    try
                    {
                        com.ConnectToServer();
                        l_error.Content = "";
                        bt_enter.IsEnabled = true;
                        isConnected = true;
                        backgroundWorker.CancelAsync();
                    }
                    catch (DirectoryNotFoundException exc)
                    {
                        l_error.Content = exc.Message;
                        bt_enter.IsEnabled = false;
                    }
                    catch (Exception exc)
                    {
                        l_error.Content = "Can't establish connection with a server!";
                        bt_enter.IsEnabled = false;
                    }
                }));

                Thread.Sleep(3000);
            }
        }

        private void logout(object sender, EventArgs e)
        {
            try
            {
                backgroundWorker.CancelAsync();
                com.sendPacketToServer(Serializer.SerializeLogoutRequest());
                this.Close();
            }
            catch (Exception ex)
            {
                // PASS
            }
        }
    }
}
