﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MagshiTriviaClient
{
    // ---------------------- Requests ------------------------
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

    public struct HighScoreRequest
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

    public struct JoinRoomRequest
    {
        public int roomId;
    }

    public struct GetPlayersInRoomRequest
    {
        public int roomId;
    }

    public struct GetHandlerTypeRequest
    {
        // EMPTY
    }

    public struct CloseRoomRequest
    {
        // EMPTY
    }

    public struct LeaveRoomRequest
    {
        // EMPTY
    }

    // -------------------------------- Responses ----------------------------------


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

    public struct HighScoreResponse
    {
        public int status;
        public string HighScore;
    }

    public struct CreateRoomResponse
    {
        public int status;
        public int roomId;
    }

    public struct GetRoomsResponse
    {
        public int status;
        public List<RoomData> Rooms;
    }

    public struct JoinRoomResponse
    {
        public int status;
    }

    public struct GetPlayersInRoomResponse
    {
        public int status;
        public string players;
    }

    public struct GetHandlerTypeResponse
    {
        public int status;
        public string handler_type;
    }

    public struct CloseRoomResponse
    {
        public int status;
        public string handler_type;
    }

    public struct LeaveRoomResponse
    {
        public int status;
        public string handler_type;
    }

    // -------------
    public struct RoomData
    {
        public int id;
        public string name;
        public int maxPlayers;
        public int numOfQuestionsInGame;
        public int timePerQuestion;
        public int isActive;
    }
}


enum ResponseStatus
{
    LoginSuccess = 100,
    LoginError = 101,

    SignupSuccess = 200,
    SignupError = 201,

    LogoutSuccess = 300,
    LogoutError = 301,

    GetRoomsSuccess = 400,
    GetRoomsError = 401,

    JoinRoomSuccess = 500,
    JoinRoomError = 501,

    CreateRoomSuccess = 600,
    CreateRoomError = 601,

    GetPlayersInRoomRequestSuccess = 700,
    GetPlayersInRoomRequestError = 701,

    GetPersonalStatsSuccess = 800,
    GetPersonalStatsError = 801,

    HighScoreRequestSuccess = 900,
    HighScoreRequestError = 901,

    CloseRoomRequestSuccess = 1000,
    CloseRoomRequestError = 1001,

    StartGameRequestSuccess = 1100,
    StartGameRequestError = 1101,

    GetRoomStateRequestSuccess = 1200,
    GetRoomStateRequestError = 1201,

    LeaveRoomRequestSucces = 1300,
    LeaveRoomRequestError = 1301,

    GetHandlerTypeRequestSuccess = 1400,
    GetHandlerTypeRequestError = 1401
};