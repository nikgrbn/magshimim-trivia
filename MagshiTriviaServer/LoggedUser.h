#pragma once

#include <iostream>

class LoggedUser {
public:
	// Constructor q Destructor
	LoggedUser(std::string username);
	~LoggedUser() = default;

	// Getter
	std::string getUsername() const;

private:
	std::string _username;
};

// Overload comparision operator
bool operator== (const LoggedUser& u1, const LoggedUser& u2);