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
	Login = 11
};

enum ResponseStatus {
	LoginSuccess = 100,
	LoginError = 101
};