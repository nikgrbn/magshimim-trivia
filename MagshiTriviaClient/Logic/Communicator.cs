using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Threading;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Reflection;

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
            // Find config file in a directory
            string config = System.IO.Path.Combine(System.AppDomain.CurrentDomain.BaseDirectory, "config.txt");
            if (!File.Exists(config))
            {
                config = Path.GetFullPath(Path.Combine(Directory.GetCurrentDirectory(), @"..\..\config.txt"));
                if (!File.Exists(config))
                {
                    throw new DirectoryNotFoundException("Can't locate a config file!");
                }
            }

            // Read a text file line by line.  
            string[] lines = File.ReadAllLines(config);
            string ip = (lines[0].Split('='))[1];
            int port = Convert.ToInt32((lines[1].Split('='))[1]);

            // Connect to a server
            socket.Connect(ip, port);
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
