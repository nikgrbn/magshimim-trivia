#include "RoomMemberRequestHandler.h"
#include "RequestHandlerFactory.h"

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
	RequestResult response{};
	LeaveRoomResponse leave_room_response{};

	try {
		this->_room.removeUser(this->_user);
		leave_room_response.status = ResponseStatus::LeaveRoomRequestSucces;
		response.newHandler = this->_handle_factory->createMenuRequestHandler(this->_user);
	} catch (std::exception& e) {
		leave_room_response.status = ResponseStatus::LeaveRoomRequestError;
		response.newHandler = this->_handle_factory->createMenuRequestHandler(this->_user);
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(leave_room_response);
	return response;
}

RequestResult RoomMemberRequestHandler::startGame(RequestInfo info) {
	/*TODO: realize what the fuck this method does */
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info) {
	RequestResult response{};
	GetRoomStateResponse get_room_state_response{};

	try {
		RoomData room_data = this->_room.getRoomData();
		get_room_state_response.players = this->_room.getAllUsers();
		get_room_state_response.questionCount = room_data.numOfQuestionsInGame;
		get_room_state_response.hasGameBegun = room_data.isActive;
		get_room_state_response.answerTimeout = room_data.timePerQuestion;

		response.newHandler = this;
		get_room_state_response.status = ResponseStatus::GetRoomStateRequestSuccess;
	} catch (std::exception& e) {
		response.newHandler = this;
		get_room_state_response.status = ResponseStatus::GetRoomStateRequestError;
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(get_room_state_response);
	return response;
}
