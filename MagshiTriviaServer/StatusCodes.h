#pragma once

// Definitions
using Buffer = std::vector<unsigned char>;

#define SERVER_PORT 8728

// Protocol headers
#define CODE_SIZE 1
#define DATA_SIZE 4
// ->
#define HEADER_SIZE 5

enum class ProtocolCodes : unsigned int {
	Error = 1,
	Signup = 10,
	Login = 11,
	CreateRoomRequest = 12,
	GetRoomsRequest = 13,
	GetPlayersInRoomRequest = 14,
	JoinRoomRequest = 15,
	GetStatisticsRequest = 16,
	LogoutRequest = 17,
	HighScoreRequest = 18,
	GetPersonalStats = 19
};

enum ResponseStatus {
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
	HighScoreRequestError = 901
};