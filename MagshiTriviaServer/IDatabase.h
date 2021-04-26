#pragma once

#include <iostream>

class IDatabase {
public:
	virtual bool doesUserExists(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string original_password, std::string input_password) = 0;
	virtual void addNewUser(std::string password, std::string username, std::string email) = 0;
};