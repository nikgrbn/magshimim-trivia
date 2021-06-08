#pragma once

// Standard library
#include <iostream>
#include <vector>

// Project headers
#include "SqliteDatabase.h"

typedef struct UserStatistics {
	std::string username;
	std::string average_answer_time;
	std::string games_played;
	std::string correct_answers;
	std::string total_answers;
	std::string score;
}; UserStatistics;

class StatisticsManager {
public:
	StatisticsManager() {};
	StatisticsManager(IDatabase* db) : m_database(db) {};
	~StatisticsManager() = default;

	std::vector<UserStatistics> getStatistics();
	std::vector<UserStatistics> getHighScore();
	UserStatistics getUserStatistics(std::string username);

private:
	int calculateScore(UserStatistics user);

	IDatabase* m_database;
};