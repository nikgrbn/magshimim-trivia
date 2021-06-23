#pragma once

// Standard libarary
#include <iostream>
#include <vector>
#include <map>

// Project header files
#include "Questionnaire.h"
#include "LoggedUser.h"
#include "SqliteDatabase.h"

typedef struct GameData {
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;

	GameData(Question cq, unsigned int cac, unsigned int wac, unsigned int aat)
		: currentQuestion(cq), correctAnswerCount(cac), wrongAnswerCount(wac), averageAnswerTime(aat) {};

} GameData;

class Game {
public:
	Game(std::vector<LoggedUser> users, unsigned int maxQuestions, IDatabase* db);
	Game(std::vector<LoggedUser> users, unsigned int maxQuestions);
	~Game() = default;

	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, unsigned int answer);
	void removePlayer(LoggedUser user);

private:
	unsigned int _maxQuestions;
	std::vector<Question> _questions;
	std::map<LoggedUser, GameData> _players;
	IDatabase* _db;
};