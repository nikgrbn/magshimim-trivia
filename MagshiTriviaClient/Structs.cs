using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MagshiTriviaClient
{
    // Request structs
    public struct LoginRequest
    {
        public string username;
        public string password;
    }
    public struct SignupRequest
    {
        public string username;
        public string password;
        public string mail;
    }

    // Response structs 
    public struct LoginResponse
    {
        public int status;
    }
    public struct SignupResponse
    {
        public int status;
    }
}
