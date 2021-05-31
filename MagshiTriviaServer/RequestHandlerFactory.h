#pragma once

// Project header files
#include "LoginManager.h"
#include "IDatabase.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	// C'TORs / D'TORs
	RequestHandlerFactory();
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();

	// Getters / Setters
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager getStatisticsManager();

private:
	LoginManager _login_manager;
	RoomManager _room_manager;
	StatisticsManager _statistics_manager;

	IDatabase* _data_base;

};