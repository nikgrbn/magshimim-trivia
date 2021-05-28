#pragma once

#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>

class SqliteDatabase : public IDatabase
{
public:
	// Constructor Q Destructor
	SqliteDatabase();
	~SqliteDatabase();

	// Questionaries
	bool doesUserExists(std::string username) override;
	bool doesPasswordMatch(std::string username, std::string password) override;
	void addNewUser(std::string username, std::string password, std::string mail) override;

	std::list<Question> getQuestions(int num) override;
	std::map<std::string, int> getScores() override;

private:
	// Database data
	sqlite3* db;
	std::string dbFileName = "Trivia_DB.sqlite";
	char** errMessage = nullptr;
};