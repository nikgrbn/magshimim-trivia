#include "Game.h"

Game::Game(std::vector<LoggedUser> users, unsigned int maxQuestions, IDatabase* db)
	: _maxQuestions(maxQuestions), _db(db)
{
	// Push random questions from database to vector
	std::list<Question> questionsList = this->_db->getQuestions(this->_maxQuestions);
	std::copy(questionsList.begin(), questionsList.end(), std::back_inserter(this->_questions));

	// Create startup game data structure
	GameData templateData(this->_questions[0], 0, 0, 0);

	// Create map of users and data
	for (auto user : users)
	{
		this->_players.insert({ user, templateData });
	}
}

Game::Game(std::vector<LoggedUser> users, unsigned int maxQuestions)
	: _maxQuestions(maxQuestions)
{
	// Initialize database
	this->_db = new SqliteDatabase();

	// Push random questions from database to vector
	std::list<Question> questionsList = this->_db->getQuestions(this->_maxQuestions);
	std::copy(questionsList.begin(), questionsList.end(), std::back_inserter(this->_questions));

	// Create startup game data structure
	GameData templateData (this->_questions[0], 0, 0, 0);

	// Create map of users and data
	for (auto user : users)
	{
		this->_players.insert({ user, templateData });
	}
}

Question Game::getQuestionForUser(LoggedUser user)
{
	std::map<LoggedUser, GameData>::iterator it = this->_players.find(user);

	return it->second.currentQuestion;
}
