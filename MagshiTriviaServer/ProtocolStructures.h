#pragma once

// Standard libarary
#include <iostream>
#include <ctime>
#include <vector>

// Project header files
#include "StatusCodes.h"
#include "Room.h"
#include "StatisticsManager.h"

class IRequestHandler;

// -------- Response ---------

typedef struct LoginResponse {
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse {
	unsigned int status;
} SignupResponse;

typedef struct ErrorResponse {
	std::string message;
} ErrorResponse;

typedef struct LogoutResponse {
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse {
	unsigned int status;
	std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct getHighScoreResponse {
	unsigned int status;
	std::vector<std::string> statistics;
} getHighScoreResponse;

typedef struct getPersonalStatsResponse {
	unsigned int status;
	std::string statistics;
} getPersonalStatsResponse;

typedef struct JoinRoomResponse {
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse {
	unsigned int status;
	unsigned int roomId;
} CreateRoomResponse;

typedef struct GetStatisticsResponse {
	unsigned int status;
	std::vector<UserStatistics> user_statistics;
	std::vector<UserStatistics> high_score;
} GetStatisticsResponse;

typedef struct CloseRoomResponse {
	unsigned int status;
} CloseRoomResponse;

typedef struct StartGameResponse {
	unsigned int status;
} StartGameResponse;

typedef struct GetRoomStateResponse {
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse {
	unsigned int status;
} LeaveRoomResponse;

typedef struct GetHandlerTypeResponse {
	unsigned int status;
	IRequestHandler* request_handler;
};

// -------- Request ---------

typedef struct LoginRequest {
	std::string username, password;
} LoginRequest;

typedef struct SignupRequest {
	std::string username, password, email;
} SignupRequest;

typedef struct RequestInfo {
	ProtocolCodes id;
	//std::ctime receivalTime;
	Buffer buffer;
} RequestInfo;

typedef struct RequestResult {
	Buffer buffer;
	IRequestHandler* newHandler;
} RequestResult;

typedef struct GetPlayersInRoomRequest {
	unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest {
	unsigned int roomId;
} JoinRoomRequest;

typedef struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
} CreateRoomRequest;
