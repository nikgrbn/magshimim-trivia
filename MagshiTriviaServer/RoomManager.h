#pragma once

// Standard libarary
#include <map>

// Project header files
#include "Room.h"

class RoomManager {
public:
	RoomManager() : _room_id_counter(0) {};
	~RoomManager() = default;

	void createRoom(LoggedUser user, RoomData rm_data);
	void deleteRoom(unsigned int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();

private:
	unsigned int _room_id_counter;
	std::map<unsigned int, Room> _rooms; // unsigned int is roomID
};