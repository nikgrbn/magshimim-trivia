#pragma once

// Standard libraries
#include <iostream>
#include <vector>

// Project libraries
#include "LoggedUser.h"
#include "IDatabase.h"

class LoginManager {
public:
	// Constructor q Destructor
	LoginManager(IDatabase* database);
	~LoginManager() = default;

	// User managment methods
	void signup(const std::string &username, const std::string &password, const std::string &mail);
	void login(const std::string &username, const std::string &password);
	void logout(const std::string &username);

private:
	IDatabase* _database;
	std::vector<LoggedUser> _loggedUsers;
};