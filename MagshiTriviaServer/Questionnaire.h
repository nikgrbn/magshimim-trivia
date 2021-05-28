#pragma once

#include <iostream>
#include <list>


typedef struct Question {
	std::string question;
	std::string answers[4];
	unsigned int correct_ans;

	Question();
	Question(std::string qu, std::string a1, std::string a2, std::string a3, std::string a4, unsigned int cor_ans)
	{
		question = qu;
		answers[0] = a1;
		answers[1] = a2;
		answers[2] = a3;
		answers[3] = a4;
		correct_ans = cor_ans;
	}
}; Question;

class Questionnaire {
public:
	Questionnaire();
	~Questionnaire() = default;

	std::list<Question> getQuestionList();

private:
	std::list<Question> questions;
};