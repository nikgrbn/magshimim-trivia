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
    class Communicator
    {
        private System.Net.Sockets.TcpClient socket;

        public Communicator()
        {
            socket = new System.Net.Sockets.TcpClient();
        }

        public void ConnectToServer()
        {
            socket.Connect("127.0.0.1", 8728);
        }

        public string sendMsgToServer(int code, string msg)
        {
            List<byte> temp_buffer = new List<byte>();
            temp_buffer.Add(Convert.ToByte(code));
            int len = msg.Length;

            for (int i = 0; i < sizeof(int); i++) {
                temp_buffer.Add(Convert.ToByte(len & 0xFF)); // pushing back the last byte in the
                len = len >> 8;
            }

            temp_buffer.AddRange(Encoding.ASCII.GetBytes(msg + "$"));

            NetworkStream serverStream = socket.GetStream();
            serverStream.Write(temp_buffer.ToArray(), 0, temp_buffer.Count());
            serverStream.Flush();

            byte[] inStream = new byte[10025];
            serverStream.Read(inStream, 0, inStream.Length);
            return System.Text.Encoding.ASCII.GetString(inStream);
        }
    }
}
