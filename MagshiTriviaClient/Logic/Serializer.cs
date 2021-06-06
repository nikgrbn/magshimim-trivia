using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace MagshiTriviaClient
{
    public static class Serializer
    {
        private static byte[] GenerateRequest(int code, object obj)
        {
            string json = JsonConvert.SerializeObject(obj);
            List<byte> temp_buffer = new List<byte>();
            temp_buffer.Add(Convert.ToByte(code));
            int len = json.Length;

            for (int i = 0; i < sizeof(int); i++)
            {
                temp_buffer.Add(Convert.ToByte(len & 0xFF)); // pushing back the last byte in the
                len = len >> 8;
            }

            temp_buffer.AddRange(Encoding.ASCII.GetBytes(json));

            return temp_buffer.ToArray();
        }
        public static byte[] SerializeLoginRequest(string username, string password)
        {
            LoginRequest req;
            req.username = username;
            req.password = password;

            return GenerateRequest(11, req);
        }

        public static byte[] SerializeSignupRequest(string username, string password, string mail)
        {
            SignupRequest req;
            req.username = username;
            req.password = password;
            req.mail = mail;

            return GenerateRequest(10, req);
        }

        public static byte[] SerializeLogoutRequest()
        {
            LogoutRequest req;

            return GenerateRequest(17, req);
        }

        public static byte[] SerializeStatisticsRequest()
        {
            StatisticsRequest req;

            return GenerateRequest(19, req);
        }

        public static byte[] SerializeCreateRoomRequest(CreateRoomRequest req)
        {
            return GenerateRequest(12, req);
        }
    }
}
