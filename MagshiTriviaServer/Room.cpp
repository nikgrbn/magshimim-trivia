#include "Room.h"

Room::Room(unsigned int id, std::string name, unsigned int maxPlayers,
	unsigned int numOfQuestionsInGame, unsigned int timePerQuestion, unsigned int isActive)
{
	this->_metadata.id = id;
	this->_metadata.name = name;
	this->_metadata.maxPlayers = maxPlayers;
	this->_metadata.numOfQuestionsInGame = numOfQuestionsInGame;
	this->_metadata.timePerQuestion = timePerQuestion;
	this->_metadata.isActive = isActive;
}

void Room::addUser(LoggedUser user)
{
}

void Room::removeUser(LoggedUser user)
{
}

std::vector<std::string> Room::getAllUsers()
{
	return std::vector<std::string>();
}
