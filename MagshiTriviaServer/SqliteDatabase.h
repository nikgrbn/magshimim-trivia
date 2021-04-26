#pragma once

#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>

class SqliteDatabase : public IDatabase
{
public:
	// Constructor Q Destrcutor
	SqliteDatabase();
	~SqliteDatabase();

	// Questionaries
	bool doesUserExists(std::string username) override;
	bool doesPasswordMatch(std::string username, std::string password) override;
	void addNewUser(std::string username, std::string password, std::string mail) override;

private:
	// Database data
	sqlite3* db;
	std::string dbFileName = "Trivia_DB.sqlite";
	char** errMessage = nullptr;
};