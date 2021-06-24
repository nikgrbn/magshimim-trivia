#pragma once

// Project header files
#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class RequestHandlerFactory
{
public:
	// C'TORs / D'TORs
	RequestHandlerFactory();
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser& user);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser& user, Room room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser& user, Room room);

	// Getters / Setters
	LoginManager& getLoginManager();
	RoomManager* getRoomManager();
	StatisticsManager getStatisticsManager();

private:
	LoginManager _login_manager;
	RoomManager* _room_manager;
	StatisticsManager _statistics_manager;

	IDatabase* _data_base;

};