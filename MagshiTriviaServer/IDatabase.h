#pragma once

#include <iostream>

class IDatabase {
public:
	virtual bool doesUserExists(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string email) = 0;
};