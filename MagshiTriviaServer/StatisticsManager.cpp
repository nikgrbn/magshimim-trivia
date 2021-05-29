#include "StatisticsManager.h"

bool comparator(const std::map<std::string, std::string>& lhs, const std::map<std::string, std::string>& rhs)
{
	return std::stoi(lhs.at("score")) < std::stoi(rhs.at("score"));
}

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

std::vector<std::map<std::string, std::string>> StatisticsManager::getHighScore()
{
	std::vector<std::map<std::string, std::string>> leaderboard;
	std::vector<std::map<std::string, std::string>> users = StatisticsManager::getStatistics();

	for (auto user : users)
	{
		// Create vector of users and their scores
		std::map<std::string, std::string> user_map;
		user_map.insert(std::pair<std::string, std::string>("username", user["username"]));
		user_map.insert(std::pair<std::string, std::string>("score", std::to_string(calculateScore(user))));
		leaderboard.push_back(user_map);
	}

	// Sort players by their scores using custom comparator
	std::sort(leaderboard.begin(), leaderboard.end(), comparator);
    return leaderboard.size() <= 5 ? leaderboard : std::vector<std::map<std::string, std::string>>(leaderboard.begin(), leaderboard.begin() + 5);
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

int StatisticsManager::calculateScore(std::map<std::string, std::string> user)
{
	float score = 0;

	// Get user stats
	float average_answer_time = std::stof(user["average_answer_time"]);
	int games_played = std::stoi(user["games_played"]);
	int correct_answers = std::stoi(user["correct_answers"]);
	int total_answers = std::stoi(user["total_answers"]);

	// Check if stats aren't zeroes
	if (average_answer_time != 0 && games_played != 0 && correct_answers != 0 && total_answers != 0)
	{
		// Calculate score by formula
		score = (float)100 * (((correct_answers / total_answers) * games_played) / average_answer_time);
	}

	return (int)score;
}
