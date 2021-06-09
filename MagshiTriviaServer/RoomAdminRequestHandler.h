#pragma once

// Project header files
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "Room.h"
#include "LoggedUser.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

class RoomAdminRequestHanlder : public IRequestHandler
{
public:
	~RoomAdminRequestHanlder();

	bool IsRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;

private:
	Room _room;
	LoggedUser _user;
	RoomManager* _room_manager;
	RequestHandlerFactory* _handle_factory;

	RequestResult closeRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);
};