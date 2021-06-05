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
            int data_length = (response[1]) | (response[2] << 8) | (response[3] << 16) | response[4] << 24;
            return response.Substring(5);
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
    }
}
