#pragma once

// Standard libarary
#include <iostream>

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
