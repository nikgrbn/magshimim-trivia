using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace MagshiTriviaClient
{
    public static class Deserializer
    {
        private static string retrieveJson(string response)
        {
            int response_code = (int) response[0];
            byte[] bytes = Encoding.ASCII.GetBytes(response);
            byte[] len_byte = new byte[4];
            Array.Copy(bytes, 1, len_byte, 0, 4);
            Array.Reverse(len_byte);
            int data_length = BitConverter.ToInt32(len_byte, 0);

            return response.Substring(5, data_length);
        }

        public static LoginResponse DeserializeLoginResponse(string response)
        {
            LoginResponse res = JsonConvert.DeserializeObject<LoginResponse>(retrieveJson(response));
            return res;
        }

        public static SignupResponse DeserializeSignupResponse(string response)
        {
            SignupResponse res = JsonConvert.DeserializeObject<SignupResponse>(retrieveJson(response));
            return res;
        }

        public static StatisticsResponse DeserializeStatisticsResponse(string response)
        {
            StatisticsResponse res = JsonConvert.DeserializeObject<StatisticsResponse>(retrieveJson(response));
            return res;
        }


        public static CreateRoomResponse DeserializeCreateRoomResponse(string response)
        {
            CreateRoomResponse res = JsonConvert.DeserializeObject<CreateRoomResponse>(retrieveJson(response));
            return res;
        }
    }
}
