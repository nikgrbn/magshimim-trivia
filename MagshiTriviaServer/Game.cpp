#include "Game.h"

Game::Game(std::vector<LoggedUser> users, GameData gameData, unsigned int maxQuestions, IDatabase* db)
	: _maxQuestions(maxQuestions), _db(db)
{
	// Create map of users and data
	for (auto user : users)
	{
		this->_players.insert({ user, gameData });
	}

	// Push random questions from database to vector
	std::list<Question> questionsList = this->_db->getQuestions(this->_maxQuestions);
	std::copy(questionsList.begin(), questionsList.end(), std::back_inserter(this->_questions));
}

Game::Game(std::vector<LoggedUser> users, GameData gameData, unsigned int maxQuestions)
	: _maxQuestions(maxQuestions)
{
	// Create map of users and data
	for (auto user : users)
	{
		this->_players.insert({ user, gameData });
	}

	// Initialize database
	this->_db = new SqliteDatabase();

	// Push random questions from database to vector
	std::list<Question> questionsList = this->_db->getQuestions(this->_maxQuestions);
	std::copy(questionsList.begin(), questionsList.end(), std::back_inserter(this->_questions));
}
