#include "RoomManager.h"

int RoomManager::createRoom(LoggedUser user, RoomData rm_data)
{
	// Create room
	this->_room_id_counter++;
	rm_data.id = this->_room_id_counter;
	Room room(rm_data);
	room.addUser(user);

	// Insert room to map
	this->_rooms.insert(std::pair<unsigned int, Room>(rm_data.id, room));

	return rm_data.id;
}

void RoomManager::deleteRoom(unsigned int ID)
{
	this->_rooms.erase(this->_rooms.find(ID));
	this->_room_id_counter--;
}

unsigned int RoomManager::getRoomState(int ID)
{
	std::map<unsigned int, Room>::iterator it = this->_rooms.find(ID);
	return (*it).second.getRoomData().isActive;
}

std::vector<Room> RoomManager::getRooms()
{
	std::vector<Room> rooms;

	// Iterate through map
	std::map<unsigned int, Room>::iterator it;
	for (it = this->_rooms.begin(); it != this->_rooms.end(); it++)
	{
		rooms.push_back(it->second);
	}

	return rooms;
}

void RoomManager::InsertUserIntoRoom(unsigned int room_id, LoggedUser& user) {
	this->_rooms.at(room_id).addUser(user);
}

void RoomManager::EraseUserFromRoom(unsigned int room_id, LoggedUser& user) {
	this->_rooms.at(room_id).removeUser(user);
}
