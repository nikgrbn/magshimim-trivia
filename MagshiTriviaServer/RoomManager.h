#pragma once

// Standard libarary
#include <map>

// Project header files
#include "Room.h"

class RoomManager {
public:
	RoomManager() {};
	~RoomManager() = default;

	void createRoom(LoggedUser user, RoomData rm_data);
	void deleteRoom(unsigned int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();

private:
	std::map<unsigned int, Room> _rooms; // unsigned int is roomID
};