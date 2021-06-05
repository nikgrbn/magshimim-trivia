using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Threading;
using System.Net;
using System.Net.Sockets;

namespace MagshiTriviaClient
{
    public class Communicator
    {
        private System.Net.Sockets.TcpClient socket;

        public Communicator()
        {
            socket = new System.Net.Sockets.TcpClient();
        }

        ~Communicator()
        {
            socket.Close();
        }
        public void ConnectToServer()
        {
            socket.Connect("127.0.0.1", 8728);
        }

        public string sendPacketToServer(byte[] packet)
        {
            NetworkStream serverStream = socket.GetStream();
            serverStream.Write(packet, 0, packet.Length);
            serverStream.Flush();

            byte[] inStream = new byte[10025];
            serverStream.Read(inStream, 0, inStream.Length);
            return System.Text.Encoding.ASCII.GetString(inStream);
        }
    }
}
