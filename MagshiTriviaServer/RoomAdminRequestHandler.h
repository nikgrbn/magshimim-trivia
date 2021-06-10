#pragma once

// Project header files
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "JsonResponsePacketSerializer.h"
class RequestHandlerFactory;

class RoomAdminRequestHanlder : public IRequestHandler
{
public:
	RoomAdminRequestHanlder(RequestHandlerFactory* factory, LoggedUser& user, Room& room, RoomManager* room_manager);
	~RoomAdminRequestHanlder();

	bool IsRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	void DisconnectUser() override;

private:
	Room _room;
	LoggedUser _user;
	RoomManager* _room_manager;
	RequestHandlerFactory* _handle_factory;

	RequestResult closeRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);
};