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
        private static string retrieveJson(byte[] response)
        {
            string str_resp = System.Text.Encoding.ASCII.GetString(response);
            int response_code = (int) str_resp[0];
            byte[] len_byte = new byte[4];
            
            Array.Copy(response, 1, len_byte, 0, 4);
            Array.Reverse(len_byte);
            int data_length = BitConverter.ToInt32(len_byte, 0);

            return str_resp.Substring(5, data_length);
        }

        public static LoginResponse DeserializeLoginResponse(byte[] response)
        {
            LoginResponse res = JsonConvert.DeserializeObject<LoginResponse>(retrieveJson(response));
            return res;
        }

        public static SignupResponse DeserializeSignupResponse(byte[] response)
        {
            SignupResponse res = JsonConvert.DeserializeObject<SignupResponse>(retrieveJson(response));
            return res;
        }

        public static StatisticsResponse DeserializeStatisticsResponse(byte[] response)
        {
            StatisticsResponse res = JsonConvert.DeserializeObject<StatisticsResponse>(retrieveJson(response));
            return res;
        }

        public static HighScoreResponse DeserializeHighScoreResponse(byte[] response)
        {
            HighScoreResponse res = JsonConvert.DeserializeObject<HighScoreResponse>(retrieveJson(response));
            return res;
        }

        public static CreateRoomResponse DeserializeCreateRoomResponse(byte[] response)
        {
            CreateRoomResponse res = JsonConvert.DeserializeObject<CreateRoomResponse>(retrieveJson(response));
            return res;
        }

        public static GetRoomsResponse DeserializeGetRoomsResponse(byte[] response)
        {
            // TODO: fix the deserialization
            GetRoomsResponse res = JsonConvert.DeserializeObject<GetRoomsResponse>(retrieveJson(response));
            return res;
        }

        public static JoinRoomResponse DeserializeJoinRoomResponse(byte[] response)
        {
            JoinRoomResponse res = JsonConvert.DeserializeObject<JoinRoomResponse>(retrieveJson(response));
            return res;
        }

        public static GetPlayersInRoomResponse DeserializeGetPlayersInRoomResponse(byte[] response)
        {
            GetPlayersInRoomResponse res = JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(retrieveJson(response));
            return res;
        }
    }
}
