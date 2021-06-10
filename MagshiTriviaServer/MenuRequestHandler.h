#pragma once

// Project header files
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoggedUser.h"
#include "JsonResponsePacketSerializer.h"
#include "SqliteDatabase.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory* factory, LoggedUser& user);
	~MenuRequestHandler();
	bool IsRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	void DisconnectUser() override;

private:
	// Class members
	RoomManager* _room_manager;
	StatisticsManager _statistics_manager;
	RequestHandlerFactory* _request_handler_factory;
	LoggedUser _user;

	// Private methods
	RequestResult signout(RequestInfo request);
	RequestResult getRooms(RequestInfo request);
	RequestResult getPlayersInRoom(RequestInfo request);
	RequestResult getPersonalStats(RequestInfo request);
	RequestResult getHighScore(RequestInfo request);
	RequestResult joinRoom(RequestInfo request);
	RequestResult createRoom(RequestInfo request);
};