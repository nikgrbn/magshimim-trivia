#pragma once

// Project header files
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoggedUser.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"
#include "SqliteDatabase.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory* factory, LoggedUser& user);
	bool IsRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;

private:
	// Class members
	RoomManager _room_manager;
	StatisticsManager _statistics_manager;
	RequestHandlerFactory* _request_handler_factory;
	LoggedUser _user;

	// Private methods
	RequestResult signout(RequestInfo);
	RequestResult getRooms(RequestInfo);
	RequestResult getPlayersInRoom(RequestInfo);
	RequestResult getPersonalStats(RequestInfo);
	RequestResult getHighScore(RequestInfo);
	RequestResult joinRoom(RequestInfo);
	RequestResult createRoom(RequestInfo);
};