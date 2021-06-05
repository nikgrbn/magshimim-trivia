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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MagshiTriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
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
        }

        // Members
        Communicator _communicator_obj;
    }
}
