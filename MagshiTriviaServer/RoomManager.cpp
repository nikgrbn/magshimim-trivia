#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData rm_data)
{
	// Create room
	Room room(rm_data);
	room.addUser(user);

	// Insert room to map
	this->_rooms.insert(std::pair<unsigned int, Room>(rm_data.id, room));
}

void RoomManager::deleteRoom(unsigned int ID)
{
	this->_rooms.erase(this->_rooms.find(ID));
}

unsigned int RoomManager::getRoomState(int ID)
{
	std::map<unsigned int, Room>::iterator it = this->_rooms.find(ID);
	return (*it).second.getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;

	// Iterate through map
	std::map<unsigned int, Room>::iterator it;
	for (it = this->_rooms.begin(); it != this->_rooms.end(); it++)
	{
		rooms.push_back(it->second.getRoomData());
	}

	return rooms;
}
