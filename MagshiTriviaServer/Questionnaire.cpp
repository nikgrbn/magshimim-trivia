#include "Questionnaire.h"

Questionnaire::Questionnaire()
{
    this->questions.push_back(Question(
        "What year was the very first model of the iPhone released?",
        "2011",
        "1998",
        "2007",
        "2003",
        3));

    this->questions.push_back(Question(
        "What’s the shortcut for the “copy” function on most computers?",
        "ctrl+c",
        "ctrl+x",
        "shift+f4",
        "alt+tab",
        1));

    this->questions.push_back(Question(
        "Which programming language shares its name with an island in Indonesia?",
        "Python",
        "Jakarta",
        "Java",
        "Kotlin",
        3));

    this->questions.push_back(Question(
        "Which of these programming languages is a low-level language?",
        "Rockstar",
        "C++",
        "Python",
        "Assembley",
        4));

    this->questions.push_back(Question(
        "Generally, which component of a computer draws the most power?",
        "Video Card",
        "Mother Board",
        "Processor",
        "Power Supply",
        1));

    this->questions.push_back(Question(
        "When Gmail first launched, how much storage did it provide for your email?",
        "512MB",
        "1GB",
        "5GB",
        "Unlimited",
        2));

    this->questions.push_back(Question(
        "All of the following programs are classified as raster graphics editors EXCEPT:",
        "Paint",
        "GIMP",
        "Adobe Photoshop",
        "Inkscape",
        4));

    this->questions.push_back(Question(
        "According to the International System of Units, how many bytes are in a kilobyte of RAM?",
        "512",
        "64",
        "1000",
        "1024",
        3));

    this->questions.push_back(Question(
        "HTML is what type of language?",
        "Macro Language",
        "Programming Language",
        "Scripting Language",
        "Markup Language",
        4));

    this->questions.push_back(Question(
        "In programming, what do you call functions with the same name but different implementations?",
        "Overloading",
        "Overriding",
        "Abstracting",
        "Inherting",
        1));
}

std::list<Question> Questionnaire::getQuestionList()
{
    return this->questions;
}
