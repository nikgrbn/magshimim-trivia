#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory* factory, LoggedUser& user, Room& room, RoomManager* room_manager)
	: _user(user), _handle_factory(factory), _room(room), _room_manager(room_manager) {

}

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{ }

bool RoomMemberRequestHandler::IsRequestRelevant(RequestInfo info) {
	return (info.id == ProtocolCodes::LeaveRoomRequest || info.id == ProtocolCodes::StartGameRequest || info.id == ProtocolCodes::GetRoomStateRequest);
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info) {
	RequestResult response;

	switch (info.id)
	{
	case ProtocolCodes::LeaveRoomRequest: {
		response = this->leaveRoom(info);
		break;
	}

	case ProtocolCodes::StartGameRequest: {
		response = this->startGame(info);
		break;
	}

	case ProtocolCodes::GetRoomStateRequest: {
		response = this->getRoomState(info);
		break;
	}

	default:
		break;
	}

	return response;
}

void RoomMemberRequestHandler::DisconnectUser()
{ }

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info) {
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::startGame(RequestInfo info) {
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info) {
	return RequestResult();
}
