#pragma once

#include <iostream>

class LoggedUser {
public:
	// Constructor q Destructor
	LoggedUser(std::string username);
	~LoggedUser() = default;

	// Getter
	std::string getUsername();

private:
	std::string _username;
};