#include "Game.h"

Game::Game(std::vector<LoggedUser> users, unsigned int maxQuestions, IDatabase* db)
	: _maxQuestions(maxQuestions), _db(db)
{
	// Push random questions from database to vector
	std::list<Question> questionsList = this->_db->getQuestions(this->_maxQuestions);
	for (auto q : questionsList) {
		this->_questions.push_back(q);
	}

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
	for (auto q : questionsList) {
		this->_questions.push_back(q);
	}

	// Create startup game data structure
	GameData templateData (this->_questions.at(0), 0, 0, 0);

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

void Game::submitAnswer(LoggedUser user, unsigned int answer)
{
	std::map<LoggedUser, GameData>::iterator it = this->_players.find(user);

	// If answer is correct
	if (answer == it->second.currentQuestion.correct_ans)
	{
		// Update data
		it->second.correctAnswerCount += 1;
		it->second.currentQuestion = this->_questions.at(it->second.correctAnswerCount + it->second.wrongAnswerCount);
	}
	// If answer is incorrect
	else
	{
		// Update data
		it->second.wrongAnswerCount += 1;
		it->second.currentQuestion = this->_questions.at(it->second.correctAnswerCount + it->second.wrongAnswerCount);
	}
}

void Game::removePlayer(LoggedUser user)
{
	std::map<LoggedUser, GameData>::iterator it = this->_players.find(user);
	this->_players.erase(it);
}
