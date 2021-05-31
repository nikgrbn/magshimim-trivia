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

	// User table questionaries
	bool doesUserExists(std::string username) override;
	bool doesPasswordMatch(std::string username, std::string password) override;
	void addNewUser(std::string username, std::string password, std::string mail) override;
	std::vector<std::string> getUsers() override;

	// Questions table questionaries
	std::list<Question> getQuestions(int num) override;

	// Statistics table questionaries
	float getPlayerAverageAnswerTime(std::string username) override;
	int getNumOfCorrectAnswers(std::string username) override;
	int getNumOfTotalAnswers(std::string username) override;
	int getNumOfPlayerGames(std::string username) override;

private:
	// Database data
	sqlite3* db;
	std::string dbFileName = "Trivia_DB.sqlite";
	char** errMessage = nullptr;
};