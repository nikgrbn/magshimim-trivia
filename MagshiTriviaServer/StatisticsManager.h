#pragma once

// Standard library
#include <iostream>
#include <vector>

// Project headers
#include "SqliteDatabase.h"

class StatisticsManager {
public:
	StatisticsManager();
	StatisticsManager(IDatabase* db) : m_database(db) {};
	~StatisticsManager() = default;

	std::vector<std::string> getStatistics();

private:
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics();

	IDatabase* m_database;
};