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
	this->_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	// Iterate through vector
	for (std::vector<LoggedUser>::iterator iter = this->_users.begin(); iter != this->_users.end(); ++iter)
	{
		// Erase user
		if (*iter == user)
		{
			this->_users.erase(iter);
			break;
		}
	}
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> usernames;

	// Iterate through vector
	for (auto user : this->_users)
	{
		// Push usernames
		usernames.push_back(user.getUsername());
	}

	return usernames;
}

RoomData Room::getRoomData()
{
	return this->_metadata;
}

void Room::activateRoom() {
	this->_metadata.isActive = active;
}
