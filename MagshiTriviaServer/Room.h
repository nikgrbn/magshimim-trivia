#pragma once

// Standard libarary
#include <iostream>
#include <vector>

// Project header files
#include "LoggedUser.h"

constexpr unsigned int active = 1;
constexpr unsigned int inactive = 0;

typedef struct RoomData {
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
}; RoomData;

class Room {
public:
	Room(RoomData rd) : _metadata(rd) {};
	Room(unsigned int id, std::string name, unsigned int maxPlayers,
		unsigned int numOfQuestionsInGame, unsigned int timePerQuestion, unsigned int isActive = 0);
	~Room() = default;

	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	RoomData getRoomData();
	void activateRoom();

private:
	RoomData _metadata;
	std::vector<LoggedUser> _users;
};
