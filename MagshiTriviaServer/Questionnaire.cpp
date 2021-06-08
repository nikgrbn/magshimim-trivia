#include "Questionnaire.h"

Questionnaire::Questionnaire()
{
    // Read .txt questions file
    std::string data;
    std::ifstream file("QuestionsRawDatabase.txt");
    while (std::getline(file, data)) {}
    file.close();

    // Parse string to json
    json js = json::parse(data);

    // Create std::list<Question> with json
    std::string question;
    std::string answers[4];
    unsigned int correct_ans = 0;
    for (int i = 0; i < js["results"].size(); i++)
    {
        // Get Question/Answers
        question = js["results"][i]["question"];
        for (int j = 0; j < 3; j++)
        {
            answers[j] = js["results"][i]["incorrect_answers"][j];
        }
        answers[3] = js["results"][i]["correct_answer"];

        // Shuffle answers
        std::random_shuffle(std::begin(answers), std::end(answers));

        // Find correct answer
        for (int j = 0; j < 4; j++)
        {
            if (answers[j] == js["results"][i]["correct_answer"])
            {
                correct_ans = j + 1;
                break;
            }
        }

        // Push question to a list
        this->questions.push_back(Question(question, answers[0], answers[1], answers[2], answers[3], correct_ans));
    }
}

std::list<Question> Questionnaire::getQuestionList()
{
    return this->questions;
}
