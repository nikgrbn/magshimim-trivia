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
    public struct StatisticsRequest
    {
        // EMPTY
    }
    public struct LogoutRequest
    {
        // EMPTY
    }
    public struct CreateRoomRequest
    {
        public string roomName;
        public int maxUsers;
        public int questionCount;
        public int answerTimeout;
    }

    public struct GetRoomsRequest
    {
        // EMPTY
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

    public struct StatisticsResponse
    {
        public int status;
        public string statistics;
    }

    public struct CreateRoomResponse
    {
        public int status;
    }

    public struct GetRoomsResponse
    {
        public int status;
        public List<string> rooms_names;
    }
}
