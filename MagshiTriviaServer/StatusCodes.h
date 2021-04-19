#pragma once

#define SERVER_PORT 8728

enum class ProtocolCodes : unsigned int {
	Error = 1,
	Signup = 10,
	Login = 11
};