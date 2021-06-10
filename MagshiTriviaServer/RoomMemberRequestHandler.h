#pragma once

// Project header files
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "JsonResponsePacketSerializer.h"
class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory* factory, LoggedUser& user, Room& room, RoomManager* room_manager);
	~RoomMemberRequestHandler();

	bool IsRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	void DisconnectUser() override;
	RequestResult GetHandlerType() override;

private:
	Room _room;
	LoggedUser _user;
	RoomManager* _room_manager;
	RequestHandlerFactory* _handle_factory;

	RequestResult leaveRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);
};