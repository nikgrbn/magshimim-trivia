#pragma once

#include "IDatabase.h"

class SqliteDatabase : public IDatabase
{
public:
	bool doesUserExists(std::string username) override;
	bool doesPasswordMatch(std::string original_password, std::string input_password) override;
	void addNewUser(std::string password, std::string username, std::string email) override;
};