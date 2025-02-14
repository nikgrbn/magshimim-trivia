#pragma once

// Project header files
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "JsonResponsePacketSerializer.h"
class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory* factory, LoggedUser& user, Room& room, RoomManager* room_manager);
	~RoomAdminRequestHandler();

	bool IsRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	void DisconnectUser() override;
	RequestResult GetHandlerType() override;
private:
	Room _room;
	LoggedUser _user;
	RoomManager* _room_manager;
	RequestHandlerFactory* _handle_factory;

	RequestResult signout(RequestInfo request);
	RequestResult closeRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);
	RequestResult getRooms(RequestInfo request);
	RequestResult getPlayersInRoom(RequestInfo request);
};