#pragma once

#include <iostream>
#include <list>

typedef struct Question {
	std::string question;
	std::string answers[4];
	unsigned int correct_ans;
}; Question;

class Questionnaire {
public:
	Questionnaire();
	~Questionnaire() = default;

	std::list<Question> getQuestionList();

private:
	std::list<Question> questions;
};