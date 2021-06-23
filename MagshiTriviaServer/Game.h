#pragma once

// Standard libarary
#include <iostream>
#include <vector>
#include <map>

// Project header files
#include "Questionnaire.h"
#include "LoggedUser.h"

typedef struct GameData {
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
}; GameData;

class Game {
public:
	//
private:
	std::vector<Question> _questions;
	std::map<LoggedUser, GameData> _players;
};