#include "StatisticsManager.h"

bool comparator(const UserStatistics& lhs, const UserStatistics& rhs)
{
	return std::stoi(lhs.score) > std::stoi(rhs.score);
}

/*
Returns all users statistics
*/
std::vector<UserStatistics> StatisticsManager::getStatistics()
{
	std::vector<UserStatistics> statistics;

	// Iterate through usernames vector
	std::vector<std::string> usernames = m_database->getUsers();
	for (auto username : usernames)
	{
		// Push each user statistics to a statisctics vector
		statistics.push_back(StatisticsManager::getUserStatistics(username));
	}

    return statistics;
}

/*
Returns vector of 5 best scores
*/
std::vector<UserStatistics> StatisticsManager::getHighScore()
{
	// Get vector of all users statistics
	std::vector<UserStatistics> leaderboard = StatisticsManager::getStatistics();

	// Sort players by their scores using custom comparator
	std::sort(leaderboard.begin(), leaderboard.end(), comparator);

    return leaderboard.size() <= 5 ? leaderboard : std::vector<UserStatistics>(leaderboard.begin(), leaderboard.begin() + 5);
}

UserStatistics StatisticsManager::getUserStatistics(std::string username)
{
	UserStatistics user_statistics;

	// Check if username exists
	if (this->m_database->doesUserExists(username))
	{
		// Fill user statistics structure
		user_statistics.username = username;
		user_statistics.average_answer_time = std::to_string(m_database->getPlayerAverageAnswerTime(username));
		user_statistics.games_played = std::to_string(m_database->getNumOfPlayerGames(username));
		user_statistics.correct_answers = std::to_string(m_database->getNumOfCorrectAnswers(username));
		user_statistics.total_answers = std::to_string(m_database->getNumOfTotalAnswers(username));
		user_statistics.score = std::to_string(calculateScore(user_statistics));
	}
	else
	{
		throw std::exception("User with such username does not exist!");
	}

	return user_statistics;
}

int StatisticsManager::calculateScore(UserStatistics user)
{
	float score = 0;

	// Get user stats
	float average_answer_time = std::stof(user.average_answer_time);
	int games_played = std::stoi(user.games_played);
	int correct_answers = std::stoi(user.correct_answers);
	int total_answers = std::stoi(user.total_answers);

	// Check if stats aren't zeroes
	if (average_answer_time != 0 && games_played != 0 && correct_answers != 0 && total_answers != 0)
	{
		// Calculate score by formula
 		score = 100 * ((((float)correct_answers / total_answers) * games_played) / average_answer_time);
	}

	return (int)score;
}
