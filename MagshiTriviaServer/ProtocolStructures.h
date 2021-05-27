#pragma once

// Standard libarary
#include <iostream>
#include <ctime>
#include <vector>

// Project header files
#include "StatusCodes.h"

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