#pragma once

// Standard libraries
#include <iostream>
#include <vector>
#include <algorithm>

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

	bool isLogged(const std::string& username) const;
	std::vector<LoggedUser> GetLoggedUsers();

private:
	IDatabase* _database;
	std::vector<LoggedUser> _loggedUsers;
};