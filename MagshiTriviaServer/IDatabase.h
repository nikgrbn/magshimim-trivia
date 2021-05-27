#pragma once

// Standard library
#include <iostream>
#include <list>

// Project header files
#include "Questionnaire.h"

class IDatabase {
public:
	virtual bool doesUserExists(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string mail) = 0;

	virtual std::list<Question> getQuestions(int num) = 0;
};