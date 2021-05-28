#include "StatisticsManager.h"


std::vector<std::string> StatisticsManager::getStatistics()
{
    // Get user/score map from database
    std::map<std::string, int> scores_map = m_database->getScores();
    std::vector<std::string> scores_vector;

    // Iterate through map and push to vector
    std::map<std::string, int>::iterator it;
    for (it = scores_map.begin(); it != scores_map.end(); it++)
    {
        char line[1024];
        snprintf(line, 1024, "{\"username\": %s, \"score\": %d}", it->first.c_str(), it->second);
        scores_vector.push_back(line);
    }

    return scores_vector;
}

std::vector<std::string> StatisticsManager::getHighScore()
{
    return std::vector<std::string>();
}

std::vector<std::string> StatisticsManager::getUserStatistics()
{
    return std::vector<std::string>();
}
