#pragma once

// Standard library
#include <iostream>
#include <vector>

// Project headers
#include "SqliteDatabase.h"

class StatisticsManager {
public:
	StatisticsManager() {};
	StatisticsManager(IDatabase* db) : m_database(db) {};
	~StatisticsManager() = default;

	std::vector<std::map<std::string, std::string>> getStatistics();
	std::vector<std::map<std::string, std::string>> getHighScore();

private:
	std::map<std::string, std::string> getUserStatistics(std::string username);
	int calculateScore(std::map<std::string, std::string> user);

	IDatabase* m_database;
};