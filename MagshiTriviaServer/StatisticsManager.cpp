#include "StatisticsManager.h"


std::vector<std::map<std::string, std::string>> StatisticsManager::getStatistics()
{
	std::vector<std::map<std::string, std::string>> statistics;

	// Iterate through usernames vector
	std::vector<std::string> usernames = m_database->getUsers();
	for (auto username : usernames)
	{
		// Push each user statistics to a statisctics vector
		statistics.push_back(StatisticsManager::getUserStatistics(username));
	}

    return statistics;
}

std::vector<std::string> StatisticsManager::getHighScore()
{
    return std::vector<std::string>();
}

std::map<std::string, std::string> StatisticsManager::getUserStatistics(std::string username)
{
	std::map<std::string, std::string> user_statistics;

	// Check if username exists
	if (this->m_database->doesUserExists(username))
	{
		// Create user statistics map
		user_statistics.insert(std::pair<std::string, std::string>("username", username));

		user_statistics.insert(std::pair<std::string, std::string>("average_answer_time",
			std::to_string(m_database->getPlayerAverageAnswerTime(username))));

		user_statistics.insert(std::pair<std::string, std::string>("games_played",
			std::to_string(m_database->getNumOfPlayerGames(username))));

		user_statistics.insert(std::pair<std::string, std::string>("correct_answers",
			std::to_string(m_database->getNumOfCorrectAnswers(username))));

		user_statistics.insert(std::pair<std::string, std::string>("total_answers",
			std::to_string(m_database->getNumOfTotalAnswers(username))));
	}
	else
	{
		throw std::exception("User with such username does not exist!");
	}

	return user_statistics;
}
